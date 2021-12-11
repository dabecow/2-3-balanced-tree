//
// Created by Andrew on 03.11.2021.
//

#ifndef TREE_BALANCEDTREE_H
#define TREE_BALANCEDTREE_H

#include "Entry.h"
#include "Node.h"

template<class K, class V>
class BalancedTree {

public:

    BalancedTree() {
        size = 0;
        root = nullptr;
    }

    Node<K, V>* addEntry(Entry<K, V>* entry){
        Node<K, V>* result = insert(root, entry);

        if (root == nullptr)
            root = result;

        size++;
        return result;
    }

    Entry<K, V>* getEntry(K* key){
        if (root == nullptr)
            return nullptr;

        auto foundNode = getNode(root, key);

        if (foundNode == nullptr)
            return nullptr;

        for (int i = 0; i < 3; ++i) {
            auto entry = foundNode->getEntries()[i];
            K* iterKey = entry->getKey();
            if (*iterKey == *key)
                return entry;
        }

        return nullptr;
    }

    void removeEntry(K* key){
        if (root != nullptr)
            remove(root, key);

    }

    ~BalancedTree() {
        removeNodesRecursively(root);
    }

private:
    Node<K, V>* root;
    int size;

    void removeNodesRecursively(Node<K, V>* node){
        if (node->getFirst() != nullptr)
            removeNodesRecursively(node->getFirst());
        if (node->getSecond() != nullptr)
            removeNodesRecursively(node->getSecond());
        if (node->getThird() != nullptr)
            removeNodesRecursively(node->getThird());

        delete node;
    }

    Node<K, V>* insert(Node<K, V>* node, Entry<K, V> *entry){
        if (node == nullptr)
            return new Node<K, V>(nullptr, entry);

        if (node->isLeaf())
            node->addEntry(entry);
        else if (entry->getKey() <= node->getKey(0))
            insert(node->getFirst(), entry);
        else if (node->getSize() == 1 || (node->getSize() == 2 && entry->getKey() <= node->getKey(1)))
            insert(node->getSecond(), entry);
        else
            insert(node->getThird(), entry);

        return split(node);
    }

    Node<K, V>* split(Node<K,V> *node){
        if (node->getSize() < 3)
            return node;

        Entry<K, V>* const* entries = node->getEntries();

        auto* left = new Node<K, V>(
                entries[0], node->getFirst(), node->getSecond(), nullptr, nullptr, node->getParent());
        auto* middle = new Node<K, V>(entries[2], node->getThird(), node->getFourth(), nullptr, nullptr, node->getParent());

        if (node->getParent() == nullptr) {
            left->setParent(node);
            middle->setParent(node);
            node->becomeNodeOf2(entries[1], left, middle);

            return node;
        }

        Node<K, V>* parent = node->getParent();
        parent->addEntry(entries[1]);

        if (parent->getFirst() == node)
            parent->setFirst(nullptr);
        else if (parent->getSecond() == node)
            parent->setSecond(nullptr);
        else if (parent->getThird() == node)
            parent->setThird(nullptr);

        if (parent->getFirst() == nullptr) {
            parent->setFourth(parent->getThird());
            parent->setThird(parent->getSecond());
            parent->setSecond(middle);
            parent->setFirst(left);
        } else if (parent->getSecond() == nullptr) {
            parent->setFourth(parent->getThird());
            parent->setThird(middle);
            parent->setSecond(left);
        } else {
            parent->setFourth(middle);
            parent->setThird(left);
        }

        Node<K,V>* tmp = parent;
        delete node;
        return tmp;
    }

    Node<K, V>* getNode(Node<K, V>* node, K* key){
        if (node == nullptr)
            return nullptr;

        Entry<K, V>* const* entries = node->getEntries();

        if (node->getKeyIdx(key) != -1)
            return node;
        else if (*key < *entries[0]->getKey())
            return getNode(node->getFirst(), key);
        else if ((node->getSize() == 2 && *key < *entries[1]->getKey()) || (node->getSize() == 1))
            return getNode(node->getSecond(), key);
        else if (node->getSize() == 2)
            return getNode(node->getThird(), key);
    }

    Node<K, V>* getNodeWithMinKey(Node<K, V>* node){
        if (node == nullptr)
            return nullptr;

        if (node->getFirst() == nullptr)
            return node;

        return getNodeWithMinKey(node->getFirst());
    }

    Node<K, V>* remove(Node<K, V>* _root, K* key) {
        Node<K, V> *node = getNode(_root, key);

        if (node == nullptr)
            return nullptr;

        Node<K, V>* nodeWithMinKey = node->getKey(0) == key ? getNodeWithMinKey(node->getSecond()) :
                                     getNodeWithMinKey(node->getThird());

        if (nodeWithMinKey != nullptr) {

            Entry<K, V> &entryToMove  = (key == node->getEntries()[0]->getKey() ? *node->getEntries()[0] : *node->getEntries()[1]);
            node->swapEntriesPointers(entryToMove, *nodeWithMinKey->getEntries()[0]);
            node = nodeWithMinKey;
        }

        node->removeEntry(*key);
        size--;
        return fix(node);
    }


    Node<K, V>* fix(Node<K,V> *node){
        // удаляли из корня единственный элемент
        if (node->getSize() == 0 && node->getParent() == nullptr){
            delete node;
            return nullptr;
        }

        // удаляли у листа с родителем одно из значений
        if (node->getSize() != 0) {
            if (node->getParent() != nullptr)
                return fix(node->getParent());
            else return node;
        }

        Node<K,V>* parent = node->getParent();
        if (parent->getFirst()->getSize() == 2 || parent->getSecond()->getSize() == 2 || parent->getSize() == 2)
            node = redistribute(node);
        else node = merge(node);

        return fix(node);
    }

    void redistributeParentSize2LeavesSizeBelow2(Node<K, V>* node, Node<K, V>* parent, Node<K, V>* first, Node<K, V>* second, Node<K, V>* third) {
        if (first == node) {
            parent->setFirst(parent->getSecond());
            parent->setSecond(parent->getThird());
            parent->setThird(nullptr);

            parent->getFirst()->addEntry(parent->getEntries()[0]);
            parent->getFirst()->setThird(parent->getFirst()->getSecond());
            parent->getFirst()->setSecond(parent->getFirst()->getFirst());

            if (node->getFirst() != nullptr)
                parent->getFirst()->setFirst(node->getFirst());
            else if (node->getSecond() != nullptr)
                parent->getFirst()->setFirst(node->getSecond());

            if (parent->getFirst()->getFirst() != nullptr)
                parent->getFirst()->getFirst()->setParent(parent->getFirst());

            parent->removeEntry(*parent->getEntries()[0]->getKey());
            delete first;

        } else if (second == node) {
            first->addEntry(parent->getEntries()[0]);
            parent->removeEntry(*parent->getEntries()[0]->getKey());

            if (node->getFirst() != nullptr)
                first->setThird(node->getFirst());
            else if (node->getSecond() != nullptr)
                first->setThird(node->getSecond());

            if (first->getThird() != nullptr)
                first->getThird()->setParent(first);

            parent->setSecond(parent->getThird());
            parent->setThird(nullptr);

            delete second;
        } else if (third == node) {
            second->addEntry(parent->getEntries()[1]);
            parent->setThird(nullptr);
            parent->removeEntry(*parent->getEntries()[1]->getKey());

            if (node->getFirst() != nullptr)
                second->setThird(node->getFirst());
            else if (node->getSecond() != nullptr)
                second->setThird(node->getSecond());

            if (second->getThird() != nullptr)
                second->getThird()->setParent(second);

            delete third;
        }
    }

    void redistributeParentSize2LeavesSize2(Node<K, V>* node, Node<K, V>* parent, Node<K, V>* first, Node<K, V>* second, Node<K, V>* third){
        if (third == node) {
            if (node->getFirst() != nullptr){
                node->setSecond(node->getFirst());
                node->setFirst(nullptr);
            }

            node->addEntry(parent->getEntries()[1]);

            if (second->getSize() == 2) {
                parent->setEntryAtIdx(second->getEntries()[1], 1);
                second->removeEntry(*second->getEntries()[1]->getKey());
                node->setFirst(second->getThird());
                second->setThird(nullptr);

                if (node->getFirst() != nullptr)
                    node->getFirst()->setParent(node);

            } else if (first->getSize() == 2) {
                parent->setEntryAtIdx(second->getEntries()[0], 1);

                node->setFirst(second->getSecond());
                second->setSecond(second->getFirst());

                if (node->getFirst() != nullptr)
                    node->getFirst()->setParent(node);

                second->setEntryAtIdx(parent->getEntries()[0], 0);
                parent->setEntryAtIdx(first->getEntries()[1], 0);
                first->removeEntry(*first->getEntries()[1]->getKey());
                second->setFirst(first->getThird());

                if (second->getFirst() != nullptr)
                    second->getFirst()->setParent(second);

                first->setThird(nullptr);
            }
        } else if (second == node) {

            if (third->getSize() == 2) {

                if (node->getFirst() == nullptr) {
                    node->setFirst(node->getSecond());
                    node->setSecond(nullptr);
                }

                second->addEntry(parent->getEntries()[1]);
                parent->setEntryAtIdx(third->getEntries()[0], 1);
                third->removeEntry(*third->getEntries()[0]->getKey());
                second->setSecond(third->getFirst());

                if (second->getSecond() != nullptr)
                    second->getSecond()->setParent(second);

                third->setFirst(third->getSecond());
                third->setSecond(third->getThird());
                third->setThird(nullptr);

            } else if (first->getSize() == 2){

                if (node->getSecond() == nullptr){
                    node->setSecond(node->getFirst());
                    node->setFirst(nullptr);
                }

                second->addEntry(parent->getEntries()[0]);
                parent->setEntryAtIdx(first->getEntries()[1], 0);

                first->removeEntry(*first->getEntries()[1]->getKey());
                second->setFirst(first->getThird());
                if (second->getFirst() != nullptr)
                    second->getFirst()->setParent(second);

                first->setThird(nullptr);
            }
        } else if (first == node) {

            if (node->getFirst() == nullptr){
                node->setFirst(node->getSecond());
                node->setSecond(nullptr);
            }

            first->addEntry(parent->getEntries()[0]);
            if (second->getSize() == 2){
                parent->setEntryAtIdx(second->getEntries()[0], 0);

                second->removeEntry(*second->getEntries()[0]->getKey());

                first->setSecond(second->getFirst());
                if (first->getSecond() != nullptr)
                    first->getSecond()->setParent(first);

                second->setFirst(second->getSecond());
                second->setSecond(second->getThird());
                second->setThird(nullptr);
            } else if (third->getSize() == 2) {
                parent->setEntryAtIdx(second->getEntries()[0], 0);
                second->setEntryAtIdx(parent->getEntries()[1], 0);
                parent->setEntryAtIdx(third->getEntries()[0], 1);

                third->removeEntry(*third->getEntries()[0]->getKey());
                first->setSecond(second->getFirst());

                if (first->getSecond() != nullptr)
                    first->getSecond()->setParent(first);

                second->setFirst(second->getSecond());
                second->setSecond(third->getFirst());

                if (second->getSecond() != nullptr)
                    second->getSecond()->setParent(second);

                third->setFirst(third->getSecond());
                third->setSecond(third->getThird());
                third->setThird(nullptr);
            }

        }
    }

    void redistributeParentSize1(Node<K, V>* node, Node<K, V>* parent, Node<K, V>* parentFirst, Node<K, V>* parentSecond){
        node->addEntry(parent->getEntries()[0]);

        if (parentFirst == node && parentSecond->getSize() == 2) { //наша нода - левая у ее родителя, а у средней 2 значения
            parent->setEntryAtIdx(parentSecond->getEntries()[0], 0); //берем первое значение из правого поддерева
            parentSecond->removeEntry(*parentSecond->getKey(0));

            if (node->getFirst() == nullptr)            //дорабатываем значения ноды и значения его среднего поддерева
                node->setFirst(node->getSecond());      //для соответствия алгоритму: если не осталось левого поддерева,
            //им становится среднее, а средним становится левое поддерево этого прошлого "среднего"
            node->setSecond(parentSecond->getFirst());        //     2                3
            parentSecond->setFirst(parentSecond->getSecond());      //  _     3,4  ->   2       4
            parentSecond->setSecond(parentSecond->getThird());
            parentSecond->setThird(nullptr);

            if (node->getSecond() != nullptr)
                node->getSecond()->setParent(node);

        } else if (parentSecond == node && parentFirst->getSize() == 2) { //наша нода - средняя, а у левого поддерева родителя 2 элемента
            parent->setEntryAtIdx(parentFirst->getEntries()[1], 0);
            parentFirst->removeEntry(*parentFirst->getKey(1));

            if (node->getSecond() == nullptr)
                node->setSecond(node->getFirst());

            node->setFirst(parentFirst->getThird());
            parentFirst->setThird(nullptr);

            if (node->getFirst() != nullptr)
                node->getFirst()->setParent(node);
        }
    }

    Node<K, V>* redistribute(Node<K, V>* node){
        auto parent = node->getParent();
        auto first = parent->getFirst();
        auto second = parent->getSecond();
        auto third = parent->getThird();

        if (parent->getSize() == 2 && first->getSize() < 2 && second->getSize() < 2 && third->getSize() < 2) {

            redistributeParentSize2LeavesSizeBelow2(node, parent, first, second, third);

        } else if (parent->getSize() == 2 && (first->getSize() == 2 || second->getSize() == 2 || third->getSize() == 2)) {

            redistributeParentSize2LeavesSize2(node, parent, first, second, third);

        } else if (parent->getSize() == 1) { //у parent 1 элемент, перемещаем его в листовой нод

            redistributeParentSize1(node, parent, first, second);

        }

        return parent;
    }

    Node<K, V>* merge(Node<K, V>* node){
        auto parent = node->getParent();

        if (parent->getFirst() == node) {

            parent->getSecond()->addEntry(parent->getEntries()[0]);
            parent->getSecond()->setThird(parent->getSecond()->getSecond());
            parent->getSecond()->setSecond(parent->getSecond()->getFirst());

            if (node->getFirst() != nullptr)
                parent->getSecond()->setFirst(node->getFirst());
            else if (node->getSecond() != nullptr)
                parent->getSecond()->setFirst(node->getSecond());

            if (parent->getSecond()->getFirst() != nullptr)
                parent->getSecond()->getFirst()->setParent(parent->getSecond());

            parent->removeEntry(*parent->getEntries()[0]->getKey());

            delete parent->getFirst();
            parent->setFirst(nullptr);

        } else if (parent->getSecond() == node) {

            parent->getFirst()->addEntry(parent->getEntries()[0]);

            if (node->getFirst() != nullptr)
                parent->getFirst()->setThird(node->getFirst());
            else if (node->getSecond() != nullptr)
                parent->getFirst()->setThird(node->getSecond());

            if (parent->getFirst()->getThird() != nullptr)
                parent->getFirst()->getThird()->setParent(parent->getFirst());

            parent->removeEntry(*parent->getEntries()[0]->getKey());

            delete parent->getSecond();
            parent->setSecond(nullptr);
        }

        if (parent->getParent() == nullptr) {
            Node<K, V> *tmp = nullptr;

            if (parent->getFirst() != nullptr)
                tmp = parent->getFirst();
            else
                tmp = parent->getSecond();

            tmp->setParent(nullptr);

            if (root == parent)
                root = tmp;

            delete parent;
            return tmp;
        }

        return parent;
    }




};


#endif //TREE_BALANCEDTREE_H

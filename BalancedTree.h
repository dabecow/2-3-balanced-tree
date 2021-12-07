//
// Created by Andrew on 03.11.2021.
//

#ifndef TREE_BALANCEDTREE_H
#define TREE_BALANCEDTREE_H

#include "Entry.h"
#include "Node.h"

template<class K, class V>
class BalancedTree {

private:
    Node<K, V>* root;
    int size;

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
        auto* right = new Node<K, V>(entries[2], node->getThird(), node->getFourth(), nullptr, nullptr, node->getParent());

        if (left->getFirst() != nullptr)
            left->getFirst()->setParent(left);
        if (left->getSecond() != nullptr)
            left->getSecond()->setParent(left);
        if (right->getFirst() != nullptr)
            right->getFirst()->setParent(right);
        if (right->getSecond() != nullptr)
            right->getSecond()->setParent(right);

        if (node->getParent() != nullptr){

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
                parent->setSecond(right);
                parent->setFirst(left);
            } else if (parent->getSecond() == nullptr) {
                parent->setFourth(parent->getThird());
                parent->setThird(right);
                parent->setSecond(left);
            } else {
                parent->setFourth(right);
                parent->setThird(left);
            }

            Node<K,V>* tmp = parent;
            delete node;
            return tmp;
        } else {
            left->setParent(node);
            right->setParent(node);
            node->become_node2(entries[1], left, right);

            return node;
        }
    }

    Node<K, V>* getNode(Node<K, V>* node, K* key){
        if (node == nullptr)
            return nullptr;

        Entry<K, V>* const* entries = node->getEntries();

        if (node->getKeyIdx(key) != -1)
            return node;
        else if (key < entries[0]->getKey())
            return getNode(node->getFirst(), key);
        else if ((node->getSize() == 2 && key < entries[1]->getKey()) || (node->getSize() == 1))
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
//        return fix(node);
    }


    Node<K, V>* fix(Node<K,V> *node){
        if (node->getSize() == 0 && node->getParent() == nullptr){
            delete node;
            return nullptr;
        }

        if (node->getSize() != 0) {
            if (node->getParent() != nullptr)
                return fix(node->getParent());
            else return node;
        }

//        Node<K,V>* parent = node->getParent();
//        if (parent->getFirst()->getSize() == 2 || parent->getSecond()->getSize() == 2 || parent->getSize() == 2)
//            node = redistribute(node);
//        else if (parent->getSize() == 2 && parent->getThird()->getSize() == 2)
//            node = redistribute(node);
//        else node = merge(node);

        return fix(node);
    }

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

        for (int i = 0; i < 3; ++i) {
            auto entry = foundNode->getEntries()[i];
            K* iterKey = entry->getKey();
            if (iterKey == key)
                return entry;
        }

        return nullptr;
    }

    void removeEntry(K* key){
        if (root != nullptr)
            remove(root, key);

    }


};


#endif //TREE_BALANCEDTREE_H

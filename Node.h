//
// Created by Andrew on 03.11.2021.
//

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "Entry.h"

template<class K, class V>
class Node {

private:

    int size;
    Entry<K, V>* entries[3] = {nullptr, nullptr, nullptr};

    Node<K, V>* first;
    Node<K, V>* second;
    Node<K, V>* third;
    Node<K, V>* fourth;

    Node<K, V>* parent;

    void sortEntries(){

        if (size < 2)
            return;

        if (entries[0]->getKey() > entries[1]->getKey())
            swapEntries(0, 1);

        if (size == 3){
            if (entries[0]->getKey() > entries[2]->getKey())
                swapEntries(0, 2);

            if (entries[1]->getKey() > entries[2]->getKey())
                swapEntries(1, 2);
        }

    }

public:

    void swapEntries(int idx1, int idx2){
        Entry<K, V>* tmp = entries[idx1];

        entries[idx1] = entries[idx2];
        entries[idx2] = tmp;
    }

    void swapEntriesPointers(Entry<K, V> &e1, Entry<K, V> &e2){
        Entry<K, V> tmp = e1;
        e1 = e2;
        e2 = tmp;
    }

    void setEntryAtIdx(Entry<K, V>* entry, int idx){
        entries[idx] = entry;
    }

    Entry<K, V> *const *getEntries() const {
        return entries;
    }

    explicit Node(Node<K, V>* parent, Entry<K, V> *entry): parent(parent) {
        size = 1;
        entries[0] = entry;

        first = nullptr;
        second = nullptr;
        third = nullptr;
        fourth = nullptr;
    };

    Node(Entry<K, V> *entry, Node<K, V> *first, Node<K, V> *second, Node<K, V> *third, Node<K, V> *fourth,
         Node<K, V> *parent) : first(first), second(second), third(third), fourth(fourth),
                               parent(parent) {
        entries[0] = entry;
        size = 1;

        if (first != nullptr)
            first->setParent(this);
        if (second != nullptr)
        second->setParent(this);
    };

    bool isLeaf(){
        return first == nullptr && second == nullptr && third == nullptr;
    }

    void addEntry(Entry<K, V> *entry){
        if (entry == nullptr)
            return;

        entries[size] = entry;

        size++;

        sortEntries();
    }

    void removeEntry(K key){
        if (size >= 1 && *entries[0]->getKey() == key) {
            entries[0] = entries[1];
            entries[1] = entries[2];
            size--;
        } else if (size == 2 && *entries[1]->getKey() == key){
            entries[1] = entries[2];
            size--;
        }
    }

    Node<K, V> *getFirst() const {
        return first;
    }

    Node<K, V> *getSecond() const {
        return second;
    }

    Node<K, V> *getThird() const {
        return third;
    }


    Node<K, V> *getFourth() const {
        return fourth;
    }

    Node<K, V> *getParent() const {
        return parent;
    }

    int getSize() const {
        return size;
    }

    K* getKey(int idx){
        return entries[idx]->getKey();
    }

    int getKeyIdx(K* key){
        for (int i = 0; i < size; ++i) {
            if (*entries[i]->getKey() == *key)
                return i;
        }

        return -1;
    }

    void setFirst(Node<K, V> *node) {
        Node::first = node;
    }

    void setSecond(Node<K, V> *node) {
        Node::second = node;
    }

    void setThird(Node<K, V> *node) {
        Node::third = node;
    }

    void setFourth(Node<K, V> *node) {
        Node::fourth = node;
    }

    void setParent(Node<K, V> *node) {
        Node::parent = node;
    }

    void becomeNodeOf2(Entry<K, V>* entry, Node<K, V>* firstNode, Node<K, V>* secondNode){
        entries[0] = entry;
        entries[1] = nullptr;
        entries[2] = nullptr;

        this->first = firstNode;
        this->second = secondNode;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
    }
};


#endif //TREE_NODE_H

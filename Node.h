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
    Entry<K, V>* entries[3];

    Node<K, V>* first;
    Node<K, V>* second;
    Node<K, V>* third;

    Node<K, V>* parent;

    void swapEntries(int idx1, int idx2){
        Entry<K, V>* tmp = entries[idx1];

        entries[idx1] = entries[idx2];
        entries[idx2] = tmp;
    }

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

    explicit Node(Node<K, V>* parent, Entry<K, V> entry): parent(parent) {
        size = 1;
        entries[0] = entry;

        first = nullptr;
        second = nullptr;
        third = nullptr;
    }

    bool isLeaf(){
        return first == nullptr && second == nullptr && third == nullptr;
    }

    void addEntry(Entry<K, V> entry){
        if (entry == nullptr)
            return;

        entries[size] = entry;

        sortEntries();
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

    int getSize() const {
        return size;
    }

    int getKey(int idx){
        return entries[idx]->getKey();
    }
};


#endif //TREE_NODE_H

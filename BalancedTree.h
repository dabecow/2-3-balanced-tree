//
// Created by Andrew on 03.11.2021.
//

#ifndef TREE_BALANCEDTREE_H
#define TREE_BALANCEDTREE_H

#include "Node.h"

template<class K, class V>
class BalancedTree {

private:
    Node<K, V>* root;
    int size;

public:

    BalancedTree() {
        size = 0;
        root = nullptr;
    }

    Node<K, V>* insert(Node<K, V>* node, Entry<K, V> entry){
        if (node == nullptr)
            return new Node<K, V>(nullptr, entry);

        if (node->isLeaf())
            node->addEntry(entry);
        else if (entry.getKey() <= node->getKey(0))
            insert(node->getFirst(), entry);
        else if (node->getSize() == 1 || (node->getSize() == 2 && entry.getKey() <= node->getKey(1)))
            insert(node->getSecond(), entry);
        else
            insert(node->getThird(), entry);

        //return split(node);
    }

    int addValue(V value){
        if (this->root == nullptr) {
            root = new Node<K, V>(nullptr, value);
            return;
        }

        if (this->root->getValuesSize() == 1){

        }
    }
};


#endif //TREE_BALANCEDTREE_H

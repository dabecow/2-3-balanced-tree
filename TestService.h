//
// Created by Andrew on 10.12.2021.
//

#ifndef TREE_TESTSERVICE_H
#define TREE_TESTSERVICE_H

#include <string>
#include "Entry.h"
#include "BalancedTree.h"

class TestService {

private:
    BalancedTree<int, std::string> *tree;
    Entry<int, std::string> *entries;

public:
    void insertElements(int numberOfElements){
        tree = new BalancedTree<int, std::string>();

        entries = new Entry<int, std::string>[numberOfElements]();

        for (int i = 0; i < numberOfElements; ++i) {
            entries[i].setKey(&i);
            entries[i].setValue(new std::string(""));
            tree->addEntry(&entries[i]);
        }
    }

    void initTree(int numberOfElements){
        tree = new BalancedTree<int, std::string>();

        entries = new Entry<int, std::string>[numberOfElements]();

        for (int i = 0; i < numberOfElements; ++i) {
            entries[i].setKey(&i);
            entries[i].setValue(new std::string(""));
            tree->addEntry(&entries[i]);
        }
    }

    void removeTree(){
        delete tree;
        delete[] entries;
    }

    void searchElement(int key){
        tree->getEntry(&key);
    }

    void removeElement(int key){
        tree->removeEntry(&key);
    }
};


#endif //TREE_TESTSERVICE_H

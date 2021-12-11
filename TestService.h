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
    int* keyValues;

public:

    void insertElement(int key){
        tree->addEntry(new Entry<int, std::string>(&key, new std::string("")));
    }

    void initTree(int numberOfElements){
        tree = new BalancedTree<int, std::string>();

        entries = new Entry<int, std::string>[numberOfElements]();
        keyValues = new int[numberOfElements];

        int keyValue = 0;
        for (int i = 0; i < numberOfElements; ++i) {
            keyValues[i] = keyValue++;

            entries[i].setKey(&keyValues[i]);
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
        int* pKey = &key;
        tree->removeEntry(pKey);
    }

    BalancedTree<int, std::string> *getTree() const {
        return tree;
    }

    Entry<int, std::string> *getEntries() const {
        return entries;
    }

};


#endif //TREE_TESTSERVICE_H

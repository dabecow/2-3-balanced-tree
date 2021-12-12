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
    int* keyValues1;

    void printNode(Node<int, std::string>* node, int level){

        if (node == nullptr)
            return;

        printNode(node->getFirst(), level + 1);

        for (int i = 0; i < level - 1; ++i) {
            std::cout << "      ";
        }


        if (level != 0) {
            if (node->getParent()->getSize() == 2)
                std::cout << "   ";
            if (node == node->getParent()->getFirst())
                std::cout << "/--->";
            else if (node == node->getParent()->getSecond())
                std::cout << "|--->";
            else
                std::cout << "\\--->";
        }
        std::cout << "[" << *node->getEntries()[0]->getKey();
        if (node->getSize() == 2)
            std::cout << ", " << *node->getEntries()[1]->getKey() << "]" << std::endl;
        else
            std::cout << "]" << std::endl;

        printNode(node->getSecond(), level + 1);

        printNode(node->getThird(), level + 1);

    }

public:

    void insertElement(int key){
        tree->addEntry(new Entry<int, std::string>(&key, new std::string("")));
    }

    void insertElement(int key, std::string value){
        tree->addEntry(new Entry<int, std::string>(&key, &value));
    }

    void initTree(int numberOfElements){
        tree = new BalancedTree<int, std::string>();

        entries = new Entry<int, std::string>[numberOfElements]();
        keyValues = new int[numberOfElements];

        int keyValue = 1;
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

    void searchAndPrintElement(int key){
        auto entry = tree->getEntry(&key);
        if (entry != nullptr)
            std::cout << "Found entry with key: " << *entry->getKey() << " and value: \"" << *entry->getValue() << "\"" << std::endl;
    }

    void removeElement(int key){
        int* pKey = &key;
        tree->removeEntry(pKey);
    }

    void printTree(){
        removeElement(8);
        printNode(tree->getRoot(), 0);
        std::cout << "\n\n" << std::endl;
        keyValues1 = new int[1];
        keyValues1[0] = 11;
        tree->addEntry(new Entry<int, std::string>(&keyValues1[0], new std::string("Hello")));
        printNode(tree->getRoot(), 0);
        searchAndPrintElement(11);
    }

};


#endif //TREE_TESTSERVICE_H

#include <iostream>
#include "BalancedTree.h"
#include "Node.h"
#include "Entry.h"

int main() {
    auto *tree = new BalancedTree<int, std::string>;
    int intValues[] = {1, 2, 3, 4, 5, 6, 7};
    std::string stringValues[] = {"Hello", ", ", "World", "!", "", "", ""};

    for (int i = 0; i < 7; ++i) {
        tree->addEntry(new Entry<int, std::string>(&intValues[i], &stringValues[i]));
    }
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(1), new std::string("Hello")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(2), new std::string(", ")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(3), new std::string("World")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(4), new std::string("!")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(5), new std::string("")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(6), new std::string("")));
//    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(7), new std::string("")));

    for (int i = 1; i <= 7; ++i) {
        std::cout << *tree->getEntry(&i)->getValue();
    }

    int keyToRemove = 1;
    tree->removeEntry(&keyToRemove);


    Entry<int, std::string>* iterEntry;

    for (int i = 1; i <= 7; ++i) {
        iterEntry = tree->getEntry(&i);
        if (iterEntry != nullptr)
            std::cout << iterEntry->getValue();
    }

    return 0;
}

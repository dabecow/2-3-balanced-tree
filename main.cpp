#include <iostream>
#include "BalancedTree.h"
#include "Node.h"
#include "Entry.h"

int main() {
    auto *tree = new BalancedTree<int, std::string>;
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(1), new std::string("Hello")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(2), new std::string(", ")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(3), new std::string("World")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(4), new std::string("!")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(5), new std::string("")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(6), new std::string("")));
    tree->addEntry(new Entry<int, std::string>(reinterpret_cast<int *>(7), new std::string("")));

    for (int i = 1; i <= 7; ++i) {
        std::cout << *tree->getEntry(reinterpret_cast<int *>(i))->getValue();
    }

    tree->removeEntry(reinterpret_cast<int *>(1));

    return 0;
}

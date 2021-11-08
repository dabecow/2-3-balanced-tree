#include <iostream>
#include "BalancedTree.h"
#include "Node.h"
#include "Entry.h"

int main() {
    auto *tree = new BalancedTree<int, int>;
    auto *result = tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(1), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(2), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(3), reinterpret_cast<int *>(1)));tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(1), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(4), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(5), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(6), reinterpret_cast<int *>(1)));
    tree->addEntry(new Entry<int, int>(reinterpret_cast<int *>(7), reinterpret_cast<int *>(1)));

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

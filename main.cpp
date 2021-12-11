#include <iostream>
#include "BalancedTree.h"
#include "Node.h"
#include "TestService.h"
#include "Entry.h"
#include "Test.h"
int main() {
//    auto *tree = new BalancedTree<int, std::string>;
//    int intValues[] = {1, 2, 3, 4, 5, 6, 7};
//    std::string stringValues[] = {"Hello", ", ", "World", "!", "", "", ""};
//
//    for (int i = 0; i < 7; ++i) {
//        tree->addEntry(new Entry<int, std::string>(&intValues[i], &stringValues[i]));
//    }
//
//    for (int i = 1; i <= 7; ++i) {
//        std::cout << *tree->getEntry(&i)->getValue();
//    }
//
//    int keyToRemove = 1;
//    tree->removeEntry(&keyToRemove);
//
//
//    Entry<int, std::string>* iterEntry;
//
//    std::cout << "\n\nAfter removing the first element which is " << stringValues[0] << ":\n\n";
//
//    for (int i = 1; i <= 7; ++i) {
//        iterEntry = tree->getEntry(&i);
//        if (iterEntry != nullptr)
//            std::cout << *iterEntry->getValue();
//    }

//    testInserting();
//    testSearching();
    testRemoving();
    return 0;
}

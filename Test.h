//
// Created by Andrew on 10.12.2021.
//

#ifndef TREE_TEST_H
#define TREE_TEST_H
#define NUMBER_OF_TESTS 100
#define NUMBER_OF_ELEMENTS 100000

#include "TestService.h"
#include <chrono>

void testInserting(){


    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using nano = std::chrono::nanoseconds;
        auto start = std::chrono::high_resolution_clock::now();

        testServices[i].insertElement(NUMBER_OF_ELEMENTS);

        auto finish = std::chrono::high_resolution_clock::now();
        std::cout << numberOfElements << ":" << std::chrono::duration_cast<nano>(finish - start).count() << std::endl;
        testServices[i].removeTree();
    }
}

void testSearching(){
    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using nano = std::chrono::nanoseconds;
        auto start = std::chrono::high_resolution_clock::now();

        testServices[i].searchAndPrintElement(0);

        auto finish = std::chrono::high_resolution_clock::now();
        std::cout << numberOfElements << ":" << std::chrono::duration_cast<nano>(finish - start).count() << std::endl;
        testServices[i].removeTree();
    }
}

void testRemoving(){
    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using nano = std::chrono::nanoseconds;
        auto start = std::chrono::high_resolution_clock::now();

        testServices[i].removeElement(1);

        auto finish = std::chrono::high_resolution_clock::now();
        std::cout << numberOfElements << ":" << std::chrono::duration_cast<nano>(finish - start).count() << std::endl;
        testServices[i].removeTree();
    }
}

void addSomeValuesAndPrintTree(int numberOfValues){
    auto testService = new TestService();
    testService->initTree(numberOfValues);

    testService->printTree();
    testService->removeTree();
}

#endif //TREE_TEST_H

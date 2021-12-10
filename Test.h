//
// Created by Andrew on 10.12.2021.
//

#ifndef TREE_TEST_H
#define TREE_TEST_H
#define NUMBER_OF_TESTS 10
#define NUMBER_OF_ELEMENTS 10000

#include "TestService.h"
#include <chrono>

void testInserting(){

    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using milli = std::chrono::milliseconds;
        auto start = std::chrono::high_resolution_clock::now();

        testServices[i].insertElements(numberOfElements);

        auto finish = std::chrono::high_resolution_clock::now();
        std::cout << "Inserting " << numberOfElements << " elements took: "
                  << std::chrono::duration_cast<milli>(finish - start).count()
                  << " milliseconds\n";
        testServices[i].removeTree();
    }
}

void testSearching(){
    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using milli = std::chrono::milliseconds;
        auto start = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < numberOfElements; ++j) {
            testServices[i].searchElement(i);
        }

        auto finish = std::chrono::high_resolution_clock::now();

        std::cout << "Searching every element in tree with size " << numberOfElements << " took "
                  << std::chrono::duration_cast<milli>(finish - start).count()
                  << " milliseconds\n";
        testServices[i].removeTree();
    }
}

void testRemoving(){
    auto testServices = new TestService[NUMBER_OF_TESTS];

    for (int i = 1; i <= NUMBER_OF_TESTS; ++i) {
        int numberOfElements = NUMBER_OF_ELEMENTS / NUMBER_OF_TESTS * i;
        testServices[i].initTree(numberOfElements);

        using milli = std::chrono::milliseconds;
        auto start = std::chrono::high_resolution_clock::now();

        for (int j = numberOfElements / 4; j < numberOfElements * 0.75; ++j) {
            testServices[i].removeElement(i);
        }

        auto finish = std::chrono::high_resolution_clock::now();

        std::cout << "Removing every element in tree with size " << numberOfElements << " took "
                  << std::chrono::duration_cast<milli>(finish - start).count()
                  << " milliseconds\n";
        testServices[i].removeTree();
    }
}

#endif //TREE_TEST_H

//
// Created by Pasha on 15/12/2019.
//

#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <vector>
#include <iostream>
#include <random>
#include <set>

template <typename T>
void printSequence(const T& begin, const T& end) {
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

std::vector<int> getRandomVector(size_t size) {
    std::vector<int> ret;
    ret.reserve(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);
    for (size_t i =0; i < size; ++i) {
        ret.push_back(dist(gen));
    }
    return ret;
}

template <typename T>
void testSortAlgorithm(size_t array_size, size_t numOfTimes, T algorithm) {
    for (int i = 0; i < numOfTimes; ++i) {
        std::vector<int> vec = getRandomVector(array_size);
        testSortAlgorithmWithVector(algorithm, vec);
    }

}

template <typename T>
void testSortAlgorithmWithVector(T algorithm, std::vector<int> &vec) {
    printSequence(vec.begin(), vec.end());
    std::vector<int> control;
    for (int j = 0; j < vec.size(); ++j) {
        control.push_back(vec[j]);
    }
    std::sort(control.begin(), control.end());
    algorithm.sort(vec);
    for (int j = 0; j < vec.size(); ++j) {
        if (vec[j] == control[j]) {
            std::cout << "Test succeeded! Expected: " << vec[j] << std::endl;
        } else {
            std::cout << "Test failed! Expected: " << control[j] <<"; got: " << vec[j] << std::endl;
            return;
        }

    }
}

#endif //SORT_UTILS_H

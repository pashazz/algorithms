//
// Created by Pasha on 15/12/2019.
//

#include "MergeSortBinarySearch.h"
#include "utils.h"

int main(int argc, char** argv) {
    MergeSortBinarySearch ms;
    //std::vector<int> vec = {3, 2, 3, 4, 2};
    //testSortAlgorithmWithVector(ms, vec);
    testSortAlgorithm(1000, 100, ms);
}
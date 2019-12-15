//
// Created by Pasha on 15/12/2019.
//

#ifndef SORT_MERGESORTBINARYSEARCH_H
#define SORT_MERGESORTBINARYSEARCH_H


#include "mergesort.h"

class MergeSortBinarySearch : public MergeSort  {
protected:
    void mergeProcedure(const std::vector<int> &vec, size_t start, size_t half, size_t end) override ;

    virtual size_t binarySearch(const std::vector<int> &sortedVec, size_t start, size_t end, int what);

};


#endif //SORT_MERGESORTBINARYSEARCH_H

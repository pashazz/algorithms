//
// Created by Pasha on 15/12/2019.
//

#ifndef SORT_MERGESORT_H
#define SORT_MERGESORT_H

#include <vector>

class MergeSort {
protected:
    size_t baseWidth = 1;
    int *memory;

public:
    void setBaseWidth(size_t baseWidth) {
        if (baseWidth > 0) {
            this->baseWidth = baseWidth;
        }
    }
    size_t getBaseWidth() {
        return baseWidth;
    }

    void sort(std::vector<int> &vec);

protected:
    void merge(std::vector<int> &vec, size_t start, size_t half, size_t end);
    virtual void mergeProcedure(const std::vector<int> &vec, size_t start, size_t half, size_t end);
    void copyFromMemory(std::vector<int> &to, size_t start, size_t size);


};

#endif //SORT_MERGESORT_H

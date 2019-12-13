//
// Created by Pasha on 12/12/2019.
//

#ifndef BINARYTREE_HEAP_H
#define BINARYTREE_HEAP_H


#include "bintree.h"
#include <vector>

/**
 * Heap is a complete binary tree based on an array
 * The root is the minimum.
 *
 * The indexes are as follows:
 * parent: (node - 1) / 2
 * left child: 2 * node + 1
 * right child: 2 * node + 2
 *
 * The stucture of the heap implies that the smallest item resides at the top
 * and both of the children of each node is smaller than the
 */
class Heap :  public BinaryTree {
public:
    void add(int what) override;
    void removeMin() override;
    int getMin() const  override ;
    void remove(int what) override;
    bool isEmpty() const override {
        return vec.empty();
    }

protected:
    std::vector<int> vec;
    void restoreAfterAdd();
    static size_t getParentIndex(int currentIndex) {
        return (currentIndex - 1) / 2;
    }
    static int getLeftChildIndex(int currentIndex) {
        return currentIndex * 2 + 1;
    }
    static int getRightChildIndex(int currentIndex) {
        return getLeftChildIndex(currentIndex) + 1;
    }

    static bool isRightChild(int currentIndex) {
        return !isRoot(currentIndex) && currentIndex % 2 == 0;
    }
    static bool isLeftChild(int currentIndex) {
        return !isRoot(currentIndex) && currentIndex % 2 == 1;
    }

    /**
     * Returns the index of the smallest of the children. Returns -1 if no children exist.
     * @param currentIndex
     * @return
     */
    int smallestChildIndex(size_t currentIndex) {
        size_t leftChildIndex = getLeftChildIndex(currentIndex);
        size_t rightChildIndex = getRightChildIndex(currentIndex);
        if (leftChildIndex < vec.size()) {
            if (rightChildIndex < vec.size()) {
                return vec[rightChildIndex] > vec[leftChildIndex]
                ? leftChildIndex : rightChildIndex;
            }
            return leftChildIndex;
        } else { //no left child -> no right child.
            return -1;
        }
    }



    static bool isRoot (size_t currentIndex) {
        return currentIndex == 0;
    }


    void restoreAfterRemove();

};


#endif //BINARYTREE_HEAP_H

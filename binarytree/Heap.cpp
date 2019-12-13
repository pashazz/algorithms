//
// Created by Pasha on 12/12/2019.
//

#include "Heap.h"

/*
 * Add item to the rightmost position, then restoreAfterAdd the tree
 */
void Heap::add(int what) {
    vec.push_back(what);
    restoreAfterAdd();
}

void swap(int &a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * Given that the rightmost item moved to the root after previous min is removed, restore the heap.
 *
 * Compare the root item with the smallest among the children and replace root with child if the root is bigger
 *
 */
void Heap::restoreAfterRemove() {
    if (vec.size() == 0) {
        return;
    }
    int currentIndex = 0;
    int currentChildIndex = smallestChildIndex(currentIndex); //Get the smaller child of the root. If only root is present, we won't even enter the loop
    while (currentChildIndex != -1) {
        if (vec[currentIndex] > vec[currentChildIndex]) {
            swap(vec[currentIndex], vec[currentChildIndex]);
            currentIndex = currentChildIndex;
            currentChildIndex = smallestChildIndex(currentIndex);
        } else {
            break;
        }
    }

}


/**
 * After an item is added to the rightmost position (i.e. push_back), compare it with its parent and swap if needed
 */
void Heap::restoreAfterAdd() {
    int currentIndex = vec.size() - 1;
    while (!isRoot(currentIndex)) {
        /*if (isRightChild(currentIndex)) {
            // Compare me with my left sibiling
            if (vec[currentIndex] < vec[currentIndex - 1]) {
                swap(vec[currentIndex], vec[currentIndex - 1]);
                currentIndex = currentIndex - 1;
            } else {
                break;
            }
        } */
        //Compare me with my parent
        int parentIndex = getParentIndex(currentIndex);
        if (vec[currentIndex] < vec[parentIndex]) {
            swap(vec[currentIndex], vec[parentIndex]);
            currentIndex = parentIndex;
        } else {
            break;
        }
    }
}

void Heap::removeMin() {
    if (vec.size() == 0) {
        return;
    }
    vec[0] = vec[vec.size() - 1];
    vec.pop_back();
    restoreAfterRemove();
}

void Heap::remove(int what) {

}

int Heap::getMin() const {
    if (vec.size() == 0) {
        return INT_MIN;
    }
    return vec[0];
}




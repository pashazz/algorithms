//
// Created by Pasha on 15/12/2019.
//

#include "mergesort.h"
/* Let's say the array is of size 9
 * the i  will grow like this: 1 -> 2 -> 4 -> 8 -> 16.
 *
 *
 */

void MergeSort::sort(std::vector<int> &vec) {
    // Create a temporary memory for our merges
    memory = new int[vec.size()];
    // Bottom-up ⬆️

    for (size_t i = baseWidth; i < vec.size(); i *= 2) { // i is the width of minimal currently sorted array
        for (size_t j = 0; j <  vec.size(); j += 2*i) {
            merge(vec, j, j+i, j+ (2*i));
        }
    }
    delete[] memory;
}
//Half is where the second half starts.  Therefore the first half ends at half-1.
void MergeSort::merge(std::vector<int> &vec, size_t start, size_t half, size_t end) {
    // Adjust end and half
    if (half >= vec.size()) {
        //Nothing to merge there as it's already been merged.
        return;
    }
    if (end > vec.size()) {
        end = vec.size();
    }
    // We assume that vec is not touched. The result of mergeProcedure are copied to memory from 0 to (end-start) instead.
    mergeProcedure(vec, start, half, end);

   // Copy back to vec.
    copyFromMemory(vec, start, end - start);
}

// This is naive merge
// It makes O (end - start) operations (namely end - start insertions and end - start comparisons.
void MergeSort::mergeProcedure(const std::vector<int> &vec, size_t start, size_t half, size_t end) {
    size_t seq1index = start;
    size_t seq2index = half; //marks exactly the start of the second half
    size_t finalIndex;
    size_t size = end - start;
    bool continueInSeq1 = true;
    bool continueInSeq2 = true;
    for (finalIndex  = 0; continueInSeq1 && continueInSeq2; finalIndex++) {

        if (vec[seq1index] < vec[seq2index]) {
            memory[finalIndex] = vec[seq1index];
            seq1index++;
        } else {
            memory[finalIndex] = vec[seq2index];
            seq2index++;
        }
        if (seq1index == half) {
            continueInSeq1 = false;
        }
        if (seq2index == end) {
            continueInSeq2 = false;
        }
    }
    assert(finalIndex < size  || (!continueInSeq1 && !continueInSeq2));
    if (continueInSeq1) {
        for (; finalIndex < size; finalIndex++,  seq1index++) {
            memory[finalIndex] = vec[seq1index];
        }
    }
    if (continueInSeq2) {
        for (; finalIndex < size; finalIndex++, seq2index++) {
            memory[finalIndex] = vec[seq2index];
        }
    }

}

void MergeSort::copyFromMemory(std::vector<int> &vec, size_t start, size_t size) {
    for (int i = 0; i < size; ++i) {
        vec[i+start] = memory[i];
    }
}

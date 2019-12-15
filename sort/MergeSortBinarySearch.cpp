//
// Created by Pasha on 15/12/2019.
//

#include <map>
#include "MergeSortBinarySearch.h"
/**
 * merge assumes that vec is sorted between [start; half) and between [half;end).
 *
 * Finds an appropriate position for every element contained in [half;end) in range [start;half).
 *
 * Uses a binary search for that. Binary search can only advance forward in range [start;half) as the time goes
 * because each binarySearch call is performed with a higher value of a target than the previous one.
 *
 * Using that information, push everything from previous found "place" index to current found "place" index
 * from the first half, then the target element, and if  the binary search suggests that we should insert target element after the first half,
 * we insert all the remaining second half elements right away.
 *
 *
 * @param vec
 * @param start
 * @param half
 * @param end
 */

void MergeSortBinarySearch::mergeProcedure(const std::vector<int> &vec, size_t start, size_t half, size_t end) {
    size_t currentBinSearchPosition = start;
    size_t previousBinSearchPosition;
    size_t memoryIndex = 0;
    //Search for everything in [half;end)  between start and half - 1.
    for (size_t  i = half; i < end; ++i) {
        previousBinSearchPosition = currentBinSearchPosition;
        //currentBinSearchPosition can only be advanced as we are moving for i in sorted array
        currentBinSearchPosition = binarySearch(vec, currentBinSearchPosition, half - 1, vec[i]);
        // Add everything to the left of current search position into temp array
        for (size_t pos  = previousBinSearchPosition; pos < currentBinSearchPosition; ++pos) {
            memory[memoryIndex++] = vec[pos];
        }
        //add current second half member into the currentBinSearchPosition
        memory[memoryIndex++] = vec[i];

        if (currentBinSearchPosition == half) { //all the remaining second half elements > all first half elements.
            for (size_t pos = i+1; pos < end; ++pos) {
                memory[memoryIndex++] = vec[pos];
            }
            break;
        }
    }

    //If we have first half elements > all the second half elements,
    // currentBinSearchPosition will be between first such element and "half".
    // Add remaining first half elements
    for (size_t pos = currentBinSearchPosition; pos < half; ++pos) {
        memory[memoryIndex++] = vec[pos];
       }




}

/**
 * Returns where to place "what" assuming that the sortedVec is sorted between start and end inclusively..
 * @param sortedVec
 * @param start search start
 * @param end search end
 * @param what What to insert into sortedVec
 * @return Where to insert "what", shifting all the elements after to the right.
 */
size_t MergeSortBinarySearch::binarySearch(const std::vector<int> &sortedVec, size_t start, size_t end, int what) {
    //Base case: end == start. Put the what at exactly start if this is less than sortedVec[start]
    if (end  == start) {
        if (what < sortedVec[start]) {
            return start;
        } else {
            return start+1;
        }
    }
    size_t mid = (end - start) / 2 + start;
    if (sortedVec[mid] < what) {
        return binarySearch(sortedVec, mid+1, end, what);
    } else if (sortedVec[mid] > what) {
        return binarySearch(sortedVec, start, mid, what);
    }
    return mid;

}

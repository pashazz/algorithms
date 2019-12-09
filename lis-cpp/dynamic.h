//
// Created by pasha on 09.12.2019.
//

#ifndef LIS_CPP_DYNAMIC_H
#define LIS_CPP_DYNAMIC_H

#include <vector>
class LongestAlternatingSequenceDP {
protected:
    std::vector<int> sequence;
    std::vector<std::vector<int>> currentInc, currentDec;

    int currentBestSequence = 0; //Indicates best subsequence, as defined by betterIndexSequence
    bool currentBestSequenceInc = false; //Indicates whether the current best subsequence is increasing


    int compareSequenceAt(int i, int j) {
        if (sequence[i] > sequence[j]) {
            return 1;
        } else if (sequence[i] == sequence[j]) {
            return 0;
        } else {
            return -1;
        }
    }
    /**
     * Decides whether an index sequence A is better than index sequence B, that is
     * returns true if |A| > |B| or a_i < b_i (with all k < i, a_k == b_k)
     * @param seqA
     * @param seqB
     * @return
     */
    static bool betterIndexSequence(const std::vector<int>& seqA, const std::vector<int>& seqB) {
        if (seqA.size() > seqB.size()) {
            return true;
        } else if (seqA.size() < seqB.size()) {
            return false;
        } else {
            for (int i = 0; i < seqA.size(); ++i) {
                if (seqA[i] < seqB[i]) {
                    return true;
                } else if (seqA[i] > seqB[i]) {
                    return false;
                }
            }
            return false;
        }
    }
    /**
     * Decide if increasing sequence of indexA is better than of indexB.
     * If indexB == -1 (special case, current best sequence not found), returns true immediately
     * @param indexA
     * @param indexB
     * @return
     */
    bool betterIncreasingSequenceByIndex(int indexA, int indexB) {
        if (indexB == -1) {
            return true;
        }
        return betterIndexSequence(currentInc[indexA], currentInc[indexB]);
    }
    bool betterDecreasingSequenceByIndex(int indexA, int indexB) {
        if (indexB == -1) {
            return true;
        }
        return betterIndexSequence(currentDec[indexA], currentDec[indexB]);
    }
public:
    LongestAlternatingSequenceDP(std::vector<int> sequence) {
        this->sequence = sequence;
        this->currentInc.resize(sequence.size());
        this->currentDec.resize(sequence.size());
    }
    std::vector<int> bestIndexSequence() {
        if (currentBestSequenceInc) {
            return currentInc[currentBestSequence];
        } else {
            return currentDec[currentBestSequence];
        }
    }
    void perform() {

        for (int i = 0; i < sequence.size(); ++i) {
            int bestSequenceIndexInc = -1;
            int bestSequenceIndexDec = -1;

            for (int j = 0; j < i; ++j) {
                int currentElementToLast = compareSequenceAt(i, j);
                switch (currentElementToLast) {
                    case 1: //Current > Last: find sequence that is currently increasing
                        if (betterIncreasingSequenceByIndex(j, bestSequenceIndexInc)) {
                            bestSequenceIndexInc = j;
                        }
                        break;
                    case -1:
                        if (betterDecreasingSequenceByIndex(j, bestSequenceIndexDec)) {
                            bestSequenceIndexDec = j;
                        }
                        break;
                }
            }
            // Fill best increasing sequence for i based on current best decreasing sequence (as it's alternating)
            if (bestSequenceIndexDec != -1) {
                currentInc[i].reserve(currentDec[bestSequenceIndexDec].size() + 1);
                for (const int elem : currentDec[bestSequenceIndexDec]) {
                    currentInc[i].push_back(elem);
                }
            }
            currentInc[i].push_back(i);
            //Same for best decreasing sequence
            if (bestSequenceIndexInc != -1) {
                currentDec[i].reserve(currentInc[bestSequenceIndexInc].size() + 1);
                for (const int elem : currentInc[bestSequenceIndexInc]) {
                    currentDec[i].push_back(elem);
                }
            }
            currentDec[i].push_back(i);

            //Find out current best
            if (betterIndexSequence(currentInc[i], bestIndexSequence()))  {
                currentBestSequence = i;
                currentBestSequenceInc = true;
            }
            if (betterIndexSequence(currentDec[i], bestIndexSequence())) {
                currentBestSequence = i;
                currentBestSequenceInc = false;
            }
        }
    }

    std::vector<std::vector<int>> getIncLAS() const {
        return currentInc;
    }
    std::vector<std::vector<int>> getDecLAS() const {
        return currentDec;
    }
};

#endif //LIS_CPP_DYNAMIC_H

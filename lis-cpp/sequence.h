//
// Created by pasha on 09.12.2019.
//

#ifndef LIS_CPP_SEQUENCE_H
#define LIS_CPP_SEQUENCE_H


#define LIS_CPP_SEQUENCE_H
#include <vector>
#include <cassert>

class LongestAlternatingSequence {
private:
    std::vector<int> sequence;
    std::vector<int> answer;

    static int compare(int i, int j) {
        return i > j ? 1 : (i == j) ? 0 : -1;
    }
    /**
     * Finds a sufficient int on a sequence
     * @param gradient if > 0 find first element on [start...end] greater than the target
     *                 if < 0 find first element on [start...end] lesser than the target
     *                 if == 0 return first (sequence[start]) element
     * @param start sequence index to start search from
     * @param end sequence index to end search on.
     * @param target sequence index to compare result with. If greater than the sequence size, return first (sequence[start]) element
     * @return
     */
    int findOnSequence(int gradient, int start, int end, int target) {
        if (gradient == 0) {
            return sequence[start]; //special case for the first element
        }
        if (target >= sequence.size()) {
            return sequence[start]; //special case for the last element
        }
        for (int i = start; i <= end; ++i) {
            if
                    ((gradient > 0 && sequence[i] > sequence[target]) ||
                    (gradient < 0 && sequence[i] < sequence[target])) {
                return sequence[i];
            }

        }
        assert(false);
    }

public:
    void perform() {
        // {1, 4, 2, 3, 5, 8, 4, 7, 9, 10}; -> 1 4 2 5 4 7
        int gradient = 0;
        int currentGradIndexChanged = 0; //an index on which the gradient is changed for the last time
        for (int i = 1; i < sequence.size(); ++i) {
            switch (compare(sequence[i], sequence[i - 1])) {
                case 1:
                    if (gradient > 0 ) { // Continue
                        continue;
                    }
                    answer.push_back(findOnSequence(gradient, currentGradIndexChanged, i-1, i));
                    currentGradIndexChanged = i;
                    gradient = 1;
                    break;
                case -1:
                    if (gradient < 0) {
                        continue;
                    }
                    answer.push_back(findOnSequence(gradient, currentGradIndexChanged, i-1, i));
                    currentGradIndexChanged = i;
                    gradient = -1;
                    break;
            }
        }
        if (sequence.size() > 0)
            answer.push_back(findOnSequence(gradient, currentGradIndexChanged, sequence.size() - 1, sequence.size()));

    }
    std::vector<int> getAnswer() const {
        return answer;
    }

public:
    LongestAlternatingSequence(std::vector<int> sequence) {
        this->sequence = sequence;
    }
};
#endif //LIS_CPP_SEQUENCE_H

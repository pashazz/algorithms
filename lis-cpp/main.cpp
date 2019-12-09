#include <iostream>
#include "dynamic.h"
#include "sequence.h"


void print(std::vector<int> vector);

void printIndexVec(const std::vector<int>& indices, const std::vector<int>& sequence) {
    for (int j = 0; j < indices.size(); ++j) {
        std::cout << sequence[indices[j]] << " ";
    }
    std::cout << std::endl;
}


void printVec(const std::vector<std::vector<int>>& indices, const std::vector<int> sequence) {
    for (int i = 0; i < indices.size(); ++i) {
        std::cout << "[" << i << "]: ";
        printIndexVec(indices[i], sequence);
    }
}




int main() {
    std::vector<int> sequence = {1, 4, 2, 3, 5, 8, 4, 7, 9, 10};
    LongestAlternatingSequenceDP dp = LongestAlternatingSequenceDP(sequence);
    dp.perform();
    std::cout << "Increasing sequences" <<std::endl;
    printVec(dp.getIncLAS(), sequence);
    std::cout << "Decreasing sequences" << std::endl;
    printVec(dp.getDecLAS(), sequence);
    std::cout << "Best sequence" << std::endl;
    printIndexVec(dp.bestIndexSequence(), sequence);

    LongestAlternatingSequence las = LongestAlternatingSequence(sequence);
    las.perform();
    print(las.getAnswer());

}

void print(std::vector<int> vector) {
    for (int elem : vector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
};



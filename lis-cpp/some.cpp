//
// Created by pasha on 09.12.2019.
//

#include <iostream>
#include <vector>

void PrintVect(const std::vector<int>& array) {
    for (size_t item = 0; item + 1 < array.size(); ++item) {
        std::cout << array[item] << ' ';
    }
    if (!array.empty()) {
        std::cout << array[array.size() - 1];
    }
}

size_t FindDec(int oldmax, const std::vector<int>& array, size_t start, size_t& ptr) {
    size_t current = start;
    while (current < array.size() && array[current] <= array[current - 1]) {
        ++current;
    }
    ptr = current;
    if (current == array.size()) {
        while (array[start] >= oldmax) {
            start++;
        }
        return start;
    }
    while (current < array.size() && array[current] >= array[current - 1]) {
        ++current;
    }
    current--;
    int newmax = array[current];
    while (array[start] >= oldmax || array[start] >= newmax) {
        start++;
    }
    return start;
}

size_t FindInc(int oldmin, const std::vector<int>& array, size_t start, size_t& ptr) {
    size_t current = start;
    while (current < array.size() && array[current] >= array[current - 1]) {
        ++current;
    }
    ptr = current;
    if (current == array.size()) {

        while (array[start] <= oldmin) {
            ++start;
        }
        return start;
    }
    while (current < array.size() && array[current] <= array[current - 1]) {
        ++current;
    }
    --current;
    int newmin = array[current];
    while (array[start] <= oldmin || array[start] <= newmin) {
        start++;
    }
    return start;
}

void FindLAS(const std::vector<int>& array) {
    if (array.size() <= 1) {
        PrintVect(array);
        return;
    }
    std::vector<int> res(0);
    res.push_back(array[0]);
    size_t current = 1;
    while (current < array.size() && array[current] == array[0]) {
        ++current;
    }
    if (current == array.size()) {
        PrintVect(res);
        return;
    }
    bool incresing = array[current] > array[0];
    current = 1;
    while (current < array.size()) {
        size_t temp = current;
        if (incresing) {
            temp = FindInc(res[res.size() - 1], array, temp, current);
        } else {
            temp = FindDec(res[res.size() - 1], array, temp, current);
        }
        res.push_back(array[temp]);
        incresing ^= 1;
    }
    PrintVect(res);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    size_t num;
    std::cin >> num;
    std::vector<int> arr(num);
    for (size_t i = 0; i < num; ++i) {
        std::cin >> arr[i];
    }
    FindLAS(arr);
    return 0;
}
#include <iostream>
#include <set>
#include <random>
#include "Heap.h"


template <typename T>
void printSequence(const T& begin, const T& end);

std::set<int> getRandomSet(size_t size);

void testImplementationOnItems(std::set<int> items, BinaryTree *obj);
int main() {
    BinaryTree *bt = new Heap();
    std::set<int> nums = getRandomSet(1000);
    //std::set nums = {-20, -34, 10, 20, 0, 40, 72, -21, -3};
    printSequence(nums.begin(), nums.end());

    testImplementationOnItems(nums, bt);
    delete bt;
}
template <typename T>
void printSequence(const T& begin, const T& end) {
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

std::set<int> getRandomSet(size_t size) {
    std::set<int> ret;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-203478032, 1000000);
    for (size_t i =0; i < size; ++i) {
        ret.insert(dist(gen));
    }
    return ret;
}

void testImplementationOnItems(std::set<int> items, BinaryTree *obj) {
    for (int item: items) {
        obj->add(item);
    }

    while (!obj->isEmpty()) {
        if (obj->getMin() != *items.begin()) {
            std::cout << "Test failed. Min element: " << obj->getMin() << "; Expected " << *items.begin();
            return;
        } else {
            std::cout << "Test succeeded. Min element: " << obj->getMin() << std::endl;
        }
        obj->removeMin();
        items.erase(items.begin()); //Remove smallest element from set
    }
}

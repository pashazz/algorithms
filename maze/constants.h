//
// Created by Pasha on 14.04.2020.
//

#ifndef MAZE_CONSTANTS_H
#define MAZE_CONSTANTS_H

#include <utility>

static const int SYMBOL_PLUS = -3;
static const int SYMBOL_MINUS = -2;
static const int SYMBOL_BAR = -1;

using coordinates = std::pair<size_t, size_t>;

struct CoordinatesComparator {
    bool operator()(const coordinates &lhs, const coordinates &rhs) const {
        if (lhs.first != rhs.first) {
            if (lhs.first != rhs.second) {
                return lhs.first < rhs.first;
            } else {
                return lhs.second < rhs.first;
            }
        } else {
            return lhs.second < rhs.second;
        }
    }
};
/**
template <typename T>
using CoordinatesMap = std::map<coordinates, T, CoordinatesComparator>
**/



#endif //MAZE_CONSTANTS_H

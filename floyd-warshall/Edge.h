//
// Created by Pasha on 15.04.2020.
//

#pragma once


#include <cassert>
#include "constants.h"



struct Edge {
    //size_t tail;
    //size_t head;
    int weight;

    /**Edge(size_t tail, size_t head, int weight)
    :tail(tail), head(head), weight(weight) {}
**/
    Edge(int weight) : weight(weight) {}

};




//
// Created by Pasha on 15.04.2020.
//

#ifndef MAZE_EDGE_H
#define MAZE_EDGE_H

struct Path {
    coordinates coords;
    Path *parent;
    int weight;
    Path(Path *parent, coordinates c) : coords(c), parent(parent) {
        if (parent) {
            weight = parent->weight + 1;
        } else {
            weight = 1;
        }
    }
};


struct Edge {
    friend bool operator<(const Edge &lhs, const Edge &rhs) {
        return lhs.weight < rhs.weight;
    }
    size_t tail;
    size_t head;
    size_t weight;
    Path*  payload;
    Edge(size_t tail, size_t head, size_t weight,  Path* payload)
    :tail(tail), head(head), weight(weight), payload(payload){}

    size_t getOther(size_t coordinate) {
        if (coordinate == tail) {
            return head;
        } else if (coordinate == head) {
            return tail;
        } else {
            assert(false);
        }
    }
};

struct EdgeComparator {
    bool operator() (const Edge *lhs, const Edge * rhs) {
        if (lhs->weight != rhs->weight) {
            return lhs->weight < rhs->weight;
        }
        if (lhs->tail != rhs->tail) {
            if (lhs->tail != rhs->head) {
                return lhs->tail < rhs->tail;
            } else {
                return lhs->head < rhs->tail;
            }
        } else {
            return lhs->head < rhs->head;
        }
    }
};


#endif //MAZE_EDGE_H

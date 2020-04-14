//
// Created by Pasha on 13.04.2020.
//

#include "Graph.h"

void Graph::addVertex(int vertex) {
    if (!hasVertex(vertex)) {
        adjList[vertex] = set<int>();
    }
}

void Graph::addEdge(int head, int tail) {
    addVertex(head);
    addVertex(tail);
    adjList[head].insert(tail);
    adjList[tail].insert(head);
}

bool Graph::hasVertex(int value) {
    return adjList.find(value) != adjList.end();

}

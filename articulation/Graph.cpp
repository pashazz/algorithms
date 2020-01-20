//
// Created by Pasha on 13/01/2020.
//

#include "Graph.h"

#include <stdexcept>

void Graph::addVertex(int vertex) {
    if (adjList.find(vertex) != adjList.end()) {
        throwVertexExists();
    }
}


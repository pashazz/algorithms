//
// Created by Pasha on 15.04.2020.
//

#include "Graph.h"
#include "Edge.h"

void Graph::addVertex(size_t vertex) {
    if (!hasVertex(vertex)) {
        adjList[vertex] = EdgeSet ();
    }
}

void Graph::addEdge(Edge * e) {
    addVertex(e->tail);
    addVertex(e->head);

    weightedEdges[coordinates(e->tail, e->head)] = e;
    adjList[e->head].insert(e);
    adjList[e->tail].insert(e);

}






}

bool Graph::hasVertex(size_t value) {
    return adjList.find(value) != adjList.end();

}

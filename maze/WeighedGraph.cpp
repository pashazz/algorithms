//
// Created by Pasha on 13.04.2020.
//

#include "WeighedGraph.h"
#include "Edge.h"

void WeighedGraph::addVertex(size_t vertex) {
    if (!hasVertex(vertex)) {
        adjList[vertex] = EdgeSet ();
    }
}
void WeighedGraph::addEdge(Edge * e) {
    addVertex(e->tail);
    addVertex(e->head);

    //Добавляем только самое легкое ребро
    auto currentEdge = weightedEdges.find(coordinates(e->tail, e->head));
    if (currentEdge ==  weightedEdges.end() ||
        currentEdge->second->weight > e->weight) {
            weightedEdges[coordinates(e->tail, e->head)] = e;
            adjList[e->head].insert(e);
            adjList[e->tail].insert(e);
    }






}

bool WeighedGraph::hasVertex(size_t value) {
    return adjList.find(value) != adjList.end();

}

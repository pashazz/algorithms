//
// Created by Pasha on 13/01/2020.
//

#ifndef ARTICULATION_GRAPH_H
#define ARTICULATION_GRAPH_H

#include <algorithm>
#include <map>
#include <set>
using namespace std;

/** A graph class in which the vertices are represented by numbers.
 * Cool for algorithm testing
 *
 * the graph contains an adjacency list
 *
 */
class Graph {
protected:
    map<int, set<int>> adjList;
    const bool directed;
    Graph(bool directed)
    : directed(directed){

    }

    void throwVertexExists(int vertex);

public:
    void addVertex(int vertex);
    void addEdge(int tail, int head);
    void removeEdge(int tail, int head);
    void removeVertex(int vertex);
    set<int> heads(int tail);

    // Converts this graph to directed graph
    Graph toDirected();
};


#endif //ARTICULATION_GRAPH_H

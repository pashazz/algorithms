//
// Created by Pasha on 15.04.2020.
//

#ifndef MAZE_GRAPH_H
#define MAZE_GRAPH_H

using EdgeSet = set<Edge*, EdgeComparator>;
using EdgeMap = map<coordinates, Edge*>;



class Graph {
public:
    void addVertex(size_t vertex);
    void addEdge(Edge *e);
    string toString();

    map<size_t, EdgeSet> getAdjList() const {
        return adjList;
    }

    EdgeMap getWeightedEdges() const {
        return weightedEdges;
    }

protected:
    //Adj. list
    map<size_t, EdgeSet> adjList;

    EdgeMap weightedEdges;



    bool hasVertex(size_t value);



};


#endif //MAZE_GRAPH_H

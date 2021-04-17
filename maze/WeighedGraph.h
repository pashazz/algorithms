//
// Created by Pasha on 13.04.2020.
//

#ifndef MAZE_WEIGHEDGRAPH_H
#define MAZE_WEIGHEDGRAPH_H

#include <string>
#include <map>
#include <set>
#include "constants.h"
#include "Edge.h"

using namespace std;




class WeighedGraph  {
    using EdgeSet = set<Edge*, EdgeComparator>;
    using EdgeMap = map<coordinates, Edge*>;

public:
    void addVertex(size_t vertex);
    void addEdge(Edge *e);

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




#endif //MAZE_WEIGHEDGRAPH_H

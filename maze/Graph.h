//
// Created by Pasha on 13.04.2020.
//

#ifndef MAZE_GRAPH_H
#define MAZE_GRAPH_H

#include <string>
#include <map>
#include <set>

using namespace std;


class Graph {
public:
    void addVertex(int vertex);
    void addEdge(int head, int tail);
    string toString();


protected:
    //Adj. list
    map<int, std::set<int>> adjList;

    bool hasVertex(int value);



};


#endif //MAZE_GRAPH_H

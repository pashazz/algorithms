//
// Created by Pasha on 15.04.2020.
//

#include "Graph.h"
#include "Edge.h"
#include <iostream>


Path * Graph::floydWarshallMinPath() {

    // Algorithm
    for (size_t k = 1; k < A.size(); ++k) {
        //cout << "Step " << k << " of " << A.size() - 1 << endl;
        //cout.sync_with_stdio();
        for (size_t i = 1; i < A.size(); ++i) {
            for (size_t j = 1; j < A.size(); ++j) {
                int pathViaK = A[i][k] + A[k][j];
                if (A[i][k] == INT_MAX || A[k][j] == INT_MAX) {
                    pathViaK = INT_MAX; //Overflow detection
                }

                int prevPath = A[i][j];
                A[i][j] =  min(pathViaK, prevPath);
            }
        }
    }

    size_t minI;
    size_t minJ;
    int minLength = INT_MAX;
    for (size_t i = 1; i < A.size(); ++i) {
        for (size_t j = 1; j < A.size(); ++j) {
            auto len = A[i][j];
            if (i == j) {
                if (len < 0) {
                    // Cycle
                    cout << "Negative cycle detected at vertex " << i << ": " << len <<  endl;
                    return nullptr;
                }
            } else {
                if (len < minLength) {
                    minLength = len;
                    minI = i;
                    minJ = j;
                }
            }
        }
    }

    auto path = new Path();
    path->length = minLength;
    path->source = minI;
    path->destination = minJ;
    return path;

}

int Graph::getEdge(size_t source, size_t destination) {
    return A[source][destination];
}

void Graph::addEdge(size_t source, size_t destination, int weight) {
    A[source][destination] = weight;
}

Graph *Graph::input(istream &is) {
    size_t vertices, edges;
    is >> vertices;
    is >> edges;

    size_t s, d;
    int w;
    auto g = new Graph(vertices);
    for (size_t i = 0; i < edges; ++i) {
        is >> s;
        is >> d;
        is >> w;
        g->addEdge(s, d, w);
    }
    return g;


}


//
// Created by Pasha on 15.04.2020.
//

#pragma once

#include <cstddef>
#include <map>
#include <set>
#include <vector>
#include "Edge.h"
#include <iostream>

using namespace std;


struct Path {
    size_t source;
    size_t destination;
    int length;
};




class Graph {
public:
    static Graph* input(istream &is);
    Graph(size_t vertices) {
        A.resize(vertices +  1);
        for (size_t i = 1; i <= vertices; ++i) {
            A[i].resize(vertices + 1);
            for (size_t j = 1; j <= vertices; ++j) {
                if (i != j) {
                    A[i][j] = INT_MAX;
                }
            }
        }

    }
    void addEdge(size_t source, size_t destination, int weight);

    int getEdge (size_t source, size_t destination);

    int getVertices() const {
        return A.size();
    }

    /**
     * ** Подпроблема

   Аналогично Knapsack Problem, где нумеруются объекты, пронумеруем вершины

$V^{(k)} = \{1,2,\dots,k\}$ - prefix - вершины с 1 по k.

Пусть i - source, j - destination, тогда подпроблема - кратчайший путь i-j с вершинами $V^{(k)}$.


Количество подпроблем n^3 (по i, по j, по k по всем вершинам).

** Алгоритм

A - трехмерный массив [i][j][k]

Внешний цикл по k.

1. Base case: k = 0
   1. Если i = j, то a[i, j, 0] = 0
   2. Если $\exists e = (i, j) \in E$, то a[i, j, 0] = weight(e)
   3. Иначе a[i, j, 0] = $+\infty$.

2. Внутренние циклы по i и j:

A[i, j, k] = min:
   1. A[i, j, k-1] (путь из i в j из предыдущего шага)
   2. A[i, k, k-1] + A[k, j, k-1] Путь из i в k + путь из k в j из предыдущего шага.


** negative-cost cycles

Если хотя бы один A[i, i, n] < 0, то цикл есть

     * @return null если есть negative cycle, иначе кратчайший путь из всех пар вершин
     */
    Path * floydWarshallMinPath();
protected:

    vector<vector<int>> A;

};


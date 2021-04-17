//
// Created by Pasha on 13.04.2020.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include "constants.h"
#include <vector>
#include <istream>
#include <set>
#include <utility>
#include <queue>
#include <map>
#include "WeighedGraph.h"
#include "Edge.h"

using namespace std;





/**
 * Number of rows is number of dotted lines
 *
 * Number of cols is number of + signs (dead points)
 *
 * e.g. rows = 2, cols = 3 means
 *
 * + - + - + - +
 * | . | . . . |
 * + - + - + - +
 * | | . | . . |
 * + - + - + - +
 *
 * Creates a matrix of (rows + rows - 1) rows and cols + cols - 1 cols.
 *
 * + is decoded as -3.
 * - is decoded as -2
 * | is decoded as -1
 * . is decoded as the connected component index starting from 0.
 *
 *
 * @param rows
 * @param cols
 *
 * 1. Traverse the graph in all directions using BFS
 * 2. If a 0 is found, continue traversing
 * 3. If a -3 is found, do nothing there, we're stuck
 * 4. If a -2 or a -1 is found,
 * if previous cell is a 0
 * create a new Path starting from there with a null parent. Insert this Path in a path set
 * if previous cell is not a 0, extend its path and insert it in a path set
 * 5. If a non 0 component is found
 *   look for a path from its parent and decide if this is best path yet by length of parents.
 *   if there's no parent raise an assert
 *
 *
 *
 */

#include <queue>
#include <map>
#include <set>

/**
 * Represents a path chunk within walls
 */

struct TraversableVertex {
    TraversableVertex(coordinates coords, Path* path, int componentIndex)
    :coords(coords), path(path), componentIndex(componentIndex) {}
    coordinates coords;
    Path *path;
    int componentIndex;
};


class Maze {
public:
    Maze();

    void readMaze(istream &);

    void make () {
        if (counter)
        goFind();

    };

    WeighedGraph* getGraph() const {
        return mazeZonesGraph;
    };

protected:
    vector<vector<int>> data;
    vector<vector<bool>> visited;


    void goFind();

    void bfsBuildWeights(coordinates source);
    void bfsAddChildren(TraversableVertex *vertex);
    TraversableVertex *buildWeights(coordinates coords, Path *path, int currentComponentIndex);

//    void bfs();



    void connect (int component, coordinates targetCoords, coordinates wallCoords);
    void dfsConnect(coordinates coords, int component);


    queue<TraversableVertex*> bfsQueue;

    friend ostream& operator<<(ostream &out, const Maze& maze);
    friend ostream& printHeader(ostream &out, const Maze& maze);






    int symbolToCode(char c, int i, int j);

    /**
     * Checks if this position can be connected to the previous connected component.
     * @param i
     * @param j
     * @return
     */
    bool connectToPrevious(int i, int j);

    /**
     * Counts connected components
     */
    int counter = -1;

    WeighedGraph *mazeZonesGraph = nullptr;




};



#endif //MAZE_MAZE_H

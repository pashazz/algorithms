//
// Created by Pasha on 13.04.2020.
//
/**
 * 1. Создать связанные компоненты
 * 2. С помощью DFS пойти из компоненты 0 искать другие компоненты.
 */

#include <iostream>
#include "maze.h"
#include "constants.h"
#include "Edge.h"


Maze::Maze() {

}



void Maze::readMaze(istream &in) {
    if (!in) {
        cout << "Failed to read from stream";
        return;
    }
    int cols, rows;
    char c;
    in >> rows;
    in >> cols;
    data.resize(2*rows-1);
    for (auto & row : data) {
        row.resize(2*cols - 1);
    }
    //ignore the first line altogether
    string lastline;
    getline(in, lastline);
    getline(in, lastline);


    cout << "Maze:\n";

    for(int i = 0; i < data.size(); ++i) {
        // ignore the first symbol
        in >> c;
        assert(c == '|' || c == '+');
        for (int j = 0; j < data[i].size(); ++j) {
            in >> c;
            cout << c;
            data[i][j] = symbolToCode(c, i, j);
            cout << data[i][j] << " ";

        }
        getline(in, lastline);
        cout << endl;
    }

    getline(in, lastline);
    assert(counter >= 0);
    cout << "Found " << counter + 1 << " components";
}



bool Maze::connectToPrevious(int i, int j) {
    return (j > 0 && data[i][j-1] >= 0) ||
           (i > 0 && data[i - 1][j] >= 0);
}

int Maze::symbolToCode(char c, int i, int j ) {
    switch (c) {
        case '+':
            return SYMBOL_PLUS;
        case '-':
            return SYMBOL_MINUS;
        case '|':
            return SYMBOL_BAR;
        case '.':
            if (connectToPrevious(i, j)) {
                assert(counter >= 0);
                return counter;
            } else {
                return ++counter;
            }
        default:
            assert(false);
    }
}

/** Use a DFS algorithm to find component connections */

void Maze::goFind() {
    visited.clear();
    visited.resize(data.size());
    coordinates source;
    bool sourceFound = false;
    for(size_t i = 0; i < data.size(); ++i) {
        visited[i].clear();
        visited[i].resize(data[i].size());
        if (!sourceFound)
            for (size_t j = 0; j < data.size(); ++j) {
                if (data[i][j] == 0) {
                    source.first = i;
                    source.second = j;
                    sourceFound = true;
                    break;
                }
            }

    }

    if (mazeZonesGraph) {
        delete mazeZonesGraph;
    }
    mazeZonesGraph = new WeighedGraph();
    bfsBuildWeights(source);


}

void Maze::bfsBuildWeights(coordinates source) {
    visited[source.first][source.second] = true;
    assert(data[source.first][source.second] == 0);
    bfsAddChildren(new TraversableVertex(source, nullptr, 0));
    while (!bfsQueue.empty()) {
        auto next = bfsQueue.front();
        bfsQueue.pop();
        auto vertex = buildWeights(next->coords, next->path, next->componentIndex);
        if (vertex) {
            bfsAddChildren(vertex);
        }
        delete next;
    }
}

void Maze::bfsAddChildren(TraversableVertex *vertex) {
    //cout << "Add children for "  << vertex->coords.first << " " << vertex->coords.second << endl;
    if (vertex->coords.first < data.size() - 1) {
        bfsQueue.push(new TraversableVertex(coordinates(vertex->coords.first + 1,
                vertex->coords.second), vertex->path, vertex->componentIndex));
    }
    if (vertex->coords.first > 0) {
        bfsQueue.push(new TraversableVertex(coordinates(vertex->coords.first - 1,
                vertex->coords.second), vertex->path, vertex->componentIndex));
    }

    if (vertex->coords.second < data[vertex->coords.first].size() - 1) {
        bfsQueue.push(new TraversableVertex(coordinates(vertex->coords.first,
                vertex->coords.second + 1), vertex->path, vertex->componentIndex));
    }

    if (vertex->coords.second > 0) {
        bfsQueue.push(new TraversableVertex(coordinates(vertex->coords.first,
                vertex->coords.second - 1), vertex->path, vertex->componentIndex));
    }

}

/**
 * Traverses the maze creating a graph structure, whose vertices are the maze's connected components
 * and edges are paths through walls that need to be broken
 * @param coords
 * @param path
 * @param currentComponentIndex
 * @return
 */
TraversableVertex * Maze::buildWeights(coordinates coords, Path *path, int currentComponentIndex) {
    int code = data[coords.first][coords.second];
    bool _visited = false;
    if (visited[coords.first][coords.second]) {
        // If we've visited this vertex, check the path. If it does not contain these coordinates, we may enter (no cycles)
        // If path is null we can not enter as we're just wandering around in the same component

        if (!path)
            return nullptr;

        //cout << "Candidate " << coords.first << " " << coords.second << " passed path nullify test" << endl;
        auto myPath = path;
        while (myPath) {
            if (myPath->coords == coords) {
                //cout << "path test failed" << endl;
                return nullptr;
            }
            myPath = myPath->parent;
        }
        cout << "Candidate " << coords.first << " " << coords.second << " passed path test" << endl;
        if (code == currentComponentIndex) { //we're back into the empty room of the same component, nothing to do there.
            //cout << "code test failed: code " << code  << endl;
            return nullptr;
        }
        //cout << "Entering already visited cell " << coords.first <<  " " << coords.second << endl;
        _visited = true;
    }

    visited[coords.first][coords.second] = true;


    if (code == SYMBOL_PLUS) {
        return nullptr; //Unbreakable barrier
    }

    if (code == SYMBOL_BAR || code == SYMBOL_MINUS) {
            path = new Path(path, coords);

        return new TraversableVertex(coords, path, currentComponentIndex);
    } else {
        if (code >=0 && code != currentComponentIndex) { // We found an edge
            assert(path);
            mazeZonesGraph->addEdge(new Edge (currentComponentIndex, code, path->weight, path));
            path = nullptr;
            currentComponentIndex = code;
        } else {
            assert(code >= 0);
        }
        return _visited ? nullptr :  new TraversableVertex(coords, path, currentComponentIndex);
    }

}

void Maze::connect (int component, coordinates targetCoords, coordinates wallCoords) {
    dfsConnect(targetCoords, component);
    data[wallCoords.first][wallCoords.second] = component;
}

void Maze::dfsConnect(coordinates coords, int component) {
    if (data[coords.first][coords.second] == component) {
        return;
    }
    cout << "Dfs: " << coords.first << " " << coords.second << " for component " << component << endl;
    data[coords.first][coords.second] = component;
    if (coords.first > 0 && data[coords.first - 1][coords.second] >= 0) {

        dfsConnect(coordinates(coords.first - 1, coords.second), component);
    }
    if (coords.first < data.size() - 1 && data[coords.first + 1][coords.second] >= 0) {
        dfsConnect(coordinates(coords.first + 1, coords.second), component);
    }
    if (coords.second > 0 && data[coords.first][coords.second - 1] >= 0) {
        dfsConnect(coordinates(coords.first, coords.second - 1), component);
    }
    if (coords.second < data[coords.first].size() - 1 && data[coords.first][coords.second + 1] >= 0 ) {
        dfsConnect(coordinates(coords.first, coords.second + 1), component);
    }
}

ostream &operator<<(ostream &out, const Maze &maze) {
    out << endl;
    printHeader(out, maze);
    for (int i = 0; i < maze.data.size(); ++i) {
        for (int j = 0; j < maze.data[i].size(); ++j) {
            if (j == 0) {
                if (i % 2 == 0) {
                    out << "| ";
                } else {
                    out << "+ ";
                }
            }
            switch(maze.data[i][j]) {
                case SYMBOL_MINUS:
                    out << "- ";
                    break;
                case SYMBOL_BAR:
                    out << "| ";
                    break;
                case SYMBOL_PLUS:
                    out << "+ ";
                    break;
                default:
                    out << ". ";
                    break;
            }
        }
        if (i % 2 == 0) {
            out << "|\n";
        }
        else {
            out << "+\n";
        }
    }
    printHeader(out, maze);
    return out;
}

ostream &printHeader(ostream &out, const Maze &maze) {
    bool plus = true;
    for (int j = 0; j <= maze.data[0].size() + 1; j++) {
        if (plus) {
            out  << "+ ";
        } else {
            out << "- ";
        }
        plus = !plus;
    }
    out << "\n";
    return out;
}










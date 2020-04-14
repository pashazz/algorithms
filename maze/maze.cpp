//
// Created by Pasha on 13.04.2020.
//
/**
 * 1. Создать связанные компоненты
 * 2. С помощью DFS пойти из компоненты 0 искать другие компоненты.
 */

#include <iostream>
#include "maze.h"



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

void Maze::goFind() {
    //Traverse every row: remove bars
    for (int i = 0; i < data.size(); i += 2) {
        //We won't touch rows 1, 3, etc as they won't contain BARS
        for (int j = 1; j < data[i].size(); j+= 2) {
            //We won't touch cols 0, 2, etc as they wont contain BARS either.
            assert(data[i][j] >= 0 || data[i][j] == SYMBOL_BAR);
            if (data[i][j] == SYMBOL_BAR) {
                assert(data[i][j-1] >= 0);
                assert(data[i][j+1] >= 0);
                if (data[i][j-1] != data[i][j+1]) {
                    if (data[i][j-1] < data[i][j+1]) {
                        connect(data[i][j-1],
                                coordinates(i, j+1), coordinates(i, j));

                    } else {
                        connect(data[i][j+1],
                                coordinates (i, j-1), coordinates(i,j));
                    }
                }
            }
        }
    }

    //Traverse every column: remove minuses

    for (int j = 0; j < data[0].size(); j += 2) {
        //We won't touch columns 1, 3 etc as they are PLUSes
        for (int i = 1; i < data.size(); i += 2) {
            //We won't touch rows 0, 2 etc as they're already processed
            assert(data[i][j] >=0 || data[i][j] == SYMBOL_MINUS);
            if (data[i][j] == SYMBOL_MINUS) {
                assert(data[i-1][j] >= 0);
                assert(data[i+1][j] >= 0);
                if (data[i-1][j] != data[i+1][j]) {
                    if (data[i-1][j] < data[i+1][j]) {
                        connect(data[i-1][j], coordinates(i+1, j), coordinates(i, j));

                    } else {
                        connect(data[i+1][j], coordinates(i-1, j), coordinates(i, j));
                    }
                }
            }

        }
    }
}

void Maze::connect (int component, coordinates targetCoords, coordinates wallCoords) {
    dfs(targetCoords, component);
    data[wallCoords.first][wallCoords.second] = component;
}

void Maze::dfs(coordinates coords, int component) {
    if (data[coords.first][coords.second] == component) {
        return;
    }
    cout << "Dfs: " << coords.first << " " << coords.second << " for component " << component << endl;
    data[coords.first][coords.second] = component;
    if (coords.first > 0 && data[coords.first - 1][coords.second] >= 0) {

        dfs(coordinates(coords.first - 1, coords.second), component);
    }
    if (coords.first < data.size() - 1 && data[coords.first + 1][coords.second] >= 0) {
        dfs(coordinates(coords.first + 1, coords.second), component);
    }
    if (coords.second > 0 && data[coords.first][coords.second - 1] >= 0) {
        dfs(coordinates(coords.first, coords.second - 1), component);
    }
    if (coords.second < data[coords.first].size() - 1 && data[coords.first][coords.second + 1] >= 0 ) {
        dfs(coordinates(coords.first, coords.second + 1), component);
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







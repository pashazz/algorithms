#include <iostream>
#include <fstream>
#include "maze.h"

int main() {
    Maze maze;
    fstream in("input1.txt");
    maze.readMaze(in);
    //cout << maze << endl;
    maze.make();
//    cout << "Maze made:\n";
    //fstream out("output2.txt");
    cout << maze << endl;
    return 0;
}

#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include <fstream>
#include "Graph.h"
#include <string>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;
ostream& operator<< (ostream &out, Path * p) {
    if (!p) {
        out << " negative cycle";
        return out;
    }
    out << p->source << " -> " << p->destination << ": " << p->length;
    return out;
}

void createGraph(const string& file) {
    auto start = steady_clock::now();
    cout << "From " << file << ": ";
    ifstream ifs (file);
    auto g = Graph::input(ifs);
    auto path = g->floydWarshallMinPath();
    auto end = steady_clock::now();


    cout << path << ": calculated in " << duration_cast<seconds>(end - start).count() << " s" << endl;
}

TEST_CASE("Graph 1") {
    //createGraph("g1.txt");
    //createGraph("g2.txt");
    createGraph("g3.txt");
}

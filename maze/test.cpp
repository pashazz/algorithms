//
// Created by Pasha on 14.04.2020.
//

#define CATCH_CONFIG_MAIN

#include "catch.hh"
#include "WeighedGraph.h"
#include <fstream>
#include "maze.h"
#include "Edge.h"

TEST_CASE("Comparison of edges is done right") {

    EdgeComparator cmp;
    SECTION("the edges with the same tail-head pair is the same regardless of the order") {
        Edge *e = new Edge(0, 1, 1, nullptr);
        Edge *e1 = new Edge (1, 0, 1, nullptr);
        REQUIRE_FALSE(cmp(e, e1));
        REQUIRE_FALSE(cmp(e1, e));
    }
    SECTION("the edges with same tail, different heads are different") {
        Edge *e = new Edge (0, 1, 1, nullptr);
        Edge *e1 = new Edge (0, 2, 1, nullptr);
        REQUIRE(cmp(e, e1) == true);
        REQUIRE(cmp(e1, e) == false);
    }

    SECTION("the edges with the same head, different tails are different") {
        Edge *e = new Edge (0, 2, 1, nullptr);
        Edge *e1 = new Edge (1, 2, 1, nullptr);
        REQUIRE(cmp(e, e1) == true);
        REQUIRE(cmp(e1, e) == false);
    }


}
/**
TEST_CASE("Graph is being built correctly with 2 comps") {
    Maze maze;
    ifstream ifs("input1.txt");
    maze.readMaze(ifs);
    maze.make();
    auto g = maze.getGraph();

    REQUIRE(g->getAdjList().size() == 2);
    REQUIRE(g->getWeightedEdges().size() == 1);
    REQUIRE(g->getAdjList()[0].size() == 1);
    REQUIRE(g->getAdjList()[1].size() == 1);


}
 */

TEST_CASE("Graph is being built correctly with 3 comps") {
    Maze maze;
    ifstream ifs("input2.txt");
    maze.readMaze(ifs);
    maze.make();
    cout << maze;
    auto g = maze.getGraph();

    REQUIRE(g->getAdjList().size() == 3);
    REQUIRE(g->getWeightedEdges().size() == 3);
    REQUIRE(g->getAdjList()[0].size() == 2);
    REQUIRE(g->getAdjList()[1].size() == 2);


}
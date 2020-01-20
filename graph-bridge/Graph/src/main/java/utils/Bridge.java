package utils;

import types.Graph;

import java.util.*;

//Finds a bridge
public class Bridge {
    final Graph g;
    Map<Integer, Integer> lowLink = new HashMap<>();
    Set<Graph.Edge> bridges = new HashSet<>();
    int currentE;
    public Bridge(Graph g) {
        this.g = g;
    }

    public Set<Graph.Edge> getBridges () {
        if (g.isDirected()) { // Return cached value
            return bridges;
        }
        currentE = 0;
        g.setDirected(true);
        dfs(g.getFirst(), -1, -1);
        return bridges;
    }

    /** The bridge edges criteria:
     * lowlink(head) > e (tail)
     *
     */
    private void dfs(int vertex, int parent, int currentE) {
        System.out.println("Going from " + parent + " to " + vertex);
        currentE++;
        assert g.isDirected();
        if (!lowLink.containsKey(vertex)) {
            lowLink.put(vertex, currentE);
        } else {
            if (parent >= 0) {
                if (lowLink.get(vertex) < lowLink.get(parent)) { //We've been there
                    lowLink.put(parent, lowLink.get(vertex));
                }
            }
            return;
        }

        //Remove backward edge
        g.removeEdge(vertex, parent);

        for (var head : g.getHeads(vertex)) {
            dfs(head, vertex, currentE);
            if (lowLink.get(head) < lowLink.get(vertex)) {
                lowLink.put(vertex, lowLink.get(head));
            }
            // Apply bridge criteria:
            // lowlink(head) > e(tail)
            if (lowLink.get(head) > currentE) {
                bridges.add(new Graph.Edge(vertex, head));
            }
        }
    }
}

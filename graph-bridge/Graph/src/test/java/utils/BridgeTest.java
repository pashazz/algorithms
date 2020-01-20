package utils;

import org.junit.Assert;
import org.junit.Test;
import static org.junit.Assert.*;
import types.Graph;

import java.util.HashSet;

public class BridgeTest {

    @Test
    public void testBridge1() {
        Graph g1 = new Graph();
        g1.addEdge(1, 0);
        g1.addEdge(0, 2);
        g1.addEdge(2, 1);
        g1.addEdge(0, 3);
        g1.addEdge(3, 4);

        var b = new Bridge(g1);
        var bs = b.getBridges();

        var expected = new HashSet<>();
        expected.add(new Graph.Edge(3,4));
        expected.add(new Graph.Edge(0,3));
        assertEquals(expected, bs);


    }

    @Test
    public void testBridge2() {
        Graph g2 = new Graph();
         g2.addEdge(0, 1);
        g2.addEdge(1, 2);
        g2.addEdge(2, 3);
        var b = new Bridge(g2);
        var bs = b.getBridges();

        var expected = new HashSet<>();
        expected.add(new Graph.Edge(2,3));
        expected.add(new Graph.Edge(1,2));
        expected.add(new Graph.Edge(0,1));
        assertEquals(expected, bs);
    }

    @Test
    public void testBridge3() {
        Graph g3 = new Graph();
        g3.addEdge(0, 1);
        g3.addEdge(1, 2);
        g3.addEdge(2, 0);
        g3.addEdge(1, 3);
        g3.addEdge(1, 4);
        g3.addEdge(1, 6);
        g3.addEdge(3, 5);
        g3.addEdge(4, 5);

        var expected = new HashSet<>();
        expected.add(new Graph.Edge(1,6));

        Bridge b = new Bridge(g3);
        var bs = b.getBridges();
        assertEquals(expected, bs);

    }
}


import types.Graph;
import utils.Bridge;

import java.util.Collection;

public  class main {
    public static void main(String[] args) {
        Graph graph = new Graph(false);
        graph.addEdge(0,1);
        graph.addEdge(0, 4);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);
        graph.addEdge(4, 5);
        graph.printGraph();

        Bridge bridge = new Bridge(graph);
        Collection<Graph.Edge> bs = bridge.getBridges();
        for (Graph.Edge b : bs) {
            System.out.println(b);
        }
    }


}
package types;

import java.util.*;


public class Graph {
    protected Map<Integer, Set<Integer>> list = new HashMap<>();
    protected boolean directed = false;
    public static class Edge {
        public int tail;
        public int head;

        public Edge (int tail, int head) {
            this.tail = tail;
            this.head = head;


        }
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Edge edge = (Edge) o;
            return tail == edge.tail &&
                    head == edge.head;
        }

        @Override
        public int hashCode() {
            return Objects.hash(tail, head);
        }

        @Override
        public String toString() {
            return "(" + tail + ", " + head + ")";
        }
    }
    public  Graph () {
        this(false);
    }
    public Graph (boolean directed) {
        this.directed = directed;
    }

    public Set<Integer> getHeads (int tail) {
        return list.get(tail);
    }
    public int getFirst() {
        return list.keySet().iterator().next();
    }

    public void addVertex(int index) {
        list.putIfAbsent(index, new HashSet<>());
    }
    public void addEdge(int tail, int head) {
        addVertex(tail);
        list.get(tail).add(head);

        if (!directed) { // for undirected we mirror the thing
            addVertex(head);
            list.get(head).add(tail);
        }
    }
    public void removeVertex(int vertex) {
        list.remove(vertex);
    }
    public void removeEdge (int tail, int head) {
        list.get(tail).remove(head);
        if (!directed) {
            list.get(head).remove(tail);
        }
    }

    public boolean isDirected() {
        return directed;
    }

    public void setDirected(boolean directed) {
        this.directed = directed;
    }

    public void printGraph() {
        for (Integer vertex : list.keySet()) {
            System.out.printf("%d is connected to (", vertex);
            for (Integer head : list.get(vertex)) {
                System.out.printf("%d ", head);
            }
            System.out.println(")");
        }
    }
}

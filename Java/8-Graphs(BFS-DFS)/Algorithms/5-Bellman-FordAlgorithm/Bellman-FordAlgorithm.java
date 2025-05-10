import java.util.*;
import java.lang.*;
import java.io.*;

class Graph {
    // A class to represent a weighted edge in the graph.
    static class Edge {
        int src, dest, weight;

        Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }
    }

    int V, E; // Number of vertices and edges
    Edge[] edges; // Array to store all edges of the graph

    Graph(int v, int e) {
        V = v;
        E = e;
        edges = new Edge[e];
        for (int i = 0; i < e; ++i) {
            edges[i] = new Edge(0,0,0); //initialise the edges
        }
    }

    // The main function to find shortest distances from source to all other vertices
    // using Bellman-Ford algorithm.  It also detects negative weight cycles.

    // Approach 1: Standard Bellman-Ford Algorithm
    void bellmanFord1(int src) {
        int[] dist = new int[V]; // Array to store shortest distances
        // Initialize all distances as INFINITE except the source vertex.
        for (int i = 0; i < V; ++i)
            dist[i] = Integer.MAX_VALUE;
        dist[src] = 0;

        // Relax all edges |V| - 1 times. A simple shortest path from src to any
        // other vertex can have at-most |V| - 1 edges.
        for (int i = 1; i < V; ++i) {
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
            }
        }

        // Check for negative-weight cycles.  The above step guarantees shortest
        // distances if graph doesn't contain negative weight cycle.  If we get
        // a shorter distance, it indicates that there is a negative weight cycle.
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                System.out.println("Graph contains negative weight cycle");
                return;
            }
        }
        printArr(dist, V, "Approach 1: Standard Bellman-Ford");
    }

    // A utility function to print the solution (distances)
    void printArr(int[] dist, int V, String approachName) {
        System.out.println(approachName + ": Vertex   Distance from Source");
        for (int i = 0; i < V; ++i)
            System.out.println(i + "\t\t" + dist[i]);
    }

    // Approach 2: Bellman-Ford with Early Termination
    // If no changes occur during an iteration, we can terminate early.
    void bellmanFord2(int src) {
        int[] dist = new int[V];
        for (int i = 0; i < V; ++i)
            dist[i] = Integer.MAX_VALUE;
        dist[src] = 0;

        boolean updated; // Added a flag to check for updates
        for (int i = 1; i < V; ++i) {
            updated = false; // Reset the flag
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    updated = true; // Set flag if updated
                }
            }
            if (!updated) // If no update, we are done.
                break;
        }

        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                System.out.println("Graph contains negative weight cycle");
                return;
            }
        }
        printArr(dist, V, "Approach 2: Bellman-Ford with Early Termination");
    }

    // Approach 3: Bellman-Ford with Queue (Optimization, not always faster)
    // Uses a queue to process only the nodes that have been updated.
    void bellmanFord3(int src) {
        int[] dist = new int[V];
        for (int i = 0; i < V; ++i)
            dist[i] = Integer.MAX_VALUE;
        dist[src] = 0;

        boolean[] inQueue = new boolean[V]; // Keep track of nodes in queue
        Queue<Integer> queue = new LinkedList<>();
        queue.add(src);
        inQueue[src] = true;
        int iterations = 0; //iteration counter

        while (!queue.isEmpty() && iterations < V) { // Added iteration limit.
            int u = queue.poll();
            inQueue[u] = false;
            iterations++;
            for (int j = 0; j < E; ++j) {
                if (edges[j].src == u) {
                    int v = edges[j].dest;
                    int weight = edges[j].weight;
                    if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        if (!inQueue[v]) {
                            queue.add(v);
                            inQueue[v] = true;
                        }
                    }
                }
            }
        }

        if (iterations >= V) {
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                    System.out.println("Graph contains negative weight cycle");
                    return;
                }
            }
        }
        printArr(dist, V, "Approach 3: Bellman-Ford with Queue");
    }

    // Approach 4: Bellman Ford using Adjacency List
    void bellmanFord4(int src, ArrayList<ArrayList<Edge>> adjList) {
        int[] dist = new int[V];
        for (int i = 0; i < V; i++) {
            dist[i] = Integer.MAX_VALUE;
        }
        dist[src] = 0;

        for (int i = 1; i < V; i++) {
            for (int u = 0; u < V; u++) {
                if (dist[u] != Integer.MAX_VALUE) {
                    for (Edge edge : adjList.get(u)) {
                        int v = edge.dest;
                        int weight = edge.weight;
                        if (dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                        }
                    }
                }
            }
        }
        for (int u = 0; u < V; u++) {
            if (dist[u] != Integer.MAX_VALUE) {
                for (Edge edge : adjList.get(u)) {
                    int v = edge.dest;
                    int weight = edge.weight;
                    if (dist[u] + weight < dist[v]) {
                        System.out.println("Graph contains negative weight cycle");
                        return;
                    }
                }
            }
        }
        printArr(dist, V, "Approach 4: Bellman-Ford with Adjacency List");
    }

    // Approach 5: Bellman Ford using Relax function
    void bellmanFord5(int src) {
        int[] dist = new int[V];
        for (int i = 0; i < V; ++i)
            dist[i] = Integer.MAX_VALUE;
        dist[src] = 0;

        for (int i = 1; i < V; ++i) {
            for (int j = 0; j < E; ++j) {
                relax(edges[j].src, edges[j].dest, edges[j].weight, dist);
            }
        }

        for (int j = 0; j < E; ++j) {
            if (dist[edges[j].src] != Integer.MAX_VALUE && dist[edges[j].src] + edges[j].weight < dist[edges[j].dest]) {
                System.out.println("Graph contains negative weight cycle");
                return;
            }
        }
        printArr(dist, V, "Approach 5: Bellman-Ford with Relax Function");
    }
    // Relax function to update the distance.
    void relax(int u, int v, int weight, int[] dist) {
        if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        int V = 5; // Number of vertices
        int E = 8; // Number of edges

        Graph graph = new Graph(V, E);

        // Example graph with negative weight edges
        graph.edges[0] = new Graph.Edge(0, 1, -1);
        graph.edges[1] = new Graph.Edge(0, 2, 4);
        graph.edges[2] = new Graph.Edge(1, 2, 3);
        graph.edges[3] = new Graph.Edge(1, 3, 2);
        graph.edges[4] = new Graph.Edge(1, 4, 2);
        graph.edges[5] = new Graph.Edge(3, 2, 5);
        graph.edges[6] = new Graph.Edge(3, 1, 1);
        graph.edges[7] = new Graph.Edge(4, 3, -3);

        int src = 0; // Source vertex

        graph.bellmanFord1(src);
        graph.bellmanFord2(src);
        graph.bellmanFord3(src);

        // Adjacency List representation for Approach 4
        ArrayList<ArrayList<Graph.Edge>> adjList = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adjList.add(new ArrayList<>());
        }
        for (int i = 0; i < E; i++) {
            Graph.Edge edge = graph.edges[i];
            adjList.get(edge.src).add(edge);
        }
        graph.bellmanFord4(src, adjList);
        graph.bellmanFord5(src);
    }
}

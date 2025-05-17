import java.util.*;
import java.lang.*;
import java.io.*;

class Graph {
    int V, E; // Number of vertices and edges
    List<Edge> edges; // Using a List to store edges, more flexible

    // Inner class representing an edge
    class Edge implements Comparable<Edge> {
        int src, dest, weight;

        public Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }

        // Comparison function to sort edges by weight (non-decreasing order)
        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight;
        }

        @Override
        public String toString() {
            return src + " - " + dest + " : " + weight;
        }
    }

    public Graph(int v) {
        V = v;
        E = 0;
        edges = new ArrayList<>(); // Initialize the edges list
    }

    // Function to add an edge to the graph
    public void addEdge(int src, int dest, int weight) {
        edges.add(new Edge(src, dest, weight)); // Add edge to the list
        E++;
    }

    // Method to represent the Graph as Adjacency List (Useful for some approaches, not directly used in Kruskal itself)
    public List<List<Integer>> getAdjacencyList() {
        List<List<Integer>> adjList = new ArrayList<>(V);
        for (int i = 0; i < V; i++) {
            adjList.add(new ArrayList<>());
        }
        for (Edge edge : edges) {
            adjList.get(edge.src).add(edge.dest);
            adjList.get(edge.dest).add(edge.src); // Assuming undirected graph
        }
        return adjList;
    }

    // 1. Kruskal's Algorithm using Union-Find (Path Compression and Rank) - Efficient
    public List<Edge> kruskalMST_PathCompressionRank() {
        List<Edge> result = new ArrayList<>();
        Collections.sort(edges); // Sort edges by weight

        int[] parent = new int[V];
        int[] rank = new int[V];

        // Create V subsets with single elements
        for (int i = 0; i < V; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        int edgeCount = 0;
        int index = 0;

        while (edgeCount < V - 1 && index < E) {
            Edge currentEdge = edges.get(index++);
            int srcParent = findParent_PathCompression(parent, currentEdge.src);
            int destParent = findParent_PathCompression(parent, currentEdge.dest);

            if (srcParent != destParent) {
                result.add(currentEdge);
                edgeCount++;
                unionByRank(parent, rank, srcParent, destParent);
            }
        }
        return result;
    }

    // Find operation with path compression
    private int findParent_PathCompression(int[] parent, int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = findParent_PathCompression(parent, parent[i]); // Path compression
    }

    // Union operation using rank
    private void unionByRank(int[] parent, int[] rank, int x, int y) {
        if (rank[x] < rank[y])
            parent[x] = y;
        else if (rank[x] > rank[y])
            parent[y] = x;
        else {
            parent[y] = x;
            rank[x]++;
        }
    }


    // 2. Kruskal's Algorithm using Union-Find (Path Compression, No Rank) - Less Efficient than with Rank
    public List<Edge> kruskalMST_PathCompression() {
        List<Edge> result = new ArrayList<>();
        Collections.sort(edges);

        int[] parent = new int[V];
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int edgeCount = 0;
        int index = 0;

        while (edgeCount < V - 1 && index < E) {
            Edge currentEdge = edges.get(index++);
            int srcParent = findParent_PathCompression(parent, currentEdge.src);
            int destParent = findParent_PathCompression(parent, currentEdge.dest);

            if (srcParent != destParent) {
                result.add(currentEdge);
                edgeCount++;
                parent[srcParent] = destParent; // Simple union, no rank
            }
        }
        return result;
    }


    // 3. Kruskal's Algorithm using Union-Find (Simple Union, No Path Compression) - Least Efficient
    public List<Edge> kruskalMST_SimpleUnion() {
        List<Edge> result = new ArrayList<>();
        Collections.sort(edges);

        int[] parent = new int[V];
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int edgeCount = 0;
        int index = 0;

        while (edgeCount < V - 1 && index < E) {
            Edge currentEdge = edges.get(index++);
            int srcParent = findParent_Simple(parent, currentEdge.src);
            int destParent = findParent_Simple(parent, currentEdge.dest);

            if (srcParent != destParent) {
                result.add(currentEdge);
                edgeCount++;
                parent[srcParent] = destParent; // Simple union, no path compression
            }
        }
        return result;
    }

    private int findParent_Simple(int[] parent, int i) {
        if (parent[i] == i)
            return i;
        return findParent_Simple(parent, parent[i]); // No path compression
    }

    // 4. Kruskal's Algorithm using iterative DFS for cycle detection -  Less efficient for large graphs
    public List<Edge> kruskalMST_DFS() {
        List<Edge> result = new ArrayList<>();
        Collections.sort(edges);

        List<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }

        int edgeCount = 0;
        int index = 0;

        while (edgeCount < V - 1 && index < E) {
            Edge currentEdge = edges.get(index++);
            int src = currentEdge.src;
            int dest = currentEdge.dest;

            // Add the edge temporarily to check for cycles
            adj[src].add(dest);
            adj[dest].add(src);

            if (!hasCycleDFS(adj, src, dest)) {
                result.add(currentEdge);
                edgeCount++;
            } else {
                // Remove the edge if it creates a cycle
                adj[src].remove(adj[src].indexOf(dest));
                adj[dest].remove(adj[dest].indexOf(src));
            }
        }
        return result;
    }

    private boolean hasCycleDFS(List<Integer>[] adj, int start, int end) {
        Set<Integer> visited = new HashSet<>();
        Stack<Integer> stack = new Stack<>();
        stack.push(start);
        visited.add(start);

        while (!stack.isEmpty()) {
            int u = stack.pop();
            if (u == end) return true; // Cycle detected

            for (Integer neighbor : adj[u]) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    stack.push(neighbor);
                }
            }
        }
        return false;
    }

    // 5. Kruskal's Algorithm using BFS for cycle detection - Less efficient for large graphs
    public List<Edge> kruskalMST_BFS() {
        List<Edge> result = new ArrayList<>();
        Collections.sort(edges);

        List<Integer>[] adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<>();
        }

        int edgeCount = 0;
        int index = 0;

        while (edgeCount < V - 1 && index < E) {
            Edge currentEdge = edges.get(index++);
            int src = currentEdge.src;
            int dest = currentEdge.dest;

            // Add the edge temporarily to check for cycles
            adj[src].add(dest);
            adj[dest].add(src);

            if (!hasCycleBFS(adj, src, dest)) {
                result.add(currentEdge);
                edgeCount++;
            } else {
                // Remove the edge if it creates a cycle
                adj[src].remove(adj[src].indexOf(dest));
                adj[dest].remove(adj[dest].indexOf(src));
            }
        }
        return result;
    }

    private boolean hasCycleBFS(List<Integer>[] adj, int start, int end) {
        Set<Integer> visited = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            if (u == end) return true;

            for (Integer neighbor : adj[u]) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.offer(neighbor);
                }
            }
        }
        return false;
    }
}

public class Main {
    public static void main(String[] args) {
        int V = 7; // Number of vertices
        Graph graph = new Graph(V);
        graph.addEdge(0, 1, 7);
        graph.addEdge(0, 2, 8);
        graph.addEdge(1, 2, 3);
        graph.addEdge(1, 3, 6);
        graph.addEdge(2, 3, 4);
        graph.addEdge(2, 5, 2);
        graph.addEdge(3, 4, 5);
        graph.addEdge(3, 5, 7);
        graph.addEdge(4, 5, 1);
        graph.addEdge(4, 6, 9);
        graph.addEdge(5, 6, 10);

        System.out.println("Graph Edges:");
        for(Graph.Edge edge: graph.edges){
            System.out.println(edge);
        }

        System.out.println("\nKruskal's MST using Path Compression and Rank:");
        List<Graph.Edge> mstPathRank = graph.kruskalMST_PathCompressionRank();
        printMST(mstPathRank);

        System.out.println("\nKruskal's MST using Path Compression (No Rank):");
        List<Graph.Edge> mstPath = graph.kruskalMST_PathCompression();
        printMST(mstPath);

        System.out.println("\nKruskal's MST using Simple Union (No Path Compression):");
        List<Graph.Edge> mstSimpleUnion = graph.kruskalMST_SimpleUnion();
        printMST(mstSimpleUnion);

        System.out.println("\nKruskal's MST using DFS for cycle detection:");
        List<Graph.Edge> mstDFS = graph.kruskalMST_DFS();
        printMST(mstDFS);

        System.out.println("\nKruskal's MST using BFS for cycle detection:");
        List<Graph.Edge> mstBFS = graph.kruskalMST_BFS();
        printMST(mstBFS);
    }

    // Function to print the Minimum Spanning Tree
    public static void printMST(List<Graph.Edge> result) {
        int cost = 0;
        for (Graph.Edge edge : result) {
            System.out.println(edge);
            cost += edge.weight;
        }
        System.out.println("Minimum Spanning Tree Cost: " + cost);
    }
}

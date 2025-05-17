import java.util.*;
import java.io.*;

public class KruskalMST {

    // Basic Edge class to represent an edge in the graph
    static class Edge implements Comparable<Edge> {
        int src, dest, weight;

        public Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight; // Sort edges by weight
        }

        @Override
        public String toString() {
            return "(" + src + " -- " + dest + ") : " + weight;
        }
    }

    // 1. Kruskal's Algorithm using Union-Find (Disjoint Set) - Classic Implementation
    //    - Uses an array to represent the parent of each node in the disjoint set.
    //    - find() uses path compression for optimization.
    //    - union() uses union by rank for optimization.
    public static List<Edge> kruskalMST_UnionFind(int numVertices, List<Edge> edges) {
        List<Edge> mst = new ArrayList<>();
        Collections.sort(edges); // Sort edges by weight

        int[] parent = new int[numVertices];
        int[] rank = new int[numVertices]; // Added for union by rank
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i; // Initialize each node as its own parent
            rank[i] = 0;  // Initialize rank of each node to 0
        }

        for (Edge edge : edges) {
            int rootSrc = find(parent, edge.src);
            int rootDest = find(parent, edge.dest);

            if (rootSrc != rootDest) {
                mst.add(edge);
                union(parent, rank, rootSrc, rootDest); // Use union by rank
            }
        }
        return mst;
    }

    // Find operation with path compression
    private static int find(int[] parent, int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent, parent[i]); // Path compression
    }

    // Union operation using union by rank
    private static void union(int[] parent, int[] rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // 2. Kruskal's Algorithm using a HashMap for Disjoint Set - Alternative Representation
    //    - Uses a HashMap to store the parent of each node.  Useful if node IDs are not simple integers.
    public static List<Edge> kruskalMST_HashMap(Set<Integer> vertices, List<Edge> edges) {
        List<Edge> mst = new ArrayList<>();
        Collections.sort(edges);

        Map<Integer, Integer> parentMap = new HashMap<>();
        Map<Integer, Integer> rankMap = new HashMap<>(); // Added for union by rank
        for (Integer vertex : vertices) {
            parentMap.put(vertex, vertex);
            rankMap.put(vertex, 0);
        }

        for (Edge edge : edges) {
            int rootSrc = findMap(parentMap, edge.src);
            int rootDest = findMap(parentMap, edge.dest);

            if (rootSrc != rootDest) {
                mst.add(edge);
                unionMap(parentMap, rankMap, rootSrc, rootDest);
            }
        }
        return mst;
    }

    // Find operation for HashMap
    private static int findMap(Map<Integer, Integer> parentMap, int i) {
        if (parentMap.get(i) == i)
            return i;
        int root = findMap(parentMap, parentMap.get(i));
        parentMap.put(i, root); // Path compression
        return root;
    }

    // Union operation for HashMap using union by rank
    private static void unionMap(Map<Integer, Integer> parentMap, Map<Integer, Integer> rankMap, int x, int y) {
        int rootX = findMap(parentMap, x);
        int rootY = findMap(parentMap, y);

        if (rootX != rootY) {
            if (rankMap.get(rootX) < rankMap.get(rootY)) {
                parentMap.put(rootX, rootY);
            } else if (rankMap.get(rootX) > rankMap.get(rootY)) {
                parentMap.put(rootY, rootX);
            } else {
                parentMap.put(rootY, rootX);
                rankMap.put(rootX, rankMap.get(rootX) + 1);
            }
        }
    }

    // 3. Kruskal's Algorithm with Path Compression and Rank Optimization (Optimized)
    //    - This is a direct optimization of the first approach, making it more efficient.
    public static List<Edge> kruskalMST_Optimized(int numVertices, List<Edge> edges) {
        List<Edge> mst = new ArrayList<>();
        Collections.sort(edges);

        int[] parent = new int[numVertices];
        int[] rank = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        for (Edge edge : edges) {
            int rootSrc = findOptimized(parent, edge.src);
            int rootDest = findOptimized(parent, edge.dest);

            if (rootSrc != rootDest) {
                mst.add(edge);
                unionOptimized(parent, rank, rootSrc, rootDest);
            }
        }
        return mst;
    }

    // Optimized find with path compression
    private static int findOptimized(int[] parent, int i) {
        if (parent[i] != i)
            parent[i] = findOptimized(parent, parent[i]);
        return parent[i];
    }

    // Optimized union by rank
    private static void unionOptimized(int[] parent, int[] rank, int x, int y) {
        int rootX = findOptimized(parent, x);
        int rootY = findOptimized(parent, y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // 4. Kruskal's Algorithm for Disconnected Graphs
    //    - Handles graphs that may have multiple disconnected components.
    public static List<Edge> kruskalMST_Disconnected(int numVertices, List<Edge> edges) {
        List<Edge> mst = new ArrayList<>();
        Collections.sort(edges);

        int[] parent = new int[numVertices];
        int[] rank = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        int numTrees = numVertices; // Initially, each vertex is its own tree
        for (Edge edge : edges) {
            int rootSrc = findOptimized(parent, edge.src);
            int rootDest = findOptimized(parent, edge.dest);

            if (rootSrc != rootDest) {
                mst.add(edge);
                unionOptimized(parent, rank, rootSrc, rootDest);
                numTrees--; // Joining two trees reduces the number of trees by 1
            }
            if (numTrees == 1) break; // Optimization: Stop when only one tree remains
        }
        if(numTrees > 1){
            System.out.println("Graph is disconnected.  MST is a Minimum Spanning Forest.");
        }
        return mst;
    }


    // 5. Kruskal's Algorithm with Edge Class Enhancement (Real-World Application)
    //    -  Demonstrates a more complex Edge class that might be used in a real-world scenario,
    //       such as network design, where edges have additional properties like bandwidth and cost.
    //    -  The `compareTo` method is adjusted to prioritize bandwidth and then cost (for example).
    static class NetworkEdge implements Comparable<NetworkEdge> {
        int src, dest;
        double bandwidth; // Example: Bandwidth of the connection
        double cost;     // Example: Cost of the connection

        public NetworkEdge(int src, int dest, double bandwidth, double cost) {
            this.src = src;
            this.dest = dest;
            this.bandwidth = bandwidth;
            this.cost = cost;
        }

        @Override
        public int compareTo(NetworkEdge other) {
            // Prioritize higher bandwidth, then lower cost
            if (this.bandwidth != other.bandwidth) {
                return Double.compare(other.bandwidth, this.bandwidth); // Descending order of bandwidth
            }
            return Double.compare(this.cost, other.cost); // Ascending order of cost
        }

        @Override
        public String toString() {
            return "(" + src + " -- " + dest + ") : Bandwidth=" + bandwidth + ", Cost=" + cost;
        }
    }

    public static List<NetworkEdge> kruskalMST_Network(int numVertices, List<NetworkEdge> networkEdges) {
        List<NetworkEdge> mst = new ArrayList<>();
        Collections.sort(networkEdges);

        int[] parent = new int[numVertices];
        int[] rank = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        for (NetworkEdge edge : networkEdges) {
            int rootSrc = findOptimized(parent, edge.src);
            int rootDest = findOptimized(parent, edge.dest);

            if (rootSrc != rootDest) {
                mst.add(edge);
                unionOptimized(parent, rank, rootSrc, rootDest);
            }
        }
        return mst;
    }



    public static void main(String[] args) {
        // Example graph represented as a list of edges
        int numVertices = 7;
        List<Edge> edges = new ArrayList<>();
        edges.add(new Edge(0, 1, 7));
        edges.add(new Edge(0, 2, 8));
        edges.add(new Edge(1, 2, 3));
        edges.add(new Edge(1, 3, 6));
        edges.add(new Edge(2, 3, 4));
        edges.add(new Edge(2, 4, 9));
        edges.add(new Edge(3, 4, 5));
        edges.add(new Edge(3, 5, 10));
        edges.add(new Edge(4, 5, 8));
        edges.add(new Edge(4, 6, 11));
        edges.add(new Edge(5, 6, 9));

        System.out.println("Example Graph Edges:");
        for (Edge edge : edges) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");

        // 1. Kruskal's Algorithm using Union-Find
        System.out.println("Kruskal's MST (Union-Find):");
        List<Edge> mst1 = kruskalMST_UnionFind(numVertices, new ArrayList<>(edges)); // Pass a copy to avoid modifying the original
        for (Edge edge : mst1) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");

        // 2. Kruskal's Algorithm using HashMap
        Set<Integer> verticesSet = new HashSet<>();
        for (Edge edge : edges) {
            verticesSet.add(edge.src);
            verticesSet.add(edge.dest);
        }
        System.out.println("Kruskal's MST (HashMap):");
        List<Edge> mst2 = kruskalMST_HashMap(verticesSet, new ArrayList<>(edges));
        for (Edge edge : mst2) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");

        // 3. Kruskal's Algorithm with Path Compression and Rank Optimization
        System.out.println("Kruskal's MST (Optimized):");
        List<Edge> mst3 = kruskalMST_Optimized(numVertices, new ArrayList<>(edges));
        for (Edge edge : mst3) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");

        // 4. Kruskal's Algorithm for Disconnected Graphs
        System.out.println("Kruskal's MST (Disconnected Graph):");
        List<Edge> mst4 = kruskalMST_Disconnected(numVertices, new ArrayList<>(edges));
        for (Edge edge : mst4) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");

        // 5. Kruskal's Algorithm with Edge Class Enhancement (Real-World)
        int numNetworkVertices = 6;
        List<NetworkEdge> networkEdges = new ArrayList<>();
        networkEdges.add(new NetworkEdge(0, 1, 100, 10)); // Example: Bandwidth 100, Cost 10
        networkEdges.add(new NetworkEdge(0, 2, 150, 15));
        networkEdges.add(new NetworkEdge(1, 2, 60, 5));
        networkEdges.add(new NetworkEdge(1, 3, 80, 8));
        networkEdges.add(new NetworkEdge(2, 3, 70, 7));
        networkEdges.add(new NetworkEdge(2, 4, 120, 12));
        networkEdges.add(new NetworkEdge(3, 4, 90, 9));
        networkEdges.add(new NetworkEdge(3, 5, 110, 11));
        networkEdges.add(new NetworkEdge(4, 5, 100, 10));

        System.out.println("Kruskal's MST (Network):");
        List<NetworkEdge> mst5 = kruskalMST_Network(numNetworkVertices, networkEdges);
        for (NetworkEdge edge : mst5) {
            System.out.println(edge);
        }
        System.out.println("\n--------------------------------------------------------");
    }
}


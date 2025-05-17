import java.util.*;

public class PrimsAlgorithm {

    // Utility function to represent an edge in the graph
    static class Edge {
        int source;
        int destination;
        int weight;

        public Edge(int source, int destination, int weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }
    }

    // Utility function to represent a graph
    static class Graph {
        int vertices;
        List<List<Edge>> adjacencyList;

        public Graph(int vertices) {
            this.vertices = vertices;
            this.adjacencyList = new ArrayList<>(vertices);
            for (int i = 0; i < vertices; i++) {
                this.adjacencyList.add(new ArrayList<>());
            }
        }

        public void addEdge(int source, int destination, int weight) {
            Edge edge = new Edge(source, destination, weight);
            this.adjacencyList.get(source).add(edge);
            this.adjacencyList.get(destination).add(edge); // For undirected graph
        }
    }

    // 1. Basic Prim's Algorithm using Priority Queue
    //   - Uses a PriorityQueue to select the minimum weight edge.
    //   - Suitable for general MST problems.
    public static List<Edge> primMSTBasic(Graph graph) {
        int vertices = graph.vertices;
        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(edge -> edge.weight));
        boolean[] visited = new boolean[vertices];
        List<Edge> mstEdges = new ArrayList<>();

        // Start from the first vertex (you can choose any starting vertex)
        visited[0] = true;
        addAllAdjacentEdges(graph, 0, pq, visited);

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int destination = currentEdge.destination;
            int source = currentEdge.source;

            if (visited[destination] && visited[source]) {
                continue; // Skip if both ends are already in MST
            }

            mstEdges.add(currentEdge);
            if (!visited[destination]) {
                visited[destination] = true;
                addAllAdjacentEdges(graph, destination, pq, visited);
            }
            if (!visited[source]) {
                visited[source] = true;
                addAllAdjacentEdges(graph, source, pq, visited);
            }
        }
        return mstEdges;
    }

    // Helper function to add all adjacent edges of a vertex to the priority queue
    private static void addAllAdjacentEdges(Graph graph, int vertex, PriorityQueue<Edge> pq, boolean[] visited) {
        for (Edge edge : graph.adjacencyList.get(vertex)) {
            int neighbor = edge.destination == vertex ? edge.source : edge.destination; // get the other end
            if (!visited[neighbor]) {
                pq.offer(edge);
            }
        }
    }

    // 2. Prim's Algorithm with Adjacency Matrix
    //    - Uses an adjacency matrix representation of the graph.
    //    - Useful when the graph is dense (many edges).
    public static List<Edge> primMSTMatrix(int[][] adjacencyMatrix) {
        int vertices = adjacencyMatrix.length;
        int[] parent = new int[vertices];  // Array to store parent of each node in MST
        int[] key = new int[vertices];     // Array to store minimum weight edge for each node
        boolean[] mstSet = new boolean[vertices]; // Array to track vertices included in MST
        List<Edge> mstEdges = new ArrayList<>();

        // Initialize key values to infinity and mstSet to false
        for (int i = 0; i < vertices; i++) {
            key[i] = Integer.MAX_VALUE;
            mstSet[i] = false;
        }

        // Pick the first vertex as the starting vertex
        key[0] = 0;     // Make key 0 so that this vertex is picked first
        parent[0] = -1; // First node is always the root of MST

        // The MST will have V-1 edges
        for (int count = 0; count < vertices - 1; count++) {
            // Pick the minimum key vertex from the set of vertices not yet included in MST
            int u = minKey(key, mstSet);

            // Add the picked vertex to the MST Set
            mstSet[u] = true;

            // Update key value and parent index of the adjacent vertices of the picked vertex.
            // Consider only those vertices which are not yet included in MST
            for (int v = 0; v < vertices; v++) {
                // graph[u][v] is non zero only for adjacent vertices of m
                // mstSet[v] is false for vertices not yet included in MST
                // Update the key only if graph[u][v] is smaller than key[v]
                if (adjacencyMatrix[u][v] != 0 && !mstSet[v] && adjacencyMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjacencyMatrix[u][v];
                }
            }
        }

        // Construct the MST edges list
        for (int i = 1; i < vertices; i++) {
            mstEdges.add(new Edge(parent[i], i, adjacencyMatrix[i][parent[i]]));
        }
        return mstEdges;
    }

    // A utility function to find the vertex with minimum key value, from
    // the set of vertices not yet included in MST
    private static int minKey(int[] key, boolean[] mstSet) {
        // Initialize min value
        int min = Integer.MAX_VALUE, min_index = -1;

        for (int v = 0; v < key.length; v++)
            if (mstSet[v] == false && key[v] < min) {
                min = key[v];
                min_index = v;
            }

        return min_index;
    }

    // 3. Prim's Algorithm for a Disconnected Graph
    //    - Handles graphs where not all vertices are connected.
    //    - Finds MST for each connected component.
    public static List<List<Edge>> primMSTDisconnected(Graph graph) {
        int vertices = graph.vertices;
        boolean[] visited = new boolean[vertices];
        List<List<Edge>> mstList = new ArrayList<>();

        for (int startVertex = 0; startVertex < vertices; startVertex++) {
            if (!visited[startVertex]) {
                List<Edge> mstEdges = new ArrayList<>();
                PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(edge -> edge.weight));
                visited[startVertex] = true;
                addAllAdjacentEdges(graph, startVertex, pq, visited);

                while (!pq.isEmpty()) {
                    Edge currentEdge = pq.poll();
                    int destination = currentEdge.destination;
                    int source = currentEdge.source;

                    if (visited[destination] && visited[source]) {
                        continue;
                    }

                    mstEdges.add(currentEdge);
                    if (!visited[destination]) {
                        visited[destination] = true;
                        addAllAdjacentEdges(graph, destination, pq, visited);
                    }
                    if (!visited[source]) {
                        visited[source] = true;
                        addAllAdjacentEdges(graph, source, pq, visited);
                    }
                }
                mstList.add(mstEdges);
            }
        }
        return mstList;
    }

    // 4. Prim's Algorithm Optimized with Fibonacci Heap (Conceptual)
    //    - Uses a Fibonacci Heap (not directly available in standard Java library).
    //    - Provides better time complexity for large graphs (O(E + V log V)).
    //    -  This is a conceptual implementation.  In a real-world scenario,
    //       you would need a 3rd-party library or a custom implementation
    //       of a Fibonacci Heap.
    public static List<Edge> primMSTFibonacciHeap(Graph graph) {
        int vertices = graph.vertices;
        //  In a real implementation,  FibonacciHeap would be a custom class
        //  or a class from an external library.  Since Java doesn't have
        //  a built-in Fibonacci Heap,  we'll use a PriorityQueue
        //  for demonstration, but the time complexity won't be optimal.
        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(edge -> edge.weight));
        boolean[] visited = new boolean[vertices];
        List<Edge> mstEdges = new ArrayList<>();
        int[] key = new int[vertices];
        int[] parent = new int[vertices];

        for (int i = 0; i < vertices; i++) {
            key[i] = Integer.MAX_VALUE;
        }

        key[0] = 0;
        parent[0] = -1;
        pq.offer(new Edge(-1, 0, 0)); // Add a dummy edge with source -1 and weight 0 for the starting vertex

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int u = currentEdge.destination;

            if (visited[u]) {
                continue;
            }
            visited[u] = true;

            if (currentEdge.source != -1) { // Exclude the dummy edge
                mstEdges.add(currentEdge);
            }

            for (Edge edge : graph.adjacencyList.get(u)) {
                int v = edge.destination == u ? edge.source : edge.destination;
                if (!visited[v] && edge.weight < key[v]) {
                    key[v] = edge.weight;
                    parent[v] = u;
                    pq.offer(new Edge(u, v, edge.weight)); // Use u as source here
                }
            }
        }
        return mstEdges;
    }


    // 5. Parallel Prim's Algorithm using Fork/Join (Conceptual)
    //    - Uses Java's Fork/Join framework for parallel execution.
    //    - Suitable for very large graphs to improve performance.
    //    - This is a simplified conceptual example.  A full parallel
    //      implementation of Prim's algorithm is complex and often
    //      involves graph partitioning and careful synchronization.
    //    -  We will parallelize the adding of edges to the queue.
    //
    // NOTE: This is a simplified conceptual example. A full parallel
    // implementation of Prim's is quite complex.
    static class ParallelPrimTask extends java.util.concurrent.RecursiveAction {
        private final Graph graph;
        private final int vertex;
        private final PriorityQueue<Edge> pq;
        private final boolean[] visited;

        public ParallelPrimTask(Graph graph, int vertex, PriorityQueue<Edge> pq, boolean[] visited) {
            this.graph = graph;
            this.vertex = vertex;
            this.pq = pq;
            this.visited = visited;
        }

        @Override
        protected void compute() {
            List<java.util.concurrent.ForkJoinTask<?>> forks = new ArrayList<>();
            for (Edge edge : graph.adjacencyList.get(vertex)) {
                int neighbor = edge.destination == vertex ? edge.source : edge.destination;
                if (!visited[neighbor]) {
                    //  Instead of directly adding to the pq, create a subtask.
                    //  For a more complete parallel implementation, you might
                    //  also parallelize the heap operations or graph traversal.
                    forks.add(new java.util.concurrent.RecursiveAction() {
                        @Override
                        protected void compute() {
                            pq.offer(edge);
                        }
                    });
                }
            }
            for (java.util.concurrent.ForkJoinTask<?> fork : forks) {
                fork.fork();
            }
            for (java.util.concurrent.ForkJoinTask<?> fork : forks) {
                fork.join();
            }
        }
    }

    public static List<Edge> parallelPrimMST(Graph graph) {
        int vertices = graph.vertices;
        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(edge -> edge.weight));
        boolean[] visited = new boolean[vertices];
        List<Edge> mstEdges = new ArrayList<>();
        java.util.concurrent.ForkJoinPool pool = new java.util.concurrent.ForkJoinPool();

        visited[0] = true;
        // Use the ForkJoinPool to execute the initial task
        pool.invoke(new ParallelPrimTask(graph, 0, pq, visited));

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int destination = currentEdge.destination;
            int source = currentEdge.source;

            if (visited[destination] && visited[source]) {
                continue;
            }

            mstEdges.add(currentEdge);
            if (!visited[destination]) {
                visited[destination] = true;
                pool.invoke(new ParallelPrimTask(graph, destination, pq, visited));
            }
            if (!visited[source]) {
                visited[source] = true;
                pool.invoke(new ParallelPrimTask(graph, source, pq, visited));
            }
        }
        pool.shutdown();
        return mstEdges;
    }



    public static void main(String[] args) {
        // Example graph (same for all approaches for consistency)
        int vertices = 9;
        Graph graph = new Graph(vertices);
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 7, 8);
        graph.addEdge(1, 2, 8);
        graph.addEdge(1, 7, 11);
        graph.addEdge(2, 3, 7);
        graph.addEdge(2, 8, 2);
        graph.addEdge(2, 5, 4);
        graph.addEdge(3, 4, 9);
        graph.addEdge(3, 5, 14);
        graph.addEdge(4, 5, 10);
        graph.addEdge(5, 6, 2);
        graph.addEdge(6, 7, 1);
        graph.addEdge(6, 8, 6);
        graph.addEdge(7, 8, 7);

        // Example Adjacency Matrix for Approach 2
        int[][] adjacencyMatrix = {
                {0, 4, 0, 0, 0, 0, 0, 8, 0},
                {4, 0, 8, 0, 0, 0, 0, 11, 0},
                {0, 8, 0, 7, 0, 4, 0, 0, 2},
                {0, 0, 7, 0, 9, 14, 0, 0, 0},
                {0, 0, 0, 9, 0, 10, 0, 0, 0},
                {0, 0, 4, 14, 10, 0, 2, 0, 0},
                {0, 0, 0, 0, 0, 2, 0, 1, 6},
                {8, 11, 0, 0, 0, 0, 1, 0, 7},
                {0, 0, 2, 0, 0, 0, 6, 7, 0}
        };

        System.out.println("Prim's Algorithm Demonstrations\n");

        System.out.println("1. Basic Prim's Algorithm:");
        List<Edge> mstBasic = primMSTBasic(graph);
        printMST(mstBasic);

        System.out.println("\n2. Prim's Algorithm with Adjacency Matrix:");
        List<Edge> mstMatrix = primMSTMatrix(adjacencyMatrix);
        printMST(mstMatrix);

        System.out.println("\n3. Prim's Algorithm for Disconnected Graph:");
        List<List<Edge>> mstDisconnected = primMSTDisconnected(graph); // graph is connected, but we use the disconnected version to show how it would work.
        for (int i = 0; i < mstDisconnected.size(); i++){
            System.out.println("  Connected Component " + (i+1) + ":");
            printMST(mstDisconnected.get(i));
        }


        System.out.println("\n4. Prim's Algorithm Optimized with Fibonacci Heap (Conceptual):");
        List<Edge> mstFibonacci = primMSTFibonacciHeap(graph);
        printMST(mstFibonacci);

        System.out.println("\n5. Parallel Prim's Algorithm using Fork/Join (Conceptual):");
        List<Edge> mstParallel = parallelPrimMST(graph);
        printMST(mstParallel);
    }

    // Utility function to print the MST edges
    private static void printMST(List<Edge> mstEdges) {
        int totalWeight = 0;
        for (Edge edge : mstEdges) {
            System.out.println("Source: " + edge.source + ", Destination: " + edge.destination + ", Weight: " + edge.weight);
            totalWeight += edge.weight;
        }
        System.out.println("Total MST Weight: " + totalWeight);
    }
}

/*
Real-world project implementations for each approach:

1. Basic Prim's Algorithm using Priority Queue:
   - Network cabling: Finding the minimum length of cable required to connect all devices in a network.
   - Water distribution: Designing a network of pipes to connect all houses in a locality with the minimum cost.
   - General graph problems where an MST is needed.

2. Prim's Algorithm with Adjacency Matrix:
   - Circuit design: Finding the minimum amount of wire needed to connect electronic components on a circuit board.  Good if the circuit has a high density of components.
   - Image processing:  Used in some image segmentation algorithms where the graph represents pixel connectivity.

3. Prim's Algorithm for a Disconnected Graph:
  - Connecting islands with bridges: Finding the minimum cost to connect groups of islands with bridges.  Each group of islands is a connected component.
  - Power grid design: Connecting multiple isolated power grids with the minimum amount of transmission lines.

4. Prim's Algorithm Optimized with Fibonacci Heap (Conceptual):
   -  Large-scale network design:  For very large telecommunication or social networks where performance is critical.
   -  VLSI design:  For optimizing the layout of connections in very large-scale integrated circuits.
   -  Route finding in very large graphs.

5. Parallel Prim's Algorithm using Fork/Join (Conceptual):
    -  Massive infrastructure projects:  Optimizing the construction of highways, railways, or pipelines across very large geographical areas.
    -  Large-scale simulations:  Used in parallel computing applications where MST is a component of a larger simulation.
    -  Big data graph processing:  Analyzing relationships in extremely large datasets, where the graph is distributed across multiple machines.
*/

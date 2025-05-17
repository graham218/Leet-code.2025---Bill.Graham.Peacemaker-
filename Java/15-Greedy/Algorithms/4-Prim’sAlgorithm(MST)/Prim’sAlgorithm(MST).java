import java.util.*;

public class PrimsAlgorithm {

    // Inner class to represent an edge in the graph
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

    // Inner class to represent a node in the graph for adjacency list representation
    static class Node {
        int vertex;
        int weight;

        public Node(int vertex, int weight) {
            this.vertex = vertex;
            this.weight = weight;
        }
    }

    // 1. Prim's Algorithm using Priority Queue (Adjacency Matrix)
    //    - Uses a priority queue to select the minimum weight edge.
    //    - Uses an adjacency matrix to represent the graph.
    //    - Time Complexity: O(V^2 log V)  (can be improved to O(E log V) with adjacency list and min-priority queue)
    //    - Space Complexity: O(V^2)
    public static List<Edge> primMST_PQ_AM(int[][] graph, int numVertices) {
        // Check for null or empty graph
        if (graph == null || graph.length == 0 || graph.length != numVertices) {
            return new ArrayList<>(); // Return empty list for safety and consistency
        }

        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight)); // Min-Priority Queue
        boolean[] visited = new boolean[numVertices];
        List<Edge> mstEdges = new ArrayList<>();

        // Start from the first vertex (you can choose any vertex)
        visited[0] = true;

        // Add all edges from the starting vertex to the priority queue
        for (int i = 0; i < numVertices; i++) {
            if (graph[0][i] != 0) { // 0 indicates no edge
                pq.add(new Edge(0, i, graph[0][i]));
            }
        }

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int destination = currentEdge.destination;

            if (visited[destination]) {
                continue; // Skip if the destination vertex is already in the MST
            }

            visited[destination] = true;
            mstEdges.add(currentEdge);

            // Add new edges from the newly added vertex to the priority queue
            for (int i = 0; i < numVertices; i++) {
                if (graph[destination][i] != 0 && !visited[i]) {
                    pq.add(new Edge(destination, i, graph[destination][i]));
                }
            }
        }
        return mstEdges;
    }


    // 2. Prim's Algorithm using Priority Queue (Adjacency List)
    //    - Uses a priority queue to select the minimum weight edge.
    //    - Uses an adjacency list to represent the graph.  This is generally preferred for sparse graphs.
    //    - Time Complexity: O(E log V)  Much better for sparse graphs.
    //    - Space Complexity: O(V + E)
    public static List<Edge> primMST_PQ_AL(List<List<Node>> adjList, int numVertices) {
        // Check for null or empty graph
        if (adjList == null || adjList.size() != numVertices) {
            return new ArrayList<>();
        }

        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight));
        boolean[] visited = new boolean[numVertices];
        List<Edge> mstEdges = new ArrayList<>();

        visited[0] = true; // Start from vertex 0

        // Add initial edges from the starting vertex
        for (Node neighbor : adjList.get(0)) {
            pq.add(new Edge(0, neighbor.vertex, neighbor.weight));
        }

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int destination = currentEdge.destination;

            if (visited[destination]) {
                continue;
            }

            visited[destination] = true;
            mstEdges.add(currentEdge);

            for (Node neighbor : adjList.get(destination)) {
                if (!visited[neighbor.vertex]) {
                    pq.add(new Edge(destination, neighbor.vertex, neighbor.weight));
                }
            }
        }
        return mstEdges;
    }

    // 3. Prim's Algorithm using simple search for minimum edge (Adjacency Matrix)
    //    - Finds the minimum weight edge by iterating through all unvisited vertices.
    //    - Uses an adjacency matrix.
    //    - Time Complexity: O(V^2)
    //    - Space Complexity: O(V^2)
    public static List<Edge> primMST_Simple_AM(int[][] graph, int numVertices) {
        // Check for null or empty graph
        if (graph == null || graph.length == 0 || graph.length != numVertices) {
            return new ArrayList<>();
        }
        int[] parent = new int[numVertices]; // Array to store parent of each vertex in MST
        int[] key = new int[numVertices];    // Array to store the minimum weight edge for each vertex
        boolean[] visited = new boolean[numVertices];
        List<Edge> mstEdges = new ArrayList<>();

        // Initialize key values to infinity and visited array to false
        for (int i = 0; i < numVertices; i++) {
            key[i] = Integer.MAX_VALUE;
            visited[i] = false;
        }

        key[0] = 0;       // Start from the first vertex
        parent[0] = -1;    // Root node has no parent

        for (int count = 0; count < numVertices - 1; count++) {
            // Pick the minimum key vertex from the set of vertices not yet included in MST
            int u = minKey(key, visited, numVertices);
            visited[u] = true;

            // Update key value and parent index of the adjacent vertices of the picked vertex.
            for (int v = 0; v < numVertices; v++) {
                // graph[u][v] is non zero only for adjacent vertices
                // visited[v] is false for vertices not yet included in MST
                // Update the key only if graph[u][v] is smaller than key[v]
                if (graph[u][v] != 0 && !visited[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        // Construct the MST edges from the parent array
        for (int i = 1; i < numVertices; i++) {
            mstEdges.add(new Edge(parent[i], i, graph[i][parent[i]]));
        }
        return mstEdges;
    }

    // Helper function to find the vertex with minimum key value
    private static int minKey(int[] key, boolean[] visited, int numVertices) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    // 4. Prim's Algorithm using simple search for minimum edge (Adjacency List)
    //    -  Finds the minimum weight edge by iterating through all unvisited vertices.
    //    -  Uses an adjacency list.
    //    - Time Complexity: O(V^2)
    //    - Space Complexity: O(V + E)
    public static List<Edge> primMST_Simple_AL(List<List<Node>> adjList, int numVertices) {
        // Check for null or empty graph
        if (adjList == null || adjList.size() != numVertices) {
            return new ArrayList<>();
        }

        int[] parent = new int[numVertices];
        int[] key = new int[numVertices];
        boolean[] visited = new boolean[numVertices];
        List<Edge> mstEdges = new ArrayList<>();

        for (int i = 0; i < numVertices; i++) {
            key[i] = Integer.MAX_VALUE;
            visited[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < numVertices - 1; count++) {
            int u = minKey(key, visited, numVertices);
            visited[u] = true;

            for (Node neighbor : adjList.get(u)) {
                int v = neighbor.vertex;
                int weight = neighbor.weight;
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        for (int i = 1; i < numVertices; i++) {
            int parentVertex = parent[i];
            // Find the edge weight by searching the adjacency list.
            int weight = -1; // Initialize to an invalid value
            for (Node neighbor : adjList.get(i)) {
                if (neighbor.vertex == parentVertex) {
                    weight = neighbor.weight;
                    break;
                }
            }
            if (weight != -1)
                mstEdges.add(new Edge(parent[i], i, weight));
        }
        return mstEdges;
    }

    // 5. Prim's Algorithm using HashSet to track visited (Adjacency List)
    //    - Uses a HashSet to keep track of visited nodes instead of a boolean array.
    //    - Uses a Priority Queue
    //    - Time Complexity: O(E log V)
    //    - Space Complexity: O(V + E)
    public static List<Edge> primMST_HashSet(List<List<Node>> adjList, int numVertices) {
        // Check for null or empty graph
        if (adjList == null || adjList.size() != numVertices) {
            return new ArrayList<>();
        }

        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight));
        Set<Integer> visited = new HashSet<>();
        List<Edge> mstEdges = new ArrayList<>();

        visited.add(0); // Start from vertex 0
        for (Node neighbor : adjList.get(0)) {
            pq.add(new Edge(0, neighbor.vertex, neighbor.weight));
        }

        while (!pq.isEmpty()) {
            Edge currentEdge = pq.poll();
            int destination = currentEdge.destination;

            if (visited.contains(destination)) {
                continue;
            }

            visited.add(destination);
            mstEdges.add(currentEdge);

            for (Node neighbor : adjList.get(destination)) {
                if (!visited.contains(neighbor.vertex)) {
                    pq.add(new Edge(destination, neighbor.vertex, neighbor.weight));
                }
            }
        }
        return mstEdges;
    }



    public static void main(String[] args) {
        // Example Graph represented as an adjacency matrix
        int numVertices = 9;
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

        // Example Graph represented as an adjacency list
        List<List<Node>> adjacencyList = new ArrayList<>();
        for (int i = 0; i < numVertices; i++) {
            adjacencyList.add(new ArrayList<>());
        }
        // Add edges to the adjacency list
        adjacencyList.get(0).add(new Node(1, 4));
        adjacencyList.get(0).add(new Node(7, 8));

        adjacencyList.get(1).add(new Node(0, 4));
        adjacencyList.get(1).add(new Node(2, 8));
        adjacencyList.get(1).add(new Node(7, 11));

        adjacencyList.get(2).add(new Node(1, 8));
        adjacencyList.get(2).add(new Node(3, 7));
        adjacencyList.get(2).add(new Node(5, 4));
        adjacencyList.get(2).add(new Node(8, 2));

        adjacencyList.get(3).add(new Node(2, 7));
        adjacencyList.get(3).add(new Node(4, 9));
        adjacencyList.get(3).add(new Node(5, 14));

        adjacencyList.get(4).add(new Node(3, 9));
        adjacencyList.get(4).add(new Node(5, 10));

        adjacencyList.get(5).add(new Node(2, 4));
        adjacencyList.get(5).add(new Node(3, 14));
        adjacencyList.get(5).add(new Node(4, 10));
        adjacencyList.get(5).add(new Node(6, 2));

        adjacencyList.get(6).add(new Node(5, 2));
        adjacencyList.get(6).add(new Node(7, 1));
        adjacencyList.get(6).add(new Node(8, 6));

        adjacencyList.get(7).add(new Node(0, 8));
        adjacencyList.get(7).add(new Node(1, 11));
        adjacencyList.get(7).add(new Node(6, 1));
        adjacencyList.get(7).add(new Node(8, 7));

        adjacencyList.get(8).add(new Node(2, 2));
        adjacencyList.get(8).add(new Node(6, 6));
        adjacencyList.get(8).add(new Node(7, 7));



        // Example usage of the 5 different approaches:
        System.out.println("Prim's MST using Priority Queue and Adjacency Matrix:");
        List<Edge> mstEdges1 = primMST_PQ_AM(adjacencyMatrix, numVertices);
        printMST(mstEdges1);

        System.out.println("\nPrim's MST using Priority Queue and Adjacency List:");
        List<Edge> mstEdges2 = primMST_PQ_AL(adjacencyList, numVertices);
        printMST(mstEdges2);

        System.out.println("\nPrim's MST using Simple Search and Adjacency Matrix:");
        List<Edge> mstEdges3 = primMST_Simple_AM(adjacencyMatrix, numVertices);
        printMST(mstEdges3);

        System.out.println("\nPrim's MST using Simple Search and Adjacency List:");
        List<Edge> mstEdges4 = primMST_Simple_AL(adjacencyList, numVertices);
        printMST(mstEdges4);

        System.out.println("\nPrim's MST using HashSet and Adjacency List:");
        List<Edge> mstEdges5 = primMST_HashSet(adjacencyList, numVertices);
        printMST(mstEdges5);
    }

    // Helper function to print the MST edges
    private static void printMST(List<Edge> mstEdges) {
        int totalWeight = 0;
        for (Edge edge : mstEdges) {
            System.out.println(edge.source + " - " + edge.destination + " : " + edge.weight);
            totalWeight += edge.weight;
        }
        System.out.println("Total MST Weight: " + totalWeight);
    }
}


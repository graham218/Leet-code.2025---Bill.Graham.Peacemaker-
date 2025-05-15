import java.util.*;

// Class to represent an edge in the graph
class Edge {
    int to;      // Destination vertex
    int weight;    // Weight of the edge

    public Edge(int to, int weight) {
        this.to = to;
        this.weight = weight;
    }
}

// Class to represent a node in the graph, used in Dijkstra's algorithm
class Node implements Comparable<Node> {
    int vertex;    // Vertex identifier
    int distance;  // Distance from the source

    public Node(int vertex, int distance) {
        this.vertex = vertex;
        this.distance = distance;
    }

    @Override
    public int compareTo(Node other) {
        // Compare nodes based on their distances.  Crucial for PriorityQueue ordering.
        return Integer.compare(this.distance, other.distance);
    }
}

// Class to represent the graph
class Graph {
    int vertices;             // Number of vertices in the graph
    List<List<Edge>> adj; // Adjacency list representation of the graph

    public Graph(int vertices) {
        this.vertices = vertices;
        this.adj = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            this.adj.add(new ArrayList<>());
        }
    }

    // Method to add an edge to the graph.  It's a directed graph.
    public void addEdge(int from, int to, int weight) {
        adj.get(from).add(new Edge(to, weight));
    }

    // 1. Dijkstra's Algorithm - Basic Implementation with Priority Queue
    //   - Uses a PriorityQueue to select the node with the smallest distance.
    //   - Computes the shortest distance from a source vertex to all other vertices.
    public int[] dijkstraBasic(int source) {
        int[] dist = new int[vertices];  // Array to store the shortest distances
        Arrays.fill(dist, Integer.MAX_VALUE); // Initialize distances to infinity
        dist[source] = 0;                   // Distance from source to itself is 0

        PriorityQueue<Node> pq = new PriorityQueue<>(); // PriorityQueue to store nodes
        pq.offer(new Node(source, 0));       // Add the source node to the queue

        while (!pq.isEmpty()) {
            Node u = pq.poll();             // Get the node with the smallest distance
            int uVertex = u.vertex;

            // Important:  Relaxation step.  Check for shorter paths.
            for (Edge edge : adj.get(uVertex)) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[uVertex] != Integer.MAX_VALUE && dist[uVertex] + weight < dist[v]) {
                    dist[v] = dist[uVertex] + weight;  // Update the distance
                    pq.offer(new Node(v, dist[v]));    // Add the updated node to the queue
                }
            }
        }
        return dist; // Return the array of shortest distances
    }

    // 2. Dijkstra's Algorithm with Path Reconstruction
    //    - Same as basic, but also stores the predecessor of each node in the shortest path.
    //    - Allows reconstructing the shortest path from the source to any destination.
    public Map<Integer, Integer> dijkstraWithPathReconstruction(int source) {
        int[] dist = new int[vertices];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        int[] prev = new int[vertices]; // Array to store the predecessor of each node
        Arrays.fill(prev, -1);         // Initialize predecessors to -1 (null)

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;

            for (Edge edge : adj.get(uVertex)) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[uVertex] != Integer.MAX_VALUE && dist[uVertex] + weight < dist[v]) {
                    dist[v] = dist[uVertex] + weight;
                    prev[v] = uVertex;             // Store the predecessor
                    pq.offer(new Node(v, dist[v]));
                }
            }
        }
        // Return the predecessors.  The distances are in 'dist' (not returned).
        Map<Integer, Integer> previous = new HashMap<>();
        for (int i = 0; i < prev.length; i++) {
            previous.put(i, prev[i]);
        }
        return previous;
    }

    // Helper method to reconstruct the shortest path from source to dest using the 'prev' array
    public List<Integer> reconstructPath(int source, int dest, Map<Integer, Integer> prev) {
        List<Integer> path = new ArrayList<>();
        int current = dest;

        // Traverse back from the destination to the source using the predecessor information.
        while (current != -1) {
            path.add(current);
            current = prev.get(current);
        }
        Collections.reverse(path); // Reverse the path to get it in the correct order (source to destination)
        if (path.get(0) != source) {
            return new ArrayList<>(); // Return an empty path if no path exists.
        }
        return path;
    }

    // 3. Dijkstra's Algorithm with Early Exit Condition
    //    - Optimizes the basic version by adding a condition to stop the algorithm
    //      when all reachable nodes have been visited.  This can improve performance
    //      in some cases, especially when the graph is not fully connected.
    public int[] dijkstraWithEarlyExit(int source) {
        int[] dist = new int[vertices];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        boolean[] visited = new boolean[vertices]; // Keep track of visited nodes
        int visitedCount = 0;

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;

            if (visited[uVertex]) {
                continue; // Skip if already visited
            }

            visited[uVertex] = true;
            visitedCount++;

            if (visitedCount == vertices) {
                break; //early exit
            }

            for (Edge edge : adj.get(uVertex)) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[uVertex] != Integer.MAX_VALUE && dist[uVertex] + weight < dist[v]) {
                    dist[v] = dist[uVertex] + weight;
                    pq.offer(new Node(v, dist[v]));
                }
            }
        }
        return dist;
    }

    // 4. Dijkstra's Algorithm for a Specific Destination
    //    - Modifies the algorithm to stop once the shortest path to a specific
    //      destination vertex has been found.  Useful when you don't need the
    //      shortest paths to all vertices.
    public int dijkstraToDestination(int source, int destination) {
        int[] dist = new int[vertices];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;

            if (uVertex == destination) {
                return dist[destination]; // Stop when the destination is reached
            }

            for (Edge edge : adj.get(uVertex)) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[uVertex] != Integer.MAX_VALUE && dist[uVertex] + weight < dist[v]) {
                    dist[v] = dist[uVertex] + weight;
                    pq.offer(new Node(v, dist[v]));
                }
            }
        }
        return -1; // Return -1 if no path to the destination is found
    }

    // 5. Dijkstra's Algorithm with Edge Relaxation Count
    //    - Keeps track of how many times each edge is relaxed (i.e., how many times
    //      a shorter path is found through that edge).  This can be useful for
    //      analyzing the graph or detecting potential issues.
    public int[] dijkstraWithEdgeRelaxationCount(int source) {
        int[] dist = new int[vertices];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        int[] edgeRelaxationCount = new int[vertices * vertices]; // Store relaxation counts.  Can be optimized.
        // Initialize all counts to 0.  The index is a flattened 2D index.
        for (int i = 0; i < vertices * vertices; i++) {
            edgeRelaxationCount[i] = 0;
        }

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;

            for (Edge edge : adj.get(uVertex)) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[uVertex] != Integer.MAX_VALUE && dist[uVertex] + weight < dist[v]) {
                    dist[v] = dist[uVertex] + weight;
                    pq.offer(new Node(v, dist[v]));
                    // Increment the relaxation count for the edge (uVertex, v)
                    edgeRelaxationCount[uVertex * vertices + v]++; //  Important:  Flattened index.
                }
            }
        }
        return edgeRelaxationCount; // Returns the edge relaxation counts.  Distances are in 'dist'.
    }
}

// Example usage of the Graph class and Dijkstra's algorithm
public class Main {
    public static void main(String[] args) {
        int vertices = 6; // Number of vertices in the graph
        Graph graph = new Graph(vertices);

        // Add edges to the graph (directed edges with weights)
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 2, 2);
        graph.addEdge(1, 2, 5);
        graph.addEdge(1, 3, 10);
        graph.addEdge(2, 4, 3);
        graph.addEdge(3, 5, 11);
        graph.addEdge(4, 3, 4);
        graph.addEdge(4, 5, 15);

        int source = 0; // Source vertex for Dijkstra's algorithm

        // 1. Basic Dijkstra's
        System.out.println("1. Basic Dijkstra's Algorithm:");
        int[] shortestDistances = graph.dijkstraBasic(source);
        System.out.println("Shortest distances from vertex " + source + ":");
        for (int i = 0; i < vertices; i++) {
            System.out.println("To " + i + ": " + shortestDistances[i]);
        }
        System.out.println();

        // 2. Dijkstra's with Path Reconstruction
        System.out.println("2. Dijkstra's Algorithm with Path Reconstruction:");
        Map<Integer, Integer> prev = graph.dijkstraWithPathReconstruction(source);
        int destination = 5;
        List<Integer> path = graph.reconstructPath(source, destination, prev);
        System.out.println("Shortest path from " + source + " to " + destination + ": " + path);
        System.out.println();

        // 3. Dijkstra's with Early Exit
        System.out.println("3. Dijkstra's Algorithm with Early Exit:");
        int[] shortestDistancesEarlyExit = graph.dijkstraWithEarlyExit(source);
        System.out.println("Shortest distances from vertex " + source + " (Early Exit):");
        for (int i = 0; i < vertices; i++) {
            System.out.println("To " + i + ": " + shortestDistancesEarlyExit[i]);
        }
        System.out.println();

        // 4. Dijkstra's to a Specific Destination
        System.out.println("4. Dijkstra's Algorithm to a Specific Destination:");
        int shortestDistanceToDest = graph.dijkstraToDestination(source, destination);
        System.out.println("Shortest distance from " + source + " to " + destination + ": " + shortestDistanceToDest);
        System.out.println();

        // 5. Dijkstra's with Edge Relaxation Count
        System.out.println("5. Dijkstra's Algorithm with Edge Relaxation Count:");
        int[] edgeRelaxationCount = graph.dijkstraWithEdgeRelaxationCount(source);
        System.out.println("Edge Relaxation Counts:");
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                int count = edgeRelaxationCount[i * vertices + j];
                if (count > 0) {
                    System.out.println("Edge (" + i + " -> " + j + "): " + count + " times");
                }
            }
        }
    }
}

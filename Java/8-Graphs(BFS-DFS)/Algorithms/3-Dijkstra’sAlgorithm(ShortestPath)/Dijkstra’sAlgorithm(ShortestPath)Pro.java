import java.util.*;

// Class to represent an edge in the graph
class Edge {
    int to;     // Destination vertex
    int weight; // Weight of the edge

    public Edge(int to, int weight) {
        this.to = to;
        this.weight = weight;
    }
}

// Class to represent a node in the priority queue for Dijkstra's algorithm
class Node implements Comparable<Node> {
    int vertex;    // Vertex ID
    int distance;  // Distance from the source

    public Node(int vertex, int distance) {
        this.vertex = vertex;
        this.distance = distance;
    }

    @Override
    public int compareTo(Node other) {
        // Compare based on distance, smaller distance has higher priority
        return Integer.compare(this.distance, other.distance);
    }
}

// Class to represent the graph
class Graph {
    int vertices;             // Number of vertices in the graph
    List<List<Edge>> adjList; // Adjacency list to store edges

    public Graph(int vertices) {
        this.vertices = vertices;
        this.adjList = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            this.adjList.add(new ArrayList<>());
        }
    }

    // Method to add an undirected edge to the graph
    public void addEdge(int from, int to, int weight) {
        // Add edge from 'from' to 'to' with the given weight
        adjList.get(from).add(new Edge(to, weight));
        adjList.get(to).add(new Edge(from, weight)); // For undirected graph
    }

    // Method to add a directed edge to the graph
    public void addDirectedEdge(int from, int to, int weight) {
        adjList.get(from).add(new Edge(to, weight));
    }

    // 1. Dijkstra's Algorithm using Priority Queue (Most Common)
    public int[] dijkstraPQ(int source) {
        // 'distances' array to store the shortest distance from source to each vertex
        int[] distances = new int[vertices];
        // Initialize all distances to infinity (Integer.MAX_VALUE), except the source
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;

        // Priority queue to store nodes (vertex, distance) and extract the one with the smallest distance
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0)); // Add the source node with distance 0

        // Main loop: continue as long as there are nodes in the priority queue
        while (!pq.isEmpty()) {
            Node currNode = pq.poll(); // Get the node with the smallest distance
            int currVertex = currNode.vertex;
            int currDistance = currNode.distance;

            // If the current distance is greater than the known shortest distance, skip it.
            if (currDistance > distances[currVertex]) {
                continue;
            }

            // Iterate over all neighbors (edges) of the current vertex
            for (Edge edge : adjList.get(currVertex)) {
                int neighbor = edge.to;       // Get the neighbor vertex
                int weight = edge.weight;   // Get the weight of the edge

                // Calculate the distance to the neighbor through the current vertex
                int newDistance = currDistance + weight;

                // If a shorter path to the neighbor is found, update the distance and add it to the priority queue
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance; // Update the shortest distance
                    pq.offer(new Node(neighbor, newDistance)); // Add the neighbor to the priority queue
                }
            }
        }
        return distances; // Return the array of shortest distances from the source
    }

    // 2. Dijkstra's Algorithm using Array (Less Efficient)
    public int[] dijkstraArray(int source) {
        int[] distances = new int[vertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;
        boolean[] visited = new boolean[vertices]; // Keep track of visited vertices

        for (int count = 0; count < vertices - 1; count++) {
            // Find the vertex with the minimum distance among the unvisited vertices
            int minVertex = -1;
            int minDistance = Integer.MAX_VALUE;
            for (int v = 0; v < vertices; v++) {
                if (!visited[v] && distances[v] <= minDistance) {
                    minDistance = distances[v];
                    minVertex = v;
                }
            }

            // If no unvisited vertex with finite distance is found, exit the loop
            if (minVertex == -1) break;

            visited[minVertex] = true; // Mark the current vertex as visited

            // Update distances of the neighbors of the current vertex
            for (Edge edge : adjList.get(minVertex)) {
                int neighbor = edge.to;
                int weight = edge.weight;
                if (!visited[neighbor] && distances[minVertex] != Integer.MAX_VALUE &&
                        distances[minVertex] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[minVertex] + weight;
                }
            }
        }
        return distances;
    }

    // 3. Dijkstra's Algorithm with Path Reconstruction
    public Map<Integer, Integer> dijkstraWithPath(int source) {
        int[] distances = new int[vertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        // 'previous' map to store the predecessor of each vertex in the shortest path
        Map<Integer, Integer> previous = new HashMap<>();
        previous.put(source, null); // Source has no predecessor

        while (!pq.isEmpty()) {
            Node currNode = pq.poll();
            int currVertex = currNode.vertex;
            int currDistance = currNode.distance;

            if (currDistance > distances[currVertex]) {
                continue;
            }

            for (Edge edge : adjList.get(currVertex)) {
                int neighbor = edge.to;
                int weight = edge.weight;
                int newDistance = currDistance + weight;
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.offer(new Node(neighbor, newDistance));
                    previous.put(neighbor, currVertex); // Store the predecessor
                }
            }
        }
        return previous; // Return the map of predecessors
    }

    // Method to reconstruct the shortest path from source to destination using the 'previous' map
    public List<Integer> getShortestPath(int source, int destination, Map<Integer, Integer> previous) {
        List<Integer> path = new ArrayList<>();
        Integer current = destination;

        // Traverse back from the destination to the source using the 'previous' map
        while (current != null) {
            path.add(current);
            current = previous.get(current);
        }
        Collections.reverse(path); // Reverse the path to get it from source to destination
        return path;
    }

    // 4. Dijkstra's Algorithm for Directed Graphs
    public int[] dijkstraDirected(int source) {
        int[] distances = new int[vertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));

        while (!pq.isEmpty()) {
            Node currNode = pq.poll();
            int currVertex = currNode.vertex;
            int currDistance = currNode.distance;

            if (currDistance > distances[currVertex]) {
                continue;
            }

            for (Edge edge : adjList.get(currVertex)) {
                int neighbor = edge.to;
                int weight = edge.weight;
                int newDistance = currDistance + weight;
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.offer(new Node(neighbor, newDistance));
                }
            }
        }
        return distances;
    }

    // 5. Dijkstra's Algorithm with Negative Edge Weight Detection
    public int[] dijkstraNegativeEdges(int source) {
        int[] distances = new int[vertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(source, 0));
        int[] edgeCount = new int[vertices]; // To track number of times each vertex is relaxed

        while (!pq.isEmpty()) {
            Node currNode = pq.poll();
            int currVertex = currNode.vertex;
            int currDistance = currNode.distance;

            if (currDistance > distances[currVertex]) {
                continue;
            }

            for (Edge edge : adjList.get(currVertex)) {
                int neighbor = edge.to;
                int weight = edge.weight;
                int newDistance = currDistance + weight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.offer(new Node(neighbor, newDistance));
                    edgeCount[neighbor]++;
                    if (edgeCount[neighbor] >= vertices) {
                        throw new RuntimeException("Negative cycle detected. Dijkstra's algorithm cannot handle negative cycles.");
                    }
                }
            }
        }
        return distances;
    }
}

// Main class to run the Dijkstra's algorithm
public class Main {
    public static void main(String[] args) {
        // Create a graph with 6 vertices (0 to 5)
        Graph graph = new Graph(6);

        // Add edges to the graph (undirected edges in this example)
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 2, 2);
        graph.addEdge(1, 2, 1);
        graph.addEdge(1, 3, 5);
        graph.addEdge(2, 3, 8);
        graph.addEdge(2, 4, 10);
        graph.addEdge(3, 4, 2);
        graph.addEdge(3, 5, 6);
        graph.addEdge(4, 5, 3);

        // Define the source vertex
        int source = 0;

        // 1. Dijkstra's Algorithm using Priority Queue
        System.out.println("Dijkstra's Algorithm using Priority Queue:");
        int[] distancesPQ = graph.dijkstraPQ(source);
        printDistances(distancesPQ, source);

        // 2. Dijkstra's Algorithm using Array
        System.out.println("\nDijkstra's Algorithm using Array:");
        int[] distancesArray = graph.dijkstraArray(source);
        printDistances(distancesArray, source);

        // 3. Dijkstra's Algorithm with Path Reconstruction
        System.out.println("\nDijkstra's Algorithm with Path Reconstruction:");
        Map<Integer, Integer> previous = graph.dijkstraWithPath(source);
        int destination = 5; // Example destination
        List<Integer> shortestPath = graph.getShortestPath(source, destination, previous);
        System.out.println("Shortest path from " + source + " to " + destination + ": " + shortestPath);

        // 4. Dijkstra's Algorithm for Directed Graphs
        System.out.println("\nDijkstra's Algorithm for Directed Graph:");
        Graph directedGraph = new Graph(6);
        directedGraph.addDirectedEdge(0, 1, 4);
        directedGraph.addDirectedEdge(0, 2, 2);
        directedGraph.addDirectedEdge(1, 2, 1);
        directedGraph.addDirectedEdge(1, 3, 5);
        directedGraph.addDirectedEdge(2, 3, 8);
        directedGraph.addDirectedEdge(2, 4, 10);
        directedGraph.addDirectedEdge(3, 4, 2);
        directedGraph.addDirectedEdge(3, 5, 6);
        directedGraph.addDirectedEdge(4, 5, 3);
        int[] distancesDirected = directedGraph.dijkstraDirected(source);
        printDistances(distancesDirected, source);

        // 5. Dijkstra's Algorithm with Negative Edge Weight Detection
        System.out.println("\nDijkstra's Algorithm with Negative Edge Weight Detection:");
        Graph negativeGraph = new Graph(6);
        negativeGraph.addEdge(0, 1, 4);
        negativeGraph.addEdge(0, 2, 2);
        negativeGraph.addEdge(1, 2, 1);
        negativeGraph.addEdge(1, 3, 5);
        negativeGraph.addEdge(2, 3, 8);
        negativeGraph.addEdge(2, 4, 10);
        negativeGraph.addEdge(3, 4, 2);
        negativeGraph.addEdge(3, 5, 6);
        negativeGraph.addEdge(4, 5, 3);
        // Add a negative edge to demonstrate the detection
        negativeGraph.addEdge(4, 1, -5); // Adding a negative edge

        try {
            int[] distancesNegative = negativeGraph.dijkstraNegativeEdges(source);
            printDistances(distancesNegative, source);
        } catch (RuntimeException e) {
            System.out.println("Error: " + e.getMessage()); // Output the error message
        }
    }

    // Method to print the distances array
    private static void printDistances(int[] distances, int source) {
        System.out.println("Shortest distances from source vertex " + source + ":");
        for (int i = 0; i < distances.length; i++) {
            System.out.println("Vertex " + i + ": " + distances[i]);
        }
    }
}

/*
Explanation of the Code:

1.  Classes:
    * `Edge`: Represents an edge in the graph with a destination vertex and weight.
    * `Node`: Represents a node in the priority queue, storing the vertex and its distance from the source.  Implements `Comparable` to allow sorting in the priority queue based on distance.
    * `Graph`: Represents the graph using an adjacency list.  It provides methods to add edges (both undirected and directed) and implementations of Dijkstra's algorithm.

2.  Dijkstra's Algorithm Implementations:
    * `dijkstraPQ(int source)`:  The most common and efficient implementation.  It uses a priority queue (`PriorityQueue`) to always select the vertex with the smallest known distance from the source.
        * Initialization:
            * `distances` array: Stores the shortest distance from the source to each vertex. Initialized to infinity (`Integer.MAX_VALUE`) for all vertices except the source, which is initialized to 0.
            * `pq`:  A priority queue to store vertices and their distances.  The source vertex with distance 0 is added initially.
        * Main Loop:
            * The loop continues as long as the priority queue is not empty.
            * In each iteration, the vertex with the smallest distance is extracted from the priority queue (`pq.poll()`).
            * If the extracted distance is greater than the current shortest distance to that vertex (meaning a shorter path has already been found), the vertex is skipped.
            * For each neighbor of the current vertex, the algorithm calculates the distance from the source to the neighbor through the current vertex.
            * If this new distance is shorter than the previously known shortest distance to the neighbor, the `distances` array is updated, and the neighbor is added to the priority queue.
        * Return Value: The `distances` array, where `distances[i]` represents the shortest distance from the source to vertex `i`.
    * `dijkstraArray(int source)`: A less efficient implementation that uses a simple array to find the vertex with the minimum distance.
        * It does not use a priority queue, resulting in a time complexity of O(V^2), where V is the number of vertices.
        * It iterates through all unvisited vertices to find the one with the smallest distance.
    * `dijkstraWithPath(int source)`:  An extension of Dijkstra's algorithm that also reconstructs the shortest path from the source to all other reachable vertices.
        * It uses a `previous` map to store, for each vertex, the vertex that precedes it in the shortest path from the source.
        * The `getShortestPath(int source, int destination, Map<Integer, Integer> previous)` method uses this `previous` map to build the path by traversing backward from the destination to the source.
    * `dijkstraDirected(int source)`:  Specifically designed to work with directed graphs.
        * The key difference is in how edges are added to the graph.  The `addDirectedEdge` method ensures that edges are added only in one direction.
        * The rest of the algorithm is the same as the standard Dijkstra's algorithm.
    * `dijkstraNegativeEdges(int source)`:  An implementation that detects negative-weight cycles in the graph.
        * Dijkstra's algorithm does not work correctly with negative-weight cycles because it assumes that once a vertex is visited, its shortest path is finalized.  In a graph with a negative cycle, it's possible to keep finding shorter paths by going around the cycle.
        * This implementation adds an `edgeCount` array to keep track of how many times the distance to each vertex has been updated (relaxed).  If a vertex's distance is updated more than V-1 times (where V is the number of vertices), it indicates the presence of a negative cycle.
        * If a negative cycle is detected, the algorithm throws a `RuntimeException`.

3.  `Main` Class:
    * Creates a `Graph` object and adds edges to it.
    * Calls the different Dijkstra's algorithm implementations on the graph, starting from a specified source vertex (0 in this case).
    * Prints the shortest distances from the source to all other vertices.
    * Demonstrates how to use the `dijkstraWithPath` method to find the shortest path between two specific vertices.
    * Includes an example of a directed graph.
    * Includes an example of a graph with a negative edge, demonstrating how the `dijkstraNegativeEdges` method detects the negative cycle.

4.  `printDistances(int[] distances, int source)` Method:
    * A helper method to print the contents of the `distances` array in a user-friendly format.

Key Concepts:

* Graph: A data structure consisting of vertices (nodes) and edges that connect them.
* Weighted Graph: A graph where each edge has a weight associated with it, representing the cost of traversing that edge.
* Shortest Path: The path between two vertices in a graph with the minimum total weight.
* Dijkstra's Algorithm: A greedy algorithm that finds the shortest path from a source vertex to all other vertices in a weighted graph.
* Priority Queue: A data structure that allows efficient retrieval of the element with the highest (or lowest) priority.  In Dijkstra's algorithm, it is used to efficiently select the vertex with the smallest distance.
* Adjacency List: A representation of a graph where each vertex has a list of its neighboring vertices and the weights of the edges connecting them.
* Negative-Weight Cycle: A cycle in a graph where the sum of the edge weights is negative.  Dijkstra's algorithm does not work correctly in graphs with negative-weight cycles.

Real-World Applications:

1.  GPS Navigation Systems:
    * Dijkstra's algorithm is used to find the shortest routes between locations.
    * The graph represents the road network, vertices represent intersections, and edge weights represent road lengths or travel times.
    * The algorithm calculates the fastest path based on real-time traffic conditions.

2.  Network Routing:
    * In computer networks, Dijkstra's algorithm is used to find the best path for data packets to travel from a source to a destination.
    * The graph represents the network topology, vertices represent routers, and edge weights represent link costs or latency.
    * Routing protocols like OSPF (Open Shortest Path First) use Dijkstra's algorithm.

3.  Airline Route Planning:
    * Airlines use Dijkstra's algorithm to determine the most cost-effective flight routes.
    * The graph represents the network of airports, vertices represent airports, and edge weights represent fuel costs, flight times, or other factors.

4.  Logistics and Supply Chain Management:
    * Dijkstra's algorithm is used to optimize delivery routes and minimize transportation costs.
    * The graph represents the network of warehouses, distribution centers, and customer locations, and edge weights represent distances, travel times, or shipping costs.

5.  Social Networking:
    * Dijkstra's algorithm can be used to find the shortest path between users in a social network.  This can be used to suggest connections or find how people are related.
    * The graph represents the network of users, vertices represent users, and edges represent connections between them.
*/

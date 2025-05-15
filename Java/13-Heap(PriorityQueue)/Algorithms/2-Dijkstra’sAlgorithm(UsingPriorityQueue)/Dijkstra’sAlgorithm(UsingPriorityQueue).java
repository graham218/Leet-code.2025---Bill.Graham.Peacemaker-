import java.util.*;

public class DijkstraAlgorithms {

    // Inner class to represent an edge in the graph
    static class Edge {
        int to;      // Destination vertex of the edge
        int weight;    // Weight/cost of the edge

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    // Inner class to represent a node with its distance, used in Dijkstra's algorithm
    static class Node implements Comparable<Node> {
        int vertex;    // The vertex represented by this node
        int distance;  // The distance from the source to this vertex

        public Node(int vertex, int distance) {
            this.vertex = vertex;
            this.distance = distance;
        }

        // Overriding compareTo method to make Node comparable based on distance
        @Override
        public int compareTo(Node other) {
            return Integer.compare(this.distance, other.distance);
        }
    }

    // Method to implement Dijkstra's algorithm using a Priority Queue
    // This is the most common and efficient approach
    public static int[] dijkstraPQ(List<List<Edge>> graph, int start) {
        int numVertices = graph.size();
        int[] distances = new int[numVertices];  // Array to store shortest distances from start
        Arrays.fill(distances, Integer.MAX_VALUE); // Initialize all distances to infinity
        distances[start] = 0;                   // Distance from start to itself is 0

        PriorityQueue<Node> pq = new PriorityQueue<>(); // Priority Queue to store nodes to visit
        pq.offer(new Node(start, 0));             // Add the starting node to the queue

        while (!pq.isEmpty()) {
            Node current = pq.poll();          // Get the node with the smallest distance
            int u = current.vertex;
            int distU = current.distance;

            if (distU > distances[u]) {       // Important: Skip if a shorter path to u is already found
                continue;
            }

            // Iterate over all neighbors of vertex u
            for (Edge edge : graph.get(u)) {
                int v = edge.to;              // Neighbor vertex
                int weightUV = edge.weight;    // Weight of the edge from u to v

                // Relax the edge: if a shorter path to v is found through u
                if (distances[u] + weightUV < distances[v]) {
                    distances[v] = distances[u] + weightUV; // Update the distance to v
                    pq.offer(new Node(v, distances[v]));     // Add v to the priority queue
                }
            }
        }
        return distances; // Return the array of shortest distances from start to all vertices
    }


    // Dijkstra's algorithm using Priority Queue with a Set for visited nodes
    public static int[] dijkstraPQVisitedSet(List<List<Edge>> graph, int start) {
        int numVertices = graph.size();
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        Set<Integer> visited = new HashSet<>(); // Keep track of visited nodes
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            int distU = current.distance;

            if (visited.contains(u)) { // If node already visited, continue
                continue;
            }
            visited.add(u); // Mark the current node as visited.

            for (Edge edge : graph.get(u)) {
                int v = edge.to;
                int weightUV = edge.weight;
                if (distances[u] + weightUV < distances[v]) {
                    distances[v] = distances[u] + weightUV;
                    pq.offer(new Node(v, distances[v]));
                }
            }
        }
        return distances;
    }

    // Dijkstra's algorithm using a Priority Queue and eager update.
    public static int[] dijkstraPQEager(List<List<Edge>> graph, int start) {
        int numVertices = graph.size();
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            int distU = current.distance;

            if (distU > distances[u]) {
                continue;
            }

            for (Edge edge : graph.get(u)) {
                int v = edge.to;
                int weightUV = edge.weight;
                if (distances[u] + weightUV < distances[v]) {
                    distances[v] = distances[u] + weightUV;
                    pq.offer(new Node(v, distances[v])); // Offer, even if already in queue.
                }
            }
        }
        return distances;
    }

    // Dijkstra's algorithm using Priority Queue with decreaseKey operation (simulated)
    //  This approach attempts to optimize by removing and re-inserting, but PriorityQueue in Java
    //  doesn't have a decreaseKey operation, so it's less efficient than standard Dijkstra with PQ.
    public static int[] dijkstraPQDecreaseKey(List<List<Edge>> graph, int start) {
        int numVertices = graph.size();
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>();
        Map<Integer, Integer> nodeToIndexMap = new HashMap<>(); // Map vertex to its index in PQ (simulated)
        pq.offer(new Node(start, 0));
        nodeToIndexMap.put(start, 0);

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            int distU = current.distance;
            nodeToIndexMap.remove(u); // Remove from "index map"

            if (distU > distances[u]) {
                continue;
            }

            for (Edge edge : graph.get(u)) {
                int v = edge.to;
                int weightUV = edge.weight;
                if (distances[u] + weightUV < distances[v]) {
                    distances[v] = distances[u] + weightUV;
                    //  Simulate decreaseKey: Remove and re-insert.  This is inefficient in Java's PQ.
                    pq.remove(new Node(v, Integer.MAX_VALUE)); // Remove the old node.
                    pq.offer(new Node(v, distances[v]));       // Add the updated node.

                }
            }
        }
        return distances;
    }

    // Dijkstra's algorithm using Priority Queue with path reconstruction
    public static int[] dijkstraPQPath(List<List<Edge>> graph, int start, int end, List<Integer> path) {
        int numVertices = graph.size();
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;
        int[] previous = new int[numVertices]; // Array to store the previous node in the shortest path
        Arrays.fill(previous, -1);

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            int distU = current.distance;

            if (distU > distances[u]) {
                continue;
            }

            if (u == end) break; // Optimization: Stop if we reach the end node

            for (Edge edge : graph.get(u)) {
                int v = edge.to;
                int weightUV = edge.weight;
                if (distances[u] + weightUV < distances[v]) {
                    distances[v] = distances[u] + weightUV;
                    previous[v] = u; // Store the previous node
                    pq.offer(new Node(v, distances[v]));
                }
            }
        }

        // Reconstruct the path from end to start
        if (distances[end] != Integer.MAX_VALUE) {
            int current = end;
            while (current != -1) {
                path.add(0, current); // Add to the beginning of the list
                current = previous[current];
            }
        }
        return distances;
    }


    public static void main(String[] args) {
        int numVertices = 6;
        List<List<Edge>> graph = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; i++) {
            graph.add(new ArrayList<>());
        }

        // Adding edges to the graph (example graph)
        graph.get(0).add(new Edge(1, 4));
        graph.get(0).add(new Edge(2, 2));
        graph.get(1).add(new Edge(2, 5));
        graph.get(1).add(new Edge(3, 10));
        graph.get(2).add(new Edge(4, 3));
        graph.get(3).add(new Edge(5, 11));
        graph.get(4).add(new Edge(3, 4));
        graph.get(4).add(new Edge(5, 15));
        graph.get(5).add(new Edge(5, 0)); //added reflexive edge

        int startVertex = 0;
        int endVertex = 5; // For the path reconstruction example

        // Example usage of the dijkstraPQ function
        System.out.println("Dijkstra's Algorithm with Priority Queue:");
        int[] shortestDistancesPQ = dijkstraPQ(graph, startVertex);
        System.out.println("Shortest distances from vertex " + startVertex + ": " + Arrays.toString(shortestDistancesPQ));

        System.out.println("\nDijkstra's Algorithm with Visited Set:");
        int[] shortestDistancesPQVisitedSet = dijkstraPQVisitedSet(graph, startVertex);
        System.out.println("Shortest distances from vertex " + startVertex + ": " + Arrays.toString(shortestDistancesPQVisitedSet));

        System.out.println("\nDijkstra's Algorithm with Eager Update:");
        int[] shortestDistancesPQEager = dijkstraPQEager(graph, startVertex);
        System.out.println("Shortest distances from vertex " + startVertex + ": " + Arrays.toString(shortestDistancesPQEager));

        System.out.println("\nDijkstra's Algorithm with Decrease Key (Simulated):");
        int[] shortestDistancesPQDecreaseKey = dijkstraPQDecreaseKey(graph, startVertex);
        System.out.println("Shortest distances from vertex " + startVertex + ": " + Arrays.toString(shortestDistancesPQDecreaseKey));

        System.out.println("\nDijkstra's Algorithm with Path Reconstruction:");
        List<Integer> path = new ArrayList<>();
        int[] distancesWithPath = dijkstraPQPath(graph, startVertex, endVertex, path);
        System.out.println("Shortest distances from vertex " + startVertex + " to " + endVertex + ": " + distancesWithPath[endVertex]);
        System.out.println("Shortest path from " + startVertex + " to " + endVertex + ": " + path);
        System.out.println("All Shortest Distances: " + Arrays.toString(distancesWithPath));
    }
}


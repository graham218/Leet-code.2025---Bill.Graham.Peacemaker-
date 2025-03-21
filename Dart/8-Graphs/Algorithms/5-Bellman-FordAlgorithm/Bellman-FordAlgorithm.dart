// Bellman-Ford Algorithm Implementations in Dart
// This code includes five different approaches with real-world applications

import 'dart:math';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> edges; // List of edges, each edge represented as [src, dest, weight]

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    edges = []; // Initialize the list of edges as empty
  }

  // Method to add a directed edge to the graph
  void addEdge(int src, int dest, int weight) {
    edges.add([src, dest, weight]); // Add the edge to the list of edges
  }

  // 1. Standard Bellman-Ford Algorithm (Single-Source Shortest Paths)
  void bellmanFordStandard(int start) {
    // Initialize distances to infinity for all vertices except the start vertex
    List<int> dist = List.filled(vertices, 1 << 30); // 1 << 30 represents a large number (infinity)
    dist[start] = 0; // Set the distance of the start vertex to 0

    // Relax edges repeatedly (vertices - 1 times)
    for (int i = 0; i < vertices - 1; i++) {
      // Iterate through all edges
      for (var edge in edges) {
        int u = edge[0], v = edge[1], weight = edge[2]; // Source, destination, and weight of the edge

        // If a shorter path to v is found, update the distance
        if (dist[u] != 1 << 30 && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
        }
      }
    }

    // Check for negative weight cycles (optional)
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2];
      if (dist[u] != 1 << 30 && dist[u] + weight < dist[v]) {
        print("Graph contains negative weight cycle");
        return; // Exit if a negative weight cycle is detected
      }
    }

    print("Shortest distances from node $start: $dist");
  }

  // 2. Bellman-Ford with Path Reconstruction
  List<int> bellmanFordPath(int start, int end) {
    // Initialize distances to infinity and previous vertices to -1
    List<int> dist = List.filled(vertices, 1 << 30);
    List<int> prev = List.filled(vertices, -1); // Store the previous vertex in the shortest path
    dist[start] = 0; // Set the distance of the start vertex to 0

    // Relax edges repeatedly (vertices - 1 times)
    for (int i = 0; i < vertices - 1; i++) {
      // Iterate through all edges
      for (var edge in edges) {
        int u = edge[0], v = edge[1], weight = edge[2]; // Source, destination, and weight of the edge

        // If a shorter path to v is found, update the distance and previous vertex
        if (dist[u] != 1 << 30 && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          prev[v] = u; // Store the previous vertex
        }
      }
    }

    // Check for negative weight cycles (optional)
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2];
      if (dist[u] != 1 << 30 && dist[u] + weight < dist[v]) {
        print("Graph contains negative weight cycle");
        return []; // Return empty list to indicate an error
      }
    }

    // Reconstruct the shortest path from end to start
    List<int> path = [];
    for (int at = end; at != -1; at = prev[at]) {
      path.insert(0, at); // Insert the vertex at the beginning of the path
    }
    return path; // Return the shortest path
  }

  // 3. Bellman-Ford for Network Routing Optimization
  void bellmanFordNetwork(int start) {
    print("Optimizing network routes from node $start:");
    bellmanFordStandard(start); // Use the standard Bellman-Ford algorithm
  }

  // 4. Bellman-Ford for Currency Arbitrage Detection
  void bellmanFordCurrencyArbitrage(int start) {
    print("Detecting arbitrage opportunities from currency node $start:");
    bellmanFordStandard(start); // Use the standard Bellman-Ford algorithm
  }

  // 5. Bellman-Ford for GPS Navigation Systems
  List<int> bellmanFordGPS(int start, int end) {
    print("Finding optimal GPS route from $start to $end:");
    return bellmanFordPath(start, end); // Use Bellman-Ford with path reconstruction
  }
}

void main() {
  Graph graph = Graph(6); // Create a graph with 6 vertices
  graph.addEdge(0, 1, 4); // Add edges to the graph
  graph.addEdge(0, 2, 2);
  graph.addEdge(1, 2, 5);
  graph.addEdge(1, 3, 10);
  graph.addEdge(2, 4, 3);
  graph.addEdge(4, 3, 4);
  graph.addEdge(3, 5, 11);

  print("\nStandard Bellman-Ford:");
  graph.bellmanFordStandard(0); // Run standard Bellman-Ford algorithm from vertex 0

  print("\nShortest Path (0 to 5):");
  print(graph.bellmanFordPath(0, 5)); // Find the shortest path from vertex 0 to 5

  print("\nNetwork Routing Optimization:");
  graph.bellmanFordNetwork(0); // Simulate network routing optimization from vertex 0

  print("\nCurrency Arbitrage Detection:");
  graph.bellmanFordCurrencyArbitrage(0); // Simulate currency arbitrage detection from vertex 0

  print("\nGPS Navigation System (0 to 5):");
  print(graph.bellmanFordGPS(0, 5)); // Simulate GPS navigation from vertex 0 to 5
}
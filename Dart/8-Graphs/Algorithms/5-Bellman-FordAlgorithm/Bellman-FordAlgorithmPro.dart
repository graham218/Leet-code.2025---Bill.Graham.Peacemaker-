// Advanced Bellman-Ford Algorithm Implementations in Dart
// This code includes six different approaches with real-world applications

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
        if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
        }
      }
    }

    // Check for negative weight cycles (optional)
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2];
      if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
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
        if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          prev[v] = u; // Store the previous vertex
        }
      }
    }

    // Check for negative weight cycles (optional)
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2];
      if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
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

  // 3. Detecting Negative Cycles
  bool hasNegativeCycle() {
    // Initialize distances to infinity for all vertices
    List<int> dist = List.filled(vertices, 1 << 30);
    dist[0] = 0; // Start from vertex 0 (arbitrary start)

    // Relax edges repeatedly (vertices - 1 times)
    for (int i = 0; i < vertices - 1; i++) {
      // Iterate through all edges
      for (var edge in edges) {
        int u = edge[0], v = edge[1], weight = edge[2]; // Source, destination, and weight of the edge

        // If a shorter path to v is found, update the distance
        if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
        }
      }
    }

    // Check for negative weight cycles (one more iteration)
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2]; // Source, destination, and weight of the edge

      // If a shorter path is found in this iteration, it indicates a negative weight cycle
      if (dist[u] != (1 << 30) && dist[u] + weight < dist[v]) {
        return true; // Negative weight cycle detected
      }
    }
    return false; // No negative weight cycle detected
  }

  // 4. Bellman-Ford for Network Routing Optimization
  void bellmanFordNetworkOptimization(int start) {
    print("Optimizing network routes from router $start:");
    bellmanFordStandard(start); // Use the standard Bellman-Ford algorithm
  }

  // 5. Bellman-Ford for GPS Navigation
  void bellmanFordGPS(int start, int end) {
    print("Finding shortest GPS route from $start to $end:");
    print(bellmanFordPath(start, end)); // Use Bellman-Ford with path reconstruction
  }

  // 6. Bellman-Ford for Financial Risk Analysis
  void bellmanFordRiskAnalysis(int start) {
    print("Analyzing financial risk paths from entity $start:");
    bellmanFordStandard(start); // Use the standard Bellman-Ford algorithm
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

  print("\nChecking for Negative Cycles:");
  print(graph.hasNegativeCycle() ? "Graph contains a negative cycle" : "No negative cycles detected");

  print("\nNetwork Routing Optimization:");
  graph.bellmanFordNetworkOptimization(0); // Simulate network routing optimization from vertex 0

  print("\nGPS Navigation (0 to 5):");
  graph.bellmanFordGPS(0, 5); // Simulate GPS navigation from vertex 0 to 5

  print("\nFinancial Risk Analysis:");
  graph.bellmanFordRiskAnalysis(0); // Simulate financial risk analysis from vertex 0
}
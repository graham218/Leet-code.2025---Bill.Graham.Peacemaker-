// Floyd-Warshall Algorithm Implementations in Dart
// This code includes five different approaches with real-world applications

import 'dart:math';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> dist; // Distance matrix representing shortest paths

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    // Initialize the distance matrix with infinity (1 << 30) for all pairs of vertices
    dist = List.generate(vertices, (_) => List.filled(vertices, 1 << 30));
    // Set the distance from each vertex to itself to 0
    for (int i = 0; i < vertices; i++) {
      dist[i][i] = 0;
    }
  }

  // Method to add a directed edge to the graph
  void addEdge(int src, int dest, int weight) {
    // Set the distance from src to dest to the given weight
    dist[src][dest] = weight;
  }

  // 1. Standard Floyd-Warshall Algorithm
  void floydWarshallStandard() {
    // Create a copy of the distance matrix to store the result
    List<List<int>> result = List.generate(vertices, (i) => List.from(dist[i]));

    // Iterate through all vertices as intermediate nodes
    for (int k = 0; k < vertices; k++) {
      // Iterate through all vertices as source nodes
      for (int i = 0; i < vertices; i++) {
        // Iterate through all vertices as destination nodes
        for (int j = 0; j < vertices; j++) {
          // Update the shortest distance if a shorter path is found
          result[i][j] = min(result[i][j], result[i][k] + result[k][j]);
        }
      }
    }
    print("Shortest distances matrix:");
    printMatrix(result); // Print the resulting shortest distances matrix
  }

  // 2. Floyd-Warshall with Path Reconstruction
  void floydWarshallPathReconstruction() {
    // Create a copy of the distance matrix to store the result
    List<List<int>> result = List.generate(vertices, (i) => List.from(dist[i]));
    // Initialize a matrix to store the next vertex in the shortest path
    List<List<int?>> next = List.generate(vertices, (_) => List.filled(vertices, null));

    // Initialize the next matrix with direct edges
    for (int i = 0; i < vertices; i++) {
      for (int j = 0; j < vertices; j++) {
        // If there is a direct edge, set next[i][j] to j
        if (dist[i][j] != 1 << 30) {
          next[i][j] = j;
        }
      }
    }

    // Iterate through all vertices as intermediate nodes
    for (int k = 0; k < vertices; k++) {
      // Iterate through all vertices as source nodes
      for (int i = 0; i < vertices; i++) {
        // Iterate through all vertices as destination nodes
        for (int j = 0; j < vertices; j++) {
          // If a shorter path is found, update the distance and next matrix
          if (result[i][j] > result[i][k] + result[k][j]) {
            result[i][j] = result[i][k] + result[k][j];
            next[i][j] = next[i][k]; // Update next[i][j] to the next vertex in the new shortest path
          }
        }
      }
    }
    print("Path reconstruction matrix:");
    printMatrix(next); // Print the path reconstruction matrix
  }

  // 3. Floyd-Warshall for Traffic Flow Optimization
  void floydWarshallTrafficOptimization() {
    print("Optimizing traffic flow between city nodes:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // 4. Floyd-Warshall for Network Routing
  void floydWarshallNetworkRouting() {
    print("Optimizing network packet routing:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // 5. Floyd-Warshall for Flight Route Optimization
  void floydWarshallFlightRoutes() {
    print("Optimizing flight routes between airports:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // Helper function to print a matrix
  void printMatrix(List<List<dynamic>> matrix) {
    for (var row in matrix) {
      // Replace infinity with "INF" for better readability
      print(row.map((e) => e == 1 << 30 ? "INF" : e).join(" "));
    }
  }
}

void main() {
  Graph graph = Graph(4); // Create a graph with 4 vertices
  graph.addEdge(0, 1, 3); // Add edges to the graph
  graph.addEdge(0, 2, 7);
  graph.addEdge(1, 2, 1);
  graph.addEdge(1, 3, 5);
  graph.addEdge(2, 3, 2);

  print("\nStandard Floyd-Warshall:");
  graph.floydWarshallStandard(); // Run standard Floyd-Warshall algorithm

  print("\nPath Reconstruction:");
  graph.floydWarshallPathReconstruction(); // Run Floyd-Warshall with path reconstruction

  print("\nTraffic Flow Optimization:");
  graph.floydWarshallTrafficOptimization(); // Simulate traffic flow optimization

  print("\nNetwork Routing:");
  graph.floydWarshallNetworkRouting(); // Simulate network routing

  print("\nFlight Route Optimization:");
  graph.floydWarshallFlightRoutes(); // Simulate flight route optimization
}
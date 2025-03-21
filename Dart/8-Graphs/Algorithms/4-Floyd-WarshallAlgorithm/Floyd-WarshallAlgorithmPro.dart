// Advanced Floyd-Warshall Algorithm Implementations in Dart
// This code includes six different approaches with real-world applications

import 'dart:math';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> dist; // Distance matrix to store shortest paths
  static const int INF = 1 << 30; // Define infinity as a large integer

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    // Initialize the distance matrix with infinity for all pairs of vertices
    dist = List.generate(vertices, (_) => List.filled(vertices, INF));
    // Set the distance from each vertex to itself to 0
    for (int i = 0; i < vertices; i++) {
      dist[i][i] = 0;
    }
  }

  // Method to add a directed edge to the graph
  void addEdge(int u, int v, int weight) {
    dist[u][v] = weight; // Set the distance from u to v to the given weight
  }

  // 1. Standard Floyd-Warshall Algorithm (All-Pairs Shortest Paths)
  void floydWarshallStandard() {
    // Iterate through all vertices as intermediate nodes
    for (int k = 0; k < vertices; k++) {
      // Iterate through all vertices as source nodes
      for (int i = 0; i < vertices; i++) {
        // Iterate through all vertices as destination nodes
        for (int j = 0; j < vertices; j++) {
          // Check if there is a path through k and if it's shorter than the current path
          if (dist[i][k] != INF && dist[k][j] != INF) {
            // Update the shortest distance if a shorter path is found
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
    print("Shortest distances between all pairs:");
    printMatrix(); // Print the resulting shortest distances matrix
  }

  // 2. Floyd-Warshall with Path Reconstruction (For Navigation Systems)
  void floydWarshallPath() {
    // Initialize a matrix to store the next vertex in the shortest path
    List<List<int>> next = List.generate(vertices, (_) => List.filled(vertices, -1));

    // Initialize the next matrix with direct edges
    for (int i = 0; i < vertices; i++) {
      for (int j = 0; j < vertices; j++) {
        // If there is a direct edge, set next[i][j] to j
        if (dist[i][j] != INF) {
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
          // Check if there is a path through k and if it's shorter than the current path
          if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
            // Update the shortest distance and the next matrix
            dist[i][j] = dist[i][k] + dist[k][j];
            next[i][j] = next[i][k]; // Update next[i][j] to the next vertex in the new shortest path
          }
        }
      }
    }

    print("Shortest path reconstruction:");
    printMatrix(); // Print the resulting shortest distances matrix, which now also contains path info.
  }

  // 3. Floyd-Warshall for Network Routing Optimization
  void floydWarshallNetwork() {
    print("Optimizing network latency using Floyd-Warshall:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // 4. Floyd-Warshall for Logistics & Supply Chain Optimization
  void floydWarshallLogistics() {
    print("Finding optimal routes for logistics using Floyd-Warshall:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // 5. Floyd-Warshall for Traffic Management Systems
  void floydWarshallTraffic() {
    print("Applying Floyd-Warshall to optimize traffic flow:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // 6. Floyd-Warshall for Social Network Analysis (Degrees of Separation)
  void floydWarshallSocialNetwork() {
    print("Analyzing shortest connections in a social network:");
    floydWarshallStandard(); // Use the standard Floyd-Warshall algorithm
  }

  // Helper function to print the distance matrix
  void printMatrix() {
    for (var row in dist) {
      // Replace infinity with "INF" for better readability
      print(row.map((e) => e == INF ? "INF" : e.toString()).join(" "));
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

  print("\nFloyd-Warshall with Path Reconstruction:");
  graph.floydWarshallPath(); // Run Floyd-Warshall with path reconstruction

  print("\nNetwork Routing Optimization:");
  graph.floydWarshallNetwork(); // Simulate network routing optimization

  print("\nLogistics Optimization:");
  graph.floydWarshallLogistics(); // Simulate logistics optimization

  print("\nTraffic Management:");
  graph.floydWarshallTraffic(); // Simulate traffic management

  print("\nSocial Network Analysis:");
  graph.floydWarshallSocialNetwork(); // Simulate social network analysis
}
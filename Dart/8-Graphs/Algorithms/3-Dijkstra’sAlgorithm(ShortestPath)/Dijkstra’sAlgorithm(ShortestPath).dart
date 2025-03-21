// Dijkstra’s Algorithm Implementations in Dart
// This code includes five different approaches with real-world applications

import 'package:collection/collection.dart'; // Import the collection package for HeapPriorityQueue
import 'dart:math';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<List<int>>> adjList; // Adjacency list representation of the graph

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    adjList = List.generate(vertices, (_) => []); // Initialize adjacency list with empty lists for each vertex
  }

  // Method to add an undirected edge to the graph
  void addEdge(int src, int dest, int weight) {
    adjList[src].add([dest, weight]); // Add edge from src to dest with the given weight
    adjList[dest].add([src, weight]); // Add edge from dest to src with the given weight (undirected)
  }

  // 1. Standard Dijkstra’s Algorithm using Min-Heap (Priority Queue)
  void dijkstraStandard(int start) {
    // Initialize distances to infinity for all vertices except the start vertex
    List<int> dist = List.filled(vertices, 1 << 30); // 1 << 30 represents a large integer (effectively infinity)
    dist[start] = 0; // Set the distance of the start vertex to 0

    // Create a priority queue (min-heap) to store vertices and their distances
    HeapPriorityQueue<List<int>> pq = HeapPriorityQueue<List<int>>((a, b) => a[1].compareTo(b[1]));
    pq.add([start, 0]); // Add the start vertex with its distance to the priority queue

    // Loop until the priority queue is empty
    while (pq.isNotEmpty) {
      var node = pq.removeFirst(); // Get the vertex with the smallest distance
      int u = node[0]; // Current vertex
      int d = node[1]; // Current distance

      // If the current distance is greater than the stored distance, skip
      if (d > dist[u]) continue;

      // Iterate through all neighbors of the current vertex
      for (var edge in adjList[u]) {
        int v = edge[0], weight = edge[1]; // Neighbor vertex and edge weight

        // If a shorter path to the neighbor is found, update the distance
        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight; // Update the distance
          pq.add([v, dist[v]]); // Add the neighbor to the priority queue
        }
      }
    }
    print("Shortest distances from node $start: $dist"); // Print the shortest distances
  }

  // 2. Dijkstra with Path Reconstruction (e.g., GPS Navigation)
  List<int> dijkstraPath(int start, int end) {
    // Initialize distances to infinity and previous vertices to -1
    List<int> dist = List.filled(vertices, 1 << 30);
    List<int> prev = List.filled(vertices, -1);
    dist[start] = 0;

    // Create a priority queue
    HeapPriorityQueue<List<int>> pq = HeapPriorityQueue<List<int>>((a, b) => a[1].compareTo(b[1]));
    pq.add([start, 0]);

    // Loop until the priority queue is empty
    while (pq.isNotEmpty) {
      var node = pq.removeFirst();
      int u = node[0];
      int d = node[1];
      if (d > dist[u]) continue;

      // Iterate through all neighbors
      for (var edge in adjList[u]) {
        int v = edge[0], weight = edge[1];
        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          prev[v] = u; // Store the previous vertex in the shortest path
          pq.add([v, dist[v]]);
        }
      }
    }

    // Reconstruct the shortest path from end to start
    List<int> path = [];
    for (int at = end; at != -1; at = prev[at]) {
      path.insert(0, at); // Insert the vertex at the beginning of the path
    }
    return path; // Return the shortest path
  }

  // 3. Dijkstra on Grid-Based Maps (e.g., City Road Navigation)
  void dijkstraGridNavigation(int start) {
    print("Finding shortest path from city node $start:");
    dijkstraStandard(start); // Use the standard Dijkstra's algorithm
  }

  // 4. Dijkstra for Network Latency Optimization
  void dijkstraNetworkLatency(int start) {
    print("Optimizing network latency from server $start:");
    dijkstraStandard(start); // Use the standard Dijkstra's algorithm
  }

  // 5. Dijkstra for Game Pathfinding (e.g., AI Enemy Movement)
  List<int> dijkstraGameAI(int start, int end) {
    print("Calculating AI movement from $start to $end:");
    return dijkstraPath(start, end); // Use Dijkstra's algorithm with path reconstruction
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

  print("\nStandard Dijkstra:");
  graph.dijkstraStandard(0); // Run standard Dijkstra's algorithm from vertex 0

  print("\nShortest Path (0 to 5):");
  print(graph.dijkstraPath(0, 5)); // Find the shortest path from vertex 0 to 5

  print("\nGrid Navigation:");
  graph.dijkstraGridNavigation(0); // Simulate grid navigation from vertex 0

  print("\nNetwork Latency Optimization:");
  graph.dijkstraNetworkLatency(0); // Simulate network latency optimization from vertex 0

  print("\nGame AI Pathfinding (0 to 5):");
  print(graph.dijkstraGameAI(0, 5)); // Simulate game AI pathfinding from vertex 0 to 5
}
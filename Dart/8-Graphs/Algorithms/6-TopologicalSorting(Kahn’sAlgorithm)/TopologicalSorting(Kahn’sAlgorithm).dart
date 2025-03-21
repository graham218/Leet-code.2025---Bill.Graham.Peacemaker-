// Topological Sorting using Kahn's Algorithm in Dart
// This code includes five different approaches with real-world applications

import 'dart:collection';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> adjList; // Adjacency list representation of the graph

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    adjList = List.generate(vertices, (_) => []); // Initialize adjacency list with empty lists
  }

  // Method to add a directed edge to the graph
  void addEdge(int src, int dest) {
    adjList[src].add(dest); // Add an edge from src to dest
  }

  // 1. Standard Kahn’s Algorithm (BFS-Based)
  void kahnStandard() {
    // Initialize in-degree of all vertices to 0
    List<int> inDegree = List.filled(vertices, 0);
    // Calculate in-degree for each vertex
    for (var neighbors in adjList) {
      for (var v in neighbors) {
        inDegree[v]++; // Increment in-degree of v for each incoming edge
      }
    }

    // Create a queue to store vertices with in-degree 0
    Queue<int> queue = Queue<int>();
    // Add all vertices with in-degree 0 to the queue
    for (int i = 0; i < vertices; i++) {
      if (inDegree[i] == 0) queue.add(i);
    }

    // List to store the topological order
    List<int> topOrder = [];
    // Process vertices in the queue
    while (queue.isNotEmpty) {
      int u = queue.removeFirst(); // Get the vertex with in-degree 0
      topOrder.add(u); // Add the vertex to the topological order

      // Update in-degree of neighbors of u
      for (var v in adjList[u]) {
        if (--inDegree[v] == 0) {
          queue.add(v); // Add neighbor to queue if its in-degree becomes 0
        }
      }
    }
    print("Standard Topological Order: $topOrder");
  }

  // 2. Topological Sorting with Cycle Detection
  bool hasCycle() {
    // Initialize in-degree of all vertices to 0
    List<int> inDegree = List.filled(vertices, 0);
    // Calculate in-degree for each vertex
    for (var neighbors in adjList) {
      for (var v in neighbors) {
        inDegree[v]++; // Increment in-degree of v for each incoming edge
      }
    }

    // Create a queue to store vertices with in-degree 0
    Queue<int> queue = Queue<int>();
    // Add all vertices with in-degree 0 to the queue
    for (int i = 0; i < vertices; i++) {
      if (inDegree[i] == 0) queue.add(i);
    }

    // Count of processed vertices
    int count = 0;
    // Process vertices in the queue
    while (queue.isNotEmpty) {
      int u = queue.removeFirst(); // Get the vertex with in-degree 0
      count++; // Increment count

      // Update in-degree of neighbors of u
      for (var v in adjList[u]) {
        if (--inDegree[v] == 0) {
          queue.add(v); // Add neighbor to queue if its in-degree becomes 0
        }
      }
    }
    // If count is not equal to vertices, there is a cycle
    return count != vertices;
  }

  // 3. Topological Sorting for Task Scheduling
  void kahnTaskScheduling() {
    print("Task Scheduling Order:");
    kahnStandard(); // Use standard Kahn's algorithm
  }

  // 4. Dependency Resolution in Package Management
  void kahnDependencyResolution() {
    print("Package Dependency Resolution Order:");
    kahnStandard(); // Use standard Kahn's algorithm
  }

  // 5. Topological Sorting for Course Prerequisite Planning
  void kahnCoursePlanning() {
    print("Course Planning Order:");
    kahnStandard(); // Use standard Kahn's algorithm
  }
}

void main() {
  Graph graph = Graph(6); // Create a graph with 6 vertices
  graph.addEdge(5, 2); // Add directed edges to the graph
  graph.addEdge(5, 0);
  graph.addEdge(4, 0);
  graph.addEdge(4, 1);
  graph.addEdge(2, 3);
  graph.addEdge(3, 1);

  print("\nStandard Kahn's Algorithm:");
  graph.kahnStandard(); // Run standard Kahn's algorithm

  print("\nCycle Detection:");
  print("Graph has cycle: ${graph.hasCycle()}"); // Check for cycles

  print("\nTask Scheduling:");
  graph.kahnTaskScheduling(); // Simulate task scheduling

  print("\nDependency Resolution:");
  graph.kahnDependencyResolution(); // Simulate dependency resolution

  print("\nCourse Planning:");
  graph.kahnCoursePlanning(); // Simulate course planning
}
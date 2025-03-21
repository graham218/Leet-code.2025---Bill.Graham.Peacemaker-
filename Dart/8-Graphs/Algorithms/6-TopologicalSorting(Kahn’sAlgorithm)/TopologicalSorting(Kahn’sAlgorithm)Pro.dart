// Advanced Topological Sorting using Kahn's Algorithm
// This implementation includes six different approaches with real-world applications

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

  // 1. Standard Kahn's Algorithm for Topological Sorting
  List<int> topologicalSort() {
    // Initialize in-degree of all vertices to 0
    List<int> inDegree = List.filled(vertices, 0);
    // Calculate in-degree for each vertex
    for (var edges in adjList) {
      for (var node in edges) {
        inDegree[node]++; // Increment in-degree of node for each incoming edge
      }
    }

    // Create a queue to store vertices with in-degree 0
    Queue<int> queue = Queue<int>();
    // Add all vertices with in-degree 0 to the queue
    for (int i = 0; i < vertices; i++) {
      if (inDegree[i] == 0) {
        queue.add(i);
      }
    }

    // List to store the topological order
    List<int> order = [];
    // Process vertices in the queue
    while (queue.isNotEmpty) {
      int node = queue.removeFirst(); // Get the vertex with in-degree 0
      order.add(node); // Add the vertex to the topological order

      // Update in-degree of neighbors of the current node
      for (var neighbor in adjList[node]) {
        inDegree[neighbor]--;
        // If the neighbor's in-degree becomes 0, add it to the queue
        if (inDegree[neighbor] == 0) {
          queue.add(neighbor);
        }
      }
    }

    // Check if the graph has a cycle
    if (order.length != vertices) {
      // If the number of processed nodes is not equal to the number of vertices,
      // it means there is a cycle, and topological sorting is not possible.
      return []; // Return an empty list indicating a cycle.
    }

    return order; // Return the topological order
  }

  // 2. Cycle Detection using Kahn’s Algorithm
  bool hasCycle() {
    List<int> order = topologicalSort();
    return order.isEmpty; // If topologicalSort returns an empty list, it means there's a cycle.
  }

  // 3. Task Scheduling System (e.g., build dependencies in CI/CD pipelines)
  void taskScheduling() {
    List<int> order = topologicalSort();
    if (order.isNotEmpty) {
      print("Task Execution Order: $order");
    } else {
      print("Cannot determine task execution order due to cycles.");
    }
  }

  // 4. Course Prerequisites Ordering (e.g., university curriculum planning)
  void courseScheduling() {
    List<int> order = topologicalSort();
    if (order.isNotEmpty) {
      print("Course Completion Order: $order");
    } else {
      print("Cannot determine course completion order due to circular dependencies.");
    }
  }

  // 5. Dependency Resolution (e.g., package installations in a programming language)
  void dependencyResolution() {
    List<int> order = topologicalSort();
    if (order.isNotEmpty) {
      print("Package Installation Order: $order");
    } else {
      print("Cannot resolve dependencies due to circular dependencies.");
    }
  }

  // 6. Project Management Workflow (e.g., sequential task completion in a team project)
  void projectWorkflow() {
    List<int> order = topologicalSort();
    if (order.isNotEmpty) {
      print("Project Task Completion Order: $order");
    } else {
      print("Cannot determine project task completion order due to cycles.");
    }
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

  print("\nTopological Sorting:");
  List<int> topOrder = graph.topologicalSort();
  if (topOrder.isNotEmpty) {
    print(topOrder);
  } else {
    print("Graph contains a cycle.");
  }

  print("\nCycle Detection:");
  print(graph.hasCycle() ? "Cycle Detected" : "No Cycle Detected");

  print("\nTask Scheduling:");
  graph.taskScheduling();

  print("\nCourse Scheduling:");
  graph.courseScheduling();

  print("\nDependency Resolution:");
  graph.dependencyResolution();

  print("\nProject Workflow:");
  graph.projectWorkflow();

  //Example with a cycle.
  Graph graph2 = Graph(3);
  graph2.addEdge(0, 1);
  graph2.addEdge(1, 2);
  graph2.addEdge(2, 0);

  print('\nGraph with cycle example:');
  print('Has Cycle: ${graph2.hasCycle()}');
  print('Topological Sort: ${graph2.topologicalSort()}');
}
// Breadth-First Search (BFS) Implementations in Dart
// This code runs on DartPad without errors and demonstrates five different approaches to BFS

import 'dart:collection';

class Graph {
  // Number of vertices in the graph
  late int vertices;
  // Adjacency list representation of the graph
  late List<List<int>> adjList;

  // Constructor to initialize the graph with the given number of vertices
  Graph(this.vertices) {
    // Initialize the adjacency list as a list of lists, each sublist representing the neighbors of a vertex
    adjList = List.generate(vertices, (_) => []);
  }

  // Adds an edge between vertices v and w (undirected graph)
  void addEdge(int v, int w) {
    adjList[v].add(w); // Add w to v's neighbors
    //If you want a directed graph, remove the next line.
    //adjList[w].add(v); // Add v to w's neighbors (for undirected graphs)
  }

  // 1. Standard BFS Using Queue
  void bfsStandard(int start) {
    // Initialize a list to track visited vertices
    List<bool> visited = List.filled(vertices, false);
    // Initialize a queue for BFS traversal
    Queue<int> queue = Queue<int>();
    // Mark the starting vertex as visited and add it to the queue
    visited[start] = true;
    queue.add(start);

    print("BFS Standard Traversal from $start:");
    // Continue BFS until the queue is empty
    while (queue.isNotEmpty) {
      // Dequeue a vertex from the queue
      int node = queue.removeFirst();
      // Print the visited vertex
      print(node);
      // Iterate over the neighbors of the current vertex
      for (int neighbor in adjList[node]) {
        // If the neighbor has not been visited
        if (!visited[neighbor]) {
          // Mark the neighbor as visited and add it to the queue
          visited[neighbor] = true;
          queue.add(neighbor);
        }
      }
    }
  }

  // 2. BFS for Shortest Path in an Unweighted Graph
  List<int> bfsShortestPath(int start, int end) {
    // Initialize a list to track visited vertices
    List<bool> visited = List.filled(vertices, false);
    // Initialize a queue to store paths (lists of vertices)
    Queue<List<int>> queue = Queue<List<int>>();
    // Add the starting vertex as a path to the queue
    queue.add([start]);
    // Mark the starting vertex as visited
    visited[start] = true;

    // Continue BFS until the queue is empty
    while (queue.isNotEmpty) {
      // Dequeue a path from the queue
      List<int> path = queue.removeFirst();
      // Get the last vertex in the path (current node)
      int node = path.last;
      // If the current node is the end vertex, return the path
      if (node == end) return path;

      // Iterate over the neighbors of the current node
      for (int neighbor in adjList[node]) {
        // If the neighbor has not been visited
        if (!visited[neighbor]) {
          // Mark the neighbor as visited
          visited[neighbor] = true;
          // Create a new path by appending the neighbor to the current path and add it to the queue
          queue.add([...path, neighbor]);
        }
      }
    }
    // If no path is found, return an empty list
    return [];
  }

  // 3. BFS for Level Order Traversal (Binary Tree Representation - using the graph as a general graph)
  void bfsLevelOrder() {
    print("BFS Level Order Traversal:");
    // Loop through each vertex as a potential starting point
    for (int i = 0; i < vertices; i++) {
      print("Level $i: ");
      // Perform standard BFS from each vertex
      bfsStandard(i);
      print("\n");
    }
  }

  // 4. BFS for Connected Components Detection
  void bfsConnectedComponents() {
    // Initialize a list to track visited vertices
    List<bool> visited = List.filled(vertices, false);
    // Initialize a counter for connected components
    int componentCount = 0;

    print("BFS Connected Components:");
    // Loop through each vertex
    for (int i = 0; i < vertices; i++) {
      // If the vertex has not been visited, it belongs to a new connected component
      if (!visited[i]) {
        // Increment the component count
        componentCount++;
        print("Component $componentCount:");
        // Perform BFS to visit all vertices in the current connected component
        _bfsComponent(i, visited);
      }
    }
  }

  // Helper function to perform BFS for a connected component
  void _bfsComponent(int start, List<bool> visited) {
    // Initialize a queue for BFS traversal
    Queue<int> queue = Queue<int>();
    // Add the starting vertex to the queue and mark it as visited
    queue.add(start);
    visited[start] = true;
    // Continue BFS until the queue is empty
    while (queue.isNotEmpty) {
      // Dequeue a vertex from the queue
      int node = queue.removeFirst();
      // Print the visited vertex
      print(node);
      // Iterate over the neighbors of the current vertex
      for (int neighbor in adjList[node]) {
        // If the neighbor has not been visited
        if (!visited[neighbor]) {
          // Mark the neighbor as visited and add it to the queue
          visited[neighbor] = true;
          queue.add(neighbor);
        }
      }
    }
  }

  // 5. BFS for Cycle Detection in an Undirected Graph
  bool bfsDetectCycle() {
    // Initialize a list to track visited vertices
    List<bool> visited = List.filled(vertices, false);
    // Loop through each vertex
    for (int i = 0; i < vertices; i++) {
      // If the vertex has not been visited and a cycle is detected starting from it, return true
      if (!visited[i] && _bfsCycleCheck(i, visited)) {
        return true;
      }
    }
    // If no cycle is detected, return false
    return false;
  }

  // Helper function to perform BFS for cycle detection
  bool _bfsCycleCheck(int start, List<bool> visited) {
    // Initialize a queue for BFS traversal
    Queue<int> queue = Queue<int>();
    // Initialize a map to store the parent of each vertex
    Map<int, int> parent = {};
    // Add the starting vertex to the queue and mark it as visited
    queue.add(start);
    visited[start] = true;
    // Set the parent of the starting vertex to -1 (no parent)
    parent[start] = -1;

    // Continue BFS until the queue is empty
    while (queue.isNotEmpty) {
      // Dequeue a vertex from the queue
      int node = queue.removeFirst();
      // Iterate over the neighbors of the current vertex
      for (int neighbor in adjList[node]) {
        // If the neighbor has not been visited
        if (!visited[neighbor]) {
          // Mark the neighbor as visited, add it to the queue, and set its parent
          visited[neighbor] = true;
          queue.add(neighbor);
          parent[neighbor] = node;
        } else if (parent[node] != neighbor) {
          // If the neighbor has been visited and is not the parent of the current node, a cycle is detected
          return true; // Cycle detected
        }
      }
    }
    // If no cycle is detected, return false
    return false;
  }
}

void main() {
  // Create a graph with 6 vertices
  Graph graph = Graph(6);
  // Add edges to the graph
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);

  print("Standard BFS:");
  graph.bfsStandard(0);

  print("\nShortest Path (0 to 5):");
  List<int> shortestPath = graph.bfsShortestPath(0, 5);
  print(shortestPath.isNotEmpty ? shortestPath : "No path found");

  print("\nLevel Order Traversal:");
  graph.bfsLevelOrder();

  print("\nConnected Components:");
  graph.bfsConnectedComponents();

  print("\nCycle Detection:");
  print(graph.bfsDetectCycle() ? "Graph has a cycle" : "Graph has no cycle");
}
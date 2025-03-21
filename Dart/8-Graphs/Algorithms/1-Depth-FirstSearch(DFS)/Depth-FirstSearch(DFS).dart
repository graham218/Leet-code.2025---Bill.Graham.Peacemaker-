// Depth-First Search (DFS) Implementations in Dart
// This code runs on DartPad without errors and demonstrates five different approaches to DFS

import 'dart:collection';

class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> adjList; // Adjacency list representation of the graph

  // Constructor: Initializes the graph with a given number of vertices
  Graph(this.vertices) {
    // Creates an adjacency list where each element is an empty list, representing the neighbors of each vertex
    adjList = List.generate(vertices, (_) => []);
  }

  // Adds an undirected edge between vertex v and vertex w
  void addEdge(int v, int w) {
    adjList[v].add(w); // Adds w to the adjacency list of v
    //If the graph is directed remove the next line.
    //adjList[w].add(v); // Adds v to the adjacency list of w (for undirected graphs)
  }

  // 1. DFS Using Recursion
  // Performs DFS starting from a given 'start' vertex using recursion
  // 'visited' is a list to keep track of visited vertices
  void dfsRecursive(int start, List<bool> visited) {
    visited[start] = true; // Mark the current vertex as visited
    print(start); // Print the current vertex (or process it)

    // Iterate through the neighbors of the current vertex
    for (int neighbor in adjList[start]) {
      // If the neighbor has not been visited, recursively call DFS on it
      if (!visited[neighbor]) {
        dfsRecursive(neighbor, visited);
      }
    }
  }

  // 2. DFS Using Stack (Iterative Approach)
  // Performs DFS starting from a given 'start' vertex using a stack (iterative)
  void dfsIterative(int start) {
    List<bool> visited = List.filled(vertices, false); // Initialize a visited list
    Stack<int> stack = Stack<int>(); // Create a stack to simulate recursion
    stack.push(start); // Push the starting vertex onto the stack

    // Continue until the stack is empty
    while (stack.isNotEmpty) {
      int node = stack.pop(); // Pop the top vertex from the stack

      // If the vertex has not been visited
      if (!visited[node]) {
        visited[node] = true; // Mark it as visited
        print(node); // Print the vertex (or process it)

        // Push the neighbors of the vertex onto the stack in reverse order
        // This ensures that the neighbors are visited in the same order as in the recursive approach
        for (int neighbor in adjList[node].reversed) {
          if (!visited[neighbor]) {
            stack.push(neighbor);
          }
        }
      }
    }
  }

  // 3. DFS Using Queue (Simulating Stack Behavior)
  // Performs DFS using a queue, but manipulates it to behave like a stack
  void dfsUsingQueue(int start) {
    List<bool> visited = List.filled(vertices, false); // Initialize a visited list
    Queue<int> queue = Queue<int>(); // Use a queue, but treat it like a stack
    queue.addFirst(start); // Add the starting vertex to the front of the queue

    // Continue until the queue is empty
    while (queue.isNotEmpty) {
      int node = queue.removeFirst(); // Remove the first element (simulating stack pop)

      // If the vertex has not been visited
      if (!visited[node]) {
        visited[node] = true; // Mark it as visited
        print(node); // Print the vertex (or process it)

        // Add the neighbors to the front of the queue in reverse order (simulating stack push)
        for (int neighbor in adjList[node].reversed) {
          if (!visited[neighbor]) {
            queue.addFirst(neighbor);
          }
        }
      }
    }
  }

  // 4. DFS Using Backtracking
  // Performs DFS with backtracking, resetting visited status after exploring a branch
  void dfsBacktracking(int start, List<bool> visited) {
    visited[start] = true; // Mark the current vertex as visited
    print(start); // Print the current vertex (or process it)

    // Iterate through the neighbors of the current vertex
    for (int neighbor in adjList[start]) {
      // If the neighbor has not been visited, recursively call DFS on it
      if (!visited[neighbor]) {
        dfsBacktracking(neighbor, visited);
        visited[neighbor] = false; // Backtrack: Reset the visited status after exploring the branch.
        //This backtracking is really only useful if you need to use the visited array for other purposes while traversing the graph, or if you need to perform other operations while unwinding the recursive stack.
      }
    }
  }

  // 5. DFS Using Set for Visited Nodes
  // Performs DFS using a Set to keep track of visited nodes
  void dfsWithSet(int start, Set<int> visited) {
    visited.add(start); // Add the current vertex to the visited set
    print(start); // Print the current vertex (or process it)

    // Iterate through the neighbors of the current vertex
    for (int neighbor in adjList[start]) {
      // If the neighbor is not in the visited set, recursively call DFS on it
      if (!visited.contains(neighbor)) {
        dfsWithSet(neighbor, visited);
      }
    }
  }
}

// Stack implementation using List
class Stack<T> {
  final List<T> _list = []; // Internal list to store stack elements

  void push(T value) => _list.add(value); // Push an element onto the stack

  T pop() => _list.removeLast(); // Pop an element from the stack

  bool get isNotEmpty => _list.isNotEmpty; // Check if the stack is not empty
}

void main() {
  Graph graph = Graph(6); // Create a graph with 6 vertices
  graph.addEdge(0, 1); // Add edges to the graph
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);

  print("DFS Recursive:");
  graph.dfsRecursive(0, List.filled(graph.vertices, false)); // Perform DFS using recursion

  print("\nDFS Iterative:");
  graph.dfsIterative(0); // Perform DFS using iteration (stack)

  print("\nDFS Using Queue:");
  graph.dfsUsingQueue(0); // Perform DFS using a queue (simulating stack)

  print("\nDFS Backtracking:");
  graph.dfsBacktracking(0, List.filled(graph.vertices, false)); // Perform DFS with backtracking

  print("\nDFS With Set:");
  graph.dfsWithSet(0, <int>{}); // Perform DFS using a Set
}
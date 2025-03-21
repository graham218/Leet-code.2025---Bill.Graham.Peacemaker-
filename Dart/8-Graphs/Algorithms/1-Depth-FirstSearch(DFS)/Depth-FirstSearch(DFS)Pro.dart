// Advanced Depth-First Search (DFS) Implementations in Dart
// This code demonstrates six different DFS approaches with real-world applications.

import 'dart:collection';

// Graph class to represent a graph using adjacency lists
class Graph {
  late int vertices; // Number of vertices in the graph
  late List<List<int>> adjList; // Adjacency list to store edges

  // Constructor to initialize the graph with a given number of vertices
  Graph(this.vertices) {
    adjList = List.generate(vertices, (_) => []); // Initialize adjacency list
  }

  // Method to add an edge between two vertices (v and w)
  void addEdge(int v, int w) {
    adjList[v].add(w); // Add w to v's adjacency list
  }

  // 1. DFS Recursive (General Graph Traversal)
  // This method performs a recursive DFS starting from a given vertex.
  void dfsRecursive(int start, List<bool> visited) {
    visited[start] = true; // Mark the current node as visited
    print(start); // Print the current node

    // Traverse all neighbors of the current node
    for (int neighbor in adjList[start]) {
      if (!visited[neighbor]) {
        dfsRecursive(neighbor, visited); // Recursively visit unvisited neighbors
      }
    }
  }

  // 2. DFS Iterative Using Stack (Maze Solver)
  // This method performs an iterative DFS using a stack, useful for maze-solving.
  void dfsMazeSolver(int start) {
    List<bool> visited = List.filled(vertices, false); // Track visited nodes
    Stack<int> stack = Stack<int>(); // Stack to manage DFS traversal
    stack.push(start); // Start with the initial node

    while (stack.isNotEmpty) {
      int node = stack.pop(); // Pop the top node from the stack
      if (!visited[node]) {
        visited[node] = true; // Mark the node as visited
        print(node); // Print the node

        // Push all unvisited neighbors to the stack (in reverse order)
        for (int neighbor in adjList[node].reversed) {
          if (!visited[neighbor]) {
            stack.push(neighbor);
          }
        }
      }
    }
  }

  // 3. DFS for Cycle Detection in a Graph
  // This method detects cycles in a directed graph using DFS.
  bool hasCycle(int node, List<bool> visited, List<bool> recStack) {
    visited[node] = true; // Mark the current node as visited
    recStack[node] = true; // Add the current node to the recursion stack

    // Traverse all neighbors of the current node
    for (int neighbor in adjList[node]) {
      if (!visited[neighbor] && hasCycle(neighbor, visited, recStack)) {
        return true; // If a cycle is found in the neighbor, return true
      } else if (recStack[neighbor]) {
        return true; // If the neighbor is in the recursion stack, a cycle exists
      }
    }

    recStack[node] = false; // Remove the current node from the recursion stack
    return false; // No cycle found
  }

  // Method to detect cycles in the entire graph
  bool detectCycle() {
    List<bool> visited = List.filled(vertices, false); // Track visited nodes
    List<bool> recStack = List.filled(vertices, false); // Track recursion stack

    // Check for cycles starting from each unvisited node
    for (int i = 0; i < vertices; i++) {
      if (!visited[i] && hasCycle(i, visited, recStack)) {
        return true; // Cycle detected
      }
    }
    return false; // No cycle found
  }

  // 4. DFS for Topological Sorting (Task Scheduling)
  // This method performs a topological sort using DFS.
  void topologicalSortUtil(int node, List<bool> visited, Stack<int> stack) {
    visited[node] = true; // Mark the current node as visited

    // Traverse all neighbors of the current node
    for (int neighbor in adjList[node]) {
      if (!visited[neighbor]) {
        topologicalSortUtil(neighbor, visited, stack); // Recursively visit neighbors
      }
    }

    stack.push(node); // Push the current node to the stack after visiting all neighbors
  }

  // Method to perform topological sorting on the graph
  void topologicalSort() {
    Stack<int> stack = Stack<int>(); // Stack to store the topological order
    List<bool> visited = List.filled(vertices, false); // Track visited nodes

    // Perform DFS for each unvisited node
    for (int i = 0; i < vertices; i++) {
      if (!visited[i]) {
        topologicalSortUtil(i, visited, stack);
      }
    }

    // Print the topological order
    while (stack.isNotEmpty) {
      print(stack.pop());
    }
  }

  // 5. DFS for Connected Components (Social Network Analysis)
  // This method finds and prints all connected components in the graph.
  void findConnectedComponents() {
    List<bool> visited = List.filled(vertices, false); // Track visited nodes
    int componentCount = 0; // Counter for connected components

    // Traverse each unvisited node to find connected components
    for (int i = 0; i < vertices; i++) {
      if (!visited[i]) {
        print("Component $componentCount:");
        dfsRecursive(i, visited); // Perform DFS to find the component
        componentCount++; // Increment component count
      }
    }
  }

  // 6. DFS for Word Search in a Grid (AI Search Algorithms)
  // This method searches for a word in a 2D grid using DFS.
  bool wordSearch(List<List<String>> board, String word) {
    int rows = board.length; // Number of rows in the grid
    int cols = board[0].length; // Number of columns in the grid
    List<List<bool>> visited = List.generate(rows, (_) => List.filled(cols, false)); // Track visited cells

    // Nested DFS function to search for the word
    bool dfs(int row, int col, int index) {
      // Base case: If the entire word is matched, return true
      if (index == word.length) return true;

      // Boundary and validity checks
      if (row < 0 || col < 0 || row >= rows || col >= cols || visited[row][col] || board[row][col] != word[index]) {
        return false;
      }

      visited[row][col] = true; // Mark the current cell as visited

      // Recursively search in all four directions
      bool found = dfs(row + 1, col, index + 1) || dfs(row - 1, col, index + 1) ||
          dfs(row, col + 1, index + 1) || dfs(row, col - 1, index + 1);

      visited[row][col] = false; // Backtrack: Unmark the current cell
      return found;
    }

    // Iterate through each cell in the grid to start the search
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (board[i][j] == word[0] && dfs(i, j, 0)) {
          return true; // Word found
        }
      }
    }
    return false; // Word not found
  }
}

// Stack implementation using List
class Stack<T> {
  final List<T> _list = []; // Internal list to store stack elements

  void push(T value) => _list.add(value); // Push an element onto the stack
  T pop() => _list.removeLast(); // Pop the top element from the stack
  bool get isNotEmpty => _list.isNotEmpty; // Check if the stack is not empty
}

// Main function to demonstrate the DFS implementations
void main() {
  Graph graph = Graph(6); // Create a graph with 6 vertices
  graph.addEdge(0, 1); // Add edges to the graph
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);

  print("DFS Recursive:");
  graph.dfsRecursive(0, List.filled(graph.vertices, false)); // Perform recursive DFS

  print("\nDFS Maze Solver:");
  graph.dfsMazeSolver(0); // Perform iterative DFS using a stack

  print("\nCycle Detection:");
  print(graph.detectCycle() ? "Graph has a cycle" : "Graph has no cycle"); // Detect cycles

  print("\nTopological Sorting:");
  graph.topologicalSort(); // Perform topological sorting

  print("\nConnected Components:");
  graph.findConnectedComponents(); // Find connected components

  print("\nWord Search:");
  List<List<String>> board = [
    ["A", "B", "C", "E"],
    ["S", "F", "C", "S"],
    ["A", "D", "E", "E"]
  ];
  print(graph.wordSearch(board, "ABCCED") ? "Word Found" : "Word Not Found"); // Search for a word in the grid
}
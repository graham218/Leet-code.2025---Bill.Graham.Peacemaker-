// Advanced Breadth-First Search (BFS) Implementations in Dart
// This code includes six different BFS approaches with real-world applications

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

  // 1. Standard BFS Traversal
  void bfsTraversal(int start) {
    // Initialize a list to track visited vertices
    List<bool> visited = List.filled(vertices, false);
    // Initialize a queue for BFS traversal
    Queue<int> queue = Queue<int>();
    // Mark the starting vertex as visited and add it to the queue
    visited[start] = true;
    queue.add(start);

    print("BFS Traversal from node $start:");
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

  // 2. Shortest Path in an Unweighted Graph (e.g., Social Network Friends Suggestion)
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

  // 3. Web Crawler (BFS-based link traversal)
  void bfsWebCrawl(int start) {
    print("Simulated Web Crawl starting at node $start:");
    // Simulate web crawling by performing standard BFS traversal
    bfsTraversal(start);
  }

  // 4. GPS Navigation (Finding Shortest Route)
  List<int> bfsGPSNavigation(int start, int destination) {
    // Utilize the shortest path BFS to simulate GPS navigation
    return bfsShortestPath(start, destination);
  }

  // 5. Network Packet Broadcasting
  void bfsPacketBroadcast(int start) {
    print("Network Packet Broadcast from node $start:");
    // Simulate packet broadcasting by performing standard BFS traversal
    bfsTraversal(start);
  }

  // 6. Maze Solver (Finding Exit in a Grid-Based Maze)
  bool bfsMazeSolver(List<List<int>> maze, List<int> start, List<int> exit) {
    // Get the dimensions of the maze
    int rows = maze.length, cols = maze[0].length;
    // Initialize a 2D list to track visited cells in the maze
    List<List<bool>> visited = List.generate(rows, (_) => List.filled(cols, false));
    // Initialize a queue to store cell coordinates
    Queue<List<int>> queue = Queue();
    // Add the starting cell to the queue and mark it as visited
    queue.add(start);
    visited[start[0]][start[1]] = true;

    // Define the possible movement directions (right, down, left, up)
    List<List<int>> directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    // Continue BFS until the queue is empty
    while (queue.isNotEmpty) {
      // Dequeue a cell from the queue
      List<int> pos = queue.removeFirst();
      // If the current cell is the exit, maze is solved
      if (pos[0] == exit[0] && pos[1] == exit[1]) {
        print("Maze solved! Path found.");
        return true;
      }
      // Iterate over the possible movement directions
      for (var dir in directions) {
        // Calculate the coordinates of the next cell
        int newRow = pos[0] + dir[0], newCol = pos[1] + dir[1];
        // Check if the next cell is within the maze boundaries, is not a wall (maze[newRow][newCol] == 0), and has not been visited
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
            maze[newRow][newCol] == 0 && !visited[newRow][newCol]) {
          // Add the next cell to the queue and mark it as visited
          queue.add([newRow, newCol]);
          visited[newRow][newCol] = true;
        }
      }
    }
    // If the queue is empty and the exit has not been found, maze is unsolvable
    print("Maze unsolvable.");
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

  print("\nStandard BFS Traversal:");
  graph.bfsTraversal(0);

  print("\nShortest Path (0 to 5):");
  print(graph.bfsShortestPath(0, 5));

  print("\nWeb Crawler Simulation:");
  graph.bfsWebCrawl(0);

  print("\nGPS Navigation (0 to 5):");
  print(graph.bfsGPSNavigation(0, 5));

  print("\nNetwork Packet Broadcasting:");
  graph.bfsPacketBroadcast(0);

  print("\nMaze Solver:");
  // Define a maze as a 2D list (0 represents open path, 1 represents wall)
  List<List<int>> maze = [
    [0, 1, 0, 0, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 0, 1, 0],
    [1, 1, 0, 1, 0],
    [0, 0, 0, 0, 0]
  ];
  // Solve the maze from starting cell [0, 0] to exit cell [4, 4]
  graph.bfsMazeSolver(maze, [0, 0], [4, 4]);
}
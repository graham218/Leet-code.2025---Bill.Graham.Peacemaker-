import 'dart:math';
import 'package:collection/collection.dart'; // Import the collection package

// 1. Backtracking Approach
bool findHamiltonianCycleBacktracking(List<List<int>> graph, List<int> path, int pos) {
  int n = graph.length;

  // Base case: all vertices are included in the path
  if (pos == n) {
    // Check if there is an edge from the last vertex to the starting vertex
    if (graph[path[pos - 1]][path[0]] == 1) {
      return true;
    } else {
      return false;
    }
  }

  // Try different vertices as the next vertex in the path
  for (int v = 0; v < n; v++) {
    // Check if this vertex is adjacent to the previous vertex and is not already in the path
    if (graph[path[pos - 1]][v] == 1 && !path.contains(v)) {
      path[pos] = v;
      // Recursively try to find a Hamiltonian Cycle
      if (findHamiltonianCycleBacktracking(graph, path, pos + 1)) {
        return true;
      }
      // Backtrack: if the recursive call does not find a solution, remove the vertex from the path
      path[pos] = -1;
    }
  }

  // If no solution is found, return false
  return false;
}

List<int>? hamiltonianCycleBacktracking(List<List<int>> graph) {
  int n = graph.length;
  List<int> path = List<int>.filled(n, -1);
  path[0] = 0; // Start from vertex 0

  if (findHamiltonianCycleBacktracking(graph, path, 1)) {
    return path;
  } else {
    return null;
  }
}

// 2. Backtracking with Adjacency Set Optimization
bool findHamiltonianCycleBacktrackingAdjSet(Map<int, Set<int>> adjList, List<int> path, int pos) {
  int n = adjList.length;

  if (pos == n) {
    // Check for edge between last and first vertex.
    return adjList[path[pos - 1]]?.contains(path[0]) ?? false;
  }

  final neighbors = adjList[path[pos - 1]] ?? {}; // Get neighbors, handle null

  for (int v in neighbors) {
    if (!path.contains(v)) {
      path[pos] = v;
      if (findHamiltonianCycleBacktrackingAdjSet(adjList, path, pos + 1)) {
        return true;
      }
      path[pos] = -1; // Backtrack
    }
  }
  return false;
}

List<int>? hamiltonianCycleBacktrackingAdjSet(List<List<int>> graph) {
  int n = graph.length;
  Map<int, Set<int>> adjList = {};
  for (int i = 0; i < n; i++) {
    adjList[i] = {};
    for (int j = 0; j < n; j++) {
      if (graph[i][j] == 1) {
        adjList[i]!.add(j);
      }
    }
  }

  List<int> path = List<int>.filled(n, -1);
  path[0] = 0;

  if (findHamiltonianCycleBacktrackingAdjSet(adjList, path, 1)) {
    return path;
  } else {
    return null;
  }
}

// 3. Optimized Backtracking with Degree Check
bool findHamiltonianCycleOptimized(List<List<int>> graph, List<int> path, int pos, List<int> degrees) {
  int n = graph.length;

  if (pos == n) {
    return graph[path[pos - 1]][path[0]] == 1;
  }

  for (int v = 0; v < n; v++) {
    if (graph[path[pos - 1]][v] == 1 && !path.contains(v)) {
      path[pos] = v;
      if (findHamiltonianCycleOptimized(graph, path, pos + 1, degrees)) {
        return true;
      }
      path[pos] = -1;
    }
  }
  return false;
}

List<int>? hamiltonianCycleOptimized(List<List<int>> graph) {
  int n = graph.length;
  List<int> path = List<int>.filled(n, -1);
  List<int> degrees = List<int>.filled(n, 0);

  // Calculate degrees (optimization: check if any node has degree < 2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (graph[i][j] == 1) {
        degrees[i]++;
      }
    }
    if (degrees[i] < 2) {
      return null; // No Hamiltonian Cycle if a vertex has degree < 2
    }
  }

  path[0] = 0;
  if (findHamiltonianCycleOptimized(graph, path, 1, degrees)) {
    return path;
  } else {
    return null;
  }
}

// 4.  Warnsdorff's Rule (for Knight's Tour - a special case, but showing a different heuristic)
List<int>? knightTourWarnsdorff(int size) {
  // Only works for Knight's Tour (L-shaped moves on a square grid)
  if (size <= 0) return null;
  List<List<int>> board = List.generate(size, (_) => List<int>.filled(size, -1));
  // Possible knight moves (relative offsets)
  final List<int> dx = [2, 1, -1, -2, -2, -1, 1, 2];
  final List<int> dy = [1, 2, 2, 1, -1, -2, -2, -1];

  bool isValid(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == -1;
  }

  int getDegree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
      if (isValid(x + dx[i], y + dy[i])) {
        count++;
      }
    }
    return count;
  }

  // Custom sort function to sort neighbors by their degree.  Important for Warnsdorff's
  List<int> getSortedNeighbors(int x, int y) {
    List<int> neighbors = [];
    List<int> degrees = []; // Store degrees of neighbors
    for (int i = 0; i < 8; i++) {
      int nextX = x + dx[i];
      int nextY = y + dy[i];
      if (isValid(nextX, nextY)) {
        neighbors.add(i); // Store the *index* of the move, not the coord
        degrees.add(getDegree(nextX, nextY));
      }
    }
    // Sort neighbors based on their degrees (Warnsdorff's heuristic)
    List<int> sortedNeighbors = [];
    while(neighbors.isNotEmpty){
      int minDegree = degrees.reduce((a, b) => a < b ? a : b);
      int minIndex = degrees.indexOf(minDegree);
      sortedNeighbors.add(neighbors[minIndex]);
      neighbors.removeAt(minIndex);
      degrees.removeAt(minIndex);
    }
    return sortedNeighbors;
  }

  bool solveKnightTour(int x, int y, int moveCount) {
    board[x][y] = moveCount;
    if (moveCount == size * size - 1) {
      return true; // Tour is complete
    }

    List<int> sortedNeighbors = getSortedNeighbors(x, y); // Get sorted neighbors

    for (int moveIndex in sortedNeighbors) { // Iterate through *sorted* neighbors
      int nextX = x + dx[moveIndex];
      int nextY = y + dy[moveIndex];
      if (solveKnightTour(nextX, nextY, moveCount + 1)) {
        return true;
      }
    }

    board[x][y] = -1; // Backtrack
    return false;
  }

  // Start the tour from the top-left corner (0, 0)
  if (solveKnightTour(0, 0, 0)) {
    // Convert the 2D board to a 1D path (Hamiltonian Cycle representation)
    List<int> path = [];
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        // Find the cell with move number 'k' and add its index to the path
        int k = i * size + j;
        for (int r = 0; r < size; r++) {
          for (int c = 0; c < size; c++) {
            if (board[r][c] == k) {
              path.add(r * size + c); // Convert 2D coords to 1D index
              break;
            }
          }
        }
      }
    }
    return path;
  } else {
    return null;
  }
}

// 5. Randomized Approach (for general Hamiltonian Cycle, not very efficient)
List<int>? hamiltonianCycleRandomized(List<List<int>> graph) {
  int n = graph.length;
  List<int> path = List<int>.filled(n, -1);
  List<int> vertices = List<int>.generate(n, (i) => i); // [0, 1, 2, ..., n-1]
  final random = Random();

  for (int startVertex = 0; startVertex < n; startVertex++) { // Try each start vertex
    path[0] = startVertex;
    List<int> remainingVertices = List<int>.from(vertices);
    remainingVertices.remove(startVertex);
    for (int i = 1; i < n; i++) {
      // Shuffle the remaining vertices to get a random order.
      remainingVertices.shuffle(random);
      bool foundNext = false;
      for (int j = 0; j < remainingVertices.length; j++) {
        int nextVertex = remainingVertices[j];
        if (graph[path[i - 1]][nextVertex] == 1) {
          path[i] = nextVertex;
          remainingVertices.removeAt(j);
          foundNext = true;
          break;
        }
      }
      if (!foundNext) {
        // If no valid next vertex is found, backtrack and try a different starting vertex
        path.fillRange(i, n, -1);
        break;
      }
    }

    if (path[n - 1] != -1 && graph[path[n - 1]][path[0]] == 1) {
      return path; // Found a Hamiltonian Cycle
    }
    path.fillRange(1, n, -1); // Clear path, except for the first vertex
  }
  return null; // No Hamiltonian Cycle found
}



void main() {
  // Example graph represented as an adjacency matrix
  List<List<int>> graph = [
    [0, 1, 0, 0, 1],
    [1, 0, 1, 0, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 1, 0, 1],
    [1, 0, 0, 1, 0],
  ];

  print("Hamiltonian Cycle Example:");
  print("Graph (Adjacency Matrix):");
  for (var row in graph) {
    print(row);
  }
  print("\n");

  // 1. Backtracking
  List<int>? path1 = hamiltonianCycleBacktracking(graph);
  print("1. Backtracking:");
  if (path1 != null) {
    print("Hamiltonian Cycle: $path1");
  } else {
    print("No Hamiltonian Cycle found.");
  }

  // 2. Backtracking with Adjacency Set
  List<int>? path2 = hamiltonianCycleBacktrackingAdjSet(graph);
  print("\n2. Backtracking with Adjacency Set:");
  if (path2 != null) {
    print("Hamiltonian Cycle: $path2");
  } else {
    print("No Hamiltonian Cycle found.");
  }

  // 3. Optimized Backtracking
  List<int>? path3 = hamiltonianCycleOptimized(graph);
  print("\n3. Optimized Backtracking:");
  if (path3 != null) {
    print("Hamiltonian Cycle: $path3");
  } else {
    print("No Hamiltonian Cycle found.");
  }

  // 4. Warnsdorff's Rule (Knight's Tour)
  print("\n4. Warnsdorff's Rule (Knight's Tour - Size 8):");
  List<int>? knightTourPath = knightTourWarnsdorff(8); // Example for an 8x8 board
  if (knightTourPath != null) {
    print("Knight's Tour Path: $knightTourPath");
  } else {
    print("No Knight's Tour found.");
  }

  // 5. Randomized Approach
  List<int>? path5 = hamiltonianCycleRandomized(graph);
  print("\n5. Randomized Approach:");
  if (path5 != null) {
    print("Hamiltonian Cycle: $path5");
  } else {
    print("No Hamiltonian Cycle found.");
  }
}
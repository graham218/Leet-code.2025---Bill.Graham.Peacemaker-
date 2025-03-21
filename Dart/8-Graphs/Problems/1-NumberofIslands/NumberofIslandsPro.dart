// Advanced Solution for Number of Islands - 6 Different Approaches in Dart

import 'dart:collection';

class NumberOfIslands {
  late List<List<int>> grid;
  late int rows;
  late int cols;

  NumberOfIslands(this.grid) {
    rows = grid.length;
    cols = grid.isNotEmpty ? grid[0].length : 0;
  }

  // 1. Depth-First Search (DFS)
  void dfs(int r, int c) {
    if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 0) return;
    grid[r][c] = 0;
    for (var d in [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
      dfs(r + d[0], c + d[1]);
    }
  }

  int countIslandsDFS() {
    int count = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 1) {
          count++;
          dfs(r, c);
        }
      }
    }
    return count;
  }

  // 2. Breadth-First Search (BFS)
  int countIslandsBFS() {
    int count = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 1) {
          count++;
          Queue<List<int>> queue = Queue();
          queue.add([r, c]);
          grid[r][c] = 0;
          while (queue.isNotEmpty) {
            var node = queue.removeFirst();
            for (var d in [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
              int nr = node[0] + d[0], nc = node[1] + d[1];
              if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == 1) {
                queue.add([nr, nc]);
                grid[nr][nc] = 0;
              }
            }
          }
        }
      }
    }
    return count;
  }

  // 3. Union-Find (Disjoint Set Union - DSU)
  class DSU {
  late List<int> parent;
  late List<int> rank;

  DSU(int n) {
  parent = List.generate(n, (i) => i);
  rank = List.filled(n, 1);
  }

  int find(int x) {
  if (parent[x] != x) {
  parent[x] = find(parent[x]);
  }
  return parent[x];
  }

  void union(int x, int y) {
  int rootX = find(x);
  int rootY = find(y);
  if (rootX != rootY) {
  if (rank[rootX] > rank[rootY]) {
  parent[rootY] = rootX;
  } else if (rank[rootX] < rank[rootY]) {
  parent[rootX] = rootY;
  } else {
  parent[rootY] = rootX;
  rank[rootX]++;
  }
  }
  }
  }

  int countIslandsDSU() {
  DSU dsu = DSU(rows * cols);
  int count = 0;
  for (int r = 0; r < rows; r++) {
  for (int c = 0; c < cols; c++) {
  if (grid[r][c] == 1) {
  count++;
  for (var d in [[1, 0], [0, 1]]) {
  int nr = r + d[0], nc = c + d[1];
  if (nr < rows && nc < cols && grid[nr][nc] == 1) {
  dsu.union(r * cols + c, nr * cols + nc);
  }
  }
  }
  }
  }
  return count;
  }

  // 4. Iterative DFS
  int countIslandsIterativeDFS() {
  int count = 0;
  for (int r = 0; r < rows; r++) {
  for (int c = 0; c < cols; c++) {
  if (grid[r][c] == 1) {
  count++;
  List<List<int>> stack = [[r, c]];
  grid[r][c] = 0;
  while (stack.isNotEmpty) {
  var node = stack.removeLast();
  for (var d in [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
  int nr = node[0] + d[0], nc = node[1] + d[1];
  if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == 1) {
  stack.add([nr, nc]);
  grid[nr][nc] = 0;
  }
  }
  }
  }
  }
  }
  return count;
  }

  // 5. Counting Components using Adjacency List
  int countIslandsAdjacencyList() {
  Map<int, List<int>> adj = {};
  for (int r = 0; r < rows; r++) {
  for (int c = 0; c < cols; c++) {
  if (grid[r][c] == 1) {
  int id = r * cols + c;
  adj[id] = [];
  for (var d in [[1, 0], [0, 1], [-1, 0], [0, -1]]) {
  int nr = r + d[0], nc = c + d[1];
  if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == 1) {
  adj[id]!.add(nr * cols + nc);
  }
  }
  }
  }
  }
  return adj.keys.length;
  }
}

void main() {
  List<List<int>> grid = [
    [1, 1, 0, 0, 0],
    [1, 1, 0, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 1]
  ];

  NumberOfIslands solver = NumberOfIslands(grid);

  print("Number of Islands using DFS: ${solver.countIslandsDFS()}");
  print("Number of Islands using BFS: ${solver.countIslandsBFS()}");
  print("Number of Islands using DSU: ${solver.countIslandsDSU()}");
  print("Number of Islands using Iterative DFS: ${solver.countIslandsIterativeDFS()}");
  print("Number of Islands using Adjacency List: ${solver.countIslandsAdjacencyList()}");
}

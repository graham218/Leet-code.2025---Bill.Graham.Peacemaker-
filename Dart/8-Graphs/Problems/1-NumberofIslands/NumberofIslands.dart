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
  void _dfs(int r, int c) {
    if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 0) return;
    grid[r][c] = 0;
    _dfs(r + 1, c);
    _dfs(r - 1, c);
    _dfs(r, c + 1);
    _dfs(r, c - 1);
  }

  int countIslandsDFS() {
    int count = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 1) {
          count++;
          _dfs(r, c);
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
            int row = node[0], col = node[1];
            for (var d in [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
              int nr = row + d[0], nc = col + d[1];
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
  int countIslandsDSU() {
    if (rows == 0) return 0;
    DSU dsu = DSU(rows * cols);
    int count = 0;

    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 1) {
          count++;
          int index = r * cols + c;
          for (var d in [[1, 0], [0, 1]]) {
            int nr = r + d[0], nc = c + d[1];
            if (nr < rows && nc < cols && grid[nr][nc] == 1) {
              dsu.union(index, nr * cols + nc);
            }
          }
        }
      }
    }
    return dsu.getCount();
  }

  // 4. Iterative DFS
  int countIslandsIterativeDFS() {
    int count = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 1) {
          count++;
          List<List<int>> stack = [];
          stack.add([r, c]);
          grid[r][c] = 0;
          while (stack.isNotEmpty) {
            var node = stack.removeLast();
            int row = node[0], col = node[1];
            for (var d in [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
              int nr = row + d[0], nc = col + d[1];
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
}

class DSU {
  late List<int> parent;
  late List<int> rank;
  late int count;

  DSU(int n) {
    parent = List.generate(n, (i) => i);
    rank = List.filled(n, 1);
    count = n;
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
      count--;
    }
  }

  int getCount() {
    return count;
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
}
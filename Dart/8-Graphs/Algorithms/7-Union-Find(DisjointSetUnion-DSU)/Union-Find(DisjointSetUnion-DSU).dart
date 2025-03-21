// Union-Find (Disjoint Set Union - DSU) Implementations in Dart
// This code includes five different approaches with real-world applications

class DSU {
  late List<int> parent; // Parent array to store the parent of each element
  late List<int> rank; // Rank array to store the rank of each set (for union by rank)

  DSU(int n) {
    // Initialize parent array: each element is its own parent initially
    parent = List.generate(n, (i) => i);
    // Initialize rank array: all sets have rank 1 initially
    rank = List.filled(n, 1);
  }

  // 1. Standard Union-Find with Path Compression
  int find(int x) {
    // If x is not its own parent, recursively find its parent with path compression
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // Path compression: update parent of x to root
    }
    return parent[x]; // Return the root (parent) of x
  }

  void union(int x, int y) {
    // Find the root (parent) of x and y
    int rootX = find(x);
    int rootY = find(y);
    // If x and y have different roots, union them
    if (rootX != rootY) {
      parent[rootX] = rootY; // Make rootY the parent of rootX
    }
  }

  // 2. Union by Rank Optimization
  void unionByRank(int x, int y) {
    // Find the root (parent) of x and y
    int rootX = find(x);
    int rootY = find(y);
    // If x and y have different roots, union them
    if (rootX != rootY) {
      // Union by rank: attach smaller rank tree to larger rank tree
      if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX; // Make rootX the parent of rootY
      } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY; // Make rootY the parent of rootX
      } else {
        parent[rootY] = rootX; // Make rootX the parent of rootY (arbitrary choice)
        rank[rootX]++; // Increment the rank of rootX
      }
    }
  }

  // 3. Detect Cycle in an Undirected Graph using DSU
  bool hasCycle(List<List<int>> edges) {
    // Iterate through all edges
    for (var edge in edges) {
      int u = edge[0], v = edge[1]; // Get the vertices of the edge
      // If u and v have the same root, they form a cycle
      if (find(u) == find(v)) return true;
      union(u, v); // Union the vertices
    }
    return false; // No cycle detected
  }

  // 4. Connected Components Counting
  int countComponents(int n, List<List<int>> edges) {
    // Union all connected vertices
    for (var edge in edges) {
      union(edge[0], edge[1]);
    }
    // Use a set to store unique roots (parents)
    Set<int> uniqueParents = {};
    // Iterate through all vertices and add their roots to the set
    for (int i = 0; i < n; i++) {
      uniqueParents.add(find(i));
    }
    return uniqueParents.length; // Return the number of unique roots (connected components)
  }

  // 5. Kruskal’s Algorithm for Minimum Spanning Tree
  int kruskalMST(List<List<int>> edges, int n) {
    // Sort edges by weight in ascending order
    edges.sort((a, b) => a[2] - b[2]);
    int mstWeight = 0; // Initialize minimum spanning tree weight to 0
    // Iterate through all edges
    for (var edge in edges) {
      int u = edge[0], v = edge[1], w = edge[2]; // Get vertices and weight of the edge
      // If u and v have different roots, they don't form a cycle, so add the edge to MST
      if (find(u) != find(v)) {
        union(u, v); // Union the vertices
        mstWeight += w; // Add the weight of the edge to MST weight
      }
    }
    return mstWeight; // Return the minimum spanning tree weight
  }
}

void main() {
  DSU dsu = DSU(6); // Create a DSU with 6 elements
  List<List<int>> edges = [
    [0, 1],
    [1, 2],
    [2, 3],
    [3, 4],
    [4, 5]
  ];

  print("Cycle Detection: ${dsu.hasCycle(edges)}"); // Check for cycles
  print("Connected Components: ${dsu.countComponents(6, edges)}"); // Count connected components

  List<List<int>> weightedEdges = [
    [0, 1, 4],
    [1, 2, 2],
    [2, 3, 3],
    [3, 4, 5],
    [4, 5, 6]
  ];
  print("Minimum Spanning Tree Weight: ${dsu.kruskalMST(weightedEdges, 6)}"); // Find MST weight
}
// Advanced Union-Find (Disjoint Set Union - DSU) Implementations in Dart
// This code includes six different approaches with real-world applications

class DSU {
  late List<int> parent, rank, size; // Parent, rank, and size arrays

  DSU(int n) {
    // Initialize parent: each element is its own parent initially
    parent = List.generate(n, (i) => i);
    // Initialize rank: all ranks are 0 initially
    rank = List.filled(n, 0);
    // Initialize size: all sizes are 1 initially
    size = List.filled(n, 1);
  }

  // 1. Basic Union-Find (Path Compression)
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
      parent[rootY] = rootX; // Make rootX the parent of rootY (basic union)
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

  // 3. Union by Size Optimization
  void unionBySize(int x, int y) {
    // Find the root (parent) of x and y
    int rootX = find(x);
    int rootY = find(y);
    // If x and y have different roots, union them
    if (rootX != rootY) {
      // Union by size: attach smaller size tree to larger size tree
      if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX; // Make rootX the parent of rootY
        size[rootX] += size[rootY]; // Update size of rootX
      } else {
        parent[rootX] = rootY; // Make rootY the parent of rootX
        size[rootY] += size[rootX]; // Update size of rootY
      }
    }
  }

  // 4. Connected Components Count (Real-world: Social Networks)
  int countComponents(int n) {
    // Use a set to store unique roots (connected components)
    Set<int> components = {};
    // Iterate through all vertices and add their roots to the set
    for (int i = 0; i < n; i++) {
      components.add(find(i));
    }
    return components.length; // Return the number of unique roots (connected components)
  }

  // 5. Cycle Detection in an Undirected Graph
  bool isCycle(List<List<int>> edges) {
    // Iterate through all edges
    for (var edge in edges) {
      int u = edge[0], v = edge[1]; // Get the vertices of the edge
      // If u and v have the same root, they form a cycle
      if (find(u) == find(v)) return true;
      union(u, v); // Union the vertices
    }
    return false; // No cycle detected
  }

  // 6. Kruskal’s Algorithm for Minimum Spanning Tree (MST)
  int kruskalMST(int n, List<List<int>> edges) {
    // Sort edges by weight in ascending order
    edges.sort((a, b) => a[2].compareTo(b[2])); // Sort edges by weight
    int mstWeight = 0; // Initialize minimum spanning tree weight to 0
    // Iterate through all edges
    for (var edge in edges) {
      int u = edge[0], v = edge[1], weight = edge[2]; // Get vertices and weight of the edge
      // If u and v have different roots, they don't form a cycle, so add the edge to MST
      if (find(u) != find(v)) {
        unionByRank(u, v); // Union the vertices (using union by rank optimization)
        mstWeight += weight; // Add the weight of the edge to MST weight
      }
    }
    return mstWeight; // Return the minimum spanning tree weight
  }
}

void main() {
  int n = 6;
  DSU dsu = DSU(n);

  print("\nUnion-Find (Basic Path Compression):");
  dsu.union(0, 1);
  dsu.union(1, 2);
  print("Parent of 2: ${dsu.find(2)}");

  print("\nUnion by Rank:");
  dsu.unionByRank(3, 4);
  dsu.unionByRank(4, 5);
  print("Parent of 5: ${dsu.find(5)}");

  print("\nUnion by Size:");
  dsu.unionBySize(0, 3);
  print("Parent of 3: ${dsu.find(3)}");

  print("\nConnected Components:");
  print("Number of components: ${dsu.countComponents(n)}");

  print("\nCycle Detection:");
  List<List<int>> edges = [
    [0, 1],
    [1, 2],
    [2, 0],
    [3, 4]
  ];
  print("Graph has cycle: ${dsu.isCycle(edges)}");

  print("\nKruskal's MST:");
  List<List<int>> weightedEdges = [
    [0, 1, 4],
    [1, 2, 1],
    [2, 3, 3],
    [3, 4, 2],
    [4, 5, 5],
    [1, 5, 7]
  ];
  print("Minimum Spanning Tree Weight: ${dsu.kruskalMST(n, weightedEdges)}");
}
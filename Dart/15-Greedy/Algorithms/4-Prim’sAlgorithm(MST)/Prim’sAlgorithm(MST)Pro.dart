import 'dart:collection'; // Import the dart:collection library for using data structures like SplayTreeSet.
import 'dart:math'; // Import the dart:math library for using mathematical functions.

void main() {
  print("Prim's Algorithm - Minimum Spanning Tree\n"); // Print a title for the program.

  // Sample graph data represented as an adjacency matrix.
  // 0 represents no edge between vertices.  Non-zero values are edge weights.
  final adjacencyMatrix = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0],
  ];

  // Sample graph data represented as an adjacency list.
  // Each inner list represents the neighbors of a vertex and the edge weights.
  final adjacencyList = [
    [ [1, 2], [3, 6] ],       // 0:  Edges to 1 with weight 2, and 3 with weight 6.
    [ [0, 2], [2, 3], [4, 5] ], // 1
    [ [1, 3], [4, 7] ],       // 2
    [ [0, 6], [1, 8], [4, 9] ], // 3
    [ [1, 5], [2, 7], [3, 9] ], // 4
  ];

  // Sample graph data represented as a list of Edge objects.
  final edges = [
    Edge(0, 1, 2), // Edge from vertex 0 to 1 with weight 2.
    Edge(0, 3, 6),
    Edge(1, 2, 3),
    Edge(1, 4, 5),
    Edge(2, 4, 7),
    Edge(3, 4, 9),
  ];

  final int numberOfVertices = 5; // Number of vertices in the graph.  Used in a couple of the approaches.

  // Run and print the output of each approach to Prim's algorithm.
  print("Approach 1: Adjacency Matrix");
  primMSTMatrix(adjacencyMatrix); // Call the function that uses adjacency matrix.

  print("\nApproach 2: Adjacency List with Priority Queue");
  primMSTList(adjacencyList); // Call the function that uses adjacency list.

  print("\nApproach 3: Edge Class with Custom Comparator");
  primMSTEdges(edges, numberOfVertices); // Call the function that uses the Edge class.

  print("\nApproach 4: Union-Find (Kruskal's-like)");
  primLikeKruskal(List.from(edges), numberOfVertices); // Call the Union-Find approach.  Pass a copy to avoid modifying original.

  print("\nApproach 5: Optimized with Indexed Priority Queue");
  primMSTOptimized(adjacencyList);
}

// Edge class: Represents an edge in the graph with source, destination, and weight.
// Implements Comparable to allow sorting edges by weight.
class Edge implements Comparable<Edge> {
  final int src, dest, weight; // Source, destination vertices, and edge weight.

  Edge(this.src, this.dest, this.weight); // Constructor for the Edge class.

  @override
  int compareTo(Edge other) => weight.compareTo(other.weight); // Compare edges based on their weights.

  @override
  String toString() => '($src-$dest: $weight)'; // Provide a string representation of the edge.
}

// Subset class: Used for the Union-Find data structure (used in primLikeKruskal).
// Represents a subset of vertices.
class Subset {
  int parent, rank; // parent: the parent node in the subset tree, rank: used for optimization.

  Subset(this.parent, this.rank); // Constructor for the Subset class.
}

// IPair class:  Represents a pair of integers, used to store key and vertex for priority queue.
// Implements Comparable to allow sorting pairs based on the first value (key).
class IPair implements Comparable<IPair> {
  final int first, second; // first: key value, second: vertex number

  IPair(this.first, this.second); // Constructor.

  @override
  int compareTo(IPair other) => first.compareTo(other.first); // Compare based on the 'first' value (the key).

  @override
  String toString() => '($first, $second)';
}

// Approach 1: Prim's Algorithm using Adjacency Matrix.
void primMSTMatrix(List<List<int>> graph) {
  int V = graph.length; // Number of vertices in the graph.
  List<int> parent = List.filled(V, 0); // Array to store the parent of each vertex in the MST.
  List<int> key = List.filled(V, 0x7fffffff); // Array to store the minimum weight edge for each vertex.  0x7fffffff is max int.
  List<bool> mstSet = List.filled(V, false); // Array to track vertices included in the MST.

  key[0] = 0; // Start with the first vertex, key is 0.
  parent[0] = -1; // Root node has no parent.

  // Iterate V-1 times (number of edges in a MST is V-1).
  for (int count = 0; count < V - 1; count++) {
    int u = minKey(key, mstSet); // Find the vertex with the minimum key value (min weight edge)
    mstSet[u] = true; // Include the vertex in the MST.

    // Update the key values of the adjacent vertices of 'u'.
    for (int v = 0; v < V; v++) {
      // graph[u][v] != 0: There is an edge between u and v.
      // !mstSet[v]: v is not yet included in MST
      // graph[u][v] < key[v]:  Weight of edge (u,v) is less than current key of v.
      if (graph[u][v] != 0 && !mstSet[v] && graph[u][v] < key[v]) {
        parent[v] = u; // Update parent of v.
        key[v] = graph[u][v]; // Update key of v.
      }
    }
  }

  printMSTMatrix(parent, graph); // Print the constructed MST.
}

// Helper function to find the vertex with the minimum key value
int minKey(List<int> key, List<bool> mstSet) {
  int min = 0x7fffffff, minIndex = -1; // Initialize min and minIndex.

  for (int v = 0; v < key.length; v++) {
    if (!mstSet[v] && key[v] < min) { // If vertex v is not in MST and has smaller key.
      min = key[v]; // Update min.
      minIndex = v; // Update minIndex.
    }
  }

  return minIndex; // Return the index of the vertex with the minimum key value.
}

// Helper function to print the Minimum Spanning Tree from the adjacency matrix approach
void printMSTMatrix(List<int> parent, List<List<int>> graph) {
  print("Edge \tWeight");
  for (int i = 1; i < graph.length; i++) {
    print("${parent[i]} - $i \t${graph[i][parent[i]]}"); // Print each edge and its weight.
  }
}

// Approach 2: Prim's Algorithm using Adjacency List and a Priority Queue (SplayTreeSet).
void primMSTList(List<List<List<int>>> graph) {
  int V = graph.length; // Number of vertices.
  List<int> parent = List.filled(V, -1); // Parent of each vertex in MST.
  List<int> key = List.filled(V, 0x7fffffff); // Key values for vertices.
  List<bool> inMST = List.filled(V, false); // Track vertices in MST.

  // Use SplayTreeSet as a priority queue.  Orders elements based on the second element of the list (which is the key).
  final pq = SplayTreeSet<List<int>>((a, b) => a[1].compareTo(b[1]));

  key[0] = 0; // Start at vertex 0.
  pq.add([0, 0]); // Add vertex 0 with key 0 to the priority queue.  List is [vertex, key].

  // While the priority queue is not empty.
  while (pq.isNotEmpty) {
    List<int> node = pq.first; // Get the vertex with the minimum key.
    pq.remove(node); // Remove it from the queue.
    int u = node[0]; // Get the vertex.
    inMST[u] = true; // Mark it as in MST.

    // Iterate through the neighbors of vertex u.
    for (List<int> neighbor in graph[u]) {
      int v = neighbor[0]; // Get the neighbor vertex.
      int weight = neighbor[1]; // Get the weight of the edge.

      // If v is not in MST and the weight is less than its current key.
      if (!inMST[v] && weight < key[v]) {
        // Remove old key if it exists.  SplayTreeSet doesn't have a direct update.
        pq.removeWhere((element) => element[0] == v);

        key[v] = weight; // Update the key of v.
        parent[v] = u; // Update the parent of v.
        pq.add([v, key[v]]); // Add v with its new key to the priority queue.
      }
    }
  }

  printMSTList(parent, graph); // Print the MST.
}

// Helper function to print the MST from the adjacency list approach.
void printMSTList(List<int> parent, List<List<List<int>>> graph) {
  print("Edge \tWeight");
  for (int i = 1; i < graph.length; i++) {
    int weight = 0;
    // Find the weight of the edge between i and its parent.
    for (List<int> neighbor in graph[i]) {
      if (neighbor[0] == parent[i]) {
        weight = neighbor[1];
        break;
      }
    }
    print("${parent[i]} - $i \t$weight");
  }
}

// Approach 3: Prim's Algorithm using Edge Class and Custom Comparator.
void primMSTEdges(List<Edge> edges, int V) {
  List<Edge> mst = []; // List to store the edges of the MST.
  List<bool> inMST = List.filled(V, false); // Track vertices in MST.
  final pq = SplayTreeSet<Edge>(); // Priority queue for edges, sorted by weight.

  inMST[0] = true; // Start with vertex 0 in the MST.
  // Add all edges starting from vertex 0 to the priority queue.
  for (Edge edge in edges) {
    if (edge.src == 0) {
      pq.add(edge);
    }
  }

  // While the priority queue is not empty and the MST has less than V-1 edges.
  while (pq.isNotEmpty && mst.length < V - 1) {
    Edge edge = pq.first; // Get the edge with the minimum weight.
    pq.remove(edge);      // Remove it from the queue.

    if (inMST[edge.dest]) continue; // If the destination vertex is already in MST, skip.

    mst.add(edge);           // Add the edge to the MST.
    inMST[edge.dest] = true; // Mark the destination vertex as in MST.

    // Add edges from the newly added vertex to the priority queue.
    for (Edge nextEdge in edges) {
      if (nextEdge.src == edge.dest && !inMST[nextEdge.dest]) {
        pq.add(nextEdge);
      }
    }
  }

  printMSTEdges(mst); // Print the MST.
}

// Approach 4: Prim's Algorithm using Union-Find (Disjoint Set) data structure.
// This approach has similarities to Kruskal's algorithm but is modified to work like Prim's.
void primLikeKruskal(List<Edge> edges, int V) {
  edges.sort(); // Sort the edges by weight (ascending order).

  // Create subsets for each vertex.
  List<Subset> subsets = List.generate(V, (i) => Subset(i, 0));
  List<Edge> mst = []; // List to store the edges of the MST.

  int e = 0; // Number of edges in the MST.
  int i = 0; // Index to iterate through the sorted edges.

  // Iterate until we have V-1 edges in MST or we have processed all edges.
  while (e < V - 1 && i < edges.length) {
    Edge nextEdge = edges[i++]; // Get the next edge.

    int x = find(subsets, nextEdge.src); // Find the subset of the source vertex.
    int y = find(subsets, nextEdge.dest); // Find the subset of the destination vertex.

    // If the source and destination vertices are in different subsets,
    // it means adding this edge will not create a cycle.
    if (x != y) {
      mst.add(nextEdge); // Add the edge to the MST.
      union(subsets, x, y); // Merge the subsets of the source and destination vertices.
      e++; // Increment the edge count.
    }
  }

  printMSTEdges(mst); // Print the MST.
}

// Find function for Union-Find: Finds the root of the subset containing vertex i.
int find(List<Subset> subsets, int i) {
  // Path compression:  Makes the parent of each node in the path point to the root.
  if (subsets[i].parent != i) {
    subsets[i].parent = find(subsets, subsets[i].parent);
  }
  return subsets[i].parent; // Return the root of the subset.
}

// Union function for Union-Find: Merges the subsets containing vertices x and y.
void union(List<Subset> subsets, int x, int y) {
  int xroot = find(subsets, x); // Find the root of the subset containing x.
  int yroot = find(subsets, y); // Find the root of the subset containing y.

  // Union by rank:  Attach the smaller rank tree under the root of the higher rank tree.
  if (subsets[xroot].rank < subsets[yroot].rank) {
    subsets[xroot].parent = yroot;
  } else if (subsets[xroot].rank > subsets[yroot].rank) {
    subsets[yroot].parent = xroot;
  } else {
    // If ranks are the same, then make one as root and increment its rank.
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

// Helper function to print the MST edges.  Used by approaches 3 and 4.
void printMSTEdges(List<Edge> mst) {
  print("Edge \tWeight");
  for (Edge edge in mst) {
    print("${edge.src} - ${edge.dest} \t${edge.weight}");
  }
}

// Approach 5: Optimized Prim's Algorithm using Indexed Priority Queue (SplayTreeSet).
void primMSTOptimized(List<List<List<int>>> graph) {
  int V = graph.length;
  List<int> parent = List.filled(V, -1);
  List<int> key = List.filled(V, 0x7fffffff);
  List<bool> inMST = List.filled(V, false);

  // Use SplayTreeSet as an indexed priority queue.
  final pq = SplayTreeSet<IPair>();

  key[0] = 0;
  pq.add(IPair(0, 0)); // Add the starting vertex with key 0.

  while (pq.isNotEmpty) {
    IPair pair = pq.first;
    pq.remove(pair);
    int u = pair.second; // Get the vertex.

    if (inMST[u]) continue; // If already in MST, skip.
    inMST[u] = true;

    for (List<int> neighbor in graph[u]) {
      int v = neighbor[0];
      int weight = neighbor[1];

      if (!inMST[v] && weight < key[v]) {
        pq.removeWhere((element) => element.second == v); // Remove old key.
        key[v] = weight;
        parent[v] = u;
        pq.add(IPair(key[v], v)); // Add with new key.
      }
    }
  }

  printMSTOptimized(parent, key);
}

// Helper to print the optimized MST.
void printMSTOptimized(List<int> parent, List<int> key) {
  print("Edge \tWeight");
  for (int i = 1; i < parent.length; i++) {
    print("${parent[i]} - $i \t${key[i]}");
  }
}

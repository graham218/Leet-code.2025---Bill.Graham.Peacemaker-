import 'dart:collection';
import 'package:collection/collection.dart'; // Import for HeapPriorityQueue

// Class to represent an edge in the graph
class Edge {
  int source;
  int destination;
  int weight;
  String? type; // Added for real-world examples

  Edge(this.source, this.destination, this.weight, {this.type});

  @override
  String toString() {
    return 'Edge{source: $source, destination: $destination, weight: $weight, type: $type}';
  }
}

// Function to find the parent of a node (with path compression)
int find(List<int> parent, int i) {
  if (parent[i] == i) return i;
  return parent[i] = find(parent, parent[i]); // Path compression
}

// Function to perform union of two sets (using rank)
void union(List<int> parent, List<int> rank, int x, int y) {
  int xRoot = find(parent, x);
  int yRoot = find(parent, y);

  if (rank[xRoot] < rank[yRoot]) {
    parent[xRoot] = yRoot;
  } else if (rank[xRoot] > rank[yRoot]) {
    parent[yRoot] = xRoot;
  } else {
    parent[yRoot] = xRoot;
    rank[xRoot]++;
  }
}

// 1. Basic Kruskal's Algorithm
List<Edge> kruskalMST(List<Edge> edges, int numVertices) {
  edges.sort((a, b) => a.weight.compareTo(b.weight));
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);
  List<Edge> minimumSpanningTree = [];
  int edgeCount = 0;

  for (Edge edge in edges) {
    int sourceParent = find(parent, edge.source);
    int destinationParent = find(parent, edge.destination);
    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      union(parent, rank, sourceParent, destinationParent);
      edgeCount++;
    }
    if (edgeCount == numVertices - 1) break;
  }
  return minimumSpanningTree;
}

// 2. Kruskal's Algorithm using a Priority Queue
List<Edge> kruskalMSTPriorityQueue(List<Edge> edges, int numVertices) {
  final PriorityQueue<Edge> pq = HeapPriorityQueue((a, b) => a.weight.compareTo(b.weight));
  pq.addAll(edges);

  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);
  List<Edge> minimumSpanningTree = [];
  int edgeCount = 0;

  while (pq.isNotEmpty) {
    Edge edge = pq.removeFirst();
    int sourceParent = find(parent, edge.source);
    int destinationParent = find(parent, edge.destination);
    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      union(parent, rank, sourceParent, destinationParent);
      edgeCount++;
    }
    if (edgeCount == numVertices - 1) break;
  }
  return minimumSpanningTree;
}

// 3. Kruskal's Algorithm with Edge Types (Real-World Application)
List<Edge> kruskalMSTWithType(List<Edge> edges, int numVertices,
    {String requiredType = 'all'}) {
  edges.sort((a, b) => a.weight.compareTo(b.weight));
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);
  List<Edge> minimumSpanningTree = [];
  int edgeCount = 0;

  for (Edge edge in edges) {
    int sourceParent = find(parent, edge.source);
    int destinationParent = find(parent, edge.destination);
    // Filter by edge type if required
    if (sourceParent != destinationParent &&
        (requiredType == 'all' || edge.type == requiredType)) {
      minimumSpanningTree.add(edge);
      union(parent, rank, sourceParent, destinationParent);
      edgeCount++;
    }
    if (edgeCount == numVertices - 1) break;
  }
  return minimumSpanningTree;
}

// 4. Kruskal's Algorithm with Capacity Constraints (Real-World)
List<Edge> kruskalMSTWithCapacity(List<Edge> edges, int numVertices,
    Map<int, int> capacity) {
  edges.sort((a, b) => a.weight.compareTo(b.weight));
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);
  List<Edge> minimumSpanningTree = [];
  int edgeCount = 0;
  Map<int, int> currentLoad = {}; // Track load on each node

  for (Edge edge in edges) {
    int sourceParent = find(parent, edge.source);
    int destinationParent = find(parent, edge.destination);

    if (sourceParent != destinationParent) {
      // Check capacity constraints
      int sourceLoad = currentLoad[edge.source] ?? 0;
      int destinationLoad = currentLoad[edge.destination] ?? 0;
      if (sourceLoad + edge.weight <= (capacity[edge.source] ?? 100000) && //Assume 100000 is max capacity if not provided.
          destinationLoad + edge.weight <= (capacity[edge.destination] ?? 100000)) {
        minimumSpanningTree.add(edge);
        union(parent, rank, sourceParent, destinationParent);
        edgeCount++;
        // Update current loads
        currentLoad[edge.source] = sourceLoad + edge.weight;
        currentLoad[edge.destination] = destinationLoad + edge.weight;
      }
    }
    if (edgeCount == numVertices - 1) break;
  }
  return minimumSpanningTree;
}

void main() {
  // Example graph:
  // (0)--(1)--(2)
  //  |    |    |
  // (3)--(4)--(5)
  List<Edge> edges = [
    Edge(0, 1, 4, type: 'cable'),
    Edge(0, 3, 8, type: 'pipe'),
    Edge(1, 2, 9, type: 'cable'),
    Edge(1, 4, 2, type: 'cable'),
    Edge(2, 5, 5, type: 'cable'),
    Edge(3, 4, 3, type: 'pipe'),
    Edge(3, 6, 6, type: 'pipe'),
    Edge(4, 5, 7, type: 'cable'),
    Edge(4, 6, 1, type: 'pipe'),
    Edge(5, 6, 8, type: 'cable'),
  ];
  int numVertices = 7;

  // 1. Basic Kruskal's
  print("1. Basic Kruskal's MST:");
  List<Edge> mst1 = kruskalMST(edges, numVertices);
  mst1.forEach(print);

  // 2. Kruskal's with Priority Queue
  print("\n2. Kruskal's MST with Priority Queue:");
  List<Edge> mst2 = kruskalMSTPriorityQueue(edges, numVertices);
  mst2.forEach(print);

  // 3. Kruskal's with Edge Types
  print("\n3. Kruskal's MST with Cable Edges:");
  List<Edge> mst3 = kruskalMSTWithType(edges, numVertices, requiredType: 'cable');
  mst3.forEach(print);

  // 4. Kruskal's with Capacity Constraints
  print("\n4. Kruskal's MST with Capacity Constraints:");
  Map<int, int> capacity = {
    0: 10,
    1: 15,
    2: 20,
    3: 12,
    4: 18,
    5: 25,
    6: 30
  }; // Example capacities
  List<Edge> mst4 = kruskalMSTWithCapacity(edges, numVertices, capacity);
  mst4.forEach(print);
}


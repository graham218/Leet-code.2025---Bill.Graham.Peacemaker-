import 'dart:collection';


// Define a class to represent an edge in the graph
class Edge {
  int source;
  int destination;
  int weight;

  Edge(this.source, this.destination, this.weight);

  // Override the == operator and hashCode for proper comparison and usage in sets/maps
  @override
  bool operator ==(Object other) {
    if (identical(this, other)) return true;
    return other is Edge &&
        source == other.source &&
        destination == other.destination &&
        weight == other.weight;
  }

  @override
  int get hashCode => source.hashCode ^ destination.hashCode ^ weight.hashCode;

  @override
  String toString() {
    return 'Edge{source: $source, destination: $destination, weight: $weight}';
  }
}

// Helper function to find the parent of a node in the disjoint set
int findParent(List<int> parent, int i) {
  if (parent[i] == i) {
    return i;
  }
  return parent[i] = findParent(parent, parent[i]); // Path compression
}

// Helper function to unite two sets
void unionSets(List<int> parent, List<int> rank, int u, int v) { // Added List<int> rank
  int rootU = findParent(parent, u);
  int rootV = findParent(parent, v);

  // Attach smaller rank tree under root of high rank tree
  // (Union by Rank)
  if (rank[rootU] < rank[rootV]) {
    parent[rootU] = rootV;
  } else if (rank[rootU] > rank[rootV]) {
    parent[rootV] = rootU;
  } else {
    // If ranks are the same, then make one as root and
    // increment its rank by one
    parent[rootV] = rootU;
    rank[rootU]++;
  }
}

// 1. Kruskal's Algorithm using List and sorting
List<Edge> kruskalMSTListSort(List<Edge> edges, int numVertices) {
  // Sort the edges by weight in ascending order
  edges.sort((a, b) => a.weight.compareTo(b.weight));

  List<Edge> minimumSpanningTree = [];
  List<int> parent = List.generate(numVertices, (i) => i); // Initialize parent array for disjoint set
  List<int> rank = List.generate(numVertices, (i) => 0);    // Initialize rank array for union by rank

  for (Edge edge in edges) {
    int sourceParent = findParent(parent, edge.source);
    int destinationParent = findParent(parent, edge.destination);

    // If including this edge does not cause a cycle, include it
    // in the result and increment the index of result for next edge
    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      unionSets(parent, rank, sourceParent, destinationParent);
    }
  }
  return minimumSpanningTree;
}

// 2. Kruskal's Algorithm using a basic Priority Queue (Min Heap) implementation for DartPad
List<Edge> kruskalMSTPriorityQueue(List<Edge> edges, int numVertices) {
  // Use a priority queue (min heap) to store edges, automatically sorted by weight
  final List<Edge> priorityQueue = [...edges]; // Create a copy to avoid modifying original
  priorityQueue.sort((a, b) => a.weight.compareTo(b.weight)); // Sort initially

  List<Edge> minimumSpanningTree = [];
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);

  while (priorityQueue.isNotEmpty) {
    Edge edge = priorityQueue.removeAt(0); //remove first instead of removeFirst
    int sourceParent = findParent(parent, edge.source);
    int destinationParent = findParent(parent, edge.destination);

    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      unionSets(parent, rank, sourceParent, destinationParent);
    }
  }
  return minimumSpanningTree;
}

// 3. Kruskal's Algorithm using Set for Edges and sorting
List<Edge> kruskalMSTSetSort(Set<Edge> edges, int numVertices) {
  // Convert the set to a list and sort it.  Sets are unordered, so sorting is necessary.
  List<Edge> sortedEdges = edges.toList();
  sortedEdges.sort((a, b) => a.weight.compareTo(b.weight)); // Sort edges

  List<Edge> minimumSpanningTree = [];
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);

  for (Edge edge in sortedEdges) { // Use the sorted list
    int sourceParent = findParent(parent, edge.source);
    int destinationParent = findParent(parent, edge.destination);

    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      unionSets(parent, rank, sourceParent, destinationParent);
    }
  }
  return minimumSpanningTree;
}

// 4. Kruskal's Algorithm using Map for Edges (weight as key)
List<Edge> kruskalMSTMap(Map<int, List<Edge>> edgesByWeight, int numVertices) {
  // Get sorted keys (weights)
  List<int> sortedWeights = edgesByWeight.keys.toList()..sort();

  List<Edge> minimumSpanningTree = [];
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);

  for (int weight in sortedWeights) {
    for (Edge edge in edgesByWeight[weight]!) {
      int sourceParent = findParent(parent, edge.source);
      int destinationParent = findParent(parent, edge.destination);

      if (sourceParent != destinationParent) {
        minimumSpanningTree.add(edge);
        unionSets(parent, rank, sourceParent, destinationParent);
      }
    }
  }
  return minimumSpanningTree;
}

// 5. Kruskal's Algorithm using custom comparison function with sorted
List<Edge> kruskalMSTCustomCompare(List<Edge> edges, int numVertices) {
  // Sort edges using a custom comparison function.
  edges.sort((a, b) {
    if (a.weight != b.weight) {
      return a.weight.compareTo(b.weight);
    }
    // If weights are equal, you might want to compare source/destination for consistency
    if (a.source != b.source) {
      return a.source.compareTo(b.source);
    }
    return a.destination.compareTo(b.destination);
  });

  List<Edge> minimumSpanningTree = [];
  List<int> parent = List.generate(numVertices, (i) => i);
  List<int> rank = List.generate(numVertices, (i) => 0);

  for (Edge edge in edges) {
    int sourceParent = findParent(parent, edge.source);
    int destinationParent = findParent(parent, edge.destination);

    if (sourceParent != destinationParent) {
      minimumSpanningTree.add(edge);
      unionSets(parent, rank, sourceParent, destinationParent);
    }
  }
  return minimumSpanningTree;
}

void main() {
  // Example graph represented as a list of edges
  List<Edge> edges = [
    Edge(0, 1, 10),
    Edge(0, 2, 6),
    Edge(0, 3, 5),
    Edge(1, 3, 15),
    Edge(2, 3, 4),
  ];
  int numVertices = 4;

  // Example graph for the Map approach
  Map<int, List<Edge>> edgesByWeight = {};
  for (Edge edge in edges) {
    if (!edgesByWeight.containsKey(edge.weight)) {
      edgesByWeight[edge.weight] = [];
    }
    edgesByWeight[edge.weight]!.add(edge);
  }

  // Example graph represented as a set of edges
  Set<Edge> edgeSet = {
    Edge(0, 1, 10),
    Edge(0, 2, 6),
    Edge(0, 3, 5),
    Edge(1, 3, 15),
    Edge(2, 3, 4),
  };

  // 1. Kruskal's Algorithm using List and sorting
  List<Edge> mstListSort = kruskalMSTListSort(edges, numVertices);
  print('Kruskal MST (List Sort):');
  for (Edge edge in mstListSort) {
    print('${edge.source} - ${edge.destination} : ${edge.weight}');
  }

  // 2. Kruskal's Algorithm using Priority Queue (Min Heap)
  List<Edge> mstPriorityQueue = kruskalMSTPriorityQueue(edges, numVertices);
  print('\nKruskal MST (Priority Queue):');
  for (Edge edge in mstPriorityQueue) {
    print('${edge.source} - ${edge.destination} : ${edge.weight}');
  }

  // 3. Kruskal's Algorithm using Set for Edges
  List<Edge> mstSetSort = kruskalMSTSetSort(edgeSet, numVertices);
  print('\nKruskal MST (Set Sort):');
  for (Edge edge in mstSetSort) {
    print('${edge.source} - ${edge.destination} : ${edge.weight}');
  }

  // 4. Kruskal's Algorithm using Map for Edges (weight as key)
  List<Edge> mstMap = kruskalMSTMap(edgesByWeight, numVertices);
  print('\nKruskal MST (Map):');
  for (Edge edge in mstMap) {
    print('${edge.source} - ${edge.destination} : ${edge.weight}');
  }

  // 5. Kruskal's Algorithm using custom comparison
  List<Edge> mstCustomCompare = kruskalMSTCustomCompare(edges, numVertices);
  print('\nKruskal MST (Custom Compare):');
  for (Edge edge in mstCustomCompare) {
    print('${edge.source} - ${edge.destination} : ${edge.weight}');
  }
}

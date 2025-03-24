import 'package:collection/collection.dart'; // Import the collection package

class Edge {
  int to;
  int weight;

  Edge(this.to, this.weight);
}

class Node implements Comparable<Node> {
  int id;
  int distance;

  Node(this.id, this.distance);

  @override
  int compareTo(Node other) {
    return distance.compareTo(other.distance);
  }
}

List<int> dijkstra(List<List<Edge>> graph, int source) {
  int n = graph.length;
  List<int> distances = List.filled(n, 1 << 30); // Initialize distances to infinity
  distances[source] = 0;

  PriorityQueue<Node> pq = PriorityQueue<Node>();
  pq.add(Node(source, 0));

  while (pq.isNotEmpty) {
    Node node = pq.removeFirst();
    int u = node.id;

    if (node.distance > distances[u]) continue; // Skip if a better distance is already found

    for (Edge edge in graph[u]) {
      int v = edge.to;
      int alt = distances[u] + edge.weight;

      if (alt < distances[v]) {
        distances[v] = alt;
        pq.add(Node(v, alt));
      }
    }
  }

  return distances;
}

void main() {
  // Example graph represented as an adjacency list
  List<List<Edge>> graph = [
    [Edge(1, 4), Edge(2, 1)], // Node 0
    [Edge(3, 1)],             // Node 1
    [Edge(1, 2), Edge(3, 5)], // Node 2
    []                        // Node 3
  ];

  int source = 0;
  List<int> distances = dijkstra(graph, source);

  print("Shortest distances from node $source:");
  for (int i = 0; i < distances.length; i++) {
    print("Node $i: ${distances[i]}");
  }
}
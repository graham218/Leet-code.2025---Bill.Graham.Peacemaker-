import 'dart:collection';
import 'dart:math';

// Priority Queue (Min Heap) implementation for Dart
class PriorityQueue<T> {
  final List<T> _heap = [];
  final int Function(T, T) _compare;

  PriorityQueue(this._compare);

  bool get isEmpty => _heap.isEmpty;
  int get length => _heap.length;

  void push(T value) {
    _heap.add(value);
    _siftUp(_heap.length - 1);
  }

  T pop() {
    if (_heap.isEmpty) {
      throw StateError('Cannot pop from an empty priority queue');
    }
    _swap(0, _heap.length - 1);
    final value = _heap.removeLast();
    _siftDown(0);
    return value;
  }

  T peek() {
    if (_heap.isEmpty) {
      throw StateError('Cannot peek at an empty priority queue');
    }
    return _heap[0];
  }

  void _siftUp(int index) {
    while (index > 0) {
      final parent = (index - 1) ~/ 2;
      if (_compare(_heap[index], _heap[parent]) >= 0) {
        break;
      }
      _swap(index, parent);
      index = parent;
    }
  }

  void _siftDown(int index) {
    while (true) {
      final left = 2 * index + 1;
      final right = 2 * index + 2;
      var smallest = index;

      if (left < _heap.length && _compare(_heap[left], _heap[smallest]) < 0) {
        smallest = left;
      }
      if (right < _heap.length && _compare(_heap[right], _heap[smallest]) < 0) {
        smallest = right;
      }
      if (smallest == index) {
        break;
      }
      _swap(index, smallest);
      index = smallest;
    }
  }

  void _swap(int i, int j) {
    final temp = _heap[i];
    _heap[i] = _heap[j];
    _heap[j] = temp;
  }

  // Method to update the priority of an element.  This is a crucial
  // addition for Dijkstra's, allowing us to update distances in the queue.
  void updatePriority(T value, int newPriority) {
    int index = _heap.indexOf(value); //  Find the element.  Expensive in a heap!
    if (index == -1) return; // Element not found.

    // IMPORTANT:  We need to re-insert the element with the new priority.
    // Simplest way is to remove and re-add.  For efficiency, you *could*
    // try to sift up/down, but it's tricky to get right.
    _heap.removeAt(index);
    _heap.add(value); // Add it back, will be sifted.
    _siftUp(_heap.length -1); // Restore heap property
    _siftDown(_heap.length-1);
  }
}

// Edge class to represent connections between nodes with their weights.
class Edge {
  final int target;
  final int weight;

  Edge(this.target, this.weight);
}

// Node class to represent a node in the graph.  Not strictly needed, but
// can make the graph representation a bit clearer.
class Node {
  final int id;
  final List<Edge> edges = [];

  Node(this.id);

  void addEdge(int target, int weight) {
    edges.add(Edge(target, weight));
  }
}

// Main function to implement Dijkstra's algorithm.
Map<int, int> dijkstra(List<Node> graph, int startNode) {
  // 1. Initialize distances.  Use a large value (simulating infinity)
  //    for all nodes except the start node.
  final distances = {
    for (var i = 0; i < graph.length; i++) i: (i == startNode) ? 0 : 1 << 31,
  };

  // 2. Create the priority queue.  The queue stores nodes, and the
  //    priority is the distance to that node.  Dart doesn't have a
  //    built-in priority queue, so we use our custom implementation.
  final queue = PriorityQueue<(int, int)>((a, b) => a.$2.compareTo(b.$2)); // (nodeId, distance)
  queue.push((startNode, 0)); // Add the start node with distance 0.

  // 3. Main loop: continue as long as there are nodes in the queue.
  while (!queue.isEmpty) {
    // 3.1. Get the node with the smallest distance from the queue.
    final (currentNodeId, currentDistance) = queue.pop();

    // 3.2. If the current distance is already greater than the known
    //      shortest distance to this node, we can skip it.  This is an
    //      optimization that prevents revisiting nodes unnecessarily.
    if (currentDistance > distances[currentNodeId]!) {
      continue;
    }

    // 3.3. Iterate over the neighbors of the current node.
    final currentNode = graph[currentNodeId]; // Get the Node object
    for (final edge in currentNode.edges) {
      final neighborId = edge.target;
      final edgeWeight = edge.weight;

      // 3.4. Calculate the distance to the neighbor through the current node.
      final newDistance = currentDistance + edgeWeight;

      // 3.5. If the new distance is shorter than the previously known
      //      shortest distance to the neighbor, update the distance
      //      and add the neighbor to the queue.
      if (newDistance < distances[neighborId]!) {
        distances[neighborId] = newDistance;
        // Important:  Update or add.  updatePriority is added to PriorityQueue
        queue.push((neighborId, newDistance)); // Add with the new distance
      }
    }
  }

  // 4. Return the map of shortest distances from the start node to all other nodes.
  return distances;
}

void main() {
  // 1. Define the graph as a list of Node objects.  Each node stores its
  //    connections (edges) to other nodes with their respective weights.
  final List<Node> graph = [
    Node(0), // Node 0
    Node(1), // Node 1
    Node(2), // Node 2
    Node(3), // Node 3
    Node(4), // Node 4
    Node(5), // Node 5
  ];

  // 2. Add the edges to the graph.  This represents the connections
  //    between the nodes and the cost (weight) of traveling between them.
  graph[0].addEdge(1, 4); // 0 -> 1, weight 4
  graph[0].addEdge(2, 2); // 0 -> 2, weight 2
  graph[1].addEdge(2, 5); // 1 -> 2, weight 5
  graph[1].addEdge(3, 10); // 1 -> 3, weight 10
  graph[2].addEdge(3, 3); // 2 -> 3, weight 3
  graph[2].addEdge(4, 1); // 2 -> 4, weight 1
  graph[3].addEdge(5, 11); // 3 -> 5, weight 11
  graph[4].addEdge(3, 4); // 4 -> 3, weight 4
  graph[4].addEdge(5, 15); // 4 -> 5, weight 15

  // 3. Choose the starting node.  Dijkstra's algorithm calculates the
  //    shortest paths from this node to all other nodes in the graph.
  final startNode = 0;

  // 4. Run Dijkstra's algorithm.
  final shortestDistances = dijkstra(graph, startNode);

  // 5. Print the results.  Display the shortest distances from the
  //    starting node to each other node in the graph.
  print('Shortest distances from node $startNode:');
  shortestDistances.forEach((node, distance) {
    print('Node $node: ${distance == (1 << 31) ? 'Infinity' : distance}');
  });
}

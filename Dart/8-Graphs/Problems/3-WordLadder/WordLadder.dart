import 'dart:collection';
import 'dart:convert';

class GraphNode {
  int val;
  List<GraphNode> neighbors;

  GraphNode(this.val) : neighbors = [];
}

class CloneGraph {
  // 1. Depth-First Search (DFS) with Recursion
  GraphNode? cloneGraphDFS(GraphNode? node, Map<int, GraphNode> visited) {
    // If the node is null, return null (base case).
    if (node == null) return null;

    // If the node has already been visited, return its clone from the visited map.
    if (visited.containsKey(node.val)) return visited[node.val];

    // Create a new clone of the current node.
    GraphNode clone = GraphNode(node.val);

    // Add the clone to the visited map to mark it as visited.
    visited[node.val] = clone;

    // Recursively clone each neighbor and add it to the clone's neighbors list.
    for (var neighbor in node.neighbors) {
      clone.neighbors.add(cloneGraphDFS(neighbor, visited)!); // Consider null checks
    }

    // Return the cloned node.
    return clone;
  }

  // 2. Iterative Depth-First Search (DFS)
  GraphNode? cloneGraphIterativeDFS(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> visited = {};
    List<GraphNode> stack = [node]; // Use a stack for DFS traversal.
    visited[node.val] = GraphNode(node.val); // Create and mark the initial node as visited.

    while (stack.isNotEmpty) {
      GraphNode current = stack.removeLast(); // Get the last added node from the stack.
      for (var neighbor in current.neighbors) {
        if (!visited.containsKey(neighbor.val)) {
          // If the neighbor hasn't been visited, create a clone and add it to the stack and visited map.
          visited[neighbor.val] = GraphNode(neighbor.val);
          stack.add(neighbor);
        }
        // Add the cloned neighbor to the cloned current node's neighbors list.
        visited[current.val]!.neighbors.add(visited[neighbor.val]!); // Consider null checks
      }
    }
    return visited[node.val]; // Return the cloned starting node.
  }

  // 3. Breadth-First Search (BFS)
  GraphNode? cloneGraphBFS(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> visited = {};
    Queue<GraphNode> queue = Queue(); // Use a queue for BFS traversal.
    queue.add(node); // Add the starting node to the queue.
    visited[node.val] = GraphNode(node.val); // Create and mark the initial node as visited.

    while (queue.isNotEmpty) {
      GraphNode current = queue.removeFirst(); // Get the first added node from the queue.
      for (var neighbor in current.neighbors) {
        if (!visited.containsKey(neighbor.val)) {
          // If the neighbor hasn't been visited, create a clone and add it to the queue and visited map.
          visited[neighbor.val] = GraphNode(neighbor.val);
          queue.add(neighbor);
        }
        // Add the cloned neighbor to the cloned current node's neighbors list.
        visited[current.val]!.neighbors.add(visited[neighbor.val]!); // Consider null checks
      }
    }
    return visited[node.val]; // Return the cloned starting node.
  }

  // 4. Using Adjacency List
  Map<int, List<int>> buildAdjacencyList(GraphNode node) {
    Map<int, List<int>> adjList = {};
    Queue<GraphNode> queue = Queue();
    Set<int> visited = {};
    queue.add(node);

    while (queue.isNotEmpty) {
      GraphNode current = queue.removeFirst();
      if (visited.contains(current.val)) continue; // Skip if already visited.
      visited.add(current.val);
      adjList[current.val] = []; // Initialize the neighbor list for the current node.

      for (var neighbor in current.neighbors) {
        adjList[current.val]!.add(neighbor.val); // Add the neighbor's value to the current node's neighbor list.
        queue.add(neighbor); // Add the neighbor to the queue for further processing.
      }
    }
    return adjList;
  }

  // 5. Serialization and Deserialization
  String serialize(GraphNode? node) {
    if (node == null) return "";
    Map<int, List<int>> adjList = buildAdjacencyList(node); // Build the adjacency list.
    return jsonEncode(adjList); // Serialize the adjacency list to a JSON string.
  }

  GraphNode? deserialize(String data) {
    if (data.isEmpty) return null;
    Map<int, List<int>> adjList = Map<int, List<int>>.from(jsonDecode(data)); // Deserialize the JSON string to an adjacency list.
    Map<int, GraphNode> nodes = {}; // Map to store created nodes.

    // Create nodes based on the keys in the adjacency list.
    for (var key in adjList.keys) {
      nodes[key] = GraphNode(key);
    }

    // Connect the nodes based on the adjacency list.
    for (var key in adjList.keys) {
      for (var neighbor in adjList[key]!) {
        nodes[key]!.neighbors.add(nodes[neighbor]!); // Consider null checks
      }
    }
    return nodes[adjList.keys.first]; // Return the first created node (root).
  }

  // 6. Deep Copy Using HashMap
  GraphNode? cloneGraphDeepCopy(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> copies = {}; // Map to store cloned nodes.

    // Recursive function to perform the deep copy.
    void copyNode(GraphNode original) {
      if (!copies.containsKey(original.val)) {
        copies[original.val] = GraphNode(original.val); // Create a new clone.
        for (var neighbor in original.neighbors) {
          copyNode(neighbor); // Recursively copy the neighbor.
          copies[original.val]!.neighbors.add(copies[neighbor.val]!); // Consider null checks
        }
      }
    }

    copyNode(node); // Start the deep copy process.
    return copies[node.val]; // Return the cloned starting node.
  }
}

void main() {
  GraphNode node1 = GraphNode(1);
  GraphNode node2 = GraphNode(2);
  GraphNode node3 = GraphNode(3);
  GraphNode node4 = GraphNode(4);

  node1.neighbors.addAll([node2, node4]);
  node2.neighbors.addAll([node1, node3]);
  node3.neighbors.addAll([node2, node4]);
  node4.neighbors.addAll([node1, node3]);

  CloneGraph solver = CloneGraph();
  GraphNode? clonedDFS = solver.cloneGraphDFS(node1, {});
  GraphNode? clonedBFS = solver.cloneGraphBFS(node1);
  GraphNode? clonedIterativeDFS = solver.cloneGraphIterativeDFS(node1);
  GraphNode? clonedDeepCopy = solver.cloneGraphDeepCopy(node1);

  print("Graph cloned using DFS: ${clonedDFS?.val}");
  print("Graph cloned using BFS: ${clonedBFS?.val}");
  print("Graph cloned using Iterative DFS: ${clonedIterativeDFS?.val}");
  print("Graph cloned using Deep Copy: ${clonedDeepCopy?.val}");
}
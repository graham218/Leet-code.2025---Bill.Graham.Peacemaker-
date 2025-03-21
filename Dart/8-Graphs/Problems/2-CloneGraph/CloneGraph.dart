import 'dart:collection';

class GraphNode {
  int val;
  List<GraphNode> neighbors;

  GraphNode(this.val) : neighbors = [];
}

class CloneGraph {
  // 1. DFS Recursive Approach
  // This function clones the graph using Depth-First Search recursively.
  // It uses a map 'visited' to keep track of the already cloned nodes, preventing infinite loops in cyclic graphs.
  GraphNode? cloneGraphDFS(GraphNode? node, Map<int, GraphNode> visited) {
    // Base case: If the input node is null, return null.
    if (node == null) return null;

    // If the node has already been visited (cloned), return the cloned node from the map.
    if (visited.containsKey(node.val)) return visited[node.val];

    // Create a new clone node with the same value as the original node.
    GraphNode clone = GraphNode(node.val);

    // Mark the clone node as visited by adding it to the map.
    visited[node.val] = clone;

    // Iterate through the neighbors of the original node.
    for (var neighbor in node.neighbors) {
      // Recursively clone each neighbor and add the cloned neighbor to the cloned node's neighbors list.
      clone.neighbors.add(cloneGraphDFS(neighbor, visited)!);
    }

    // Return the cloned node.
    return clone;
  }

  // 2. DFS Iterative Approach
  // This function clones the graph using Depth-First Search iteratively with a stack.
  // It also uses a map 'visited' to keep track of cloned nodes.
  GraphNode? cloneGraphDFSIterative(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> visited = {}; // Map to store cloned nodes.
    List<GraphNode> stack = []; // Stack for DFS.
    stack.add(node); // Push the starting node onto the stack.
    visited[node.val] = GraphNode(node.val); // Create and store the clone of the starting node.

    while (stack.isNotEmpty) {
      GraphNode current = stack.removeLast(); // Pop the top node from the stack.
      for (var neighbor in current.neighbors) {
        if (!visited.containsKey(neighbor.val)) {
          visited[neighbor.val] = GraphNode(neighbor.val); // Create and store the clone of the neighbor.
          stack.add(neighbor); // Push the neighbor onto the stack.
        }
        visited[current.val]!.neighbors.add(visited[neighbor.val]!); // Add the cloned neighbor to the cloned current node's neighbors.
      }
    }
    return visited[node.val]; // Return the cloned starting node.
  }

  // 3. BFS Approach
  // This function clones the graph using Breadth-First Search with a queue.
  // It also uses a map 'visited' to keep track of cloned nodes.
  GraphNode? cloneGraphBFS(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> visited = {}; // Map to store cloned nodes.
    Queue<GraphNode> queue = Queue(); // Queue for BFS.
    queue.add(node); // Enqueue the starting node.
    visited[node.val] = GraphNode(node.val); // Create and store the clone of the starting node.

    while (queue.isNotEmpty) {
      GraphNode current = queue.removeFirst(); // Dequeue the front node.
      for (var neighbor in current.neighbors) {
        if (!visited.containsKey(neighbor.val)) {
          visited[neighbor.val] = GraphNode(neighbor.val); // Create and store the clone of the neighbor.
          queue.add(neighbor); // Enqueue the neighbor.
        }
        visited[current.val]!.neighbors.add(visited[neighbor.val]!); // Add the cloned neighbor to the cloned current node's neighbors.
      }
    }
    return visited[node.val]; // Return the cloned starting node.
  }

  // 4. Using Adjacency List
  // This function clones the graph by first creating an adjacency list representation of the graph,
  // then creating the cloned nodes, and finally connecting the cloned nodes based on the adjacency list.
  GraphNode? cloneGraphAdjList(GraphNode? node) {
    if (node == null) return null;
    Map<int, List<int>> adjList = {}; // Adjacency list to store the graph's connections.
    Queue<GraphNode> queue = Queue(); // Queue for traversing the graph.
    queue.add(node); // Enqueue the starting node.

    // Build the adjacency list.
    while (queue.isNotEmpty) {
      GraphNode current = queue.removeFirst();
      if (!adjList.containsKey(current.val)) {
        adjList[current.val] = [];
      }
      for (var neighbor in current.neighbors) {
        adjList[current.val]!.add(neighbor.val);
        if (!adjList.containsKey(neighbor.val)) {
          queue.add(neighbor);
        }
      }
    }

    // Create cloned nodes.
    Map<int, GraphNode> nodes = {};
    for (var entry in adjList.entries) {
      nodes[entry.key] = GraphNode(entry.key);
    }

    // Connect cloned nodes based on the adjacency list.
    for (var entry in adjList.entries) {
      for (var neighbor in entry.value) {
        nodes[entry.key]!.neighbors.add(nodes[neighbor]!);
      }
    }
    return nodes[node.val]; // Return the cloned starting node.
  }

  // 5. Using HashMap for Memory Optimization
  // This function clones the graph using a helper function and a map 'clones' for memory optimization.
  // It avoids redundant cloning by checking if a node has already been cloned.
  GraphNode? cloneGraphOptimized(GraphNode? node) {
    if (node == null) return null;
    Map<int, GraphNode> clones = {}; // Map to store cloned nodes.
    return _cloneHelper(node, clones); // Call the helper function.
  }

  // Helper function for recursive cloning with memory optimization.
  GraphNode _cloneHelper(GraphNode node, Map<int, GraphNode> clones) {
    if (clones.containsKey(node.val)) return clones[node.val]!; // If already cloned, return the clone.
    GraphNode clone = GraphNode(node.val); // Create a new clone.
    clones[node.val] = clone; // Store the clone in the map.
    for (var neighbor in node.neighbors) {
      clone.neighbors.add(_cloneHelper(neighbor, clones)); // Recursively clone neighbors.
    }
    return clone; // Return the cloned node.
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

  print("Cloning using DFS Recursive:");
  print(solver.cloneGraphDFS(node1, {})?.val);

  print("Cloning using DFS Iterative:");
  print(solver.cloneGraphDFSIterative(node1)?.val);

  print("Cloning using BFS:");
  print(solver.cloneGraphBFS(node1)?.val);

  print("Cloning using Adjacency List:");
  print(solver.cloneGraphAdjList(node1)?.val);

  print("Cloning using Memory Optimized HashMap:");
  print(solver.cloneGraphOptimized(node1)?.val);
}
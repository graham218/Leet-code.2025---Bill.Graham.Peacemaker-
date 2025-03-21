import 'dart:collection';

// Definition for a Node.
class Node {
  int val;
  List<Node?> neighbors;
  Node(this.val, [List<Node?>? neighbors]) : neighbors = neighbors ?? [];
  @override
  String toString() {
    return 'Node{val: $val, neighbors: ${neighbors.map((n) => n?.val).toList()}}';
  }
}

class CloneGraph {
  // Approach 1: Iterative Depth-First Search (DFS)
  Node? cloneGraphDFS(Node? node) {
    if (node == null) return null;

    Map<Node, Node> visited = {};
    //Stack<Node> stack = Stack(); // 'Stack' is not a standard Dart class.
    List<Node> stack = []; // Use a List as a stack.
    Node newHead = Node(node.val); // Create the new head node.
    visited[node] = newHead;
    stack.add(node);

    while (stack.isNotEmpty) {
      Node current = stack.removeLast(); // Use removeLast() for stack behavior.
      Node clonedNode = visited[current]!;

      for (Node? neighbor in current.neighbors) {
        if (neighbor == null) continue; // handle null neighbors
        if (!visited.containsKey(neighbor)) {
          visited[neighbor] = Node(neighbor.val);
          stack.add(neighbor);
        }
        clonedNode.neighbors.add(visited[neighbor]);
      }
    }
    return newHead;
  }

  // Approach 2: Recursive Depth-First Search (DFS)
  Node? cloneGraphDFS_Recursive(Node? node) {
    if (node == null) return null;
    Map<Node, Node> visited = {};
    return _cloneGraphDFS_RecursiveHelper(node, visited);
  }

  Node? _cloneGraphDFS_RecursiveHelper(Node node, Map<Node, Node> visited) {
    if (visited.containsKey(node)) {
      return visited[node];
    }
    Node clonedNode = Node(node.val);
    visited[node] = clonedNode;
    for (Node? neighbor in node.neighbors) {
      if(neighbor != null) { //check for null
        clonedNode.neighbors.add(_cloneGraphDFS_RecursiveHelper(neighbor, visited));
      }
    }
    return clonedNode;
  }

  // Approach 3: Iterative Breadth-First Search (BFS)
  Node? cloneGraphBFS(Node? node) {
    if (node == null) return null;

    Map<Node, Node> visited = {};
    Queue<Node> queue = Queue();
    Node newHead = Node(node.val);
    visited[node] = newHead;
    queue.add(node);

    while (queue.isNotEmpty) {
      Node current = queue.removeFirst();
      Node clonedNode = visited[current]!;

      for (Node? neighbor in current.neighbors) {
        if (neighbor == null) continue;
        if (!visited.containsKey(neighbor)) {
          visited[neighbor] = Node(neighbor.val);
          queue.add(neighbor);
        }
        clonedNode.neighbors.add(visited[neighbor]);
      }
    }
    return newHead;
  }

  // Approach 4: Using a Map to store cloned nodes, similar to DFS iterative
  Node? cloneGraphMap(Node? node) {
    if (node == null) return null;

    final Map<int, Node> clonedNodes = {};
    final Queue<Node> queue = Queue()..add(node);
    clonedNodes[node.val] = Node(node.val);

    while (queue.isNotEmpty) {
      final Node current = queue.removeFirst();
      final Node clonedCurrent = clonedNodes[current.val]!;

      for (final Node? neighbor in current.neighbors) {
        if (neighbor == null) continue;
        if (!clonedNodes.containsKey(neighbor.val)) {
          clonedNodes[neighbor.val] = Node(neighbor.val);
          queue.add(neighbor);
        }
        clonedCurrent.neighbors.add(clonedNodes[neighbor.val]);
      }
    }
    return clonedNodes.containsKey(node.val) ? clonedNodes[node.val] : null;
  }

  // Approach 5: Optimized DFS with early cloning
  Node? cloneGraphDFS_Optimized(Node? node) {
    if (node == null) return null;

    Map<Node, Node> visited = {};

    Node _clone(Node n) {
      if (!visited.containsKey(n)) {
        visited[n] = Node(n.val); // Create clone *before* recursion
        for (var neighbor in n.neighbors) {
          if(neighbor != null){
            visited[n]!.neighbors.add(_clone(neighbor));
          }
        }
      }
      return visited[n]!;
    }
    return _clone(node);
  }

  // Approach 6:  A variation of BFS using a queue and a map
  Node? cloneGraphBFSVariation(Node? node) {
    if (node == null) {
      return null;
    }

    Map<Node, Node> visited = {};
    Queue<Node> q = Queue();

    q.add(node);
    visited[node] = Node(node.val); // Create the clone of the starting node

    while (q.isNotEmpty) {
      Node u = q.removeFirst();
      Node clonedU = visited[u]!;

      for (Node? v in u.neighbors) {
        if (v == null) continue;
        if (!visited.containsKey(v)) {
          visited[v] = Node(v.val); // Create a clone for unseen nodes
          q.add(v);
        }
        clonedU.neighbors.add(visited[v]);
      }
    }
    return visited[node];
  }
}

void main() {
  // Create a sample graph: 1 -- 2, 1 -- 3, 2 -- 2, 2 -- 3
  Node node1 = Node(1);
  Node node2 = Node(2);
  Node node3 = Node(3);

  node1.neighbors = [node2, node3];
  node2.neighbors = [node2, node3];
  node3.neighbors = [node1];

  CloneGraph solution = CloneGraph();

  // Test each approach:
  void testApproach(String name, Node? Function(Node?) cloneFunction, Node? originalNode) {
    print("Testing $name:");
    Node? clonedGraph = cloneFunction(originalNode);
    if (clonedGraph != null) {
      print("Cloned Graph: ${clonedGraph.toString()}");
      // You would add more sophisticated checks here to ensure a *deep* copy.
      //  - Check that the structure is identical (number of nodes, connections)
      //  - Check that the *instances* are different (cloned nodes are not the same as original nodes)
      //  For brevity, we're doing a basic print here.  For real testing, use test frameworks.
    } else {
      print("Cloned Graph: null");
    }
    print("-" * 50);
  }

  testApproach("Iterative DFS", solution.cloneGraphDFS, node1);
  testApproach("Recursive DFS", solution.cloneGraphDFS_Recursive, node1);
  testApproach("Iterative BFS", solution.cloneGraphBFS, node1);
  testApproach("Using Map", solution.cloneGraphMap, node1);
  testApproach("Optimized DFS", solution.cloneGraphDFS_Optimized, node1);
  testApproach("BFS Variation", solution.cloneGraphBFSVariation, node1);
}

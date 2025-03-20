// Dart program for real-world applications using binary tree depth calculation
// Implementations include real-world use cases applicable in projects

import 'dart:collection';
import 'dart:async'; // Import for asynchronous operations

// Definition for a binary tree node
class TreeNode {
  int val;
  TreeNode? left;
  TreeNode? right;
  TreeNode(this.val, [this.left, this.right]);
}

// 1. Recursive DFS - Used in Employee Hierarchy Management Systems
// This function calculates the depth of an employee hierarchy using recursive Depth-First Search (DFS).
// It's suitable for systems where the hierarchy is relatively small and fits within memory.
int employeeHierarchyDepth(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;
  // Calculate the depth recursively by adding 1 to the maximum depth of the left and right subtrees.
  return 1 + (employeeHierarchyDepth(root.left)).clamp(0, employeeHierarchyDepth(root.right));
}

// 2. Iterative DFS - Used in AI Decision Trees for Predictive Analysis
// This function computes the depth of an AI decision tree using iterative DFS with a stack.
// Useful for large decision trees where recursion might lead to stack overflow.
int aiDecisionTreeDepth(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;
  // Initialize a stack to store nodes and their depths.
  List<MapEntry<TreeNode, int>> stack = [MapEntry(root, 1)];
  int maxDepth = 0;
  // Iterate while the stack is not empty.
  while (stack.isNotEmpty) {
    var entry = stack.removeLast();
    TreeNode node = entry.key;
    int depth = entry.value;
    // Update the maximum depth if necessary.
    maxDepth = maxDepth > depth ? maxDepth : depth;
    // Push the left and right children onto the stack with their updated depths.
    if (node.left != null) stack.add(MapEntry(node.left!, depth + 1));
    if (node.right != null) stack.add(MapEntry(node.right!, depth + 1));
  }
  return maxDepth;
}

// 3. BFS - Used in Social Network Graph Depth Calculation
// This function calculates the depth of a social network graph using Breadth-First Search (BFS).
// Suitable for finding the shortest path or depth in a graph where nodes represent users and edges represent connections.
int socialNetworkDepth(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;
  // Initialize a queue with the root node.
  Queue<TreeNode> queue = Queue<TreeNode>()..add(root);
  int depth = 0;
  // Iterate while the queue is not empty.
  while (queue.isNotEmpty) {
    int size = queue.length;
    // Process all nodes at the current level.
    for (int i = 0; i < size; i++) {
      TreeNode node = queue.removeFirst();
      // Enqueue the left and right children.
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }
    // Increment the depth after processing each level.
    depth++;
  }
  return depth;
}

// 4. Tail Recursion - Used in Database Index Tree Optimization
// This function calculates the depth of a database index tree using tail recursion.
// Note: Dart does not automatically optimize tail recursion, so this is functionally equivalent to the regular recursive approach.
// Useful for optimizing database queries by ensuring efficient index traversal.
int databaseIndexDepth(TreeNode? root, [int depth = 0]) {
  // Base case: If the root is null, return the current depth.
  if (root == null) return depth;
  // Calculate the depth recursively by incrementing the depth for each level.
  return (databaseIndexDepth(root.left, depth + 1)).clamp(0, databaseIndexDepth(root.right, depth + 1));
}

// 5. Morris Traversal - Used in File System Navigation Without Extra Memory
// This function calculates the depth of a file system tree using Morris traversal.
// Useful for navigating file systems without using recursion or a stack, saving memory.
int fileSystemDepth(TreeNode? root) {
  int depth = 0, currentDepth = 0;
  TreeNode? current = root;
  while (current != null) {
    if (current.left == null) {
      current = current.right;
      currentDepth++;
    } else {
      TreeNode? pre = current.left;
      int tempDepth = 1;
      while (pre!.right != null && pre.right != current) {
        pre = pre.right;
        tempDepth++;
      }
      if (pre.right == null) {
        pre.right = current;
        current = current.left;
        currentDepth += tempDepth;
      } else {
        pre.right = null;
        depth = depth > currentDepth ? depth : currentDepth;
        current = current.right;
        currentDepth -= tempDepth;
      }
    }
  }
  return depth;
}

// 6. Parallel Processing - Used in Cloud-Based Distributed Processing Systems
// This function calculates the depth of a tree using parallel processing in a cloud environment.
// It leverages asynchronous operations to compute the left and right subtree depths concurrently.
Future<int> cloudProcessingDepth(TreeNode? root) async {
  if (root == null) return 0;
  int leftDepth = 0, rightDepth = 0;
  // Use Future.wait to execute the depth calculations for the left and right subtrees concurrently.
  await Future.wait([
    Future(() => leftDepth = employeeHierarchyDepth(root.left)),
    Future(() => rightDepth = employeeHierarchyDepth(root.right))
  ]);
  // Return the maximum depth of the subtrees plus 1 for the current node.
  return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

void main() async {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, null, TreeNode(6, null, TreeNode(7))));

  print("Employee Hierarchy Depth: ${employeeHierarchyDepth(root)}");
  print("AI Decision Tree Depth: ${aiDecisionTreeDepth(root)}");
  print("Social Network Depth: ${socialNetworkDepth(root)}");
  print("Database Index Tree Depth: ${databaseIndexDepth(root)}");
  print("File System Navigation Depth: ${fileSystemDepth(root)}");
  print("Cloud Processing Tree Depth: ${await cloudProcessingDepth(root)}");
}
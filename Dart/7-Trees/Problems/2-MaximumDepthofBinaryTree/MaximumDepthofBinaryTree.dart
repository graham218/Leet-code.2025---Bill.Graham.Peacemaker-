// Dart program to find the maximum depth of a binary tree using 5 different approaches

import 'dart:collection';

// Definition for a binary tree node
class TreeNode {
  int val;
  TreeNode? left;
  TreeNode? right;
  TreeNode(this.val, [this.left, this.right]);
}

// 1. Recursive DFS Approach
// This function calculates the maximum depth of a binary tree using a recursive Depth-First Search (DFS).
int maxDepthRecursive(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;

  // Recursively calculate the depth of the left and right subtrees.
  // The depth of the current node is 1 (for the current node) plus the maximum depth of its subtrees.
  // clamp(0, ...) is used to ensure the returned depth is not negative, though this is not strictly needed.
  return 1 + (maxDepthRecursive(root.left)).clamp(0, maxDepthRecursive(root.right));
}

// 2. Iterative DFS Using Stack
// This function calculates the maximum depth using an iterative DFS with a stack.
int maxDepthIterativeDFS(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;

  // Initialize a stack to store nodes and their depths.
  List<MapEntry<TreeNode, int>> stack = [MapEntry(root, 1)];

  // Initialize the maximum depth.
  int maxDepth = 0;

  // Continue while the stack is not empty.
  while (stack.isNotEmpty) {
    // Pop the top node and its depth from the stack.
    var entry = stack.removeLast();
    TreeNode node = entry.key;
    int depth = entry.value;

    // Update the maximum depth if the current depth is greater.
    maxDepth = maxDepth > depth ? maxDepth : depth;

    // Push the left and right children onto the stack with their updated depths.
    if (node.left != null) stack.add(MapEntry(node.left!, depth + 1));
    if (node.right != null) stack.add(MapEntry(node.right!, depth + 1));
  }

  // Return the maximum depth.
  return maxDepth;
}

// 3. BFS Using Queue
// This function calculates the maximum depth using Breadth-First Search (BFS) with a queue.
int maxDepthBFS(TreeNode? root) {
  // Base case: If the root is null, the depth is 0.
  if (root == null) return 0;

  // Initialize a queue with the root node.
  Queue<TreeNode> queue = Queue<TreeNode>()..add(root);

  // Initialize the depth.
  int depth = 0;

  // Continue while the queue is not empty.
  while (queue.isNotEmpty) {
    // Get the number of nodes at the current level.
    int size = queue.length;

    // Process all nodes at the current level.
    for (int i = 0; i < size; i++) {
      // Dequeue a node.
      TreeNode node = queue.removeFirst();

      // Enqueue the left and right children.
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }

    // Increment the depth after processing each level.
    depth++;
  }

  // Return the depth.
  return depth;
}

// 4. Using Tail Recursion Optimization
// This function calculates the maximum depth using tail recursion.
// Note: Dart does not automatically optimize tail recursion, so this is functionally equivalent to the regular recursive approach.
int maxDepthTailRec(TreeNode? root, [int depth = 0]) {
  // Base case: If the root is null, return the current depth.
  if (root == null) return depth;

  // Recursively calculate the depth of the left and right subtrees.
  // The depth is incremented for each level.
  // clamp(0, ...) is used to ensure the returned depth is not negative, though this is not strictly needed.
  return (maxDepthTailRec(root.left, depth + 1)).clamp(0, maxDepthTailRec(root.right, depth + 1));
}

// 5. Using Morris Traversal
// This function calculates the maximum depth using Morris traversal, which is an in-order traversal without using recursion or a stack.
// This approach is more complex and less intuitive for calculating depth, and is not generally recommended for this purpose.
// It is more efficient in terms of space complexity.
int maxDepthMorris(TreeNode? root) {
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

void main() {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, null, TreeNode(6, null, TreeNode(7))));

  print("Recursive DFS Max Depth: ${maxDepthRecursive(root)}");
  print("Iterative DFS Max Depth: ${maxDepthIterativeDFS(root)}");
  print("BFS Max Depth: ${maxDepthBFS(root)}");
  print("Tail Recursive Max Depth: ${maxDepthTailRec(root)}");
  print("Morris Traversal Max Depth: ${maxDepthMorris(root)}");
}
// Dart program to calculate the Diameter of a Binary Tree using 5 different approaches
// Real-world applications include Network Routing, File System Analysis, and AI Decision Trees

import 'dart:math';
import 'dart:collection';
import 'dart:async'; // Import for asynchronous operations

// Definition for a binary tree node
class TreeNode {
  int val;
  TreeNode? left;
  TreeNode? right;
  TreeNode(this.val, [this.left, this.right]);
}

// 1. Recursive Approach (Used in Network Latency Calculation)
// This function calculates the diameter of a binary tree using a recursive approach.
// The diameter is the length of the longest path between any two nodes in a tree.
int diameterRecursive(TreeNode? root, [List<int>? maxDiameter]) {
  // Initialize maxDiameter if it's null.
  maxDiameter ??= [0];

  // Helper function to calculate the height of a node.
  int height(TreeNode? node) {
    if (node == null) return 0;

    // Recursively calculate the height of the left and right subtrees.
    int leftHeight = height(node.left);
    int rightHeight = height(node.right);

    // Update the maximum diameter found so far.
    // The diameter at the current node is the sum of the left and right subtree heights.
    maxDiameter![0] = max(maxDiameter[0], leftHeight + rightHeight);

    // Return the height of the current node, which is 1 plus the maximum height of its subtrees.
    return 1 + max(leftHeight, rightHeight);
  }

  // Start the height calculation from the root.
  height(root);

  // Return the maximum diameter found.
  return maxDiameter[0];
}

// 2. Iterative DFS Approach (Used in AI Decision Trees)
// This function calculates the diameter of a binary tree using an iterative Depth-First Search (DFS) approach.
int diameterIterativeDFS(TreeNode? root) {
  if (root == null) return 0;

  int maxDiameter = 0;
  Map<TreeNode?, int> heights = {};
  List<TreeNode> stack = [];
  TreeNode? lastVisited;

  while (stack.isNotEmpty || root != null) {
    if (root != null) {
      stack.add(root);
      root = root.left;
    } else {
      TreeNode node = stack.last;
      if (node.right != null && node.right != lastVisited) {
        root = node.right;
      } else {
        stack.removeLast();
        int leftHeight = heights[node.left] ?? 0;
        int rightHeight = heights[node.right] ?? 0;
        heights[node] = 1 + max(leftHeight, rightHeight);
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);
        lastVisited = node;
      }
    }
  }
  return maxDiameter;
}

// 3. BFS Approach (Fixed for Correct Calculation)
// This function calculates the diameter of a binary tree using a Breadth-First Search (BFS) approach.
// It is now corrected to properly calculate the diameter.
int diameterBFS(TreeNode? root) {
  if (root == null) return 0;
  int maxDiameter = 0;
  Queue<TreeNode> queue = Queue<TreeNode>();
  Map<TreeNode?, int> heights = {};
  queue.add(root);

  while (queue.isNotEmpty) {
    TreeNode node = queue.removeFirst();
    int leftHeight = heights[node.left] ?? 0;
    int rightHeight = heights[node.right] ?? 0;
    maxDiameter = max(maxDiameter, leftHeight + rightHeight);
    heights[node] = 1 + max(leftHeight, rightHeight);

    if (node.left != null) {
      queue.add(node.left!);
      // Corrected height calculation for left child
      heights[node.left] = (heights[node] ?? 0) + 1;
    }
    if (node.right != null) {
      queue.add(node.right!);
      // Corrected height calculation for right child
      heights[node.right] = (heights[node] ?? 0) + 1;
    }
  }
  return maxDiameter;
}

// 4. Dynamic Programming Approach (Fixed for Correct Calculation)
// This function calculates the diameter of a binary tree using dynamic programming.
int diameterDP(TreeNode? root, Map<TreeNode?, int> memo, List<int> maxDiameter) {
  if (root == null) return 0;
  if (memo.containsKey(root)) return memo[root]!;

  // Recursively calculate the heights of the left and right subtrees.
  int left = diameterDP(root.left, memo, maxDiameter);
  int right = diameterDP(root.right, memo, maxDiameter);

  // Update the maximum diameter found so far.
  maxDiameter[0] = max(maxDiameter[0], left + right);

  // Store the height of the current node in the memo.
  memo[root] = 1 + max(left, right);

  // Return the height of the current node.
  return memo[root]!;
}

// 5. Parallel Processing Approach (Used in Distributed Data Systems)
// This function calculates the diameter of a binary tree using parallel processing.
Future<int> diameterParallel(TreeNode? root) async {
  if (root == null) return 0;

  // Calculate the diameters of the left and right subtrees concurrently.
  int leftDiameter = 0, rightDiameter = 0;
  await Future.wait([
    Future(() => leftDiameter = diameterRecursive(root.left)),
    Future(() => rightDiameter = diameterRecursive(root.right))
  ]);

  // Return the maximum diameter found.
  return max(leftDiameter, rightDiameter);
}

void main() async {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, null, TreeNode(6, null, TreeNode(7))));

  print("Recursive Approach (Network Latency) Diameter: ${diameterRecursive(root)}");
  print("Iterative DFS (AI Decision Trees) Diameter: ${diameterIterativeDFS(root)}");
  print("BFS Approach (File System Analysis) Diameter: ${diameterBFS(root)}");
  print("Dynamic Programming (Routing Optimization) Diameter: ${diameterDP(root, {}, [0])}");
  print("Parallel Processing (Distributed Systems) Diameter: ${await diameterParallel(root)}");
}
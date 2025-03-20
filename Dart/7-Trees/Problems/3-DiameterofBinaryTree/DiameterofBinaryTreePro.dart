// Dart program to calculate the Diameter of a Binary Tree using 6 different approaches
// Real-world applications include Network Optimization, Social Network Analysis, and AI Pathfinding

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

// 1. Standard Recursive Approach (Used in Network Topology Analysis)
int diameterRecursive(TreeNode? root) {
  int maxDiameter = 0;
  int height(TreeNode? node) {
    if (node == null) return 0;
    int leftHeight = height(node.left);
    int rightHeight = height(node.right);
    maxDiameter = max(maxDiameter, leftHeight + rightHeight);
    return 1 + max(leftHeight, rightHeight);
  }
  height(root);
  return maxDiameter;
}

// 2. Bottom-Up Approach (Used in Hierarchical Data Processing)
int diameterBottomUp(TreeNode? root) {
  List<int> maxDiameter = [0];
  int depth(TreeNode? node) {
    if (node == null) return 0;
    int left = depth(node.left);
    int right = depth(node.right);
    maxDiameter[0] = max(maxDiameter[0], left + right);
    return 1 + max(left, right);
  }
  depth(root);
  return maxDiameter[0];
}

// 3. BFS with Level Tracking (Used in Social Network Analysis)
int diameterBFS(TreeNode? root) {
  if (root == null) return 0;
  int maxDiameter = 0;
  Queue<TreeNode> queue = Queue<TreeNode>();
  Map<TreeNode, int> depths = {};
  queue.add(root);
  depths[root] = 1;
  while (queue.isNotEmpty) {
    TreeNode node = queue.removeFirst();
    int leftDepth = 0;
    int rightDepth = 0;
    if(node.left != null && depths.containsKey(node.left)){
      leftDepth = depths[node.left]!;
    }
    if(node.right != null && depths.containsKey(node.right)){
      rightDepth = depths[node.right]!;
    }
    maxDiameter = max(maxDiameter, leftDepth + rightDepth);
    if (node.left != null) {
      queue.add(node.left!);
      depths[node.left!] = depths[node]! + 1;
    }
    if (node.right != null) {
      queue.add(node.right!);
      depths[node.right!] = depths[node]! + 1;
    }
  }
  return maxDiameter;
}

// 4. HashMap Memoization (Used in Caching and Query Optimization)
int diameterMemoization(TreeNode? root) {
  Map<TreeNode?, int> memo = {};
  List<int> maxDiameter = [0];
  int helper(TreeNode? node) {
    if (node == null) return 0;
    if (memo.containsKey(node)) return memo[node]!;
    int left = helper(node.left);
    int right = helper(node.right);
    maxDiameter[0] = max(maxDiameter[0], left + right);
    memo[node] = 1 + max(left, right);
    return memo[node]!;
  }
  helper(root);
  return maxDiameter[0];
}

// 5. Multi-threaded Parallel Approach (Used in Distributed Computing)
Future<int> diameterParallel(TreeNode? root) async {
  if (root == null) return 0;
  int leftDiameter = await Future(() => diameterRecursive(root.left));
  int rightDiameter = await Future(() => diameterRecursive(root.right));
  return max(leftDiameter, rightDiameter);
}

// 6. Iterative Post-Order Traversal (Used in AI Path Planning)
int diameterIterative(TreeNode? root) {
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

void main() async {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, null, TreeNode(6, null, TreeNode(7))));

  print("Recursive Approach (Network Analysis) Diameter: ${diameterRecursive(root)}");
  print("Bottom-Up Approach (Hierarchical Data) Diameter: ${diameterBottomUp(root)}");
  print("BFS Approach (Social Networks) Diameter: ${diameterBFS(root)}");
  print("Memoization (Query Optimization) Diameter: ${diameterMemoization(root)}");
  print("Parallel Processing (Distributed Systems) Diameter: ${await diameterParallel(root)}");
  print("Iterative Post-Order (AI Pathfinding) Diameter: ${diameterIterative(root)}");
}
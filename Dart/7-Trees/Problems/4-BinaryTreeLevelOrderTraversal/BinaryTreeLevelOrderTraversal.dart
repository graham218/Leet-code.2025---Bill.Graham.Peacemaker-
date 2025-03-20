// Dart program for Binary Tree Level Order Traversal using multiple approaches
// Real-world applications include hierarchical processing, scheduling tasks, and AI decision trees.

import 'dart:collection';

// Definition for a binary tree node
class TreeNode {
  int val; // Value of the node
  TreeNode? left; // Left child node
  TreeNode? right; // Right child node
  TreeNode(this.val, [this.left, this.right]); // Constructor to create a node
}

// 1. BFS Using Queue (Standard Level Order Traversal)
// This approach uses Breadth-First Search (BFS) with a queue to traverse the tree level by level.
// It processes nodes at each level before moving to the next level.
List<List<int>> levelOrderBFS(TreeNode? root) {
  List<List<int>> result = []; // Initialize the result list to store level-wise node values
  if (root == null) return result; // If the tree is empty, return an empty result

  Queue<TreeNode> queue = Queue<TreeNode>(); // Create a queue for BFS traversal
  queue.add(root); // Add the root node to the queue

  while (queue.isNotEmpty) {
    int levelSize = queue.length; // Get the number of nodes at the current level
    List<int> level = []; // Initialize a list to store node values at the current level

    // Process all nodes at the current level
    for (int i = 0; i < levelSize; i++) {
      TreeNode node = queue.removeFirst(); // Dequeue a node
      level.add(node.val); // Add the node's value to the current level list

      // Enqueue the left and right children if they exist
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }

    result.add(level); // Add the current level's node values to the result list
  }
  return result; // Return the level-wise node values
}

// 2. Recursive DFS Approach
// This approach uses Depth-First Search (DFS) recursively to traverse the tree.
// It maintains a level parameter to track the depth of each node and adds nodes to the corresponding level in the result list.
void dfs(TreeNode? node, int level, List<List<int>> result) {
  if (node == null) return; // Base case: if node is null, return

  // If the current level doesn't exist in the result list, create a new list for it
  if (result.length == level) result.add([]);

  result[level].add(node.val); // Add the node's value to the corresponding level list

  // Recursively traverse the left and right subtrees
  dfs(node.left, level + 1, result);
  dfs(node.right, level + 1, result);
}

List<List<int>> levelOrderDFS(TreeNode? root) {
  List<List<int>> result = []; // Initialize the result list
  dfs(root, 0, result); // Start the DFS traversal from the root at level 0
  return result; // Return the level-wise node values
}

// 3. Zigzag Level Order Traversal
// This approach is similar to BFS but alternates the order of node values at each level (left to right, right to left).
List<List<int>> zigzagLevelOrder(TreeNode? root) {
  List<List<int>> result = []; // Initialize the result list
  if (root == null) return result; // If the tree is empty, return an empty result

  Queue<TreeNode> queue = Queue<TreeNode>(); // Create a queue for BFS traversal
  queue.add(root); // Add the root node to the queue
  bool leftToRight = true; // Flag to track the direction of traversal (left to right or right to left)

  while (queue.isNotEmpty) {
    int levelSize = queue.length; // Get the number of nodes at the current level
    List<int> level = List.filled(levelSize, 0); // Initialize a list with fixed size to store node values at the current level

    // Process all nodes at the current level
    for (int i = 0; i < levelSize; i++) {
      TreeNode node = queue.removeFirst(); // Dequeue a node
      int index = leftToRight ? i : (levelSize - 1 - i); // Calculate the index based on the traversal direction
      level[index] = node.val; // Add the node's value to the level list at the calculated index

      // Enqueue the left and right children if they exist
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }

    result.add(level); // Add the current level's node values to the result list
    leftToRight = !leftToRight; // Toggle the traversal direction for the next level
  }
  return result; // Return the zigzag level-wise node values
}

// 4. Reverse Level Order Traversal
// This approach performs standard BFS and then reverses the result list to get the level order traversal in reverse.
List<List<int>> reverseLevelOrder(TreeNode? root) {
  List<List<int>> result = levelOrderBFS(root); // Perform standard BFS
  return result.reversed.toList(); // Reverse the result list and return it
}

// 5. Using a HashMap to Store Levels
// This approach uses a HashMap to store node values at each level.
// The keys of the HashMap represent the level, and the values are lists of node values at that level.
Map<int, List<int>> levelOrderWithMap(TreeNode? root) {
  Map<int, List<int>> levelMap = {}; // Initialize a HashMap to store level-wise node values

  // Recursive function to traverse the tree and store node values in the HashMap
  void traverse(TreeNode? node, int level) {
    if (node == null) return; // Base case: if node is null, return

    // If the current level doesn't exist in the HashMap, create a new list for it
    if (!levelMap.containsKey(level)) {
      levelMap[level] = [];
    }

    levelMap[level]!.add(node.val); // Add the node's value to the corresponding level list in the HashMap

    // Recursively traverse the left and right subtrees
    traverse(node.left, level + 1);
    traverse(node.right, level + 1);
  }

  traverse(root, 0); // Start the traversal from the root at level 0
  return levelMap; // Return the HashMap containing level-wise node values
}

void main() {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, null, TreeNode(6, null, TreeNode(7))));

  print("Level Order Traversal (BFS Queue): ${levelOrderBFS(root)}");
  print("Level Order Traversal (DFS Recursive): ${levelOrderDFS(root)}");
  print("Zigzag Level Order Traversal: ${zigzagLevelOrder(root)}");
  print("Reverse Level Order Traversal: ${reverseLevelOrder(root)}");
  print("Level Order with HashMap: ${levelOrderWithMap(root)}");
}
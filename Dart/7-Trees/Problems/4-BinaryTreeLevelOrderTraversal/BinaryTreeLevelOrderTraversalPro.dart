// Dart program for Binary Tree Level Order Traversal using 6 different approaches
// Real-world applications include processing hierarchical data, scheduling tasks, and rendering UI components.

import 'dart:collection';
import 'dart:async'; // Import for asynchronous operations in parallel approach

// Definition for a binary tree node
class TreeNode {
  int val; // Value of the node
  TreeNode? left; // Left child node
  TreeNode? right; // Right child node
  TreeNode(this.val, [this.left, this.right]); // Constructor to create a node
}

// 1. Standard BFS Approach (Used in Task Scheduling Systems)
// This approach uses Breadth-First Search (BFS) with a queue to traverse the tree level by level.
// Nodes at each level are processed before moving to the next level.
List<List<int>> levelOrderBFS(TreeNode? root) {
  if (root == null) return []; // If the tree is empty, return an empty list
  List<List<int>> result = []; // Initialize the result list to store level-wise node values
  Queue<TreeNode> queue = Queue<TreeNode>(); // Create a queue for BFS traversal
  queue.add(root); // Add the root node to the queue

  while (queue.isNotEmpty) {
    int levelSize = queue.length; // Get the number of nodes at the current level
    List<int> currentLevel = []; // Initialize a list to store node values at the current level

    // Process all nodes at the current level
    for (int i = 0; i < levelSize; i++) {
      TreeNode node = queue.removeFirst(); // Dequeue a node
      currentLevel.add(node.val); // Add the node's value to the current level list

      // Enqueue the left and right children if they exist
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }
    result.add(currentLevel); // Add the current level's node values to the result list
  }
  return result; // Return the level-wise node values
}

// 2. Recursive DFS Approach (Used in Hierarchical Data Processing)
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

// 3. Zigzag Level Order (Used in Tree-Based UI Rendering)
// This approach is similar to BFS but alternates the order of node values at each level (left to right, right to left).
List<List<int>> levelOrderZigzag(TreeNode? root) {
  if (root == null) return []; // If the tree is empty, return an empty list
  List<List<int>> result = []; // Initialize the result list
  Queue<TreeNode> queue = Queue<TreeNode>(); // Create a queue for BFS traversal
  queue.add(root); // Add the root node to the queue
  bool leftToRight = true; // Flag to track the direction of traversal (left to right or right to left)

  while (queue.isNotEmpty) {
    int levelSize = queue.length; // Get the number of nodes at the current level
    List<int> currentLevel = List.filled(levelSize, 0); // Initialize a list with fixed size to store node values at the current level

    // Process all nodes at the current level
    for (int i = 0; i < levelSize; i++) {
      TreeNode node = queue.removeFirst(); // Dequeue a node
      int index = leftToRight ? i : (levelSize - 1 - i); // Calculate the index based on the traversal direction
      currentLevel[index] = node.val; // Add the node's value to the level list at the calculated index

      // Enqueue the left and right children if they exist
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }

    leftToRight = !leftToRight; // Toggle the traversal direction for the next level
    result.add(currentLevel); // Add the current level's node values to the result list
  }
  return result; // Return the zigzag level-wise node values
}

// 4. Reverse Level Order (Used in Stack-Based Processing)
// This approach performs standard BFS and then reverses the result list to get the level order traversal in reverse.
List<List<int>> levelOrderReverse(TreeNode? root) {
  List<List<int>> result = levelOrderBFS(root); // Perform standard BFS
  return result.reversed.toList(); // Reverse the result list and return it
}

// 5. Parallel Level Order (Used in Distributed Computing)
// This approach uses a Future to execute the standard BFS asynchronously, simulating parallel processing.
// Note: This approach only parallelizes the top-level BFS call, and may not provide significant performance benefits for smaller trees.
Future<List<List<int>>> levelOrderParallel(TreeNode? root) async {
  return await Future(() => levelOrderBFS(root)); // Execute BFS asynchronously
}

// 6. Iterative Level Order using Stack (Used in AI Path Search Algorithms)
// This approach, while named levelOrderStack, actually uses a queue for level order traversal.
// It inserts each level at the beginning of the result list, effectively reversing the level order.
List<List<int>> levelOrderStack(TreeNode? root) {
  if (root == null) return []; // If the tree is empty, return an empty list
  List<List<int>> result = []; // Initialize the result list
  Queue<TreeNode> queue = Queue<TreeNode>(); // Create a queue for level order traversal
  queue.add(root); // Add the root node to the queue

  while (queue.isNotEmpty) {
    int levelSize = queue.length; // Get the number of nodes at the current level
    List<int> currentLevel = []; // Initialize a list to store node values at the current level

    // Process all nodes at the current level
    for (int i = 0; i < levelSize; i++) {
      TreeNode node = queue.removeFirst(); // Dequeue a node
      currentLevel.add(node.val); // Add the node's value to the current level list

      // Enqueue the left and right children if they exist
      if (node.left != null) queue.add(node.left!);
      if (node.right != null) queue.add(node.right!);
    }
    result.insert(0, currentLevel); // Insert the current level at the beginning of the result list
  }
  return result; // Return the reversed level-wise node values
}

void main() async {
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, TreeNode(6), TreeNode(7)));

  print("BFS Level Order Traversal: ${levelOrderBFS(root)}");
  print("DFS Level Order Traversal: ${levelOrderDFS(root)}");
  print("Zigzag Level Order Traversal: ${levelOrderZigzag(root)}");
  print("Reverse Level Order Traversal: ${levelOrderReverse(root)}");
  print("Parallel Level Order Traversal: ${await levelOrderParallel(root)}");
  print("Stack-Based Level Order Traversal: ${levelOrderStack(root)}");
}
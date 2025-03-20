// Dart program demonstrating Breadth-First Search (BFS) on Trees
// Implementing 5 different BFS approaches

import 'dart:collection';

// Tree Node structure
class TreeNode {
  int value; // Value stored in the node
  List<TreeNode> children; // List of child nodes

  // Constructor to create a TreeNode
  TreeNode(this.value) : children = [];
}

// 1. Standard BFS Traversal
void bfsTraversal(TreeNode root) {
  // Initialize a queue to store nodes for BFS traversal
  Queue<TreeNode> queue = Queue();
  // Add the root node to the queue
  queue.add(root);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first node
    TreeNode node = queue.removeFirst();
    // Print the visited node's value
    print("Visited: ${node.value}");
    // Enqueue all children of the current node
    for (var child in node.children) {
      queue.add(child);
    }
  }
  // BFS Traversal visits all nodes level by level.
}

// 2. BFS to Find a Target Value
bool bfsSearch(TreeNode root, int target) {
  // Initialize a queue for BFS
  Queue<TreeNode> queue = Queue();
  // Add the root node to the queue
  queue.add(root);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first node
    TreeNode node = queue.removeFirst();
    // Check if the node's value matches the target
    if (node.value == target) return true; // Return true if found
    // Enqueue all children of the current node
    for (var child in node.children) {
      queue.add(child);
    }
  }
  // Return false if the target is not found after traversing all nodes
  return false;
}

// 3. BFS Level Order Traversal
void bfsLevelOrder(TreeNode root) {
  // Initialize a queue for BFS
  Queue<TreeNode> queue = Queue();
  // Add the root node to the queue
  queue.add(root);
  // Initialize the level counter
  int level = 0;

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Get the number of nodes at the current level
    int size = queue.length;
    // Print the current level
    print("Level $level:");
    // Process all nodes at the current level
    for (int i = 0; i < size; i++) {
      // Dequeue the first node
      TreeNode node = queue.removeFirst();
      // Print the node's value with indentation for level representation
      print("  ${node.value}");
      // Enqueue all children of the current node
      for (var child in node.children) {
        queue.add(child);
      }
    }
    // Increment the level counter
    level++;
  }
  // Prints the tree level by level.
}

// 4. BFS to Find Maximum Value in Tree
int bfsFindMax(TreeNode root) {
  // Initialize a queue for BFS
  Queue<TreeNode> queue = Queue();
  // Add the root node to the queue
  queue.add(root);
  // Initialize the maximum value with the root's value
  int maxValue = root.value;

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first node
    TreeNode node = queue.removeFirst();
    // Check if the node's value is greater than the current maximum value
    if (node.value > maxValue) {
      // Update the maximum value
      maxValue = node.value;
    }
    // Enqueue all children of the current node
    for (var child in node.children) {
      queue.add(child);
    }
  }
  // Return the maximum value found in the tree
  return maxValue;
}

// 5. BFS to Count Nodes in the Tree
int bfsCountNodes(TreeNode root) {
  // Initialize a queue for BFS
  Queue<TreeNode> queue = Queue();
  // Add the root node to the queue
  queue.add(root);
  // Initialize the node counter
  int count = 0;

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first node
    TreeNode node = queue.removeFirst();
    // Increment the node counter
    count++;
    // Enqueue all children of the current node
    for (var child in node.children) {
      queue.add(child);
    }
  }
  // Return the total number of nodes in the tree
  return count;
}

void main() {
  // Constructing a sample tree
  TreeNode root = TreeNode(1);
  root.children.add(TreeNode(2));
  root.children.add(TreeNode(3));
  root.children[0].children.add(TreeNode(4));
  root.children[0].children.add(TreeNode(5));
  root.children[1].children.add(TreeNode(6));
  root.children[1].children.add(TreeNode(7));

  print("Standard BFS Traversal:");
  bfsTraversal(root);

  print("\nSearching for value 5: ${bfsSearch(root, 5)}");
  print("Searching for value 10: ${bfsSearch(root, 10)}");

  print("\nLevel Order Traversal:");
  bfsLevelOrder(root);

  print("\nMaximum Value in Tree: ${bfsFindMax(root)}");
  print("Total Nodes in Tree: ${bfsCountNodes(root)}");
}
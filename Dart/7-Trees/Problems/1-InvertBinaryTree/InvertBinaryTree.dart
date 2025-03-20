// Dart program demonstrating 5 different approaches to invert a Binary Tree

class TreeNode {
  int value;
  TreeNode? left, right;
  TreeNode(this.value, [this.left, this.right]);
}

// 1. Recursive Approach
TreeNode? invertTreeRecursive(TreeNode? root) {
  // Base case: if the root is null, return null (empty tree)
  if (root == null) return null;

  // Store the left subtree temporarily
  TreeNode? temp = root.left;

  // Recursively invert the right subtree and assign it to the left child
  root.left = invertTreeRecursive(root.right);

  // Recursively invert the left subtree (which was stored in temp) and assign it to the right child
  root.right = invertTreeRecursive(temp);

  // Return the inverted root
  return root;
}

// 2. Iterative Approach using Queue (BFS)
TreeNode? invertTreeIterativeBFS(TreeNode? root) {
  // Base case: if the root is null, return null (empty tree)
  if (root == null) return null;

  // Initialize a queue with the root node for Breadth-First Search (BFS)
  List<TreeNode?> queue = [root];

  // Continue processing nodes while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first node
    TreeNode? node = queue.removeAt(0);

    // If the node is not null, swap its left and right children
    if (node != null) {
      // Store the left child temporarily
      TreeNode? temp = node.left;

      // Swap the left and right children
      node.left = node.right;
      node.right = temp;

      // Enqueue the left child (if it exists)
      queue.add(node.left);

      // Enqueue the right child (if it exists)
      queue.add(node.right);
    }
  }

  // Return the inverted root
  return root;
}

// 3. Iterative Approach using Stack (DFS)
TreeNode? invertTreeIterativeDFS(TreeNode? root) {
  // Base case: if the root is null, return null (empty tree)
  if (root == null) return null;

  // Initialize a stack with the root node for Depth-First Search (DFS)
  List<TreeNode?> stack = [root];

  // Continue processing nodes while the stack is not empty
  while (stack.isNotEmpty) {
    // Pop the last node from the stack
    TreeNode? node = stack.removeLast();

    // If the node is not null, swap its left and right children
    if (node != null) {
      // Store the left child temporarily
      TreeNode? temp = node.left;

      // Swap the left and right children
      node.left = node.right;
      node.right = temp;

      // Push the left child (if it exists) onto the stack
      stack.add(node.left);

      // Push the right child (if it exists) onto the stack
      stack.add(node.right);
    }
  }

  // Return the inverted root
  return root;
}

// 4. Using Morris Traversal (In-Place, No Extra Space)
TreeNode? invertTreeMorris(TreeNode? root) {
  // Initialize the current node to the root
  TreeNode? current = root;

  // Continue traversing while the current node is not null
  while (current != null) {
    // If the current node has a left child
    if (current.left != null) {
      // Find the inorder predecessor of the current node
      TreeNode? pre = current.left;
      while (pre!.right != null && pre.right != current.right) {
        pre = pre.right;
      }

      // Make the right child of the predecessor point to the right child of the current node
      pre.right = current.right;

      // Make the right child of the current node point to its left child
      current.right = current.left;

      // Make the left child of the current node null (effectively swapping left and right)
      current.left = null;
    }

    // Move to the right child of the current node
    current = current.right;
  }

  // Return the inverted root
  return root;
}

// 5. Real-World Implementation: Mirroring a File System Structure
class FileNode {
  String name;
  List<FileNode> children;
  FileNode(this.name, [this.children = const []]);
}

FileNode? invertFileSystem(FileNode? root) {
  // Base case: if the root is null, return null (empty directory)
  if (root == null) return null;

  // Reverse the order of the children list
  root.children = root.children.reversed.toList();

  // Recursively invert each child node
  for (var child in root.children) {
    invertFileSystem(child);
  }

  // Return the inverted root
  return root;
}

// Helper function to print tree
void printTree(TreeNode? root, [String prefix = ""]) {
  // Base case: if the root is null, return (empty subtree)
  if (root == null) return;

  // Print the current node's value with the given prefix
  print("$prefix${root.value}");

  // Recursively print the left subtree with an indented prefix
  printTree(root.left, "$prefix  ");

  // Recursively print the right subtree with an indented prefix
  printTree(root.right, "$prefix  ");
}

void main() {
  // Sample binary tree
  TreeNode root = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)));

  print("Original Tree:");
  printTree(root);

  print("\nInverted Tree (Recursive):");
  printTree(invertTreeRecursive(TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))));

  print("\nInverted Tree (Iterative BFS):");
  printTree(invertTreeIterativeBFS(TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))));

  print("\nInverted Tree (Iterative DFS):");
  printTree(invertTreeIterativeDFS(TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))));

  print("\nInverted Tree (Morris Traversal):");
  printTree(invertTreeMorris(TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))));

  // File System Example
  FileNode fileRoot = FileNode("Root", [FileNode("Folder1", [FileNode("File1.1"), FileNode("File1.2")]), FileNode("Folder2", [FileNode("File2.1")])]);
  print("\nOriginal File System Structure: ${fileRoot.children.map((e) => e.name).toList()}");
  invertFileSystem(fileRoot);
  print("Inverted File System Structure: ${fileRoot.children.map((e) => e.name).toList()}");
}
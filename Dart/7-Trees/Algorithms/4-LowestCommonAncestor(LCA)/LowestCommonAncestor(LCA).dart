// Dart program demonstrating 5 different approaches to find the Lowest Common Ancestor (LCA) in a Binary Tree

class TreeNode {
  int value;
  TreeNode? left, right;
  TreeNode(this.value, [this.left, this.right]);
}

// 1. Recursive Approach
TreeNode? findLCARecursive(TreeNode? root, int n1, int n2) {
  // Base case: if the root is null, return null
  if (root == null) return null;
  // If the root's value matches either n1 or n2, return the root
  if (root.value == n1 || root.value == n2) return root;

  // Recursively find the LCA in the left and right subtrees
  TreeNode? leftLCA = findLCARecursive(root.left, n1, n2);
  TreeNode? rightLCA = findLCARecursive(root.right, n1, n2);

  // If both left and right subtrees have found an LCA, the current root is the LCA
  if (leftLCA != null && rightLCA != null) return root;
  // If only one subtree has found an LCA, return that LCA
  return leftLCA ?? rightLCA;
  // This recursive approach explores the tree from the root, checking if n1 or n2 are present in the left and right subtrees.
}

// 2. Iterative Approach using Parent Mapping
TreeNode? findLCAIterative(TreeNode? root, int n1, int n2) {
  // Base case: if the root is null, return null
  if (root == null) return null;

  // Map to store the parent of each node
  Map<TreeNode, TreeNode?> parentMap = {};

  // Stack for iterative traversal (BFS-like)
  List<TreeNode?> stack = [root];
  // The root has no parent, so it's null
  parentMap[root] = null;

  // Build the parent map
  while (stack.isNotEmpty) {
    TreeNode? node = stack.removeLast();
    if (node?.left != null) {
      parentMap[node!.left!] = node; // Store the parent of the left child
      stack.add(node.left);
    }
    if (node?.right != null) {
      parentMap[node!.right!] = node; // Store the parent of the right child
      stack.add(node.right);
    }
  }

  // Set to store the ancestors of n1
  Set<TreeNode?> ancestors = {};
  TreeNode? temp = root;
  // Traverse up from n1 to the root, adding each ancestor to the set
  while (temp != null) {
    ancestors.add(temp);
    temp = parentMap[temp];
  }

  // Traverse up from n2 to the root, finding the first common ancestor
  temp = root;
  while (!ancestors.contains(temp)) {
    temp = parentMap[temp];
  }
  return temp;
  // This iterative approach builds a parent map and then traverses up from n1 and n2 to find the first common ancestor.
}

// 3. Path-Based Approach
bool findPath(TreeNode? root, int n, List<TreeNode> path) {
  // Base case: if the root is null, return false
  if (root == null) return false;
  // Add the current node to the path
  path.add(root);
  // If the current node's value matches n, return true
  if (root.value == n) return true;
  // Recursively find the path in the left and right subtrees
  if (findPath(root.left, n, path) || findPath(root.right, n, path)) return true;
  // If the path is not found, remove the current node from the path
  path.removeLast();
  return false;
  // This function finds the path from the root to the node with value n.
}

TreeNode? findLCAPathBased(TreeNode? root, int n1, int n2) {
  // Lists to store the paths from the root to n1 and n2
  List<TreeNode> path1 = [], path2 = [];
  // If either n1 or n2 is not found, return null
  if (!findPath(root, n1, path1) || !findPath(root, n2, path2)) return null;

  int i = 0;
  // Find the common prefix of the two paths
  while (i < path1.length && i < path2.length && path1[i] == path2[i]) {
    i++;
  }
  // The LCA is the last common node in the paths
  return path1[i - 1];
  // This path-based approach finds the paths from the root to n1 and n2, then finds the last common node in the paths.
}

// 4. Binary Search Tree (BST) Approach
TreeNode? findLCABST(TreeNode? root, int n1, int n2) {
  // Traverse the BST until the LCA is found
  while (root != null) {
    // If both n1 and n2 are in the left subtree, move to the left subtree
    if (root.value > n1 && root.value > n2) {
      root = root.left;
    }
    // If both n1 and n2 are in the right subtree, move to the right subtree
    else if (root.value < n1 && root.value < n2) {
      root = root.right;
    }
    // If n1 and n2 are in different subtrees, the current root is the LCA
    else {
      return root;
    }
  }
  return null;
  // This BST approach leverages the BST property to efficiently find the LCA.
}

// 5. Using Lowest Depth Node
TreeNode? findLCAUsingDepth(TreeNode? root, int n1, int n2) {
  // Map to store the depth of each node
  Map<TreeNode, int> depth = {};

  // Recursive function to compute the depth of each node
  void computeDepth(TreeNode? node, int d) {
    if (node == null) return;
    depth[node] = d;
    computeDepth(node.left, d + 1);
    computeDepth(node.right, d + 1);
  }

  // Compute the depth of each node
  computeDepth(root, 0);

  // Find the LCA using the recursive approach
  TreeNode? ancestor = findLCARecursive(root, n1, n2);
  return ancestor;

  // This approach is redundant, since the recursive LCA is already being calculated, the depth map is not being used.
}

void main() {
  // Constructing a sample binary tree
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, TreeNode(6), TreeNode(7)));

  int n1 = 4, n2 = 5;
  print("Recursive LCA of $n1 and $n2: ${findLCARecursive(root, n1, n2)?.value}");
  print("Iterative LCA of $n1 and $n2: ${findLCAIterative(root, n1, n2)?.value}");
  print("Path-Based LCA of $n1 and $n2: ${findLCAPathBased(root, n1, n2)?.value}");
  print("BST LCA of $n1 and $n2: ${findLCABST(root, n1, n2)?.value}");
  print("Depth-Based LCA of $n1 and $n2: ${findLCAUsingDepth(root, n1, n2)?.value}");
}
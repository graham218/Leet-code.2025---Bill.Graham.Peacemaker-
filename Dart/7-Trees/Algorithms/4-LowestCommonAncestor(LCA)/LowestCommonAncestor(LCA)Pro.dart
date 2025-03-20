// Dart program demonstrating 6 different approaches to find the Lowest Common Ancestor (LCA) in a Binary Tree
// with real-world implementations

class TreeNode {
  int value;
  TreeNode? left, right;
  TreeNode(this.value, [this.left, this.right]);
}

// 1. Recursive Approach (General Tree)
// This approach recursively traverses the tree.
// If either n1 or n2 is found, that node is returned.
// If both left and right subtrees return a node, the current node is the LCA.
// Otherwise, the non-null result (if any) is returned.
TreeNode? findLCARecursive(TreeNode? root, int n1, int n2) {
  // Base case: If the root is null, return null.
  if (root == null) return null;

  // If the current node's value is either n1 or n2, return the current node.
  if (root.value == n1 || root.value == n2) return root;

  // Recursively find the LCA in the left and right subtrees.
  TreeNode? leftLCA = findLCARecursive(root.left, n1, n2);
  TreeNode? rightLCA = findLCARecursive(root.right, n1, n2);

  // If both left and right subtrees return non-null, the current node is the LCA.
  if (leftLCA != null && rightLCA != null) return root;

  // Otherwise, return the non-null result (if any).
  return leftLCA ?? rightLCA;
}

// 2. Iterative Approach using Parent Mapping
// This approach uses a map to store the parent of each node.
// It then traverses the ancestors of n1 and n2 until a common ancestor is found.
TreeNode? findLCAIterative(TreeNode? root, int n1, int n2) {
  // Base case: If the root is null, return null.
  if (root == null) return null;

  // Map to store the parent of each node.
  Map<TreeNode, TreeNode?> parentMap = {};
  // Stack for iterative traversal.
  List<TreeNode?> stack = [root];
  // The root node has no parent.
  parentMap[root] = null;

  // Build the parent map using iterative traversal.
  while (stack.isNotEmpty) {
    TreeNode? node = stack.removeLast();
    if (node?.left != null) {
      parentMap[node!.left!] = node;
      stack.add(node.left);
    }
    if (node?.right != null) {
      parentMap[node!.right!] = node;
      stack.add(node.right);
    }
  }

  // Set to store the ancestors of n1.
  Set<TreeNode?> ancestors = {};
  // Start from n1 and traverse up to the root, adding each ancestor to the set.
  TreeNode? temp = _findNode(root,n1,parentMap);
  while (temp != null) {
    ancestors.add(temp);
    temp = parentMap[temp];
  }

  // Start from n2 and traverse up to the root, checking if each ancestor is in the set.
  temp = _findNode(root,n2,parentMap);
  while (!ancestors.contains(temp)) {
    temp = parentMap[temp];
  }
  // The first ancestor found in the set is the LCA.
  return temp;
}

TreeNode? _findNode(TreeNode? root, int target, Map<TreeNode,TreeNode?> parentMap) {
  if(root == null) return null;
  if(root.value == target) return root;
  for(TreeNode node in parentMap.keys){
    if(node.value == target) return node;
  }
  return null;
}

// 3. Path-Based Approach
// This approach finds the paths from the root to n1 and n2.
// It then compares the paths to find the last common node.
bool findPath(TreeNode? root, int n, List<TreeNode> path) {
  // Base case: If the root is null, return false.
  if (root == null) return false;

  // Add the current node to the path.
  path.add(root);

  // If the current node's value is n, return true.
  if (root.value == n) return true;

  // Recursively find the path in the left and right subtrees.
  if (findPath(root.left, n, path) || findPath(root.right, n, path)) return true;

  // If n is not found in the subtree, remove the current node from the path.
  path.removeLast();
  return false;
}

TreeNode? findLCAPathBased(TreeNode? root, int n1, int n2) {
  // Lists to store the paths from the root to n1 and n2.
  List<TreeNode> path1 = [], path2 = [];

  // Find the paths.
  if (!findPath(root, n1, path1) || !findPath(root, n2, path2)) return null;

  // Compare the paths to find the last common node.
  int i = 0;
  while (i < path1.length && i < path2.length && path1[i] == path2[i]) {
    i++;
  }
  // The last common node is the LCA.
  return path1[i - 1];
}

// 4. Binary Search Tree (BST) Approach
// This approach takes advantage of the BST property:
// If both n1 and n2 are smaller than the current node, the LCA is in the left subtree.
// If both n1 and n2 are larger than the current node, the LCA is in the right subtree.
// Otherwise, the current node is the LCA.
TreeNode? findLCABST(TreeNode? root, int n1, int n2) {
  // Traverse the BST until the LCA is found.
  while (root != null) {
    // If both n1 and n2 are smaller than the current node, go to the left subtree.
    if (root.value > n1 && root.value > n2) {
      root = root.left;
    }
    // If both n1 and n2 are larger than the current node, go to the right subtree.
    else if (root.value < n1 && root.value < n2) {
      root = root.right;
    }
    // Otherwise, the current node is the LCA.
    else {
      return root;
    }
  }
  // If the root is null, return null.
  return null;
}

// 5. Using Depth Mapping
// This approach calculates the depth of each node and then uses the recursive LCA function.
// This example shows that depth mapping, while useful in other tree problems,
// adds unnecessary overhead for finding the LCA when a simple recursive approach works.
TreeNode? findLCAUsingDepth(TreeNode? root, int n1, int n2) {
  // Map to store the depth of each node.
  Map<TreeNode, int> depth = {};

  // Function to compute the depth of each node.
  void computeDepth(TreeNode? node, int d) {
    if (node == null) return;
    depth[node] = d;
    computeDepth(node.left, d + 1);
    computeDepth(node.right, d + 1);
  }

  // Compute the depth of each node.
  computeDepth(root, 0);

  // Use the recursive LCA function to find the LCA.
  return findLCARecursive(root, n1, n2);
}

// 6. Real-World Implementation: Finding LCA in an Organization Hierarchy
// This approach simulates finding the common manager of two employees in an organization hierarchy.
class Employee {
  String name;
  Employee? manager;
  Employee(this.name, [this.manager]);
}

Employee? findLCAInHierarchy(Employee? emp1, Employee? emp2) {
  // Set to store the visited managers.
  Set<Employee?> visited = {};

  // Traverse up the hierarchy until a common manager is found.
  while (emp1 != null || emp2 != null) {
    if (emp1 != null) {
      // If the manager has already been visited, it is the LCA.
      if (visited.contains(emp1)) return emp1;
      // Add the manager to the visited set.
      visited.add(emp1);
      // Go up to the next manager.
      emp1 = emp1.manager;
    }
    if (emp2 != null) {
      // If the manager has already been visited, it is the LCA.
      if (visited.contains(emp2)) return emp2;
      // Add the manager to the visited set.
      visited.add(emp2);
      // Go up to the next manager.
      emp2 = emp2.manager;
    }
  }
  return null;
}

void main() {
  // Constructing a sample binary tree
  TreeNode root = TreeNode(1,
      TreeNode(2, TreeNode(4), TreeNode(5)),
      TreeNode(3, TreeNode(6), TreeNode(7)));

  int n1 = 4, n2 = 5;
  print("Recursive LCA: ${findLCARecursive(root, n1, n2)?.value}");
  print("Iterative LCA: ${findLCAIterative(root, n1, n2)?.value}");
  print("Path-Based LCA: ${findLCAPathBased(root, n1, n2)?.value}");
  print("BST LCA: ${findLCABST(root, n1, n2)?.value}");
  print("Depth-Based LCA: ${findLCAUsingDepth(root, n1, n2)?.value}");

  // Organization Hierarchy Example
  Employee ceo = Employee("CEO");
  Employee managerA = Employee("ManagerA", ceo);
  Employee managerB = Employee("ManagerB", ceo);
  Employee emp1 = Employee("Employee1", managerA);
  Employee emp2 = Employee("Employee2", managerB);

  print("LCA in Hierarchy: ${findLCAInHierarchy(emp1, emp2)?.name}");
}

// Dart program to demonstrate Depth-First Search (DFS) on a Tree
// Using 5 different approaches, with detailed comments and enhanced functionality.

// Node structure for the tree
class TreeNode {
  int value;
  List<TreeNode> children;

  TreeNode(this.value) : children = [];

  @override
  String toString() {
    return 'TreeNode{value: $value}';
  }
}

// 1. Recursive DFS: Simple traversal
void recursiveDFS(TreeNode? node) {
  // Base case: If the node is null, return.
  if (node == null) return;

  // Process the current node (e.g., print its value).
  print(node.value);

  // Recursively visit each child of the current node.
  for (var child in node.children) {
    recursiveDFS(child);
  }
}

// 2. Iterative DFS using Stack: Non-recursive traversal
void iterativeDFS(TreeNode? root) {
  // Base case: If the root is null, return.
  if (root == null) return;

  // Initialize a stack with the root node.
  List<TreeNode> stack = [root];

  // Continue while the stack is not empty.
  while (stack.isNotEmpty) {
    // Pop the top node from the stack.
    TreeNode node = stack.removeLast();

    // Process the current node (e.g., print its value).
    print(node.value);

    // Add children to the stack in reverse order to maintain DFS order.
    // Reversing the order ensures the leftmost child is processed first.
    stack.addAll(node.children.reversed);
  }
}

// 3. DFS with Path Tracking: Records the path taken to each node
void dfsWithPath(TreeNode? node, List<int> path) {
  // Base case: If the node is null, return.
  if (node == null) return;

  // Add the current node's value to the path.
  path.add(node.value);

  // Print the current path.
  print("Current Path: $path");

  // Recursively visit each child, passing a copy of the current path.
  // Using List<int>.from(path) creates a new list, preventing modifications
  // from affecting other branches.
  for (var child in node.children) {
    dfsWithPath(child, List<int>.from(path));
  }
}

// 4. DFS with Parent Mapping: Tracks the parent of each node
void dfsWithParent(TreeNode? node, Map<int, int?> parentMap, [int? parent]) {
  // Base case: If the node is null, return.
  if (node == null) return;

  // Map the current node's value to its parent's value.
  parentMap[node.value] = parent;

  // Print the node and its parent.
  print("Node: ${node.value}, Parent: ${parent}");

  // Recursively visit each child, setting the current node as the parent.
  for (var child in node.children) {
    dfsWithParent(child, parentMap, node.value);
  }
}

// 5. Counting Nodes using DFS: Counts the total number of nodes in the tree
int countNodesDFS(TreeNode? node) {
  // Base case: If the node is null, return 0.
  if (node == null) return 0;

  // Initialize the count to 1 (for the current node).
  int count = 1;

  // Recursively count the nodes in each subtree and add them to the count.
  for (var child in node.children) {
    count += countNodesDFS(child);
  }

  // Return the total count.
  return count;
}

// 6. Find a node by value using DFS
TreeNode? findNodeDFS(TreeNode? node, int targetValue) {
  if (node == null) return null;
  if(node.value == targetValue) return node;
  for(var child in node.children){
    TreeNode? found = findNodeDFS(child, targetValue);
    if(found != null) return found;
  }
  return null;
}

// 7. DFS with level tracking
void dfsWithLevel(TreeNode? node, int level){
  if(node == null) return;
  print("Node: ${node.value}, Level: $level");
  for(var child in node.children){
    dfsWithLevel(child, level+1);
  }
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

  print("Recursive DFS:");
  recursiveDFS(root);

  print("\nIterative DFS:");
  iterativeDFS(root);

  print("\nDFS with Path Tracking:");
  dfsWithPath(root, []);

  print("\nDFS with Parent Mapping:");
  Map<int, int?> parentMap = {};
  dfsWithParent(root, parentMap);

  print("\nTotal Nodes in Tree: ${countNodesDFS(root)}");

  print("\nFind Node with value 5: ${findNodeDFS(root, 5)}");

  print("\nDFS with Level Tracking:");
  dfsWithLevel(root, 0);

}
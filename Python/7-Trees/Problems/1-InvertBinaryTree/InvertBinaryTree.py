from collections import deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        """
        Initializes a TreeNode object.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            left (TreeNode, optional): The left child of the node. Defaults to None.
            right (TreeNode, optional): The right child of the node. Defaults to None.
        """
        self.val = val  # Store the node's value
        self.left = left  # Store the left child
        self.right = right  # Store the right child

# Approach 1: Recursive DFS (Preorder Traversal)
def invert_tree_recursive_preorder(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using recursive Depth-First Search (DFS) with preorder traversal.
    Preorder traversal means we process the current node *before* processing its children.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to invert.

    Returns:
        Optional[TreeNode]: The root of the inverted binary tree.  Returns None if the input root is None.
    """
    if not root:  # Base case: If the node is None (empty), return None
        return None

    # Swap left and right children of the current node.  This is the "inversion" step.
    root.left, root.right = root.right, root.left

    # Recursively invert the left subtree.  This will process all nodes on the left side.
    invert_tree_recursive_preorder(root.left)
    # Recursively invert the right subtree. This will process all nodes on the right side.
    invert_tree_recursive_preorder(root.right)

    # Return the root of the modified tree.  The entire tree is inverted due to the recursive calls.
    return root

# Approach 2: Recursive DFS (Postorder Traversal)
def invert_tree_recursive_postorder(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using recursive Depth-First Search (DFS) with postorder traversal.
    Postorder traversal means we process the current node *after* processing its children.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to invert.

    Returns:
        Optional[TreeNode]: The root of the inverted binary tree.
    """
    if not root:  # Base case: If the node is None, return None
        return None

    # Recursively invert the left subtree first
    left = invert_tree_recursive_postorder(root.left)
    # Recursively invert the right subtree
    right = invert_tree_recursive_postorder(root.right)

    # Swap left and right children of the current node *after* the subtrees are inverted.
    root.left, root.right = right, left  # Corrected swap

    # Return the root of the modified tree
    return root

# Approach 3: Iterative DFS (Using Stack)
def invert_tree_iterative_dfs(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using iterative Depth-First Search (DFS) with a stack.
    This avoids recursion.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to invert.

    Returns:
        Optional[TreeNode]: The root of the inverted binary tree.
    """
    if not root:  # Handle empty tree case
        return None

    stack = [root]  # Initialize a stack with the root node
    while stack:  # Continue as long as there are nodes in the stack
        node = stack.pop()  # Get the top node from the stack
        # Swap left and right children
        node.left, node.right = node.right, node.left

        # Push the right child onto the stack *if it exists*.  Important for correct traversal.
        if node.right:
            stack.append(node.right)
        # Push the left child onto the stack *if it exists*.  Important for correct traversal.  Left child is pushed *after* right, so it's processed next.
        if node.left:
            stack.append(node.left)

    return root  # Return the modified root

# Approach 4: Iterative BFS (Using Queue)
def invert_tree_iterative_bfs(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using iterative Breadth-First Search (BFS) with a queue.
    BFS processes nodes level by level.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to invert.

    Returns:
        Optional[TreeNode]: The root of the inverted binary tree.
    """
    if not root:  # Handle empty tree
        return None

    queue = deque([root])  # Initialize a queue with the root node
    while queue:  # Continue as long as there are nodes in the queue
        node = queue.popleft()  # Get the node at the front of the queue
        # Swap left and right children
        node.left, node.right = node.right, node.left

        # Enqueue the left child *if it exists*
        if node.left:
            queue.append(node.left)
        # Enqueue the right child *if it exists*
        if node.right:
            queue.append(node.right)

    return root  # Return the modified root

# Approach 5: Functional Approach (Purely Recursive)
def invert_tree_functional(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using a functional, purely recursive approach.
    This approach avoids any explicit state manipulation.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to invert.

    Returns:
        Optional[TreeNode]: The root of the inverted binary tree.
    """
    if not root:  # Base case: Empty tree
        return None
    # Recursively construct a new tree with swapped children.  This creates a *new* tree, not modifying the original in place.
    return TreeNode(root.val, invert_tree_functional(root.right), invert_tree_functional(root.left))

# Helper function to print the tree level-wise (BFS)
def print_tree(root: Optional[TreeNode]):
    """
    Prints the binary tree in a level-wise manner (Breadth-First Search).
    This is helpful for visualizing the tree structure.  Handles null nodes.

    Args:
        root (Optional[TreeNode]): The root of the binary tree to print.
    """
    if not root:
        print("Empty Tree")
        return
    queue = deque([root])  # Initialize queue
    result = []
    while queue:
        node = queue.popleft()
        result.append(node.val if node else None) # Append node value or None for null
        if node:
            queue.append(node.left)
            queue.append(node.right)

    print(result)

# Sample Usage (Demonstrates each inversion method)
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("Original Tree:")
print_tree(tree)  # Print the original tree

print("\nInverted using Recursive Preorder:")
tree = invert_tree_recursive_preorder(tree) # Invert and assign
print_tree(tree)

# Recreate the tree for a fresh inversion
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Recursive Postorder:")
tree = invert_tree_recursive_postorder(tree)
print_tree(tree)

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Iterative DFS:")
tree = invert_tree_iterative_dfs(tree)
print_tree(tree)

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Iterative BFS:")
tree = invert_tree_iterative_bfs(tree)
print_tree(tree)

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Functional Approach:")
tree = invert_tree_functional(tree)
print_tree(tree)

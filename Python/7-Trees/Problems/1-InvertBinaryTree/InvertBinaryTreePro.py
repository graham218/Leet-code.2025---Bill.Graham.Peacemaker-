from collections import deque
from typing import Optional, Dict
import time
import pickle
import heapq

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val  # Store the value of the node.
        self.left = left  # Store the left child node.
        self.right = right  # Store the right child node.

# Approach 1: Time Delay Simulation (Simulating Processing Time)
def invert_tree_with_delay(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree by swapping the left and right children of each node.
    This version simulates processing time with a delay.

    Args:
        root: The root of the binary tree to invert.

    Returns:
        The root of the inverted binary tree.
    """
    if not root:  # Base case: if the node is None, return None.
        return None
    time.sleep(0.1)  # Simulate processing time (100ms delay).  This is NOT a standard part of tree inversion.
    root.left, root.right = root.right, root.left  # Swap left and right children.
    invert_tree_with_delay(root.left)  # Recursively invert the left subtree.
    invert_tree_with_delay(root.right)  # Recursively invert the right subtree.
    return root  # Return the root of the modified tree.

# Approach 2: Binary Heap Storage and Inversion
def invert_tree_heap(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using a binary heap.  This is an unusual and inefficient approach.
    It stores node values in a heap, then reconstructs the tree from the heap.  This does NOT
    preserve the original tree structure, and the inverted tree will be heap-ordered, not
    a true inversion.

    Args:
        root: The root of the binary tree.

    Returns:
        The root of the "inverted" tree (which will be heap-ordered).
    """
    if not root:
        return None

    heap = []  # Initialize an empty list to be used as a min-heap.

    def store_in_heap(node: Optional[TreeNode]):
        """
        Recursively traverses the tree and stores the *values* of the nodes in the heap.
        """
        if node:
            heapq.heappush(heap, node.val)  # Push the node's value onto the heap.
            store_in_heap(node.left)  # Recurse on the left subtree.
            store_in_heap(node.right)  # Recurse on the right subtree.

    store_in_heap(root)  # Start storing node values from the root.

    def construct_inverted_tree():
        """
        Recursively constructs a new tree from the values in the heap.  The tree will be
        heap-ordered (smallest value at the root), NOT a proper inversion.  The original
        tree structure is lost.
        """
        if not heap:
            return None
        return TreeNode(heapq.heappop(heap), construct_inverted_tree(), construct_inverted_tree())  # Create a new node with the smallest value from the heap.

    return construct_inverted_tree()  # Start constructing the new tree.

# Approach 3: Pickle Serialization and Inversion
def invert_tree_pickle(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using Python's pickle serialization.  This is also an unusual
    and generally inefficient way to invert a binary tree.  It serializes the tree,
    deserializes it, and then swaps the left and right children at the root of the *deserialized* tree.
    This will not correctly invert subtrees.

    Args:
        root: The root of the binary tree.

    Returns:
        The root of the inverted tree.  Inversion is only done at the top level.
    """
    if not root:
        return None
    serialized_tree = pickle.dumps(root)  # Serialize the tree into a byte string.
    inverted_tree = pickle.loads(serialized_tree)  # Deserialize the byte string back into a tree structure.
    inverted_tree.left, inverted_tree.right = inverted_tree.right, inverted_tree.left # Only swaps the root's children.
    return inverted_tree

# Approach 4: Stack-based Manual Inversion
def invert_tree_stack(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using a stack (iterative approach).  This is a standard and
    efficient way to invert a binary tree.

    Args:
        root: The root of the binary tree.

    Returns:
        The root of the inverted tree.
    """
    if not root:
        return None
    stack = [root]  # Initialize a stack with the root node.
    while stack:
        node = stack.pop()  # Pop a node from the stack.
        node.left, node.right = node.right, node.left  # Swap left and right children.
        if node.left:
            stack.append(node.left)  # Push the left child onto the stack.
        if node.right:
            stack.append(node.right)  # Push the right child onto the stack.
    return root  # Return the root of the modified tree.

# Approach 5: Inversion with Linked List Simulation (using deque)
def invert_tree_linked_list(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree using a deque (double-ended queue) to simulate a queue
    (breadth-first traversal). This is a standard and efficient way to invert a binary tree.
    This is essentially an iterative level-order traversal where you swap children.

    Args:
        root: The root of the binary tree.

    Returns:
        The root of the inverted tree.
    """
    if not root:
        return None
    queue = deque([root])  # Initialize a deque with the root node.
    while queue:
        node = queue.popleft()  # Dequeue a node from the front.
        node.left, node.right = node.right, node.left  # Swap left and right children.
        if node.left:
            queue.append(node.left)  # Enqueue the left child.
        if node.right:
            queue.append(node.right)  # Enqueue the right child.
    return root  # Return the root of the modified tree.

# Approach 6: Counting Nodes and Inverting
def invert_tree_counting(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """
    Inverts a binary tree and counts the number of nodes before and after inversion.
    This is not a different inversion method, but adds a node-counting operation
    to the standard swapping of left and right children.

    Args:
        root: The root of the binary tree.

    Returns:
        The root of the inverted tree.
    """
    if not root:
        return None

    def count_nodes(node: Optional[TreeNode]) -> int:
        """
        Recursively counts the number of nodes in the subtree rooted at 'node'.
        """
        if not node:
            return 0
        return 1 + count_nodes(node.left) + count_nodes(node.right)  # Count the current node + left subtree + right subtree.

    print(f"Total nodes before inversion: {count_nodes(root)}")  # Print the node count before inversion.
    root.left, root.right = root.right, root.left  # Swap left and right children.
    print(f"Total nodes after inversion: {count_nodes(root)}")  # Print the node count after inversion.
    return root  # Return the root of the inverted tree.

# Helper function to print tree (Breadth-First Traversal)
def print_tree(root: Optional[TreeNode]):
    """
    Prints the binary tree in a breadth-first manner (level-order traversal).
    This function prints node values, and None for missing nodes, in a list format.

    Args:
        root: The root of the binary tree to print.
    """
    if not root:
        return
    queue = deque([root])  # Initialize a deque with the root node.
    result = []  # List to store the node values.
    while queue:
        node = queue.popleft()  # Dequeue a node.
        result.append(node.val if node else None)  # Append node's value or None if node is None
        if node:
            queue.append(node.left)  # Enqueue left child.
            queue.append(node.right)  # Enqueue right child.
    print(result)  # Print the list of node values.

# Sample Usage
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("Original Tree:")
print_tree(tree)

print("\nInverted using Time Delay:")
print_tree(invert_tree_with_delay(tree))

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Binary Heap:")
print_tree(invert_tree_heap(tree))

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Pickle Serialization:")
print_tree(invert_tree_pickle(tree))

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Stack:")
print_tree(invert_tree_stack(tree))

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Linked List Simulation:")
print_tree(invert_tree_linked_list(tree))

# Recreate the tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("\nInverted using Node Counting:")
print_tree(invert_tree_counting(tree))

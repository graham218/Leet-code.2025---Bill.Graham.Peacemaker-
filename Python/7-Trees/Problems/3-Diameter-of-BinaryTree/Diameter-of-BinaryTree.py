from typing import Optional
from collections import deque
import threading
import asyncio
import concurrent.futures

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        """
        Initializes a TreeNode object.

        Args:
            val (int): The value of the node. Defaults to 0.
            left (Optional[TreeNode]): The left child of the node. Defaults to None.
            right (Optional[TreeNode]): The right child of the node. Defaults to None.
        """
        self.val = val
        self.left = left
        self.right = right

# Approach 1: Recursive DFS (Naive)
def diameter_of_binary_tree_recursive(root: Optional[TreeNode]) -> int:
    """
    Calculates the diameter of a binary tree using a recursive Depth-First Search (DFS) approach.
    The diameter of a binary tree is the longest path between any two nodes in the tree.
    This implementation calculates the depth of left and right subtrees for each node
    and updates the diameter if the sum of the depths is greater than the current diameter.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The diameter of the binary tree.
    """
    diameter = 0  # Initialize the diameter to 0

    def depth(node: Optional[TreeNode]) -> int:
        """
        Helper function to calculate the depth of a subtree.  It also updates the diameter.

        Args:
            node (Optional[TreeNode]): The root of the subtree.

        Returns:
            int: The depth of the subtree.
        """
        nonlocal diameter  # Allows modification of the 'diameter' variable in the outer scope
        if not node:
            return 0  # Base case: if the node is None, the depth is 0
        left = depth(node.left)  # Recursively calculate the depth of the left subtree
        right = depth(node.right)  # Recursively calculate the depth of the right subtree
        diameter = max(diameter, left + right)  # Update the diameter if a longer path is found
        return 1 + max(left, right)  # Return the depth of the current node
    depth(root)  # Start the depth calculation from the root
    return diameter  # Return the calculated diameter

# Approach 2: BFS with Queue
def diameter_of_binary_tree_bfs(root: Optional[TreeNode]) -> int:
    """
    Calculates the diameter of a binary tree using Breadth-First Search (BFS) with a queue.
    This approach iterates through the tree level by level, calculating the depth of the left
    and right children for each node and updating the maximum diameter found so far.
    However, standard BFS is not ideally suited for this problem, as it focuses on level-order
    traversal, not path length.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The diameter of the binary tree.
    """
    if not root:
        return 0  # Base case: if the root is None, the diameter is 0

    queue = deque([(root, 0)])  # Initialize a queue with the root node and its depth (0)
    max_diameter = 0  # Initialize the maximum diameter to 0

    while queue:
        node, depth = queue.popleft()  # Dequeue a node and its depth
        left_depth = depth + 1 if node.left else 0  # Calculate the depth of the left child
        right_depth = depth + 1 if node.right else 0  # Calculate the depth of the right child
        max_diameter = max(max_diameter, left_depth + right_depth)  # Update max_diameter
        if node.left:
            queue.append((node.left, left_depth))  # Enqueue the left child and its depth
        if node.right:
            queue.append((node.right, right_depth))  # Enqueue the right child and its depth

    return max_diameter  # Return the maximum diameter

# Approach 3: Iterative DFS with Stack
def diameter_of_binary_tree_dfs(root: Optional[TreeNode]) -> int:
    """
    Calculates the diameter of a binary tree using iterative Depth-First Search (DFS) with a stack.
    This approach is similar to the BFS approach in that it explores nodes and their depths,
    but it uses a stack instead of a queue.  Like BFS, iterative DFS is not the most natural
    fit for the diameter problem, which is inherently about finding the longest path.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The diameter of the binary tree.
    """
    if not root:
        return 0  # Base case: if the root is None, the diameter is 0

    stack = [(root, 0)]  # Initialize a stack with the root node and its depth (0)
    max_diameter = 0  # Initialize the maximum diameter to 0

    while stack:
        node, depth = stack.pop()  # Pop a node and its depth from the stack
        left_depth = depth + 1 if node.left else 0  # Calculate the depth of the left child
        right_depth = depth + 1 if node.right else 0  # Calculate the depth of the right child
        max_diameter = max(max_diameter, left_depth + right_depth)  # Update max_diameter
        if node.left:
            stack.append((node.left, left_depth))  # Push the left child and its depth onto the stack
        if node.right:
            stack.append((node.right, right_depth))  # Push the right child and its depth onto the stack

    return max_diameter  # Return the maximum diameter

# Approach 4: Multithreaded Diameter Calculation
def diameter_of_binary_tree_multithreaded(root: Optional[TreeNode]) -> int:
    """
    Calculates the diameter of a binary tree using multiple threads. This approach attempts to
    improve performance by calculating the depths of the left and right subtrees concurrently.
    However, due to the Global Interpreter Lock (GIL) in Python, true parallelism is not achieved
    for CPU-bound tasks like this.  The overhead of thread management can sometimes outweigh any
    potential gains.  Also, the original 'diameter' was not being correctly updated across threads.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The diameter of the tree.
    """
    if not root:
        return 0

    def calculate_depth(node: Optional[TreeNode]) -> int:
        if not node:
            return 0
        left_depth = calculate_depth(node.left)
        right_depth = calculate_depth(node.right)
        return 1 + max(left_depth, right_depth)

    with concurrent.futures.ThreadPoolExecutor() as executor:
        left_future = executor.submit(calculate_depth, root.left)
        right_future = executor.submit(calculate_depth, root.right)
        left_depth = left_future.result()
        right_depth = right_future.result()
    return left_depth + right_depth

# Approach 5: Async Diameter Calculation
async def diameter_of_binary_tree_async(root: Optional[TreeNode]) -> int:
    """
    Calculates the diameter of a binary tree using asynchronous recursion. This approach
    leverages `asyncio` to potentially improve performance in I/O-bound scenarios. However,
    like multithreading, it doesn't offer true parallelism for CPU-bound tasks due to Python's GIL.
     The diameter calculation is inherently a recursive process of finding the maximum path
     between nodes.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The diameter of the tree.
    """
    if not root:
        return 0

    async def get_depth(node: Optional[TreeNode]) -> int:
        if not node:
            return 0
        left_depth, right_depth = await asyncio.gather(get_depth(node.left), get_depth(node.right))
        return 1 + max(left_depth, right_depth)

    left_depth = await get_depth(root.left)
    right_depth = await get_depth(root.right)
    return left_depth + right_depth
# Sample Usage
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("Recursive DFS Diameter:", diameter_of_binary_tree_recursive(tree))
print("BFS Diameter:", diameter_of_binary_tree_bfs(tree))
print("DFS Stack Diameter:", diameter_of_binary_tree_dfs(tree))
print("Multithreaded Diameter:", diameter_of_binary_tree_multithreaded(tree))

# Run Async Diameter Calculation
async def run_async():
    diameter = await diameter_of_binary_tree_async(tree)
    print("Async Diameter:", diameter)

asyncio.run(run_async())

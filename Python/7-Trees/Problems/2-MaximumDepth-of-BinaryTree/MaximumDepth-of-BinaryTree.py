from typing import Optional
from collections import deque
import threading
import asyncio
import multiprocessing

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

# Approach 1: Recursive DFS
def max_depth_recursive(root: Optional[TreeNode]) -> int:
    """
    Calculates the maximum depth of a binary tree using recursive Depth-First Search (DFS).

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The maximum depth of the tree.
    """
    if not root:
        return 0  # Base case: if the node is None, the depth is 0
    # Recursively calculate the depth of the left and right subtrees, and return the greater depth + 1
    return 1 + max(max_depth_recursive(root.left), max_depth_recursive(root.right))

# Approach 2: Iterative BFS using Queue
def max_depth_bfs(root: Optional[TreeNode]) -> int:
    """
    Calculates the maximum depth of a binary tree using iterative Breadth-First Search (BFS).

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The maximum depth of the tree.
    """
    if not root:
        return 0  # Base case: if the root is None, the depth is 0
    queue = deque([root])  # Initialize a queue with the root node
    depth = 0  # Initialize the depth counter
    while queue:
        depth += 1 # Increment depth at the start of each level
        for _ in range(len(queue)): # Iterate through all nodes at the current level
            node = queue.popleft()  # Dequeue a node
            if node.left:
                queue.append(node.left)  # Enqueue the left child if it exists
            if node.right:
                queue.append(node.right)  # Enqueue the right child if it exists
    return depth  # Return the final depth

# Approach 3: Iterative DFS using Stack
def max_depth_dfs(root: Optional[TreeNode]) -> int:
    """
    Calculates the maximum depth of a binary tree using iterative Depth-First Search (DFS) with a stack.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The maximum depth of the tree.
    """
    if not root:
        return 0  # Base case: if the root is None, the depth is 0
    stack = [(root, 1)]  # Initialize a stack with the root node and its depth (1)
    max_depth = 0  # Initialize the maximum depth
    while stack:
        node, depth = stack.pop()  # Pop a node and its depth from the stack
        max_depth = max(max_depth, depth)  # Update max_depth if the current depth is greater
        if node.left:
            stack.append((node.left, depth + 1))  # Push the left child and its depth onto the stack
        if node.right:
            stack.append((node.right, depth + 1))  # Push the right child and its depth onto the stack
    return max_depth  # Return the maximum depth

# Approach 4: Multithreaded Depth Calculation
def max_depth_multithreaded(root: Optional[TreeNode]) -> int:
    """
      Calculates the maximum depth of a binary tree using multiple threads.
      This approach attempts to improve performance by calculating the depths of the left
      and right subtrees concurrently.  However, due to the Global Interpreter Lock (GIL)
      in Python, true parallelism is not achieved for CPU-bound tasks like this.

      Args:
          root (Optional[TreeNode]): The root of the binary tree.

      Returns:
          int: The maximum depth of the tree.
      """
    if not root:
        return 0

    left_depth = 0
    right_depth = 0

    def calculate_left_depth():
        nonlocal left_depth
        left_depth = max_depth_recursive(root.left)

    def calculate_right_depth():
        nonlocal right_depth
        right_depth = max_depth_recursive(root.right)

    left_thread = threading.Thread(target=calculate_left_depth)
    right_thread = threading.Thread(target=calculate_right_depth)

    left_thread.start()
    right_thread.start()

    left_thread.join()
    right_thread.join()
    return 1 + max(left_depth, right_depth)
# Approach 5: Async Depth Calculation
async def max_depth_async(root: Optional[TreeNode]) -> int:
    """
    Calculates the maximum depth of a binary tree using asynchronous recursion.
    This approach leverages `asyncio` to potentially improve performance in I/O-bound
    scenarios, but it doesn't offer true parallelism for CPU-bound tasks due to Python's GIL.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The maximum depth of the tree.
    """
    if not root:
        return 0  # Base case: if the root is None, the depth is 0

    async def worker(node: Optional[TreeNode]) -> int:
        """
        An asynchronous helper function to recursively calculate the depth of a subtree.

        Args:
            node (Optional[TreeNode]): The root of the subtree.

        Returns:
            int: The depth of the subtree.
        """
        if not node:
            return 0  # Base case: if the node is None, the depth is 0
        # Use asyncio.gather to concurrently (but not truly in parallel due to GIL)
        # calculate the depths of the left and right subtrees
        left_depth, right_depth = await asyncio.gather(worker(node.left), worker(node.right))
        return 1 + max(left_depth, right_depth)  # Return the depth of the current node

    return await worker(root)  # Start the asynchronous recursion from the root

# Sample Usage
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("Recursive DFS Depth:", max_depth_recursive(tree))
print("BFS Depth:", max_depth_bfs(tree))
print("DFS Stack Depth:", max_depth_dfs(tree))
print("Multithreaded Depth:", max_depth_multithreaded(tree))

# Run Async Depth Calculation
async def run_async():
    depth = await max_depth_async(tree)
    print("Async Depth:", depth)

asyncio.run(run_async())

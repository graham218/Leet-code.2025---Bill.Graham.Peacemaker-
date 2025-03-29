from typing import Optional, List
from collections import deque
import threading
import asyncio

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

# Approach 1: Recursive DFS (Preorder)
def dfs_recursive_preorder(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree using recursion.
    This implementation uses a preorder traversal strategy:
    1. Visit the current node.
    2. Recursively traverse the left subtree.
    3. Recursively traverse the right subtree.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in preorder traversal order.
    """
    result = []  # Initialize an empty list to store the traversal result

    def dfs(node: Optional[TreeNode]):
        """
        Recursive helper function to perform the DFS traversal.

        Args:
            node (Optional[TreeNode]): The current node being visited.
        """
        if not node:
            return  # Base case: if the node is None, return (stop recursion)
        result.append(node.val)  # Preorder: Visit the node *before* its children
        dfs(node.left)          # Recursively traverse the left subtree
        dfs(node.right)         # Recursively traverse the right subtree

    dfs(root)  # Start the DFS traversal from the root of the tree
    return result  # Return the list of node values in preorder order

# Approach 2: Iterative DFS Using Stack (Preorder)
def dfs_iterative_preorder(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree using a stack.
    This implementation uses a preorder traversal strategy:
    1. Visit the current node.
    2. Push the right child onto the stack (if it exists).
    3. Push the left child onto the stack (if it exists).
    The left child is pushed last so it will be processed first (LIFO).

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in preorder traversal order.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list for the result
    stack = [root]  # Initialize a stack with the root node

    while stack:
        node = stack.pop()          # Pop the top node from the stack
        result.append(node.val)    # Visit the node (preorder)

        if node.right:
            stack.append(node.right)  # Push the right child onto the stack *first*
        if node.left:
            stack.append(node.left)   # Push the left child onto the stack *last*
            #  (so it's processed *next*)
    return result  # Return the preorder traversal list

# Approach 3: Multi-threaded DFS (Preorder)
def dfs_multithreaded(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Depth-First Search (DFS) traversal of a binary tree using
    multiple threads.  This implementation uses a preorder traversal strategy.
    However, due to Python's Global Interpreter Lock (GIL), true parallelism is not
    achieved, and this approach is generally *not* recommended for CPU-bound tasks
    like tree traversal.  It's included here for demonstration and comparison.  A lock
    is used to protect the shared result list.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in preorder traversal order.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize the result list
    lock = threading.Lock()  # Initialize a lock to protect access to 'result'

    def dfs(node: Optional[TreeNode]):
        """
        Recursive helper function to perform DFS in a thread.

        Args:
            node (Optional[TreeNode]): The current node being visited.
        """
        if not node:
            return  # Base case: if the node is None, return
        with lock:
            result.append(node.val)  # Preorder: Visit the node before its children.
            #  Use a lock to ensure thread-safe access to the shared 'result' list.
        left_thread = threading.Thread(target=dfs, args=(node.left,))  # Create thread for left subtree
        right_thread = threading.Thread(target=dfs, args=(node.right,)) # Create thread for right subtree
        left_thread.start()         # Start the left subtree thread
        right_thread.start()        # Start the right subtree thread
        left_thread.join()          # Wait for the left subtree thread to finish
        right_thread.join()         # Wait for the right subtree thread to finish

    dfs(root)  # Start the DFS traversal from the root
    return result  # Return the preorder traversal list

# Approach 4: Async DFS Using Coroutine (Preorder-like)
async def dfs_async(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Depth-First Search (DFS) traversal of a binary tree using
    asynchronous operations with `asyncio`.  This implementation is *not* a standard
    preorder traversal.  The use of a queue and `asyncio.sleep` makes it behave
    more like a level-order traversal with artificial delays, and the order of
    node processing is not guaranteed to be strictly DFS.  It's included as an
    example of using `asyncio` with a tree, but it's not a correct DFS implementation.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values, but *not* in standard preorder order.
    """
    if not root:
        return []
    result = []
    queue = deque([root])

    async def process_node(node: Optional[TreeNode]):
        """
        Asynchronous helper function to process a node.
        """
        if not node:
            return
        result.append(node.val)
        await asyncio.sleep(0.01)  # Simulate an asynchronous operation (e.g., I/O)
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

    while queue:
        node = queue.popleft()
        await process_node(node)

    return result

# Approach 5: DFS Using Generator (Preorder)
def dfs_generator(root: Optional[TreeNode]):
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree using a generator.
    This implementation uses a preorder traversal strategy and yields the node
    values one at a time.  Generators are memory-efficient for potentially large trees.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Yields:
        int: The value of the next node in the preorder traversal.
    """
    if not root:
        return  # Base case: if the root is None, return (generator stops)
    yield root.val        # Preorder: Yield the node's value *before* its children
    yield from dfs_generator(root.left)  # Yield values from the left subtree
    yield from dfs_generator(root.right) # Yield values from the right subtree

# Sample Tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))

# Execute different DFS methods
print("Recursive Preorder DFS:", dfs_recursive_preorder(tree))
print("Iterative Preorder DFS:", dfs_iterative_preorder(tree))
print("Multithreaded DFS:", dfs_multithreaded(tree))
print("Generator-based DFS:", list(dfs_generator(tree))) #convert generator to list for printing

# Run Async DFS
async def run_async():
    result = await dfs_async(tree)
    print("Async DFS:", result)

asyncio.run(run_async())

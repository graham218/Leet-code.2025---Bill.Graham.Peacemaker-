from typing import Optional, List, Dict
from collections import deque
import threading
import asyncio
import pickle
import json
import time

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

# Approach 1: Recursive DFS with Depth Tracking
def dfs_recursive_depth(root: Optional[TreeNode]) -> Dict[int, List[int]]:
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree using recursion
    and tracks the depth of each node.  It stores the node values in a dictionary,
    where the keys are the depths and the values are lists of node values at that depth.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        Dict[int, List[int]]: A dictionary where keys are node depths (starting from 0)
                            and values are lists of node values at that depth.
    """
    result = {}  # Initialize an empty dictionary to store the results

    def dfs(node: Optional[TreeNode], depth: int):
        """
        Recursive helper function to perform DFS and track depth.

        Args:
            node (Optional[TreeNode]): The current node being visited.
            depth (int): The depth of the current node.
        """
        if not node:
            return  # Base case: if the node is None, return
        if depth not in result:
            result[depth] = []  # If this depth is not in the dictionary, create a new list for it
        result[depth].append(node.val)  # Append the current node's value to the list for its depth
        dfs(node.left, depth + 1)  # Recursively traverse the left subtree, incrementing depth
        dfs(node.right, depth + 1)  # Recursively traverse the right subtree, incrementing depth

    dfs(root, 0)  # Start the DFS traversal from the root at depth 0
    return result  # Return the dictionary containing node values by depth

# Approach 2: DFS with Iterative Stack and Time Logging
def dfs_iterative_time(root: Optional[TreeNode]) -> List[int]:
    """
    Performs an iterative Depth-First Search (DFS) traversal of a binary tree using a stack
    and logs the time of visiting each node.  It uses a stack to mimic the call stack
    of a recursive DFS and records the time.time() when each node is visited.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in the order they are visited.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list to store the results
    stack = [(root, time.time())]  # Initialize the stack with a tuple: (node, timestamp)

    while stack:
        node, timestamp = stack.pop()  # Pop a node and its timestamp from the stack
        print(f"Visiting {node.val} at {time.ctime(timestamp)}")  # Print the node value and visit time
        result.append(node.val)  # Add the node's value to the result list

        if node.right:
            stack.append((node.right, time.time()))  # Push right child and its time onto the stack
        if node.left:
            stack.append((node.left, time.time()))    # Push left child and its time onto the stack
            # Left child is pushed last to be processed first (LIFO)
    return result  # Return the list of node values in visit order

# Approach 3: Multithreaded DFS with Locks
def dfs_multithreaded_lock(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Depth-First Search (DFS) traversal of a binary tree using multiple
    threads and a lock to protect shared data.  This approach is included for demonstration,
    but due to Python's Global Interpreter Lock (GIL), it does not achieve true parallelism
    for CPU-bound tasks like tree traversal.  A lock is used to ensure thread-safe access
    to the shared 'result' list.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in preorder traversal order.  Note that
                   the order may not be strictly guaranteed due to thread scheduling.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list to store the results
    lock = threading.Lock()  # Initialize a thread lock to protect the 'result' list

    def dfs(node: Optional[TreeNode]):
        """
        Recursive helper function to perform DFS in a separate thread.

        Args:
            node (Optional[TreeNode]): The current node being visited.
        """
        if not node:
            return  # Base case: if the node is None, return
        with lock:
            result.append(node.val)  # Acquire the lock before accessing the shared 'result' list
            #  This ensures that only one thread modifies 'result' at a time.
        left_thread = threading.Thread(target=dfs, args=(node.left,))  # Create a thread for the left subtree
        right_thread = threading.Thread(target=dfs, args=(node.right,)) # Create a thread for the right subtree
        left_thread.start()  # Start the left subtree thread
        right_thread.start()  # Start the right subtree thread
        left_thread.join()  # Wait for the left subtree thread to complete
        right_thread.join()  # Wait for the right subtree thread to complete

    dfs(root)  # Start the DFS traversal from the root
    return result  # Return the list of node values

# Approach 4: Async DFS with Task Queue
async def dfs_async_queue(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Depth-First Search (DFS) traversal of a binary tree using
    asynchronous operations with `asyncio` and a queue.  This approach is *not* a
    standard DFS implementation.  The use of a queue makes it behave more like a
    level-order traversal, and the `asyncio.sleep` introduces artificial delays.
    The order of node processing is not guaranteed to be strictly DFS. It's included
    as an example of using `asyncio` with a tree, but it's not a correct DFS.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values, but *not* in standard DFS order.
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

# Approach 5: DFS with Pickle Serialization
def dfs_pickle(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree by serializing the tree
    using pickle, then deserializing it, and then performing an iterative DFS with time logging
    on the deserialized tree.  This approach is inefficient due to the overhead of
    serialization and deserialization.  It's included primarily as a demonstration of
    an alternative (but not recommended) technique.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in the order they are visited
                   during the iterative DFS traversal of the deserialized tree.
    """
    if not root:
        return []
    serialized = pickle.dumps(root)  # Serialize the tree to a byte stream
    deserialized = pickle.loads(serialized)  # Deserialize the byte stream back to a tree
    return dfs_iterative_time(deserialized)  # Perform iterative DFS with time logging on the deserialized tree

# Approach 6: DFS with JSON Serialization
def dfs_json(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Depth-First Search (DFS) traversal of a binary tree by serializing the tree
    to a JSON string, deserializing it back into a tree structure, and then performing
    an iterative DFS with time logging on the deserialized tree. This approach is
    inefficient due to the overhead of JSON serialization and deserialization.
     It's included primarily as a demonstration of an alternative (but not recommended) technique.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]:  A list containing the node values in the order they are visited
                    during the iterative DFS traversal of the deserialized tree.
    """
    if not root:
        return []
    json_data = json.dumps(tree_to_dict(root))  # Serialize the tree to a JSON string
    root_dict = json.loads(json_data)  # Deserialize the JSON string back to a dictionary
    new_root = dict_to_tree(root_dict)  # Convert the dictionary back to a TreeNode object
    return dfs_iterative_time(new_root)  # Perform iterative DFS with time logging on the reconstructed tree

# Helper functions for JSON serialization
def tree_to_dict(root: Optional[TreeNode]) -> dict:
    """
    Helper function to convert a binary tree to a dictionary representation.
    This is used for JSON serialization.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        dict: A dictionary representation of the tree.
    """
    if not root:
        return None
    return {"val": root.val, "left": tree_to_dict(root.left), "right": tree_to_dict(root.right)}

def dict_to_tree(data: Optional[dict]) -> Optional[TreeNode]:
    """
    Helper function to convert a dictionary representation of a tree back to a binary tree.
    This is used for JSON deserialization.

    Args:
        data (Optional[dict]): The dictionary representation of the tree.

    Returns:
        Optional[TreeNode]: The root of the reconstructed binary tree.
    """
    if not data:
        return None
    return TreeNode(data["val"], dict_to_tree(data["left"]), dict_to_tree(data["right"]))

# Sample Tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))

# Execute different DFS methods
print("Recursive DFS with Depth:", dfs_recursive_depth(tree))
print("Iterative DFS with Time Logging:", dfs_iterative_time(tree))
print("Multithreaded DFS with Locks:", dfs_multithreaded_lock(tree))
print("Pickle Serialized DFS:", dfs_pickle(tree))
print("JSON Serialized DFS:", dfs_json(tree))

# Run Async DFS
async def run_async():
    result = await dfs_async_queue(tree)
    print("Async DFS with Task Queue:", result)

asyncio.run(run_async())

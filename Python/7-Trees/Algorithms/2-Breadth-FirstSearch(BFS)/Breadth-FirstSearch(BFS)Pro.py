from typing import Optional, List, Dict
from collections import deque
import threading
import asyncio
import heapq
import json
import time
import pickle

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

# Approach 1: BFS with Depth Tracking and Dictionary Output
def bfs_with_depth_tracking(root: Optional[TreeNode]) -> Dict[int, List[int]]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree and tracks the depth of each node.
    It stores the nodes at each depth in a dictionary.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        Dict[int, List[int]]: A dictionary where keys are node depths (starting from 0) and values are
                            lists of node values at that depth.
    """
    if not root:
        return {}  # Base case: return an empty dictionary if the tree is empty
    result = {}  # Initialize an empty dictionary to store the results (depth: [nodes])
    queue = deque([(root, 0)])  # Initialize a queue with the root node and its depth (0)

    while queue:
        node, depth = queue.popleft()  # Dequeue a node and its depth
        if depth not in result:
            result[depth] = []  # If this depth is not yet a key in the dictionary, create a new list
        result[depth].append(node.val)  # Append the node's value to the list at its depth
        if node.left:
            queue.append((node.left, depth + 1))  # Enqueue left child with incremented depth
        if node.right:
            queue.append((node.right, depth + 1))  # Enqueue right child with incremented depth
    return result  # Return the dictionary containing nodes at each depth

# Approach 2: BFS with Logging and Time Stamps
def bfs_with_logging(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree and logs the time of visiting each node.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS order.
    """
    if not root:
        return []  # Base case: return an empty list if the tree is empty
    result = []  # Initialize an empty list to store the results
    queue = deque([root])  # Initialize a queue with the root node

    while queue:
        node = queue.popleft()  # Dequeue a node
        timestamp = time.time()  # Get the current timestamp
        print(f"Visiting {node.val} at {time.ctime(timestamp)}")  # Log the node and timestamp
        result.append(node.val)  # Append the node's value to the result list
        if node.left:
            queue.append(node.left)  # Enqueue left child
        if node.right:
            queue.append(node.right)  # Enqueue right child
    return result  # Return the list of node values

# Approach 3: Multithreaded BFS Using a Thread Pool
def bfs_multithreaded_pool(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Breadth-First Search (BFS) traversal of a binary tree using a thread pool.
    This approach aims to improve performance by processing nodes concurrently, but the Global
    Interpreter Lock (GIL) in Python can limit the actual parallelism achieved for CPU-bound tasks.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS order.  The order of values in the result
                   list might not be strictly guaranteed due to the nature of multithreading.
    """
    if not root:
        return []  # Base case: return an empty list if the tree is empty
    result = []  # Initialize an empty list to store the results
    queue = deque([root])  # Initialize a queue with the root node
    lock = threading.Lock()  # Initialize a lock to protect access to the shared queue and result list

    def worker():
        """
        Worker function to be executed by each thread in the pool.  Each worker continuously
        dequeues a node, processes it, and enqueues its children until the queue is empty.
        """
        while True:
            with lock:  # Acquire the lock before accessing the shared queue
                if not queue:  # If the queue is empty, this thread has nothing more to process
                    break  # Exit the worker function
                node = queue.popleft()  # Dequeue a node
                result.append(node.val)  # Append the node's value to the result list
            if node.left:
                queue.append(node.left)  # Enqueue left child
            if node.right:
                queue.append(node.right)  # Enqueue right child

    threads = [threading.Thread(target=worker) for _ in range(4)]  # Create 4 worker threads
    for thread in threads:
        thread.start()  # Start each thread
    for thread in threads:
        thread.join()  # Wait for all threads to finish their work
    return result  # Return the list of node values

# Approach 4: Async BFS with Coroutines and Delay Simulation
async def bfs_async(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Breadth-First Search (BFS) traversal of a binary tree using asynchronous
    coroutines.  This approach is *not* a standard BFS implementation.  The use of `asyncio.sleep`
    introduces artificial delays, simulating asynchronous operations, but the order of node
    processing is not strictly guaranteed to follow BFS order.  This is more of a demonstration
    of using `asyncio` with a tree structure.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values.  The order of the values in the result list
                   might not be standard BFS order.
    """
    result = []  # Initialize the result list
    queue = deque([root])  # Initialize the queue

    async def process_node():
        """
        Asynchronous helper function to process nodes from the queue.
        """
        while queue:
            node = queue.popleft()
            result.append(node.val)
            await asyncio.sleep(0.01)  # Simulate an asynchronous operation (e.g., non-blocking I/O)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    await process_node()  # Start the asynchronous processing
    return result

# Approach 5: BFS with JSON Serialization
def bfs_json_serialization(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree by serializing the tree to a JSON
    string, deserializing it back to a tree, and then performing a standard BFS with logging on the
    deserialized tree.  This approach demonstrates using JSON serialization but is inefficient due to
    the overhead of serialization and deserialization.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS order (with time logging).
    """
    if not root:
        return []
    json_data = json.dumps(tree_to_dict(root))  # Serialize the tree to a JSON string
    root_dict = json.loads(json_data)  # Deserialize the JSON string back to a dictionary
    new_root = dict_to_tree(root_dict)  # Convert the dictionary back to a TreeNode object
    return bfs_with_logging(new_root)  # Perform BFS with logging on the reconstructed tree

# Approach 6: BFS with Pickle Serialization
def bfs_pickle_serialization(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree by serializing the tree using
    pickle, deserializing it back to a tree, and then performing a standard BFS with logging on the
    deserialized tree.  This approach demonstrates using pickle serialization but is inefficient
    due to the overhead of serialization and deserialization.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS order (with time logging).
    """
    if not root:
        return []
    serialized = pickle.dumps(root)  # Serialize the tree using pickle
    deserialized = pickle.loads(serialized)  # Deserialize the pickled data
    return bfs_with_logging(deserialized)  # Perform BFS with logging on the deserialized tree

# Helper functions for JSON serialization
def tree_to_dict(root: Optional[TreeNode]) -> dict:
    """
    Helper function to convert a binary tree to a dictionary representation for JSON serialization.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        dict: A dictionary representing the tree structure.
    """
    if not root:
        return None
    return {"val": root.val, "left": tree_to_dict(root.left), "right": tree_to_dict(root.right)}

def dict_to_tree(data: Optional[dict]) -> Optional[TreeNode]:
    """
    Helper function to convert a dictionary representation of a tree back to a TreeNode object.
    This is used for deserialization from JSON.

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

# Execute BFS methods
print("BFS with Depth Tracking:", bfs_with_depth_tracking(tree))
print("BFS with Logging:", bfs_with_logging(tree))
print("Multithreaded BFS:", bfs_multithreaded_pool(tree))
print("BFS with JSON Serialization:", bfs_json_serialization(tree))
print("BFS with Pickle Serialization:", bfs_pickle_serialization(tree))

# Run Async BFS
async def run_async():
    result = await bfs_async(tree)
    print("Async BFS:", result)

asyncio.run(run_async())

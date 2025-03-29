from typing import List, Optional
from collections import deque
import json
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

# Approach 1: BFS Using Queue
def level_order_bfs(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a level order traversal of a binary tree using Breadth-First Search (BFS).
    It processes nodes level by level, adding the value of each node to a list
    representing that level.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents the values
                         of the nodes at a given level.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize the result list to store the level order traversal
    queue = deque([root])  # Initialize a queue with the root node

    while queue:
        level = []  # List to store nodes at the current level
        for _ in range(len(queue)):  # Iterate through all nodes at the current level
            node = queue.popleft()  # Dequeue a node
            level.append(node.val)  # Add the node's value to the current level list
            if node.left:
                queue.append(node.left)  # Enqueue the left child if it exists
            if node.right:
                queue.append(node.right)  # Enqueue the right child if it exists
        result.append(level)  # Add the list of nodes at the current level to the result
    return result  # Return the 2D list representing the level order traversal

# Approach 2: Recursive DFS
def level_order_dfs(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a level order traversal of a binary tree using recursive Depth-First Search (DFS).
    It visits nodes recursively and keeps track of the depth to store the node's value
    in the correct level list.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents the values
                         of the nodes at a given level.
    """
    result = []  # Initialize the result list

    def dfs(node: Optional[TreeNode], depth: int):
        """
        Recursive helper function to perform DFS.

        Args:
            node (Optional[TreeNode]): The current node being visited.
            depth (int): The depth of the current node.
        """
        if not node:
            return  # Base case: if the node is None, return
        if len(result) <= depth:
            result.append([])  # If the level list doesn't exist, create it
        result[depth].append(node.val)  # Add the node's value to the corresponding level list
        dfs(node.left, depth + 1)  # Recursively visit the left child
        dfs(node.right, depth + 1)  # Recursively visit the right child

    dfs(root, 0)  # Start the DFS traversal from the root at depth 0
    return result  # Return the 2D list representing the level order traversal

# Approach 3: Multi-threaded BFS
def level_order_multithreaded(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Attempts to perform a level order traversal of a binary tree using multiple threads.
    However, due to Python's Global Interpreter Lock (GIL), this approach does not
    achieve true parallelism and may not provide significant performance improvements.
    It divides the processing of each level into a separate thread.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents the values
                         of the nodes at a given level.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize the result list
    queue = deque([root])  # Initialize a queue with the root node

    def process_level():
        """
        Helper function to process a single level of the tree.
        """
        level = []
        for _ in range(len(queue)):
            node = queue.popleft()
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        result.append(level)

    while queue:
        thread = threading.Thread(target=process_level)  # Create a thread for processing the current level
        thread.start()  # Start the thread
        thread.join()  # Wait for the thread to complete before moving to the next level
    return result  # Return the 2D list

# Approach 4: Async Level Order Traversal
async def level_order_async(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a level order traversal of a binary tree using asynchronous operations.
    This approach is similar to the multi-threaded version but uses `asyncio` instead
    of threads.  Like multithreading, it may not provide significant performance gains
    for CPU-bound tasks due to the GIL, but it's included for completeness and to
    demonstrate an alternative approach.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents the values
                         of the nodes at a given level.
    """
    if not root:
        return []
    result = []
    queue = deque([root])

    async def process_level():
        level = []
        for _ in range(len(queue)):
            node = queue.popleft()
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        result.append(level)

    while queue:
        await process_level()  # Await the completion of processing the current level
    return result

# Approach 5: JSON Serialization
def level_order_json(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a level order traversal of a binary tree by serializing the tree to a JSON
    string and then deserializing it back into a tree structure before performing a standard
    BFS traversal.  This approach is highly inefficient as it involves unnecessary
    serialization and deserialization.  It's included as a demonstration of an alternative
     (but not recommended) approach.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents the values
                         of the nodes at a given level.
    """
    if not root:
        return []
    json_data = json.dumps(tree_to_dict(root))  # Serialize the tree to a JSON string
    root_dict = json.loads(json_data)  # Deserialize the JSON string back to a dictionary
    new_root = dict_to_tree(root_dict)  # Convert the dictionary to a TreeNode
    return level_order_bfs(new_root)  # Perform BFS on the reconstructed tree

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

# Sample Usage
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))
print("BFS Level Order:", level_order_bfs(tree))
print("DFS Level Order:", level_order_dfs(tree))
print("Multi-threaded Level Order:", level_order_multithreaded(tree))
print("JSON Serialized Level Order:", level_order_json(tree))

# Run Async Level Order
async def run_async():
    result = await level_order_async(tree)
    print("Async Level Order:", result)

asyncio.run(run_async())

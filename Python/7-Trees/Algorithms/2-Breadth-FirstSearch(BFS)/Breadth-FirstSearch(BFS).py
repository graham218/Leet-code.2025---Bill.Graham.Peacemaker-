from typing import Optional, List
from collections import deque
import threading
import asyncio
import heapq

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

# Approach 1: Standard BFS Using Queue
def bfs_standard(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a standard Breadth-First Search (BFS) traversal of a binary tree using a queue.
    BFS explores all nodes at the current level before moving on to the next level.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS traversal order.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list to store the traversal result
    queue = deque([root])  # Initialize a queue with the root node

    while queue:
        node = queue.popleft()  # Dequeue (remove) the node at the front of the queue
        result.append(node.val)  # Visit the node (add its value to the result list)

        if node.left:
            queue.append(node.left)  # Enqueue the left child if it exists
        if node.right:
            queue.append(node.right)  # Enqueue the right child if it exists

    return result  # Return the list of node values in BFS order

# Approach 2: BFS with Level Tracking
def bfs_with_levels(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree and tracks the nodes
    at each level.  It returns a list of lists, where each inner list represents the
    nodes at a specific level in the tree.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list contains the node
                         values at a particular level.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list to store the level-wise results
    queue = deque([root])  # Initialize a queue with the root node

    while queue:
        level_size = len(queue)  # Get the number of nodes at the current level
        level = []  # Initialize an empty list to store the nodes at the current level

        for _ in range(level_size):  # Iterate through all nodes at the current level
            node = queue.popleft()  # Dequeue a node
            level.append(node.val)  # Add the node's value to the current level's list

            if node.left:
                queue.append(node.left)  # Enqueue the left child if it exists
            if node.right:
                queue.append(node.right)  # Enqueue the right child if it exists

        result.append(level)  # Add the list of nodes for the current level to the result
    return result  # Return the list of lists representing nodes at each level

# Approach 3: Multithreaded BFS
def bfs_multithreaded(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Breadth-First Search (BFS) traversal of a binary tree using
    multiple threads.  This approach is included for demonstration, but due to Python's
    Global Interpreter Lock (GIL), it does not achieve true parallelism for CPU-bound
    tasks like tree traversal.  It divides the processing of nodes among multiple threads,
    but the overhead of thread management and the GIL can limit performance gains.
    A lock is used to protect access to the shared queue and result list.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in BFS traversal order.  Note that
                   the order may not be strictly guaranteed due to thread scheduling.
    """
    if not root:
        return []  # Base case: if the root is None, return an empty list
    result = []  # Initialize an empty list to store the results
    queue = deque([root])  # Initialize a queue with the root node
    lock = threading.Lock()  # Initialize a lock to protect access to the shared queue and result

    def process_node():
        """
        Helper function to process nodes from the queue in a thread.
        """
        while queue:
            with lock:
                if not queue:  # Check if the queue is empty (another thread might have emptied it)
                    return  # If the queue is empty, exit the thread
                node = queue.popleft()  # Dequeue a node
                result.append(node.val)  # Append the node's value to the result list
            if node.left:
                queue.append(node.left)  # Enqueue the left child
            if node.right:
                queue.append(node.right)  # Enqueue the right child

    threads = [threading.Thread(target=process_node) for _ in range(4)]  # Create 4 threads
    for thread in threads:
        thread.start()  # Start each thread
    for thread in threads:
        thread.join()  # Wait for all threads to complete

    return result  # Return the list of node values

# Approach 4: Async BFS
def bfs_async(root: Optional[TreeNode]) -> List[int]:
    """
    Attempts to perform a Breadth-First Search (BFS) traversal of a binary tree using
    asynchronous operations with `asyncio`.  This approach is *not* a standard BFS
    implementation.  The use of `asyncio.sleep` introduces artificial delays, and the
    order of node processing is not strictly guaranteed to be correct BFS order.
    It's included as an example of using `asyncio` with a tree, but it's not a
    recommended way to implement BFS.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values, but *not* in standard BFS order.
    """
    result = []
    queue = deque([root])

    async def process_node():
        """
        Asynchronous helper function to process nodes from the queue.
        """
        while queue:
            node = queue.popleft()
            result.append(node.val)
            await asyncio.sleep(0.01)  # Simulate an asynchronous operation (e.g., I/O)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    asyncio.run(process_node())  # Run the asynchronous function
    return result

# Approach 5: BFS Using Priority Queue (Min-Heap)
def bfs_priority_queue(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a Breadth-First Search (BFS) traversal of a binary tree using a priority queue
    (min-heap).  This approach is *not* a standard or correct way to implement BFS.
    BFS is inherently a level-order traversal, and using a priority queue (which
    prioritizes nodes based on value) will not, in general, process nodes in the
    correct level order.  This is included as a demonstration of an alternative
    data structure, but it does not implement BFS correctly.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values, but *not* in standard BFS order.
    """
    if not root:
        return []
    result = []
    heap = [(0, root)]  # (Priority, Node).  Using node value as priority.

    while heap:
        _, node = heapq.heappop(heap)  # Pop the node with the smallest value
        result.append(node.val)  # Add the node's value to the result

        if node.left:
            heapq.heappush(heap, (node.left.val, node.left))  # Push left child with its value as priority
        if node.right:
            heapq.heappush(heap, (node.right.val, node.right))  # Push right child with its value as priority
    return result
# Sample Tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))

# Execute BFS methods
print("Standard BFS:", bfs_standard(tree))
print("BFS with Levels:", bfs_with_levels(tree))
print("Multithreaded BFS:", bfs_multithreaded(tree))
print("Priority Queue BFS:", bfs_priority_queue(tree))

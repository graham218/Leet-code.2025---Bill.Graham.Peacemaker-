from collections import deque, defaultdict
from typing import Dict, List, Optional

# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, neighbors: Optional[List['Node']] = None):
        """
        Initializes a Node object.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            neighbors (Optional[List['Node']], optional): A list of neighboring nodes.
                Defaults to an empty list if None is provided.
        """
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

# Approach 1: DFS using Recursion
# Time Complexity: O(N + E) | Space Complexity: O(N)
def cloneGraphDFSRecursive(node: 'Node') -> 'Node':
    """
    Clones an undirected graph using Depth-First Search (DFS) with recursion.

    Args:
        node ('Node'): The starting node of the graph to clone.

    Returns:
        'Node': The cloned graph's starting node.  Returns None if the input node is None.
    """
    if not node:
        return None  # Handle the case where the input node is None

    clone_map: Dict['Node', 'Node'] = {}  # Use a dictionary to store original to cloned node mapping

    def dfs(original: 'Node') -> 'Node':
        """
        Recursive helper function to perform DFS.

        Args:
            original ('Node'): The current node in the original graph being visited.

        Returns:
            'Node': The cloned node corresponding to the original node.
        """
        if original in clone_map:
            return clone_map[original]  # If the node is already cloned, return the clone

        copy = Node(original.val)  # Create a new node with the same value
        clone_map[original] = copy  # Store the mapping from original to clone

        for neighbor in original.neighbors:
            copy.neighbors.append(dfs(neighbor))  # Recursively clone neighbors and add to the copy's neighbors

        return copy

    return dfs(node)  # Start the DFS from the given node

# Approach 2: DFS using Stack
# Time Complexity: O(N + E) | Space Complexity: O(N)
def cloneGraphDFSStack(node: 'Node') -> 'Node':
    """
    Clones an undirected graph using Depth-First Search (DFS) with a stack (iterative).

    Args:
        node ('Node'): The starting node of the graph to clone.

    Returns:
        'Node': The cloned graph's starting node. Returns None if the input node is None.
    """
    if not node:
        return None  # Handle the case where the input node is None

    clone_map: Dict['Node', 'Node'] = {}  # Store mapping from original node to cloned node
    stack = [node]  # Use a stack for iterative DFS
    clone_map[node] = Node(node.val)  # Create the clone of the starting node and add to the map

    while stack:
        original = stack.pop()  # Get the next node to process
        for neighbor in original.neighbors:
            if neighbor not in clone_map:
                clone_map[neighbor] = Node(neighbor.val)  # Create clone if not already cloned
                stack.append(neighbor)  # Add neighbor to stack for processing
            clone_map[original].neighbors.append(clone_map[neighbor])  # Add cloned neighbor to cloned node's neighbors

    return clone_map[node]  # Return the clone of the starting node

# Approach 3: BFS using Queue
# Time Complexity: O(N + E) | Space Complexity: O(N)
def cloneGraphBFS(node: 'Node') -> 'Node':
    """
    Clones an undirected graph using Breadth-First Search (BFS).

    Args:
        node ('Node'): The starting node of the graph to clone.

    Returns:
        'Node': The cloned graph's starting node. Returns None if the input node is None.
    """
    if not node:
        return None # Handle empty graph
    clone_map: Dict['Node', 'Node'] = {node: Node(node.val)} # Store original to clone mapping, init with the first node clone
    queue = deque([node]) # Use a queue for BFS

    while queue:
        original = queue.popleft() # Dequeue the current node
        for neighbor in original.neighbors:
            if neighbor not in clone_map:
                clone_map[neighbor] = Node(neighbor.val) # Create clone if it doesn't exist
                queue.append(neighbor) # Enqueue the neighbor
            clone_map[original].neighbors.append(clone_map[neighbor]) # Add the cloned neighbor to the cloned node's neighbor list
    return clone_map[node]

# Approach 4: Using Dictionary to Store Clones
# Time Complexity: O(N + E) | Space Complexity: O(N)
def cloneGraphDict(node: 'Node') -> 'Node':
    """
    Clones an undirected graph using BFS and a defaultdict for concise clone creation.

    Args:
        node ('Node'): The starting node of the graph to clone.

    Returns:
        'Node': The cloned graph's starting node. Returns None if the input node is None.
    """
    if not node:
        return None
    clones: Dict['Node', 'Node'] = defaultdict(Node) # defaultdict simplifies node creation
    clones[node].val = node.val # Set the value of the cloned starting node
    queue = deque([node])

    while queue:
        original = queue.popleft()
        for neighbor in original.neighbors:
            if neighbor not in clones:
                clones[neighbor].val = neighbor.val # set the value of the cloned neighbor
                queue.append(neighbor)
            clones[original].neighbors.append(clones[neighbor])
    return clones[node]

# Approach 5: Iterative Deep Copy with Mapping
# Time Complexity: O(N + E) | Space Complexity: O(N)
def cloneGraphIterative(node: 'Node') -> 'Node':
    """
    Clones an undirected graph iteratively using a queue and a dictionary for mapping.

    Args:
        node ('Node'): The starting node of the graph.

    Returns:
        'Node': The cloned graph's starting node.
    """
    if not node:
        return None

    mapping: Dict['Node', 'Node'] = {} # Dictionary to store mapping between original and cloned nodes.
    queue = deque([node]) # Queue for iterative BFS traversal.
    mapping[node] = Node(node.val) # Create the clone of the starting node.

    while queue:
        current = queue.popleft() # Get the next node from the queue.
        for neighbor in current.neighbors:
            if neighbor not in mapping:
                mapping[neighbor] = Node(neighbor.val) # Create a clone if it doesn't exist.
                queue.append(neighbor) # Add the neighbor to the queue for processing.
            mapping[current].neighbors.append(mapping[neighbor]) # Add the cloned neighbor to the current clone's neighbors.
    return mapping[node] # Return the cloned starting node.

# Function to Print Graph (for verification)
def printGraph(node: 'Node'):
    """
    Prints the graph structure in a readable format.  Uses BFS to traverse.

    Args:
        node ('Node'): The starting node of the graph to print.
    """
    if not node:
        print("Graph is empty")
        return

    visited = set()
    queue = deque([node])

    while queue:
        current = queue.popleft()
        if current in visited:
            continue
        visited.add(current)
        neighbor_vals = [n.val for n in current.neighbors] # Collect neighbor values for printing
        print(f"Node {current.val}: {neighbor_vals}")
        queue.extend(current.neighbors)

# Example Usage
if __name__ == "__main__":
    # Create a sample graph: 1 -- 2 -- 3 -- 1
    node1 = Node(1)
    node2 = Node(2)
    node3 = Node(3)
    node1.neighbors = [node2, node3]
    node2.neighbors = [node1, node3]
    node3.neighbors = [node1, node2]

    print("Original Graph:")
    printGraph(node1)

    print("\nCloned Graph (DFS Recursive):")
    cloned_graph_dfs = cloneGraphDFSRecursive(node1)
    printGraph(cloned_graph_dfs)

    print("\nCloned Graph (DFS Stack):")
    cloned_graph_dfs_stack = cloneGraphDFSStack(node1)
    printGraph(cloned_graph_dfs_stack)

    print("\nCloned Graph (BFS):")
    cloned_graph_bfs = cloneGraphBFS(node1)
    printGraph(cloned_graph_bfs)

    print("\nCloned Graph (Dict):")
    cloned_graph_dict = cloneGraphDict(node1)
    printGraph(cloned_graph_dict)

    print("\nCloned Graph (Iterative):")
    cloned_graph_iterative = cloneGraphIterative(node1)
    printGraph(cloned_graph_iterative)

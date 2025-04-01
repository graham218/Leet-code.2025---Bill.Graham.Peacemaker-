from collections import deque
from typing import List, Dict, Set, Tuple

# Define a simple graph representation using an adjacency list
Graph = Dict[int, List[int]]

def create_graph() -> Graph:
    """
    Creates a sample graph for demonstration purposes.
    The graph is represented as a dictionary where keys are nodes
    and values are lists of their neighbors.

    Returns:
        Graph: A dictionary representing the graph.
    """
    graph: Graph = {
        0: [1, 2],
        1: [0, 3, 4],
        2: [0, 4],
        3: [1, 5],
        4: [1, 2, 5],
        5: [3, 4],
    }
    return graph

# 1. Iterative BFS with a Queue (Standard Approach)
def bfs_iterative_queue(graph: Graph, start_node: int) -> List[int]:
    """
    Performs Breadth-First Search (BFS) on a graph using an iterative approach
    with a queue.  This is the most common and straightforward way to implement BFS.

    Args:
        graph: The graph to traverse (represented as an adjacency list).
        start_node: The node to start the BFS traversal from.

    Returns:
        List[int]: A list of nodes visited in BFS order.
    """
    visited: Set[int] = set()  # Keep track of visited nodes to avoid cycles.
    queue: deque[int] = deque([start_node])  # Use a deque for efficient FIFO operations.
    visited.add(start_node)
    traversal_order: List[int] = []  # Store the order in which nodes are visited.

    print(f"\n1. Iterative BFS with Queue starting from node {start_node}:") # Output Approach Name

    while queue:
        node = queue.popleft()  # Get the next node from the front of the queue.
        traversal_order.append(node)  # Add the node to the result list.

        # Explore the neighbors of the current node.
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)  # Mark the neighbor as visited.
                queue.append(neighbor)  # Add the neighbor to the back of the queue.
    return traversal_order

# 2. Iterative BFS with Queue and Path Reconstruction
def bfs_iterative_path(graph: Graph, start_node: int, target_node: int) -> Tuple[List[int], List[int]]:
    """
    Performs BFS and reconstructs the shortest path from the start node to a target node.

    Args:
        graph: The graph to traverse.
        start_node: The starting node.
        target_node: The destination node.

    Returns:
        Tuple[List[int], List[int]]: A tuple containing:
            - The BFS traversal order.
            - The shortest path from start_node to target_node (or an empty list if no path exists).
    """
    visited: Set[int] = set()
    queue: deque[int] = deque([start_node])
    visited.add(start_node)
    traversal_order: List[int] = []
    parent: Dict[int, int] = {}  # Store the parent of each node in the path.
    path: List[int] = [] # Initialize path

    print(f"\n2. Iterative BFS with Path Reconstruction from {start_node} to {target_node}:") # Output Approach Name

    while queue:
        node = queue.popleft()
        traversal_order.append(node)

        if node == target_node:
            break  # Stop BFS if the target node is found.

        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
                parent[neighbor] = node  # Record the parent of the neighbor.

    # Reconstruct the path from target to start
    if target_node in parent:
        node = target_node
        while node != start_node:
            path.insert(0, node)  # Insert at the beginning to build path in correct order
            node = parent[node]
        path.insert(0, start_node)  # Add the start node to the beginning of the path.

    return traversal_order, path

# 3. Recursive BFS (Less Common, Not Recommended for Large Graphs)
def bfs_recursive(graph: Graph, start_node: int) -> List[int]:
    """
    Performs BFS using a recursive approach.  This is less common and
    can be less efficient than the iterative approach, especially for large graphs
    due to the overhead of recursive function calls and potential stack overflow issues.

    Args:
        graph: The graph to traverse.
        start_node: The starting node.

    Returns:
        List[int]: A list of nodes visited in BFS order.
    """
    visited: Set[int] = set()
    traversal_order: List[int] = []
    queue: deque[int] = deque([start_node]) # Initialize queue

    print(f"\n3. Recursive BFS starting from node {start_node}:") # Output Approach Name

    def _bfs_recursive_helper(queue: deque[int], visited: Set[int], traversal_order: List[int]):
        """
        Helper function to perform the recursive BFS traversal.

        Args:
            queue (deque): The queue of nodes to visit.
            visited (Set[int]): The set of visited nodes.
            traversal_order (List[int]): The list of nodes in traversal order.
        """
        if not queue:
            return  # Base case: the queue is empty, so we're done.

        node = queue.popleft()
        if node not in visited: # check if the node is visited
            visited.add(node)
            traversal_order.append(node)

            for neighbor in graph[node]:
                if neighbor not in visited:
                    queue.append(neighbor)  # Add neighbors to the queue

            _bfs_recursive_helper(queue, visited, traversal_order)  # Recursive call

    _bfs_recursive_helper(queue, visited, traversal_order)
    return traversal_order

# 4. BFS with Distance Tracking
def bfs_with_distance(graph: Graph, start_node: int) -> Dict[int, int]:
    """
    Performs BFS and calculates the distance (number of edges) from the start node
    to every other reachable node in the graph.

    Args:
        graph: The graph to traverse.
        start_node: The starting node.

    Returns:
        Dict[int, int]: A dictionary where keys are nodes and values are their
                        distances from the start node.  Nodes not reachable
                        from the start node will not be present in the dictionary.
    """
    visited: Set[int] = set()
    queue: deque[int] = deque([start_node])
    visited.add(start_node)
    distances: Dict[int, int] = {start_node: 0}  # Distance from start to itself is 0.

    print(f"\n4. BFS with Distance Tracking starting from node {start_node}:") # Output Approach Name
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
                distances[neighbor] = distances[node] + 1  # Distance is one more than the parent.
    return distances

# 5. BFS on a Disconnected Graph
def bfs_disconnected_graph(graph: Graph) -> List[List[int]]:
    """
    Performs BFS on a disconnected graph, visiting all components.

    Args:
        graph: The graph to traverse.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents
                         the nodes visited in a separate BFS traversal
                         for each connected component.
    """
    visited: Set[int] = set()
    components: List[List[int]] = []

    print(f"\n5. BFS on a Disconnected Graph:") # Output Approach Name

    for node in graph:
        if node not in visited:
            # Start a new BFS traversal for each unvisited node (component).
            queue: deque[int] = deque([node])
            visited.add(node)
            component_traversal: List[int] = []

            while queue:
                curr_node = queue.popleft()
                component_traversal.append(curr_node)
                for neighbor in graph[curr_node]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            components.append(component_traversal)
    return components

if __name__ == "__main__":
    sample_graph = create_graph()

    # 1. Iterative BFS
    bfs_result_1 = bfs_iterative_queue(sample_graph, 0)
    print(f"BFS Traversal: {bfs_result_1}")  # Output: [0, 1, 2, 3, 4, 5]

    # 2. Iterative BFS with Path Reconstruction
    start_node = 0
    target_node = 5
    bfs_result_2, path = bfs_iterative_path(sample_graph, start_node, target_node)
    print(f"BFS Traversal: {bfs_result_2}") # Output: [0, 1, 2, 3, 4, 5]
    print(f"Shortest Path from {start_node} to {target_node}: {path}")  # Output: [0, 1, 3, 5]

    # 3. Recursive BFS
    bfs_result_3 = bfs_recursive(sample_graph, 0)
    print(f"BFS Traversal: {bfs_result_3}")  # Output: [0, 1, 2, 3, 4, 5]

    # 4. BFS with Distance Tracking
    distances = bfs_with_distance(sample_graph, 0)
    print(f"Distances from node 0: {distances}")  # Output: {0: 0, 1: 1, 2: 1, 3: 2, 4: 2, 5: 3}

    # 5. BFS on a Disconnected Graph (Modified graph to be disconnected)
    disconnected_graph: Graph = {
        0: [1, 2],
        1: [0, 3],
        2: [0, 4],
        3: [1],
        4: [2],
        5: [6],  # Added disconnected component
        6: [5],  # Added disconnected component
        7: [],
        8: [9],
        9: [8]
    }
    components = bfs_disconnected_graph(disconnected_graph)
    print(f"Connected Components: {components}")  # Output: [[0, 1, 2, 3, 4], [5, 6], [7], [8, 9]]

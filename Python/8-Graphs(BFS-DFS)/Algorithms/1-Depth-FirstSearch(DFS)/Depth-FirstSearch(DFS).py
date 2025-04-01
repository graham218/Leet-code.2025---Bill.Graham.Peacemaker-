# Graph Traversal - Depth First Search (DFS)

# Detailed Explanation:
# Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible
# along each branch before backtracking.  It uses a stack (implicitly with recursion,
# or explicitly with a stack data structure) to keep track of the next node to visit.

# Key Concepts:
# - Vertex (Node): A point in the graph.
# - Edge: A connection between two vertices.
# - Graph: A collection of vertices and edges.
# - Traversal: The process of visiting all vertices in a graph.
# - Stack: A LIFO (Last-In, First-Out) data structure.
# - Recursion: A programming technique where a function calls itself.

# Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
# Space Complexity: O(V) in the worst case (when the graph is a linear chain), due to the
#                   stack (recursion stack or explicit stack).

# 1. Recursive DFS (Adjacency List)
def dfs_recursive_adj_list(graph, start_node, visited=None):
    """
    Performs DFS traversal of a graph using recursion.
    The graph is represented as an adjacency list.

    Args:
        graph: An adjacency list representing the graph.
               Example: {
                   'A': ['B', 'C'],
                   'B': ['D', 'E'],
                   'C': ['F'],
                   'D': [],
                   'E': ['F'],
                   'F': []
               }
        start_node: The node to start the DFS traversal from.
        visited: A set to keep track of visited nodes.  Defaults to None, creating a new set.

    Returns:
        A list of nodes visited in DFS order.
    """
    if visited is None:
        visited = set()  # Initialize visited set if not provided
    visited.add(start_node)  # Mark the current node as visited
    print(f"Visiting node: {start_node}") # Output the current node being visited
    result = [start_node] # start the result list

    # Iterate through neighbors (adjacent nodes)
    for neighbor in graph.get(start_node, []):  # handles the case where a node has no neighbors.
        if neighbor not in visited:
            result.extend(dfs_recursive_adj_list(graph, neighbor, visited)) # Extend the result list
    return result

# 2. Iterative DFS (Adjacency List)
def dfs_iterative_adj_list(graph, start_node):
    """
    Performs DFS traversal of a graph using a stack (iterative approach).
    The graph is represented as an adjacency list.

    Args:
        graph: An adjacency list representing the graph.
        start_node: The node to start the DFS traversal from.

    Returns:
        A list of nodes visited in DFS order.
    """
    visited = set()  # Set to store visited nodes
    stack = [start_node]  # Stack to store nodes to visit, initialize with the start node.
    result = [] # Initialize result list

    while stack:
        node = stack.pop()  # Get the next node from the stack
        if node not in visited:
            visited.add(node)  # Mark the node as visited
            print(f"Visiting node: {node}") # print
            result.append(node) # add to result
            # Add neighbors to the stack in reverse order to maintain DFS order.
            #  get(node, []) handles the case where a node has no neighbors.
            neighbors = graph.get(node, [])
            stack.extend(neighbors[::-1])  # Push neighbors onto the stack
    return result

# 3. Recursive DFS (Adjacency Matrix)
def dfs_recursive_adj_matrix(matrix, start_node, visited=None):
    """
    Performs DFS traversal of a graph using recursion.
    The graph is represented as an adjacency matrix.

    Args:
        matrix: An adjacency matrix representing the graph.
                Example:
                    [[0, 1, 1, 0, 0, 0],  # A
                     [0, 0, 0, 1, 1, 0],  # B
                     [0, 0, 0, 0, 0, 1],  # C
                     [0, 0, 0, 0, 0, 0],  # D
                     [0, 0, 0, 0, 0, 1],  # E
                     [0, 0, 0, 0, 0, 0]]  # F
        start_node: The node to start the DFS traversal from (index in the matrix).
        visited: A set to keep track of visited nodes.

    Returns:
        A list of nodes visited in DFS order.
    """
    num_nodes = len(matrix)
    if visited is None:
        visited = set()
    visited.add(start_node)
    print(f"Visiting node: {chr(65 + start_node)}")  # Convert index to character (A, B, C, ...)
    result = [chr(65 + start_node)]

    for neighbor in range(num_nodes):
        if matrix[start_node][neighbor] == 1 and neighbor not in visited:
            result.extend(dfs_recursive_adj_matrix(matrix, neighbor, visited))
    return result


# 4. Iterative DFS (Adjacency Matrix)
def dfs_iterative_adj_matrix(matrix, start_node):
    """
    Performs DFS traversal of a graph using a stack (iterative approach).
    The graph is represented as an adjacency matrix.

    Args:
        matrix: An adjacency matrix representing the graph.
        start_node: The node to start the DFS traversal from (index in the matrix).

    Returns:
        A list of nodes visited in DFS order.
    """
    num_nodes = len(matrix)
    visited = set()
    stack = [start_node]
    result = []

    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            print(f"Visiting node: {chr(65 + node)}")
            result.append(chr(65 + node))
            neighbors = []
            for i in range(num_nodes):
                if matrix[node][i] == 1:
                    neighbors.append(i)
            stack.extend(neighbors[::-1])
    return result

# 5. DFS with Path Reconstruction (Adjacency List)
def dfs_path(graph, start_node, target_node, visited=None, path=None):
    """
    Performs DFS to find a path between a start and target node.

    Args:
        graph: An adjacency list representing the graph.
        start_node: The node to start the DFS traversal from.
        target_node: The node to find a path to.
        visited: A set to keep track of visited nodes.
        path: The current path being explored.

    Returns:
        A list representing the path from start_node to target_node, or None if no path exists.
    """
    if visited is None:
        visited = set()
    if path is None:
        path = [start_node]

    visited.add(start_node)

    if start_node == target_node:
        return path

    for neighbor in graph.get(start_node, []):
        if neighbor not in visited:
            new_path = list(path)  # Create a copy of the path
            new_path.append(neighbor)
            result_path = dfs_path(graph, neighbor, target_node, visited, new_path) # corrected variable name
            if result_path:
                return result_path
    return None # Explicitly return None if no path is found

if __name__ == "__main__":
    # Example Graph (Adjacency List)
    graph_adj_list = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': [],
        'E': ['F'],
        'F': []
    }

    # Example Graph (Adjacency Matrix)
    graph_adj_matrix = [
        [0, 1, 1, 0, 0, 0],  # A
        [0, 0, 0, 1, 1, 0],  # B
        [0, 0, 0, 0, 0, 1],  # C
        [0, 0, 0, 0, 0, 0],  # D
        [0, 0, 0, 0, 0, 1],  # E
        [0, 0, 0, 0, 0, 0]   # F
    ]
    print("1. Recursive DFS (Adjacency List):")
    result_recursive_adj_list = dfs_recursive_adj_list(graph_adj_list, 'A')
    print("DFS Traversal (Recursive, Adjacency List):", result_recursive_adj_list)
    # Expected output:  Visiting node: A
    #                   Visiting node: B
    #                   Visiting node: D
    #                   Visiting node: E
    #                   Visiting node: F
    #                   Visiting node: C
    #                   Visiting node: F
    #                   DFS Traversal (Recursive, Adjacency List): ['A', 'B', 'D', 'E', 'F', 'C', 'F']

    print("\n2. Iterative DFS (Adjacency List):")
    result_iterative_adj_list = dfs_iterative_adj_list(graph_adj_list, 'A')
    print("DFS Traversal (Iterative, Adjacency List):", result_iterative_adj_list)
    # Expected output: Visiting node: A
    #                  Visiting node: C
    #                  Visiting node: B
    #                  Visiting node: E
    #                  Visiting node: F
    #                  Visiting node: D
    #                  DFS Traversal (Iterative, Adjacency List): ['A', 'C', 'B', 'E', 'F', 'D']

    print("\n3. Recursive DFS (Adjacency Matrix):")
    result_recursive_adj_matrix = dfs_recursive_adj_matrix(graph_adj_matrix, 0)  # Start from node A (index 0)
    print("DFS Traversal (Recursive, Adjacency Matrix):", result_recursive_adj_matrix)
    # Expected output:
    # Visiting node: A
    # Visiting node: B
    # Visiting node: D
    # Visiting node: E
    # Visiting node: F
    # Visiting node: C
    # DFS Traversal (Recursive, Adjacency Matrix): ['A', 'B', 'D', 'E', 'F', 'C']

    print("\n4. Iterative DFS (Adjacency Matrix):")
    result_iterative_adj_matrix = dfs_iterative_adj_matrix(graph_adj_matrix, 0)
    print("DFS Traversal (Iterative, Adjacency Matrix):", result_iterative_adj_matrix)
    # Expected output:
    # Visiting node: A
    # Visiting node: C
    # Visiting node: B
    # Visiting node: E
    # Visiting node: F
    # Visiting node: D
    # DFS Traversal (Iterative, Adjacency Matrix): ['A', 'C', 'B', 'E', 'F', 'D']

    print("\n5. DFS with Path Reconstruction (Adjacency List):")
    start_node = 'A'
    target_node = 'F'
    path = dfs_path(graph_adj_list, start_node, target_node)
    if path:
        print(f"Path from {start_node} to {target_node}: {path}")
    else:
        print(f"No path found from {start_node} to {target_node}")
    # Expected output:
    # Path from A to F: ['A', 'C', 'F']  OR ['A', 'B', 'E', 'F']

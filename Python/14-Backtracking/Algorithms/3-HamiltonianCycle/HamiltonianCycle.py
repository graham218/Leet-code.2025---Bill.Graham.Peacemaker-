"""
Hamiltonian Cycle Problem:

Given a graph, determine if a Hamiltonian cycle exists. A Hamiltonian cycle is a
path that visits every vertex exactly once and returns to the starting vertex.

This implementation provides five different approaches to solve the Hamiltonian Cycle
problem using backtracking:

1.  **Basic Backtracking:** A straightforward recursive backtracking approach.
2.  **Backtracking with Adjacency Matrix:** Uses an adjacency matrix
    representation of the graph.
3.  **Backtracking with Early Pruning:** Optimizes the basic backtracking
    approach by adding a condition to check if a node is a dead end.
4.  **Backtracking with Degree Check:** Adds a degree check for each node
    before starting the backtracking to quickly rule out impossible graphs.
5. **Backtracking with Iterative Approach:** Uses a stack-based iterative approach.

Each approach includes detailed comments to explain the logic and workings of the algorithm.
"""

def is_safe(v, graph, path, pos):
    """
    Checks if vertex v can be added to the current path.

    Args:
        v: The vertex to check.
        graph: The graph represented as an adjacency list.
        path: The current path being constructed.
        pos: The current position in the path.

    Returns:
        True if the vertex can be added, False otherwise.
    """
    # Check if this vertex is an adjacent vertex of the previously added vertex.
    if graph[path[pos - 1]][v] == 0:
        return False

    # Check if the vertex has already been included in the path.  A Hamiltonian
    # cycle should not have repeated vertices.
    for vertex in path:
        if vertex == v:
            return False

    return True

def hamiltonian_cycle_util(graph, path, pos, num_vertices):
    """
    Recursive utility function to find a Hamiltonian cycle using backtracking.

    Args:
        graph: The graph represented as an adjacency list.
        path: The current path being constructed.
        pos: The current position in the path.
        num_vertices: Total number of vertices in the graph.

    Returns:
        True if a Hamiltonian cycle is found, False otherwise.
    """
    # Base case: If all vertices are included in the path
    if pos == num_vertices:
        # Check if there is an edge from the last vertex to the starting vertex.
        if graph[path[pos - 1]][path[0]] == 1:
            return True
        else:
            return False

    # Try different vertices as the next vertex in the path
    for v in range(num_vertices):
        if is_safe(v, graph, path, pos):
            path[pos] = v
            # Recursively try to construct the rest of the path
            if hamiltonian_cycle_util(graph, path, pos + 1, num_vertices):
                return True
            # Backtrack: If adding vertex v doesn't lead to a solution, remove it
            path[pos] = -1

    # If no vertex can be added to the path, return False
    return False

def hamiltonian_cycle(graph):
    """
    Finds a Hamiltonian cycle in the given graph using backtracking.

    Args:
        graph: The graph represented as an adjacency list.

    Returns:
        A list representing the Hamiltonian cycle, or None if no cycle exists.
    """
    num_vertices = len(graph)
    path = [-1] * num_vertices  # Initialize the path with -1
    path[0] = 0  # Start the path from vertex 0

    if hamiltonian_cycle_util(graph, path, 1, num_vertices):
        return path
    else:
        return None

def print_cycle(cycle):
    """
    Prints the Hamiltonian cycle.

    Args:
        cycle: A list representing the Hamiltonian cycle.
    """
    if cycle is None:
        print("No Hamiltonian cycle exists.")
    else:
        print("Hamiltonian Cycle:", end=" ")
        for vertex in cycle:
            print(vertex, end=" ")
        print(cycle[0])  # Print the starting vertex again to complete the cycle

def basic_backtracking_example():
    """
    Example usage of the basic backtracking approach.
    """
    print("\n--- Basic Backtracking Example ---")
    # Example graph represented as an adjacency list
    graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
    ]
    cycle = hamiltonian_cycle(graph)
    print_cycle(cycle)
    # Example graph with no Hamiltonian Cycle
    graph2 = [
        [0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1],
        [0, 0, 0, 1, 0],
    ]
    cycle2 = hamiltonian_cycle(graph2)
    print_cycle(cycle2)

def is_safe_matrix(v, graph, path, pos):
    """
    Checks if vertex v can be added to the current path, using an adjacency matrix.

    Args:
        v: The vertex to check.
        graph: The graph represented as an adjacency matrix.
        path: The current path being constructed.
        pos: The current position in the path.

    Returns:
        True if the vertex can be added, False otherwise.
    """
    if graph[path[pos - 1]][v] == 0:
        return False
    for vertex in path:
        if vertex == v:
            return False
    return True

def hamiltonian_cycle_util_matrix(graph, path, pos, num_vertices):
    """
    Recursive utility function to find a Hamiltonian cycle using an adjacency matrix.

    Args:
        graph: The graph represented as an adjacency matrix.
        path: The current path being constructed.
        pos: The current position in the path.
        num_vertices: The number of vertices in the graph.

    Returns:
        True if a Hamiltonian cycle is found, False otherwise.
    """
    if pos == num_vertices:
        if graph[path[pos - 1]][path[0]] == 1:
            return True
        else:
            return False

    for v in range(num_vertices):
        if is_safe_matrix(v, graph, path, pos):
            path[pos] = v
            if hamiltonian_cycle_util_matrix(graph, path, pos + 1, num_vertices):
                return True
            path[pos] = -1
    return False

def hamiltonian_cycle_matrix(graph):
    """
    Finds a Hamiltonian cycle in the given graph represented as an adjacency matrix.

    Args:
        graph: The graph represented as an adjacency matrix.

    Returns:
        A list representing the Hamiltonian cycle, or None if no cycle exists.
    """
    num_vertices = len(graph)
    path = [-1] * num_vertices
    path[0] = 0
    if hamiltonian_cycle_util_matrix(graph, path, 1, num_vertices):
        return path
    else:
        return None

def backtracking_with_adjacency_matrix_example():
    """
    Example usage of the backtracking approach with an adjacency matrix.
    """
    print("\n--- Backtracking with Adjacency Matrix Example ---")
    # Example graph represented as an adjacency matrix
    graph_matrix = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
    ]
    cycle_matrix = hamiltonian_cycle_matrix(graph_matrix)
    print_cycle(cycle_matrix)

    graph_matrix_2 = [
        [0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1],
        [0, 0, 0, 1, 0],
    ]
    cycle_matrix_2 = hamiltonian_cycle_matrix(graph_matrix_2)
    print_cycle(cycle_matrix_2)

def is_safe_pruning(v, graph, path, pos):
    """
    Checks if vertex v can be added to the current path, with early pruning.

    Args:
        v: The vertex to check.
        graph: The graph represented as an adjacency list.
        path: The current path being constructed.
        pos: The current position in the path.

    Returns:
        True if the vertex can be added, False otherwise.
    """
    if graph[path[pos - 1]][v] == 0:
        return False
    for vertex in path:
        if vertex == v:
            return False
    return True

def hamiltonian_cycle_util_pruning(graph, path, pos, num_vertices):
    """
    Recursive utility function to find a Hamiltonian cycle with early pruning.

    Args:
        graph: The graph represented as an adjacency list.
        path: The current path being constructed.
        pos: The current position in the path.
        num_vertices: The number of vertices in the graph.

    Returns:
        True if a Hamiltonian cycle is found, False otherwise.
    """
    if pos == num_vertices:
        if graph[path[pos - 1]][path[0]] == 1:
            return True
        else:
            return False

    for v in range(num_vertices):
        if is_safe_pruning(v, graph, path, pos):
            path[pos] = v
            if hamiltonian_cycle_util_pruning(graph, path, pos + 1, num_vertices):
                return True
            path[pos] = -1
    return False

def hamiltonian_cycle_pruning(graph):
    """
    Finds a Hamiltonian cycle in the given graph using backtracking with early pruning.

    Args:
        graph: The graph represented as an adjacency list.

    Returns:
        A list representing the Hamiltonian cycle, or None if no cycle exists.
    """
    num_vertices = len(graph)
    path = [-1] * num_vertices
    path[0] = 0
    if hamiltonian_cycle_util_pruning(graph, path, 1, num_vertices):
        return path
    else:
        return None

def backtracking_with_early_pruning_example():
    """
    Example usage of the backtracking approach with early pruning.
    """
    print("\n--- Backtracking with Early Pruning Example ---")
    graph_pruning = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
    ]
    cycle_pruning = hamiltonian_cycle_pruning(graph_pruning)
    print_cycle(cycle_pruning)

    graph_pruning_2 = [
        [0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1],
        [0, 0, 0, 1, 0],
    ]
    cycle_pruning_2 = hamiltonian_cycle_pruning(graph_pruning_2)
    print_cycle(cycle_pruning_2)

def has_valid_degree(graph):
    """
    Checks if the graph has a valid degree for a Hamiltonian Cycle.
    A Hamiltonian cycle requires that every vertex has a degree of at least 2.

    Args:
        graph: The graph represented as an adjacency list.

    Returns:
        True if every vertex has a degree of 2 or more, False otherwise.
    """
    num_vertices = len(graph)
    for i in range(num_vertices):
        degree = sum(graph[i])
        if degree < 2:
            return False
    return True

def hamiltonian_cycle_util_degree_check(graph, path, pos, num_vertices):
    """
    Recursive utility function to find a Hamiltonian cycle with a degree check.

    Args:
        graph: The graph represented as an adjacency list.
        path: The current path being constructed.
        pos: The current position in the path.
        num_vertices: The number of vertices in the graph.

    Returns:
        True if a Hamiltonian cycle is found, False otherwise.
    """
    if pos == num_vertices:
        if graph[path[pos - 1]][path[0]] == 1:
            return True
        else:
            return False

    for v in range(num_vertices):
        if is_safe_pruning(v, graph, path, pos):
            path[pos] = v
            if hamiltonian_cycle_util_degree_check(graph, path, pos + 1, num_vertices):
                return True
            path[pos] = -1
    return False

def hamiltonian_cycle_degree_check(graph):
    """
    Finds a Hamiltonian cycle in the given graph using backtracking with a degree check.

    Args:
        graph: The graph represented as an adjacency list.

    Returns:
        A list representing the Hamiltonian cycle, or None if no cycle exists.
    """
    num_vertices = len(graph)
    # Check the degree of each vertex before starting the backtracking
    if not has_valid_degree(graph):
        return None  # Return None if a vertex has degree less than 2

    path = [-1] * num_vertices
    path[0] = 0
    if hamiltonian_cycle_util_degree_check(graph, path, 1, num_vertices):
        return path
    else:
        return None
def backtracking_with_degree_check_example():
    """
    Example usage of the backtracking approach with a degree check.
    """
    print("\n--- Backtracking with Degree Check Example ---")
    graph_degree_check = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
    ]
    cycle_degree_check = hamiltonian_cycle_degree_check(graph_degree_check)
    print_cycle(cycle_degree_check)

    graph_degree_check_2 = [
        [0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1],
        [0, 0, 0, 1, 0],
    ]
    cycle_degree_check_2 = hamiltonian_cycle_degree_check(graph_degree_check_2)
    print_cycle(cycle_degree_check_2)

    graph_degree_check_3 = [ # A graph where each node has degree >= 2
        [0, 1, 1, 0, 0],
        [1, 0, 1, 1, 0],
        [1, 1, 0, 0, 1],
        [0, 1, 0, 0, 1],
        [0, 0, 1, 1, 0],
    ]
    cycle_degree_check_3 = hamiltonian_cycle_degree_check(graph_degree_check_3)
    print_cycle(cycle_degree_check_3)

def hamiltonian_cycle_iterative(graph):
    """
    Finds a Hamiltonian cycle in the given graph using an iterative approach.

    Args:
        graph: The graph represented as an adjacency list.

    Returns:
        A list representing the Hamiltonian cycle, or None if no cycle exists.
    """
    num_vertices = len(graph)
    stack = [(0, [0])]  # Start from vertex 0, path starts with [0]

    while stack:
        current_vertex, path = stack.pop()
        if len(path) == num_vertices:
            if graph[current_vertex][0] == 1:
                return path
            else:
                continue  # Dead end, try other paths

        for next_vertex in range(num_vertices):
            if is_safe(next_vertex, graph, path, len(path)):
                stack.append((next_vertex, path + [next_vertex]))
    return None

def backtracking_with_iterative_approach_example():
    """
    Example usage of the backtracking approach.
    """
    print("\n--- Backtracking with Iterative Approach Example ---")
    # Example graph represented as an adjacency list
    graph_iterative = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
        [1, 0, 1, 0, 1],
        [0, 1, 0, 1, 0],
    ]
    cycle_iterative = hamiltonian_cycle_iterative(graph_iterative)
    print_cycle(cycle_iterative)

    graph_iterative_2 = [
        [0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1],
        [0, 0, 0, 1, 0],
    ]
    cycle_iterative_2 = hamiltonian_cycle_iterative(graph_iterative_2)
    print_cycle(cycle_iterative_2)

if __name__ == "__main__":
    basic_backtracking_example()
    backtracking_with_adjacency_matrix_example()
    backtracking_with_early_pruning_example()
    backtracking_with_degree_check_example()
    backtracking_with_iterative_approach_example()

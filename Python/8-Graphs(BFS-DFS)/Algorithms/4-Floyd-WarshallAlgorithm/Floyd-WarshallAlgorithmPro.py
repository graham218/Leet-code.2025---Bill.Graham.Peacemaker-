import numpy as np
import time
import sys

# 1. Basic Floyd-Warshall Algorithm

def floyd_warshall_basic(graph):
    """
    Implements the basic Floyd-Warshall algorithm to find the shortest paths
    between all pairs of vertices in a graph.

    Args:
        graph (list of lists): A 2D list representing the graph's adjacency matrix.
            graph[i][j] is the weight of the edge from vertex i to vertex j.
            If there is no edge, the weight is represented by infinity (float('inf')).

    Returns:
        list of lists: A 2D list representing the shortest path distances
        between all pairs of vertices.  Returns None if the input graph
        is invalid (e.g., not square).
    """
    if not graph or not all(len(row) == len(graph) for row in graph):
        return None  # Handle invalid input
    num_vertices = len(graph)
    dist = [row[:] for row in graph] # Create a copy to avoid modifying the original graph

    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist

# 2. Floyd-Warshall with Path Reconstruction

def floyd_warshall_with_path(graph):
    """
    Implements the Floyd-Warshall algorithm with path reconstruction.  It not
    only calculates the shortest path distances but also determines the
    intermediate nodes in those paths.

    Args:
        graph (list of lists): A 2D list representing the graph's adjacency matrix.

    Returns:
        tuple: A tuple containing two 2D lists:
            - The first list represents the shortest path distances.
            - The second list represents the 'next' node in the shortest path
              from i to j.  If next[i][j] is -1, there is no explicit path
              (i.e., direct edge or no path). Returns (None, None) for
              invalid input.
    """
    if not graph or not all(len(row) == len(graph) for row in graph):
        return None, None
    num_vertices = len(graph)
    dist = [row[:] for row in graph]
    next_node = [[-1 for _ in range(num_vertices)] for _ in range(num_vertices)]

    # Initialize the 'next' matrix.  For direct edges, the 'next' node is j.
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i != j and graph[i][j] != float('inf'):
                next_node[i][j] = j

    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_node[i][j] = next_node[i][k]  # Path goes through k
    return dist, next_node

def reconstruct_path(next_node, start, end):
    """
    Reconstructs the shortest path from start to end using the 'next' node
    information from Floyd-Warshall with path reconstruction.

    Args:
        next_node (list of lists): The 'next' node matrix from Floyd-Warshall.
        start (int): The starting vertex.
        end (int): The ending vertex.

    Returns:
        list: A list of the vertices in the shortest path from start to end,
        inclusive. Returns an empty list if no path exists.
    """
    if next_node is None or start < 0 or start >= len(next_node) or end < 0 or end >= len(next_node):
        return [] # Handle invalid input
    if next_node[start][end] == -1:
        if start == end:
            return [start] # Path from a node to itself.
        else:
            return []  # No path exists
    path = [start]
    while start != end:
        start = next_node[start][end]
        path.append(start)
    return path

# 3. Floyd-Warshall for Detecting Negative Cycles

def floyd_warshall_negative_cycle(graph):
    """
    Implements Floyd-Warshall to detect negative cycles in a graph.

    Args:
        graph (list of lists): A 2D list representing the graph's adjacency matrix.

    Returns:
        tuple:  A tuple containing:
            - A boolean indicating whether a negative cycle exists (True) or not (False).
            - The shortest path distance matrix (which may be meaningless if
              a negative cycle exists).  Returns (None, None) for invalid input.
    """
    if not graph or not all(len(row) == len(graph) for row in graph):
        return None, None
    num_vertices = len(graph)
    dist = [row[:] for row in graph]

    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    # Check for negative cycles on the diagonal
    for i in range(num_vertices):
        if dist[i][i] < 0:
            return True, dist  # Negative cycle detected
    return False, dist  # No negative cycle

# 4. Floyd-Warshall with Limited Memory (Iterative Deepening)
def floyd_warshall_limited_memory(graph, max_k):
    """
    Implements a memory-limited version of Floyd-Warshall using iterative deepening.
    This version performs Floyd-Warshall up to a maximum intermediate node 'k'.
    This is useful when you don't need all-pairs shortest paths, or when
    memory is extremely constrained.

    Args:
        graph (list of lists): Adjacency matrix of the graph.
        max_k (int): The maximum intermediate node (k) to consider.
            Nodes 0 to max_k (inclusive) will be used as intermediate nodes.

    Returns:
        list of lists: Shortest path distances considering intermediate nodes up to max_k.
        Returns None for invalid input.
    """
    if not graph or not all(len(row) == len(graph) for row in graph) or max_k < 0 or max_k >= len(graph):
        return None
    num_vertices = len(graph)
    dist = [row[:] for row in graph]

    for k in range(min(num_vertices, max_k + 1)): # Important:  Limit k
        for i in range(num_vertices):
            for j in range(num_vertices):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist

# 5. Floyd-Warshall with Early Termination
def floyd_warshall_early_termination(graph, target_pairs=None):
    """
    Implements Floyd-Warshall with early termination.  The algorithm stops
    early if the shortest paths for all pairs in 'target_pairs' have been found.
    This can significantly speed up the computation if you only need a subset
    of all-pairs shortest paths.

    Args:
        graph (list of lists): Adjacency matrix of the graph.
        target_pairs (set of tuples, optional): A set of (start_node, end_node) tuples
            representing the pairs for which shortest paths are needed.
            If None, compute all-pairs shortest paths.  For example: {(0, 3), (1, 2)}.

    Returns:
        list of lists:  The shortest path distances. Returns None for invalid input.
    """
    if not graph or not all(len(row) == len(graph) for row in graph):
        return None
    num_vertices = len(graph)
    dist = [row[:] for row in graph]
    if target_pairs is None:
        target_pairs = {(i, j) for i in range(num_vertices) for j in range(num_vertices)} # All pairs

    found_paths = set() # Keep track of which pairs we've found shortest paths for.

    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
                if (i, j) in target_pairs:
                    found_paths.add((i, j))
        if found_paths == target_pairs:
            return dist # Early termination

    return dist

# 6. Floyd-Warshall with A* Heuristic (Guided Search - Improvement, Not Core FW)

def floyd_warshall_astar_heuristic(graph, start_node, end_node, heuristic_func):
    """
    Implements a variation of Floyd-Warshall guided by an A* heuristic
    to find the shortest path between a *single* pair of nodes (start_node, end_node).
    This is NOT a true all-pairs shortest path algorithm.  It's an optimization
    for finding a single shortest path, combining ideas from A* and Floyd-Warshall.
    It precomputes a limited Floyd-Warshall and then uses A* to guide the search.

    Args:
        graph (list of lists): Adjacency matrix of the graph.
        start_node (int): The starting node for the path.
        end_node (int): The ending node for the path.
        heuristic_func (callable): A function that takes two node indices (current, goal)
            and returns an estimated cost (heuristic) of reaching the goal from the
            current node.  Admissible heuristic is crucial for A*.

    Returns:
        tuple: (distance, path).
            - distance (float): The shortest path distance from start_node to end_node.
            - path (list): The sequence of nodes in the shortest path.
            Returns (float('inf'), []) if no path is found or for invalid input.
    """
    if not graph or not all(len(row) == len(graph) for row in graph) or \
            start_node < 0 or start_node >= len(graph) or end_node < 0 or end_node >= len(graph):
        return float('inf'), []

    num_vertices = len(graph)
    dist = [row[:] for row in graph]
    next_node = [[-1 for _ in range(num_vertices)] for _ in range(num_vertices)]

    # Initialize next_node for direct edges
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i != j and graph[i][j] != float('inf'):
                next_node[i][j] = j

    # Precompute limited Floyd-Warshall (k up to a small value, e.g., 2 or 3)
    # This helps find some initial shorter paths.  The A* search will then refine.
    for k in range(min(num_vertices, 3)):  # Limit k for precomputation
        for i in range(num_vertices):
            for j in range(num_vertices):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_node[i][j] = next_node[i][k]

    # A* Search
    open_set = [(0 + heuristic_func(start_node, end_node), start_node)]  # (f_score, node)
    came_from = {}
    g_score = {node: float('inf') for node in range(num_vertices)}
    g_score[start_node] = 0

    while open_set:
        open_set.sort()  # Get node with smallest f_score
        current_node = open_set.pop(0)[1]

        if current_node == end_node:
            break  # Found the goal

        for neighbor in range(num_vertices):
            if graph[current_node][neighbor] != float('inf'):
                tentative_g_score = g_score[current_node] + graph[current_node][neighbor]
                if tentative_g_score < g_score[neighbor]:
                    came_from[neighbor] = current_node
                    g_score[neighbor] = tentative_g_score
                    f_score = tentative_g_score + heuristic_func(neighbor, end_node)
                    open_set.append((f_score, neighbor))

    if end_node not in came_from:
        return float('inf'), []  # No path found

    # Reconstruct path
    path = []
    current = end_node
    while current != start_node:
        path.insert(0, current)
        current = came_from[current]
    path.insert(0, start_node)
    return g_score[end_node], path

# Helper function for A* heuristic (example: Euclidean distance on a grid)
def euclidean_distance_heuristic(node1, node2):
    """
    Example of an admissible heuristic function: Euclidean distance
    between two nodes, assuming they are coordinates on a 2D grid.
    If your graph doesn't represent a 2D grid, you'll need a different
    heuristic function.  Admissibility is crucial for A*.
    """
    #  Replace with actual coordinates if your nodes represent points in space
    x1, y1 = node1 // 10, node1 % 10  # Example:  Node ID -> (x, y)
    x2, y2 = node2 // 10, node2 % 10
    return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5

def print_matrix(matrix):
    """
    Helper function to print a matrix in a more readable format.
    Handles infinity representation.
    """
    if matrix is None:
        print("Invalid Graph Input")
        return
    for row in matrix:
        print("  ".join(f"{x:8.2f}" if x != float('inf') else "    inf" for x in row))

def generate_random_graph(num_vertices, density=0.5, weight_range=(1, 10)):
    """
    Generates a random weighted graph (adjacency matrix) for testing.

    Args:
        num_vertices (int): The number of vertices in the graph.
        density (float): The probability of an edge existing between two vertices (0 to 1).
        weight_range (tuple):  A tuple (min_weight, max_weight) for the range of edge weights.

    Returns:
        list of lists: A 2D list representing the adjacency matrix of the random graph.
    """
    graph = [[float('inf')] * num_vertices for _ in range(num_vertices)]
    for i in range(num_vertices):
        graph[i][i] = 0  # Distance from a node to itself is 0
        for j in range(i + 1, num_vertices):
            if np.random.rand() < density:
                weight = np.random.randint(weight_range[0], weight_range[1] + 1)
                graph[i][j] = weight
                graph[j][i] = weight  # Assuming an undirected graph
    return graph

def main():
    """
    Main function to demonstrate the different Floyd-Warshall implementations
    with example graphs and real-world scenarios.
    """
    # 1. Basic Floyd-Warshall Example
    print("\n1. Basic Floyd-Warshall Algorithm:")
    graph_basic = [
        [0, 5, float('inf'), 10],
        [float('inf'), 0, 3, float('inf')],
        [float('inf'), float('inf'), 0, 1],
        [float('inf'), float('inf'), float('inf'), 0]
    ]
    print("Original Graph:")
    print_matrix(graph_basic)
    start_time = time.time()
    shortest_distances_basic = floyd_warshall_basic(graph_basic)
    end_time = time.time()
    print("Shortest Path Distances:")
    print_matrix(shortest_distances_basic)
    print(f"Basic Floyd-Warshall Time: {end_time - start_time:.4f} seconds")

    # 2. Floyd-Warshall with Path Reconstruction Example
    print("\n2. Floyd-Warshall with Path Reconstruction:")
    graph_path = [
        [0, 2, float('inf'), 5, float('inf')],
        [float('inf'), 0, 3, float('inf'), 1],
        [float('inf'), float('inf'), 0, 1, float('inf')],
        [float('inf'), float('inf'), float('inf'), 0, 2],
        [float('inf'), float('inf'), float('inf'), float('inf'), 0]
    ]
    print("Original Graph:")
    print_matrix(graph_path)
    shortest_distances_path, next_node = floyd_warshall_with_path(graph_path)
    print("Shortest Path Distances:")
    print_matrix(shortest_distances_path)
    print("Next Node Matrix:")
    print_matrix(next_node)

    # Example of path reconstruction
    start_node = 0
    end_node = 4
    path = reconstruct_path(next_node, start_node, end_node)
    print(f"Shortest path from {start_node} to {end_node}: {path}")

    # 3. Floyd-Warshall for Detecting Negative Cycles Example
    print("\n3. Floyd-Warshall for Detecting Negative Cycles:")
    graph_negative_cycle = [
        [0, 1, float('inf')],
        [float('inf'), 0, -2],
        [float('inf'), float('inf'), 0]
    ]
    print("Original Graph:")
    print_matrix(graph_negative_cycle)
    has_negative_cycle, distances_negative_cycle = floyd_warshall_negative_cycle(graph_negative_cycle)
    if has_negative_cycle:
        print("Negative cycle detected!")
        print("Distances (may be incorrect due to negative cycle):")
        print_matrix(distances_negative_cycle)
    else:
        print("No negative cycle detected.")
        print("Shortest Path Distances:")
        print_matrix(distances_negative_cycle)

    graph_negative_cycle2 = [ # Example WITH a negative cycle
        [0, 2, -2],
        [1, 0, 3],
        [2, -1, 0]
    ]
    print("\nOriginal Graph with Negative Cycle:")
    print_matrix(graph_negative_cycle2)
    has_negative_cycle2, distances_negative_cycle2 = floyd_warshall_negative_cycle(graph_negative_cycle2)
    if has_negative_cycle2:
        print("Negative cycle detected!")
        print("Distances (may be incorrect due to negative cycle):")
        print_matrix(distances_negative_cycle2)
    else:
        print("No negative cycle detected.")
        print("Shortest Path Distances:")
        print_matrix(distances_negative_cycle2)

    # 4. Floyd-Warshall with Limited Memory (Iterative Deepening)
    print("\n4. Floyd-Warshall with Limited Memory (Iterative Deepening):")
    graph_memory = generate_random_graph(5, density=0.7)
    print("Original Graph:")
    print_matrix(graph_memory)
    max_k = 2
    print(f"Shortest paths with max_k = {max_k}:")
    distances_limited_memory = floyd_warshall_limited_memory(graph_memory, max_k)
    print_matrix(distances_limited_memory)

    # 5. Floyd-Warshall with Early Termination
    print("\n5. Floyd-Warshall with Early Termination:")
    graph_early_term = generate_random_graph(5, density=0.8)
    print("Original Graph:")
    print_matrix(graph_early_term)
    target_pairs = {(0, 2), (1, 3)}
    print(f"Shortest paths for pairs: {target_pairs}")
    distances_early_term = floyd_warshall_early_termination(graph_early_term, target_pairs)
    print_matrix(distances_early_term)

    target_pairs_all = {(0, 0), (0, 1), (0, 2), (0, 3), (0, 4),
                        (1, 0), (1, 1), (1, 2), (1, 3), (1, 4),
                        (2, 0), (2, 1), (2, 2), (2, 3), (2, 4),
                        (3, 0), (3, 1), (3, 2), (3, 3), (3, 4),
                        (4, 0), (4, 1), (4, 2), (4, 3), (4, 4)}
    print(f"\nShortest paths for all pairs: {target_pairs_all}")
    distances_early_term_all = floyd_warshall_early_termination(graph_early_term, target_pairs_all)
    print_matrix(distances_early_term_all)

    # 6. Floyd-Warshall with A* Heuristic (Guided Search)
    print("\n6. Floyd-Warshall with A* Heuristic (Guided Search):")
    # Example graph (representing a 10x10 grid, for simplicity of heuristic)
    graph_astar = [[float('inf')] * 100 for _ in range(100)]
    for i in range(100):
        for j in range(100):
            if i == j:
                graph_astar[i][j] = 0
            #  Define neighbors in the grid (example:  allow moves up, down, left, right)
            if i - 10 >= 0:
                graph_astar[i][i - 10] = 1  # Up
            if i + 10 < 100:
                graph_astar[i][i + 10] = 1  # Down
            if i % 10 > 0:
                graph_astar[i][i - 1] = 1   # Left
            if i % 10 < 9:
                graph_astar[i][i + 1] = 1   # Right

    start_node_astar = 0
    end_node_astar = 99
    print(f"Shortest path from {start_node_astar} to {end_node_astar}:")
    distance_astar, path_astar = floyd_warshall_astar_heuristic(graph_astar, start_node_astar, end_node_astar, euclidean_distance_heuristic)
    print(f"Distance: {distance_astar}")
    print(f"Path: {path_astar}")

if __name__ == "__main__":
    main()

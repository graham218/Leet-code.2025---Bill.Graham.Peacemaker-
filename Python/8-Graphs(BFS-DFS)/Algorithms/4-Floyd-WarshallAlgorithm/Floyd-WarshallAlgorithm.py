import numpy as np

# 1. Floyd-Warshall Algorithm (Basic Implementation)
def floyd_warshall_basic(graph):
    """
    Floyd-Warshall algorithm to find the shortest distances between all pairs of vertices
    in a weighted graph.  This is the most straightforward implementation.

    Args:
        graph (list of lists): A square matrix representing the graph where
            graph[i][j] is the weight of the edge from vertex i to vertex j.
            If there is no edge between i and j, graph[i][j] should be float('inf').
            The diagonal elements (graph[i][i]) should be 0.

    Returns:
        list of lists: A matrix of shortest distances between every pair of vertices.
                       If a path doesn't exist, the corresponding entry will be float('inf').
    """
    num_vertices = len(graph)
    dist = [row[:] for row in graph]  # Create a copy of the graph

    # Iterate through all possible intermediate vertices k
    for k in range(num_vertices):
        # Iterate through all possible source vertices i
        for i in range(num_vertices):
            # Iterate through all possible destination vertices j
            for j in range(num_vertices):
                # If going through vertex k is shorter than the current distance from i to j, update the distance
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist

# 2. Floyd-Warshall Algorithm with Path Reconstruction
def floyd_warshall_path(graph):
    """
    Floyd-Warshall algorithm that also reconstructs the shortest paths between all pairs of vertices.

    Args:
        graph (list of lists): A square matrix representing the graph (same as in floyd_warshall_basic).

    Returns:
        tuple: A tuple containing two elements:
            - dist (list of lists): The shortest distance matrix.
            - next_matrix (list of lists): A matrix where next_matrix[i][j] stores the intermediate
              node in the shortest path from i to j.  If there is a direct edge from i to j,
              next_matrix[i][j] is j.  This matrix is used to reconstruct the actual paths.
    """
    num_vertices = len(graph)
    dist = [row[:] for row in graph]  # Create a copy of the graph
    next_matrix = [[j if graph[i][j] != float('inf') and i != j else None for j in range(num_vertices)] for i in range(num_vertices)]

    # Iterate through all possible intermediate vertices k
    for k in range(num_vertices):
        # Iterate through all possible source vertices i
        for i in range(num_vertices):
            # Iterate through all possible destination vertices j
            for j in range(num_vertices):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_matrix[i][j] = next_matrix[i][k]  # Update the intermediate node
    return dist, next_matrix

def reconstruct_path(next_matrix, start_vertex, end_vertex):
    """
    Reconstructs the shortest path from start_vertex to end_vertex using the next_matrix
    computed by floyd_warshall_path.

    Args:
        next_matrix (list of lists): The next_matrix returned by floyd_warshall_path.
        start_vertex (int): The starting vertex index.
        end_vertex (int): The ending vertex index.

    Returns:
        list: A list of vertex indices representing the shortest path from start_vertex
              to end_vertex. Returns an empty list if no path exists.
    """
    if next_matrix[start_vertex][end_vertex] is None:
        return []  # No path exists
    path = [start_vertex]
    current_vertex = start_vertex
    while current_vertex != end_vertex:
        current_vertex = next_matrix[current_vertex][end_vertex]
        path.append(current_vertex)
    return path

# 3. Floyd-Warshall Algorithm with NumPy
def floyd_warshall_numpy(graph):
    """
    Floyd-Warshall algorithm implemented using NumPy for potential performance improvements
    on larger graphs.

    Args:
        graph (list of lists): A square matrix representing the graph.

    Returns:
        numpy.ndarray: A NumPy array representing the shortest distance matrix.
    """
    num_vertices = len(graph)
    dist = np.array(graph, dtype=float)  # Convert to NumPy array

    # Iterate through all possible intermediate vertices k
    for k in range(num_vertices):
        # Create a temporary matrix to store updated distances
        temp_dist = np.minimum(
            np.tile(dist[:, k], (num_vertices, 1)) + np.tile(dist[k, :], (num_vertices, 1)).T,
            dist
        )
        dist = temp_dist
    return dist

# 4. Floyd-Warshall Algorithm with Edge List Input
def floyd_warshall_edge_list(num_vertices, edge_list):
    """
    Floyd-Warshall algorithm that takes the graph as an edge list instead of an adjacency matrix.

    Args:
        num_vertices (int): The number of vertices in the graph.
        edge_list (list of tuples): A list of tuples where each tuple (u, v, weight)
            represents a directed edge from vertex u to vertex v with the given weight.
            Vertices are assumed to be 0-indexed.

    Returns:
        list of lists: A matrix of shortest distances between every pair of vertices.
    """
    # Initialize the distance matrix with infinity for all pairs of vertices
    dist = [[float('inf')] * num_vertices for _ in range(num_vertices)]
    for i in range(num_vertices):
        dist[i][i] = 0  # Distance from a vertex to itself is 0

    # Populate the distance matrix with the given edge weights
    for u, v, weight in edge_list:
        dist[u][v] = weight

    # Iterate through all possible intermediate vertices k
    for k in range(num_vertices):
        # Iterate through all possible source vertices i
        for i in range(num_vertices):
            # Iterate through all possible destination vertices j
            for j in range(num_vertices):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist

# 5. Floyd-Warshall Algorithm with Predecessor Matrix
def floyd_warshall_predecessor(graph):
    """
    Floyd-Warshall algorithm that also computes a predecessor matrix, which can be
    used to reconstruct the shortest paths.  This is similar to the next_matrix
    approach, but stores the predecessor node instead.

    Args:
        graph (list of lists): A square matrix representing the graph.

    Returns:
        tuple: A tuple containing two elements:
            - dist (list of lists): The shortest distance matrix.
            - pred (list of lists): A matrix where pred[i][j] stores the predecessor
              node in the shortest path from i to j. If there is a direct edge from i to j,
              pred[i][j] is i.
    """
    num_vertices = len(graph)
    dist = [row[:] for row in graph]  # Create a copy of the graph
    pred = [[i if graph[i][j] != float('inf') and i != j else None for j in range(num_vertices)] for i in range(num_vertices)]

    # Iterate through all possible intermediate vertices k
    for k in range(num_vertices):
        # Iterate through all possible source vertices i
        for i in range(num_vertices):
            # Iterate through all possible destination vertices j
            for j in range(num_vertices):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    pred[i][j] = pred[k][j]  # Update the predecessor
    return dist, pred

def reconstruct_path_predecessor(pred, start_vertex, end_vertex):
    """
    Reconstructs the shortest path from start_vertex to end_vertex using the predecessor
    matrix computed by floyd_warshall_predecessor.

    Args:
        pred (list of lists): The predecessor matrix returned by floyd_warshall_predecessor.
        start_vertex (int): The starting vertex index.
        end_vertex (int): The ending vertex index.

    Returns:
        list: A list of vertex indices representing the shortest path from start_vertex
              to end_vertex. Returns an empty list if no path exists.
    """
    if pred[start_vertex][end_vertex] is None:
        return []  # No path exists
    path = [end_vertex]
    current_vertex = end_vertex
    while current_vertex != start_vertex:
        current_vertex = pred[start_vertex][current_vertex]
        path.append(current_vertex)
    path.reverse()  # Reverse the path to get it in the correct order
    return path

if __name__ == "__main__":
    # Example graph represented as an adjacency matrix
    graph = [
        [0, 5, float('inf'), 10],
        [float('inf'), 0, 3, float('inf')],
        [float('inf'), float('inf'), 0, 1],
        [float('inf'), float('inf'), float('inf'), 0]
    ]
    num_vertices = len(graph)

    # 1. Floyd-Warshall Algorithm (Basic Implementation)
    print("\n1. Floyd-Warshall Algorithm (Basic Implementation):")
    dist_basic = floyd_warshall_basic(graph)
    print("Shortest distance matrix:")
    for row in dist_basic:
        print(row)

    # 2. Floyd-Warshall Algorithm with Path Reconstruction
    print("\n2. Floyd-Warshall Algorithm with Path Reconstruction:")
    dist_path, next_matrix = floyd_warshall_path(graph)
    print("Shortest distance matrix:")
    for row in dist_path:
        print(row)
    print("Next matrix:")
    for row in next_matrix:
        print(row)

    start_vertex = 0
    end_vertex = 3
    path = reconstruct_path(next_matrix, start_vertex, end_vertex)
    print(f"Shortest path from {start_vertex} to {end_vertex}: {path}")

    # 3. Floyd-Warshall Algorithm with NumPy
    print("\n3. Floyd-Warshall Algorithm with NumPy:")
    dist_numpy = floyd_warshall_numpy(graph)
    print("Shortest distance matrix:")
    print(dist_numpy)

    # 4. Floyd-Warshall Algorithm with Edge List Input
    print("\n4. Floyd-Warshall Algorithm with Edge List Input:")
    edge_list = [
        (0, 1, 5),
        (1, 2, 3),
        (2, 3, 1),
        (0, 3, 10)
    ]
    dist_edge_list = floyd_warshall_edge_list(num_vertices, edge_list)
    print("Shortest distance matrix:")
    for row in dist_edge_list:
        print(row)

    # 5. Floyd-Warshall Algorithm with Predecessor Matrix
    print("\n5. Floyd-Warshall Algorithm with Predecessor Matrix:")
    dist_pred, pred_matrix = floyd_warshall_predecessor(graph)
    print("Shortest distance matrix:")
    for row in dist_pred:
        print(row)
    print("Predecessor matrix:")
    for row in pred_matrix:
        print(row)

    start_vertex_pred = 0
    end_vertex_pred = 3
    path_pred = reconstruct_path_predecessor(pred_matrix, start_vertex_pred, end_vertex_pred)
    print(f"Shortest path from {start_vertex_pred} to {end_vertex_pred}: {path_pred}")

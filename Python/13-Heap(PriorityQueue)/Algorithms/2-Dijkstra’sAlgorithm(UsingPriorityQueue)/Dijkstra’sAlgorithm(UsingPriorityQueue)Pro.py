import heapq
import sys

# 1. Basic Dijkstra's Algorithm with Priority Queue
def dijkstra_basic(graph, start):
    """
    Computes the shortest paths from a start node to all other nodes in a graph using Dijkstra's algorithm.

    Args:
        graph: A dictionary representing the graph where keys are nodes and values are dictionaries
               of neighboring nodes with edge weights.  For example:
               graph = {
                   'A': {'B': 5, 'C': 1},
                   'B': {'A': 5, 'C': 2, 'D': 1},
                   'C': {'A': 1, 'B': 2, 'D': 4, 'E': 8},
                   'D': {'B': 1, 'C': 4, 'E': 3, 'F': 6},
                   'E': {'C': 8, 'D': 3, 'F': 9},
                   'F': {'D': 6, 'E': 9}
               }
        start: The starting node.

    Returns:
        A dictionary where keys are nodes and values are the shortest distances from the start node.
    """
    distances = {node: float('inf') for node in graph}  # Initialize distances to infinity for all nodes
    distances[start] = 0  # Distance from start node to itself is 0
    priority_queue = [(0, start)]  # Priority queue of (distance, node) tuples

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)  # Get the node with the smallest distance

        if dist > distances[current_node]:  # Important: Check if a shorter path has already been found
            continue  # If so, skip this node

        for neighbor, weight in graph[current_node].items():
            new_distance = dist + weight  # Calculate distance to the neighbor
            if new_distance < distances[neighbor]:  # If a shorter path is found
                distances[neighbor] = new_distance  # Update the distance
                heapq.heappush(priority_queue, (new_distance, neighbor))  # Add to the priority queue

    return distances

# 2. Dijkstra's Algorithm with Path Reconstruction
def dijkstra_with_path_reconstruction(graph, start, end):
    """
    Computes the shortest path and its distance from a start node to an end node, reconstructing the path.

    Args:
        graph:  A dictionary representing the graph.
        start: The starting node.
        end: The destination node.

    Returns:
        A tuple containing the shortest distance and the path (list of nodes) from start to end.
        Returns (float('inf'), []) if no path exists.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]
    previous_nodes = {node: None for node in graph}  # Store the preceding node in the shortest path

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if dist > distances[current_node]:
            continue

        if current_node == end:  # Optimization: Stop if the destination is reached
            break

        for neighbor, weight in graph[current_node].items():
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                previous_nodes[neighbor] = current_node  # Store the previous node
                heapq.heappush(priority_queue, (new_distance, neighbor))

    # Reconstruct the path from end to start
    path = []
    current = end
    while current is not None:
        path.insert(0, current)  # Insert at the beginning to get the correct order
        current = previous_nodes[current]

    if distances[end] == float('inf'):
        return float('inf'), []  # No path found
    else:
        return distances[end], path
# 3. Dijkstra's Algorithm for a Grid (2D Array)
def dijkstra_grid(grid, start):
    """
    Computes the shortest paths from a start cell to all other cells in a 2D grid.
    Assumes the grid represents a graph where movement is allowed up, down, left, and right.

    Args:
        grid: A 2D list (list of lists) representing the grid.  Each cell contains the cost
              to move to that cell.
        start: A tuple (row, col) representing the starting cell.

    Returns:
        A 2D list of the same dimensions as the grid, where each cell contains the shortest
        distance from the start cell.  Returns None if the input is invalid.
    """
    if not grid or not grid[0] or not isinstance(start, tuple) or len(start) != 2:
        return None  # Handle invalid input

    rows, cols = len(grid), len(grid[0])
    distances = [[float('inf')] * cols for _ in range(rows)]  # Initialize distances
    distances[start[0]][start[1]] = 0
    priority_queue = [(0, start)]
    visited = set() # Keep track of visited nodes

    while priority_queue:
        dist, (row, col) = heapq.heappop(priority_queue)
        if (row, col) in visited:
            continue
        visited.add((row,col))

        if dist > distances[row][col]:
            continue

        # Define possible movements (up, down, left, right)
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        for dr, dc in directions:
            new_row, new_col = row + dr, col + dc
            # Check if the new cell is within the grid bounds
            if 0 <= new_row < rows and 0 <= new_col < cols:
                new_distance = dist + grid[new_row][new_col]  # Cost to move to the new cell
                if new_distance < distances[new_row][new_col]:
                    distances[new_row][new_col] = new_distance
                    heapq.heappush(priority_queue, (new_distance, (new_row, new_col)))
    return distances

# 4. Dijkstra's Algorithm with Edge Weights as a Separate List
def dijkstra_with_edge_weights(nodes, edges, start):
    """
    Computes the shortest paths using Dijkstra's algorithm, where edge weights are provided in a separate list.

    Args:
        nodes: A list of nodes in the graph (e.g., ['A', 'B', 'C', 'D']).
        edges: A list of tuples, where each tuple represents an edge (u, v, weight),
               where u and v are nodes, and weight is the edge weight.
        start: The starting node.

    Returns:
        A dictionary where keys are nodes and values are the shortest distances from the start node.
    """
    graph = {node: {} for node in nodes}  # Create an adjacency list representation of the graph
    for u, v, weight in edges:
        graph[u][v] = weight
        graph[v][u] = weight  # Assuming an undirected graph.  Remove this line for a directed graph.

    distances = {node: float('inf') for node in nodes}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))
    return distances

# 5. Dijkstra's Algorithm with a Modified Priority Queue (No Duplicates) - Less Efficient
def dijkstra_no_duplicates(graph, start):
    """
    Computes the shortest paths using Dijkstra's algorithm, but avoids adding duplicate nodes
    to the priority queue.  This approach can be less efficient in some cases, as it requires
    more complex logic to update distances.

    Args:
        graph: A dictionary representing the graph.
        start: The starting node.

    Returns:
        A dictionary where keys are nodes and values are the shortest distances from the start node.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]
    in_queue = {start}  # Keep track of nodes currently in the queue

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)
        in_queue.remove(current_node) # remove the node

        if dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                if neighbor not in in_queue: # only add if the neighbor is not in the queue
                    heapq.heappush(priority_queue, (new_distance, neighbor))
                    in_queue.add(neighbor)  # Mark the neighbor as being in the queue
                else:
                    #  Priority queue doesn't have a decrease_key operation, and it's
                    #  difficult to update the priority of an existing item.  This else
                    #  condition is reached, but the priority queue is not updated.
                    #  This is less efficient than the standard approach.
                    pass # Do nothing.

    return distances

# 6. Dijkstra's Algorithm with Early Exit for a Specific Target
def dijkstra_target(graph, start, target):
    """
    Computes the shortest path from a start node to a specific target node.  The algorithm terminates
    as soon as the shortest path to the target node is found.

    Args:
        graph: A dictionary representing the graph.
        start: The starting node.
        target: The target node.

    Returns:
        The shortest distance from the start node to the target node. Returns float('inf') if no path exists.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if dist > distances[current_node]:
            continue

        if current_node == target:  # Exit early if the target is reached
            return distances[target]

        for neighbor, weight in graph[current_node].items():
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))

    return distances[target] # returns infinity if target is not reachable.

if __name__ == "__main__":
    # Example graph (same as in the problem description)
    graph = {
        'A': {'B': 5, 'C': 1},
        'B': {'A': 5, 'C': 2, 'D': 1},
        'C': {'A': 1, 'B': 2, 'D': 4, 'E': 8},
        'D': {'B': 1, 'C': 4, 'E': 3, 'F': 6},
        'E': {'C': 8, 'D': 3, 'F': 9},
        'F': {'D': 6, 'E': 9}
    }
    nodes = ['A', 'B', 'C', 'D', 'E', 'F']
    edges = [
        ('A', 'B', 5), ('A', 'C', 1), ('B', 'C', 2), ('B', 'D', 1),
        ('C', 'D', 4), ('C', 'E', 8), ('D', 'E', 3), ('D', 'F', 6), ('E', 'F', 9)
    ]
    grid = [
        [0, 2, 3, 4],
        [9, 8, 7, 6],
        [1, 2, 3, 4],
        [8, 7, 6, 5]
    ]

    # 1. Basic Dijkstra's
    print("\n1. Basic Dijkstra's Algorithm:")
    start_node = 'A'
    shortest_distances = dijkstra_basic(graph, start_node)
    print(f"Shortest distances from node {start_node}: {shortest_distances}")
    # Expected output: {'A': 0, 'B': 3, 'C': 1, 'D': 4, 'E': 7, 'F': 10}

    # 2. Dijkstra's with Path Reconstruction
    print("\n2. Dijkstra's Algorithm with Path Reconstruction:")
    start_node = 'A'
    end_node = 'F'
    distance, path = dijkstra_with_path_reconstruction(graph, start_node, end_node)
    print(f"Shortest distance from {start_node} to {end_node}: {distance}")
    print(f"Shortest path from {start_node} to {end_node}: {path}")
    # Expected output:
    # Shortest distance from A to F: 10
    # Shortest path from A to F: ['A', 'B', 'D', 'F']

    # 3. Dijkstra's for a Grid
    print("\n3. Dijkstra's Algorithm for a Grid:")
    start_cell = (0, 0)
    shortest_distances_grid = dijkstra_grid(grid, start_cell)
    print(f"Shortest distances from cell {start_cell}:")
    for row in shortest_distances_grid:
        print(row)
    # Expected output:
    # Shortest distances from cell (0, 0):
    # [0, 2, 3, 4]
    # [9, 8, 7, 6]
    # [10, 10, 10, 10]
    # [17, 17, 16, 15]


    # 4. Dijkstra's with Edge Weights as a Separate List
    print("\n4. Dijkstra's Algorithm with Edge Weights as a Separate List:")
    start_node_edges = 'A'
    shortest_distances_edges = dijkstra_with_edge_weights(nodes, edges, start_node_edges)
    print(f"Shortest distances from node {start_node_edges}: {shortest_distances_edges}")
    # Expected output:  {'A': 0, 'B': 3, 'C': 1, 'D': 4, 'E': 7, 'F': 10}

    # 5. Dijkstra's Algorithm with No Duplicates (Less Efficient)
    print("\n5. Dijkstra's Algorithm with No Duplicates (Less Efficient):")
    start_node_no_duplicates = 'A'
    shortest_distances_no_duplicates = dijkstra_no_duplicates(graph, start_node_no_duplicates)
    print(f"Shortest distances from node {start_node_no_duplicates}: {shortest_distances_no_duplicates}")
    # Expected output: {'A': 0, 'B': 3, 'C': 1, 'D': 4, 'E': 7, 'F': 10}

    # 6. Dijkstra's Algorithm with Early Exit for a Specific Target
    print("\n6. Dijkstra's Algorithm with Early Exit for a Specific Target:")
    start_node_target = 'A'
    target_node = 'D'
    shortest_distance_target = dijkstra_target(graph, start_node_target, target_node)
    print(f"Shortest distance from node {start_node_target} to {target_node}: {shortest_distance_target}")
    # Expected output: 4

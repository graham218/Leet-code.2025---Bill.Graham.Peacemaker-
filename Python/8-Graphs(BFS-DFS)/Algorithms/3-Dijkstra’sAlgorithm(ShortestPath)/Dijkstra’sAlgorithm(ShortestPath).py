import heapq
import sys
from collections import defaultdict

# Sample graph representation (adjacency list with edge weights)
# graph = {
#     'A': [('B', 1), ('C', 4)],
#     'B': [('A', 1), ('D', 3), ('E', 7)],
#     'C': [('A', 4), ('D', 1), ('F', 5)],
#     'D': [('B', 3), ('C', 1), ('E', 2), ('F', 1)],
#     'E': [('B', 7), ('D', 2), ('G', 2)],
#     'F': [('C', 5), ('D', 1), ('G', 3)],
#     'G': [('E', 2), ('F', 3)]
# }
#
# start_node = 'A'
#
# Expected output for node 'A':
# Shortest distances from A: {'A': 0, 'B': 1, 'C': 4, 'D': 2, 'E': 4, 'F': 3, 'G': 6}
# Path from A to G: ['A', 'B', 'D', 'E', 'G']

def print_result(distances, path, start_node, end_node=None):
    """
    Helper function to print the results in a user-friendly format.

    Args:
        distances (dict): Dictionary of shortest distances from the start node.
        path (dict): Dictionary of paths from the start node.
        start_node (str): The starting node for Dijkstra's algorithm.
        end_node (str, optional): The destination node. If provided, print path to this node only.
    """
    print(f"\nShortest distances from {start_node}: {distances}")
    if end_node:
        if end_node in path:
            print(f"Path from {start_node} to {end_node}: {path[end_node]}")
        else:
            print(f"No path found from {start_node} to {end_node}")
    else:
        for node, p in path.items():
            print(f"Path from {start_node} to {node}: {p}")
# 1. Dijkstra's Algorithm using Priority Queue (heapq)
def dijkstra_heapq(graph, start_node):
    """
    Dijkstra's algorithm using a priority queue (heapq) to find the shortest paths
    from a start node to all other nodes in a graph.

    Args:
        graph (dict): A dictionary representing the graph where keys are nodes
                       and values are lists of (neighbor, edge_weight) tuples.
        start_node (str): The node to start the search from.

    Returns:
        tuple: A tuple containing two dictionaries:
               - distances:  Shortest distances from the start node to all other nodes.
               - path: The shortest paths from the start node to all other nodes.
    """

    distances = {node: float('inf') for node in graph}  # Initialize distances to infinity
    distances[start_node] = 0  # Distance from start node to itself is 0
    priority_queue = [(0, start_node)]  # Priority queue (distance, node)
    path = {start_node: [start_node]}  # Store the path

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)  # Get node with smallest distance

        if dist > distances[current_node]:
            continue  # Skip if a shorter path has already been found

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight  # Calculate distance to neighbor
            if new_distance < distances[neighbor]:  # If shorter path is found
                distances[neighbor] = new_distance  # Update distance
                heapq.heappush(priority_queue, (new_distance, neighbor))  # Add to queue
                path[neighbor] = list(path[current_node])  # Copy the current path
                path[neighbor].append(neighbor)  # Append the neighbor to the path
    return distances, path



# 2. Dijkstra's Algorithm using Priority Queue and Visited Set
def dijkstra_heapq_visited(graph, start_node):
    """
    Dijkstra's algorithm using a priority queue (heapq) and a visited set
    to find the shortest paths from a start node to all other nodes in a graph.
    This version explicitly tracks visited nodes to avoid revisiting them.

    Args:
        graph (dict): A dictionary representing the graph where keys are nodes
                       and values are lists of (neighbor, edge_weight) tuples.
        start_node (str): The node to start the search from.

    Returns:
        tuple: A tuple containing two dictionaries:
               - distances:  Shortest distances from the start node to all other nodes.
               - path: The shortest paths from the start node to all other nodes.
    """
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = [(0, start_node)]
    visited = set()  # Keep track of visited nodes
    path = {start_node: [start_node]}

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if current_node in visited:  # Skip if already visited
            continue
        visited.add(current_node)  # Mark the current node as visited

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
    return distances, path


# 3. Dijkstra's Algorithm using Relaxation
def dijkstra_relaxation(graph, start_node):
    """
    Dijkstra's algorithm using the relaxation technique.  This version iterates
    through all edges in the graph multiple times, "relaxing" the distances until
    they converge to the shortest path values.

    Args:
        graph (dict): A dictionary representing the graph where keys are nodes
                       and values are lists of (neighbor, edge_weight) tuples.
        start_node (str): The node to start the search from.

    Returns:
        tuple: A tuple containing two dictionaries:
               - distances:  Shortest distances from the start node to all other nodes.
               - path: The shortest paths from the start node to all other nodes.
    """
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    path = {start_node: [start_node]}

    # Relax edges repeatedly. The loop runs V-1 times, where V is the number of vertices.
    for _ in range(len(graph) - 1):
        for current_node in graph:
            for neighbor, weight in graph[current_node]:
                new_distance = distances[current_node] + weight
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    path[neighbor] = list(path[current_node])
                    path[neighbor].append(neighbor)
    return distances, path


# 4. Dijkstra's Algorithm using a dictionary as a priority queue
def dijkstra_dict(graph, start_node):
    """
    Dijkstra's algorithm using a dictionary as a priority queue.  This approach
    avoids using the heapq module and implements a simple priority queue
    using a dictionary.

    Args:
        graph (dict): A dictionary representing the graph where keys are nodes
                       and values are lists of (neighbor, edge_weight) tuples.
        start_node (str): The node to start the search from.

    Returns:
        tuple: A tuple containing two dictionaries:
               - distances:  Shortest distances from the start node to all other nodes.
               - path: The shortest paths from the start node to all other nodes.
    """
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = {start_node: 0}  # Use a dictionary as a priority queue
    path = {start_node: [start_node]}

    while priority_queue:
        # Find the node with the smallest distance in the priority queue
        current_node = min(priority_queue, key=priority_queue.get)
        dist = priority_queue.pop(current_node) # Get the distance and remove from queue.

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                priority_queue[neighbor] = new_distance  # Add/update in "priority queue"
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
    return distances, path

# 5. Dijkstra with Adjacency Matrix
def dijkstra_matrix(graph_matrix, start_node):
    """
    Dijkstra's algorithm implemented using an adjacency matrix representation
    of the graph.

    Args:
        graph_matrix (list of lists):  A square matrix representing the graph.
                                       graph_matrix[i][j] is the weight of the edge from
                                       node i to node j.  Use 0 for no edge, and
                                       float('inf') for edges that don't exist.
        start_node (int): The index of the starting node.

    Returns:
        tuple: A tuple containing two dictionaries:
               - distances:  Shortest distances from the start node to all other nodes
                             (represented by their indices).
               - path: The shortest paths from the start node to all other nodes
                       (represented by their indices).
    """
    num_nodes = len(graph_matrix)
    distances = [float('inf')] * num_nodes
    distances[start_node] = 0
    visited = [False] * num_nodes
    path = {start_node: [start_node]}

    for _ in range(num_nodes):
        # Find the node with the minimum distance among the unvisited nodes
        min_distance = float('inf')
        current_node = -1
        for i in range(num_nodes):
            if not visited[i] and distances[i] < min_distance:
                min_distance = distances[i]
                current_node = i

        if current_node == -1:
            break  # No more reachable nodes

        visited[current_node] = True  # Mark the current node as visited

        # Update distances to the neighbors of the current node
        for neighbor in range(num_nodes):
            if (
                    graph_matrix[current_node][neighbor] != 0
                    and not visited[neighbor]
                    and distances[current_node] != float('inf')
            ):
                new_distance = distances[current_node] + graph_matrix[current_node][neighbor]
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    path[neighbor] = list(path[current_node])
                    path[neighbor].append(neighbor)

    return distances, path
if __name__ == "__main__":
    # Example graph represented as an adjacency list
    graph = {
        'A': [('B', 1), ('C', 4)],
        'B': [('A', 1), ('D', 3), ('E', 7)],
        'C': [('A', 4), ('D', 1), ('F', 5)],
        'D': [('B', 3), ('C', 1), ('E', 2), ('F', 1)],
        'E': [('B', 7), ('D', 2), ('G', 2)],
        'F': [('C', 5), ('D', 1), ('G', 3)],
        'G': [('E', 2), ('F', 3)]
    }
    start_node = 'A'

    # Example graph represented as an adjacency matrix
    # 0 represents no edge, INF represents non-existent edge.
    graph_matrix = [
        [0, 1, 4, 0, 0, 0, 0],  # A
        [1, 0, 0, 3, 7, 0, 0],  # B
        [4, 0, 0, 1, 0, 5, 0],  # C
        [0, 3, 1, 0, 2, 1, 0],  # D
        [0, 7, 0, 2, 0, 0, 2],  # E
        [0, 0, 5, 1, 0, 0, 3],  # F
        [0, 0, 0, 0, 2, 3, 0]   # G
    ]
    start_node_matrix = 0  # Starting node index (A)

    # 1. Dijkstra's Algorithm using Priority Queue (heapq)
    print("\n1. Dijkstra's Algorithm using Priority Queue (heapq):")
    distances_heapq, path_heapq = dijkstra_heapq(graph, start_node)
    print_result(distances_heapq, path_heapq, start_node)

    # 2. Dijkstra's Algorithm using Priority Queue and Visited Set
    print("\n2. Dijkstra's Algorithm using Priority Queue and Visited Set:")
    distances_heapq_visited, path_heapq_visited = dijkstra_heapq_visited(graph, start_node)
    print_result(distances_heapq_visited, path_heapq_visited, start_node)

    # 3. Dijkstra's Algorithm using Relaxation
    print("\n3. Dijkstra's Algorithm using Relaxation:")
    distances_relaxation, path_relaxation = dijkstra_relaxation(graph, start_node)
    print_result(distances_relaxation, path_relaxation, start_node)

    # 4. Dijkstra's Algorithm using a dictionary as a priority queue
    print("\n4. Dijkstra's Algorithm using a dictionary as a priority queue:")
    distances_dict, path_dict = dijkstra_dict(graph, start_node)
    print_result(distances_dict, path_dict, start_node)

    # 5. Dijkstra's Algorithm with Adjacency Matrix
    print("\n5. Dijkstra's Algorithm with Adjacency Matrix:")
    distances_matrix, path_matrix = dijkstra_matrix(graph_matrix, start_node_matrix)
    print("Shortest distances from node 0:", distances_matrix)
    print("Shortest paths from node 0:", path_matrix)
    print_result(distances_matrix, path_matrix, start_node_matrix)

import heapq  # For the heapq implementation of the priority queue
import sys  # For accessing the maximum integer value
from collections import defaultdict # For creating dictionaries of lists

def dijkstra_heapq(graph, start):
    """
    Dijkstra's algorithm using the heapq module for the priority queue.

    Args:
        graph: A dictionary representing the graph.  Keys are nodes, and values
               are lists of (neighbor, edge_weight) tuples.
        start: The starting node for the algorithm.

    Returns:
        A dictionary where keys are nodes, and values are the shortest distance
        from the start node.
    """
    distances = {node: float('inf') for node in graph}  # Initialize distances to infinity
    distances[start] = 0  # Distance to the start node is 0
    priority_queue = [(0, start)]  # (distance, node) tuple
    #  Using heapq, priority queue is a min heap, so the smallest distance is always at the top.

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)  # Get the node with the smallest distance

        if dist > distances[current_node]:
            continue  # Important optimization:  If the distance we have is greater
            # than the known shortest distance to this node, skip it.

        for neighbor, edge_weight in graph[current_node]:
            new_distance = distances[current_node] + edge_weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))  # Add with the new distance

    return distances



def dijkstra_list_as_queue(graph, start):
    """
    Dijkstra's algorithm using a Python list as a basic priority queue
    (implemented without using heapq).  This is less efficient, but shows the basic idea.
    We sort the list to find the minimum.

    Args:
        graph: A dictionary representing the graph.
        start: The starting node.

    Returns:
        A dictionary of shortest distances from the start node.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)] # (distance, node)

    while priority_queue:
        priority_queue.sort()  # Sort by distance.  This is the inefficient part.
        dist, current_node = priority_queue.pop(0) # Get the node with the smallest distance

        if dist > distances[current_node]:
            continue

        for neighbor, edge_weight in graph[current_node]:
            new_distance = distances[current_node] + edge_weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                priority_queue.append((new_distance, neighbor))
    return distances


def dijkstra_modified_list(graph, start):
    """
    Dijkstra's algorithm using a Python list, but with a slight optimization
    to reduce sorting.  We find the minimum, then remove it.

    Args:
        graph: Adjacency list representation of the graph.
        start: Starting node.

    Returns:
         Dictionary of shortest path distances.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        min_dist = float('inf')
        min_index = -1
        for i, (dist, _) in enumerate(priority_queue): # Find min distance
            if dist < min_dist:
                min_dist = dist
                min_index = i

        dist, current_node = priority_queue.pop(min_index) # Remove min element

        if dist > distances[current_node]:
            continue

        for neighbor, edge_weight in graph[current_node]:
            new_distance = distances[current_node] + edge_weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                priority_queue.append((new_distance, neighbor))
    return distances



def dijkstra_no_queue(graph, start):
    """
    Dijkstra's algorithm without using any explicit priority queue.  It
    iterates through all nodes to find the one with the minimum distance.
    This is the most inefficient version, O(V^2 + E), where V is the number of vertices.

    Args:
        graph: The graph represented as an adjacency list.
        start: The source node.

    Returns:
        Dictionary of shortest distances.
    """
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    visited = {node: False for node in graph} # Keep track of visited nodes

    for _ in range(len(graph)): # Iterate V times
        min_distance = float('inf')
        current_node = None

        for node in graph: # Find the unvisited node with the smallest distance
            if not visited[node] and distances[node] < min_distance:
                min_distance = distances[node]
                current_node = node

        if current_node is None:
            break  # No more reachable nodes

        visited[current_node] = True # Mark current node as visited

        for neighbor, edge_weight in graph[current_node]:
            new_distance = distances[current_node] + edge_weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
    return distances


def dijkstra_defaultdict(graph_dict, start_node):
    """
    Dijkstra's algorithm using defaultdict for graph representation and heapq for the priority queue.

    Args:
        graph_dict (dict): A dictionary representing the graph where keys are nodes and values are
                           lists of tuples (neighbor, edge_weight).  Uses defaultdict.
        start_node: The starting node for Dijkstra's algorithm.

    Returns:
        dict: A dictionary containing the shortest distances from the start_node to all other nodes
              in the graph.
    """

    distances = {node: float('inf') for node in graph_dict}
    distances[start_node] = 0
    priority_queue = [(0, start_node)]

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph_dict[current_node]:
            distance_to_neighbor = current_distance + weight
            if distance_to_neighbor < distances[neighbor]:
                distances[neighbor] = distance_to_neighbor
                heapq.heappush(priority_queue, (distance_to_neighbor, neighbor))

    return distances



if __name__ == "__main__":
    # Example graph represented as a dictionary (adjacency list)
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

    print("Graph:")
    for node, edges in graph.items():
        print(f"{node}: {edges}")
    print(f"Starting Node: {start_node}\n")


    # Dijkstra's Algorithm with heapq
    print("Dijkstra's Algorithm with heapq:")
    distances_heapq = dijkstra_heapq(graph, start_node)
    print(f"Shortest distances from {start_node}: {distances_heapq}")

    # Dijkstra's Algorithm with list as queue
    print("\nDijkstra's Algorithm with list as queue:")
    distances_list_queue = dijkstra_list_as_queue(graph, start_node)
    print(f"Shortest distances from {start_node}: {distances_list_queue}")

    print("\nDijkstra's Algorithm with modified list:")
    distances_modified_list = dijkstra_modified_list(graph, start_node)
    print(f"Shortest distances from {start_node}: {distances_modified_list}")

    # Dijkstra's Algorithm without queue
    print("\nDijkstra's Algorithm without queue:")
    distances_no_queue = dijkstra_no_queue(graph, start_node)
    print(f"Shortest distances from {start_node}: {distances_no_queue}")

    # Example graph using defaultdict
    graph_defaultdict = defaultdict(list)
    graph_defaultdict['A'].extend([('B', 1), ('C', 4)])
    graph_defaultdict['B'].extend([('A', 1), ('D', 3), ('E', 7)])
    graph_defaultdict['C'].extend([('A', 4), ('D', 1), ('F', 5)])
    graph_defaultdict['D'].extend([('B', 3), ('C', 1), ('E', 2), ('F', 1)])
    graph_defaultdict['E'].extend([('B', 7), ('D', 2), ('G', 2)])
    graph_defaultdict['F'].extend([('C', 5), ('D', 1), ('G', 3)])
    graph_defaultdict['G'].extend([('E', 2), ('F', 3)])

    print("\nGraph using defaultdict:")
    for node, edges in graph_defaultdict.items():
        print(f"{node}: {edges}")

    print("\nDijkstra's Algorithm with defaultdict:")
    distances_defaultdict = dijkstra_defaultdict(graph_defaultdict, start_node)
    print(f"Shortest distances from {start_node}: {distances_defaultdict}")

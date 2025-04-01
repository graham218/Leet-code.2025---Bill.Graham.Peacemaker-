import heapq
import sys
from collections import defaultdict
import time
from typing import Dict, List, Tuple, Optional, Callable

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

# 1. Dijkstra with Time Profiling and Logging
def dijkstra_time_profile(graph: Dict[str, List[Tuple[str, float]]], start_node: str, log_func: Optional[Callable[[str], None]] = None) -> Tuple[Dict[str, float], Dict[str, List[str]]]:
    """
    Dijkstra's algorithm with time profiling and optional logging.  This is useful
    for performance analysis in real-world applications.

    Args:
        graph: Adjacency list representation of the graph.
        start_node: The starting node.
        log_func: Optional logging function.  If provided, log messages will be
                  printed using this function.  Defaults to None (no logging).

    Returns:
        A tuple containing distances and paths.
    """
    start_time = time.time()
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = [(0, start_node)]
    path = {start_node: [start_node]}

    if log_func:
        log_func(f"Starting Dijkstra from node {start_node}")

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if dist > distances[current_node]:
            continue

        if log_func:
            log_func(f"  Processing node {current_node} with distance {dist}")

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
                if log_func:
                    log_func(f"    Updated distance to {neighbor} to {new_distance}")

    end_time = time.time()
    if log_func:
        log_func(f"Dijkstra finished in {end_time - start_time:.4f} seconds")
    return distances, path

# 2. Dijkstra with Node IDs (for database integration)
def dijkstra_node_ids(graph: Dict[int, List[Tuple[int, float]]], start_node_id: int) -> Tuple[Dict[int, float], Dict[int, List[int]]]:
    """
    Dijkstra's algorithm using integer node IDs, suitable for database integration.
    In real-world applications, nodes are often represented by unique integer IDs
    in a database.

    Args:
        graph: Adjacency list, but with integer node IDs.
        start_node_id: Integer ID of the starting node.

    Returns:
        A tuple containing distances and paths, both using integer IDs.
    """
    distances = {node_id: float('inf') for node_id in graph}
    distances[start_node_id] = 0
    priority_queue = [(0, start_node_id)]
    path = {start_node_id: [start_node_id]}

    while priority_queue:
        dist, current_node_id = heapq.heappop(priority_queue)

        if dist > distances[current_node_id]:
            continue

        for neighbor_id, weight in graph[current_node_id]:
            new_distance = dist + weight
            if new_distance < distances[neighbor_id]:
                distances[neighbor_id] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor_id))
                path[neighbor_id] = list(path[current_node_id])
                path[neighbor_id].append(neighbor_id)
    return distances, path

# 3. Dijkstra with Heuristic (A* - like) -  Informed Search
def dijkstra_heuristic(graph: Dict[str, List[Tuple[str, float]]], start_node: str, heuristic: Dict[str, float]) -> Tuple[Dict[str, float], Dict[str, List[str]]]:
    """
    Dijkstra's algorithm with a heuristic function (similar to A*).  This can improve
    performance if a good heuristic is available, guiding the search towards the goal.
    This version assumes we have a heuristic function that estimates the distance
    from any node to the goal.  In a real application, the heuristic would be
    problem-specific (e.g., Euclidean distance for GPS navigation).
    This version does NOT assume a goal node.  It calculates shortest paths to ALL nodes,
    but uses the heuristic to influence the order in which nodes are explored.

    Args:
        graph: Adjacency list representation of the graph.
        start_node: The starting node.
        heuristic: A dictionary of heuristic values for each node.  For each node, it estimates the distance to the goal.

    Returns:
        A tuple containing distances and paths.
    """
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = [(heuristic[start_node], 0, start_node)]  # Use f-value (h + g)
    path = {start_node: [start_node]}

    while priority_queue:
        _, dist, current_node = heapq.heappop(priority_queue)  # Get node with smallest f-value

        if dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                #  f(n) = g(n)
                f_value = new_distance + heuristic[neighbor] # Calculate f-value
                heapq.heappush(priority_queue, (f_value, new_distance, neighbor))
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
    return distances, path

# 4. Dijkstra for Real-Time Traffic Updates (Edge Weight Changes)
def dijkstra_dynamic_updates(graph: Dict[str, List[Tuple[str, float]]], start_node: str, traffic_updates: List[Tuple[str, str, float]]) -> Tuple[Dict[str, float], Dict[str, List[str]]]:
    """
    Dijkstra's algorithm with support for real-time traffic updates (edge weight changes).
    In a real-world navigation system, traffic conditions change dynamically.  This
    version allows you to update the graph's edge weights and re-run Dijkstra's
    algorithm to get the new shortest paths.  For simplicity, this version
    recomputes the entire shortest path tree from the start node.  For a very large
    graph and frequent updates, more optimized techniques (like the
    Dijkstra's algorithm with dynamic updates) may be needed.

    Args:
        graph: Adjacency list representation of the graph.
        start_node: The starting node.
        traffic_updates: A list of tuples, where each tuple represents a traffic update:
                         (node1, node2, new_weight).  This means the weight of the edge
                         from node1 to node2 is changed to new_weight.

    Returns:
        A tuple containing distances and paths after applying the updates.
    """
    # Apply traffic updates to the graph
    for u, v, new_weight in traffic_updates:
        found = False
        for i, (neighbor, weight) in enumerate(graph[u]):
            if neighbor == v:
                graph[u][i] = (v, new_weight)  # Update the edge weight
                found = True
                break
        if not found:
            graph[u].append((v, new_weight)) # add the edge if it does not exist

    # Re-run Dijkstra's algorithm with the updated graph
    distances, path = dijkstra_time_profile(graph, start_node, None)  # Use the basic heapq version
    return distances, path



# 5.  Dijkstra with a custom data structure
class MinHeap:
    """
    A custom min-heap implementation.  This is a more verbose implementation
    compared to using heapq, but it provides more control and can be
    instructive for understanding how priority queues work.  In a real-world
    scenario, you might use this if you need very specific control over the
    heap's behavior or if you are working in an environment without access to
    the standard heapq module.
    """
    def __init__(self):
        self.heap_array = []
        self.size = 0
        self.position = {}  # Dictionary to store the position of each node in the heap

    def __len__(self):
        return self.size

    def is_empty(self):
        return self.size == 0

    def insert(self, key, value):
        """
        Insert a new node (key, value) into the min-heap.
        key is the node, value is the distance.
        """
        if key in self.position:
            return  # Key already exists, handle as you see fit (update, error, etc.)
        self.heap_array.append((key, value))
        self.position[key] = self.size
        self.size += 1
        self.bubble_up(self.size - 1)

    def extract_min(self):
        """
        Extract the node with the minimum value (distance) from the heap.
        """
        if self.is_empty():
            return None
        if self.size == 1:
            self.size -= 1
            key, value = self.heap_array.pop()
            del self.position[key]
            return key, value

        root = self.heap_array[0]
        self.heap_array[0] = self.heap_array[self.size - 1]
        self.position[self.heap_array[0][0]] = 0  # Update position of the new root
        self.heap_array.pop()
        self.size -= 1
        del self.position[root[0]]
        self.min_heapify(0)
        return root[0], root[1]

    def bubble_up(self, index):
        """
        Move a node up the heap to its correct position.
        """
        parent = (index - 1) // 2
        while index > 0 and self.heap_array[index][1] < self.heap_array[parent][1]:
            self.swap(index, parent)
            index = parent
            parent = (index - 1) // 2

    def min_heapify(self, index):
        """
        Move a node down the heap to its correct position.
        """
        left = 2 * index + 1
        right = 2 * index + 2
        smallest = index
        if left < self.size and self.heap_array[left][1] < self.heap_array[smallest][1]:
            smallest = left
        if right < self.size and self.heap_array[right][1] < self.heap_array[smallest][1]:
            smallest = right
        if smallest != index:
            self.swap(index, smallest)
            self.min_heapify(smallest)

    def decrease_key(self, key, new_value):
        """
        Decrease the value (distance) of a node in the heap.
        """
        if key not in self.position:
            return
        index = self.position[key]
        if self.heap_array[index][1] > new_value:
            self.heap_array[index] = (key, new_value)
            self.bubble_up(index)

    def swap(self, i, j):
        """
        Swap two nodes in the heap.
        """
        self.position[self.heap_array[i][0]] = j
        self.position[self.heap_array[j][0]] = i
        self.heap_array[i], self.heap_array[j] = self.heap_array[j], self.heap_array[i]
def dijkstra_custom_heap(graph: Dict[str, List[Tuple[str, float]]], start_node: str) -> Tuple[Dict[str, float], Dict[str, List[str]]]:
    """
    Dijkstra's algorithm using a custom min-heap implementation.

    Args:
        graph: Adjacency list representation of the graph.
        start_node: The starting node.

    Returns:
        A tuple containing distances and paths.
    """
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = MinHeap()
    priority_queue.insert(start_node, 0)
    path = {start_node: [start_node]}

    while not priority_queue.is_empty():
        current_node, dist = priority_queue.extract_min()

        if dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node]:
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                priority_queue.decrease_key(neighbor, new_distance)
                if neighbor not in priority_queue.position:
                    priority_queue.insert(neighbor, new_distance)
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
    return distances, path

# 6. Dijkstra with alternative graph representation
def dijkstra_alternative_graph(graph_data: Dict[str, Dict[str, float]], start_node: str) -> Tuple[Dict[str, float], Dict[str, List[str]]]:
    """
    Dijkstra's algorithm with an alternative graph representation.
    The graph is represented as a dictionary where keys are nodes, and values are
    dictionaries mapping neighbor nodes to edge weights.
    For example:
    {
        'A': {'B': 1, 'C': 4},
        'B': {'A': 1, 'D': 3, 'E': 7},
        ...
    }

    Args:
        graph_data: Alternative adjacency list representation of the graph.
        start_node: The starting node.

    Returns:
        A tuple containing distances and paths.
    """
    distances = {node: float('inf') for node in graph_data}
    distances[start_node] = 0
    priority_queue = [(0, start_node)]
    path = {start_node: [start_node]}

    while priority_queue:
        dist, current_node = heapq.heappop(priority_queue)

        if dist > distances[current_node]:
            continue

        for neighbor, weight in graph_data[current_node].items():
            new_distance = dist + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))
                path[neighbor] = list(path[current_node])
                path[neighbor].append(neighbor)
    return distances, path
if __name__ == "__main__":
    # Example graph
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

    # 1. Dijkstra with Time Profiling and Logging
    print("\n1. Dijkstra with Time Profiling and Logging:")
    def log_message(message):
        print(f"[LOG] {message}")
    distances_time_profile, path_time_profile = dijkstra_time_profile(graph, start_node, log_func=log_message)
    print_result(distances_time_profile, path_time_profile, start_node)

    # 2. Dijkstra with Node IDs
    print("\n2. Dijkstra with Node IDs:")
    graph_with_ids = {
        1: [(2, 1), (3, 4)],
        2: [(1, 1), (4, 3), (5, 7)],
        3: [(1, 4), (4, 1), (6, 5)],
        4: [(2, 3), (3, 1), (5, 2), (6, 1)],
        5: [(2, 7), (4, 2), (7, 2)],
        6: [(3, 5), (4, 1), (7, 3)],
        7: [(5, 2), (6, 3)]
    }
    start_node_id = 1
    distances_node_ids, path_node_ids = dijkstra_node_ids(graph_with_ids, start_node_id)
    print("Distances:", distances_node_ids)
    print("Paths:", path_node_ids)

    # 3. Dijkstra with Heuristic (A* - like)
    print("\n3. Dijkstra with Heuristic (A* - like):")
    heuristic_values = {
        'A': 7,  # Example heuristic values (actual values would depend on the problem)
        'B': 6,
        'C': 5,
        'D': 4,
        'E': 3,
        'F': 2,
        'G': 0
    }
    distances_heuristic, path_heuristic = dijkstra_heuristic(graph, start_node, heuristic_values)
    print_result(distances_heuristic, path_heuristic, start_node)

    # 4. Dijkstra for Real-Time Traffic Updates
    print("\n4. Dijkstra for Real-Time Traffic Updates:")
    traffic_updates = [('A', 'B', 2), ('D', 'F', 3)]  # Increase weight of A->B, D->F
    distances_dynamic, path_dynamic = dijkstra_dynamic_updates(graph, start_node, traffic_updates)
    print_result(distances_dynamic, path_dynamic, start_node)
    print("Original Graph", graph)

    # 5. Dijkstra with a custom data structure
    print("\n5. Dijkstra with a custom data structure:")
    distances_custom_heap, path_custom_heap = dijkstra_custom_heap(graph, start_node)
    print_result(distances_custom_heap, path_custom_heap, start_node)

    # 6. Dijkstra with alternative graph representation
    print("\n6. Dijkstra with alternative graph representation:")
    alternative_graph_data = {
        'A': {'B': 1, 'C': 4},
        'B': {'A': 1, 'D': 3, 'E': 7},
        'C': {'A': 4, 'D': 1, 'F': 5},
        'D': {'B': 3, 'C': 1, 'E': 2, 'F': 1},
        'E': {'B': 7, 'D': 2, 'G': 2},
        'F': {'C': 5, 'D': 1, 'G': 3},
        'G': {'E': 2, 'F': 3}
    }
    distances_alternative, path_alternative = dijkstra_alternative_graph(alternative_graph_data, start_node)
    print_result(distances_alternative, path_alternative, start_node)


from collections import deque
from typing import List, Dict, Set, Tuple, Optional
import heapq

# Define a more complex graph representation, supporting edge weights and node metadata.
class Graph:
    """
    A more advanced graph class that supports weighted edges and node metadata.
    It uses an adjacency list representation.
    """
    def __init__(self):
        self.adj_list: Dict[int, List[Tuple[int, float]]] = {}  # {node: [(neighbor, weight), ...]}
        self.node_metadata: Dict[int, dict] = {}  # {node: {metadata_key: value, ...}}

    def add_node(self, node: int, metadata: Optional[dict] = None) -> None:
        """Adds a node to the graph."""
        if node not in self.adj_list:
            self.adj_list[node] = []
            self.node_metadata[node] = metadata if metadata else {}
        else:
            print(f"Node {node} already exists.")

    def add_edge(self, u: int, v: int, weight: float = 1.0) -> None:
        """Adds a directed edge from node u to node v with a specified weight."""
        if u not in self.adj_list:
            self.add_node(u)
        if v not in self.adj_list:
            self.add_node(v)
        self.adj_list[u].append((v, weight))

    def get_neighbors(self, node: int) -> List[Tuple[int, float]]:
        """Returns the neighbors of a node along with the edge weights."""
        return self.adj_list.get(node, [])

    def get_node_metadata(self, node: int) -> Optional[dict]:
        """Retrieves the metadata associated with a node."""
        return self.node_metadata.get(node)

    def update_node_metadata(self, node: int, key: str, value: any) -> None:
        """Updates the metadata for a given node."""
        if node in self.node_metadata:
            self.node_metadata[node][key] = value
        else:
            print(f"Node {node} does not exist.")

    def __str__(self) -> str:
        """Returns a string representation of the graph."""
        return f"Adjacency List: {self.adj_list}, Node Metadata: {self.node_metadata}"

def create_advanced_graph() -> Graph:
    """
    Creates a sample advanced graph for demonstration.
    """
    graph = Graph()
    graph.add_node(0, {"name": "A", "type": "start"})
    graph.add_node(1, {"name": "B", "type": "intermediate"})
    graph.add_node(2, {"name": "C", "type": "intermediate"})
    graph.add_node(3, {"name": "D", "type": "end"})
    graph.add_node(4, {"name": "E", "type": "intermediate"})
    graph.add_edge(0, 1, 2.0)
    graph.add_edge(0, 2, 4.0)
    graph.add_edge(1, 3, 5.0)
    graph.add_edge(1, 4, 1.0)
    graph.add_edge(2, 4, 3.0)
    graph.add_edge(4, 3, 1.0)
    return graph

# 1.  Iterative BFS with Node Metadata and Edge Weights
def bfs_advanced(graph: Graph, start_node: int) -> List[Tuple[int, float, dict]]:
    """
    Performs BFS on a graph with node metadata and edge weights.

    Args:
        graph: The advanced graph object.
        start_node: The starting node for the BFS traversal.

    Returns:
        List[Tuple[int, float, dict]]: A list of tuples, where each tuple contains:
            - The visited node ID.
            - The cumulative distance from the start node.
            - The metadata of the visited node.
    """
    visited: Set[int] = set()
    queue: deque[Tuple[int, float]] = deque([(start_node, 0.0)])  # (node, distance)
    visited.add(start_node)
    traversal_order: List[Tuple[int, float, dict]] = []

    print(f"\n1. Advanced BFS with Metadata and Weights, starting from node {start_node}:")

    while queue:
        node, distance = queue.popleft()
        node_metadata = graph.get_node_metadata(node)
        traversal_order.append((node, distance, node_metadata))

        for neighbor, weight in graph.get_neighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, distance + weight))  # Accumulate the distance
    return traversal_order

# 2. BFS with Early Exit Condition
def bfs_early_exit(graph: Graph, start_node: int, target_node: int) -> Optional[List[int]]:
    """
    Performs BFS with an early exit condition when the target node is found.
    This is useful for pathfinding when you only need to find *a* path, not necessarily the shortest.

    Args:
        graph: The graph to search.
        start_node: The starting node.
        target_node: The node to search for.

    Returns:
        Optional[List[int]]:  The path from start to target (including both), or None if no path is found.
    """
    visited: Set[int] = set()
    queue: deque[Tuple[int, List[int]]] = deque([(start_node, [start_node])]) # Store the path
    visited.add(start_node)

    print(f"\n2. BFS with Early Exit, searching for path from {start_node} to {target_node}:")
    while queue:
        node, path = queue.popleft()
        if node == target_node:
            return path # Return the path

        for neighbor, _ in graph.get_neighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [neighbor]))
    return None

# 3.  BFS for Finding Connected Components with Metadata
def bfs_connected_components_metadata(graph: Graph) -> List[List[Tuple[int, dict]]]:
    """
    Finds the connected components of a graph, including node metadata.

    Args:
        graph: The graph to process.

    Returns:
        List[List[Tuple[int, dict]]]: A list of connected components.  Each component is a list of
                                     (node_id, node_metadata) tuples.
    """
    visited: Set[int] = set()
    components: List[List[Tuple[int, dict]]] = []

    print(f"\n3. BFS for Connected Components with Metadata:")
    for node in graph.adj_list:
        if node not in visited:
            queue: deque[int] = deque([node])
            visited.add(node)
            component: List[Tuple[int, dict]] = []
            while queue:
                curr_node = queue.popleft()
                node_metadata = graph.get_node_metadata(curr_node)
                component.append((curr_node, node_metadata))
                for neighbor, _ in graph.get_neighbors(curr_node):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            components.append(component)
    return components

# 4.  BFS with Layer Information (Distance from Start)
def bfs_with_layers(graph: Graph, start_node: int) -> Dict[int, List[int]]:
    """
    Performs BFS and returns nodes organized by their layer (distance from the start node).

    Args:
        graph: The graph to traverse.
        start_node: The starting node.

    Returns:
        Dict[int, List[int]]: A dictionary where keys are layer numbers (distances) and
                               values are lists of nodes in that layer.
    """
    visited: Set[int] = set()
    queue: deque[Tuple[int, int]] = deque([(start_node, 0)])  # (node, layer)
    visited.add(start_node)
    layers: Dict[int, List[int]] = {}

    print(f"\n4. BFS with Layer Information, starting from node {start_node}:")
    while queue:
        node, layer = queue.popleft()
        if layer not in layers:
            layers[layer] = []
        layers[layer].append(node)
        for neighbor, _ in graph.get_neighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, layer + 1))
    return layers

# 5.  Weighted BFS with Dijkstra's Algorithm (Corrected for Positive Weights)
def dijkstra_bfs(graph: Graph, start_node: int) -> Dict[int, float]:
    """
    Implements Dijkstra's algorithm using a priority queue (heapq) for finding the shortest paths
    from a start node to all other nodes in a weighted graph.  This version assumes
    non-negative edge weights, which is crucial for Dijkstra's correctness.  If negative weights
    are present, use Bellman-Ford instead.

    Args:
        graph: The weighted graph.
        start_node: The starting node.

    Returns:
        Dict[int, float]: A dictionary of shortest distances from the start node to each reachable node.
                          Nodes not reachable from the start node will not be in the dictionary.
    """
    distances: Dict[int, float] = {node: float('inf') for node in graph.adj_list}  # Initialize all distances to infinity
    distances[start_node] = 0.0  # Distance from start node to itself is 0
    priority_queue: List[Tuple[float, int]] = [(0.0, start_node)]  # (distance, node)
    visited: Set[int] = set() # Keep track of visited

    print(f"\n5. Weighted BFS (Dijkstra's Algorithm), starting from node {start_node}:")

    while priority_queue:
        dist, u = heapq.heappop(priority_queue)  # Get the node with the smallest distance
        if u in visited:
            continue
        visited.add(u)

        if dist > distances[u]:
            continue  # Important optimization: avoid outdated entries in the queue

        for v, weight in graph.get_neighbors(u):
            new_dist = distances[u] + weight
            if new_dist < distances[v]:
                distances[v] = new_dist
                heapq.heappush(priority_queue, (new_dist, v))  # Add to the queue with the new distance
    return distances

# 6.  BFS for Network Routing (Finding Neighbors within a Hop Distance)
def bfs_network_routing(graph: Graph, start_node: int, max_hops: int) -> Dict[int, int]:
    """
    Finds all nodes within a specified number of hops from a start node in a network graph.
    This is useful for network routing protocols.

    Args:
        graph: The network graph.
        start_node: The starting node.
        max_hops: The maximum number of hops to traverse.

    Returns:
        Dict[int, int]: A dictionary where keys are the reachable nodes within max_hops,
                       and values are the number of hops from the start node.
    """
    visited: Set[int] = set()
    queue: deque[Tuple[int, int]] = deque([(start_node, 0)])  # (node, hops)
    visited.add(start_node)
    reachable_nodes: Dict[int, int] = {start_node: 0}

    print(f"\n6. BFS for Network Routing (max_hops = {max_hops}), starting from node {start_node}:")
    while queue:
        node, hops = queue.popleft()
        if hops < max_hops:
            for neighbor, _ in graph.get_neighbors(node):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, hops + 1))
                    reachable_nodes[neighbor] = hops + 1
    return reachable_nodes

if __name__ == "__main__":
    advanced_graph = create_advanced_graph()
    print("Advanced Graph:")
    print(advanced_graph)

    # 1. BFS with Metadata and Weights
    bfs_result_1 = bfs_advanced(advanced_graph, 0)
    print("BFS Traversal (Node, Distance, Metadata):")
    for node, distance, metadata in bfs_result_1:
        print(f"Node: {node}, Distance: {distance}, Metadata: {metadata}")

    # 2. BFS with Early Exit
    path_to_3 = bfs_early_exit(advanced_graph, 0, 3)
    print(f"Path from 0 to 3: {path_to_3}")

    # 3. BFS for Connected Components with Metadata
    components_with_metadata = bfs_connected_components_metadata(advanced_graph)
    print("Connected Components (with Metadata):")
    for component in components_with_metadata:
        print(component)

    # 4. BFS with Layer Information
    layers = bfs_with_layers(advanced_graph, 0)
    print("BFS Layers:")
    for layer, nodes in layers.items():
        print(f"Layer {layer}: {nodes}")

    # 5. Weighted BFS (Dijkstra's)
    shortest_distances = dijkstra_bfs(advanced_graph, 0)
    print("Shortest Distances from node 0 (Dijkstra's):")
    print(shortest_distances)

    # 6. BFS for Network Routing
    reachable_nodes_within_2_hops = bfs_network_routing(advanced_graph, 0, 2)
    print("Reachable Nodes within 2 Hops from node 0:")
    print(reachable_nodes_within_2_hops)

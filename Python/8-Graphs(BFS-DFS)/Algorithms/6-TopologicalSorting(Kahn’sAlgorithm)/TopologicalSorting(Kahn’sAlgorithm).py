from collections import defaultdict, deque
from typing import List, Dict

class Graph:
    """
    A class to represent a directed graph.  Uses an adjacency list
    representation.
    """
    def __init__(self, num_vertices: int):
        """
        Constructor for the Graph class.

        Args:
            num_vertices: The number of vertices in the graph.
        """
        self.num_vertices = num_vertices
        self.adj_list = defaultdict(list)  # Adjacency list representation
        self.in_degree = [0] * num_vertices # Array to store in-degrees

    def add_edge(self, u: int, v: int) -> None:
        """
        Adds a directed edge from vertex u to vertex v.

        Args:
            u: The starting vertex of the edge.
            v: The ending vertex of the edge.
        """
        self.adj_list[u].append(v)
        self.in_degree[v] += 1 # Increment in-degree of destination

    def get_indegree(self) -> List[int]:
        """
        Returns the in-degree list of the graph.

        Returns:
            A list representing the in-degrees of each vertex.
        """
        return self.in_degree

    def get_adj_list(self) -> Dict[int, List[int]]:
        """
        Returns the adjacency list representation of the graph.

        Returns:
            A dictionary representing the adjacency list.
        """
        return self.adj_list

    def __str__(self) -> str:
        """
        Returns a string representation of the graph.

        Returns:
            A string showing the number of vertices and the adjacency list.
        """
        return f"Graph with {self.num_vertices} vertices and adjacency list: {self.adj_list}"

def topological_sort_kahns_1(graph: Graph) -> List[int]:
    """
    Kahn's algorithm for topological sorting - Version 1.
    Finds nodes with in-degree 0, adds them to a queue, and iteratively
    removes nodes from the queue, adding their neighbors to the queue if
    their in-degrees become 0.

    Args:
        graph: A Graph object.

    Returns:
        A list representing the topological order of the vertices.
        Returns an empty list if the graph has a cycle.
    """
    in_degree = graph.get_indegree()
    queue = deque([i for i in range(graph.num_vertices) if in_degree[i] == 0])
    # Initialize queue with nodes having in-degree 0
    topological_order = []

    while queue:
        u = queue.popleft() # Get the next node
        topological_order.append(u) # Add to topological order
        for neighbor in graph.adj_list[u]:
            in_degree[neighbor] -= 1 # Reduce in-degree of neighbors
            if in_degree[neighbor] == 0:
                queue.append(neighbor) # Add to queue if in-degree is 0

    if len(topological_order) != graph.num_vertices:
        return []  # Cycle detected
    return topological_order

def topological_sort_kahns_2(graph: Graph) -> List[int]:
    """
    Kahn's algorithm for topological sorting - Version 2.
    Slightly different variable names for clarity.

    Args:
        graph: A Graph object.

    Returns:
        A list representing the topological order of the vertices.
        Returns an empty list if the graph has a cycle.
    """
    in_degrees = graph.get_indegree()
    nodes_with_no_incoming_edges = deque([node for node in range(graph.num_vertices) if in_degrees[node] == 0])
    # Initialize queue
    sorted_nodes = []

    while nodes_with_no_incoming_edges:
        current_node = nodes_with_no_incoming_edges.popleft()
        sorted_nodes.append(current_node)
        for neighbor in graph.adj_list[current_node]:
            in_degrees[neighbor] -= 1
            if in_degrees[neighbor] == 0:
                nodes_with_no_incoming_edges.append(neighbor)

    if len(sorted_nodes) != graph.num_vertices:
        return []  # Cycle detected
    return sorted_nodes

def topological_sort_kahns_3(graph: Graph) -> List[int]:
    """
    Kahn's algorithm for topological sorting - Version 3.
    More detailed comments.

    Args:
        graph: A Graph object.

    Returns:
        A list representing the topological order of the vertices.
        Returns an empty list if the graph has a cycle.
    """
    in_degree_counts = graph.get_indegree() # Get in-degrees
    # Use a list as a queue (for demonstration; deque is preferred for efficiency)
    queue_of_nodes_with_no_incoming_edges = [node for node in range(graph.num_vertices) if in_degree_counts[node] == 0]
    topologically_sorted_list = [] # Store result

    while queue_of_nodes_with_no_incoming_edges:
        # Get and remove a node from the front of the queue
        current_node = queue_of_nodes_with_no_incoming_edges.pop(0)
        topologically_sorted_list.append(current_node) # Add to result

        # Iterate through the neighbors of the current node
        for neighbor_node in graph.adj_list[current_node]:
            in_degree_counts[neighbor_node] -= 1 # Reduce in-degree
            # If the in-degree of a neighbor becomes 0, add it to the queue
            if in_degree_counts[neighbor_node] == 0:
                queue_of_nodes_with_no_incoming_edges.append(neighbor_node)

    # Check for cycle: If all nodes were not processed, there's a cycle
    if len(topologically_sorted_list) != graph.num_vertices:
        return []  # Return empty list to indicate cycle
    return topologically_sorted_list

def topological_sort_kahns_4(graph: Graph) -> List[int]:
    """
    Kahn's algorithm for topological sorting - Version 4.
    Using a helper function to find initial nodes.

    Args:
        graph: A Graph object.

    Returns:
        A list representing the topological order of the vertices.
        Returns an empty list if the graph has a cycle.
    """

    def find_initial_nodes(in_degrees: List[int]) -> deque:
        """Helper function to find nodes with in-degree 0."""
        initial_nodes = deque()
        for node, degree in enumerate(in_degrees):
            if degree == 0:
                initial_nodes.append(node)
        return initial_nodes

    in_degrees = graph.get_indegree()
    queue = find_initial_nodes(in_degrees) # Use helper
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph.adj_list[node]:
            in_degrees[neighbor] -= 1
            if in_degrees[neighbor] == 0:
                queue.append(neighbor)

    return result if len(result) == graph.num_vertices else []

def topological_sort_kahns_5(graph: Graph) -> List[int]:
    """
    Kahn's algorithm for topological sorting - Version 5.
    Combining some steps for conciseness.

    Args:
        graph: A Graph object.

    Returns:
        A list representing the topological order of the vertices.
        Returns an empty list if the graph has a cycle.
    """
    in_degree = graph.get_indegree()
    queue = deque(node for node in range(graph.num_vertices) if in_degree[node] == 0) # Concise init
    count = 0
    top_order = []

    while queue:
        node = queue.popleft()
        top_order.append(node)
        count += 1
        for neighbor in graph.adj_list[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    return top_order if count == graph.num_vertices else []

if __name__ == "__main__":
    # Example usage of the Graph class and topological sort functions
    num_vertices = 6
    graph = Graph(num_vertices)
    graph.add_edge(5, 2)
    graph.add_edge(5, 0)
    graph.add_edge(4, 0)
    graph.add_edge(4, 1)
    graph.add_edge(2, 3)
    graph.add_edge(3, 1)

    print("Graph:", graph)
    print("In-degrees:", graph.get_indegree())

    print("\nTopological Sort (Kahn's Algorithm - Version 1):", topological_sort_kahns_1(graph))
    print("Topological Sort (Kahn's Algorithm - Version 2):", topological_sort_kahns_2(graph))
    print("Topological Sort (Kahn's Algorithm - Version 3):", topological_sort_kahns_3(graph))
    print("Topological Sort (Kahn's Algorithm - Version 4):", topological_sort_kahns_4(graph))
    print("Topological Sort (Kahn's Algorithm - Version 5):", topological_sort_kahns_5(graph))

    # Example with a cycle (for demonstration of cycle detection)
    num_vertices_with_cycle = 4
    graph_with_cycle = Graph(num_vertices_with_cycle)
    graph_with_cycle.add_edge(0, 1)
    graph_with_cycle.add_edge(1, 2)
    graph_with_cycle.add_edge(2, 0)  # Creates a cycle

    print("\nGraph with a cycle:", graph_with_cycle)
    print("Topological Sort (Kahn's Algorithm - Version 1) with cycle:", topological_sort_kahns_1(graph_with_cycle)) # Should return []

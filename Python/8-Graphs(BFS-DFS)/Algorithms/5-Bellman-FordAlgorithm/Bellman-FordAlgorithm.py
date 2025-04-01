import math

# Approach 1: Basic Implementation with Explicit Relaxation
def bellman_ford_basic(graph, source):
    """
    Implements the Bellman-Ford algorithm to find the shortest paths from a source
    node to all other nodes in a weighted graph.

    Args:
        graph: A dictionary representing the graph where keys are nodes and values
               are lists of tuples (neighbor, weight).  For example:
               graph = {
                  'A': [('B', -1), ('C', 4)],
                  'B': [('C', 3), ('D', 2), ('E', 2)],
                  'C': [],
                  'D': [('B', 1), ('C', 5)],
                  'E': [('D', -3)]
               }
        source: The starting node (e.g., 'A').

    Returns:
        A tuple containing:
        - distances: A dictionary where keys are nodes and values are the shortest
                     distances from the source.  Returns None if a negative cycle is detected.
        - predecessor: A dictionary where keys are nodes and values are their
                       predecessor nodes in the shortest path from the source.
                       Returns None if a negative cycle is detected.
    """
    num_nodes = len(graph)
    distances = {node: float('inf') for node in graph}  # Initialize distances to infinity
    distances[source] = 0  # Distance from source to itself is 0
    predecessor = {node: None for node in graph} # Initialize predecessor

    # Relax edges repeatedly
    for _ in range(num_nodes - 1):
        for u in graph:
            for v, weight in graph[u]:
                if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight  # Update distance if shorter path is found
                    predecessor[v] = u

    # Check for negative cycles.  If a shorter path is found after the (n-1)th iteration,
    # there is a negative cycle.
    for u in graph:
        for v, weight in graph[u]:
            if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                return None, None  # Negative cycle detected

    return distances, predecessor

# Approach 2:  Early Termination Optimization
def bellman_ford_early_stop(graph, source):
    """
    Implements the Bellman-Ford algorithm with early termination. If no distances
    change during an iteration, the algorithm terminates early.

    Args:
        graph:  See description in bellman_ford_basic.
        source: The starting node.

    Returns:
        A tuple containing:
        - distances:  See description in bellman_ford_basic.
        - predecessor: See description in bellman_ford_basic.
    """
    num_nodes = len(graph)
    distances = {node: float('inf') for node in graph}
    distances[source] = 0
    predecessor = {node: None for node in graph}

    for _ in range(num_nodes - 1):
        updated = False  # Flag to check if any distance was updated in this iteration
        for u in graph:
            for v, weight in graph[u]:
                if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessor[v] = u
                    updated = True
        if not updated:  # If no updates occurred, we have found the shortest paths
            break

    for u in graph:
        for v, weight in graph[u]:
            if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                return None, None
    return distances, predecessor

# Approach 3: Graph Representation using Named Tuples
from collections import namedtuple

def bellman_ford_namedtuple(graph, source):
    """
    Implements Bellman-Ford using named tuples to represent edges,
    making the code more readable.

    Args:
        graph: A dictionary where keys are nodes and values are lists of
               Edge named tuples.
        source: The starting node.

    Returns:
        A tuple containing:
        - distances:  See description in bellman_ford_basic.
        - predecessor: See description in bellman_ford_basic.
    """
    Edge = namedtuple('Edge', ['source', 'destination', 'weight'])
    # Convert the graph representation to use named tuples
    edges = []
    for u in graph:
        for v, weight in graph[u]:
            edges.append(Edge(u, v, weight))

    num_nodes = len(graph)
    distances = {node: float('inf') for node in graph}
    distances[source] = 0
    predecessor = {node: None for node in graph}

    for _ in range(num_nodes - 1):
        for edge in edges:
            if distances[edge.source] != float('inf') and distances[edge.source] + edge.weight < distances[edge.destination]:
                distances[edge.destination] = distances[edge.source] + edge.weight
                predecessor[edge.destination] = edge.source

    for edge in edges:
        if distances[edge.source] != float('inf') and distances[edge.source] + edge.weight < distances[edge.destination]:
            return None, None
    return distances, predecessor

# Approach 4: Using a Class to Represent the Graph
class Graph:
    """
    A class to represent a weighted graph, making it easier to manage
    nodes and edges.
    """
    def __init__(self):
        self.graph = {}

    def add_node(self, node):
        if node not in self.graph:
            self.graph[node] = []

    def add_edge(self, source, destination, weight):
        self.add_node(source)
        self.add_node(destination)
        self.graph[source].append((destination, weight))

    def get_nodes(self):
        return list(self.graph.keys())

    def get_edges(self):
        edges = []
        for u in self.graph:
            for v, weight in self.graph[u]:
                edges.append((u, v, weight))
        return edges

    def bellman_ford(self, source):
        """
        Implements Bellman-Ford algorithm within the Graph class.

        Args:
            source: The starting node.

        Returns:
        A tuple containing:
        - distances:  See description in bellman_ford_basic.
        - predecessor: See description in bellman_ford_basic.
        """
        num_nodes = len(self.graph)
        distances = {node: float('inf') for node in self.graph}
        distances[source] = 0
        predecessor = {node: None for node in self.graph}
        edges = self.get_edges()

        for _ in range(num_nodes - 1):
            for u, v, weight in edges:
                if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessor[v] = u

        for u, v, weight in edges:
            if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                return None, None
        return distances, predecessor

# Approach 5:  More Pythonic Version
def bellman_ford_pythonic(graph, source):
    """
    A more concise and Pythonic implementation of the Bellman-Ford algorithm.

    Args:
        graph:  See description in bellman_ford_basic.
        source: The starting node.

    Returns:
        A tuple containing:
        - distances:  See description in bellman_ford_basic.
        - predecessor: See description in bellman_ford_basic.
    """
    distances = {node: float('inf') for node in graph}
    distances[source] = 0
    predecessors = {node: None for node in graph}

    for _ in range(len(graph) - 1):
        for u, neighbors in graph.items():
            for v, weight in neighbors:
                if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessors[v] = u

    for u, neighbors in graph.items():
        for v, weight in neighbors:
            if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                return None, None
    return distances, predecessors

if __name__ == "__main__":
    # Example graph (as used in the problem description)
    example_graph = {
        'A': [('B', -1), ('C', 4)],
        'B': [('C', 3), ('D', 2), ('E', 2)],
        'C': [],
        'D': [('B', 1), ('C', 5)],
        'E': [('D', -3)]
    }
    source_node = 'A'

    print("Bellman-Ford Algorithm Example")
    print("Graph:", example_graph)
    print("Source Node:", source_node)
    print("-" * 40)

    # Test each approach
    print("Approach 1: Basic Implementation")
    distances1, predecessors1 = bellman_ford_basic(example_graph, source_node)
    if distances1:
        print("Distances:", distances1)
        print("Predecessors:", predecessors1)
    else:
        print("Negative cycle detected")

    print("-" * 40)
    print("Approach 2: Early Termination Optimization")
    distances2, predecessors2 = bellman_ford_early_stop(example_graph, source_node)
    if distances2:
        print("Distances:", distances2)
        print("Predecessors:", predecessors2)
    else:
        print("Negative cycle detected")

    print("-" * 40)
    print("Approach 3: Using Named Tuples")
    distances3, predecessors3 = bellman_ford_namedtuple(example_graph, source_node)
    if distances3:
        print("Distances:", distances3)
        print("Predecessors:", predecessors3)
    else:
        print("Negative cycle detected")

    print("-" * 40)
    print("Approach 4: Using a Graph Class")
    graph_obj = Graph()
    for node in example_graph:
        graph_obj.add_node(node)
        for neighbor, weight in example_graph[node]:
            graph_obj.add_edge(node, neighbor, weight)
    distances4, predecessors4 = graph_obj.bellman_ford(source_node)
    if distances4:
        print("Distances:", distances4)
        print("Predecessors:", predecessors4)
    else:
        print("Negative cycle detected")

    print("-" * 40)
    print("Approach 5: More Pythonic Version")
    distances5, predecessors5 = bellman_ford_pythonic(example_graph, source_node)
    if distances5:
        print("Distances:", distances5)
        print("Predecessors:", predecessors5)
    else:
        print("Negative cycle detected")

    # Example with a negative cycle
    negative_cycle_graph = {
        'A': [('B', -1)],
        'B': [('C', -2)],
        'C': [('A', -3)]
    }
    print("\nExample with Negative Cycle:")
    distances_neg, predecessors_neg = bellman_ford_basic(negative_cycle_graph, 'A')
    if distances_neg is None:
        print("Negative cycle detected (as expected)")
    else:
        print("Distances:", distances_neg) # This will not be printed
        print("Predecessors:", predecessors_neg) # This will not be printed

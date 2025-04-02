import heapq

# 1. Basic Prim's Algorithm using Adjacency Matrix

def prims_matrix(graph):
    """
    Computes the Minimum Spanning Tree (MST) of a graph using Prim's algorithm.
    This implementation uses an adjacency matrix representation of the graph
    and a simple array to track visited nodes and edge weights.

    Args:
        graph: A square matrix representing the graph.  graph[i][j] is the
               weight of the edge between node i and node j.
               If graph[i][j] is 0, there is no edge.

    Returns:
        A list of tuples representing the edges of the MST. Each tuple
        (u, v, weight) indicates an edge between node u and node v with
        the given weight.  Returns an empty list if the graph is empty or invalid.
    """
    num_nodes = len(graph)
    if num_nodes == 0:
        return []  # Handle empty graph case

    # Initialize MST and visited set
    mst_edges = []
    visited = [False] * num_nodes
    min_weights = [float('inf')] * num_nodes  # Stores the minimum weight to connect each node to the MST
    parent = [None] * num_nodes  # Stores the parent node in the MST

    # Start from the first node (you can choose any starting node)
    start_node = 0
    min_weights[start_node] = 0
    visited[start_node] = True

    # Use a simple loop to find the minimum weight edge
    for _ in range(num_nodes - 1):
        min_edge_weight = float('inf')
        u = -1
        v = -1

        # Find the minimum weight edge connecting a visited node to an unvisited node
        for i in range(num_nodes):
            if visited[i]:
                for j in range(num_nodes):
                    if not visited[j] and graph[i][j] != 0 and graph[i][j] < min_edge_weight:
                        min_edge_weight = graph[i][j]
                        u = i
                        v = j

        if u != -1 and v != -1:
            mst_edges.append((u, v, min_edge_weight))
            visited[v] = True
            min_weights[v] = 0  # Mark the new node as visited
            parent[v] = u

    return mst_edges

# 2. Prim's Algorithm using Adjacency List and Priority Queue (Heapq)

def prims_list_heapq(adj_list):
    """
    Computes the Minimum Spanning Tree (MST) of a graph using Prim's algorithm.
    This implementation uses an adjacency list representation of the graph
    and a priority queue (heapq) to efficiently find the minimum weight edge.

    Args:
        adj_list: A list of lists representing the graph's adjacency list.
                  adj_list[i] is a list of tuples (neighbor, weight) where
                  neighbor is the neighboring node and weight is the
                  weight of the edge connecting node i to the neighbor.

    Returns:
        A list of tuples representing the edges of the MST. Each tuple
        (u, v, weight) indicates an edge between node u and node v with
        the given weight. Returns an empty list if the graph is empty or invalid.
    """
    num_nodes = len(adj_list)
    if num_nodes == 0:
        return []

    mst_edges = []
    visited = [False] * num_nodes
    priority_queue = [(0, 0, -1)]  # (weight, node, parent). Start at node 0 with weight 0 and no parent.
    # parent is initialized to -1.

    while priority_queue:
        weight, u, parent = heapq.heappop(priority_queue)

        if visited[u]:
            continue  # Skip if the node is already visited

        visited[u] = True

        if parent != -1:  # Exclude the starting node's dummy edge
            mst_edges.append((parent, u, weight))

        for neighbor, edge_weight in adj_list[u]:
            if not visited[neighbor]:
                heapq.heappush(priority_queue, (edge_weight, neighbor, u))

    return mst_edges

# 3. Optimized Prim's with Early Stopping
def prims_early_stop(graph):
    """
    Computes the MST, stopping early if a disconnected graph is detected.

    Args:
        graph: Adjacency matrix.

    Returns:
        MST edges or None if graph is disconnected.
    """
    num_nodes = len(graph)
    if num_nodes == 0:
        return []

    mst_edges = []
    visited = [False] * num_nodes
    min_weights = [float('inf')] * num_nodes
    parent = [None] * num_nodes

    start_node = 0
    min_weights[start_node] = 0
    visited[start_node] = True
    nodes_added = 0 # Keep track of the number of nodes added to the MST

    for _ in range(num_nodes - 1):
        min_edge_weight = float('inf')
        u = -1
        v = -1

        for i in range(num_nodes):
            if visited[i]:
                for j in range(num_nodes):
                    if not visited[j] and graph[i][j] != 0 and graph[i][j] < min_edge_weight:
                        min_edge_weight = graph[i][j]
                        u = i
                        v = j

        if u != -1 and v != -1:
            mst_edges.append((u, v, min_edge_weight))
            visited[v] = True
            min_weights[v] = 0
            parent[v] = u
            nodes_added += 1
        else:
            return None # Graph is disconnected

    if nodes_added != num_nodes -1:
        return None # Graph is disconnected

    return mst_edges

# 4. Prim's Algorithm for Sparse Graphs
def prims_sparse(adj_list):
    """
    Computes MST for sparse graphs using adjacency list and heapq.

    Args:
      adj_list: Adjacency list

    Returns:
      MST edges
    """
    num_nodes = len(adj_list)
    if num_nodes == 0:
        return []

    mst_edges = []
    visited = [False] * num_nodes
    pq = [(0, 0, -1)]

    while pq:
        weight, u, parent = heapq.heappop(pq)
        if visited[u]:
            continue
        visited[u] = True
        if parent != -1:
            mst_edges.append((parent, u, weight))
        for v, w in adj_list[u]:
            if not visited[v]:
                heapq.heappush(pq, (w, v, u))
    return mst_edges

# 5.  Prim's Algorithm with Path Reconstruction
def prims_with_path(graph):
    """
    Computes the MST and reconstructs the path from start to each node.

    Args:
        graph: Adjacency matrix.

    Returns:
        A tuple containing:
        - MST edges
        - A dictionary where keys are nodes and values are paths from the start node.
    """
    num_nodes = len(graph)
    if num_nodes == 0:
        return [], {}

    mst_edges = []
    visited = [False] * num_nodes
    min_weights = [float('inf')] * num_nodes
    parent = [None] * num_nodes
    start_node = 0
    min_weights[start_node] = 0
    visited[start_node] = True
    paths = {start_node: [start_node]}  # Store paths from start_node

    for _ in range(num_nodes - 1):
        min_edge_weight = float('inf')
        u = -1
        v = -1

        for i in range(num_nodes):
            if visited[i]:
                for j in range(num_nodes):
                    if not visited[j] and graph[i][j] != 0 and graph[i][j] < min_edge_weight:
                        min_edge_weight = graph[i][j]
                        u = i
                        v = j

        if u != -1 and v != -1:
            mst_edges.append((u, v, min_edge_weight))
            visited[v] = True
            min_weights[v] = 0
            parent[v] = u

            # Update path for the newly added node
            paths[v] = paths[u] + [v]

    return mst_edges, paths

# 6. Prim's Algorithm with Cost Calculation
def prims_with_cost(adj_matrix):
    """
    Computes the MST and calculates the total cost.

    Args:
        adj_matrix: Adjacency matrix.

    Returns:
        A tuple containing:
        - MST edges
        - Total cost of the MST
    """
    num_nodes = len(adj_matrix)
    if num_nodes == 0:
        return [], 0

    mst_edges = []
    visited = [False] * num_nodes
    min_weights = [float('inf')] * num_nodes
    parent = [None] * num_nodes
    total_cost = 0  # Initialize total cost
    start_node = 0
    min_weights[start_node] = 0
    visited[start_node] = True

    for _ in range(num_nodes - 1):
        min_edge_weight = float('inf')
        u = -1
        v = -1

        for i in range(num_nodes):
            if visited[i]:
                for j in range(num_nodes):
                    if not visited[j] and adj_matrix[i][j] != 0 and adj_matrix[i][j] < min_edge_weight:
                        min_edge_weight = adj_matrix[i][j]
                        u = i
                        v = j

        if u != -1 and v != -1:
            mst_edges.append((u, v, min_edge_weight))
            visited[v] = True
            min_weights[v] = 0
            parent[v] = u
            total_cost += min_edge_weight  # Accumulate the cost

    return mst_edges, total_cost

def main():
    """
    Main function to demonstrate the usage of Prim's algorithm with different graph representations.
    """
    # 1. Example graph represented as an adjacency matrix
    graph_matrix = [
        [0, 2, 0, 6, 0, 0],
        [2, 0, 3, 8, 5, 0],
        [0, 3, 0, 0, 7, 0],
        [6, 8, 0, 0, 9, 15],
        [0, 5, 7, 9, 0, 6],
        [0, 0, 0, 15, 6, 0]
    ]

    print("\n1. Prim's Algorithm with Adjacency Matrix:")
    mst_matrix = prims_matrix(graph_matrix)
    print("MST Edges (Matrix):", mst_matrix)
    # Expected output: [(0, 1, 2), (1, 2, 3), (0, 3, 6), (1, 4, 5), (4, 5, 6)]

    # 2. Example graph represented as an adjacency list
    graph_list = [
        [(1, 2), (3, 6)],  # Node 0
        [(0, 2), (2, 3), (3, 8), (4, 5)],  # Node 1
        [(1, 3), (4, 7)],  # Node 2
        [(0, 6), (1, 8), (4, 9), (5, 15)],  # Node 3
        [(1, 5), (2, 7), (3, 9), (5, 6)],  # Node 4
        [(3, 15), (4, 6)]  # Node 5
    ]

    print("\n2. Prim's Algorithm with Adjacency List and Priority Queue (Heapq):")
    mst_list_heapq = prims_list_heapq(graph_list)
    print("MST Edges (List + Heapq):", mst_list_heapq)
    # Expected Output: [(0, 1, 2), (1, 2, 3), (0, 3, 6), (1, 4, 5), (4, 5, 6)]

    # 3. Example of early stopping with a disconnected graph
    disconnected_graph = [
        [0, 1, 0, 0],
        [1, 0, 1, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0],  # Node 3 is disconnected
    ]
    print("\n3. Prim's Algorithm with Early Stopping (Disconnected Graph):")
    mst_early_stop = prims_early_stop(disconnected_graph)
    if mst_early_stop is None:
        print("Graph is disconnected, MST not found.")
    else:
        print("MST Edges (Early Stop):", mst_early_stop)

    # 4. Prim's Algorithm for Sparse Graphs
    sparse_graph = [
        [(1, 10), (3, 30)],  # Node 0
        [(0, 10), (2, 15), (4, 20)],  # Node 1
        [(1, 15), (4, 5)],  # Node 2
        [(0, 30), (4, 8)],  # Node 3
        [(1, 20), (2, 5), (3, 8)]  # Node 4
    ]
    print("\n4. Prim's Algorithm for Sparse Graph:")
    mst_sparse = prims_sparse(sparse_graph)
    print("MST Edges (Sparse):", mst_sparse)
    # Expected Output: [(0, 1, 10), (2, 4, 5), (3, 4, 8), (1, 2, 15)]

    # 5. Prim's Algorithm with Path Reconstruction
    graph_matrix_path = [
        [0, 2, 0, 6, 0, 0],
        [2, 0, 3, 8, 5, 0],
        [0, 3, 0, 0, 7, 0],
        [6, 8, 0, 0, 9, 15],
        [0, 5, 7, 9, 0, 6],
        [0, 0, 0, 15, 6, 0]
    ]
    print("\n5. Prim's Algorithm with Path Reconstruction:")
    mst_path, paths = prims_with_path(graph_matrix_path)
    print("MST Edges (Path):", mst_path)
    print("Paths from start node (0):", paths)
    # Expected Output:
    # MST Edges (Path): [(0, 1, 2), (1, 2, 3), (0, 3, 6), (1, 4, 5), (4, 5, 6)]
    # Paths from start node (0): {0: [0], 1: [0, 1], 2: [0, 1, 2], 3: [0, 3], 4: [0, 1, 4], 5: [0, 1, 4, 5]}

    # 6. Prim's Algorithm with Cost Calculation
    graph_matrix_cost = [
        [0, 2, 0, 6, 0, 0],
        [2, 0, 3, 8, 5, 0],
        [0, 3, 0, 0, 7, 0],
        [6, 8, 0, 0, 9, 15],
        [0, 5, 7, 9, 0, 6],
        [0, 0, 0, 15, 6, 0]
    ]
    print("\n6. Prim's Algorithm with Cost Calculation:")
    mst_cost, total_cost = prims_with_cost(graph_matrix_cost)
    print("MST Edges (Cost):", mst_cost)
    print("Total Cost:", total_cost)
    # Expected Output:
    # MST Edges (Cost): [(0, 1, 2), (1, 2, 3), (0, 3, 6), (1, 4, 5), (4, 5, 6)]
    # Total Cost: 22

if __name__ == "__main__":
    main()

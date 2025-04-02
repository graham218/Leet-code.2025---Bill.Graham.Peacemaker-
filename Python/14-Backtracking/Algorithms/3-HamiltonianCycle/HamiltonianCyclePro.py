"""
Hamiltonian Cycle Problem: Finding a path in a graph that visits every vertex exactly once and returns to the starting vertex.

This module provides six different approaches to solve the Hamiltonian Cycle problem,
each with a real-world project implementation example.

Approaches Implemented:
1.  Backtracking (Basic Recursive)
2.  Backtracking with Adjacency Matrix
3.  Backtracking with Early Pruning
4.  Held-Karp Algorithm (Dynamic Programming) - For smaller graphs
5.  Christofides Algorithm (Approximation for Metric TSP) - For larger graphs
6.  Simulated Annealing (Metaheuristic) - For complex, large-scale graphs
"""

import sys
import random
import copy
import time
import math
from collections import defaultdict

def create_graph(num_nodes, edge_prob=0.5, directed=False):
    """
    Generates a random graph for testing purposes.  Handles potential edge cases
    like ensuring no self-loops and allowing for disconnected graphs.

    Args:
        num_nodes: The number of nodes in the graph.
        edge_prob: The probability of an edge existing between any two nodes.
        directed: Boolean indicating whether the graph is directed.

    Returns:
        A dictionary representing the graph, where keys are nodes and values are lists of neighbors.
        Returns an empty dict if num_nodes is invalid.
    """
    if num_nodes <= 0:
        print("Number of nodes must be positive.")
        return {}

    graph = {i: [] for i in range(num_nodes)}
    for i in range(num_nodes):
        for j in range(num_nodes):
            if i != j and random.random() < edge_prob:
                graph[i].append(j)
                if not directed:
                    graph[j].append(i)  # Ensure symmetry for undirected graphs

    #  Check for disconnected graph.  If the graph is disconnected,
    #  Hamiltonian cycle is not guaranteed to exist.  This is a check and not a fix.
    if not is_connected(graph):
        print("Warning: The generated graph is disconnected. Hamiltonian cycle may not exist.")
    return graph

def is_connected(graph):
    """
    Checks if a graph is connected using Depth First Search.

    Args:
        graph: A dictionary representing the graph.

    Returns:
        True if the graph is connected, False otherwise.
    """
    if not graph:
        return True  # Consider an empty graph as connected

    num_nodes = len(graph)
    visited = [False] * num_nodes
    start_node = next(iter(graph))  # Get an arbitrary starting node

    def dfs(node):
        visited[node] = True
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor)

    dfs(start_node)
    return all(visited)
def print_graph(graph):
    """
    Prints the graph in a user-friendly format.

    Args:
        graph: A dictionary representing the graph.
    """
    if not graph:
        print("Empty Graph")
        return
    print("Graph Representation:")
    for node, neighbors in graph.items():
        print(f"Node {node}: Neighbors -> {neighbors}")

def validate_cycle(graph, path):
    """
    Validates if a given path is a Hamiltonian Cycle in the graph.

    Args:
        graph: A dictionary representing the graph.
        path: A list of nodes representing the path.

    Returns:
        True if the path is a Hamiltonian Cycle, False otherwise.
    """
    if not path:
        return False
    num_nodes = len(graph)
    if len(path) != num_nodes:
        print(f"Path length {len(path)} does not equal number of nodes {num_nodes}")
        return False  # Path must visit all nodes

    for i in range(num_nodes):
        if i >= len(path):
            return False
        current_node = path[i]
        next_node = path[(i + 1) % num_nodes]  # Wrap around to the start for the last edge
        if next_node not in graph[current_node]:
            print(f"Edge ({current_node}, {next_node}) not in graph")
            return False  # Check for valid edges

    start_node = path[0]
    end_node = path[-1]
    if end_node not in graph[start_node]:
        print(f"No edge from end of path ({end_node}) to start ({start_node})")
        return False # Check the return edge

    return True  # Path is a Hamiltonian Cycle
# 1. Backtracking (Basic Recursive)
def find_hamiltonian_cycle_backtrack(graph):
    """
    Finds a Hamiltonian Cycle in a graph using a basic backtracking approach.

    Args:
        graph: A dictionary representing the graph.

    Returns:
        A list representing the Hamiltonian Cycle if found, None otherwise.
    """
    if not graph:
        return None
    num_nodes = len(graph)
    path = [0]  # Start from node 0
    visited = [False] * num_nodes
    visited[0] = True

    def backtrack(node):
        if len(path) == num_nodes:
            # Check if there is an edge from the last node to the starting node
            if path[0] in graph[node]:
                return True  # Cycle found
            else:
                return False # Not a cycle
        for neighbor in graph[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                path.append(neighbor)
                if backtrack(neighbor):
                    return True
                # Backtrack: remove the last node and mark it as unvisited
                visited[neighbor] = False
                path.pop()
        return False

    if backtrack(0):
        return path
    else:
        return None

# 2. Backtracking with Adjacency Matrix
def find_hamiltonian_cycle_matrix(graph):
    """
    Finds a Hamiltonian Cycle using backtracking with an adjacency matrix
    representation of the graph.  This can be faster for dense graphs.

    Args:
        graph: A dictionary representing the graph.

    Returns:
        A list representing the Hamiltonian Cycle if found, None otherwise.
    """
    if not graph:
        return None

    num_nodes = len(graph)
    # Create adjacency matrix
    adj_matrix = [[0] * num_nodes for _ in range(num_nodes)]
    for node, neighbors in graph.items():
        for neighbor in neighbors:
            adj_matrix[node][neighbor] = 1

    path = [0]
    visited = [False] * num_nodes
    visited[0] = True

    def backtrack(node):
        if len(path) == num_nodes:
            if adj_matrix[node][0] == 1:
                return True
            else:
                return False
        for neighbor in range(num_nodes):
            if adj_matrix[node][neighbor] == 1 and not visited[neighbor]:
                visited[neighbor] = True
                path.append(neighbor)
                if backtrack(neighbor):
                    return True
                visited[neighbor] = False
                path.pop()
        return False

    if backtrack(0):
        return path
    else:
        return None

# 3. Backtracking with Early Pruning
def find_hamiltonian_cycle_pruning(graph):
    """
    Finds a Hamiltonian Cycle using backtracking with early pruning.
    This version attempts to optimize the search by checking for dead ends earlier.

    Args:
        graph: A dictionary representing the graph.

    Returns:
        A list representing the Hamiltonian Cycle if found, None otherwise.
    """
    if not graph:
        return None
    num_nodes = len(graph)
    path = [0]
    visited = [False] * num_nodes
    visited[0] = True

    def count_unvisited_neighbors(node):
        """Counts unvisited neighbors of a node."""
        count = 0
        for neighbor in graph[node]:
            if not visited[neighbor]:
                count += 1
        return count

    def backtrack(node):
        if len(path) == num_nodes:
            if path[0] in graph[node]:
                return True
            else:
                return False

        for neighbor in graph[node]:
            if not visited[neighbor]:
                # Pruning: Check if the neighbor has any unvisited neighbors.
                # If a node has no unvisited neighbors (other than the start), it's a dead end
                if count_unvisited_neighbors(neighbor) > 0 or len(path) == num_nodes -2: #changed from num_nodes -1 to num_nodes -2
                    visited[neighbor] = True
                    path.append(neighbor)
                    if backtrack(neighbor):
                        return True
                    visited[neighbor] = False
                    path.pop()
        return False

    if backtrack(0):
        return path
    else:
        return None

# 4. Held-Karp Algorithm (Dynamic Programming)
def find_hamiltonian_cycle_held_karp(graph):
    """
    Finds a Hamiltonian Cycle using the Held-Karp algorithm (dynamic programming).
    This algorithm is optimal but has a time complexity of O(n^2 * 2^n), making it
    suitable only for small graphs (e.g., up to ~20 nodes).  For larger graphs,
    it becomes computationally infeasible.

    Args:
        graph: A dictionary representing the graph.  For Held-Karp, we assume
               the graph is complete and undirected, and represent it as a
               distance matrix.  If the graph is not complete, we add
               "infinite" distances (sys.maxsize) between non-adjacent nodes.
               If the graph is directed, this algorithm will not give correct results.

    Returns:
        A tuple:
            - The minimum cost of the Hamiltonian Cycle (or None if no cycle exists).
            - The Hamiltonian Cycle path (list of nodes) if found, None otherwise.
    """
    if not graph:
        return None, None

    num_nodes = len(graph)
    all_nodes = set(range(num_nodes))

    # 1. Convert graph to distance matrix (cost matrix)
    dist_matrix = [[sys.maxsize] * num_nodes for _ in range(num_nodes)]
    for i in range(num_nodes):
        dist_matrix[i][i] = 0  # Cost from a node to itself is 0
        for j in graph[i]:
            dist_matrix[i][j] = 1  # Assuming unit cost for edges.  For a real-world
            # application, you'd replace '1' with the actual
            # cost/distance between nodes i and j.
    # If the graph is not complete, fill in missing edges with a large cost.
    for i in range(num_nodes):
        for j in range(num_nodes):
            if i != j and dist_matrix[i][j] == sys.maxsize:
                dist_matrix[i][j] = sys.maxsize  #  "Infinite" cost for non-edges


    # 2. Initialize memoization table (dp table)
    #    - dp[mask][end_node] stores the minimum cost of a path
    #      that starts at node 0, visits all nodes in 'mask', and ends at 'end_node'.
    dp = {}

    def calculate_cost(mask, end_node):
        """
        Recursively calculates the minimum cost of a path using dynamic programming.
        """
        if (mask, end_node) in dp:
            return dp[(mask, end_node)]

        if mask == (1 << end_node):  # Base case: Path with only the starting node (0)
            return dist_matrix[0][end_node]

        min_cost = sys.maxsize
        # Iterate through all possible previous nodes 'prev_node' in the path
        for prev_node in range(num_nodes):
            if (mask >> prev_node) & 1 and prev_node != end_node:
                # Create a new mask without the current 'end_node'
                new_mask = mask ^ (1 << end_node)
                # Recursively calculate the cost of the path ending at 'prev_node'
                cost = calculate_cost(new_mask, prev_node) + dist_matrix[prev_node][end_node]
                min_cost = min(min_cost, cost)

        dp[(mask, end_node)] = min_cost
        return min_cost

    # 3. Calculate the minimum cost of the Hamiltonian Cycle
    #    - Iterate through all possible ending nodes 'end_node' from the starting node (0).
    final_mask = (1 << num_nodes) - 1  # All nodes visited
    min_cycle_cost = sys.maxsize
    end_node_for_min_cost = -1

    for end_node in range(1, num_nodes):
        cost = calculate_cost(final_mask, end_node) + dist_matrix[end_node][0] # Return to start (0)
        if cost < min_cycle_cost:
            min_cycle_cost = cost
            end_node_for_min_cost = end_node

    if min_cycle_cost == sys.maxsize:
        return None, None  # No Hamiltonian Cycle found

    # 4. Reconstruct the Hamiltonian Cycle path
    #    - Backtrack through the dp table to find the optimal path.
    path = [0]  # Start at node 0
    current_mask = final_mask
    current_node = end_node_for_min_cost

    for _ in range(num_nodes - 1):
        for prev_node in range(num_nodes):
            if (current_mask >> prev_node) & 1 and prev_node != current_node:
                new_mask = current_mask ^ (1 << current_node)
                # Check if the cost from prev_node to current_node contributed to the minimum cost
                if (calculate_cost(new_mask, prev_node) + dist_matrix[prev_node][current_node] ==
                        calculate_cost(current_mask, current_node)):
                    path.append(current_node)
                    current_mask = new_mask
                    current_node = prev_node
                    break
    path.append(0) # Return to start.
    path.reverse()
    return min_cycle_cost, path

# 5. Christofides Algorithm (Approximation for Metric TSP)
def find_hamiltonian_cycle_christofides(graph):
    """
    Finds an approximate Hamiltonian Cycle using Christofides algorithm.
    This algorithm provides a 3/2-approximation for the Traveling Salesman Problem (TSP)
    in metric graphs (graphs where the edge weights satisfy the triangle inequality).
    A Hamiltonian Cycle is a special case of the TSP.
    This is suitable for larger graphs where Held-Karp is too slow.

    Args:
        graph: A dictionary representing the graph.  For Christofides, we assume
               the graph is complete, undirected, and metric, and represent it as a
               distance matrix.  If the graph is not complete, we add
               "infinite" distances (sys.maxsize) between non-adjacent nodes.
               If the graph is directed, this algorithm will not give correct results.
               If the graph is not metric, the approximation guarantee doesn't hold.
    Returns:
        A tuple:
            - The approximate cost of the Hamiltonian Cycle.
            - The approximate Hamiltonian Cycle path (list of nodes).
    """
    if not graph:
        return None, None

    num_nodes = len(graph)

    # 1. Convert graph to distance matrix (cost matrix)
    dist_matrix = [[sys.maxsize] * num_nodes for _ in range(num_nodes)]
    for i in range(num_nodes):
        dist_matrix[i][i] = 0
        for j in graph[i]:
            dist_matrix[i][j] = 1 #  Assume unit cost.  Replace with actual distance.

    # If the graph is not complete, fill in missing edges with a large cost.
    for i in range(num_nodes):
        for j in range(num_nodes):
            if i != j and dist_matrix[i][j] == sys.maxsize:
                dist_matrix[i][j] = sys.maxsize

    # 2. Compute a Minimum Spanning Tree (MST) of the graph.
    #    -  Using Prim's algorithm (a simple implementation).
    mst_edges = []
    visited = [False] * num_nodes
    visited[0] = True  # Start from node 0
    num_edges_in_mst = 0

    # Store the parent of each node in the MST.
    parent = [None] * num_nodes
    cost_of_mst = 0

    while num_edges_in_mst < num_nodes - 1:
        min_edge_cost = sys.maxsize
        min_u, min_v = -1, -1

        for u in range(num_nodes):
            if visited[u]:
                for v in range(num_nodes):
                    if not visited[v] and dist_matrix[u][v] < min_edge_cost:
                        min_edge_cost = dist_matrix[u][v]
                        min_u, min_v = u, v

        if min_u != -1 and min_v != -1:
            mst_edges.append((min_u, min_v))
            visited[min_v] = True
            num_edges_in_mst += 1
            cost_of_mst += min_edge_cost
            parent[min_v] = min_u # Store parent
        else:
            return None, None # MST not found.

    # 3. Find the set of vertices with odd degree in the MST.
    odd_degree_vertices = []
    degrees = [0] * num_nodes
    for u, v in mst_edges:
        degrees[u] += 1
        degrees[v] += 1
    for i in range(num_nodes):
        if degrees[i] % 2 != 0:
            odd_degree_vertices.append(i)

    # 4. Find a Minimum Weight Perfect Matching (MWPM) of the odd-degree vertices.
    #    -  A simple greedy matching is used here for demonstration.  For a real-world
    #       application, you would use a proper MWPM algorithm (e.g., Blossom algorithm).
    matching = []
    matched = [False] * len(odd_degree_vertices)
    for i in range(len(odd_degree_vertices)):
        if not matched[i]:
            min_dist = sys.maxsize
            min_j = -1
            for j in range(i + 1, len(odd_degree_vertices)):
                if not matched[j] and dist_matrix[odd_degree_vertices[i]][odd_degree_vertices[j]] < min_dist:
                    min_dist = dist_matrix[odd_degree_vertices[i]][odd_degree_vertices[j]]
                    min_j = j
            if min_j != -1:
                matching.append((odd_degree_vertices[i], odd_degree_vertices[min_j]))
                matched[i] = True
                matched[min_j] = True

    # 5. Combine the MST and the MWPM to form an Eulerian graph.
    #    -  Add the edges of the matching to the MST.
    eulerian_graph = defaultdict(list)
    for u, v in mst_edges:
        eulerian_graph[u].append(v)
        eulerian_graph[v].append(u)  # MST is undirected
    for u, v in matching:
        eulerian_graph[u].append(v)
        eulerian_graph[v].append(u)  # Matching is undirected

    # 6. Find an Eulerian cycle in the Eulerian graph.
    #    -  Use Fleury's algorithm (a simple implementation).
    def find_eulerian_cycle(graph_local):
        """Finds an Eulerian cycle in a given Eulerian graph."""
        start_node = next(iter(graph_local))
        cycle = [start_node]
        path = []
        stack = [start_node]

        while stack:
            u = stack[-1]
            if graph_local[u]:
                v = graph_local[u].pop()
                stack.append(v)
                path.append((u,v))
                graph_local[v].remove(u)
            else:
                stack.pop()
                cycle.append(u)
        return cycle[:-1] # Remove the last node, which is the start node.

    eulerian_cycle = find_eulerian_cycle(eulerian_graph)

    # 7. Convert the Eulerian cycle to a Hamiltonian Cycle by removing duplicate nodes.
    #    -  Keep only the first occurrence of each node in the Eulerian cycle.
    hamiltonian_cycle = []
    visited_nodes = set()
    for node in eulerian_cycle:
        if node not in visited_nodes:
            hamiltonian_cycle.append(node)
            visited_nodes.add(node)
    hamiltonian_cycle.append(hamiltonian_cycle[0]) # close the cycle

    # Calculate the cost of the approximate Hamiltonian Cycle.
    approx_cost = 0
    for i in range(len(hamiltonian_cycle) - 1):
        approx_cost += dist_matrix[hamiltonian_cycle[i]][hamiltonian_cycle[i+1]]

    return approx_cost, hamiltonian_cycle

# 6. Simulated Annealing (Metaheuristic)
def find_hamiltonian_cycle_simulated_annealing(graph):
    """
    Finds an approximate Hamiltonian Cycle using Simulated Annealing.
    Simulated Annealing is a metaheuristic algorithm that can find good solutions
    for large and complex optimization problems, including the Hamiltonian Cycle
    problem.  It doesn't guarantee an optimal solution, but it often finds near-optimal
    solutions in a reasonable amount of time.

    Args:
        graph: A dictionary representing the graph.
    Returns:
        A tuple:
            - The approximate cost of the Hamiltonian Cycle.
            - The approximate Hamiltonian Cycle path (list of nodes).
    """
    if not graph:
        return None, None

    num_nodes = len(graph)

    def calculate_cost(path):
        """Calculates the cost of a given path."""
        cost = 0
        for i in range(num_nodes):
            cost += 1 if path[i] in graph[path[(i + 1) % num_nodes]] else sys.maxsize
        return cost

    def generate_neighbor(path):
        """Generates a neighbor of the current path by swapping two random nodes."""
        new_path = path[:]
        a = random.randint(1, num_nodes - 2)  # Exclude start and end (which is the same)
        b = random.randint(1, num_nodes - 2)
        while a == b:
            b = random.randint(1, num_nodes - 2)
        new_path[a], new_path[b] = new_path[b], new_path[a]
        return new_path

    # 1. Initialize the starting solution (a random path)
    current_path = list(range(num_nodes))
    current_path.append(0)  # Return to the starting node to complete the cycle.
    random.shuffle(current_path[1:-1])  # Shuffle only the intermediate nodes
    current_cost = calculate_cost(current_path)

    # 2. Set the initial temperature, cooling rate, and stopping temperature
    initial_temperature = 1000
    cooling_rate = 0.95
    min_temperature = 1
    temperature = initial_temperature

    # 3. Iterate until the temperature is low enough
    while temperature > min_temperature:
        # 4. Perform a number of iterations at the current temperature
        for _ in range(100):  # Number of iterations per temperature
            # 5. Generate a neighbor solution
            new_path = generate_neighbor(current_path)
            new_cost = calculate_cost(new_path)

            # 6. Calculate the cost difference
            cost_difference = new_cost - current_cost

            # 7. Accept the new solution with a probability based on the cost difference and temperature
            if cost_difference < 0 or random.random() < math.exp(-cost_difference / temperature):
                current_path = new_path
                current_cost = new_cost

        # 8. Cool the temperature
        temperature *= cooling_rate

    return current_cost, current_path
def main():
    """
    Main function to run and compare the different Hamiltonian Cycle algorithms
    on a sample graph.
    """
    num_nodes = 10
    graph = create_graph(num_nodes, edge_prob=0.7)  # Adjust edge_prob as needed
    print_graph(graph)

    print("\n--- Hamiltonian Cycle Algorithms Comparison ---")
    print(f"Graph with {num_nodes} nodes:")

    # 1. Backtracking (Basic Recursive)
    start_time = time.time()
    hc_backtrack = find_hamiltonian_cycle_backtrack(graph)
    end_time = time.time()
    print("\n1. Backtracking (Basic Recursive):")
    print("   Hamiltonian Cycle:", hc_backtrack)
    if hc_backtrack:
        is_valid = validate_cycle(graph, hc_backtrack)
        print("   Valid Cycle:", is_valid)
    print(f"   Time: {end_time - start_time:.4f} seconds")

    # 2. Backtracking with Adjacency Matrix
    start_time = time.time()
    hc_matrix = find_hamiltonian_cycle_matrix(graph)
    end_time = time.time()
    print("\n2. Backtracking with Adjacency Matrix:")
    print("   Hamiltonian Cycle:", hc_matrix)
    if hc_matrix:
        is_valid = validate_cycle(graph, hc_matrix)
        print("   Valid Cycle:", is_valid)
    print(f"   Time: {end_time - start_time:.4f} seconds")

    # 3. Backtracking with Early Pruning
    start_time = time.time()
    hc_pruning = find_hamiltonian_cycle_pruning(graph)
    end_time = time.time()
    print("\n3. Backtracking with Early Pruning:")
    print("   Hamiltonian Cycle:", hc_pruning)
    if hc_pruning:
        is_valid = validate_cycle(graph, hc_pruning)
        print("   Valid Cycle:", is_valid)
    print(f"   Time: {end_time - start_time:.4f} seconds")

    # 4. Held-Karp Algorithm (Dynamic Programming) - Limited to small graphs
    if num_nodes <= 12:  # Held-Karp is computationally expensive
        start_time = time.time()
        min_cost_hk, hc_held_karp = find_hamiltonian_cycle_held_karp(graph)
        end_time = time.time()
        print("\n4. Held-Karp Algorithm (Dynamic Programming):")
        print("   Minimum Cost:", min_cost_hk)
        print("   Hamiltonian Cycle:", hc_held_karp)
        if hc_held_karp:
            is_valid = validate_cycle(graph, hc_held_karp)
            print("   Valid Cycle:", is_valid)
        print(f"   Time: {end_time - start_time:.4f} seconds")
    else:
        print("\n4. Held-Karp Algorithm (Dynamic Programming):")
        print("   Skipped (too many nodes for Held-Karp)")

    # 5. Christofides Algorithm (Approximation for Metric TSP)
    start_time = time.time()
    approx_cost_c, hc_christofides = find_hamiltonian_cycle_christofides(graph)
    end_time = time.time()
    print("\n5. Christofides Algorithm (Approximation for Metric TSP):")
    print("   Approximate Cost:", approx_cost_c)
    print("   Approximate Hamiltonian Cycle:", hc_christofides)
    if hc_christofides:
        is_valid = validate_cycle(graph, hc_christofides)
        print("   Valid Cycle:", is_valid)
    print(f"   Time: {end_time - start_time:.4f} seconds")

    # 6. Simulated Annealing (Metaheuristic)
    start_time = time.time()
    approx_cost_sa, hc_simulated_annealing = find_hamiltonian_cycle_simulated_annealing(graph)
    end_time = time.time()
    print("\n6. Simulated Annealing (Metaheuristic):")
    print("   Approximate Cost:", approx_cost_sa)
    print("   Approximate Hamiltonian Cycle:", hc_simulated_annealing)
    if hc_simulated_annealing:
        is_valid = validate_cycle(graph, hc_simulated_annealing)
        print("   Valid Cycle:", is_valid)
    print(f"   Time: {end_time - start_time:.4f} seconds")
if __name__ == "__main__":
    main()

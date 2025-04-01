import math

# 1. Network Routing (Cisco Routers)
def network_routing_bellman_ford(network_topology, source_router):
    """
    Calculates the shortest path from a source router to all other routers in a network
    using the Bellman-Ford algorithm.  This is a fundamental concept in how
    routing protocols like RIP (Routing Information Protocol) operate (though modern
    routing uses more sophisticated algorithms like OSPF).

    Args:
        network_topology: A dictionary representing the network topology.
            - Keys: Router names (e.g., 'A', 'B', 'C')
            - Values: A dictionary of directly connected routers and the cost (or distance)
              to reach them.  For example:
              {
                  'A': {'B': 5, 'C': 10},
                  'B': {'C': 3, 'D': 2},
                  'C': {'D': 1},
                  'D': {}
              }
        source_router: The starting router for calculating shortest paths.

    Returns:
        A tuple containing two dictionaries:
        - distances:  Shortest distances from the source router to all other routers.
          (Keys: Router names, Values: Distances.  Infinite distance is represented by math.inf)
        - predecessors: A dictionary to reconstruct the shortest paths.
          (Keys: Router names, Values: The previous router in the shortest path from the source.
           None for the source router and for unreachable nodes.)
        - Returns None, None if a negative cycle is detected.

    Example:
    network_topology = {
        'A': {'B': -1, 'C': 4},
        'B': {'C': 3, 'D': 2, 'E': 2},
        'C': {},
        'D': {'B': 1, 'C': 5},
        'E': {'D': -3}
    }
    source_router = 'A'
    distances, predecessors = network_routing_bellman_ford(network_topology, source_router)
    print(distances)
    print(predecessors)

    # To get the path from A to D:
    if distances and predecessors: # Check for None returns
        path = []
        current = 'D'
        while current:
            path.append(current)
            current = predecessors[current]
        path.reverse()
        print(f"Path from A to D: {path}")
    """
    num_routers = len(network_topology)
    distances = {router: math.inf for router in network_topology}
    distances[source_router] = 0
    predecessors = {router: None for router in network_topology}

    # Relax edges repeatedly
    for _ in range(num_routers - 1):
        for u, neighbors in network_topology.items():
            for v, weight in neighbors.items():
                if distances[u] != math.inf and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessors[v] = u

    # Check for negative cycles
    for u, neighbors in network_topology.items():
        for v, weight in neighbors.items():
            if distances[u] != math.inf and distances[u] + weight < distances[v]:
                return None, None  # Negative cycle detected

    return distances, predecessors



# 2. Currency Exchange Rate Arbitrage Detection
def detect_currency_arbitrage(exchange_rates):
    """
    Detects arbitrage opportunities in currency exchange rates using the Bellman-Ford algorithm.
    Arbitrage exists if, by starting with a certain amount of currency,
    it's possible to make a profit by going through a series of currency exchanges
    and ending up with more of the initial currency.

    Args:
        exchange_rates: A dictionary representing the exchange rates between currencies.
            - Keys: Currency codes (e.g., 'USD', 'EUR', 'GBP')
            - Values: A dictionary of exchange rates to other currencies.
              For example:
              {
                  'USD': {'EUR': 0.85, 'GBP': 0.75},  # 1 USD buys 0.85 EUR or 0.75 GBP
                  'EUR': {'USD': 1.18, 'GBP': 0.88},
                  'GBP': {'USD': 1.33, 'EUR': 1.14}
              }

    Returns:
        True if an arbitrage opportunity exists, False otherwise.

    Example:
    exchange_rates = {
        'USD': {'EUR': 0.85, 'GBP': 0.75},
        'EUR': {'USD': 1.18, 'GBP': 0.88},
        'GBP': {'USD': 1.33, 'EUR': 1.14}
    }
    if detect_currency_arbitrage(exchange_rates):
        print("Arbitrage opportunity exists!")
    else:
        print("No arbitrage opportunity.")
    """
    num_currencies = len(exchange_rates)
    # Use log of exchange rates because  a->b->c->a  > 1  becomes
    # log(a->b) + log(b->c) + log(c->a) > 0, and we want to find a *negative* cycle.
    log_rates = {
        currency: {
            to_currency: -math.log(rate) for to_currency, rate in rates.items()
        }
        for currency, rates in exchange_rates.items()
    }

    # Initialize distances (using log rates)
    distances = {currency: math.inf for currency in exchange_rates}
    start_currency = list(exchange_rates.keys())[0]  # Pick an arbitrary starting currency
    distances[start_currency] = 0

    # Relax edges
    for _ in range(num_currencies - 1):
        for u, rates in log_rates.items():
            for v, weight in rates.items():
                if distances[u] != math.inf and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight

    # Check for negative cycles (arbitrage)
    for u, rates in log_rates.items():
        for v, weight in rates.items():
            if distances[u] != math.inf and distances[u] + weight < distances[v]:
                return True  # Arbitrage opportunity found
    return False



# 3. Project Scheduling with Negative Dependencies
def project_scheduling_bellman_ford(tasks, dependencies):
    """
    Determines the earliest start time for each task in a project, considering dependencies
    and potential negative dependencies (which could represent time savings or overlaps,
    though this is less common in standard project scheduling and more of a theoretical
    extension).  This is similar to Critical Path Method (CPM) but handles negative weights.

    Args:
        tasks: A list of task names (e.g., ['A', 'B', 'C', 'D']).
        dependencies: A list of tuples, where each tuple represents a dependency:
            (start_task, end_task, time_until_start_of_end_task).
            For example:
            [
                ('A', 'B', 5),  # Task B can start 5 units of time after the start of A
                ('A', 'C', 3),
                ('B', 'D', 2),
                ('C', 'D', 1),
                ('E', 'A', -2) # Example of a negative dependency: A starts 2 units *before* E.
            ]
            A negative weight indicates that the 'end_task' can start *before* the 'start_task'
            by the given amount.

    Returns:
        A tuple containing two dictionaries:
        - start_times:  Earliest start times for each task (Keys: Task names, Values: Start times).
           Returns None if a negative cycle is detected.
        - predecessors: A dictionary to reconstruct the path (task dependencies).
          (Keys: Task names, Values: The previous task in the dependency chain.)

    Example:
    tasks = ['A', 'B', 'C', 'D', 'E']
    dependencies = [
        ('A', 'B', 5),
        ('A', 'C', 3),
        ('B', 'D', 2),
        ('C', 'D', 1),
        ('E', 'A', -2)
    ]
    start_times, predecessors = project_scheduling_bellman_ford(tasks, dependencies)
    print(start_times)
    print(predecessors)
    """
    num_tasks = len(tasks)
    start_times = {task: math.inf for task in tasks}
    start_times[tasks[0]] = 0  # Assume the first task in the list can start at time 0
    predecessors = {task: None for task in tasks}

    # Relax edges
    for _ in range(num_tasks - 1):
        for u, v, weight in dependencies:
            if start_times[u] != math.inf and start_times[u] + weight < start_times[v]:
                start_times[v] = start_times[u] + weight
                predecessors[v] = u

    # Check for negative cycles
    for u, v, weight in dependencies:
        if start_times[u] != math.inf and start_times[u] + weight < start_times[v]:
            return None, None # Negative cycle

    return start_times, predecessors



# 4.  Distance Vector Routing Protocol (Simplified)
def distance_vector_routing(network):
    """
    Simulates a simplified version of the Distance Vector Routing protocol,
    which uses a principle similar to Bellman-Ford.  Each node maintains a table
    of distances to all other nodes, and iteratively updates this table based
    on information from its neighbors.  This example demonstrates the core idea
    of distributed shortest path computation.

    Args:
        network: A dictionary representing the network topology.
            - Keys: Node names (e.g., 'A', 'B', 'C')
            - Values: A dictionary of directly connected nodes and the cost to reach them.
              Example:
              {
                  'A': {'B': 2, 'C': 5},
                  'B': {'A': 2, 'C': 1, 'D': 3},
                  'C': {'A': 5, 'B': 1, 'D': 1},
                  'D': {'B': 3, 'C': 1}
              }

    Returns:
        A dictionary representing the final routing tables for each node.
        - Keys: Node names
        - Values: A dictionary of shortest distances to all other nodes.
          For example:
          {
              'A': {'A': 0, 'B': 2, 'C': 3, 'D': 4},
              'B': {'A': 2, 'B': 0, 'C': 1, 'D': 2},
              'C': {'A': 3, 'B': 1, 'C': 0, 'D': 1},
              'D': {'A': 4, 'B': 2, 'C': 1, 'D': 0}
          }
    """
    nodes = list(network.keys())
    num_nodes = len(nodes)

    # Initialize distance tables
    distances = {node: {other_node: math.inf for other_node in nodes} for node in nodes}
    for node in nodes:
        distances[node][node] = 0  # Distance to itself is 0
        for neighbor, cost in network[node].items():
            distances[node][neighbor] = cost

    # Iteratively update distances (similar to Bellman-Ford relaxation)
    for _ in range(num_nodes - 1):
        for source_node in nodes:
            for neighbor_node, cost_to_neighbor in network[source_node].items():
                for dest_node in nodes:
                    #  Important:  The core Distance Vector update rule:
                    #  "My distance to destination is the minimum of my current distance,
                    #   and the distance to my neighbor plus my neighbor's distance to that destination."
                    if distances[source_node][neighbor_node] + distances[neighbor_node][dest_node] < distances[source_node][dest_node]:
                        distances[source_node][dest_node] = distances[source_node][neighbor_node] + distances[neighbor_node][dest_node]
    return distances



# 5.  Finding the Minimum Cost Path in a Graph with Constraints
def constrained_shortest_path(graph, source, destination, constraints):
    """
    Finds the shortest path between two nodes in a graph, subject to constraints.
    While not a direct application of Bellman-Ford in its purest form, this demonstrates
    how the core concept of iterative relaxation can be adapted to solve more complex
    pathfinding problems.  In this case, we're adding a constraint.

    Args:
        graph: A dictionary representing the graph.
            - Keys: Node names
            - Values: A dictionary of neighbor nodes and edge costs.
        source: The starting node.
        destination: The target node.
        constraints: A dictionary of constraints.  For simplicity, let's assume
                     a constraint on the maximum number of hops (edges) allowed
                     in the path.  More complex constraints could be added.
                     Example: {'max_hops': 3}  means the path can have at most 3 edges.

    Returns:
        A tuple containing:
        - The shortest distance that satisfies the constraints (or math.inf if no such path exists).
        - A list representing the shortest path (or an empty list if no path exists).

    Example:
    graph = {
        'A': {'B': 2, 'C': 5},
        'B': {'C': 1, 'D': 3},
        'C': {'D': 1},
        'D': {}
    }
    source = 'A'
    destination = 'D'
    constraints = {'max_hops': 3}
    distance, path = constrained_shortest_path(graph, source, destination, constraints)
    print(f"Shortest distance: {distance}")
    print(f"Shortest path: {path}")

    constraints = {'max_hops': 2}
    distance, path = constrained_shortest_path(graph, source, destination, constraints)
    print(f"Shortest distance: {distance}")
    print(f"Shortest path: {path}")
    """
    num_nodes = len(graph)
    distances = {node: math.inf for node in graph}
    distances[source] = 0
    predecessors = {node: None for node in graph}
    max_hops = constraints.get('max_hops', math.inf)  # Default to infinite hops if not specified

    # Relax edges, considering the hop constraint
    for _ in range(min(num_nodes - 1, max_hops)): # Important: Loop at most max_hops times.
        for u, neighbors in graph.items():
            for v, weight in neighbors.items():
                if distances[u] != math.inf and distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessors[v] = u

    # Check for negative cycles (though with hop constraints, this is less typical,
    #  as the number of iterations is limited)
    for u, neighbors in graph.items():
        for v, weight in neighbors.items():
            if distances[u] != math.inf and distances[u] + weight < distances[v]:
                return math.inf, []  # Return infinity and empty path if negative cycle

    # Reconstruct the path (if a path exists)
    if distances[destination] == math.inf:
        return math.inf, []  # No path found

    path = []
    current = destination
    while current:
        path.append(current)
        current = predecessors[current]
    path.reverse()
    return distances[destination], path



# 6.  Verification of Shortest Path Algorithms
def verify_shortest_path(graph, source, distances, predecessors):
    """
    Verifies the correctness of a computed shortest-path solution (distances and predecessors)
    for a given graph, source node.  This is useful for testing the implementation
    of a shortest-path algorithm (like Bellman-Ford) or for checking the output
    of a routing protocol.  It checks two key properties:
    1.  For each node v, the distance from the source to v is not greater than the
        distance to any neighbor u plus the weight of the edge (u, v).  This checks the
        relaxation property.
    2.  For each node v in the path from source to destination, the predecessor
        relationship is consistent with the computed distances.

    Args:
        graph: A dictionary representing the graph.
            - Keys: Node names
            - Values: A dictionary of neighbor nodes and edge costs.
        source: The source node for the shortest-path computation.
        distances: A dictionary of computed shortest distances from the source.
            - Keys: Node names, Values: Distances.
        predecessors: A dictionary of predecessors in the computed shortest paths.
            - Keys: Node names, Values: Predecessor nodes.

    Returns:
        True if the computed shortest paths are valid, False otherwise.

    Example:
    graph = {
        'A': {'B': 2, 'C': 5},
        'B': {'C': 1, 'D': 3},
        'C': {'D': 1},
        'D': {}
    }
    source = 'A'
    # Example of correct output from a shortest-path algorithm:
    correct_distances = {'A': 0, 'B': 2, 'C': 3, 'D': 4}
    correct_predecessors = {'A': None, 'B': 'A', 'C': 'B', 'D': 'C'}
    print(f"Verification (correct): {verify_shortest_path(graph, source, correct_distances, correct_predecessors)}")

    # Example of incorrect output:
    incorrect_distances = {'A': 0, 'B': 2, 'C': 4, 'D': 4} # C's distance is wrong
    incorrect_predecessors = {'A': None, 'B': 'A', 'C': 'B', 'D': 'C'}
    print(f"Verification (incorrect): {verify_shortest_path(graph, source, incorrect_distances, incorrect_predecessors)}")
    """
    for node in graph:
        # Check the relaxation property for all edges
        for neighbor, weight in graph[node].items():
            if distances[node] != math.inf and distances[node] + weight < distances[neighbor]:
                print(f"Relaxation property violated for edge ({node}, {neighbor})")
                return False

    # Check path consistency using predecessors
    for node in graph:
        if node == source:
            if predecessors[node] is not None:
                print(f"Predecessor of source node {node} should be None")
                return False
        else:
            if predecessors[node] is None and distances[node] != math.inf:
                print(f"Node {node} is unreachable, but distance is not infinity")
                return False
            if predecessors[node] is not None:
                predecessor_distance = distances[predecessors[node]] if predecessors[node] else 0
                edge_weight = 0
                # Find the edge weight between predecessor and current node
                if predecessors[node] in graph:
                    if node in graph[predecessors[node]]:
                        edge_weight = graph[predecessors[node]][node]
                    else:
                        # handle the case where edge does not exist.
                        edge_weight = math.inf
                else:
                    edge_weight = math.inf

                if predecessor_distance + edge_weight != distances[node]:
                    print(f"Path consistency violated for node {node}. Expected distance from {predecessors[node]} + edge weight ({edge_weight}) = {distances[node]}")
                    return False
    return True

# Example Usage (Add this to the end of your code)
if __name__ == "__main__":
    # 1. Network Routing Example
    network_topology = {
        'A': {'B': 2, 'C': 5},
        'B': {'C': 1, 'D': 3},
        'C': {'D': 1},
        'D': {}
    }
    source_router = 'A'
    distances, predecessors = network_routing_bellman_ford(network_topology, source_router)
    print("\nNetwork Routing Example:")
    print("Distances:", distances)
    print("Predecessors:", predecessors)

    # 2. Currency Exchange Arbitrage Detection Example
    exchange_rates = {
        'USD': {'EUR': 0.85, 'GBP': 0.75},
        'EUR': {'USD': 1.18, 'GBP': 0.88},
        'GBP': {'USD': 1.33, 'EUR': 1.14}
    }
    print("\nCurrency Exchange Arbitrage Example:")
    if detect_currency_arbitrage(exchange_rates):
        print("Arbitrage opportunity exists!")
    else:
        print("No arbitrage opportunity.")

    # 3. Project Scheduling Example
    tasks = ['A', 'B', 'C', 'D', 'E']
    dependencies = [
        ('A', 'B', 5),
        ('A', 'C', 3),
        ('B', 'D', 2),
        ('C', 'D', 1),
        ('E', 'A', -2)
    ]
    start_times, predecessors = project_scheduling_bellman_ford(tasks, dependencies)
    print("\nProject Scheduling Example:")
    print("Start Times:", start_times)
    print("Predecessors:", predecessors)

    # 4. Distance Vector Routing Example
    network = {
        'A': {'B': 2, 'C': 5},
        'B': {'A': 2, 'C': 1, 'D': 3},
        'C': {'A': 5, 'B': 1, 'D': 1},
        'D': {'B': 3, 'C': 1}
    }
    routing_tables = distance_vector_routing(network)
    print("\nDistance Vector Routing Example:")
    print("Routing Tables:", routing_tables)

    # 5. Constrained Shortest Path Example
    graph = {
        'A': {'B': 2, 'C': 5},
        'B': {'C': 1, 'D': 3},
        'C': {'D': 1},
        'D': {}
    }
    source = 'A'
    destination = 'D'
    constraints = {'max_hops': 3}
    distance, path = constrained_shortest_path(graph, source, destination, constraints)
    print(f"\nConstrained Shortest Path Example (max_hops=3):")
    print(f"Shortest distance: {distance}")
    print(f"Shortest path: {path}")

    constraints = {'max_hops': 2}
    distance, path = constrained_shortest_path(graph, source, destination, constraints)
    print(f"\nConstrained Shortest Path Example (max_hops=2):")
    print(f"Shortest distance: {distance}")
    print(f"Shortest path: {path}")

    # 6. Verification of Shortest Path Algorithms
    graph = {
        'A': {'B': 2, 'C': 5},
        'B': {'C': 1, 'D': 3},
        'C': {'D': 1},
        'D': {}
    }
    source = 'A'
    # Example of correct output from a shortest-path algorithm:
    correct_distances = {'A': 0, 'B': 2, 'C': 3, 'D': 4}
    correct_predecessors = {'A': None, 'B': 'A', 'C': 'B', 'D': 'C'}
    print(f"\nVerification of Shortest Path Algorithm (Correct): {verify_shortest_path(graph, source, correct_distances, correct_predecessors)}")

    # Example of incorrect output:
    incorrect_distances = {'A': 0, 'B': 2, 'C': 4, 'D': 4} # C's distance is wrong
    incorrect_predecessors = {'A': None, 'B': 'A', 'C': 'B', 'D': 'C'}
    print(f"Verification of Shortest Path Algorithm (Incorrect): {verify_shortest_path(graph, source, incorrect_distances, incorrect_predecessors)}")

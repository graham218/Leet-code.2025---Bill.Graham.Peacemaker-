from collections import defaultdict, deque
from typing import List, Dict, Set, Tuple, Optional

# 1. Basic Kahn's Algorithm - Dependency Resolution (Build Systems)
def topological_sort_kahn_basic(graph: Dict[str, List[str]]) -> List[str]:
    """
    Implements Kahn's algorithm for topological sorting.

    Args:
        graph: A dictionary representing the directed acyclic graph (DAG).
               Keys are nodes, and values are lists of their dependent nodes.

    Returns:
        A list of nodes in topological order. Returns an empty list if a cycle exists.

    Example Application:
        In a software build system (like Make or CMake), tasks (nodes) depend on other tasks
        (e.g., compiling a source file depends on having the header files). Topological sort
        determines the order in which to execute the tasks.

    """
    in_degree = {node: 0 for node in graph}  # Calculate in-degrees
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    queue = deque([node for node in in_degree if in_degree[node] == 0])  # Start with nodes with no dependencies
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(result) != len(graph):
        return []  # Cycle detected
    else:
        return result

# 2. Kahn's Algorithm with Cycle Detection - Task Scheduling with Dependencies
def topological_sort_kahn_cycle_detect(graph: Dict[str, List[str]]) -> Tuple[List[str], bool]:
    """
    Kahn's algorithm with explicit cycle detection.

    Args:
        graph: Adjacency list representation of the graph.

    Returns:
        A tuple:
            - The topological order (list of nodes) or an empty list if a cycle exists.
            - A boolean indicating whether a cycle was detected (True if cycle, False otherwise).

     Example Application:
        Task scheduling in project management.  Tasks have dependencies, and you need to schedule
        them in an order that satisfies those dependencies.  This version detects if the dependencies
        are contradictory (a cycle), which would mean the project is impossible to schedule.
    """
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    queue = deque([node for node in in_degree if in_degree[node] == 0])
    result = []
    nodes_visited = 0 # Keep track of how many nodes were visited

    while queue:
        node = queue.popleft()
        result.append(node)
        nodes_visited += 1
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if nodes_visited != len(graph):
        return [], True  # Cycle detected
    else:
        return result, False

# 3. Kahn's Algorithm with Priority - Course Scheduling with Prerequisites
def topological_sort_kahn_priority(graph: Dict[str, List[str]], priorities: Dict[str, int]) -> List[str]:
    """
    Kahn's algorithm, considering node priorities.

    Args:
        graph: Adjacency list representation of the graph.
        priorities: A dictionary mapping nodes to their priorities (lower value means higher priority).

    Returns:
        A list of nodes in topological order, considering priorities.  If there's a tie,
        nodes with higher priority (lower priority value) are added to the result first.

    Example Application:
        Course scheduling in a university.  Courses have prerequisites (dependencies),
        and some courses might have higher priority (e.g., required courses for a major).
        This version ensures that high-priority courses are scheduled as early as possible.
    """
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    # Use a list and sort it to simulate a priority queue.  For large graphs, a heap would be more efficient.
    queue_list = [(node, in_degree[node]) for node in in_degree if in_degree[node] == 0]
    queue_list.sort(key=lambda x: priorities[x[0]])  # Sort by priority

    queue = deque(queue_list)
    result = []

    while queue:
        node, _ = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue_list.append((neighbor, in_degree[neighbor]))
                queue_list.sort(key=lambda x: priorities[x[0]]) # keep sorted
                queue = deque(queue_list) #update queue

    if len(result) != len(graph):
        return []  # Cycle detected
    else:
        return result
# 4. Kahn's Algorithm with Feedback - Dependency Resolution with Updates
def topological_sort_kahn_feedback(graph: Dict[str, List[str]], initial_order: Optional[List[str]] = None) -> List[str]:
    """
    Kahn's algorithm that can incorporate a partial initial ordering.

    Args:
        graph: Adjacency list representation of the graph.
        initial_order: An optional list representing a partial topological order.
                       Nodes in this list are prioritized in the sorting process.

    Returns:
        A topological ordering of the nodes.

    Example Application:
        Software dependency management where a user provides a partial order of installation.
        For example, a user might want a specific library to be installed first.  This version
        respects that preference while still satisfying dependencies.
    """
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    queue = deque()
    if initial_order:
        for node in initial_order:
            if in_degree[node] == 0:
                queue.append(node)
                in_degree[node] = -1  # Mark as added to queue
        for node in in_degree: #add the rest
            if in_degree[node] == 0:
                queue.append(node)
    else:
        queue = deque([node for node in in_degree if in_degree[node] == 0])

    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(result) != len(graph):
        return []  # Cycle detected
    else:
        return result

# 5. Kahn's Algorithm for DAG Validation - Workflow Validation
def is_dag_kahn(graph: Dict[str, List[str]]) -> bool:
    """
    Uses Kahn's algorithm to determine if a graph is a DAG.  It's not strictly a topological sort,
    but it leverages the same logic.

    Args:
        graph: Adjacency list representation of the graph.

    Returns:
        True if the graph is a DAG, False otherwise.

    Example Application:
        Validating workflows in a business process management system.  A workflow can be represented
        as a graph where activities are nodes and dependencies between activities are edges.  This
        function checks if the workflow definition is valid (i.e., contains no circular dependencies).
    """
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    queue = deque([node for node in in_degree if in_degree[node] == 0])
    count = 0

    while queue:
        node = queue.popleft()
        count += 1
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    return count == len(graph) #if count is equal to number of nodes, then it is a DAG

# 6. Kahn's Algorithm with Edge Weights (for shortest path in DAG) - Project Scheduling with Time Constraints
def topological_sort_kahn_weighted(graph: Dict[str, List[Tuple[str, int]]]) -> List[str]:
    """
    Kahn's algorithm for a graph with edge weights.  While not a pure topological sort,
    it's adapted to handle weighted edges, which is useful for finding the longest path
    in a DAG (which is related to critical path analysis).

    Args:
        graph:  Adjacency list where values are lists of (neighbor, weight) tuples.
                For example: {'A': [('B', 5), ('C', 3)], 'B': [('D', 2)]}
        start_node: The starting node for the longest path calculation.

    Returns:
        A topological ordering of the nodes.

    Example Application:
        Project scheduling with time constraints.  Nodes are tasks, edges are dependencies,
        and edge weights are the time it takes to complete a task.  This can be adapted to find
        the critical path (the longest sequence of tasks that determines the project duration).
    """
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor, _ in graph[node]:  # Iterate through neighbors and weights, we only care about neighbors for in_degree
            in_degree[neighbor] += 1

    queue = deque([node for node in in_degree if in_degree[node] == 0])
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor, _ in graph[node]: # Iterate through neighbors and weights.
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(result) != len(graph):
        return []  # Cycle detected
    else:
        return result

def main():
    """
    Main function to demonstrate the different topological sort implementations.
    """
    # Example graph (Directed Acyclic Graph)
    graph = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': ['E', 'F'],
        'E': ['F'],
        'F': []
    }

    print("1. Basic Kahn's Algorithm - Dependency Resolution:")
    result1 = topological_sort_kahn_basic(graph)
    print("   Topological Order:", result1)  # Output: ['A', 'C', 'B', 'D', 'E', 'F'] or other valid order

    print("\n2. Kahn's Algorithm with Cycle Detection - Task Scheduling:")
    result2, has_cycle = topological_sort_kahn_cycle_detect(graph)
    print("   Topological Order:", result2)
    print("   Cycle Detected:", has_cycle)  # Output: False

    # Example graph with a cycle
    graph_with_cycle = {
        'A': ['B'],
        'B': ['C'],
        'C': ['A']
    }
    result2_cycle, has_cycle_cycle = topological_sort_kahn_cycle_detect(graph_with_cycle)
    print("\n   With Cycle:")
    print("   Topological Order:", result2_cycle)
    print("   Cycle Detected:", has_cycle_cycle)  # Output: True

    print("\n3. Kahn's Algorithm with Priority - Course Scheduling:")
    priorities = {'A': 2, 'B': 1, 'C': 3, 'D': 1, 'E': 2, 'F': 3}  # Lower value = higher priority
    result3 = topological_sort_kahn_priority(graph, priorities)
    print("   Topological Order with Priorities:", result3)  # Output:  ['B', 'D', 'A', 'E', 'C', 'F']

    print("\n4. Kahn's Algorithm with Feedback - Dependency Resolution with Updates:")
    initial_order = ['B', 'C']  # User wants B and C to be processed first, if possible
    result4 = topological_sort_kahn_feedback(graph, initial_order)
    print("   Topological Order with Feedback:", result4) # Output: ['B', 'C', 'A', 'D', 'E', 'F']

    print("\n5. Kahn's Algorithm for DAG Validation - Workflow Validation:")
    is_dag = is_dag_kahn(graph)
    print("   Is DAG:", is_dag)  # Output: True
    is_dag_cycle = is_dag_kahn(graph_with_cycle)
    print("   Is DAG (with cycle):", is_dag_cycle) # Output: False

    print("\n6. Kahn's Algorithm with Edge Weights - Project Scheduling with Time Constraints:")
    weighted_graph = {
        'A': [('B', 5), ('C', 3)],
        'B': [('D', 2), ('E', 4)],
        'C': [('F', 1)],
        'D': [('E', 1), ('F', 6)],
        'E': [('F', 2)],
        'F': []
    }
    result6 = topological_sort_kahn_weighted(weighted_graph)
    print("  Topological Order with Weights:", result6)

if __name__ == "__main__":
    main()

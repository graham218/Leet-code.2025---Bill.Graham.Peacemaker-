# Definition for a Node.
class Node:
    def __init__(self, val=0, neighbors=None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

    def __repr__(self):
        """
        String representation of the Node for easy printing.  Important for debugging
        and visualizing the graph structure.  Correctly handles cycles.
        """
        visited = set()
        nodes = [(self, [self.val])]  # Use a list to keep track of the path
        result = []

        while nodes:
            node, path = nodes.pop(0)  # Use FIFO for Breadth-First Traversal
            if node not in visited:
                visited.add(node)
                neighbor_vals = [n.val for n in node.neighbors]
                result.append(f"{node.val}: {neighbor_vals}")

                for neighbor in node.neighbors:
                    if neighbor not in visited:
                        nodes.append((neighbor, path + [neighbor.val]))
        return ', '.join(result)

def create_graph(adj_list):
    """
    Helper function to create a graph from an adjacency list.  Handles empty graphs.

    Args:
        adj_list (list of lists): Adjacency list representation of the graph.
            For example, [[2,4],[1,3],[2,4],[1,3]] represents a graph where:
            - Node 1 is connected to nodes 2 and 4.
            - Node 2 is connected to nodes 1 and 3.
            - Node 3 is connected to nodes 2 and 4.
            - Node 4 is connected to nodes 1 and 3.

    Returns:
        Node: The root node of the created graph.  Returns None for an empty graph.
    """
    if not adj_list:
        return None  # Handle empty graph case

    nodes = [Node(i) for i in range(1, len(adj_list) + 1)]  # 1-indexed nodes
    for i, neighbors in enumerate(adj_list):
        for neighbor_val in neighbors:
            # Adjust to 0-based indexing for the nodes list.
            nodes[i].neighbors.append(nodes[neighbor_val - 1])
    return nodes[0]  # Return the first node as the starting point of the graph.

def print_graph(node):
    """
    Helper function to print the graph structure in a user-friendly format.
    Handles the case of an empty graph (None node).  Uses the __repr__
    method of the Node class for clear output.

    Args:
        node (Node): The starting node of the graph to print.
    """
    if not node:
        print("Graph is empty (None).")
        return
    print(node)  # Use the string representation of the Node

################################################################################
# Approach 1: Depth-First Search (DFS) - Iterative with Stack
################################################################################
def cloneGraph_dfs_iterative(node: Node) -> Node:
    """
    Clones an undirected graph using iterative Depth-First Search (DFS) with a stack.

    This approach avoids recursion, which can be helpful for very large graphs
    to prevent stack overflow errors.  It uses a stack to keep track of nodes
    to visit.

    Args:
        node (Node): The node to start the cloning process from.

    Returns:
        Node: A clone of the input graph's starting node. Returns None if the input node is None.

    Real-world application:
    -   **Network Visualization:** In a network monitoring tool, you might use this to create a copy of the network topology
        for analysis or simulation without affecting the live network.  Changes in the cloned graph (simulated changes)
        won't affect the original network.
    """
    if not node:
        return None

    stack = [node]
    # Use a dictionary (node_map) to store the mapping between original nodes and their clones.
    node_map = {node: Node(node.val)}  # Store the initial node

    while stack:
        original_node = stack.pop()
        cloned_node = node_map[original_node]

        for neighbor in original_node.neighbors:
            if neighbor not in node_map:
                # Create a clone of the neighbor if it hasn't been cloned yet.
                node_map[neighbor] = Node(neighbor.val)
                stack.append(neighbor)  # Add to stack for processing
            # Add the cloned neighbor to the cloned node's neighbors list.
            cloned_node.neighbors.append(node_map[neighbor])
    return node_map[node]  # Return the clone of the starting node

################################################################################
# Approach 2: Breadth-First Search (BFS)
################################################################################
def cloneGraph_bfs(node: Node) -> Node:
    """
    Clones an undirected graph using Breadth-First Search (BFS).

    BFS uses a queue to explore the graph level by level, ensuring that nodes closer
    to the starting node are visited first.

    Args:
        node (Node): The node to start the cloning process from.

    Returns:
        Node: A clone of the input graph's starting node. Returns None if the input node is None.

    Real-world application:
    -   **Social Network Analysis:** You could use this to create a copy of a user's connections
        (friends, followers) to analyze their social graph without modifying the original data.
        For example, you might want to find the shortest path between two users in a social network,
        and you'd do that on a *clone* of the graph to avoid altering the original data.
    """
    if not node:
        return None

    queue = [node]
    node_map = {node: Node(node.val)}  # Store the initial node

    while queue:
        original_node = queue.pop(0)  # Dequeue from the front
        cloned_node = node_map[original_node]

        for neighbor in original_node.neighbors:
            if neighbor not in node_map:
                node_map[neighbor] = Node(neighbor.val)
                queue.append(neighbor)  # Enqueue the neighbor
            cloned_node.neighbors.append(node_map[neighbor])
    return node_map[node]

################################################################################
# Approach 3: Depth-First Search (DFS) - Recursive
################################################################################
def cloneGraph_dfs_recursive(node: Node) -> Node:
    """
    Clones an undirected graph using recursive Depth-First Search (DFS).

    This is a classic recursive approach.  For each node, it creates a clone and
    then recursively clones its neighbors.

    Args:
        node (Node): The node to start the cloning process from.

    Returns:
        Node: A clone of the input graph's starting node. Returns None if the input node is None.

    Real-world application:
    -   **Version Control Systems:** In a distributed version control system (like Git), you might use a recursive
        DFS approach to clone a repository and all its branches and commits.  Each commit can be considered
        a node, and the parent-child relationships between commits form a graph.  Cloning creates a complete copy
        of this graph.
    """
    if not node:
        return None

    node_map = {}  # Use a dictionary to store cloned nodes

    def _clone(node):
        if node in node_map:
            return node_map[node]  # Return the cloned node if it exists

        cloned_node = Node(node.val)
        node_map[node] = cloned_node  # Store the cloned node
        for neighbor in node.neighbors:
            cloned_node.neighbors.append(_clone(neighbor))  # Recursive call
        return cloned_node

    return _clone(node)  # Start the recursion from the given node

################################################################################
# Approach 4: Iterative DFS with Visited Set
################################################################################
def cloneGraph_dfs_iterative_visited(node: Node) -> Node:
    """
    Clones a graph using iterative DFS with a visited set to prevent revisiting nodes.

    This approach is similar to the first iterative DFS, but uses a set to keep
    track of visited nodes, which can improve efficiency in some cases.

    Args:
        node (Node): The node to start the cloning from.

    Returns:
        Node: A clone of the graph's starting node, or None if the input is None.

    Real-world application:
     -  **Web Crawlers:** Web crawlers use graph traversal algorithms to explore the internet.  They need to keep track of
        which pages they have already visited to avoid infinite loops.  A clone of a subset of the web graph
        could be created for analysis (e.g., link analysis, identifying influential pages).
    """
    if not node:
        return None

    stack = [node]
    visited = {node}
    node_map = {node: Node(node.val)}

    while stack:
        curr_node = stack.pop()
        cloned_node = node_map[curr_node]

        for neighbor in curr_node.neighbors:
            if neighbor not in node_map:
                node_map[neighbor] = Node(neighbor.val)
            cloned_node.neighbors.append(node_map[neighbor])
            if neighbor not in visited:
                visited.add(neighbor)
                stack.append(neighbor)
    return node_map[node]

################################################################################
# Approach 5: Using a Queue and a Visited Set
################################################################################
def cloneGraph_queue_visited(node: Node) -> Node:
    """
    Clones a graph using a queue and a visited set. This is very similar to BFS.

    This approach combines the queue data structure with a visited set to ensure
    efficient and correct graph traversal.

    Args:
        node (Node): The starting node for cloning.

    Returns:
        Node: The cloned graph's starting node, or None for an empty input.

    Real-world Application:
    - **Robotics and Path Planning**:  Consider a robot navigating a maze or a complex environment.  The environment can be
       represented as a graph, and the robot needs to explore it systematically.  A clone of the environment's graph
       can be useful for simulating different paths or testing navigation strategies *before* executing them in the real world.
    """
    if not node:
        return None

    queue = [node]
    visited = {node}
    node_map = {node: Node(node.val)}

    while queue:
        curr_node = queue.pop(0)
        cloned_node = node_map[curr_node]

        for neighbor in curr_node.neighbors:
            if neighbor not in node_map:
                node_map[neighbor] = Node(neighbor.val)
            cloned_node.neighbors.append(node_map[neighbor])
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return node_map[node]

################################################################################
# Approach 6:  Iterative Approach with Explicit Node Creation
################################################################################
def cloneGraph_iterative_explicit(node: Node) -> Node:
    """
    Clones a graph iteratively, with more explicit node creation and handling.

    This approach provides a very clear step-by-step process of node creation
    and neighbor assignment.

    Args:
        node (Node): The entry point for cloning the graph.

    Returns:
        Node: The cloned graph's starting node, or None if the input is None.

    Real-world Application:
    -  **Circuit Design and Simulation**:  Electronic circuits can be modeled as graphs, where components are nodes and
       connections are edges.  If you're designing or simulating a complex circuit, you might need to create a copy of the
       circuit graph to test different configurations or analyze its behavior without affecting the original design.
    """
    if not node:
        return None

    stack = [node]
    node_map = {}

    # 1. Create clones for all nodes first
    nodes_to_clone = [node]
    visited = {node}
    while nodes_to_clone:
        curr = nodes_to_clone.pop(0)
        node_map[curr] = Node(curr.val) # Create clone, store in map
        for neighbor in curr.neighbors:
            if neighbor not in visited:
                visited.add(neighbor)
                nodes_to_clone.append(neighbor)

    # 2.  Connect the cloned nodes based on the original graph's connections
    stack = [node]
    visited = {node}
    while stack:
        curr = stack.pop()
        cloned_node = node_map[curr]  # Get the clone
        for neighbor in curr.neighbors:
            cloned_neighbor = node_map[neighbor] # Get the cloned neighbor
            cloned_node.neighbors.append(cloned_neighbor) # Add cloned neighbor
            if neighbor not in visited:
                visited.add(neighbor)
                stack.append(neighbor)

    return node_map[node]
################################################################################
# Main function to test the cloneGraph implementations
################################################################################
def main():
    """
    Main function to test the cloneGraph implementations with various graph examples.
    """
    # Test Case 1:  A simple connected graph
    adj_list1 = [[2, 4], [1, 3], [2, 4], [1, 3]]
    print("\nTest Case 1: Simple Connected Graph")
    original_graph1 = create_graph(adj_list1)
    print("Original Graph 1:")
    print_graph(original_graph1)

    # Test each cloneGraph implementation:
    cloned_graph_1_dfs_iterative = cloneGraph_dfs_iterative(original_graph1)
    print("\nCloned Graph 1 (DFS Iterative):")
    print_graph(cloned_graph_1_dfs_iterative)

    cloned_graph_1_bfs = cloneGraph_bfs(original_graph1)
    print("\nCloned Graph 1 (BFS):")
    print_graph(cloned_graph_1_bfs)

    cloned_graph_1_dfs_recursive = cloneGraph_dfs_recursive(original_graph1)
    print("\nCloned Graph 1 (DFS Recursive):")
    print_graph(cloned_graph_1_dfs_recursive)

    cloned_graph_1_dfs_iterative_visited = cloneGraph_dfs_iterative_visited(original_graph1)
    print("\nCloned Graph 1 (DFS Iterative Visited):")
    print_graph(cloned_graph_1_dfs_iterative_visited)

    cloned_graph_1_queue_visited = cloneGraph_queue_visited(original_graph1)
    print("\nCloned Graph 1 (Queue Visited):")
    print_graph(cloned_graph_1_queue_visited)

    cloned_graph_1_explicit = cloneGraph_iterative_explicit(original_graph1)
    print("\nCloned Graph 1 (Iterative Explicit):")
    print_graph(cloned_graph_1_explicit)
    # Test Case 2:  A graph with a cycle
    adj_list2 = [[2], [1, 3], [2, 4], [3, 1]]
    print("\nTest Case 2: Graph with a Cycle")
    original_graph2 = create_graph(adj_list2)
    print("Original Graph 2:")
    print_graph(original_graph2)

    cloned_graph_2_dfs_iterative = cloneGraph_dfs_iterative(original_graph2)
    print("\nCloned Graph 2 (DFS Iterative):")
    print_graph(cloned_graph_2_dfs_iterative)

    cloned_graph_2_bfs = cloneGraph_bfs(original_graph2)
    print("\nCloned Graph 2 (BFS):")
    print_graph(cloned_graph_2_bfs)

    cloned_graph_2_dfs_recursive = cloneGraph_dfs_recursive(original_graph2)
    print("\nCloned Graph 2 (DFS Recursive):")
    print_graph(cloned_graph_2_dfs_recursive)

    cloned_graph_2_dfs_iterative_visited = cloneGraph_dfs_iterative_visited(original_graph2)
    print("\nCloned Graph 2 (DFS Iterative Visited):")
    print_graph(cloned_graph_2_dfs_iterative_visited)

    cloned_graph_2_queue_visited = cloneGraph_queue_visited(original_graph2)
    print("\nCloned Graph 2 (Queue Visited):")
    print_graph(cloned_graph_2_queue_visited)

    cloned_graph_2_explicit = cloneGraph_iterative_explicit(original_graph2)
    print("\nCloned Graph 2 (Iterative Explicit):")
    print_graph(cloned_graph_2_explicit)

    # Test Case 3:  An empty graph
    adj_list3 = []
    print("\nTest Case 3: Empty Graph")
    original_graph3 = create_graph(adj_list3)
    print("Original Graph 3:")
    print_graph(original_graph3)

    cloned_graph_3_dfs_iterative = cloneGraph_dfs_iterative(original_graph3)
    print("\nCloned Graph 3 (DFS Iterative):")
    print_graph(cloned_graph_3_dfs_iterative)

    cloned_graph_3_bfs = cloneGraph_bfs(original_graph3)
    print("\nCloned Graph 3 (BFS):")
    print_graph(cloned_graph_3_bfs)

    cloned_graph_3_dfs_recursive = cloneGraph_dfs_recursive(original_graph3)
    print("\nCloned Graph 3 (DFS Recursive):")
    print_graph(cloned_graph_3_dfs_recursive)

    cloned_graph_3_dfs_iterative_visited = cloneGraph_dfs_iterative_visited(original_graph3)
    print("\nCloned Graph 3 (DFS Iterative Visited):")
    print_graph(cloned_graph_3_dfs_iterative_visited)

    cloned_graph_3_queue_visited = cloneGraph_queue_visited(original_graph3)
    print("\nCloned Graph 3 (Queue Visited):")
    print_graph(cloned_graph_3_queue_visited)

    cloned_graph_3_explicit = cloneGraph_iterative_explicit(original_graph3)
    print("\nCloned Graph 3 (Iterative Explicit):")
    print_graph(cloned_graph_3_explicit)

    # Test Case 4: Single Node Graph
    adj_list4 = [[]]
    print("\nTest Case 4: Single Node Graph")
    original_graph4 = create_graph(adj_list4)
    print("Original Graph 4:")
    print_graph(original_graph4)

    cloned_graph_4_dfs_iterative = cloneGraph_dfs_iterative(original_graph4)
    print("\nCloned Graph 4 (DFS Iterative):")
    print_graph(cloned_graph_4_dfs_iterative)

    cloned_graph_4_bfs = cloneGraph_bfs(original_graph4)
    print("\nCloned Graph 4 (BFS):")
    print_graph(cloned_graph_4_bfs)

    cloned_graph_4_dfs_recursive = cloneGraph_dfs_recursive(original_graph4)
    print("\nCloned Graph 4 (DFS Recursive):")
    print_graph(cloned_graph_4_dfs_recursive)

    cloned_graph_4_dfs_iterative_visited = cloneGraph_dfs_iterative_visited(original_graph4)
    print("\nCloned Graph 4 (DFS Iterative Visited):")
    print_graph(cloned_graph_4_dfs_iterative_visited)

    cloned_graph_4_queue_visited = cloneGraph_queue_visited(original_graph4)
    print("\nCloned Graph 4 (Queue Visited):")
    print_graph(cloned_graph_4_queue_visited)

    cloned_graph_4_explicit = cloneGraph_iterative_explicit(original_graph4)
    print("\nCloned Graph 4 (Iterative Explicit):")
    print_graph(cloned_graph_4_explicit)

if __name__ == "__main__":
    main()

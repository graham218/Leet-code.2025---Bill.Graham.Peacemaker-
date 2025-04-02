# Kruskal's Algorithm for Minimum Spanning Tree (MST)

# A class to represent a graph edge
class Edge:
    def __init__(self, u, v, weight):
        self.u = u
        self.v = v
        self.weight = weight

    def __lt__(self, other):  # For comparing edges based on weight
        return self.weight < other.weight

    def __str__(self):
        return f"({self.u}, {self.v}, {self.weight})"

# ----------------------------------------------------------------------------------------
# 1. Kruskal's Algorithm using a simple list for edges and a dictionary for parent (Disjoint Set)
# ----------------------------------------------------------------------------------------
def kruskal_mst_simple(edges, num_vertices):
    """
    Computes the Minimum Spanning Tree (MST) of a graph using Kruskal's algorithm.

    Args:
        edges: A list of Edge objects representing the graph's edges.
        num_vertices: The number of vertices in the graph.

    Returns:
        A list of Edge objects representing the MST, or None if the input is invalid.
    """
    if not edges or num_vertices <= 0:
        print("Error: Invalid input (empty edges or non-positive number of vertices).")
        return None

    # Sort edges by weight in ascending order
    edges.sort()
    print("\n1. Kruskal's Algorithm - Simple List & Dictionary")
    print("Sorted Edges:", [str(e) for e in edges])

    # Initialize parent dictionary for disjoint set
    parent = {v: v for v in range(num_vertices)}

    def find_simple(i):
        """Find the set of an element i (with path compression)."""
        if parent[i] == i:
            return i
        parent[i] = find_simple(parent[i])  # Path compression
        return parent[i]

    def union_simple(i, j):
        """Union the sets of two elements i and j."""
        root_i = find_simple(i)
        root_j = find_simple(j)
        if root_i != root_j:
            parent[root_i] = root_j
            return True # Return True if union was successful
        return False # Return False if no union was needed

    mst_edges = []
    mst_weight = 0
    num_edges_added = 0 # Keep track of edges added to the MST

    for edge in edges:
        if union_simple(edge.u, edge.v):
            mst_edges.append(edge)
            mst_weight += edge.weight
            num_edges_added += 1
            print(f"Added edge: {edge}, Current MST Weight: {mst_weight}")

        if num_edges_added == num_vertices - 1:
            break # Optimization: Stop if we have enough edges for a MST

    if num_edges_added != num_vertices - 1:
        print("Error: Graph is not connected. MST not found.")
        return None

    print("MST Edges:", [str(e) for e in mst_edges])
    print("Total MST Weight:", mst_weight)
    return mst_edges

# ----------------------------------------------------------------------------------------
# 2. Kruskal's Algorithm using a class for Disjoint Set Union (DSU)
# ----------------------------------------------------------------------------------------
class DisjointSet:
    """
    A class to represent the Disjoint Set Union (DSU) data structure.
    Implements path compression and union by rank.
    """
    def __init__(self, num_vertices):
        self.parent = list(range(num_vertices))
        self.rank = [0] * num_vertices  # Added rank for union by rank

    def find(self, i):
        """Find the set of an element i (with path compression)."""
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i, j):
        """Union the sets of two elements i and j (using union by rank)."""
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1  # Increment rank if ranks are equal
            return True # Return True if union was successful
        return False # Return False if no union

def kruskal_mst_dsu_class(edges, num_vertices):
    """
    Computes the MST using Kruskal's algorithm with a DisjointSet class.

    Args:
        edges: A list of Edge objects.
        num_vertices: The number of vertices.

    Returns:
        A list of Edge objects representing the MST, or None if input is invalid.
    """
    if not edges or num_vertices <= 0:
        print("Error: Invalid input (empty edges or non-positive number of vertices).")
        return None

    edges.sort()
    print("\n2. Kruskal's Algorithm - DSU Class")
    print("Sorted Edges:", [str(e) for e in edges])

    dsu = DisjointSet(num_vertices)
    mst_edges = []
    mst_weight = 0
    num_edges_added = 0

    for edge in edges:
        if dsu.union(edge.u, edge.v):
            mst_edges.append(edge)
            mst_weight += edge.weight
            num_edges_added += 1
            print(f"Added edge: {edge}, Current MST Weight: {mst_weight}")

        if num_edges_added == num_vertices - 1:
            break

    if num_edges_added != num_vertices - 1:
        print("Error: Graph is not connected. MST not found.")
        return None

    print("MST Edges:", [str(e) for e in mst_edges])
    print("Total MST Weight:", mst_weight)
    return mst_edges

# ----------------------------------------------------------------------------------------
# 3. Kruskal's Algorithm with Path Compression and Rank (Explicit Implementation)
# ----------------------------------------------------------------------------------------
def kruskal_mst_path_rank(edges, num_vertices):
    """
    Computes the MST using Kruskal's algorithm with explicit path compression
    and union by rank.

    Args:
        edges: A list of Edge objects.
        num_vertices: The number of vertices.

    Returns:
        A list of Edge objects representing the MST, or None.
    """
    if not edges or num_vertices <= 0:
        print("Error: Invalid input (empty edges or non-positive number of vertices).")
        return None

    edges.sort()
    print("\n3. Kruskal's Algorithm - Path Compression & Rank")
    print("Sorted Edges:", [str(e) for e in edges])

    parent = list(range(num_vertices))
    rank = [0] * num_vertices

    def find_path_rank(i):
        """Find the set of an element i (with path compression)."""
        if parent[i] == i:
            return i
        parent[i] = find_path_rank(parent[i])
        return parent[i]

    def union_path_rank(i, j):
        """Union the sets of two elements i and j (using union by rank)."""
        root_i = find_path_rank(i)
        root_j = find_path_rank(j)
        if root_i != root_j:
            if rank[root_i] < rank[root_j]:
                parent[root_i] = root_j
            elif rank[root_i] > rank[root_j]:
                parent[root_j] = root_i
            else:
                parent[root_j] = root_i
                rank[root_i] += 1
            return True # Return True if union was successful
        return False # Return False if no union

    mst_edges = []
    mst_weight = 0
    num_edges_added = 0

    for edge in edges:
        if union_path_rank(edge.u, edge.v):
            mst_edges.append(edge)
            mst_weight += edge.weight
            num_edges_added += 1
            print(f"Added edge: {edge}, Current MST Weight: {mst_weight}")

        if num_edges_added == num_vertices - 1:
            break

    if num_edges_added != num_vertices - 1:
        print("Error: Graph is not connected. MST not found.")
        return None

    print("MST Edges:", [str(e) for e in mst_edges])
    print("Total MST Weight:", mst_weight)
    return mst_edges

# ----------------------------------------------------------------------------------------
# 4. Kruskal's Algorithm using a helper function for edge processing
# ----------------------------------------------------------------------------------------
def process_edge(edge, parent, mst_edges, mst_weight, num_edges_added):
    """
    Helper function to process an edge in Kruskal's algorithm.

    Args:
        edge: The Edge to process.
        parent: The parent dictionary for DSU.
        mst_edges: The list of MST edges.
        mst_weight: The current MST weight.
        num_edges_added: Number of edges added so far.

    Returns:
        A tuple containing (updated mst_edges, updated mst_weight, updated num_edges_added).
    """
    def find(i):
        if parent[i] == i:
            return i
        parent[i] = find(parent[i])
        return parent[i]

    def union(i, j):
        root_i = find(i)
        root_j = find(j)
        if root_i != root_j:
            parent[root_i] = root_j
            return True
        return False

    if union(edge.u, edge.v):
        mst_edges.append(edge)
        mst_weight += edge.weight
        num_edges_added += 1
        print(f"Added edge: {edge}, Current MST Weight: {mst_weight}")
    return mst_edges, mst_weight, num_edges_added

def kruskal_mst_helper(edges, num_vertices):
    """
    Computes the MST using Kruskal's algorithm with a helper function.

    Args:
        edges: A list of Edge objects.
        num_vertices: The number of vertices.

    Returns:
        A list of Edge objects representing the MST, or None.
    """
    if not edges or num_vertices <= 0:
        print("Error: Invalid input (empty edges or non-positive number of vertices).")
        return None

    edges.sort()
    print("\n4. Kruskal's Algorithm - Helper Function")
    print("Sorted Edges:", [str(e) for e in edges])

    parent = {v: v for v in range(num_vertices)}
    mst_edges = []
    mst_weight = 0
    num_edges_added = 0

    for edge in edges:
        mst_edges, mst_weight, num_edges_added = process_edge(edge, parent, mst_edges, mst_weight, num_edges_added)
        if num_edges_added == num_vertices - 1:
            break

    if num_edges_added != num_vertices - 1:
        print("Error: Graph is not connected. MST not found.")
        return None

    print("MST Edges:", [str(e) for e in mst_edges])
    print("Total MST Weight:", mst_weight)
    return mst_edges

# ----------------------------------------------------------------------------------------
# 5. Kruskal's Algorithm with early stopping and validation
# ----------------------------------------------------------------------------------------
def kruskal_mst_early_stop(edges, num_vertices):
    """
    Computes the MST using Kruskal's algorithm with early stopping
    and input validation.

    Args:
        edges: A list of Edge objects.
        num_vertices: The number of vertices.

    Returns:
        A list of Edge objects representing the MST, or None.
    """
    if not edges or num_vertices <= 0:
        print("Error: Invalid input (empty edges or non-positive number of vertices).")
        return None

    if len(edges) < num_vertices -1:
        print("Error: The number of edges is less than (number of vertices -1).  MST not possible.")
        return None

    edges.sort()
    print("\n5. Kruskal's Algorithm - Early Stopping & Validation")
    print("Sorted Edges:", [str(e) for e in edges])

    parent = {v: v for v in range(num_vertices)}

    def find(i):
        if parent[i] == i:
            return i
        parent[i] = find(parent[i])
        return parent[i]

    def union(i, j):
        root_i = find(i)
        root_j = find(j)
        if root_i != root_j:
            parent[root_i] = root_j
            return True
        return False

    mst_edges = []
    mst_weight = 0
    num_edges_added = 0

    for edge in edges:
        if union(edge.u, edge.v):
            mst_edges.append(edge)
            mst_weight += edge.weight
            num_edges_added += 1
            print(f"Added edge: {edge}, Current MST Weight: {mst_weight}")

        if num_edges_added == num_vertices - 1:
            break  # Early stopping: MST is complete

    if num_edges_added != num_vertices - 1:
        print("Error: Graph is not connected. MST not found.")
        return None

    print("MST Edges:", [str(e) for e in mst_edges])
    print("Total MST Weight:", mst_weight)
    return mst_edges

if __name__ == "__main__":
    # Example graph represented as a list of edges
    # (u, v, weight) represents an edge between vertex u and v with the given weight
    edges = [
        Edge(0, 1, 10),
        Edge(0, 2, 6),
        Edge(0, 3, 5),
        Edge(1, 3, 15),
        Edge(2, 3, 4),
    ]
    num_vertices = 4

    # Run Kruskal's algorithm with the different implementations
    mst_simple = kruskal_mst_simple(edges, num_vertices)
    print("-" * 40)
    mst_dsu_class = kruskal_mst_dsu_class(edges, num_vertices)
    print("-" * 40)
    mst_path_rank = kruskal_mst_path_rank(edges, num_vertices)
    print("-" * 40)
    mst_helper = kruskal_mst_helper(edges, num_vertices)
    print("-" * 40)
    mst_early_stop = kruskal_mst_early_stop(edges, num_vertices)

    # Example with a disconnected graph
    edges_disconnected = [
        Edge(0, 1, 10),
        Edge(2, 3, 4),
    ]
    num_vertices_disconnected = 4
    mst_disconnected = kruskal_mst_simple(edges_disconnected, num_vertices_disconnected) # Should print an error
    print("-" * 40)

    # Example with an empty graph
    edges_empty = []
    num_vertices_empty = 0
    mst_empty = kruskal_mst_simple(edges_empty, num_vertices_empty) # Should print an error
    print("-" * 40)

    # Example with a graph that has fewer edges than required for MST
    edges_few = [
        Edge(0, 1, 10),
        Edge(0, 2, 6),
    ]
    num_vertices_few = 4
    mst_few = kruskal_mst_early_stop(edges_few, num_vertices_few) # Should print an error
    print("-" * 40)

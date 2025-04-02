import heapq
import sys

# Define a class to represent a graph
class Graph:
    def __init__(self, vertices):
        """
        Initializes the Graph object.

        Args:
            vertices: The number of vertices in the graph.
        """
        self.V = vertices  # Number of vertices
        self.graph = [[] for _ in range(vertices)]  # Adjacency list representation

    def add_edge(self, u, v, w):
        """
        Adds an edge to the graph.  Since it's an undirected graph,
        we add the edge in both directions.

        Args:
            u: The source vertex.
            v: The destination vertex.
            w: The weight of the edge.
        """
        self.graph[u].append((v, w))
        self.graph[v].append((u, w))  # Add edge in both directions for undirected graph

    def prim_mst_heapq(self):
        """
        Prim's algorithm using heapq (priority queue).  This is generally the
        most efficient approach in Python due to the optimized heap implementation.

        Returns:
            A list of tuples representing the edges in the MST,
            and the total weight of the MST.  Returns empty list and 0 if graph is empty.
        """
        if not self.graph:
            print("Graph is empty.  Returning empty MST.")
            return [], 0

        mst_edges = []  # List to store edges of the MST
        mst_weight = 0  # Total weight of the MST
        visited = [False] * self.V  # Track visited vertices
        pq = [(0, 0, -1)]  # Priority queue (weight, vertex, parent). Start at vertex 0 with weight 0 and no parent.
        #  The parent is included to help reconstruct the MST edges.

        print("\nPrim's Algorithm using heapq:")
        while pq:
            weight, u, parent = heapq.heappop(pq)  # Get the minimum weight edge
            if visited[u]:
                continue  # If vertex already visited, skip it
            visited[u] = True  # Mark vertex as visited
            mst_weight += weight  # Add the weight to the MST weight

            if parent != -1:  # Add the edge to the MST (unless it's the starting vertex)
                mst_edges.append((parent, u, weight))
                print(f"  Added edge: {parent} - {u} with weight {weight}")

            for v, w in self.graph[u]:  # Iterate over neighbors of u
                if not visited[v]:
                    heapq.heappush(pq, (w, v, u))  # Add neighbor to priority queue

        print(f"  MST Edges: {mst_edges}")
        print(f"  Total MST weight: {mst_weight}")
        return mst_edges, mst_weight


    def prim_mst_naive(self):
        """
        Prim's algorithm using a naive approach (finding min weight edge manually).
        This is less efficient than the heapq approach, especially for larger graphs.

        Returns:
            A list of tuples representing the edges in the MST,
            and the total weight of the MST. Returns empty list and 0 if graph is empty.
        """
        if not self.graph:
            print("Graph is empty.  Returning empty MST.")
            return [], 0

        mst_edges = []
        mst_weight = 0
        visited = [False] * self.V
        visited[0] = True  # Start at vertex 0
        num_edges = 0

        print("\nPrim's Algorithm using naive approach:")
        while num_edges < self.V - 1:
            min_weight = sys.maxsize
            u, v = -1, -1  # Initialize to invalid values

            # Find the minimum weight edge connecting a visited vertex to an unvisited vertex
            for i in range(self.V):
                if visited[i]:
                    for j, w in self.graph[i]:
                        if not visited[j] and w < min_weight:
                            min_weight = w
                            u, v = i, j

            if u != -1 and v != -1:  # Check if a valid edge was found
                visited[v] = True
                mst_weight += min_weight
                mst_edges.append((u, v, min_weight))
                print(f"  Added edge: {u} - {v} with weight {min_weight}")
                num_edges += 1
            else:
                break # Exit if no valid edge is found.  This can happen in disconnected graphs.

        print(f"  MST Edges: {mst_edges}")
        print(f"  Total MST weight: {mst_weight}")
        return mst_edges, mst_weight

    def prim_mst_dict(self):
        """
        Prim's algorithm using a dictionary to store edge weights.  This can
        be helpful for understanding the algorithm, but the heapq approach is
        generally preferred for performance.

        Returns:
            A list of tuples representing the edges in the MST,
            and the total weight of the MST. Returns empty list and 0 if graph is empty.
        """
        if not self.graph:
            print("Graph is empty. Returning empty MST")
            return [], 0

        mst_edges = []
        mst_weight = 0
        visited = [False] * self.V
        weights = {v: sys.maxsize for v in range(self.V)}  # Initialize weights to infinity
        parents = {v: -1 for v in range(self.V)}  # Store parent of each vertex in MST
        weights[0] = 0  # Start at vertex 0 with weight 0

        print("\nPrim's Algorithm using dictionary:")
        for _ in range(self.V):
            min_weight = sys.maxsize
            u = -1

            # Find the vertex with the minimum weight among the unvisited vertices
            for v in range(self.V):
                if not visited[v] and weights[v] < min_weight:
                    min_weight = weights[v]
                    u = v

            if u == -1:
                break # Handle Disconnected Graph

            visited[u] = True
            mst_weight += weights[u]
            if parents[u] != -1:
                mst_edges.append((parents[u], u, weights[u]))
                print(f"  Added edge: {parents[u]} - {u} with weight {weights[u]}")

            for v, w in self.graph[u]:
                if not visited[v] and w < weights[v]:
                    weights[v] = w
                    parents[v] = u

        print(f"  MST Edges: {mst_edges}")
        print(f"  Total MST weight: {mst_weight}")
        return mst_edges, mst_weight

    def prim_mst_set(self):
        """
        Prim's algorithm using a set to keep track of the minimum weight edges
        available from the visited nodes.  A set is used instead of a heapq.

        Returns:
            A list of tuples representing the edges in the MST,
            and the total weight of the MST. Returns empty list and 0 if graph is empty.
        """
        if not self.graph:
            print("Graph is empty. Returning empty MST")
            return [], 0
        mst_edges = []
        mst_weight = 0
        visited = [False] * self.V
        min_edge_set = set()  # Use a set to store (weight, u, v) tuples,  no duplicates, but no auto sorting

        visited[0] = True  # Start from the first node
        # Add edges from the starting node to the min_edge_set
        for v, w in self.graph[0]:
            min_edge_set.add((w, 0, v))

        print("\nPrim's Algorithm using a set:")
        while min_edge_set:
            min_edge = min(min_edge_set)  # Find the minimum weight edge in the set.  This is the slow part.
            min_edge_set.remove(min_edge)
            weight, u, v = min_edge

            if visited[v]:
                continue  # Skip if the destination vertex is already visited

            visited[v] = True
            mst_weight += weight
            mst_edges.append((u, v, weight))
            print(f"  Added edge: {u} - {v} with weight {weight}")

            # Add new edges from the newly visited vertex
            for next_v, next_w in self.graph[v]:
                if not visited[next_v]:
                    min_edge_set.add((next_w, v, next_v))

        print(f"  MST Edges: {mst_edges}")
        print(f"  Total MST weight: {mst_weight}")
        return mst_edges, mst_weight

    def prim_mst_list(self):
        """
        Prim's algorithm using a list to store the edges.  This is similar to the
        naive approach but stores the edges to be considered in a list.

        Returns:
            A list of tuples representing the edges in the MST,
            and the total weight of the MST. Returns empty list and 0 if graph is empty.
        """
        if not self.graph:
            print("Graph is empty. Returning empty MST.")
            return [], 0

        mst_edges = []
        mst_weight = 0
        visited = [False] * self.V
        edges = []  # List to store edges (weight, u, v)
        visited[0] = True

        # Add initial edges from the starting vertex
        for v, w in self.graph[0]:
            edges.append((w, 0, v))

        print("\nPrim's Algorithm using a list:")
        while len(mst_edges) < self.V - 1:
            if not edges:
                break # Handle Disconnected Graph
            min_weight = sys.maxsize
            min_edge_index = -1

            # Find the minimum weight edge
            for i, (w, u, v) in enumerate(edges):
                if w < min_weight:
                    min_weight = w
                    min_edge_index = i

            if min_edge_index == -1:
                break # Handle Disconnected Graph

            weight, u, v = edges.pop(min_edge_index)  # Remove the minimum weight edge
            if visited[v]:
                continue  # Skip if already visited

            visited[v] = True
            mst_weight += weight
            mst_edges.append((u, v, weight))
            print(f"  Added edge: {u} - {v} with weight {weight}")

            # Add new edges from the newly visited vertex
            for next_v, next_w in self.graph[v]:
                if not visited[next_v]:
                    edges.append((next_w, v, next_v))

        print(f"  MST Edges: {mst_edges}")
        print(f"  Total MST weight: {mst_weight}")
        return mst_edges, mst_weight



if __name__ == "__main__":
    # Create a graph with 9 vertices
    g = Graph(9)
    g.add_edge(0, 1, 4)
    g.add_edge(0, 7, 8)
    g.add_edge(1, 2, 8)
    g.add_edge(1, 7, 11)
    g.add_edge(2, 3, 7)
    g.add_edge(2, 8, 2)
    g.add_edge(2, 5, 4)
    g.add_edge(3, 4, 9)
    g.add_edge(3, 5, 14)
    g.add_edge(4, 5, 10)
    g.add_edge(5, 6, 2)
    g.add_edge(6, 7, 1)
    g.add_edge(6, 8, 6)
    g.add_edge(7, 8, 7)

    # Test the Prim's algorithm implementations
    mst_edges_heapq, mst_weight_heapq = g.prim_mst_heapq()
    mst_edges_naive, mst_weight_naive = g.prim_mst_naive()
    mst_edges_dict, mst_weight_dict = g.prim_mst_dict()
    mst_edges_set, mst_weight_set = g.prim_mst_set()
    mst_edges_list, mst_weight_list = g.prim_mst_list()

    # Create a disconnected graph to test robustness
    g_disconnected = Graph(5)
    g_disconnected.add_edge(0, 1, 1)
    g_disconnected.add_edge(2, 3, 1)

    print("\nTesting with a disconnected graph:")
    mst_edges_disconnected_heapq, mst_weight_disconnected_heapq = g_disconnected.prim_mst_heapq()
    mst_edges_disconnected_naive, mst_weight_disconnected_naive = g_disconnected.prim_mst_naive()
    mst_edges_disconnected_dict, mst_weight_disconnected_dict = g_disconnected.prim_mst_dict()
    mst_edges_disconnected_set, mst_weight_disconnected_set = g_disconnected.prim_mst_set()
    mst_edges_disconnected_list, mst_weight_disconnected_list = g_disconnected.prim_mst_list()

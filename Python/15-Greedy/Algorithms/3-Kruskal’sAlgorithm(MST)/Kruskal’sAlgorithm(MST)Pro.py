# Kruskal's Algorithm for Minimum Spanning Tree (MST)

"""
Kruskal's algorithm is a greedy algorithm used to find the Minimum Spanning Tree (MST)
of a weighted, undirected graph.  A Minimum Spanning Tree is a subset of the edges
of a graph that connects all the vertices together, without any cycles and with the
minimum possible total edge weight.

Here's how Kruskal's algorithm works:

1.  Sort all the edges in non-decreasing order of their weight.
2.  Pick the smallest edge. Check if it forms a cycle with the spanning tree formed
    so far. If cycle is not formed, include this edge in the MST.
3.  Repeat step 2 until there are (V-1) edges in the MST, where V is the number of vertices
    in the graph.

Time Complexity: O(E log E) or O(E log V), where E is the number of edges and V is
                 the number of vertices.  Sorting the edges takes O(E log E) time.
                 The union-find operations (to detect cycles) take O(log V) time
                 per edge in the worst case.  Since there can be at most E edges,
                 the total time for union-find is O(E log V).  If E < V^2, then
                 log E < 2 log V, so O(E log E) is O(E log V).

Space Complexity: O(V + E), for storing the graph and auxiliary data structures.
"""

class Graph:
    def __init__(self, vertices):
        """
        Initializes the graph with the given number of vertices.

        Args:
            vertices (int): The number of vertices in the graph.
        """
        self.V = vertices  # Number of vertices
        self.graph = []  # List of edges, where each edge is a tuple (u, v, w)
        # representing an edge between vertex u and v with weight w

    def add_edge(self, u, v, w):
        """
        Adds an edge to the graph.

        Args:
            u (int): The source vertex of the edge.
            v (int): The destination vertex of the edge.
            w (int): The weight of the edge.
        """
        self.graph.append([u, v, w])

    def find_parent(self, parent, i):
        """
        Finds the parent of a vertex using path compression.  This is part of the
        Union-Find algorithm.

        Args:
            parent (list): A list representing the parent of each vertex.
            i (int): The index of the vertex for which to find the parent.

        Returns:
            int: The parent of the vertex i.
        """
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])  # Path compression

    def union(self, parent, rank, x, y):
        """
        Performs the union operation of two sets using union by rank. This is part
        of the Union-Find algorithm.  It merges the sets containing vertices x and y.

        Args:
            parent (list): A list representing the parent of each vertex.
            rank (list): A list representing the rank of each vertex.
            x (int): The index of the first set.
            y (int): The index of the second set.
        """
        xroot = self.find_parent(parent, x)
        yroot = self.find_parent(parent, y)

        # Attach smaller rank tree under root of high rank tree
        # (Union by Rank)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        # If ranks are same, then make one as root and increment
        # its rank by one
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_mst(self):
        """
        Implements Kruskal's algorithm to find the Minimum Spanning Tree (MST).

        Returns:
            list: A list of edges in the MST, where each edge is a tuple (u, v, w).
                    Returns an empty list if the graph is empty.
        """
        result = []  # This will store the result MST
        i = 0  # An index variable, used for sorted edges
        e = 0  # An index variable, used for result[]

        # Step 1:  Sort all the edges in non-decreasing order of their weight.
        self.graph = sorted(self.graph, key=lambda item: item[2])  # Sort by weight (item[2])

        parent = []
        rank = []

        # Create V subsets with single elements
        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        # Number of edges to be taken is equal to V-1
        while e < self.V - 1 and i < len(self.graph):  # Corrected loop condition
            # Step 2: Pick the smallest edge and increment the index
            # for next iteration
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find_parent(parent, u)
            y = self.find_parent(parent, v)

            # If including this edge does't cause cycle, include it
            # in result and increment the index of result for next edge
            if x != y:
                e = e + 1
                result.append((u, v, w))
                self.union(parent, rank, x, y)
            # Else discard the edge

        return result

    def print_mst(self, mst_edges):
        """
        Prints the Minimum Spanning Tree.

        Args:
            mst_edges (list): A list of edges in the MST, where each edge is a tuple (u, v, w).
        """
        if not mst_edges:
            print("Graph is empty. No MST found.")
            return

        print("Minimum Spanning Tree:")
        total_weight = 0
        for u, v, weight in mst_edges:
            print(f"{u} - {v}  Weight: {weight}")
            total_weight += weight
        print(f"Total MST Weight: {total_weight}")

# ----------------------------------------------------------------------------------------------------------------------
# 1. Network Cable Laying
#
# Problem:  A company wants to connect several offices with network cables.  The cost
#           of laying cable between each pair of offices is known.  The goal is to
#           connect all offices with the minimum total cost of cable.
#
# Solution:  Represent the offices as vertices and the cable costs as edge weights.
#            Use Kruskal's algorithm to find the MST, which represents the minimum
#            cost network connection.
# ----------------------------------------------------------------------------------------------------------------------
def network_cabling_example():
    print("\n1. Network Cable Laying Example:")
    num_offices = 5
    graph = Graph(num_offices)
    # (Office A, Office B, Cost)  (0, 1, cost)
    graph.add_edge(0, 1, 10)  # A-B
    graph.add_edge(0, 2, 6)   # A-C
    graph.add_edge(0, 3, 5)   # A-D
    graph.add_edge(1, 3, 15)  # B-D
    graph.add_edge(2, 3, 4)   # C-D
    graph.add_edge(2, 4, 8)  # C-E
    graph.add_edge(3, 4, 9)  # D-E

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

# ----------------------------------------------------------------------------------------------------------------------
# 2.  Power Grid Design
#
# Problem:  A utility company needs to build a power grid to connect several cities.
#           The cost of building a power line between each pair of cities is known.
#           The goal is to connect all cities with the minimum total cost.
#
# Solution: Represent the cities as vertices and the power line costs as edge weights.
#           Use Kruskal's algorithm to find the MST, which represents the minimum
#           cost power grid.
# ----------------------------------------------------------------------------------------------------------------------

def power_grid_design_example():
    print("\n2. Power Grid Design Example:")
    num_cities = 6
    graph = Graph(num_cities)
    # (City A, City B, Cost) (0, 1, cost)
    graph.add_edge(0, 1, 4)
    graph.add_edge(0, 2, 3)
    graph.add_edge(1, 2, 1)
    graph.add_edge(1, 3, 2)
    graph.add_edge(2, 3, 4)
    graph.add_edge(3, 4, 5)
    graph.add_edge(4, 5, 7)
    graph.add_edge(3, 5, 8)

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

# ----------------------------------------------------------------------------------------------------------------------
# 3.  Water Pipeline Network
#
# Problem:  A water company wants to build a pipeline network to connect several cities.
#           The cost of building a pipeline between each pair of cities is known.
#           The goal is to connect all cities with the minimum total cost.
#
# Solution: Represent the cities as vertices and the pipeline costs as edge weights.
#           Use Kruskal's algorithm to find the MST, which represents the minimum
#           cost pipeline network.
# ----------------------------------------------------------------------------------------------------------------------
def water_pipeline_example():
    print("\n3. Water Pipeline Network Example:")
    num_cities = 7
    graph = Graph(num_cities)
    # (City A, City B, Cost) (0, 1, cost)
    graph.add_edge(0, 1, 2)
    graph.add_edge(0, 2, 4)
    graph.add_edge(1, 2, 1)
    graph.add_edge(1, 3, 7)
    graph.add_edge(2, 4, 3)
    graph.add_edge(3, 4, 1)
    graph.add_edge(3, 5, 5)
    graph.add_edge(4, 5, 2)
    graph.add_edge(4, 6, 4)
    graph.add_edge(5, 6, 6)

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

# ----------------------------------------------------------------------------------------------------------------------
# 4.  Transportation Network Optimization
#
# Problem:  A logistics company wants to build a road network to connect several cities.
#           The cost of building a road between each pair of cities is known.
#           The goal is to connect all cities with the minimum total cost.
#
# Solution: Represent the cities as vertices and the road costs as edge weights.
#           Use Kruskal's algorithm to find the MST, which represents the minimum
#           cost road network.
# ----------------------------------------------------------------------------------------------------------------------
def transportation_network_example():
    print("\n4. Transportation Network Optimization Example:")
    num_cities = 5
    graph = Graph(num_cities)
    # (City A, City B, Cost) (0, 1, cost)
    graph.add_edge(0, 1, 3)
    graph.add_edge(0, 2, 2)
    graph.add_edge(1, 2, 5)
    graph.add_edge(1, 3, 4)
    graph.add_edge(2, 3, 6)
    graph.add_edge(2, 4, 7)
    graph.add_edge(3, 4, 1)

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

# ----------------------------------------------------------------------------------------------------------------------
# 5.  Railway Network Construction
#
# Problem:  A railway company wants to build a railway network to connect several cities.
#           The cost of building a railway line between each pair of cities is known.
#           The goal is to connect all cities with the minimum total cost.
#
# Solution: Represent the cities as vertices and the railway costs as edge weights.
#           Use Kruskal's algorithm to find the MST, which represents the minimum
#           cost railway network.
# ----------------------------------------------------------------------------------------------------------------------

def railway_network_example():
    print("\n5. Railway Network Construction Example:")
    num_cities = 4
    graph = Graph(num_cities)
    graph.add_edge(0, 1, 5)  # A-B
    graph.add_edge(0, 2, 8)  # A-C
    graph.add_edge(1, 2, 10) # B-C
    graph.add_edge(1, 3, 12) # B-D
    graph.add_edge(2, 3, 15) # C-D

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

# ----------------------------------------------------------------------------------------------------------------------
# 6.  Telecommunications Network Design
#
# Problem: A telecommunications company wants to set up a network of communication
#          towers to connect several towns. The cost of establishing a link between
#          each pair of towns is known. The goal is to connect all towns with the
#          minimum total cost.
#
# Solution: Represent the towns as vertices and the link costs as edge weights.
#           Use Kruskal's algorithm to find the MST, which represents the minimum
#           cost telecommunications network.
# ----------------------------------------------------------------------------------------------------------------------
def telecommunications_network_example():
    print("\n6. Telecommunications Network Design Example:")
    num_towns = 6
    graph = Graph(num_towns)
    graph.add_edge(0, 1, 7)  # Town A to Town B, cost 7
    graph.add_edge(0, 2, 8)  # Town A to Town C, cost 8
    graph.add_edge(1, 2, 3)  # Town B to Town C, cost 3
    graph.add_edge(1, 3, 6)  # Town B to Town D, cost 6
    graph.add_edge(2, 3, 4)  # Town C to Town D, cost 4
    graph.add_edge(2, 4, 9)  # Town C to Town E, cost 9
    graph.add_edge(3, 4, 2)  # Town D to Town E, cost 2
    graph.add_edge(3, 5, 5)  # Town D to Town F, cost 5
    graph.add_edge(4, 5, 1)  # Town E to Town F, cost 1

    mst_edges = graph.kruskal_mst()
    graph.print_mst(mst_edges)
    return mst_edges #returning for testing

if __name__ == "__main__":
    network_cabling_example()
    power_grid_design_example()
    water_pipeline_example()
    transportation_network_example()
    railway_network_example()
    telecommunications_network_example()

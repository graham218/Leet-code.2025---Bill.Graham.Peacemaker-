"""
Union-Find (Disjoint Set Union - DSU) in Python with 6 Real-World Project Implementations

This module provides implementations of the Disjoint Set Union (DSU) data structure,
also known as Union-Find, along with examples demonstrating its application in
various real-world scenarios.

DSU is a data structure that keeps track of a set of elements partitioned into a
number of disjoint (non-overlapping) subsets. It supports two main operations:

- find(element): Determines which subset a particular element is in.  This can be
  used to determine if two elements are in the same subset.
- union(set1, set2): Joins two subsets into a single subset.

Implementations:

1.  Basic Implementation (No Optimizations):  A straightforward implementation
    using a list/array as the parent array, without any path compression or
    union by rank optimizations.  This is the easiest to understand but has
    the worst-case time complexity.

2.  Path Compression:  Improves the `find` operation by making each visited node
    point directly to the root of the set. This significantly reduces the
    height of the trees and improves performance.

3.  Union by Rank:  Improves the `union` operation by attaching the shorter
    tree to the root of the taller tree.  The rank of a tree is an upper bound
    on its height.

4.  Path Compression + Union by Rank: Combines both optimizations for maximum
    performance.  This is the most commonly used and recommended approach.

5.  DSU with List of Sets:  Instead of a parent array, this implementation uses
    a dictionary where each key is a representative element of a set, and the
    value is a set containing all elements in that subset.  This provides
    more intuitive access to the elements within each set.

6.  Iterative Path Compression: A non-recursive version of path compression,
    useful in environments with limited recursion depth.

Real-World Project Implementations:

1.  Network Connectivity: Determining if two computers are in the same network.
2.  Social Network Connectivity: Checking if two users are connected in a social network.
3.  Image Processing (Segmentation): Grouping pixels into regions.
4.  Kruskal's Algorithm (Minimum Spanning Tree):  Efficiently determining if adding
    an edge would create a cycle.
5.  Circuit Network Analysis: Identifying connected components in an electrical circuit.
6.  Maze Generation: Creating random mazes by ensuring walls are removed without
    creating cycles.
"""

from typing import List, Dict, Set, Tuple


class DSU_Basic:
    """
    Basic Disjoint Set Union implementation with no optimizations.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))  # Parent array: initially, each element is its own parent

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        if self.parent[i] == i:
            return i  # If i is its own parent, it's the root
        return self.find(self.parent[i])  # Recursively find the parent's parent

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)  # Find the root of the set containing i
        root_j = self.find(j)  # Find the root of the set containing j
        if root_i != root_j:
            self.parent[root_i] = root_j  # Make one root the parent of the other


class DSU_PathCompression:
    """
    DSU implementation with path compression optimization.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to,
        with path compression.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])  # Path compression: make i point to root
        return self.parent[i]  # Return the root

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            self.parent[root_i] = root_j


class DSU_UnionByRank:
    """
    DSU implementation with union by rank optimization.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n  # Rank array: stores the rank of each root

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        if self.parent[i] == i:
            return i
        return self.find(self.parent[i])

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j, using union by rank.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:  # Attach shorter tree to taller
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i  # If ranks are equal, increment rank of one
                self.rank[root_i] += 1



class DSU_PathCompressionAndRank:
    """
    DSU implementation with both path compression and union by rank optimizations.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to,
        with path compression.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j, using union by rank.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1



class DSU_ListOfSets:
    """
    DSU implementation using a list of sets.  This provides more direct access
    to the elements within each disjoint set.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.sets: Dict[int, Set[int]] = {i: {i} for i in range(n)}  # {root: {elements}}
        self.element_to_root: Dict[int, int] = {i: i for i in range(n)} # {element: root}

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        return self.element_to_root[i]

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i != root_j:
            if len(self.sets[root_i]) < len(self.sets[root_j]):
                smaller_root, larger_root = root_i, root_j
            else:
                smaller_root, larger_root = root_j, root_i

            # Merge the smaller set into the larger set
            self.sets[larger_root].update(self.sets[smaller_root])
            del self.sets[smaller_root]

            # Update the element_to_root mapping for the merged elements
            for element in self.sets[larger_root]:
                self.element_to_root[element] = larger_root

    def get_sets(self) -> Dict[int, Set[int]]:
        """
        Returns the current sets.

        Returns:
            A dictionary representing the sets.  Keys are root elements,
            values are the sets of elements.
        """
        return self.sets



class DSU_IterativePathCompression:
    """
    DSU implementation with iterative path compression.  This avoids recursion.
    """

    def __init__(self, n: int):
        """
        Initializes the DSU data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i: int) -> int:
        """
        Finds the representative (root) of the set that element i belongs to,
        using iterative path compression.

        Args:
            i: The element to find the set for.

        Returns:
            The representative (root) of the set containing i.
        """
        path = []
        while self.parent[i] != i:
            path.append(i)
            i = self.parent[i]
        root = i  # Found the root

        # Iterative path compression: update parents along the path
        for node in path:
            self.parent[node] = root
        return root

    def union(self, i: int, j: int) -> None:
        """
        Merges the sets containing elements i and j, using union by rank.

        Args:
            i: The first element.
            j: The second element.
        """
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1



def test_dsu_implementations():
    """
    Tests the various DSU implementations with example usage and real-world scenarios.
    """
    num_elements = 10

    # 1. Basic Implementation
    print("\n1. Basic Implementation:")
    dsu_basic = DSU_Basic(num_elements)
    dsu_basic.union(0, 1)
    dsu_basic.union(2, 3)
    dsu_basic.union(1, 3)  # Merge {0, 1} and {2, 3}
    print(f"  Find(0): {dsu_basic.find(0)}")  # Output: 3 (or 0, depending on which is parent)
    print(f"  Find(1): {dsu_basic.find(1)}")  # Output: 3 (or 0)
    print(f"  Find(2): {dsu_basic.find(2)}")  # Output: 3
    print(f"  Find(4): {dsu_basic.find(4)}")  # Output: 4
    print(f"  Parents: {dsu_basic.parent}")

    # 2. Path Compression
    print("\n2. Path Compression:")
    dsu_pc = DSU_PathCompression(num_elements)
    dsu_pc.union(0, 1)
    dsu_pc.union(2, 3)
    dsu_pc.union(1, 3)
    print(f"  Find(0): {dsu_pc.find(0)}")
    print(f"  Find(1): {dsu_pc.find(1)}")
    print(f"  Find(2): {dsu_pc.find(2)}")
    print(f"  Find(4): {dsu_pc.find(4)}")
    print(f"  Parents: {dsu_pc.parent}")

    # 3. Union by Rank
    print("\n3. Union by Rank:")
    dsu_ur = DSU_UnionByRank(num_elements)
    dsu_ur.union(0, 1)
    dsu_ur.union(2, 3)
    dsu_ur.union(1, 3)
    print(f"  Find(0): {dsu_ur.find(0)}")
    print(f"  Find(1): {dsu_ur.find(1)}")
    print(f"  Find(2): {dsu_ur.find(2)}")
    print(f"  Find(4): {dsu_ur.find(4)}")
    print(f"  Parents: {dsu_ur.parent}")
    print(f"  Ranks:   {dsu_ur.rank}")

    # 4. Path Compression + Union by Rank
    print("\n4. Path Compression + Union by Rank:")
    dsu_pcr = DSU_PathCompressionAndRank(num_elements)
    dsu_pcr.union(0, 1)
    dsu_pcr.union(2, 3)
    dsu_pcr.union(1, 3)
    print(f"  Find(0): {dsu_pcr.find(0)}")
    print(f"  Find(1): {dsu_pcr.find(1)}")
    print(f"  Find(2): {dsu_pcr.find(2)}")
    print(f"  Find(4): {dsu_pcr.find(4)}")
    print(f"  Parents: {dsu_pcr.parent}")
    print(f"  Ranks:   {dsu_pcr.rank}")

    # 5. DSU with List of Sets
    print("\n5. DSU with List of Sets:")
    dsu_sets = DSU_ListOfSets(num_elements)
    dsu_sets.union(0, 1)
    dsu_sets.union(2, 3)
    dsu_sets.union(1, 3)
    dsu_sets.union(4, 5)
    print(f"  Find(0): {dsu_sets.find(0)}")
    print(f"  Find(1): {dsu_sets.find(1)}")
    print(f"  Find(2): {dsu_sets.find(2)}")
    print(f"  Find(4): {dsu_sets.find(4)}")
    print(f"  Sets:    {dsu_sets.get_sets()}")

    # 6. Iterative Path Compression
    print("\n6. Iterative Path Compression:")
    dsu_ipc = DSU_IterativePathCompression(num_elements)
    dsu_ipc.union(0, 1)
    dsu_ipc.union(2, 3)
    dsu_ipc.union(1, 3)
    print(f"  Find(0): {dsu_ipc.find(0)}")
    print(f"  Find(1): {dsu_ipc.find(1)}")
    print(f"  Find(2): {dsu_ipc.find(2)}")
    print(f"  Find(4): {dsu_ipc.find(4)}")
    print(f"  Parents: {dsu_ipc.parent}")
    print(f"  Ranks:   {dsu_ipc.rank}")

    # Real-World Examples

    # 1. Network Connectivity
    print("\nReal-World Example 1: Network Connectivity")
    num_computers = 10
    network_dsu = DSU_PathCompressionAndRank(num_computers)
    connections = [(0, 1), (2, 3), (1, 3), (4, 5), (6, 7), (8, 9)]  # Computer connections
    for c1, c2 in connections:
        network_dsu.union(c1, c2)
    print(f"  Computers 0 and 3 connected? {network_dsu.find(0) == network_dsu.find(3)}")  # True
    print(f"  Computers 0 and 4 connected? {network_dsu.find(0) == network_dsu.find(4)}")  # False

    # 2. Social Network Connectivity
    print("\nReal-World Example 2: Social Network Connectivity")
    num_users = 8
    social_dsu = DSU_PathCompressionAndRank(num_users)
    friendships = [(0, 1), (1, 2), (3, 4), (5, 6), (4, 6)]
    for u1, u2 in friendships:
        social_dsu.union(u1, u2)
    print(f"  Users 0 and 2 connected? {social_dsu.find(0) == social_dsu.find(2)}")  # True
    print(f"  Users 0 and 5 connected? {social_dsu.find(0) == social_dsu.find(5)}")  # False
    print(f"  Users 3 and 5 connected? {social_dsu.find(3) == social_dsu.find(5)}") # True

    # 3. Image Processing (Segmentation) - Simplified Example
    print("\nReal-World Example 3: Image Processing (Segmentation)")
    # Imagine a 4x4 image represented as a 1D array (pixels 0-15)
    num_pixels = 16
    segment_dsu = DSU_PathCompressionAndRank(num_pixels)
    # Similar pixels are connected (example - based on some criteria)
    similar_pixels = [(0, 1), (1, 2), (4, 5), (5, 6), (8, 9), (9, 10), (12, 13), (13, 14),
                      (0, 4), (1, 5), (2, 6), (4, 8), (5, 9), (6, 10), (8, 12), (9, 13), (10, 14)]
    for p1, p2 in similar_pixels:
        segment_dsu.union(p1, p2)
    #  pixels 0,1,2,4,5,6,8,9,10,12,13,14 are in same segment. 3, 7, 11, 15 are in their own segments
    print(f"  Pixel 0 and 5 in same segment? {segment_dsu.find(0) == segment_dsu.find(5)}")  # True
    print(f"  Pixel 0 and 15 in same segment? {segment_dsu.find(0) == segment_dsu.find(15)}")  # False

    # 4. Kruskal's Algorithm (Minimum Spanning Tree) - Simplified
    print("\nReal-World Example 4: Kruskal's Algorithm (Minimum Spanning Tree) - Simplified")
    num_nodes = 7
    mst_dsu = DSU_PathCompressionAndRank(num_nodes)
    # Edges sorted by weight (simplified for demonstration)
    edges = [(0, 1), (1, 2), (0, 3), (3, 4), (2, 5), (4, 5), (5, 6)]  # (u, v) representing edges.  In real Kruskal, these would be (u,v, weight)
    mst_edges = [] # list to store edges in Minimum Spanning Tree
    for u, v in edges:
        if mst_dsu.find(u) != mst_dsu.find(v):  # If adding edge doesn't form a cycle
            mst_dsu.union(u, v)  # Add edge to MST
            mst_edges.append((u, v))
    print(f"  Edges in MST (simplified): {mst_edges}")  #  A possible MST: [(0, 1), (1, 2), (0, 3), (3, 4), (2, 5), (5, 6)]

    # 5. Circuit Network Analysis - Simplified
    print("\nReal-World Example 5: Circuit Network Analysis - Simplified")
    num_components = 8  #  Example:  Components in a circuit
    circuit_dsu = DSU_PathCompressionAndRank(num_components)
    connections = [(0, 1), (1, 2), (3, 4), (4, 5), (6, 7)]  # Connections between components
    for c1, c2 in connections:
        circuit_dsu.union(c1, c2)
    print(f"  Components 0 and 2 connected? {circuit_dsu.find(0) == circuit_dsu.find(2)}")  # True
    print(f"  Components 0 and 5 connected? {circuit_dsu.find(0) == circuit_dsu.find(5)}")  # False
    print(f"  Components 3 and 5 connected? {circuit_dsu.find(3) == circuit_dsu.find(5)}") # True

    # 6. Maze Generation - Simplified
    print("\nReal-World Example 6: Maze Generation - Simplified")
    width = 4
    height = 4
    num_cells = width * height
    maze_dsu = DSU_PathCompressionAndRank(num_cells)
    #  Walls are represented implicitly.  We'll just remove walls between adjacent cells
    #  in a way that doesn't create cycles.
    walls_to_remove = []
    #  For simplicity, consider only right and down walls.
    for r in range(height):
        for c in range(width):
            cell = r * width + c
            if c < width - 1: # Right wall
                right_neighbor = cell + 1
                walls_to_remove.append((cell, right_neighbor))
            if r < height - 1: # Down wall
                down_neighbor = cell + width
                walls_to_remove.append((cell, down_neighbor))
    import random
    random.shuffle(walls_to_remove) # Randomize wall removal order
    removed_walls = []
    for cell1, cell2 in walls_to_remove:
        if maze_dsu.find(cell1) != maze_dsu.find(cell2):
            maze_dsu.union(cell1, cell2)
            removed_walls.append((cell1, cell2))
    print(f"  Removed Walls (Simplified): {removed_walls}") #  List of walls removed to create maze.

if __name__ == "__main__":
    test_dsu_implementations()
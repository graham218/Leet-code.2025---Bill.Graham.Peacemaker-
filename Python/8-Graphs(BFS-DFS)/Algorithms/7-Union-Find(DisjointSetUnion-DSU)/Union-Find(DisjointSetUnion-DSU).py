"""
Union-Find (Disjoint Set Union - DSU) Implementation in Python

This module provides implementations of the Union-Find data structure, also known as
Disjoint Set Union.  It's useful for problems involving connected components in graphs,
detecting cycles, and efficiently grouping elements into sets.

Five approaches are included:

1.  Basic Union-Find:  Simple implementation with path compression but no explicit rank.
2.  Union-by-Rank:  Improves efficiency by attaching smaller trees to larger ones.
3.  Path Compression: Optimizes find operation by flattening the tree structure.
4.  Union-by-Rank with Path Compression: Combines both optimizations for best performance.
5.  Iterative Path Compression: A non-recursive version of path compression

Each approach includes:
    -   Initialization:  Creating the data structure.
    -   Find:  Finding the representative (root) of the set an element belongs to.
    -   Union:  Merging two sets.
    -   isConnected: Checks if two elements are in the same set.

Example Usage:
    # Initialize Union-Find with 5 elements
    uf = UnionFind(5)  #  or use UnionFindRanked(5), etc.

    # Perform some union operations
    uf.union(0, 1)
    uf.union(2, 3)
    uf.union(1, 3)  # Merges sets {0, 1} and {2, 3}

    # Check if elements are connected
    print(uf.isConnected(0, 3))  # Output: True
    print(uf.isConnected(0, 2))  # Output: False

    # Find the representative of an element
    print(uf.find(0))      # Might output 0 or 1 or 2 or 3 (depending on path compression)
    print(uf.find(2))      # Might output 2 or 3
"""


class UnionFind:
    """
    Basic Union-Find implementation with path compression.
    """

    def __init__(self, n):
        """
        Initializes the Union-Find data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))  # Initialize each element as its own parent

    def find(self, x):
        """
        Finds the representative (root) of the set that an element belongs to,
        with path compression.

        Args:
            x: The element.

        Returns:
            The representative of the set.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]

    def union(self, x, y):
        """
        Merges the sets containing elements x and y.

        Args:
            x: The first element.
            y: The second element.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            self.parent[root_x] = root_y  # Merge by attaching one root to another

    def isConnected(self, x, y):
        """
        Checks if two elements are in the same set.

        Args:
            x: The first element.
            y: The second element.

        Returns:
            True if the elements are in the same set, False otherwise.
        """
        return self.find(x) == self.find(y)

    def count_sets(self):
        """
        Counts the number of distinct sets.

        Returns:
            The number of distinct sets.
        """
        roots = set()
        for i in range(len(self.parent)):
            roots.add(self.find(i))
        return len(roots)


class UnionFindRanked:
    """
    Union-Find implementation with union by rank and path compression.
    """

    def __init__(self, n):
        """
        Initializes the Union-Find data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n  # Initialize rank of each element to 0

    def find(self, x):
        """
        Finds the representative (root) of the set that an element belongs to,
        with path compression.

        Args:
            x: The element.

        Returns:
            The representative of the set.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]

    def union(self, x, y):
        """
        Merges the sets containing elements x and y, using union by rank.

        Args:
            x: The first element.
            y: The second element.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y  # Attach smaller rank tree to larger
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_y] = root_x  # If ranks are equal, choose either
                self.rank[root_x] += 1  # Increment the rank of the new root

    def isConnected(self, x, y):
        """
        Checks if two elements are in the same set.

        Args:
            x: The first element.
            y: The second element.

        Returns:
            True if the elements are in the same set, False otherwise.
        """
        return self.find(x) == self.find(y)

    def count_sets(self):
        """
        Counts the number of distinct sets.

        Returns:
            The number of distinct sets.
        """
        roots = set()
        for i in range(len(self.parent)):
            roots.add(self.find(i))
        return len(roots)



class UnionFindPathCompression:
    """
    Union-Find implementation with only path compression (no rank).  Included for completeness,
    though UnionFindRanked is generally preferred.  This is the same as the first
    implementation (UnionFind).
    """

    def __init__(self, n):
        """
        Initializes the Union-Find data structure.
        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))

    def find(self, x):
        """
        Finds the representative (root) of the set that an element belongs to,
        with path compression.
        Args:
            x: The element.
        Returns:
            The representative of the set.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        """
        Merges the sets containing elements x and y.
        Args:
            x: The first element.
            y: The second element.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            self.parent[root_x] = root_y

    def isConnected(self, x, y):
        """
        Checks if two elements are in the same set.
        Args:
            x: The first element.
            y: The second element.
        Returns:
            True if the elements are in the same set, False otherwise.
        """
        return self.find(x) == self.find(y)

    def count_sets(self):
        """
        Counts the number of distinct sets.
        Returns:
        The number of distinct sets
        """
        roots = set()
        for i in range(len(self.parent)):
            roots.add(self.find(i))
        return len(roots)



class UnionFindRankedPathCompression:
    """
    Union-Find implementation with both union by rank and path compression.
    This is generally the most efficient implementation.
    """

    def __init__(self, n):
        """
        Initializes the Union-Find data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        """
        Finds the representative (root) of the set that an element belongs to,
        with path compression.

        Args:
            x: The element.

        Returns:
            The representative of the set.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        """
        Merges the sets containing elements x and y, using union by rank.

        Args:
            x: The first element.
            y: The second element.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1

    def isConnected(self, x, y):
        """
        Checks if two elements are in the same set.

        Args:
            x: The first element.
            y: The second element.

        Returns:
            True if the elements are in the same set, False otherwise.
        """
        return self.find(x) == self.find(y)

    def count_sets(self):
        """
        Counts the number of distinct sets.

        Returns:
            The number of distinct sets.
        """
        roots = set()
        for i in range(len(self.parent)):
            roots.add(self.find(i))
        return len(roots)


class UnionFindIterativePC:
    """
    Union-Find implementation with iterative path compression and union by rank.
    This version of path compression uses a while loop instead of recursion.
    """

    def __init__(self, n):
        """
        Initializes the Union-Find data structure.

        Args:
            n: The number of elements.
        """
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        """
        Finds the representative (root) of the set that an element belongs to,
        using *iterative* path compression.

        Args:
            x: The element.

        Returns:
            The representative of the set.
        """
        path = []
        root = x
        while root != self.parent[root]:
            path.append(root)
            root = self.parent[root]

        # Iterative path compression:
        for node in path:
            self.parent[node] = root
        return root

    def union(self, x, y):
        """
        Merges the sets containing elements x and y, using union by rank.

        Args:
            x: The first element.
            y: The second element.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1

    def isConnected(self, x, y):
        """
        Checks if two elements are in the same set.

        Args:
            x: The first element.
            y: The second element.

        Returns:
            True if the elements are in the same set, False otherwise.
        """
        return self.find(x) == self.find(y)

    def count_sets(self):
        """
        Counts the number of distinct sets.
        Returns:
            The number of distinct sets.
        """
        roots = set()
        for i in range(len(self.parent)):
            roots.add(self.find(i))
        return len(roots)


def main():
    """
    Main function to demonstrate the usage of the Union-Find implementations.
    """
    # Example usage with UnionFindRankedPathCompression (the most efficient)
    num_elements = 6
    print(f"\n--- Union-Find with {num_elements} elements ---")
    uf = UnionFindRankedPathCompression(num_elements)

    print(f"Initial parent array: {uf.parent}")  # Print initial state
    print(f"Initial ranks: {uf.rank}")

    # Perform union operations
    uf.union(0, 1)
    print(f"After union(0, 1): parent = {uf.parent}, ranks = {uf.rank}")
    uf.union(2, 3)
    print(f"After union(2, 3): parent = {uf.parent}, ranks = {uf.rank}")
    uf.union(4, 5)
    print(f"After union(4, 5): parent = {uf.parent}, ranks = {uf.rank}")
    uf.union(1, 3)  # Merges {0, 1} and {2, 3}
    print(f"After union(1, 3): parent = {uf.parent}, ranks = {uf.rank}")
    uf.union(0, 4)
    print(f"After union(0, 4): parent = {uf.parent}, ranks = {uf.rank}")

    # Check connectivity
    print(f"Is 0 connected to 3? {uf.isConnected(0, 3)}")  # Expected: True
    print(f"Is 0 connected to 2? {uf.isConnected(0, 2)}")  # Expected: True
    print(f"Is 0 connected to 5? {uf.isConnected(0, 5)}")  # Expected: True
    print(f"Is 1 connected to 4? {uf.isConnected(1, 4)}")  # Expected: True
    print(f"Is 2 connected to 5? {uf.isConnected(2, 5)}")  # Expected: True

    # Find representatives
    print(f"Representative of 0: {uf.find(0)}")
    print(f"Representative of 1: {uf.find(1)}")
    print(f"Representative of 2: {uf.find(2)}")
    print(f"Representative of 3: {uf.find(3)}")
    print(f"Representative of 4: {uf.find(4)}")
    print(f"Representative of 5: {uf.find(5)}")

    # Count the number of sets
    print(f"Number of distinct sets: {uf.count_sets()}")  # Expected: 1


    # Example using the basic UnionFind class
    print("\n--- Basic Union-Find Example ---")
    uf_basic = UnionFind(5)
    uf_basic.union(0, 1)
    uf_basic.union(3, 4)
    print(f"Are 0 and 1 connected? {uf_basic.isConnected(0, 1)}") # True
    print(f"Are 0 and 2 connected? {uf_basic.isConnected(0, 2)}") # False
    print(f"Number of sets: {uf_basic.count_sets()}")

    # Example using UnionFindRanked
    print("\n--- Union-Find with Rank Example ---")
    uf_ranked = UnionFindRanked(5)
    uf_ranked.union(0, 1)
    uf_ranked.union(2, 3)
    uf_ranked.union(1, 3)
    print(f"Are 0 and 3 connected? {uf_ranked.isConnected(0, 3)}") # True
    print(f"Number of sets: {uf_ranked.count_sets()}")

    # Example using UnionFindIterativePC
    print("\n--- Union-Find with Iterative Path Compression ---")
    uf_iterative = UnionFindIterativePC(5)
    uf_iterative.union(0, 1)
    uf_iterative.union(2, 3)
    uf_iterative.union(1, 3)
    print(f"Are 0 and 3 connected? {uf_iterative.isConnected(0, 3)}")
    print(f"Number of sets: {uf_iterative.count_sets()}")

if __name__ == "__main__":
    main()

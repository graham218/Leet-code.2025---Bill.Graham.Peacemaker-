"""
Graphs: Number of Islands

Problem Statement:
Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands
horizontally or vertically.  You may assume all four edges of the grid are all
surrounded by water.

Example 1:
Input:
[
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input:
[
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
"""

from collections import deque
from typing import List
import threading

class Solution:
    """
    Solution class containing multiple approaches to solve the
    "Number of Islands" problem.
    """

    def __init__(self):
        """
        Constructor for the Solution class.
        Initializes an empty grid.  Useful for some methods.
        """
        self.grid = []

    def numIslands_dfs(self, grid: List[List[str]]) -> int:
        """
        1. Depth-First Search (DFS) Approach

        - Time Complexity: O(M * N), where M is the number of rows and N is the
          number of columns.  We visit each cell at most once.
        - Space Complexity: O(M * N) in the worst case, due to the recursion
          depth.  In the worst case, the entire grid is land, and the recursion
          stack will grow to the size of the grid.

        Real-world application:
        - Connected component analysis in image processing: Identifying distinct
          objects in a bitmap image.  For example, counting the number of separate
          regions in a scanned document or a satellite image.
        - Network analysis: Determining the number of disconnected sub-networks.
          For example, identifying isolated groups of computers in a network.

        Explanation:
        The DFS approach works by traversing the grid. When it finds a '1' (land),
        it starts a depth-first search to mark all connected '1's as visited.
        Each time a new '1' is found that hasn't been visited, it indicates a new
        island.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        num_islands = 0

        def dfs(r, c):
            """
            Helper function to perform depth-first search.
            """
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == '0':
                return
            grid[r][c] = '0'  # Mark the current cell as visited
            # Explore adjacent cells
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    num_islands += 1
                    dfs(r, c)  # Start DFS from the current land cell

        return num_islands

    def numIslands_bfs(self, grid: List[List[str]]) -> int:
        """
        2. Breadth-First Search (BFS) Approach

        - Time Complexity: O(M * N), where M is the number of rows and N is the
          number of columns.  Each cell is visited at most once.
        - Space Complexity: O(min(M, N)).  The maximum size of the queue is
          bounded by the smaller dimension of the grid.  In the worst case,
          where the island is very long and thin, the queue will hold at most
          min(M, N) elements.

        Real-world application:
        - Network routing: Finding the shortest path between two nodes in a
          network.  Although this problem only counts islands, BFS can be adapted
          to find the shortest path through a grid.
        - Web crawling: Exploring all linked web pages within a website.  BFS can
          systematically visit all connected pages.

        Explanation:
        The BFS approach uses a queue to explore the grid. When it finds a '1',
        it adds its neighbors to the queue and marks them as visited.  This
        process continues until all connected '1's are visited.  Each time a new
        '1' is found that hasn't been visited, it indicates a new island.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        num_islands = 0

        def bfs(r, c):
            """
            Helper function to perform breadth-first search.
            """
            queue = deque([(r, c)])
            grid[r][c] = '0'  # Mark the starting cell as visited

            while queue:
                row, col = queue.popleft()
                # Explore adjacent cells
                neighbors = [(row + 1, col), (row - 1, col), (row, col + 1), (row, col - 1)]
                for n_row, n_col in neighbors:
                    if 0 <= n_row < rows and 0 <= n_col < cols and grid[n_row][n_col] == '1':
                        grid[n_row][n_col] = '0'  # Mark neighbor as visited
                        queue.append((n_row, n_col))

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    num_islands += 1
                    bfs(r, c)  # Start BFS from the current land cell

        return num_islands

    def numIslands_union_find(self, grid: List[List[str]]) -> int:
        """
        3. Union-Find (Disjoint Set) Approach

        - Time Complexity: O(M * N * α(M * N)), where α is the Inverse Ackermann
          Function, which is very slow-growing and can be considered almost
          constant for practical input sizes.  The find operation with path
          compression takes O(α(M*N)) time.  The union operation also takes
          O(α(M*N)) time.  We perform at most M*N union operations.
        - Space Complexity: O(M * N) to store the parent array.

        Real-world application:
        - Network connectivity: Determining if two computers are in the same
          network.  Union-Find can efficiently track which nodes are connected.
        - Circuit design: Checking if two components in an electronic circuit are
          connected.
        - Social network analysis: Identifying connected components in a social
          graph.  For example, finding groups of people who are all friends
          with each other.

        Explanation:
        The Union-Find approach treats each cell as a node.  When it finds a
        '1', it unions it with its adjacent '1's.  The number of islands is
        equal to the number of disjoint sets.  Path compression and rank
        optimization are used to improve the efficiency of the Union-Find
        algorithm.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        parent = [i for i in range(rows * cols)]
        rank = [0] * (rows * cols)
        num_islands = 0

        def find(i):
            """
            Find the root of the set that i belongs to with path compression.
            """
            if parent[i] != i:
                parent[i] = find(parent[i])  # Path compression
            return parent[i]

        def union(i, j):
            """
            Union the sets that i and j belong to using rank.
            """
            root_i = find(i)
            root_j = find(j)
            if root_i != root_j:
                if rank[root_i] < rank[root_j]:
                    parent[root_i] = root_j
                elif rank[root_i] > rank[root_j]:
                    parent[root_j] = root_i
                else:
                    parent[root_j] = root_i
                    rank[root_i] += 1
                return True  # Return True if a union was performed
            return False # Return False if no union was performed

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    num_islands += 1  # Initially, every '1' is its own island
                    cell_index = r * cols + c
                    # Check and union with neighbors
                    neighbors = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
                    for n_row, n_col in neighbors:
                        if 0 <= n_row < rows and 0 <= n_col < cols and grid[n_row][n_col] == '1':
                            neighbor_index = n_row * cols + n_col
                            if union(cell_index, neighbor_index):
                                num_islands -= 1  # A union means one less island
        return num_islands

    def numIslands_iterative_dfs(self, grid: List[List[str]]) -> int:
        """
        4. Iterative Depth-First Search (DFS) Approach

        - Time Complexity: O(M * N), where M is the number of rows and N is
          the number of columns.  Each cell is visited at most once.
        - Space Complexity: O(M * N) in the worst case.  The stack can grow to
          the size of the grid if the entire grid is land.

        Real-world application:
        -  Web crawling:  Crawling a website can be done iteratively using a stack,
           similar to how we explore the grid here.
        -  Solving mazes:  Finding a path through a maze can be implemented
           iteratively with a stack.

        Explanation:
        This approach uses a stack to perform DFS iteratively.  It starts at a
        land cell ('1'), marks it as visited, and pushes its unvisited neighbors
        onto the stack.  The process continues until the stack is empty.  Each
        time a new unvisited '1' cell is encountered, it indicates a new island.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        num_islands = 0
        visited = set()

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1' and (r, c) not in visited:
                    num_islands += 1
                    stack = [(r, c)]
                    visited.add((r, c))

                    while stack:
                        curr_r, curr_c = stack.pop()
                        # Explore neighbors
                        neighbors = [(curr_r + 1, curr_c), (curr_r - 1, curr_c),
                                     (curr_r, curr_c + 1), (curr_r, curr_c - 1)]
                        for n_r, n_c in neighbors:
                            if 0 <= n_r < rows and 0 <= n_c < cols and \
                                    grid[n_r][n_c] == '1' and (n_r, n_c) not in visited:
                                stack.append((n_r, n_c))
                                visited.add((n_r, n_c))
        return num_islands

    def numIslands_optimized_bfs(self, grid: List[List[str]]) -> int:
        """
        5. Optimized Breadth-First Search (BFS) Approach

        - Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
        - Space Complexity: O(min(M, N)).  The queue size is bounded by the smaller dimension.

        Real-world application:
        -  Shortest path finding in games:  Pathfinding algorithms in games often use BFS
           or variations of it to find the shortest path for a character to move.  This
           optimized version can be helpful in reducing the memory footprint.
        -  Resource allocation in networks:  BFS can be used to find available resources
           in a network, and this optimization can help in managing the search efficiently.

        Explanation:
        This is an optimized version of the BFS approach. Instead of using a separate
        visited set, it modifies the grid itself to mark visited cells ('0').  This in-place
        modification reduces the space complexity.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        num_islands = 0

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    num_islands += 1
                    queue = deque([(r, c)])
                    grid[r][c] = '0'  # Mark as visited

                    while queue:
                        row, col = queue.popleft()
                        # Explore neighbors
                        neighbors = [(row + 1, col), (row - 1, col), (row, col + 1), (row, col - 1)]
                        for n_row, n_col in neighbors:
                            if 0 <= n_row < rows and 0 <= n_col < cols and grid[n_row][n_col] == '1':
                                grid[n_row][n_col] = '0'  # Mark as visited
                                queue.append((n_row, n_col))
        return num_islands

    def numIslands_parallel_dfs(self, grid: List[List[str]]) -> int:
        """
        6. Parallel Depth-First Search (DFS) Approach using Threading

        - Time Complexity: O(M * N / P), where P is the number of threads.  Ideally,
          the work is divided among the threads.
        - Space Complexity: O(M * N) in the worst case, similar to the standard DFS.
          The space used by each thread's stack can, in the worst case, be the
          same as the original DFS.

        Real-world application:
        -   Large-scale image processing: Processing very large images can be
            speeded up by dividing the image into tiles and processing each tile
            in parallel.
        -   Massive network analysis: Analyzing very large networks, such as social
            networks or the internet, can be parallelized to improve performance.
        -   Geographic data processing: Processing large geographical datasets,
            such as satellite imagery or map data, can be parallelized.

        Explanation:
        This approach uses Python's `threading` module to parallelize the DFS
        exploration of the grid.  The grid is divided into sections, and each
        section is processed by a separate thread.  This can significantly
        reduce the execution time for large grids.  However, due to Python's
        Global Interpreter Lock (GIL), the actual speedup might be limited for
        CPU-bound tasks.  This approach is more suitable for I/O-bound tasks.

        Args:
            grid: A 2D list of strings representing the grid.

        Returns:
            The number of islands in the grid.
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        num_islands = 0
        visited = set()
        lock = threading.Lock()  # Lock for thread-safe access to shared data

        def dfs_thread(r, c):
            """
            Helper function to perform DFS in a thread.
            """
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == '0' or (r, c) in visited:
                return
            with lock:
                visited.add((r, c))
                grid[r][c] = '0'  # Mark visited
            # Explore neighbors
            dfs_thread(r + 1, c)
            dfs_thread(r - 1, c)
            dfs_thread(r, c + 1)
            dfs_thread(r, c - 1)

        threads = []
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    with lock: # Use lock here
                        if (r,c) not in visited:
                            num_islands += 1
                            thread = threading.Thread(target=dfs_thread, args=(r, c))
                            threads.append(thread)
                            thread.start()

        for thread in threads:
            thread.join()  # Wait for all threads to complete

        return num_islands
    def numIslands(self, grid: List[List[str]], approach="dfs") -> int:
        """
        Main function to select and call the desired approach.

        Args:
            grid: The input grid.
            approach: The approach to use ("dfs", "bfs", "union_find",
                      "iterative_dfs", "optimized_bfs", or "parallel_dfs").
                      Defaults to "dfs".

        Returns:
            The number of islands.

        Raises:
            ValueError: If an invalid approach is specified.
        """
        if not grid:
            return 0

        approaches = {
            "dfs": self.numIslands_dfs,
            "bfs": self.numIslands_bfs,
            "union_find": self.numIslands_union_find,
            "iterative_dfs": self.numIslands_iterative_dfs,
            "optimized_bfs": self.numIslands_optimized_bfs,
            "parallel_dfs": self.numIslands_parallel_dfs,
        }
        if approach not in approaches:
            raise ValueError(f"Invalid approach: {approach}")
        return approaches[approach](grid)

def main():
    """
    Main function to demonstrate the usage of the Solution class
    with different input grids and approaches.
    """
    solution = Solution()

    # Test cases
    test_cases = [
        (
            [
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"],
            ],
            1,
        ),
        (
            [
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"],
            ],
            3,
        ),
        (
            [
                ["1", "1", "1"],
                ["0", "1", "0"],
                ["1", "1", "1"],
            ],
            1,
        ),
        (
            [
                ["1", "0", "1", "0", "1"],
                ["0", "1", "0", "1", "0"],
                ["1", "0", "1", "0", "1"],
            ],
            5,
        ),
        (
            [],
            0,
        ),
        (
            [["1"]],
            1
        ),
        (
            [["0"]],
            0
        )
    ]

    # Run tests for each approach
    for approach in ["dfs", "bfs", "union_find", "iterative_dfs", "optimized_bfs", "parallel_dfs"]:
        print(f"\nTesting {approach.upper()} Approach:")
        for i, (grid, expected_output) in enumerate(test_cases):
            try:
                output = solution.numIslands(grid, approach=approach)
                print(f"Test Case {i + 1}:")
                print(f"Input Grid: {grid}")
                print(f"Expected Output: {expected_output}")
                print(f"Actual Output:   {output}")
                if output == expected_output:
                    print("Result: PASS")
                else:
                    print("Result: FAIL")
            except Exception as e:
                print(f"Test Case {i + 1}:")
                print(f"Input Grid: {grid}")
                print(f"Error: {e}")

if __name__ == "__main__":
    main()

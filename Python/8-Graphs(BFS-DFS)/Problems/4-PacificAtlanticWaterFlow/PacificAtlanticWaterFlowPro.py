from typing import List, Tuple
from collections import deque

class PacificAtlanticWaterFlowAdvanced:
    """
    Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
    the water can flow from the cell to any adjacent up, down, left, or right cell with height less than or equal to it.
    Determine which cells can flow to both the Pacific ocean and the Atlantic ocean.

    This class provides several advanced approaches to solve this problem, along with real-world application examples.
    """

    def __init__(self, matrix: List[List[int]]):
        """
        Initializes the class with the input matrix.

        Args:
            matrix: A 2D list of integers representing the height of each cell.
        """
        self.matrix = matrix
        self.rows = len(matrix)
        self.cols = len(matrix[0]) if matrix else 0
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Possible directions to move: right, left, down, up

    def solve(self) -> Tuple[List[List[int]], List[List[int]], List[List[int]], List[List[int]], List[List[int]], List[List[int]]]:
        """
        Finds the cells that can reach both the Pacific and Atlantic oceans using six different approaches:
        1.  Depth-First Search (DFS) - Iterative calls
        2.  Breadth-First Search (BFS)
        3.  Optimized DFS with Memoization
        4.  Single DFS with Visited Set
        5.  Iterative DFS with Stack
        6.  Divide and Conquer Approach

        Returns:
            A tuple containing six lists of lists, where each inner list represents the row and column indices
            of cells that can reach both oceans, corresponding to the six approaches.
        """
        if not self.matrix or not self.matrix[0]:
            return [], [], [], [], [], []

        # 1. Approach 1: Depth-First Search (DFS) - Iterative calls
        pacific_reach1 = set()
        atlantic_reach1 = set()
        for r in range(self.rows):
            self._dfs(r, 0, pacific_reach1)
            self._dfs(r, self.cols - 1, atlantic_reach1)
        for c in range(self.cols):
            self._dfs(0, c, pacific_reach1)
            self._dfs(self.rows - 1, c, atlantic_reach1)
        result1 = [list(cell) for cell in pacific_reach1.intersection(atlantic_reach1)]

        # 2. Approach 2: Breadth-First Search (BFS)
        pacific_reach2 = set()
        atlantic_reach2 = set()
        self._bfs(pacific_reach2, [(r, 0) for r in range(self.rows)] + [(0, c) for c in range(1, self.cols)])
        self._bfs(atlantic_reach2, [(r, self.cols - 1) for r in range(self.rows)] + [(self.rows - 1, c) for c in range(self.cols - 1)])
        result2 = [list(cell) for cell in pacific_reach2.intersection(atlantic_reach2)]

        # 3. Approach 3: Optimized DFS with Memoization
        pacific_reach3 = set()
        atlantic_reach3 = set()
        pacific_memo = {}
        atlantic_memo = {}
        for r in range(self.rows):
            self._dfs_memo(r, 0, pacific_reach3, pacific_memo)
            self._dfs_memo(r, self.cols - 1, atlantic_reach3, atlantic_memo)
        for c in range(self.cols):
            self._dfs_memo(0, c, pacific_reach3, pacific_memo)
            self._dfs_memo(self.rows - 1, c, atlantic_reach3, atlantic_memo)
        result3 = [list(cell) for cell in pacific_reach3.intersection(atlantic_reach3)]

        # 4. Approach 4: Single DFS with Visited Set
        pacific_reach4 = set()
        atlantic_reach4 = set()

        def _single_dfs(r, c, reachable):
            if (r, c) in reachable:
                return
            reachable.add((r, c))
            for dr, dc in self.directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                    _single_dfs(nr, nc, reachable)

        for r in range(self.rows):
            _single_dfs(r, 0, pacific_reach4)
            _single_dfs(r, self.cols - 1, atlantic_reach4)
        for c in range(self.cols):
            _single_dfs(0, c, pacific_reach4)
            _single_dfs(self.rows - 1, c, atlantic_reach4)
        result4 = [list(cell) for cell in pacific_reach4.intersection(atlantic_reach4)]

        # 5. Approach 5: Iterative DFS with Stack
        pacific_reach5 = set()
        atlantic_reach5 = set()

        def _iterative_dfs(r, c, reachable):
            stack = [(r, c)]
            reachable.add((r, c))
            while stack:
                curr_r, curr_c = stack.pop()
                for dr, dc in self.directions:
                    next_r, next_c = curr_r + dr, curr_c + dc
                    if 0 <= next_r < self.rows and 0 <= next_c < self.cols and \
                            (next_r, next_c) not in reachable and self.matrix[next_r][next_c] >= self.matrix[curr_r][curr_c]:
                        reachable.add((next_r, next_c))
                        stack.append((next_r, next_c))

        for r in range(self.rows):
            _iterative_dfs(r, 0, pacific_reach5)
            _iterative_dfs(r, self.cols - 1, atlantic_reach5)
        for c in range(self.cols):
            _iterative_dfs(0, c, pacific_reach5)
            _iterative_dfs(self.rows - 1, c, atlantic_reach5)
        result5 = [list(cell) for cell in pacific_reach5.intersection(atlantic_reach5)]

        # 6. Approach 6: Divide and Conquer
        pacific_reach6 = set()
        atlantic_reach6 = set()

        def _divide_conquer(matrix, r_start, r_end, c_start, c_end, reachable):
            """
             Recursively divides the matrix and finds reachable cells.

             Args:
                matrix:  The input matrix.
                r_start: Starting row index of the submatrix.
                r_end:   Ending row index of the submatrix.
                c_start: Starting column index of the submatrix.
                c_end:   Ending column index of the submatrix.
                reachable: Set to store reachable cells.
            """
            if r_start > r_end or c_start > c_end:
                return

            # Base case: 1x1 matrix
            if r_start == r_end and c_start == c_end:
                reachable.add((r_start, c_start))
                return

            # Divide the matrix into four submatrices.
            r_mid = (r_start + r_end) // 2
            c_mid = (c_start + c_end) // 2

            # Recursively process each submatrix
            _divide_conquer(matrix, r_start, r_mid, c_start, c_mid, reachable)
            _divide_conquer(matrix, r_start, r_mid, c_mid + 1, c_end, reachable)
            _divide_conquer(matrix, r_mid + 1, r_end, c_start, c_mid, reachable)
            _divide_conquer(matrix, r_mid + 1, r_end, c_mid + 1, c_end, reachable)

            # Find reachable cells in the current submatrix.
            for r in range(r_start, r_end + 1):
                for c in range(c_start, c_end + 1):
                    if (r_start == 0 or c_start == 0 or r_end == self.rows -1 or c_end == self.cols -1):
                        self._dfs(r, c, reachable)

        _divide_conquer(self.matrix, 0, self.rows - 1, 0, self.cols - 1, pacific_reach6)
        _divide_conquer(self.matrix, 0, self.rows - 1, 0, self.cols - 1, atlantic_reach6)
        result6 = [list(cell) for cell in pacific_reach6.intersection(atlantic_reach6)]

        return result1, result2, result3, result4, result5, result6

    def _dfs(self, r: int, c: int, reachable: set) -> None:
        """
        Performs Depth-First Search to find cells reachable from a given cell.

        Args:
            r: The row index of the starting cell.
            c: The column index of the starting cell.
            reachable: A set to store the coordinates of reachable cells.
        """
        if (r, c) in reachable:
            return
        reachable.add((r, c))
        for dr, dc in self.directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                self._dfs(nr, nc, reachable)

    def _bfs(self, reachable: set, queue: List[Tuple[int, int]]) -> None:
        """
        Performs Breadth-First Search to find cells reachable from a given set of starting cells.

        Args:
            reachable: A set to store the coordinates of reachable cells.
            queue: A list of tuples, where each tuple contains the row and column indices of a starting cell.
        """
        q = deque(queue)
        while q:
            r, c = q.popleft()
            if (r, c) in reachable:
                continue
            reachable.add((r, c))
            for dr, dc in self.directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                    q.append((nr, nc))

    def _dfs_memo(self, r: int, c: int, reachable: set, memo: dict) -> None:
        """
        Performs Depth-First Search with memoization.

        Args:
            r: Row index.
            c: Column index.
            reachable: Reachable set.
            memo: Memoization dictionary.
        """
        if (r, c) in reachable:
            return
        if (r, c) in memo:
            return
        reachable.add((r, c))
        memo[(r, c)] = True
        for dr, dc in self.directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                self._dfs_memo(nr, nc, reachable, memo)



def main():
    """
    Main function to demonstrate the Pacific Atlantic Water Flow problem with example matrices and
    real-world project implementations.
    """
    # Example 1
    matrix1 = [
        [1, 2, 2, 3, 5],
        [3, 2, 3, 4, 4],
        [2, 4, 5, 3, 1],
        [6, 7, 1, 4, 5],
        [5, 1, 1, 2, 4]
    ]
    solution1 = PacificAtlanticWaterFlowAdvanced(matrix1)
    (result1_1, result1_2, result1_3, result1_4, result1_5, result1_6) = solution1.solve()

    print("Example 1:")
    print("Matrix:")
    for row in matrix1:
        print(row)
    print("DFS Result (Iterative calls):", result1_1)
    print("BFS Result:", result1_2)
    print("DFS with Memoization:", result1_3)
    print("Single DFS with Visited Set:", result1_4)
    print("Iterative DFS with Stack:", result1_5)
    print("Divide and Conquer:", result1_6)
    print("-" * 40)

    # Example 2
    matrix2 = [
        [1, 2, 3],
        [8, 9, 4],
        [7, 6, 5]
    ]
    solution2 = PacificAtlanticWaterFlowAdvanced(matrix2)
    (result2_1, result2_2, result2_3, result2_4, result2_5, result2_6) = solution2.solve()
    print("Example 2:")
    print("Matrix:")
    for row in matrix2:
        print(row)
    print("DFS Result (Iterative calls):", result2_1)
    print("BFS Result:", result2_2)
    print("DFS with Memoization:", result2_3)
    print("Single DFS with Visited Set:", result2_4)
    print("Iterative DFS with Stack:", result2_5)
    print("Divide and Conquer:", result2_6)
    print("-" * 40)

    # Example 3: Empty matrix
    matrix3 = []
    solution3 = PacificAtlanticWaterFlowAdvanced(matrix3)
    (result3_1, result3_2, result3_3, result3_4, result3_5, result3_6) = solution3.solve()
    print("Example 3: Empty Matrix")
    print("Matrix:")
    print(matrix3)
    print("DFS Result (Iterative calls):", result3_1)
    print("BFS Result:", result3_2)
    print("DFS with Memoization:", result3_3)
    print("Single DFS with Visited Set:", result3_4)
    print("Iterative DFS with Stack:", result3_5)
    print("Divide and Conquer:", result3_6)
    print("-" * 40)

    # Example 4: Single cell matrix
    matrix4 = [[5]]
    solution4 = PacificAtlanticWaterFlowAdvanced(matrix4)
    (result4_1, result4_2, result4_3, result4_4, result4_5, result4_6) = solution4.solve()
    print("Example 4: Single Cell Matrix")
    print("Matrix:")
    print(matrix4)
    print("DFS Result (Iterative calls):", result4_1)
    print("BFS Result:", result4_2)
    print("DFS with Memoization:", result4_3)
    print("Single DFS with Visited Set:", result4_4)
    print("Iterative DFS with Stack:", result4_5)
    print("Divide and Conquer:", result4_6)
    print("-" * 40)

    # Example 5: rectangular matrix
    matrix5 = [
        [1, 2, 3, 4],
        [12, 13, 14, 5],
        [11, 16, 15, 6],
        [10, 9, 8, 7]
    ]
    solution5 = PacificAtlanticWaterFlowAdvanced(matrix5)
    (result5_1, result5_2, result5_3, result5_4, result5_5, result5_6) = solution5.solve()
    print("Example 5: Rectangular Matrix")
    print("Matrix:")
    for row in matrix5:
        print(row)
    print("DFS Result (Iterative calls):", result5_1)
    print("BFS Result:", result5_2)
    print("DFS with Memoization:", result5_3)
    print("Single DFS with Visited Set:", result5_4)
    print("Iterative DFS with Stack:", result5_5)
    print("Divide and Conquer:", result5_6)
    print("-" * 40)

    print("\nReal-World Project Implementations:\n")

    print("1.  Environmental Monitoring (All Approaches):")
    print("    -   Use case: Simulate water flow in a watershed to predict flood risk and identify areas prone to contamination.")
    print("    -   The matrix represents terrain elevation, and the algorithm determines how water flows across the landscape.")
    print("    -   Different approaches can be used for validation and performance comparison in large-scale simulations.")

    print("\n2.  Urban Planning (BFS, Divide and Conquer):")
    print("    -   Use case: Model the spread of resources or pollutants in a city grid.")
    print("    -   The matrix represents city blocks and their connectivity, and the algorithm simulates how resources/pollutants spread from source points.")
    print("    -   BFS can efficiently model the spread from multiple sources, while divide and conquer can handle very large city grids.")

    print("\n3.  Network Analysis (DFS, Iterative DFS):")
    print("    -  Use case: Determine the flow of information or dependencies in a network.")
    print("    -  The matrix represents network nodes and their connections, and the algorithm identifies how information/dependencies propagate from one node to another.")
    print("    -  DFS and iterative DFS can be used to trace the paths of information flow and identify critical nodes.")

    print("\n4.  Image Processing (Single DFS, DFS with Memoization):")
    print("    -   Use case: Analyze the connectivity of regions in an image.")
    print("    -   The matrix represents pixel intensities, and the algorithm identifies connected regions based on intensity similarity.")
    print("    -   Single DFS can efficiently identify connected components, while memoization can optimize performance for large images with repeated calculations.")
if __name__ == "__main__":
    main()

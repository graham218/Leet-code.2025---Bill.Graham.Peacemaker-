from typing import List, Tuple

class PacificAtlanticWaterFlow:
    """
    Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
    the water can flow from the cell to any adjacent up, down, left, or right cell with height less than or equal to it.
    Determine which cells can flow to both the Pacific ocean and the Atlantic ocean.
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
        self.pacific_reach = set()
        self.atlantic_reach = set()
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Possible directions to move: right, left, down, up

    def solve(self) -> List[List[int]]:
        """
        Finds the cells that can reach both the Pacific and Atlantic oceans using Depth-First Search (DFS).

        Returns:
            A list of lists, where each inner list contains the row and column indices of a cell
            that can reach both oceans.
        """
        if not self.matrix or not self.matrix[0]:
            return []

        # 1. Approach 1: Depth-First Search (DFS) - Iterative calls
        self.pacific_reach = set()
        self.atlantic_reach = set()
        for r in range(self.rows):
            self.dfs(r, 0, self.pacific_reach)  # Water from Pacific can reach these cells
            self.dfs(r, self.cols - 1, self.atlantic_reach)  # Water from Atlantic can reach these cells
        for c in range(self.cols):
            self.dfs(0, c, self.pacific_reach)
            self.dfs(self.rows - 1, c, self.atlantic_reach)

        result1 = [list(cell) for cell in self.pacific_reach.intersection(self.atlantic_reach)]

        # 2. Approach 2: Breadth-First Search (BFS)
        self.pacific_reach = set()
        self.atlantic_reach = set()
        self.bfs(self.pacific_reach, [(r, 0) for r in range(self.rows)] + [(0, c) for c in range(1, self.cols)])
        self.bfs(self.atlantic_reach, [(r, self.cols - 1) for r in range(self.rows)] + [(self.rows - 1, c) for c in range(self.cols - 1)])
        result2 = [list(cell) for cell in self.pacific_reach.intersection(self.atlantic_reach)]

        # 3. Approach 3: Optimized DFS with Memoization (Not really needed here, but shown for completeness)
        self.pacific_reach = set()
        self.atlantic_reach = set()
        pacific_memo = {}
        atlantic_memo = {}

        for r in range(self.rows):
            self.dfs_memo(r, 0, self.pacific_reach, pacific_memo)
            self.dfs_memo(r, self.cols - 1, self.atlantic_reach, atlantic_memo)
        for c in range(self.cols):
            self.dfs_memo(0, c, self.pacific_reach, pacific_memo)
            self.dfs_memo(self.rows - 1, c, self.atlantic_reach, atlantic_memo)
        result3 = [list(cell) for cell in self.pacific_reach.intersection(self.atlantic_reach)]

        # 4. Approach 4: Single DFS with Visited Set
        self.pacific_reach = set()
        self.atlantic_reach = set()
        visited = set()

        def single_dfs(r, c, reachable):
            if (r, c) in reachable:
                return
            reachable.add((r, c))
            for dr, dc in self.directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                    single_dfs(nr, nc, reachable)

        for r in range(self.rows):
            single_dfs(r, 0, self.pacific_reach)
            single_dfs(r, self.cols - 1, self.atlantic_reach)
        for c in range(self.cols):
            single_dfs(0, c, self.pacific_reach)
            single_dfs(self.rows - 1, c, self.atlantic_reach)
        result4 = [list(cell) for cell in self.pacific_reach.intersection(self.atlantic_reach)]

        # 5. Approach 5: Iterative DFS with Stack
        self.pacific_reach = set()
        self.atlantic_reach = set()

        def iterative_dfs(r, c, reachable):
            stack = [(r, c)]
            reachable.add((r, c))  # Mark the starting cell as reachable
            while stack:
                curr_r, curr_c = stack.pop()
                for dr, dc in self.directions:
                    next_r, next_c = curr_r + dr, curr_c + dc
                    if 0 <= next_r < self.rows and 0 <= next_c < self.cols and \
                            (next_r, next_c) not in reachable and self.matrix[next_r][next_c] >= self.matrix[curr_r][curr_c]:
                        reachable.add((next_r, next_c))
                        stack.append((next_r, next_c))

        for r in range(self.rows):
            iterative_dfs(r, 0, self.pacific_reach)
            iterative_dfs(r, self.cols - 1, self.atlantic_reach)
        for c in range(self.cols):
            iterative_dfs(0, c, self.pacific_reach)
            iterative_dfs(self.rows - 1, c, self.atlantic_reach)
        result5 = [list(cell) for cell in self.pacific_reach.intersection(self.atlantic_reach)]

        return result1, result2, result3, result4, result5

    def dfs(self, r: int, c: int, reachable: set) -> None:
        """
        Performs Depth-First Search to find cells reachable from a given cell.

        Args:
            r: The row index of the starting cell.
            c: The column index of the starting cell.
            reachable: A set to store the coordinates of reachable cells.
        """
        if (r, c) in reachable:
            return  # If cell is already visited, stop recursion
        reachable.add((r, c))  # Mark the current cell as visited
        for dr, dc in self.directions:
            nr, nc = r + dr, c + dc  # Explore adjacent cells
            if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                self.dfs(nr, nc, reachable)  # Recurse on valid neighbors

    def bfs(self, reachable: set, queue: List[Tuple[int, int]]) -> None:
        """
        Performs Breadth-First Search to find cells reachable from a given set of starting cells.

        Args:
            reachable: A set to store the coordinates of reachable cells.
            queue: A list of tuples, where each tuple contains the row and column indices of a starting cell.
        """
        from collections import deque
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

    def dfs_memo(self, r: int, c: int, reachable: set, memo: dict) -> None:
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
        memo[(r, c)] = True # Mark as visited
        for dr, dc in self.directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.rows and 0 <= nc < self.cols and self.matrix[nr][nc] >= self.matrix[r][c]:
                self.dfs_memo(nr, nc, reachable, memo)

def main():
    """
    Main function to demonstrate the Pacific Atlantic Water Flow problem with example matrices.
    """
    # Example 1
    matrix1 = [
        [1, 2, 2, 3, 5],
        [3, 2, 3, 4, 4],
        [2, 4, 5, 3, 1],
        [6, 7, 1, 4, 5],
        [5, 1, 1, 2, 4]
    ]
    solution1 = PacificAtlanticWaterFlow(matrix1)
    result1_1, result1_2, result1_3, result1_4, result1_5 = solution1.solve()
    print("Example 1:")
    print("Matrix:")
    for row in matrix1:
        print(row)
    print("DFS Result (Iterative calls):", result1_1)
    print("BFS Result:", result1_2)
    print("DFS with Memoization:", result1_3)
    print("Single DFS with Visited Set:", result1_4)
    print("Iterative DFS with Stack:", result1_5)
    print("-" * 40)

    # Example 2
    matrix2 = [
        [1, 2, 3],
        [8, 9, 4],
        [7, 6, 5]
    ]
    solution2 = PacificAtlanticWaterFlow(matrix2)
    result2_1, result2_2, result2_3, result2_4, result2_5  = solution2.solve()
    print("Example 2:")
    print("Matrix:")
    for row in matrix2:
        print(row)
    print("DFS Result (Iterative calls):", result2_1)
    print("BFS Result:", result2_2)
    print("DFS with Memoization:", result2_3)
    print("Single DFS with Visited Set:", result2_4)
    print("Iterative DFS with Stack:", result2_5)
    print("-" * 40)

    # Example 3: Empty matrix
    matrix3 = []
    solution3 = PacificAtlanticWaterFlow(matrix3)
    if not matrix3:
        print("Example 3: Empty Matrix")
        print("Matrix:")
        print(matrix3)
        print("DFS Result (Iterative calls): []")
        print("BFS Result: []")
        print("DFS with Memoization: []")
        print("Single DFS with Visited Set: []")
        print("Iterative DFS with Stack: []")
        print("-" * 40)
        return
    result3_1, result3_2, result3_3, result3_4, result3_5 = solution3.solve()
    print("Example 3: Empty Matrix")
    print("Matrix:")
    print(matrix3)
    print("DFS Result (Iterative calls):", result3_1)
    print("BFS Result:", result3_2)
    print("DFS with Memoization:", result3_3)
    print("Single DFS with Visited Set:", result3_4)
    print("Iterative DFS with Stack:", result3_5)
    print("-" * 40)

    # Example 4: Single cell matrix
    matrix4 = [[5]]
    solution4 = PacificAtlanticWaterFlow(matrix4)
    result4_1, result4_2, result4_3, result4_4, result4_5 = solution4.solve()
    print("Example 4: Single Cell Matrix")
    print("Matrix:")
    print(matrix4)
    print("DFS Result (Iterative calls):", result4_1)
    print("BFS Result:", result4_2)
    print("DFS with Memoization:", result4_3)
    print("Single DFS with Visited Set:", result4_4)
    print("Iterative DFS with Stack:", result4_5)
    print("-" * 40)

    # Example 5: rectangular matrix
    matrix5 = [
        [1, 2, 3, 4],
        [12, 13, 14, 5],
        [11, 16, 15, 6],
        [10, 9, 8, 7]
    ]
    solution5 = PacificAtlanticWaterFlow(matrix5)
    result5_1, result5_2, result5_3, result5_4, result5_5 = solution5.solve()
    print("Example 5: Rectangular Matrix")
    print("Matrix:")
    for row in matrix5:
        print(row)
    print("DFS Result (Iterative calls):", result5_1)
    print("BFS Result:", result5_2)
    print("DFS with Memoization:", result5_3)
    print("Single DFS with Visited Set:", result5_4)
    print("Iterative DFS with Stack:", result5_5)
    print("-" * 40)

if __name__ == "__main__":
    main()

"""
Number of Islands Problem:
Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.

Approaches Implemented:
1. Depth-First Search (DFS) - Recursive
2. Depth-First Search (DFS) - Iterative
3. Breadth-First Search (BFS)
4. Union-Find (Disjoint Set)
5. Flood Fill Algorithm
"""
from collections import deque

# Approach 1: DFS Recursive
def num_islands_dfs_recursive(grid):
    """
    Counts the number of islands in a grid using recursive Depth-First Search (DFS).

    Args:
        grid (List[List[str]]): A 2D list of strings representing the grid ('1' for land, '0' for water).

    Returns:
        int: The number of islands.

    Algorithm:
        1.  If the grid is empty, return 0.
        2.  Initialize `rows` and `cols` to the dimensions of the grid.
        3.  `directions` stores the possible movements (up, down, left, right).
        4.  Define a recursive function `dfs(r, c)`:
            a.  Base case: If the current cell is out of bounds or is water ('0'), return.
            b.  Mark the current cell as visited by setting it to '0'.
            c.  Recursively call `dfs` for the four adjacent cells.
        5.  Initialize `count` to 0.
        6.  Iterate through each cell in the grid:
            a.  If the cell is land ('1'):
                i.  Increment `count`.
                ii. Call `dfs(r, c)` to explore the entire island.
        7.  Return `count`.

    Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
    Space Complexity: O(M * N) in the worst case (when the entire grid is land), due to the recursion depth.
    """
    if not grid:
        return 0

    rows, cols = len(grid), len(grid[0])
    directions = [(0,1), (1,0), (0,-1), (-1,0)]

    def dfs(r, c):
        if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == '0':
            return
        grid[r][c] = '0'  # Mark visited
        for dr, dc in directions:
            dfs(r + dr, c + dc)

    count = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                dfs(r, c)
    return count

# Approach 2: DFS Iterative
def num_islands_dfs_iterative(grid):
    """
    Counts the number of islands in a grid using iterative Depth-First Search (DFS) with a stack.

    Args:
        grid (List[List[str]]): A 2D list of strings representing the grid.

    Returns:
        int: The number of islands.

    Algorithm:
        1.  If the grid is empty, return 0.
        2.  Initialize `rows`, `cols`, and `directions`.
        3.  Initialize an empty stack and `count` to 0.
        4.  Iterate through each cell in the grid:
            a.  If the cell is land ('1'):
                i.  Increment `count`.
                ii. Push the cell's coordinates onto the stack.
                iii. While the stack is not empty:
                    1.  Pop a cell's coordinates (x, y) from the stack.
                    2.  If the cell is land ('1'):
                        a.  Mark the cell as visited ('0').
                        b.  For each neighbor:
                            i.  If the neighbor is within bounds and is land ('1'), push its coordinates onto the stack.
        5.  Return `count`.

    Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
    Space Complexity: O(M * N) in the worst case (when the entire grid is land), due to the stack.
    """
    if not grid:
        return 0

    rows, cols = len(grid), len(grid[0])
    directions = [(0,1), (1,0), (0,-1), (-1,0)]
    stack = []
    count = 0

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                stack.append((r, c))
                while stack:
                    x, y = stack.pop()
                    if grid[x][y] == '1':
                        grid[x][y] = '0'  # Mark visited
                        for dr, dc in directions:
                            nr, nc = x + dr, y + dc
                            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                                stack.append((nr, nc))
    return count

# Approach 3: BFS
def num_islands_bfs(grid):
    """
    Counts the number of islands in a grid using Breadth-First Search (BFS).

    Args:
        grid (List[List[str]]): A 2D list of strings representing the grid.

    Returns:
        int: The number of islands.

    Algorithm:
        1.  If the grid is empty, return 0.
        2.  Initialize `rows`, `cols`, and `directions`.
        3.  Initialize an empty queue and `count` to 0.
        4.  Iterate through each cell in the grid:
            a.  If the cell is land ('1'):
                i.  Increment `count`.
                ii. Enqueue the cell's coordinates.
                iii. While the queue is not empty:
                    1.  Dequeue a cell's coordinates (x, y).
                    2.  If the cell is land ('1'):
                        a.  Mark the cell as visited ('0').
                        b.  For each neighbor:
                            i.  If the neighbor is within bounds and is land ('1'), enqueue its coordinates.
        5.  Return `count`.

    Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
    Space Complexity: O(M * N) in the worst case (when the entire grid is land), due to the queue.
    """
    if not grid:
        return 0

    rows, cols = len(grid), len(grid[0])
    directions = [(0,1), (1,0), (0,-1), (-1,0)]
    queue = deque()
    count = 0

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                queue.append((r, c))
                while queue:
                    x, y = queue.popleft()
                    if grid[x][y] == '1':
                        grid[x][y] = '0'  # Mark visited
                        for dr, dc in directions:
                            nr, nc = x + dr, y + dc
                            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                                queue.append((nr, nc))
    return count

# Approach 4: Union-Find (Disjoint Set)
class UnionFind:
    """
    Represents a Union-Find (Disjoint Set) data structure.  This class is used to efficiently
    track connected components in the grid.

    Attributes:
        parent (List[int]):  A list where parent[i] stores the parent of element i.
        rank (List[int]): A list where rank[i] stores the rank (height) of the subtree rooted at i.
        count (int): The number of disjoint sets.

    Methods:
        __init__(size): Initializes the Union-Find structure with a given size.
        find(x): Finds the root (representative) of the set that element x belongs to, using path compression.
        union(x, y): Merges the sets containing elements x and y, using union by rank.
    """
    def __init__(self, size):
        """
        Initializes the Union-Find data structure.

        Args:
            size (int): The number of elements.
        """
        self.parent = list(range(size))
        self.rank = [1] * size
        self.count = 0

    def find(self, x):
        """
        Finds the root (representative) of the set that element x belongs to.
        Implements path compression for efficiency.

        Args:
            x (int): The element to find the root of.

        Returns:
            int: The root of the set containing x.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]

    def union(self, x, y):
        """
        Merges the sets containing elements x and y.
        Implements union by rank for efficiency.

        Args:
            x (int): The first element.
            y (int): The second element.
        """
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] += 1
            self.count -= 1

def num_islands_union_find(grid):
    """
    Counts the number of islands in a grid using the Union-Find (Disjoint Set) algorithm.

    Args:
        grid (List[List[str]]): A 2D list of strings representing the grid.

    Returns:
        int: The number of islands.

    Algorithm:
        1.  If the grid is empty, return 0.
        2.  Initialize `rows` and `cols`.
        3.  Create a UnionFind object with the size of the grid (rows * cols).
        4. `directions` stores the possible movements (right, down).  We only need to check right and down
           because checking left and up would duplicate work.
        5.  Iterate through each cell in the grid:
            a.  If the cell is land ('1'):
                i.  Increment the `count` in the UnionFind object.
                ii. For each neighbor (right and down):
                    1.  If the neighbor is within bounds and is land ('1'):
                        a.  Perform a union operation on the current cell and the neighbor in the UnionFind object.  The cell indices are calculated as r * cols + c.
        6.  Return the `count` from the UnionFind object, which represents the number of disjoint sets (islands).

    Time Complexity: O(M * N * α(M * N)), where α is the inverse Ackermann function, which is very slow-growing and
                     can be considered almost constant for practical input sizes.  Essentially, it's nearly O(M*N).
    Space Complexity: O(M * N) for the UnionFind data structure.
    """
    if not grid:
        return 0

    rows, cols = len(grid), len(grid[0])
    uf = UnionFind(rows * cols)
    directions = [(0,1), (1,0)]

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                uf.count += 1
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                        uf.union(r * cols + c, nr * cols + nc)
    return uf.count

# Approach 5: Flood Fill Algorithm
def num_islands_flood_fill(grid):
    """
    Counts the number of islands in a grid using the Flood Fill algorithm.  This is very similar
    to the recursive DFS approach, but it's presented here as a distinct approach for completeness.

    Args:
        grid (List[List[str]]): A 2D list of strings representing the grid.

    Returns:
        int: The number of islands.

    Algorithm:
        1.  If the grid is empty, return 0.
        2.  Initialize `rows` and `cols`.
        3.  Define a recursive function `flood_fill(r, c)`:
            a.  Base case: If the current cell is out of bounds or is water ('0'), return.
            b.  Mark the current cell as visited by setting it to '0'.
            c.  Recursively call `flood_fill` for the four adjacent cells.
        4.  Initialize `count` to 0.
        5.  Iterate through each cell in the grid:
            a.  If the cell is land ('1'):
                i.  Increment `count`.
                ii. Call `flood_fill(r, c)` to "flood" the entire island, marking all connected land cells as visited.
        6.  Return `count`.

    Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
    Space Complexity: O(M * N) in the worst case (when the entire grid is land), due to the recursion depth.
    """
    if not grid:
        return 0

    rows, cols = len(grid), len(grid[0])

    def flood_fill(r, c):
        if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == '0':
            return
        grid[r][c] = '0'  # Mark visited
        flood_fill(r+1, c)
        flood_fill(r-1, c)
        flood_fill(r, c+1)
        flood_fill(r, c-1)

    count = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                flood_fill(r, c)
    return count

# Test the functions
grid = [
    ['1', '1', '0', '0', '0'],
    ['1', '1', '0', '0', '0'],
    ['0', '0', '1', '0', '0'],
    ['0', '0', '0', '1', '1']
]

print("DFS Recursive:", num_islands_dfs_recursive([row[:] for row in grid]))
print("DFS Iterative:", num_islands_dfs_iterative([row[:] for row in grid]))
print("BFS:", num_islands_bfs([row[:] for row in grid]))
print("Union-Find:", num_islands_union_find([row[:] for row in grid]))
print("Flood Fill:", num_islands_flood_fill([row[:] for row in grid]))

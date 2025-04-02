import time
import copy

class SudokuSolver:
    """
    A class that implements six different approaches to solve Sudoku puzzles using backtracking.
    Each method aims to solve the puzzle in place, modifying the input grid.

    The approaches are:
    1.  Basic Backtracking: A straightforward recursive backtracking algorithm.
    2.  Backtracking with Forward Checking:  Improves backtracking by checking for
        domain consistency (if a value has no possible options) before recursing.
    3.  Backtracking with MRV (Minimum Remaining Values): A heuristic that selects
        the cell with the fewest possible values to fill next, reducing the branching factor.
    4.  Backtracking with MRV and Forward Checking: Combines the benefits of MRV
        and forward checking for potentially faster solving.
    5.  Backtracking with Constraint Propagation (AC-3): Uses the AC-3 algorithm
        to enforce arc consistency, further reducing the search space.
    6.  Iterative Backtracking with Stack: Solves Sudoku iteratively using a stack
        to manage the search, avoiding recursion depth limits.

    Attributes:
        grid (list[list[int]]): The Sudoku puzzle represented as a 9x9 grid of integers.
            Empty cells are represented by 0.
    """

    def __init__(self, grid):
        """
        Initializes the SudokuSolver with a 9x9 Sudoku grid.

        Args:
            grid (list[list[int]]): A 9x9 list of lists representing the Sudoku puzzle.
        """
        self.grid = grid
        self.size = 9
        self.subgrid_size = 3

    def print_grid(self, grid):
        """
        Prints the Sudoku grid in a user-friendly format.

        Args:
            grid (list[list[int]]): The Sudoku grid to print.
        """
        for r in range(self.size):
            if r % self.subgrid_size == 0 and r != 0:
                print("-" * 25)
            for c in range(self.size):
                if c % self.subgrid_size == 0 and c != 0:
                    print("|", end=" ")
                print(grid[r][c], end=" ")
            print()

    def find_empty_cell(self, grid):
        """
        Finds the first empty cell (cell with value 0) in the grid.

        Args:
            grid (list[list[int]]): The Sudoku grid to search.

        Returns:
            tuple (int, int): The row and column indices of the empty cell, or None if no empty cell is found.
        """
        for r in range(self.size):
            for c in range(self.size):
                if grid[r][c] == 0:
                    return r, c
        return None

    def is_valid(self, grid, row, col, num):
        """
        Checks if a number can be placed in a cell during the solving process.

        Args:
            grid (list[list[int]]): The Sudoku grid.
            row (int): The row index of the cell to check.
            col (int): The column index of the cell to check.
            num (int): The number to check for validity.

        Returns:
            bool: True if the number is valid in the cell, False otherwise.
        """
        # Check row and column for duplicates
        for x in range(self.size):
            if grid[row][x] == num or grid[x][col] == num:
                return False

        # Check the 3x3 subgrid for duplicates
        start_row = row - row % self.subgrid_size
        start_col = col - col % self.subgrid_size
        for r in range(start_row, start_row + self.subgrid_size):
            for c in range(start_col, start_col + self.subgrid_size):
                if grid[r][c] == num:
                    return False
        return True

    def get_possible_values(self, grid, row, col):
        """
        Gets all possible values (1-9) that can be placed in a cell.

        Args:
            grid (list[list[int]]): The Sudoku grid.
            row (int): The row index of the cell.
            col (int): The column index of the cell.

        Returns:
            list[int]: A list of possible values for the cell.
        """
        possible_values = []
        for num in range(1, self.size + 1):
            if self.is_valid(grid, row, col, num):
                possible_values.append(num)
        return possible_values

    def forward_checking(self, grid, row, col, num):
        """
        Checks if assigning a number to a cell will leave any empty cell with no possible values.

        Args:
            grid (list[list[int]]): The Sudoku grid.
            row (int): The row index of the cell.
            col (int): The column index of the cell.
            num (int): The number being assigned to the cell.

        Returns:
            bool: True if the assignment is safe, False otherwise.
        """
        temp_grid = [row[:] for row in grid]  # Create a copy to avoid modifying original grid during check.
        temp_grid[row][col] = num

        for r in range(self.size):
            for c in range(self.size):
                if temp_grid[r][c] == 0:
                    if not self.get_possible_values(temp_grid, r, c):
                        return False
        return True

    def select_mrv_cell(self, grid):
        """
        Selects the empty cell with the Minimum Remaining Values (MRV).

        Args:
            grid (list[list[int]]): The Sudoku grid.

        Returns:
            tuple (int, int): The row and column indices of the cell with the MRV, or None if no empty cell.
        """
        min_values = float('inf')
        mrv_cell = None
        for r in range(self.size):
            for c in range(self.size):
                if grid[r][c] == 0:
                    possible_values = self.get_possible_values(grid, r, c)
                    num_values = len(possible_values)
                    if num_values < min_values:
                        min_values = num_values
                        mrv_cell = (r, c)
        return mrv_cell

    def ac_3(self, grid):
        """
        Applies the AC-3 algorithm to enforce arc consistency in the Sudoku grid.
        This version initializes the queue and enforces consistency.  It's a core
        component of a constraint propagation approach.  It reduces the domains
        of variables before the search starts, not during the search.

        Args:
            grid (list[list[int]]): The Sudoku grid.
        Returns:
            bool: True if the grid is arc consistent, False otherwise.
        """
        def remove_inconsistent_values(grid, row1, col1, row2, col2):
            """
            Removes inconsistent values from the domain of cell (row1, col1) based on cell (row2, col2).
            """
            removed = False
            val1 = grid[row1][col1]
            val2 = grid[row2][col2]
            if val1 == 0 and val2 != 0:
                domain1 = self.get_possible_values(grid, row1, col1)
                if val2 in domain1:
                    domain1.remove(val2)
                    if not domain1:
                        return True # Return True if domain becomes empty
                    # No need to update grid here, as we are working with possible values, not the grid
                    removed = True
            return removed

        queue = []
        for r in range(self.size):
            for c in range(self.size):
                if grid[r][c] == 0:
                    # Add constraints for row, column, and subgrid
                    for i in range(self.size):
                        if i != c:
                            queue.append((r, c, r, i))  # Row constraint
                        if i != r:
                            queue.append((r, c, i, c))  # Column constraint

                    start_row = r - r % self.subgrid_size
                    start_col = c - c % self.subgrid_size
                    for i in range(start_row, start_row + self.subgrid_size):
                        for j in range(start_col, start_col + self.subgrid_size):
                            if (i, j) != (r, c):
                                queue.append((r, c, i, j))  # Subgrid constraint

        while queue:
            row1, col1, row2, col2 = queue.pop(0)
            if remove_inconsistent_values(grid, row1, col1, row2, col2):
                return False  # Inconsistency found

        return True  # Grid is arc consistent

    def solve_sudoku_basic(self, grid):
        """
        Solves the Sudoku puzzle using basic backtracking.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        empty_cell = self.find_empty_cell(grid)
        if not empty_cell:
            return True  # Puzzle is solved
        row, col = empty_cell

        for num in range(1, self.size + 1):
            if self.is_valid(grid, row, col, num):
                grid[row][col] = num
                if self.solve_sudoku_basic(grid):
                    return True  # Recursively solve the rest of the puzzle
                grid[row][col] = 0  # Backtrack: reset the cell
        return False  # No solution found

    def solve_sudoku_forward_checking(self, grid):
        """
        Solves the Sudoku puzzle using backtracking with forward checking.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        empty_cell = self.find_empty_cell(grid)
        if not empty_cell:
            return True
        row, col = empty_cell

        for num in range(1, self.size + 1):
            if self.is_valid(grid, row, col, num) and self.forward_checking(grid, row, col, num):
                grid[row][col] = num
                if self.solve_sudoku_forward_checking(grid):
                    return True
                grid[row][col] = 0
        return False

    def solve_sudoku_mrv(self, grid):
        """
        Solves the Sudoku puzzle using backtracking with the Minimum Remaining Values (MRV) heuristic.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        empty_cell = self.select_mrv_cell(grid)
        if not empty_cell:
            return True
        row, col = empty_cell

        possible_values = self.get_possible_values(grid, row, col)
        for num in possible_values:
            if self.is_valid(grid, row, col, num):
                grid[row][col] = num
                if self.solve_sudoku_mrv(grid):
                    return True
                grid[row][col] = 0
        return False

    def solve_sudoku_mrv_forward_checking(self, grid):
        """
        Solves the Sudoku puzzle using backtracking with MRV and forward checking.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        empty_cell = self.select_mrv_cell(grid)
        if not empty_cell:
            return True
        row, col = empty_cell

        possible_values = self.get_possible_values(grid, row, col)
        for num in possible_values:
            if self.is_valid(grid, row, col, num) and self.forward_checking(grid, row, col, num):
                grid[row][col] = num
                if self.solve_sudoku_mrv_forward_checking(grid):
                    return True
                grid[row][col] = 0
        return False

    def solve_sudoku_ac3(self, grid):
        """
        Solves the Sudoku puzzle using backtracking with AC-3 preprocessing.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        # First, enforce arc consistency
        if not self.ac_3(grid):
            return False  # The puzzle is unsolvable

        # Then, use backtracking (basic backtracking here, could also use MRV, etc.)
        return self.solve_sudoku_basic(grid) # Simplest backtracking after AC-3

    def solve_sudoku_iterative(self, grid):
        """
        Solves the Sudoku puzzle using iterative backtracking with a stack.

        Args:
            grid (list[list[int]]): The Sudoku grid to solve.

        Returns:
            bool: True if the puzzle is solved, False otherwise.
        """
        stack = []
        empty_cell = self.find_empty_cell(grid)
        if not empty_cell:
            return True  # Puzzle is solved

        row, col = empty_cell
        stack.append((row, col, 1))  # Start with the first possible number

        while stack:
            row, col, num = stack.pop()

            if num > self.size:
                grid[row][col] = 0  # Backtrack: reset the cell
                continue

            if self.is_valid(grid, row, col, num):
                grid[row][col] = num
                next_empty_cell = self.find_empty_cell(grid)
                if not next_empty_cell:
                    return True  # Puzzle is solved

                next_row, next_col = next_empty_cell
                stack.append((row, col, num + 1))  # Push current cell with next number
                stack.append((next_row, next_col, 1)) # Push the next empty cell with 1
            else:
                stack.append((row, col, num + 1))  # Try the next number in the same cell

        return False  # No solution found

if __name__ == "__main__":
    # Example Sudoku puzzle (0 represents empty cells)
    grid = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9],
    ]

    solver = SudokuSolver(grid)

    print("Original Sudoku Grid:")
    solver.print_grid(grid)

    print("\nSolving with Basic Backtracking:")
    grid_basic = copy.deepcopy(grid)  # Create a copy to avoid modifying the original
    start_time = time.time()
    if solver.solve_sudoku_basic(grid_basic):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_basic)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

    print("\nSolving with Backtracking and Forward Checking:")
    grid_forward = copy.deepcopy(grid)
    start_time = time.time()
    if solver.solve_sudoku_forward_checking(grid_forward):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_forward)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

    print("\nSolving with Backtracking and MRV:")
    grid_mrv = copy.deepcopy(grid)
    start_time = time.time()
    if solver.solve_sudoku_mrv(grid_mrv):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_mrv)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

    print("\nSolving with Backtracking, MRV, and Forward Checking:")
    grid_mrv_forward = copy.deepcopy(grid)
    start_time = time.time()
    if solver.solve_sudoku_mrv_forward_checking(grid_mrv_forward):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_mrv_forward)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

    print("\nSolving with Backtracking and AC-3:")
    grid_ac3 = copy.deepcopy(grid)
    start_time = time.time()
    if solver.solve_sudoku_ac3(grid_ac3):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_ac3)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

    print("\nSolving with Iterative Backtracking:")
    grid_iterative = copy.deepcopy(grid)
    start_time = time.time()
    if solver.solve_sudoku_iterative(grid_iterative):
        end_time = time.time()
        print("Solved Grid:")
        solver.print_grid(grid_iterative)
        print(f"Time taken: {end_time - start_time:.4f} seconds")
    else:
        print("No solution exists.")

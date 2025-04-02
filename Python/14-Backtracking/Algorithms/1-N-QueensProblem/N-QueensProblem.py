"""
N-Queens Problem:

The N-Queens problem is a classic puzzle where you need to place N chess queens on an N x N chessboard
such that no two queens attack each other. This means no two queens can be in the same row,
column, or diagonal.

This code provides five different approaches to solving the N-Queens problem using backtracking:

1.  **Simple Backtracking:** A basic recursive backtracking approach.
2.  **Backtracking with Pruning:** Improves efficiency by checking for conflicts before placing a queen.
3.  **Backtracking with Forward Checking:** Further optimization by checking for future conflicts.
4.  **Backtracking with Bit Manipulation:** Uses bitwise operations for very efficient conflict checking.
5. **Iterative Backtracking:** Uses a stack to avoid recursion.

Each approach will:
-   Find all possible solutions to the N-Queens problem.
-   Print the number of solutions found.
-   Print one of the solutions in a user-friendly format ('.' for empty square, 'Q' for queen).

"""

def is_safe(board, row, col, n):
    """
    Checks if it's safe to place a queen at board[row][col].

    Args:
        board: The current state of the chessboard (list of lists).
        row: The row to check.
        col: The column to check.
        n: The size of the board.

    Returns:
        True if it's safe to place a queen, False otherwise.
    """
    # Check the column
    for i in range(row):
        if board[i][col] == 'Q':
            return False

    # Check the left diagonal
    for i, j in zip(range(row - 1, -1, -1), range(col - 1, -1, -1)):
        if board[i][j] == 'Q':
            return False

    # Check the right diagonal
    for i, j in zip(range(row - 1, -1, -1), range(col + 1, n)):
        if board[i][j] == 'Q':
            return False

    return True

def solve_n_queens_simple(n):
    """
    1. Simple Backtracking:
    A basic recursive backtracking approach to solve the N-Queens problem.

    Args:
        n: The size of the chessboard.

    Returns:
        A list of all possible solutions.  Each solution is a list of queen positions,
        where each position is the column index of the queen in that row.
        Returns an empty list if no solutions are found.
    """
    solutions = []
    board = [['.' for _ in range(n)] for _ in range(n)]

    def backtrack(row):
        if row == n:
            # Found a solution, store it
            solution = []
            for r in range(n):
                for c in range(n):
                    if board[r][c] == 'Q':
                        solution.append(c)
                        break
            solutions.append(solution)
            return

        for col in range(n):
            if is_safe(board, row, col, n):
                board[row][col] = 'Q'
                backtrack(row + 1)
                board[row][col] = '.'  # Backtrack: remove the queen

    backtrack(0)
    return solutions
def solve_n_queens_pruning(n):
    """
    2. Backtracking with Pruning:
    Improves efficiency by checking for conflicts before placing a queen.

    Args:
        n: The size of the chessboard.

    Returns:
        A list of all possible solutions.
    """
    solutions = []
    board = [['.' for _ in range(n)] for _ in range(n)]

    def is_safe_pruning(board, row, col, n, row_placements):
        """
        Check if a position is safe, given the row placements already made.
        """
        # Check column
        if any(board[i][col] == 'Q' for i in range(row)):
            return False

        # Check diagonals
        for i, j in zip(range(row - 1, -1, -1), range(col - 1, -1, -1)):
            if board[i][j] == 'Q':
                return False
        for i, j in zip(range(row - 1, -1, -1), range(col + 1, n)):
            if board[i][j] == 'Q':
                return False
        return True

    def backtrack(row):
        if row == n:
            solution = []
            for r in range(n):
                for c in range(n):
                    if board[r][c] == 'Q':
                        solution.append(c)
                        break
            solutions.append(solution)
            return

        for col in range(n):
            if is_safe_pruning(board, row, col, n, []):
                board[row][col] = 'Q'
                backtrack(row + 1)
                board[row][col] = '.'

    backtrack(0)
    return solutions

def solve_n_queens_forward_checking(n):
    """
    3. Backtracking with Forward Checking:
    Further optimization by checking for future conflicts.

    Args:
        n: The size of the chessboard.

    Returns:
        A list of all possible solutions.
    """
    solutions = []
    board = [['.' for _ in range(n)] for _ in range(n)]
    rows = [True] * n  # available rows
    cols = [True] * n  # available columns
    diag1 = [True] * (2 * n - 1)  # available diagonals (row + col)
    diag2 = [True] * (2 * n - 1)  # available diagonals (row - col + n - 1)

    def is_safe_forward(row, col, n):
        """Check with forward checking."""
        return rows[row] and cols[col] and diag1[row + col] and diag2[row - col + n - 1]

    def backtrack(row):
        if row == n:
            solution = []
            for r in range(n):
                for c in range(n):
                    if board[r][c] == 'Q':
                        solution.append(c)
                        break
            solutions.append(solution)
            return

        for col in range(n):
            if is_safe_forward(row, col, n):
                board[row][col] = 'Q'
                rows[row] = False
                cols[col] = False
                diag1[row + col] = False
                diag2[row - col + n - 1] = False
                backtrack(row + 1)
                board[row][col] = '.'
                rows[row] = True
                cols[col] = True
                diag1[row + col] = True
                diag2[row - col + n - 1] = True

    backtrack(0)
    return solutions

def solve_n_queens_bit_manipulation(n):
    """
    4. Backtracking with Bit Manipulation:
    Uses bitwise operations for very efficient conflict checking.

    Args:
        n: The size of the chessboard.

    Returns:
        A list of all possible solutions.
    """
    solutions = []

    def backtrack(row, cols, left_diags, right_diags, board):
        if row == n:
            solution = []
            for r in range(n):
                for c in range(n):
                    if board[r][c] == 'Q':
                        solution.append(c)
                        break
            solutions.append(solution)
            return

        available_positions = ((1 << n) - 1) & ~(cols | left_diags | right_diags)  # Available positions in the current row

        while available_positions:
            # Get the rightmost available position
            p = available_positions & -available_positions
            col = bin(p - 1).count('1') #convert the bit to column number
            board[row][col] = 'Q'
            backtrack(
                row + 1,
                cols | p,
                (left_diags | p) << 1,
                (right_diags | p) >> 1,
                board
            )
            board[row][col] = '.' # Backtrack
            available_positions &= ~p  # Remove the current position

    board = [['.' for _ in range(n)] for _ in range(n)]
    backtrack(0, 0, 0, 0, board)
    return solutions

def solve_n_queens_iterative(n):
    """
    5. Iterative Backtracking:
    Uses a stack to avoid recursion.

    Args:
        n: The size of the chessboard.

    Returns:
        A list of all possible solutions.
    """
    solutions = []
    stack = [(0, 0, [], [['.' for _ in range(n)] for _ in range(n)])]  # (row, col, current_solution, board)

    while stack:
        row, col, current_solution, board = stack.pop()

        if row == n:
            solutions.append(current_solution)
            continue

        for c in range(n):
            if is_safe(board, row, c, n):
                new_board = [row[:] for row in board]  # Create a copy
                new_board[row][c] = 'Q'
                stack.append((row + 1, 0, current_solution + [c], new_board))
    return solutions

def print_solution(solution, n):
    """
    Prints a single solution in a user-friendly format.

    Args:
        solution: A list representing a single solution (column positions of queens).
        n: The size of the board.
    """
    for row in range(n):
        line = ['.'] * n
        line[solution[row]] = 'Q'
        print(' '.join(line))

if __name__ == "__main__":
    n = 8  # Change this to the desired board size

    print(f"\nN-Queens Problem with N = {n}\n")

    print("\n1. Simple Backtracking:")
    solutions_simple = solve_n_queens_simple(n)
    print(f"Number of solutions: {len(solutions_simple)}")
    if solutions_simple:
        print("One possible solution:")
        print_solution(solutions_simple[0], n)

    print("\n2. Backtracking with Pruning:")
    solutions_pruning = solve_n_queens_pruning(n)
    print(f"Number of solutions: {len(solutions_pruning)}")
    if solutions_pruning:
        print("One possible solution:")
        print_solution(solutions_pruning[0], n)

    print("\n3. Backtracking with Forward Checking:")
    solutions_forward = solve_n_queens_forward_checking(n)
    print(f"Number of solutions: {len(solutions_forward)}")
    if solutions_forward:
        print("One possible solution:")
        print_solution(solutions_forward[0], n)

    print("\n4. Backtracking with Bit Manipulation:")
    solutions_bit = solve_n_queens_bit_manipulation(n)
    print(f"Number of solutions: {len(solutions_bit)}")
    if solutions_bit:
        print("One possible solution:")
        print_solution(solutions_bit[0], n)

    print("\n5. Iterative Backtracking:")
    solutions_iterative = solve_n_queens_iterative(n)
    print(f"Number of solutions: {len(solutions_iterative)}")
    if solutions_iterative:
        print("One possible solution:")
        print_solution(solutions_iterative[0], n)

import time
from copy import deepcopy

# Sample Sudoku board (0 represents empty cells)
sample_board = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

def print_board(board):
    """Helper function to print the Sudoku board"""
    for i in range(len(board)):
        if i % 3 == 0 and i != 0:
            print("- - - - - - - - - - -")
        for j in range(len(board[0])):
            if j % 3 == 0 and j != 0:
                print("|", end=" ")
            print(board[i][j] if board[i][j] != 0 else ".", end=" ")
        print()

def find_empty(board):
    """Find the next empty cell in the board (row, col)"""
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return (i, j)
    return None

# Approach 1: Basic Backtracking
def solve_sudoku_basic(board):
    """Basic backtracking approach without any optimizations"""
    empty = find_empty(board)
    if not empty:
        return True  # Puzzle solved

    row, col = empty

    for num in range(1, 10):
        if is_valid(board, num, (row, col)):
            board[row][col] = num

            if solve_sudoku_basic(board):
                return True

            board[row][col] = 0  # Backtrack

    return False

# Approach 2: Backtracking with MRV (Minimum Remaining Values)
def solve_sudoku_mrv(board):
    """Backtracking with Minimum Remaining Values heuristic"""
    empty = find_empty_mrv(board)
    if not empty:
        return True

    row, col = empty

    for num in get_possible_numbers(board, row, col):
        board[row][col] = num

        if solve_sudoku_mrv(board):
            return True

        board[row][col] = 0

    return False

def find_empty_mrv(board):
    """Find empty cell with minimum remaining values (MRV)"""
    min_options = 10
    best_cell = None

    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                options = len(get_possible_numbers(board, i, j))
                if options < min_options:
                    min_options = options
                    best_cell = (i, j)

    return best_cell

def get_possible_numbers(board, row, col):
    """Get possible numbers for a cell based on current board state"""
    used_numbers = set()

    # Check row and column
    for i in range(9):
        used_numbers.add(board[row][i])
        used_numbers.add(board[i][col])

    # Check 3x3 box
    box_row = (row // 3) * 3
    box_col = (col // 3) * 3
    for i in range(3):
        for j in range(3):
            used_numbers.add(board[box_row + i][box_col + j])

    return [num for num in range(1, 10) if num not in used_numbers]

# Approach 3: Backtracking with Forward Checking
def solve_sudoku_forward(board):
    """Backtracking with forward checking"""
    empty = find_empty(board)
    if not empty:
        return True

    row, col = empty

    for num in range(1, 10):
        if is_valid(board, num, (row, col)):
            board[row][col] = num

            # Forward checking: remove num from neighbors' domains
            if forward_check(board, row, col, num):
                if solve_sudoku_forward(board):
                    return True

            board[row][col] = 0  # Backtrack

    return False

def forward_check(board, row, col, num):
    """Check if assigning num to (row,col) leaves no empty domains"""
    # Check row
    for j in range(9):
        if board[row][j] == 0 and j != col:
            if not get_possible_numbers(board, row, j):
                return False

    # Check column
    for i in range(9):
        if board[i][col] == 0 and i != row:
            if not get_possible_numbers(board, i, col):
                return False

    # Check 3x3 box
    box_row = (row // 3) * 3
    box_col = (col // 3) * 3
    for i in range(3):
        for j in range(3):
            if board[box_row + i][box_col + j] == 0 and not (box_row + i == row and box_col + j == col):
                if not get_possible_numbers(board, box_row + i, box_col + j):
                    return False

    return True

# Approach 4: Backtracking with Arc Consistency (AC-3)
def solve_sudoku_ac3(board):
    """Backtracking with Arc Consistency (AC-3) algorithm"""
    # Initialize domains
    domains = {}
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                domains[(i, j)] = set(range(1, 10))
            else:
                domains[(i, j)] = {board[i][j]}

    # Run AC-3 to reduce domains
    if not ac3(board, domains):
        return False

    return backtrack_ac3(board, domains)

def backtrack_ac3(board, domains):
    """Backtracking with reduced domains from AC-3"""
    empty = find_empty(board)
    if not empty:
        return True

    row, col = empty

    for num in list(domains[(row, col)]):
        board[row][col] = num
        old_domains = deepcopy(domains)
        domains[(row, col)] = {num}

        # Propagate constraints
        if ac3(board, domains) and backtrack_ac3(board, domains):
            return True

        # Restore domains if failed
        board[row][col] = 0
        domains = old_domains

    return False

def ac3(board, domains):
    """AC-3 algorithm for constraint propagation"""
    queue = []

    # Initialize queue with all constraints
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                # Add row constraints
                for k in range(9):
                    if k != j and board[i][k] == 0:
                        queue.append(((i, j), (i, k)))
                # Add column constraints
                for k in range(9):
                    if k != i and board[k][j] == 0:
                        queue.append(((i, j), (k, j)))
                # Add box constraints
                box_row = (i // 3) * 3
                box_col = (j // 3) * 3
                for x in range(3):
                    for y in range(3):
                        cell = (box_row + x, box_col + y)
                        if cell != (i, j) and board[cell[0]][cell[1]] == 0:
                            queue.append(((i, j), cell))

    while queue:
        (xi, xj), (yi, yj) = queue.pop(0)
        if revise(domains, (xi, xj), (yi, yj)):
            if not domains[(xi, xj)]:
                return False
            # Add new constraints to queue
            # Row neighbors
            for k in range(9):
                if k != xj and board[xi][k] == 0 and k != yj:
                    queue.append(((xi, k), (xi, xj)))
            # Column neighbors
            for k in range(9):
                if k != xi and board[k][xj] == 0 and k != yi:
                    queue.append(((k, xj), (xi, xj)))
            # Box neighbors
            box_row = (xi // 3) * 3
            box_col = (xj // 3) * 3
            for x in range(3):
                for y in range(3):
                    cell = (box_row + x, box_col + y)
                    if cell != (xi, xj) and board[cell[0]][cell[1]] == 0 and cell != (yi, yj):
                        queue.append((cell, (xi, xj)))

    return True

def revise(domains, xi, xj):
    """Revise domains based on constraints"""
    revised = False
    for x in list(domains[xi]):
        # If no value in xj's domain satisfies the constraint (x != y)
        if all(x == y for y in domains[xj]):
            domains[xi].remove(x)
            revised = True
    return revised

# Approach 5: Backtracking with Naked Singles
def solve_sudoku_naked_singles(board):
    """Backtracking that first fills in naked singles (cells with only one possible value)"""
    while True:
        naked_single_found = False
        for i in range(9):
            for j in range(9):
                if board[i][j] == 0:
                    possible = get_possible_numbers(board, i, j)
                    if len(possible) == 1:
                        board[i][j] = possible[0]
                        naked_single_found = True

        if not naked_single_found:
            break

    # Now proceed with regular backtracking
    empty = find_empty(board)
    if not empty:
        return True

    row, col = empty

    for num in get_possible_numbers(board, row, col):
        board[row][col] = num

        if solve_sudoku_naked_singles(board):
            return True

        board[row][col] = 0

    return False

# Common helper function
def is_valid(board, num, pos):
    """Check if placing num at pos is valid"""
    row, col = pos

    # Check row
    for j in range(9):
        if board[row][j] == num and col != j:
            return False

    # Check column
    for i in range(9):
        if board[i][col] == num and row != i:
            return False

    # Check 3x3 box
    box_row = (row // 3) * 3
    box_col = (col // 3) * 3
    for i in range(3):
        for j in range(3):
            if board[box_row + i][box_col + j] == num and (box_row + i != row or box_col + j != col):
                return False

    return True

# Test all approaches
def test_approach(approach_name, solver_func):
    print(f"\nSolving with {approach_name}...")
    board = deepcopy(sample_board)
    print("\nInitial board:")
    print_board(board)

    start_time = time.time()
    if solver_func(board):
        print("\nSolved board:")
        print_board(board)
    else:
        print("\nNo solution exists!")

    elapsed = time.time() - start_time
    print(f"Time taken: {elapsed:.4f} seconds")

if __name__ == "__main__":
    # Test all approaches
    test_approach("Basic Backtracking", solve_sudoku_basic)
    test_approach("Backtracking with MRV", solve_sudoku_mrv)
    test_approach("Backtracking with Forward Checking", solve_sudoku_forward)
    test_approach("Backtracking with AC-3", solve_sudoku_ac3)
    test_approach("Backtracking with Naked Singles", solve_sudoku_naked_singles)
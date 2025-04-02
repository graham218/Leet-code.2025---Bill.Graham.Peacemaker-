def solve_word_search(board, word):
    """
    This function serves as a wrapper to call different word search solving methods.
    It takes the board and the word to search as input and prints the result
    of each approach.

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.
    """
    if not board or not board[0] or not word:
        print("Invalid input: Board or word is empty.")
        return

    print("Word Search Board:")
    for row in board:
        print(row)
    print(f"Searching for word: {word}")

    # Call each of the word search solving methods and print their results
    print("\nApproach 1: Using a Stack (Iterative Backtracking)")
    result1 = find_word_iterative_stack(board, word)
    print(f"Word found: {result1}")

    print("\nApproach 2: Recursive Backtracking with Visited Set")
    result2 = find_word_recursive_visited(board, word)
    print(f"Word found: {result2}")

    print("\nApproach 3: Recursive Backtracking with Modified Board")
    result3 = find_word_recursive_modify(board, word)
    print(f"Word found: {result3}")

    print("\nApproach 4: Optimized Recursive Backtracking")
    result4 = find_word_optimized(board, word)
    print(f"Word found: {result4}")

    print("\nApproach 5: Backtracking with explicit path")
    result5 = find_word_with_path(board, word)
    print(f"Word found: {result5[0]}, Path: {result5[1]}")



# Approach 1: Iterative Backtracking using a Stack
def find_word_iterative_stack(board, word):
    """
    Iteratively searches for the word in the board using a stack.  This avoids
    recursion and uses a stack to keep track of the path.

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.

    Returns:
        True if the word is found, False otherwise.
    """
    rows, cols = len(board), len(board[0])
    stack = []

    for r in range(rows):
        for c in range(cols):
            if board[r][c] == word[0]:
                stack.append((r, c, 0))  # (row, col, word_index)

                while stack:
                    curr_r, curr_c, curr_index = stack.pop()

                    if curr_index == len(word) - 1:
                        return True

                    for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                        new_r, new_c = curr_r + dr, curr_c + dc
                        if 0 <= new_r < rows and 0 <= new_c < cols and \
                                board[new_r][new_c] == word[curr_index + 1]:
                            stack.append((new_r, new_c, curr_index + 1))
    return False



# Approach 2: Recursive Backtracking with Visited Set
def find_word_recursive_visited(board, word):
    """
    Recursively searches for the word in the board using a visited set to
    keep track of the cells that have been visited in the current path.

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.

    Returns:
        True if the word is found, False otherwise.
    """
    rows, cols = len(board), len(board[0])
    visited = set()

    def backtrack(r, c, index):
        if index == len(word):
            return True
        if r < 0 or r >= rows or c < 0 or c >= cols or \
                (r, c) in visited or board[r][c] != word[index]:
            return False

        visited.add((r, c))
        for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if backtrack(r + dr, c + dc, index + 1):
                return True
        visited.remove((r, c))  # Backtrack: remove the cell from visited
        return False

    for r in range(rows):
        for c in range(cols):
            if backtrack(r, c, 0):
                return True
    return False



# Approach 3: Recursive Backtracking with Modified Board
def find_word_recursive_modify(board, word):
    """
    Recursively searches for the word in the board by temporarily modifying
    the board itself (changing visited cells to a special character,
    and then restoring them).

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.

    Returns:
        True if the word is found, False otherwise.
    """
    rows, cols = len(board), len(board[0])

    def backtrack(r, c, index):
        if index == len(word):
            return True
        if r < 0 or r >= rows or c < 0 or c >= cols or board[r][c] != word[index]:
            return False

        temp = board[r][c]  # Store the original character
        board[r][c] = '#'    # Mark as visited
        for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if backtrack(r + dr, c + dc, index + 1):
                return True
        board[r][c] = temp  # Restore the original character (backtrack)
        return False

    for r in range(rows):
        for c in range(cols):
            if backtrack(r, c, 0):
                return True
    return False


# Approach 4: Optimized Recursive Backtracking
def find_word_optimized(board, word):
    """
    An optimized recursive approach that combines the benefits of the
    previous approaches.  It's similar to the visited set approach,
    but avoids creating a new set on each recursive call.

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.

    Returns:
        True if the word is found, False otherwise.
    """
    rows, cols = len(board), len(board[0])

    def backtrack(r, c, index, visited):
        if index == len(word):
            return True
        if r < 0 or r >= rows or c < 0 or c >= cols or (r, c) in visited or board[r][c] != word[index]:
            return False

        visited.add((r, c))
        for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if backtrack(r + dr, c + dc, index + 1, visited):
                return True
        visited.remove((r, c))  # Backtrack
        return False

    for r in range(rows):
        for c in range(cols):
            if backtrack(r, c, 0, set()):
                return True
    return False

# Approach 5: Backtracking with Explicit Path
def find_word_with_path(board, word):
    """
    Finds the word and returns the path taken to find it.

    Args:
        board: A list of lists of characters representing the game board.
        word: The string to search for in the board.

    Returns:
        A tuple: (True/False, list of tuples (row, col))
        The boolean indicates if the word was found, and the list
        contains the coordinates of the path if found.
    """
    rows, cols = len(board), len(board[0])

    def backtrack(r, c, index, path):
        if index == len(word):
            return True, path
        if r < 0 or r >= rows or c < 0 or c >= cols or board[r][c] != word[index]:
            return False, []

        path.append((r, c))
        temp = board[r][c]
        board[r][c] = '#' # Mark visited for current path.  Important for finding *a* path, not all paths.
        for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            found, result_path = backtrack(r + dr, c + dc, index + 1, path)
            if found:
                board[r][c] = temp # Restore on the way *out* after finding a solution
                return True, result_path
        path.pop()
        board[r][c] = temp # Restore on the way *out* after NOT finding a solution
        return False, []

    for r in range(rows):
        for c in range(cols):
            found, path = backtrack(r, c, 0, [])
            if found:
                return True, path
    return False, []



if __name__ == "__main__":
    # Example board and word to search
    board = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    word = "ABCCED"
    solve_word_search(board, word)

    board2 = [
        ['a', 'a']
    ]
    word2 = "aa"
    solve_word_search(board2, word2)

    board3 = [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]
    word3 = "SEE"
    solve_word_search(board3, word3)

    board4 = [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]
    word4 = "ABCESCFADEES"
    solve_word_search(board4, word4)

    board5 = [
        ['a','b','c'],
        ['d','e','f'],
        ['g','h','i']
    ]
    word5 = "abcdefghi"
    solve_word_search(board5, word5)

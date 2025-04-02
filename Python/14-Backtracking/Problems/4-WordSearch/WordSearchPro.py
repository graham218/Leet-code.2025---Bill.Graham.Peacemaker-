"""
Word Search Problem:

Given an m x n grid of characters board and a string word, determine if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example:

board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED"  -> Returns True
word = "SEE"     -> Returns True
word = "ABCB"    -> Returns False

Different Approaches:

1.  Backtracking with Explicit Stack (Iterative):
    * Uses a stack to keep track of the path.
    * Manually pushes and pops coordinates and indices.
    * More verbose but shows the backtracking process clearly.

2.  Backtracking with Recursion and Visited Set:
    * Uses recursion to explore possible paths.
    * Uses a set to keep track of visited cells in the current path.
    * Slightly more concise than the explicit stack approach.

3.  Backtracking with Recursion and In-Place Modification:
    * Uses recursion to explore possible paths.
    * Modifies the board in-place (temporarily changes visited cells) to track the path.
    * Restores the board after the recursion.  This is often claimed to be faster, but the difference is usually small.
    * This approach modifies the original input, which may not be desirable in all applications.

4.  Backtracking with Recursion and Optimized Visited Check
    * Similar to #2, but optimizes the visited check by combining it with the board bounds check.

5. Backtracking with Recursion and Generator (Conceptual):
    * Uses a generator to yield possible paths.  This is more of a conceptual example,
    * as it doesn't directly solve the "Word Search" problem, but illustrates how generators
    * could be used in a backtracking context.  It's not a full, working solution.

6. Backtracking with Recursion and Early Termination:
    * Improves the standard recursive backtracking by adding a check to stop searching
    * as soon as a match is found.  This avoids unnecessary exploration of the search space.
"""

def solve_word_search(board, word, approach=1):
    """
    Solves the Word Search problem using the specified approach.

    Args:
        board: The 2D board of characters.
        word: The word to search for.
        approach: The approach to use (1-6).

    Returns:
        True if the word exists in the board, False otherwise.
    """
    if not board or not word:
        return False

    rows, cols = len(board), len(board[0])
    word_len = len(word)

    def is_valid(r, c):
        return 0 <= r < rows and 0 <= c < cols

    def search_word(r, c, word_index, visited=None): # Added visited as parameter, initialized in main loop for approach 5
        """
        Recursive helper function to search for the word.
        """
        if visited is None:
            visited = set()

        if approach in [1, 2, 3, 4]:
            if word_index == word_len:
                return True

            if not is_valid(r, c) or board[r][c] != word[word_index]:
                return False
        elif approach == 6: #Early Termination Approach
            if word_index == word_len:
                return True

            if not is_valid(r, c) or board[r][c] != word[word_index]:
                return False

        if approach == 1:
            stack.append((r, c, word_index))
            visited.add((r, c))

            while stack:
                curr_r, curr_c, curr_index = stack[-1]

                if curr_index == word_len:
                    return True

                found_next = False
                for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                    next_r, next_c = curr_r + dr, curr_c + dc
                    if is_valid(next_r, next_c) and (next_r, next_c) not in visited and board[next_r][next_c] == word[curr_index]:
                        stack.append((next_r, next_c, curr_index + 1))
                        visited.add((next_r, next_c))
                        found_next = True
                        break
                if not found_next:
                    stack.pop()
                    visited.remove((curr_r, curr_c))
            return False

        elif approach == 2:
            if (r, c) in visited:
                return False

            visited.add((r, c))
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                next_r, next_c = r + dr, c + dc
                if search_word(next_r, next_c, word_index + 1, visited):
                    return True
            visited.remove((r, c))
            return False

        elif approach == 3:
            temp = board[r][c]
            board[r][c] = '#'  # Mark as visited
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                next_r, next_c = r + dr, c + dc
                if search_word(next_r, next_c, word_index + 1):
                    board[r][c] = temp # Restore
                    return True
            board[r][c] = temp # Restore
            return False

        elif approach == 4:
            if not is_valid(r, c) or board[r][c] != word[word_index]:
                return False

            # Combine visited check with board bounds check.
            temp = board[r][c]
            board[r][c] = '#'
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                next_r, next_c = r + dr, c + dc
                if search_word(next_r, next_c, word_index + 1):
                    board[r][c] = temp
                    return True
            board[r][c] = temp
            return False

        elif approach == 5: # Conceptual Example using Generator
            if word_index == word_len:
                yield True
                return

            if not is_valid(r, c) or board[r][c] != word[word_index]:
                yield False
                return

            visited.add((r, c)) # Keep track of visited for this conceptual example.
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                next_r, next_c = r + dr, c + dc
                yield from search_word(next_r, next_c, word_index + 1, visited)
            visited.remove((r,c))

        elif approach == 6: # Early Termination
            if word_index == word_len:
                return True

            if not is_valid(r, c) or board[r][c] != word[word_index]:
                return False
            temp = board[r][c]
            board[r][c] = '#'
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                next_r, next_c = r + dr, c + dc
                if search_word(next_r, next_c, word_index + 1):
                    board[r][c] = temp
                    return True # Early return upon finding a solution
            board[r][c] = temp
            return False

    for r in range(rows):
        for c in range(cols):
            if board[r][c] == word[0]:
                if approach == 1:
                    stack = []
                    visited = set()
                    if search_word(r, c, 0):
                        return True
                elif approach in [2, 3, 4, 6]:
                    if search_word(r, c, 0, set()):
                        return True
                elif approach == 5:
                    if any(search_word(r, c, 0, set())): # Check if any of the yielded values are True
                        return True
    return False

if __name__ == "__main__":
    board = [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]
    word1 = "ABCCED"
    word2 = "SEE"
    word3 = "ABCB"
    word4 = "ESEE"

    print("Board:")
    for row in board:
        print(row)
    print("\n")

    for approach in range(1, 7):
        print(f"Approach {approach}:")
        print(f"Word '{word1}': {solve_word_search(board, word1, approach)}")
        print(f"Word '{word2}': {solve_word_search(board, word2, approach)}")
        print(f"Word '{word3}': {solve_word_search(board, word3, approach)}")
        print(f"Word '{word4}': {solve_word_search(board, word4, approach)}") # Added test case
        print("-" * 20)

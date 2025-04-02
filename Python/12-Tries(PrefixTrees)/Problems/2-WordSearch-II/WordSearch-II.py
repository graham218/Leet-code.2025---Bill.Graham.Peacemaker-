from typing import List, Tuple
from collections import defaultdict

class TrieNode:
    """
    Represents a node in the Trie data structure.
    Each node stores a character and a dictionary of child nodes.
    """
    def __init__(self):
        self.children = defaultdict(TrieNode)
        self.is_word = False
        self.word = None  # Store the complete word at the leaf node

class Trie:
    """
    Represents a Trie (prefix tree) data structure.
    It is used to efficiently store and search for words.
    """
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the Trie.

        Args:
            word: The word to insert.
        """
        node = self.root
        for char in word:
            node = node.children[char]
        node.is_word = True
        node.word = word  # Store the word at the leaf

    def search(self, word: str) -> bool:
        """
        Searches for a word in the Trie.  (Full word search)

        Args:
            word: The word to search for.

        Returns:
            True if the word exists in the Trie, False otherwise.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_word

    def startsWith(self, prefix: str) -> bool:
        """
        Checks if there is any word in the trie that starts with the given prefix.

        Args:
            prefix: The prefix to search for.

        Returns:
            True if there is a word with the prefix, False otherwise.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True # Important: Return True, not node.is_word

class Solution:
    """
    Provides a solution to the "Word Search II" problem.
    Finds all words in a given board that are present in a word list.
    """

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        """
        Finds all words in the board that are present in the word list.

        Args:
            board: A 2D list of characters representing the game board.
            words: A list of words to search for.

        Returns:
            A list of words found in the board.
        """
        if not board or not board[0] or not words:
            return []

        trie = Trie()
        for word in words:
            trie.insert(word)

        rows, cols = len(board), len(board[0])
        result = set()  # Use a set to avoid duplicate words

        def dfs(row: int, col: int, node: TrieNode, path: str) -> None:
            """
            Depth-first search (DFS) function to explore the board.

            Args:
                row: The current row index.
                col: The current column index.
                node: The current Trie node.
                path: The current path (string) being explored.  Not strictly needed,
                       but can be helpful for debugging or alternative solutions.
            """
            if row < 0 or row >= rows or col < 0 or col >= cols or board[row][col] not in node.children:
                return

            char = board[row][col]
            next_node = node.children[char]

            if next_node.is_word:
                result.add(next_node.word) # Add the word, not the path
                # Important: Do NOT return here.  There might be other words with this prefix.

            # Mark the current cell as visited to avoid revisiting it in the current path.
            temp = board[row][col]
            board[row][col] = '#'  # Use '#' or any character not in the board

            # Explore all four directions
            dfs(row + 1, col, next_node, path + char)
            dfs(row - 1, col, next_node, path + char)
            dfs(row, col + 1, next_node, path + char)
            dfs(row, col - 1, next_node, path + char)

            # Restore the original character of the cell after exploring its neighbors.
            board[row][col] = temp

        # Iterate through each cell in the board and start a DFS search.
        for r in range(rows):
            for c in range(cols):
                dfs(r, c, trie.root, "")

        return list(result)
    # Approach 1: Basic Trie + DFS (As implemented above)
    #    - Time Complexity: O(M * 4^L), where M is the number of cells in the board,
    #      and L is the maximum length of a word in the dictionary.
    #    - Space Complexity: O(N), where N is the total number of characters in all words.

    def findWords2(self, board: List[List[str]], words: List[str]) -> List[str]:
        """
        Slightly optimized:  Check for empty board *inside* the function.
        """
        if not board or not board[0] or not words:
            return []

        trie = Trie()
        for word in words:
            trie.insert(word)

        rows, cols = len(board), len(board[0])
        result = set()

        def dfs(row, col, node):
            if row < 0 or row >= rows or col < 0 or col >= cols or board[row][col] not in node.children:
                return
            char = board[row][col]
            next_node = node.children[char]

            if next_node.is_word:
                result.add(next_node.word)

            temp = board[row][col]
            board[row][col] = '#'
            dfs(row + 1, col, next_node)
            dfs(row - 1, col, next_node)
            dfs(row, col + 1, next_node)
            dfs(row, col - 1, next_node)
            board[row][col] = temp

        for r in range(rows):
            for c in range(cols):
                dfs(r, c, trie.root)
        return list(result)

    # Approach 2:  Slightly Cleaner DFS
    #   -  Same time and space complexity as Approach 1.
    #   -  Minor code cleanup in the DFS function.

    def findWords3(self, board: List[List[str]], words: List[str]) -> List[str]:
        """
         Early termination in DFS if no matching word is possible
        """
        if not board or not board[0] or not words:
            return []

        trie = Trie()
        for word in words:
            trie.insert(word)

        rows, cols = len(board), len(board[0])
        result = set()

        def dfs(row, col, node):
            if row < 0 or row >= rows or col < 0 or col >= cols or board[row][col] not in node.children:
                return

            char = board[row][col]
            next_node = node.children[char]

            if next_node.is_word:
                result.add(next_node.word)

            temp = board[row][col]
            board[row][col] = '#'
            dfs(row + 1, col, next_node)
            dfs(row - 1, col, next_node)
            dfs(row, col + 1, next_node)
            dfs(row, col - 1, next_node)
            board[row][col] = temp

        for r in range(rows):
            for c in range(cols):
                if board[r][c] in trie.root.children: # Only start DFS if the first letter is in Trie
                    dfs(r, c, trie.root)
        return list(result)
    # Approach 3:  Early Termination in DFS
    #   - Time Complexity:  Potentially better than Approach 1 in some cases, but worst-case is still O(M * 4^L).
    #   - Space Complexity:  O(N)

    def findWords4(self, board: List[List[str]], words: List[str]) -> List[str]:
        """
        Optimization: Remove word from Trie after finding it.  This can significantly
        reduce the search space, especially if there are many overlapping words.
        """
        if not board or not board[0] or not words:
            return []

        trie = Trie()
        for word in words:
            trie.insert(word)

        rows, cols = len(board), len(board[0])
        result = set()

        def dfs(row, col, node):
            if row < 0 or row >= rows or col < 0 or col >= cols or board[row][col] not in node.children:
                return

            char = board[row][col]
            next_node = node.children[char]

            if next_node.is_word:
                result.add(next_node.word)
                # Remove word from Trie to avoid duplicate findings and reduce search space
                self.removeWord(trie.root, next_node.word) # Added removeWord
                return  # Important: return after finding a word

            temp = board[row][col]
            board[row][col] = '#'
            dfs(row + 1, col, next_node)
            dfs(row - 1, col, next_node)
            dfs(row, col + 1, next_node)
            dfs(row, col - 1, next_node)
            board[row][col] = temp

        for r in range(rows):
            for c in range(cols):
                if board[r][c] in trie.root.children:
                    dfs(r, c, trie.root)
        return list(result)

    def removeWord(self, root: TrieNode, word: str) -> None:
        """Removes a word from the Trie."""
        node = root
        path = []
        for char in word:
            if char not in node.children:
                return  # Word not in Trie
            path.append((node, char))
            node = node.children[char]

        if not node.is_word:
            return  # Word is not a complete word in Trie

        node.is_word = False
        node.word = None

        # Backtrack and remove nodes if they have no other children
        for i in range(len(path) - 1, -1, -1):
            parent, char = path[i]
            del parent.children[char]
            if parent.children:
                break # Stop if the parent has other children

    # Approach 4: Remove words from Trie after finding them
    #   - Time Complexity:  O(M * 4^L) in the worst case, but can be significantly faster in practice,
    #     especially when there are many overlapping words.  Removing words reduces the search space.
    #   - Space Complexity: O(N)  (Trie size can decrease, but is still bounded by O(N) initially)

    def findWords5(self, board: List[List[str]], words: List[str]) -> List[str]:
        """
        Optimized Trie Construction: Build Trie only with letters from the board.
        """
        if not board or not board[0] or not words:
            return []

        rows, cols = len(board), len(board[0])
        board_letters = set()
        for r in range(rows):
            for c in range(cols):
                board_letters.add(board[r][c])

        trie = Trie()
        for word in words:
            # Only insert words that can be formed from the board's letters
            if all(char in board_letters for char in word):
                trie.insert(word)

        result = set()

        def dfs(row, col, node):
            if row < 0 or row >= rows or col < 0 or col >= cols or board[row][col] not in node.children:
                return

            char = board[row][col]
            next_node = node.children[char]

            if next_node.is_word:
                result.add(next_node.word)
                self.removeWord(trie.root, next_node.word)
                return

            temp = board[row][col]
            board[row][col] = '#'
            dfs(row + 1, col, next_node)
            dfs(row - 1, col, next_node)
            dfs(row, col + 1, next_node)
            dfs(row, col - 1, next_node)
            board[row][col] = temp

        for r in range(rows):
            for c in range(cols):
                if board[r][c] in trie.root.children:
                    dfs(r, c, trie.root)
        return list(result)

    # Approach 5: Optimized Trie Construction
    #   - Time Complexity:  Potentially the most efficient, as it reduces Trie construction time
    #     and search space.  Still O(M * 4^L) in the worst case, but often much faster.
    #   - Space Complexity:  Can be significantly lower than O(N) if the board has few unique letters.
    #     In the worst case, it's still O(N).



if __name__ == "__main__":
    board = [
        ["o", "a", "a", "n"],
        ["e", "t", "a", "e"],
        ["i", "h", "k", "r"],
        ["i", "f", "l", "v"],
    ]
    words = ["oath", "pea", "eat", "rain"]

    solution = Solution()

    print("Approach 1: Basic Trie + DFS")
    result1 = solution.findWords(board, words)
    print(f"Found words: {result1}")  # Output: ['oath', 'eat']

    print("\nApproach 2: Slightly Cleaner DFS")
    result2 = solution.findWords2(board, words)
    print(f"Found words: {result2}")

    print("\nApproach 3: Early Termination in DFS")
    result3 = solution.findWords3(board, words)
    print(f"Found words: {result3}")

    print("\nApproach 4: Remove words from Trie after finding them")
    result4 = solution.findWords4(board, words)
    print(f"Found words: {result4}")

    print("\nApproach 5: Optimized Trie Construction")
    result5 = solution.findWords5(board, words)
    print(f"Found words: {result5}")

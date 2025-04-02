from collections import defaultdict

class TrieNode:
    def __init__(self):
        self.children = defaultdict(TrieNode)
        self.is_word = False
        self.word = ""

class Solution:
    def __init__(self):
        self.root = TrieNode()
        self.result = set()

    def insert(self, word):
        node = self.root
        for char in word:
            node = node.children[char]
        node.is_word = True
        node.word = word

    # Approach 1: Standard DFS with Trie Pruning (Most Common Implementation)
    def findWords1(self, board, words):
        """
        Approach 1: Standard DFS with Trie Pruning
        - Build a trie from the words
        - DFS through each cell, following valid paths in the trie
        - Prune paths when no words exist in that branch
        - Time: O(m*n*4^L) where L is max word length
        - Space: O(k*L) where k is number of words
        """
        if not board or not board[0]:
            return []

        # Build the trie
        for word in words:
            self.insert(word)

        m, n = len(board), len(board[0])

        for i in range(m):
            for j in range(n):
                if board[i][j] in self.root.children:
                    self._dfs1(board, i, j, self.root.children[board[i][j]])

        return list(self.result)

    def _dfs1(self, board, i, j, node):
        # Check if we found a word
        if node.is_word:
            self.result.add(node.word)

        # Mark the cell as visited
        temp = board[i][j]
        board[i][j] = '#'

        # Explore all 4 directions
        for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = i + di, j + dj
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and board[x][y] in node.children:
                self._dfs1(board, x, y, node.children[board[x][y]])

        # Backtrack
        board[i][j] = temp

    # Approach 2: Optimized with Early Termination and Trie Node Removal
    def findWords2(self, board, words):
        """
        Approach 2: Optimized with Early Termination and Trie Node Removal
        - Same as Approach 1 but removes found words from trie
        - Also removes leaf nodes during backtracking to prune search space
        - Time: O(m*n*4^L) but with better average case
        - Space: O(k*L)
        """
        if not board or not board[0]:
            return []

        # Build the trie
        for word in words:
            self.insert(word)

        m, n = len(board), len(board[0])

        for i in range(m):
            for j in range(n):
                if board[i][j] in self.root.children:
                    self._dfs2(board, i, j, self.root)

        return list(self.result)

    def _dfs2(self, board, i, j, parent_node):
        char = board[i][j]
        curr_node = parent_node.children[char]

        # Check if we found a word
        if curr_node.is_word:
            self.result.add(curr_node.word)
            curr_node.is_word = False  # Mark as found to avoid duplicates

        # Mark the cell as visited
        board[i][j] = '#'

        # Explore all 4 directions
        for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = i + di, j + dj
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and board[x][y] in curr_node.children:
                self._dfs2(board, x, y, curr_node)

        # Backtrack
        board[i][j] = char

        # Optimization: Remove leaf nodes to prune the search space
        if not curr_node.children:
            parent_node.children.pop(char)

    # Approach 3: Using Word Count and Trie for Faster Lookup
    def findWords3(self, board, words):
        """
        Approach 3: Using Word Count and Trie for Faster Lookup
        - Counts remaining words to find for early termination
        - Uses a counter to track how many words left to find
        - Time: O(m*n*4^L) but terminates early when all words found
        - Space: O(k*L)
        """
        if not board or not board[0] or not words:
            return []

        # Build the trie
        for word in words:
            self.insert(word)

        self.words_to_find = len(words)
        m, n = len(board), len(board[0])

        for i in range(m):
            for j in range(n):
                if self.words_to_find > 0 and board[i][j] in self.root.children:
                    self._dfs3(board, i, j, self.root)

        return list(self.result)

    def _dfs3(self, board, i, j, parent_node):
        if self.words_to_find == 0:
            return

        char = board[i][j]
        curr_node = parent_node.children[char]

        # Check if we found a word
        if curr_node.is_word:
            self.result.add(curr_node.word)
            curr_node.is_word = False
            self.words_to_find -= 1

        # Mark the cell as visited
        board[i][j] = '#'

        # Explore all 4 directions
        for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = i + di, j + dj
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and board[x][y] in curr_node.children:
                self._dfs3(board, x, y, curr_node)

        # Backtrack
        board[i][j] = char

    # Approach 4: Using BFS with Trie (Alternative to DFS)
    def findWords4(self, board, words):
        """
        Approach 4: Using BFS with Trie
        - Uses BFS instead of DFS to explore paths
        - Maintains a queue of (position, trie_node) pairs
        - Time: O(m*n*4^L)
        - Space: O(m*n + k*L) for queue and trie
        """
        if not board or not board[0]:
            return []

        # Build the trie
        for word in words:
            self.insert(word)

        m, n = len(board), len(board[0])
        result = set()

        for i in range(m):
            for j in range(n):
                if board[i][j] in self.root.children:
                    queue = []
                    queue.append((i, j, self.root.children[board[i][j]], {(i, j)}))

                    while queue:
                        x, y, node, visited = queue.pop(0)

                        if node.is_word:
                            result.add(node.word)

                        for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                            ni, nj = x + di, y + dj
                            if (0 <= ni < m and 0 <= nj < n and
                                    (ni, nj) not in visited and
                                    board[ni][nj] in node.children):
                                new_visited = set(visited)
                                new_visited.add((ni, nj))
                                queue.append((ni, nj, node.children[board[ni][nj]], new_visited))

        return list(result)

    # Approach 5: Using Trie with Hash Map for Children (Alternative Implementation)
    def findWords5(self, board, words):
        """
        Approach 5: Using Trie with Hash Map for Children
        - Alternative trie implementation using dictionary instead of defaultdict
        - More explicit about handling missing children
        - Time: O(m*n*4^L)
        - Space: O(k*L)
        """
        if not board or not board[0]:
            return []

        # Build the trie with regular dict
        root = {}
        for word in words:
            node = root
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = word  # Mark end of word

        m, n = len(board), len(board[0])
        result = []

        def backtrack(i, j, parent):
            char = board[i][j]
            curr_node = parent[char]

            # Check if we found a word
            word_match = curr_node.pop('$', False)
            if word_match:
                result.append(word_match)

            # Mark the cell as visited
            board[i][j] = '#'

            # Explore all 4 directions
            for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and board[ni][nj] in curr_node:
                    backtrack(ni, nj, curr_node)

            # Backtrack
            board[i][j] = char

            # Optimization: remove empty nodes
            if not curr_node:
                parent.pop(char)

        for i in range(m):
            for j in range(n):
                if board[i][j] in root:
                    backtrack(i, j, root)

        return result

    # Approach 6: Parallel Processing for Large Boards (Conceptual)
    def findWords6(self, board, words):
        """
        Approach 6: Parallel Processing for Large Boards (Conceptual)
        - Divides board into sections for parallel processing
        - Each section processed independently with its own trie
        - Results combined at the end
        - Note: This is a conceptual implementation showing the approach
        """
        if not board or not board[0]:
            return []

        # Build the trie
        for word in words:
            self.insert(word)

        m, n = len(board), len(board[0])
        result = set()

        # Divide board into 4 quadrants (in practice would use more sophisticated division)
        sections = [
            (0, m//2, 0, n//2),        # Top-left
            (0, m//2, n//2, n),         # Top-right
            (m//2, m, 0, n//2),        # Bottom-left
            (m//2, m, n//2, n)         # Bottom-right
        ]

        # In a real implementation, we'd use multiprocessing here
        for section in sections:
            start_i, end_i, start_j, end_j = section
            for i in range(start_i, end_i):
                for j in range(start_j, end_j):
                    if board[i][j] in self.root.children:
                        self._dfs6(board, i, j, self.root.children[board[i][j]], result)

        return list(result)

    def _dfs6(self, board, i, j, node, result):
        if node.is_word:
            result.add(node.word)

        temp = board[i][j]
        board[i][j] = '#'

        for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = i + di, j + dj
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and board[x][y] in node.children:
                self._dfs6(board, x, y, node.children[board[x][y]], result)

        board[i][j] = temp


# Test Cases
def test_solutions():
    board = [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ]
    words = ["oath","pea","eat","rain"]

    sol = Solution()

    print("Approach 1 (Standard DFS with Trie Pruning):")
    result1 = sol.findWords1([row[:] for row in board], words)
    print(result1)  # Expected: ['oath', 'eat']

    print("\nApproach 2 (Optimized with Early Termination and Trie Node Removal):")
    sol = Solution()  # Reset
    result2 = sol.findWords2([row[:] for row in board], words)
    print(result2)  # Expected: ['oath', 'eat']

    print("\nApproach 3 (Using Word Count and Trie for Faster Lookup):")
    sol = Solution()  # Reset
    result3 = sol.findWords3([row[:] for row in board], words)
    print(result3)  # Expected: ['oath', 'eat']

    print("\nApproach 4 (Using BFS with Trie):")
    sol = Solution()  # Reset
    result4 = sol.findWords4([row[:] for row in board], words)
    print(result4)  # Expected: ['oath', 'eat']

    print("\nApproach 5 (Using Trie with Hash Map for Children):")
    sol = Solution()  # Reset
    result5 = sol.findWords5([row[:] for row in board], words)
    print(result5)  # Expected: ['oath', 'eat']

    print("\nApproach 6 (Parallel Processing - Conceptual):")
    sol = Solution()  # Reset
    result6 = sol.findWords6([row[:] for row in board], words)
    print(result6)  # Expected: ['oath', 'eat']

if __name__ == "__main__":
    test_solutions()
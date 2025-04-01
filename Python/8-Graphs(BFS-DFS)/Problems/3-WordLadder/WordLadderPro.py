from collections import deque
from typing import List, Set, Dict, Tuple
import string
import heapq

# ====================
# 1. Breadth-First Search (BFS)
# ====================
def word_ladder_bfs(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using Breadth-First Search (BFS).

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity: O(M * N), where N is the length of wordList and M is the length of the words.
    Space Complexity: O(N), for the queue and visited set.

    Real-world application:
    - Spell checkers: Suggesting possible word corrections by finding words with minimal edit distance.
    - Bioinformatics: Analyzing gene sequences by finding mutations (word changes) between them.
    """
    wordList = set(wordList)  # For faster lookup
    if endWord not in wordList:
        return 0

    queue = deque([(beginWord, 1)])  # (word, level)
    visited = {beginWord}

    while queue:
        curr_word, level = queue.popleft()
        if curr_word == endWord:
            return level

        for i in range(len(curr_word)):
            for char in string.ascii_lowercase:
                next_word = curr_word[:i] + char + curr_word[i + 1:]
                if next_word in wordList and next_word not in visited:
                    visited.add(next_word)
                    queue.append((next_word, level + 1))

    return 0

# ====================
# 2. Bidirectional BFS
# ====================
def word_ladder_bidirectional_bfs(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using Bidirectional BFS.

    This approach searches from both the start and end words simultaneously,
    often leading to faster results, especially for large word lists.

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity: O(M * N), where N is the length of wordList and M is the length of the words.  Often faster than standard BFS in practice.
    Space Complexity: O(N), for the two sets.

    Real-world application:
    - Search engines: Optimizing search for connections between two concepts or documents.
    - Network routing: Finding the shortest path between two nodes in a network.
    """
    wordList = set(wordList)
    if endWord not in wordList:
        return 0

    front_queue = deque([(beginWord, 1)])
    back_queue = deque([(endWord, 1)])
    front_visited = {beginWord}
    back_visited = {endWord}

    while front_queue and back_queue:
        # Search from front
        front_level = _bfs_level(front_queue, front_visited, back_visited, wordList)
        if front_level:
            return front_level
        # Search from back
        back_level = _bfs_level(back_queue, back_visited, front_visited, wordList)
        if back_level:
            return back_level
    return 0

def _bfs_level(queue: deque, visited: Set[str], other_visited: Set[str], wordList: Set[str]) -> int:
    """Helper function for Bidirectional BFS to process one level of the search."""
    size = len(queue)
    for _ in range(size):
        curr_word, level = queue.popleft()
        if curr_word in other_visited:
            return level + other_visited[curr_word] if isinstance(other_visited, dict) else level + 1
        for i in range(len(curr_word)):
            for char in string.ascii_lowercase:
                next_word = curr_word[:i] + char + curr_word[i + 1:]
                if next_word in wordList and next_word not in visited:
                    visited.add(next_word)
                    queue.append((next_word, level + 1))
    return 0

# ====================
# 3. A* Search
# ====================
def word_ladder_astar(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using A* search algorithm.
    A* uses a heuristic (estimated distance to the goal) to guide the search.

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity:  In the worst case, it can be similar to BFS, O(M * N), where N is the length of wordList and M is the length of the words.  However, with a good heuristic, it's often much faster.
    Space Complexity: O(N), for the queue and visited set.

    Real-world application:
    - Robotics: Pathfinding for robots, considering obstacles and distances.
    - Game AI:  Finding efficient paths for game characters.
    """
    wordList = set(wordList)
    if endWord not in wordList:
        return 0

    def heuristic(word: str) -> int:
        """Calculates the Manhattan distance (number of differing characters) to the endWord."""
        distance = 0
        for i in range(len(word)):
            if word[i] != endWord[i]:
                distance += 1
        return distance

    priority_queue = [(heuristic(beginWord), beginWord, 1)]  # (f_score, word, level)
    visited = {beginWord}

    while priority_queue:
        f_score, curr_word, level = heapq.heappop(priority_queue)
        if curr_word == endWord:
            return level

        for i in range(len(curr_word)):
            for char in string.ascii_lowercase:
                next_word = curr_word[:i] + char + curr_word[i + 1:]
                if next_word in wordList and next_word not in visited:
                    visited.add(next_word)
                    heapq.heappush(priority_queue, (level + 1 + heuristic(next_word), next_word, level + 1))

    return 0

# ====================
# 4. Optimized BFS with Precomputed Neighbors
# ====================
def word_ladder_optimized_bfs(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using BFS, with precomputed neighbors.
    This optimization pre-calculates all possible one-letter variations for each word,
    reducing the inner loop overhead in the BFS.

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity: O(N + M^2 * 26), where N is the length of wordList and M is the length of the words.  The neighbor precomputation is O(M^2 * 26).  The BFS is then closer to O(N).
    Space Complexity: O(N + M^2 * 26), for the queue and the neighbors dictionary.

    Real-world application:
    - Code compilation: Finding similar code snippets for error correction or code suggestion.
    - Data cleaning: Identifying and correcting misspelled words in large datasets.
    """
    wordList = set(wordList)
    if endWord not in wordList:
        return 0

    def get_neighbors(word: str) -> List[str]:
        """Generates all one-letter neighbors of a word."""
        neighbors = []
        for i in range(len(word)):
            for char in string.ascii_lowercase:
                next_word = word[:i] + char + word[i + 1:]
                if next_word in wordList:
                    neighbors.append(next_word)
        return neighbors

    # Precompute neighbors for each word in wordList
    neighbors_map: Dict[str, List[str]] = {word: get_neighbors(word) for word in wordList}
    neighbors_map[beginWord] = get_neighbors(beginWord) # add beginWord neighbors

    queue = deque([(beginWord, 1)])
    visited = {beginWord}

    while queue:
        curr_word, level = queue.popleft()
        if curr_word == endWord:
            return level

        for next_word in neighbors_map[curr_word]:
            if next_word not in visited:
                visited.add(next_word)
                queue.append((next_word, level + 1))

    return 0

# ====================
# 5. Using a Graph Class
# ====================
class Graph:
    """
    A simple graph class to represent words and their connections.
    This approach encapsulates the graph logic, making the word ladder solution cleaner.
    """
    def __init__(self, words: List[str]):
        """
        Initializes the graph with a list of words.  Edges are created between words
        that differ by only one letter.
        """
        self.graph: Dict[str, List[str]] = {}
        self.words = words
        self.build_graph()

    def build_graph(self):
        """Builds the graph by creating edges between adjacent words."""
        for word in self.words:
            self.graph[word] = []
        for i in range(len(self.words)):
            for j in range(i + 1, len(self.words)):
                if self.is_adjacent(self.words[i], self.words[j]):
                    self.graph[self.words[i]].append(self.words[j])
                    self.graph[self.words[j]].append(self.words[i])

    def is_adjacent(self, word1: str, word2: str) -> bool:
        """Checks if two words differ by only one letter."""
        if len(word1) != len(word2):
            return False
        diff_count = 0
        for i in range(len(word1)):
            if word1[i] != word2[i]:
                diff_count += 1
                if diff_count > 1:
                    return False
        return diff_count == 1

    def find_shortest_path(self, start: str, end: str) -> int:
        """
        Finds the shortest path (word ladder length) between two words using BFS on the graph.

        Args:
            start: The starting word.
            end: The target word.

        Returns:
            The length of the shortest path, or 0 if no path exists.
        """
        if start not in self.graph or end not in self.graph:
            return 0

        queue = deque([(start, 1)])
        visited = {start}

        while queue:
            curr_word, level = queue.popleft()
            if curr_word == end:
                return level
            for neighbor in self.graph[curr_word]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, level + 1))
        return 0

def word_ladder_graph(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using a custom Graph class.

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity: O(N^2 * M + N), where N is the length of wordList and M is the length of the words. Graph construction is O(N^2 * M), BFS is O(N) in this case.
    Space Complexity: O(N^2), for storing the graph.

     Real-world application:
     - Social network analysis: Finding connections between people or entities.
     - Knowledge graphs:  Determining relationships between concepts.
    """
    if endWord not in wordList:
        return 0
    graph = Graph([beginWord] + wordList) # Include beginWord in the graph.
    return graph.find_shortest_path(beginWord, endWord)

# ====================
# 6. Optimized Graph with Adjacency Matrix
# ====================

class OptimizedGraph:
    """
    An optimized graph class using an adjacency matrix for faster neighbor lookup.
    This is beneficial when dealing with a large number of words, as it provides
    constant-time access to check if two words are adjacent.
    """
    def __init__(self, words: List[str]):
        """
        Initializes the graph with a list of words.
        The adjacency matrix stores whether two words are one letter apart.
        """
        self.words = words
        self.word_to_index = {word: i for i, word in enumerate(words)}
        self.adj_matrix = [[False] * len(words) for _ in range(len(words))]
        self.build_graph()

    def build_graph(self):
        """Builds the adjacency matrix."""
        for i in range(len(self.words)):
            for j in range(i + 1, len(self.words)):
                if self.is_adjacent(self.words[i], self.words[j]):
                    self.adj_matrix[i][j] = True
                    self.adj_matrix[j][i] = True

    def is_adjacent(self, word1: str, word2: str) -> bool:
        """Checks if two words differ by only one letter."""
        if len(word1) != len(word2):
            return False
        diff_count = 0
        for i in range(len(word1)):
            if word1[i] != word2[i]:
                diff_count += 1
                if diff_count > 1:
                    return False
        return diff_count == 1

    def get_neighbors(self, word: str) -> List[str]:
        """Gets the neighbors of a word using the adjacency matrix."""
        neighbors = []
        word_index = self.word_to_index[word]
        for i, is_neighbor in enumerate(self.adj_matrix[word_index]):
            if is_neighbor:
                neighbors.append(self.words[i])
        return neighbors

    def find_shortest_path(self, start: str, end: str) -> int:
        """
        Finds the shortest path (word ladder length) between two words using BFS on the graph.

        Args:
            start: The starting word.
            end: The target word.

        Returns:
            The length of the shortest path, or 0 if no path exists.
        """
        if start not in self.word_to_index or end not in self.word_to_index:
            return 0

        queue = deque([(start, 1)])
        visited = {start}

        while queue:
            curr_word, level = queue.popleft()
            if curr_word == end:
                return level
            for neighbor in self.get_neighbors(curr_word):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, level + 1))
        return 0


def word_ladder_optimized_graph(beginWord: str, endWord: str, wordList: List[str]) -> int:
    """
    Finds the shortest word ladder length using an optimized Graph class with an adjacency matrix.

    Args:
        beginWord: The starting word.
        endWord: The target word.
        wordList: The list of words to form the ladder.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Time Complexity: O(N^2 * M + N), where N is the length of wordList and M is the length of the words. Graph construction is O(N^2 * M), but BFS neighbor lookup is O(1) per neighbor.
    Space Complexity: O(N^2), for the adjacency matrix.

    Real-world application:
    -  Social network analysis:  Optimized for large networks where checking connections needs to be very fast.
    -  Route planning:  When dealing with a fixed map and needing to find routes repeatedly.
    """
    if endWord not in wordList:
        return 0
    graph = OptimizedGraph([beginWord] + wordList)
    return graph.find_shortest_path(beginWord, endWord)

def main():
    """
    Main function to run and test the word ladder solutions.
    """
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot", "dot", "dog", "lot", "log", "cog"]

    print("Word Ladder Problem Solutions:")
    print(f"Start Word: {beginWord}, End Word: {endWord}, Word List: {wordList}")
    print("-" * 40)

    # 1. Breadth-First Search (BFS)
    result_bfs = word_ladder_bfs(beginWord, endWord, wordList)
    print(f"1. BFS Solution: {result_bfs}")

    # 2. Bidirectional BFS
    result_bidirectional_bfs = word_ladder_bidirectional_bfs(beginWord, endWord, wordList)
    print(f"2. Bidirectional BFS Solution: {result_bidirectional_bfs}")

    # 3. A* Search
    result_astar = word_ladder_astar(beginWord, endWord, wordList)
    print(f"3. A* Search Solution: {result_astar}")

    # 4. Optimized BFS with Precomputed Neighbors
    result_optimized_bfs = word_ladder_optimized_bfs(beginWord, endWord, wordList)
    print(f"4. Optimized BFS Solution: {result_optimized_bfs}")

    # 5. Using a Graph Class
    result_graph = word_ladder_graph(beginWord, endWord, wordList)
    print(f"5. Graph Class Solution: {result_graph}")

    # 6. Optimized Graph with Adjacency Matrix
    result_optimized_graph = word_ladder_optimized_graph(beginWord, endWord, wordList)
    print(f"6. Optimized Graph Solution: {result_optimized_graph}")
    print("-" * 40)

if __name__ == "__main__":
    main()

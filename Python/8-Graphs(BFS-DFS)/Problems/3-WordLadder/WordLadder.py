from collections import deque
from typing import List

# Approach 1: Breadth-First Search (BFS)
def word_ladder_bfs(begin_word: str, end_word: str, word_list: List[str]) -> int:
    """
    Finds the shortest word ladder length using Breadth-First Search (BFS).

    Args:
        begin_word: The starting word.
        end_word: The target ending word.
        word_list: A list of words to form the transformation sequence.

    Returns:
        The length of the shortest word ladder, or 0 if no such ladder exists.

    Algorithm:
    1.  Check if the end_word is in the word_list. If not, return 0.
    2.  Initialize a queue with the begin_word and a length of 1.
    3.  Initialize a set from word_list for efficient lookup.
    4.  While the queue is not empty:
        a.  Dequeue a word and its length.
        b.  If the word is the end_word, return the length.
        c.  For each character in the word:
            i.  For each letter 'a' to 'z':
                -   Create a new word by replacing the character.
                -   If the new word is in the word_set:
                    -   Enqueue the new word and the incremented length.
                    -   Remove the new word from word_set to prevent revisiting.
    5.  If the queue is empty and the end_word is not found, return 0.
    """
    word_set = set(word_list)
    if end_word not in word_set:
        return 0

    queue = deque([(begin_word, 1)])

    while queue:
        word, length = queue.popleft()
        if word == end_word:
            return length

        for i in range(len(word)):
            for c in 'abcdefghijklmnopqrstuvwxyz':
                next_word = word[:i] + c + word[i+1:]
                if next_word in word_set:
                    queue.append((next_word, length + 1))
                    word_set.remove(next_word)  # Important to prevent cycles and revisits

    return 0

# Approach 2: Bi-Directional BFS
def word_ladder_bidirectional_bfs(begin_word: str, end_word: str, word_list: List[str]) -> int:
    """
    Finds the shortest word ladder length using Bi-Directional Breadth-First Search.

    This approach searches from both the start and end words simultaneously,
    often leading to faster results, especially in large graphs.

    Args:
        begin_word: The starting word.
        end_word: The target ending word.
        word_list: The list of words for transformation.

    Returns:
        The length of the shortest word ladder, or 0 if no path exists.

    Algorithm:
    1.  Check if the end_word is in the word_list.  If not, return 0.
    2.  Initialize two sets: one starting from begin_word (begin_set) and the other from end_word (end_set).
    3.  Initialize the length of the path to 1.
    4.  While both sets are not empty:
        a.  If the begin_set is larger than the end_set, swap them to optimize search.
        b.  Create a temporary set (next_set) to store the next level of words.
        c.  For each word in the begin_set:
            i.  For each character in the word:
                -   For each letter 'a' to 'z':
                    -   Generate a new word by changing one character.
                    -   If the new word is in the end_set, return the current length + 1 (since they met).
                    -   If the new word is in the word_set and not visited, add it to next_set and remove from word_set.
        d.  Replace begin_set with next_set.
        e.  Increment the length.
    5.  If the loops finish without finding a connection, return 0.
    """
    word_set = set(word_list)
    if end_word not in word_set:
        return 0

    begin_set, end_set = {begin_word}, {end_word}
    length = 1

    while begin_set and end_set:
        if len(begin_set) > len(end_set):
            begin_set, end_set = end_set, begin_set  # Swap for efficiency

        next_set = set()
        for word in begin_set:
            for i in range(len(word)):
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    next_word = word[:i] + c + word[i+1:]
                    if next_word in end_set:
                        return length + 1
                    if next_word in word_set:
                        next_set.add(next_word)
                        word_set.remove(next_word)

        begin_set = next_set
        length += 1

    return 0

# Approach 3: Dijkstra's Algorithm (Shortest Path)
import heapq

def word_ladder_dijkstra(begin_word: str, end_word: str, word_list: List[str]) -> int:
    """
    Finds the shortest word ladder length using Dijkstra's Algorithm.
    Dijkstra's is typically used for weighted graphs, but here all edge weights are 1,
    making it suitable for finding the shortest path.  It's less efficient than standard BFS here.

    Args:
        begin_word: The starting word.
        end_word: The ending word.
        word_list: The list of words.

    Returns:
        The shortest ladder length, or 0 if no path exists.

    Algorithm:
    1.  Check if end_word is in word_list. If not, return 0.
    2.  Initialize a priority queue (heap) with (cost: 1, word: begin_word).
    3.  Initialize a set to track visited words.
    4.  While the heap is not empty:
        a.  Pop the word with the smallest cost from the heap.
        b.  If the word is the end_word, return the cost.
        c.  If the word has already been visited, continue to the next iteration.
        d.  Mark the word as visited.
        e.  For each possible one-character variation of the word:
            -   If the variation is in word_set:
                -   Push the (cost + 1, variation) onto the heap.
    5.  If the heap becomes empty without finding the end_word, return 0.
    """
    word_set = set(word_list)
    if end_word not in word_set:
        return 0

    heap = [(1, begin_word)]  # (cost, word)
    visited = set()

    while heap:
        cost, word = heapq.heappop(heap)
        if word == end_word:
            return cost

        if word in visited:
            continue
        visited.add(word)

        for i in range(len(word)):
            for c in 'abcdefghijklmnopqrstuvwxyz':
                next_word = word[:i] + c + word[i+1:]
                if next_word in word_set:
                    heapq.heappush(heap, (cost + 1, next_word))
                    word_set.remove(next_word) # prevent re-visit.

    return 0

# Approach 4: A* Search Algorithm
def heuristic(word1: str, word2: str) -> int:
    """
    Calculates the heuristic (estimated distance) between two words.
    This heuristic counts the number of differing characters.  It's admissible
    because it never overestimates the actual number of transformations.

    Args:
        word1: The first word.
        word2: The second word.

    Returns:
        The number of differing characters.
    """
    return sum(c1 != c2 for c1, c2 in zip(word1, word2))

def word_ladder_astar(begin_word: str, end_word: str, word_list: List[str]) -> int:
    """
    Finds the shortest word ladder length using the A* search algorithm.
    A* is an informed search algorithm that uses a heuristic to guide its search.
    In this case, the heuristic estimates the number of transformations needed
    to reach the end_word.

    Args:
        begin_word: The starting word.
        end_word: The ending word.
        word_list: The list of words.

    Returns:
        The shortest ladder length, or 0 if no path exists.

    Algorithm:
    1.  Check if the end_word is in word_list. If not, return 0.
    2.  Initialize a priority queue (heap) with (f_cost, cost, word).
        -   f_cost = cost + heuristic(word, end_word)
        -   cost = current path length
        -   word = current word
    3.  Initialize a visited set.
    4.  While the heap is not empty:
        a.  Pop the word with the smallest f_cost from the heap.
        b.  If the word is the end_word, return the cost.
        c.  If the word has been visited, continue.
        d.  Mark the word as visited.
        e.  For each possible one-character variation of the word:
            -   If the variation is in word_set:
                -   Calculate the new_cost (cost + 1).
                -   Calculate the new_f_cost (new_cost + heuristic(variation, end_word)).
                -   Push (new_f_cost, new_cost, variation) onto the heap.
    5.  If the heap is empty without finding the end_word, return 0.
    """
    word_set = set(word_list)
    if end_word not in word_set:
        return 0

    heap = [(heuristic(begin_word, end_word), 1, begin_word)]  # (f_cost, cost, word)
    visited = set()

    while heap:
        _, cost, word = heapq.heappop(heap)
        if word == end_word:
            return cost

        if word in visited:
            continue
        visited.add(word)

        for i in range(len(word)):
            for c in 'abcdefghijklmnopqrstuvwxyz':
                next_word = word[:i] + c + word[i+1:]
                if next_word in word_set:
                    heapq.heappush(heap, (cost + 1 + heuristic(next_word, end_word), cost + 1, next_word))
                    word_set.remove(next_word)

    return 0

# Approach 5: Bidirectional Dijkstra's Algorithm
def word_ladder_bidirectional_dijkstra(begin_word: str, end_word: str, word_list: List[str]) -> int:
    """
    Finds the shortest word ladder using a bidirectional Dijkstra's approach.
    This combines the efficiency of bidirectional search with Dijkstra's cost-based
    exploration, potentially improving performance in some cases.

    Args:
        begin_word: The starting word.
        end_word: The ending word.
        word_list: The list of valid words.

    Returns:
        The length of the shortest word ladder, or 0 if no path exists.

    Algorithm:
    1.  Check if the end_word is in the word_list. If not, return 0.
    2.  Initialize two priority queues (heaps) for forward and backward search.
    3.  Initialize two dictionaries to store visited nodes and their costs for each direction.
    4.  While both heaps are not empty:
        a.  Define a helper function `expand` to:
            i.   Pop a node from the current heap.
            ii.  If the node is in the visited set of the other direction, return the combined cost.
            iii.  For each neighbor of the current node:
                -   If the neighbor is in the word_set and not visited:
                    -   Add the neighbor and its cost to the visited set.
                    -   Push the neighbor and its cost onto the heap.
            iv.  Return None if no meeting point is found.
        b.  Call `expand` for the forward search. If a meeting point is found, return the result.
        c.  Call `expand` for the backward search. If a meeting point is found, return the result.
    5.  If the heaps become empty without finding a connection, return 0.
    """
    word_set = set(word_list)
    if end_word not in word_set:
        return 0

    forward_heap = [(1, begin_word)]
    backward_heap = [(1, end_word)]
    forward_visited = {begin_word: 1}
    backward_visited = {end_word: 1}

    while forward_heap and backward_heap:
        def expand(heap, visited, other_visited):
            cost, word = heapq.heappop(heap)
            if word in other_visited:
                return cost + other_visited[word] - 1

            for i in range(len(word)):
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    next_word = word[:i] + c + word[i+1:]
                    if next_word in word_set and next_word not in visited:
                        visited[next_word] = cost + 1
                        heapq.heappush(heap, (cost + 1, next_word))

            return None

        result = expand(forward_heap, forward_visited, backward_visited)
        if result:
            return result
        result = expand(backward_heap, backward_visited, forward_visited)
        if result:
            return result

    return 0

# Example usage
begin = "hit"
end = "cog"
word_list = ["hot","dot","dog","lot","log","cog"]

print("BFS Solution:", word_ladder_bfs(begin, end, word_list))
print("Bi-Directional BFS Solution:", word_ladder_bidirectional_bfs(begin, end, word_list))
print("Dijkstra's Algorithm Solution:", word_ladder_dijkstra(begin, end, word_list))
print("A* Algorithm Solution:", word_ladder_astar(begin, end, word_list))
print("Bidirectional Dijkstra Solution:", word_ladder_bidirectional_dijkstra(begin, end, word_list))

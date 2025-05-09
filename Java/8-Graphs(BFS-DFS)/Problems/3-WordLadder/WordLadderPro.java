import java.util.*;

public class WordLadder {

    /**
     * Approach 1: Breadth-First Search (BFS) - Standard Implementation
     *
     * This is the most common and efficient approach for solving the Word Ladder problem.
     * It uses BFS to explore the graph of word connections level by level, ensuring that
     * the shortest path is found.
     *
     * Time Complexity: O(V * E), where V is the number of vertices (words) and E is the number of edges.
     * In the worst case, it can be O(N * M * 26), where N is the length of the word, and M is the number of words
     * Space Complexity: O(V) - for the queue and visited set.
     */
    public int ladderLengthBFS(String beginWord, String endWord, List<String> wordList) {
        // Check for invalid input
        if (beginWord == null || endWord == null || wordList == null || wordList.isEmpty()) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) {
            return 0; // End word not in dictionary
        }

        Queue<String> queue = new LinkedList<>();
        queue.offer(beginWord);
        Set<String> visited = new HashSet<>();
        visited.add(beginWord);
        int level = 1;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String currentWord = queue.poll();
                if (currentWord.equals(endWord)) {
                    return level;
                }

                for (String nextWord : getNextWords(currentWord, dict)) {
                    if (!visited.contains(nextWord)) {
                        visited.add(nextWord);
                        queue.offer(nextWord);
                    }
                }
            }
            level++;
        }
        return 0; // No path found
    }

    /**
     * Helper function to get all possible one-letter different words from the dictionary.
     */
    private List<String> getNextWords(String word, Set<String> dict) {
        List<String> nextWords = new ArrayList<>();
        for (int i = 0; i < word.length(); i++) {
            char[] charArray = word.toCharArray();
            for (char c = 'a'; c <= 'z'; c++) {
                if (charArray[i] == c) continue; // Skip the original character
                charArray[i] = c;
                String newWord = new String(charArray);
                if (dict.contains(newWord)) {
                    nextWords.add(newWord);
                }
            }
        }
        return nextWords;
    }

    /**
     * Approach 2: Bidirectional BFS
     *
     * This approach improves upon the standard BFS by searching from both the beginWord
     * and the endWord simultaneously.  This often reduces the search space and improves
     * performance, especially for larger word lists.
     *
     * Time Complexity: O(V * E) in the worst case, but often faster than standard BFS in practice.
     * Space Complexity: O(V)
     */
    public int ladderLengthBiBFS(String beginWord, String endWord, List<String> wordList) {
        if (beginWord == null || endWord == null || wordList == null || wordList.isEmpty()) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) {
            return 0;
        }

        Set<String> beginSet = new HashSet<>();
        Set<String> endSet = new HashSet<>();
        Set<String> visited = new HashSet<>();

        beginSet.add(beginWord);
        endSet.add(endWord);
        visited.add(beginWord);
        visited.add(endWord);
        int level = 1;

        while (!beginSet.isEmpty() && !endSet.isEmpty()) {
            // Swap beginSet and endSet to always iterate the smaller set
            if (beginSet.size() > endSet.size()) {
                Set<String> temp = beginSet;
                beginSet = endSet;
                endSet = temp;
            }

            Set<String> nextSet = new HashSet<>();
            for (String word : beginSet) {
                if (endSet.contains(word)) {
                    return level;
                }
                for (String nextWord : getNextWords(word, dict)) {
                    if (!visited.contains(nextWord)) {
                        visited.add(nextWord);
                        nextSet.add(nextWord);
                    }
                }
            }
            beginSet = nextSet;
            level++;
        }
        return 0;
    }

    /**
     * Approach 3: A* Search (Informed Search) - Heuristic Approach
     *
     * A* search is an informed search algorithm that uses a heuristic function to guide its search.
     * In this case, a suitable heuristic is the Hamming distance (number of different characters)
     * between the current word and the endWord.  A* can be more efficient than BFS if the heuristic
     * is well-chosen, but it's more complex to implement.
     *
     * Time Complexity:  Depends on the heuristic.  In the best case, it can be much faster than BFS,
     * but in the worst case, it can be similar to BFS.
     * Space Complexity: O(V)
     */
    public int ladderLengthAStar(String beginWord, String endWord, List<String> wordList) {
        if (beginWord == null || endWord == null || wordList == null || wordList.isEmpty()) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) {
            return 0;
        }

        PriorityQueue<WordNode> pq = new PriorityQueue<>();
        Set<String> visited = new HashSet<>();

        pq.offer(new WordNode(beginWord, 1, hammingDistance(beginWord, endWord)));
        visited.add(beginWord);

        while (!pq.isEmpty()) {
            WordNode current = pq.poll();
            String currentWord = current.word;
            int level = current.level;

            if (currentWord.equals(endWord)) {
                return level;
            }

            for (String nextWord : getNextWords(currentWord, dict)) {
                if (!visited.contains(nextWord)) {
                    visited.add(nextWord);
                    pq.offer(new WordNode(nextWord, level + 1, hammingDistance(nextWord, endWord)));
                }
            }
        }
        return 0;
    }

    /**
     * Helper class for A* search to store word, level, and heuristic value.
     */
    private static class WordNode implements Comparable<WordNode> {
        String word;
        int level;
        int heuristic; // Estimated distance to endWord

        public WordNode(String word, int level, int heuristic) {
            this.word = word;
            this.level = level;
            this.heuristic = heuristic;
        }

        @Override
        public int compareTo(WordNode other) {
            // Compare based on f(n) = g(n) + h(n) (level + heuristic)
            int thisValue = this.level + this.heuristic;
            int otherValue = other.level + other.heuristic;
            return Integer.compare(thisValue, otherValue);
        }
    }

    /**
     * Helper function to calculate the Hamming distance between two words.
     */
    private int hammingDistance(String word1, String word2) {
        int distance = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                distance++;
            }
        }
        return distance;
    }

    /**
     * Approach 4: Precomputed Graph + BFS
     *
     * This approach optimizes the process of finding neighboring words by precomputing the graph
     * of word connections.  Instead of generating neighbors on the fly, we build an adjacency list
     * representing the graph before performing the BFS.  This can be beneficial if the word list
     * is large and the `getNextWords` operation is expensive.
     *
     * Time Complexity: O(M * N^2 + V + E), where M is word list size, N is word length, V is vertices, E is edges.
     * Precomputation takes O(M * N^2), BFS takes O(V + E).
     * Space Complexity: O(V + E) to store the graph, potentially O(M * N^2) in worst case.
     */
    public int ladderLengthPrecomputed(String beginWord, String endWord, List<String> wordList) {
        if (beginWord == null || endWord == null || wordList == null || wordList.isEmpty()) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) {
            return 0;
        }

        Map<String, List<String>> graph = buildGraph(beginWord, dict); // Precompute the graph

        if (!graph.containsKey(beginWord))
            return 0;

        Queue<String> queue = new LinkedList<>();
        queue.offer(beginWord);
        Set<String> visited = new HashSet<>();
        visited.add(beginWord);
        int level = 1;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String currentWord = queue.poll();
                if (currentWord.equals(endWord)) {
                    return level;
                }

                if (graph.containsKey(currentWord)) { // Use precomputed neighbors
                    for (String nextWord : graph.get(currentWord)) {
                        if (!visited.contains(nextWord)) {
                            visited.add(nextWord);
                            queue.offer(nextWord);
                        }
                    }
                }
            }
            level++;
        }
        return 0;
    }

    /**
     * Helper function to build the graph of word connections.
     */
    private Map<String, List<String>> buildGraph(String beginWord, Set<String> dict) {
        Map<String, List<String>> graph = new HashMap<>();
        dict.add(beginWord); // Ensure beginWord is in the dictionary for graph building.

        for (String word : dict) {
            List<String> neighbors = new ArrayList<>();
            for (String otherWord : dict) {
                if (isOneLetterDiff(word, otherWord)) {
                    neighbors.add(otherWord);
                }
            }
            graph.put(word, neighbors);
        }
        return graph;
    }

    /**
     * Helper function to check if two words differ by only one letter.
     */
    private boolean isOneLetterDiff(String word1, String word2) {
        if (word1.length() != word2.length()) {
            return false;
        }
        int diffCount = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                diffCount++;
            }
        }
        return diffCount == 1;
    }

    /**
     * Approach 5: Optimized Precomputed Graph + Bidirectional BFS
     *
     * Combines the advantages of precomputed graph and bidirectional BFS.  This is often the
     * most efficient approach, especially for large word lists, as it avoids redundant neighbor
     * calculations and searches from both ends.
     *
     * Time Complexity: Similar to Precomputed Graph + BFS, but often faster in practice due to
     * bidirectional search.  Precomputation: O(M * N^2), Search: O(V + E), but search space is reduced.
     * Space Complexity: O(V + E) for the graph.
     */
    public int ladderLengthOptimized(String beginWord, String endWord, List<String> wordList) {
        if (beginWord == null || endWord == null || wordList == null || wordList.isEmpty()) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) {
            return 0;
        }

        Map<String, List<String>> graph = buildGraph(beginWord, dict); // Precompute graph

        if (!graph.containsKey(beginWord))
            return 0;

        Set<String> beginSet = new HashSet<>();
        Set<String> endSet = new HashSet<>();
        Set<String> visited = new HashSet<>();

        beginSet.add(beginWord);
        endSet.add(endWord);
        visited.add(beginWord);
        visited.add(endWord);
        int level = 1;

        while (!beginSet.isEmpty() && !endSet.isEmpty()) {
            if (beginSet.size() > endSet.size()) {
                Set<String> temp = beginSet;
                beginSet = endSet;
                endSet = temp;
            }

            Set<String> nextSet = new HashSet<>();
            for (String word : beginSet) {
                if (endSet.contains(word)) {
                    return level;
                }
                if (graph.containsKey(word)) { // Use precomputed neighbors
                    for (String nextWord : graph.get(word)) {
                        if (!visited.contains(nextWord)) {
                            visited.add(nextWord);
                            nextSet.add(nextWord);
                        }
                    }
                }
            }
            beginSet = nextSet;
            level++;
        }
        return 0;
    }

    public static void main(String[] args) {
        WordLadder wordLadder = new WordLadder();
        String beginWord = "hit";
        String endWord = "cog";
        List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        // Test Approach 1: BFS
        System.out.println("BFS Result: " + wordLadder.ladderLengthBFS(beginWord, endWord, wordList)); // Expected: 5

        // Test Approach 2: Bidirectional BFS
        System.out.println("Bi-BFS Result: " + wordLadder.ladderLengthBiBFS(beginWord, endWord, wordList)); // Expected: 5

        // Test Approach 3: A* Search
        System.out.println("A* Search Result: " + wordLadder.ladderLengthAStar(beginWord, endWord, wordList)); // Expected: 5

        // Test Approach 4: Precomputed Graph + BFS
        System.out.println("Precomputed Graph + BFS Result: " + wordLadder.ladderLengthPrecomputed(beginWord, endWord, wordList)); // Expected: 5

        // Test Approach 5: Optimized Precomputed Graph + Bidirectional BFS
        System.out.println("Optimized Result: " + wordLadder.ladderLengthOptimized(beginWord, endWord, wordList)); // Expected: 5

        // Example where endWord is not reachable
        String beginWord2 = "apple";
        String endWord2 = "banana";
        List<String> wordList2 = Arrays.asList("apple", "aplle", "aplle", "bannna");
        System.out.println("No Path Test (BFS): " + wordLadder.ladderLengthBFS(beginWord2, endWord2, wordList2)); // Expected: 0
        System.out.println("No Path Test (BiBFS): " + wordLadder.ladderLengthBiBFS(beginWord2, endWord2, wordList2)); // Expected: 0
        System.out.println("No Path Test (AStar): " + wordLadder.ladderLengthAStar(beginWord2, endWord2, wordList2)); // Expected: 0
        System.out.println("No Path Test (Precomputed): " + wordLadder.ladderLengthPrecomputed(beginWord2, endWord2, wordList2)); //Expected: 0
        System.out.println("No Path Test (Optimized): " + wordLadder.ladderLengthOptimized(beginWord2, endWord2, wordList2)); //Expected: 0

        // Example with empty wordList
        String beginWord3 = "hit";
        String endWord3 = "cog";
        List<String> wordList3 = new ArrayList<>();
        System.out.println("Empty List Test (BFS): " + wordLadder.ladderLengthBFS(beginWord3, endWord3, wordList3)); // Expected: 0
        System.out.println("Empty List Test (BiBFS): " + wordLadder.ladderLengthBiBFS(beginWord3, endWord3, wordList3)); // Expected: 0
        System.out.println("Empty List Test (AStar): " + wordLadder.ladderLengthAStar(beginWord3, endWord3, wordList3)); // Expected: 0
        System.out.println("Empty List Test (Precomputed): " + wordLadder.ladderLengthPrecomputed(beginWord3, endWord3, wordList3)); // Expected: 0
        System.out.println("Empty List Test (Optimized): " + wordLadder.ladderLengthOptimized(beginWord3, endWord3, wordList3)); // Expected: 0
    }
}


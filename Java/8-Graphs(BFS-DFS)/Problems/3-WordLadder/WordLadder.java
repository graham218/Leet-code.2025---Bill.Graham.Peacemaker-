import java.util.*;

public class WordLadder {

    /**
     * Solves the Word Ladder problem using Breadth-First Search (BFS).
     *
     * Given a begin word, an end word, and a dictionary of words, find the length of the shortest transformation sequence from beginWord to endWord, such that:
     * 1. Only one letter can be changed at a time.
     * 2. Each transformed word must exist in the dictionary.
     *
     * @param beginWord The starting word.
     * @param endWord   The target word.
     * @param wordList  The list of words in the dictionary.
     * @return The length of the shortest transformation sequence, or 0 if no such sequence exists.
     *
     * Time Complexity: O(M * N), where N is the number of words in wordList and M is the length of each word.
     * Space Complexity: O(N), for the queue and visited set.
     */
    public int ladderLengthBFS(String beginWord, String endWord, List<String> wordList) {
        // Check if the endWord is in the wordList. If not, no transformation is possible.
        if (!wordList.contains(endWord)) {
            return 0;
        }

        // Create a set to store the words from the wordList for efficient lookup.
        Set<String> dict = new HashSet<>(wordList);
        // Create a queue to store the words to be processed.  Start with the beginWord.
        Queue<String> queue = new LinkedList<>();
        queue.offer(beginWord);
        // Create a set to keep track of visited words to avoid cycles.
        Set<String> visited = new HashSet<>();
        visited.add(beginWord);
        // Initialize the length of the transformation sequence.
        int level = 1;

        // Perform BFS.
        while (!queue.isEmpty()) {
            int size = queue.size(); // Get the number of words at the current level.

            // Process all words at the current level.
            for (int i = 0; i < size; i++) {
                String currentWord = queue.poll();

                // If the current word is the end word, we have found the shortest path.
                if (currentWord.equals(endWord)) {
                    return level;
                }

                // Generate all possible one-letter variations of the current word.
                for (String nextWord : getNextWords(currentWord, dict)) {
                    if (!visited.contains(nextWord)) {
                        visited.add(nextWord); // Mark the word as visited.
                        queue.offer(nextWord); // Add the word to the queue for processing.
                    }
                }
            }
            level++; // Move to the next level in the BFS.
        }

        // If the queue is empty and the end word is not found, there is no valid transformation sequence.
        return 0;
    }

    /**
     * Helper function to generate all possible one-letter variations of a given word.
     *
     * @param word The input word.
     * @param dict The dictionary of valid words.
     * @return A list of words that are one letter different from the input word and are present in the dictionary.
     */
    private List<String> getNextWords(String word, Set<String> dict) {
        List<String> nextWords = new ArrayList<>();
        char[] charArray = word.toCharArray();

        // Iterate through each character of the word.
        for (int i = 0; i < charArray.length; i++) {
            char originalChar = charArray[i]; // Store the original character.

            // Replace the character with all possible letters from 'a' to 'z'.
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != originalChar) { // Skip the original character.
                    charArray[i] = c; // Change the character.
                    String newWord = new String(charArray); // Create a new word.

                    // If the new word is in the dictionary, add it to the list of next words.
                    if (dict.contains(newWord)) {
                        nextWords.add(newWord);
                    }
                }
            }
            charArray[i] = originalChar; // Restore the original character.
        }
        return nextWords;
    }


    /**
     * Solves the Word Ladder problem using Bidirectional Breadth-First Search (BFS).
     * This approach improves upon the standard BFS by searching from both the beginWord
     * and the endWord simultaneously.
     *
     * @param beginWord The starting word.
     * @param endWord The target word.
     * @param wordList The list of words in the dictionary.
     * @return The length of the shortest transformation sequence, or 0 if no such sequence exists.
     *
     * Time Complexity: O(M * N), where N is the number of words in wordList and M is the length of each word.  Generally faster than standard BFS.
     * Space Complexity: O(N), for the two sets and queues.
     */
    public int ladderLengthBiBFS(String beginWord, String endWord, List<String> wordList) {
        if (!wordList.contains(endWord)) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        // Use two sets to store words to visit from both ends.
        Set<String> head = new HashSet<>();
        Set<String> tail = new HashSet<>();
        head.add(beginWord);
        tail.add(endWord);

        // Use two sets to track visited words from both ends.
        Set<String> visitedHead = new HashSet<>();
        Set<String> visitedTail = new HashSet<>();
        visitedHead.add(beginWord);
        visitedTail.add(endWord);

        int level = 1; // Initialize the level.

        while (!head.isEmpty() && !tail.isEmpty()) {
            // Swap head and tail if head is larger to optimize.
            if (head.size() > tail.size()) {
                Set<String> temp = head;
                head = tail;
                tail = temp;
                Set<String> tempVisited = visitedHead;
                visitedHead = visitedTail;
                visitedTail = tempVisited;
            }

            Set<String> nextLevel = new HashSet<>(); // Store the next level's words.
            for (String word : head) {
                // Generate next words.
                for (String nextWord : getNextWords(word, dict)) {
                    if (visitedTail.contains(nextWord)) {
                        return level + 1; // Found the intersection.
                    }
                    if (!visitedHead.contains(nextWord)) {
                        visitedHead.add(nextWord);
                        nextLevel.add(nextWord);
                    }
                }
            }
            head = nextLevel; // Move to the next level.
            level++;
        }
        return 0;
    }


    /**
     * Solves the Word Ladder problem using Depth-First Search (DFS).
     * DFS is generally not preferred for shortest path problems like Word Ladder
     * because it doesn't guarantee finding the shortest path.  This is included
     * for completeness and comparison.
     *
     * @param beginWord The starting word.
     * @param endWord The target word.
     * @param wordList The list of words in the dictionary.
     * @return The length of the shortest transformation sequence, or 0 if no such sequence exists.
     *
     * Time Complexity:  O(M * N!), where N is the number of words and M is the word length, in the worst case.
     * Space Complexity: O(N), for the recursion stack and visited set.
     */
    public int ladderLengthDFS(String beginWord, String endWord, List<String> wordList) {
        if (!wordList.contains(endWord)) {
            return 0;
        }
        Set<String> dict = new HashSet<>(wordList);
        Set<String> visited = new HashSet<>();
        // minLen stores the shortest path length found so far.  Initialize it to a large value.
        final int[] minLen = {Integer.MAX_VALUE};
        visited.add(beginWord);
        // Start the DFS from the beginWord.
        dfs(beginWord, endWord, dict, visited, 1, minLen);
        return minLen[0] == Integer.MAX_VALUE ? 0 : minLen[0];
    }

    private void dfs(String currentWord, String endWord, Set<String> dict, Set<String> visited, int level, final int[] minLen) {
        if (currentWord.equals(endWord)) {
            minLen[0] = level; // Update the minimum length.
            return;
        }

        // Explore all possible next words.
        for (String nextWord : getNextWords(currentWord, dict)) {
            if (!visited.contains(nextWord) && level < minLen[0]) { // Optimization: Prune if current level is already longer than minLen
                visited.add(nextWord);
                dfs(nextWord, endWord, dict, visited, level + 1, minLen);
                visited.remove(nextWord); // Backtrack.
            }
        }
    }

    /**
     * Solves the Word Ladder problem using A* search algorithm.
     * A* is an informed search algorithm that uses a heuristic to guide the search.
     * In this case, the heuristic is the Manhattan distance (number of different characters)
     * between the current word and the end word.
     *
     * @param beginWord The starting word.
     * @param endWord The target word.
     * @param wordList The list of words in the dictionary.
     * @return The length of the shortest transformation sequence, or 0 if no such sequence exists.
     *
     * Time Complexity:  Difficult to express precisely, but generally better than BFS in many cases due to the heuristic.
     * Space Complexity: O(N), for the priority queue and visited set.
     */
    public int ladderLengthAStar(String beginWord, String endWord, List<String> wordList) {
        if (!wordList.contains(endWord)) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        // Priority queue to store words to visit, prioritized by f-score (g-score + h-score).
        PriorityQueue<WordNode> pq = new PriorityQueue<>(Comparator.comparingInt(WordNode::getFScore));
        // Map to store the g-score (cost from start to current node) for each word.
        Map<String, Integer> gScore = new HashMap<>();
        gScore.put(beginWord, 1); // Cost from start to start is 1.

        // Calculate the heuristic (h-score) for the start word.
        int hScore = getHeuristic(beginWord, endWord);
        pq.offer(new WordNode(beginWord, 1 + hScore)); // Add start word to PQ.

        Set<String> visited = new HashSet<>(); // Keep track of visited words.
        visited.add(beginWord);

        while (!pq.isEmpty()) {
            WordNode current = pq.poll();
            String currentWord = current.word;

            if (currentWord.equals(endWord)) {
                return gScore.get(currentWord); // Return the g-score, which is the shortest path length.
            }

            for (String nextWord : getNextWords(currentWord, dict)) {
                if (!visited.contains(nextWord)) {
                    visited.add(nextWord);
                    int tentativeGScore = gScore.get(currentWord) + 1; // Cost to reach nextWord.
                    gScore.put(nextWord, tentativeGScore);
                    hScore = getHeuristic(nextWord, endWord);
                    pq.offer(new WordNode(nextWord, tentativeGScore + hScore));
                } else {
                    // Important: Update g-score if a shorter path is found.
                    int tentativeGScore = gScore.get(currentWord) + 1;
                    if (tentativeGScore < gScore.get(nextWord)) {
                        gScore.put(nextWord, tentativeGScore);
                        hScore = getHeuristic(nextWord, endWord);
                        // Re-add to the priority queue with the updated f-score.
                        pq.offer(new WordNode(nextWord, tentativeGScore + hScore));
                    }
                }
            }
        }
        return 0;
    }

    /**
     * Computes the Manhattan distance (number of different characters) between two words.
     * This is used as the heuristic for the A* search algorithm.
     */
    private int getHeuristic(String word1, String word2) {
        int diff = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                diff++;
            }
        }
        return diff;
    }

    // Inner class to represent a word and its f-score for A* search.
    private static class WordNode {
        String word;
        int fScore;

        public WordNode(String word, int fScore) {
            this.word = word;
            this.fScore = fScore;
        }

        public int getFScore() {
            return fScore;
        }
    }



    /**
     * Solves the Word Ladder problem using a precomputed graph and BFS.
     * This approach precomputes all possible one-letter neighbors for each word
     * in the dictionary, which can speed up the search, especially for larger dictionaries.
     *
     * @param beginWord The starting word.
     * @param endWord The target word.
     * @param wordList The list of words in the dictionary.
     * @return The length of the shortest transformation sequence, or 0 if no such sequence exists.
     *
     * Time Complexity: O(N + M^2 * N + M * E), where N is the number of words, M is the word length, and E is the number of edges in the graph.
     * Space Complexity: O(N + E), to store the graph.
     */
    public int ladderLengthPrecomputedGraph(String beginWord, String endWord, List<String> wordList) {
        if (!wordList.contains(endWord)) {
            return 0;
        }

        Set<String> dict = new HashSet<>(wordList);
        dict.add(beginWord); // Ensure beginWord is in the dictionary.

        // 1. Build the graph.
        Map<String, List<String>> graph = buildGraph(dict);

        // 2. Perform BFS on the precomputed graph.
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
                // Use the precomputed neighbors from the graph.
                List<String> neighbors = graph.get(currentWord);
                if (neighbors != null) { // Check if the word has neighbors.
                    for (String neighbor : neighbors) {
                        if (!visited.contains(neighbor)) {
                            visited.add(neighbor);
                            queue.offer(neighbor);
                        }
                    }
                }
            }
            level++;
        }
        return 0;
    }

    /**
     * Builds a graph where nodes are words and edges connect words that differ by one letter.
     *
     * @param dict The set of words.
     * @return A map representing the graph, where keys are words and values are lists of their neighbors.
     */
    private Map<String, List<String>> buildGraph(Set<String> dict) {
        Map<String, List<String>> graph = new HashMap<>();
        for (String word : dict) {
            graph.put(word, new ArrayList<>()); // Initialize an empty list for each word.
        }

        for (String word1 : dict) {
            for (String word2 : dict) {
                if (isOneLetterDiff(word1, word2)) {
                    // Add edges in both directions since the graph is undirected.
                    graph.get(word1).add(word2);
                    graph.get(word2).add(word1);
                }
            }
        }
        return graph;
    }

    /**
     * Checks if two words differ by exactly one letter.
     *
     * @param word1 The first word.
     * @param word2 The second word.
     * @return true if the words differ by one letter, false otherwise.
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



    public static void main(String[] args) {
        WordLadder wordLadder = new WordLadder();
        String beginWord = "hit";
        String endWord = "cog";
        List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        // Test BFS
        System.out.println("BFS Result: " + wordLadder.ladderLengthBFS(beginWord, endWord, wordList)); // Expected: 5

        // Test Bidirectional BFS
        System.out.println("Bi-BFS Result: " + wordLadder.ladderLengthBiBFS(beginWord, endWord, wordList)); // Expected: 5

        // Test DFS
        System.out.println("DFS Result: " + wordLadder.ladderLengthDFS(beginWord, endWord, wordList)); // Expected: 5 (but not guaranteed to be shortest)

        // Test A*
        System.out.println("A* Result: " + wordLadder.ladderLengthAStar(beginWord, endWord, wordList)); // Expected: 5

        // Test Precomputed Graph + BFS
        System.out.println("Precomputed Graph + BFS Result: " + wordLadder.ladderLengthPrecomputedGraph(beginWord, endWord, wordList)); // Expected: 5
    }
}


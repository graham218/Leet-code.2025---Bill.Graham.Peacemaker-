import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


// Class to represent the Trie data structure
class Trie {
    public static void main(String[] args) {
        WordSearchII solution = new WordSearchII();
        char[][] board = {
                {'o', 'a', 'a', 'n'},
                {'e', 't', 'a', 'e'},
                {'i', 'h', 'k', 'r'},
                {'i', 'f', 'l', 'v'}
        };
        String[] words = {"oath", "pea", "eat", "rain"};

        System.out.println("Approach 1: " + solution.findWords1(board, words));
        System.out.println("Approach 2: " + solution.findWords2(board, words));
        System.out.println("Approach 3: " + solution.findWords3(board, words));
        System.out.println("Approach 4: " + solution.findWords4(board, words));
        System.out.println("Approach 5: " + solution.findWords5(board, words));
    }

    TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    // Method to insert a word into the Trie
    public void insert(String word) {
        TrieNode current = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (current.children[index] == null) {
                current.children[index] = new TrieNode();
            }
            current = current.children[index];
        }
        current.isEndOfWord = true;
        current.word = word; // Store the complete word at the end node
    }
}

public class WordSearchII {

    // 1.  Backtracking with Trie - Basic Implementation
    //     -   Uses a Trie to store words and backtracking to search the board.
    //     -   Good for understanding the basic approach.
    //     -   Time Complexity: O(M * N * 4^L), where M is rows, N is cols, L is longest word.
    //     -   Space Complexity: O(W), where W is the total number of characters in words.
    public List<String> findWords1(char[][] board, String[] words) {
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }
        Set<String> result = new HashSet<>();
        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                search1(board, i, j, trie.root, result);
            }
        }
        return new ArrayList<>(result);
    }

    private void search1(char[][] board, int row, int col, TrieNode node, Set<String> result) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] == '#' || node == null) {
            return;
        }

        char c = board[row][col];
        int index = c - 'a';
        if (node.children[index] == null) {
            return;
        }

        node = node.children[index]; // Move to the next node in the trie
        if (node.isEndOfWord) {
            result.add(node.word);
        }

        // Mark the current cell as visited
        board[row][col] = '#';
        // Explore all 4 directions
        search1(board, row + 1, col, node, result);
        search1(board, row - 1, col, node, result);
        search1(board, row, col + 1, node, result);
        search1(board, row, col - 1, node, result);
        // Backtrack: Restore the original character
        board[row][col] = c;
    }

    // 2. Backtracking with Trie + Optimization 1: Early Stop
    //    - Optimized version of approach 1.  Stops searching a path
    //      as soon as it's clear no word can be formed.
    //    - Prunes unnecessary search paths, improving performance.
    //    - Time Complexity: O(M * N * 4^L), but performs better in average case.
    //    - Space Complexity: O(W)
    public List<String> findWords2(char[][] board, String[] words) {
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }
        Set<String> result = new HashSet<>();
        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                search2(board, i, j, trie.root, result);
            }
        }
        return new ArrayList<>(result);
    }

    private void search2(char[][] board, int row, int col, TrieNode node, Set<String> result) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] == '#' || node == null) {
            return;
        }

        char c = board[row][col];
        int index = c - 'a';
        if (node.children[index] == null) {
            return; // Stop if there's no matching prefix in Trie
        }

        node = node.children[index];
        if (node.isEndOfWord) {
            result.add(node.word);
            node.isEndOfWord = false; // Avoid duplicates, IMPORTANT for optimization
        }

        board[row][col] = '#';
        search2(board, row + 1, col, node, result);
        search2(board, row - 1, col, node, result);
        search2(board, row, col + 1, node, result);
        search2(board, row, col - 1, node, result);
        board[row][col] = c;
    }

    // 3. Backtracking with Trie + Optimization 2: Trie Node Modification
    //    - Further optimization of approach 2.  Instead of just setting
    //      isEndOfWord to false, we remove the word from the Trie node.
    //    - This prevents revisiting already found words and reduces search space.
    //     - Time Complexity: O(M * N * 4^L), but performs significantly better in practice.
    //    - Space Complexity: O(W)
    public List<String> findWords3(char[][] board, String[] words) {
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }
        Set<String> result = new HashSet<>();
        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                search3(board, i, j, trie, trie.root, result);
            }
        }
        return new ArrayList<>(result);
    }

    private void search3(char[][] board, int row, int col, Trie trie, TrieNode node, Set<String> result) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] == '#' || node == null) {
            return;
        }

        char c = board[row][col];
        int index = c - 'a';
        if (node.children[index] == null) {
            return;
        }

        TrieNode nextNode = node.children[index];
        if (nextNode.isEndOfWord) {
            result.add(nextNode.word);
            // Remove word from Trie to avoid duplicates and further searching
            nextNode.isEndOfWord = false;
            nextNode.word = null; // Important:  Clear the word!

        }

        board[row][col] = '#';
        search3(board, row + 1, col, trie, nextNode, result);
        search3(board, row - 1, col, trie, nextNode, result);
        search3(board, row, col + 1, trie, nextNode, result);
        search3(board, row, col - 1, trie, nextNode, result);
        board[row][col] = c;
    }

    // 4. Backtracking with Trie + Optimization 3:  Check for Empty Trie Node
    //    -  The most optimized version.  After finding a word, if a Trie node
    //       has no more children, we can effectively prune that node from the
    //       search space.
    //    -  This can significantly reduce the search space for large inputs.
    //    - Time Complexity: O(M * N * 4^L),  best practical performance.
    //    - Space Complexity: O(W)
    public List<String> findWords4(char[][] board, String[] words) {
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }
        Set<String> result = new HashSet<>();
        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                search4(board, i, j, trie, trie.root, result);
            }
        }
        return new ArrayList<>(result);
    }

    private void search4(char[][] board, int row, int col, Trie trie, TrieNode node, Set<String> result) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] == '#' || node == null) {
            return;
        }

        char c = board[row][col];
        int index = c - 'a';
        if (node.children[index] == null) {
            return;
        }

        TrieNode nextNode = node.children[index];
        if (nextNode.isEndOfWord) {
            result.add(nextNode.word);
            nextNode.isEndOfWord = false;
            nextNode.word = null;
        }

        board[row][col] = '#';
        search4(board, row + 1, col, trie, nextNode, result);
        search4(board, row - 1, col, trie, nextNode, result);
        search4(board, row, col + 1, trie, nextNode, result);
        search4(board, row, col - 1, trie, nextNode, result);
        board[row][col] = c;

        // After exploring all paths from the current node, check if it has become empty.
        boolean hasChildren = false;
        for (int i = 0; i < 26; i++) {
            if (nextNode.children[i] != null) {
                hasChildren = true;
                break;
            }
        }
        if (!hasChildren) {
            // If the node has no children, remove it from its parent.
            node.children[index] = null;
        }
    }

    // 5.  Iterative Approach using Depth-First Search (DFS) with Trie
    //     -   Implements an iterative DFS using a stack to avoid recursion.
    //     -   Useful for very large boards where recursion might lead to stack overflow.
    //     -   Time Complexity: O(M * N * 4^L)
    //     -   Space Complexity: O(W + M * N),  W for Trie, M*N for stack in worst case.
    public List<String> findWords5(char[][] board, String[] words) {
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }
        Set<String> result = new HashSet<>();
        int rows = board.length;
        int cols = board[0].length;
        // Use a Stack to simulate DFS
        java.util.Stack<State> stack = new java.util.Stack<>();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                stack.push(new State(i, j, trie.root)); // Start DFS from each cell
                while (!stack.isEmpty()) {
                    State currentState = stack.pop();
                    int row = currentState.row;
                    int col = currentState.col;
                    TrieNode node = currentState.node;

                    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] == '#' || node == null) {
                        continue;
                    }

                    char c = board[row][col];
                    int index = c - 'a';
                    if (node.children[index] == null) {
                        continue;
                    }

                    TrieNode nextNode = node.children[index];
                    if (nextNode.isEndOfWord) {
                        result.add(nextNode.word);
                        nextNode.isEndOfWord = false;
                        nextNode.word = null;
                    }
                    board[row][col] = '#'; // Mark visited

                    stack.push(new State(row + 1, col, nextNode));
                    stack.push(new State(row - 1, col, nextNode));
                    stack.push(new State(row, col + 1, nextNode));
                    stack.push(new State(row, col - 1, nextNode));

                    board[row][col] = c; // Backtrack
                }
            }
        }
        return new ArrayList<>(result);
    }

    // Helper class for iterative DFS
    private static class State {
        int row;
        int col;
        TrieNode node;

        public State(int row, int col, TrieNode node) {
            this.row = row;
            this.col = col;
            this.node = node;
        }
    }
}

// Class to represent a node in the Trie
class TrieNode {
    TrieNode[] children;
    String word; // Stores the complete word if this node represents the end of a word
    boolean isEndOfWord;

    public TrieNode() {
        children = new TrieNode[26]; // For 'a' to 'z'
        word = null;
        isEndOfWord = false;
    }
}

/*
Real-world project implementation scenarios for each approach:

1.  Backtracking with Trie - Basic Implementation:
    -   Suitable for small-scale applications where performance is not critical.
    -   Example: A simple word search game in a mobile app with a limited dictionary.
    -   Educational tool to demonstrate Trie and backtracking concepts.

2.  Backtracking with Trie + Optimization 1: Early Stop:
    -   Applicable in scenarios where some optimization is needed.
    -   Example: Implementing word search in a web application with a moderate-sized dictionary.
    -   Useful when response time is important but not extremely critical.

3.  Backtracking with Trie + Optimization 2: Trie Node Modification:
    -   Good for applications with a larger dictionary and more complex board configurations.
    -   Example: A word search puzzle generator or solver with a substantial word list.
    -   Improves efficiency by avoiding redundant searches.

4.  Backtracking with Trie + Optimization 3: Check for Empty Trie Node:
    -   Best for high-performance applications with very large dictionaries.
    -   Example: A server-side component for a multiplayer word game with a massive word database.
    -   Critical in scenarios where minimizing search space is essential for speed.

5.  Iterative Approach using Depth-First Search (DFS) with Trie:
    -   Essential for applications that need to handle extremely large boards or dictionaries.
    -   Example: A professional word search solver or a text analysis tool processing large datasets.
    -   Prevents stack overflow errors and provides a more robust solution.
*/

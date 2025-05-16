import java.util.Arrays;

public class WordSearch {

    /**
     * Approach 1: Basic Backtracking
     * -   Uses a recursive helper function to explore possible paths in the board.
     * -   Marks visited cells to avoid cycles.
     * -   Simple and easy to understand.
     */
    public boolean exist1(char[][] board, String word) {
        if (board == null || board.length == 0 || board[0].length == 0 || word == null || word.isEmpty()) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack1(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack1(char[][] board, String word, int index, int row, int col, boolean[][] visited) {
        if (index == word.length()) {
            return true; // Found the whole word
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || visited[row][col] || board[row][col] != word.charAt(index)) {
            return false; // Out of bounds, visited, or mismatch
        }

        visited[row][col] = true; // Mark as visited
        // Explore all four directions
        boolean found = backtrack1(board, word, index + 1, row + 1, col, visited) ||
                backtrack1(board, word, index + 1, row - 1, col, visited) ||
                backtrack1(board, word, index + 1, row, col + 1, visited) ||
                backtrack1(board, word, index + 1, row, col - 1, visited);

        visited[row][col] = false; // Backtrack: unmark visited for other paths
        return found;
    }

    /**
     * Approach 2: Backtracking with Optimized Visited Array
     * -   Similar to Approach 1, but optimizes the visited tracking.
     * -   Instead of a separate boolean array, it modifies the board itself.
     * -   Temporarily changes the cell value and then restores it.
     */
    public boolean exist2(char[][] board, String word) {
        if (board == null || board.length == 0 || board[0].length == 0 || word == null || word.isEmpty()) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack2(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack2(char[][] board, String word, int index, int row, int col) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] != word.charAt(index)) {
            return false;
        }

        char temp = board[row][col]; // Store the original character
        board[row][col] = '*';    // Mark as visited (using a character that won't appear in the board)

        boolean found = backtrack2(board, word, index + 1, row + 1, col) ||
                backtrack2(board, word, index + 1, row - 1, col) ||
                backtrack2(board, word, index + 1, row, col + 1) ||
                backtrack2(board, word, index + 1, row, col - 1);

        board[row][col] = temp; // Restore the original character (backtrack)
        return found;
    }

    /**
     * Approach 3: Iterative Backtracking with Stack
     * -   Uses a stack to simulate the recursive calls in backtracking.
     * -   Stores the current state (row, col, index) on the stack.
     * -   More complex to implement but avoids recursion overhead.
     */
    public boolean exist3(char[][] board, String word) {
        if (board == null || board.length == 0 || board[0].length == 0 || word == null || word.isEmpty()) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // Directions to explore

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == word.charAt(0)) { // Start of word found
                    java.util.Stack<int[]> stack = new java.util.Stack<>();
                    stack.push(new int[]{i, j, 0}); // Push initial state
                    board[i][j] = '*'; // Mark the starting cell as visited

                    while (!stack.isEmpty()) {
                        int[] current = stack.pop();
                        int row = current[0];
                        int col = current[1];
                        int index = current[2];

                        if (index == word.length() - 1) {
                            return true; // Whole word found
                        }

                        for (int[] dir : directions) {
                            int nextRow = row + dir[0];
                            int nextCol = col + dir[1];

                            if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols && board[nextRow][nextCol] == word.charAt(index + 1)) {
                                stack.push(new int[]{nextRow, nextCol, index + 1});
                                board[nextRow][nextCol] = '*'; // Mark visited
                                break; // Important: Only explore one direction at a time from current cell
                            }
                        }
                        // If no valid next cell, the current path is stuck, and the loop continues
                        // with the next element from the stack.
                    }
                    // Reset the board.
                    for (int r = 0; r < rows; r++) {
                        for (int c = 0; c < cols; c++) {
                            if (board[r][c] == '*') {
                                board[r][c] = word.charAt(0); // Only reset the starting point if needed for this approach.
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    /**
     * Approach 4: Backtracking with Early Termination
     * -   Improves upon the basic backtracking by adding a check
     * -   to see if a path is still promising before exploring it.
     * -   This can prune the search space and improve efficiency.
     */
    public boolean exist4(char[][] board, String word) {
        if (board == null || board.length == 0 || board[0].length == 0 || word == null || word.isEmpty()) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack4(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack4(char[][] board, String word, int index, int row, int col, boolean[][] visited) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || visited[row][col] || board[row][col] != word.charAt(index)) {
            return false;
        }

        visited[row][col] = true;

        // Early termination check:
        // Check if any neighbor matches the next character. If not, no need to continue exploring this path.
        boolean found = false;
        if (index + 1 < word.length()) { // Important check to avoid out of bounds access to word
            char nextChar = word.charAt(index + 1);
            if ( (row + 1 < board.length && board[row+1][col] == nextChar && !visited[row+1][col]) ||
                    (row - 1 >= 0 && board[row-1][col] == nextChar && !visited[row-1][col]) ||
                    (col + 1 < board[0].length && board[row][col+1] == nextChar && !visited[row][col+1]) ||
                    (col - 1 >= 0 && board[row][col-1] == nextChar && !visited[row][col-1]) ||
                    index + 1 == word.length()
            )
            {
                found = backtrack4(board, word, index + 1, row + 1, col, visited) ||
                        backtrack4(board, word, index + 1, row - 1, col, visited) ||
                        backtrack4(board, word, index + 1, row, col + 1, visited) ||
                        backtrack4(board, word, index + 1, row, col - 1, visited);
            }
        } else {
            found = backtrack4(board, word, index + 1, row + 1, col, visited) ||
                    backtrack4(board, word, index + 1, row - 1, col, visited) ||
                    backtrack4(board, word, index + 1, row, col + 1, visited) ||
                    backtrack4(board, word, index + 1, row, col - 1, visited);
        }

        visited[row][col] = false;
        return found;
    }

    /**
     * Approach 5: Backtracking with Trie
     * -   Uses a Trie data structure to efficiently check if a prefix of the word exists.
     * -   Can be very efficient for multiple word searches on the same board.
     * -  Trie construction adds some overhead, but speeds up the search.
     */
    static class TrieNode {
        TrieNode[] children = new TrieNode[26]; // 'a' to 'z'
        boolean isEndOfWord;
    }

    static class Trie {
        TrieNode root = new TrieNode();

        void insert(String word) {
            TrieNode node = root;
            for (char c : word.toCharArray()) {
                int index = c - 'A'; // Assuming uppercase letters
                if (node.children[index] == null) {
                    node.children[index] = new TrieNode();
                }
                node = node.children[index];
            }
            node.isEndOfWord = true;
        }

        boolean startsWith(String prefix) {
            TrieNode node = root;
            for (char c : prefix.toCharArray()) {
                int index = c - 'A';
                if (node.children[index] == null) {
                    return false;
                }
                node = node.children[index];
            }
            return true;
        }
    }

    public boolean exist5(char[][] board, String word) {
        if (board == null || board.length == 0 || board[0].length == 0 || word == null || word.isEmpty()) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];
        Trie trie = new Trie();
        trie.insert(word); // Build Trie

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack5(board, word, 0, i, j, visited, trie)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack5(char[][] board, String word, int index, int row, int col, boolean[][] visited, Trie trie) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || visited[row][col] || board[row][col] != word.charAt(index)) {
            return false;
        }

        visited[row][col] = true;
        String prefix = word.substring(0, index + 1);
        if (!trie.startsWith(prefix))
        {
            visited[row][col] = false;
            return false;
        }

        boolean found = backtrack5(board, word, index + 1, row + 1, col, visited, trie) ||
                backtrack5(board, word, index + 1, row - 1, col, visited, trie) ||
                backtrack5(board, word, index + 1, row, col + 1, visited, trie) ||
                backtrack5(board, word, index + 1, row, col - 1, visited, trie);

        visited[row][col] = false;
        return found;
    }

    public static void main(String[] args) {
        WordSearch wordSearch = new WordSearch();
        char[][] board = {
                {'A', 'B', 'C', 'E'},
                {'S', 'F', 'C', 'S'},
                {'A', 'D', 'E', 'E'}
        };
        String word1 = "ABCCED";
        String word2 = "SEE";
        String word3 = "ABCB";
        String word4 = "ASF";
        String word5 = "XYZ";

        // Test cases for Approach 1
        System.out.println("Approach 1:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist1(board, word1)); // true
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist1(board, word2)); // true
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist1(board, word3)); // false
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist1(board, word4)); // true
        System.out.println("Word \"" + word5 + "\" found: " + wordSearch.exist1(board, word5)); // false
        System.out.println();

        // Test cases for Approach 2
        System.out.println("Approach 2:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist2(board, word1));
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist2(board, word2));
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist2(board, word3));
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist2(board, word4));
        System.out.println("Word \"" + word5 + "\" found: " + wordSearch.exist2(board, word5));
        System.out.println();

        // Test cases for Approach 3
        System.out.println("Approach 3:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist3(board, word1));
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist3(board, word2));
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist3(board, word3));
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist3(board, word4));
        System.out.println("Word \"" + word5 + "\" found: " + wordSearch.exist3(board, word5));
        System.out.println();

        // Test cases for Approach 4
        System.out.println("Approach 4:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist4(board, word1));
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist4(board, word2));
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist4(board, word3));
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist4(board, word4));
        System.out.println("Word \"" + word5 + "\" found: " + wordSearch.exist4(board, word5));
        System.out.println();

        // Test cases for Approach 5
        System.out.println("Approach 5:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist5(board, word1));
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist5(board, word2));
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist5(board, word3));
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist5(board, word4));
        System.out.println("Word \"" + word5 + "\" found: " + wordSearch.exist5(board, word5));
        System.out.println();
    }
}


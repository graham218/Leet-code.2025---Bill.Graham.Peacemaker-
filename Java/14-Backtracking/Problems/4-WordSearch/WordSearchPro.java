import java.util.ArrayList;
import java.util.List;

public class WordSearch {

    /**
     * Approach 1: Basic Backtracking
     *
     * This is the most straightforward backtracking solution.  It explores each cell
     * in the board and tries to match the word starting from that cell.
     *
     * Time Complexity: O(M * N * 4^L) where M is the number of rows, N is the
     * number of columns, and L is the length of the word.  For each cell,
     * we explore up to 4 directions, and the depth of the exploration is L.
     * Space Complexity: O(L) for the recursion stack, where L is the length of the word.
     */
    public boolean exist(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack1(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack1(char[][] board, int row, int col, String word, int index) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] != word.charAt(index)) {
            return false;
        }

        char temp = board[row][col];  // Store the current cell's character
        board[row][col] = '#';       // Mark the cell as visited (important for backtracking)

        // Explore all four directions
        boolean found = backtrack1(board, row + 1, col, word, index + 1) ||
                backtrack1(board, row - 1, col, word, index + 1) ||
                backtrack1(board, row, col + 1, word, index + 1) ||
                backtrack1(board, row, col - 1, word, index + 1);

        board[row][col] = temp;  // Restore the original character (backtracking step)
        return found;
    }

    /**
     * Approach 2: Backtracking with Visited Array
     *
     * This approach uses a separate boolean array to keep track of visited cells.
     * This avoids modifying the original board, which might be preferred in some
     * applications where the board should remain unchanged.
     *
     * Time Complexity: O(M * N * 4^L)
     * Space Complexity: O(M * N + L), for the visited array and recursion stack.
     */
    public boolean exist2(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack2(board, i, j, word, 0, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack2(char[][] board, int row, int col, String word, int index, boolean[][] visited) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || visited[row][col] || board[row][col] != word.charAt(index)) {
            return false;
        }

        visited[row][col] = true; // Mark as visited

        boolean found = backtrack2(board, row + 1, col, word, index + 1, visited) ||
                backtrack2(board, row - 1, col, word, index + 1, visited) ||
                backtrack2(board, row, col + 1, word, index + 1, visited) ||
                backtrack2(board, row, col - 1, word, index + 1, visited);

        visited[row][col] = false; // Backtrack: mark as not visited
        return found;
    }

    /**
     * Approach 3: Backtracking with Early Pruning
     *
     * This approach adds a small optimization: if the first character of the word
     * doesn't match the current cell, we can immediately return false.  This can
     * improve performance in cases where the board has many cells that don't
     * match the beginning of the word.
     *
     * Time Complexity: O(M * N * 4^L) in the worst case, but can be faster in practice.
     * Space Complexity: O(L)
     */
    public boolean exist3(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == word.charAt(0) && backtrack3(board, i, j, word, 0)) { // Early pruning
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack3(char[][] board, int row, int col, String word, int index) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] != word.charAt(index)) {
            return false;
        }

        char temp = board[row][col];
        board[row][col] = '#';

        boolean found = backtrack3(board, row + 1, col, word, index + 1) ||
                backtrack3(board, row - 1, col, word, index + 1) ||
                backtrack3(board, row, col + 1, word, index + 1) ||
                backtrack3(board, row, col - 1, word, index + 1);

        board[row][col] = temp;
        return found;
    }

    /**
     * Approach 4: Iterative DFS with Stack
     *
     * This approach uses a stack to perform Depth-First Search iteratively.  This
     * can be useful in situations where recursion depth might be a concern, or
     * for better control over the search process.
     *
     * Time Complexity: O(M * N * 4^L)
     * Space Complexity: O(M * N * L) in the worst case, if the stack holds many paths.
     */
    public boolean exist4(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == word.charAt(0)) {
                    // Use a Stack to store the state of each path we are exploring
                    java.util.Stack<int[]> stack = new java.util.Stack<>();
                    stack.push(new int[]{i, j, 0}); // {row, col, wordIndex}
                    boolean[][] visited = new boolean[rows][cols];
                    visited[i][j] = true;

                    while (!stack.isEmpty()) {
                        int[] current = stack.pop();
                        int row = current[0];
                        int col = current[1];
                        int index = current[2];

                        if (index == word.length() - 1) {
                            return true;
                        }

                        // Explore neighbors
                        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
                        for (int[] dir : directions) {
                            int nextRow = row + dir[0];
                            int nextCol = col + dir[1];

                            if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols &&
                                    !visited[nextRow][nextCol] && board[nextRow][nextCol] == word.charAt(index + 1)) {
                                stack.push(new int[]{nextRow, nextCol, index + 1});
                                visited[nextRow][nextCol] = true;
                                break; // Important:  Avoid pushing multiple paths for the same cell
                            }
                        }
                    }
                }
            }
        }
        return false;
    }



    /**
     * Approach 5: Optimized Backtracking with Direction Array and Single Visit Array
     *
     * This approach combines the visited array with a direction array for more concise
     * neighbor exploration. It aims to improve code readability and potentially
     * offer slight performance gains by reducing redundant code.  It also uses only one visited array.
     *
     * Time Complexity: O(M * N * 4^L)
     * Space Complexity: O(M * N + L)
     */
    public boolean exist5(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // Store directions

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack5(board, i, j, word, 0, visited, directions)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack5(char[][] board, int row, int col, String word, int index, boolean[][] visited, int[][] directions) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || visited[row][col] || board[row][col] != word.charAt(index)) {
            return false;
        }

        visited[row][col] = true; // Mark as visited

        // Explore neighbors using the direction array
        for (int[] dir : directions) {
            int nextRow = row + dir[0];
            int nextCol = col + dir[1];
            if (backtrack5(board, nextRow, nextCol, word, index + 1, visited, directions)) {
                return true;
            }
        }

        visited[row][col] = false; // Backtrack
        return false;
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
        String word4 = "ASFC";

        // Test Approach 1
        System.out.println("Approach 1:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist(board, word1)); // true
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist(board, word2)); // true
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist(board, word3)); // false
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist(board, word4)); // true

        // Test Approach 2
        System.out.println("\nApproach 2:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist2(board, word1)); // true
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist2(board, word2)); // true
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist2(board, word3)); // false
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist2(board, word4)); // true

        // Test Approach 3
        System.out.println("\nApproach 3:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist3(board, word1)); // true
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist3(board, word2)); // true
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist3(board, word3)); // false
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist3(board, word4)); // true

        // Test Approach 4
        System.out.println("\nApproach 4:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist4(board, word1)); // true
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist4(board, word2)); // true
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist4(board, word3)); // false
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist4(board, word4)); // true

        // Test Approach 5
        System.out.println("\nApproach 5:");
        System.out.println("Word \"" + word1 + "\" found: " + wordSearch.exist5(board, word1));
        System.out.println("Word \"" + word2 + "\" found: " + wordSearch.exist5(board, word2));
        System.out.println("Word \"" + word3 + "\" found: " + wordSearch.exist5(board, word3));
        System.out.println("Word \"" + word4 + "\" found: " + wordSearch.exist5(board, word4));
    }
}


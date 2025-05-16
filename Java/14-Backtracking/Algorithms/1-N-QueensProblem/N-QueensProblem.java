import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class NQueens {

    public static void main(String[] args) {
        int n = 8; // Change this to the desired board size

        System.out.println("N-Queens Solutions for n = " + n);

        System.out.println("\n1. Backtracking with explicit board representation:");
        List<List<String>> solutions1 = solveNQueens1(n);
        printSolutions(solutions1);

        System.out.println("\n2. Backtracking with 1D array representation:");
        List<List<String>> solutions2 = solveNQueens2(n);
        printSolutions(solutions2);

        System.out.println("\n3. Backtracking with bit manipulation:");
        List<List<String>> solutions3 = solveNQueens3(n);
        printSolutions(solutions3);

        System.out.println("\n4. Iterative Backtracking:");
        List<List<String>> solutions4 = solveNQueens4(n);
        printSolutions(solutions4);

        System.out.println("\n5. Optimized Backtracking with Pruning:");
        List<List<String>> solutions5 = solveNQueens5(n);
        printSolutions(solutions5);
    }

    // Helper function to print the solutions in a user-friendly format
    private static void printSolutions(List<List<String>> solutions) {
        if (solutions.isEmpty()) {
            System.out.println("No solutions found.");
            return;
        }
        System.out.println("Total solutions: " + solutions.size());
        for (int i = 0; i < solutions.size(); i++) {
            System.out.println("Solution " + (i + 1) + ":");
            for (String row : solutions.get(i)) {
                System.out.println(row);
            }
            System.out.println();
        }
    }

    // 1. Backtracking with explicit board representation (char[][])
    //   - Uses a 2D char array to represent the board.
    //   - The most straightforward and intuitive approach.
    public static List<List<String>> solveNQueens1(int n) {
        List<List<String>> solutions = new ArrayList<>();
        char[][] board = new char[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(board[i], '.'); // Initialize the board with empty cells
        }
        solveNQueens1Helper(board, 0, solutions);
        return solutions;
    }

    private static void solveNQueens1Helper(char[][] board, int row, List<List<String>> solutions) {
        if (row == board.length) {
            solutions.add(boardToStringList(board)); // Found a valid solution, add it to the result
            return;
        }

        for (int col = 0; col < board.length; col++) {
            if (isSafe1(board, row, col)) {
                board[row][col] = 'Q'; // Place the queen
                solveNQueens1Helper(board, row + 1, solutions); // Recur for the next row
                board[row][col] = '.'; // Backtrack: Remove the queen to try other positions
            }
        }
    }

    private static boolean isSafe1(char[][] board, int row, int col) {
        // Check the column for conflicts
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        // Check the left diagonal for conflicts
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        // Check the right diagonal for conflicts
        for (int i = row - 1, j = col + 1; i >= 0 && j < board.length; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }

    private static List<String> boardToStringList(char[][] board) {
        List<String> list = new ArrayList<>();
        for (char[] row : board) {
            list.add(new String(row)); // Convert each row (char array) to a String
        }
        return list;
    }


    // 2. Backtracking with 1D array representation
    //    - Uses a 1D array to represent the column position of the queen in each row.
    //    - More space-efficient than the 2D array approach.
    public static List<List<String>> solveNQueens2(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n]; // queens[i] = column position of the queen in row i
        solveNQueens2Helper(queens, 0, solutions);
        return solutions;
    }

    private static void solveNQueens2Helper(int[] queens, int row, List<List<String>> solutions) {
        if (row == queens.length) {
            solutions.add(boardToStringList2(queens));
            return;
        }

        for (int col = 0; col < queens.length; col++) {
            if (isSafe2(queens, row, col)) {
                queens[row] = col;
                solveNQueens2Helper(queens, row + 1, solutions);
                // No explicit backtracking needed, the next iteration of the loop will overwrite queens[row]
            }
        }
    }

    private static boolean isSafe2(int[] queens, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (queens[i] == col || Math.abs(queens[i] - col) == row - i) {
                return false;
            }
        }
        return true;
    }

    private static List<String> boardToStringList2(int[] queens) {
        List<String> board = new ArrayList<>();
        for (int queen : queens) {
            char[] row = new char[queens.length];
            Arrays.fill(row, '.');
            row[queen] = 'Q';
            board.add(new String(row));
        }
        return board;
    }

    // 3. Backtracking with bit manipulation
    //    - Uses bit manipulation to represent the board and check for safe positions.
    //    - The most efficient approach in terms of performance.
    public static List<List<String>> solveNQueens3(int n) {
        List<List<String>> solutions = new ArrayList<>();
        solveNQueens3Helper(n, 0, 0, 0, 0, new int[n], solutions);
        return solutions;
    }

    private static void solveNQueens3Helper(int n, int row, int cols, int leftDiags, int rightDiags, int[] queens, List<List<String>> solutions) {
        if (row == n) {
            solutions.add(boardToStringList2(queens));
            return;
        }

        int availablePositions = ((1 << n) - 1) & (~(cols | leftDiags | rightDiags)); // Available positions for this row
        while (availablePositions != 0) {
            int p = availablePositions & (-availablePositions); // Get the rightmost set bit (position of the next queen)
            availablePositions &= (availablePositions - 1);    // Remove the rightmost set bit
            int col = Integer.bitCount(p - 1); // Calculate the column index from the bit position
            queens[row] = col;
            solveNQueens3Helper(n, row + 1, cols | p, (leftDiags | p) << 1, (rightDiags | p) >> 1, queens, solutions);
        }
    }

    // 4. Iterative Backtracking
    //   - Solves the N-Queens problem using an iterative approach with a stack.
    //   - Avoids recursion, which can be beneficial for very large values of N.
    public static List<List<String>> solveNQueens4(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n]; // Array to store column positions of queens
        int row = 0;

        while (row >= 0) {
            // Find a safe column for the queen in the current row
            while (queens[row] < n && !isSafe2(queens, row, queens[row])) {
                queens[row]++;
            }

            if (queens[row] < n) { // Found a safe position
                if (row == n - 1) { // If it's the last row, we have a solution
                    solutions.add(boardToStringList2(queens));
                    queens[row] = 0; // Reset for finding more solutions
                    row--;
                } else {
                    row++;         // Move to the next row
                    queens[row] = 0; // Initialize the column for the next row
                }
            } else {             // No safe position found in this row
                queens[row] = 0; // Reset the column for backtracking
                row--;             // Backtrack to the previous row
            }
        }
        return solutions;
    }

    // 5. Optimized Backtracking with Pruning
    //    - Uses sets to keep track of occupied columns, diagonals to optimize the isSafe check.
    //    -  Improves the efficiency of the backtracking process by avoiding redundant checks.
    public static List<List<String>> solveNQueens5(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n];
        boolean[] cols = new boolean[n];       // Tracks columns
        boolean[] leftDiags = new boolean[2 * n - 1];  // Tracks left diagonals (row + col)
        boolean[] rightDiags = new boolean[2 * n - 1]; // Tracks right diagonals (row - col + n - 1)
        solveNQueens5Helper(queens, 0, cols, leftDiags, rightDiags, solutions);
        return solutions;
    }

    private static void solveNQueens5Helper(int[] queens, int row, boolean[] cols, boolean[] leftDiags, boolean[] rightDiags, List<List<String>> solutions) {
        if (row == queens.length) {
            solutions.add(boardToStringList2(queens));
            return;
        }

        for (int col = 0; col < queens.length; col++) {
            int ldIndex = row + col;
            int rdIndex = row - col + queens.length - 1;

            if (!cols[col] && !leftDiags[ldIndex] && !rightDiags[rdIndex]) {
                queens[row] = col;
                cols[col] = true;
                leftDiags[ldIndex] = true;
                rightDiags[rdIndex] = true;
                solveNQueens5Helper(queens, row + 1, cols, leftDiags, rightDiags, solutions);
                // Backtrack
                cols[col] = false;
                leftDiags[ldIndex] = false;
                rightDiags[rdIndex] = false;
            }
        }
    }
}


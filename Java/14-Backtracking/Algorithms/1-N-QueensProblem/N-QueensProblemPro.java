import java.util.ArrayList;
import java.util.List;

public class NQueens {

    /**
     * Solves the N-Queens problem using backtracking.
     *
     * The N-Queens problem asks to place N queens on an N×N chessboard
     * such that no two queens threaten each other. This means no two queens
     * can share the same row, column, or diagonal.
     *
     * This implementation provides five different approaches to solve the N-Queens problem:
     * 1.  **Simple Backtracking:** A basic backtracking approach.
     * 2.  **Backtracking with Pruning:** An optimized backtracking approach that prunes invalid branches.
     * 3.  **Using Bit Manipulation:** A very efficient approach using bit manipulation.
     * 4. **Backtracking with Forward Checking: ** Includes a forward checking mechanism
     * 5. **Iterative Backtracking:** A non-recursive approach to solve the problem.
     *
     * Each approach is implemented as a separate method within the `NQueens` class.
     */

    public static void main(String[] args) {
        int n = 8; // Change this value to solve for different board sizes

        System.out.println("N-Queens Solutions for n = " + n + ":");

        System.out.println("\n1. Simple Backtracking:");
        List<List<String>> solutions1 = solveNQueensSimple(n);
        printSolutions(solutions1);

        System.out.println("\n2. Backtracking with Pruning:");
        List<List<String>> solutions2 = solveNQueensPruning(n);
        printSolutions(solutions2);

        System.out.println("\n3. Bit Manipulation:");
        List<List<String>> solutions3 = solveNQueensBitManipulation(n);
        printSolutions(solutions3);

        System.out.println("\n4. Backtracking with Forward Checking:");
        List<List<String>> solutions4 = solveNQueensForwardChecking(n);
        printSolutions(solutions4);

        System.out.println("\n5. Iterative Backtracking:");
        List<List<String>> solutions5 = solveNQueensIterative(n);
        printSolutions(solutions5);
    }

    // 1. Simple Backtracking
    // ----------------------

    /**
     * Solves the N-Queens problem using a simple backtracking algorithm.
     *
     * This method explores all possible placements of queens and backtracks
     * when a conflict is found.  It's the most straightforward approach but
     * can be less efficient for larger values of N.
     *
     * @param n The size of the chessboard.
     * @return A list of all possible solutions, where each solution is a list of strings
     * representing the board configuration.
     */
    public static List<List<String>> solveNQueensSimple(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n]; // Array to store the column position of the queen in each row
        solveNQueensSimpleHelper(n, 0, queens, solutions);
        return solutions;
    }

    /**
     * Recursive helper function for the simple backtracking approach.
     *
     * @param n         The size of the chessboard.
     * @param row       The current row being processed.
     * @param queens    Array to store queen placements.
     * @param solutions List to store the final solutions.
     */
    private static void solveNQueensSimpleHelper(int n, int row, int[] queens, List<List<String>> solutions) {
        if (row == n) {
            // If all queens are placed successfully, add the solution to the list.
            solutions.add(generateBoard(n, queens));
            return;
        }

        for (int col = 0; col < n; col++) {
            // Try placing a queen in each column of the current row.
            queens[row] = col;
            if (isValidPlacementSimple(queens, row)) {
                // If the placement is valid, recursively try to place the next queen.
                solveNQueensSimpleHelper(n, row + 1, queens, solutions);
            }
            // If the placement is invalid, or no solution is found in the recursive call,
            // the loop continues to the next column (backtracking).
        }
    }

    /**
     * Checks if the placement of a queen in the current row is valid.
     *
     * @param queens The array representing the column position of queens in each row.
     * @param row    The current row being checked.
     * @return True if the placement is valid, false otherwise.
     */
    private static boolean isValidPlacementSimple(int[] queens, int row) {
        for (int i = 0; i < row; i++) {
            // Check for conflicts with previously placed queens.
            if (queens[i] == queens[row] || Math.abs(queens[i] - queens[row]) == row - i) {
                // Two queens are in the same column or on the same diagonal.
                return false;
            }
        }
        return true;
    }


    // 2. Backtracking with Pruning
    // -----------------------------

    /**
     * Solves the N-Queens problem using backtracking with pruning.
     *
     * This approach optimizes the simple backtracking method by checking for
     * conflicts (same column or diagonal) *before* placing a queen. This
     * avoids unnecessary recursive calls and improves efficiency.
     *
     * @param n The size of the chessboard.
     * @return A list of all possible solutions.
     */
    public static List<List<String>> solveNQueensPruning(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n];
        solveNQueensPruningHelper(n, 0, queens, solutions);
        return solutions;
    }

    /**
     * Recursive helper function for backtracking with pruning.
     *
     * @param n         The size of the chessboard.
     * @param row       The current row being processed.
     * @param queens    Array to store queen placements.
     * @param solutions List to store the final solutions.
     */
    private static void solveNQueensPruningHelper(int n, int row, int[] queens, List<List<String>> solutions) {
        if (row == n) {
            solutions.add(generateBoard(n, queens));
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isValidPlacementPruning(queens, row, col)) { // Check validity *before* placing
                queens[row] = col;
                solveNQueensPruningHelper(n, row + 1, queens, solutions);
            }
        }
    }

    /**
     * Checks if placing a queen at (row, col) is valid.
     *
     * @param queens The array representing the column position of queens in each row.
     * @param row    The row to place the queen in.
     * @param col    The column to place the queen in.
     * @return True if the placement is valid, false otherwise.
     */
    private static boolean isValidPlacementPruning(int[] queens, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (queens[i] == col || Math.abs(queens[i] - col) == row - i) {
                return false;
            }
        }
        return true;
    }


    // 3. Bit Manipulation
    // --------------------

    /**
     * Solves the N-Queens problem using bit manipulation.
     *
     * This approach is highly efficient as it uses bitwise operations to represent
     * the board and check for conflicts.  It's significantly faster than the
     * backtracking methods, especially for larger boards.
     *
     * @param n The size of the chessboard.
     * @return A list of all possible solutions.
     */
    public static List<List<String>> solveNQueensBitManipulation(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n];
        long all = (1L << n) - 1; // Represents all columns being available
        solveNQueensBitManipulationHelper(n, 0, 0, 0, 0, all, queens, solutions);
        return solutions;
    }

    /**
     * Recursive helper function for the bit manipulation approach.
     *
     * @param n         The size of the chessboard.
     * @param row       The current row being processed.
     * @param ld        Bits representing blocked left diagonals.
     * @param rd        Bits representing blocked right diagonals.
     * @param cols      Bits representing blocked columns.
     * @param all       Bits representing all available columns.
     * @param queens    Array to store queen placements.
     * @param solutions List to store the final solutions.
     */
    private static void solveNQueensBitManipulationHelper(int n, int row, long ld, long rd, long cols, long all, int[] queens, List<List<String>> solutions) {
        if (row == n) {
            solutions.add(generateBoard(n, queens));
            return;
        }

        long possible = all & (~(ld | rd | cols)); // Available positions in this row
        while (possible != 0) {
            long p = possible & (-possible);       // Rightmost available position
            possible -= p;                         // Remove this position from possible
            int col = Long.numberOfTrailingZeros(p); // Convert bitmask to column index
            queens[row] = col;
            solveNQueensBitManipulationHelper(n, row + 1, (ld | p) << 1, (rd | p) >> 1, cols | p, all, queens, solutions);
        }
    }


    // 4. Backtracking with Forward Checking
    // ---------------------------------------
    /**
     * Solves the N-Queens problem using backtracking with forward checking.
     * Forward checking is a refinement of backtracking.  Instead of just checking
     * if a placement is valid *after* it's made, forward checking looks ahead
     * to see if there are any remaining valid placements in future rows.  If
     * a placement eliminates all possible placements in a future row, the
     * algorithm can backtrack immediately, avoiding unnecessary exploration.
     *
     * @param n The size of the chessboard.
     * @return A list of all possible solutions.
     */
    public static List<List<String>> solveNQueensForwardChecking(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n];
        // available[row][col] indicates if placing a queen at (row, col) is still possible
        boolean[][] available = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                available[i][j] = true;
            }
        }
        solveNQueensForwardCheckingHelper(n, 0, queens, available, solutions);
        return solutions;
    }

    /**
     * Recursive helper function for backtracking with forward checking.
     *
     * @param n         The size of the chessboard.
     * @param row       The current row being processed.
     * @param queens    Array to store queen placements.
     * @param available 2D array indicating available positions.
     * @param solutions List to store the final solutions.
     */
    private static void solveNQueensForwardCheckingHelper(int n, int row, int[] queens, boolean[][] available, List<List<String>> solutions) {
        if (row == n) {
            solutions.add(generateBoard(n, queens));
            return;
        }

        for (int col = 0; col < n; col++) {
            if (available[row][col]) {
                queens[row] = col;
                // Store the current state of 'available' to restore later (backtracking)
                boolean[][] savedAvailable = new boolean[n][n];
                for (int i = 0; i < n; i++) {
                    System.arraycopy(available[i], 0, savedAvailable[i], 0, n);
                }

                // Update 'available' to reflect the consequences of placing a queen at (row, col)
                updateAvailable(available, row, col, n, false); // Mark attacked positions as unavailable

                // Forward checking: Check if there are any valid placements in the next row
                if (hasValidPlacement(available, row + 1, n)) {
                    solveNQueensForwardCheckingHelper(n, row + 1, queens, available, solutions);
                }

                // Backtrack: Restore the 'available' array
                for (int i = 0; i < n; i++) {
                    System.arraycopy(savedAvailable[i], 0, available[i], 0, n);
                }
            }
        }
    }

    /**
     * Checks if there is at least one valid placement in the given row.
     *
     * @param available 2D array indicating available positions.
     * @param row       The row to check.
     * @param n         The size of the board.
     * @return True if there is a valid placement, false otherwise.
     */
    private static boolean hasValidPlacement(boolean[][] available, int row, int n) {
        if (row >= n) return true; // No need to check beyond the board
        for (int col = 0; col < n; col++) {
            if (available[row][col]) {
                return true; // Found a valid placement
            }
        }
        return false; // No valid placements in this row
    }

    /**
     * Updates the 'available' array to reflect the placement of a queen.
     *
     * @param available 2D array indicating available positions.
     * @param row       The row where the queen is placed.
     * @param col       The column where the queen is placed.
     * @param n         The size of the board.
     * @param setAvailable  if true, set the cells to true, otherwise false.
     */
    private static void updateAvailable(boolean[][] available, int row, int col, int n, boolean setAvailable) {
        for (int i = 0; i < n; i++) {
            available[row][i] = setAvailable; // Mark the entire row as unavailable
            available[i][col] = setAvailable; // Mark the entire column as unavailable
        }
        // Mark diagonals as unavailable
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            available[i][j] = setAvailable;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            available[i][j] = setAvailable;
        }
        for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
            available[i][j] = setAvailable;
        }
        for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
            available[i][j] = setAvailable;
        }
        available[row][col] = setAvailable; //mark the current cell
    }


    // 5. Iterative Backtracking
    // --------------------------
    /**
     * Solves the N-Queens problem using iterative backtracking.
     * This approach avoids recursion by using a stack (implemented with an array)
     * to keep track of the current state of the board.  It can be useful in
     * environments where recursion depth is limited.
     *
     * @param n The size of the chessboard.
     * @return A list of all possible solutions.
     */
    public static List<List<String>> solveNQueensIterative(int n) {
        List<List<String>> solutions = new ArrayList<>();
        int[] queens = new int[n];
        int row = 0;

        while (row >= 0) {
            // While we haven't backtracked past the first row
            if (row == n) {
                // If we've found a solution (all rows filled), save it
                solutions.add(generateBoard(n, queens));
                row--; // Backtrack to find more solutions
            } else {
                // Try to place a queen in the current row
                queens[row] = -1; // Initialize column to -1
                while (queens[row] < n - 1) {
                    // Try the next column
                    queens[row]++;
                    if (isValidPlacementIterative(queens, row)) {
                        // If the placement is valid, move to the next row
                        row++;
                        break; // Exit the column loop
                    }
                }
                if (queens[row] == n) {
                    // If we've tried all columns in this row without success, backtrack
                    row--;
                }
            }
        }
        return solutions;
    }

    /**
     * Checks if the placement of a queen in the current row is valid for iterative approach.
     *
     * @param queens The array representing the column position of queens in each row.
     * @param row    The current row being checked.
     * @return True if the placement is valid, false otherwise.
     */
    private static boolean isValidPlacementIterative(int[] queens, int row) {
        for (int i = 0; i < row; i++) {
            if (queens[i] == queens[row] || Math.abs(queens[i] - queens[row]) == row - i) {
                return false;
            }
        }
        return true;
    }


    // Helper Functions
    // --------------

    /**
     * Generates a board representation from the queen placement array.
     *
     * @param n      The size of the chessboard.
     * @param queens The array representing the column position of queens in each row.
     * @return A list of strings, where each string represents a row of the board.
     */
    private static List<String> generateBoard(int n, int[] queens) {
        List<String> board = new ArrayList<>();
        for (int row = 0; row < n; row++) {
            StringBuilder sb = new StringBuilder();
            for (int col = 0; col < n; col++) {
                if (queens[row] == col) {
                    sb.append('Q'); // Queen
                } else {
                    sb.append('.'); // Empty square
                }
            }
            board.add(sb.toString());
        }
        return board;
    }

    /**
     * Prints the solutions to the N-Queens problem in a user-friendly format.
     *
     * @param solutions A list of solutions, where each solution is a list of strings
     * representing the board configuration.
     */
    private static void printSolutions(List<List<String>> solutions) {
        if (solutions.isEmpty()) {
            System.out.println("No solutions found.");
            return;
        }
        System.out.println("Total solutions: " + solutions.size());
        for (int i = 0; i < solutions.size(); i++) {
            System.out.println("\nSolution " + (i + 1) + ":");
            List<String> board = solutions.get(i);
            for (String row : board) {
                System.out.println(row);
            }
        }
    }
}


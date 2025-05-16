import java.util.ArrayList;
import java.util.List;

public class SudokuSolver {

    // 1. Backtracking with Basic Constraint Checking
    //   - The most straightforward approach.
    //   - Checks row, column, and 3x3 box constraints after placing each number.
    //   - Can be slow for difficult Sudoku puzzles.
    public static boolean solveSudoku1(char[][] board) {
        return solve1(board, 0, 0);
    }

    private static boolean solve1(char[][] board, int row, int col) {
        if (row == 9) {
            return true; // Reached the end of the board, solution found.
        }

        if (col == 9) {
            return solve1(board, row + 1, 0); // Move to the next row.
        }

        if (board[row][col] != '.') {
            return solve1(board, row, col + 1); // Skip filled cells.
        }

        for (char num = '1'; num <= '9'; num++) {
            if (isValid1(board, row, col, num)) {
                board[row][col] = num; // Place the number.

                if (solve1(board, row, col + 1)) {
                    return true; // Solution found with this placement.
                }

                board[row][col] = '.'; // Backtrack: remove the number.
            }
        }
        return false; // No valid number found for this cell.
    }

    private static boolean isValid1(char[][] board, int row, int col, char num) {
        // Check row and column
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) return false;
            if (board[i][col] == num) return false;
        }

        // Check 3x3 box
        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;
        for (int i = boxRowStart; i < boxRowStart + 3; i++) {
            for (int j = boxColStart; j < boxColStart + 3; j++) {
                if (board[i][j] == num) return false;
            }
        }
        return true;
    }

    // 2. Backtracking with Precomputed Constraints
    //   - Optimizes constraint checking by precomputing possible values for each cell.
    //   - Uses boolean arrays to track used numbers in rows, columns, and boxes.
    //   - Faster than the basic approach, especially for larger boards.
    public static boolean solveSudoku2(char[][] board) {
        boolean[][] rowUsed = new boolean[9][10];
        boolean[][] colUsed = new boolean[9][10];
        boolean[][][] boxUsed = new boolean[3][3][10];

        // Precompute used numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    rowUsed[i][num] = true;
                    colUsed[j][num] = true;
                    boxUsed[i / 3][j / 3][num] = true;
                }
            }
        }
        return solve2(board, 0, 0, rowUsed, colUsed, boxUsed);
    }

    private static boolean solve2(char[][] board, int row, int col, boolean[][] rowUsed, boolean[][] colUsed, boolean[][][] boxUsed) {
        if (row == 9) {
            return true;
        }
        if (col == 9) {
            return solve2(board, row + 1, 0, rowUsed, colUsed, boxUsed);
        }
        if (board[row][col] != '.') {
            return solve2(board, row, col + 1, rowUsed, colUsed, boxUsed);
        }

        for (char numChar = '1'; numChar <= '9'; numChar++) {
            int num = numChar - '0';
            if (!rowUsed[row][num] && !colUsed[col][num] && !boxUsed[row / 3][col / 3][num]) {
                board[row][col] = numChar;
                rowUsed[row][num] = true;
                colUsed[col][num] = true;
                boxUsed[row / 3][col / 3][num] = true;

                if (solve2(board, row, col + 1, rowUsed, colUsed, boxUsed)) {
                    return true;
                }

                board[row][col] = '.';
                rowUsed[row][num] = false;
                colUsed[col][num] = false;
                boxUsed[row / 3][col / 3][num] = false;
            }
        }
        return false;
    }

    // 3. Backtracking with Optimized Search Order (Minimum Remaining Values)
    //   - Improves efficiency by selecting the cell with the fewest possible values first.
    //   - Reduces the branching factor in the search tree.
    //   - More complex to implement but often significantly faster.
    public static boolean solveSudoku3(char[][] board) {
        List<Cell> emptyCells = new ArrayList<>();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    emptyCells.add(new Cell(i, j));
                }
            }
        }
        // Sort cells by their possible values count
        emptyCells.sort((a, b) -> countPossibleValues(board, a.row, a.col) - countPossibleValues(board, b.row, b.col));

        return solve3(board, emptyCells, 0);
    }

    private static boolean solve3(char[][] board, List<Cell> emptyCells, int index) {
        if (index == emptyCells.size()) {
            return true;
        }

        Cell cell = emptyCells.get(index);
        int row = cell.row;
        int col = cell.col;

        for (char num = '1'; num <= '9'; num++) {
            if (isValid1(board, row, col, num)) {
                board[row][col] = num;
                if (solve3(board, emptyCells, index + 1)) {
                    return true;
                }
                board[row][col] = '.';
            }
        }
        return false;
    }

    private static int countPossibleValues(char[][] board, int row, int col) {
        int count = 0;
        for (char num = '1'; num <= '9'; num++) {
            if (isValid1(board, row, col, num)) {
                count++;
            }
        }
        return count;
    }

    private static class Cell {
        int row;
        int col;

        public Cell(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    // 4. Backtracking with Bitwise Operations for Constraint Checking
    //    - Uses bitwise operations to represent and check constraints efficiently.
    //    - Numbers 1-9 are represented by bits 1-9 in an integer.
    //    - Very fast constraint checking.
    public static boolean solveSudoku4(char[][] board) {
        int[] rows = new int[9];
        int[] cols = new int[9];
        int[] boxes = new int[9];

        // Precompute used numbers using bitwise operations
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    int mask = 1 << (num - 1);
                    rows[i] |= mask;
                    cols[j] |= mask;
                    boxes[i / 3 * 3 + j / 3] |= mask;
                }
            }
        }
        return solve4(board, 0, 0, rows, cols, boxes);
    }

    private static boolean solve4(char[][] board, int row, int col, int[] rows, int[] cols, int[] boxes) {
        if (row == 9) {
            return true;
        }
        if (col == 9) {
            return solve4(board, row + 1, 0, rows, cols, boxes);
        }
        if (board[row][col] != '.') {
            return solve4(board, row, col + 1, rows, cols, boxes);
        }

        for (char numChar = '1'; numChar <= '9'; numChar++) {
            int num = numChar - '0';
            int mask = 1 << (num - 1);
            if ((rows[row] & mask) == 0 && (cols[col] & mask) == 0 && (boxes[row / 3 * 3 + col / 3] & mask) == 0) {
                board[row][col] = numChar;
                rows[row] |= mask;
                cols[col] |= mask;
                boxes[row / 3 * 3 + col / 3] |= mask;

                if (solve4(board, row, col + 1, rows, cols, boxes)) {
                    return true;
                }

                board[row][col] = '.';
                rows[row] &= ~mask;
                cols[col] &= ~mask;
                boxes[row / 3 * 3 + col / 3] &= ~mask;
            }
        }
        return false;
    }

    // 5.  Iterative Backtracking with Stack
    //    - Uses a stack to keep track of empty cells and their tried numbers
    //    - Avoids recursion, which can be beneficial in environments with limited stack space
    public static boolean solveSudoku5(char[][] board) {
        Stack<CellNum> stack = new Stack<>();
        List<Cell> emptyCells = new ArrayList<>();

        // Find all empty cells
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    emptyCells.add(new Cell(i, j));
                }
            }
        }

        int cellIndex = 0;
        while (cellIndex < emptyCells.size()) {
            Cell cell = emptyCells.get(cellIndex);
            int row = cell.row;
            int col = cell.col;
            boolean found = false;

            // Try numbers starting from the last tried number (if any)
            int startNum = 1;
            if (!stack.isEmpty() && stack.peek().cell.row == row && stack.peek().cell.col == col) {
                startNum = stack.peek().num + 1;
                stack.pop(); // Remove the previous attempt
            }

            for (int num = startNum; num <= 9; num++) {
                char numChar = (char) (num + '0');
                if (isValid1(board, row, col, numChar)) {
                    board[row][col] = numChar;
                    stack.push(new CellNum(cell, num)); // Push the current attempt
                    found = true;
                    break;
                }
            }

            if (found) {
                cellIndex++; // Move to the next empty cell
            } else {
                board[row][col] = '.'; // Clear the cell
                if (cellIndex > 0) {
                    cellIndex--; // Backtrack to the previous cell
                } else {
                    return false; // No solution found
                }
            }
        }
        return true;
    }

    private static class CellNum {
        Cell cell;
        int num;

        public CellNum(Cell cell, int num) {
            this.cell = cell;
            this.num = num;
        }
    }

    private static class Stack<T> {
        private List<T> list = new ArrayList<>();

        public void push(T item) {
            list.add(item);
        }

        public T pop() {
            if (list.isEmpty()) {
                return null; // Or throw an exception
            }
            return list.remove(list.size() - 1);
        }

        public T peek() {
            if (list.isEmpty()) {
                return null;
            }
            return list.get(list.size() - 1);
        }

        public boolean isEmpty() {
            return list.isEmpty();
        }

        public int size(){
            return list.size();
        }
    }

    public static void main(String[] args) {
        char[][] board = {
                {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
                {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
                {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
                {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
                {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
                {'.', '.', '.', '.', '.', '.', '.', '3', '.'},
                {'.', '.', '.', '4', '.', '.', '.', '.', '2'},
                {'.', '.', '.', '.', '.', '3', '.', '.', '.'},
                {'.', '.', '.', '.', '.', '2', '.', '.', '.'}
        };

        System.out.println("Original Sudoku Board:");
        printBoard(board);

        char[][] board1 = deepCopyBoard(board);
        long startTime1 = System.nanoTime();
        boolean solved1 = solveSudoku1(board1);
        long endTime1 = System.nanoTime();
        double duration1 = (endTime1 - startTime1) / 1e6; // in milliseconds

        char[][] board2 = deepCopyBoard(board);
        long startTime2 = System.nanoTime();
        boolean solved2 = solveSudoku2(board2);
        long endTime2 = System.nanoTime();
        double duration2 = (endTime2 - startTime2) / 1e6;

        char[][] board3 = deepCopyBoard(board);
        long startTime3 = System.nanoTime();
        boolean solved3 = solveSudoku3(board3);
        long endTime3 = System.nanoTime();
        double duration3 = (endTime3 - startTime3) / 1e6;

        char[][] board4 = deepCopyBoard(board);
        long startTime4 = System.nanoTime();
        boolean solved4 = solveSudoku4(board4);
        long endTime4 = System.nanoTime();
        double duration4 = (endTime4 - startTime4) / 1e6;

        char[][] board5 = deepCopyBoard(board);
        long startTime5 = System.nanoTime();
        boolean solved5 = solveSudoku5(board5);
        long endTime5 = System.nanoTime();
        double duration5 = (endTime5 - startTime5) / 1e6;


        if (solved1) {
            System.out.println("\nSolution using Approach 1 (Basic Backtracking):");
            printBoard(board1);
            System.out.println("Time taken: " + duration1 + " ms");
        } else {
            System.out.println("\nNo solution found using Approach 1.");
        }

        if (solved2) {
            System.out.println("\nSolution using Approach 2 (Precomputed Constraints):");
            printBoard(board2);
            System.out.println("Time taken: " + duration2 + " ms");
        } else {
            System.out.println("\nNo solution found using Approach 2.");
        }

        if (solved3) {
            System.out.println("\nSolution using Approach 3 (MRV Heuristic):");
            printBoard(board3);
            System.out.println("Time taken: " + duration3 + " ms");
        } else {
            System.out.println("\nNo solution found using Approach 3.");
        }

        if (solved4) {
            System.out.println("\nSolution using Approach 4 (Bitwise Operations):");
            printBoard(board4);
            System.out.println("Time taken: " + duration4 + " ms");
        } else {
            System.out.println("\nNo solution found using Approach 4.");
        }

        if (solved5) {
            System.out.println("\nSolution using Approach 5 (Iterative Stack):");
            printBoard(board5);
            System.out.println("Time taken: " + duration5 + " ms");
        } else {
            System.out.println("\nNo solution found using Approach 5.");
        }
    }

    // Helper method to print the Sudoku board
    private static void printBoard(char[][] board) {
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                System.out.println("---------");
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {
                    System.out.print("|");
                }
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    // Helper method to create a deep copy of the Sudoku board
    private static char[][] deepCopyBoard(char[][] board) {
        char[][] newBoard = new char[9][9];
        for (int i = 0; i < 9; i++) {
            System.arraycopy(board[i], 0, newBoard[i], 0, 9);
        }
        return newBoard;
    }
}


import java.util.ArrayList;
import java.util.List;

public class SudokuSolver {

    /**
     * Main method to test the Sudoku solvers.
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        int[][] board = {
                {5, 3, 0, 0, 7, 0, 0, 0, 0},
                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                {8, 0, 0, 0, 6, 0, 0, 0, 3},
                {4, 0, 0, 8, 0, 3, 0, 0, 1},
                {7, 0, 0, 0, 2, 0, 0, 0, 6},
                {0, 6, 0, 0, 0, 0, 2, 8, 0},
                {0, 0, 0, 4, 1, 9, 0, 0, 5},
                {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };

        System.out.println("Original Sudoku Board:");
        printBoard(board);

        System.out.println("\nSolving using Approach 1: Basic Backtracking");
        int[][] board1 = copyBoard(board); // Create a copy to avoid modifying the original
        if (solveSudoku1(board1)) {
            System.out.println("Solved Sudoku Board:");
            printBoard(board1);
        } else {
            System.out.println("No solution exists.");
        }

        System.out.println("\nSolving using Approach 2: Backtracking with Helper Functions");
        int[][] board2 = copyBoard(board);
        if (solveSudoku2(board2)) {
            System.out.println("Solved Sudoku Board:");
            printBoard(board2);
        } else {
            System.out.println("No solution exists.");
        }

        System.out.println("\nSolving using Approach 3: Optimized Backtracking");
        int[][] board3 = copyBoard(board);
        if (solveSudoku3(board3)) {
            System.out.println("Solved Sudoku Board:");
            printBoard(board3);
        } else {
            System.out.println("No solution exists.");
        }

        System.out.println("\nSolving using Approach 4: Backtracking with Precomputed Possibilities");
        int[][] board4 = copyBoard(board);
        if (solveSudoku4(board4)) {
            System.out.println("Solved Sudoku Board:");
            printBoard(board4);
        } else {
            System.out.println("No solution exists.");
        }

        System.out.println("\nSolving using Approach 5: Iterative Backtracking with Stack");
        int[][] board5 = copyBoard(board);
        if (solveSudoku5(board5)) {
            System.out.println("Solved Sudoku Board:");
            printBoard(board5);
        } else {
            System.out.println("No solution exists.");
        }
    }

    /**
     * Helper method to print the Sudoku board.
     *
     * @param board the Sudoku board to print
     */
    public static void printBoard(int[][] board) {
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                System.out.println("-----------");
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

    /**
     * Helper method to copy the Sudoku board.  Used to avoid modifying the original board
     * when testing different solving approaches.
     * @param board The sudoku board to copy.
     * @return A new 2D array with the same values as the input board.
     */
    public static int[][] copyBoard(int[][] board) {
        int[][] newBoard = new int[9][9];
        for (int i = 0; i < 9; i++) {
            System.arraycopy(board[i], 0, newBoard[i], 0, 9);
        }
        return newBoard;
    }

    // Approach 1: Basic Backtracking
    // This is the most straightforward backtracking solution.  It iterates through
    // each empty cell and tries every possible number.  If a number is valid, it
    // recursively calls itself to fill the next empty cell.  If no number is valid,
    // it backtracks and tries a different number.
    /**
     * Solves the Sudoku puzzle using basic backtracking.
     *
     * @param board the Sudoku board to solve
     * @return true if the board is solved, false otherwise
     */
    public static boolean solveSudoku1(int[][] board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    for (int number = 1; number <= 9; number++) {
                        if (isValid(board, i, j, number)) {
                            board[i][j] = number;
                            if (solveSudoku1(board)) {
                                return true; // Found a solution
                            } else {
                                board[i][j] = 0; // Backtrack
                            }
                        }
                    }
                    return false; // No valid number found
                }
            }
        }
        return true; // Board is fully filled
    }

    /**
     * Checks if a number can be placed in a cell.
     *
     * @param board  the Sudoku board
     * @param row    the row of the cell
     * @param col    the column of the cell
     * @param number the number to check
     * @return true if the number is valid, false otherwise
     */
    public static boolean isValid(int[][] board, int row, int col, int number) {
        // Check row and column
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == number || board[i][col] == number) {
                return false;
            }
        }
        // Check 3x3 subgrid
        int subgridRowStart = row - row % 3;
        int subgridColStart = col - col % 3;
        for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
            for (int j = subgridColStart; j < subgridColStart + 3; j++) {
                if (board[i][j] == number) {
                    return false;
                }
            }
        }
        return true;
    }

    // Approach 2: Backtracking with Helper Functions
    // This approach is similar to the first one, but it uses helper functions
    // to check the row, column, and subgrid, making the code more organized
    // and readable.  It doesn't improve the performance, but it's good
    // for code clarity.
    /**
     * Solves the Sudoku puzzle using backtracking with helper functions.
     *
     * @param board the Sudoku board to solve
     * @return true if the board is solved, false otherwise
     */
    public static boolean solveSudoku2(int[][] board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    for (int number = 1; number <= 9; number++) {
                        if (isValid2(board, i, j, number)) {
                            board[i][j] = number;
                            if (solveSudoku2(board)) {
                                return true;
                            } else {
                                board[i][j] = 0;
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Checks if a number can be placed in a cell, using helper functions.
     *
     * @param board  the Sudoku board
     * @param row    the row of the cell
     * @param col    the column of the cell
     * @param number the number to check
     * @return true if the number is valid, false otherwise
     */
    public static boolean isValid2(int[][] board, int row, int col, int number) {
        return !isInRow(board, row, number) &&
                !isInCol(board, col, number) &&
                !isInSubgrid(board, row, col, number);
    }

    /**
     * Checks if a number is already in the row.
     *
     * @param board  the Sudoku board
     * @param row    the row to check
     * @param number the number to check
     * @return true if the number is in the row, false otherwise
     */
    public static boolean isInRow(int[][] board, int row, int number) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == number) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks if a number is already in the column.
     *
     * @param board  the Sudoku board
     * @param col    the column to check
     * @param number the number to check
     * @return true if the number is in the column, false otherwise
     */
    public static boolean isInCol(int[][] board, int col, int number) {
        for (int row = 0; row < 9; row++) {
            if (board[row][col] == number) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks if a number is already in the 3x3 subgrid.
     *
     * @param board the Sudoku board
     * @param row   the row of the cell
     * @param col   the column of the cell
     * @param number the number to check
     * @return true if the number is in the subgrid, false otherwise
     */
    public static boolean isInSubgrid(int[][] board, int row, int col, int number) {
        int subgridRowStart = row - row % 3;
        int subgridColStart = col - col % 3;
        for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
            for (int j = subgridColStart; j < subgridColStart + 3; j++) {
                if (board[i][j] == number) {
                    return true;
                }
            }
        }
        return false;
    }

    // Approach 3: Optimized Backtracking
    // This approach optimizes the backtracking by finding the next empty cell
    // that has the fewest possible valid numbers.  This reduces the number of
    // branches the algorithm has to explore, improving performance.
    /**
     * Solves the Sudoku puzzle using optimized backtracking.
     *
     * @param board the Sudoku board to solve
     * @return true if the board is solved, false otherwise
     */
    public static boolean solveSudoku3(int[][] board) {
        int[] emptyCell = findNextEmptyCell(board);
        if (emptyCell == null) {
            return true; // Board is solved
        }
        int row = emptyCell[0];
        int col = emptyCell[1];

        for (int number = 1; number <= 9; number++) {
            if (isValid(board, row, col, number)) {
                board[row][col] = number;
                if (solveSudoku3(board)) {
                    return true;
                } else {
                    board[row][col] = 0;
                }
            }
        }
        return false;
    }

    /**
     * Finds the next empty cell with the fewest possible valid numbers.
     *
     * @param board the Sudoku board
     * @return an array containing the row and column of the empty cell, or null if no empty cell is found
     */
    public static int[] findNextEmptyCell(int[][] board) {
        int minPossibleNumbers = 10; // Initialize with a value greater than 9
        int[] nextEmptyCell = null;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    int possibleNumbers = countPossibleNumbers(board, i, j);
                    if (possibleNumbers < minPossibleNumbers) {
                        minPossibleNumbers = possibleNumbers;
                        nextEmptyCell = new int[]{i, j};
                        if (possibleNumbers == 1) {
                            return nextEmptyCell; // Optimization: If only 1 possibility, return immediately
                        }
                    }
                }
            }
        }
        return nextEmptyCell;
    }

    /**
     * Counts the number of possible valid numbers for a cell.
     *
     * @param board the Sudoku board
     * @param row   the row of the cell
     * @param col   the column of the cell
     * @return the number of possible valid numbers
     */
    public static int countPossibleNumbers(int[][] board, int row, int col) {
        int count = 0;
        for (int number = 1; number <= 9; number++) {
            if (isValid(board, row, col, number)) {
                count++;
            }
        }
        return count;
    }

    // Approach 4: Backtracking with Precomputed Possibilities
    // This approach precomputes the possible numbers for each empty cell
    // before starting the backtracking.  This can speed up the process
    // because the isValid function doesn't need to be called repeatedly.
    /**
     * Solves the Sudoku puzzle using backtracking with precomputed possibilities.
     *
     * @param board the Sudoku board to solve
     * @return true if the board is solved, false otherwise
     */
    public static boolean solveSudoku4(int[][] board) {
        List<Cell> emptyCells = new ArrayList<>();
        List<List<Integer>> possibleNumbers = new ArrayList<>();

        // Precompute empty cells and their possible numbers
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    emptyCells.add(new Cell(i, j));
                    List<Integer> numbers = new ArrayList<>();
                    for (int number = 1; number <= 9; number++) {
                        if (isValid(board, i, j, number)) {
                            numbers.add(number);
                        }
                    }
                    possibleNumbers.add(numbers);
                }
            }
        }

        return solveSudoku4Helper(board, emptyCells, possibleNumbers, 0);
    }

    /**
     * Recursive helper function for solveSudoku4.
     */
    private static boolean solveSudoku4Helper(int[][] board, List<Cell> emptyCells, List<List<Integer>> possibleNumbers, int index) {
        if (index == emptyCells.size()) {
            return true; // All cells filled
        }

        Cell cell = emptyCells.get(index);
        int row = cell.row;
        int col = cell.col;
        List<Integer> numbers = possibleNumbers.get(index);

        for (int number : numbers) {
            board[row][col] = number;
            if (solveSudoku4Helper(board, emptyCells, possibleNumbers, index + 1)) {
                return true;
            } else {
                board[row][col] = 0; // Backtrack
            }
        }
        return false;
    }

    /**
     * Inner class to represent a cell in the Sudoku board.
     */
    private static class Cell {
        int row;
        int col;

        public Cell(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    // Approach 5: Iterative Backtracking with Stack
    // This approach uses a stack to keep track of the empty cells and the
    // numbers that have been tried.  This avoids recursion, which can be
    // more efficient in some cases.
    /**
     * Solves the Sudoku puzzle using iterative backtracking with a stack.
     *
     * @param board the Sudoku board to solve
     * @return true if the board is solved, false otherwise
     */
    public static boolean solveSudoku5(int[][] board) {
        Stack<CellNumber> stack = new Stack<>();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    stack.push(new CellNumber(i, j, 1)); // Start with 1
                }
            }
        }

        while (!stack.isEmpty()) {
            CellNumber current = stack.peek();
            int row = current.row;
            int col = current.col;
            int number = current.number;

            if (number > 9) {
                board[row][col] = 0; // Reset and backtrack
                stack.pop();
                if (!stack.isEmpty()) {
                    stack.peek().number++; // Increment number for the previous cell
                }
                continue;
            }

            if (isValid(board, row, col, number)) {
                board[row][col] = number;
                current.number = number + 1; // Increment for the next iteration
                // Find next empty cell
                boolean foundNext = false;
                for (int i = row; i < 9; i++) {
                    for (int j = (i == row) ? col + 1 : 0; j < 9; j++) { // start from col+1 if same row
                        if (board[i][j] == 0) {
                            stack.push(new CellNumber(i, j, 1));
                            foundNext = true;
                            break;
                        }
                    }
                    if (foundNext) break;
                }
                if (!foundNext && isBoardFull(board)) return true;

            } else {
                current.number++; // Try next number
            }
        }
        return false;
    }

    private static boolean isBoardFull(int[][] board){
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j] == 0) return false;
            }
        }
        return true;
    }
    /**
     * Inner class to represent a cell and the number being tried.
     */
    private static class CellNumber {
        int row;
        int col;
        int number;

        public CellNumber(int row, int col, int number) {
            this.row = row;
            this.col = col;
            this.number = number;
        }
    }

    //Custom Stack Implementation
    private static class Stack<T> {
        private List<T> stack;

        public Stack() {
            this.stack = new ArrayList<>();
        }

        public void push(T element) {
            stack.add(element);
        }

        public T pop() {
            if (isEmpty()) {
                return null; // Or throw an exception
            }
            return stack.remove(stack.size() - 1);
        }

        public T peek() {
            if (isEmpty()) {
                return null; // Or throw an exception
            }
            return stack.get(stack.size() - 1);
        }

        public boolean isEmpty() {
            return stack.isEmpty();
        }

        public int size(){
            return stack.size();
        }
    }
}


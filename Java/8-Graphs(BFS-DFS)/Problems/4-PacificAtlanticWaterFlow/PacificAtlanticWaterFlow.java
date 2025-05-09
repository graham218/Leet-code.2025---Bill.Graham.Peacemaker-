import java.util.*;

public class PacificAtlanticWaterFlow {

    /**
     * Problem:
     *
     * Given an m x n rectangular island where the value of each cell represents
     * the height of the terrain, water can flow to neighboring cells with heights
     * less than or equal to its own. The island is surrounded by the Pacific Ocean
     * to the north and west, and the Atlantic Ocean to the south and east.
     *
     * Find the cells from which water can flow to both the Pacific and Atlantic
     * oceans.
     *
     * Example:
     *
     * Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
     * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
     *
     * Explanation:
     *
     * The following cells have a path to both the Pacific and Atlantic oceans:
     * - (0, 4): Water can flow to the Pacific via (0, 3), (0, 2), (0, 1), and (0, 0).
     * Water can flow to the Atlantic via (1, 4), (2, 4), (3, 4), and (4, 4).
     * - (1, 3): Water can flow to the Pacific via (0, 3), (0, 2), (0, 1), and (0, 0).
     * Water can flow to the Atlantic via (1, 4), (2, 4), (3, 4), and (4, 4).
     * - (1, 4): Water can flow to the Pacific via (0, 4), (0, 3), (0, 2), (0,1), and (0, 0).
     * Water can flow to the Atlantic via (2, 4), (3, 4), and (4, 4).
     * - (2, 2): Water can flow to the Pacific via (1, 2), (0, 2), (0, 1), and (0, 0).
     * Water can flow to the Atlantic via (2, 3), (2, 4), (3, 4), and (4, 4).
     * - (3, 0): Water can flow to the Pacific via (2, 0), (1, 0), and (0, 0).
     * Water can flow to the Atlantic via (3, 1), (3, 2), (3, 3), and (3, 4).
     * - (3, 1): Water can flow to the Pacific via (2, 1), (1, 1), and (0, 1).
     * Water can flow to the Atlantic via (3, 2), (3, 3), (3, 4), and (4, 4).
     * - (4, 0): Water can flow to the Pacific via (3,0), (2,0), (1,0), and (0,0).
     * Water can flow to the Atlantic via (4,1), (4,2), (4,3), and (4,4).
     *
     */

    // Helper method to check if the row and col are within bounds
    private boolean isValid(int row, int col, int[][] matrix) {
        return row >= 0 && row < matrix.length && col >= 0 && col < matrix[0].length;
    }

    // Helper method to perform DFS
    private void dfs(int row, int col, int[][] matrix, boolean[][] visited, int prevHeight) {
        // If the cell is out of bounds or already visited, or the current height
        // is less than the previous height, return.
        if (!isValid(row, col, matrix) || visited[row][col] || matrix[row][col] < prevHeight) {
            return;
        }

        // Mark the cell as visited.
        visited[row][col] = true;

        // Define the directions for the four neighbors (up, down, left, right).
        int[] dx = {0, 0, 1, -1};
        int[] dy = {1, -1, 0, 0};

        // Recursively call DFS for the four neighbors.
        for (int i = 0; i < 4; i++) {
            dfs(row + dx[i], col + dy[i], matrix, visited, matrix[row][col]);
        }
    }

    // Helper method to perform BFS
    private void bfs(Queue<int[]> queue, int[][] matrix, boolean[][] visited) {
        // Perform BFS until the queue is empty.
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int row = cell[0];
            int col = cell[1];

            // Mark the cell as visited.
            visited[row][col] = true;

            // Define the directions for the four neighbors (up, down, left, right).
            int[] dx = {0, 0, 1, -1};
            int[] dy = {1, -1, 0, 0};

            // Iterate over the four neighbors.
            for (int i = 0; i < 4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];

                // If the neighbor is within bounds, not visited, and has a height
                // greater than or equal to the current cell, add it to the queue.
                if (isValid(newRow, newCol, matrix) && !visited[newRow][newCol]
                        && matrix[newRow][newCol] >= matrix[row][col]) {
                    queue.offer(new int[]{newRow, newCol});
                }
            }
        }
    }

    /**
     * Approach 1: DFS from both oceans
     *
     * Time Complexity: O(m * n), where m is the number of rows and n is the
     * number of columns. We visit each cell at most twice, once from the Pacific
     * and once from the Atlantic.
     *
     * Space Complexity: O(m * n) in the worst case, due to the recursion stack
     * and the visited arrays.
     */
    public List<List<Integer>> pacificAtlanticDFS(int[][] heights) {
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = heights.length;
        int cols = heights[0].length;

        // Create two boolean arrays to track the cells reachable from the
        // Pacific and Atlantic oceans.
        boolean[][] pacificReachable = new boolean[rows][cols];
        boolean[][] atlanticReachable = new boolean[rows][cols];

        // Perform DFS from the Pacific ocean (top and left edges).
        for (int i = 0; i < rows; i++) {
            dfs(i, 0, heights, pacificReachable, heights[i][0]);
        }
        for (int j = 0; j < cols; j++) {
            dfs(0, j, heights, pacificReachable, heights[0][j]);
        }

        // Perform DFS from the Atlantic ocean (bottom and right edges).
        for (int i = 0; i < rows; i++) {
            dfs(i, cols - 1, heights, atlanticReachable, heights[i][cols - 1]);
        }
        for (int j = 0; j < cols; j++) {
            dfs(rows - 1, j, heights, atlanticReachable, heights[rows - 1][j]);
        }

        // Collect the cells that are reachable from both oceans.
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (pacificReachable[i][j] && atlanticReachable[i][j]) {
                    List<Integer> cell = new ArrayList<>();
                    cell.add(i);
                    cell.add(j);
                    result.add(cell);
                }
            }
        }

        return result;
    }

    /**
     * Approach 2: BFS from both oceans
     *
     * Time Complexity: O(m * n), where m is the number of rows and n is the
     * number of columns. We visit each cell at most twice, once from the Pacific
     * and once from the Atlantic.
     *
     * Space Complexity: O(m * n) in the worst case, due to the queues and the
     * visited arrays.
     */
    public List<List<Integer>> pacificAtlanticBFS(int[][] heights) {
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = heights.length;
        int cols = heights[0].length;

        // Create two boolean arrays to track the cells reachable from the
        // Pacific and Atlantic oceans.
        boolean[][] pacificReachable = new boolean[rows][cols];
        boolean[][] atlanticReachable = new boolean[rows][cols];

        // Create queues for BFS.
        Queue<int[]> pacificQueue = new LinkedList<>();
        Queue<int[]> atlanticQueue = new LinkedList<>();

        // Initialize the queues with the cells on the edges.
        for (int i = 0; i < rows; i++) {
            pacificQueue.offer(new int[]{i, 0});
            atlanticQueue.offer(new int[]{i, cols - 1});
        }
        for (int j = 0; j < cols; j++) {
            pacificQueue.offer(new int[]{0, j});
            atlanticQueue.offer(new int[]{rows - 1, j});
        }

        // Perform BFS from the Pacific ocean.
        bfs(pacificQueue, heights, pacificReachable);

        // Perform BFS from the Atlantic ocean.
        bfs(atlanticQueue, heights, atlanticReachable);

        // Collect the cells that are reachable from both oceans.
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (pacificReachable[i][j] && atlanticReachable[i][j]) {
                    List<Integer> cell = new ArrayList<>();
                    cell.add(i);
                    cell.add(j);
                    result.add(cell);
                }
            }
        }

        return result;
    }

    /**
     * Approach 3: Optimized DFS (Single DFS)
     *
     * Time Complexity: O(m * n), where m is the number of rows and n is the
     * number of columns.  Although it looks like we do one DFS, in the worst case,
     * we still visit each node twice (once from pacific and once from atlantic).
     *
     * Space Complexity: O(m * n) in the worst case, due to the recursion stack
     * and the visited arrays.
     *
     * Ref: https://www.youtube.com/watch?v=5j4M9G93e7E
     */
    public List<List<Integer>> pacificAtlanticOptimizedDFS(int[][] heights) {
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = heights.length;
        int cols = heights[0].length;

        boolean[][] pacificReachable = new boolean[rows][cols];
        boolean[][] atlanticReachable = new boolean[rows][cols];
        List<List<Integer>> result = new ArrayList<>();

        // DFS from Pacific and Atlantic edges
        for (int r = 0; r < rows; r++) {
            dfs(r, 0, heights, pacificReachable, heights[r][0]);       // Pacific (left edge)
            dfs(r, cols - 1, heights, atlanticReachable, heights[r][cols - 1]); // Atlantic (right edge)
        }
        for (int c = 0; c < cols; c++) {
            dfs(0, c, heights, pacificReachable, heights[0][c]);       // Pacific (top edge)
            dfs(rows - 1, c, heights, atlanticReachable, heights[rows - 1][c]); // Atlantic (bottom edge)
        }

        // Collect common reachable cells
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    /**
     * Approach 4: Optimized BFS (Single BFS) - Not truly single BFS, but combines the logic
     * This approach improves upon the BFS approach by combining the BFS traversals for
     * both oceans into a single method, reducing code duplication.  It's not a *single* BFS,
     * but it's more optimized than doing two separate BFS traversals.
     *
     * Time Complexity: O(m * n), where m is the number of rows and n is the number of columns.
     * Each cell is visited at most twice.
     *
     * Space Complexity: O(m * n) in the worst case, due to the queues and visited arrays.
     */
    public List<List<Integer>> pacificAtlanticOptimizedBFS2(int[][] heights) {
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = heights.length;
        int cols = heights[0].length;
        boolean[][] pacificReachable = new boolean[rows][cols];
        boolean[][] atlanticReachable = new boolean[rows][cols];
        Queue<int[]> pacificQueue = new LinkedList<>();
        Queue<int[]> atlanticQueue = new LinkedList<>();
        List<List<Integer>> result = new ArrayList<>();

        // Initialize queues for Pacific and Atlantic boundaries
        for (int r = 0; r < rows; r++) {
            pacificQueue.offer(new int[]{r, 0});
            atlanticQueue.offer(new int[]{r, cols - 1});
        }
        for (int c = 0; c < cols; c++) {
            pacificQueue.offer(new int[]{0, c});
            atlanticQueue.offer(new int[]{rows - 1, c});
        }

        // Perform BFS for both oceans
        bfs(pacificQueue, heights, pacificReachable);
        bfs(atlanticQueue, heights, atlanticReachable);

        // Collect cells reachable from both oceans
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    /**
     * Approach 5: Iterative DFS with Stack (Non-Recursive DFS)
     *
     * This approach implements DFS iteratively using a stack instead of recursion.  This can
     * sometimes be more efficient in Java by avoiding the overhead of recursive function calls,
     * and it also avoids the risk of stack overflow for very large input grids.
     *
     * Time Complexity: O(m * n), where m is the number of rows and n is the number of columns.  Each cell
     * is visited at most twice (once from Pacific and once from Atlantic).
     *
     * Space Complexity: O(m * n) in the worst case.  The stack can potentially hold all the cells
     * in the grid.
     */
    public List<List<Integer>> pacificAtlanticIterativeDFS(int[][] heights) {
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = heights.length;
        int cols = heights[0].length;
        boolean[][] pacificReachable = new boolean[rows][cols];
        boolean[][] atlanticReachable = new boolean[rows][cols];
        List<List<Integer>> result = new ArrayList<>();

        // Perform iterative DFS from the Pacific ocean (top and left edges).
        for (int i = 0; i < rows; i++) {
            iterativeDfs(heights, pacificReachable, i, 0);
        }
        for (int j = 0; j < cols; j++) {
            iterativeDfs(heights, pacificReachable, 0, j);
        }

        // Perform iterative DFS from the Atlantic ocean (bottom and right edges).
        for (int i = 0; i < rows; i++) {
            iterativeDfs(heights, atlanticReachable, i, cols - 1);
        }
        for (int j = 0; j < cols; j++) {
            iterativeDfs(heights, atlanticReachable, rows - 1, j);
        }

        // Collect the cells that are reachable from both oceans.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (pacificReachable[i][j] && atlanticReachable[i][j]) {
                    result.add(Arrays.asList(i, j));
                }
            }
        }
        return result;
    }

    private void iterativeDfs(int[][] heights, boolean[][] visited, int startRow, int startCol) {
        Stack<int[]> stack = new Stack<>();
        stack.push(new int[]{startRow, startCol});
        visited[startRow][startCol] = true;

        int[] dx = {0, 0, 1, -1};
        int[] dy = {1, -1, 0, 0};

        while (!stack.isEmpty()) {
            int[] cell = stack.pop();
            int row = cell[0];
            int col = cell[1];

            for (int i = 0; i < 4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];

                if (isValid(newRow, newCol, heights) && !visited[newRow][newCol] && heights[newRow][newCol] >= heights[row][col]) {
                    visited[newRow][newCol] = true;
                    stack.push(new int[]{newRow, newCol});
                }
            }
        }
    }

    public static void main(String[] args) {
        PacificAtlanticWaterFlow solution = new PacificAtlanticWaterFlow();

        int[][] heights = {
                {1, 2, 2, 3, 5},
                {3, 2, 3, 4, 4},
                {2, 4, 5, 3, 1},
                {6, 7, 1, 4, 5},
                {5, 1, 1, 2, 4}
        };

        System.out.println("Input:");
        for (int[] row : heights) {
            System.out.println(Arrays.toString(row));
        }
        System.out.println();

        // Test Approach 1: DFS from both oceans
        List<List<Integer>> result1 = solution.pacificAtlanticDFS(heights);
        System.out.println("DFS from both oceans: " + result1);

        // Test Approach 2: BFS from both oceans
        List<List<Integer>> result2 = solution.pacificAtlanticBFS(heights);
        System.out.println("BFS from both oceans: " + result2);

        // Test Approach 3: Optimized DFS
        List<List<Integer>> result3 = solution.pacificAtlanticOptimizedDFS(heights);
        System.out.println("Optimized DFS: " + result3);

        // Test Approach 4: Optimized BFS
        List<List<Integer>> result4 = solution.pacificAtlanticOptimizedBFS2(heights);
        System.out.println("Optimized BFS: " + result4);

        // Test Approach 5: Iterative DFS
        List<List<Integer>> result5 = solution.pacificAtlanticIterativeDFS(heights);
        System.out.println("Iterative DFS: " + result5);
    }
}


import java.util.*;

public class PacificAtlanticWaterFlow {

    // Main method to test the different approaches
    public static void main(String[] args) {
        int[][] matrix = {
                {1, 2, 2, 3, 5},
                {3, 2, 3, 4, 4},
                {2, 4, 5, 3, 1},
                {6, 7, 1, 4, 5},
                {5, 1, 1, 2, 4}
        };

        System.out.println("Input Matrix:");
        printMatrix(matrix);

        PacificAtlanticWaterFlow solution = new PacificAtlanticWaterFlow();

        System.out.println("\nApproach 1: Basic DFS");
        List<List<Integer>> result1 = solution.pacificAtlanticDFS(matrix);
        printResult(result1);

        System.out.println("\nApproach 2: Optimized DFS with Visited Array");
        List<List<Integer>> result2 = solution.pacificAtlanticDFSOptimized(matrix);
        printResult(result2);

        System.out.println("\nApproach 3: BFS");
        List<List<Integer>> result3 = solution.pacificAtlanticBFS(matrix);
        printResult(result3);

        System.out.println("\nApproach 4:  Divide and Conquer DFS");
        List<List<Integer>> result4 = solution.pacificAtlanticDivideAndConquer(matrix);
        printResult(result4);

        System.out.println("\nApproach 5: Iterative DFS with Stack");
        List<List<Integer>> result5 = solution.pacificAtlanticDFSIterative(matrix);
        printResult(result5);
    }

    // Helper method to print the matrix
    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }

    // Helper method to print the result list
    private static void printResult(List<List<Integer>> result) {
        for (List<Integer> pair : result) {
            System.out.println(pair);
        }
    }

    // Approach 1: Basic DFS
    // Time Complexity: O(m^2 * n^2) -  For each cell, we might explore all other cells in the worst case.
    // Space Complexity: O(m * n) -  The depth of the recursion can go up to the size of the matrix.
    // This is the most basic approach.  It directly applies DFS from each cell
    // to check reachability.  Performance is not optimal.
    public List<List<Integer>> pacificAtlanticDFS(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        List<List<Integer>> result = new ArrayList<>();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                // Check if water can flow to both Pacific and Atlantic from this cell
                boolean canReachPacific = canReachOceanDFS(matrix, r, c, -1, new HashSet<>());
                boolean canReachAtlantic = canReachOceanDFS(matrix, r, c, -1, new HashSet<>());
                if (canReachPacific && canReachAtlantic) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    // Helper function for basic DFS
    private boolean canReachOceanDFS(int[][] matrix, int r, int c, int prevHeight, HashSet<String> visited) {
        if (r < 0 || r >= matrix.length || c < 0 || c >= matrix[0].length || matrix[r][c] < prevHeight) {
            return false;
        }

        String cell = r + "," + c;
        if(visited.contains(cell)) return false;
        visited.add(cell);

        // Check if it can reach to the border
        if (r == 0 || c == 0) return true; // Reach Pacific
        if (r == matrix.length - 1 || c == matrix[0].length - 1) return true; // Reach Atlantic

        int currentHeight = matrix[r][c];
        // Explore adjacent cells
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : directions) {
            int newR = r + dir[0];
            int newC = c + dir[1];
            if (canReachOceanDFS(matrix, newR, newC, currentHeight, visited)) {
                return true;
            }
        }
        return false;
    }

    // Approach 2: Optimized DFS with Visited Array
    // Time Complexity: O(m * n) - Each cell is visited at most twice (once from Pacific, once from Atlantic).
    // Space Complexity: O(m * n) - For the visited arrays and the recursion stack.
    // This approach optimizes the basic DFS by using visited arrays.  It avoids
    // redundant calculations by remembering which cells can reach which ocean.
    public List<List<Integer>> pacificAtlanticDFSOptimized(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        List<List<Integer>> result = new ArrayList<>();
        boolean[][] canReachPacific = new boolean[rows][cols];
        boolean[][] canReachAtlantic = new boolean[rows][cols];

        // Perform DFS from the borders of each ocean
        for (int c = 0; c < cols; c++) {
            dfsOptimized(matrix, 0, c, canReachPacific, -1); // Top row (Pacific)
            dfsOptimized(matrix, rows - 1, c, canReachAtlantic, -1); // Bottom row (Atlantic)
        }
        for (int r = 0; r < rows; r++) {
            dfsOptimized(matrix, r, 0, canReachPacific, -1); // Left column (Pacific)
            dfsOptimized(matrix, r, cols - 1, canReachAtlantic, -1); // Right column (Atlantic)
        }

        // Collect the cells that can reach both oceans
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (canReachPacific[r][c] && canReachAtlantic[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    // Helper function for optimized DFS
    private void dfsOptimized(int[][] matrix, int r, int c, boolean[][] canReach, int prevHeight) {
        if (r < 0 || r >= matrix.length || c < 0 || c >= matrix[0].length || canReach[r][c] || matrix[r][c] < prevHeight) {
            return;
        }

        canReach[r][c] = true;
        int currentHeight = matrix[r][c];
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : directions) {
            int newR = r + dir[0];
            int newC = c + dir[1];
            dfsOptimized(matrix, newR, newC, canReach, currentHeight);
        }
    }

    // Approach 3: BFS
    // Time Complexity: O(m * n) - Each cell is visited at most twice.
    // Space Complexity: O(m * n) - For the queues and visited arrays.
    // This approach uses Breadth-First Search (BFS) instead of DFS.  BFS can
    // sometimes be more efficient in finding the shortest path (though not
    // relevant in this problem, it's a different exploration strategy).
    public List<List<Integer>> pacificAtlanticBFS(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        List<List<Integer>> result = new ArrayList<>();
        boolean[][] canReachPacific = new boolean[rows][cols];
        boolean[][] canReachAtlantic = new boolean[rows][cols];

        // BFS from Pacific border
        Queue<int[]> pacificQueue = new LinkedList<>();
        for (int r = 0; r < rows; r++) {
            pacificQueue.offer(new int[]{r, 0}); // Left column
        }
        for (int c = 0; c < cols; c++) {
            pacificQueue.offer(new int[]{0, c}); // Top row
        }
        bfs(matrix, pacificQueue, canReachPacific);

        // BFS from Atlantic border
        Queue<int[]> atlanticQueue = new LinkedList<>();
        for (int r = 0; r < rows; r++) {
            atlanticQueue.offer(new int[]{r, cols - 1}); // Right column
        }
        for (int c = 0; c < cols; c++) {
            atlanticQueue.offer(new int[]{rows - 1, c}); // Bottom row
        }
        bfs(matrix, atlanticQueue, canReachAtlantic);

        // Collect the cells that can reach both oceans
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (canReachPacific[r][c] && canReachAtlantic[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    // Helper function for BFS
    private void bfs(int[][] matrix, Queue<int[]> queue, boolean[][] canReach) {
        int rows = matrix.length;
        int cols = matrix[0].length;

        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int r = cell[0];
            int c = cell[1];

            if (r < 0 || r >= rows || c < 0 || c >= cols || canReach[r][c]) {
                continue;
            }
            canReach[r][c] = true;

            int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (int[] dir : directions) {
                int newR = r + dir[0];
                int newC = c + dir[1];
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && matrix[newR][newC] >= matrix[r][c]) {
                    queue.offer(new int[]{newR, newC});
                }
            }
        }
    }

    // Approach 4: Divide and Conquer DFS
    // Time Complexity: O(m * n) -  Similar to optimized DFS, each cell is visited a constant number of times.
    // Space Complexity: O(m * n) -  Due to the recursion stack, although the depth is reduced compared to basic DFS.
    // This approach divides the matrix into subproblems.  It's a more advanced
    // technique that can be useful for very large matrices, as it can be
    // parallelized.  In this specific problem, the benefit might be marginal,
    // but the technique is important.
    public List<List<Integer>> pacificAtlanticDivideAndConquer(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        List<List<Integer>> result = new ArrayList<>();
        boolean[][] canReachPacific = new boolean[rows][cols];
        boolean[][] canReachAtlantic = new boolean[rows][cols];

        // Divide the matrix and conquer
        divideAndConquer(matrix, 0, 0, rows - 1, cols - 1, canReachPacific, canReachAtlantic);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (canReachPacific[r][c] && canReachAtlantic[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    private void divideAndConquer(int[][] matrix, int rowStart, int colStart, int rowEnd, int colEnd, boolean[][] canReachPacific, boolean[][] canReachAtlantic) {
        if (rowStart > rowEnd || colStart > colEnd) {
            return;
        }

        // Base case: when the submatrix is small enough, solve it directly using DFS
        if ((rowEnd - rowStart + 1) <= 10 && (colEnd - colStart + 1) <= 10) { //tune this threshold
            for (int r = rowStart; r <= rowEnd; r++) {
                for (int c = colStart; c <= colEnd; c++) {
                    if ((r == 0 || c == 0)) {
                        dfsDivideAndConquer(matrix, r, c, canReachPacific, -1);
                    }
                    if ((r == matrix.length -1 || c == matrix[0].length-1)){
                        dfsDivideAndConquer(matrix, r, c, canReachAtlantic, -1);
                    }
                }
            }
            return;
        }

        // Divide the submatrix into four quadrants
        int midRow = (rowStart + rowEnd) / 2;
        int midCol = (colStart + colEnd) / 2;

        // Recursively process each quadrant
        divideAndConquer(matrix, rowStart, colStart, midRow, midCol, canReachPacific, canReachAtlantic);
        divideAndConquer(matrix, rowStart, midCol + 1, midRow, colEnd, canReachPacific, canReachAtlantic);
        divideAndConquer(matrix, midRow + 1, colStart, rowEnd, midCol, canReachPacific, canReachAtlantic);
        divideAndConquer(matrix, midRow + 1, midCol + 1, rowEnd, colEnd, canReachPacific, canReachAtlantic);
    }

    private void dfsDivideAndConquer(int[][] matrix, int r, int c, boolean[][] canReach, int prevHeight) {
        if (r < 0 || r >= matrix.length || c < 0 || c >= matrix[0].length || canReach[r][c] || matrix[r][c] < prevHeight) {
            return;
        }

        canReach[r][c] = true;
        int currentHeight = matrix[r][c];
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : directions) {
            int newR = r + dir[0];
            int newC = c + dir[1];
            dfsDivideAndConquer(matrix, newR, newC, canReach, currentHeight);
        }
    }

    // Approach 5: Iterative DFS with Stack
    // Time Complexity: O(m * n) - Each cell is visited at most twice.
    // Space Complexity: O(m * n) - For the stack and visited arrays.
    //  This approach implements DFS iteratively using a stack.  Iterative DFS
    //  can be useful in environments with limited stack space, as it avoids
    //  deep recursion.
    public List<List<Integer>> pacificAtlanticDFSIterative(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new ArrayList<>();
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        List<List<Integer>> result = new ArrayList<>();
        boolean[][] canReachPacific = new boolean[rows][cols];
        boolean[][] canReachAtlantic = new boolean[rows][cols];

        // Iterative DFS for Pacific
        for (int c = 0; c < cols; c++) {
            dfsIterative(matrix, 0, c, canReachPacific); // Top row
        }
        for (int r = 0; r < rows; r++) {
            dfsIterative(matrix, r, 0, canReachPacific); // Left column
        }

        // Iterative DFS for Atlantic
        for (int c = 0; c < cols; c++) {
            dfsIterative(matrix, rows - 1, c, canReachAtlantic); // Bottom row
        }
        for (int r = 0; r < rows; r++) {
            dfsIterative(matrix, r, cols - 1, canReachAtlantic); // Right column
        }

        // Collect the cells that can reach both oceans
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (canReachPacific[r][c] && canReachAtlantic[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }
        return result;
    }

    private void dfsIterative(int[][] matrix, int startR, int startC, boolean[][] canReach) {
        Stack<int[]> stack = new Stack<>();
        stack.push(new int[]{startR, startC});
        int rows = matrix.length;
        int cols = matrix[0].length;

        while (!stack.isEmpty()) {
            int[] cell = stack.pop();
            int r = cell[0];
            int c = cell[1];

            if (r < 0 || r >= rows || c < 0 || c >= cols || canReach[r][c]) {
                continue;
            }
            canReach[r][c] = true;

            int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (int[] dir : directions) {
                int newR = r + dir[0];
                int newC = c + dir[1];
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && matrix[newR][newC] >= matrix[r][c]) {
                    stack.push(new int[]{newR, newC});
                }
            }
        }
    }
}


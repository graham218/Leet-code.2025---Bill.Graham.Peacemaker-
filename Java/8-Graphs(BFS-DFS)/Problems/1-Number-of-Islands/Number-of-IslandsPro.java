/*
 * Problem: Number of Islands (Leetcode-style)
 * Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 */

import java.util.LinkedList;
import java.util.Queue;

public class NumberOfIslands {

    // ----------------------
    // 1. DFS - Recursive (Classic)
    // ----------------------
    // Suitable for systems that can handle deep recursions (like some GIS mapping tools)
    public int numIslandsDFS(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int count = 0;
        int rows = grid.length;
        int cols = grid[0].length; // Add this line to get the number of columns
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }

    private void dfs(char[][] grid, int i, int j) {
        int rows = grid.length;
        int cols = grid[0].length; // Important: Get column length here too.
        if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] != '1') return;
        grid[i][j] = '0'; // mark visited
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }

    // ----------------------
    // 2. BFS - Queue-based
    // ----------------------
    // Suitable for mobile-based mapping apps that avoid deep stack usage
    public int numIslandsBFS(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int count = 0;
        int rows = grid.length;
        int cols = grid[0].length;  // Get number of columns
        int[] dir = {0, 1, 0, -1, 0};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    Queue<int[]> q = new LinkedList<>();
                    q.offer(new int[]{i, j});
                    grid[i][j] = '0';
                    while (!q.isEmpty()) {
                        int[] curr = q.poll();
                        for (int d = 0; d < 4; d++) {
                            int ni = curr[0] + dir[d];
                            int nj = curr[1] + dir[d + 1];
                            if (ni >= 0 && nj >= 0 && ni < rows && nj < cols && grid[ni][nj] == '1') {
                                q.offer(new int[]{ni, nj});
                                grid[ni][nj] = '0';
                            }
                        }
                    }
                }
            }
        }
        return count;
    }

    // ----------------------
    // 3. Union Find (Disjoint Set)
    // ----------------------
    // Practical in distributed systems like urban planning simulation tools
    public int numIslandsUnionFind(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int rows = grid.length, cols = grid[0].length;
        int[] parent = new int[rows * cols];
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    int id = i * cols + j;
                    parent[id] = id;
                    count++;
                }
            }
        }

        int[] dir = {-1, 0, 1, 0, -1};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dir[d];
                        int nj = j + dir[d + 1];
                        if (ni >= 0 && nj >= 0 && ni < rows && nj < cols && grid[ni][nj] == '1') {
                            int id1 = i * cols + j;
                            int id2 = ni * cols + nj;
                            int root1 = find(parent, id1);
                            int root2 = find(parent, id2);
                            if (root1 != root2) {
                                parent[root1] = root2;
                                count--;
                            }
                        }
                    }
                }
            }
        }

        return count;
    }

    private int find(int[] parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]); // path compression
        }
        return parent[i];
    }

    // ----------------------
    // 4. DFS with Visited Set (Useful for mutable grid reuse)
    // ----------------------
    // Ideal in multi-threaded services to avoid mutating original data
    public int numIslandsDFSVisitedSet(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int rows = grid.length, cols = grid[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfsVisited(grid, visited, i, j);
                    count++;
                }
            }
        }
        return count;
    }

    private void dfsVisited(char[][] grid, boolean[][] visited, int i, int j) {
        int rows = grid.length;
        int cols = grid[0].length;
        if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] != '1' || visited[i][j]) return;

        visited[i][j] = true;
        dfsVisited(grid, visited, i + 1, j);
        dfsVisited(grid, visited, i - 1, j);
        dfsVisited(grid, visited, i, j + 1);
        dfsVisited(grid, visited, i, j - 1);
    }

    // ----------------------
    // 5. Flood Fill Variation (BFS-style for Map Coloring Systems)
    // ----------------------
    public int numIslandsFloodFill(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int count = 0;
        int rows = grid.length;
        int cols = grid[0].length;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    floodFill(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }

    private void floodFill(char[][] grid, int i, int j) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{i, j});
        grid[i][j] = '0';

        int[] dirs = {-1, 0, 1, 0, -1};
        int rows = grid.length;
        int cols = grid[0].length;
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            for (int d = 0; d < 4; d++) {
                int ni = cell[0] + dirs[d];
                int nj = cell[1] + dirs[d + 1];
                if (ni >= 0 && nj >= 0 && ni < rows && nj < cols && grid[ni][nj] == '1') {
                    queue.offer(new int[]{ni, nj});
                    grid[ni][nj] = '0';
                }
            }
        }
    }

    public static void main(String[] args) {
        NumberOfIslands solution = new NumberOfIslands();

        // Example Grid
        char[][] grid = {
                {'1', '1', '1', '1', '0'},
                {'1', '1', '0', '1', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '0', '0', '0'}
        };

        // Using DFS
        int numIslandsDFS = solution.numIslandsDFS(grid);
        System.out.println("Number of islands (DFS): " + numIslandsDFS); // Output: 1

        // Using BFS
        int numIslandsBFS = solution.numIslandsBFS(grid);
        System.out.println("Number of islands (BFS): " + numIslandsBFS); // Output: 1

        // Using Union Find
        char[][] grid3 = {
                {'1', '1', '0', '0', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '1', '0', '0'},
                {'0', '0', '0', '1', '1'}
        };
        int numIslandsUnionFind = solution.numIslandsUnionFind(grid3);
        System.out.println("Number of islands (Union Find): " + numIslandsUnionFind); // Output: 3

        // Using DFS with Visited Set
        char[][] grid4 = {
                {'1', '1', '0', '0', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '1', '0', '0'},
                {'0', '0', '0', '1', '1'}
        };
        int numIslandsDFSVisitedSet = solution.numIslandsDFSVisitedSet(grid4);
        System.out.println("Number of islands (DFS with Visited Set): " + numIslandsDFSVisitedSet); // Output: 3

        // Using Flood Fill
        char[][] grid5 = {
                {'1', '1', '0', '0', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '1', '0', '0'},
                {'0', '0', '0', '1', '1'}
        };
        int numIslandsFloodFill = solution.numIslandsFloodFill(grid5);
        System.out.println("Number of islands (Flood Fill): " + numIslandsFloodFill); // Output: 3
    }
}

/*
 * Real-world use cases:
 * - Urban planners visualizing connected land masses from satellite images.
 * - Game development: determining territory control or flood areas.
 * - Map coloring or heatmap zoning in smart city applications.
 * - Agricultural zoning and land-use classification.
 * - Environmental monitoring of fragmented ecosystems.
 */

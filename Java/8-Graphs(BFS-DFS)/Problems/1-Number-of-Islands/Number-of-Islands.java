import java.util.*;

public class NumberOfIslands {

    /**
     * Approach 1: DFS Recursive
     * Traverse the grid and call DFS to sink the island.
     */
    public int numIslandsDFS(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;
        int count = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }

    private void dfs(char[][] grid, int i, int j) {
        // Check bounds and if current cell is water
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != '1') return;
        grid[i][j] = '0'; // mark as visited
        dfs(grid, i - 1, j);
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }

    /**
     * Approach 2: BFS Iterative
     * Use queue to explore neighbors level by level.
     */
    public int numIslandsBFS(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;
        int count = 0;
        int rows = grid.length, cols = grid[0].length;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    grid[i][j] = '0';
                    while (!queue.isEmpty()) {
                        int[] cell = queue.poll();
                        int r = cell[0], c = cell[1];
                        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
                        for (int[] d : directions) {
                            int nr = r + d[0], nc = c + d[1];
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                                queue.offer(new int[]{nr, nc});
                                grid[nr][nc] = '0';
                            }
                        }
                    }
                }
            }
        }
        return count;
    }

    /**
     * Approach 3: Union Find (Disjoint Set Union)
     */
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

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    int id = i * cols + j;
                    if (i + 1 < rows && grid[i + 1][j] == '1') union(parent, id, (i + 1) * cols + j);
                    if (j + 1 < cols && grid[i][j + 1] == '1') union(parent, id, i * cols + (j + 1));
                }
            }
        }

        Set<Integer> uniqueParents = new HashSet<>();
        for (int i = 0; i < rows * cols; i++) {
            if (grid[i / cols][i % cols] == '1') {
                uniqueParents.add(find(parent, i));
            }
        }
        return uniqueParents.size();
    }

    private int find(int[] parent, int i) {
        if (parent[i] != i) parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    private void union(int[] parent, int i, int j) {
        int rootI = find(parent, i);
        int rootJ = find(parent, j);
        if (rootI != rootJ) {
            parent[rootJ] = rootI;
        }
    }

    /**
     * Approach 4: DFS Using Stack (Iterative DFS)
     */
    public int numIslandsIterativeDFS(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;
        int count = 0;
        int rows = grid.length, cols = grid[0].length;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    Stack<int[]> stack = new Stack<>();
                    stack.push(new int[]{i, j});
                    grid[i][j] = '0';
                    while (!stack.isEmpty()) {
                        int[] cell = stack.pop();
                        int r = cell[0], c = cell[1];
                        int[][] dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                        for (int[] d : dirs) {
                            int nr = r + d[0], nc = c + d[1];
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                                stack.push(new int[]{nr, nc});
                                grid[nr][nc] = '0';
                            }
                        }
                    }
                    count++;
                }
            }
        }
        return count;
    }

    /**
     * Approach 5: DFS with Visited Matrix
     * Keep original grid intact using a visited matrix.
     */
    public int numIslandsWithVisited(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;
        int rows = grid.length, cols = grid[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfsWithVisited(grid, visited, i, j);
                    count++;
                }
            }
        }
        return count;
    }

    private void dfsWithVisited(char[][] grid, boolean[][] visited, int i, int j) {
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != '1' || visited[i][j]) return;
        visited[i][j] = true;
        dfsWithVisited(grid, visited, i - 1, j);
        dfsWithVisited(grid, visited, i + 1, j);
        dfsWithVisited(grid, visited, i, j - 1);
        dfsWithVisited(grid, visited, i, j + 1);
    }

    // Test stub (optional): Add your own main method for testing each approach.
    public static void main(String[] args) {
        NumberOfIslands sol = new NumberOfIslands();
        char[][] grid = {
                {'1','1','0','0','0'},
                {'1','1','0','0','0'},
                {'0','0','1','0','0'},
                {'0','0','0','1','1'}
        };

        System.out.println("DFS Recursive: " + sol.numIslandsDFS(copyGrid(grid)));
        System.out.println("BFS Iterative: " + sol.numIslandsBFS(copyGrid(grid)));
        System.out.println("Union Find: " + sol.numIslandsUnionFind(copyGrid(grid)));
        System.out.println("Iterative DFS: " + sol.numIslandsIterativeDFS(copyGrid(grid)));
        System.out.println("DFS with Visited: " + sol.numIslandsWithVisited(copyGrid(grid)));
    }

    private static char[][] copyGrid(char[][] grid) {
        char[][] copy = new char[grid.length][grid[0].length];
        for (int i = 0; i < grid.length; i++) {
            System.arraycopy(grid[i], 0, copy[i], 0, grid[0].length);
        }
        return copy;
    }
}

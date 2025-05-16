import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class HamiltonianCycle {

    private static final int V = 5; // Number of vertices in the graph.  Can be changed.

    // 1. Basic Backtracking Approach
    //   - Simple, recursive backtracking to find a Hamiltonian Cycle.
    //   - Good for understanding the core concept.
    //   - Real-world application:  Route planning for a robot in a small, simple environment.
    public static boolean hasHamiltonianCycleBasic(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1); // Initialize path array
        path[0] = 0; // Start from vertex 0
        return hasHamiltonianCycleBasicUtil(graph, path, 1);
    }

    private static boolean hasHamiltonianCycleBasicUtil(int[][] graph, int[] path, int pos) {
        if (pos == V) {
            // Check if there is an edge from the last vertex to the starting vertex (0)
            return graph[path[pos - 1]][0] == 1;
        }

        for (int v = 0; v < V; v++) {
            // Check if v is a valid next vertex
            if (isSafeBasic(v, graph, path, pos)) {
                path[pos] = v;
                if (hasHamiltonianCycleBasicUtil(graph, path, pos + 1)) {
                    return true;
                }
                // Backtrack: Remove v from path and try different vertex
                path[pos] = -1;
            }
        }
        return false;
    }

    private static boolean isSafeBasic(int v, int[][] graph, int[] path, int pos) {
        // Check if the vertex v is adjacent to the previous vertex in the path
        if (graph[path[pos - 1]][v] == 0) {
            return false;
        }

        // Check if the vertex v is already included in the path
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    }


    // 2. Backtracking with Forward Checking
    //   - Improves upon the basic approach by adding a forward checking step.
    //   - Checks if a vertex has unvisited neighbors before adding it to the path.
    //   - Real-world application:  More efficient route planning for delivery trucks,
    //     where it's important to ensure all locations can be visited.
    public static boolean hasHamiltonianCycleForwardChecking(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        boolean[] visited = new boolean[V];
        visited[0] = true; // Mark the starting node as visited
        return hasHamiltonianCycleForwardCheckingUtil(graph, path, 1, visited);
    }

    private static boolean hasHamiltonianCycleForwardCheckingUtil(int[][] graph, int[] path, int pos, boolean[] visited) {
        if (pos == V) {
            return graph[path[pos - 1]][0] == 1;
        }

        for (int v = 0; v < V; v++) {
            if (isSafeForwardChecking(v, graph, visited, path, pos)) {
                path[pos] = v;
                visited[v] = true; // Mark vertex v as visited
                if (hasHamiltonianCycleForwardCheckingUtil(graph, path, pos + 1, visited)) {
                    return true;
                }
                path[pos] = -1;
                visited[v] = false; // Backtrack: unmark visited
            }
        }
        return false;
    }

    private static boolean isSafeForwardChecking(int v, int[][] graph, boolean[] visited, int[] path, int pos) {
        if (graph[path[pos - 1]][v] == 0) {
            return false;
        }
        if (visited[v]) {
            return false;
        }

        // Forward checking: Check if v has any unvisited neighbors.  If not, it's a dead end.
        boolean hasUnvisitedNeighbor = false;
        for (int i = 0; i < V; i++) {
            if (graph[v][i] == 1 && !visited[i]) {
                hasUnvisitedNeighbor = true;
                break;
            }
        }
        if (pos == V - 1 && graph[v][0] != 1){
            return false;
        }
        return hasUnvisitedNeighbor || pos == V - 1; // Allow it if it is the last node.
    }


    // 3. Backtracking with Degree Ordering
    //   - Optimizes the search by considering vertices in increasing order of their degree.
    //   - The degree of a vertex is the number of edges connected to it.
    //   - Real-world application:  Useful in network routing, where nodes with fewer connections
    //     might be more constrained and should be considered earlier.
    public static boolean hasHamiltonianCycleDegreeOrdering(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        boolean[] visited = new boolean[V];
        visited[0] = true;
        int[] degree = new int[V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                degree[i] += graph[i][j];
            }
        }
        return hasHamiltonianCycleDegreeOrderingUtil(graph, path, 1, visited, degree);
    }

    private static boolean hasHamiltonianCycleDegreeOrderingUtil(int[][] graph, int[] path, int pos, boolean[] visited, int[] degree) {
        if (pos == V) {
            return graph[path[pos - 1]][0] == 1;
        }

        // Create an array of vertices and sort it based on degree.
        Integer[] vertices = new Integer[V];
        for (int i = 0; i < V; i++) {
            vertices[i] = i;
        }
        Arrays.sort(vertices, (a, b) -> degree[a] - degree[b]); // Sort by degree

        for (int v : vertices) {
            if (isSafeForwardChecking(v, graph, visited, path, pos)) { // Use Forward Checking
                path[pos] = v;
                visited[v] = true;
                if (hasHamiltonianCycleDegreeOrderingUtil(graph, path, pos + 1, visited, degree)) {
                    return true;
                }
                path[pos] = -1;
                visited[v] = false;
            }
        }
        return false;
    }


    // 4. Backtracking with Warnsdorff's Rule (for Knight's Tour)
    //   - A heuristic specifically designed for the Knight's Tour problem (a special case
    //     of the Hamiltonian Cycle problem on a chessboard).
    //   - Prioritizes moving to the square with the fewest possible next moves.
    //   - Real-world application:  Path planning for specialized robotic arms or movement
    //     in constrained grid-like environments.
    public static boolean hasHamiltonianCycleWarnsdorff(int[][] graph, int startX, int startY) {
        int[][] path = new int[V][2]; // Store (x, y) coordinates of the path
        // Initialize path
        path[0][0] = startX;
        path[0][1] = startY;

        boolean[][] visited = new boolean[V][V];
        visited[startX][startY] = true;

        return hasHamiltonianCycleWarnsdorffUtil(graph, path, 1, visited);
    }

    private static boolean hasHamiltonianCycleWarnsdorffUtil(int[][] graph, int[][] path, int pos, boolean[][] visited) {
        if (pos == V) {
            int startX = path[0][0];
            int startY = path[0][1];
            int endX = path[pos-1][0];
            int endY = path[pos-1][1];
            return graph[endX][startX] == 1;
        }

        int currX = path[pos - 1][0];
        int currY = path[pos - 1][1];

        // Get valid moves (neighbors)
        List<int[]> moves = getValidMovesWarnsdorff(currX, currY, visited, graph);

        // Sort moves using Warnsdorff's Rule (sort by degree of the neighbor)
        moves.sort((a, b) -> countNeighbors(a[0], a[1], visited, graph) - countNeighbors(b[0], b[1], visited, graph));

        for (int[] move : moves) {
            int nextX = move[0];
            int nextY = move[1];

            path[pos][0] = nextX;
            path[pos][1] = nextY;
            visited[nextX][nextY] = true;

            if (hasHamiltonianCycleWarnsdorffUtil(graph, path, pos + 1, visited)) {
                return true;
            }

            path[pos][0] = -1; // Backtrack
            path[pos][1] = -1;
            visited[nextX][nextY] = false;
        }

        return false;
    }

    private static List<int[]> getValidMovesWarnsdorff(int x, int y, boolean[][] visited, int[][] graph) {
        List<int[]> moves = new ArrayList<>();
        int[] dx = {1, 2, 2, 1, -1, -2, -2, -1};
        int[] dy = {2, 1, -1, -2, -2, -1, 1, 2};

        for (int i = 0; i < 8; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < V && newY >= 0 && newY < V && !visited[newX][newY] && graph[x][newX] == 1) {
                moves.add(new int[]{newX, newY});
            }
        }
        return moves;
    }

    private static int countNeighbors(int x, int y, boolean[][] visited, int[][] graph) {
        int count = 0;
        int[] dx = {1, 2, 2, 1, -1, -2, -2, -1};
        int[] dy = {2, 1, -1, -2, -2, -1, 1, 2};
        for (int i = 0; i < 8; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < V && newY >= 0 && newY < V && !visited[newX][newY] && graph[x][newX] == 1) {
                count++;
            }
        }
        return count;
    }



    // 5. Randomized Backtracking
    //   - Introduces randomness into the vertex selection process.
    //   - Can help to escape local optima and explore a wider range of possible solutions.
    //   - Real-world application:  Useful for generating diverse solutions, such as in
    //     artistic design or game level generation.
    public static boolean hasHamiltonianCycleRandomized(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        boolean[] visited = new boolean[V];
        visited[0] = true;
        return hasHamiltonianCycleRandomizedUtil(graph, path, 1, visited);
    }

    private static boolean hasHamiltonianCycleRandomizedUtil(int[][] graph, int[] path, int pos, boolean[] visited) {
        if (pos == V) {
            return graph[path[pos - 1]][0] == 1;
        }

        List<Integer> candidates = new ArrayList<>();
        for (int v = 0; v < V; v++) {
            if (isSafeForwardChecking(v, graph, visited, path, pos)) { // Use forward checking
                candidates.add(v);
            }
        }

        // Randomly shuffle the candidates
        java.util.Collections.shuffle(candidates);

        for (int v : candidates) {
            path[pos] = v;
            visited[v] = true;
            if (hasHamiltonianCycleRandomizedUtil(graph, path, pos + 1, visited)) {
                return true;
            }
            path[pos] = -1;
            visited[v] = false;
        }
        return false;
    }



    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example graph (adjacency matrix representation)
        int[][] graph = {
                {0, 1, 0, 1, 0},
                {1, 0, 1, 1, 1},
                {0, 1, 0, 0, 1},
                {1, 1, 0, 0, 1},
                {0, 1, 1, 1, 0},
        };

        System.out.println("Hamiltonian Cycle Detection");
        System.out.println("-----------------------------");
        System.out.println("Graph (Adjacency Matrix):");
        for (int i = 0; i < V; i++) {
            System.out.println(Arrays.toString(graph[i]));
        }
        System.out.println();

        // Basic Backtracking
        System.out.println("1. Basic Backtracking:");
        if (hasHamiltonianCycleBasic(graph)) {
            System.out.println("Hamiltonian Cycle exists (Basic).");
        } else {
            System.out.println("Hamiltonian Cycle does not exist (Basic).");
        }
        System.out.println();

        // Backtracking with Forward Checking
        System.out.println("2. Backtracking with Forward Checking:");
        if (hasHamiltonianCycleForwardChecking(graph)) {
            System.out.println("Hamiltonian Cycle exists (Forward Checking).");
        } else {
            System.out.println("Hamiltonian Cycle does not exist (Forward Checking).");
        }
        System.out.println();

        // Backtracking with Degree Ordering
        System.out.println("3. Backtracking with Degree Ordering:");
        if (hasHamiltonianCycleDegreeOrdering(graph)) {
            System.out.println("Hamiltonian Cycle exists (Degree Ordering).");
        } else {
            System.out.println("Hamiltonian Cycle does not exist (Degree Ordering).");
        }
        System.out.println();

        // Backtracking with Warnsdorff's Rule (Knight's Tour - Example on a 5x5 grid)
        System.out.println("4. Backtracking with Warnsdorff's Rule (Knight's Tour - Example):");
        //  For Warnsdorff, the graph needs to represent knight's moves.  We'll use a simple example.
        int startXWarnsdorff = 0;
        int startYWarnsdorff = 0;
        if (hasHamiltonianCycleWarnsdorff(graph, startXWarnsdorff, startYWarnsdorff)) {
            System.out.println("Hamiltonian Cycle exists (Warnsdorff's Rule - Knight's Tour).");
        } else {
            System.out.println("Hamiltonian Cycle does not exist (Warnsdorff's Rule - Knight's Tour).");
        }
        System.out.println();

        // Randomized Backtracking
        System.out.println("5. Randomized Backtracking:");
        if (hasHamiltonianCycleRandomized(graph)) {
            System.out.println("Hamiltonian Cycle exists (Randomized).");
        } else {
            System.out.println("Hamiltonian Cycle does not exist (Randomized).");
        }
        System.out.println();

        scanner.close();
    }
}


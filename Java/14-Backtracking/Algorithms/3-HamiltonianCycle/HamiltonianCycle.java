import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class HamiltonianCycle {

    private static final int V = 5; // Number of vertices in the graph.  Can be changed.

    // 1. Basic Backtracking Approach
    //   - Uses a simple recursive backtracking algorithm.
    //   - Tries all possible paths, and checks if they form a Hamiltonian Cycle.
    //   - Not very efficient for larger graphs.
    public static boolean hasHamiltonianCycle1(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1); // Initialize path array with -1
        path[0] = 0; // Start from vertex 0
        return solveHamiltonianCycle1(graph, path, 1);
    }

    private static boolean solveHamiltonianCycle1(int[][] graph, int[] path, int pos) {
        // Base case: All vertices are included in the path
        if (pos == V) {
            // Check if there is an edge from the last vertex to the starting vertex (0)
            if (graph[path[pos - 1]][0] == 1) {
                return true; // Form a cycle
            } else {
                return false; // Path is not a cycle
            }
        }

        // Try different vertices as the next vertex in the path
        for (int v = 0; v < V; v++) {
            // Check if the current vertex v can be added to the path
            if (isSafe1(v, graph, path, pos)) {
                path[pos] = v; // Add vertex v to the path
                // Recursively try to find a path for the remaining vertices
                if (solveHamiltonianCycle1(graph, path, pos + 1)) {
                    return true; // Solution found
                }
                // Backtrack: Remove vertex v from the path and try other options
                path[pos] = -1;
            }
        }
        // If no vertex can be added to the path, return false
        return false;
    }

    private static boolean isSafe1(int v, int[][] graph, int[] path, int pos) {
        // Check if the vertex v is adjacent to the previous vertex in the path
        if (graph[path[pos - 1]][v] == 0) {
            return false; // Not adjacent
        }

        // Check if the vertex v is already included in the path
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false; // Already in path
            }
        }
        return true; // Vertex v is safe to add
    }


    // 2. Backtracking with Adjacency List
    //    - Uses an adjacency list to represent the graph, which can be more efficient for sparse graphs.
    public static boolean hasHamiltonianCycle2(List<List<Integer>> adjList) {
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        return solveHamiltonianCycle2(adjList, path, 1);
    }

    private static boolean solveHamiltonianCycle2(List<List<Integer>> adjList, int[] path, int pos) {
        if (pos == V) {
            if (adjList.get(path[pos - 1]).contains(0)) {
                return true;
            } else {
                return false;
            }
        }

        for (int v : adjList.get(path[pos - 1])) { // Iterate over neighbors
            if (isSafe2(v, path, pos)) {
                path[pos] = v;
                if (solveHamiltonianCycle2(adjList, path, pos + 1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }
        return false;
    }

    private static boolean isSafe2(int v, int[] path, int pos) {
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    }

    // 3. Backtracking with Degree Check
    //    - Before starting the backtracking, it checks if every vertex has a degree of at least 2.
    //    - A Hamiltonian Cycle is not possible if any vertex has a degree less than 2.
    public static boolean hasHamiltonianCycle3(int[][] graph) {
        for (int i = 0; i < V; i++) {
            int degree = 0;
            for (int j = 0; j < V; j++) {
                if (graph[i][j] == 1) {
                    degree++;
                }
            }
            if (degree < 2) {
                return false; // Hamiltonian Cycle not possible
            }
        }
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        return solveHamiltonianCycle3(graph, path, 1);
    }

    private static boolean solveHamiltonianCycle3(int[][] graph, int[] path, int pos) {
        if (pos == V) {
            if (graph[path[pos - 1]][0] == 1) {
                return true;
            } else {
                return false;
            }
        }

        for (int v = 0; v < V; v++) {
            if (isSafe3(v, graph, path, pos)) {
                path[pos] = v;
                if (solveHamiltonianCycle3(graph, path, pos + 1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }
        return false;
    }

    private static boolean isSafe3(int v, int[][] graph, int[] path, int pos) {
        if (graph[path[pos - 1]][v] == 0) {
            return false;
        }
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    }

    // 4. Backtracking with Forward Checking
    //    - After adding a vertex to the path, it checks if there are enough unvisited neighbors
    //      for the remaining vertices in the path.
    //    - This can help prune the search space and improve efficiency.
    public static boolean hasHamiltonianCycle4(int[][] graph) {
        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        return solveHamiltonianCycle4(graph, path, 1);
    }

    private static boolean solveHamiltonianCycle4(int[][] graph, int[] path, int pos) {
        if (pos == V) {
            if (graph[path[pos - 1]][0] == 1) {
                return true;
            } else {
                return false;
            }
        }

        for (int v = 0; v < V; v++) {
            if (isSafe4(v, graph, path, pos)) {
                path[pos] = v;
                if (solveHamiltonianCycle4(graph, path, pos + 1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }
        return false;
    }

    private static boolean isSafe4(int v, int[][] graph, int[] path, int pos) {
        if (graph[path[pos - 1]][v] == 0) {
            return false;
        }
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }

        // Forward checking: Check if enough neighbors are available for remaining vertices
        int remainingVertices = V - pos - 1;
        int availableNeighbors = 0;
        for (int i = 0; i < V; i++) {
            if (graph[v][i] == 1 && !contains(path, i, pos)) {
                availableNeighbors++;
            }
        }
        if (availableNeighbors < remainingVertices) {
            return false; // Not enough neighbors
        }

        return true;
    }

    private static boolean contains(int[] array, int value, int pos) {
        for (int i = 0; i < pos; i++) {
            if (array[i] == value) {
                return true;
            }
        }
        return false;
    }


    // 5. Backtracking with Optimized Adjacency List and Degree Check
    //    - Combines the adjacency list representation with the degree check for better performance.
    public static boolean hasHamiltonianCycle5(List<List<Integer>> adjList) {
        // Degree Check
        for (int i = 0; i < V; i++) {
            if (adjList.get(i).size() < 2) {
                return false;
            }
        }

        int[] path = new int[V];
        Arrays.fill(path, -1);
        path[0] = 0;
        return solveHamiltonianCycle5(adjList, path, 1);
    }

    private static boolean solveHamiltonianCycle5(List<List<Integer>> adjList, int[] path, int pos) {
        if (pos == V) {
            if (adjList.get(path[pos - 1]).contains(0)) {
                return true;
            } else {
                return false;
            }
        }

        for (int v : adjList.get(path[pos - 1])) {
            if (isSafe5(v, path, pos)) {
                path[pos] = v;
                if (solveHamiltonianCycle5(adjList, path, pos + 1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }
        return false;
    }

    private static boolean isSafe5(int v, int[] path, int pos) {
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    }



    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix
        int[][] graph1 = {
                {0, 1, 0, 1, 0},
                {1, 0, 1, 1, 1},
                {0, 1, 0, 0, 1},
                {1, 1, 0, 0, 1},
                {0, 1, 1, 1, 0},
        };

        // Example graph represented as an adjacency list
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adjList.add(new ArrayList<>());
        }
        adjList.get(0).add(1);
        adjList.get(0).add(3);
        adjList.get(1).add(0);
        adjList.get(1).add(2);
        adjList.get(1).add(3);
        adjList.get(1).add(4);
        adjList.get(2).add(1);
        adjList.get(2).add(4);
        adjList.get(3).add(0);
        adjList.get(3).add(1);
        adjList.get(3).add(4);
        adjList.get(4).add(1);
        adjList.get(4).add(2);
        adjList.get(4).add(3);


        System.out.println("Hamiltonian Cycle Detection:");
        System.out.println("\nUsing Adjacency Matrix:");
        System.out.println("--------------------------");
        System.out.println("Approach 1 (Basic Backtracking): " + hasHamiltonianCycle1(graph1));
        System.out.println("Approach 3 (Degree Check): " + hasHamiltonianCycle3(graph1));
        System.out.println("Approach 4 (Forward Checking): " + hasHamiltonianCycle4(graph1));

        System.out.println("\nUsing Adjacency List:");
        System.out.println("--------------------------");
        System.out.println("Approach 2 (Adjacency List): " + hasHamiltonianCycle2(adjList));
        System.out.println("Approach 5 (Optimized List + Degree Check): " + hasHamiltonianCycle5(adjList));


        // Test case where a Hamiltonian cycle exists
        int[][] graph2 = {
                {0, 1, 0, 0, 1},
                {1, 0, 1, 0, 0},
                {0, 1, 0, 1, 0},
                {0, 0, 1, 0, 1},
                {1, 0, 0, 1, 0},
        };
        System.out.println("\nTest Case with Hamiltonian Cycle:");
        System.out.println("Approach 1 (Basic Backtracking): " + hasHamiltonianCycle1(graph2)); // Should return true


        // Test case where a Hamiltonian cycle does not exist (Degree Check)
        int[][] graph3 = {
                {0, 1, 0, 0, 0},
                {1, 0, 1, 0, 0},
                {0, 1, 0, 0, 0},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0},
        };
        System.out.println("\nTest Case without Hamiltonian Cycle (Degree < 2):");
        System.out.println("Approach 1 (Basic Backtracking): " + hasHamiltonianCycle1(graph3)); // Should return false, but might take time
        System.out.println("Approach 3 (Degree Check): " + hasHamiltonianCycle3(graph3));       // Should return false quickly

        // Test case with a larger graph (for performance comparison)
        int V_LARGE = 8;
        int[][] graph4 = new int[V_LARGE][V_LARGE];
        for (int i = 0; i < V_LARGE; i++) {
            for (int j = 0; j < V_LARGE; j++) {
                if (Math.random() < 0.3) { // Adjust probability for graph density
                    graph4[i][j] = 1;
                    graph4[j][i] = 1; // Ensure undirected graph
                }
            }
            graph4[i][i] = 0; // No self-loops
        }

        System.out.println("\nPerformance Test (Large Graph, V = " + V_LARGE + "):");
        long startTime = System.nanoTime();
        boolean result1 = hasHamiltonianCycle1(graph4); // Basic backtracking (may be slow)
        long endTime = System.nanoTime();
        System.out.println("Approach 1 (Basic Backtracking): " + result1 + " (Time: " + (endTime - startTime) / 1e6 + " ms)");

        startTime = System.nanoTime();
        boolean result3 = hasHamiltonianCycle3(graph4); // Backtracking with degree check
        endTime = System.nanoTime();
        System.out.println("Approach 3 (Degree Check): " + result3 + " (Time: " + (endTime - startTime) / 1e6 + " ms)");

        startTime = System.nanoTime();
        boolean result4 = hasHamiltonianCycle4(graph4); // Backtracking with forward checking
        endTime = System.nanoTime();
        System.out.println("Approach 4 (Forward Checking): " + result4 + " (Time: " + (endTime - startTime) / 1e6 + " ms)");


    }
}


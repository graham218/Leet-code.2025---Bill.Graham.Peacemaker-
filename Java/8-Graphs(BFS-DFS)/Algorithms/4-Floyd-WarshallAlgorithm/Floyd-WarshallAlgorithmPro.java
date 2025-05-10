import java.util.Arrays;

public class FloydWarshall {

    // Define a constant for infinity, used to represent unreachable nodes.  Using Integer.MAX_VALUE directly can lead to overflow issues
    // when adding to it, so we use a slightly smaller value.
    private static final int INF = 1000000000; // A large number, but not too close to Integer.MAX_VALUE

    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix.  The value at matrix[i][j] represents the weight of the edge
        // from node i to node j.  If there is no direct edge, we use INF.
        int[][] graph = {
                {0, 5, INF, 10},
                {INF, 0, 3, INF},
                {INF, INF, 0, 1},
                {INF, INF, INF, 0}
        };

        System.out.println("Original Graph:");
        printMatrix(graph);

        // 1. Basic Floyd-Warshall Algorithm:  Finds the shortest paths between all pairs of nodes in the graph.
        int[][] shortestPaths1 = floydWarshallBasic(graph);
        System.out.println("\n1. Basic Floyd-Warshall Algorithm:");
        printMatrix(shortestPaths1);

        // 2. Floyd-Warshall with Path Reconstruction:  Computes the shortest paths and also determines the intermediate
        // nodes in those paths, allowing us to reconstruct the full path.
        int[][] shortestPaths2 = floydWarshallWithPathReconstruction(graph);
        System.out.println("\n2. Floyd-Warshall with Path Reconstruction:");
        printMatrix(shortestPaths2);
        // Example of how to reconstruct a path from node 0 to node 3
        System.out.println("Example Path from 0 to 3: " + reconstructPath(graph, 0, 3));


        // 3. Floyd-Warshall for Detecting Negative Cycles:  Checks if the graph contains any negative-weight cycles.  If a negative
        // cycle exists, the shortest path between some nodes can become infinitely small (negative), which can cause problems
        // in some applications.
        boolean hasNegativeCycle = floydWarshallNegativeCycleDetection(graph);
        System.out.println("\n3. Floyd-Warshall for Detecting Negative Cycles:");
        System.out.println("Has Negative Cycle: " + hasNegativeCycle);

        // 4. Floyd-Warshall with Optimization (Space):  The basic Floyd-Warshall algorithm uses a 2D array to store the
        // intermediate distances.  We can optimize this to use only a 1D array, reducing the space complexity.
        int[] shortestPaths4 = floydWarshallOptimizedSpace(graph);
        System.out.println("\n4. Floyd-Warshall with Optimization (Space):");
        printArrayAsMatrix(shortestPaths4, graph.length); // Print 1D array as matrix

        // 5. Floyd-Warshall for finding the Transitive Closure: Finds if there is a path between all pairs of vertices
        // A transitive closure matrix has 1 at i,j if a path exists from i to j, otherwise 0.
        int[][] transitiveClosure = transitiveClosure(graph);
        System.out.println("\n5. Floyd-Warshall for Transitive Closure:");
        printMatrix(transitiveClosure);
    }

    /**
     * 1. Basic Floyd-Warshall Algorithm Implementation:
     *
     * Computes the shortest distances between all pairs of nodes in a graph.
     *
     * @param graph A square matrix representing the graph, where graph[i][j] is the weight of the edge from node i to node j.
     * Use INF (a large value) to represent no direct edge.  The graph matrix is assumed to represent
     * edge weights, and the algorithm will modify it to store shortest path distances.
     * @return A new matrix representing the shortest distances between all pairs of nodes.  The original graph
     * matrix is NOT modified by this method.
     */
    public static int[][] floydWarshallBasic(int[][] graph) {
        int V = graph.length; // Number of vertices in the graph.
        // Create a copy of the graph to store the shortest path distances.  This is important to avoid modifying
        // the original graph data.
        int[][] dist = new int[V][V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
            }
        }

        // The core of the Floyd-Warshall algorithm.  It iterates through all possible intermediate nodes (k).
        // For each pair of nodes (i, j), it checks if going through k is shorter than the current shortest path
        // from i to j.
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    // Check for overflow before adding.  If either dist[i][k] or dist[k][j] is INF, adding them could
                    // result in a value that wraps around to a small positive number, leading to incorrect results.
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }

    /**
     * 2. Floyd-Warshall Algorithm with Path Reconstruction:
     *
     * Computes the shortest distances between all pairs of nodes and also stores the intermediate nodes
     * used in the shortest paths.  This allows for reconstructing the actual path taken.
     *
     * @param graph A square matrix representing the graph (same format as floydWarshallBasic).
     * @return A new matrix representing the shortest distances between all pairs of nodes.
     */

    public static int[][] floydWarshallWithPathReconstruction(int[][] graph) {
        int V = graph.length;
        int[][] dist = new int[V][V];
        int[][] next = new int[V][V]; // Stores the intermediate node in the shortest path from i to j.

        // Initialize the distance matrix and the 'next' matrix.
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
                if (graph[i][j] != INF && i != j) {
                    next[i][j] = j; // Initially, the next node is j itself (direct edge).
                } else {
                    next[i][j] = -1; // No intermediate node.
                }
            }
        }

        // Core of the algorithm, same as before, but also update the 'next' matrix.
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k]; // The next node on the path from i to j is now the same as the next node on the path from i to k.
                    }
                }
            }
        }
        return dist;
    }

    /**
     * Helper function to reconstruct the shortest path between two nodes, using the 'next' matrix
     * computed by floydWarshallWithPathReconstruction.
     *
     * @param graph The original graph (used to check for valid nodes).
     * @param start The starting node.
     * @param end   The ending node.
     * @return A list of the nodes in the shortest path from start to end, or an empty list if no path exists.
     */
    public static String reconstructPath(int[][] graph, int start, int end) {
        int V = graph.length;
        if (start < 0 || start >= V || end < 0 || end >= V) {
            return "Invalid input: Start or end node out of bounds.";
        }

        int[][] next = new int[V][V]; // Create the 'next' matrix.
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (graph[i][j] != INF && i != j) {
                    next[i][j] = j;
                } else {
                    next[i][j] = -1;
                }
            }
        }

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (graph[i][k] != INF && graph[k][j] != INF && graph[i][k] + graph[k][j] < graph[i][j]) {
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        if (next[start][end] == -1) {
            return "No path exists between " + start + " and " + end;
        } else {
            StringBuilder path = new StringBuilder();
            path.append(start);
            int current = start;
            while (current != end) {
                current = next[current][end];
                path.append(" -> ").append(current);
            }
            return path.toString();
        }
    }


    /**
     * 3. Floyd-Warshall Algorithm for Detecting Negative Cycles:
     *
     * Detects if a graph contains any negative-weight cycles.  A negative-weight cycle is a cycle in the graph
     * where the sum of the edge weights is negative.  The presence of a negative cycle means that there is no
     * shortest path between some nodes, as you can keep going around the cycle to decrease the path length
     * indefinitely.
     *
     * @param graph A square matrix representing the graph.
     * @return true if the graph contains a negative cycle, false otherwise.
     */
    public static boolean floydWarshallNegativeCycleDetection(int[][] graph) {
        int V = graph.length;
        int[][] dist = new int[V][V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
            }
        }

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // After the main loop, check the diagonal elements of the distance matrix.  If any diagonal element is negative,
        // it means there is a negative-weight cycle reachable from that node.  This is because the diagonal element
        // represents the shortest path from a node to itself.  In a graph with no negative cycles, this should always be 0.
        for (int i = 0; i < V; i++) {
            if (dist[i][i] < 0) {
                return true; // Negative cycle detected.
            }
        }
        return false; // No negative cycle found.
    }

    /**
     * 4. Floyd-Warshall Algorithm with Optimization (Space):
     *
     * Optimizes the space complexity of the Floyd-Warshall algorithm from O(V^2) to O(V) by using a single 1D array
     * instead of a 2D array.  This is possible because the algorithm iteratively updates the distances, and we
     * can overwrite the previous distances in place.
     *
     * @param graph A square matrix representing the graph.
     * @return A 1D array representing the shortest distances between all pairs of nodes.  The array is organized such
     * that the distances from node i to all other nodes are stored in consecutive elements.  Specifically,
     * the distance from node i to node j is stored at index i * V + j, where V is the number of vertices.
     */
    public static int[] floydWarshallOptimizedSpace(int[][] graph) {
        int V = graph.length;
        int[] dist = new int[V * V]; // 1D array to store distances.

        // Initialize the 1D array from the 2D graph matrix.
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i * V + j] = graph[i][j];
            }
        }

        // Core of the algorithm, adapted for the 1D array representation.
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i * V + k] != INF && dist[k * V + j] != INF) {
                        dist[i * V + j] = Math.min(dist[i * V + j], dist[i * V + k] + dist[k * V + j]);
                    }
                }
            }
        }
        return dist;
    }

    /**
     * 5. Floyd-Warshall Algorithm for Transitive Closure:
     *
     * Computes the transitive closure of a graph.  The transitive closure is a matrix that indicates whether
     * there is a path (of any length) between any two nodes in the graph.  If there is a path from node i to node j,
     * the (i, j) entry in the transitive closure matrix is 1; otherwise, it is 0.
     *
     * @param graph A square matrix representing the graph.
     * @return A new matrix representing the transitive closure of the graph.
     */
    public static int[][] transitiveClosure(int[][] graph) {
        int V = graph.length;
        int[][] tc = new int[V][V];

        // Initialize the transitive closure matrix.  If there is an edge from i to j, then there is a path from i to j.
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (graph[i][j] != INF || i == j) { // Important: i == j means there is a path from a node to itself.
                    tc[i][j] = 1;
                } else {
                    tc[i][j] = 0;
                }
            }
        }

        // Floyd-Warshall algorithm adapted for transitive closure.  Instead of computing shortest distances, we're
        // checking for path existence.  If there is a path from i to k AND a path from k to j, then there is a path from i to j.
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    tc[i][j] = tc[i][j] | (tc[i][k] & tc[k][j]); // If there is a path i->k AND k->j, then there is a path i->j
                }
            }
        }
        return tc;
    }

    /**
     * Helper function to print a 2D matrix.
     *
     * @param matrix The matrix to print.
     */
    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                if (val == INF) {
                    System.out.print("INF\t");
                } else {
                    System.out.print(val + "\t");
                }
            }
            System.out.println();
        }
    }

    /**
     * Helper function to print a 1D array as a 2D matrix.  Useful for displaying the output of
     * floydWarshallOptimizedSpace.
     *
     * @param array The 1D array to print.
     * @param V     The number of vertices (used to determine the dimensions of the matrix).
     */
    public static void printArrayAsMatrix(int[] array, int V) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int val = array[i * V + j];
                if (val == INF) {
                    System.out.print("INF\t");
                } else {
                    System.out.print(val + "\t");
                }
            }
            System.out.println();
        }
    }
}


import java.util.Arrays;

public class FloydWarshall {

    // Define a constant for infinity, used to represent unreachable nodes.
    private static final int INF = Integer.MAX_VALUE;

    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix.
        // The graph has 4 vertices, with some edges having specific weights,
        // and others initially considered unreachable (represented by INF).
        int[][] graph = {
                {0, 5, INF, 10},
                {INF, 0, 3, INF},
                {INF, INF, 0, 1},
                {INF, INF, INF, 0}
        };

        int numVertices = graph.length;

        // 1. Basic Floyd-Warshall Algorithm
        System.out.println("1. Basic Floyd-Warshall Algorithm:");
        int[][] result1 = floydWarshallBasic(copyGraph(graph), numVertices); // Pass a copy to avoid modifying original
        printMatrix(result1, numVertices);

        // 2. Floyd-Warshall with Path Reconstruction (predecessor matrix)
        System.out.println("\n2. Floyd-Warshall with Path Reconstruction:");
        int[][] result2 = floydWarshallWithPath(copyGraph(graph), numVertices);
        printMatrix(result2, numVertices);

        // 3. Floyd-Warshall with Early Termination (no changes in iteration)
        System.out.println("\n3. Floyd-Warshall with Early Termination:");
        int[][] result3 = floydWarshallEarlyStop(copyGraph(graph), numVertices);
        printMatrix(result3, numVertices);

        // 4. Floyd-Warshall with printing intermediate matrices
        System.out.println("\n4. Floyd-Warshall with Intermediate Matrices:");
        floydWarshallIntermediate(copyGraph(graph), numVertices);

        // 5. Floyd Warshall using 3D array to store intermediate distances
        System.out.println("\n5. Floyd-Warshall with 3D array:");
        int[][][] result5 = floydWarshall3D(copyGraph(graph), numVertices);
        printMatrix(result5[numVertices-1], numVertices); // Print the final matrix

    }

    // Helper method to print the adjacency matrix in a readable format.
    public static void printMatrix(int[][] matrix, int numVertices) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][j] == INF) {
                    System.out.print("INF\t");
                } else {
                    System.out.print(matrix[i][j] + "\t");
                }
            }
            System.out.println();
        }
    }

    // Helper method to create a copy of the graph (adjacency matrix).
    public static int[][] copyGraph(int[][] graph) {
        int numVertices = graph.length;
        int[][] copy = new int[numVertices][numVertices];
        for (int i = 0; i < numVertices; i++) {
            System.arraycopy(graph[i], 0, copy[i], 0, numVertices);
        }
        return copy;
    }

    // 1. Basic Floyd-Warshall Algorithm
    // Computes the shortest path between all pairs of vertices in a graph.
    // Parameters:
    //   graph: The adjacency matrix representing the graph.
    //   numVertices: The number of vertices in the graph.
    // Returns:
    //   A new matrix representing the shortest path distances between all pairs of vertices.
    public static int[][] floydWarshallBasic(int[][] graph, int numVertices) {
        // Create a copy of the input graph to store the results.  This prevents
        // modification of the original input graph.
        int[][] dist = copyGraph(graph);

        // The core of the Floyd-Warshall algorithm.  It iterates through each
        // vertex 'k' and considers it as an intermediate node in the path
        // between every pair of vertices (i, j).
        for (int k = 0; k < numVertices; k++) {
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    // If there is a path from i to k and from k to j, check if
                    // the current distance from i to j is greater than the distance
                    // from i to k plus the distance from k to j.  If it is,
                    // update the distance from i to j.
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        // Return the matrix of shortest path distances.
        return dist;
    }

    // 2. Floyd-Warshall Algorithm with Path Reconstruction
    // This version of the algorithm not only computes the shortest path
    // distances but also reconstructs the shortest paths themselves.  It uses
    // a predecessor matrix to keep track of the intermediate nodes in the
    // shortest paths.
    // Parameters:
    //   graph: The adjacency matrix representing the graph.
    //   numVertices: The number of vertices in the graph.
    // Returns:
    //   A new matrix representing the shortest path distances between all pairs of vertices.
    public static int[][] floydWarshallWithPath(int[][] graph, int numVertices) {
        int[][] dist = copyGraph(graph);
        int[][] next = new int[numVertices][numVertices];

        // Initialize the 'next' matrix.  For each pair of vertices (i, j),
        // if there is a direct edge from i to j, then 'next[i][j]' is set to 'j',
        // indicating that the shortest path from i to j initially goes directly
        // to j.  If there is no direct edge, 'next[i][j]' is set to -1.
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (graph[i][j] != INF && i != j) {
                    next[i][j] = j;
                } else {
                    next[i][j] = -1;
                }
            }
        }

        // The main loop of the Floyd-Warshall algorithm.
        for (int k = 0; k < numVertices; k++) {
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        int newDist = dist[i][k] + dist[k][j];
                        if (dist[i][j] > newDist) {
                            dist[i][j] = newDist;
                            next[i][j] = next[i][k]; // Update the 'next' matrix.
                        }
                    }
                }
            }
        }

        // Print the shortest paths.
        System.out.println("Shortest Paths:");
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i != j) {
                    System.out.print("Path from " + i + " to " + j + ": ");
                    if (dist[i][j] == INF) {
                        System.out.println("No path");
                    } else {
                        printPath(i, j, next);
                        System.out.println();
                    }
                }
            }
        }
        return dist;
    }

    // Helper method to print the shortest path between two vertices, using the
    // 'next' matrix.  This method recursively reconstructs the path.
    // Parameters:
    //   i: The starting vertex.
    //   j: The ending vertex.
    //   next: The 'next' matrix, which stores the intermediate nodes in the shortest paths.
    public static void printPath(int i, int j, int[][] next) {
        if (next[i][j] == -1) {
            System.out.print("No path");
            return;
        }
        System.out.print(i + " ");
        while (i != j) {
            i = next[i][j];
            System.out.print(i + " ");
        }
    }

    // 3. Floyd-Warshall Algorithm with Early Termination
    // This version of the algorithm includes an optimization to terminate early
    // if no changes occur in an iteration.  If no distances are updated in an
    // iteration, it means that the algorithm has converged, and there is no
    // need to continue iterating.
    // Parameters:
    //   graph: The adjacency matrix representing the graph.
    //   numVertices: The number of vertices in the graph.
    // Returns:
    //   A new matrix representing the shortest path distances between all pairs of vertices.
    public static int[][] floydWarshallEarlyStop(int[][] graph, int numVertices) {
        int[][] dist = copyGraph(graph);
        boolean changed;

        for (int k = 0; k < numVertices; k++) {
            changed = false; // Initialize 'changed' to false for each iteration.
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        int newDist = dist[i][k] + dist[k][j];
                        if (dist[i][j] > newDist) {
                            dist[i][j] = newDist;
                            changed = true; // Set 'changed' to true if a change occurs.
                        }
                    }
                }
            }
            if (!changed) {
                break; // If no changes occurred in this iteration, break the loop.
            }
        }
        return dist;
    }

    // 4. Floyd-Warshall Algorithm with Printing Intermediate Matrices
    // This version of the algorithm prints the distance matrix at each
    // iteration of the outermost loop (i.e., after considering each
    // intermediate node k).  This can be useful for visualizing the
    // execution of the algorithm and understanding how the distances
    // are updated step by step.
    // Parameters:
    //   graph: The adjacency matrix representing the graph.
    //   numVertices: The number of vertices in the graph.
    public static void floydWarshallIntermediate(int[][] graph, int numVertices) {
        int[][] dist = copyGraph(graph);

        for (int k = 0; k < numVertices; k++) {
            System.out.println("Intermediate Matrix for k = " + k + ":");
            printMatrix(dist, numVertices); // Print the matrix at each iteration.
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }

    // 5. Floyd-Warshall using 3D array to store intermediate distances
    // This approach uses a 3D array to store the distance matrices at each
    // iteration.  The 3rd dimension of the array represents the
    // intermediate node 'k'.  This can provide a more structured way to
    // store the intermediate results, but it also uses more memory.
    // Parameters:
    //   graph: The adjacency matrix representing the graph.
    //   numVertices: The number of vertices in the graph.
    // Returns:
    //   A 3D array where the element at [k][i][j] represents the shortest
    //   distance from vertex i to vertex j using intermediate vertices up to k.
    public static int[][][] floydWarshall3D(int[][] graph, int numVertices) {
        int[][][] dist = new int[numVertices][numVertices][numVertices];

        // Initialize the first layer (k = 0) of the 3D array with the original graph.
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                dist[0][i][j] = graph[i][j];
            }
        }

        // Iterate through each intermediate node k.
        for (int k = 1; k < numVertices; k++) {
            // For each pair of vertices i and j, calculate the shortest distance
            // using intermediate nodes up to k.
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    // The distance from i to j using intermediate nodes up to k
                    // is the minimum of:
                    // 1. The distance from i to j using intermediate nodes up to k-1.
                    // 2. The distance from i to k plus the distance from k to j,
                    //    both using intermediate nodes up to k-1.
                    dist[k][i][j] = Math.min(dist[k - 1][i][j],
                            (dist[k - 1][i][k] == INF || dist[k - 1][k][j] == INF) ? INF : dist[k - 1][i][k] + dist[k - 1][k][j]);
                }
            }
        }
        return dist;
    }
}


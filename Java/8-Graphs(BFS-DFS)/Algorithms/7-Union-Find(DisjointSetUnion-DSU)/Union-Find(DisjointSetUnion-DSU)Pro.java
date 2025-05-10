import java.util.*;
import java.io.*;

public class GraphAlgorithms {

    // =================================================================================================
    // 1. Breadth-First Search (BFS) - Level Order Traversal
    //    - Application: Finding the shortest path in an unweighted graph (e.g., social network connections).
    // =================================================================================================

    /**
     * Performs Breadth-First Search (BFS) on a graph represented as an adjacency list.
     *
     * @param graph An adjacency list representing the graph.  The keys are node IDs,
     * and the values are lists of neighboring node IDs.
     * @param startNode The ID of the node to start the BFS from.
     * @return A list of node IDs in the order they were visited by BFS.  Returns an empty
     * list if the graph is empty or the startNode is not found.
     */
    public static List<Integer> breadthFirstSearch(Map<Integer, List<Integer>> graph, int startNode) {
        List<Integer> visitedOrder = new ArrayList<>();
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            return visitedOrder; // Handle empty graph or invalid start node.
        }

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.offer(startNode); // Add the start node to the queue.
        visited.add(startNode); // Mark the start node as visited.

        while (!queue.isEmpty()) {
            int currentNode = queue.poll(); // Get the next node from the queue.
            visitedOrder.add(currentNode);    // Add it to the visited order.

            // Get the neighbors of the current node.  If the node doesn't exist
            // in the graph, we'll get an empty list, which is fine.
            List<Integer> neighbors = graph.getOrDefault(currentNode, new ArrayList<>());
            for (int neighbor : neighbors) {
                if (!visited.contains(neighbor)) {
                    queue.offer(neighbor);     // Add unvisited neighbors to the queue.
                    visited.add(neighbor); // Mark the neighbor as visited.
                }
            }
        }
        return visitedOrder;
    }

    // Example Usage (BFS for Social Network Connections):
    public static void useBFSForSocialNetwork() {
        // Represent a social network graph as an adjacency list:
        // User IDs are nodes, and friendships are edges.
        Map<Integer, List<Integer>> socialNetwork = new HashMap<>();
        socialNetwork.put(1, Arrays.asList(2, 3, 4));
        socialNetwork.put(2, Arrays.asList(1, 5));
        socialNetwork.put(3, Arrays.asList(1, 6, 7));
        socialNetwork.put(4, Arrays.asList(1, 8));
        socialNetwork.put(5, Arrays.asList(2));
        socialNetwork.put(6, Arrays.asList(3));
        socialNetwork.put(7, Arrays.asList(3));
        socialNetwork.put(8, Arrays.asList(4));

        int startUser = 1;
        List<Integer> connections = breadthFirstSearch(socialNetwork, startUser);
        System.out.println("BFS Traversal (Social Network - User " + startUser + "): " + connections);
        // Expected output (or similar): [1, 2, 3, 4, 5, 6, 7, 8] -  the order might vary slightly
    }


    // =================================================================================================
    // 2. Depth-First Search (DFS) - Preorder Traversal
    //    - Application: Topological sorting (e.g., task scheduling, dependency resolution).
    // =================================================================================================

    /**
     * Performs Depth-First Search (DFS) on a graph represented as an adjacency list
     * using recursion.  This version does a *preorder* traversal.
     *
     * @param graph     An adjacency list representing the graph.
     * @param startNode The ID of the node to start the DFS from.
     * @param visited   A set to keep track of visited nodes during the traversal.
     * @param result    A list to store the nodes in the order they are visited.
     */
    public static void depthFirstSearchRecursive(Map<Integer, List<Integer>> graph, int startNode, Set<Integer> visited, List<Integer> result) {
        if (graph == null || !graph.containsKey(startNode)) {
            return; // Handle null graph or node not in graph
        }

        visited.add(startNode);    // Mark the current node as visited.
        result.add(startNode);     // Add the current node to the result list (preorder).

        List<Integer> neighbors = graph.getOrDefault(startNode, new ArrayList<>()); //handle missing nodes
        for (int neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                depthFirstSearchRecursive(graph, neighbor, visited, result); // Recurse on unvisited neighbors.
            }
        }
    }

    /**
     * Helper method to initiate the recursive DFS traversal.
     *
     * @param graph     The adjacency list representing the graph.
     * @param startNode The starting node for DFS.
     * @return A list of nodes visited in DFS order.
     */
    public static List<Integer> depthFirstSearch(Map<Integer, List<Integer>> graph, int startNode) {
        Set<Integer> visited = new HashSet<>();
        List<Integer> result = new ArrayList<>();
        depthFirstSearchRecursive(graph, startNode, visited, result);
        return result;
    }

    // Example Usage (DFS for Task Scheduling - Topological Sort):
    public static void useDFSForTaskScheduling() {
        // Represent task dependencies as an adjacency list:
        // Task IDs are nodes, and dependencies (prerequisites) are edges.
        // For example, task 2 depends on task 1 (1 -> 2).
        Map<Integer, List<Integer>> taskDependencies = new HashMap<>();
        taskDependencies.put(1, Arrays.asList(2, 3));
        taskDependencies.put(2, Arrays.asList(4));
        taskDependencies.put(3, Arrays.asList(4, 5));
        taskDependencies.put(4, Collections.emptyList()); // Task 4 has no dependencies.
        taskDependencies.put(5, Collections.emptyList()); // Task 5 has no dependencies.
        // A valid task schedule is a topological sort of this graph.

        int startTask = 1; // You could start DFS from any node in a connected component
        List<Integer> taskOrder = depthFirstSearch(taskDependencies, startTask);
        System.out.println("DFS Traversal (Task Schedule - Starting from task 1): " + taskOrder);
        //  Output: [1, 2, 4, 3, 5]  (or another valid topological order)
    }


    // =================================================================================================
    // 3. Depth-First Search (DFS) - Iterative Approach
    //    - Application: File system traversal (directories and files).
    // =================================================================================================
    /**
     * Performs Depth-First Search (DFS) on a graph represented as an adjacency list
     * using an iterative approach with a stack.
     *
     * @param graph     An adjacency list representing the graph.
     * @param startNode The ID of the node to start the DFS from.
     * @return A list of node IDs in the order they were visited by DFS.
     */
    public static List<Integer> depthFirstSearchIterative(Map<Integer, List<Integer>> graph, int startNode) {
        List<Integer> visitedOrder = new ArrayList<>();
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            return visitedOrder; // Handle empty graph or invalid start node.
        }

        Stack<Integer> stack = new Stack<>();
        Set<Integer> visited = new HashSet<>();

        stack.push(startNode);    // Push the start node onto the stack.
        visited.add(startNode); // Mark the start node as visited.

        while (!stack.isEmpty()) {
            int currentNode = stack.pop(); // Get the top node from the stack.
            visitedOrder.add(currentNode);    // Add it to the visited order.

            List<Integer> neighbors = graph.getOrDefault(currentNode, new ArrayList<>());
            // Iterate through neighbors in *reverse* order to maintain a similar
            // traversal order to the recursive version.
            for (int i = neighbors.size() - 1; i >= 0; i--) {
                int neighbor = neighbors.get(i);
                if (!visited.contains(neighbor)) {
                    stack.push(neighbor);     // Push unvisited neighbors onto the stack.
                    visited.add(neighbor); // Mark the neighbor as visited.
                }
            }
        }
        return visitedOrder;
    }

    // Example Usage (DFS for File System Traversal):
    public static void useDFSIterativeForFileSystem() {
        // Represent a file system as a graph:
        //  -  Directories and files are nodes.
        //  -  Edges represent the "contains" relationship (directory contains file/subdirectory).
        //  -  For simplicity, let's use integers as unique IDs for files and directories.
        Map<Integer, List<Integer>> fileSystemGraph = new HashMap<>();
        fileSystemGraph.put(1, Arrays.asList(2, 3, 4)); // Directory 1 contains file 2, file 3, and directory 4
        fileSystemGraph.put(2, Collections.emptyList());       // File 2
        fileSystemGraph.put(3, Collections.emptyList());       // File 3
        fileSystemGraph.put(4, Arrays.asList(5, 6));    // Directory 4 contains file 5 and file 6
        fileSystemGraph.put(5, Collections.emptyList());       // File 5
        fileSystemGraph.put(6, Collections.emptyList());       // File 6

        int startDirectory = 1; // Start traversal from the root directory
        List<Integer> traversalOrder = depthFirstSearchIterative(fileSystemGraph, startDirectory);
        System.out.println("DFS Iterative (File System Traversal - Starting from directory 1): " + traversalOrder);
        // Expected output (or similar): [1, 4, 6, 5, 3, 2]
    }


    // =================================================================================================
    // 4. Union-Find (Disjoint Set Union) - Path Compression and Rank
    //    - Application: Network connectivity (determining if two computers are in the same network).
    // =================================================================================================

    /**
     * Implements the Union-Find (Disjoint Set Union) data structure with path compression
     * and union by rank.  This is used to efficiently determine if two elements
     * are in the same set.
     */
    public static class UnionFind {
        private int[] parent; // parent[i] stores the parent of element i
        private int[] rank;   // rank[i] stores the rank (approximate height) of the tree rooted at i
        private int count;    // Number of disjoint sets

        /**
         * Constructor for the UnionFind data structure.
         *
         * @param n The number of elements in the universe (e.g., number of computers in a network).
         * Elements are assumed to be numbered from 0 to n-1.
         */
        public UnionFind(int n) {
            this.count = n;
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i; // Initially, each element is its own parent (singleton set).
                rank[i] = 0;    // Initially, the rank of each element is 0.
            }
        }

        /**
         * Finds the root (representative) of the set that element 'x' belongs to, using path compression.
         *
         * @param x The element to find the root of.
         * @return The root of the set containing 'x'.
         */
        public int find(int x) {
            if (parent[x] != x) {
                // Path compression:  Set the parent of x to the root of its set, making
                // future find operations faster.
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        /**
         * Merges the sets containing elements 'x' and 'y' (union by rank).
         *
         * @param x The first element.
         * @param y The second element.
         * @return true if the sets were merged, false if they were already in the same set.
         */
        public boolean union(int x, int y) {
            int rootX = find(x); // Find the root of the set containing x.
            int rootY = find(y); // Find the root of the set containing y.

            if (rootX == rootY) {
                return false; // x and y are already in the same set.
            }

            // Union by rank:  Attach the smaller rank tree under the root of the larger rank tree.
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY; // Make rootY the parent of rootX.
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX; // Make rootX the parent of rootY.
            } else {
                // If the ranks are equal, choose either root to be the parent and increment its rank.
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            count--;
            return true;
        }

        /**
         * Checks if two elements are in the same set.
         * @param x The first element.
         * @param y The second element.
         * @return True if x and y are in the same set, false otherwise.
         */
        public boolean isConnected(int x, int y) {
            return find(x) == find(y);
        }

        /**
         * Returns the number of disjoint sets.
         * @return The number of disjoint sets.
         */
        public int countSets() {
            return count;
        }
    }

    // Example Usage (Union-Find for Network Connectivity):
    public static void useUnionFindForNetworkConnectivity() {
        int numComputers = 10; // 10 computers in the network, numbered 0 to 9.
        UnionFind network = new UnionFind(numComputers);

        // Simulate network connections:
        // Connect computer 1 to 2, 3 to 4, and 5 to 6.
        network.union(1, 2);
        network.union(3, 4);
        network.union(5, 6);

        System.out.println("Initial Network Connectivity:");
        for (int i = 0; i < numComputers; i++) {
            System.out.println("Computer " + i + " is connected to: " + network.find(i));
        }
        // Check if computers 1 and 2 are connected (they should be).
        System.out.println("Are computers 1 and 2 connected? " + network.isConnected(1, 2)); // true
        System.out.println("Are computers 1 and 3 connected? " + network.isConnected(1, 3)); // false

        // Connect computers 2 and 3.  This merges the sets {1, 2} and {3, 4}.
        network.union(2, 3);
        System.out.println("\nAfter connecting computers 2 and 3:");
        System.out.println("Are computers 1 and 3 connected? " + network.isConnected(1, 3)); // true now
        System.out.println("Number of connected components: " + network.countSets()); //2: {0}, {1,2,3,4}, {5,6}, {7}, {8}, {9}
    }



    // =================================================================================================
    // 5. Union-Find for Image Processing (Connected Components)
    //    - Application: Image segmentation, identifying regions of connected pixels.
    // =================================================================================================

    /**
     * Finds connected components in a binary image represented as a 2D array, using Union-Find.
     *
     * @param image A 2D array of integers representing the image.  1 represents a pixel that is
     * part of an object, and 0 represents background.
     * @return The number of connected components in the image.
     */
    public static int findConnectedComponents(int[][] image) {
        if (image == null || image.length == 0 || image[0].length == 0) {
            return 0; // Handle null or empty image.
        }

        int rows = image.length;
        int cols = image[0].length;
        UnionFind uf = new UnionFind(rows * cols); // Each pixel is a node in the Union-Find structure.

        // Iterate through the image, and for each '1' pixel, connect it to its neighbors.
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (image[r][c] == 1) {
                    int currentPixel = r * cols + c; // Convert 2D coordinates to 1D index.

                    // Check neighbors (up, down, left, right) and merge them if they are also '1' pixels.
                    // We only check down and right to avoid processing the same edge twice.
                    if (r + 1 < rows && image[r + 1][c] == 1) {
                        int bottomPixel = (r + 1) * cols + c;
                        uf.union(currentPixel, bottomPixel);
                    }
                    if (c + 1 < cols && image[r][c + 1] == 1) {
                        int rightPixel = r * cols + (c + 1);
                        uf.union(currentPixel, rightPixel);
                    }
                }
            }
        }

        return uf.countSets(); // The number of disjoint sets is the number of connected components.
    }

    // Example Usage (Union-Find for Image Processing):
    public static void useUnionFindForImageProcessing() {
        // Example binary image:
        // 1 represents an object pixel, 0 represents background.
        int[][] binaryImage = {
                {0, 0, 1, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 1, 1},
                {0, 0, 0, 1, 0}
        };

        int numComponents = findConnectedComponents(binaryImage);
        System.out.println("Number of connected components in the image: " + numComponents); // Output: 2
    }



    public static void main(String[] args) {
        // Run the example usage methods:
        System.out.println("--- BFS Example (Social Network) ---");
        useBFSForSocialNetwork();

        System.out.println("\n--- DFS Example (Task Scheduling) ---");
        useDFSForTaskScheduling();

        System.out.println("\n--- DFS Iterative Example (File System Traversal) ---");
        useDFSIterativeForFileSystem();

        System.out.println("\n--- Union-Find Example (Network Connectivity) ---");
        useUnionFindForNetworkConnectivity();

        System.out.println("\n--- Union-Find Example (Image Processing) ---");
        useUnionFindForImageProcessing();
    }
}


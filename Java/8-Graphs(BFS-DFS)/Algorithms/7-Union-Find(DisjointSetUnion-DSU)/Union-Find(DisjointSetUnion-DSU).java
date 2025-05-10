import java.util.*;

public class GraphAndUnionFind {

    // ========================================================================
    // 1. Breadth-First Search (BFS) - Graph Traversal
    // ========================================================================
    /**
     * Performs Breadth-First Search (BFS) on a graph represented as an adjacency list.
     *
     * @param graph The adjacency list representing the graph.  Each key is a node,
     * and the value is a list of its neighbors.
     * @param startNode The node to start the BFS from.
     * @return A list of nodes visited in BFS order.  Returns an empty list if the
     * graph is empty or the startNode is not in the graph.
     */
    public static List<Integer> bfs(Map<Integer, List<Integer>> graph, int startNode) {
        List<Integer> visited = new ArrayList<>();
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            return visited; // Handle null or empty graph, or invalid start node.
        }

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> discovered = new HashSet<>(); // Keep track of discovered nodes

        queue.offer(startNode);
        discovered.add(startNode);

        while (!queue.isEmpty()) {
            int currentNode = queue.poll();
            visited.add(currentNode);

            List<Integer> neighbors = graph.get(currentNode);
            if (neighbors != null) { // Handle cases where a node has no neighbors.
                for (int neighbor : neighbors) {
                    if (!discovered.contains(neighbor)) {
                        queue.offer(neighbor);
                        discovered.add(neighbor);
                    }
                }
            }
        }
        return visited;
    }

    // ========================================================================
    // 2. Depth-First Search (DFS) - Graph Traversal (Iterative)
    // ========================================================================
    /**
     * Performs Depth-First Search (DFS) on a graph using an iterative approach
     * with a stack.
     *
     * @param graph The adjacency list representing the graph.
     * @param startNode The node to start the DFS from.
     * @return A list of nodes visited in DFS order.  Returns an empty list if
     * the graph is empty or the startNode is not in the graph.
     */
    public static List<Integer> dfsIterative(Map<Integer, List<Integer>> graph, int startNode) {
        List<Integer> visited = new ArrayList<>();
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            return visited;
        }

        Stack<Integer> stack = new Stack<>();
        Set<Integer> discovered = new HashSet<>();

        stack.push(startNode);
        discovered.add(startNode);

        while (!stack.isEmpty()) {
            int currentNode = stack.pop();
            visited.add(currentNode);

            List<Integer> neighbors = graph.get(currentNode);
            if (neighbors != null) {
                for (int neighbor : neighbors) {
                    if (!discovered.contains(neighbor)) {
                        stack.push(neighbor);
                        discovered.add(neighbor);
                    }
                }
            }
        }
        return visited;
    }

    // ========================================================================
    // 3. Depth-First Search (DFS) - Graph Traversal (Recursive)
    // ========================================================================

    /**
     * Performs Depth-First Search (DFS) on a graph using a recursive approach.
     *
     * @param graph     The adjacency list representing the graph.
     * @param startNode The node to start the DFS from.
     * @param visited   A set to keep track of visited nodes during the recursion.
     * This is necessary for the recursive implementation.
     * @param result    The list to store the visited nodes in DFS order.
     */
    private static void dfsRecursiveHelper(Map<Integer, List<Integer>> graph, int startNode, Set<Integer> visited, List<Integer> result) {
        visited.add(startNode);
        result.add(startNode);

        List<Integer> neighbors = graph.get(startNode);
        if (neighbors != null) {
            for (int neighbor : neighbors) {
                if (!visited.contains(neighbor)) {
                    dfsRecursiveHelper(graph, neighbor, visited, result);
                }
            }
        }
    }

    /**
     * Wrapper function to start the recursive DFS.  Handles the initial setup
     * and error conditions.
     *
     * @param graph The adjacency list representing the graph.
     * @param startNode The node to start the DFS from.
     * @return A list of nodes visited in DFS order. Returns an empty list if the
     * graph is empty or the startNode is not in the graph.
     */
    public static List<Integer> dfsRecursive(Map<Integer, List<Integer>> graph, int startNode) {
        List<Integer> result = new ArrayList<>();
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            return result;
        }
        Set<Integer> visited = new HashSet<>();
        dfsRecursiveHelper(graph, startNode, visited, result);
        return result;
    }


    // ========================================================================
    // 4. Union-Find (Disjoint Set Union) - Path Compression
    // ========================================================================
    /**
     * Implements the Union-Find (Disjoint Set Union) data structure with path compression.
     * This version uses an array to represent the parent of each element.
     */
    public static class UnionFind {
        private int[] parent;
        private int[] rank; // Added for improved union operation (union by rank)
        private int count; // Number of connected components

        /**
         * Constructor for the UnionFind class.
         *
         * @param n The number of elements in the set.
         */
        public UnionFind(int n) {
            parent = new int[n];
            rank = new int[n]; // Initialize rank array
            count = n;
            for (int i = 0; i < n; i++) {
                parent[i] = i; // Each element is initially its own parent.
                rank[i] = 0;  // Rank of each element is initially 0
            }
        }

        /**
         * Finds the root (representative) of the set that an element belongs to, using path compression.
         *
         * @param x The element to find the root of.
         * @return The root of the set that x belongs to.
         */
        public int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]); // Path compression: directly attach x to its root.
            }
            return parent[x];
        }

        /**
         * Merges the sets that elements x and y belong to.  Uses union by rank
         * to keep the tree as flat as possible.
         *
         * @param x The first element.
         * @param y The second element.
         */
        public void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY; // Attach the smaller rank tree to the larger rank tree
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else {
                    parent[rootY] = rootX; // If ranks are equal, attach either way
                    rank[rootX]++;       // and increment the rank of the new root
                }
                count--; // Decrement connected component count
            }
        }

        /**
         * Checks if two elements are in the same set.
         *
         * @param x The first element.
         * @param y The second element.
         * @return True if x and y are in the same set, false otherwise.
         */
        public boolean isConnected(int x, int y) {
            return find(x) == find(y);
        }

        /**
         * Returns the number of connected components.
         * @return The number of connected components.
         */
        public int getCount() {
            return count;
        }
    }

    // ========================================================================
    // 5.  Union-Find Application:  Checking for Graph Cycle
    // ========================================================================

    /**
     * Detects if a graph contains a cycle using the Union-Find algorithm.  The graph
     * is represented as a list of edges, where each edge is a pair of node IDs.
     *
     * @param numNodes The number of nodes in the graph.
     * @param edges    A list of edges, where each edge is an array of two integers
     * representing the nodes connected by the edge.
     * @return True if the graph contains a cycle, false otherwise.
     */
    public static boolean hasCycle(int numNodes, int[][] edges) {
        UnionFind uf = new UnionFind(numNodes);

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            if (uf.isConnected(u, v)) {
                return true; // Found a cycle:  u and v were already connected.
            }
            uf.union(u, v); // Merge the sets containing u and v.
        }
        return false; // No cycles detected.
    }

    public static void main(String[] args) {
        // Example Graph for BFS and DFS
        Map<Integer, List<Integer>> graph = new HashMap<>();
        graph.put(0, Arrays.asList(1, 2));
        graph.put(1, Arrays.asList(0, 3, 4));
        graph.put(2, Arrays.asList(0, 4));
        graph.put(3, Arrays.asList(1));
        graph.put(4, Arrays.asList(1, 2));

        System.out.println("BFS Traversal (starting from node 0): " + bfs(graph, 0));
        System.out.println("DFS Traversal (Iterative, starting from node 0): " + dfsIterative(graph, 0));
        System.out.println("DFS Traversal (Recursive, starting from node 0): " + dfsRecursive(graph, 0));

        // Example for Union-Find
        UnionFind uf = new UnionFind(5); // 5 elements: 0, 1, 2, 3, 4
        uf.union(0, 1);
        uf.union(2, 3);
        System.out.println("Are 0 and 1 connected? " + uf.isConnected(0, 1)); // true
        System.out.println("Are 0 and 2 connected? " + uf.isConnected(0, 2)); // false
        System.out.println("Number of connected components: " + uf.getCount()); //2

        // Example graph with a cycle
        int numNodes = 4;
        int[][] edgesWithCycle = {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 0} // This edge creates a cycle
        };
        System.out.println("Graph with cycle has cycle: " + hasCycle(numNodes, edgesWithCycle)); // true

        // Example graph without a cycle
        int[][] edgesWithoutCycle = {
                {0, 1},
                {1, 2},
                {2, 3}
        };
        System.out.println("Graph without cycle has cycle: " + hasCycle(numNodes, edgesWithoutCycle)); // false
    }
}


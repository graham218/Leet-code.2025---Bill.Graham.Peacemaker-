import java.util.*;

public class TopologicalSort {

    /**
     * Approach 1: Basic Kahn's Algorithm (using a queue and indegree array)
     *
     * Core implementation of Kahn's algorithm.  Calculates indegrees,
     * adds nodes with no incoming edges to a queue, and iteratively removes
     * nodes, updating indegrees of neighbors.  Suitable for simple topological
     * sorting problems.
     */
    public static List<Integer> topologicalSortBasic(int numNodes, int[][] edges) {
        // 1. Calculate indegrees for each node.
        int[] indegree = new int[numNodes];
        for (int[] edge : edges) {
            indegree[edge[1]]++; // edge: [source, dest], increment dest's indegree
        }

        // 2. Create a queue and add nodes with indegree 0.
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }

        // 3. Process nodes from the queue.
        List<Integer> sortedOrder = new ArrayList<>();
        while (!queue.isEmpty()) {
            int node = queue.poll();
            sortedOrder.add(node);

            // 4. Update indegrees of neighbors and add them to the queue if their indegree becomes 0.
            for (int[] edge : edges) {
                if (edge[0] == node) { // If the current node is the source of an edge
                    int neighbor = edge[1];
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        queue.offer(neighbor);
                    }
                }
            }
        }

        // 5. Check for cycles: If not all nodes were processed, there is a cycle.
        if (sortedOrder.size() != numNodes) {
            return new ArrayList<>(); // Return empty list to indicate a cycle.
        }

        return sortedOrder;
    }

    /**
     * Approach 2: Kahn's Algorithm with Adjacency List
     *
     * Uses an adjacency list to represent the graph, which is more efficient
     * for sparse graphs.  Improves neighbor lookup performance compared to
     * iterating through all edges.  Recommended for larger graphs.
     */
    public static List<Integer> topologicalSortAdjacencyList(int numNodes, int[][] edges) {
        // 1. Build the adjacency list.
        List<List<Integer>> adjList = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adjList.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            adjList.get(edge[0]).add(edge[1]); // edge: [source, dest], add dest to source's list
        }

        // 2. Calculate indegrees.
        int[] indegree = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            for (int neighbor : adjList.get(i)) {
                indegree[neighbor]++;
            }
        }

        // 3. Create a queue and add nodes with indegree 0.
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }

        // 4. Process nodes from the queue.
        List<Integer> sortedOrder = new ArrayList<>();
        while (!queue.isEmpty()) {
            int node = queue.poll();
            sortedOrder.add(node);

            // 5. Update indegrees of neighbors using the adjacency list.
            for (int neighbor : adjList.get(node)) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        // 6. Check for cycles.
        if (sortedOrder.size() != numNodes) {
            return new ArrayList<>();
        }
        return sortedOrder;
    }

    /**
     * Approach 3: Kahn's Algorithm with Priority Queue (for lexicographical order)
     *
     * Uses a priority queue instead of a regular queue to obtain a specific
     * topological order (e.g., lexicographically smallest).  Useful when
     * the order of processing nodes with the same indegree matters.
     */
    public static List<Integer> topologicalSortPriorityQueue(int numNodes, int[][] edges) {
        // 1. Build adjacency list.
        List<List<Integer>> adjList = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adjList.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            adjList.get(edge[0]).add(edge[1]);
        }

        // 2. Calculate indegrees.
        int[] indegree = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            for (int neighbor : adjList.get(i)) {
                indegree[neighbor]++;
            }
        }

        // 3. Create a priority queue (min-heap for smallest node first).
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                pq.offer(i);
            }
        }

        // 4. Process nodes from the priority queue.
        List<Integer> sortedOrder = new ArrayList<>();
        while (!pq.isEmpty()) {
            int node = pq.poll();
            sortedOrder.add(node);

            // 5. Update indegrees of neighbors.
            for (int neighbor : adjList.get(node)) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    pq.offer(neighbor);
                }
            }
        }

        // 6. Check for cycles.
        if (sortedOrder.size() != numNodes) {
            return new ArrayList<>();
        }
        return sortedOrder;
    }

    /**
     * Approach 4: Kahn's Algorithm with Indegree Tracking and Cycle Detection
     *
     * Explicitly tracks the number of visited nodes to provide more robust
     * cycle detection.  Returns null if a cycle is detected, making it
     * suitable for applications where cycle detection is critical.
     */
    public static List<Integer> topologicalSortWithCycleDetection(int numNodes, int[][] edges) {
        // 1. Build adjacency list
        List<List<Integer>> adjList = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adjList.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            adjList.get(edge[0]).add(edge[1]);
        }

        // 2. Calculate indegrees
        int[] indegree = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            for (int neighbor : adjList.get(i)) {
                indegree[neighbor]++;
            }
        }

        // 3. Create queue and add nodes with indegree 0
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }

        // 4. Process nodes from the queue
        List<Integer> sortedOrder = new ArrayList<>();
        int visitedCount = 0; // Keep track of visited nodes.
        while (!queue.isEmpty()) {
            int node = queue.poll();
            sortedOrder.add(node);
            visitedCount++;

            // 5. Update indegrees of neighbors
            for (int neighbor : adjList.get(node)) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        // 6. Check for cycles:  Crucially, check if all nodes were visited.
        if (visitedCount != numNodes) {
            return null; // Return null to explicitly indicate a cycle.
        }
        return sortedOrder;
    }

    /**
     * Approach 5: Kahn's Algorithm with Layered Approach
     *
     * This approach not only finds a topological order but also groups the nodes
     * into layers, where each layer represents a level of dependency.  Nodes in
     * layer i depend only on nodes in layers 0 to i-1.  Useful for build systems
     * or task scheduling where you need to know the execution order of tasks in stages.
     */
    public static List<List<Integer>> topologicalSortLayered(int numNodes, int[][] edges) {
        // 1. Build the adjacency list.
        List<List<Integer>> adjList = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adjList.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            adjList.get(edge[0]).add(edge[1]);
        }

        // 2. Calculate indegrees.
        int[] indegree = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            for (int neighbor : adjList.get(i)) {
                indegree[neighbor]++;
            }
        }

        // 3. Initialize queue and layers.
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }
        List<List<Integer>> layers = new ArrayList<>();

        // 4. Process nodes layer by layer.
        while (!queue.isEmpty()) {
            int layerSize = queue.size();
            List<Integer> currentLayer = new ArrayList<>();
            for (int i = 0; i < layerSize; i++) {
                int node = queue.poll();
                currentLayer.add(node);

                // Update indegrees and add neighbors to the queue.
                for (int neighbor : adjList.get(node)) {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        queue.offer(neighbor);
                    }
                }
            }
            layers.add(currentLayer);
        }
        // 5. Check for cycles.  If the total number of nodes in all layers
        //    is not equal to numNodes, then a cycle exists.
        int totalNodes = 0;
        for (List<Integer> layer : layers) {
            totalNodes += layer.size();
        }
        if (totalNodes != numNodes) {
            return new ArrayList<>(); // Return an empty list of layers to indicate a cycle
        }
        return layers;
    }

    public static void main(String[] args) {
        // Example graph represented as an array of edges.
        //  0 -> 1,  0 -> 2,  1 -> 3,  2 -> 3,  3 -> 4
        int[][] edges = { { 0, 1 }, { 0, 2 }, { 1, 3 }, { 2, 3 }, { 3, 4 } };
        int numNodes = 5;

        System.out.println("Topological Sort - Basic: " + topologicalSortBasic(numNodes, edges));
        System.out.println("Topological Sort - Adjacency List: " + topologicalSortAdjacencyList(numNodes, edges));
        System.out.println("Topological Sort - Priority Queue: " + topologicalSortPriorityQueue(numNodes, edges));
        System.out.println("Topological Sort - Cycle Detection: " + topologicalSortWithCycleDetection(numNodes, edges));

        List<List<Integer>> layeredResult = topologicalSortLayered(numNodes, edges);
        System.out.println("Topological Sort - Layered:");
        if (layeredResult != null && !layeredResult.isEmpty()) {
            for (int i = 0; i < layeredResult.size(); i++) {
                System.out.println("Layer " + i + ": " + layeredResult.get(i));
            }
        } else {
            System.out.println("Cycle detected, no topological order.");
        }

        // Example with a cycle (for testing cycle detection)
        int[][] cyclicEdges = { { 0, 1 }, { 1, 2 }, { 2, 0 } };
        int numCyclicNodes = 3;
        System.out.println("\nTopological Sort - Cycle Example (Basic): " + topologicalSortBasic(numCyclicNodes, cyclicEdges));
        System.out.println("Topological Sort - Cycle Example (Adjacency List): " + topologicalSortAdjacencyList(numCyclicNodes, cyclicEdges));
        System.out.println("Topological Sort - Cycle Example (Priority Queue): " + topologicalSortPriorityQueue(numCyclicNodes, cyclicEdges));
        System.out.println("Topological Sort - Cycle Example (Cycle Detection): " + topologicalSortWithCycleDetection(numCyclicNodes, cyclicEdges));

        List<List<Integer>> cyclicLayeredResult = topologicalSortLayered(numCyclicNodes, cyclicEdges);
        System.out.println("Topological Sort - Cycle Example (Layered):");
        if (cyclicLayeredResult != null && !cyclicLayeredResult.isEmpty()) {
            for (int i = 0; i < cyclicLayeredResult.size(); i++) {
                System.out.println("Layer " + i + ": " + cyclicLayeredResult.get(i));
            }
        }
        else
        {
            System.out.println("Cycle Detected");
        }
    }
}


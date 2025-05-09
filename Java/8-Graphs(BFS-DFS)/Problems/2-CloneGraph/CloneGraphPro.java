import java.util.*;

public class CloneGraph {

    /**
     * Approach 1: BFS with HashMap (Iterative)
     * - Uses Breadth-First Search to traverse the graph.
     * - A HashMap is used to store the mapping between original nodes and their clones.
     * - This approach is efficient for large graphs and avoids recursion issues.
     *
     * Implementation Details:
     * 1. Check for null input.  If the input graph is null, return null.
     * 2. Create a HashMap `map` to store the mapping of original nodes to their clones: `Map<OriginalNode, ClonedNode>`.
     * 3. Create a queue `queue` to hold nodes to be visited.
     * 4. Clone the starting node and put it in the map.
     * 5. Add the starting node to the queue.
     * 6. While the queue is not empty:
     * - Dequeue a node from the queue (current node).
     * - Iterate through the neighbors of the current node.
     * - If a neighbor has not been cloned:
     * - Clone the neighbor and put it in the map.
     * - Enqueue the neighbor.
     * - Add the clone of the neighbor to the neighbors list of the cloned current node.
     * 7. Return the clone of the starting node.
     *
     * Example Use Case:
     * - Cloning a social network graph to create a sandbox environment for testing new features.
     *
     * @param node The node to start cloning from.
     * @return The cloned graph's starting node.
     */
    public Node cloneGraphBFS(Node node) {
        if (node == null) {
            return null;
        }

        Map<Node, Node> map = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();

        // Clone the starting node.
        Node clonedStart = new Node(node.val);
        map.put(node, clonedStart);
        queue.offer(node);

        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            Node clonedCurr = map.get(curr); // Get the cloned version of the current node.

            for (Node neighbor : curr.neighbors) {
                if (!map.containsKey(neighbor)) {
                    // Clone the neighbor if it hasn't been cloned.
                    Node clonedNeighbor = new Node(neighbor.val);
                    map.put(neighbor, clonedNeighbor);
                    queue.offer(neighbor);
                }
                // Add the cloned neighbor to the cloned current node's neighbors.
                clonedCurr.neighbors.add(map.get(neighbor));
            }
        }
        return clonedStart;
    }

    /**
     * Approach 2: DFS with HashMap (Recursive)
     * - Uses Depth-First Search to traverse the graph recursively.
     * - A HashMap is used to store the mapping between original nodes and their clones.
     * - This approach is concise but can lead to stack overflow errors for very large graphs.
     *
     * Implementation Details:
     * 1. Check for null input. If the input graph is null, return null.
     * 2. Create a HashMap `map` to store the mapping of original nodes to their clones.
     * 3. Call the recursive helper function `cloneGraphDFSRecursive`.
     * 4. The `cloneGraphDFSRecursive` function:
     * - Checks if the node is null, and returns null if it is.
     * - Checks if the node has already been cloned (present in the map). If so, return the cloned node from the map.
     * - If the node hasn't been cloned:
     * - Create a new clone of the node.
     * - Store the mapping in the map.
     * - Recursively clone each neighbor and add the cloned neighbors to the cloned node's neighbors list.
     * - Return the cloned node.
     *
     * Example Use Case:
     * - Cloning a configuration graph in a network management system.
     *
     * @param node The node to start cloning from.
     * @return The cloned graph's starting node.
     */
    public Node cloneGraphDFS(Node node) {
        if (node == null) {
            return null;
        }
        Map<Node, Node> map = new HashMap<>();
        return cloneGraphDFSRecursive(node, map);
    }

    private Node cloneGraphDFSRecursive(Node node, Map<Node, Node> map) {
        if (node == null) return null;

        if (map.containsKey(node)) {
            return map.get(node);
        }

        Node clonedNode = new Node(node.val);
        map.put(node, clonedNode);

        for (Node neighbor : node.neighbors) {
            clonedNode.neighbors.add(cloneGraphDFSRecursive(neighbor, map));
        }
        return clonedNode;
    }

    /**
     * Approach 3: Iterative DFS with Stack
     * - Uses Depth-First Search iteratively with a stack.
     * - This avoids recursion and potential stack overflow errors.
     * - A HashMap is used to store the mapping between original nodes and their clones.
     *
     * Implementation Details:
     * 1. Check for null input.
     * 2. Create a HashMap `map` to store cloned nodes.
     * 3. Create a stack `stack` to simulate DFS.
     * 4. Clone the starting node, put it in the map, and push the original node onto the stack.
     * 5. While the stack is not empty:
     * - Pop a node from the stack.
     * - Get its clone from the map.
     * - For each neighbor:
     * - If the neighbor hasn't been cloned:
     * - Clone it, put it in the map, and push the original neighbor onto the stack.
     * - Add the clone of the neighbor to the cloned node's neighbors.
     * 6. Return the clone of the starting node.
     *
     * Example Use Case:
     * - Cloning a dependency graph in a software build system.
     *
     * @param node The node to start cloning from.
     * @return The cloned graph's starting node.
     */
    public Node cloneGraphIterativeDFS(Node node) {
        if (node == null) {
            return null;
        }

        Map<Node, Node> map = new HashMap<>();
        Stack<Node> stack = new Stack<>();

        Node clonedStart = new Node(node.val);
        map.put(node, clonedStart);
        stack.push(node);

        while (!stack.isEmpty()) {
            Node current = stack.pop();
            Node clonedCurrent = map.get(current);

            for (Node neighbor : current.neighbors) {
                if (!map.containsKey(neighbor)) {
                    Node clonedNeighbor = new Node(neighbor.val);
                    map.put(neighbor, clonedNeighbor);
                    stack.push(neighbor);
                }
                clonedCurrent.neighbors.add(map.get(neighbor));
            }
        }
        return clonedStart;
    }

    /**
     * Approach 4: BFS with HashMap and Visited Set Optimization
     * - Similar to Approach 1 (BFS), but uses a `visited` set for optimization.
     * - This approach ensures that nodes are not processed multiple times, improving efficiency.
     * - Uses Breadth-First Search to traverse the graph.
     * - A HashMap is used to store the mapping between original nodes and their clones.
     *
     * Implementation Details:
     * 1. Check for null input.
     * 2. Create a HashMap `map` to store cloned nodes.
     * 3. Create a queue `queue` for BFS traversal.
     * 4. Create a HashSet `visited` to track visited nodes.
     * 5. Clone the starting node, put it in the map, add the original to visited, and enqueue the original.
     * 6. While the queue is not empty:
     * - Dequeue a node.
     * - Get its clone.
     * - For each neighbor:
     * - If the neighbor hasn't been visited:
     * - Clone it, put it in the map, add the original neighbor to visited, and enqueue the original neighbor.
     * - Add the clone of the neighbor to the cloned node's neighbors.
     * 7. Return the clone of the starting node.
     *
     * Example Use Case:
     * - Optimizing the cloning of a large graph representing a complex system architecture.
     *
     * @param node The node to start cloning from.
     * @return The cloned graph's starting node.
     */
    public Node cloneGraphBFSWithVisited(Node node) {
        if (node == null) {
            return null;
        }

        Map<Node, Node> map = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();
        Set<Node> visited = new HashSet<>();

        Node clonedStart = new Node(node.val);
        map.put(node, clonedStart);
        visited.add(node);
        queue.offer(node);

        while (!queue.isEmpty()) {
            Node current = queue.poll();
            Node clonedCurrent = map.get(current);

            for (Node neighbor : current.neighbors) {
                if (!visited.contains(neighbor)) {
                    Node clonedNeighbor = new Node(neighbor.val);
                    map.put(neighbor, clonedNeighbor);
                    visited.add(neighbor);
                    queue.offer(neighbor);
                }
                clonedCurrent.neighbors.add(map.get(neighbor));
            }
        }
        return clonedStart;
    }

    /**
     * Approach 5: DFS with HashMap and Explicit Visited Check
     * - Similar to Approach 2 (Recursive DFS), but with an explicit check to prevent revisiting.
     * - Emphasizes clarity in the recursive step.
     * - Uses Depth-First Search to traverse the graph recursively.
     * - A HashMap is used to store the mapping between original nodes and their clones.
     *
     * Implementation Details:
     * 1. Check for null input.
     * 2. Create a HashMap `map` to store the cloned nodes.
     * 3. Create a HashSet `visited` to track visited nodes.
     * 4. Call the recursive helper function `cloneGraphDFSRecursiveWithVisited`.
     * 5. The `cloneGraphDFSRecursiveWithVisited` function:
     * - Checks if the node is null, returns null.
     * - Checks if the node has already been cloned (present in the map), returns the clone.
     * - If not cloned:
     * - Clone the node, put it in the map, and mark the original as visited.
     * - For each neighbor:
     * - Recursively clone the neighbor.
     * - Add the cloned neighbor to the current clone's neighbors.
     * - Return the cloned node.
     *
     * Example Use Case:
     * - Cloning a directed acyclic graph (DAG) representing task dependencies in a workflow engine.
     *
     * @param node The node to start cloning from.
     * @return The cloned graph's starting node.
     */
    public Node cloneGraphDFSWithVisited(Node node) {
        if (node == null) {
            return null;
        }
        Map<Node, Node> map = new HashMap<>();
        Set<Node> visited = new HashSet<>();
        return cloneGraphDFSRecursiveWithVisited(node, map, visited);
    }

    private Node cloneGraphDFSRecursiveWithVisited(Node node, Map<Node, Node> map, Set<Node> visited) {
        if (node == null) return null;

        if (map.containsKey(node)) {
            return map.get(node);
        }

        Node clonedNode = new Node(node.val);
        map.put(node, clonedNode);
        visited.add(node); // Mark the original node as visited.

        for (Node neighbor : node.neighbors) {
            clonedNode.neighbors.add(cloneGraphDFSRecursiveWithVisited(neighbor, map, visited));
        }
        return clonedNode;
    }

    // Helper method to construct a graph from an adjacency list (for testing)
    private Node buildGraph(int[][] adjList) {
        if (adjList == null || adjList.length == 0) {
            return null;
        }

        Node[] nodes = new Node[adjList.length + 1]; // 1-indexed
        for (int i = 1; i <= adjList.length; i++) {
            nodes[i] = new Node(i);
        }

        for (int i = 1; i <= adjList.length; i++) {
            for (int neighborVal : adjList[i - 1]) {
                nodes[i].neighbors.add(nodes[neighborVal]);
            }
        }
        return nodes[1]; // Return the first node as the starting point of the graph
    }

    // Helper method to print the cloned graph (for testing)
    private void printGraph(Node node, Map<Node, Node> visited) {
        if (node == null) return;

        if (visited.containsKey(node)) return;  //avoid infinite loops

        visited.put(node, node);
        System.out.print("Node " + node.val + " -> ");
        for (Node neighbor : node.neighbors) {
            System.out.print(neighbor.val + " ");
        }
        System.out.println();
        for (Node neighbor : node.neighbors) {
            printGraph(neighbor, visited);
        }
    }

    public static void main(String[] args) {
        CloneGraph solution = new CloneGraph();

        // Example graph represented as an adjacency list (1-indexed)
        // {{2, 4}, {1, 3}, {2, 4}, {1, 3}} represents the following graph:
        // 1 -> 2, 4
        // 2 -> 1, 3
        // 3 -> 2, 4
        // 4 -> 1, 3
        int[][] adjList = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};
        Node graph = solution.buildGraph(adjList);

        // Test with a null graph
        Node clonedNull = solution.cloneGraphBFS(null);
        System.out.println("Cloned null graph: " + (clonedNull == null ? "null" : "not null"));

        // Test with an empty graph (represented as an empty adjacency list)
        int[][] emptyAdjList = {};
        Node emptyGraph = solution.buildGraph(emptyAdjList);
        Node clonedEmpty = solution.cloneGraphBFS(emptyGraph);
        System.out.println("Cloned empty graph: " + (clonedEmpty == null ? "null" : "not null"));


        // Test different cloning approaches
        System.out.println("\nOriginal Graph:");
        solution.printGraph(graph, new HashMap<>());

        // Clone using BFS
        Node clonedBFS = solution.cloneGraphBFS(graph);
        System.out.println("\nCloned Graph (BFS):");
        solution.printGraph(clonedBFS, new HashMap<>());

        // Clone using DFS
        Node clonedDFS = solution.cloneGraphDFS(graph);
        System.out.println("\nCloned Graph (DFS):");
        solution.printGraph(clonedDFS, new HashMap<>());

        // Clone using Iterative DFS
        Node clonedIterativeDFS = solution.cloneGraphIterativeDFS(graph);
        System.out.println("\nCloned Graph (Iterative DFS):");
        solution.printGraph(clonedIterativeDFS, new HashMap<>());

        // Clone using BFS with Visited Set
        Node clonedBFSVisited = solution.cloneGraphBFSWithVisited(graph);
        System.out.println("\nCloned Graph (BFS with Visited):");
        solution.printGraph(clonedBFSVisited, new HashMap<>());

        // Clone using DFS with Visited Set
        Node clonedDFSVisited = solution.cloneGraphDFSWithVisited(graph);
        System.out.println("\nCloned Graph (DFS with Visited):");
        solution.printGraph(clonedDFSVisited, new HashMap<>());
    }
}

// Definition for a Node.
class Node {
    public int val;
    public List<Node> neighbors;

    public Node() {
        val = 0;
        neighbors = new ArrayList<Node>();
    }

    public Node(int _val) {
        val = _val;
        neighbors = new ArrayList<Node>();
    }

    public Node(int _val, ArrayList<Node> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
}
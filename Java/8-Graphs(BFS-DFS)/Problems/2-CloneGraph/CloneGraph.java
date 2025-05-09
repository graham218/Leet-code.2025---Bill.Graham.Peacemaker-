import java.util.*;

public class CloneGraph {

    /**
     * Approach 1: Breadth-First Search (BFS)
     *
     * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     * Space Complexity: O(V), as we use a queue and a map to store nodes.
     */
    public Node cloneGraphBFS(Node node) {
        if (node == null) {
            return null;
        }

        // Use a map to store the mapping between original nodes and their clones.
        Map<Node, Node> nodeMap = new HashMap<>();
        // Use a queue to perform BFS.
        Queue<Node> queue = new LinkedList<>();

        // Clone the starting node and add it to the queue and map.
        Node firstClone = new Node(node.val);
        nodeMap.put(node, firstClone);
        queue.offer(node);

        // Perform BFS.
        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            Node currClone = nodeMap.get(curr);

            // Iterate over the neighbors of the current node.
            for (Node neighbor : curr.neighbors) {
                // If the neighbor has not been cloned, clone it and add it to the queue and map.
                if (!nodeMap.containsKey(neighbor)) {
                    Node neighborClone = new Node(neighbor.val);
                    nodeMap.put(neighbor, neighborClone);
                    queue.offer(neighbor);
                }
                // Add the clone of the neighbor to the neighbors list of the clone of the current node.
                currClone.neighbors.add(nodeMap.get(neighbor));
            }
        }

        return firstClone;
    }

    /**
     * Approach 2: Depth-First Search (DFS) - Iterative
     *
     * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     * Space Complexity: O(V), as we use a stack and a map to store nodes.
     */
    public Node cloneGraphDFSIterative(Node node) {
        if (node == null) {
            return null;
        }

        // Use a map to store the mapping between original nodes and their clones.
        Map<Node, Node> nodeMap = new HashMap<>();
        // Use a stack to perform DFS.
        Stack<Node> stack = new Stack<>();

        // Clone the starting node and add it to the stack and map.
        Node firstClone = new Node(node.val);
        nodeMap.put(node, firstClone);
        stack.push(node);

        // Perform DFS.
        while (!stack.isEmpty()) {
            Node curr = stack.pop();
            Node currClone = nodeMap.get(curr);

            // Iterate over the neighbors of the current node.
            for (Node neighbor : curr.neighbors) {
                // If the neighbor has not been cloned, clone it and add it to the stack and map.
                if (!nodeMap.containsKey(neighbor)) {
                    Node neighborClone = new Node(neighbor.val);
                    nodeMap.put(neighbor, neighborClone);
                    stack.push(neighbor);
                }
                // Add the clone of the neighbor to the neighbors list of the clone of the current node.
                currClone.neighbors.add(nodeMap.get(neighbor));
            }
        }

        return firstClone;
    }

    /**
     * Approach 3: Depth-First Search (DFS) - Recursive
     *
     * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     * Space Complexity: O(V), as we use a map to store nodes and the recursion stack can go up to V in the worst case.
     */
    public Node cloneGraphDFSRecursive(Node node) {
        if (node == null) {
            return null;
        }

        // Use a map to store the mapping between original nodes and their clones.
        Map<Node, Node> nodeMap = new HashMap<>();
        return cloneGraphDFSRecursiveHelper(node, nodeMap);
    }

    private Node cloneGraphDFSRecursiveHelper(Node node, Map<Node, Node> nodeMap) {
        // If the node has already been cloned, return the clone.
        if (nodeMap.containsKey(node)) {
            return nodeMap.get(node);
        }

        // Clone the current node.
        Node cloneNode = new Node(node.val);
        nodeMap.put(node, cloneNode);

        // Recursively clone the neighbors.
        for (Node neighbor : node.neighbors) {
            cloneNode.neighbors.add(cloneGraphDFSRecursiveHelper(neighbor, nodeMap));
        }

        return cloneNode;
    }

    /**
     * Approach 4: Iterative using a Queue and Visited Set
     * Uses a queue for BFS and a set to track visited nodes, simplifying the logic slightly.
     *
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    public Node cloneGraphQueueSet(Node node) {
        if (node == null) return null;

        Map<Node, Node> map = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();
        Set<Node> visited = new HashSet<>();

        Node clonedStart = new Node(node.val);
        map.put(node, clonedStart);
        queue.offer(node);
        visited.add(node);

        while (!queue.isEmpty()) {
            Node u = queue.poll();
            Node clonedU = map.get(u);

            for (Node v : u.neighbors) {
                if (!map.containsKey(v)) {
                    Node clonedV = new Node(v.val);
                    map.put(v, clonedV);
                }
                clonedU.neighbors.add(map.get(v));
                if (!visited.contains(v)) {
                    queue.offer(v);
                    visited.add(v);
                }
            }
        }
        return clonedStart;
    }

    /**
     * Approach 5: Using a single HashMap and iterative approach.
     * This approach uses only one HashMap to store the mapping of original nodes to cloned nodes.
     * It iteratively clones the graph using a queue.
     *
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    public Node cloneGraphSingleMap(Node node) {
        if (node == null) {
            return null;
        }

        Map<Node, Node> cloned = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();

        cloned.put(node, new Node(node.val)); // Create clone of the first node.
        queue.offer(node);

        while (!queue.isEmpty()) {
            Node u = queue.poll();
            Node clonedU = cloned.get(u);

            for (Node neighbor : u.neighbors) {
                if (!cloned.containsKey(neighbor)) {
                    cloned.put(neighbor, new Node(neighbor.val)); // Create clone if it doesn't exist
                    queue.offer(neighbor);
                }
                clonedU.neighbors.add(cloned.get(neighbor));
            }
        }
        return cloned.get(node);
    }

    public static void main(String[] args) {
        // Create a sample graph.
        Node node1 = new Node(1);
        Node node2 = new Node(2);
        Node node3 = new Node(3);
        Node node4 = new Node(4);

        node1.neighbors.add(node2);
        node1.neighbors.add(node4);
        node2.neighbors.add(node1);
        node2.neighbors.add(node3);
        node3.neighbors.add(node2);
        node3.neighbors.add(node4);
        node4.neighbors.add(node1);
        node4.neighbors.add(node3);

        CloneGraph solution = new CloneGraph();

        // Test the BFS approach.
        Node clonedGraphBFS = solution.cloneGraphBFS(node1);
        System.out.println("BFS Clone:");
        printGraph(clonedGraphBFS);

        // Test the DFS Iterative approach.
        Node clonedGraphDFSIterative = solution.cloneGraphDFSIterative(node1);
        System.out.println("\nDFS Iterative Clone:");
        printGraph(clonedGraphDFSIterative);

        // Test the DFS Recursive approach.
        Node clonedGraphDFSRecursive = solution.cloneGraphDFSRecursive(node1);
        System.out.println("\nDFS Recursive Clone:");
        printGraph(clonedGraphDFSRecursive);

        // Test the Queue and Set approach.
        Node clonedGraphQueueSet = solution.cloneGraphQueueSet(node1);
        System.out.println("\nQueue and Set Clone:");
        printGraph(clonedGraphQueueSet);

        // Test the Single Map approach
        Node clonedGraphSingleMap = solution.cloneGraphSingleMap(node1);
        System.out.println("\nSingle Map Clone:");
        printGraph(clonedGraphSingleMap);
    }

    // Helper method to print the graph (for testing purposes).  Avoids infinite recursion.
    public static void printGraph(Node node) {
        if (node == null) {
            System.out.println("Graph is null.");
            return;
        }
        Set<Node> visited = new HashSet<>();
        Queue<Node> queue = new LinkedList<>();
        queue.offer(node);
        visited.add(node);

        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            System.out.print("Node " + curr.val + ": Neighbors -> ");
            for (Node neighbor : curr.neighbors) {
                System.out.print(neighbor.val + " ");
                if (!visited.contains(neighbor)) {
                    queue.offer(neighbor);
                    visited.add(neighbor);
                }
            }
            System.out.println();
        }
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
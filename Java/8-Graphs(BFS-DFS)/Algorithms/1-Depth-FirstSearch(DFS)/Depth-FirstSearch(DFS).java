import java.util.*;

public class DFSGraphTraversal {

    // Adjacency List representation of the graph
    private static Map<Integer, List<Integer>> adjList;

    // Method to add an edge to the graph
    private static void addEdge(int u, int v) {
        adjList.computeIfAbsent(u, k -> new ArrayList<>()).add(v);
        adjList.computeIfAbsent(v, k -> new ArrayList<>()).add(u); // For an undirected graph
    }

    // Method to initialize the graph
    private static void initializeGraph(int numNodes) {
        adjList = new HashMap<>();
        for (int i = 0; i < numNodes; i++) {
            adjList.put(i, new ArrayList<>()); // Initialize each node with an empty list of neighbors
        }
    }

    public static void main(String[] args) {
        // Create a graph with 6 nodes (0 to 5)
        int numNodes = 6;
        initializeGraph(numNodes);

        // Add edges to the graph
        addEdge(0, 1);
        addEdge(0, 2);
        addEdge(1, 3);
        addEdge(1, 4);
        addEdge(2, 4);
        addEdge(3, 5);

        System.out.println("Graph Adjacency List: " + adjList);

        System.out.println("\nDepth-First Search (DFS) Traversal:");
        System.out.println("\n1. Recursive DFS:");
        // Visited array to keep track of visited nodes.  Important to prevent infinite loops in graphs with cycles.
        boolean[] visitedRecursive = new boolean[numNodes];
        // Start DFS from node 0
        dfsRecursive(0, visitedRecursive);

        System.out.println("\n\n2. Iterative DFS with Stack:");
        boolean[] visitedIterative = new boolean[numNodes];
        dfsIterative(0, visitedIterative);

        System.out.println("\n\n3. Recursive DFS with Pre-order Traversal:");
        boolean[] visitedPreOrder = new boolean[numNodes];
        dfsPreOrder(0, visitedPreOrder, new ArrayList<>());

        System.out.println("\n\n4. Recursive DFS with Post-order Traversal:");
        boolean[] visitedPostOrder = new boolean[numNodes];
        List<Integer> postOrderList = new ArrayList<>();
        dfsPostOrder(0, visitedPostOrder, postOrderList);
        System.out.println(postOrderList);

        System.out.println("\n\n5. Iterative DFS with Stack (Alternative):");
        boolean[] visitedIterativeAlt = new boolean[numNodes];
        dfsIterativeAlt(0, visitedIterativeAlt);

        System.out.println("\n\nDFS starting from different nodes:");
        for (int startNode = 0; startNode < numNodes; startNode++) {
            boolean[] visited = new boolean[numNodes];
            System.out.print("DFS from node " + startNode + ": ");
            dfsRecursive(startNode, visited);
            System.out.println();
        }
    }

    // 1. Recursive Depth-First Search
    //   - Uses a recursive approach.
    //   - Base case: If the node is visited, return.
    //   - Mark the current node as visited.
    //   - Print the current node.
    //   - Recursively call DFS for all the neighbors of the current node.
    private static void dfsRecursive(int node, boolean[] visited) {
        if (visited[node]) {
            return; // Base case: Node already visited
        }

        visited[node] = true; // Mark the current node as visited
        System.out.print(node + " "); // Process the node (e.g., print it)

        // Iterate over the neighbors of the current node
        List<Integer> neighbors = adjList.get(node);
        if (neighbors != null) {
            for (int neighbor : neighbors) {
                dfsRecursive(neighbor, visited); // Recursively call DFS for each neighbor
            }
        }
    }

    // 2. Iterative Depth-First Search using Stack
    //   - Uses a stack to simulate recursion.
    //   - Push the starting node onto the stack.
    //   - While the stack is not empty:
    //     - Pop a node from the stack.
    //     - If the node is not visited:
    //       - Mark the node as visited.
    //       - Print the node.
    //       - Push all the unvisited neighbors of the node onto the stack.
    private static void dfsIterative(int startNode, boolean[] visited) {
        Stack<Integer> stack = new Stack<>();
        stack.push(startNode); // Push the starting node onto the stack

        while (!stack.isEmpty()) {
            int node = stack.pop(); // Pop the top node from the stack

            if (!visited[node]) {
                visited[node] = true; // Mark the node as visited
                System.out.print(node + " "); // Process the node

                List<Integer> neighbors = adjList.get(node);
                if (neighbors != null) {
                    // Push neighbors onto the stack in reverse order to maintain DFS order (important for some graph structures)
                    for (int i = neighbors.size() - 1; i >= 0; i--) {
                        stack.push(neighbors.get(i));
                    }
                }
            }
        }
    }

    // 3. Recursive DFS with Pre-order Traversal
    //    - Similar to the first recursive approach, but explicitly demonstrates pre-order processing.
    //    - "Pre-order" means that the node is visited *before* its children.
    private static void dfsPreOrder(int node, boolean[] visited, List<Integer> resultList) {
        if (visited[node]) {
            return;
        }
        visited[node] = true;
        resultList.add(node); // Add the node to the result list *before* visiting neighbors (pre-order)
        System.out.print(node + " "); // Process the node
        List<Integer> neighbors = adjList.get(node);
        if (neighbors != null) {
            for (int neighbor : neighbors) {
                dfsPreOrder(neighbor, visited, resultList);
            }
        }
    }

    // 4. Recursive DFS with Post-order Traversal
    //    - Demonstrates post-order processing in DFS.
    //    - "Post-order" means that the node is visited *after* its children.
    private static void dfsPostOrder(int node, boolean[] visited, List<Integer> resultList) {
        if (visited[node]) {
            return;
        }
        visited[node] = true;
        List<Integer> neighbors = adjList.get(node);
        if (neighbors != null) {
            for (int neighbor : neighbors) {
                dfsPostOrder(neighbor, visited, resultList);
            }
        }
        resultList.add(node); // Add the node to the result list *after* visiting neighbors (post-order)
    }

    // 5. Iterative DFS with Stack (Alternative)
    //    - Another iterative approach, slightly different neighbor processing.
    private static void dfsIterativeAlt(int startNode, boolean[] visited) {
        Stack<Integer> stack = new Stack<>();
        stack.push(startNode);

        while (!stack.isEmpty()) {
            int node = stack.pop();

            if (!visited[node]) {
                visited[node] = true;
                System.out.print(node + " ");

                List<Integer> neighbors = adjList.get(node);
                if (neighbors != null) {
                    for (int neighbor : neighbors) {
                        if (!visited[neighbor]) { // Only push unvisited neighbors
                            stack.push(neighbor);
                        }
                    }
                }
            }
        }
    }
}


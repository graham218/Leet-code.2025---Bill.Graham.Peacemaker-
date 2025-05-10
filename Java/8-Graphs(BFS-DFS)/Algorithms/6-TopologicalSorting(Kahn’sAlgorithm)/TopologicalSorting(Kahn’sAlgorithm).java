import java.util.*;

public class TopologicalSort {

    // 1. Kahn's Algorithm using Array for In-degree and Queue
    //   - Uses a simple array to store in-degrees.
    //   - Iterates through the graph only once to calculate in-degrees.
    //   - Suitable for smaller graphs where the number of nodes is known and relatively small.
    public static List<Integer> topologicalSort1(int V, List<List<Integer>> adj) {
        int[] inDegree = new int[V]; // Array to store in-degrees of all vertices
        Queue<Integer> queue = new LinkedList<>(); // Queue to store vertices with in-degree 0
        List<Integer> result = new ArrayList<>(); // List to store the sorted vertices

        // Calculate in-degrees for each vertex
        for (int i = 0; i < V; i++) {
            for (Integer neighbor : adj.get(i)) {
                inDegree[neighbor]++;
            }
        }

        // Add vertices with in-degree 0 to the queue
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }

        // Process vertices from the queue
        while (!queue.isEmpty()) {
            int u = queue.poll(); // Get the next vertex with in-degree 0
            result.add(u); // Add it to the result

            // Reduce in-degrees of its neighbors
            for (Integer neighbor : adj.get(u)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor); // If a neighbor's in-degree becomes 0, add it to the queue
                }
            }
        }

        // Check for cycles: If not all vertices are in the result, there's a cycle
        if (result.size() != V) {
            return new ArrayList<>(); // Return empty list to indicate cycle
        }

        return result;
    }

    // 2. Kahn's Algorithm using HashMap for In-degree and Queue
    //   - Uses a HashMap to store in-degrees, allowing for non-contiguous vertex labels.
    //   - Useful when vertex labels are not simple 0 to V-1 integers.
    //   - Slightly more memory overhead than using an array, but more flexible.
    public static List<Integer> topologicalSort2(int V, List<List<Integer>> adj) {
        Map<Integer, Integer> inDegree = new HashMap<>(); // HashMap to store in-degrees
        Queue<Integer> queue = new LinkedList<>(); // Queue to store vertices with in-degree 0
        List<Integer> result = new ArrayList<>(); // List to store the sorted vertices

        // Initialize in-degrees to 0 for all vertices
        for (int i = 0; i < V; i++) {
            inDegree.put(i, 0);
        }

        // Calculate in-degrees for each vertex
        for (int i = 0; i < V; i++) {
            for (Integer neighbor : adj.get(i)) {
                inDegree.put(neighbor, inDegree.get(neighbor) + 1); // Increment in-degree of neighbor
            }
        }

        // Add vertices with in-degree 0 to the queue
        for (Integer vertex : inDegree.keySet()) {
            if (inDegree.get(vertex) == 0) {
                queue.offer(vertex);
            }
        }

        // Process vertices from the queue
        while (!queue.isEmpty()) {
            int u = queue.poll(); // Get the next vertex with in-degree 0
            result.add(u); // Add it to the result

            // Reduce in-degrees of its neighbors
            for (Integer neighbor : adj.get(u)) {
                inDegree.put(neighbor, inDegree.get(neighbor) - 1); // Decrement in-degree of neighbor
                if (inDegree.get(neighbor) == 0) {
                    queue.offer(neighbor); // If a neighbor's in-degree becomes 0, add it to the queue
                }
            }
        }
        // Check for cycles: If not all vertices are in the result, there's a cycle
        if (result.size() != V) {
            return new ArrayList<>(); // Return empty list to indicate cycle
        }

        return result;
    }

    // 3. Kahn's Algorithm using Array and ArrayList for In-degree and Queue
    //   - Uses an array for in-degrees and an ArrayList as a queue.
    //   - Demonstrates using ArrayList as a queue (less efficient for queue operations, but possible).
    //   - Mainly for educational purposes to show different data structure options.
    public static List<Integer> topologicalSort3(int V, List<List<Integer>> adj) {
        int[] inDegree = new int[V]; // Array to store in-degrees
        List<Integer> queue = new ArrayList<>(); // ArrayList used as a queue
        List<Integer> result = new ArrayList<>(); // List to store the sorted vertices

        // Calculate in-degrees for each vertex
        for (int i = 0; i < V; i++) {
            for (Integer neighbor : adj.get(i)) {
                inDegree[neighbor]++;
            }
        }

        // Add vertices with in-degree 0 to the queue
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                queue.add(i); // Add to the end of the list (enqueue)
            }
        }

        // Process vertices from the queue
        while (!queue.isEmpty()) {
            int u = queue.remove(0); // Remove from the front of the list (dequeue)
            result.add(u);

            for (Integer neighbor : adj.get(u)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.add(neighbor); // Add to the end of the list (enqueue)
                }
            }
        }
        // Check for cycles: If not all vertices are in the result, there's a cycle
        if (result.size() != V) {
            return new ArrayList<>(); // Return empty list to indicate cycle
        }
        return result;
    }

    // 4. Kahn's Algorithm using PriorityQueue
    // - Uses PriorityQueue.
    // - The output order will be affected if there are multiple nodes with 0 in-degree.
    public static List<Integer> topologicalSort4(int V, List<List<Integer>> adj) {
        int[] inDegree = new int[V];
        PriorityQueue<Integer> pq = new PriorityQueue<>(); // Use PriorityQueue
        List<Integer> result = new ArrayList<>();

        // Calculate in-degrees for each vertex
        for (int i = 0; i < V; i++) {
            for (Integer neighbor : adj.get(i)) {
                inDegree[neighbor]++;
            }
        }

        // Add vertices with in-degree 0 to the queue
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                pq.offer(i);
            }
        }

        // Process vertices from the queue
        while (!pq.isEmpty()) {
            int u = pq.poll();
            result.add(u);

            for (Integer neighbor : adj.get(u)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    pq.offer(neighbor);
                }
            }
        }
        // Check for cycles: If not all vertices are in the result, there's a cycle
        if (result.size() != V) {
            return new ArrayList<>(); // Return empty list to indicate cycle
        }

        return result;
    }

    // 5. Kahn's Algorithm using LinkedList as Queue
    // - Uses LinkedList as the Queue.
    // - Demonstrates using LinkedList as queue.
    public static List<Integer> topologicalSort5(int V, List<List<Integer>> adj) {
        int[] inDegree = new int[V];
        LinkedList<Integer> queue = new LinkedList<>();
        List<Integer> result = new ArrayList<>();

        // Calculate in-degrees for each vertex
        for (int i = 0; i < V; i++) {
            for (Integer neighbor : adj.get(i)) {
                inDegree[neighbor]++;
            }
        }

        // Add vertices with in-degree 0 to the queue
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i); //offer is used to add element in queue
            }
        }

        // Process vertices from the queue
        while (!queue.isEmpty()) {
            int u = queue.poll();  //poll() is used to remove the head of the queue
            result.add(u);

            for (Integer neighbor : adj.get(u)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }
        // Check for cycles: If not all vertices are in the result, there's a cycle
        if (result.size() != V) {
            return new ArrayList<>(); // Return empty list to indicate cycle
        }

        return result;
    }

    public static void main(String[] args) {
        int V = 6; // Number of vertices
        // Adjacency list representation of the graph
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Add edges to the graph (0-based indexing)
        adj.get(5).add(2);
        adj.get(5).add(0);
        adj.get(4).add(0);
        adj.get(4).add(1);
        adj.get(2).add(3);
        adj.get(3).add(1);

        // Perform topological sort using different methods and print the results
        System.out.println("Topological Sort (Method 1 - Array, Queue): " + topologicalSort1(V, adj));
        System.out.println("Topological Sort (Method 2 - HashMap, Queue): " + topologicalSort2(V, adj));
        System.out.println("Topological Sort (Method 3 - Array, ArrayList): " + topologicalSort3(V, adj));
        System.out.println("Topological Sort (Method 4 - Array, PriorityQueue): " + topologicalSort4(V, adj));
        System.out.println("Topological Sort (Method 5 - Array, LinkedList): " + topologicalSort5(V, adj));

        // Example of a graph with a cycle (for testing cycle detection)
        List<List<Integer>> cyclicAdj = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            cyclicAdj.add(new ArrayList<>());
        }
        cyclicAdj.get(0).add(1);
        cyclicAdj.get(1).add(2);
        cyclicAdj.get(2).add(0); // This creates a cycle: 0 -> 1 -> 2 -> 0

        System.out.println("Topological Sort of Cyclic Graph (Method 1): " + topologicalSort1(3, cyclicAdj)); // Should return []
    }
}


import java.util.*;

// Class to represent a graph using an adjacency list representation
class Graph {
    private int V; // Number of vertices
    private LinkedList<Integer>[] adj; // Adjacency list representation

    // Constructor to initialize the graph
    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList();
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].add(w);
        adj[w].add(v); // For an undirected graph
    }

    // Method 1: Standard BFS Traversal
    // Performs BFS traversal starting from a given source node
    void BFS(int s) {
        // Mark all the vertices as not visited(By default set
        // as false)
        boolean visited[] = new boolean[V];
        // Create a queue for BFS
        LinkedList<Integer> queue = new LinkedList<Integer>();
        // Mark the current node as visited and enqueue it
        visited[s] = true;
        queue.add(s);

        System.out.println("BFS Traversal (Standard):");
        while (queue.size() != 0) {
            // Dequeue a vertex from queue and print it
            s = queue.poll();
            System.out.print(s + " ");

            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it
            // visited and enqueue it
            Iterator<Integer> i = adj[s].listIterator();
            while (i.hasNext()) {
                int n = i.next();
                if (!visited[n]) {
                    visited[n] = true;
                    queue.add(n);
                }
            }
        }
        System.out.println();
    }

    // Method 2: BFS with Path Reconstruction
    // Performs BFS and reconstructs the path from the start node to all other reachable nodes
    void BFSWithPath(int startNode) {
        boolean[] visited = new boolean[V];
        int[] parent = new int[V]; // Array to store parent of each node in the BFS tree
        LinkedList<Integer> queue = new LinkedList<>();

        // Initialize visited and parent arrays
        for (int i = 0; i < V; i++) {
            visited[i] = false;
            parent[i] = -1; // -1 indicates no parent
        }

        visited[startNode] = true;
        queue.add(startNode);

        System.out.println("BFS Traversal with Path Reconstruction:");
        while (!queue.isEmpty()) {
            int currentNode = queue.poll();
            System.out.print(currentNode + " ");

            Iterator<Integer> iterator = adj[currentNode].listIterator();
            while (iterator.hasNext()) {
                int neighbor = iterator.next();
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = currentNode; // Store the parent
                    queue.add(neighbor);
                }
            }
        }
        System.out.println();

        // Print paths to all reachable nodes from the start node
        for (int i = 0; i < V; i++) {
            if (i != startNode && visited[i]) {
                System.out.print("Path from " + startNode + " to " + i + ": ");
                printPath(startNode, i, parent);
                System.out.println();
            } else if (i != startNode) {
                System.out.println("No path from " + startNode + " to " + i);
            }
        }
    }

    // Helper function to print the path from start to end node using the parent array
    private void printPath(int start, int end, int[] parent) {
        if (end == -1) return; // No path exists
        ArrayList<Integer> path = new ArrayList<>();
        for (int at = end; at != start; at = parent[at]) {
            if (at == -1) {
                System.out.print("No path");
                return;
            }
            path.add(at);
        }
        path.add(start);
        Collections.reverse(path); // Reverse the path to print it in the correct order
        for (int node : path) {
            System.out.print(node + " ");
        }
    }

    // Method 3: BFS with Distance Tracking
    // Performs BFS and tracks the distance from the start node to all other nodes
    void BFSWithDistance(int startNode) {
        boolean[] visited = new boolean[V];
        int[] distance = new int[V];
        LinkedList<Integer> queue = new LinkedList<>();

        // Initialize visited and distance arrays
        for (int i = 0; i < V; i++) {
            visited[i] = false;
            distance[i] = -1; // -1 indicates unreachable
        }

        visited[startNode] = true;
        distance[startNode] = 0; // Distance from start node to itself is 0
        queue.add(startNode);

        System.out.println("BFS Traversal with Distance:");
        while (!queue.isEmpty()) {
            int currentNode = queue.poll();
            System.out.print(currentNode + " ");

            Iterator<Integer> iterator = adj[currentNode].listIterator();
            while (iterator.hasNext()) {
                int neighbor = iterator.next();
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[currentNode] + 1; // Calculate distance
                    queue.add(neighbor);
                }
            }
        }
        System.out.println();

        // Print distances
        for (int i = 0; i < V; i++) {
            System.out.println("Distance from " + startNode + " to " + i + ": " + distance[i]);
        }
    }

    // Method 4: BFS for disconnected graph
    // Handles disconnected graphs by iterating through all nodes
    void BFSDisconnected() {
        boolean[] visited = new boolean[V];
        LinkedList<Integer> queue = new LinkedList<>();

        System.out.println("BFS Traversal for Disconnected Graph:");
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                // Perform BFS starting from each unvisited node
                visited[i] = true;
                queue.add(i);

                while (!queue.isEmpty()) {
                    int currentNode = queue.poll();
                    System.out.print(currentNode + " ");

                    Iterator<Integer> iterator = adj[currentNode].listIterator();
                    while (iterator.hasNext()) {
                        int neighbor = iterator.next();
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            queue.add(neighbor);
                        }
                    }
                }
            }
        }
        System.out.println();
    }

    // Method 5: Using a Queue Collection
    void BFSUsingQueue(int startNode) {
        boolean[] visited = new boolean[V];
        Queue<Integer> queue = new LinkedList<>(); // Use the Queue interface

        // Initialize visited array
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        visited[startNode] = true;
        queue.offer(startNode); // Use offer() to add to the queue

        System.out.println("BFS Traversal Using Queue Interface:");
        while (!queue.isEmpty()) {
            int currentNode = queue.poll(); // Use poll() to remove from the queue
            System.out.print(currentNode + " ");

            Iterator<Integer> iterator = adj[currentNode].listIterator();
            while (iterator.hasNext()) {
                int neighbor = iterator.next();
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(neighbor);
                }
            }
        }
        System.out.println();
    }
}

// Main class to demonstrate BFS
public class Main {
    public static void main(String[] args) {
        // Create a graph with 6 vertices (0 to 5)
        Graph g = new Graph(6);

        // Add edges to the graph
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(3, 5);
        g.addEdge(4, 5);

        System.out.println("Breadth First Traversal for the graph:");

        // Perform BFS starting from vertex 0
        g.BFS(0); // Standard BFS

        g.BFSWithPath(0); // BFS with path reconstruction

        g.BFSWithDistance(0); // BFS with distance tracking

        // Create a disconnected graph
        Graph g2 = new Graph(7);
        g2.addEdge(0, 1);
        g2.addEdge(2, 3);
        g2.addEdge(4, 5);
        g2.addEdge(4, 6);
        g2.BFSDisconnected();

        g.BFSUsingQueue(0);
    }
}

import java.util.*;
import java.io.*;

// Class to represent a graph using an adjacency list representation
class Graph {
    private int V; // Number of vertices
    private LinkedList<Integer>[] adj; // Adjacency list representation
    private boolean[] visited; // Array to keep track of visited vertices

    // Constructor to initialize the graph
    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList();
        visited = new boolean[v];
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].add(w);
        adj[w].add(v); // For an undirected graph
    }

    // 1. Depth-First Search (DFS) - Recursive Approach
    //   - Basic DFS implementation using recursion.
    //   - Real-world application: Finding connected components in a social network.
    void DFS_Recursive(int v) {
        visited[v] = true; // Mark the current node as visited
        System.out.print(v + " "); // Print the current node

        // Recur for all the adjacent vertices
        Iterator<Integer> i = adj[v].listIterator();
        while (i.hasNext()) {
            int n = i.next();
            if (!visited[n])
                DFS_Recursive(n);
        }
    }

    // 2. DFS - Iterative Approach using Stack
    //   - DFS implementation using a stack instead of recursion.
    //   - Real-world application: Pathfinding in a maze.
    void DFS_Iterative(int start) {
        Stack<Integer> stack = new Stack<>();
        boolean[] visited = new boolean[V]; // Local visited array

        stack.push(start); // Push the starting node onto the stack
        visited[start] = true; // Mark the starting node as visited

        while (!stack.isEmpty()) {
            int v = stack.pop(); // Pop a node from the stack
            System.out.print(v + " "); // Print the node

            // Get all adjacent vertices of the popped vertex v
            Iterator<Integer> i = adj[v].listIterator();
            while (i.hasNext()) {
                int n = i.next();
                if (!visited[n]) {
                    visited[n] = true; // Mark the neighbor as visited
                    stack.push(n); // Push the neighbor onto the stack
                }
            }
        }
    }

    // 3. DFS with Path Tracking
    //    - Modified DFS to track the path from a start node to a target node.
    //    - Real-world application: Finding a route between two locations in a GPS navigation system.
    boolean DFS_PathTracking(int start, int target, List<Integer> path) {
        visited[start] = true;
        path.add(start);

        if (start == target) {
            return true; // Path found
        }

        Iterator<Integer> i = adj[start].listIterator();
        while (i.hasNext()) {
            int n = i.next();
            if (!visited[n]) {
                if (DFS_PathTracking(n, target, path)) {
                    return true; // Path found in recursive call
                }
            }
        }
        path.remove(path.size() - 1); // Remove the current node from the path if no path found
        return false; // Path not found
    }

    // 4. DFS for Topological Sorting
    //    - DFS implementation to perform topological sorting on a directed acyclic graph (DAG).
    //    - Real-world application: Task scheduling or dependency resolution.
    void DFS_TopologicalSort(int v, Stack<Integer> stack) {
        visited[v] = true;
        Integer i;

        Iterator<Integer> it = adj[v].iterator();
        while (it.hasNext()) {
            i = it.next();
            if (!visited[i])
                DFS_TopologicalSort(i, stack);
        }
        stack.push(v); // Push the current vertex to stack which stores result
    }

    // Function to perform topological sort. It uses recursive DFS_TopologicalSort()
    void topologicalSort() {
        Stack<Integer> stack = new Stack<>();
        visited = new boolean[V]; // Reset visited array

        // Call the recursive function to fill the stack
        // in topological order.  Iterate over all vertices, because the graph might
        // be disconnected.
        for (int i = 0; i < V; i++)
            if (!visited[i])
                DFS_TopologicalSort(i, stack);

        // Print contents of stack
        System.out.println("Topological Sort:");
        while (!stack.empty())
            System.out.print(stack.pop() + " ");
        System.out.println();
    }

    // 5. DFS to find Cycle in a Directed Graph
    //    - Detects whether a cycle exists in a directed graph.
    //    - Real-world application: Detecting deadlocks in resource allocation.
    boolean DFS_FindCycle(int v, boolean[] recStack) {
        visited[v] = true;
        recStack[v] = true;

        Iterator<Integer> i = adj[v].listIterator();
        while (i.hasNext()) {
            int neighbor = i.next();
            if (!visited[neighbor]) {
                if (DFS_FindCycle(neighbor, recStack))
                    return true;
            } else if (recStack[neighbor])
                return true;
        }
        recStack[v] = false; // Remove vertex from recursion stack
        return false;
    }

    boolean isCyclic() {
        boolean[] recStack = new boolean[V];
        for (int i = 0; i < V; i++)
            if (!visited[i])
                if (DFS_FindCycle(i, recStack))
                    return true;
        return false;
    }
}

// Main class to test the Graph and DFS implementations
public class Main {
    public static void main(String[] args) {
        // Create a graph with 6 vertices
        Graph g = new Graph(6);

        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(3, 5);
        g.addEdge(4, 5);

        System.out.println("DFS Traversal (Recursive starting from vertex 0):");
        g.DFS_Recursive(0);
        System.out.println();

        System.out.println("DFS Traversal (Iterative starting from vertex 0):");
        g.DFS_Iterative(0);
        System.out.println();

        // Test DFS with path tracking
        List<Integer> path = new ArrayList<>();
        int startNode = 0;
        int targetNode = 5;
        if (g.DFS_PathTracking(startNode, targetNode, path)) {
            System.out.println("Path from " + startNode + " to " + targetNode + ": " + path);
        } else {
            System.out.println("No path found from " + startNode + " to " + targetNode);
        }

        // Create a graph for topological sort
        Graph gTopSort = new Graph(6);
        gTopSort.addEdge(5, 2);
        gTopSort.addEdge(5, 0);
        gTopSort.addEdge(4, 0);
        gTopSort.addEdge(4, 1);
        gTopSort.addEdge(2, 3);
        gTopSort.addEdge(3, 1);
        gTopSort.topologicalSort();

        // Create a graph to test for cycles
        Graph gCycle = new Graph(4);
        gCycle.addEdge(0, 1);
        gCycle.addEdge(0, 2);
        gCycle.addEdge(1, 2);
        gCycle.addEdge(2, 0); // Add this edge to create a cycle
        gCycle.addEdge(2, 3);
        if (gCycle.isCyclic())
            System.out.println("Graph contains cycle");
        else
            System.out.println("Graph does not contain cycle");

        // Create a graph without cycle
        Graph gNoCycle = new Graph(4);
        gNoCycle.addEdge(0, 1);
        gNoCycle.addEdge(0, 2);
        gNoCycle.addEdge(1, 2);
        gNoCycle.addEdge(2, 3);
        if (gNoCycle.isCyclic())
            System.out.println("Graph contains cycle");
        else
            System.out.println("Graph does not contain cycle");
    }
}

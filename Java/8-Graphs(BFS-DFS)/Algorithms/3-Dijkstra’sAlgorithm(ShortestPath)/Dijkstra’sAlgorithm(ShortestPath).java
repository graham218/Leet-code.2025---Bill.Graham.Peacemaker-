import java.util.*;

public class DijkstraAlgorithm {

    // 1. Dijkstra's Algorithm using Priority Queue (Optimized)
    //    - Uses a PriorityQueue to efficiently select the node with the smallest distance.
    //    - Time Complexity: O(E + V log V), where V is the number of vertices and E is the number of edges.
    //    - This is the most common and efficient implementation.
    public static int[] dijkstraPQ(int[][] graph, int start) {
        int numVertices = graph.length;
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        // PriorityQueue to store nodes with their distances.  The queue is ordered
        // based on the distance to the node (shortest distance first).
        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.distance));
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;
            int uDistance = u.distance;

            // Important optimization: If the current distance to u is greater than the
            // known shortest distance, we can skip processing its neighbors.  This is
            // because we've already found a shorter path to u.
            if (uDistance > distances[uVertex]) {
                continue;
            }

            for (int v = 0; v < numVertices; v++) {
                if (graph[uVertex][v] != 0) { // There is an edge from u to v
                    int edgeWeight = graph[uVertex][v];
                    int newDistance = uDistance + edgeWeight;

                    if (newDistance < distances[v]) {
                        distances[v] = newDistance;
                        pq.offer(new Node(v, newDistance));
                    }
                }
            }
        }
        return distances;
    }

    // 2. Dijkstra's Algorithm using a basic array (Unoptimized)
    //    - Uses a simple array to store distances and iterates through it to find
    //      the minimum distance.
    //    - Time Complexity: O(V^2), where V is the number of vertices.
    //    - Less efficient than the PriorityQueue approach, especially for large graphs.
    public static int[] dijkstraArray(int[][] graph, int start) {
        int numVertices = graph.length;
        int[] distances = new int[numVertices];
        boolean[] visited = new boolean[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        for (int count = 0; count < numVertices - 1; count++) {
            // Find the vertex with the minimum distance among the unvisited vertices
            int minDistance = Integer.MAX_VALUE;
            int u = -1; // Initialize u to -1 (invalid vertex)
            for (int v = 0; v < numVertices; v++) {
                if (!visited[v] && distances[v] <= minDistance) {
                    minDistance = distances[v];
                    u = v;
                }
            }

            // If no unvisited vertex with finite distance was found, exit the loop.
            if (u == -1) break;

            visited[u] = true; // Mark the selected vertex as visited

            // Update distances of the adjacent vertices of u
            for (int v = 0; v < numVertices; v++) {
                if (!visited[v] && graph[u][v] != 0 && distances[u] != Integer.MAX_VALUE
                        && distances[u] + graph[u][v] < distances[v]) {
                    distances[v] = distances[u] + graph[u][v];
                }
            }
        }
        return distances;
    }

    // 3. Dijkstra's Algorithm with Path Reconstruction
    //    -  In addition to finding the shortest distances, it also reconstructs the
    //       shortest paths.
    //    - Time Complexity: O(E + V log V)  (using PriorityQueue)
    public static Map<Integer, Integer> dijkstraWithPath(int[][] graph, int start, int end) {
        int numVertices = graph.length;
        int[] distances = new int[numVertices];
        int[] predecessors = new int[numVertices]; // Store the predecessor node in the shortest path
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;
        Arrays.fill(predecessors, -1); // Initialize predecessors array

        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.distance));
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;
            int uDistance = u.distance;

            if (uDistance > distances[uVertex]) {
                continue;
            }

            if (uVertex == end) {
                break; // Optimization: Stop if we reach the end node.
            }

            for (int v = 0; v < numVertices; v++) {
                if (graph[uVertex][v] != 0) {
                    int edgeWeight = graph[uVertex][v];
                    int newDistance = uDistance + edgeWeight;

                    if (newDistance < distances[v]) {
                        distances[v] = newDistance;
                        predecessors[v] = uVertex; // Store the predecessor
                        pq.offer(new Node(v, newDistance));
                    }
                }
            }
        }

        // Reconstruct the path from start to end using the predecessors array
        Map<Integer, Integer> path = new HashMap<>();
        if (distances[end] != Integer.MAX_VALUE) {
            int current = end;
            while (current != start) {
                path.put(predecessors[current], current);
                current = predecessors[current];
            }
        }
        return path;
    }

    // 4. Dijkstra with Adjacency List
    //    - Uses an adjacency list to represent the graph, which can be more efficient
    //      for sparse graphs (graphs with fewer edges).
    //    - Time Complexity: O(E + V log V)
    public static int[] dijkstraAdjacencyList(List<List<Edge>> adjList, int start) {
        int numVertices = adjList.size();
        int[] distances = new int[numVertices];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[start] = 0;

        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.distance));
        pq.offer(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node u = pq.poll();
            int uVertex = u.vertex;
            int uDistance = u.distance;

            if (uDistance > distances[uVertex]) {
                continue;
            }

            for (Edge edge : adjList.get(uVertex)) {
                int v = edge.destination;
                int weight = edge.weight;
                int newDistance = uDistance + weight;

                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    pq.offer(new Node(v, newDistance));
                }
            }
        }
        return distances;
    }

    // 5. Dijkstra's Algorithm for a Grid (2D array)
    //    -  Handles a 2D grid where each cell represents a node, and movement
    //       is allowed in four directions (up, down, left, right).
    //    - Time Complexity: O(R * C * log(R * C)) where R is number of rows and C is number of columns.
    public static int dijkstraGrid(int[][] grid, int startRow, int startCol, int endRow, int endCol) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][] distances = new int[rows][cols];
        for (int[] row : distances) {
            Arrays.fill(row, Integer.MAX_VALUE);
        }
        distances[startRow][startCol] = 0;

        PriorityQueue<GridNode> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.distance));
        pq.offer(new GridNode(startRow, startCol, 0));

        int[] dr = {-1, 1, 0, 0}; // Possible row movements (up, down, left, right)
        int[] dc = {0, 0, -1, 1}; // Possible column movements

        while (!pq.isEmpty()) {
            GridNode u = pq.poll();
            int uRow = u.row;
            int uCol = u.col;
            int uDistance = u.distance;

            if (uDistance > distances[uRow][uCol]) {
                continue;
            }

            if (uRow == endRow && uCol == endCol) {
                return uDistance; // Found the shortest path
            }

            for (int i = 0; i < 4; i++) {
                int newRow = uRow + dr[i];
                int newCol = uCol + dc[i];

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    int newDistance = uDistance + grid[newRow][newCol]; // Assuming grid[r][c] is the cost to move to cell (r, c)
                    if (newDistance < distances[newRow][newCol]) {
                        distances[newRow][newCol] = newDistance;
                        pq.offer(new GridNode(newRow, newCol, newDistance));
                    }
                }
            }
        }
        return -1; // No path found
    }

    // Helper class for Dijkstra with Priority Queue and Adjacency List
    static class Node {
        int vertex;
        int distance;

        public Node(int vertex, int distance) {
            this.vertex = vertex;
            this.distance = distance;
        }
    }

    // Helper class for Dijkstra in Grid
    static class GridNode {
        int row;
        int col;
        int distance;

        public GridNode(int row, int col, int distance) {
            this.row = row;
            this.col = col;
            this.distance = distance;
        }
    }

    // Helper class for Adjacency List
    static class Edge {
        int destination;
        int weight;

        public Edge(int destination, int weight) {
            this.destination = destination;
            this.weight = weight;
        }
    }

    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix
        int[][] graph = {
                {0, 4, 0, 0, 0, 0, 0, 8, 0},
                {4, 0, 8, 0, 0, 0, 0, 11, 0},
                {0, 8, 0, 7, 0, 4, 0, 0, 2},
                {0, 0, 7, 0, 9, 14, 0, 0, 0},
                {0, 0, 0, 9, 0, 10, 0, 0, 0},
                {0, 0, 4, 14, 10, 0, 2, 0, 0},
                {0, 0, 0, 0, 0, 2, 0, 1, 6},
                {8, 11, 0, 0, 0, 0, 1, 0, 7},
                {0, 0, 2, 0, 0, 0, 6, 7, 0}
        };

        int startNode = 0;
        System.out.println("Dijkstra's Algorithm Results:");

        // 1. Dijkstra with Priority Queue
        int[] distancesPQ = dijkstraPQ(graph, startNode);
        System.out.println("Shortest distances from node " + startNode + " (Priority Queue): " + Arrays.toString(distancesPQ));

        // 2. Dijkstra with Array
        int[] distancesArray = dijkstraArray(graph, startNode);
        System.out.println("Shortest distances from node " + startNode + " (Array): " + Arrays.toString(distancesArray));

        // 3. Dijkstra with Path Reconstruction
        int endNode = 6;
        Map<Integer, Integer> path = dijkstraWithPath(graph, startNode, endNode);
        System.out.println("Shortest path from " + startNode + " to " + endNode + ": " + getPathString(path, startNode, endNode));

        // 4. Dijkstra with Adjacency List
        List<List<Edge>> adjList = new ArrayList<>();
        for (int i = 0; i < graph.length; i++) {
            adjList.add(new ArrayList<>());
            for (int j = 0; j < graph[i].length; j++) {
                if (graph[i][j] != 0) {
                    adjList.get(i).add(new Edge(j, graph[i][j]));
                }
            }
        }
        int[] distancesList = dijkstraAdjacencyList(adjList, startNode);
        System.out.println("Shortest distances from node " + startNode + " (Adjacency List): " + Arrays.toString(distancesList));

        // 5. Dijkstra for Grid
        int[][] grid = {
                {0, 3, 0, 0},
                {1, 0, 2, 3},
                {0, 2, 0, 1},
                {0, 0, 1, 0}
        };
        int startRow = 0, startCol = 0;
        int endRow = 3, endCol = 3;
        int shortestDistanceGrid = dijkstraGrid(grid, startRow, startCol, endRow, endCol);
        System.out.println("Shortest distance in grid from (" + startRow + "," + startCol + ") to (" + endRow + "," + endCol + "): " + shortestDistanceGrid);
    }

    // Helper method to reconstruct path as a string
    private static String getPathString(Map<Integer, Integer> path, int start, int end) {
        if (path.isEmpty()) {
            return "No path exists";
        }
        StringBuilder sb = new StringBuilder();
        sb.append(start);
        int current = start;
        while (current != end) {
            current = path.get(current);
            sb.append(" -> ").append(current);
        }
        return sb.toString();
    }
}


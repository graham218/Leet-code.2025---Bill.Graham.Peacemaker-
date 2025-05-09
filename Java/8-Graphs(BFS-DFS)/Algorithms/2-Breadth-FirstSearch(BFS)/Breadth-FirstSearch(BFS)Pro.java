import java.util.*;

// Class to represent a graph
class Graph {
    private int V; // Number of vertices
    private LinkedList<Integer> adj[]; // Adjacency list representation

    // Constructor
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

    // Prints BFS traversal from a given source node 's'
    void BFS(int s) {
        // Mark all the vertices as not visited(By default
        // set as false)
        boolean visited[] = new boolean[V];
        // Create a queue for BFS
        LinkedList<Integer> queue = new LinkedList<Integer>();
        // Mark the current node as visited and enqueue it
        visited[s] = true;
        queue.add(s);

        System.out.println("BFS Traversal starting from node " + s + ":"); //Added for better readability
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
        System.out.println(); // Add a newline for better formatting
    }

    // 1. Web Crawler Implementation using BFS
    // Scenario: Crawling a website to discover all linked pages.
    void webCrawl(String startURL, int maxDepth) {
        Set<String> visitedURLs = new HashSet<>();
        Queue<String> queue = new LinkedList<>();
        int depth = 0;

        queue.add(startURL);
        visitedURLs.add(startURL);

        System.out.println("\nWeb Crawl (BFS) starting from: " + startURL + " with max depth: " + maxDepth); // Added

        while (!queue.isEmpty() && depth <= maxDepth) {
            int levelSize = queue.size(); // Process all nodes at the current level
            System.out.println("Depth: " + depth); // display depth
            for (int i = 0; i < levelSize; i++) {
                String currentURL = queue.poll();
                System.out.println("  Crawling: " + currentURL); // Indentation for better visualization

                // Simulate fetching links from the current URL (replace with actual HTTP request logic)
                List<String> links = getLinksFromURL(currentURL); // Assume this method returns a list of links

                for (String link : links) {
                    if (!visitedURLs.contains(link)) {
                        visitedURLs.add(link);
                        queue.add(link);
                        System.out.println("    Found link: " + link); // show the links found
                    }
                }
            }
            depth++;
        }
        System.out.println("Web Crawling complete.");
    }

    // Simulate fetching links from a URL (replace with actual implementation)
    private List<String> getLinksFromURL(String url) {
        // In a real application, this method would use an HTTP client (e.g., Jsoup)
        // to fetch the HTML content of the URL and extract the links.
        // For this example, we'll return a dummy list of links.
        List<String> dummyLinks = new ArrayList<>();
        if (url.equals("https://www.example.com")) {
            dummyLinks.add("https://www.example.com/page1");
            dummyLinks.add("https://www.example.com/page2");
        } else if (url.equals("https://www.example.com/page1")) {
            dummyLinks.add("https://www.example.com/page3");
        } else if (url.equals("https://www.example.com/page2")) {
            dummyLinks.add("https://www.example.com/page4");
        }
        return dummyLinks;
    }


    // 2. Social Network Friend Recommendation using BFS
    // Scenario: Finding friends of friends in a social network.
    void recommendFriends(int user, int degree) {
        boolean[] visited = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();
        int currentDegree = 0;

        queue.add(user);
        visited[user] = true;

        System.out.println("\nFriend Recommendations (BFS) for user " + user + " up to degree " + degree + ":"); // Added

        while (!queue.isEmpty() && currentDegree < degree) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                int currentUser = queue.poll();
                //System.out.println("  Checking friends of: " + currentUser); // Removed to reduce verbosity

                Iterator<Integer> friendIterator = adj[currentUser].listIterator();
                while (friendIterator.hasNext()) {
                    int friend = friendIterator.next();
                    if (!visited[friend]) {
                        visited[friend] = true;
                        queue.add(friend);
                        if (currentDegree == degree -1)
                        {
                            System.out.println("    Recommended friend: " + friend);
                        }

                    }
                }
            }
            currentDegree++;
        }
        System.out.println("Friend recommendation process complete.");
    }

    // 3. Network Routing using BFS
    // Scenario: Finding the shortest path between two nodes in a network.
    void findShortestPath(int start, int end) {
        boolean[] visited = new boolean[V];
        int[] parent = new int[V]; // Store the parent of each node in the shortest path
        Queue<Integer> queue = new LinkedList<>();

        queue.add(start);
        visited[start] = true;
        parent[start] = -1; // Start node has no parent

        System.out.println("\nShortest Path (BFS) from " + start + " to " + end + ":"); // Added

        while (!queue.isEmpty()) {
            int current = queue.poll();
            //System.out.println("  Checking node: " + current); //Removed to reduce verbosity

            if (current == end) {
                break; // Path found, exit the loop
            }

            Iterator<Integer> neighborIterator = adj[current].listIterator();
            while (neighborIterator.hasNext()) {
                int neighbor = neighborIterator.next();
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current; // Store the parent
                    queue.add(neighbor);
                }
            }
        }

        // Reconstruct the path from end to start using the parent array
        if (visited[end]) {
            List<Integer> path = new ArrayList<>();
            for (int at = end; at != -1; at = parent[at]) {
                path.add(at);
            }
            Collections.reverse(path); // Reverse the path to get it from start to end
            System.out.println("    Shortest path: " + path);
        } else {
            System.out.println("    No path exists between " + start + " and " + end);
        }
    }

    // 4. Game Tree Traversal (Finding possible moves)
    // Scenario: Exploring possible moves in a game (e.g., chess, tic-tac-toe).
    void findPossibleMoves(int gameState, int player) {
        boolean[] visited = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();

        queue.add(gameState);
        visited[gameState] = true;

        System.out.println("\nPossible Moves (BFS) for Player " + player + " from Game State " + gameState + ":"); // Added
        int moveNumber = 1; // Added to number the moves

        while (!queue.isEmpty()) {
            int currentGameState = queue.poll();
            //System.out.println("  Analyzing Game State: " + currentGameState); // Removed to reduce verbosity

            // Simulate generating possible next game states (replace with actual game logic)
            List<Integer> possibleMoves = getPossibleMoves(currentGameState, player);

            for (int nextMove : possibleMoves) {
                if (!visited[nextMove]) {
                    visited[nextMove] = true;
                    queue.add(nextMove);
                    System.out.println("    Move " + moveNumber + ": " + nextMove); // Display with move number
                    moveNumber++;
                }
            }
        }
        System.out.println("Possible moves analysis complete.");
    }
    // Simulate generating possible moves in a game
    private List<Integer> getPossibleMoves(int gameState, int player) {
        //  Replace this with actual game logic to generate valid moves
        //  from a given game state for a specific player.  For example,
        //  in Tic-Tac-Toe, you'd calculate the empty cells and create
        //  new game states for each possible move.
        List<Integer> moves = new ArrayList<>();
        if (gameState == 1) { // Example: If the game state is 1, player can make these moves
            if (player == 1)
            {
                moves.add(2);
                moves.add(3);
            }
            else
            {
                moves.add(4);
                moves.add(5);
            }

        } else if (gameState == 2) {
            if (player == 1)
            {
                moves.add(4);
                moves.add(5);
            }
            else
            {
                moves.add(6);
                moves.add(7);
            }
        }
        return moves;
    }

    // 5.  Finding shortest path in a unweighted graph.
    // Scenario: You have a simple graph and want to find the shortest path
    void shortestPathUnweightedGraph(int startNode, int endNode)
    {
        boolean[] visited = new boolean[V];
        int[] parent = new int[V];
        Queue<Integer> queue = new LinkedList<>();

        queue.add(startNode);
        visited[startNode] = true;
        parent[startNode] = -1;

        System.out.println("\nShortest Path in Unweighted Graph (BFS) from " + startNode + " to " + endNode + ":");

        while(!queue.isEmpty())
        {
            int currentNode = queue.poll();
            if(currentNode == endNode)
            {
                break;
            }

            Iterator<Integer> neighborIterator = adj[currentNode].listIterator();
            while(neighborIterator.hasNext())
            {
                int neighbor = neighborIterator.next();
                if(!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parent[neighbor] = currentNode;
                    queue.add(neighbor);
                }
            }
        }

        if(visited[endNode])
        {
            List<Integer> path = new ArrayList<>();
            for(int at = endNode; at != -1; at = parent[at])
            {
                path.add(at);
            }
            Collections.reverse(path);
            System.out.println("   Shortest Path: " + path);
        }
        else{
            System.out.println("   No path exists");
        }
    }
}

// Main class
public class Main {
    public static void main(String args[]) {
        Graph g = new Graph(12); // Increased to 12 for more comprehensive examples.

        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        g.addEdge(2, 0);
        g.addEdge(2, 3);
        g.addEdge(3, 3);
        g.addEdge(3, 4); // Added edge for shortest path
        g.addEdge(4, 5);
        g.addEdge(5, 6);
        g.addEdge(6, 7);
        g.addEdge(7, 8);
        g.addEdge(8, 9);
        g.addEdge(9, 10);
        g.addEdge(10, 11);


        g.BFS(2); // Basic BFS traversal

        // 1. Web Crawler Application
        g.webCrawl("https://www.example.com", 2); // Crawl up to depth 2

        // 2. Social Network Friend Recommendation
        g.recommendFriends(0, 2); // Recommend friends of friends of user 0

        // 3. Network Routing Application
        g.findShortestPath(3, 7); // Find shortest path between node 3 and 7

        // 4. Game Tree Traversal
        g.findPossibleMoves(1, 1);

        // 5. Shortest path in unweighted graph
        g.shortestPathUnweightedGraph(3, 7);
    }
}

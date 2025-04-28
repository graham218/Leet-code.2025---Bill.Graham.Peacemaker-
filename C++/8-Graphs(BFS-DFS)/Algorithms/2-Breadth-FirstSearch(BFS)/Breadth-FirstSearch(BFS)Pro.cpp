#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set> // Added for unordered_set
#include <limits>       // Required for numeric_limits

using namespace std;

// 1. Basic BFS Implementation (Graph Traversal)
//   - Represents a simple graph using an adjacency list.
//   - Performs BFS traversal from a given starting node.
//   - Prints the nodes in the order they are visited.
void basicBFS(const vector<vector<int>>& adjList, int startNode) {
    int numNodes = adjList.size();
    vector<bool> visited(numNodes, false); // Keep track of visited nodes
    queue<int> q;

    // Mark the starting node as visited and enqueue it.
    visited[startNode] = true;
    q.push(startNode);

    cout << "Basic BFS Traversal starting from node " << startNode << ": ";

    while (!q.empty()) {
        // Dequeue a node from the front of the queue.
        int currentNode = q.front();
        q.pop();

        // Print the current node.
        cout << currentNode << " ";

        // Iterate over the neighbors of the current node.
        for (int neighbor : adjList[currentNode]) {
            // If a neighbor has not been visited, mark it as visited and enqueue it.
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// 2. BFS for Shortest Path in an Unweighted Graph
//   - Finds the shortest path from a start node to all other nodes in an unweighted graph.
//   - Uses BFS to guarantee the shortest path (in terms of number of edges).
//   - Stores the distance from the start node to each other node.
void shortestPathBFS(const vector<vector<int>>& adjList, int startNode, vector<int>& distances) {
    int numNodes = adjList.size();
    distances.assign(numNodes, -1); // Initialize distances to -1 (unreachable)
    queue<int> q;

    // The distance to the start node from itself is 0.
    distances[startNode] = 0;
    q.push(startNode);

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int neighbor : adjList[currentNode]) {
            if (distances[neighbor] == -1) { // If the neighbor is not visited
                distances[neighbor] = distances[currentNode] + 1; // Distance is one more than current
                q.push(neighbor);
            }
        }
    }
    // Note: nodes unreachable from startNode will have distance of -1.
}

// 3. BFS for Finding Connected Components in a Graph
//   - Identifies the different connected components in an undirected graph.
//   - Uses BFS to explore all nodes reachable from a starting node.
//   - Assigns a component ID to each node.
void findConnectedComponents(const vector<vector<int>>& adjList, vector<int>& componentIds) {
    int numNodes = adjList.size();
    componentIds.assign(numNodes, -1); // Initialize component IDs to -1 (unassigned)
    int numComponents = 0;

    for (int startNode = 0; startNode < numNodes; ++startNode) {
        if (componentIds[startNode] == -1) { // If the node hasn't been assigned to a component yet
            numComponents++; // Start a new component
            queue<int> q;
            q.push(startNode);
            componentIds[startNode] = numComponents; // Assign component ID

            while (!q.empty()) {
                int currentNode = q.front();
                q.pop();

                for (int neighbor : adjList[currentNode]) {
                    if (componentIds[neighbor] == -1) {
                        componentIds[neighbor] = numComponents; // Assign the same component ID
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    cout << "Number of connected components: " << numComponents << endl;
}

// 4. BFS with Custom Node Structure (e.g., for a grid)
//    - Demonstrates BFS on a grid (represented as a 2D vector).
//    - Uses a custom `Node` struct to store coordinates and additional information.
//    - Useful for pathfinding in games or image processing.
struct Node {
    int x;
    int y;
    int distance; // Example of additional information
};

void gridBFS(const vector<vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Node> q;

    // Check if start and target are within bounds
    if (startX < 0 || startX >= rows || startY < 0 || startY >= cols ||
        targetX < 0 || targetX >= rows || targetY < 0 || targetY >= cols) {
        cout << "Start or target coordinates are out of bounds." << endl;
        return;
    }
    if (grid[startX][startY] == -1 || grid[targetX][targetY] == -1) {
        cout << "Start or target is blocked." << endl;
        return;
    }

    Node startNode = {startX, startY, 0};
    visited[startX][startY] = true;
    q.push(startNode);

    // Define possible движения (up, down, left, right)
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        Node currentNode = q.front();
        q.pop();

        if (currentNode.x == targetX && currentNode.y == targetY) {
            cout << "Found target at (" << targetX << ", " << targetY << ") with distance "
                 << currentNode.distance << endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = currentNode.x + dx[i];
            int newY = currentNode.y + dy[i];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                !visited[newX][newY] && grid[newX][newY] != -1) { // -1 represents a blocked cell
                visited[newX][newY] = true;
                Node nextNode = {newX, newY, currentNode.distance + 1};
                q.push(nextNode);
            }
        }
    }
    cout << "Target is not reachable." << endl;
}

// 5. BFS for Web Crawler (Simplified)
//    - Simulates a simplified web crawler.
//    - Takes a starting URL and explores linked URLs (represented as an adjacency list).
//    - Uses a hash set (unordered_set) to keep track of visited URLs to avoid cycles.
//    - Uses a queue to manage the URLs to crawl.
void webCrawlerBFS(const unordered_map<string, vector<string>>& urlGraph, const string& startURL) {
    unordered_set<string> visitedURLs;
    queue<string> q;

    visitedURLs.insert(startURL);
    q.push(startURL);

    cout << "Web Crawler starting from URL: " << startURL << endl;

    while (!q.empty()) {
        string currentURL = q.front();
        q.pop();

        cout << "Crawling URL: " << currentURL << endl;

        // Simulate fetching linked URLs (neighbors in the graph)
        auto it = urlGraph.find(currentURL);
        if (it != urlGraph.end()) {
            for (const string& linkedURL : it->second) {
                if (visitedURLs.find(linkedURL) == visitedURLs.end()) {
                    visitedURLs.insert(linkedURL);
                    q.push(linkedURL);
                }
            }
        }
        // In a real web crawler, you would fetch the HTML of the page
        // and extract the links.  This is a simplified example.
    }
    cout << "Finished crawling." << endl;
}

int main() {
    // Example graph represented as an adjacency list.
    // Node connections are 0-indexed.
    vector<vector<int>> adjList = {
        {1, 2},    // Node 0 is connected to 1 and 2
        {0, 3, 4}, // Node 1 is connected to 0, 3, and 4
        {0, 4},    // Node 2 is connected to 0 and 4
        {1},       // Node 3 is connected to 1
        {1, 2},    // Node 4 is connected to 1 and 2
    };

    // 1. Basic BFS Traversal
    basicBFS(adjList, 0); // Start BFS from node 0

    // 2. Shortest Path BFS
    vector<int> distances;
    shortestPathBFS(adjList, 0, distances);
    cout << "Shortest distances from node 0:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }

    // 3. Connected Components
    vector<int> componentIds;
    findConnectedComponents(adjList, componentIds);
    cout << "Component IDs:" << endl;
    for (int i = 0; i < componentIds.size(); ++i) {
        cout << "Node " << i << ": Component " << componentIds[i] << endl;
    }

    // Example Grid for BFS (0: open, -1: blocked)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, -1, 0, -1, 0},
        {0, 0, 0, 0, 0},
        {0, -1, -1, -1, 0},
        {0, 0, 0, 0, 0},
    };
    // 4. Grid BFS
    gridBFS(grid, 0, 0, 4, 4); // Find path from (0,0) to (4,4)

    // 5. Web Crawler BFS (Simplified)
    unordered_map<string, vector<string>> urlGraph = {
        {"https://www.example.com", {"https://www.example.com/about", "https://www.example.com/contact"}},
        {"https://www.example.com/about", {"https://www.example.com"}},
        {"https://www.example.com/contact", {}},
    };
    webCrawlerBFS(urlGraph, "https://www.example.com");

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm> // Added for std::reverse
#include <numeric>   // For iota

using namespace std;

// 1. Breadth-First Search (BFS) - Shortest Path in a Social Network
//
//   * Problem: Find the shortest path between two users in a social network.
//   * Application: Calculating degrees of separation (e.g., "Six Degrees of Kevin Bacon").
//   * Data Structure: Adjacency list for the graph, queue for BFS traversal.
void bfs(const vector<vector<int>>& graph, int start, int end, vector<int>& distances, vector<int>& previous) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;

    // Initialize starting node
    visited[start] = true;
    distances[start] = 0;
    q.push(start);
    previous[start] = -1; // No previous node for the start node

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            break; // Stop if the target node is found
        }

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[current] + 1;
                previous[neighbor] = current; // Store the path
                q.push(neighbor);
            }
        }
    }
}

// Function to reconstruct the shortest path
vector<int> reconstructPath(int start, int end, const vector<int>& previous) {
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end()); // Reverse to get the correct order
    if (path[0] != start) {
        return {}; // Return empty path if no path exists.
    }
    return path;
}

void shortestPathSocialNetwork() {
    // Example graph representing a small social network
    //  0---1---2
    //  |   |
    //  3---4---5
    vector<vector<int>> graph = {
        {1, 3},    // 0
        {0, 2, 4}, // 1
        {1, 5},    // 2
        {0, 4},    // 3
        {1, 3, 5}, // 4
        {2, 4}     // 5
    };

    int numNodes = graph.size();
    vector<int> distances(numNodes, -1); // -1 indicates not visited
    vector<int> previous(numNodes, -1);
    int startUser = 0;
    int endUser = 5;

    bfs(graph, startUser, endUser, distances, previous);

    if (distances[endUser] != -1) {
        cout << "Shortest path between user " << startUser << " and " << endUser << ":\n";
        vector<int> path = reconstructPath(startUser, endUser, previous);
        for (int node : path) {
            cout << node << " ";
        }
        cout << "\nDistance: " << distances[endUser] << endl;
    } else {
        cout << "No path found between user " << startUser << " and " << endUser << endl;
    }
    cout << "--------------------------------------\n";
}

// 2. Depth-First Search (DFS) - Topological Sort for Task Scheduling
//
//   * Problem: Determine a valid order to execute tasks with dependencies.
//   * Application: Course scheduling, build systems (e.g., makefiles).
//   * Data Structure: Adjacency list for the directed graph, stack for DFS traversal.

void dfs(const vector<vector<int>>& graph, int start, vector<bool>& visited, stack<int>& stack) {
    visited[start] = true;
    for (int neighbor : graph[start]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited, stack);
        }
    }
    stack.push(start); // Push the node onto the stack AFTER visiting its neighbors
}

void topologicalSort(const vector<vector<int>>& graph, vector<int>& result) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    stack<int> stack;

    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }

    // Pop nodes from the stack to get the topological order
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }
}

void taskScheduling() {
    // Example graph representing task dependencies
    //  0 -> 1 -> 2
    //  |    |
    //  v    v
    //  3 -> 4
    vector<vector<int>> graph = {
        {1, 3}, // 0
        {2, 4}, // 1
        {},    // 2
        {4},    // 3
        {}     // 4
    };

    vector<int> sortedTasks;
    topologicalSort(graph, sortedTasks);

    cout << "Task scheduling order (Topological Sort): ";
    if (sortedTasks.size() == graph.size()) {
        for (int task : sortedTasks) {
            cout << task << " ";
        }
    } else {
        cout << "Cycle detected. No valid task order exists.";
    }

    cout << "\n--------------------------------------\n";
}

// 3. Union-Find (Disjoint Set Union) - Network Connectivity
//
//   * Problem: Determine if two computers are in the same network.
//   * Application: Network connection management, Kruskal's algorithm for Minimum Spanning Tree.
//   * Data Structure: Array to represent the parent of each node (node's representative).

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank; // Optional: Used for optimization (union by rank)

    UnionFind(int n) : parent(n), rank(n, 0) {
        // Initialize each node as its own parent (singleton set)
        iota(parent.begin(), parent.end(), 0); // Sets parent[i] = i for all i
    }

    // Find the representative of the set that 'node' belongs to (with path compression)
    int find(int node) {
        if (node == parent[node]) {
            return node;
        }
        // Path compression: update the parent of 'node' to point directly to the root
        return parent[node] = find(parent[node]);
    }

    // Unite the sets containing 'node1' and 'node2'
    void unite(int node1, int node2) {
        int root1 = find(node1);
        int root2 = find(node2);

        if (root1 != root2) {
            // Union by rank (optional optimization)
            if (rank[root1] < rank[root2]) {
                parent[root1] = root2;
            } else if (rank[root1] > rank[root2]) {
                parent[root2] = root1;
            } else {
                parent[root2] = root1;
                rank[root1]++; // Increment rank if ranks are equal
            }
        }
    }

    // Check if two nodes are connected
    bool isConnected(int node1, int node2) {
        return find(node1) == find(node2);
    }
};

void networkConnectivity() {
    int numComputers = 6;
    UnionFind uf(numComputers);

    // Simulate network connections
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(1, 2); // Connects 0,1,2,3

    cout << "Network Connectivity:\n";
    cout << "Computer 0 and 3 are connected: " << (uf.isConnected(0, 3) ? "true" : "false") << endl; // true
    cout << "Computer 0 and 4 are connected: " << (uf.isConnected(0, 4) ? "true" : "false") << endl; // false
    cout << "Computer 2 and 5 are connected: " << (uf.isConnected(2, 5) ? "true" : "false") << endl; // false
    cout << "Computer 4 and 5 are connected: " << (uf.isConnected(4, 5) ? "true" : "false") << endl; // true
    cout << "--------------------------------------\n";
}

// 4.  BFS - Web Crawler
//
//    * Problem: Crawl a website to collect all accessible links.
//    * Application: Search engine indexing, data mining.
//    * Data Structure: Adjacency list (implicit, based on discovered links), queue for BFS.
//    * Simplification:  Simulating link discovery within a small, predefined set of pages.
void webCrawler() {
    // Simplified website representation (adjacency list)
    //  0: "home.html"
    //  1: "about.html"
    //  2: "services.html"
    //  3: "contact.html"
    //  4: "products.html"

    vector<vector<int>> website = {
        {1, 2},       // home.html links to about.html and services.html
        {0, 3},       // about.html links to home.html and contact.html
        {0, 4},       // services.html links to home.html and products.html
        {1},         // contact.html links to about.html
        {2}          // products.html links to services.html
    };
    vector<string> pageNames = {"home.html", "about.html", "services.html", "contact.html", "products.html"};
    int startPage = 0; // Start crawling from home.html
    int numPages = website.size();
    vector<bool> visited(numPages, false);
    queue<int> q;

    visited[startPage] = true;
    q.push(startPage);

    cout << "Web Crawler starting from " << pageNames[startPage] << ":\n";

    while (!q.empty()) {
        int currentPage = q.front();
        q.pop();

        cout << "Crawling page: " << pageNames[currentPage] << endl;

        for (int linkedPage : website[currentPage]) {
            if (!visited[linkedPage]) {
                visited[linkedPage] = true;
                q.push(linkedPage);
            }
        }
    }
    cout << "--------------------------------------\n";
}

// 5. DFS - Maze Solver
//
//   * Problem: Find a path from the start to the end of a maze.
//   * Application: Robotics navigation, game development.
//   * Data Structure: 2D vector (or array) to represent the maze, stack for DFS.

bool dfsMaze(vector<vector<int>>& maze, int row, int col, int endRow, int endCol, vector<pair<int, int>>& path) {
    int numRows = maze.size();
    int numCols = maze[0].size();

    // Base cases:
    if (row < 0 || row >= numRows || col < 0 || col >= numCols || maze[row][col] == 1) {
        return false; // Out of bounds or wall
    }
    if (row == endRow && col == endCol) {
        path.push_back({row, col});
        return true; // Found the end
    }

    maze[row][col] = 1; // Mark as visited (1 is wall, for simplicity)
    path.push_back({row, col});

    // Explore neighbors: up, down, left, right
    if (dfsMaze(maze, row - 1, col, endRow, endCol, path) ||
        dfsMaze(maze, row + 1, col, endRow, endCol, path) ||
        dfsMaze(maze, row, col - 1, endRow, endCol, path) ||
        dfsMaze(maze, row, col + 1, endRow, endCol, path)) {
        return true;
    }

    path.pop_back(); // Dead end, remove from path
    return false;
}

void mazeSolver() {
    // Example maze: 0 = path, 1 = wall
    vector<vector<int>> maze = {
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };

    int startRow = 0;
    int startCol = 0;
    int endRow = 6;
    int endCol = 6;
    vector<pair<int, int>> path;

    if (dfsMaze(maze, startRow, startCol, endRow, endCol, path)) {
        cout << "Path found in the maze:\n";
        for (const auto& cell : path) {
            cout << "(" << cell.first << ", " << cell.second << ") -> ";
        }
        cout << "End\n";
    } else {
        cout << "No path found in the maze.\n";
    }
    cout << "--------------------------------------\n";
}

int main() {
    shortestPathSocialNetwork();
    taskScheduling();
    networkConnectivity();
    webCrawler();
    mazeSolver();

    return 0;
}

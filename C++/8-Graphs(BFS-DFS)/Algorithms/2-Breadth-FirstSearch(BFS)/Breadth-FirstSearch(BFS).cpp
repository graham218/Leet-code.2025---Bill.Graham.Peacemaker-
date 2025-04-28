#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm> // Required for std::find

using namespace std;

// Structure to represent a graph using an adjacency list.
struct Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list representation

    // Constructor for the Graph struct.
    Graph(int vertices) : V(vertices), adjList(vertices) {}

    // Function to add an edge to the graph.
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Assuming an undirected graph
    }
};

// 1. Standard BFS Implementation using a queue.
void bfsStandard(const Graph& graph, int startVertex) {
    vector<bool> visited(graph.V, false); // Keep track of visited vertices.
    queue<int> q; // Queue for BFS traversal.

    visited[startVertex] = true; // Mark the start vertex as visited.
    q.push(startVertex); // Enqueue the start vertex.

    cout << "BFS (Standard): ";
    while (!q.empty()) {
        int currentVertex = q.front(); // Get the front vertex from the queue.
        q.pop(); // Dequeue the front vertex.
        cout << currentVertex << " "; // Print the current vertex.

        // Iterate through the neighbors of the current vertex.
        for (int neighbor : graph.adjList[currentVertex]) {
            if (!visited[neighbor]) { // If the neighbor is not visited.
                visited[neighbor] = true; // Mark the neighbor as visited.
                q.push(neighbor); // Enqueue the neighbor.
            }
        }
    }
    cout << endl;
}

// 2. BFS with Path Reconstruction.  This version keeps track of the path
//    from the start vertex to each other vertex.
void bfsWithPath(const Graph& graph, int startVertex, int targetVertex) {
    vector<bool> visited(graph.V, false);
    queue<int> q;
    vector<int> parent(graph.V, -1); // Store the parent of each node in the BFS traversal.

    visited[startVertex] = true;
    q.push(startVertex);

    bool foundTarget = false; // Flag to indicate if the target is found.

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        if (currentVertex == targetVertex) {
            foundTarget = true;
            break; // Stop BFS if target is found
        }

        for (int neighbor : graph.adjList[currentVertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = currentVertex; // Store how we got to this neighbor.
                q.push(neighbor);
            }
        }
    }

    if (foundTarget) {
        cout << "BFS (Path to " << targetVertex << "): ";
        vector<int> path;
        // Reconstruct the path from target to start
        for (int at = targetVertex; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end()); // Reverse to get path from start to target.
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "BFS (Path): Target vertex " << targetVertex << " not reachable from "
             << startVertex << endl;
    }
}

// 3. BFS with Level Tracking.  This version keeps track of the level (distance)
//    of each node from the start vertex.
void bfsWithLevel(const Graph& graph, int startVertex) {
    vector<bool> visited(graph.V, false);
    queue<pair<int, int>> q; // Store vertex and its level
    vector<int> level(graph.V, -1);     // Initialize levels to -1

    visited[startVertex] = true;
    level[startVertex] = 0;
    q.push({startVertex, 0});

    cout << "BFS (Level):" << endl;
    while (!q.empty()) {
        int currentVertex = q.front().first;
        int currentLevel = q.front().second;
        q.pop();
        cout << "Vertex " << currentVertex << " at level " << currentLevel << endl;

        for (int neighbor : graph.adjList[currentVertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                level[neighbor] = currentLevel + 1; // Increment level
                q.push({neighbor, currentLevel + 1});
            }
        }
    }
}

// 4. BFS using an iterator for adjacency list traversal.  This is functionally
//    the same as the standard BFS, but uses iterators.
void bfsWithIterator(const Graph& graph, int startVertex) {
    vector<bool> visited(graph.V, false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    cout << "BFS (Iterator): ";
    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        // Use iterators to traverse the adjacency list.
        for (auto it = graph.adjList[currentVertex].begin(); it != graph.adjList[currentVertex].end(); ++it) {
            int neighbor = *it;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// 5. BFS with Early Exit.  This version of BFS allows you to stop the search
//    early if you find the target vertex.
void bfsEarlyExit(const Graph& graph, int startVertex, int targetVertex) {
    vector<bool> visited(graph.V, false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    cout << "BFS (Early Exit): ";
    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        if (currentVertex == targetVertex) {
            cout << "(Target Found!)" << endl;
            return; // Exit the function early
        }

        for (int neighbor : graph.adjList[currentVertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl; // If targetVertex was not found.
}

int main() {
    // Create a graph with 6 vertices (0 to 5).
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    int startVertex = 0;
    int targetVertex = 5; // For the path reconstruction and early exit examples.

    // Perform BFS using the different approaches.
    bfsStandard(g, startVertex);
    bfsWithPath(g, startVertex, targetVertex);
    bfsWithLevel(g, startVertex);
    bfsWithIterator(g, startVertex);
    bfsEarlyExit(g, startVertex, targetVertex);

    return 0;
}

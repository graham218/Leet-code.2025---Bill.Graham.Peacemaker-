#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <functional> // Include the <functional> header

using namespace std;

// A structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// 1. Bellman-Ford Algorithm - Basic Implementation
//   -  Finds the shortest paths from a single source vertex to all other vertices in a weighted graph.
//   -  Works with negative edge weights.
//   -  Detects negative weight cycles.
void bellmanFordBasic(int V, int E, vector<Edge>& edges, int src) {
    // Initialize distances to all vertices as INFINITE, except for the source vertex.
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax all edges |V| - 1 times. A simple shortest path can have at most |V| - 1 edges.
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative weight cycles.  If we get a shorter path after |V|-1 iterations, there is a negative weight cycle.
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return; // Exit if a negative cycle is detected.  Important for correctness.
        }
    }

    // Print the shortest distances from the source vertex.
    cout << "Vertex   Distance from Source (Basic)" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "          " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 2. Bellman-Ford with Early Termination
//    - Optimized version that terminates if no changes occur in an iteration.
//    - Can be significantly faster for graphs without negative weight cycles.
void bellmanFordEarlyTermination(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    bool updated; // Flag to check if any distance was updated in an iteration

    for (int i = 1; i <= V - 1; i++) {
        updated = false; // Reset the flag for each iteration
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                updated = true; // Set flag to true if a distance is updated
            }
        }
        if (!updated) // If no updates occurred, we've found the shortest paths
            break;
    }

    // Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Vertex   Distance from Source (Early Termination)" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "          " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 3. Bellman-Ford with Path Reconstruction
//    -  Stores the predecessor of each vertex in the shortest path.
//    -  Allows reconstructing the shortest path from the source to any vertex.
void bellmanFordWithPathReconstruction(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    vector<int> parent(V, -1); // Array to store the predecessor of each vertex

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Store the predecessor
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Vertex   Distance from Source (Path Reconstruction)" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "          " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }

    // Function to print the shortest path from source to a given vertex
    function<void(int)> printPath = [&](int v) {  // Fix: Added std::
        if (v == -1) return;
        printPath(parent[v]);
        cout << v << " ";
    };

    // Print shortest paths for each vertex
    for (int i = 0; i < V; i++) {
        cout << "Path from " << src << " to " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "No path" << endl;
        } else {
            printPath(i);
            cout << endl;
        }
    }
}

// 4. Bellman-Ford for Large Graphs (Optimization for Sparse Graphs)
//    - Uses an adjacency list representation, which can be more efficient for sparse graphs.
//    - Uses a queue to process vertices, similar to Dijkstra's algorithm, but still works with negative weights.
void bellmanFordSparse(int V, vector<vector<pair<int, int>>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    vector<int> count(V, 0); // To detect negative cycles
    queue<int> q;
    vector<bool> inQueue(V, false); // Keep track of vertices in the queue

    q.push(src);
    inQueue[src] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        count[u]++; // Increment the count of times vertex u is processed

        if (count[u] > V - 1) {
            cout << "Graph contains negative weight cycle (Sparse)" << endl;
            return;
        }

        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    cout << "Vertex   Distance from Source (Sparse)" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "          " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 5. Bellman-Ford with Fixed-Point Iteration (Application in Network Routing)
//    - Demonstrates how Bellman-Ford's principle can be applied in a distributed setting.
//    - Simulates a simplified distance-vector routing protocol.
//    - Each node iteratively updates its distance estimates based on neighbors.
void distanceVectorRouting(int V, vector<vector<pair<int, int>>>& adj, int maxIterations = 100) {
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX)); // dist[i][j] is the distance from i to j
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0; // Distance to itself is 0
    }

    // Initialize distances based on direct neighbors
    for (int i = 0; i < V; i++) {
        for (auto& neighbor : adj[i]) {
            int j = neighbor.first;
            int weight = neighbor.second;
            dist[i][j] = weight;
        }
    }

    // Iteratively update distance vectors
    for (int iteration = 0; iteration < maxIterations; iteration++) {
        bool updated = false;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) { // For each destination j
                if (i == j) continue;
                int min_dist = INT_MAX;
                for (auto& neighbor : adj[i]) {
                    int k = neighbor.first; // Neighbor k
                    if (dist[k][j] != INT_MAX) {
                        min_dist = min(min_dist, neighbor.second + dist[k][j]);
                    }
                }
                if (min_dist != INT_MAX && dist[i][j] > min_dist) {
                    dist[i][j] = min_dist;
                    updated = true;
                }
            }
        }
        if (!updated) break; // Stop if no changes
    }

    // Output the distance vectors for each node
    cout << "Distance Vectors (Network Routing)" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << ": ";
        for (int j = 0; j < V; j++) {
            cout << "To " << j << ": " << (dist[i][j] == INT_MAX ? "INF" : to_string(dist[i][j])) << "  ";
        }
        cout << endl;
    }
}

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges

    // Example graph represented as a vector of edges
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    int src = 0; // Source vertex

    // 1. Basic Bellman-Ford
    bellmanFordBasic(V, E, edges, src);
    cout << endl;

    // 2. Bellman-Ford with Early Termination
    bellmanFordEarlyTermination(V, E, edges, src);
    cout << endl;

    // 3. Bellman-Ford with Path Reconstruction
    bellmanFordWithPathReconstruction(V, E, edges, src);
    cout << endl;

    // 4. Bellman-Ford for Sparse Graphs (Adjacency List Representation)
    vector<vector<pair<int, int>>> adj(V);
    for (auto& edge : edges) {
        adj[edge.src].push_back({edge.dest, edge.weight});
    }
    bellmanFordSparse(V, adj, src);
    cout << endl;

    // 5. Distance Vector Routing Example
    //    - Adjacency list representing network topology with link costs
     vector<vector<pair<int, int>>> networkAdj = {
        {{1, 2}, {2, 6}},       // Node 0: Neighbors 1 (cost 2), 2 (cost 6)
        {{0, 2}, {2, 3}, {3, 5}},  // Node 1: Neighbors 0 (cost 2), 2 (cost 3), 3 (cost 5)
        {{0, 6}, {1, 3}, {3, 3}, {4, 7}},  // Node 2
        {{1, 5}, {2, 3}, {4, 4}},  // Node 3
        {{2, 7}, {3, 4}}       // Node 4
    };
    distanceVectorRouting(networkAdj.size(), networkAdj);

    return 0;
}


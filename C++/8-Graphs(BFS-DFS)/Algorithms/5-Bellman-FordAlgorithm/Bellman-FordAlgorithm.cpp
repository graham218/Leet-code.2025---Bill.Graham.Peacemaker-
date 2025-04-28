#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <functional> // Include for std::function
#include <limits>     // Include for std::numeric_limits

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// 1. Basic Bellman-Ford Algorithm
//   - Straightforward implementation.
//   - Detects negative cycles.
void bellmanFordBasic(int V, int E, vector<Edge>& edges, int source) {
    // Initialize distances to all vertices as INFINITE, except for the source vertex.
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // Relax edges repeatedly |V| - 1 times. A simple shortest path can have at most |V| - 1 edges.
    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
            }
        }
    }

    // Check for negative-weight cycles.  If we get a shorter path after |V|-1 iterations, there is a negative cycle.
    for (const auto& edge : edges) {
        if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
            cout << "Graph contains negative weight cycle" << endl;
            return; // Exit if a negative cycle is detected.  Important to prevent incorrect results.
        }
    }

    // Print the calculated shortest distances from the source vertex.
    cout << "Shortest distances from source " << source << " (Basic):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 2. Bellman-Ford with Early Termination
//    - Stops if no distance is updated in an iteration.
//    - Can be faster for graphs without negative cycles.
void bellmanFordEarlyStop(int V, int E, vector<Edge>& edges, int source) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    bool updated;

    for (int i = 1; i <= V - 1; ++i) {
        updated = false; // Flag to check if any distance was updated in this iteration
        for (const auto& edge : edges) {
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
                updated = true; // Set flag to true if a distance is updated
            }
        }
        if (!updated) // If no updates, we've found the shortest paths
            break;
    }

    // Check for negative cycles
    for (const auto& edge : edges) {
        if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Shortest distances from source " << source << " (Early Stop):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 3. Bellman-Ford with Path Reconstruction
//    - Stores the predecessor of each vertex in the shortest path.
//    - Allows reconstructing the path from source to any vertex.
void bellmanFordWithPath(int V, int E, vector<Edge>& edges, int source) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    vector<int> parent(V, -1); // Array to store the parent of each vertex in the shortest path

    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
                parent[edge.dest] = edge.src; // Store the parent vertex
            }
        }
    }

    // Check for negative cycles
    for (const auto& edge : edges) {
        if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Shortest distances from source " << source << " (With Path):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }

    // Function to print the shortest path from source to a given vertex
    function<void(int)> printPath = [&](int v) {
        if (v == -1) return;
        printPath(parent[v]);
        cout << v << " ";
    };

    // Print shortest paths for each vertex
    for (int i = 0; i < V; ++i) {
        cout << "Path to vertex " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "No path" << endl;
        } else {
            printPath(i);
            cout << endl;
        }
    }
}

// 4. Bellman-Ford for a Specific Destination
//    - Stops calculation as soon as the shortest distance to a destination is found.
//    - Useful when only interested in the shortest path to a particular node.
void bellmanFordForDestination(int V, int E, vector<Edge>& edges, int source, int destination) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        bool updated = false;
        for (const auto& edge : edges) {
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
                updated = true;
            }
        }
        if (!updated)
            break;
        if (dist[destination] != INT_MAX) // Stop if destination distance is finalized
            break;
    }

    // Check for negative cycles, even if we stopped early.
     for (const auto& edge : edges) {
        if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }
    cout << "Shortest distance from source " << source << " to destination " << destination << " (For Destination):" << endl;
    cout << (dist[destination] == INT_MAX ? "INF" : to_string(dist[destination])) << endl;
}

// 5. Bellman-Ford with Floating Point Weights
//    - Handles floating-point edge weights.  Uses a tolerance for comparisons.
void bellmanFordFloat(int V, int E, vector<pair<pair<int, int>, double>>& edges, int source) {
    vector<double> dist(V, numeric_limits<double>::infinity());
    dist[source] = 0.0;
    const double EPSILON = 1e-6; // Tolerance for floating-point comparisons

    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge.first.first;
            int v = edge.first.second;
            double weight = edge.second;
            if (dist[u] != numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative cycles using the tolerance
    for (const auto& edge : edges) {
        int u = edge.first.first;
        int v = edge.first.second;
        double weight = edge.second;
        if (dist[u] != numeric_limits<double>::infinity() && dist[u] + weight < dist[v] - EPSILON) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Shortest distances from source " << source << " (Floating Point):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == numeric_limits<double>::infinity() ? "INF" : to_string(dist[i])) << endl;
    }
}

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges

    // Example graph represented as a vector of edges.  Each edge has a source, destination, and weight.
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    int source = 0; // Source vertex for the shortest path calculations.

    // 1. Basic Bellman-Ford
    bellmanFordBasic(V, E, edges, source);
    cout << endl;

    // 2. Bellman-Ford with Early Termination
    bellmanFordEarlyStop(V, E, edges, source);
    cout << endl;

    // 3. Bellman-Ford with Path Reconstruction
    bellmanFordWithPath(V, E, edges, source);
    cout << endl;

    // 4. Bellman-Ford for a Specific Destination
    int destination = 4;
    bellmanFordForDestination(V, E, edges, source, destination);
    cout << endl;

    // 5. Bellman-Ford with Floating Point Weights
    //    Example with floating-point weights.  Using a different edge representation.
    vector<pair<pair<int, int>, double>> floatEdges = {
        {{0, 1}, -1.0}, {{0, 2}, 4.2}, {{1, 2}, 3.5}, {{1, 3}, 2.0},
        {{1, 4}, 2.1}, {{3, 2}, 5.3}, {{3, 1}, 1.0}, {{4, 3}, -3.1}
    };
    bellmanFordFloat(V, E, floatEdges, source);
    cout << endl;

    return 0;
}

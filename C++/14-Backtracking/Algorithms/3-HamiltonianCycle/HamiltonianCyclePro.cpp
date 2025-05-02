#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>   // For iota
#include <limits>    // For numeric_limits
#include <chrono>    // For timing
#include <random>    // For std::mt19937 and std::uniform_int_distribution

using namespace std;
using namespace std::chrono;

// Function to check if a given vertex 'v' can be added to the current path
bool isSafe(int v, vector<int>& path, vector<vector<int>>& graph, int pos) {
    // Check if the vertex 'v' is adjacent to the last vertex in the path.
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if the vertex 'v' is already present in the current path.
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// 1. Basic Backtracking Approach
//   - Recursively explores all possible paths.
//   - Returns true if a Hamiltonian Cycle exists, otherwise false.
bool hamiltonianCycleBasic(vector<vector<int>>& graph, vector<int>& path, int pos) {
    int V = graph.size();

    // Base case: If all vertices are included in the path
    if (pos == V) {
        // Check if there is an edge from the last vertex to the starting vertex.
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next vertex in the path.
    for (int v = 0; v < V; v++) {
        if (isSafe(v, path, graph, pos)) {
            path[pos] = v;
            // Recursively explore the remaining path.
            if (hamiltonianCycleBasic(graph, path, pos + 1))
                return true;
            // Backtrack: If adding vertex 'v' doesn't lead to a solution, remove it.
            path[pos] = -1;
        }
    }

    // If no vertex can be added to the path, return false.
    return false;
}

// Function to find a Hamiltonian Cycle using the basic backtracking approach.
bool findHamiltonianCycleBasic(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1); // Initialize path with -1 (no vertex assigned)
    path[0] = 0;             // Start the path from vertex 0

    // Start the recursion from the second vertex (index 1 in path).
    if (hamiltonianCycleBasic(graph, path, 1) == false) {
        cout << "Hamiltonian Cycle does not exist (Basic)." << endl;
        return false;
    } else {
        cout << "Hamiltonian Cycle found (Basic): ";
        for (int vertex : path)
            cout << vertex << " ";
        cout << path[0] << endl; // Print the starting vertex to complete the cycle.
        return true;
    }
}

// 2. Backtracking with Forward Checking
//    - Improves basic backtracking by checking future possibilities.
//    - If a vertex has no unvisited neighbors, the current path is invalid.
bool hamiltonianCycleForwardChecking(vector<vector<int>>& graph, vector<int>& path, int pos, vector<bool>& visited) {
    int V = graph.size();

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    for (int v = 0; v < V; v++) {
        if (isSafe(v, path, graph, pos) && !visited[v]) {
            // Forward checking:
            // Check if adding 'v' will leave any unvisited node with no path
            bool valid = true;
            visited[v] = true; // Mark v as visited for the check
            int unvisitedCount = 0;
            for (int u = 0; u < V; ++u) {
                if (!visited[u]) {
                    unvisitedCount++;
                    bool hasNeighbor = false;
                    for (int neighbor = 0; neighbor < V; ++neighbor) {
                        if (graph[u][neighbor] == 1 && !visited[neighbor]) {
                            hasNeighbor = true;
                            break;
                        }
                    }
                    if (!hasNeighbor) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid) {
                path[pos] = v;
                if (hamiltonianCycleForwardChecking(graph, path, pos + 1, visited))
                    return true;
                path[pos] = -1;
            }
            visited[v] = false; // backtrack
        }
    }
    return false;
}

bool findHamiltonianCycleForwardChecking(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    path[0] = 0;
    vector<bool> visited(V, false);
    visited[0] = true;

    if (hamiltonianCycleForwardChecking(graph, path, 1, visited) == false) {
        cout << "Hamiltonian Cycle does not exist (Forward Checking)." << endl;
        return false;
    } else {
        cout << "Hamiltonian Cycle found (Forward Checking): ";
        for (int vertex : path)
            cout << vertex << " ";
        cout << path[0] << endl;
        return true;
    }
}

// 3. Backtracking with Degree Ordering
//    - Prioritizes vertices with higher degrees.
//    - Improves performance in some graphs by exploring more promising paths first.
bool hamiltonianCycleDegreeOrdering(vector<vector<int>>& graph, vector<int>& path, int pos, vector<bool>& visited, vector<int>& degree) {
    int V = graph.size();

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Create a vector of unvisited vertices with their degrees.
    vector<pair<int, int>> unvisitedVertices; // (vertex, degree)
    for (int v = 0; v < V; ++v) {
        if (!visited[v] && isSafe(v, path, graph, pos)) { // Added isSafe check here
            unvisitedVertices.push_back({v, degree[v]});
        }
    }
    // Sort unvisited vertices in descending order of their degrees.
    sort(unvisitedVertices.begin(), unvisitedVertices.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (const auto& vertexDegreePair : unvisitedVertices) {
        int v = vertexDegreePair.first;
        if (isSafe(v, path, graph, pos)) { // Check if it is safe to visit the node.
            path[pos] = v;
            visited[v] = true;
            if (hamiltonianCycleDegreeOrdering(graph, path, pos + 1, visited, degree))
                return true;
            path[pos] = -1;
            visited[v] = false;
        }
    }
    return false;
}

bool findHamiltonianCycleDegreeOrdering(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    path[0] = 0;
    vector<bool> visited(V, false);
    visited[0] = true;
    vector<int> degree(V, 0);

    // Calculate the degree of each vertex.
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            degree[i] += graph[i][j];
        }
    }

    if (hamiltonianCycleDegreeOrdering(graph, path, 1, visited, degree) == false) {
        cout << "Hamiltonian Cycle does not exist (Degree Ordering)." << endl;
        return false;
    } else {
        cout << "Hamiltonian Cycle found (Degree Ordering): ";
        for (int vertex : path)
            cout << vertex << " ";
        cout << path[0] << endl;
        return true;
    }
}

// 4. Backtracking with Warnsdorff's Rule (for Knight's Tour) - Adapted for Hamiltonian Cycle
//    - Originally for Knight's Tour, but adapted to prioritize vertices with fewer neighbors.
//    - May not guarantee a solution for all graphs, but often performs well in sparse graphs.
bool hamiltonianCycleWarnsdorff(vector<vector<int>>& graph, vector<int>& path, int pos, vector<bool>& visited, vector<int>& degree) {
    int V = graph.size();

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    vector<pair<int, int>> unvisitedVertices; // (vertex, num_neighbors)
    for (int v = 0; v < V; ++v) {
        if (!visited[v] && isSafe(v, path, graph, pos)) {
            int numNeighbors = 0;
            for (int neighbor = 0; neighbor < V; ++neighbor) {
                if (graph[v][neighbor] == 1 && !visited[neighbor]) {
                    numNeighbors++;
                }
            }
            unvisitedVertices.push_back({v, numNeighbors});
        }
    }

    // Sort unvisited vertices in ascending order of number of unvisited neighbors.
    sort(unvisitedVertices.begin(), unvisitedVertices.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (const auto& vertexNeighborPair : unvisitedVertices) {
        int v = vertexNeighborPair.first;
        if (isSafe(v, path, graph, pos)) {
            path[pos] = v;
            visited[v] = true;
            if (hamiltonianCycleWarnsdorff(graph, path, pos + 1, visited, degree))
                return true;
            path[pos] = -1;
            visited[v] = false;
        }
    }
    return false;
}

bool findHamiltonianCycleWarnsdorff(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    path[0] = 0;
    vector<bool> visited(V, false);
    visited[0] = true;
    vector<int> degree(V, 0);

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            degree[i] += graph[i][j];
        }
    }

    if (hamiltonianCycleWarnsdorff(graph, path, 1, visited, degree) == false) {
        cout << "Hamiltonian Cycle does not exist (Warnsdorff's)." << endl;
        return false;
    } else {
        cout << "Hamiltonian Cycle found (Warnsdorff's): ";
        for (int vertex : path)
            cout << vertex << " ";
        cout << path[0] << endl;
        return true;
    }
}

// 5. Randomized Backtracking
//    - Introduces randomness in vertex selection to explore diverse paths.
//    - Can help escape local optima and find solutions in complex graphs.
bool hamiltonianCycleRandomized(vector<vector<int>>& graph, vector<int>& path, int pos, vector<bool>& visited) {
    int V = graph.size();

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    vector<int> possibleVertices;
    for (int v = 0; v < V; v++) {
        if (isSafe(v, path, graph, pos) && !visited[v]) {
            possibleVertices.push_back(v);
        }
    }

    // Use std::shuffle instead of random_shuffle (deprecated in C++14, removed in C++17)
    if (!possibleVertices.empty()) { // Make sure possibleVertices is not empty
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, possibleVertices.size() - 1);

        for (int i = possibleVertices.size() - 1; i > 0; --i) {
            int j = dist(gen);
            std::swap(possibleVertices[i], possibleVertices[j]);
        }
    }

    for (int v : possibleVertices) {
        path[pos] = v;
        visited[v] = true;
        if (hamiltonianCycleRandomized(graph, path, pos + 1, visited))
            return true;
        path[pos] = -1;
        visited[v] = false;
    }
    return false;
}

bool findHamiltonianCycleRandomized(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    path[0] = 0;
    vector<bool> visited(V, false);
    visited[0] = true;

    if (hamiltonianCycleRandomized(graph, path, 1, visited) == false) {
        cout << "Hamiltonian Cycle does not exist (Randomized)." << endl;
        return false;
    } else {
        cout << "Hamiltonian Cycle found (Randomized): ";
        for (int vertex : path)
            cout << vertex << " ";
        cout << path[0] << endl;
        return true;
    }
}

int main() {
    // Example graph represented as an adjacency matrix.
    //  0 1 2 3
    //0 0 1 0 1
    //1 1 0 1 1
    //2 0 1 0 1
    //3 1 1 1 0
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 0}
    };
    // Expected output: 0 1 3 2 0

    cout << "Graph:" << endl;
    for (const auto& row : graph) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Test each approach and measure execution time.
    auto start = high_resolution_clock::now();
    findHamiltonianCycleBasic(graph);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Basic: " << duration.count() << " microseconds" << endl << endl;

    start = high_resolution_clock::now();
    findHamiltonianCycleForwardChecking(graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Forward Checking: " << duration.count() << " microseconds" << endl << endl;

    start = high_resolution_clock::now();
    findHamiltonianCycleDegreeOrdering(graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Degree Ordering: " << duration.count() << " microseconds" << endl << endl;

    start = high_resolution_clock::now();
    findHamiltonianCycleWarnsdorff(graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Warnsdorff's: " << duration.count() << " microseconds" << endl << endl;

    start = high_resolution_clock::now();
    findHamiltonianCycleRandomized(graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Randomized: " << duration.count() << " microseconds" << endl << endl;

    return 0;
}

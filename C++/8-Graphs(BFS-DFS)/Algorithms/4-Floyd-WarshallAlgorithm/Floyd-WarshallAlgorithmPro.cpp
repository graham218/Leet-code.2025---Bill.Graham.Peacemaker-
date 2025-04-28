#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to print the distance matrix
void printSolution(const vector<vector<int>>& dist, const string& title) {
    cout << "\n" << title << ":\n";
    for (const auto& row : dist) {
        for (int val : row) {
            if (val == INT_MAX)
                cout << setw(5) << "INF"; // Use setw for consistent spacing
            else
                cout << setw(5) << val;
        }
        cout << endl;
    }
}

// Function to initialize the distance matrix
void initializeDistanceMatrix(vector<vector<int>>& dist, const vector<vector<int>>& graph) {
    int V = graph.size();
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                dist[i][j] = 0; // Distance from a node to itself is 0
            } else if (graph[i][j] != 0) {
                dist[i][j] = graph[i][j]; // Use the edge weight from the graph
            } else {
                dist[i][j] = INT_MAX; // No direct edge, initialize to infinity
            }
        }
    }
}

// 1. Basic Floyd-Warshall Algorithm
//   - Computes all-pairs shortest paths in a graph.
//   - Useful for route planning in GPS systems.
void floydWarshallBasic(vector<vector<int>>& dist, int V) {
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) { // Check for overflow
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    //check for negative weight cycles.  If any diagonal element is negative, there is a negative weight cycle.
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }
}

// 2. Floyd-Warshall with Path Reconstruction
//   - Extends the basic algorithm to also compute the shortest paths.
//   - Useful for network routing protocols.
void floydWarshallWithPathReconstruction(vector<vector<int>>& dist, vector<vector<int>>& next, int V, const vector<vector<int>>& graph) {
     // Initialize the 'next' matrix.  Stores the intermediate node in the shortest path
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j)
                next[i][j] = i;  // Path from i to i is just i
            else if (graph[i][j] != 0)
                next[i][j] = j; // Initial next node is j
            else
                next[i][j] = -1; // No direct path
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k]; // Update the intermediate node
                }
            }
        }
    }
    //check for negative weight cycles.
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }
}

// Function to print the shortest path
void printPath(const vector<vector<int>>& next, int u, int v) {
    if (next[u][v] == -1) {
        cout << "No path exists from " << u << " to " << v << endl;
        return;
    }
    cout << "Shortest path from " << u << " to " << v << ": " << u << " ";
    while (u != v) {
        u = next[u][v];
        cout << u << " ";
    }
    cout << endl;
}

// 3. Floyd-Warshall for Transitive Closure
//   - Determines if there is a path between any two vertices in a graph.
//   - Useful for analyzing relationships in social networks.
void floydWarshallTransitiveClosure(vector<vector<int>>& reachability, int V, const vector<vector<int>>& graph) {
    // Initialize reachability matrix.  0/1 instead of distances.
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j || graph[i][j] != 0)
                reachability[i][j] = 1; // There is a path from a node to itself, and to direct neighbors
            else
                reachability[i][j] = 0;
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                reachability[i][j] = reachability[i][j] || (reachability[i][k] && reachability[k][j]);
            }
        }
    }
}

// 4. Floyd-Warshall for Detecting Negative Cycles
//    - Detects the presence of negative weight cycles in a graph.
//    - Important for currency exchange arbitrage detection.
void floydWarshallNegativeCycleDetection(vector<vector<int>>& dist, int V, bool& hasNegativeCycle) {
     for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                dist[i][j] = 0; // Distance from a node to itself is 0
            }
            else if (dist[i][j] == 0)
                dist[i][j] = INT_MAX;
        }
    }
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    hasNegativeCycle = false;
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            break;
        }
    }
}

// 5. Floyd-Warshall with Arbitrary Precision (using long double)
//    - Handles larger edge weights or more precision to avoid overflow.
//    - Useful in financial modeling or scientific simulations.
void floydWarshallArbitraryPrecision(vector<vector<long double>>& dist_ld, int V, const vector<vector<int>>& graph) {
    // Initialize the distance matrix with long doubles.
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                dist_ld[i][j] = 0.0;
            } else if (graph[i][j] != 0) {
                dist_ld[i][j] = static_cast<long double>(graph[i][j]);
            } else {
                dist_ld[i][j] = numeric_limits<long double>::infinity();
            }
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist_ld[i][k] != numeric_limits<long double>::infinity() && dist_ld[k][j] != numeric_limits<long double>::infinity()) {
                    dist_ld[i][j] = min(dist_ld[i][j], dist_ld[i][k] + dist_ld[k][j]);
                }
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (dist_ld[i][i] < 0) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0,   5,  INT_MAX, 10},
        {INT_MAX, 0,   3,  INT_MAX},
        {INT_MAX, INT_MAX, 0,   1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int V = graph.size();

    // 1. Basic Floyd-Warshall
    vector<vector<int>> dist_basic(V, vector<int>(V));
    initializeDistanceMatrix(dist_basic, graph);
    floydWarshallBasic(dist_basic, V);
    printSolution(dist_basic, "1. Basic Floyd-Warshall");

    // 2. Floyd-Warshall with Path Reconstruction
    vector<vector<int>> dist_path(V, vector<int>(V));
    vector<vector<int>> next(V, vector<int>(V));
    initializeDistanceMatrix(dist_path, graph);
    floydWarshallWithPathReconstruction(dist_path, next, V, graph);
    printSolution(dist_path, "2. Floyd-Warshall with Path Reconstruction");
    printPath(next, 0, 3); // Example path

    // 3. Floyd-Warshall for Transitive Closure
    vector<vector<int>> reachability(V, vector<int>(V));
     floydWarshallTransitiveClosure(reachability, V, graph);
    printSolution(reachability, "3. Floyd-Warshall for Transitive Closure");

    // 4. Floyd-Warshall for Detecting Negative Cycles
    vector<vector<int>> dist_negative_cycle(V, vector<int>(V));
    bool hasNegativeCycle;
    initializeDistanceMatrix(dist_negative_cycle, graph); // Important to initialize *before* calling the function
    floydWarshallNegativeCycleDetection(dist_negative_cycle, V, hasNegativeCycle);
    if (hasNegativeCycle)
        cout << "4. Graph contains a negative weight cycle" << endl;
    else
        cout << "4. Graph does not contain any negative weight cycle" << endl;

     // 5. Floyd-Warshall with Arbitrary Precision
    vector<vector<long double>> dist_ld(V, vector<long double>(V));
    floydWarshallArbitraryPrecision(dist_ld, V, graph);
    cout << "\n5. Floyd-Warshall with Arbitrary Precision:\n";
    for (const auto& row : dist_ld) {
        for (long double val : row) {
             if (val == numeric_limits<long double>::infinity())
                cout << setw(10) << "INF";
            else
                cout << setw(10) << fixed << setprecision(2) << val;
        }
        cout << endl;
    }

    return 0;
}

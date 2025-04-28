#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// Function to print the distance matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INT_MAX)
                std::cout << "INF ";
            else
                std::cout << std::setw(4) << val << " "; // Use setw for consistent formatting
        }
        std::cout << std::endl;
    }
}

// 1. Basic Floyd-Warshall Algorithm
//   - Computes shortest paths between all pairs of vertices in a weighted graph.
//   - Works with both positive and negative edge weights.
//   - Time complexity: O(V^3), where V is the number of vertices.
//   - Space complexity: O(V^2)
void floydWarshallBasic(std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    // dist matrix will store the shortest distances between all pairs of vertices
    std::vector<std::vector<int>> dist = graph; // Initialize dist matrix with the original graph

    // Iterate through all vertices as intermediate nodes
    for (int k = 0; k < V; ++k) {
        // Iterate through all vertices as source nodes
        for (int i = 0; i < V; ++i) {
            // Iterate through all vertices as destination nodes
            for (int j = 0; j < V; ++j) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    graph = dist; //update the original graph
}

// 2. Floyd-Warshall with Path Reconstruction
//    - Extends the basic algorithm to also determine the shortest paths themselves.
//    - Uses a predecessor matrix to store the intermediate nodes in the shortest paths.
//    - Time complexity: O(V^3)
//    - Space complexity: O(V^2) for distances, O(V^2) for predecessors
void floydWarshallWithPath(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& next) {
    int V = graph.size();
    std::vector<std::vector<int>> dist = graph; // Initialize the distance matrix.
    next.resize(V, std::vector<int>(V, -1));    // Initialize the 'next' matrix.

    // Initialize the 'next' matrix:
    // For each pair (i, j), if there is an edge from i to j, set next[i][j] to j.
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] != INT_MAX && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Standard Floyd-Warshall algorithm
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k]; // Update the 'next' matrix.
                }
            }
        }
    }
    graph = dist;
}

// Function to reconstruct the shortest path between two vertices using the 'next' matrix
std::vector<int> reconstructPath(int start, int end, const std::vector<std::vector<int>>& next) {
    if (next[start][end] == -1) {
        return {}; // No path exists
    }
    std::vector<int> path = {start};
    while (start != end) {
        start = next[start][end];
        path.push_back(start);
    }
    return path;
}

// 3. Floyd-Warshall with Negative Cycle Detection
//   - Detects the presence of negative cycles in the graph.
//   - A negative cycle is a cycle whose edges sum to a negative value,
//     making shortest paths undefined.
//   - Time complexity: O(V^3)
//   - Space complexity: O(V^2)
bool floydWarshallNegativeCycle(std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<std::vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Check for negative cycles on the main diagonal
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            return true; // Negative cycle detected
        }
    }
    graph = dist;
    return false; // No negative cycle
}

// 4. Floyd-Warshall with Optimization (Early Termination)
//    - Optimizes the basic algorithm by adding a check for early termination.
//    - If no changes occur in a particular iteration (k), it means that no shorter paths
//      were found using vertex k as an intermediate node, so we can stop iterating.
//    - This optimization might not improve the worst-case time complexity, but can
//      lead to significant performance gains in practice for some graphs.
//    - Time complexity: O(V^3) in the worst case, potentially less in practice.
//    - Space complexity: O(V^2)
void floydWarshallOptimized(std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<std::vector<int>> dist = graph;
    bool changed; // Flag to track if any changes occurred in an iteration

    for (int k = 0; k < V; ++k) {
        changed = false; // Reset the flag for each iteration
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        changed = true; // Set flag to true if a change occurred
                    }
                }
            }
        }
        if (!changed) {
            break; // If no changes occurred, terminate early
        }
    }
    graph = dist;
}

// 5. Floyd-Warshall with Dynamic Programming Table
//    - This approach explicitly creates a 3D table (though we optimize it to 2D)
//      to store intermediate distances, emphasizing the dynamic programming nature
//      of the algorithm.  The k-th layer of the table, dist[k][i][j], stores the
//      shortest distance from i to j using only vertices 0 through k as
//      intermediate nodes.  We avoid the 3D table for efficiency.
//    - Time complexity: O(V^3)
//    - Space complexity: O(V^2)
void floydWarshallDPTable(std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<std::vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // Base case: k = -1, dist[i][j][k] = weight of edge from i to j.
                // Recursive case:
                // dist[i][j][k] = min(dist[i][j][k-1], dist[i][k][k-1] + dist[k][j][k-1])
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    graph = dist;
}

int main() {
    // Example graph represented as an adjacency matrix
    // INT_MAX represents no direct edge between two vertices.
    std::vector<std::vector<int>> graph = {
        {0,   5,   INT_MAX, 10},
        {INT_MAX, 0,   3,   INT_MAX},
        {INT_MAX, INT_MAX, 0,   1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int V = graph.size();

    std::cout << "Original Graph:" << std::endl;
    printMatrix(graph);
    std::cout << std::endl;

    // 1. Basic Floyd-Warshall
    std::vector<std::vector<int>> graph1 = graph; // Create a copy to preserve the original
    floydWarshallBasic(graph1);
    std::cout << "1. Basic Floyd-Warshall Algorithm:" << std::endl;
    printMatrix(graph1);
    std::cout << std::endl;

    // 2. Floyd-Warshall with Path Reconstruction
    std::vector<std::vector<int>> graph2 = graph;
    std::vector<std::vector<int>> next;
    floydWarshallWithPath(graph2, next);
    std::cout << "2. Floyd-Warshall with Path Reconstruction:" << std::endl;
    printMatrix(graph2);

    // Example of path reconstruction
    int startVertex = 0;
    int endVertex = 3;
    std::vector<int> path = reconstructPath(startVertex, endVertex, next);
    if (path.empty()) {
        std::cout << "No path exists between " << startVertex << " and " << endVertex << std::endl;
    } else {
        std::cout << "Shortest path between " << startVertex << " and " << endVertex << ": ";
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // 3. Floyd-Warshall with Negative Cycle Detection
    std::vector<std::vector<int>> graph3 = graph;
    bool hasNegativeCycle = floydWarshallNegativeCycle(graph3);
    std::cout << "3. Floyd-Warshall with Negative Cycle Detection:" << std::endl;
    if (hasNegativeCycle) {
        std::cout << "Negative cycle detected!" << std::endl;
    } else {
        std::cout << "No negative cycle detected." << std::endl;
        printMatrix(graph3);
    }
    std::cout << std::endl;

     // Example with a graph containing a negative weight cycle.
    std::vector<std::vector<int>> graphNegativeCycle = {
        {0, 2, INT_MAX, INT_MAX},
        {INT_MAX, 0, -3, INT_MAX},
        {INT_MAX, INT_MAX, 0, -1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };

    graphNegativeCycle[3][1] = -4;  // Introduce a negative cycle: 3 -> 1 -> 2 -> 3

    std::vector<std::vector<int>> graph4 = graphNegativeCycle;
    bool hasNegativeCycle2 = floydWarshallNegativeCycle(graph4);
    std::cout << "3. Floyd-Warshall with Negative Cycle Detection (Example with Negative Cycle):" << std::endl;
    if (hasNegativeCycle2) {
        std::cout << "Negative cycle detected!" << std::endl;
    } else {
        std::cout << "No negative cycle detected." << std::endl;
        printMatrix(graph4);
    }
    std::cout << std::endl;


    // 4. Floyd-Warshall with Optimization (Early Termination)
    std::vector<std::vector<int>> graph4_1 = graph;
    floydWarshallOptimized(graph4_1);
    std::cout << "4. Floyd-Warshall with Optimization (Early Termination):" << std::endl;
    printMatrix(graph4_1);
    std::cout << std::endl;

    // 5. Floyd-Warshall with Dynamic Programming Table
    std::vector<std::vector<int>> graph5 = graph;
    floydWarshallDPTable(graph5);
    std::cout << "5. Floyd-Warshall with Dynamic Programming Table:" << std::endl;
    printMatrix(graph5);
    std::cout << std::endl;

    return 0;
}

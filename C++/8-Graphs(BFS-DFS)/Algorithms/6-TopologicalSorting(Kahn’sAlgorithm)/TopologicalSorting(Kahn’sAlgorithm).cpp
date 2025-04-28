#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <stack> // Include stack for the stack-based approach

// Structure to represent a graph using an adjacency list.
struct Graph {
    int V; // Number of vertices
    std::vector<std::vector<int>> adj; // Adjacency list representation

    // Constructor for the Graph struct.
    Graph(int vertices) : V(vertices), adj(vertices) {}

    // Function to add an edge to the graph.
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
};

// 1. Kahn's Algorithm using a queue (standard approach)
//   - Computes the in-degrees of all nodes.
//   - Adds nodes with in-degree 0 to a queue.
//   - Iteratively removes nodes from the queue, adds them to the result,
//     and updates the in-degrees of their neighbors.
std::vector<int> topologicalSort_Kahn_Queue(const Graph& graph) {
    std::vector<int> inDegree(graph.V, 0); // Array to store in-degrees of vertices
    std::queue<int> q; // Queue to store vertices with in-degree 0
    std::vector<int> result; // Vector to store the topological sort order

    // Calculate in-degrees of all vertices.
    for (int u = 0; u < graph.V; ++u) {
        for (int v : graph.adj[u]) {
            inDegree[v]++;
        }
    }

    // Enqueue vertices with in-degree 0.
    for (int u = 0; u < graph.V; ++u) {
        if (inDegree[u] == 0) {
            q.push(u);
        }
    }

    // Process vertices in the queue.
    while (!q.empty()) {
        int u = q.front(); // Get the front vertex
        q.pop();             // Remove the front vertex
        result.push_back(u); // Add it to the result

        // Update in-degrees of neighbors and enqueue them if their in-degree becomes 0.
        for (int v : graph.adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Check for cycles: If not all vertices are included, there is a cycle.
    if (result.size() != graph.V) {
        return {}; // Return empty vector to indicate cycle
    }

    return result;
}

// 2. Kahn's Algorithm using a priority queue (for lexicographically smallest order)
//    - Uses a min-priority queue instead of a regular queue.
//    - This ensures that the nodes with the smallest value are processed first.
//    - The rest of the algorithm is the same as the standard Kahn's algorithm.
std::vector<int> topologicalSort_Kahn_PriorityQueue(const Graph& graph) {
    std::vector<int> inDegree(graph.V, 0);
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // Min-priority queue
    std::vector<int> result;

    for (int u = 0; u < graph.V; ++u) {
        for (int v : graph.adj[u]) {
            inDegree[v]++;
        }
    }

    for (int u = 0; u < graph.V; ++u) {
        if (inDegree[u] == 0) {
            pq.push(u);
        }
    }

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        result.push_back(u);

        for (int v : graph.adj[u]) {
            if (--inDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    if (result.size() != graph.V) {
        return {};
    }
    return result;
}

// 3. Kahn's Algorithm with early cycle detection
//    - This version bails out as soon as it detects a cycle.
//    - It maintains a count of visited nodes. If this count is not equal to
//      the number of nodes, it implies a cycle.
std::vector<int> topologicalSort_Kahn_EarlyCycleDetection(const Graph& graph) {
    std::vector<int> inDegree(graph.V, 0);
    std::queue<int> q;
    std::vector<int> result;
    int visitedCount = 0; // Keep track of visited nodes

    for (int u = 0; u < graph.V; ++u) {
        for (int v : graph.adj[u]) {
            inDegree[v]++;
        }
    }

    for (int u = 0; u < graph.V; ++u) {
        if (inDegree[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        visitedCount++; // Increment visited count

        for (int v : graph.adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (visitedCount != graph.V) {
        return {}; // Cycle detected
    }
    return result;
}

// 4. Kahn's Algorithm using a stack (modified approach)
//   - Uses a stack instead of a queue.  This is NOT the standard Kahn's.
//   - It might produce a different valid topological ordering.
std::vector<int> topologicalSort_Kahn_Stack(const Graph& graph) {
    std::vector<int> inDegree(graph.V, 0);
    std::stack<int> s; // Use a stack instead of a queue
    std::vector<int> result;

    for (int u = 0; u < graph.V; ++u) {
        for (int v : graph.adj[u]) {
            inDegree[v]++;
        }
    }

    for (int u = 0; u < graph.V; ++u) {
        if (inDegree[u] == 0) {
            s.push(u); // Push to stack instead of queue
        }
    }

    while (!s.empty()) {
        int u = s.top(); // Get top element
        s.pop();         // Pop from stack
        result.push_back(u);

        for (int v : graph.adj[u]) {
            if (--inDegree[v] == 0) {
                s.push(v); // Push to stack
            }
        }
    }

    if (result.size() != graph.V) {
        return {};
    }
    return result;
}

// 5. Kahn's Algorithm with a lambda for in-degree calculation
//   - Encapsulates the in-degree calculation within a lambda function.
//   - This improves code organization and readability by making the in-degree
//     calculation more localized.
std::vector<int> topologicalSort_Kahn_Lambda(const Graph& graph) {
    std::vector<int> inDegree(graph.V, 0);
    std::queue<int> q;
    std::vector<int> result;

    // Lambda function to calculate in-degrees
    auto calculateInDegrees = [&]() {
        for (int u = 0; u < graph.V; ++u) {
            for (int v : graph.adj[u]) {
                inDegree[v]++;
            }
        }
    };

    calculateInDegrees(); // Call the lambda function

    for (int u = 0; u < graph.V; ++u) {
        if (inDegree[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : graph.adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (result.size() != graph.V) {
        return {};
    }
    return result;
}

int main() {
    // Create a graph with 6 vertices.
    Graph graph(6);
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    std::cout << "Topological Sort (Kahn's Algorithm):\n";

    // 1. Using Queue
    std::cout << "1. Using Queue: ";
    std::vector<int> result1 = topologicalSort_Kahn_Queue(graph);
    if (result1.empty()) {
        std::cout << "Cycle detected\n";
    } else {
        for (int v : result1) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    // 2. Using Priority Queue
    std::cout << "2. Using Priority Queue: ";
    std::vector<int> result2 = topologicalSort_Kahn_PriorityQueue(graph);
    if (result2.empty()) {
        std::cout << "Cycle detected\n";
    } else {
        for (int v : result2) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    // 3. Early Cycle Detection
    std::cout << "3. Early Cycle Detection: ";
    std::vector<int> result3 = topologicalSort_Kahn_EarlyCycleDetection(graph);
    if (result3.empty()) {
        std::cout << "Cycle detected\n";
    } else {
        for (int v : result3) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    // 4. Using Stack
    std::cout << "4. Using Stack: ";
    std::vector<int> result4 = topologicalSort_Kahn_Stack(graph);
    if (result4.empty()) {
        std::cout << "Cycle detected\n";
    } else {
        for (int v : result4) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

     // 5. Using Lambda
    std::cout << "5. Using Lambda: ";
    std::vector<int> result5 = topologicalSort_Kahn_Lambda(graph);
    if (result5.empty()) {
        std::cout << "Cycle detected\n";
    } else {
        for (int v : result5) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

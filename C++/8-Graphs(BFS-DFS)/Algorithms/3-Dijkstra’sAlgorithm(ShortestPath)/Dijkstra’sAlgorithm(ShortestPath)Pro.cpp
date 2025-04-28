#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

// A utility function to print the solution (shortest path from source to all vertices)
void printSolution(const vector<int>& dist, int n, int source) {
    cout << "Shortest distances from source " << source << " to all other vertices:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INT_MAX ? "Infinity" : to_string(dist[i])) << endl;
    }
}

// Function to reconstruct the shortest path from source to a given target vertex
vector<int> reconstructPath(const vector<int>& parent, int target) {
    vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end()); // Reverse to get path from source to target
    return path;
}

// Function to print the shortest path
void printPath(const vector<int>& path, int source, int target) {
    cout << "Shortest path from " << source << " to " << target << ": ";
    if (path.empty() || path[0] != source || path.back() != target) {
        cout << "No path exists" << endl; // Handle the case where no path was found.
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

// 1. Dijkstra's Algorithm using Priority Queue (Greedy Approach)
//   - Project Application: Network Routing (e.g., OSPF - Open Shortest Path First)
//   - Key Feature: Efficiently finds the shortest path in a network by iteratively selecting the closest unvisited node.
void dijkstraPriorityQueue(const vector<vector<pair<int, int>>>& graph, int source, int target = -1) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // Initialize distances to infinity
    vector<int> parent(n, -1);    // To store the parent of each node in the shortest path
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap

    dist[source] = 0; // Distance from source to itself is 0
    pq.push({0, source}); // Push the source node with its distance

    while (!pq.empty()) {
        int u = pq.top().second; // Get the node with the smallest distance
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) { // Important: Check if the stored distance is obsolete
            continue;       // If it is, skip processing this node.
        }

        if (target != -1 && u == target) {
            break; // Optional: Stop if the target is reached (for single-pair shortest path)
        }

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; // Update distance to neighbor
                parent[v] = u;             // Update parent for path reconstruction
                pq.push({dist[v], v});     // Push the neighbor with the updated distance
            }
        }
    }

    if (target == -1) {
        printSolution(dist, n, source); // Print shortest distances to all nodes
    }
    else {
        if (dist[target] == INT_MAX) {
            cout << "No path exists from " << source << " to " << target << endl;
        }
        else {
            cout << "Shortest distance from " << source << " to " << target << ": " << dist[target] << endl;
            vector<int> path = reconstructPath(parent, target);
            printPath(path, source, target);
        }
    }
}

// 2. Dijkstra's Algorithm using Set (for Faster Updates)
//   - Project Application: Geographic Navigation Systems (e.g., finding the shortest route on a map)
//   - Key Feature: Uses a set to efficiently find the minimum distance node and update distances.
void dijkstraSet(const vector<vector<pair<int, int>>>& graph, int source, int target = -1) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    set<pair<int, int>> s; // Use a set instead of a priority queue

    dist[source] = 0;
    s.insert({0, source});

    while (!s.empty()) {
        auto it = s.begin();
        int u = it->second;
        int d = it->first;
        s.erase(it);

        if (target != -1 && u == target) {
            break;
        }

        if (d > dist[u]) {
            continue;
        }

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                // Remove the old distance if it exists
                if (dist[v] != INT_MAX) {
                    s.erase({dist[v], v});
                }
                dist[v] = dist[u] + weight;
                parent[v] = u;
                s.insert({dist[v], v}); // Insert the new distance
            }
        }
    }
    if (target == -1) {
        printSolution(dist, n, source);
    }
    else {
        if (dist[target] == INT_MAX) {
            cout << "No path exists from " << source << " to " << target << endl;
        }
        else {
            cout << "Shortest distance from " << source << " to " << target << ": " << dist[target] << endl;
            vector<int> path = reconstructPath(parent, target);
            printPath(path, source, target);
        }
    }
}

// 3. Dijkstra's Algorithm with Adjacency Matrix
//   - Project Application: Circuit Board Routing (finding the shortest path for connections)
//   - Key Feature: Uses an adjacency matrix representation of the graph.  Good for dense graphs.
void dijkstraMatrix(const vector<vector<int>>& graphMatrix, int source, int target = -1) {
    int n = graphMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[source] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;
        // Find the vertex with the minimum distance among the unvisited vertices
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1) break; // No more reachable unvisited vertices.

        visited[u] = true;

        if (target != -1 && u == target) {
            break;
        }
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graphMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graphMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graphMatrix[u][v];
                parent[v] = u;
            }
        }
    }
    if (target == -1) {
        printSolution(dist, n, source);
    }
    else {
       if (dist[target] == INT_MAX) {
            cout << "No path exists from " << source << " to " << target << endl;
        }
        else {
            cout << "Shortest distance from " << source << " to " << target << ": " << dist[target] << endl;
            vector<int> path = reconstructPath(parent, target);
            printPath(path, source, target);
        }
    }
}

// 4. Dijkstra's Algorithm for Large Graphs (Optimization Considerations)
//   - Project Application: Social Network Analysis (finding shortest connections between users)
//   - Key Feature: Considers optimizations for very large graphs, such as using more efficient data structures or heuristics.  This example focuses on using a map for potentially faster lookups, though its performance can vary.
void dijkstraLargeGraph(const unordered_map<int, vector<pair<int, int>>>& graph, int source, int target = -1) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        if (target != -1 && u == target) {
            break;
        }

        // Use find() since graph is now an unordered_map
        auto it = graph.find(u);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    if (target == -1) {
        printSolution(dist, n, source);
    }
    else {
        if (dist[target] == INT_MAX) {
            cout << "No path exists from " << source << " to " << target << endl;
        }
        else {
            cout << "Shortest distance from " << source << " to " << target << ": " << dist[target] << endl;
            vector<int> path = reconstructPath(parent, target);
            printPath(path, source, target);
        }
    }
}

// 5. Dijkstra's Algorithm with Edge List
//   - Project Application: Transportation Networks (modeling roads, railways, etc.)
//   - Key Feature: Uses an edge list representation, which can be more memory-efficient for sparse graphs.
void dijkstraEdgeList(const vector<tuple<int, int, int>>& edgeList, int numVertices, int source, int target = -1) {
    vector<int> dist(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }
        if (target != -1 && u == target){
            break;
        }

        for (const auto& edge : edgeList) {
            int u_edge, v_edge, weight;
            tie(u_edge, v_edge, weight) = edge; //unpack the tuple
            if (u_edge == u && dist[u] != INT_MAX && dist[u] + weight < dist[v_edge]) {
                dist[v_edge] = dist[u] + weight;
                parent[v_edge] = u;
                pq.push({dist[v_edge], v_edge});
            }
        }
    }
    if (target == -1) {
        printSolution(dist, numVertices, source);
    }
    else {
        if (dist[target] == INT_MAX) {
            cout << "No path exists from " << source << " to " << target << endl;
        }
        else {
            cout << "Shortest distance from " << source << " to " << target << ": " << dist[target] << endl;
            vector<int> path = reconstructPath(parent, target);
            printPath(path, source, target);
        }
    }
}

int main() {
    // Example graph represented as an adjacency list (for approaches 1, 2, and 4)
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 2}}, // Node 0
        {{2, 5}, {3, 10}, {0, 4}}, // Node 1
        {{0, 2}, {1, 5}, {3, 3}}, // Node 2
        {{2, 3}, {1, 10}}  // Node 3
    };
    // Example graph represented as an adjacency matrix (for approach 3)
    vector<vector<int>> graphMatrix = {
        {0, 4, 2, 0},
        {4, 0, 5, 10},
        {2, 5, 0, 3},
        {0, 10, 3, 0}
    };

    // Example graph for large graph scenario
    unordered_map<int, vector<pair<int, int>>> largeGraph = {
        {0, {{1, 4}, {2, 2}}},
        {1, {{2, 5}, {3, 10}, {0, 4}}},
        {2, {{0, 2}, {1, 5}, {3, 3}}},
        {3, {{2, 3}, {1, 10}}}
    };

    // Example edge list for approach 5
    vector<tuple<int, int, int>> edgeList = {
        {0, 1, 4}, {0, 2, 2},
        {1, 2, 5}, {1, 3, 10}, {1, 0, 4},
        {2, 0, 2}, {2, 1, 5}, {2, 3, 3},
        {3, 2, 3}, {3, 1, 10}
    };
    int numVertices = 4; // Number of vertices for the edge list example.

    int source = 0;
    int target = 3; // Example target node for single-pair shortest path

    cout << "1. Dijkstra's Algorithm using Priority Queue:\n";
    dijkstraPriorityQueue(graph, source, target);
    cout << endl;

    cout << "2. Dijkstra's Algorithm using Set:\n";
    dijkstraSet(graph, source, target);
    cout << endl;

    cout << "3. Dijkstra's Algorithm using Adjacency Matrix:\n";
    dijkstraMatrix(graphMatrix, source, target);
    cout << endl;

    cout << "4. Dijkstra's Algorithm for Large Graphs:\n";
    dijkstraLargeGraph(largeGraph, source, target);
    cout << endl;

    cout << "5. Dijkstra's Algorithm with Edge List:\n";
    dijkstraEdgeList(edgeList, numVertices, source, target);
    cout << endl;

    return 0;
}


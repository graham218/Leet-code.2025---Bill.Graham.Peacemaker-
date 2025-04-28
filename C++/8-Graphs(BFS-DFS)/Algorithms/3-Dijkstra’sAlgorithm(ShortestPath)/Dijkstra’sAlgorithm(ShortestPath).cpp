#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int to;      // Destination vertex
    int weight;    // Weight of the edge
};

// Structure to represent a node in the priority queue for Dijkstra's algorithm
struct Node {
    int vertex;  // Vertex
    int distance; // Distance from the source

    // Overload the less than operator for the priority queue.  We want the *smallest* distance
    // to have the highest priority, so we reverse the comparison.
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to add an edge to the graph.  We represent the graph as an adjacency list.
void addEdge(vector<vector<Edge>>& graph, int from, int to, int weight) {
    graph[from].push_back({to, weight});
    // For an undirected graph, you would also add the reverse edge:
    // graph[to].push_back({from, weight});
}

// 1. Dijkstra's Algorithm using a Priority Queue (Min Heap)
//    - Uses priority_queue (which is a max heap by default in C++)
//    - We use std::greater to make it a min heap.
//    - Efficient for most cases.
vector<int> dijkstraPQ(const vector<vector<Edge>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INT_MAX); // Initialize distances to infinity
    distance[source] = 0;                      // Distance from source to itself is 0

    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min heap
    pq.push({source, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        int dist_u = current.distance;

        if (dist_u > distance[u]) {
            continue; // Important optimization: Skip if we've found a shorter path to u
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight_uv = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight_uv < distance[v]) {
                distance[v] = distance[u] + weight_uv; // Update distance
                pq.push({v, distance[v]});           // Add to priority queue
            }
        }
    }
    return distance;
}

// 2. Dijkstra's Algorithm using a Set (for ordered storage)
//    - Uses a set to store nodes and their distances.
//    - Set automatically orders elements, providing the smallest distance at the beginning.
vector<int> dijkstraSet(const vector<vector<Edge>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INT_MAX);
    distance[source] = 0;

    set<pair<int, int>> s; // Store {distance, vertex} pairs.  Set is ordered by the first element.
    s.insert({0, source});

    while (!s.empty()) {
        pair<int, int> current = *s.begin(); // Get the node with the smallest distance
        s.erase(s.begin());             // Remove it from the set
        int u = current.second;
        int dist_u = current.first;

       if (dist_u > distance[u]) {
            continue; // Important optimization: Skip if we've found a shorter path to u
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight_uv = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight_uv < distance[v]) {
                // If a shorter path is found, we need to update the distance.
                // Because set does not allow updating the element directly, we remove the old pair and insert a new one.
                s.erase({distance[v], v}); // Remove the old distance-vertex pair
                distance[v] = distance[u] + weight_uv;
                s.insert({distance[v], v}); // Insert the updated pair
            }
        }
    }
    return distance;
}

// 3. Dijkstra's Algorithm using a simple array (less efficient, but good for understanding)
//    -  The most basic implementation.
//    -  Finds the vertex with the minimum distance by iterating through all vertices.
//    -  Time complexity: O(V^2), where V is the number of vertices.
vector<int> dijkstraArray(const vector<vector<Edge>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INT_MAX);
    distance[source] = 0;
    vector<bool> visited(numVertices, false); // Keep track of visited vertices

    for (int count = 0; count < numVertices - 1; ++count) {
        // Find the vertex with the minimum distance among the unvisited vertices
        int minDistance = INT_MAX, u;
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                u = v;
            }
        }

        visited[u] = true; // Mark the selected vertex as visited

        // Update distances of the adjacent vertices of u
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight_uv = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight_uv < distance[v]) {
                distance[v] = distance[u] + weight_uv;
            }
        }
    }
    return distance;
}

// 4. Dijkstra with Adjacency Matrix
//    - Uses an adjacency matrix to represent the graph.  Useful for dense graphs.
//    -  Adjacency Matrix Graph Representation:
//       graph[u][v] stores the weight of the edge from vertex u to vertex v.
//       If there is no edge between u and v, graph[u][v] is 0 or a large value (like INT_MAX).
vector<int> dijkstraMatrix(const vector<vector<pair<int, int>>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INT_MAX);
    distance[source] = 0;
    vector<bool> visited(numVertices, false);

    for (int count = 0; count < numVertices - 1; ++count) {
        int minDistance = INT_MAX, u;
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                u = v;
            }
        }
        visited[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            // Important:  Check if there is an edge from u to v AND handle the case where there is no edge.
            if (graph[u][v].first != -1 && distance[u] != INT_MAX && distance[u] + graph[u][v].second < distance[v]) {
                distance[v] = distance[u] + graph[u][v].second;
            }
        }
    }
    return distance;
}

// 5. Dijkstra's Algorithm using a Fibonacci Heap (Conceptual)
//    -  Conceptually uses a Fibonacci heap.  C++ doesn't have a standard Fibonacci heap.
//    -  Fibonacci heaps offer better theoretical time complexity, especially for sparse graphs.
//    -  In practice, they are more complex to implement and the constant factors can make them slower for small to medium-sized graphs.
//    -  This implementation uses a map to simulate the decrease-key operation (which is the key advantage of Fibonacci heaps).
//    -  This is more of a conceptual implementation, as it doesn't use a true Fibonacci Heap.
vector<int> dijkstraFibonacci(const vector<vector<Edge>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INT_MAX);
    distance[source] = 0;

    map<int, int> m; // Map to store {distance, vertex}.  Ordered by distance.
    m[0] = source;

    while (!m.empty()) {
        auto it = m.begin();
        int u = it->second;
        int dist_u = it->first;
        m.erase(it);

        if (dist_u > distance[u]) {
            continue;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight_uv = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight_uv < distance[v]) {
                // "Decrease-key" operation:  We don't have a true decrease-key in std::map, so we remove and re-insert.
                if (m.find(distance[v]) != m.end()) {
                    m.erase(distance[v]);
                }
                distance[v] = distance[u] + weight_uv;
                m[distance[v]] = v; // Insert with the new, smaller distance
            }
        }
    }
    return distance;
}

int main() {
    int numVertices = 6;
    vector<vector<Edge>> graph(numVertices);

    // Build the graph (example graph)
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 1, 3);
    addEdge(graph, 2, 3, 9);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 4, 4);
    addEdge(graph, 3, 5, 6);
    addEdge(graph, 4, 5, 4);

    // Example of Adjacency Matrix representation
    vector<vector<pair<int, int>>> matrixGraph(numVertices, vector<pair<int, int>>(numVertices, {-1, 0})); // Initialize with -1 and 0
    // Convert the previous graph to adjacency matrix
    for (int i = 0; i < numVertices; i++) {
        for (const Edge& edge : graph[i]) {
            matrixGraph[i][edge.to] = {1, edge.weight}; // 1 indicates there is an edge, second value is the weight.
        }
    }
    // Choose the source vertex
    int source = 0;

    // 1. Dijkstra with Priority Queue
    vector<int> distancePQ = dijkstraPQ(graph, source);
    cout << "Dijkstra's Algorithm with Priority Queue (Min Heap):" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distancePQ[i] << endl;
    }
    cout << endl;

    // 2. Dijkstra with Set
    vector<int> distanceSet = dijkstraSet(graph, source);
    cout << "Dijkstra's Algorithm with Set:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distanceSet[i] << endl;
    }
    cout << endl;

    // 3. Dijkstra with Array
    vector<int> distanceArray = dijkstraArray(graph, source);
    cout << "Dijkstra's Algorithm with Array:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distanceArray[i] << endl;
    }
    cout << endl;

    // 4. Dijkstra with Adjacency Matrix
    vector<int> distanceMatrix = dijkstraMatrix(matrixGraph, source);
    cout << "Dijkstra's Algorithm with Adjacency Matrix:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distanceMatrix[i] << endl;
    }
    cout << endl;

    // 5. Dijkstra with Fibonacci Heap (Conceptual)
    vector<int> distanceFibonacci = dijkstraFibonacci(graph, source);
    cout << "Dijkstra's Algorithm with Fibonacci Heap (Conceptual):" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distanceFibonacci[i] << endl;
    }
    cout << endl;

    return 0;
}


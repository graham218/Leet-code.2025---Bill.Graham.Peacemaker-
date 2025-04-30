#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional> // For greater<T>
#include <algorithm>  // For std::fill

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int to;      // Destination vertex
    int weight;    // Weight of the edge

    Edge(int t, int w) : to(t), weight(w) {}
};

// Function to implement Dijkstra's algorithm using a priority queue
// 1. Using std::priority_queue (Min Heap) with pair
void dijkstra_pq_pair(const vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int num_vertices = graph.size();
    dist.assign(num_vertices, INT_MAX); // Initialize distances to infinity
    dist[start] = 0;                   // Distance from start to itself is 0

    // Use a priority queue (min heap) to store vertices and their distances
    // pair (distance, vertex),  lower distance means higher priority
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start}); // Push the starting vertex with distance 0

    while (!pq.empty()) {
        int d = pq.top().first; // Get the current distance
        int u = pq.top().second; // Get the current vertex
        pq.pop();               // Remove the element from the priority queue

        if (d > dist[u]) {
            continue; // Important optimization: If the stored distance is greater than the known distance, skip it
        }

        // Iterate over the neighbors of the current vertex
        for (const auto& edge : graph[u]) {
            int v = edge.to;           // Neighbor vertex
            int weight = edge.weight; // Edge weight

            // If a shorter path to 'v' is found
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; // Update the distance to 'v'
                pq.push({dist[v], v});     // Push the updated distance and vertex to the priority queue
            }
        }
    }
}

// 2. Using std::priority_queue with a custom struct and operator overloading
struct Node {
    int vertex;
    int distance;

    Node(int v, int d) : vertex(v), distance(d) {}

    // Overload the less-than operator for the priority queue.  Min heap.
    bool operator>(const Node& other) const {
        return distance > other.distance; // Compare distances for priority queue ordering
    }
};

void dijkstra_pq_struct(const vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int num_vertices = graph.size();
    dist.assign(num_vertices, INT_MAX);
    dist[start] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq; // min heap
    pq.push(Node(start, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        int d = current.distance;

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(Node(v, dist[v]));
            }
        }
    }
}

// 3. Using std::priority_queue with a custom comparator (functor)
class CompareNodes {
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first; // Compare distances (a.first, b.first)
    }
};

void dijkstra_pq_comparator(const vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int num_vertices = graph.size();
    dist.assign(num_vertices, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNodes> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// 4.  Using a simple, non-optimized approach (for comparison) - NOT RECOMMENDED for large graphs
void dijkstra_naive(const vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int num_vertices = graph.size();
    dist.assign(num_vertices, INT_MAX);
    dist[start] = 0;
    vector<bool> visited(num_vertices, false);

    for (int count = 0; count < num_vertices - 1; count++) {
        // Find the vertex with the minimum distance among the unvisited vertices
        int min_dist = INT_MAX, u = -1;
        for (int i = 0; i < num_vertices; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // No unvisited node reachable

        visited[u] = true; // Mark the current vertex as visited

        // Update distances of the adjacent vertices
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
}

// 5. Using priority queue, but with a slight variation in the loop condition
void dijkstra_pq_variation(const vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int num_vertices = graph.size();
    dist.assign(num_vertices, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    vector<bool> visited(num_vertices, false); // Keep track of visited status

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;  // Skip if already visited.  Slight difference.
        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int num_vertices = 6;
    // Adjacency list representation of the graph
    vector<vector<Edge>> graph(num_vertices);

    // Add edges to the graph (directed graph)
    graph[0].push_back(Edge(1, 10));
    graph[0].push_back(Edge(2, 3));
    graph[1].push_back(Edge(2, 1));
    graph[1].push_back(Edge(3, 2));
    graph[2].push_back(Edge(1, 4));
    graph[2].push_back(Edge(3, 8));
    graph[2].push_back(Edge(4, 2));
    graph[3].push_back(Edge(4, 7));
    graph[3].push_back(Edge(5, 1));
    graph[4].push_back(Edge(5, 6));

    int start_vertex = 0; // Starting vertex for Dijkstra's algorithm
    vector<int> distances;  // Vector to store the shortest distances

    cout << "Dijkstra's Algorithm (Using priority queue with pair):\n";
    dijkstra_pq_pair(graph, start_vertex, distances);
    cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }
    cout << endl;

    cout << "Dijkstra's Algorithm (Using priority queue with struct):\n";
    dijkstra_pq_struct(graph, start_vertex, distances);
    cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }
    cout << endl;

    cout << "Dijkstra's Algorithm (Using priority queue with comparator):\n";
    dijkstra_pq_comparator(graph, start_vertex, distances);
    cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }
    cout << endl;

    cout << "Dijkstra's Algorithm (Naive approach):\n";
    dijkstra_naive(graph, start_vertex, distances);
    cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }
    cout << endl;

    cout << "Dijkstra's Algorithm (Priority Queue Variation):\n";
    dijkstra_pq_variation(graph, start_vertex, distances);
    cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "To vertex " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }
    cout << endl;

    return 0;
}
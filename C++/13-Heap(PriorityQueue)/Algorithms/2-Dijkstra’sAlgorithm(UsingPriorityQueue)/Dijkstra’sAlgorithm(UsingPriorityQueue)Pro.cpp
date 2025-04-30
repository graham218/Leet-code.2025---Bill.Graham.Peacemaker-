#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <unordered_map>
#include <set>
#include <algorithm> // Include the algorithm header for std::reverse

using namespace std;

// A structure to represent an edge in the graph.  Weight is the cost
struct Edge {
    int to;
    int weight;
};

// A structure to represent a node in the graph.  'id' is the node's identifier
struct Node {
    int id;
    vector<Edge> neighbors; // Use 'neighbors' instead of 'edges' for clarity
};

// Function to add an edge to the graph.  Handles undirected graphs.
void addEdge(vector<Node>& graph, int from, int to, int weight) {
    graph[from].neighbors.push_back({to, weight});
    graph[to].neighbors.push_back({from, weight}); // Undirected graph
}

// 1. Dijkstra's Algorithm using a standard priority_queue (min-heap) of pairs
//    -  pair: (distance, node_id).
//    -  Uses a vector for the graph.
//    -  Basic implementation, good for understanding the core algorithm.
vector<int> dijkstra_pq_pair(const vector<Node>& graph, int startNode) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INT_MAX);  // Initialize all distances to infinity
    distances[startNode] = 0;                 // Distance from start node to itself is 0

    // Use a min-heap (priority queue) to store nodes to visit.
    // The pair stores (distance, node_id), and the queue is ordered by distance.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode}); // Start with the start node and its distance

    while (!pq.empty()) {
        int currentDistance = pq.top().first; // Get the smallest distance
        int currentNode = pq.top().second;    // and the corresponding node.
        pq.pop();                            // Remove the element from queue

        if (currentDistance > distances[currentNode]) {
            continue; // Important optimization: If we've found a shorter path, skip this
        }

        // Iterate through the neighbors of the current node.
        for (const auto& edge : graph[currentNode].neighbors) {
            int neighbor = edge.to;
            int weight = edge.weight;
            int newDistance = currentDistance + weight; // Calculate distance to neighbor

            // If a shorter path to the neighbor is found, update the distance.
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance; // Update the distance
                pq.push({newDistance, neighbor});    // Add the neighbor to the queue
            }
        }
    }
    return distances; // Return the calculated shortest distances from startNode
}

// 2. Dijkstra's Algorithm using a priority_queue with a custom NodeDistance struct
//    -  Instead of pair, create a struct to hold node and distance.
//    -  Overload the `operator>` for the struct to make priority queue work.
//    -  Improves readability compared to using pairs.
struct NodeDistance {
    int node;
    int distance;

    // Overload the greater-than operator for the priority queue.  Essential!
    bool operator>(const NodeDistance& other) const {
        return distance > other.distance; // Min-heap based on distance
    }
};

vector<int> dijkstra_pq_struct(const vector<Node>& graph, int startNode) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INT_MAX);
    distances[startNode] = 0;

    priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> pq;
    pq.push({startNode, 0});

    while (!pq.empty()) {
        NodeDistance current = pq.top();
        pq.pop();
        int currentDistance = current.distance;
        int currentNode = current.node;

        if (currentDistance > distances[currentNode]) {
            continue;
        }

        for (const auto& edge : graph[currentNode].neighbors) {
            int neighbor = edge.to;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                pq.push({neighbor, newDistance});
            }
        }
    }
    return distances;
}

// 3. Dijkstra's Algorithm using a set (instead of priority_queue)
//    -  Sets are ordered, so they can be used as a priority queue.
//    -  Using a set often has slightly different performance characteristics
//       than a priority_queue, and can be more efficient in some cases.
//    -  Requires a custom comparator or a struct with overloaded operators.
vector<int> dijkstra_set(const vector<Node>& graph, int startNode) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INT_MAX);
    distances[startNode] = 0;

    // Use a set to store nodes to visit, ordered by distance.
    set<pair<int, int>> s; // set of (distance, node_id)
    s.insert({0, startNode});

    while (!s.empty()) {
        auto current = *s.begin(); // Get the node with the smallest distance
        int currentDistance = current.first;
        int currentNode = current.second;
        s.erase(s.begin());      // Remove the node from the set

        if (currentDistance > distances[currentNode]) {
            continue;
        }

        for (const auto& edge : graph[currentNode].neighbors) {
            int neighbor = edge.to;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                // Important:  Remove the old entry from the set if it exists.
                s.erase({distances[neighbor], neighbor}); // Remove old distance.  Crucial for set!
                distances[neighbor] = newDistance;
                s.insert({newDistance, neighbor});       // Insert the new distance.
            }
        }
    }
    return distances;
}

// 4. Dijkstra's with path reconstruction
//    -  Keeps track of the predecessor node in the shortest path.
//    -  Allows you to find the actual shortest path, not just the distance.
vector<int> dijkstra_with_path(const vector<Node>& graph, int startNode, vector<int>& parent) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INT_MAX);
    distances[startNode] = 0;
    parent.assign(numNodes, -1); // Initialize parent array. -1 means no parent.

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDistance > distances[currentNode]) {
            continue;
        }

        for (const auto& edge : graph[currentNode].neighbors) {
            int neighbor = edge.to;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                parent[neighbor] = currentNode; // Store the parent of the neighbor
                pq.push({newDistance, neighbor});
            }
        }
    }
    return distances;
}

// Function to reconstruct the shortest path from startNode to endNode
vector<int> reconstructPath(const vector<int>& parent, int startNode, int endNode) {
    vector<int> path;
    int current = endNode;

    // Traverse back from the end node to the start node using the parent array.
    while (current != -1 && current != startNode) {
        path.push_back(current);
        current = parent[current];
    }
    if(current == -1){
        return {}; // No path
    }
    path.push_back(startNode); // Add the start node to the path
    reverse(path.begin(), path.end()); // Reverse the path to get the correct order
    return path;
}

// 5. Dijkstra's Algorithm Optimized (More efficient for large graphs)
//    - Uses a map to track visited nodes
//    - Uses a set
vector<int> dijkstra_optimized(const vector<Node>& graph, int startNode) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INT_MAX);
    distances[startNode] = 0;

    set<pair<int, int>> activeNodes; // (distance, node)
    activeNodes.insert({0, startNode});

    unordered_map<int, int> visited;

    while (!activeNodes.empty()) {
        int currentNode = activeNodes.begin()->second;
        int currentDistance = activeNodes.begin()->first;
        activeNodes.erase(activeNodes.begin());
        visited[currentNode] = 1;

        if (currentDistance > distances[currentNode])
            continue;

        for (const auto& edge : graph[currentNode].neighbors) {
            int neighbor = edge.to;
            int weight = edge.weight;
            if(visited.find(neighbor) == visited.end()){
                int newDistance = currentDistance + weight;
                if (newDistance < distances[neighbor]) {
                    if (distances[neighbor] != INT_MAX)
                        activeNodes.erase({distances[neighbor], neighbor});
                    distances[neighbor] = newDistance;
                    activeNodes.insert({newDistance, neighbor});
                }
            }
        }
    }
    return distances;
}

int main() {
    // Example graph (same as before for consistency)
    int numNodes = 6;
    vector<Node> graph(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        graph[i].id = i;
    }

    // Add edges to the graph
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 3, 10);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 4, 8);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 5, 11);
    addEdge(graph, 4, 5, 9);

    int startNode = 0; // Starting node for Dijkstra's algorithm

    // 1. Dijkstra's with pair
    cout << "Dijkstra's Algorithm (Pair):" << endl;
    vector<int> distances1 = dijkstra_pq_pair(graph, startNode);
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << distances1[i] << endl;
    }
    cout << endl;

    // 2. Dijkstra's with struct
    cout << "Dijkstra's Algorithm (Struct):" << endl;
    vector<int> distances2 = dijkstra_pq_struct(graph, startNode);
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << distances2[i] << endl;
    }
    cout << endl;

    // 3. Dijkstra's with set
    cout << "Dijkstra's Algorithm (Set):" << endl;
    vector<int> distances3 = dijkstra_set(graph, startNode);
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << distances3[i] << endl;
    }
    cout << endl;

    // 4. Dijkstra's with path reconstruction
    cout << "Dijkstra's Algorithm (with Path):" << endl;
    vector<int> parent(numNodes);
    vector<int> distances4 = dijkstra_with_path(graph, startNode, parent);
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << distances4[i] << ", Parent: " << parent[i] << endl;
    }

    int endNode = 5;
    vector<int> shortestPath = reconstructPath(parent, startNode, endNode);
    if (shortestPath.empty()) {
        cout << "No path from " << startNode << " to " << endNode << endl;
    } else {
        cout << "Shortest path from " << startNode << " to " << endNode << ": ";
        for (int node : shortestPath) {
            cout << node << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 5. Dijkstra's Optimized
    cout << "Dijkstra's Algorithm (Optimized):" << endl;
    vector<int> distances5 = dijkstra_optimized(graph, startNode);
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << distances5[i] << endl;
    }
    cout << endl;

    return 0;
}

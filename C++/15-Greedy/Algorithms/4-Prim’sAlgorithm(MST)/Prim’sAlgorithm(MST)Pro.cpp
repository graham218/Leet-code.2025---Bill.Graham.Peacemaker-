/*
 * Title: Greedy -> Prim’s Algorithm (Minimum Spanning Tree - MST)
 * Language: C++
 * Description: This code demonstrates 5 different real-world inspired applications of Prim's algorithm
 * for finding the Minimum Spanning Tree (MST) using greedy strategy. Each approach includes detailed comments.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Graph represented using adjacency list
class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // adj[u] = {v, weight}

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected graph
    }

    // Core implementation of Prim's algorithm
    int primMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> key(V, INT_MAX); // Minimum weight to reach a node
        vector<bool> inMST(V, false); // MST inclusion

        key[0] = 0;
        pq.push({0, 0}); // (weight, vertex)

        int totalWeight = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;

            inMST[u] = true;
            totalWeight += key[u];

            for (auto &[v, weight] : adj[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }

        return totalWeight;
    }
};

// --- Real World Applications ---

// 1. Network Cable Laying in a Building
void buildingNetworkMST() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 4);

    cout << "[1] Building Network MST Cost: " << g.primMST() << endl;
}

// 2. Road Network Between Cities
void cityRoadNetworkMST() {
    Graph g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 6);

    cout << "[2] Road Network MST Cost: " << g.primMST() << endl;
}

// 3. Electrical Grid Design
void electricalGridMST() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    cout << "[3] Electrical Grid MST Cost: " << g.primMST() << endl;
}

// 4. Laying Fiber Optic Cables in a Campus
void campusFiberMST() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "[4] Campus Fiber MST Cost: " << g.primMST() << endl;
}

// 5. Connecting Data Centers with Minimum Cost
void dataCenterMST() {
    Graph g(7);
    g.addEdge(0, 1, 7);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 9);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 15);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 8);
    g.addEdge(4, 6, 9);
    g.addEdge(5, 6, 11);

    cout << "[5] Data Center MST Cost: " << g.primMST() << endl;
}

int main() {
    buildingNetworkMST();
    cityRoadNetworkMST();
    electricalGridMST();
    campusFiberMST();
    dataCenterMST();

    return 0;
}

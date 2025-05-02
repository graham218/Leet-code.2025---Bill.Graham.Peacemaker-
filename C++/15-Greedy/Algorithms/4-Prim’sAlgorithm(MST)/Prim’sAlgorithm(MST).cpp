// C++ Implementations of Prim's Algorithm (Minimum Spanning Tree - MST)
// Using different approaches with detailed comments

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

// 1. Basic Prim’s Algorithm using Adjacency Matrix (O(V^2))
void primMatrix(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> key(V, INF);
    vector<bool> mstSet(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        int minKey = INF;

        // Pick minimum key vertex from the set of vertices not yet included in MST
        for (int v = 0; v < V; ++v) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        // Update key values of adjacent vertices
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "MST using Adjacency Matrix:" << endl;
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << endl;
}

// 2. Prim’s Algorithm using Min-Heap (Priority Queue) and Adjacency List (O(E log V))
void primHeap(int V, vector<vector<pair<int, int>>> &adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    key[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto &[v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.emplace(key[v], v);
                parent[v] = u;
            }
        }
    }

    cout << "MST using Min-Heap and Adjacency List:" << endl;
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << endl;
}

// 3. Prim’s Algorithm using Set (std::set) instead of priority_queue (O(E log V))
void primSet(int V, vector<vector<pair<int, int>>>& adj) {
    set<pair<int, int>> st;
    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    key[0] = 0;
    st.insert({0, 0});

    while (!st.empty()) {
        auto [k, u] = *st.begin();
        st.erase(st.begin());

        inMST[u] = true;

        for (auto &[v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                st.erase({key[v], v});
                key[v] = weight;
                parent[v] = u;
                st.insert({key[v], v});
            }
        }
    }

    cout << "MST using Set and Adjacency List:" << endl;
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << endl;
}

// 4. Prim’s Algorithm with Custom Min-Heap (manual heapify)
// This implementation is more educational and not typically used in practice
struct MinHeapNode {
    int v, key;
};

class MinHeap {
    vector<MinHeapNode> heap;
    vector<int> pos;
    int size;
public:
    MinHeap(int V) : size(V) {
        heap.resize(V);
        pos.resize(V);
        for (int v = 0; v < V; ++v) {
            heap[v] = {v, INF};
            pos[v] = v;
        }
        heap[0].key = 0;
    }

    void minHeapify(int idx) {
        int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
        if (left < size && heap[left].key < heap[smallest].key)
            smallest = left;
        if (right < size && heap[right].key < heap[smallest].key)
            smallest = right;
        if (smallest != idx) {
            swap(pos[heap[idx].v], pos[heap[smallest].v]);
            swap(heap[idx], heap[smallest]);
            minHeapify(smallest);
        }
    }

    bool isInMinHeap(int v) { return pos[v] < size; }

    MinHeapNode extractMin() {
        MinHeapNode root = heap[0];
        heap[0] = heap[size - 1];
        pos[heap[0].v] = 0;
        --size;
        minHeapify(0);
        return root;
    }

    void decreaseKey(int v, int key) {
        int i = pos[v];
        heap[i].key = key;
        while (i && heap[i].key < heap[(i - 1) / 2].key) {
            pos[heap[i].v] = (i - 1) / 2;
            pos[heap[(i - 1) / 2].v] = i;
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    bool empty() { return size == 0; }
};

void primCustomHeap(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> key(V, INF), parent(V, -1);
    vector<bool> inMST(V, false);
    MinHeap mh(V);

    while (!mh.empty()) {
        MinHeapNode node = mh.extractMin();
        int u = node.v;
        inMST[u] = true;

        for (auto &[v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                mh.decreaseKey(v, key[v]);
            }
        }
    }

    cout << "MST using Custom MinHeap:" << endl;
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << endl;
}

// 5. Prim’s Algorithm with Priority Queue and Edge List (for sparse graphs)
void primEdgeList(int V, vector<tuple<int, int, int>>& edges) {
    vector<vector<pair<int, int>>> adj(V);
    for (auto &[u, v, w] : edges) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    primHeap(V, adj);  // Reuse heap-based version
}

// Sample usage
int main() {
    vector<vector<int>> matrix = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    vector<vector<pair<int, int>>> adj = {
        {{1,2}, {3,6}},
        {{0,2}, {2,3}, {3,8}, {4,5}},
        {{1,3}, {4,7}},
        {{0,6}, {1,8}, {4,9}},
        {{1,5}, {2,7}, {3,9}}
    };

    vector<tuple<int, int, int>> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5},
        {2, 4, 7}, {3, 4, 9}
    };

    primMatrix(matrix);
    primHeap(5, adj);
    primSet(5, adj);
    primCustomHeap(5, adj);
    primEdgeList(5, edges);

    return 0;
}

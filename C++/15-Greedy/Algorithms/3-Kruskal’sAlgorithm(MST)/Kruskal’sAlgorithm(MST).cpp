// Kruskal's Algorithm - Minimum Spanning Tree (MST) using 5 approaches in C++
// Approaches differ by union-find optimizations and graph representations

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// Edge structure to store (weight, source, destination)
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) with path compression and union by rank
class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr) return;

        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

// Approach 1: Kruskal's using edge list and DSU with full optimizations
int kruskal1(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int mst_weight = 0;

    for (Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mst_weight += e.weight;
        }
    }
    return mst_weight;
}

// Approach 2: Kruskal's using edge list and DSU with only path compression
class DSUPathCompressionOnly {
private:
    vector<int> parent;

public:
    DSUPathCompressionOnly(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

int kruskal2(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSUPathCompressionOnly dsu(n);
    int mst_weight = 0;

    for (Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mst_weight += e.weight;
        }
    }
    return mst_weight;
}

// Approach 3: Kruskal's with DSU having no optimizations (naive find/unite)
class DSUNaive {
private:
    vector<int> parent;

public:
    DSUNaive(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

int kruskal3(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSUNaive dsu(n);
    int mst_weight = 0;

    for (Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mst_weight += e.weight;
        }
    }
    return mst_weight;
}

// Approach 4: Kruskal's with adjacency matrix converted to edge list
int kruskal4(int n, vector<vector<int>>& adjMatrix) {
    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] != 0)
                edges.push_back({i, j, adjMatrix[i][j]});
        }
    }
    return kruskal1(n, edges);
}

// Approach 5: Kruskal's using tuple representation for edges
int kruskal5(int n, vector<tuple<int, int, int>>& edgeTuples) {
    vector<Edge> edges;
    for (auto& [w, u, v] : edgeTuples) {
        edges.push_back({u, v, w});
    }
    return kruskal1(n, edges);
}

// Example usage:
int main() {
    int n = 4; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    cout << "Kruskal MST Approach 1: " << kruskal1(n, edges) << endl;
    cout << "Kruskal MST Approach 2: " << kruskal2(n, edges) << endl;
    cout << "Kruskal MST Approach 3: " << kruskal3(n, edges) << endl;

    vector<vector<int>> adjMatrix = {
        {0, 10, 6, 5},
        {10, 0, 0, 15},
        {6, 0, 0, 4},
        {5, 15, 4, 0}
    };
    cout << "Kruskal MST Approach 4 (adjacency matrix): " << kruskal4(n, adjMatrix) << endl;

    vector<tuple<int, int, int>> edgeTuples = {
        {10, 0, 1}, {6, 0, 2}, {5, 0, 3}, {15, 1, 3}, {4, 2, 3}
    };
    cout << "Kruskal MST Approach 5 (tuple-based): " << kruskal5(n, edgeTuples) << endl;

    return 0;
}

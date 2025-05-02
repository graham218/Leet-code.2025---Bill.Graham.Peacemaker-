// C++ Solution: Kruskal's Algorithm (MST) with 5 Real-World Use Case Implementations
// Each approach demonstrates a different context where MST via Kruskal’s algorithm is used.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;
    string description; // Real-world context description

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr) return;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

void kruskalMST(int n, vector<Edge>& edges, const string& context) {
    cout << "\n--- MST for: " << context << " ---\n";
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    int totalWeight = 0;

    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            totalWeight += edge.weight;
            cout << "Connect node " << edge.u << " to node " << edge.v
                 << " [Weight: " << edge.weight << "] -> " << edge.description << "\n";
        }
    }
    cout << "Total MST Weight: " << totalWeight << "\n";
}

int main() {
    // 1. Electrical Grid Planning (Cities = nodes, Cables = edges)
    vector<Edge> gridEdges = {
        {0, 1, 4, "Connect power stations"},
        {0, 2, 3, "Lay main cable"},
        {1, 2, 1, "Install junction switch"},
        {1, 3, 2, "Route to suburb A"},
        {2, 3, 4, "Alternative route to suburb A"},
        {3, 4, 2, "Supply suburb B"}
    };
    kruskalMST(5, gridEdges, "Electrical Grid Planning");

    // 2. Road Network Optimization (Cities = nodes, Roads = edges)
    vector<Edge> roadEdges = {
        {0, 1, 10, "Highway connection"},
        {0, 2, 6, "Rural road"},
        {0, 3, 5, "State road"},
        {1, 3, 15, "Long-distance road"},
        {2, 3, 4, "Short direct path"}
    };
    kruskalMST(4, roadEdges, "Road Network Optimization");

    // 3. Network Cabling in a Data Center (Servers = nodes, Cables = edges)
    vector<Edge> dataCenterEdges = {
        {0, 1, 1, "Patch cable A"},
        {1, 2, 2, "Patch cable B"},
        {0, 2, 2, "Backup cable"},
        {2, 3, 1, "Main data link"},
        {3, 4, 3, "External connection"},
        {1, 4, 4, "Redundant path"}
    };
    kruskalMST(5, dataCenterEdges, "Data Center Cabling");

    // 4. Airline Route Optimization (Airports = nodes, Routes = edges)
    vector<Edge> airlineEdges = {
        {0, 1, 100, "Nairobi to Mombasa"},
        {0, 2, 300, "Nairobi to Eldoret"},
        {1, 2, 200, "Mombasa to Eldoret"},
        {2, 3, 400, "Eldoret to Kisumu"},
        {3, 4, 150, "Kisumu to Nakuru"},
        {4, 0, 250, "Nakuru to Nairobi"}
    };
    kruskalMST(5, airlineEdges, "Airline Route Optimization");

    // 5. Laying Underground Water Pipes in Urban Areas (Buildings = nodes, Pipes = edges)
    vector<Edge> waterPipeEdges = {
        {0, 1, 7, "Main pipe along street A"},
        {1, 2, 5, "Connect apartment blocks"},
        {2, 3, 8, "Extension to neighborhood"},
        {3, 4, 9, "Connect new estate"},
        {4, 0, 10, "Loop redundancy"},
        {1, 3, 6, "Secondary line"}
    };
    kruskalMST(5, waterPipeEdges, "Urban Water Pipe Layout");

    return 0;
}

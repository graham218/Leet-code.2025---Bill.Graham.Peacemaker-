#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <numeric> // For iota

using namespace std;

// 1. Breadth-First Search (BFS)
//    - Iterative approach to traverse a graph level by level.
//    - Uses a queue to keep track of nodes to visit.
void bfs(const vector<vector<int>>& graph, int startNode, vector<bool>& visited, vector<int>& traversalOrder) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;
    traversalOrder.push_back(startNode);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                traversalOrder.push_back(v);
            }
        }
    }
}

// 2. Depth-First Search (DFS) - Recursive
//    - Recursive approach to traverse a graph by exploring as far as possible
//      along each branch before backtracking.
void dfsRecursive(const vector<vector<int>>& graph, int u, vector<bool>& visited, vector<int>& traversalOrder) {
    visited[u] = true;
    traversalOrder.push_back(u);

    for (int v : graph[u]) {
        if (!visited[v]) {
            dfsRecursive(graph, v, visited, traversalOrder);
        }
    }
}

// 3. Depth-First Search (DFS) - Iterative
//    - Iterative approach to traverse a graph using a stack.
void dfsIterative(const vector<vector<int>>& graph, int startNode, vector<bool>& visited, vector<int>& traversalOrder) {
    stack<int> s;
    s.push(startNode);
    visited[startNode] = true;
    traversalOrder.push_back(startNode);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        for (int v = graph[u].size() - 1; v >= 0; --v) { // Iterate in reverse order for same traversal as recursive
            if (!visited[graph[u][v]]) {
                s.push(graph[u][v]);
                visited[graph[u][v]] = true;
                traversalOrder.push_back(graph[u][v]);
            }
        }
    }
}



// 4. Union-Find (Disjoint Set Union) - Path Compression and Rank
//    - Efficient data structure to track disjoint sets and perform union and find operations.
//    - Path compression optimizes find operation.
//    - Rank optimization minimizes the height of the trees.

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count; // Number of disjoint sets

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        count = n;
        iota(parent.begin(), parent.end(), 0); // Initialize each element as its own parent
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            count--; // Decrease count when uniting two sets
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

// 5. Union-Find (Disjoint Set Union) - Simple Implementation (No Rank, No Path Compression)
//    - Basic implementation of Union-Find without path compression or rank optimization.
//    - Less efficient but easier to understand.
class SimpleUnionFind {
public:
    vector<int> parent;
    int count;

    SimpleUnionFind(int n) {
        parent.resize(n);
        count = n;
        iota(parent.begin(), parent.end(), 0); // Initialize each element as its own parent
    }

    int find(int x) {
        while (x != parent[x]) {
            x = parent[x];
        }
        return x;
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
            count--;
        }
    }

     bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // Example graph represented as an adjacency list
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1},
        {2}
    };
    int numNodes = graph.size();

    // 1. BFS Example
    cout << "BFS Traversal starting from node 0: ";
    vector<bool> visitedBFS(numNodes, false);
    vector<int> bfsTraversal;
    bfs(graph, 0, visitedBFS, bfsTraversal);
    for (int node : bfsTraversal) {
        cout << node << " ";
    }
    cout << endl;

    // 2. DFS Recursive Example
    cout << "DFS (Recursive) Traversal starting from node 0: ";
    vector<bool> visitedDFSRecursive(numNodes, false);
    vector<int> dfsRecursiveTraversal;
    dfsRecursive(graph, 0, visitedDFSRecursive, dfsRecursiveTraversal);
    for (int node : dfsRecursiveTraversal) {
        cout << node << " ";
    }
    cout << endl;

    // 3. DFS Iterative Example
    cout << "DFS (Iterative) Traversal starting from node 0: ";
    vector<bool> visitedDFSIterative(numNodes, false);
    vector<int> dfsIterativeTraversal;
    dfsIterative(graph, 0, visitedDFSIterative, dfsIterativeTraversal);
    for (int node : dfsIterativeTraversal) {
        cout << node << " ";
    }
    cout << endl;


    // 4. Union-Find Example (with Path Compression and Rank)
    UnionFind uf(numNodes);
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(0, 2); // Unite sets {0, 1} and {2, 3}

    cout << "Number of disjoint sets after unions: " << uf.count << endl; // Expected: 2
    cout << "Is 0 connected to 3? " << (uf.isConnected(0, 3) ? "Yes" : "No") << endl; // Expected: Yes
    cout << "Is 1 connected to 4? " << (uf.isConnected(1, 4) ? "Yes" : "No") << endl; // Expected: No

     // 5. Simple Union-Find Example (without Path Compression and Rank)
    SimpleUnionFind simpleUF(numNodes);
    simpleUF.unite(0, 1);
    simpleUF.unite(2, 3);
    simpleUF.unite(0, 2);

    cout << "Number of disjoint sets after unions (SimpleUnionFind): " << simpleUF.count << endl;
    cout << "Is 0 connected to 3? (SimpleUnionFind) " << (simpleUF.isConnected(0, 3) ? "Yes" : "No") << endl;
    cout << "Is 1 connected to 4? (SimpleUnionFind) " << (simpleUF.isConnected(1, 4) ? "Yes" : "No") << endl;

    return 0;
}

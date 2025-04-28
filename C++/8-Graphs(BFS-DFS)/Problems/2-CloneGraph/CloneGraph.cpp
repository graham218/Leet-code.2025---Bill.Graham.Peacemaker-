#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;

// Definition for a node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// Approach 1: Breadth-First Search (BFS)
Node* cloneGraphBFS(Node* node) {
    if (!node) return nullptr;

    // Use a queue for BFS traversal
    queue<Node*> q;
    q.push(node);

    // Use a map to store the mapping between original and cloned nodes
    unordered_map<Node*, Node*> nodeMap;
    // Create the clone of the starting node
    nodeMap[node] = new Node(node->val);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // Iterate through the neighbors of the current node
        for (Node* neighbor : curr->neighbors) {
            // If the neighbor has not been cloned, clone it
            if (nodeMap.find(neighbor) == nodeMap.end()) {
                nodeMap[neighbor] = new Node(neighbor->val);
                q.push(neighbor); // Add the neighbor to the queue for processing
            }
            // Add the cloned neighbor to the cloned current node's neighbors
            nodeMap[curr]->neighbors.push_back(nodeMap[neighbor]);
        }
    }
    return nodeMap[node]; // Return the clone of the starting node, which is the entry point to the cloned graph
}

// Approach 2: Depth-First Search (DFS) - Iterative using Stack
Node* cloneGraphDFSIterative(Node* node) {
    if (!node) return nullptr;

    stack<Node*> st;
    st.push(node);
    unordered_map<Node*, Node*> nodeMap;
    nodeMap[node] = new Node(node->val);

    while (!st.empty()) {
        Node* curr = st.top();
        st.pop();

        for (Node* neighbor : curr->neighbors) {
            if (nodeMap.find(neighbor) == nodeMap.end()) {
                nodeMap[neighbor] = new Node(neighbor->val);
                st.push(neighbor);
            }
            nodeMap[curr]->neighbors.push_back(nodeMap[neighbor]);
        }
    }
    return nodeMap[node];
}

// Approach 3: Depth-First Search (DFS) - Recursive
Node* cloneGraphDFSRecursive(Node* node, unordered_map<Node*, Node*>& nodeMap) {
    if (!node) return nullptr;

    // If the node has already been cloned, return the cloned node
    if (nodeMap.find(node) != nodeMap.end()) {
        return nodeMap[node];
    }

    // Clone the current node
    nodeMap[node] = new Node(node->val);

    // Recursively clone its neighbors
    for (Node* neighbor : node->neighbors) {
        nodeMap[node]->neighbors.push_back(cloneGraphDFSRecursive(neighbor, nodeMap));
    }
    return nodeMap[node];
}

Node* cloneGraphDFSRecursive(Node* node) {
    unordered_map<Node*, Node*> nodeMap;
    return cloneGraphDFSRecursive(node, nodeMap);
}

// Approach 4: Optimized BFS (Slightly more efficient)
Node* cloneGraphBFSOptimized(Node* node) {
    if (!node) return nullptr;

    queue<Node*> q;
    q.push(node);
    unordered_map<Node*, Node*> visited; // Use a map to track visited nodes and their clones
    visited[node] = new Node(node->val);

    while (!q.empty()) {
        Node* u = q.front();
        q.pop();
        for (Node* v : u->neighbors) {
            if (visited.find(v) == visited.end()) {
                visited[v] = new Node(v->val);
                q.push(v);
            }
            visited[u]->neighbors.push_back(visited[v]);
        }
    }
    return visited[node];
}

// Approach 5: Iterative DFS using stack, similar to Approach 2, but with a slight variation in variable names
Node* cloneGraphDFSIterative2(Node* node) {
    if (!node) return nullptr;

    stack<Node*> stack;
    stack.push(node);
    unordered_map<Node*, Node*> cloned;
    cloned[node] = new Node(node->val);

    while (!stack.empty()) {
        Node* u = stack.top();
        stack.pop();

        for (Node* v : u->neighbors) {
            if (cloned.find(v) == cloned.end()) {
                cloned[v] = new Node(v->val);
                stack.push(v);
            }
            cloned[u]->neighbors.push_back(cloned[v]);
        }
    }
    return cloned[node];
}

int main() {
    // Create a sample graph (for testing)
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};

    // Clone the graph using BFS
    Node* clonedGraphBFS = cloneGraphBFS(node1);
    cout << "BFS Clone starting node val: " << clonedGraphBFS->val << endl;

    // Clone using Iterative DFS
    Node* clonedGraphDFSIter = cloneGraphDFSIterative(node1);
    cout << "Iterative DFS Clone starting node val: " << clonedGraphDFSIter->val << endl;

    // Clone using Recursive DFS
    Node* clonedGraphDFSRec = cloneGraphDFSRecursive(node1);
    cout << "Recursive DFS Clone starting node val: " << clonedGraphDFSRec->val << endl;

    // Clone using Optimized BFS
    Node* clonedGraphBFSOpt = cloneGraphBFSOptimized(node1);
    cout << "Optimized BFS Clone starting node val: " << clonedGraphBFSOpt->val << endl;

    // Clone using Iterative DFS 2
    Node* clonedGraphDFSIter2 = cloneGraphDFSIterative2(node1);
    cout << "Iterative DFS 2 Clone starting node val: " << clonedGraphDFSIter2->val << endl;

    //  Clean up memory (Important to prevent memory leaks, especially for larger graphs)
    //  Iterate through the cloned graph and delete the nodes.  A map is helpful
    //  to track which nodes have been deleted.  This is CRUCIAL, and often missed.
    std::unordered_map<Node*, bool> deleted;
    std::queue<Node*> cleanupQueue;
    cleanupQueue.push(clonedGraphBFS); // Start with the cloned graph's entry point.

    while (!cleanupQueue.empty()) {
        Node* current = cleanupQueue.front();
        cleanupQueue.pop();

        if (current == nullptr || deleted[current]) continue; //important null check

        deleted[current] = true; // Mark as deleted *before* processing neighbors

        for (Node* neighbor : current->neighbors) {
            if (neighbor && !deleted[neighbor]) { //prevent double adding and null
                 cleanupQueue.push(neighbor);
            }
        }
        delete current; // Delete the node *after* processing its neighbors
    }
    return 0;
}

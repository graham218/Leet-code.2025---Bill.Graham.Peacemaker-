#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set> // Include the header for std::unordered_set
#include <memory>       // For smart pointers

// Definition for a node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() : val(0), neighbors({}) {}
    Node(int _val) : val(_val), neighbors({}) {}
    Node(int _val, std::vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

// Function to display the cloned graph (for verification)
void displayGraph(Node* node, std::unordered_map<Node*, bool>& visited) {
    if (node == nullptr || visited[node]) return;
    visited[node] = true;
    std::cout << "Node " << node->val << ": ";
    for (Node* neighbor : node->neighbors) {
        std::cout << neighbor->val << " ";
    }
    std::cout << std::endl;
    for (Node* neighbor : node->neighbors) {
        displayGraph(neighbor, visited);
    }
}

// 1. Breadth-First Search (BFS) - Iterative Approach
//   - Uses a queue to traverse the graph level by level.
//   - Suitable for scenarios where you need to maintain the level order of the graph.
//   - Example:  Cloning a network topology where you want to process devices in order of their distance from a starting point.
Node* cloneGraphBFS(Node* node) {
    if (!node) return nullptr;

    std::unordered_map<Node*, Node*> nodeMap; // Maps original nodes to their clones
    std::queue<Node*> q;
    q.push(node);

    // Clone the starting node
    nodeMap[node] = new Node(node->val);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        Node* clonedNode = nodeMap[current]; // Get the clone of the current node

        // Iterate through the neighbors of the current node
        for (Node* neighbor : current->neighbors) {
            // If the neighbor hasn't been cloned, clone it and add it to the queue
            if (nodeMap.find(neighbor) == nodeMap.end()) {
                nodeMap[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            // Add the cloned neighbor to the cloned node's neighbor list
            clonedNode->neighbors.push_back(nodeMap[neighbor]);
        }
    }
    return nodeMap[node]; // Return the clone of the starting node, which is the entry point to the cloned graph.
}

// 2. Depth-First Search (DFS) - Iterative Approach with Stack
//   - Uses a stack to traverse the graph.
//   - Useful when you need to explore deeply into each branch of the graph before moving on.
//   - Example:  Cloning a dependency graph in a software project, where you need to resolve dependencies recursively.
Node* cloneGraphDFSIterative(Node* node) {
    if (!node) return nullptr;

    std::unordered_map<Node*, Node*> nodeMap; // Maps original nodes to their clones
    std::stack<Node*> stack;
    stack.push(node);

    nodeMap[node] = new Node(node->val); // Clone the starting node

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();
        Node* clonedNode = nodeMap[current];

        for (Node* neighbor : current->neighbors) {
            if (nodeMap.find(neighbor) == nodeMap.end()) {
                nodeMap[neighbor] = new Node(neighbor->val);
                stack.push(neighbor);
            }
            clonedNode->neighbors.push_back(nodeMap[neighbor]);
        }
    }
    return nodeMap[node];
}


// 3. Depth-First Search (DFS) - Recursive Approach
//   - A recursive implementation of DFS.
//   - Often more concise than the iterative version.
//   - Example: Cloning a hierarchical organizational structure, where you can recursively clone departments and sub-departments.
Node* cloneGraphDFSRecursive(Node* node, std::unordered_map<Node*, Node*>& nodeMap) {
    if (!node) return nullptr;

    // If the node has already been cloned, return the clone
    if (nodeMap.find(node) != nodeMap.end()) {
        return nodeMap[node];
    }

    // Clone the current node
    nodeMap[node] = new Node(node->val);
    Node* clonedNode = nodeMap[node];

    // Recursively clone the neighbors
    for (Node* neighbor : node->neighbors) {
        clonedNode->neighbors.push_back(cloneGraphDFSRecursive(neighbor, nodeMap));
    }
    return clonedNode;
}

Node* cloneGraphDFSRecursive(Node* node) { // Wrapper function for the recursive DFS
    std::unordered_map<Node*, Node*> nodeMap;
    return cloneGraphDFSRecursive(node, nodeMap);
}

// 4. Optimized BFS with Visited Set - Avoids redundant processing
//   - Uses a set to keep track of visited nodes, improving efficiency.
//   - Useful when dealing with graphs that have cycles, preventing infinite loops.
//   - Example: Cloning a complex network of interconnected servers, ensuring each server is cloned only once.
Node* cloneGraphBFSOptimized(Node* node) {
    if (!node) return nullptr;

    std::unordered_map<Node*, Node*> nodeMap;
    std::unordered_set<Node*> visited;  // Use a set for visited nodes
    std::queue<Node*> q;
    q.push(node);
    visited.insert(node);
    nodeMap[node] = new Node(node->val);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        Node* clonedNode = nodeMap[current];

        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                nodeMap[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            clonedNode->neighbors.push_back(nodeMap[neighbor]);
        }
    }
    return nodeMap[node];
}

// 5. Iterative DFS with Explicitly Managed Stack and Visited Set
//    - Combines the iterative approach with a visited set for more control and efficiency.
//    - Provides a balance between the iterative and recursive approaches.
//    - Example:  Cloning a state transition graph in a game AI, where you need to carefully manage the order of state exploration.
Node* cloneGraphDFSIterativeOptimized(Node* node) {
    if (!node) return nullptr;

    std::unordered_map<Node*, Node*> nodeMap;
    std::unordered_set<Node*> visited;
    std::stack<Node*> stack;
    stack.push(node);
    visited.insert(node);
    nodeMap[node] = new Node(node->val);

    while (!stack.empty()) {
        Node* current = stack.top();
        Node* clonedNode = nodeMap[current];
        stack.pop(); // Important: Pop *before* the loop

        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                nodeMap[neighbor] = new Node(neighbor->val);
                stack.push(neighbor); // Push the neighbor onto the stack
                clonedNode->neighbors.push_back(nodeMap[neighbor]);
            }
            else {
                clonedNode->neighbors.push_back(nodeMap[neighbor]);
            }
        }
    }
    return nodeMap[node];
}

int main() {
    // Create a sample graph (you can modify this for testing)
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};

    // Test the cloneGraph functions
    std::cout << "Original Graph:" << std::endl;
    std::unordered_map<Node*, bool> visited;
    displayGraph(node1, visited);

    std::cout << "\nCloned Graph (BFS):" << std::endl;
    Node* clonedGraphBFS = cloneGraphBFS(node1);
    visited.clear(); // Clear visited map for the new graph
    displayGraph(clonedGraphBFS, visited);

    std::cout << "\nCloned Graph (DFS Iterative):" << std::endl;
    Node* clonedGraphDFSIterative = cloneGraphDFSIterative(node1);
    visited.clear();
    displayGraph(clonedGraphDFSIterative, visited);

    std::cout << "\nCloned Graph (DFS Recursive):" << std::endl;
    Node* clonedGraphDFSRecursive = cloneGraphDFSRecursive(node1);
    visited.clear();
    displayGraph(clonedGraphDFSRecursive, visited);

    std::cout << "\nCloned Graph (BFS Optimized):" << std::endl;
    Node* clonedGraphBFSOptimized = cloneGraphBFSOptimized(node1);
    visited.clear();
    displayGraph(clonedGraphBFSOptimized, visited);

    std::cout << "\nCloned Graph (DFS Iterative Optimized):" << std::endl;
    Node* clonedGraphDFSIterativeOptimized = cloneGraphDFSIterativeOptimized(node1);
    visited.clear();
    displayGraph(clonedGraphDFSIterativeOptimized, visited);
    // Remember to deallocate memory to prevent memory leaks (important for real-world applications!)
    // This is a simplified example; in a robust application, you'd use smart pointers or a graph manager.
    // Deallocation is shown here for the cloned graphs.  You would also deallocate the original graph in a full solution.
    std::unordered_map<Node*, bool> deallocated;
    std::queue<Node*> q;

    // Function to safely deallocate nodes and their neighbors
    auto safeDeallocate = [&](Node* n) {
        if (!n || deallocated[n]) return;
        deallocated[n] = true; // Mark as deallocated
        q.push(n);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            // Safely deallocate neighbors (if they haven't been already)
            for (Node* neighbor : current->neighbors) {
                if (!deallocated[neighbor]) {
                    deallocated[neighbor] = true;
                    q.push(neighbor);
                }
            }
            delete current; // Delete the node itself
        }
    };
    safeDeallocate(clonedGraphBFS);
    safeDeallocate(clonedGraphDFSIterative);
    safeDeallocate(clonedGraphDFSRecursive);
    safeDeallocate(clonedGraphBFSOptimized);
    safeDeallocate(clonedGraphDFSIterativeOptimized);

    return 0;
}

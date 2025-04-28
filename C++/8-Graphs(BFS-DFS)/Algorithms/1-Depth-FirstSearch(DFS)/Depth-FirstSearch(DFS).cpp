#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm> // For std::reverse

using namespace std;

// Basic structure to represent a graph node.  Using an adjacency list.
struct GraphNode {
    int val;
    vector<int> neighbors; // Indices of neighbors in the 'nodes' vector.

    GraphNode(int v) : val(v) {}
};

// 1. DFS for Web Crawler (Finding all linked pages)
//    -  Real-world application:  Web crawlers like those used by search engines.
//    -  The graph is the web, nodes are web pages, edges are hyperlinks.
void dfsWebCrawler(int startNodeIndex, vector<GraphNode>& nodes, unordered_set<int>& visited) {
    stack<int> s;
    s.push(startNodeIndex);
    visited.insert(startNodeIndex);

    cout << "Web Crawler DFS Order: "; // Added descriptive output

    while (!s.empty()) {
        int currentNodeIndex = s.top();
        s.pop();
        cout << nodes[currentNodeIndex].val << " "; // Output the *value* of the node

        for (int neighborIndex : nodes[currentNodeIndex].neighbors) {
            if (visited.find(neighborIndex) == visited.end()) {
                s.push(neighborIndex);
                visited.insert(neighborIndex);
            }
        }
    }
    cout << endl;
}

// 2. DFS for Maze Solving
//    - Real-world application: Pathfinding in games, robotics.
//    - The graph is the maze, nodes are cells, edges are possible movements.
bool dfsMazeSolver(int startNodeIndex, int endNodeIndex, vector<GraphNode>& nodes, unordered_set<int>& visited, vector<int>& path) {
    stack<int> s;
    s.push(startNodeIndex);
    visited.insert(startNodeIndex);
    path.push_back(startNodeIndex); // Add the starting node to the path

    while (!s.empty()) {
        int currentNodeIndex = s.top();
        if (currentNodeIndex == endNodeIndex) {
            return true; // Path found!
        }
        bool foundUnvisitedNeighbor = false; // Track if we found a valid neighbor

        for (int neighborIndex : nodes[currentNodeIndex].neighbors) {
            if (visited.find(neighborIndex) == visited.end()) {
                s.push(neighborIndex);
                visited.insert(neighborIndex);
                path.push_back(neighborIndex); // Add neighbor to path
                foundUnvisitedNeighbor = true;
                break; // Important:  Go to the new neighbor
            }
        }
        if (!foundUnvisitedNeighbor) {
            s.pop();         // No unvisited neighbors, backtrack
            path.pop_back(); // Remove from path, backtracking
        }
    }
    return false; // Path not found
}

// 3. DFS for Topological Sort
//    - Real-world application: Task scheduling, dependency resolution (e.g., in build systems).
//    - The graph represents dependencies between tasks.
void dfsTopologicalSort(int startNodeIndex, vector<GraphNode>& nodes, unordered_set<int>& visited, stack<int>& resultStack) {
    visited.insert(startNodeIndex);

    for (int neighborIndex : nodes[startNodeIndex].neighbors) {
        if (visited.find(neighborIndex) == visited.end()) {
            dfsTopologicalSort(neighborIndex, nodes, visited, resultStack);
        }
    }
    resultStack.push(startNodeIndex); // Push *after* visiting neighbors
}

// 4. DFS for Cycle Detection in Undirected Graphs
//   - Real-world application: Detecting inconsistencies in data, error checking in file systems.
//   - The graph represents relationships; a cycle indicates a problem.
bool dfsCycleDetectionUndirected(int currentNodeIndex, int parentNodeIndex, vector<GraphNode>& nodes, unordered_set<int>& visited) {
    visited.insert(currentNodeIndex);

    for (int neighborIndex : nodes[currentNodeIndex].neighbors) {
        if (neighborIndex != parentNodeIndex) { // Important: Don't go back to the parent
            if (visited.find(neighborIndex) != visited.end()) {
                return true; // Cycle detected!
            }
            if (dfsCycleDetectionUndirected(neighborIndex, currentNodeIndex, nodes, visited)) {
                return true; // Cycle detected in a recursive call
            }
        }
    }
    return false; // No cycle found
}

// 5. DFS for Finding Connected Components
//    - Real-world application: Network analysis, image processing (grouping pixels).
//    - The graph represents connections; components are groups of connected nodes.
void dfsConnectedComponents(int startNodeIndex, vector<GraphNode>& nodes, unordered_set<int>& visited, vector<int>& component) {
    stack<int> s;
    s.push(startNodeIndex);
    visited.insert(startNodeIndex);

    while (!s.empty()) {
        int currentNodeIndex = s.top();
        s.pop();
        component.push_back(currentNodeIndex); // Add to the current component

        for (int neighborIndex : nodes[currentNodeIndex].neighbors) {
            if (visited.find(neighborIndex) == visited.end()) {
                s.push(neighborIndex);
                visited.insert(neighborIndex);
            }
        }
    }
}

int main() {
    // Create a graph for testing.  The graph is represented using a vector of GraphNode objects.
    // Each GraphNode stores its value and a list of indices of its neighbors in the vector.
    vector<GraphNode> nodes = {
        {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}
    };

    // Define the connections (edges) between the nodes.  Using indices.
    nodes[0].neighbors = {1, 2};
    nodes[1].neighbors = {0, 3, 4};
    nodes[2].neighbors = {0, 5};
    nodes[3].neighbors = {1};
    nodes[4].neighbors = {1, 5, 6};
    nodes[5].neighbors = {2, 4};
    nodes[6].neighbors = {4, 7};
    nodes[7].neighbors = {6};

    cout << "--- Graph Representation ---" << endl;
    for (int i = 0; i < nodes.size(); ++i) {
        cout << "Node " << nodes[i].val << ": Neighbors = ";
        for (int neighborIndex : nodes[i].neighbors) {
            cout << neighborIndex << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 1. Web Crawler
    unordered_set<int> visitedWebCrawler;
    dfsWebCrawler(0, nodes, visitedWebCrawler); // Start from node 0

    cout << "\n--- Maze Solver ---" << endl;
    unordered_set<int> visitedMaze;
    vector<int> mazePath;
    bool pathFound = dfsMazeSolver(0, 6, nodes, visitedMaze, mazePath); // Find path from 0 to 6
    if (pathFound) {
        cout << "Path found: ";
        for (int nodeIndex : mazePath) {
            cout << nodes[nodeIndex].val << " ";
        }
        cout << endl;
    } else {
        cout << "Path not found" << endl;
    }

    cout << "\n--- Topological Sort ---" << endl;
     // Create a new graph for topological sort (it's a DAG)
    vector<GraphNode> topoNodes = {
        {0}, {1}, {2}, {3}, {4}, {5}
    };
    topoNodes[0].neighbors = {1, 2};
    topoNodes[1].neighbors = {3, 4};
    topoNodes[2].neighbors = {4};
    topoNodes[3].neighbors = {5};
    // topoNodes[4].neighbors = {}; // No outgoing edges
    // topoNodes[5].neighbors = {}; // No outgoing edges

    unordered_set<int> visitedTopoSort;
    stack<int> resultStack;
    for (int i = 0; i < topoNodes.size(); ++i) { //Iterate to handle disconnected graphs
        if (visitedTopoSort.find(i) == visitedTopoSort.end()) {
            dfsTopologicalSort(i, topoNodes, visitedTopoSort, resultStack);
        }
    }

    cout << "Topological Sort Order: ";
    while (!resultStack.empty()) {
        cout << topoNodes[resultStack.top()].val << " ";
        resultStack.pop();
    }
    cout << endl;

    cout << "\n--- Cycle Detection (Undirected) ---" << endl;
    unordered_set<int> visitedCycle;
    bool hasCycle = false;
    for (int i = 0; i < nodes.size(); ++i) { // Handle disconnected graph
        if (visitedCycle.find(i) == visitedCycle.end()) {
            if (dfsCycleDetectionUndirected(i, -1, nodes, visitedCycle)) { // -1 for no parent initially
                hasCycle = true;
                break;
            }
        }
    }
    if (hasCycle) {
        cout << "Cycle detected in the graph." << endl;
    } else {
        cout << "No cycle detected in the graph." << endl;
    }

    cout << "\n--- Connected Components ---" << endl;
    unordered_set<int> visitedComponents;
    vector<vector<int>> components;

     for (int i = 0; i < nodes.size(); ++i) {
        if (visitedComponents.find(i) == visitedComponents.end()) {
            vector<int> component;
            dfsConnectedComponents(i, nodes, visitedComponents, component);
            components.push_back(component);
        }
    }

    cout << "Connected Components:" << endl;
    for (int i = 0; i < components.size(); ++i) {
        cout << "Component " << i + 1 << ": ";
        for (int nodeIndex : components[i]) {
            cout << nodes[nodeIndex].val << " ";
        }
        cout << endl;
    }

    return 0;
}


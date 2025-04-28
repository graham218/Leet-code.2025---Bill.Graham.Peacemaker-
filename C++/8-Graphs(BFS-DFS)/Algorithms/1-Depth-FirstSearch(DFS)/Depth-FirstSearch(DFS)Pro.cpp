#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Basic structure to represent a graph using an adjacency list.
// The graph is represented as an unordered_map where the key is a node,
// and the value is a vector of its neighboring nodes.
typedef unordered_map<int, vector<int>> Graph;

// Function to add an edge to the graph.  Handles both directed and undirected graphs.
void addEdge(Graph& graph, int u, int v, bool isDirected = false) {
    graph[u].push_back(v);
    if (!isDirected) {
        graph[v].push_back(u); // For undirected graphs, add edge in both directions.
    }
}

// 1. Recursive DFS Implementation
//   - Classic DFS approach using recursion.
//   - Uses a visited set (vector) to keep track of visited nodes.
//   - Prints the nodes in the order they are visited.
void recursiveDFS(const Graph& graph, int startNode, vector<bool>& visited) {
    // Mark the current node as visited.
    visited[startNode] = true;
    cout << startNode << " "; // Process the current node (e.g., print it).

    // Iterate through the neighbors of the current node.
    for (int neighbor : graph.at(startNode)) {
        if (!visited[neighbor]) {
            // Recursively call DFS on the unvisited neighbor.
            recursiveDFS(graph, neighbor, visited);
        }
    }
}

// 2. Iterative DFS Implementation using a Stack
//   - DFS approach using a stack instead of recursion.
//   - Maintains the order of exploration similar to the recursive version.
void iterativeDFS(const Graph& graph, int startNode) {
    stack<int> nodeStack;
    vector<bool> visited(graph.size(), false); // Initialize all nodes as not visited.

    nodeStack.push(startNode); // Push the starting node onto the stack.

    while (!nodeStack.empty()) {
        int currentNode = nodeStack.top(); // Get the top node without removing it.
        nodeStack.pop();                 // Remove the top node.

        if (!visited[currentNode]) {
            visited[currentNode] = true; // Mark the node as visited.
            cout << currentNode << " ";    // Process the node.

            // Push the unvisited neighbors onto the stack.  Important:  Push in reverse
            // order of how they appear in the adjacency list.  This ensures that the
            // nodes are processed in a similar order to the recursive DFS.
            for (int neighbor : graph.at(currentNode)) {
                if (!visited[neighbor]) {
                    nodeStack.push(neighbor);
                }
            }
        }
    }
}

// 3. DFS to find a path between two nodes.
//    - Demonstrates how to use DFS to solve a specific problem: finding a path.
//    - Returns true if a path exists, false otherwise.
//    - Stores the path in the 'path' vector.
bool findPathDFS(const Graph& graph, int startNode, int endNode, vector<bool>& visited, vector<int>& path) {
    visited[startNode] = true;
    path.push_back(startNode); // Add the current node to the path.

    if (startNode == endNode) {
        return true; // Path found!
    }

    for (int neighbor : graph.at(startNode)) {
        if (!visited[neighbor]) {
            if (findPathDFS(graph, neighbor, endNode, visited, path)) {
                return true; // Path found from a neighbor.
            }
        }
    }

    // If no path found from any neighbor, remove the current node from the path.
    path.pop_back();
    return false; // No path found from this node.
}

// 4. DFS for Topological Sorting (for Directed Acyclic Graphs - DAGs)
//    -  Topological sorting is a linear ordering of nodes such that for every directed
//       edge u -> v, node u comes before node v in the ordering.
//    -  Only applicable to DAGs.
//    -  Uses DFS to find the finishing times of nodes.
//    -  Nodes are added to the 'sortedNodes' vector in reverse order of their finishing times.
void topologicalSortDFS(const Graph& graph, int startNode, vector<bool>& visited, vector<int>& sortedNodes) {
    visited[startNode] = true;

    for (int neighbor : graph.at(startNode)) {
        if (!visited[neighbor]) {
            topologicalSortDFS(graph, neighbor, visited, sortedNodes);
        }
    }

    // After visiting all neighbors, push the current node to the sorted list.
    // This ensures nodes are added in reverse order of finishing times.
    sortedNodes.push_back(startNode);
}

// 5. DFS to count connected components in an undirected graph.
//    -  A connected component is a subgraph in which any two vertices are connected
//       to each other by paths, and which is connected to no additional vertices
//       in the supergraph.
//    -  This function uses DFS to mark all nodes in a component as visited.
//    -  It counts the number of times it has to start a new DFS to visit all nodes.
void countConnectedComponentsDFS(const Graph& graph, int startNode, vector<bool>& visited) {
    visited[startNode] = true; // Mark current node as visited.
    for (int neighbor : graph.at(startNode)) {
        if (!visited[neighbor]) {
            countConnectedComponentsDFS(graph, neighbor, visited); // Explore the component.
        }
    }
}

int main() {
    // Create a graph represented as an adjacency list.
    Graph graph;
    //      0
    //     / \
    //    1---2
    //    | \ |
    //    3---4
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    // For the topological sort example
    Graph dag;
    addEdge(dag, 5, 2, true);
    addEdge(dag, 5, 0, true);
    addEdge(dag, 4, 0, true);
    addEdge(dag, 4, 1, true);
    addEdge(dag, 2, 3, true);
    addEdge(dag, 3, 1, true);
    //      5
    //    /  \
    //   2    0
    //  /    / \
    // 3    4---1

    cout << "Graph representation (Adjacency List):" << endl;
    for (const auto& [node, neighbors] : graph) {
        cout << node << ": ";
        for (int neighbor : neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 1. Recursive DFS Example
    cout << "1. Recursive DFS starting from node 0: ";
    vector<bool> visited(graph.size(), false); // Initialize visited array.
    recursiveDFS(graph, 0, visited);
    cout << endl << endl;

    // 2. Iterative DFS Example
    cout << "2. Iterative DFS starting from node 0: ";
    iterativeDFS(graph, 0);
    cout << endl << endl;

    // 3. Find Path DFS Example
    int startNode = 0;
    int endNode = 4;
    vector<bool> visitedPath(graph.size(), false);
    vector<int> path;
    if (findPathDFS(graph, startNode, endNode, visitedPath, path)) {
        cout << "3. Path found between " << startNode << " and " << endNode << ": ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl << endl;
    } else {
        cout << "3. No path found between " << startNode << " and " << endNode << endl << endl;
    }

    // 4. Topological Sort Example
    cout << "4. Topological Sort: ";
    vector<bool> visitedTopSort(dag.size(), false);
    vector<int> sortedNodes;
    //  Run DFS from each unvisited node
    for (const auto& [node, _] : dag) {
        if (!visitedTopSort[node]) {
            topologicalSortDFS(dag, node, visitedTopSort, sortedNodes);
        }
    }
    reverse(sortedNodes.begin(), sortedNodes.end()); // Reverse to get correct order.
    for (int node : sortedNodes) {
        cout << node << " ";
    }
    cout << endl << endl;

    // 5. Count Connected Components Example
    cout << "5. Counting Connected Components: ";
    Graph graph2; // Graph with multiple connected components
    addEdge(graph2, 0, 1);
    addEdge(graph2, 2, 3);
    addEdge(graph2, 4, 5);
    addEdge(graph2, 6, 6); // A single node is also a component.

    vector<bool> visitedComponents(7, false); // 7 nodes in graph2
    int componentCount = 0;
    for (int i = 0; i < 7; ++i) {
        if (!visitedComponents[i]) {
            countConnectedComponentsDFS(graph2, i, visitedComponents);
            componentCount++;
        }
    }
    cout << "Number of connected components: " << componentCount << endl;

    return 0;
}

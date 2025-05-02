#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack> // Include the stack header

using namespace std;

// Function to check if a given vertex 'v' can be added to the current path
bool isSafe(int v, vector<int>& path, vector<vector<int>>& graph, int pos) {
    // Check if the current vertex 'v' is adjacent to the previously added vertex in the path.
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if the vertex 'v' is already included in the path.  A Hamiltonian cycle visits each vertex exactly once.
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// 1.  Recursive Backtracking Approach
//    - Basic backtracking implementation.
//    - Uses recursion to explore possible paths.
//    - Time Complexity: O(n!), where n is the number of vertices.
//    - Space Complexity: O(n) for the path vector and recursion stack.
bool findHamiltonianCycle_Recursive(vector<vector<int>>& graph, vector<int>& path, int pos, int start) {
    int n = graph.size();

    // Base case: All vertices have been included in the path.
    if (pos == n) {
        // Check if there is an edge from the last vertex to the starting vertex to complete the cycle.
        if (graph[path[pos - 1]][start] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next vertex in the path.
    for (int v = 0; v < n; v++) {
        if (isSafe(v, path, graph, pos)) {
            path[pos] = v;  // Add the vertex 'v' to the current path.
            // Recursively try to find a Hamiltonian cycle from the new path.
            if (findHamiltonianCycle_Recursive(graph, path, pos + 1, start))
                return true;
            // Backtrack: If adding 'v' doesn't lead to a solution, remove it from the path.
            path[pos] = -1;
        }
    }

    // If no vertex can be added to the path, return false.
    return false;
}

// Function to initiate the recursive backtracking approach
void solveHamiltonianCycle_Recursive(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1); // Initialize the path vector with -1.
    path[0] = 0;             // Start the path from vertex 0 (you can choose any starting vertex).

    if (findHamiltonianCycle_Recursive(graph, path, 1, 0)) {
        cout << "Hamiltonian Cycle found (Recursive): ";
        for (int v : path)
            cout << v << " ";
        cout << "0" << endl; // Print the starting vertex to complete the cycle.
    } else {
        cout << "No Hamiltonian Cycle exists (Recursive)" << endl;
    }
}


// 2. Backtracking with Forward Checking
//    - Improves upon basic backtracking by adding a forward checking step.
//    - Before adding a vertex to the path, it checks if that vertex has any unvisited neighbors.
//    - This prunes the search space and can improve performance in some cases.
//    - Time Complexity: O(n!), but often faster than basic backtracking in practice.
//    - Space Complexity: O(n)
bool findHamiltonianCycle_ForwardChecking(vector<vector<int>>& graph, vector<int>& path, int pos, int start, vector<bool>& visited) {
    int n = graph.size();

    if (pos == n) {
        if (graph[path[pos - 1]][start] == 1)
            return true;
        else
            return false;
    }

    for (int v = 0; v < n; v++) {
        if (isSafe(v, path, graph, pos) && !visited[v]) {
             // Forward checking: Check if 'v' has any unvisited neighbors
            bool hasUnvisitedNeighbor = false;
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (graph[v][neighbor] == 1 && !visited[neighbor] && neighbor != start) {
                    hasUnvisitedNeighbor = true;
                    break;
                }
            }
            if (!hasUnvisitedNeighbor && pos != n-1) continue;

            path[pos] = v;
            visited[v] = true;
            if (findHamiltonianCycle_ForwardChecking(graph, path, pos + 1, start, visited))
                return true;
            path[pos] = -1;
            visited[v] = false;
        }
    }
    return false;
}

void solveHamiltonianCycle_ForwardChecking(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    vector<bool> visited(n, false);
    path[0] = 0;
    visited[0] = true;

    if (findHamiltonianCycle_ForwardChecking(graph, path, 1, 0, visited)) {
        cout << "Hamiltonian Cycle found (Forward Checking): ";
        for (int v : path)
            cout << v << " ";
         cout << "0" << endl;
    } else {
        cout << "No Hamiltonian Cycle exists (Forward Checking)" << endl;
    }
}



// 3. Backtracking with Degree Ordering
//    - Heuristic-guided backtracking.
//    - Tries to visit vertices with the lowest degree first.  The intuition is that these vertices are more constrained.
//    - Can significantly improve performance in some graphs.
//    - Time Complexity: Still O(n!) in the worst case, but often much faster in practice.
//    - Space Complexity: O(n)
bool findHamiltonianCycle_DegreeOrdering(vector<vector<int>>& graph, vector<int>& path, int pos, int start, vector<bool>& visited, vector<int>& degree) {
    int n = graph.size();

    if (pos == n) {
        if (graph[path[pos - 1]][start] == 1)
            return true;
        else
            return false;
    }

    // Create a vector of candidate vertices and sort them by their degree.
    vector<pair<int, int>> candidates; // (vertex, degree)
    for (int v = 0; v < n; v++) {
        if (isSafe(v, path, graph, pos) && !visited[v]) {
            candidates.push_back({v, degree[v]});
        }
    }
    sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
        return a.second < b.second; // Sort in ascending order of degree
    });

    for (const auto& candidate : candidates) {
        int v = candidate.first;
        path[pos] = v;
        visited[v] = true;
        if (findHamiltonianCycle_DegreeOrdering(graph, path, pos + 1, start, visited, degree))
            return true;
        path[pos] = -1;
        visited[v] = false;
    }
    return false;
}

void solveHamiltonianCycle_DegreeOrdering(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    vector<bool> visited(n, false);
    path[0] = 0;
    visited[0] = true;

    // Calculate the degree of each vertex.
    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1)
                degree[i]++;
        }
    }

    if (findHamiltonianCycle_DegreeOrdering(graph, path, 1, 0, visited, degree)) {
        cout << "Hamiltonian Cycle found (Degree Ordering): ";
        for (int v : path)
            cout << v << " ";
        cout << "0" << endl;
    } else {
        cout << "No Hamiltonian Cycle exists (Degree Ordering)" << endl;
    }
}

// 4. Backtracking with Warnsdorff's Rule (for Knight's Tour on a chessboard)
//    - A heuristic specifically designed for finding Knight's Tours (a special case of Hamiltonian paths).
//    - Prioritizes moving to the square with the fewest possible next moves.
//    -  This approach is specific to Knight's tour, but I'll adapt it to work (less efficiently) for a general graph to demonstrate the concept.  It's not ideal for general Hamiltonian cycles.
//    - Time Complexity:  Difficult to express generally, but often very efficient for Knight's Tours.  Less so for general graphs.
//    - Space Complexity: O(n)
bool findHamiltonianCycle_Warnsdorff(vector<vector<int>>& graph, vector<int>& path, int pos, int start, vector<bool>& visited) {
    int n = graph.size();

    if (pos == n) {
        if (graph[path[pos - 1]][start] == 1)
            return true;
        else
            return false;
    }

    vector<pair<int, int>> candidates; // (vertex, number of unvisited neighbors)
      for (int v = 0; v < n; v++) {
        if (isSafe(v, path, graph, pos) && !visited[v]) {
            int unvisitedNeighbors = 0;
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (graph[v][neighbor] == 1 && !visited[neighbor]) {
                    unvisitedNeighbors++;
                }
            }
            candidates.push_back({v, unvisitedNeighbors});
        }
    }

    // Sort candidates based on the number of unvisited neighbors (Warnsdorff's rule).
    sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (const auto& candidate : candidates) {
        int v = candidate.first;
        path[pos] = v;
        visited[v] = true;
        if (findHamiltonianCycle_Warnsdorff(graph, path, pos + 1, start, visited))
            return true;
        path[pos] = -1;
        visited[v] = false;
    }
    return false;
}

void solveHamiltonianCycle_Warnsdorff(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    vector<bool> visited(n, false);
    path[0] = 0;
    visited[0] = true;

    if (findHamiltonianCycle_Warnsdorff(graph, path, 1, 0, visited)) {
        cout << "Hamiltonian Cycle found (Warnsdorff's): ";
        for (int v : path)
            cout << v << " ";
        cout << "0" << endl;
    } else {
        cout << "No Hamiltonian Cycle exists (Warnsdorff's)" << endl;
    }
}

// 5. Iterative Backtracking (Stack-based)
//    - Implements backtracking using a stack instead of recursion.
//    - Can sometimes be more efficient than recursion due to reduced overhead.
//    - Time Complexity: O(n!)
//    - Space Complexity: O(n)
void solveHamiltonianCycle_Iterative(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    vector<bool> visited(n, false);
    stack<pair<int, int>> s; // (vertex, position in path)
    int start = 0;

    path[0] = start;
    visited[start] = true;
    s.push({start, 1});

    while (!s.empty()) {
        int currentVertex = s.top().first;
        int pos = s.top().second;
        s.pop();

        if (pos == n) {
            if (graph[currentVertex][start] == 1) {
                cout << "Hamiltonian Cycle found (Iterative): ";
                for (int v = 0; v < n; v++)
                    cout << path[v] << " ";
                cout << start << endl;
                return;
            }
            else
                continue; // Important: Keep searching if the last vertex doesn't connect to start.
        }

        for (int v = 0; v < n; v++) {
            if (isSafe(v, path, graph, pos) && !visited[v]) {
                path[pos] = v;
                visited[v] = true;
                s.push({v, pos + 1});
                break; // Move to the next vertex
            }
             if (v == n - 1) {
                // Backtrack: If no safe vertex is found, reset and backtrack.
                path[pos-1] = -1;
                visited[currentVertex] = false;
             }
        }
    }
    cout << "No Hamiltonian Cycle exists (Iterative)" << endl;
}



int main() {
    // Example graph represented as an adjacency matrix.
    //  0 1 2 3
    //0 0 1 0 1
    //1 1 0 1 1
    //2 0 1 0 1
    //3 1 1 1 0
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 0}
    };
    // Expected output (one possible solution):
    // Hamiltonian Cycle found: 0 1 2 3 0

    cout << "Graph:" << endl;
    for(const auto& row : graph){
        for(int val : row){
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    solveHamiltonianCycle_Recursive(graph);
    solveHamiltonianCycle_ForwardChecking(graph);
    solveHamiltonianCycle_DegreeOrdering(graph);
    solveHamiltonianCycle_Warnsdorff(graph); // Note: Not ideal for general graphs.
    solveHamiltonianCycle_Iterative(graph);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <tuple> // For using std::tuple

using namespace std;

// Approach 1: Depth-First Search (DFS) - Recursive
// Real-world application: Network connectivity analysis.  Imagine a social network where '1' represents a user and '0' represents no connection.  This algorithm can find connected components of users.
void dfsRecursive(vector<vector<char>>& grid, int row, int col) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Base cases:
    // 1. Out of bounds
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
        return;
    }
    // 2. Already visited ('0') or water ('0')
    if (grid[row][col] == '0') {
        return;
    }

    // Mark the current cell as visited.  This is crucial to prevent infinite recursion.
    grid[row][col] = '0';

    // Recursively explore adjacent cells (up, down, left, right)
    dfsRecursive(grid, row - 1, col); // Up
    dfsRecursive(grid, row + 1, col); // Down
    dfsRecursive(grid, row, col - 1); // Left
    dfsRecursive(grid, row, col + 1); // Right
}

int numIslandsDFS(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;

    // Iterate through each cell in the grid
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            // If we find land ('1') that hasn't been visited yet, it's a new island
            if (grid[i][j] == '1') {
                numIslands++;
                dfsRecursive(grid, i, j); // Explore the entire island using DFS
            }
        }
    }

    return numIslands;
}

// Approach 2: Depth-First Search (DFS) - Iterative
// Real-world application:  Web crawling.  You can use DFS to traverse links on a website, where each webpage is a node and each link is an edge.
int numIslandsDFSIterative(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;
    stack<pair<int, int>> stack; // Use a stack for iterative DFS

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] == '1') {
                numIslands++;
                stack.push({i, j}); // Start DFS from this cell

                while (!stack.empty()) {
                    pair<int, int> current = stack.top();
                    stack.pop();
                    int row = current.first;
                    int col = current.second;

                    if (row < 0 || row >= numRows || col < 0 || col >= numCols || grid[row][col] == '0') {
                        continue; // Important: Check bounds and visited status *before* pushing neighbors
                    }

                    grid[row][col] = '0'; // Mark as visited

                    // Push neighbors onto the stack (in reverse order for DFS-like behavior)
                    stack.push({row - 1, col}); // Up
                    stack.push({row + 1, col}); // Down
                    stack.push({row, col - 1}); // Left
                    stack.push({row, col + 1}); // Right
                }
            }
        }
    }
    return numIslands;
}


// Approach 3: Breadth-First Search (BFS)
// Real-world application:  Shortest path finding in a grid (though not necessarily the *most* efficient for shortest paths if weights vary).  Imagine a robot navigating a maze, where '1' is a path and '0' is a wall.
int numIslandsBFS(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;
    queue<pair<int, int>> queue; // Use a queue for BFS

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] == '1') {
                numIslands++;
                queue.push({i, j}); // Start BFS from this cell
                grid[i][j] = '0'; // Mark the starting cell as visited *before* entering the loop

                while (!queue.empty()) {
                    pair<int, int> current = queue.front();
                    queue.pop();
                    int row = current.first;
                    int col = current.second;

                    // Explore neighbors
                    int dr[] = {-1, 1, 0, 0};
                    int dc[] = {0, 0, -1, 1};
                    for (int k = 0; k < 4; ++k) {
                        int newRow = row + dr[k];
                        int newCol = col + dc[k];
                        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && grid[newRow][newCol] == '1') {
                            queue.push({newRow, newCol});
                            grid[newRow][newCol] = '0'; // Mark neighbor as visited
                        }
                    }
                }
            }
        }
    }
    return numIslands;
}

// Approach 4: Union-Find (Disjoint Set)
// Real-world application:  Network connection problems.  Imagine determining if two computers are in the same network, even if they are connected through other computers.
class UnionFind {
public:
    vector<int> parent;
    int count; // Number of connected components

    UnionFind(int n) : parent(n), count(n) {
        // Initialize each node as its own parent.
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the root of the set that 'node' belongs to, with path compression
    int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]); // Path compression:  Make the parent the root
        }
        return parent[node];
    }

    // Union (merge) the sets containing 'node1' and 'node2'
    void unite(int node1, int node2) {
        int root1 = find(node1);
        int root2 = find(node2);
        if (root1 != root2) {
            parent[root1] = root2; // Merge the two sets
            count--; // Decrement the number of connected components
        }
    }
};

int numIslandsUnionFind(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numNodes = numRows * numCols;
    UnionFind uf(numNodes);

    // Iterate through the grid.
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] == '1') {
                // Convert 2D coordinates to 1D index
                int currentNode = i * numCols + j;

                // Check neighbors (right and down only to avoid double counting)
                if (j + 1 < numCols && grid[i][j + 1] == '1') {
                    int rightNode = i * numCols + (j + 1);
                    uf.unite(currentNode, rightNode);
                }
                if (i + 1 < numRows && grid[i + 1][j] == '1') {
                    int downNode = (i + 1) * numCols + j;
                    uf.unite(currentNode, downNode);
                }
            }
            // If it is water, we don't do anything.
        }
    }

    // After processing the entire grid, the 'count' in UnionFind represents the number of islands
    int numIslands = 0;
     for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] == '1') {
                if(uf.find(i * numCols + j) == i * numCols + j)
                    numIslands++;
            }
        }
    }
    return numIslands;
    //return uf.count; //This will give wrong answer if the grid is not fully connected.
}

// Approach 5: Optimized DFS with Boundary Check Reduction
// Real-world application:  Image processing, where you need to identify connected regions of pixels.  This optimization reduces redundant boundary checks.
void dfsOptimized(vector<vector<char>>& grid, int row, int col, int numRows, int numCols) { // Pass numRows and numCols
    // Base case:  Use a single, combined condition for all boundary checks
    if (row < 0 || row >= numRows || col < 0 || col >= numCols || grid[row][col] == '0') {
        return;
    }

    grid[row][col] = '0'; // Mark as visited
    // Explore neighbors
    dfsOptimized(grid, row - 1, col, numRows, numCols);
    dfsOptimized(grid, row + 1, col, numRows, numCols);
    dfsOptimized(grid, row, col - 1, numRows, numCols);
    dfsOptimized(grid, row, col + 1, numRows, numCols);
}

int numIslandsDFSOptimized(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }
    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] == '1') {
                numIslands++;
                dfsOptimized(grid, i, j, numRows, numCols); // Pass numRows and numCols
            }
        }
    }
    return numIslands;
}

int main() {
    // Example grid (you can modify this)
    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    cout << "Original Grid:" << endl;
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Create a copy for each approach to avoid modifying the original grid
    vector<vector<char>> grid1 = grid;
    vector<vector<char>> grid2 = grid;
    vector<vector<char>> grid3 = grid;
    vector<vector<char>> grid4 = grid;
    vector<vector<char>> grid5 = grid;

    // Test and print the results for each approach
    cout << "Number of islands (DFS Recursive): " << numIslandsDFS(grid1) << endl;
    cout << "Number of islands (DFS Iterative): " << numIslandsDFSIterative(grid2) << endl;
    cout << "Number of islands (BFS):             " << numIslandsBFS(grid3) << endl;
    cout << "Number of islands (Union-Find):      " << numIslandsUnionFind(grid4) << endl;
    cout << "Number of islands (DFS Optimized):   " << numIslandsDFSOptimized(grid5) << endl;

    return 0;
}

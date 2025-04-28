#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <numeric> // For iota
#include <algorithm> // For count

using namespace std;

// Function to print the grid (for debugging purposes)
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Approach 1: Depth First Search (DFS) - Recursive
// Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
// Space Complexity: O(M * N) in the worst case (if the entire grid is land), due to the recursion stack.
void dfsRecursive(vector<vector<char>>& grid, int row, int col) {
    // Base cases:
    // 1. Out of bounds
    // 2. Current cell is water ('0') or already visited ('2')
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] != '1') {
        return;
    }

    // Mark the current cell as visited ('2')
    grid[row][col] = '2';

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

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (grid[row][col] == '1') {
                // Found a new island, increment the count
                numIslands++;
                // Explore the entire island using DFS
                dfsRecursive(grid, row, col);
            }
        }
    }

    return numIslands;
}

// Approach 2: Depth First Search (DFS) - Iterative
// Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
// Space Complexity: O(M * N) in the worst case (if the entire grid is land), due to the stack.
int numIslandsDFSIterative(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (grid[row][col] == '1') {
                numIslands++;
                stack<pair<int, int>> islandStack;
                islandStack.push({row, col});
                grid[row][col] = '2'; // Mark as visited

                while (!islandStack.empty()) {
                    pair<int, int> current = islandStack.top();
                    islandStack.pop();

                    int r = current.first;
                    int c = current.second;

                    // Explore neighbors
                    int dr[] = {-1, 1, 0, 0};
                    int dc[] = {0, 0, -1, 1};

                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];

                        if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && grid[nr][nc] == '1') {
                            grid[nr][nc] = '2'; // Mark neighbor as visited
                            islandStack.push({nr, nc});
                        }
                    }
                }
            }
        }
    }
    return numIslands;
}


// Approach 3: Breadth First Search (BFS)
// Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
// Space Complexity: O(M * N) in the worst case (if the entire grid is land), due to the queue.
int numIslandsBFS(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (grid[row][col] == '1') {
                numIslands++;
                queue<pair<int, int>> islandQueue;
                islandQueue.push({row, col});
                grid[row][col] = '2'; // Mark as visited

                while (!islandQueue.empty()) {
                    pair<int, int> current = islandQueue.front();
                    islandQueue.pop();

                    int r = current.first;
                    int c = current.second;

                    // Explore neighbors
                    int dr[] = {-1, 1, 0, 0};
                    int dc[] = {0, 0, -1, 1};

                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];

                        if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && grid[nr][nc] == '1') {
                            grid[nr][nc] = '2'; // Mark neighbor as visited
                            islandQueue.push({nr, nc});
                        }
                    }
                }
            }
        }
    }
    return numIslands;
}

// Approach 4: Optimized BFS (In-place modification)
// Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
// Space Complexity: O(min(M, N)) - improved, as the maximum size of the queue is bound by the smaller dimension.
int numIslandsBFSOptimized(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numIslands = 0;

    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (grid[r][c] == '1') {
                numIslands++;
                grid[r][c] = '0'; // Sink the island (mark as water)
                queue<pair<int, int>> q;
                q.push({r, c});

                while (!q.empty()) {
                    int row = q.front().first;
                    int col = q.front().second;
                    q.pop();

                    // Check neighbors
                    int dr[] = {-1, 1, 0, 0};
                    int dc[] = {0, 0, -1, 1};
                    for (int i = 0; i < 4; ++i) {
                        int nextRow = row + dr[i];
                        int nextCol = col + dc[i];
                        if (nextRow >= 0 && nextRow < numRows && nextCol >= 0 && nextCol < numCols && grid[nextRow][nextCol] == '1') {
                            grid[nextRow][nextCol] = '0'; // Sink neighbor
                            q.push({nextRow, nextCol});
                        }
                    }
                }
            }
        }
    }
    return numIslands;
}

// Approach 5: Disjoint Set Union (DSU)
// Time Complexity: O(M * N * α(M * N)), where α is the Inverse Ackermann function (very slow-growing, effectively constant).
// Space Complexity: O(M * N) for the parent and rank arrays.
class DisjointSet {
public:
    vector<int> parent;
    vector<int> rank;
    int count; // Number of disjoint sets

    DisjointSet(int n) : parent(n), rank(n, 0), count(n) {
        // Initialize each node as its own parent
        iota(parent.begin(), parent.end(), 0); // Fills parent with 0, 1, 2, ..., n-1
    }

    int find(int x) {
        if (parent[x] != x) {
            // Path compression: make the parent of x the root of the set
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            count--; // Decrement count when uniting two sets
        }
    }
};

int numIslandsDSU(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();
    int numCells = numRows * numCols;
    DisjointSet ds(numCells);

    // Iterate through the grid
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (grid[r][c] == '1') {
                // Calculate the 1D index for the current cell
                int currentCellIndex = r * numCols + c;

                // Check neighbors and unite them if they are also land
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && grid[nr][nc] == '1') {
                        int neighborCellIndex = nr * numCols + nc;
                        ds.unite(currentCellIndex, neighborCellIndex);
                    }
                }
            }
        }
    }

    // Count the number of connected components (islands)
    int numIslands = 0;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (grid[r][c] == '1') {
                int cellIndex = r * numCols + c;
                if (ds.find(cellIndex) == cellIndex) {
                    numIslands++;
                }
            }
        }
    }
    return numIslands;
}

int main() {
    // Example grid
    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    cout << "Original Grid:" << endl;
    printGrid(grid);

    // Test with different approaches
    vector<vector<char>> grid1 = grid;
    cout << "Number of islands (DFS Recursive): " << numIslandsDFS(grid1) << endl;

    vector<vector<char>> grid2 = grid;
    cout << "Number of islands (DFS Iterative): " << numIslandsDFSIterative(grid2) << endl;

    vector<vector<char>> grid3 = grid;
    cout << "Number of islands (BFS): " << numIslandsBFS(grid3) << endl;

    vector<vector<char>> grid4 = grid;
    cout << "Number of islands (BFS Optimized): " << numIslandsBFSOptimized(grid4) << endl;

    vector<vector<char>> grid5 = grid;
    cout << "Number of islands (DSU): " << numIslandsDSU(grid5) << endl;


    // Example 2 (More complex)
    vector<vector<char>> grid2_complex = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << "\nComplex Grid:" << endl;
    printGrid(grid2_complex);
    vector<vector<char>> grid6 = grid2_complex;
    cout << "Number of islands (DSU) on complex grid: " << numIslandsDSU(grid6) << endl;

    return 0;
}

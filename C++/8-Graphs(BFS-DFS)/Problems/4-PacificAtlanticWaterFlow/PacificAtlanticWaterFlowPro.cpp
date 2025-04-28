#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional> // Added for std::function
#include <stack>      // Added for std::stack

using namespace std;

// Define the possible directions to move (up, down, left, right)
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

// 1. DFS Approach 1: Simple Recursive DFS
//   - Directly implements the recursive DFS approach.
//   - Pro: Simple to understand and implement.
//   - Con: Can be slow for large grids due to recursion overhead and potential stack overflow.
vector<vector<int>> pacificAtlanticDFS1(vector<vector<int>>& heights) {
    if (heights.empty() || heights[0].empty()) return {};

    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    // Helper function for DFS
    function<void(int, int, vector<vector<bool>>&)> dfs =
        [&](int r, int c, vector<vector<bool>>& visited) { // Using std::function
        if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c]) return;
        visited[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && heights[nr][nc] >= heights[r][c]) {
                dfs(nr, nc, visited);
            }
        }
    };

    // Perform DFS from the borders of the grid
    for (int i = 0; i < m; ++i) {
        dfs(i, 0, pacific);     // Pacific border (left)
        dfs(i, n - 1, atlantic); // Atlantic border (right)
    }
    for (int j = 0; j < n; ++j) {
        dfs(0, j, pacific);     // Pacific border (top)
        dfs(m - 1, j, atlantic); // Atlantic border (bottom)
    }

    // Collect the cells that can reach both oceans
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j]) {
                result.push_back({i, j});
            }
        }
    }
    return result;
}

// 2. DFS Approach 2: Iterative DFS using Stack
//   - Implements DFS using a stack instead of recursion.
//   - Pro: Avoids recursion overhead and potential stack overflow, more memory-efficient.
//   - Con: Slightly more complex to implement than the recursive version.
vector<vector<int>> pacificAtlanticDFS2(vector<vector<int>>& heights) {
    if (heights.empty() || heights[0].empty()) return {};

    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    // Helper function for iterative DFS
    auto dfs = [&](int start_r, int start_c, vector<vector<bool>>& visited) {
        stack<pair<int, int>> stk;
        stk.push({start_r, start_c});
        visited[start_r][start_c] = true;

        while (!stk.empty()) {
            pair<int, int> curr = stk.top();
            stk.pop();
            int r = curr.first, c = curr.second;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dx[i], nc = c + dy[i];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    visited[nr][nc] = true;
                    stk.push({nr, nc});
                }
            }
        }
    };

    // Perform DFS from the borders
    for (int i = 0; i < m; ++i) {
        dfs(i, 0, pacific);
        dfs(i, n - 1, atlantic);
    }
    for (int j = 0; j < n; ++j) {
        dfs(0, j, pacific);
        dfs(m - 1, j, atlantic);
    }

    // Collect result
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j]) {
                result.push_back({i, j});
            }
        }
    }
    return result;
}

// 3. BFS Approach 1: Simple BFS
//   - Implements BFS to solve the problem.
//   - Pro: Guaranteed to find the shortest path (though not relevant for this problem, BFS is generally well-behaved).
//   - Con: Can be slightly slower than optimized DFS in some cases, potentially uses more memory.
vector<vector<int>> pacificAtlanticBFS1(vector<vector<int>>& heights) {
    if (heights.empty() || heights[0].empty()) return {};

    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    // Helper function for BFS
    auto bfs = [&](int start_r, int start_c, vector<vector<bool>>& visited) {
        queue<pair<int, int>> q;
        q.push({start_r, start_c});
        visited[start_r][start_c] = true;

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first, c = curr.second;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dx[i], nc = c + dy[i];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    };

    // Perform BFS from the borders
    for (int i = 0; i < m; ++i) {
        bfs(i, 0, pacific);
        bfs(i, n - 1, atlantic);
    }
    for (int j = 0; j < n; ++j) {
        bfs(0, j, pacific);
        bfs(m - 1, j, atlantic);
    }

    // Collect result
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j]) {
                result.push_back({i, j});
            }
        }
    }
    return result;
}

// 4. BFS Approach 2: Optimized BFS
//    - Uses a queue to perform BFS, similar to approach 3, but may have slight optimizations.
//   - Pro:  Avoids recursion, can be efficient.
//    - Con:  Slightly more complex than the recursive DFS approach.
vector<vector<int>> pacificAtlanticBFS2(vector<vector<int>>& heights) {
    if (heights.empty() || heights[0].empty()) {
        return {};
    }

    int m = heights.size();
    int n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));
    queue<pair<int, int>> q;

    // Lambda function for performing BFS
    auto bfs = [&](vector<vector<bool>>& visited, int row, int col) {
        q.push({row, col});
        visited[row][col] = true;

        while (!q.empty()) {
            auto [r, c] = q.front(); // Structured binding
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dx[i];
                int nc = c + dy[i];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    };

    // Perform BFS from Pacific and Atlantic borders
    for (int i = 0; i < m; ++i) {
        bfs(pacific, i, 0);
        bfs(atlantic, i, n - 1);
    }
    for (int j = 0; j < n; ++j) {
        bfs(pacific, 0, j);
        bfs(atlantic, m - 1, j);
    }

    // Find the intersection of cells reachable from both oceans
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j]) {
                result.push_back({i, j});
            }
        }
    }
    return result;
}

// 5. Optimized DFS with Visited Array Sharing
//   - Uses a single visited array to track reachability from both oceans to optimize memory, and a helper.
//   - Pro: Most memory-efficient, avoids redundant visited array allocations.
//   - Con:  Slightly more complex logic for handling the shared visited array.
vector<vector<int>> pacificAtlanticDFS3(vector<vector<int>>& heights) {
    if (heights.empty() || heights[0].empty()) return {};

    int m = heights.size(), n = heights[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0)); // 0: unvisited, 1: pacific, 2: atlantic, 3: both

    // Helper function for DFS
    function<void(int, int, int)> dfs =
        [&](int r, int c, int ocean) {
        if (r < 0 || r >= m || c < 0 || c >= n || (visited[r][c] & ocean)) return; // Check if already visited from this ocean
        visited[r][c] |= ocean; // Mark visited for the current ocean (1 for pacific, 2 for atlantic)
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && heights[nr][nc] >= heights[r][c]) {
                dfs(nr, nc, ocean);
            }
        }
    };

    // Perform DFS from the borders
    for (int i = 0; i < m; ++i) {
        dfs(i, 0, 1);     // Pacific (1)
        dfs(i, n - 1, 2); // Atlantic (2)
    }
    for (int j = 0; j < n; ++j) {
        dfs(0, j, 1);     // Pacific (1)
        dfs(m - 1, j, 2); // Atlantic (2)
    }

    // Collect the cells that can reach both oceans (visited[r][c] == 3)
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visited[i][j] == 3) { // Both Pacific (1) and Atlantic (2) are set: 1 | 2 == 3
                result.push_back({i, j});
            }
        }
    }
    return result;
}

int main() {
    // Example usage
    vector<vector<int>> heights = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    cout << "DFS Approach 1:\n";
    vector<vector<int>> result1 = pacificAtlanticDFS1(heights);
    for (const auto& p : result1) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    cout << "DFS Approach 2:\n";
    vector<vector<int>> result2 = pacificAtlanticDFS2(heights);
    for (const auto& p : result2) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    cout << "BFS Approach 1:\n";
    vector<vector<int>> result3 = pacificAtlanticBFS1(heights);
    for (const auto& p : result3) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    cout << "BFS Approach 2:\n";
    vector<vector<int>> result4 = pacificAtlanticBFS2(heights);
    for (const auto& p : result4) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    cout << "DFS Approach 3 (Optimized):\n";
    vector<vector<int>> result5 = pacificAtlanticDFS3(heights);
    for (const auto& p : result5) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    return 0;
}

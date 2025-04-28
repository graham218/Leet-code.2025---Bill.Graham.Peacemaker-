#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional> // Added for std::function
#include <stack>    // Added for std::stack

using namespace std;

// Approach 1: Breadth-First Search (BFS) - Optimized
class Solution1 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // Function to perform BFS from a given cell
        auto bfs = [&](vector<vector<bool>>& visited, queue<pair<int, int>>& q) {
            while (!q.empty()) {
                int r, c;
                tie(r, c) = q.front();
                q.pop();
                visited[r][c] = true; // Mark the current cell as visited
                // Explore neighbors: up, down, left, right
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i], nc = c + dc[i];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                        q.push({nr, nc}); // Add valid neighbors to the queue
                    }
                }
            }
        };

        // 1. BFS from Pacific coast (top and left edges)
        queue<pair<int, int>> pacificQueue;
        for (int r = 0; r < m; ++r) pacificQueue.push({r, 0});     // Left edge
        for (int c = 0; c < n; ++c) pacificQueue.push({0, c});     // Top edge
        bfs(pacific, pacificQueue);

        // 2. BFS from Atlantic coast (bottom and right edges)
        queue<pair<int, int>> atlanticQueue;
        for (int r = 0; r < m; ++r) atlanticQueue.push({r, n - 1}); // Right edge
        for (int c = 0; c < n; ++c) atlanticQueue.push({m - 1, c}); // Bottom edge
        bfs(atlantic, atlanticQueue);

        // 3. Find cells reachable from both oceans
        vector<vector<int>> result;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        return result;
    }
};

// Approach 2: Depth-First Search (DFS) - Optimized
class Solution2 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // Function to perform DFS from a given cell
        std::function<void(int, int, vector<vector<bool>>&, int)> dfs =  // Changed to std::function
            [&](int r, int c, vector<vector<bool>>& visited, int prevHeight) {
                if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c] || heights[r][c] < prevHeight) {
                    return; // Base case: out of bounds, already visited, or lower height
                }
                visited[r][c] = true; // Mark the current cell as visited
                // Explore neighbors: up, down, left, right
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i], nc = c + dc[i];
                    dfs(nr, nc, visited, heights[r][c]); // Recursively call DFS for neighbors
                }
            };

        // 1. DFS from Pacific coast
        for (int r = 0; r < m; ++r) dfs(r, 0, pacific, 0);     // Left edge
        for (int c = 0; c < n; ++c) dfs(0, c, pacific, 0);     // Top edge

        // 2. DFS from Atlantic coast
        for (int r = 0; r < m; ++r) dfs(r, n - 1, atlantic, 0); // Right edge
        for (int c = 0; c < n; ++c) dfs(m - 1, c, atlantic, 0); // Bottom edge

        // 3. Find cells reachable from both oceans
        vector<vector<int>> result;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        return result;
    }
};

// Approach 3: Optimized DFS with Visited Set
class Solution3 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // DFS function
       std::function<void(int, int, vector<vector<bool>>&, int)> dfs = // Changed to std::function
            [&](int r, int c, vector<vector<bool>>& visited, int prevHeight) {
                if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c] || heights[r][c] < prevHeight) {
                    return;
                }
                visited[r][c] = true;
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i], nc = c + dc[i];
                    dfs(nr, nc, visited, heights[r][c]);
                }
            };

        // Perform DFS from the edges for both oceans
        for (int r = 0; r < m; ++r) {
            dfs(r, 0, pacific, 0);
            dfs(r, n - 1, atlantic, 0);
        }
        for (int c = 0; c < n; ++c) {
            dfs(0, c, pacific, 0);
            dfs(m - 1, c, atlantic, 0);
        }

        // Collect the cells that can reach both oceans
        vector<vector<int>> result;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        return result;
    }
};

// Approach 4: BFS with Early Stopping
class Solution4 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // BFS function with early stopping
        auto bfs = [&](vector<vector<bool>>& visited, queue<pair<int, int>>& q) {
            while (!q.empty()) {
                int r, c;
                tie(r, c) = q.front();
                q.pop();
                if (visited[r][c]) continue; // Early stopping: if already visited, skip
                visited[r][c] = true;
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i], nc = c + dc[i];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                        q.push({nr, nc});
                    }
                }
            }
        };

        // BFS from Pacific and Atlantic edges
        queue<pair<int, int>> pacificQueue;
        for (int r = 0; r < m; ++r) pacificQueue.push({r, 0});
        for (int c = 0; c < n; ++c) pacificQueue.push({0, c});
        bfs(pacific, pacificQueue);

        queue<pair<int, int>> atlanticQueue;
        for (int r = 0; r < m; ++r) atlanticQueue.push({r, n - 1});
        for (int c = 0; c < n; ++c) atlanticQueue.push({m - 1, c});
        bfs(atlantic, atlanticQueue);

        // Collect result
        vector<vector<int>> result;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        return result;
    }
};

// Approach 5: Iterative DFS with Stack
class Solution5 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // Iterative DFS using a stack
        auto iterativeDfs = [&](vector<vector<bool>>& visited, vector<pair<int, int>>& starts) {
            stack<pair<int, int>> stack; // Fix: Moved stack declaration here
            for (auto start : starts) {
                stack.push(start);
            }

            while (!stack.empty()) {
                pair<int, int> curr = stack.top();
                stack.pop();
                int r = curr.first, c = curr.second;

                if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c]) continue;
                visited[r][c] = true;

                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i], nc = c + dc[i];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && heights[nr][nc] >= heights[r][c]) {
                        stack.push({nr, nc});
                    }
                }
            }
        };

        // 1. DFS from Pacific coast
        vector<pair<int, int>> pacificStarts;
        for (int r = 0; r < m; ++r) pacificStarts.push_back({r, 0});
        for (int c = 0; c < n; ++c) pacificStarts.push_back({0, c});
        iterativeDfs(pacific, pacificStarts);

        // 2. DFS from Atlantic coast
        vector<pair<int, int>> atlanticStarts;
        for (int r = 0; r < m; ++r) atlanticStarts.push_back({r, n - 1});
        for (int c = 0; c < n; ++c) atlanticStarts.push_back({m - 1, c});
        iterativeDfs(atlantic, atlanticStarts);

        // 3. Find intersection
        vector<vector<int>> result;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        return result;
    }
};

int main() {
    // Example usage
    vector<vector<int>> heights = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    Solution1 sol1;
    vector<vector<int>> result1 = sol1.pacificAtlantic(heights);
    cout << "BFS Approach:" << endl;
    for (const auto& row : result1) {
        cout << "[" << row[0] << ", " << row[1] << "]" << endl;
    }

    Solution2 sol2;
    vector<vector<int>> result2 = sol2.pacificAtlantic(heights);
    cout << "\nDFS Approach:" << endl;
    for (const auto& row : result2) {
        cout << "[" << row[0] << ", " << row[1] << "]" << endl;
    }

    Solution3 sol3;
    vector<vector<int>> result3 = sol3.pacificAtlantic(heights);
    cout << "\nOptimized DFS Approach:" << endl;
     for (const auto& row : result3) {
        cout << "[" << row[0] << ", " << row[1] << "]" << endl;
    }

    Solution4 sol4;
    vector<vector<int>> result4 = sol4.pacificAtlantic(heights);
    cout << "\nBFS with Early Stopping Approach:" << endl;
    for (const auto& row : result4) {
        cout << "[" << row[0] << ", " << row[1] << "]" << endl;
    }

    Solution5 sol5;
    vector<vector<int>> result5 = sol5.pacificAtlantic(heights);
    cout << "\nIterative DFS Approach:" << endl;
    for (const auto& row : result5) {
        cout << "[" << row[0] << ", " << row[1] << "]" << endl;
    }
    return 0;
}

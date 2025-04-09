/**
 * Pacific Atlantic Water Flow
 *
 * Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
 * the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches
 * the right and bottom edges.
 *
 * Water can only flow in four directions (up, down, left, or right) from a cell to another cell with height less than or equal to it.
 *
 * Return a 2D list of the cells that can flow to both the Pacific and Atlantic ocean.
 *
 * Example 1:
 *
 * Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
 * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
 *
 * Example 2:
 *
 * Input: heights = [[2,1],[1,0]]
 * Output: [[0,0],[0,1],[1,0],[1,1]]
 *
 * Constraints:
 *
 * m == heights.length
 * n == heights[i].length
 * 1 <= m, n <= 200
 * 0 <= heights[i][j] <= 10^5
 */

/**
 * Approach 1: Depth-First Search (DFS) - Separate Functions
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */
function pacificAtlanticDFS(heights) {
    if (!heights || heights.length === 0 || !heights[0] || heights[0].length === 0) {
        return [];
    }

    const m = heights.length;
    const n = heights[0].length;
    const pacificReachable = Array(m).fill(null).map(() => Array(n).fill(false));
    const atlanticReachable = Array(m).fill(null).map(() => Array(n).fill(false));

    function dfs(r, c, reachable) {
        if (reachable[r][c]) {
            return;
        }
        reachable[r][c] = true;
        const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
        for (const [dr, dc] of directions) {
            const newR = r + dr;
            const newC = c + dc;
            if (newR >= 0 && newR < m && newC >= 0 && newC < n && heights[newR][newC] >= heights[r][c]) {
                dfs(newR, newC, reachable);
            }
        }
    }

    for (let r = 0; r < m; r++) {
        dfs(r, 0, pacificReachable);
        dfs(r, n - 1, atlanticReachable);
    }
    for (let c = 0; c < n; c++) {
        dfs(0, c, pacificReachable);
        dfs(m - 1, c, atlanticReachable);
    }

    const result = [];
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                result.push([r, c]);
            }
        }
    }
    return result;
}

/**
 * Approach 2: Depth-First Search (DFS) - Single Function
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */
function pacificAtlanticDFSCombined(heights) {
    if (!heights || heights.length === 0 || !heights[0] || heights[0].length === 0) {
        return [];
    }

    const m = heights.length;
    const n = heights[0].length;
    const pacificReachable = Array(m).fill(null).map(() => Array(n).fill(false));
    const atlanticReachable = Array(m).fill(null).map(() => Array(n).fill(false));

    function dfs(r, c, reachable) {
        if (r < 0 || r >= m || c < 0 || c >= n || reachable[r][c]) return;
        reachable[r][c] = true;
        const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
        for (const [dr, dc] of directions) {
            const newR = r + dr;
            const newC = c + dc;
            if (newR >= 0 && newR < m && newC >= 0 && newC < n && heights[newR][newC] >= heights[r][c]) {
                dfs(newR, newC, reachable);
            }
        }
    }

    for (let r = 0; r < m; r++) {
        dfs(r, 0, pacificReachable);
        dfs(r, n - 1, atlanticReachable);
    }
    for (let c = 0; c < n; c++) {
        dfs(0, c, pacificReachable);
        dfs(m - 1, c, atlanticReachable);
    }

    const result = [];
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                result.push([r, c]);
            }
        }
    }
    return result;
}

/**
 * Approach 3: Breadth-First Search (BFS)
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */
function pacificAtlanticBFS(heights) {
    if (!heights || heights.length === 0 || !heights[0] || heights[0].length === 0) {
        return [];
    }

    const m = heights.length;
    const n = heights[0].length;
    const pacificReachable = Array(m).fill(null).map(() => Array(n).fill(false));
    const atlanticReachable = Array(m).fill(null).map(() => Array(n).fill(false));

    function bfs(queue, reachable) {
        while (queue.length > 0) {
            const [r, c] = queue.shift();
            reachable[r][c] = true;
            const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
            for (const [dr, dc] of directions) {
                const newR = r + dr;
                const newC = c + dc;
                if (newR >= 0 && newR < m && newC >= 0 && newC < n && heights[newR][newC] >= heights[r][c] && !reachable[newR][newC]) {
                    queue.push([newR, newC]);
                }
            }
        }
    }

    const pacificQueue = [];
    const atlanticQueue = [];

    for (let r = 0; r < m; r++) {
        pacificQueue.push([r, 0]);
        atlanticQueue.push([r, n - 1]);
    }
    for (let c = 0; c < n; c++) {
        pacificQueue.push([0, c]);
        atlanticQueue.push([m - 1, c]);
    }

    bfs(pacificQueue, pacificReachable);
    bfs(atlanticQueue, atlanticReachable);

    const result = [];
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                result.push([r, c]);
            }
        }
    }
    return result;
}

/**
 * Approach 4: Optimized DFS with Visited Set
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */
function pacificAtlanticDFSOptimized(heights) {
    if (!heights || heights.length === 0 || !heights[0] || heights[0].length === 0) {
        return [];
    }

    const m = heights.length;
    const n = heights[0].length;
    const pacificReachable = new Set();
    const atlanticReachable = new Set();

    function dfs(r, c, reachable) {
        const key = `${r}-${c}`;
        if (r < 0 || r >= m || c < 0 || c >= n || reachable.has(key)) return;
        reachable.add(key);
        const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
        for (const [dr, dc] of directions) {
            const newR = r + dr;
            const newC = c + dc;
            if (newR >= 0 && newR < m && newC >= 0 && newC < n && heights[newR][newC] >= heights[r][c]) {
                dfs(newR, newC, reachable);
            }
        }
    }

    for (let r = 0; r < m; r++) {
        dfs(r, 0, pacificReachable);
        dfs(r, n - 1, atlanticReachable);
    }
    for (let c = 0; c < n; c++) {
        dfs(0, c, pacificReachable);
        dfs(m - 1, c, atlanticReachable);
    }

    const result = [];
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            const key = `${r}-${c}`;
            if (pacificReachable.has(key) && atlanticReachable.has(key)) {
                result.push([r, c]);
            }
        }
    }
    return result;
}

/**
 * Approach 5: Iterative DFS with Stack
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */
function pacificAtlanticDFSIterative(heights) {
    if (!heights || heights.length === 0 || !heights[0] || heights[0].length === 0) {
        return [];
    }

    const m = heights.length;
    const n = heights[0].length;
    const pacificReachable = Array(m).fill(null).map(() => Array(n).fill(false));
    const atlanticReachable = Array(m).fill(null).map(() => Array(n).fill(false));

    function dfsIterative(stack, reachable) {
        while (stack.length > 0) {
            const [r, c] = stack.pop();
            if (reachable[r][c]) continue;
            reachable[r][c] = true;
            const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
            for (const [dr, dc] of directions) {
                const newR = r + dr;
                const newC = c + dc;
                if (newR >= 0 && newR < m && newC >= 0 && newC < n && heights[newR][newC] >= heights[r][c]) {
                    stack.push([newR, newC]);
                }
            }
        }
    }

    const pacificStack = [];
    const atlanticStack = [];

    for (let r = 0; r < m; r++) {
        pacificStack.push([r, 0]);
        atlanticStack.push([r, n - 1]);
    }
    for (let c = 0; c < n; c++) {
        pacificStack.push([0, c]);
        atlanticStack.push([m - 1, c]);
    }

    dfsIterative(pacificStack, pacificReachable);
    dfsIterative(atlanticStack, atlanticReachable);

    const result = [];
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                result.push([r, c]);
            }
        }
    }
    return result;
}



// Example Usage and Output
const heights1 = [[1, 2, 2, 3, 5], [3, 2, 3, 4, 4], [2, 4, 5, 3, 1], [6, 7, 1, 4, 5], [5, 1, 1, 2, 4]];
const heights2 = [[2, 1], [1, 0]];

console.log("Input 1:");
console.log(heights1);
console.log("Input 2:");
console.log(heights2);


console.log("\nApproach 1: DFS - Separate Functions");
console.log("Output 1:", pacificAtlanticDFS(heights1));
console.log("Output 2:", pacificAtlanticDFS(heights2));

console.log("\nApproach 2: DFS - Single Function");
console.log("Output 1:", pacificAtlanticDFSCombined(heights1));
console.log("Output 2:", pacificAtlanticDFSCombined(heights2));

console.log("\nApproach 3: BFS");
console.log("Output 1:", pacificAtlanticBFS(heights1));
console.log("Output 2:", pacificAtlanticBFS(heights2));

console.log("\nApproach 4: Optimized DFS with Visited Set");
console.log("Output 1:", pacificAtlanticDFSOptimized(heights1));
console.log("Output 2:", pacificAtlanticDFSOptimized(heights2));

console.log("\nApproach 5: Iterative DFS with Stack");
console.log("Output 1:", pacificAtlanticDFSIterative(heights1));
console.log("Output 2:", pacificAtlanticDFSIterative(heights2));

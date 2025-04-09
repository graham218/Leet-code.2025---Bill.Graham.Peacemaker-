/**
 * Number of Islands
 *
 * Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are all
 * surrounded by water.
 *
 * Example 1:
 *
 * Input:
 * [
 * ["1","1","1","1","0"],
 * ["1","1","0","1","0"],
 * ["1","1","0","0","0"],
 * ["0","0","0","0","0"]
 * ]
 * Output: 1
 *
 * Example 2:
 *
 * Input:
 * [
 * ["1","1","0","0","0"],
 * ["1","1","0","0","0"],
 * ["0","0","1","0","0"],
 * ["0","0","0","1","1"]
 * ]
 * Output: 3
 */

/**
 * Approach 1: Depth First Search (DFS) - Iterative with Stack
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst case (when the grid is filled with '1's).
 */
function numIslandsDFSStack(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;
  const stack = [];

  const visitLand = (r, c) => {
    stack.push([r, c]);
    while (stack.length > 0) {
      const [row, col] = stack.pop();
      if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] === '0') {
        continue;
      }
      grid[row][col] = '0'; // Mark as visited
      stack.push([row + 1, col]);
      stack.push([row - 1, col]);
      stack.push([row, col + 1]);
      stack.push([row, col - 1]);
    }
  };

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === '1') {
        numIslands++;
        visitLand(r, c);
      }
    }
  }

  return numIslands;
}

/**
 * Approach 2: Depth First Search (DFS) - Recursive
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst case (when the grid is filled with '1's) due to recursion depth.
 */
function numIslandsDFSRecursive(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;

  const visitLand = (r, c) => {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] === '0') {
      return;
    }
    grid[r][c] = '0'; // Mark as visited
    visitLand(r + 1, c);
    visitLand(r - 1, c);
    visitLand(r, c + 1);
    visitLand(r, c - 1);
  };

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === '1') {
        numIslands++;
        visitLand(r, c);
      }
    }
  }

  return numIslands;
}

/**
 * Approach 3: Breadth First Search (BFS)
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(min(M, N)) in the worst case (when the grid is a large rectangle of '1's).
 */
function numIslandsBFS(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;
  const queue = [];

  const visitLand = (r, c) => {
    queue.push([r, c]);
    while (queue.length > 0) {
      const [row, col] = queue.shift();
      if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] === '0') {
        continue;
      }
      grid[row][col] = '0'; // Mark as visited
      queue.push([row + 1, col]);
      queue.push([row - 1, col]);
      queue.push([row, col + 1]);
      queue.push([row, col - 1]);
    }
  };

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === '1') {
        numIslands++;
        visitLand(r, c);
      }
    }
  }

  return numIslands;
}

/**
 * Approach 4: Union Find (Disjoint Set)
 *
 * Time Complexity: O(M * N * α(M * N)), where α is the inverse Ackermann function,
 * which is very slow-growing, so it's almost constant.
 * Space Complexity: O(M * N)
 */
class UnionFind {
  constructor(size) {
    this.parent = new Array(size);
    this.rank = new Array(size).fill(0);
    this.count = 0; // Number of connected components
    for (let i = 0; i < size; i++) {
      this.parent[i] = i;
    }
  }

  find(i) {
    if (this.parent[i] === i) {
      return i;
    }
    this.parent[i] = this.find(this.parent[i]); // Path compression
    return this.parent[i];
  }

  union(i, j) {
    const rootP = this.find(i);
    const rootQ = this.find(j);
    if (rootP !== rootQ) {
      if (this.rank[rootP] > this.rank[rootQ]) {
        this.parent[rootQ] = rootP;
      } else if (this.rank[rootP] < this.rank[rootQ]) {
        this.parent[rootP] = rootQ;
      } else {
        this.parent[rootQ] = rootP;
        this.rank[rootP]++;
      }
      this.count--;
    }
  }

  getCount() {
    return this.count;
  }
}

function numIslandsUnionFind(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;
  const uf = new UnionFind(rows * cols);

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === '1') {
        numIslands++; // Potential island
        uf.count++;
        const index = r * cols + c;
        if (r > 0 && grid[r - 1][c] === '1') {
          uf.union(index, index - cols);
        }
        if (c > 0 && grid[r][c - 1] === '1') {
          uf.union(index, index - 1);
        }
      }
    }
  }
  return uf.getCount();
}

/**
 * Approach 5: Optimized DFS with In-Place Modification
 *
 * This approach optimizes the recursive DFS by directly modifying the grid in-place
 * and avoids unnecessary boundary checks within the recursive function.
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst-case scenario (when the entire grid is land) due to the depth of the recursion.
 */
function numIslandsDFSOptimized(grid) {
    if (!grid || grid.length === 0) {
        return 0;
    }

    const rows = grid.length;
    const cols = grid[0].length;
    let numIslands = 0;

    const sinkIsland = (r, c) => {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] === '0') {
            return;
        }

        grid[r][c] = '0'; // Sink the land
        sinkIsland(r + 1, c);
        sinkIsland(r - 1, c);
        sinkIsland(r, c + 1);
        sinkIsland(r, c - 1);
    };

    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (grid[r][c] === '1') {
                numIslands++;
                sinkIsland(r, c);
            }
        }
    }

    return numIslands;
}



// Example Usage and Verification
const grid1 = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
];

const grid2 = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
];

const grid3 = [
    ["1","1","1"],
    ["0","1","0"],
    ["1","1","1"]
];

const grid4 = [
    ["1","1","1","1","1"],
    ["1","0","0","0","1"],
    ["1","0","1","0","1"],
    ["1","0","0","0","1"],
    ["1","1","1","1","1"]
];

const grid5 = [
  ["1", "0", "1", "0", "1"],
  ["0", "1", "0", "1", "0"],
  ["1", "0", "1", "0", "1"],
  ["0", "1", "0", "1", "0"],
  ["1", "0", "1", "0", "1"],
];


console.log("Grid 1:");
console.log(grid1);
console.log("DFS (Stack):", numIslandsDFSStack(grid1.map(row => [...row]))); // Create a copy to avoid modifying original
console.log("DFS (Recursive):", numIslandsDFSRecursive(grid1.map(row => [...row])));
console.log("BFS:", numIslandsBFS(grid1.map(row => [...row])));
console.log("Union Find:", numIslandsUnionFind(grid1.map(row => [...row])));
console.log("DFS Optimized:", numIslandsDFSOptimized(grid1.map(row => [...row])));


console.log("\nGrid 2:");
console.log(grid2);
console.log("DFS (Stack):", numIslandsDFSStack(grid2.map(row => [...row])));
console.log("DFS (Recursive):", numIslandsDFSRecursive(grid2.map(row => [...row])));
console.log("BFS:", numIslandsBFS(grid2.map(row => [...row])));
console.log("Union Find:", numIslandsUnionFind(grid2.map(row => [...row])));
console.log("DFS Optimized:", numIslandsDFSOptimized(grid2.map(row => [...row])));

console.log("\nGrid 3:");
console.log(grid3);
console.log("DFS (Stack):", numIslandsDFSStack(grid3.map(row => [...row])));
console.log("DFS (Recursive):", numIslandsDFSRecursive(grid3.map(row => [...row])));
console.log("BFS:", numIslandsBFS(grid3.map(row => [...row])));
console.log("Union Find:", numIslandsUnionFind(grid3.map(row => [...row])));
console.log("DFS Optimized:", numIslandsDFSOptimized(grid3.map(row => [...row])));

console.log("\nGrid 4:");
console.log(grid4);
console.log("DFS (Stack):", numIslandsDFSStack(grid4.map(row => [...row])));
console.log("DFS (Recursive):", numIslandsDFSRecursive(grid4.map(row => [...row])));
console.log("BFS:", numIslandsBFS(grid4.map(row => [...row])));
console.log("Union Find:", numIslandsUnionFind(grid4.map(row => [...row])));
console.log("DFS Optimized:", numIslandsDFSOptimized(grid4.map(row => [...row])));

console.log("\nGrid 5:");
console.log(grid5);
console.log("DFS (Stack):", numIslandsDFSStack(grid5.map(row => [...row])));
console.log("DFS (Recursive):", numIslandsDFSRecursive(grid5.map(row => [...row])));
console.log("BFS:", numIslandsBFS(grid5.map(row => [...row])));
console.log("Union Find:", numIslandsUnionFind(grid5.map(row => [...row])));
console.log("DFS Optimized:", numIslandsDFSOptimized(grid5.map(row => [...row])));

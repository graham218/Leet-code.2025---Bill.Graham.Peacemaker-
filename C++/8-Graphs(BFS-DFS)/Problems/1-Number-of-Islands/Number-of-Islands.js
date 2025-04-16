/**
 * Given a 2D grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *
 * Input:
 * [
 * ['1', '1', '1', '1', '0'],
 * ['1', '1', '0', '1', '0'],
 * ['1', '1', '0', '0', '0'],
 * ['0', '0', '0', '0', '0']
 * ]
 * Output: 1
 *
 * Example 2:
 *
 * Input:
 * [
 * ['1', '1', '0', '0', '0'],
 * ['1', '1', '0', '0', '0'],
 * ['0', '0', '1', '0', '0'],
 * ['0', '0', '0', '1', '1']
 * ]
 * Output: 3
 */

/**
 * Approach 1: Depth First Search (DFS)
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst case (when the grid is filled with '1's), due to the recursion stack.
 */
function numIslandsDFS(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;

  function dfs(row, col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] === '0') {
      return;
    }

    grid[row][col] = '0'; // Mark the current land as visited
    // Explore adjacent cells
    dfs(row + 1, col);
    dfs(row - 1, col);
    dfs(row, col + 1);
    dfs(row, col - 1);
  }

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === '1') {
        numIslands++;
        dfs(i, j);
      }
    }
  }

  return numIslands;
}

/**
 * Approach 2: Breadth First Search (BFS)
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(min(M, N)) in the worst case, due to the queue size.
 */
function numIslandsBFS(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;
  const queue = [];

  const directions = [
    [0, 1],
    [0, -1],
    [1, 0],
    [-1, 0],
  ];

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === '1') {
        numIslands++;
        queue.push([i, j]);
        grid[i][j] = '0'; // Mark the current land as visited

        while (queue.length > 0) {
          const [currRow, currCol] = queue.shift();

          for (const [deltaRow, deltaCol] of directions) {
            const nextRow = currRow + deltaRow;
            const nextCol = currCol + deltaCol;

            if (
              nextRow >= 0 &&
              nextRow < rows &&
              nextCol >= 0 &&
              nextCol < cols &&
              grid[nextRow][nextCol] === '1'
            ) {
              grid[nextRow][nextCol] = '0'; // Mark the neighbor as visited
              queue.push([nextRow, nextCol]);
            }
          }
        }
      }
    }
  }

  return numIslands;
}

/**
 * Approach 3: Union Find (Disjoint Set)
 *
 * Time Complexity: O(M * N * α(M * N)), where α is the Inverse Ackermann function,
 * which is very slowly growing and can be considered almost constant.
 * Space Complexity: O(M * N)
 */
class UnionFind {
  constructor(grid) {
    this.count = 0;
    this.parent = [];
    this.rank = [];
    const rows = grid.length;
    const cols = grid[0].length;

    for (let i = 0; i < rows; i++) {
      for (let j = 0; j < cols; j++) {
        if (grid[i][j] === '1') {
          this.parent[i * cols + j] = i * cols + j;
          this.count++;
        }
        this.rank[i * cols + j] = 0;
      }
    }
  }

  find(i) {
    if (this.parent[i] !== i) {
      this.parent[i] = this.find(this.parent[i]);
    }
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
  const uf = new UnionFind(grid);
  const directions = [
    [0, 1],
    [0, -1],
    [1, 0],
    [-1, 0],
  ];

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === '1') {
        for (const [deltaRow, deltaCol] of directions) {
          const nextRow = i + deltaRow;
          const nextCol = j + deltaCol;
          if (
            nextRow >= 0 &&
            nextRow < rows &&
            nextCol >= 0 &&
            nextCol < cols &&
            grid[nextRow][nextCol] === '1'
          ) {
            uf.union(i * cols + j, nextRow * cols + nextCol);
          }
        }
      }
    }
  }
  return uf.getCount();
}

/**
 * Approach 4: Iterative Depth First Search (DFS) with Stack
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst case (when the grid is filled with '1's).
 */
function numIslandsIterativeDFS(grid) {
  if (!grid || grid.length === 0) {
    return 0;
  }

  const rows = grid.length;
  const cols = grid[0].length;
  let numIslands = 0;
  const stack = [];

  const directions = [
    [0, 1],
    [0, -1],
    [1, 0],
    [-1, 0],
  ];

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === '1') {
        numIslands++;
        stack.push([i, j]);
        grid[i][j] = '0'; // Mark as visited

        while (stack.length > 0) {
          const [currRow, currCol] = stack.pop();

          for (const [deltaRow, deltaCol] of directions) {
            const nextRow = currRow + deltaRow;
            const nextCol = currCol + deltaCol;

            if (
              nextRow >= 0 &&
              nextRow < rows &&
              nextCol >= 0 &&
              nextCol < cols &&
              grid[nextRow][nextCol] === '1'
            ) {
              grid[nextRow][nextCol] = '0'; // Mark as visited
              stack.push([nextRow, nextCol]);
            }
          }
        }
      }
    }
  }
  return numIslands;
}

/**
 * Approach 5: Modified Input (In-place modification of grid) with DFS
 * This approach modifies the input grid directly to mark visited cells.
 *
 * Time Complexity: O(M * N), where M is the number of rows and N is the number of columns.
 * Space Complexity: O(M * N) in the worst case due to the recursion stack.  However, this approach has the advantage of not using additional data structures like a queue or visited set, but it modifies the input.
 */
function numIslandsModifiedInputDFS(grid) {
    if (!grid || grid.length === 0) {
        return 0;
    }

    const rows = grid.length;
    const cols = grid[0].length;
    let numIslands = 0;

    function dfs(row, col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] === '0') {
            return;
        }

        grid[row][col] = '0'; // Mark the current cell as visited by changing its value
        dfs(row + 1, col);
        dfs(row - 1, col);
        dfs(row, col + 1);
        dfs(row, col - 1);
    }

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (grid[i][j] === '1') {
                numIslands++;
                dfs(i, j);
            }
        }
    }
    return numIslands;
}



// Example Usage:
const grid1 = [
  ['1', '1', '1', '1', '0'],
  ['1', '1', '0', '1', '0'],
  ['1', '1', '0', '0', '0'],
  ['0', '0', '0', '0', '0'],
];

const grid2 = [
  ['1', '1', '0', '0', '0'],
  ['1', '1', '0', '0', '0'],
  ['0', '0', '1', '0', '0'],
  ['0', '0', '0', '1', '1'],
];

const grid3 = [
    ['1', '1', '1'],
    ['0', '1', '0'],
    ['1', '1', '1']
];

const grid4 = [
    ['1', '0', '1', '1', '1'],
    ['1', '0', '1', '0', '1'],
    ['1', '1', '1', '0', '1']
];

const grid5 = [
  ['0', '1', '0'],
  ['1', '0', '1'],
  ['0', '1', '0']
];


console.log("Input Grid 1:", grid1);
console.log("DFS:", numIslandsDFS(grid1)); // Output: 1
console.log("BFS:", numIslandsBFS(grid1)); // Output: 1
console.log("Union Find:", numIslandsUnionFind(grid1)); // Output: 1
console.log("Iterative DFS:", numIslandsIterativeDFS(grid1)); // Output: 1

// IMPORTANT:  Make a copy, because the Modified DFS *changes* the input.
const grid1Copy = grid1.map(row => [...row]);
console.log("Modified Input DFS:", numIslandsModifiedInputDFS(grid1Copy));
console.log("Modified Grid 1:", grid1Copy); // The grid1Copy is now modified.

console.log("\nInput Grid 2:", grid2);
console.log("DFS:", numIslandsDFS(grid2)); // Output: 3
console.log("BFS:", numIslandsBFS(grid2)); // Output: 3
console.log("Union Find:", numIslandsUnionFind(grid2)); // Output: 3
console.log("Iterative DFS:", numIslandsIterativeDFS(grid2)); // Output: 3
const grid2Copy = grid2.map(row => [...row]);
console.log("Modified Input DFS:", numIslandsModifiedInputDFS(grid2Copy));
console.log("Modified Grid 2:", grid2Copy);

console.log("\nInput Grid 3:", grid3);
console.log("DFS:", numIslandsDFS(grid3)); // Output: 1
console.log("BFS:", numIslandsBFS(grid3)); // Output: 1
console.log("Union Find:", numIslandsUnionFind(grid3)); // Output: 1
console.log("Iterative DFS:", numIslandsIterativeDFS(grid3)); // Output: 1
const grid3Copy = grid3.map(row => [...row]);
console.log("Modified Input DFS:", numIslandsModifiedInputDFS(grid3Copy));
console.log("Modified Grid 3:", grid3Copy);

console.log("\nInput Grid 4:", grid4);
console.log("DFS:", numIslandsDFS(grid4)); // Output: 3
console.log("BFS:", numIslandsBFS(grid4)); // Output: 3
console.log("Union Find:", numIslandsUnionFind(grid4)); // Output: 3
console.log("Iterative DFS:", numIslandsIterativeDFS(grid4)); // Output: 3
const grid4Copy = grid4.map(row => [...row]);
console.log("Modified Input DFS:", numIslandsModifiedInputDFS(grid4Copy));
console.log("Modified Grid 4:", grid4Copy);

console.log("\nInput Grid 5:", grid5);
console.log("DFS:", numIslandsDFS(grid5)); // Output = 2
console.log("BFS:", numIslandsBFS(grid5)); // Output = 2
console.log("Union Find:", numIslandsUnionFind(grid5));  // Output: 2
console.log("Iterative DFS:", numIslandsIterativeDFS(grid5)); // Output: 2
const grid5Copy = grid5.map(row => [...row]);
console.log("Modified Input DFS:", numIslandsModifiedInputDFS(grid5Copy));
console.log("Modified Grid 5:", grid5Copy);

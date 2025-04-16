/**
 * Pacific Atlantic Water Flow
 *
 * Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
 * the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches
 * the right and bottom edges.
 *
 * Water can only flow in four directions: up, down, left, or right, from a cell to another cell with height less than or equal to itself.
 *
 * Find a list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.
 *
 * Example:
 *
 * Given the following 5x5 matrix:
 *
 * [[1,2,2,3,5],
 * [3,2,3,4,4],
 * [2,4,5,3,1],
 * [6,7,1,4,5],
 * [5,1,1,2,4]]
 *
 * Return:
 *
 * [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
 *
 *
 * Constraints:
 *
 * m == matrix.length
 * n == matrix[r].length
 * 1 <= m, n <= 200
 * 0 <= matrix[r][c] <= 10^5
 */

const pacificAtlantic = (matrix) => {
  if (!matrix || matrix.length === 0 || !matrix[0] || matrix[0].length === 0) {
    return [];
  }

  const numRows = matrix.length;
  const numCols = matrix[0].length;
  const pacificReachable = Array(numRows)
    .fill(null)
    .map(() => Array(numCols).fill(false));
  const atlanticReachable = Array(numRows)
    .fill(null)
    .map(() => Array(numCols).fill(false));

  const directions = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0],
  ];

  const dfs = (row, col, reachable) => {
    if (reachable[row][col]) {
      return;
    }
    reachable[row][col] = true;

    for (const [deltaRow, deltaCol] of directions) {
      const newRow = row + deltaRow;
      const newCol = col + deltaCol;
      if (
        newRow >= 0 &&
        newRow < numRows &&
        newCol >= 0 &&
        newCol < numCols &&
        matrix[newRow][newCol] >= matrix[row][col]
      ) {
        dfs(newRow, newCol, reachable);
      }
    }
  };

  // Start DFS from the edges for both oceans
  for (let col = 0; col < numCols; col++) {
    dfs(0, col, pacificReachable);
    dfs(numRows - 1, col, atlanticReachable);
  }
  for (let row = 0; row < numRows; row++) {
    dfs(row, 0, pacificReachable);
    dfs(row, numCols - 1, atlanticReachable);
  }

  const result = [];
  for (let row = 0; row < numRows; row++) {
    for (let col = 0; col < numCols; col++) {
      if (pacificReachable[row][col] && atlanticReachable[row][col]) {
        result.push([row, col]);
      }
    }
  }
  return result;
};

// Approach 1: DFS (Depth First Search)
const approach1 = (matrix) => {
    return pacificAtlantic(matrix);
}

// Approach 2: BFS (Breadth First Search)
const pacificAtlanticBFS = (matrix) => {
    if (!matrix || matrix.length === 0 || !matrix[0] || matrix[0].length === 0) {
        return [];
    }

    const numRows = matrix.length;
    const numCols = matrix[0].length;
    const pacificReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(false));
    const atlanticReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(false));
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    const bfs = (ocean) => {
        const queue = [];
        for (let i = 0; i < numRows; i++) {
            if (ocean === 'pacific') {
                queue.push([i, 0]);
                pacificReachable[i][0] = true;
            } else {
                queue.push([i, numCols - 1]);
                atlanticReachable[i][numCols - 1] = true;
            }
        }
        for (let j = 0; j < numCols; j++) {
            if (ocean === 'pacific') {
                if(!pacificReachable[0][j]){
                    queue.push([0, j]);
                    pacificReachable[0][j] = true;
                }

            } else {
                if(!atlanticReachable[numRows-1][j]){
                  queue.push([numRows - 1, j]);
                  atlanticReachable[numRows - 1][j] = true;
                }
            }
        }

        while (queue.length > 0) {
            const [row, col] = queue.shift();

            for (const [deltaRow, deltaCol] of directions) {
                const newRow = row + deltaRow;
                const newCol = col + deltaCol;

                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                    ((ocean === 'pacific' && !pacificReachable[newRow][newCol]) ||
                     (ocean === 'atlantic' && !atlanticReachable[newRow][newCol])) &&
                    matrix[newRow][newCol] >= matrix[row][col]) {
                    if (ocean === 'pacific') {
                        pacificReachable[newRow][newCol] = true;
                    } else {
                        atlanticReachable[newRow][newCol] = true;
                    }
                    queue.push([newRow, newCol]);
                }
            }
        }
    };

    bfs('pacific');
    bfs('atlantic');

    const result = [];
    for (let row = 0; row < numRows; row++) {
        for (let col = 0; col < numCols; col++) {
            if (pacificReachable[row][col] && atlanticReachable[row][col]) {
                result.push([row, col]);
            }
        }
    }
    return result;
};

const approach2 = (matrix) => {
    return pacificAtlanticBFS(matrix);
}

// Approach 3: Optimized DFS (Slightly more efficient) -  No major changes, but good for project
const pacificAtlanticOptimizedDFS = (matrix) => {
    if (!matrix || matrix.length === 0 || !matrix[0] || matrix[0].length === 0) {
        return [];
    }

    const numRows = matrix.length;
    const numCols = matrix[0].length;
    const pacificReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(false));
    const atlanticReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(false));

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    const dfs = (row, col, reachable) => {
        if (reachable[row][col]) {
            return;
        }
        reachable[row][col] = true;

        for (const [deltaRow, deltaCol] of directions) {
            const newRow = row + deltaRow;
            const newCol = col + deltaCol;
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && matrix[newRow][newCol] >= matrix[row][col]) {
                dfs(newRow, newCol, reachable);
            }
        }
    };

    // Optimized:  Start DFS only from ocean edges
    for (let col = 0; col < numCols; col++) {
        if (!pacificReachable[0][col]) dfs(0, col, pacificReachable);
        if (!atlanticReachable[numRows - 1][col]) dfs(numRows - 1, col, atlanticReachable);
    }
    for (let row = 0; row < numRows; row++) {
        if (!pacificReachable[row][0]) dfs(row, 0, pacificReachable);
        if (!atlanticReachable[row][numCols - 1]) dfs(row, numCols - 1, atlanticReachable);
    }

    const result = [];
    for (let row = 0; row < numRows; row++) {
        for (let col = 0; col < numCols; col++) {
            if (pacificReachable[row][col] && atlanticReachable[row][col]) {
                result.push([row, col]);
            }
        }
    }
    return result;
};

const approach3 = (matrix) => {
  return pacificAtlanticOptimizedDFS(matrix);
}

// Approach 4: Iterative DFS (Using a stack) - Useful when call stack is limited
const pacificAtlanticIterativeDFS = (matrix) => {
  if (!matrix || matrix.length === 0 || !matrix[0] || matrix[0].length === 0) {
    return [];
  }

  const numRows = matrix.length;
  const numCols = matrix[0].length;
  const pacificReachable = Array(numRows)
    .fill(null)
    .map(() => Array(numCols).fill(false));
  const atlanticReachable = Array(numRows)
    .fill(null)
    .map(() => Array(numCols).fill(false));

  const directions = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0],
  ];

  const dfsIterative = (row, col, reachable) => {
    const stack = [[row, col]];

    while (stack.length > 0) {
      const [currRow, currCol] = stack.pop();

      if (reachable[currRow][currCol]) {
        continue;
      }
      reachable[currRow][currCol] = true;

      for (const [deltaRow, deltaCol] of directions) {
        const newRow = currRow + deltaRow;
        const newCol = currCol + deltaCol;
        if (
          newRow >= 0 &&
          newRow < numRows &&
          newCol >= 0 &&
          newCol < numCols &&
          matrix[newRow][newCol] >= matrix[currRow][currCol]
        ) {
          stack.push([newRow, newCol]);
        }
      }
    }
  };

  // Start DFS from the edges for both oceans
  for (let col = 0; col < numCols; col++) {
    dfsIterative(0, col, pacificReachable);
    dfsIterative(numRows - 1, col, atlanticReachable);
  }
  for (let row = 0; row < numRows; row++) {
    dfsIterative(row, 0, pacificReachable);
    dfsIterative(row, numCols - 1, atlanticReachable);
  }

  const result = [];
  for (let row = 0; row < numRows; row++) {
    for (let col = 0; col < numCols; col++) {
      if (pacificReachable[row][col] && atlanticReachable[row][col]) {
        result.push([row, col]);
      }
    }
  }
  return result;
};

const approach4 = (matrix) => {
    return pacificAtlanticIterativeDFS(matrix);
}

// Approach 5: Dynamic Programming (Memoization) - Conceptually similar to DFS, but storing results
const pacificAtlanticDP = (matrix) => {
    if (!matrix || matrix.length === 0 || !matrix[0] || matrix[0].length === 0) {
        return [];
    }

    const numRows = matrix.length;
    const numCols = matrix[0].length;
    const pacificReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(null)); // null for not visited, true/false for visited
    const atlanticReachable = Array(numRows).fill(null).map(() => Array(numCols).fill(null));
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    const canReach = (row, col, reachable) => {
        if (reachable[row][col] !== null) {
            return reachable[row][col];
        }

        reachable[row][col] = true; // Mark as visited
        let canFlow = false;

        for (const [deltaRow, deltaCol] of directions) {
            const newRow = row + deltaRow;
            const newCol = col + deltaCol;
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && matrix[newRow][newCol] >= matrix[row][col]) {
                if (canReach(newRow, newCol, reachable)) { // Use recursion and check the result
                    canFlow = true;
                    break; // Important:  No need to continue if we found a path
                }
            }
        }
        reachable[row][col] = canFlow; //Store the result
        return canFlow;
    };

    // Calculate reachability for each cell
    for (let row = 0; row < numRows; row++) {
        for (let col = 0; col < numCols; col++) {
            canReach(row, col, pacificReachable);
            canReach(row, col, atlanticReachable);
        }
    }

    const result = [];
    for (let row = 0; row < numRows; row++) {
        for (let col = 0; col < numCols; col++) {
            if (pacificReachable[row][col] && atlanticReachable[row][col]) {
                result.push([row, col]);
            }
        }
    }
    return result;
};

const approach5 = (matrix) => {
    return pacificAtlanticDP(matrix);
}

// Example Usage and output
const matrix = [
  [1, 2, 2, 3, 5],
  [3, 2, 3, 4, 4],
  [2, 4, 5, 3, 1],
  [6, 7, 1, 4, 5],
  [5, 1, 1, 2, 4],
];

console.log("Input Matrix:");
console.log(matrix);

console.log("\nApproach 1: DFS");
console.log(approach1(matrix));

console.log("\nApproach 2: BFS");
console.log(approach2(matrix));

console.log("\nApproach 3: Optimized DFS");
console.log(approach3(matrix));

console.log("\nApproach 4: Iterative DFS");
console.log(approach4(matrix));

console.log("\nApproach 5: Dynamic Programming");
console.log(approach5(matrix));

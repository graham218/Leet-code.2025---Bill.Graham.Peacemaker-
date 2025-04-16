/*
Hamiltonian Cycle Problem:

A Hamiltonian cycle is a cycle in an undirected graph that visits each vertex exactly once.

This code provides five different approaches to find a Hamiltonian Cycle in a given graph:

1.  **Backtracking (Basic):** A straightforward recursive backtracking approach.
2.  **Backtracking with Adjacency Matrix:** Uses an adjacency matrix representation of the graph.
3.  **Backtracking with Degree Heuristic:** A heuristic approach that tries to visit vertices with higher degrees first.
4.  **Backtracking with Warnsdorff's Rule (for Knight's Tour):** Specifically optimized for the Knight's Tour problem (a special case of the Hamiltonian Cycle problem).
5.  **Iterative Backtracking with Stack:** An iterative approach using a stack to manage the path.

Each approach will attempt to find a Hamiltonian cycle in the graph and the result (whether a cycle was found and the path if found) will be printed to the console.

Note:  Hamiltonian Cycle problem is NP-complete, so these algorithms may take a long time to run for larger graphs.
*/

/**
 * Utility function to check if a given vertex 'v' can be added to the current path.
 * @param {number} v The vertex to check.
 * @param {number[]} path The current path.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @returns {boolean} True if the vertex can be added, false otherwise.
 */
function isSafe(v, path, graph) {
    const n = graph.length;

    // Check if the vertex 'v' is adjacent to the last vertex in the path.
    const last = path[path.length - 1];
    if (graph[last].indexOf(v) === -1) {
        return false;
    }

    // Check if the vertex 'v' is already included in the path.
    if (path.includes(v)) {
        return false;
    }

    return true;
}

// 1. Backtracking (Basic)
/**
 * Recursive function to find a Hamiltonian Cycle using basic backtracking.
 * @param {number} v The current vertex.
 * @param {number[]} path The current path.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @param {number} pos The current position in the path.
 * @param {number} n The number of vertices in the graph.
 * @returns {boolean} True if a Hamiltonian Cycle is found, false otherwise.
 */
function findHamiltonianCycleBasic(v, path, graph, pos, n) {
    // Base case: If all vertices are included in the path,
    // check if there is an edge from the last vertex to the starting vertex.
    if (pos === n) {
        if (graph[path[0]].includes(v)) {
            path.push(v); // Complete the cycle
            return true;
        } else {
            return false;
        }
    }

    // Try different vertices adjacent to the current vertex.
    for (const neighbor of graph[v]) {
        if (isSafe(neighbor, path, graph)) {
            path.push(neighbor);
            if (findHamiltonianCycleBasic(neighbor, path, graph, pos + 1, n)) {
                return true;
            }
            // Backtrack: Remove the vertex if it doesn't lead to a solution.
            path.pop();
        }
    }

    // If no adjacent vertex leads to a solution, return false.
    return false;
}

/**
 * Wrapper function to start the Hamiltonian Cycle search using basic backtracking.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @returns {number[]|null} The Hamiltonian Cycle path if found, null otherwise.
 */
function hamiltonianCycleBasic(graph) {
    const n = graph.length;
    const path = [0]; // Start from vertex 0.
    if (findHamiltonianCycleBasic(0, path, graph, 1, n)) {
        return path;
    }
    return null;
}



// 2. Backtracking with Adjacency Matrix
/**
 * Recursive function to find a Hamiltonian Cycle using backtracking with an adjacency matrix.
 * @param {number} v The current vertex.
 * @param {number[]} path The current path.
 * @param {number[][]} adjMatrix The graph represented as an adjacency matrix.
 * @param {number} pos The current position in the path.
 * @param {number} n The number of vertices in the graph.
 * @returns {boolean} True if a Hamiltonian Cycle is found, false otherwise.
 */
function findHamiltonianCycleMatrix(v, path, adjMatrix, pos, n) {
    if (pos === n) {
        if (adjMatrix[path[0]][v] === 1) {
            path.push(path[0]); // Complete the cycle
            return true;
        } else {
            return false;
        }
    }

    for (let i = 0; i < n; i++) {
        if (adjMatrix[v][i] === 1 && !path.includes(i)) {
            path.push(i);
            if (findHamiltonianCycleMatrix(i, path, adjMatrix, pos + 1, n)) {
                return true;
            }
            path.pop();
        }
    }
    return false;
}

/**
 * Wrapper function to start the Hamiltonian Cycle search using an adjacency matrix.
 * @param {number[][]} adjMatrix The graph represented as an adjacency matrix.
 * @returns {number[]|null} The Hamiltonian Cycle path if found, null otherwise.
 */
function hamiltonianCycleMatrix(adjMatrix) {
    const n = adjMatrix.length;
    const path = [0];
    if (findHamiltonianCycleMatrix(0, path, adjMatrix, 1, n)) {
        return path;
    }
    return null;
}



// 3. Backtracking with Degree Heuristic
/**
 * Recursive function to find a Hamiltonian Cycle using backtracking with a degree heuristic.
 * Tries to visit vertices with higher degrees first.
 * @param {number} v The current vertex.
 * @param {number[]} path The current path.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @param {number[]} degree The degree of each vertex.
 * @param {number} pos The current position in the path.
 * @param {number} n The number of vertices in the graph.
 * @returns {boolean} True if a Hamiltonian Cycle is found, false otherwise.
 */
function findHamiltonianCycleDegree(v, path, graph, degree, pos, n) {
    if (pos === n) {
        if (graph[path[0]].includes(v)) {
            path.push(v);
            return true;
        } else {
            return false;
        }
    }

    // Sort neighbors by degree (descending order)
    const neighbors = [...graph[v]];
    neighbors.sort((a, b) => degree[b] - degree[a]);

    for (const neighbor of neighbors) {
        if (isSafe(neighbor, path, graph)) {
            path.push(neighbor);
            if (findHamiltonianCycleDegree(neighbor, path, graph, degree, pos + 1, n)) {
                return true;
            }
            path.pop();
        }
    }
    return false;
}

/**
 * Wrapper function to start the Hamiltonian Cycle search using a degree heuristic.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @returns {number[]|null} The Hamiltonian Cycle path if found, null otherwise.
 */
function hamiltonianCycleDegree(graph) {
    const n = graph.length;
    const path = [0];
    const degree = graph.map(neighbors => neighbors.length); // Calculate degrees
    if (findHamiltonianCycleDegree(0, path, graph, degree, 1, n)) {
        return path;
    }
    return null;
}



// 4. Backtracking with Warnsdorff's Rule (for Knight's Tour)
/**
 * Recursive function to find a Knight's Tour (Hamiltonian Cycle on a chessboard)
 * using Warnsdorff's Rule.  This is a heuristic that prioritizes
 * moving to the square with the fewest possible next moves.
 * @param {number} x The current x-coordinate.
 * @param {number} y The current y-coordinate.
 * @param {number[][]} path The path represented as a 2D array.
 * @param {number} moveCount The current move number.
 * @param {number} n The size of the chessboard (n x n).
 * @param {number[][]} moves The possible knight moves.
 * @returns {boolean} True if a Knight's Tour is found, false otherwise.
 */
function findKnightTour(x, y, path, moveCount, n, moves) {
    if (moveCount === n * n) {
        return true; // All squares visited
    }

    // Get possible moves from the current position
    const possibleMoves = getPossibleMoves(x, y, path, n, moves);

    // Sort moves based on Warnsdorff's Rule (number of accessible neighbors)
    possibleMoves.sort((a, b) => countAccessibleNeighbors(a[0], a[1], path, n, moves) - countAccessibleNeighbors(b[0], b[1], path, n, moves));

    for (const [nextX, nextY] of possibleMoves) {
        path[nextX][nextY] = moveCount + 1; // Mark the square
        if (findKnightTour(nextX, nextY, path, moveCount + 1, n, moves)) {
            return true;
        } else {
            path[nextX][nextY] = -1; // Backtrack: Unmark the square
        }
    }

    return false;
}

/**
 * Gets the possible knight moves from a given position.
 * @param {number} x The current x-coordinate.
 * @param {number} y The current y-coordinate.
 * @param {number[][]} path The path array.
 * @param {number} n The size of the board.
 * @param {number[][]} moves The possible knight moves.
 * @returns {number[][]} An array of possible moves ( [x, y] pairs).
 */
function getPossibleMoves(x, y, path, n, moves) {
    const validMoves = [];
    for (const [dx, dy] of moves) {
        const newX = x + dx;
        const newY = y + dy;
        if (newX >= 0 && newX < n && newY >= 0 && newY < n && path[newX][newY] === -1) {
            validMoves.push([newX, newY]);
        }
    }
    return validMoves;
}

/**
 * Counts the number of accessible neighbors for a given position.
 * @param {number} x The x-coordinate.
 * @param {number} y The y-coordinate.
 * @param {number[][]} path The path array.
 * @param {number} n The size of the board.
 * @param {number[][]} moves The possible knight moves.
 * @returns {number} The number of accessible neighbors.
 */
function countAccessibleNeighbors(x, y, path, n, moves) {
    let count = 0;
    for (const [dx, dy] of moves) {
        const newX = x + dx;
        const newY = y + dy;
        if (newX >= 0 && newX < n && newY >= 0 && newY < n && path[newX][newY] === -1) {
            count++;
        }
    }
    return count;
}

/**
 * Wrapper function to start the Knight's Tour search.
 * @param {number} n The size of the chessboard.
 * @returns {number[][]|null} The Knight's Tour path (2D array) if found, null otherwise.
 */
function knightTour(n) {
    const path = Array(n).fill(null).map(() => Array(n).fill(-1)); // Initialize path array
    const startX = 0;
    const startY = 0;
    path[startX][startY] = 1; // Start at (0, 0)
    const moves = [
        [2, 1], [2, -1], [-2, 1], [-2, -1],
        [1, 2], [1, -2], [-1, 2], [-1, -2]
    ];

    if (findKnightTour(startX, startY, path, 1, n, moves)) {
        return path;
    }
    return null;
}



// 5. Iterative Backtracking with Stack
/**
 * Iterative function to find a Hamiltonian Cycle using a stack.
 * @param {number[][]} graph The graph represented as an adjacency list.
 * @returns {number[]|null} The Hamiltonian Cycle path if found, null otherwise.
 */
function hamiltonianCycleIterative(graph) {
    const n = graph.length;
    const stack = [[0]]; // Start with vertex 0 in the stack
    const visited = new Array(n).fill(false);
    visited[0] = true;

    while (stack.length > 0) {
        const path = stack[stack.length - 1];
        const v = path[path.length - 1];

        if (path.length === n) {
            if (graph[path[0]].includes(v)) {
                path.push(path[0]); // Complete the cycle
                return path;
            } else {
                stack.pop();
                visited[v] = false;
                continue;
            }
        }

        let foundNext = false;
        for (const neighbor of graph[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push([...path, neighbor]);
                foundNext = true;
                break; // Move to the next vertex
            }
        }
        if (!foundNext) {
            stack.pop();
            if(stack.length > 0){
               visited[v] = false;
            }

        }
    }
    return null;
}



// Example Usage:
const graph1 = [
    [1, 2],
    [0, 2, 3],
    [0, 1, 3, 4],
    [1, 2, 4],
    [2, 3]
];

const adjMatrix1 = [
    [0, 1, 1, 0, 0],
    [1, 0, 1, 1, 0],
    [1, 1, 0, 1, 1],
    [0, 1, 1, 0, 1],
    [0, 0, 1, 1, 0]
];

const graph2 = [
    [1, 3],
    [0, 2],
    [1, 3],
    [0, 2]
];

const adjMatrix2 = [
  [0, 1, 0, 1],
  [1, 0, 1, 0],
  [0, 1, 0, 1],
  [1, 0, 1, 0],
];

console.log("Example Graph 1 (Adjacency List):", graph1);
console.log("Example Graph 1 (Adjacency Matrix):", adjMatrix1);
console.log("Example Graph 2 (Adjacency List):", graph2);
console.log("Example Graph 2 (Adjacency Matrix):", adjMatrix2);


console.log("\n1. Backtracking (Basic):");
const result1 = hamiltonianCycleBasic(graph1);
console.log(result1 ? "Hamiltonian Cycle found: " + result1 : "No Hamiltonian Cycle found.");

console.log("\n2. Backtracking with Adjacency Matrix:");
const result2 = hamiltonianCycleMatrix(adjMatrix1);
console.log(result2 ? "Hamiltonian Cycle found: " + result2 : "No Hamiltonian Cycle found.");

console.log("\n3. Backtracking with Degree Heuristic:");
const result3 = hamiltonianCycleDegree(graph1);
console.log(result3 ? "Hamiltonian Cycle found: " + result3 : "No Hamiltonian Cycle found.");

console.log("\n4. Backtracking with Warnsdorff's Rule (Knight's Tour, n=6):");
const result4 = knightTour(6); // Example with a 6x6 board
if (result4) {
    console.log("Knight's Tour found:");
    for (const row of result4) {
        console.log(row.map(n => n.toString().padStart(3)).join("")); // Pretty print the path
    }
} else {
    console.log("No Knight's Tour found.");
}

console.log("\n5. Iterative Backtracking with Stack:");
const result5 = hamiltonianCycleIterative(graph1);
console.log(result5 ? "Hamiltonian Cycle found: " + result5 : "No Hamiltonian Cycle found.");

console.log("\nIterative Backtracking with Stack: (Graph 2)");
const result6 = hamiltonianCycleIterative(graph2);
console.log(result6 ? "Hamiltonian Cycle found: " + result6 : "No Hamiltonian Cycle found.");

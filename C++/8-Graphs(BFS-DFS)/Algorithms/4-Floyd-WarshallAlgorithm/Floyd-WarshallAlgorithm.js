/*
 * Implementation of the Floyd-Warshall Algorithm in JavaScript
 * Demonstrates 5 different approaches to solve the all-pairs shortest paths problem.
 */

const INF = Infinity;

// 1. Standard Floyd-Warshall Algorithm
function floydWarshallStandard(graph) {
  const V = graph.length;
  let dist = new Array(V).fill(null).map(() => new Array(V).fill(INF));

  // Initialize the distance matrix with the given graph
  for (let i = 0; i < V; i++) {
    for (let j = 0; j < V; j++) {
      dist[i][j] = graph[i][j];
    }
    dist[i][i] = 0; // Distance from a vertex to itself is 0
  }

  // Floyd-Warshall algorithm
  for (let k = 0; k < V; k++) {
    for (let i = 0; i < V; i++) {
      for (let j = 0; j < V; j++) {
        if (dist[i][k] !== INF && dist[k][j] !== INF) { // Check for intermediate overflow.
          dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

// 2. Floyd-Warshall with Path Reconstruction
function floydWarshallWithPath(graph) {
  const V = graph.length;
  let dist = new Array(V).fill(null).map(() => new Array(V).fill(INF));
  let next = new Array(V).fill(null).map(() => new Array(V).fill(null));

  // Initialize the distance and next matrices
  for (let i = 0; i < V; i++) {
    for (let j = 0; j < V; j++) {
      dist[i][j] = graph[i][j];
      if (graph[i][j] !== INF && i !== j) {
        next[i][j] = j;
      }
    }
    dist[i][i] = 0;
    next[i][i] = i; //important for path reconstruction
  }

  // Floyd-Warshall algorithm
  for (let k = 0; k < V; k++) {
    for (let i = 0; i < V; i++) {
      for (let j = 0; j < V; j++) {
        if (dist[i][k] !== INF && dist[k][j] !== INF && dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }

  // Function to reconstruct the shortest path
  function getPath(i, j) {
    if (next[i][j] === null) {
      return [];
    }
    let path = [i];
    while (i !== j) {
      i = next[i][j];
      path.push(i);
    }
    return path;
  }

  return { dist, next, getPath };
}

// 3. Floyd-Warshall with Early Termination
function floydWarshallEarlyStop(graph) {
  const V = graph.length;
  let dist = new Array(V).fill(null).map(() => new Array(V).fill(INF));
  let changed = true; // Track if any changes occurred in an iteration

  // Initialize the distance matrix
  for (let i = 0; i < V; i++) {
    for (let j = 0; j < V; j++) {
      dist[i][j] = graph[i][j];
    }
    dist[i][i] = 0;
  }

  // Floyd-Warshall algorithm with early termination
  for (let k = 0; k < V && changed; k++) {
    changed = false; // Reset the flag for each iteration
    for (let i = 0; i < V; i++) {
      for (let j = 0; j < V; j++) {
        if (dist[i][k] !== INF && dist[k][j] !== INF && dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          changed = true; // Set flag if a shorter path is found
        }
      }
    }
    if (!changed) {
      break; // Exit the loop if no changes occurred
    }
  }
  return dist;
}

// 4. Floyd-Warshall with Negative Cycle Detection
function floydWarshallNegativeCycle(graph) {
  const V = graph.length;
  let dist = new Array(V).fill(null).map(() => new Array(V).fill(INF));
  let hasNegativeCycle = false;

  // Initialize the distance matrix
  for (let i = 0; i < V; i++) {
    for (let j = 0; j < V; j++) {
      dist[i][j] = graph[i][j];
    }
    dist[i][i] = 0;
  }

  // Floyd-Warshall algorithm
  for (let k = 0; k < V; k++) {
    for (let i = 0; i < V; i++) {
      for (let j = 0; j < V; j++) {
        if (dist[i][k] !== INF && dist[k][j] !== INF) {
          dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  // Check for negative cycles on the main diagonal
  for (let i = 0; i < V; i++) {
    if (dist[i][i] < 0) {
      hasNegativeCycle = true;
      break;
    }
  }

  return { dist, hasNegativeCycle };
}

// 5. Floyd-Warshall using Dynamic Programming (Explicit Table) - For demonstration
function floydWarshallDP(graph) {
  const V = graph.length;
  // dp[k][i][j] stores the shortest path from i to j using intermediate nodes up to k
  let dp = new Array(V + 1).fill(null).map(() =>
    new Array(V).fill(null).map(() => new Array(V).fill(INF))
  );

  // Initialize base case: k = 0 (no intermediate nodes)
  for (let i = 0; i < V; i++) {
    for (let j = 0; j < V; j++) {
      dp[0][i][j] = graph[i][j];
    }
    dp[0][i][i] = 0;
  }

  // Fill the DP table
  for (let k = 1; k <= V; k++) {
    for (let i = 0; i < V; i++) {
      for (let j = 0; j < V; j++) {
        const viaK = (dp[k - 1][i][k - 1] !== INF && dp[k - 1][k - 1][j] !== INF)
          ? dp[k - 1][i][k - 1] + dp[k - 1][k - 1][j]
          : INF;
        dp[k][i][j] = Math.min(dp[k - 1][i][j], viaK);
      }
    }
  }

  return dp[V]; // Result is stored in dp[V]
}

// Example Usage:
const graph = [
  [0, 5, INF, 10],
  [INF, 0, 3, INF],
  [INF, INF, 0, 1],
  [INF, INF, INF, 0],
];

console.log("Original Graph:");
console.log(graph);

console.log("\n1. Standard Floyd-Warshall Algorithm:");
const resultStandard = floydWarshallStandard(graph);
console.log(resultStandard);

console.log("\n2. Floyd-Warshall with Path Reconstruction:");
const resultWithPath = floydWarshallWithPath(graph);
console.log("Distance Matrix:", resultWithPath.dist);
console.log("Next Matrix (for path reconstruction):", resultWithPath.next);
console.log("Path from 0 to 3:", resultWithPath.getPath(0, 3)); // Example path

console.log("\n3. Floyd-Warshall with Early Termination:");
const resultEarlyStop = floydWarshallEarlyStop(graph);
console.log(resultEarlyStop);

console.log("\n4. Floyd-Warshall with Negative Cycle Detection:");
const resultNegativeCycle = floydWarshallNegativeCycle(graph);
console.log("Distance Matrix:", resultNegativeCycle.dist);
console.log("Has Negative Cycle:", resultNegativeCycle.hasNegativeCycle);

console.log("\n5. Floyd-Warshall using Dynamic Programming (Explicit Table):");
const resultDP = floydWarshallDP(graph);
console.log(resultDP);

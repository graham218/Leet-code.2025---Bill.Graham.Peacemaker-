// Depth-First Search (DFS) Implementation in JavaScript - 5 Ways

// 1. Recursive Approach
console.log("1. Recursive Approach");
function dfsRecursive(graph, start, visited = new Set()) {
  if (!graph || !graph[start]) {
    return; // Handle null or empty graph or non-existent start node
  }

  visited.add(start);
  console.log(start); // Process the current node (e.g., print it)

  for (const neighbor of graph[start] || []) { // Iterate over neighbors, handle undefined
    if (!visited.has(neighbor)) {
      dfsRecursive(graph, neighbor, visited);
    }
  }
}

// 2. Iterative Approach using Stack
console.log("\n2. Iterative Approach using Stack");
function dfsIterative(graph, start) {
  if (!graph || !graph[start]) {
    return;
  }

  const stack = [start];
  const visited = new Set();

  while (stack.length > 0) {
    const node = stack.pop();

    if (!visited.has(node)) {
      visited.add(node);
      console.log(node);

      for (const neighbor of graph[node] || []) {
        if (!visited.has(neighbor)) {
          stack.push(neighbor);
        }
      }
    }
  }
}

// 3. Recursive Approach with Pre-order Traversal
console.log("\n3. Recursive Approach with Pre-order Traversal");
function dfsPreOrder(graph, start, visited = new Set()) {
    if (!graph || !graph[start]) return;

    console.log(start);  // Process (print) the node *before* visiting neighbors (pre-order)
    visited.add(start);

    for (const neighbor of graph[start] || []) {
        if (!visited.has(neighbor)) {
            dfsPreOrder(graph, neighbor, visited);
        }
    }
}

// 4. Iterative Approach using Stack and Custom Object for Node Tracking
console.log("\n4. Iterative Approach using Stack and Custom Object for Node Tracking");
function dfsIterativeObj(graph, start) {
    if (!graph || !graph[start]) return;

    const stack = [{ node: start, visited: false }]; // Store nodes with their visited status
    const visited = new Set();

    while (stack.length > 0) {
        const { node, visited: isVisited } = stack.pop();

        if (!isVisited) {
            stack.push({ node, visited: true }); // Mark the current node as visited
            if (!visited.has(node))
            {
                 console.log(node);
                 visited.add(node);
            }


            for (const neighbor of graph[node] || []) {
                if (!visited.has(neighbor)) {
                    stack.push({ node: neighbor, visited: false }); // Add neighbors to stack
                }
            }
        }
    }
}

// 5. Recursive Approach with an Adjacency Matrix
console.log("\n5. Recursive Approach with an Adjacency Matrix");
function dfsMatrix(matrix, start, visited = new Set()) {
  if (!matrix || start < 0 || start >= matrix.length) {
    return; // Handle null matrix or invalid start node
  }

  visited.add(start);
  console.log(start);

  for (let neighbor = 0; neighbor < matrix.length; neighbor++) {
    if (matrix[start][neighbor] === 1 && !visited.has(neighbor)) {
      dfsMatrix(matrix, neighbor, visited);
    }
  }
}



// Example Graph Representation (Adjacency List)
const graph = {
  'A': ['B', 'C'],
  'B': ['D', 'E'],
  'C': ['F'],
  'D': [],
  'E': ['F'],
  'F': []
};

console.log("\nDFS on the following graph (Adjacency List):");
console.log(graph);
//      A
//    /   \
//   B     C
//  / \   /
// D   E F

// Example Graph Representation (Adjacency Matrix)
const matrix = [
  [0, 1, 1, 0, 0, 0], // A
  [1, 0, 0, 1, 1, 0], // B
  [1, 0, 0, 0, 0, 1], // C
  [0, 1, 0, 0, 0, 0], // D
  [0, 1, 0, 0, 0, 1], // E
  [0, 0, 1, 0, 1, 0]  // F
];
console.log("\nDFS on the following graph (Adjacency Matrix):");
console.log(matrix);
// Call the DFS functions with the example graph and matrix
dfsRecursive(graph, 'A');
dfsIterative(graph, 'A');
dfsPreOrder(graph, 'A');
dfsIterativeObj(graph, 'A');
dfsMatrix(matrix, 0); // Start from node 0 (A)


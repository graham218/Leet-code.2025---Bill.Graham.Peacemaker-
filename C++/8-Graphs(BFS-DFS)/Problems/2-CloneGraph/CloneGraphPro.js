// Definition of a Node in the graph (same as provided)
class Node {
    constructor(val, neighbors = []) {
        this.val = val;
        this.neighbors = neighbors;
    }
}

/**
 * Clones an undirected graph.
 *
 * @param {Node} node - The node to start cloning from.  If null, returns null.
 * @returns {Node} - A deep copy of the graph, or null if the input is null.
 */
const cloneGraph = (node) => {
    if (!node) {
        return null;
    }

    const visited = new Map(); // Map to store original node and its clone.  Using Map for better performance.

    const clone = (node) => {
        if (visited.has(node)) {
            return visited.get(node); // Return the cloned node if it exists.
        }

        const clonedNode = new Node(node.val); // Create a new node with the same value.
        visited.set(node, clonedNode); // Store the original node and its clone.

        for (const neighbor of node.neighbors) {
            clonedNode.neighbors.push(clone(neighbor)); // Recursively clone neighbors.
        }
        return clonedNode;
    };

    return clone(node);
};



// ------------------------------
// 1. Iterative DFS Approach
// ------------------------------
/**
 * Clones a graph using iterative Depth-First Search.
 *
 * @param {Node} node - The node to start cloning from.
 * @returns {Node} A deep copy of the graph.
 */
const cloneGraphDFS = (node) => {
    if (!node) return null;

    const visited = new Map();
    const stack = [node]; // Use a stack for DFS

    // Clone the first node
    visited.set(node, new Node(node.val));

    while (stack.length) {
        const curr = stack.pop();
        const clonedCurr = visited.get(curr);

        for (const neighbor of curr.neighbors) {
            if (!visited.has(neighbor)) {
                visited.set(neighbor, new Node(neighbor.val)); // Clone neighbor
                stack.push(neighbor);             // Visit neighbor
            }
            clonedCurr.neighbors.push(visited.get(neighbor));
        }
    }
    return visited.get(node);
};



// ------------------------------
// 2. Iterative BFS Approach
// ------------------------------

/**
 * Clones a graph using iterative Breadth-First Search.
 *
 * @param {Node} node - The node to start cloning from.
 * @returns {Node} A deep copy of the graph.
 */
const cloneGraphBFS = (node) => {
    if (!node) return null;

    const visited = new Map();
    const queue = [node]; // Use a queue for BFS

    // Clone the first node.
    visited.set(node, new Node(node.val));

    while (queue.length) {
        const curr = queue.shift();
        const clonedCurr = visited.get(curr);

        for (const neighbor of curr.neighbors) {
            if (!visited.has(neighbor)) {
                visited.set(neighbor, new Node(neighbor.val)); // Clone neighbor
                queue.push(neighbor);             // Enqueue neighbor
            }
            clonedCurr.neighbors.push(visited.get(neighbor));
        }
    }
    return visited.get(node);
};



// ------------------------------
// 3. Optimized Recursive DFS
// ------------------------------
/**
 * Clones a graph using a slightly optimized recursive DFS.  This version is very similar to the first, but
 * the key difference is how the visited map is checked.  It's checked *before* creating the new node.
 *
 * @param {Node} node - The node to start cloning from.
 * @returns {Node} A deep copy of the graph.
 */
const cloneGraphDFSOptimized = (node) => {
    if (!node) return null;

    const visited = new Map();

    const clone = (node) => {
        if (visited.has(node)) {
            return visited.get(node);
        }

        const clonedNode = new Node(node.val); // Create node *after* checking visited
        visited.set(node, clonedNode);

        for (const neighbor of node.neighbors) {
            clonedNode.neighbors.push(clone(neighbor));
        }
        return clonedNode;
    };

    return clone(node);
};

// ------------------------------
// 4.  Iterative with Explicit Node Creation
// ------------------------------
/**
 * Clones a graph iteratively, with more explicit node creation.  This separates the
 * creation of the cloned nodes from the neighbor assignment, which can sometimes
 * be clearer to follow.
 *
 * @param {Node} node - The node to start cloning from.
 * @returns {Node} A deep copy of the graph.
 */
const cloneGraphIterativeExplicit = (node) => {
    if (!node) return null;

    const visited = new Map();
    const queue = [node];

    // First, create all the nodes (without neighbors)
    visited.set(node, new Node(node.val));
    while (queue.length) {
        const curr = queue.shift();
        for (const neighbor of curr.neighbors) {
            if (!visited.has(neighbor)) {
                visited.set(neighbor, new Node(neighbor.val));
                queue.push(neighbor);
            }
        }
    }

    // Second, assign the neighbors
    for (const [originalNode, clonedNode] of visited) {
        for (const neighbor of originalNode.neighbors) {
            clonedNode.neighbors.push(visited.get(neighbor));
        }
    }

    return visited.get(node);
};


// ------------------------------
// Example Usage and Testing
// ------------------------------

// Helper function to create a sample graph.
function createSampleGraph() {
    const node1 = new Node(1);
    const node2 = new Node(2);
    const node3 = new Node(3);
    const node4 = new Node(4);

    node1.neighbors = [node2, node4];
    node2.neighbors = [node1, node3];
    node3.neighbors = [node2, node4];
    node4.neighbors = [node1, node3];

    return node1;
}

// Helper function to print the graph (for verification)
function printGraph(node, visited = new Set()) {
    if (!node || visited.has(node)) return;

    visited.add(node);
    let neighbors = node.neighbors.map(n => n.val).join(', ');
    console.log(`Node ${node.val}: Neighbors [${neighbors}]`);
    for (const neighbor of node.neighbors) {
        printGraph(neighbor, visited);
    }
}

// Create a sample graph
const originalGraph = createSampleGraph();

// --- 1.  Vanilla Recursive DFS ---
console.log("--- 1. Original Graph (Vanilla Recursive DFS) ---");
printGraph(originalGraph);
const clonedGraph1 = cloneGraph(originalGraph);
console.log("--- 1. Cloned Graph (Vanilla Recursive DFS) ---");
printGraph(clonedGraph1);
console.log("Are graphs deep equal?", clonedGraph1 !== originalGraph); // Should be true


// --- 2. Iterative DFS ---
console.log("\n--- 2. Original Graph (Iterative DFS) ---");
printGraph(originalGraph); // Print original graph again to show it's unchanged
const clonedGraph2 = cloneGraphDFS(originalGraph);
console.log("--- 2. Cloned Graph (Iterative DFS) ---");
printGraph(clonedGraph2);
console.log("Are graphs deep equal?", clonedGraph2 !== originalGraph);

// --- 3. Iterative BFS ---
console.log("\n--- 3. Original Graph (Iterative BFS) ---");
printGraph(originalGraph);
const clonedGraph3 = cloneGraphBFS(originalGraph);
console.log("--- 3. Cloned Graph (Iterative BFS) ---");
printGraph(clonedGraph3);
console.log("Are graphs deep equal?", clonedGraph3 !== originalGraph);

// --- 4. Optimized Recursive DFS ---
console.log("\n--- 4. Original Graph (Optimized Recursive DFS) ---");
printGraph(originalGraph);
const clonedGraph4 = cloneGraphDFSOptimized(originalGraph);
console.log("--- 4. Cloned Graph (Optimized Recursive DFS) ---");
printGraph(clonedGraph4);
console.log("Are graphs deep equal?", clonedGraph4 !== originalGraph);


// --- 5. Iterative with Explicit Node Creation ---
console.log("\n--- 5. Original Graph (Iterative with Explicit Node Creation) ---");
printGraph(originalGraph);
const clonedGraph5 = cloneGraphIterativeExplicit(originalGraph);
console.log("--- 5. Cloned Graph (Iterative with Explicit Node Creation) ---");
printGraph(clonedGraph5);
console.log("Are graphs deep equal?", clonedGraph5 !== originalGraph);

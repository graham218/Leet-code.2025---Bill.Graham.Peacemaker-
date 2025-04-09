/**
 * Breadth-First Search (BFS) Implementation in JavaScript (5 Ways)
 *
 * BFS is a graph traversal algorithm that explores all the neighbor nodes
 * at the current depth prior to moving on to nodes at the next depth level.
 *
 * We will implement BFS for an unweighted, undirected graph represented
 * using an adjacency list.  We'll demonstrate 5 different ways to implement BFS.
 */

// Helper function to create an adjacency list from an edge list
function createAdjacencyList(edges, numNodes) {
    const adjacencyList = Array.from({ length: numNodes }, () => []);
    for (const [node1, node2] of edges) {
        adjacencyList[node1].push(node2);
        adjacencyList[node2].push(node1); // For undirected graph
    }
    return adjacencyList;
}

// Example graph represented as an edge list
const edges = [
    [0, 1],
    [0, 2],
    [1, 3],
    [1, 4],
    [2, 5],
    [2, 6],
    [3, 7],
    [4, 7],
    [5, 8],
    [6, 8],
    [7, 9],
    [8, 9],
];
const numNodes = 10; // Total number of nodes in the graph (0-9)
const startNode = 0; // Starting node for BFS

const adjacencyList = createAdjacencyList(edges, numNodes);

console.log("Adjacency List Representation of the Graph:");
console.log(adjacencyList);

/**
 * 1. Iterative BFS using a Queue (Classic Approach)
 */
function bfsIterative(graph, start) {
    const visited = new Array(graph.length).fill(false);
    const queue = [start];
    const result = [];
    visited[start] = true;

    while (queue.length > 0) {
        const node = queue.shift();
        result.push(node);

        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
    return result;
}

console.log("\n1. Iterative BFS using a Queue:");
console.log(bfsIterative(adjacencyList, startNode)); // Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


/**
 * 2. Iterative BFS with Path Reconstruction
 * - Tracks the path from the start node to each visited node.
 */
function bfsWithPath(graph, start, target) {
    const visited = new Array(graph.length).fill(false);
    const queue = [start];
    const path = new Array(graph.length).fill(null); // Store parent node in path
    const result = [];
    visited[start] = true;

    while (queue.length > 0) {
        const node = queue.shift();
        result.push(node);

        if (node === target) { // Added target check.
            break; // Stop BFS if target is found
        }

        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
                path[neighbor] = node; // Store how we got to this neighbor
            }
        }
    }

    // Reconstruct the path from start to target (if target was found)
    if (target !== undefined && visited[target]) {
        const reconstructedPath = [];
        let current = target;
        while (current !== null) {
            reconstructedPath.unshift(current);
            current = path[current];
        }
        return { path: result, reconstructedPath }; // Return both
    }
    return { path: result, reconstructedPath: [] };
}

const targetNode = 9;
console.log("\n2. Iterative BFS with Path Reconstruction:");
const { path, reconstructedPath } = bfsWithPath(adjacencyList, startNode, targetNode);
console.log("BFS Path:", path);
console.log("Path from", startNode, "to", targetNode, ":", reconstructedPath);


/**
 * 3. BFS using a Queue and Set (for visited tracking)
 * -  Uses a Set to keep track of visited nodes, for potentially faster lookups.
 */
function bfsWithSet(graph, start) {
    const visited = new Set();
    const queue = [start];
    const result = [];
    visited.add(start);

    while (queue.length > 0) {
        const node = queue.shift();
        result.push(node);

        for (const neighbor of graph[node]) {
            if (!visited.has(neighbor)) {
                visited.add(neighbor);
                queue.push(neighbor);
            }
        }
    }
    return result;
}

console.log("\n3. BFS using a Queue and Set:");
console.log(bfsWithSet(adjacencyList, startNode));


/**
 * 4. BFS with Early Exit (Targeted Search)
 * - Stops the search as soon as the target node is found.
 */
function bfsTargeted(graph, start, target) {
    const visited = new Array(graph.length).fill(false);
    const queue = [start];
    const result = [];
    visited[start] = true;

    while (queue.length > 0) {
        const node = queue.shift();
        result.push(node);

        if (node === target) {
            return result; // Stop and return the path so far
        }

        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
    return result; // Return the path even if target is not found.
}

console.log("\n4. BFS with Early Exit (Targeted Search):");
console.log(bfsTargeted(adjacencyList, startNode, 7)); // Search for node 7


/**
 * 5. BFS with Level Tracking
 * - Tracks the level (distance from the start node) of each visited node.
 */
function bfsWithLevel(graph, start) {
    const visited = new Array(graph.length).fill(false);
    const queue = [{ node: start, level: 0 }]; // Store node and its level
    const result = [];
    const levels = {}; // Store node levels,  e.g., { 0: 0, 1: 1, 2: 1, ... }
    visited[start] = true;
    levels[start] = 0;

    while (queue.length > 0) {
        const { node, level } = queue.shift();
        result.push(node);

        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                levels[neighbor] = level + 1; // Increment level
                queue.push({ node: neighbor, level: level + 1 });
            }
        }
    }
    return { traversal: result, levels };
}

console.log("\n5. BFS with Level Tracking:");
const { traversal, levels } = bfsWithLevel(adjacencyList, startNode);
console.log("BFS Traversal:", traversal);
console.log("Node Levels:", levels);

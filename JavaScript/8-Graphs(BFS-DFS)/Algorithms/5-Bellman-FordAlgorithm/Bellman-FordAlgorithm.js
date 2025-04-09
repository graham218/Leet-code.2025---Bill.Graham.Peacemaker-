// Define a graph as an array of edges.  Each edge is an array [u, v, weight].
//  u: start node, v: end node, weight: edge weight.
const graph = [
    [0, 1, -1],
    [0, 2, 4],
    [1, 2, 3],
    [1, 3, 2],
    [1, 4, 2],
    [3, 1, 1],
    [3, 2, 5],
    [4, 3, -3]
];

const numNodes = 5; // Number of nodes in the graph
const startNode = 0; // Starting node for Bellman-Ford

// 1. Basic Bellman-Ford Algorithm
function bellmanFordBasic(graph, numNodes, startNode) {
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;

    // Relax edges repeatedly
    for (let i = 0; i < numNodes - 1; i++) {
        for (const [u, v, weight] of graph) {
            if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    // Check for negative cycles
    for (const [u, v, weight] of graph) {
        if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
            return "Negative cycle detected";
        }
    }

    return distances;
}

// 2. Bellman-Ford with Early Termination
function bellmanFordEarlyTermination(graph, numNodes, startNode) {
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;
    let updated;

    for (let i = 0; i < numNodes - 1; i++) {
        updated = false;
        for (const [u, v, weight] of graph) {
            if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                updated = true;
            }
        }
        if (!updated) break; // If no updates, we're done
    }

    for (const [u, v, weight] of graph) {
        if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
            return "Negative cycle detected";
        }
    }
    return distances;
}

// 3. Bellman-Ford with Queue (Optimization - Not always faster, but can be in some cases)
function bellmanFordQueue(graph, numNodes, startNode) {
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;
    const queue = [startNode];
    const inQueue = new Array(numNodes).fill(false); // Track if node is in queue
    inQueue[startNode] = true;
    const visitCount = new Array(numNodes).fill(0); // Check for negative cycles

    while (queue.length > 0) {
        const u = queue.shift();
        inQueue[u] = false;

        visitCount[u]++;
        if (visitCount[u] > numNodes) {
            return "Negative cycle detected"; // More than n visits means a cycle
        }

        for (const [source, dest, weight] of graph) { // Changed u,v to source, dest to avoid shadowing
            if (source === u) { // Check only edges starting from u
                if (distances[u] !== Infinity && distances[u] + weight < distances[dest]) {
                    distances[dest] = distances[u] + weight;
                    if (!inQueue[dest]) {
                        queue.push(dest);
                        inQueue[dest] = true;
                    }
                }
            }
        }
    }
    return distances;
}

// 4. Bellman-Ford using an adjacency list representation of the graph.
function bellmanFordAdjacencyList(adjList, numNodes, startNode) {
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;

    for (let i = 0; i < numNodes - 1; i++) {
        let updated = false;
        for (let u = 0; u < numNodes; u++) {
            if (distances[u] !== Infinity && adjList[u]) { // Corrected: Check if adjList[u] exists
                for (const [v, weight] of adjList[u]) {
                    if (distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        updated = true;
                    }
                }
            }
        }
        if (!updated) break;
    }

    for (let u = 0; u < numNodes; u++) {
        if (distances[u] !== Infinity && adjList[u]) { // Corrected: Check if adjList[u] exists
            for (const [v, weight] of adjList[u]) {
                if (distances[u] + weight < distances[v]) {
                    return "Negative cycle detected";
                }
            }
        }
    }
    return distances;
}

// Convert the edge list graph representation to an adjacency list representation.
function createAdjacencyList(graph, numNodes) {
    const adjList = new Array(numNodes).fill(null).map(() => []); // Initialize as array of arrays
    for (const [u, v, weight] of graph) {
        if (!adjList[u]) {
            adjList[u] = [];
        }
        adjList[u].push([v, weight]);
    }
    return adjList;
}

// 5.  Bellman Ford with path reconstruction
function bellmanFordWithPath(graph, numNodes, startNode) {
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;
    const predecessors = new Array(numNodes).fill(null); // To store the path

    for (let i = 0; i < numNodes - 1; i++) {
        for (const [u, v, weight] of graph) {
            if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessors[v] = u; // Store the predecessor
            }
        }
    }

    for (const [u, v, weight] of graph) {
        if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
            return { distances: "Negative cycle detected", path: null };
        }
    }

    // Function to reconstruct the path from startNode to endNode
    function getPath(endNode) {
        if (distances[endNode] === Infinity) return []; // No path
        const path = [];
        let current = endNode;
        while (current !== null) {
            path.unshift(current); // Add to the beginning
            current = predecessors[current];
        }
        return path;
    }

    return { distances, getPath }; // Return both distances and the path reconstruction function
}



// Example usage and output using console.log
console.log("Graph:", graph);
console.log("Number of Nodes:", numNodes);
console.log("Start Node:", startNode);

console.log("\n1. Basic Bellman-Ford:");
console.log(bellmanFordBasic(graph, numNodes, startNode));

console.log("\n2. Bellman-Ford with Early Termination:");
console.log(bellmanFordEarlyTermination(graph, numNodes, startNode));

console.log("\n3. Bellman-Ford with Queue:");
console.log(bellmanFordQueue(graph, numNodes, startNode));

const adjList = createAdjacencyList(graph, numNodes);
console.log("\n4. Bellman-Ford with Adjacency List:");
console.log("Adjacency List:", adjList);
console.log(bellmanFordAdjacencyList(adjList, numNodes, startNode));

console.log("\n5. Bellman-Ford with Path Reconstruction:");
const resultWithPath = bellmanFordWithPath(graph, numNodes, startNode);
console.log("Distances:", resultWithPath.distances);
if (resultWithPath.distances !== "Negative cycle detected") {
    const endNode = 4; // Example end node
    const path = resultWithPath.getPath(endNode);
    console.log(`Path from ${startNode} to ${endNode}:`, path);
}

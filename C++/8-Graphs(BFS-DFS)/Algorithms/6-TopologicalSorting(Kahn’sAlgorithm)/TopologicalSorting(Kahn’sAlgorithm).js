/**
 * Topological Sorting (Kahn's Algorithm) - 5 Approaches in JavaScript
 *
 * Topological sorting for a Directed Acyclic Graph (DAG) is a linear ordering of vertices
 * such that for every directed edge u -> v, vertex u comes before vertex v in the ordering.
 * Kahn's algorithm is a popular algorithm for performing topological sorting.
 */

// Helper function to create an adjacency list from edge list
function createAdjacencyList(edges, numNodes) {
    const adjList = Array.from({ length: numNodes }, () => []);
    for (const [u, v] of edges) {
        adjList[u].push(v);
    }
    return adjList;
}

// Helper function to calculate in-degrees
function calculateInDegrees(adjList, numNodes) {
    const inDegrees = Array(numNodes).fill(0);
    for (let u = 0; u < numNodes; u++) {
        for (const v of adjList[u]) {
            inDegrees[v]++;
        }
    }
    return inDegrees;
}

// Example graph represented as an array of edges.  The nodes are assumed to be 0-indexed.
const edges = [
    [0, 1],
    [0, 2],
    [1, 3],
    [2, 3],
    [3, 4],
    [4, 5],
];
const numNodes = 6; // Number of nodes in the graph

// Approach 1: Basic Kahn's Algorithm using a queue
function topologicalSortKahnBasic(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const queue = [];
    const result = [];

    // Enqueue nodes with in-degree 0
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            queue.push(i);
        }
    }

    while (queue.length > 0) {
        const u = queue.shift();
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                queue.push(v);
            }
        }
    }

    // Check for cycles (if the result doesn't contain all nodes, there's a cycle)
    if (result.length !== numNodes) {
        return "Graph contains a cycle. Topological sort is not possible.";
    }
    return result;
}

// Approach 2: Kahn's Algorithm with Priority Queue (for lexicographical order -  Smallest node first)
function topologicalSortKahnPriorityQueue(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const pq = []; // Use a min-heap (priority queue)
    const result = [];

    // Enqueue nodes with in-degree 0
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            pq.push(i);
        }
    }

    // Min-heap implementation (simple, for demonstration -  for larger graphs, use a proper heap library)
    pq.sort((a, b) => a - b); // Sort to maintain min-heap property

    while (pq.length > 0) {
        const u = pq.shift(); // Get the smallest element
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                pq.push(v);
                pq.sort((a, b) => a - b); // Maintain min-heap property
            }
        }
    }

    if (result.length !== numNodes) {
        return "Graph contains a cycle. Topological sort is not possible.";
    }
    return result;
}

// Approach 3: Kahn's Algorithm with Set (for efficient removal)
function topologicalSortKahnSet(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const zeroInDegreeSet = new Set();
    const result = [];

    // Add nodes with in-degree 0 to the set
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            zeroInDegreeSet.add(i);
        }
    }

    while (zeroInDegreeSet.size > 0) {
        // Get an arbitrary element and remove it.  This is more efficient than
        // searching for the minimum in a long array.
        const u = zeroInDegreeSet.values().next().value;
        zeroInDegreeSet.delete(u);
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                zeroInDegreeSet.add(v);
            }
        }
    }

    if (result.length !== numNodes) {
        return "Graph contains a cycle. Topological sort is not possible.";
    }
    return result;
}

// Approach 4: Kahn's Algorithm with Array as Queue (Optimized for speed)
function topologicalSortKahnArrayQueue(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const queue = [];
    let queueIndex = 0; // Keep track of the "head" of the queue
    const result = [];

    // Enqueue nodes with in-degree 0
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            queue.push(i);
        }
    }

    while (queueIndex < queue.length) { // Use queueIndex to track the "head"
        const u = queue[queueIndex++]; // Dequeue (efficiently)
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                queue.push(v); // Enqueue
            }
        }
    }

    if (result.length !== numNodes) {
        return "Graph contains a cycle. Topological sort is not possible.";
    }
    return result;
}

// Approach 5: Kahn's Algorithm with Object as Queue (for sparse graphs) - less common, but shows variation
function topologicalSortKahnObjectQueue(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const queue = {}; // Use an object as a queue (keys are indices, values are true)
    let head = 0;
    let tail = 0;
    const result = [];

    // Enqueue nodes with in-degree 0
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            queue[tail++] = i; // Use tail to add to the "end"
        }
    }

    while (head < tail) { // While the "head" is behind the "tail"
        const u = queue[head++]; // Get from the "head" and move head forward
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                queue[tail++] = v; // Add to the "end"
            }
        }
    }

    if (result.length !== numNodes) {
        return "Graph contains a cycle. Topological sort is not possible.";
    }
    return result;
}

// Display the results from each approach
console.log("Input Edges:", edges);
console.log("Number of Nodes:", numNodes);
console.log("\nTopological Sort Results:");
console.log("--------------------------");
console.log("Approach 1 (Basic Queue):", topologicalSortKahnBasic(edges, numNodes));
console.log("Approach 2 (Priority Queue):", topologicalSortKahnPriorityQueue(edges, numNodes));
console.log("Approach 3 (Set):", topologicalSortKahnSet(edges, numNodes));
console.log("Approach 4 (Array Queue):", topologicalSortKahnArrayQueue(edges, numNodes));
console.log("Approach 5 (Object Queue):", topologicalSortKahnObjectQueue(edges, numNodes));

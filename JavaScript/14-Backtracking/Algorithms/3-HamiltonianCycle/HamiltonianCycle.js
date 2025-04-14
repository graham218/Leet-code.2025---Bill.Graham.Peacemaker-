/*
Hamiltonian Cycle: A Hamiltonian cycle is a path in an undirected or directed graph that visits each vertex exactly once and also returns to the starting vertex.

Problem: Given a graph, find a Hamiltonian cycle in it.

Approaches Implemented:
1.  Backtracking (Basic Recursive)
2.  Backtracking with Adjacency Matrix
3.  Backtracking with Early Pruning
4.  Fleury's Algorithm (for Eulerian graphs - will be adapted) - Not directly for Hamiltonian, but related concept
5.  Using a Library (for graph manipulation) - Demonstrative
*/

// --- 1. Backtracking (Basic Recursive) ---
// Uses an adjacency list representation of the graph.
function findHamiltonianCycleBasic(graph) {
    const numVertices = graph.length;
    const path = [0]; // Start from vertex 0

    function isSafe(vertex, path, pos) {
        if (graph[path[pos - 1]].indexOf(vertex) === -1) {
            return false;
        }
        for (let i = 0; i < pos; i++) {
            if (path[i] === vertex) {
                return false;
            }
        }
        return true;
    }

    function hamiltonianCycleUtil(path, pos) {
        if (pos === numVertices) {
            if (graph[path[pos - 1]].indexOf(path[0]) !== -1) {
                return true; // Cycle found
            } else {
                return false; // Path, not cycle
            }
        }

        for (let vertex = 1; vertex < numVertices; vertex++) {
            if (isSafe(vertex, path, pos)) {
                path[pos] = vertex;
                if (hamiltonianCycleUtil(path, pos + 1)) {
                    return true;
                }
                path[pos] = -1; // Backtrack
            }
        }
        return false;
    }

    if (hamiltonianCycleUtil(path, 1)) {
        return path;
    } else {
        return null;
    }
}

// --- 2. Backtracking with Adjacency Matrix ---
// Uses an adjacency matrix representation.  Can be faster for dense graphs.
function findHamiltonianCycleMatrix(adjMatrix) {
    const numVertices = adjMatrix.length;
    const path = [0];
    const visited = Array(numVertices).fill(false);
    visited[0] = true;

    function isSafeMatrix(vertex, path, pos) {
        if (adjMatrix[path[pos - 1]][vertex] === 0) return false;
        if (visited[vertex]) return false;
        return true;
    }

    function hamiltonianCycleUtilMatrix(path, pos) {
        if (pos === numVertices) {
            if (adjMatrix[path[pos - 1]][0] === 1) return true;
            return false;
        }
        for (let vertex = 1; vertex < numVertices; vertex++) {
            if (isSafeMatrix(vertex, path, pos)) {
                path[pos] = vertex;
                visited[vertex] = true;
                if (hamiltonianCycleUtilMatrix(path, pos + 1)) return true;
                path[pos] = -1;
                visited[vertex] = false;
            }
        }
        return false;
    }

    if (hamiltonianCycleUtilMatrix(path, 1)) {
        return path;
    }
    return null;
}

// --- 3. Backtracking with Early Pruning ---
// Adds a degree check to potentially reduce search space.
function findHamiltonianCyclePruning(graph) {
    const numVertices = graph.length;
    const path = [0];
    const visited = Array(numVertices).fill(false);
    visited[0] = true;

    // Check if the degree of each vertex is >= 2 (necessary condition)
    for (let i = 0; i < numVertices; i++) {
        if (graph[i].length < 2) {
            console.log("Pruning: Vertex degree < 2");
            return null; // Early exit: No Hamiltonian Cycle possible
        }
    }

    function isSafePruning(vertex, path, pos) {
        if (graph[path[pos - 1]].indexOf(vertex) === -1) return false;
        if (visited[vertex]) return false;
        return true;
    }

    function hamiltonianCycleUtilPruning(path, pos) {
        if (pos === numVertices) {
            if (graph[path[pos - 1]].indexOf(path[0]) !== -1) return true;
            return false;
        }
        for (let vertex = 1; vertex < numVertices; vertex++) {
            if (isSafePruning(vertex, path, pos)) {
                path[pos] = vertex;
                visited[vertex] = true;
                if (hamiltonianCycleUtilPruning(path, pos + 1)) return true;
                path[pos] = -1;
                visited[vertex] = false;
            }
        }
        return false;
    }

    if (hamiltonianCycleUtilPruning(path, 1)) {
        return path;
    }
    return null;
}

// --- 4. Fleury's Algorithm (for Eulerian Paths/Cycles - Adapted) ---
//  Fleury's is for *Eulerian* cycles (edges visited once), not Hamiltonian (vertices visited once).
//  This is included to show a different graph traversal algorithm, but it DOES NOT solve the Hamiltonian Cycle problem.  It's adapted to *try* to find a Hamiltonian-like path, but it's not guaranteed.
function fleuryAttempt(graph) {
    const numVertices = graph.length;
    const edges = [];
    for (let u = 0; u < numVertices; u++) {
        for (let v of graph[u]) {
            if (u < v) { // Avoid duplicate edges
                edges.push({ u, v });
            }
        }
    }

    const path = [0];
    let currentVertex = 0;

    while (edges.length > 0) {
        let foundNext = false;
        for (let i = 0; i < edges.length; i++) {
            const { u, v } = edges[i];
            if (u === currentVertex || v === currentVertex) {
                const nextVertex = (u === currentVertex) ? v : u;
                path.push(nextVertex);
                currentVertex = nextVertex;
                edges.splice(i, 1); // Remove the edge
                foundNext = true;
                break; // Important: Move to the next edge
            }
        }
        if (!foundNext) {
            console.log("Fleury's: Stuck, no next edge found.");
            return null; // Stuck
        }
    }
    //Check if it is a cycle.
    if(path[0] === path[path.length-1] && path.length === numVertices + 1){
        return path;
    }
    else{
        return null;
    }

}

// --- 5. Using a Library (Demonstrative - requires an external library, e.g., graphology) ---
// This is conceptual.  In a real application, you'd install a graph library.
//  We'll simulate the library's behavior for demonstration.
function findHamiltonianCycleLibrary(graph) {
    //  Simulated library functions (replace with actual library calls)
    const simulatedLibrary = {
        createGraph: (graphData) => {
            // In a real library, this would create a graph object.
            return graphData; //  Just return the input for this example
        },
        findHamiltonianCycle: (graphInstance) => {
            //  Simulate finding a Hamiltonian cycle.
            //  This is a placeholder; a real library would have a proper algorithm.

            // Very simplified simulation (this will only work for *very* specific graphs):
            if (graphInstance.length === 5) {
                return [0, 1, 2, 4, 3, 0]; // Example for a 5-vertex cycle
            }
            return null;
        },
    };

    const graphInstance = simulatedLibrary.createGraph(graph);
    const cycle = simulatedLibrary.findHamiltonianCycle(graphInstance);
    return cycle;
}

// --- Example Usage ---

// Example Graph (Adjacency List)
const graphList = [
    [1, 3],
    [0, 2],
    [1, 4],
    [0, 4],
    [2, 3],
];

// Example Graph (Adjacency Matrix)
const graphMatrix = [
    [0, 1, 0, 1, 0],
    [1, 0, 1, 0, 0],
    [0, 1, 0, 0, 1],
    [1, 0, 0, 0, 1],
    [0, 0, 1, 1, 0],
];

console.log("--- Hamiltonian Cycle ---");
console.log("Graph (List):", graphList);
console.log("Graph (Matrix):", graphMatrix);

console.log("\n1. Backtracking (Basic):", findHamiltonianCycleBasic(graphList));
console.log("2. Backtracking (Matrix):", findHamiltonianCycleMatrix(graphMatrix));
console.log("3. Backtracking (Pruning):", findHamiltonianCyclePruning(graphList));
console.log("4. Fleury's Attempt (Eulerian - NOT Hamiltonian):", fleuryAttempt(graphList));  // NOT Hamiltonian
console.log("5. Using a Library (Simulated):", findHamiltonianCycleLibrary(graphList));

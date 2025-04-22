// Kruskal's Algorithm for Minimum Spanning Tree (MST)

/*
Kruskal's algorithm is a greedy algorithm used to find a minimum spanning tree (MST) for a weighted, undirected graph. It works by repeatedly adding the cheapest edge to the MST that does not create a cycle.

Here's a breakdown of the algorithm:

1.  Sort all the edges of the graph in non-decreasing order of their weight.
2.  Create an empty MST.
3.  Pick the smallest edge. Check if including this edge in the MST creates a cycle.
    * If a cycle is not formed, include this edge in the MST.
    * Else, discard this edge.
4.  Repeat step 3 until there are (V-1) edges in the MST, where V is the number of vertices in the graph.

Data Structures:

* Graph Representation:  Adjacency List or Edge List.  For Kruskal's, an Edge List is generally preferred due to the sorting step.  An edge list is an array of tuples (u, v, weight) representing the edges.
* Disjoint Set Union (DSU):  Essential for cycle detection.  We'll implement this using:
    * Parent Array (for basic DSU)
    * Rank and Path Compression (for optimized DSU)

Time Complexity: O(E log E) or O(E log V), where E is the number of edges and V is the number of vertices.
    * Sorting edges takes O(E log E).
    * DSU operations (find and union) take nearly constant time with rank and path compression.
Space Complexity: O(V + E)
    * O(V) for the parent array in DSU.
    * O(E) for storing the edges.

Variations in Implementation (Demonstrated Below):

We'll show 5 different ways to implement Kruskal's, primarily focusing on variations in:
1.  Graph Representation: Edge List
2.  Disjoint Set Union (DSU) Implementation:
    * Basic Parent Array
    * Rank Optimization
    * Path Compression Optimization
    * Rank and Path Compression Optimization
    * ES6 Class based implementation of DSU
*/

// Example Graph (for all implementations)
const graph = [
    [0, 1, 10], // Edge between node 0 and 1 with weight 10
    [0, 2, 6],
    [0, 3, 5],
    [1, 3, 15],
    [2, 3, 4],
];
const numVertices = 4; // Number of vertices in the graph

// ------------------------------------------------------------------------------------------------
// 1. Kruskal's Algorithm with Basic Disjoint Set Union (Parent Array)
// ------------------------------------------------------------------------------------------------
function kruskalBasicDSU(edges, numVertices) {
    let mstWeight = 0;
    const parent = new Array(numVertices);

    // Initialize parent array: Each vertex is its own parent initially
    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    // Function to find the parent of a vertex (without path compression)
    function find(i) {
        if (parent[i] === i) {
            return i;
        }
        return find(parent[i]); // Recursive call
    }

    // Function to unite two sets (without rank)
    function union(i, j) {
        const a = find(i);
        const b = find(j);
        if (a !== b) { // only union if they are not already in the same set.
            parent[a] = b;
        }
    }

    // 1. Sort edges by weight in ascending order
    edges.sort((a, b) => a[2] - b[2]);

    const mstEdges = []; // Array to store edges of the MST

    // 2. Iterate through sorted edges
    for (const edge of edges) {
        const u = edge[0];
        const v = edge[1];
        const weight = edge[2];

        // 3. Find the parent of the vertices
        const parentU = find(u);
        const parentV = find(v);

        // 4. If including the edge doesn't form a cycle, include it in the MST
        if (parentU !== parentV) {
            mstWeight += weight;
            union(parentU, parentV); // Merge the sets
            mstEdges.push(edge);
        }
    }
    return { weight: mstWeight, edges: mstEdges };
}

// ------------------------------------------------------------------------------------------------
// 2. Kruskal's Algorithm with Rank Optimization in DSU
// ------------------------------------------------------------------------------------------------
function kruskalRankDSU(edges, numVertices) {
    let mstWeight = 0;
    const parent = new Array(numVertices);
    const rank = new Array(numVertices).fill(0); // Initialize rank array

    // Initialize parent and rank
    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    function find(i) {
        if (parent[i] === i) {
            return i;
        }
        return find(parent[i]);
    }

    function union(i, j) {
        const a = find(i);
        const b = find(j);
        if (a !== b) {
            if (rank[a] < rank[b]) {  // Attach smaller rank tree under root of high rank tree
                parent[a] = b;
            } else if (rank[a] > rank[b]) {
                parent[b] = a;
            } else { // If ranks are same, then make one as root and increment its rank by one
                parent[b] = a;
                rank[a]++;
            }
        }
    }

    edges.sort((a, b) => a[2] - b[2]);
    const mstEdges = [];

    for (const edge of edges) {
        const u = edge[0];
        const v = edge[1];
        const weight = edge[2];

        const parentU = find(u);
        const parentV = find(v);

        if (parentU !== parentV) {
            mstWeight += weight;
            union(parentU, parentV);
            mstEdges.push(edge);
        }
    }
    return { weight: mstWeight, edges: mstEdges };
}

// ------------------------------------------------------------------------------------------------
// 3. Kruskal's Algorithm with Path Compression Optimization in DSU
// ------------------------------------------------------------------------------------------------
function kruskalPathCompressionDSU(edges, numVertices) {
    let mstWeight = 0;
    const parent = new Array(numVertices);

    // Initialize parent
    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    function find(i) {
        if (parent[i] === i) {
            return i;
        }
        // Path compression:  Make the parent of i the root of the tree
        parent[i] = find(parent[i]);
        return parent[i];
    }

    function union(i, j) {
        const a = find(i);
        const b = find(j);
        if (a !== b) {
            parent[a] = b;
        }
    }

    edges.sort((a, b) => a[2] - b[2]);
    const mstEdges = [];

    for (const edge of edges) {
        const u = edge[0];
        const v = edge[1];
        const weight = edge[2];

        const parentU = find(u);
        const parentV = find(v);

        if (parentU !== parentV) {
            mstWeight += weight;
            union(parentU, parentV);
            mstEdges.push(edge);
        }
    }
    return { weight: mstWeight, edges: mstEdges };
}

// ------------------------------------------------------------------------------------------------
// 4. Kruskal's Algorithm with Rank and Path Compression Optimization in DSU
// ------------------------------------------------------------------------------------------------
function kruskalOptimizedDSU(edges, numVertices) {
    let mstWeight = 0;
    const parent = new Array(numVertices);
    const rank = new Array(numVertices).fill(0);

    // Initialize parent and rank
    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    function find(i) {
        if (parent[i] === i) {
            return i;
        }
        // Path compression:
        parent[i] = find(parent[i]);
        return parent[i];
    }

    function union(i, j) {
        const a = find(i);
        const b = find(j);
        if (a !== b) {
            if (rank[a] < rank[b]) {
                parent[a] = b;
            } else if (rank[a] > rank[b]) {
                parent[b] = a;
            } else {
                parent[b] = a;
                rank[a]++;
            }
        }
    }

    edges.sort((a, b) => a[2] - b[2]);
    const mstEdges = [];

    for (const edge of edges) {
        const u = edge[0];
        const v = edge[1];
        const weight = edge[2];

        const parentU = find(u);
        const parentV = find(v);

        if (parentU !== parentV) {
            mstWeight += weight;
            union(parentU, parentV);
            mstEdges.push(edge);
        }
    }
    return { weight: mstWeight, edges: mstEdges };
}

// ------------------------------------------------------------------------------------------------
// 5. Kruskal's Algorithm with ES6 Class for DSU
// ------------------------------------------------------------------------------------------------

class DisjointSet {
    constructor(numVertices) {
        this.parent = new Array(numVertices);
        this.rank = new Array(numVertices).fill(0);
        for (let i = 0; i < numVertices; i++) {
            this.parent[i] = i;
        }
    }

    find(i) {
        if (this.parent[i] === i) {
            return i;
        }
        this.parent[i] = this.find(this.parent[i]); // Path compression
        return this.parent[i];
    }

    union(i, j) {
        const a = this.find(i);
        const b = this.find(j);
        if (a !== b) {
            if (this.rank[a] < this.rank[b]) {
                this.parent[a] = b;
            } else if (this.rank[a] > this.rank[b]) {
                this.parent[b] = a;
            } else {
                this.parent[b] = a;
                this.rank[a]++;
            }
        }
    }
}

function kruskalClassDSU(edges, numVertices) {
    let mstWeight = 0;
    const dsu = new DisjointSet(numVertices);
    edges.sort((a, b) => a[2] - b[2]);
    const mstEdges = [];

    for (const edge of edges) {
        const u = edge[0];
        const v = edge[1];
        const weight = edge[2];

        const parentU = dsu.find(u);
        const parentV = dsu.find(v);

        if (parentU !== parentV) {
            mstWeight += weight;
            dsu.union(parentU, parentV);
            mstEdges.push(edge);
        }
    }
    return { weight: mstWeight, edges: mstEdges };
}

// ------------------------------------------------------------------------------------------------
// Output the results using console.log
// ------------------------------------------------------------------------------------------------

console.log("Graph:", graph);
console.log("Number of Vertices:", numVertices);

console.log("\n1. Kruskal's Algorithm with Basic DSU:");
const mstBasic = kruskalBasicDSU(graph, numVertices);
console.log("MST Weight:", mstBasic.weight);
console.log("MST Edges:", mstBasic.edges);

console.log("\n2. Kruskal's Algorithm with Rank Optimization:");
const mstRank = kruskalRankDSU(graph, numVertices);
console.log("MST Weight:", mstRank.weight);
console.log("MST Edges:", mstRank.edges);

console.log("\n3. Kruskal's Algorithm with Path Compression:");
const mstPathCompression = kruskalPathCompressionDSU(graph, numVertices);
console.log("MST Weight:", mstPathCompression.weight);
console.log("MST Edges:", mstPathCompression.edges);

console.log("\n4. Kruskal's Algorithm with Rank and Path Compression:");
const mstOptimized = kruskalOptimizedDSU(graph, numVertices);
console.log("MST Weight:", mstOptimized.weight);
console.log("MST Edges:", mstOptimized.edges);

console.log("\n5. Kruskal's Algorithm with Class-based DSU:");
const mstClass = kruskalClassDSU(graph, numVertices);
console.log("MST Weight:", mstClass.weight);
console.log("MST Edges:", mstClass.edges);

// Prim's Algorithm for Minimum Spanning Tree (MST)

// Helper function to find the minimum key vertex not yet in MST
function minKey(key, mstSet) {
    let min = Infinity, minIndex = -1;

    for (let v = 0; v < key.length; v++) {
        if (mstSet[v] === false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Approach 1: Using an Adjacency Matrix
function primMST_Matrix(graph) {
    const V = graph.length; // Number of vertices
    const parent = []; // Array to store constructed MST
    const key = [];   // Key values used to pick minimum weight edge in cut
    const mstSet = [];  // To represent set of vertices included in MST

    // Initialize all keys as INFINITE and mstSet values as false
    for (let i = 0; i < V; i++) {
        key[i] = Infinity;
        mstSet[i] = false;
    }

    // Include first vertex in MST and make key 0 so that this vertex is picked first
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (let count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        const u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (let v = 0; v < V; v++) {
            // graph[u][v] is non zero only for adjacent vertices of u
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] === false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    console.log("Approach 1: Using Adjacency Matrix");
    printMST(parent, graph);
}

// Approach 2: Using an Adjacency List
function primMST_List(adjList) {
    const V = adjList.length;
    const parent = [];
    const key = [];
    const mstSet = [];

    for (let i = 0; i < V; i++) {
        key[i] = Infinity;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (let count = 0; count < V - 1; count++) {
        const u = minKey(key, mstSet);
        mstSet[u] = true;

        for (const [v, weight] of adjList[u]) {
            if (mstSet[v] === false && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    console.log("Approach 2: Using Adjacency List");
    printMST(parent, adjListToMatrix(adjList)); // Convert list to matrix for printing
}

// Helper function to convert adjacency list to adjacency matrix (for consistent output)
function adjListToMatrix(adjList) {
    const V = adjList.length;
    const matrix = Array(V).fill(null).map(() => Array(V).fill(0));
    for (let u = 0; u < V; u++) {
        for (const [v, weight] of adjList[u]) {
            matrix[u][v] = weight;
            matrix[v][u] = weight; // Assuming undirected graph
        }
    }
    return matrix;
}

// Function to print the constructed MST (used by both Matrix and List approaches)
function printMST(parent, graph) {
    console.log("Edge \tWeight");
    for (let i = 1; i < graph.length; i++) {
        console.log(`${parent[i]} - ${i} \t${graph[i][parent[i]]}`);
    }
}

// Approach 3: Using Priority Queue (Min Heap)
class MinPriorityQueue {
    constructor() {
        this.heap = [];
    }

    enqueue(item, priority) {
        this.heap.push({ item, priority });
        this.bubbleUp(this.heap.length - 1);
    }

    dequeue() {
        if (this.isEmpty()) return null;
        this.swap(0, this.heap.length - 1);
        const item = this.heap.pop();
        this.bubbleDown(0);
        return item.item;
    }

    isEmpty() {
        return this.heap.length === 0;
    }

    bubbleUp(index) {
        while (index > 0) {
            const parent = Math.floor((index - 1) / 2);
            if (this.heap[index].priority >= this.heap[parent].priority) break;
            this.swap(index, parent);
            index = parent;
        }
    }

    bubbleDown(index) {
        while (true) {
            const left = 2 * index + 1;
            const right = 2 * index + 2;
            let smallest = index;

            if (left < this.heap.length && this.heap[left].priority < this.heap[smallest].priority) {
                smallest = left;
            }
            if (right < this.heap.length && this.heap[right].priority < this.heap[smallest].priority) {
                smallest = right;
            }
            if (smallest === index) break;
            this.swap(index, smallest);
            index = smallest;
        }
    }

    swap(i, j) {
        [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
    }

    updatePriority(item, newPriority) {
        for (let i = 0; i < this.heap.length; i++) {
            if (this.heap[i].item === item) {
                this.heap[i].priority = newPriority;
                this.bubbleUp(i); // Maintain heap property
                return;
            }
        }
    }
}

function primMST_PQ(graph) {
    const V = graph.length;
    const parent = [];
    const key = [];
    const mstSet = [];
    const pq = new MinPriorityQueue();

    for (let i = 0; i < V; i++) {
        key[i] = Infinity;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;
    pq.enqueue(0, 0); // Enqueue the starting vertex with priority 0

    while (!pq.isEmpty()) {
        const u = pq.dequeue();
        mstSet[u] = true;

        for (let v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] === false && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.updatePriority(v, key[v]); // Update priority in the queue
                pq.enqueue(v, key[v]);
            }
        }
    }
    console.log("Approach 3: Using Priority Queue");
    printMST(parent, graph);
}

// Approach 4: Using a Different Graph Representation (Object)
function primMST_Object(graphObj) {
    const V = Object.keys(graphObj).length;
    const vertices = Object.keys(graphObj);
    const parent = {};
    const key = {};
    const mstSet = {};

    vertices.forEach(v => {
        key[v] = Infinity;
        mstSet[v] = false;
    });

    const startVertex = vertices[0];
    key[startVertex] = 0;
    parent[startVertex] = null;
    mstSet[startVertex] = false;


    for (let count = 0; count < V - 1; count++) {
        let u;
        let minKeyVal = Infinity;
        for (const v of vertices) {
            if (!mstSet[v] && key[v] < minKeyVal) {
                minKeyVal = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        for (const neighbor in graphObj[u]) {
            const weight = graphObj[u][neighbor];
            if (!mstSet[neighbor] && weight < key[neighbor]) {
                parent[neighbor] = u;
                key[neighbor] = weight;
            }
        }
    }

    console.log("Approach 4: Using Adjacency Object");
    printMST_Object(parent, graphObj);
}

function printMST_Object(parent, graphObj) {
    console.log("Edge \tWeight");
    for (const vertex in parent) {
        if (parent[vertex] !== null) {
            console.log(`${parent[vertex]} - ${vertex} \t${graphObj[vertex][parent[vertex]]}`);
        }
    }
}

// Approach 5: Optimized using Min Heap (Simplified)
function primMST_Optimized(graph) {
    const V = graph.length;
    const parent = Array(V).fill(null);
    const key = Array(V).fill(Infinity);
    const inMST = Array(V).fill(false);
    const minHeap = [[0, 0]]; // [vertex, key]

    key[0] = 0;

    while (minHeap.length > 0) {
        minHeap.sort((a, b) => a[1] - b[1]); // Sort by key (weight)
        const [u, weightU] = minHeap.shift();

        if (inMST[u]) continue; // Skip if already in MST
        inMST[u] = true;

        for (let v = 0; v < V; v++) {
            if (graph[u][v] !== 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                minHeap.push([v, key[v]]); // Add/Update the vertex and key
            }
        }
    }

    console.log("Approach 5: Optimized using Min Heap");
    printMST(parent, graph);
}

// Example Graph (Adjacency Matrix Representation)
const graphMatrix = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
];

// Example Graph (Adjacency List Representation)
const graphList = [
    [[1, 2], [3, 6]],
    [[0, 2], [2, 3], [3, 8], [4, 5]],
    [[1, 3], [4, 7]],
    [[0, 6], [1, 8], [4, 9]],
    [[1, 5], [2, 7], [3, 9]]
];

// Example Graph (Adjacency Object Representation)
const graphObject = {
    'A': { 'B': 2, 'D': 6 },
    'B': { 'A': 2, 'C': 3, 'D': 8, 'E': 5 },
    'C': { 'B': 3, 'E': 7 },
    'D': { 'A': 6, 'B': 8, 'E': 9 },
    'E': { 'B': 5, 'C': 7, 'D': 9 }
};

// Run the algorithms and print the output
primMST_Matrix(graphMatrix);
primMST_List(graphList);
primMST_PQ(graphMatrix);
primMST_Object(graphObject);
primMST_Optimized(graphMatrix);

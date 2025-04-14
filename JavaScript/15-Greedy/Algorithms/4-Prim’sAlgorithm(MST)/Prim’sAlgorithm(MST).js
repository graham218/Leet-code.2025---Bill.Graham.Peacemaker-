// Prim's Algorithm for Minimum Spanning Tree (MST)

// Helper function to find the vertex with the minimum key value
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

// Function to print the constructed MST
function printMST(parent, graph) {
    console.log("Edge \tWeight");
    let totalWeight = 0;
    for (let i = 1; i < graph.length; i++) {
        console.log(parent[i] + " - " + i + "\t" + graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    console.log("Total MST Weight:", totalWeight);
}

// Approach 1: Basic Implementation of Prim's Algorithm
function primMST_Basic(graph) {
    const V = graph.length; // Number of vertices in the graph
    const parent = new Array(V); // Array to store constructed MST
    const key = new Array(V);   // Key values used to pick minimum weight edge in cut
    const mstSet = new Array(V); // To represent set of vertices included in MST

    // Initialize all keys as INFINITE and mstSet[] as false
    for (let v = 0; v < V; v++) {
        key[v] = Infinity;
        mstSet[v] = false;
    }

    // Include first vertex in MST
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V-1 vertices
    for (let count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        const u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (let v = 0; v < V; v++) {
            // graph[u][v] is non zero only for adjacent vertices of u
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] !== 0 && mstSet[v] === false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    console.log("Prim's Algorithm - Basic Implementation:");
    printMST(parent, graph);
}

// Approach 2: Using Priority Queue (Min Heap)
class PriorityQueue {
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
}

function primMST_PriorityQueue(graph) {
    const V = graph.length;
    const parent = new Array(V);
    const key = new Array(V);
    const mstSet = new Array(V);
    const pq = new PriorityQueue();

    for (let v = 0; v < V; v++) {
        key[v] = Infinity;
        mstSet[v] = false;
    }

    key[0] = 0;
    parent[0] = -1;
    pq.enqueue(0, 0); // Enqueue the starting vertex with priority 0

    while (!pq.isEmpty()) {
        const u = pq.dequeue(); // Dequeue the vertex with minimum key value
        mstSet[u] = true;

        for (let v = 0; v < V; v++) {
            if (graph[u][v] !== 0 && mstSet[v] === false && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.enqueue(v, key[v]); // Enqueue with updated key value
            }
        }
    }
    console.log("Prim's Algorithm - Priority Queue Implementation:");
    printMST(parent, graph);
}

// Approach 3: Using Adjacency List
function primMST_AdjacencyList(adjList) {
    const V = adjList.length;
    const parent = new Array(V);
    const key = new Array(V);
    const mstSet = new Array(V);
    const pq = new PriorityQueue();

    for (let v = 0; v < V; v++) {
        key[v] = Infinity;
        mstSet[v] = false;
    }

    key[0] = 0;
    parent[0] = -1;
    pq.enqueue(0, 0);

    while (!pq.isEmpty()) {
        const u = pq.dequeue();
        mstSet[u] = true;

        for (const [v, weight] of adjList[u]) {
            if (mstSet[v] === false && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.enqueue(v, key[v]);
            }
        }
    }

    console.log("Prim's Algorithm - Adjacency List Implementation:");
    const graph = Array(V).fill(null).map(() => Array(V).fill(0)); //convert adjList back to matrix to use printMST
     for (let i = 0; i < V; i++) {
        for (const [j, weight] of adjList[i]) {
            graph[i][j] = weight;
        }
    }
    printMST(parent, graph);
}

// Approach 4: Optimized with Lazy Deletion in Priority Queue
class PriorityQueueLazy {
    constructor() {
        this.heap = [];
        this.position = []; // Keep track of the position of each vertex in the heap
    }

    enqueue(item, priority) {
        this.heap.push({ item, priority, deleted: false });
        this.position[item] = this.heap.length - 1;
        this.bubbleUp(this.heap.length - 1);
    }

    dequeue() {
        if (this.isEmpty()) return null;
        let item;
        do {
            this.swap(0, this.heap.length - 1);
            item = this.heap.pop();
        } while (item.deleted); // Keep removing until we get a non-deleted item
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
        //update the positions
        this.position[this.heap[i].item] = i;
        this.position[this.heap[j].item] = j;
    }

     updatePriority(item, newPriority) {
        const index = this.position[item];
        if (index !== undefined) {
            this.heap[index].priority = newPriority;
            this.bubbleUp(index); // Maintain heap property
            this.bubbleDown(index);
        }
    }

    remove(item) {
        const index = this.position[item];
        if (index !== undefined) {
            this.heap[index].deleted = true; // Mark as deleted
            // No need to re-heapify here, we'll handle it in dequeue
        }
    }
}
function primMST_Optimized(graph) {
    const V = graph.length;
    const parent = new Array(V);
    const key = new Array(V);
    const mstSet = new Array(V);
    const pq = new PriorityQueueLazy();

    for (let v = 0; v < V; v++) {
        key[v] = Infinity;
        mstSet[v] = false;
    }

    key[0] = 0;
    parent[0] = -1;
    pq.enqueue(0, 0);

    while (!pq.isEmpty()) {
        const u = pq.dequeue();
        mstSet[u] = true;

        for (let v = 0; v < V; v++) {
            if (graph[u][v] !== 0 && mstSet[v] === false && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.updatePriority(v, key[v]);
            }
        }
    }

    console.log("Prim's Algorithm - Optimized Implementation:");
    printMST(parent, graph);
}

// Approach 5: Real-world Application - Network Cable Laying
function networkCableLaying(sites, connections) {
    const V = sites.length;
    const siteIndices = {};
    for (let i = 0; i < V; i++) {
        siteIndices[sites[i]] = i;
    }

    // Create the graph representation
    const graph = Array(V).fill(null).map(() => Array(V).fill(0));
    for (const [site1, site2, cost] of connections) {
        const u = siteIndices[site1];
        const v = siteIndices[site2];
        graph[u][v] = cost;
        graph[v][u] = cost; // Assuming undirected graph
    }

    const parent = new Array(V);
    const key = new Array(V);
    const mstSet = new Array(V);

    for (let v = 0; v < V; v++) {
        key[v] = Infinity;
        mstSet[v] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (let count = 0; count < V - 1; count++) {
        const u = minKey(key, mstSet);
        mstSet[u] = true;

        for (let v = 0; v < V; v++) {
            if (graph[u][v] !== 0 && mstSet[v] === false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    console.log("Network Cable Laying Application (Prim's Algorithm):");
    let totalCost = 0;
    const mstEdges = [];
    for (let i = 1; i < V; i++) {
        const fromSite = sites[parent[i]];
        const toSite = sites[i];
        const cost = graph[i][parent[i]];
        console.log(`Lay cable between ${fromSite} and ${toSite} with cost: ${cost}`);
        totalCost += cost;
        mstEdges.push([fromSite, toSite, cost]); // Store edges for further use if needed
    }
    console.log("Total Cost of Cable Laying:", totalCost);
    return { totalCost, mstEdges };
}

// Example Graph Representation (Adjacency Matrix)
const graph = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
];

// Example Adjacency List
const adjList = [
    [[1, 2], [3, 6]],       // Node 0
    [[0, 2], [2, 3], [3, 8], [4, 5]], // Node 1
    [[1, 3], [4, 7]],       // Node 2
    [[0, 6], [1, 8], [4, 9]], // Node 3
    [[1, 5], [2, 7], [3, 9]]  // Node 4
];

// Example for Network Cable Laying
const sites = ['A', 'B', 'C', 'D', 'E'];
const connections = [
    ['A', 'B', 2],
    ['A', 'D', 6],
    ['B', 'C', 3],
    ['B', 'D', 8],
    ['B', 'E', 5],
    ['C', 'E', 7],
    ['D', 'E', 9]
];

// Run the algorithms and application
primMST_Basic(graph);
primMST_PriorityQueue(graph);
primMST_AdjacencyList(adjList);
primMST_Optimized(graph);
networkCableLaying(sites, connections);

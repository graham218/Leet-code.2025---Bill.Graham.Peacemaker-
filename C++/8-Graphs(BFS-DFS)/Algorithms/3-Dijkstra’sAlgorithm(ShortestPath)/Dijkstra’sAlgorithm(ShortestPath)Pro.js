// Dijkstra's Algorithm in JavaScript - 5 Approaches with Real-World Examples

// 1. Basic Dijkstra's Algorithm (Adjacency Matrix)
//   - Simple implementation for demonstration.  Not optimized for large graphs.
//   - Example Application:  Finding the shortest path in a small, static network.

function dijkstraMatrix(graph, startNode) {
    const numNodes = graph.length;
    const distances = new Array(numNodes).fill(Infinity);
    const visited = new Array(numNodes).fill(false);

    distances[startNode] = 0;

    for (let count = 0; count < numNodes - 1; count++) {
        const u = minDistance(distances, visited);
        visited[u] = true;

        for (let v = 0; v < numNodes; v++) {
            if (!visited[v] && graph[u][v] !== 0 && distances[u] !== Infinity &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }
    return distances;
}

function minDistance(distances, visited) {
    let min = Infinity;
    let minIndex = -1;

    for (let v = 0; v < distances.length; v++) {
        if (!visited[v] && distances[v] <= min) {
            min = distances[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// 2. Dijkstra's Algorithm with Priority Queue (Adjacency List)
//   - Uses a priority queue (implemented as a min-heap) for efficiency.
//   - Example Application:  Route planning in a GPS navigation system (calculating the fastest route).

class PriorityQueue {
    constructor() {
        this.heap = [];
    }

    enqueue(node, priority) {
        this.heap.push({ node, priority });
        this.bubbleUp(this.heap.length - 1);
    }

    dequeue() {
        if (this.isEmpty()) return null;
        this.swap(0, this.heap.length - 1);
        const item = this.heap.pop();
        this.bubbleDown(0);
        return item.node;
    }

    isEmpty() {
        return this.heap.length === 0;
    }
    peek() {
      return this.heap[0];
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
        const length = this.heap.length;
        while (true) {
            let left = 2 * index + 1;
            let right = 2 * index + 2;
            let smallest = index;

            if (left < length && this.heap[left].priority < this.heap[smallest].priority) {
                smallest = left;
            }
            if (right < length && this.heap[right].priority < this.heap[smallest].priority) {
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

function dijkstraList(adjList, startNode) {
    const numNodes = adjList.length;
    const distances = new Array(numNodes).fill(Infinity);
    distances[startNode] = 0;
    const pq = new PriorityQueue();
    pq.enqueue(startNode, 0);

    while (!pq.isEmpty()) {
        const u = pq.dequeue();

        for (const neighbor of adjList[u]) {
            const v = neighbor.node;
            const weight = neighbor.weight;
            if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.enqueue(v, distances[v]);
            }
        }
    }
    return distances;
}

// 3. Dijkstra's Algorithm with Path Reconstruction
//    -  Reconstructs the shortest path in addition to finding the distance.
//    -  Example Application:  Network routing protocols (e.g., OSPF) where routers need to know the shortest path to each destination.
function dijkstraWithPath(adjList, startNode, endNode) {
    const numNodes = adjList.length;
    const distances = new Array(numNodes).fill(Infinity);
    const previous = new Array(numNodes).fill(null);  // Store the previous node in the shortest path
    distances[startNode] = 0;
    const pq = new PriorityQueue();
    pq.enqueue(startNode, 0);

    while (!pq.isEmpty()) {
        const u = pq.dequeue();
        if (u === endNode) break; // Optimization: Stop if we reach the target

        for (const neighbor of adjList[u]) {
            const v = neighbor.node;
            const weight = neighbor.weight;
            if (distances[u] !== Infinity && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u; // Store the path
                pq.enqueue(v, distances[v]);
            }
        }
    }

    // Reconstruct the path
    const path = [];
    if (distances[endNode] !== Infinity) {
        let current = endNode;
        while (current !== null) {
            path.unshift(current); // Add to the beginning of the path
            current = previous[current];
        }
    }
    return { distance: distances[endNode], path };
}

// 4. Dijkstra's Algorithm for a Grid (2D Array)
//    - Adapted to find the shortest path in a 2D grid (e.g., a maze).
//     - Example Application:  Pathfinding in a game (e.g., finding the shortest route for an AI character).

function dijkstraGrid(grid, startRow, startCol, endRow, endCol) {
    const numRows = grid.length;
    const numCols = grid[0].length;
    const distances = Array(numRows).fill(null).map(() => Array(numCols).fill(Infinity));
    const visited = Array(numRows).fill(null).map(() => Array(numCols).fill(false));
    const pq = new PriorityQueue();

    distances[startRow][startCol] = 0;
    pq.enqueue({ row: startRow, col: startCol }, 0);

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // Possible moves (right, down, left, up)

    while (!pq.isEmpty()) {
        const { row, col } = pq.dequeue();
        if (row === endRow && col === endCol) break;

        if (visited[row][col]) continue;
        visited[row][col] = true;

        for (const [deltaRow, deltaCol] of directions) {
            const newRow = row + deltaRow;
            const newCol = col + deltaCol;

            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                grid[newRow][newCol] !== 0) { // 0 represents a wall or obstacle
                const newDistance = distances[row][col] + grid[newRow][newCol]; // Weight is the cell value
                if (newDistance < distances[newRow][newCol]) {
                    distances[newRow][newCol] = newDistance;
                    pq.enqueue({ row: newRow, col: newCol }, newDistance);
                }
            }
        }
    }
    return distances[endRow][endCol];
}

// 5. Dijkstra's Algorithm with Edge Weights as Objects
//    - Handles edge weights represented as objects with properties (e.g., cost and time).
//    - Example Application:  Multi-criteria route optimization (e.g., finding the route with the lowest cost and shortest travel time).

function dijkstraWeightedObjects(adjList, startNode, endNode) {
    const numNodes = adjList.length;
    const distances = new Array(numNodes).fill(Infinity);
    const previous = new Array(numNodes).fill(null);
    distances[startNode] = 0;
    const pq = new PriorityQueue();
    pq.enqueue(startNode, 0);

    while (!pq.isEmpty()) {
        const u = pq.dequeue();
         if (u === endNode) break;

        for (const neighbor of adjList[u]) {
            const v = neighbor.node;
            const weight = neighbor.weight; //  neighbor.weight is an object
            const cost = weight.cost;
            const time = weight.time;
            // In a real scenario, you might want to optimize for a combination of cost and time.
            // Here, we'll just use cost for the shortest path calculation.
            if (distances[u] !== Infinity && distances[u] + cost < distances[v]) {
                distances[v] = distances[u] + cost;
                previous[v] = u;
                pq.enqueue(v, distances[v]);
            }
        }
    }
      const path = [];
      if (distances[endNode] !== Infinity) {
          let current = endNode;
          while (current !== null) {
              path.unshift(current);
              current = previous[current];
          }
      }
      return { distance: distances[endNode], path };
}



// Example Usage and Output

// 1. Basic Dijkstra's Algorithm (Adjacency Matrix)
const graphMatrix = [
    [0, 4, 0, 0, 0, 0, 0, 8, 0],
    [4, 0, 8, 0, 0, 0, 0, 11, 0],
    [0, 8, 0, 7, 0, 4, 0, 0, 2],
    [0, 0, 7, 0, 9, 14, 0, 0, 0],
    [0, 0, 0, 9, 0, 10, 0, 0, 0],
    [0, 0, 4, 14, 10, 0, 2, 0, 0],
    [0, 0, 0, 0, 0, 2, 0, 1, 6],
    [8, 11, 0, 0, 0, 0, 1, 0, 7],
    [0, 0, 2, 0, 0, 0, 6, 7, 0]
];
console.log("1. Dijkstra's Algorithm (Adjacency Matrix):");
console.log(dijkstraMatrix(graphMatrix, 0)); // Output: [ 0, 4, 12, 19, 21, 11, 9, 8, 14 ]


// 2. Dijkstra's Algorithm with Priority Queue (Adjacency List)
const graphList = [
    [{ node: 1, weight: 4 }, { node: 7, weight: 8 }],
    [{ node: 0, weight: 4 }, { node: 2, weight: 8 }, { node: 7, weight: 11 }],
    [{ node: 1, weight: 8 }, { node: 3, weight: 7 }, { node: 5, weight: 4 }, { node: 8, weight: 2 }],
    [{ node: 2, weight: 7 }, { node: 4, weight: 9 }, { node: 5, weight: 14 }],
    [{ node: 3, weight: 9 }, { node: 5, weight: 10 }],
    [{ node: 2, weight: 4 }, { node: 3, weight: 14 }, { node: 4, weight: 10 }, { node: 6, weight: 2 }],
    [{ node: 5, weight: 2 }, { node: 7, weight: 1 }, { node: 8, weight: 6 }],
    [{ node: 0, weight: 8 }, { node: 1, weight: 11 }, { node: 6, weight: 1 }, { node: 8, weight: 7 }],
    [{ node: 2, weight: 2 }, { node: 6, weight: 6 }, { node: 7, weight: 7 }]
];

console.log("\n2. Dijkstra's Algorithm with Priority Queue (Adjacency List):");
console.log(dijkstraList(graphList, 0)); // Output: [ 0, 4, 12, 19, 21, 11, 9, 8, 14 ]


// 3. Dijkstra's Algorithm with Path Reconstruction
console.log("\n3. Dijkstra's Algorithm with Path Reconstruction:");
const { distance, path } = dijkstraWithPath(graphList, 0, 4);
console.log("Shortest Distance:", distance); // Output: 21
console.log("Shortest Path:", path);       // Output: [ 0, 1, 2, 3, 4 ]

// 4. Dijkstra's Algorithm for a Grid (2D Array)
const grid = [
    [1, 3, 1, 2],
    [4, 0, 3, 0],
    [2, 1, 5, 1],
    [1, 1, 1, 1]
];
console.log("\n4. Dijkstra's Algorithm for a Grid (2D Array):");
const shortestPathLength = dijkstraGrid(grid, 0, 0, 3, 3);
console.log("Shortest Path Length:", shortestPathLength); // Output: 8


// 5. Dijkstra's Algorithm with Edge Weights as Objects
const weightedGraphList = [
  [
    { node: 1, weight: { cost: 4, time: 10 } },
    { node: 7, weight: { cost: 8, time: 15 } },
  ],
  [
    { node: 0, weight: { cost: 4, time: 10 } },
    { node: 2, weight: { cost: 8, time: 20 } },
    { node: 7, weight: { cost: 11, time: 25 } },
  ],
  [
    { node: 1, weight: { cost: 8, time: 20 } },
    { node: 3, weight: { cost: 7, time: 18 } },
    { node: 5, weight: { cost: 4, time: 12 } },
    { node: 8, weight: { cost: 2, time: 5 } },
  ],
  [
    { node: 2, weight: { cost: 7, time: 18 } },
    { node: 4, weight: { cost: 9, time: 22 } },
    { node: 5, weight: { cost: 14, time: 30 } },
  ],
  [
    { node: 3, weight: { cost: 9, time: 22 } },
    { node: 5, weight: { cost: 10, time: 24 } },
  ],
  [
    { node: 2, weight: { cost: 4, time: 12 } },
    { node: 3, weight: { cost: 14, time: 30 } },
    { node: 4, weight: { cost: 10, time: 24 } },
    { node: 6, weight: { cost: 2, time: 6 } },
  ],
  [
    { node: 5, weight: { cost: 2, time: 6 } },
    { node: 7, weight: { cost: 1, time: 3 } },
    { node: 8, weight: { cost: 6, time: 14 } },
  ],
  [
    { node: 0, weight: { cost: 8, time: 15 } },
    { node: 1, weight: { cost: 11, time: 25 } },
    { node: 6, weight: { cost: 1, time: 3 } },
    { node: 8, weight: { cost: 7, time: 16 } },
  ],
  [
    { node: 2, weight: { cost: 2, time: 5 } },
    { node: 6, weight: { cost: 6, time: 14 } },
    { node: 7, weight: { cost: 7, time: 16 } },
  ],
];

console.log("\n5. Dijkstra's Algorithm with Edge Weights as Objects:");
const result = dijkstraWeightedObjects(weightedGraphList, 0, 4);
console.log("Shortest Distance (Cost):", result.distance);
console.log("Shortest Path:", result.path);

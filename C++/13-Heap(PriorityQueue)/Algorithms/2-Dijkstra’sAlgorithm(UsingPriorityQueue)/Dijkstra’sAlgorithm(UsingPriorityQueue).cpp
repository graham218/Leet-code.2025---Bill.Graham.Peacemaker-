/**
 * Dijkstra's Algorithm Implementation in JavaScript
 * Using a Priority Queue (Heap)
 * Demonstrates 5 different approaches for comparison
 */

// Helper function to create an adjacency list from edge list
function createAdjacencyList(edges, directed = false) {
  const adjacencyList = {};
  for (const [u, v, weight] of edges) {
    if (!adjacencyList[u]) {
      adjacencyList[u] = [];
    }
    adjacencyList[u].push({ node: v, weight });
    if (!directed) {
      if (!adjacencyList[v]) {
        adjacencyList[v] = [];
      }
      adjacencyList[v].push({ node: u, weight });
    }
  }
  return adjacencyList;
}

// Sample graph represented as an edge list: (node1, node2, weight)
const graphEdges = [
  ['A', 'B', 4],
  ['A', 'C', 2],
  ['B', 'C', 1],
  ['B', 'D', 5],
  ['C', 'D', 8],
  ['C', 'E', 10],
  ['D', 'E', 2],
  ['E', 'F', 3],
  ['D', 'F', 2],
];
const startNode = 'A';
const adjacencyList = createAdjacencyList(graphEdges);

/**
 * Approach 1:  Simple Array as Priority Queue (No optimization)
 * -   Uses a simple array to store nodes and distances.
 * -   Finds the minimum distance node by iterating through the entire array.
 * -   This is the most basic implementation, not very efficient for large graphs.
 */
function dijkstraArray(graph, start) {
  const distances = {};
  const visited = {};
  const nodes = Object.keys(graph);

  // Initialize distances to Infinity for all nodes except the start node
  for (const node of nodes) {
    distances[node] = node === start ? 0 : Infinity;
  }

  const queue = [[start, 0]]; // [node, distance]

  while (queue.length > 0) {
    // Find the node with the smallest distance in the queue
    let minDistance = Infinity;
    let minIndex = -1;
    for (let i = 0; i < queue.length; i++) {
      if (queue[i][1] < minDistance) {
        minDistance = queue[i][1];
        minIndex = i;
      }
    }
    const [currentNode, currentDistance] = queue.splice(minIndex, 1)[0];

    if (visited[currentNode]) {
      continue; // Skip if already visited
    }
    visited[currentNode] = true;

    if (currentDistance > distances[currentNode]) {
        continue; // Important: Check for outdated distances
    }

    if (!graph[currentNode]) continue; // handle disconnected nodes

    for (const neighbor of graph[currentNode]) {
      const newDistance = currentDistance + neighbor.weight;
      if (newDistance < distances[neighbor.node]) {
        distances[neighbor.node] = newDistance;
        queue.push([neighbor.node, newDistance]);
      }
    }
  }
  return distances;
}

/**
 * Approach 2: Sorted Array as Priority Queue
 * - Uses a sorted array, keeping it sorted by distance.
 * -  Insertion is O(n), extraction is O(1), but still O(n^2) overall.
 */
function dijkstraSortedArray(graph, start) {
    const distances = {};
    const visited = {};
    const nodes = Object.keys(graph);

    for (const node of nodes) {
        distances[node] = node === start ? 0 : Infinity;
    }

    let queue = [[start, 0]];

    while (queue.length > 0) {
        const [currentNode, currentDistance] = queue.shift(); // Get the first element

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        if (currentDistance > distances[currentNode]) continue;

        if (!graph[currentNode]) continue;

        for (const neighbor of graph[currentNode]) {
            const newDistance = currentDistance + neighbor.weight;
            if (newDistance < distances[neighbor.node]) {
                distances[neighbor.node] = newDistance;
                // Insert into the sorted array to maintain order
                let inserted = false;
                for (let i = 0; i < queue.length; i++) {
                    if (newDistance < queue[i][1]) {
                        queue.splice(i, 0, [neighbor.node, newDistance]);
                        inserted = true;
                        break;
                    }
                }
                if (!inserted) {
                    queue.push([neighbor.node, newDistance]);
                }
            }
        }
    }
    return distances;
}

/**
 * Approach 3: Binary Heap (Priority Queue) - Efficient
 * -   Uses a binary min-heap to efficiently store and retrieve the node with the smallest distance.
 * -   Improves the time complexity to O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
class MinHeap {
  constructor() {
    this.heap = [];
  }

  push(value) {
    this.heap.push(value);
    this.bubbleUp(this.heap.length - 1);
  }

  pop() {
    if (this.isEmpty()) {
      return null;
    }
    this.swap(0, this.heap.length - 1);
    const min = this.heap.pop();
    this.bubbleDown(0);
    return min;
  }

  isEmpty() {
    return this.heap.length === 0;
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index][1] >= this.heap[parentIndex][1]) {
        break;
      }
      this.swap(index, parentIndex);
      index = parentIndex;
    }
  }

  bubbleDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let smallest = index;

      if (
        leftChild < this.heap.length &&
        this.heap[leftChild][1] < this.heap[smallest][1]
      ) {
        smallest = leftChild;
      }

      if (
        rightChild < this.heap.length &&
        this.heap[rightChild][1] < this.heap[smallest][1]
      ) {
        smallest = rightChild;
      }

      if (smallest === index) {
        break;
      }

      this.swap(index, smallest);
      index = smallest;
    }
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }
}

function dijkstraHeap(graph, start) {
  const distances = {};
  const visited = {};
  const nodes = Object.keys(graph);

  for (const node of nodes) {
    distances[node] = node === start ? 0 : Infinity;
  }

  const priorityQueue = new MinHeap();
  priorityQueue.push([start, 0]);

  while (!priorityQueue.isEmpty()) {
    const [currentNode, currentDistance] = priorityQueue.pop();

    if (visited[currentNode]) continue;
    visited[currentNode] = true;

     if (currentDistance > distances[currentNode]) continue;

    if (!graph[currentNode]) continue;

    for (const neighbor of graph[currentNode]) {
      const newDistance = currentDistance + neighbor.weight;
      if (newDistance < distances[neighbor.node]) {
        distances[neighbor.node] = newDistance;
        priorityQueue.push([neighbor.node, newDistance]);
      }
    }
  }
  return distances;
}

/**
 * Approach 4: Optimized Binary Heap with Decrease Key (If Applicable)
 * -   This approach is similar to the Binary Heap approach but includes a `decreaseKey` operation
 * for the priority queue, which can further optimize the algorithm in some cases.  JavaScript
 * doesn't have a native decreaseKey, and implementing it efficiently adds complexity.  This
 * version shows the *idea* but isn't fully optimized.
 */
 class MinHeapWithDecreaseKey extends MinHeap {
    decreaseKey(node, newDistance) {
        for (let i = 0; i < this.heap.length; i++) {
            if (this.heap[i][0] === node) {
                if (newDistance < this.heap[i][1]) {
                    this.heap[i][1] = newDistance;
                    this.bubbleUp(i); // Important:  Bubble up after decreasing key
                }
                return;
            }
        }
        // If the node isn't in the heap, it's not an error, just don't do anything.
    }

    // push needs to be modified to handle the case where a node is already in the heap
    push(value) {
      for (let i = 0; i < this.heap.length; i++) {
        if (this.heap[i][0] === value[0]) {
          if (value[1] < this.heap[i][1]) {
             this.decreaseKey(value[0], value[1]);
          }
          return; // Important: Exit if node is found
        }
      }
      // If the node wasn't found, add it as a new element
      this.heap.push(value);
      this.bubbleUp(this.heap.length - 1);
    }
}

function dijkstraDecreaseKey(graph, start) {
    const distances = {};
    const visited = {};
    const nodes = Object.keys(graph);

    for (const node of nodes) {
        distances[node] = node === start ? 0 : Infinity;
    }

    const priorityQueue = new MinHeapWithDecreaseKey();
    priorityQueue.push([start, 0]);

    while (!priorityQueue.isEmpty()) {
        const [currentNode, currentDistance] = priorityQueue.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        if (currentDistance > distances[currentNode]) continue;

        if (!graph[currentNode]) continue;

        for (const neighbor of graph[currentNode]) {
            const newDistance = currentDistance + neighbor.weight;
            if (newDistance < distances[neighbor.node]) {
                distances[neighbor.node] = newDistance;
                priorityQueue.push([neighbor.node, newDistance]); // Use the modified push
            }
        }
    }
    return distances;
}

/**
 * Approach 5: Using a JavaScript Object as a Priority Queue (for demonstration)
 * -  This approach uses a JavaScript object to simulate a priority queue.  It's NOT
 * generally recommended for performance-critical applications because object key
 * iteration is not guaranteed to be ordered, and finding the minimum is O(n).
 * -  It's included here for comparison and to show a different way of thinking
 * about the problem.
 */
function dijkstraObject(graph, start) {
  const distances = {};
  const visited = {};
  const nodes = Object.keys(graph);

  for (const node of nodes) {
    distances[node] = node === start ? 0 : Infinity;
  }

  const queue = { [start]: 0 }; // {node: distance}

  while (Object.keys(queue).length > 0) {
    // Find the node with the smallest distance in the queue
    let minDistance = Infinity;
    let currentNode = null;
    for (const node in queue) {
      if (queue[node] < minDistance) {
        minDistance = queue[node];
        currentNode = node;
      }
    }

    if (currentNode === null) break;  // Should not happen, but for safety

    const currentDistance = queue[currentNode];
    delete queue[currentNode]; // Remove the current node

    if (visited[currentNode]) continue;
    visited[currentNode] = true;

     if (currentDistance > distances[currentNode]) continue;

    if (!graph[currentNode]) continue;

    for (const neighbor of graph[currentNode]) {
      const newDistance = currentDistance + neighbor.weight;
      if (newDistance < distances[neighbor.node]) {
        distances[neighbor.node] = newDistance;
        queue[neighbor.node] = newDistance; // Add/update in the queue
      }
    }
  }
  return distances;
}

// Run and display results using console.log
console.log('Graph:', adjacencyList);
console.log('Start Node:', startNode);

console.log('\nApproach 1: Simple Array');
console.log(dijkstraArray(adjacencyList, startNode));

console.log('\nApproach 2: Sorted Array');
console.log(dijkstraSortedArray(adjacencyList, startNode));

console.log('\nApproach 3: Binary Heap');
console.log(dijkstraHeap(adjacencyList, startNode));

console.log('\nApproach 4: Binary Heap with Decrease Key');
console.log(dijkstraDecreaseKey(adjacencyList, startNode));

console.log('\nApproach 5: Using Object as Priority Queue');
console.log(dijkstraObject(adjacencyList, startNode));

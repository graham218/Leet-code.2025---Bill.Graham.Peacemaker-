/**
 * Dijkstra's Algorithm Implementation in JavaScript (5 Approaches)
 * -------------------------------------------------------------
 * Demonstrates 5 different ways to implement Dijkstra's algorithm to find the shortest
 * path from a source node to all other nodes in a weighted graph.
 *
 * Approaches Included:
 * 1.  Basic Implementation (using a simple array for unvisited nodes)
 * 2.  Optimized with a Min-Heap (Priority Queue)
 * 3.  Using a Set (for visited tracking and removal) -  *Note: Sets do not provide efficient priority queue functionality, this is for demonstration of an alternative data structure, and is not recommended for performance.*
 * 4.  Object for unvisited, optimized removal
 * 5.  Adjacency Matrix Representation
 *
 * Key Concepts:
 * -   Graph: A data structure representing a set of vertices (nodes) and edges (connections)
 * -   Weighted Graph: A graph where each edge has a weight (cost) associated with it
 * -   Shortest Path: The path between two nodes in a graph with the minimum total weight
 * -   Dijkstra's Algorithm: A greedy algorithm that finds the shortest path from a source
 * node to all other nodes in a weighted graph (with non-negative edge weights)
 * -   Min-Heap (Priority Queue): A data structure that allows efficient retrieval of the
 * minimum element.  Essential for efficient Dijkstra's.
 *
 * Time Complexity:
 * -   Basic Implementation: O(V^2), where V is the number of vertices.
 * -   Optimized with Min-Heap: O((V + E) log V), where E is the number of edges.
 * -   Using a Set:  O(V^2) in the worst case, can be higher depending on JS engine.
 * -   Object for unvisited: O(V^2)
  * -  Adjacency Matrix: O(V^2)
 *
 * Space Complexity: O(V + E) for adjacency list, O(V^2) for adjacency matrix, O(V) for distances and visited sets.
 */

// Helper function to create a simple min-heap (for demonstration purposes)
// In a real-world scenario, use a dedicated library or a more robust heap implementation.
class MinHeap {
  constructor() {
    this.heap = [];
  }

  insert(value) {
    this.heap.push(value);
    this.bubbleUp(this.heap.length - 1);
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index][1] >= this.heap[parentIndex][1]) break;
      [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
      index = parentIndex;
    }
  }

  extractMin() {
    if (this.heap.length === 0) return null;
    if (this.heap.length === 1) return this.heap.pop();

    const min = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.sinkDown(0);
    return min;
  }

  sinkDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let smallest = index;

      if (leftChild < this.heap.length && this.heap[leftChild][1] < this.heap[smallest][1]) {
        smallest = leftChild;
      }

      if (rightChild < this.heap.length && this.heap[rightChild][1] < this.heap[smallest][1]) {
        smallest = rightChild;
      }

      if (smallest === index) break;

      [this.heap[index], this.heap[smallest]] = [this.heap[smallest], this.heap[index]];
      index = smallest;
    }
  }

  isEmpty() {
    return this.heap.length === 0;
  }
}

// 1. Basic Implementation
function dijkstraBasic(graph, startNode) {
  const numNodes = graph.length;
  const distances = Array(numNodes).fill(Infinity);
  const visited = Array(numNodes).fill(false);
  const previous = Array(numNodes).fill(null); // To reconstruct the path

  distances[startNode] = 0;
  let unvisited = Array.from({ length: numNodes }, (_, i) => i); // [0, 1, 2, ..., numNodes-1]

  while (unvisited.length > 0) {
    // Find the node with the smallest distance
    let minIndex = 0;
    for (let i = 1; i < unvisited.length; i++) {
      if (distances[unvisited[i]] < distances[unvisited[minIndex]]) {
        minIndex = i;
      }
    }
    const currentNode = unvisited[minIndex];
    unvisited.splice(minIndex, 1);
    visited[currentNode] = true;

    // Update distances to neighbors
    for (let neighbor = 0; neighbor < numNodes; neighbor++) {
      if (graph[currentNode][neighbor] !== 0 && !visited[neighbor] && distances[currentNode] + graph[currentNode][neighbor] < distances[neighbor]) {
        distances[neighbor] = distances[currentNode] + graph[currentNode][neighbor];
        previous[neighbor] = currentNode; // Store the previous node in the shortest path
      }
    }
  }
  return { distances, previous };
}

// 2. Optimized with Min-Heap
function dijkstraHeap(graph, startNode) {
  const numNodes = graph.length;
  const distances = Array(numNodes).fill(Infinity);
  const visited = Array(numNodes).fill(false);
  const previous = Array(numNodes).fill(null);
  distances[startNode] = 0;
  const minHeap = new MinHeap();
  minHeap.insert([startNode, 0]); // [node, distance]

  while (!minHeap.isEmpty()) {
    const [currentNode, currentDistance] = minHeap.extractMin();

    if (visited[currentNode]) continue; // Important optimization
    visited[currentNode] = true;

    for (let neighbor = 0; neighbor < numNodes; neighbor++) {
      if (graph[currentNode][neighbor] !== 0 && distances[currentNode] + graph[currentNode][neighbor] < distances[neighbor]) {
        distances[neighbor] = distances[currentNode] + graph[currentNode][neighbor];
        previous[neighbor] = currentNode;
        minHeap.insert([neighbor, distances[neighbor]]);
      }
    }
  }
  return { distances, previous };
}

// 3. Using a Set (for demonstration - not efficient for priority queue)
function dijkstraSet(graph, startNode) {
  const numNodes = graph.length;
  const distances = Array(numNodes).fill(Infinity);
  const visited = new Set();
    const previous = Array(numNodes).fill(null);

  distances[startNode] = 0;
  const unvisited = new Set(Array.from({ length: numNodes }, (_, i) => i)); // Use a Set

  while (unvisited.size > 0) {
    let minNode = null;
    let minDistance = Infinity;
    for (const node of unvisited) { // Iterate through the *Set*
      if (distances[node] < minDistance) {
        minDistance = distances[node];
        minNode = node;
      }
    }

    const currentNode = minNode;
    unvisited.delete(currentNode); // Remove from the Set.  Expensive in JS.
    visited.add(currentNode);

    for (let neighbor = 0; neighbor < numNodes; neighbor++) {
      if (graph[currentNode][neighbor] !== 0 && !visited.has(neighbor) && distances[currentNode] + graph[currentNode][neighbor] < distances[neighbor]) {
        distances[neighbor] = distances[currentNode] + graph[currentNode][neighbor];
         previous[neighbor] = currentNode;
      }
    }
  }
  return { distances, previous };
}

// 4. Object for unvisited, optimized removal
function dijkstraObject(graph, startNode) {
  const numNodes = graph.length;
  const distances = Array(numNodes).fill(Infinity);
  const visited = Array(numNodes).fill(false);
    const previous = Array(numNodes).fill(null);

  distances[startNode] = 0;
  const unvisited = {}; // Use an object as a "set" for faster deletion
  for (let i = 0; i < numNodes; i++) {
    unvisited[i] = distances[i]; // Store distances in the object
  }

  while (Object.keys(unvisited).length > 0) {
    let minNode = null;
    let minDistance = Infinity;
    for (const node in unvisited) {
      if (unvisited[node] < minDistance) {
        minDistance = unvisited[node];
        minNode = parseInt(node); // Parse back to number from string
      }
    }

    const currentNode = minNode;
    visited[currentNode] = true;
    delete unvisited[currentNode]; // Faster deletion using 'delete'

    for (let neighbor = 0; neighbor < numNodes; neighbor++) {
      if (graph[currentNode][neighbor] !== 0 && !visited[neighbor] && distances[currentNode] + graph[currentNode][neighbor] < distances[neighbor]) {
        distances[neighbor] = distances[currentNode] + graph[currentNode][neighbor];
        previous[neighbor] = currentNode;
        unvisited[neighbor] = distances[neighbor]; // Update distance in the unvisited object
      }
    }
  }
  return { distances, previous };
}

// 5. Adjacency Matrix Representation
function dijkstraMatrix(matrix, startNode) {
    const numNodes = matrix.length;
    const distances = Array(numNodes).fill(Infinity);
    const visited = Array(numNodes).fill(false);
      const previous = Array(numNodes).fill(null);

    distances[startNode] = 0;

    for (let count = 0; count < numNodes - 1; count++) {
        // Pick the minimum distance node from the unvisited nodes
        let minIndex = -1;
        let minDistance = Infinity;
        for (let v = 0; v < numNodes; v++) {
            if (visited[v] === false && distances[v] < minDistance) {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        if (minIndex === -1) break; // No reachable unvisited nodes

        const u = minIndex;
        visited[u] = true;

        // Update distances of the adjacent vertices of the picked node.
        for (let v = 0; v < numNodes; v++) {
            if (!visited[v] && matrix[u][v] !== 0 && distances[u] !== Infinity && distances[u] + matrix[u][v] < distances[v]) {
                distances[v] = distances[u] + matrix[u][v];
                previous[v] = u;
            }
        }
    }
    return { distances, previous };
}

// Example Graph (Adjacency Matrix)
const graph = [
  [0, 4, 0, 0, 0, 0, 0, 8, 0],
  [4, 0, 8, 0, 0, 0, 0, 11, 0],
  [0, 8, 0, 7, 0, 4, 0, 0, 2],
  [0, 0, 7, 0, 9, 14, 0, 0, 0],
  [0, 0, 0, 9, 0, 10, 0, 0, 0],
  [0, 0, 4, 14, 10, 0, 2, 0, 0],
  [0, 0, 0, 0, 0, 2, 0, 1, 6],
  [8, 11, 0, 0, 0, 0, 1, 0, 7],
  [0, 0, 2, 0, 0, 0, 6, 7, 0],
];

const startNode = 0;

// Function to reconstruct the shortest path
function reconstructPath(previous, startNode, endNode) {
  const path = [];
  let current = endNode;
  while (current !== null) {
    path.unshift(current); // Add to the beginning of the path
    current = previous[current];
  }
  if (path[0] !== startNode) {
    return []; // No path exists
  }
  return path;
}

// Function to display results, including the path
function displayResults(algorithmName, results, graph, startNode, endNode) {
    console.log(`\n${algorithmName}:`);
    console.log('Distances:', results.distances);

    if (results.previous) {
        const path = reconstructPath(results.previous, startNode, endNode);
        if (path.length > 0) {
            console.log(`Shortest path from ${startNode} to ${endNode}: ${path.join(' -> ')}`);
        } else {
            console.log(`No path exists from ${startNode} to ${endNode}`);
        }
    }
     else if (algorithmName === "dijkstraMatrix")
    {
       const numNodes = graph.length;
        for (let i = 0; i < numNodes; i++)
        {
             const path = reconstructPath(results.previous, startNode, i);
             if (path.length > 0)
             {
                  console.log(`Shortest path from ${startNode} to ${i}: ${path.join(' -> ')}`);
             }
             else
             {
                  console.log(`No path exists from ${startNode} to ${i}`);
             }
        }
    }
    else {
        const numNodes = graph.length;
        for (let i = 0; i < numNodes; i++) {
            const path = reconstructPath(results.previous, startNode, i);
            if (path.length > 0) {
                console.log(`Shortest path from ${startNode} to ${i}: ${path.join(' -> ')}`);
            } else {
                console.log(`No path exists from ${startNode} to ${i}`);
            }
        }
    }
}
// Run and display results for each implementation
const endNode = 5; // Example end node for path reconstruction

const basicResult = dijkstraBasic(graph, startNode);
displayResults("Basic Implementation", basicResult, graph, startNode, endNode);

const heapResult = dijkstraHeap(graph, startNode);
displayResults("Optimized with Min-Heap", heapResult, graph, startNode, endNode);

const setResult = dijkstraSet(graph, startNode);
displayResults("Using a Set", setResult, graph, startNode, endNode);

const objectResult = dijkstraObject(graph, startNode);
displayResults("Object for unvisited", objectResult, graph, startNode, endNode);

const matrixResult = dijkstraMatrix(graph, startNode);
displayResults("Adjacency Matrix Representation", matrixResult, graph, startNode, endNode);

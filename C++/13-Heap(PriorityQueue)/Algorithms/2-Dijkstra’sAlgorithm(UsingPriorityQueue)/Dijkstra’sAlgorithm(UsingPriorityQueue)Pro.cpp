// Dijkstra's Algorithm with Priority Queue (Heap) - 5 Approaches

// Core Dijkstra's Algorithm Implementation (using a min-heap)
class MinHeap {
  constructor() {
    this.heap = [];
  }

  push(node) {
    this.heap.push(node);
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

      if (leftChild < this.heap.length && this.heap[leftChild][1] < this.heap[smallest][1]) {
        smallest = leftChild;
      }

      if (rightChild < this.heap.length && this.heap[rightChild][1] < this.heap[smallest][1]) {
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

function dijkstra(graph, startNode) {
  const distances = {};
  const priorityQueue = new MinHeap();

  // Initialize distances
  for (const node in graph) {
    distances[node] = Infinity;
  }
  distances[startNode] = 0;
  priorityQueue.push([startNode, 0]);

  while (!priorityQueue.isEmpty()) {
    const [currentNode, currentDistance] = priorityQueue.pop();

    if (currentDistance > distances[currentNode]) {
      continue; // Skip if a shorter path has already been found
    }

    if (graph[currentNode]) { // Check if the node has neighbors
        for (const neighbor in graph[currentNode]) {
          const edgeWeight = graph[currentNode][neighbor];
          const newDistance = currentDistance + edgeWeight;

          if (newDistance < distances[neighbor]) {
            distances[neighbor] = newDistance;
            priorityQueue.push([neighbor, newDistance]);
          }
        }
    }
  }
  return distances;
}

// 1. Network Routing Optimization
function networkRouting(networkGraph, startRouter) {
  console.log('\n1. Network Routing Optimization:');
  const shortestPaths = dijkstra(networkGraph, startRouter);
  console.log('Shortest paths from router', startRouter, ':', shortestPaths);
  return shortestPaths;
}

// 2. City Navigation App
function cityNavigation(cityGraph, startLocation, destination) {
  console.log('\n2. City Navigation App:');
  const shortestPaths = dijkstra(cityGraph, startLocation);
  if (shortestPaths[destination] !== Infinity) {
    console.log(`Shortest distance from ${startLocation} to ${destination}: ${shortestPaths[destination]}`);
  } else {
    console.log(`No route found from ${startLocation} to ${destination}`);
  }
}

// 3. Supply Chain Management
function supplyChain(supplyGraph, startWarehouse, finalDestination) {
  console.log('\n3. Supply Chain Management:');
  const shortestPaths = dijkstra(supplyGraph, startWarehouse);
    if (shortestPaths[finalDestination] !== Infinity) {
        console.log(`Shortest path from ${startWarehouse} to ${finalDestination}: ${shortestPaths[finalDestination]}`);
    } else {
        console.log(`No route found from ${startWarehouse} to ${finalDestination}`);
    }

  return shortestPaths;
}

// 4. Airline Route Planning
function airlineRoute(flightGraph, source, dest) {
    console.log('\n4. Airline Route Planning');
    const shortestPaths = dijkstra(flightGraph, source);
     if (shortestPaths[dest] !== Infinity) {
        console.log(`Shortest path from ${source} to ${dest}: ${shortestPaths[dest]}`);
    } else {
        console.log(`No route found from ${source} to ${dest}`);
    }
    return shortestPaths;
}

// 5. Robotics Path Planning
function roboticsPath(robotGraph, startPoint, endPoint) {
  console.log('\n5. Robotics Path Planning:');
  const shortestPaths = dijkstra(robotGraph, startPoint);
  if(shortestPaths[endPoint] !== Infinity){
     console.log(`Shortest path from ${startPoint} to ${endPoint}: ${shortestPaths[endPoint]}`);
  }
  else{
    console.log(`No route found from ${startPoint} to ${endPoint}`);
  }

}

// Example Graphs (Adjacency List Representation)
const networkGraph = {
  'A': { 'B': 5, 'C': 3 },
  'B': { 'D': 2, 'E': 4 },
  'C': { 'B': 1, 'D': 7 },
  'D': { 'E': 1 },
  'E': {}
};

const cityGraph = {
  'Home': { 'Office': 10, 'Park': 5 },
  'Office': { 'Cafe': 3, 'Library': 7 },
  'Park': { 'Cafe': 2 },
  'Cafe': { 'Library': 4 },
  'Library': {}
};

const supplyGraph = {
    'WarehouseA': { 'DistributionCenterB': 10, 'RetailerC': 15 },
    'DistributionCenterB': { 'RetailerC': 5, 'StoreD': 20 },
    'RetailerC': { 'StoreD': 10 },
    'StoreD': {}
};
const flightGraph = {
    'NewYork': { 'Chicago': 200, 'LosAngeles': 500 },
    'Chicago': { 'Denver': 300, 'LosAngeles': 400 },
    'LosAngeles': { 'Denver': 100 },
    'Denver': {}
};

const robotGraph = {
  'A': { 'B': 1, 'C': 4 },
  'B': { 'D': 2, 'E': 5 },
  'C': { 'F': 3 },
  'D': { 'E': 1 },
  'E': { 'F': 1 },
  'F': {}
};

// Run the examples
networkRouting(networkGraph, 'A');
cityNavigation(cityGraph, 'Home', 'Library');
supplyChain(supplyGraph, 'WarehouseA', 'StoreD');
airlineRoute(flightGraph, 'NewYork', 'Denver');
roboticsPath(robotGraph, 'A', 'F');

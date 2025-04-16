// Helper function to create a weighted edge
function createWeightedEdge(source, destination, weight) {
  return { source, destination, weight };
}

// 1. Network Routing (Finding Shortest Paths in a Network)
function networkRoutingBellmanFord(nodes, edges, sourceNode) {
  const distances = {};
  nodes.forEach(node => distances[node] = Infinity);
  distances[sourceNode] = 0;

  for (let i = 0; i < nodes.length - 1; i++) {
    for (const { source, destination, weight } of edges) {
      if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
        distances[destination] = distances[source] + weight;
      }
    }
  }

  // Check for negative cycles
  for (const { source, destination, weight } of edges) {
    if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
      return "Negative cycle detected!";
    }
  }

  return distances;
}

// 2. Currency Exchange (Arbitrage Detection)
function currencyExchangeBellmanFord(currencies, exchangeRates, sourceCurrency) {
  const distances = {};
  currencies.forEach(currency => distances[currency] = Infinity);
  distances[sourceCurrency] = 0;

  const edges = [];
  for (const currency1 in exchangeRates) {
    for (const currency2 in exchangeRates[currency1]) {
      // Use negative logarithm to detect arbitrage (positive weight cycle)
      edges.push(createWeightedEdge(currency1, currency2, -Math.log(exchangeRates[currency1][currency2])));
    }
  }

  for (let i = 0; i < currencies.length - 1; i++) {
    for (const { source, destination, weight } of edges) {
      if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
        distances[destination] = distances[source] + weight;
      }
    }
  }

  // Check for arbitrage (negative cycle)
  for (const { source, destination, weight } of edges) {
    if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
      return "Arbitrage opportunity detected!";
    }
  }

  const result = {};
  for(const currency in distances){
     result[currency] = Math.exp(-distances[currency]);
  }
  return result;
}

// 3. Project Management (Finding the longest path, with negated weights)
function projectManagementBellmanFord(tasks, dependencies, startTask) {
    const distances = {};
    tasks.forEach(task => distances[task] = -Infinity);  // Initialize with negative infinity for longest path
    distances[startTask] = 0;

    const edges = [];
    for (const dependency of dependencies) {
        const { source, destination, duration } = dependency;
        edges.push(createWeightedEdge(source, destination, -duration)); // Negate duration for longest path
    }

    for (let i = 0; i < tasks.length - 1; i++) {
        for (const { source, destination, weight } of edges) {
            if (distances[source] !== -Infinity && distances[source] + weight < distances[destination]) {
                distances[destination] = distances[source] + weight;
            }
        }
    }

    // No negative cycle check is needed for longest path in a DAG.  If there were a negative cycle,
    // it would imply an infinitely long path, which doesn't make sense in project management.

    const result = {};
    for (const task in distances) {
      result[task] = -distances[task]; // Convert back to positive durations
    }
    return result;
}

// 4.  Distance Vector Routing Protocol
function distanceVectorRouting(nodes, edges, sourceNode) {
  const distances = {};
  nodes.forEach(node => distances[node] = Infinity);
  distances[sourceNode] = 0;
  const predecessors = {};

   for (let i = 0; i < nodes.length - 1; i++) {
        let updated = false;
        for (const { source, destination, weight } of edges) {
            if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
                distances[destination] = distances[source] + weight;
                predecessors[destination] = source; // Keep track of the path
                updated = true;
            }
        }
        if (!updated) break; // Optimization: Stop if no updates occur
    }
    //check negative cycle
     for (const { source, destination, weight } of edges) {
        if (distances[source] !== Infinity && distances[source] + weight < distances[destination]) {
            return "Negative cycle detected!";
        }
    }

  return { distances, predecessors };
}

// 5. Finding Minimum Cost in a Transportation Network
function transportationCostBellmanFord(locations, routes, startLocation) {
  const distances = {};
  locations.forEach(location => distances[location] = Infinity);
  distances[startLocation] = 0;

  for (let i = 0; i < locations.length - 1; i++) {
    for (const { source, destination, cost } of routes) {
      if (distances[source] !== Infinity && distances[source] + cost < distances[destination]) {
        distances[destination] = distances[source] + cost;
      }
    }
  }

  // Check for negative cycles (which would indicate a problem in the cost model)
  for (const { source, destination, cost } of routes) {
    if (distances[source] !== Infinity && distances[source] + cost < distances[destination]) {
      return "Negative cycle detected!";
    }
  }

  return distances;
}



// Example Usage (Inside the Canvas)
function runBellmanFordExamples() {
  // 1. Network Routing Example
  const networkNodes = ['A', 'B', 'C', 'D', 'E'];
  const networkEdges = [
    createWeightedEdge('A', 'B', -1),
    createWeightedEdge('A', 'C', 4),
    createWeightedEdge('B', 'C', 3),
    createWeightedEdge('B', 'D', 2),
    createWeightedEdge('B', 'E', 2),
    createWeightedEdge('D', 'B', 1),
    createWeightedEdge('D', 'C', 5),
    createWeightedEdge('E', 'D', -3),
  ];
  const networkSource = 'A';
  console.log("1. Network Routing:");
  console.log(networkRoutingBellmanFord(networkNodes, networkEdges, networkSource));
  // Expected output: { A: 0, B: -1, C: 2, D: -2, E: 1 }

  // 2. Currency Exchange Example
  const currencies = ['USD', 'EUR', 'GBP'];
  const exchangeRates = {
    'USD': { 'EUR': 0.85, 'GBP': 0.75 },
    'EUR': { 'USD': 1.18, 'GBP': 0.88 },
    'GBP': { 'USD': 1.33, 'EUR': 1.14 },
  };
  const sourceCurrency = 'USD';
  console.log("\n2. Currency Exchange:");
  console.log(currencyExchangeBellmanFord(currencies, exchangeRates, sourceCurrency));
  // Expected output: Object with exchange rates, or "Arbitrage opportunity detected!"

  // 3. Project Management Example
    const projectTasks = ['Start', 'A', 'B', 'C', 'End'];
    const projectDependencies = [
        { source: 'Start', destination: 'A', duration: 2 },
        { source: 'Start', destination: 'B', duration: 4 },
        { source: 'A', destination: 'C', duration: 3 },
        { source: 'B', destination: 'C', duration: 1 },
        { source: 'C', destination: 'End', duration: 2 },
    ];
    const projectStartTask = 'Start';
    console.log("\n3. Project Management:");
    console.log(projectManagementBellmanFord(projectTasks, projectDependencies, projectStartTask));
    // Expected output: { Start: 0, A: 2, B: 4, C: 5, End: 7 }

  // 4. Distance Vector Routing Protocol
  const routingNodes = ['A', 'B', 'C', 'D'];
    const routingEdges = [
        createWeightedEdge('A', 'B', 2),
        createWeightedEdge('A', 'C', 4),
        createWeightedEdge('B', 'C', 1),
        createWeightedEdge('B', 'D', 3),
        createWeightedEdge('C', 'D', 1),
    ];
    const routingSource = 'A';
    console.log("\n4. Distance Vector Routing:");
    console.log(distanceVectorRouting(routingNodes, routingEdges, routingSource));
    // Expected output: { distances: { A: 0, B: 2, C: 3, D: 4 }, predecessors: { B: 'A', C: 'B', D: 'C' } }

  // 5. Transportation Network Example
  const transportLocations = ['City1', 'City2', 'City3', 'City4'];
  const transportRoutes = [
    createWeightedEdge('City1', 'City2', 10),
    createWeightedEdge('City1', 'City3', 30),
    createWeightedEdge('City2', 'City3', 20),
    createWeightedEdge('City2', 'City4', 15),
    createWeightedEdge('City3', 'City4', 5),
  ];
  const transportStart = 'City1';
  console.log("\n5. Transportation Network:");
  console.log(transportationCostBellmanFord(transportLocations, transportRoutes, transportStart));
  // Expected output: { City1: 0, City2: 10, City3: 30, City4: 35 }
}

runBellmanFordExamples();

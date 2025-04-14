// Kruskal's Algorithm Implementation in JavaScript - 5 Approaches

// Helper function to find the parent of a node (used for cycle detection)
function find(parent, i) {
    if (parent[i] === i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]); // Path compression for optimization
}

// Helper function to unite two sets (used for cycle detection)
function union(parent, rank, x, y) {
    const xroot = find(parent, x);
    const yroot = find(parent, y);

    if (xroot === yroot) {
        return; // They are already in the same set
    }

    // Attach smaller rank tree under root of high rank tree
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// 1. Kruskal's Algorithm - Basic Implementation
function kruskalBasic(edges) {
    const sortedEdges = edges.sort((a, b) => a.weight - b.weight); // Sort edges by weight
    const parent = [];
    const rank = [];
    const result = [];
    const numVertices = getNumVertices(edges);

    // Initialize parent and rank arrays
    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    let edgeCount = 0;
    let i = 0;
    while (edgeCount < numVertices - 1 && i < sortedEdges.length) {
        const edge = sortedEdges[i++];
        const x = find(parent, edge.source);
        const y = find(parent, edge.destination);

        if (x !== y) {
            result.push(edge);
            union(parent, rank, x, y);
            edgeCount++;
        }
    }
    return result;
}

// 2. Kruskal's Algorithm - Optimized with Path Compression and Union by Rank
function kruskalOptimized(edges) {
    const sortedEdges = [...edges].sort((a, b) => a.weight - b.weight);
    const parent = [];
    const rank = [];
     const result = [];
    const numVertices = getNumVertices(edges);

    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    let edgeCount = 0;
    let i = 0;
    while (edgeCount < numVertices - 1 && i < sortedEdges.length) {
        const edge = sortedEdges[i++];
        const x = find(parent, edge.source);
        const y = find(parent, edge.destination);

        if (x !== y) {
            result.push(edge);
            union(parent, rank, x, y);
            edgeCount++;
        }
    }
    return result;
}

// 3. Kruskal's Algorithm -  Real-World Application:  Network Cable Laying
function kruskalNetworkCabling(connections) {
    const sortedConnections = [...connections].sort((a, b) => a.cost - b.cost);
    const parent = [];
    const rank = [];
    const result = [];
    const numVertices = getNumVertices(connections);

     for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    let connectionCount = 0;
    let i = 0;
    while (connectionCount < numVertices - 1 && i < sortedConnections.length) {
        const connection = sortedConnections[i++];
        const x = find(parent, connection.source);
        const y = find(parent, connection.destination);

        if (x !== y) {
            result.push(connection);
            union(parent, rank, x, y);
            connectionCount++;
        }
    }
    return result;
}

// 4. Kruskal's Algorithm - Real-World Application:  Minimum Cost Road Network
function kruskalRoadNetwork(roads) {
    const sortedRoads = [...roads].sort((a, b) => a.cost - b.cost);
    const parent = [];
    const rank = [];
    const result = [];
    const numVertices = getNumVertices(roads);

    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    let roadCount = 0;
    let i = 0;
    while (roadCount < numVertices - 1 && i < sortedRoads.length) {
        const road = sortedRoads[i++];
        const x = find(parent, road.source);
        const y = find(parent, road.destination);

        if (x !== y) {
            result.push(road);
            union(parent, rank, x, y);
            roadCount++;
        }
    }
    return result;
}

// 5. Kruskal's Algorithm - Real-World Application:  Power Grid Connection
function kruskalPowerGrid(powerLines) {
    const sortedPowerLines = [...powerLines].sort((a, b) => a.cost - b.cost);
    const parent = [];
    const rank = [];
    const result = [];
    const numVertices = getNumVertices(powerLines);

    for (let i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    let lineCount = 0;
    let i = 0;
    while (lineCount < numVertices - 1 && i < sortedPowerLines.length) {
        const line = sortedPowerLines[i++];
        const x = find(parent, line.source);
        const y = find(parent, line.destination);

        if (x !== y) {
            result.push(line);
            union(parent, rank, x, y);
            lineCount++;
        }
    }
    return result;
}

// Helper function to get the number of vertices from the edges
function getNumVertices(edges) {
    const vertices = new Set();
    for (const edge of edges) {
        vertices.add(edge.source);
        vertices.add(edge.destination);
    }
    return vertices.size;
}

// Example Usage (replace with your graph data)
const graphEdges = [
    { source: 0, destination: 1, weight: 4 },
    { source: 0, destination: 2, weight: 8 },
    { source: 1, destination: 2, weight: 11 },
    { source: 1, destination: 3, weight: 9 },
    { source: 2, destination: 3, weight: 7 },
    { source: 2, destination: 4, weight: 2 },
    { source: 3, destination: 4, weight: 6 },
];

const networkConnections = [
    { source: 'A', destination: 'B', cost: 5 },
    { source: 'A', destination: 'C', cost: 6 },
    { source: 'B', destination: 'C', cost: 1 },
    { source: 'B', destination: 'D', cost: 3 },
    { source: 'C', destination: 'D', cost: 4 },
    { source: 'C', destination: 'E', cost: 2 },
    { source: 'D', destination: 'E', cost: 7 },
];

const roadNetwork = [
    { source: 'City1', destination: 'City2', cost: 10 },
    { source: 'City1', destination: 'City3', cost: 15 },
    { source: 'City2', destination: 'City3', cost: 5 },
    { source: 'City2', destination: 'City4', cost: 20 },
    { source: 'City3', destination: 'City4', cost: 12 },
];

const powerGridLines = [
    { source: 'Plant1', destination: 'Sub1', cost: 20 },
    { source: 'Plant1', destination: 'Sub2', cost: 30 },
    { source: 'Sub1', destination: 'Sub2', cost: 10 },
    { source: 'Sub1', destination: 'City1', cost: 15 },
    { source: 'Sub2', destination: 'City2', cost: 25 },
    { source: 'City1', destination: 'City2', cost: 5 },
];

// Function to display output
function displayOutput(algorithmName, result) {
    console.log(`\n${algorithmName}:`);
    if (result && result.length > 0) {
        let totalCost = 0;
        result.forEach(edge => {
            console.log(`Source: ${edge.source}, Destination: ${edge.destination}, Weight/Cost: ${'weight' in edge ? edge.weight : edge.cost}`);
            totalCost += ('weight' in edge ? edge.weight : edge.cost);
        });
        console.log(`Total Cost: ${totalCost}`);
    } else {
        console.log("No MST found (possibly disconnected graph).");
    }
}
// Run and display the results
const basicResult = kruskalBasic(graphEdges);
displayOutput("Kruskal's Basic Implementation", basicResult);

const optimizedResult = kruskalOptimized(graphEdges);
displayOutput("Kruskal's Optimized Implementation", optimizedResult);

const networkCablingResult = kruskalNetworkCabling(networkConnections);
displayOutput("Kruskal's for Network Cabling", networkCablingResult);

const roadNetworkResult = kruskalRoadNetwork(roadNetwork);
displayOutput("Kruskal's for Road Network", roadNetworkResult);

const powerGridResult = kruskalPowerGrid(powerGridLines);
displayOutput("Kruskal's for Power Grid", powerGridResult);

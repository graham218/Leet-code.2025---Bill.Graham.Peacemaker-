/*
 * Implementation of the Floyd-Warshall Algorithm with 5 different approaches showcasing real-world project implementations
 */

// Helper function to create a deep copy of a 2D array
function deepCopy(arr) {
  return arr.map(row => [...row]);
}

// Helper function to print the distance matrix
function printMatrix(matrix, title) {
  console.log(`\n${title}:`);
  for (let i = 0; i < matrix.length; i++) {
    let rowString = matrix[i].map(val => val === Infinity ? "∞" : val).join("\t");
    console.log(rowString);
  }
}

/**
 * Floyd-Warshall Algorithm Implementation
 *
 * The Floyd-Warshall algorithm is an all-pairs shortest path algorithm. It finds the shortest distance between every pair of vertices in a weighted graph.
 *
 * Parameters:
 * graph (number[][]): A 2D array representing the graph's adjacency matrix.
 * - graph[i][j] is the weight of the edge from vertex i to vertex j.
 * - If there is no edge from i to j, graph[i][j] is Infinity.
 * - The diagonal elements (graph[i][i]) should be 0.
 *
 * Returns:
 * number[][]: A 2D array representing the shortest distances between all pairs of vertices.
 * - The returned matrix dist[i][j] is the shortest distance from vertex i to vertex j.
 */
function floydWarshall(graph) {
  const V = graph.length;
  // Initialize the distance matrix with the input graph
  let dist = deepCopy(graph);

  // Iterate through all possible intermediate vertices k
  for (let k = 0; k < V; k++) {
    // Iterate through all possible source vertices i
    for (let i = 0; i < V; i++) {
      // Iterate through all possible destination vertices j
      for (let j = 0; j < V; j++) {
        // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
        if (dist[i][k] !== Infinity && dist[k][j] !== Infinity) { // Check for Infinity to avoid issues with unreachable nodes
          dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

// Utility function to create a sample graph (adjacency matrix)
function createSampleGraph() {
  // Adjacency matrix representing the graph
  const graph = [
    [0, 5, Infinity, 10],
    [Infinity, 0, 3, Infinity],
    [Infinity, Infinity, 0, 1],
    [Infinity, Infinity, Infinity, 0]
  ];
  return graph;
}

/*
 * 1. Network Routing (Cisco Routers)
 *
 * Problem:
 * In a network, routers need to determine the shortest path to forward data packets to their destination.
 *
 * Implementation:
 * Use the Floyd-Warshall algorithm to compute the shortest paths between all pairs of routers in the network.
 * The adjacency matrix represents the network topology, where the weights represent the cost (e.g., latency, bandwidth) of sending data between routers.
 */
function networkRouting() {
  console.log("\n1. Network Routing (Cisco Routers):");
  const networkGraph = [
    [0, 7, Infinity, 8],
    [7, 0, 2, Infinity],
    [Infinity, 2, 0, 6],
    [8, Infinity, 6, 0]
  ];
  printMatrix(networkGraph, "Network Topology (Adjacency Matrix)");
  const shortestPaths = floydWarshall(networkGraph);
  printMatrix(shortestPaths, "Shortest Paths between Routers");
}

/*
 * 2. City Transportation Planning
 *
 * Problem:
 * A city planner wants to find the shortest routes between any two locations in the city to optimize transportation (e.g., minimize travel time, distance).
 *
 * Implementation:
 * Represent the city as a graph where nodes are locations and edges are roads with weights representing travel time or distance.
 * Apply the Floyd-Warshall algorithm to find the shortest paths between all pairs of locations.
 */
function cityTransportationPlanning() {
  console.log("\n2. City Transportation Planning:");
  const cityGraph = [
    [0, 10, Infinity, 30, 100],
    [Infinity, 0, 5, Infinity, Infinity],
    [Infinity, Infinity, 0, 50, Infinity],
    [Infinity, Infinity, Infinity, 0, 10],
    [Infinity, Infinity, Infinity, Infinity, 0]
  ];

  printMatrix(cityGraph, "City Road Network (Adjacency Matrix)");
  const shortestRoutes = floydWarshall(cityGraph);
  printMatrix(shortestRoutes, "Shortest Routes Between Locations");
}

/*
 * 3. Airline Route Planning (Amadeus)
 *
 * Problem:
 * An airline wants to determine the shortest flight paths between all pairs of airports to minimize fuel consumption and travel time.
 *
 * Implementation:
 * Model the airline network as a graph where airports are nodes and flights are edges with weights representing distance or travel time.
 * Use the Floyd-Warshall algorithm to find the shortest paths between all pairs of airports.
 */
function airlineRoutePlanning() {
  console.log("\n3. Airline Route Planning (Amadeus):");
  const airlineGraph = [
    [0, 500, Infinity, 200],
    [500, 0, 300, Infinity],
    [Infinity, 300, 0, 100],
    [200, Infinity, 100, 0]
  ];
  printMatrix(airlineGraph, "Airline Route Network (Adjacency Matrix)");
  const shortestFlightPaths = floydWarshall(airlineGraph);
  printMatrix(shortestFlightPaths, "Shortest Flight Paths Between Airports");
}

/*
 * 4. Robotics Path Planning
 *
 * Problem:
 * A robot needs to navigate through an environment with obstacles to reach its destination.  The robot needs to find the shortest path to avoid collisions and minimize travel time.
 *
 * Implementation:
 * Represent the environment as a grid graph where nodes are reachable locations and edges represent possible movements with weights representing the cost of movement.  Use Floyd-Warshall to find the shortest path between any two points in the environment.
 */
function roboticsPathPlanning() {
  console.log("\n4. Robotics Path Planning:");
  const roboticsGraph = [
      [0, 2, Infinity, 5, Infinity],
      [2, 0, 3, Infinity, 1],
      [Infinity, 3, 0, 1, Infinity],
      [5, Infinity, 1, 0, 4],
      [Infinity, 1, Infinity, 4, 0]
  ];

  printMatrix(roboticsGraph, "Robot Navigation Grid (Adjacency Matrix)");
  const shortestPaths = floydWarshall(roboticsGraph);
  printMatrix(shortestPaths, "Shortest Paths for Robot Navigation");
}

/*
 * 5. Social Network Analysis (LinkedIn Connections)
 *
 * Problem:
 * In a social network, you want to find the shortest path (e.g., minimum number of connections) between any two users.  This can be used to suggest connections or measure the degree of separation.
 *
 * Implementation:
 * Represent the social network as a graph where users are nodes and connections are edges.  Use the Floyd-Warshall algorithm to find the shortest paths (minimum number of connections) between all pairs of users.
 */
function socialNetworkAnalysis() {
  console.log("\n5. Social Network Analysis (LinkedIn Connections):");
  const socialNetworkGraph = [
    [0, 1, Infinity, 1, Infinity],
    [1, 0, 1, Infinity, Infinity],
    [Infinity, 1, 0, Infinity, 1],
    [1, Infinity, Infinity, 0, 1],
    [Infinity, Infinity, 1, 1, 0]
  ];

  printMatrix(socialNetworkGraph, "Social Network Connections (Adjacency Matrix)");
  const shortestConnections = floydWarshall(socialNetworkGraph);
  printMatrix(shortestConnections, "Shortest Connections Between Users");
}

// Main function to run the examples
function main() {
  const sampleGraph = createSampleGraph();
  console.log("Original Graph (Adjacency Matrix):");
  printMatrix(sampleGraph, "Original Graph");

  const shortestDistances = floydWarshall(sampleGraph);
  printMatrix(shortestDistances, "Shortest Distances Between All Pairs of Vertices");

  networkRouting();
  cityTransportationPlanning();
  airlineRoutePlanning();
  roboticsPathPlanning();
  socialNetworkAnalysis();
}

// Run the main function
main();

// Union-Find (Disjoint Set Union - DSU) Implementation in JavaScript

// 1. Basic Union-Find (Path Compression)
class BasicUnionFind {
  constructor(n) {
    this.parent = new Array(n);
    for (let i = 0; i < n; i++) {
      this.parent[i] = i;
    }
  }

  find(x) {
    if (this.parent[x] !== x) {
      this.parent[x] = this.find(this.parent[x]); // Path compression
    }
    return this.parent[x];
  }

  union(x, y) {
    const rootX = this.find(x);
    const rootY = this.find(y);
    if (rootX !== rootY) {
      this.parent[rootX] = rootY;
    }
  }

  isConnected(x, y) {
    return this.find(x) === this.find(y);
  }
}

// 2. Union-Find with Union by Rank
class UnionFindWithRank {
  constructor(n) {
    this.parent = new Array(n);
    this.rank = new Array(n);
    for (let i = 0; i < n; i++) {
      this.parent[i] = i;
      this.rank[i] = 0;
    }
  }

  find(x) {
    if (this.parent[x] !== x) {
      this.parent[x] = this.find(this.parent[x]); // Path compression
    }
    return this.parent[x];
  }

  union(x, y) {
    const rootX = this.find(x);
    const rootY = this.find(y);
    if (rootX !== rootY) {
      if (this.rank[rootX] < this.rank[rootY]) {
        this.parent[rootX] = rootY;
      } else if (this.rank[rootX] > this.rank[rootY]) {
        this.parent[rootY] = rootX;
      } else {
        this.parent[rootY] = rootX;
        this.rank[rootX]++;
      }
    }
  }

  isConnected(x, y) {
      return this.find(x) === this.find(y);
  }
}

// 3. Kruskal's Algorithm for Minimum Spanning Tree (MST)
//    - A classic application of Union-Find
function kruskalMST(edges, numVertices) {
  edges.sort((a, b) => a.weight - b.weight); // Sort edges by weight
  const uf = new UnionFindWithRank(numVertices);
  const mstEdges = [];
  let mstWeight = 0;

  for (const edge of edges) {
    const { u, v, weight } = edge;
    if (!uf.isConnected(u, v)) {
      uf.union(u, v);
      mstEdges.push(edge);
      mstWeight += weight;
    }
  }
  return { edges: mstEdges, weight: mstWeight };
}

// 4. Network Connectivity
//    - Checking if two servers are in the same network
class NetworkConnectivity {
  constructor(n) {
    this.uf = new UnionFindWithRank(n);
    this.numComponents = n;
  }

  connect(server1, server2) {
    if (!this.uf.isConnected(server1, server2)) {
      this.uf.union(server1, server2);
      this.numComponents--;
    }
  }

  areConnected(server1, server2) {
    return this.uf.isConnected(server1, server2);
  }

  getNumberOfConnectedComponents() {
    return this.numComponents;
  }
}

// 5.  Finding Cycle in a Graph
function hasCycle(edges, numVertices) {
    const uf = new UnionFindWithRank(numVertices);

    for (const edge of edges) {
        const { u, v } = edge;
        if (uf.isConnected(u, v)) {
            return true; // Cycle detected
        }
        uf.union(u, v);
    }
    return false;
}

// Example Usage and Output
(() => {
  // 1. Basic Union-Find
  console.log("1. Basic Union-Find:");
  const basicUF = new BasicUnionFind(5);
  basicUF.union(0, 1);
  basicUF.union(2, 3);
  console.log("isConnected(0, 1):", basicUF.isConnected(0, 1)); // true
  console.log("isConnected(0, 2):", basicUF.isConnected(0, 2)); // false

  // 2. Union-Find with Union by Rank
  console.log("\n2. Union-Find with Union by Rank:");
  const rankUF = new UnionFindWithRank(5);
  rankUF.union(0, 1);
  rankUF.union(2, 3);
  console.log("isConnected(0, 1):", rankUF.isConnected(0, 1)); // true
  console.log("isConnected(0, 2):", rankUF.isConnected(0, 2)); // false

  // 3. Kruskal's Algorithm for MST
  console.log("\n3. Kruskal's Algorithm for MST:");
  const graphEdges = [
    { u: 0, v: 1, weight: 10 },
    { u: 0, v: 2, weight: 6 },
    { u: 0, v: 3, weight: 5 },
    { u: 1, v: 3, weight: 15 },
    { u: 2, v: 3, weight: 4 },
  ];
  const numVertices = 4;
  const mstResult = kruskalMST(graphEdges, numVertices);
  console.log("MST Edges:", mstResult.edges);
  console.log("MST Weight:", mstResult.weight);

  // 4. Network Connectivity
  console.log("\n4. Network Connectivity:");
  const network = new NetworkConnectivity(6);
  network.connect(0, 1);
  network.connect(2, 3);
  network.connect(4, 5);
  console.log("Are 0 and 1 connected:", network.areConnected(0, 1)); // true
  console.log("Are 0 and 2 connected:", network.areConnected(0, 2)); // false
  console.log("Number of connected components:", network.getNumberOfConnectedComponents()); // 3
  network.connect(1, 2);
  console.log("Number of connected components after connecting 1 and 2:", network.getNumberOfConnectedComponents()); // 2

  // 5. Finding Cycle in a Graph
  console.log("\n5. Finding Cycle in a Graph:");
    const graphWithCycleEdges = [
        { u: 0, v: 1 },
        { u: 1, v: 2 },
        { u: 2, v: 0 }, // Cycle: 0 -> 1 -> 2 -> 0
    ];
    const graphWithoutCycleEdges = [
        { u: 0, v: 1 },
        { u: 1, v: 2 },
        { u: 2, v: 3 },
    ];
    console.log("Graph with cycle:", hasCycle(graphWithCycleEdges, 3)); // true
    console.log("Graph without cycle:", hasCycle(graphWithoutCycleEdges, 4)); // false

})();

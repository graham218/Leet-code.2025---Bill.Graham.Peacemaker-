/**
 * Union-Find (Disjoint Set Union - DSU) Implementation in JavaScript
 * Demonstrates 5 different approaches:
 * 1. Quick Find
 * 2. Quick Union
 * 3. Weighted Quick Union
 * 4. Path Compression (with Weighted Quick Union)
 * 5. Rank with Path Compression
 */

// Helper function to create an array of size n with initial values
function createArray(n, initialValue) {
  const arr = new Array(n);
  for (let i = 0; i < n; i++) {
    arr[i] = initialValue;
  }
  return arr;
}

// ----------------------------------------------------------------------
// 1. Quick Find
// ----------------------------------------------------------------------
class QuickFind {
  constructor(n) {
    this.id = createArray(n, (i) => i); // Initialize each element as its own root
    this.count = n; // Number of connected components
  }

  find(p) {
    return this.id[p]; // O(1)
  }

  union(p, q) {
    const pId = this.find(p);
    const qId = this.find(q);

    if (pId === qId) return; // Already connected

    for (let i = 0; i < this.id.length; i++) {
      if (this.id[i] === pId) {
        this.id[i] = qId; // Change all elements with pId to qId
      }
    }
    this.count--;
  }

  isConnected(p, q) {
    return this.find(p) === this.find(q);
  }

  countSets() {
    return this.count;
  }
}

// ----------------------------------------------------------------------
// 2. Quick Union
// ----------------------------------------------------------------------
class QuickUnion {
  constructor(n) {
    this.parent = createArray(n, (i) => i); // Initialize each element as its own parent
    this.count = n;
  }

  find(p) {
    // Find the root of p
    while (p !== this.parent[p]) {
      p = this.parent[p];
    }
    return p;
  }

  union(p, q) {
    const pRoot = this.find(p);
    const qRoot = this.find(q);

    if (pRoot === qRoot) return; // Already connected

    this.parent[pRoot] = qRoot; // Make the root of p point to the root of q
    this.count--;
  }

  isConnected(p, q) {
    return this.find(p) === this.find(q);
  }

  countSets() {
    return this.count;
  }
}

// ----------------------------------------------------------------------
// 3. Weighted Quick Union
// ----------------------------------------------------------------------
class WeightedQuickUnion {
  constructor(n) {
    this.parent = createArray(n, (i) => i); // Initialize each element as its own parent
    this.size = createArray(n, 1); // Size of each tree, initially 1
    this.count = n;
  }

  find(p) {
    // Find the root of p
    while (p !== this.parent[p]) {
      p = this.parent[p];
    }
    return p;
  }

  union(p, q) {
    const pRoot = this.find(p);
    const qRoot = this.find(q);

    if (pRoot === qRoot) return; // Already connected

    // Make the smaller tree point to the larger tree
    if (this.size[pRoot] < this.size[qRoot]) {
      this.parent[pRoot] = qRoot;
      this.size[qRoot] += this.size[pRoot];
    } else {
      this.parent[qRoot] = pRoot;
      this.size[pRoot] += this.size[qRoot];
    }
    this.count--;
  }

  isConnected(p, q) {
    return this.find(p) === this.find(q);
  }
  countSets() {
    return this.count;
  }
}

// ----------------------------------------------------------------------
// 4. Path Compression (with Weighted Quick Union)
// ----------------------------------------------------------------------
class PathCompression {
  constructor(n) {
    this.parent = createArray(n, (i) => i);
    this.size = createArray(n, 1);
    this.count = n;
  }

  find(p) {
    // Find the root of p with path compression
    while (p !== this.parent[p]) {
      this.parent[p] = this.parent[this.parent[p]]; // Path compression: make p point to its grandparent
      p = this.parent[p];
    }
    return p;
  }

  union(p, q) {
    const pRoot = this.find(p);
    const qRoot = this.find(q);

    if (pRoot === qRoot) return;

    if (this.size[pRoot] < this.size[qRoot]) {
      this.parent[pRoot] = qRoot;
      this.size[qRoot] += this.size[pRoot];
    } else {
      this.parent[qRoot] = pRoot;
      this.size[pRoot] += this.size[qRoot];
    }
    this.count--;
  }

  isConnected(p, q) {
    return this.find(p) === this.find(q);
  }
  countSets() {
    return this.count;
  }
}

// ----------------------------------------------------------------------
// 5. Rank with Path Compression
// ----------------------------------------------------------------------
class RankPathCompression {
  constructor(n) {
    this.parent = createArray(n, (i) => i);
    this.rank = createArray(n, 0); // Use rank instead of size
    this.count = n;
  }

  find(p) {
    while (p !== this.parent[p]) {
      this.parent[p] = this.parent[this.parent[p]];
      p = this.parent[p];
    }
    return p;
  }

  union(p, q) {
    const pRoot = this.find(p);
    const qRoot = this.find(q);

    if (pRoot === qRoot) return;

    if (this.rank[pRoot] < this.rank[qRoot]) {
      this.parent[pRoot] = qRoot;
    } else if (this.rank[pRoot] > this.rank[qRoot]) {
      this.parent[qRoot] = pRoot;
    } else {
      this.parent[qRoot] = pRoot; // Make qRoot child of pRoot
      this.rank[pRoot]++; // Increase rank of pRoot
    }
    this.count--;
  }

  isConnected(p, q) {
    return this.find(p) === this.find(q);
  }

  countSets() {
    return this.count;
  }
}

// ----------------------------------------------------------------------
// Example Usage and Testing
// ----------------------------------------------------------------------

function runTests() {
  const n = 10; // Number of elements

  console.log("--------------------------------------------------");
  console.log("1. Quick Find");
  console.log("--------------------------------------------------");
  const qf = new QuickFind(n);
  console.log("Initial:", qf.id);
  qf.union(0, 1);
  qf.union(2, 3);
  qf.union(4, 5);
  qf.union(6, 7);
  qf.union(8, 9);
  console.log("After unions (0,1), (2,3), (4,5), (6,7), (8,9):", qf.id);
  console.log("isConnected(0, 1):", qf.isConnected(0, 1)); // true
  console.log("isConnected(0, 2):", qf.isConnected(0, 2)); // false
  console.log("Number of sets:", qf.countSets()); //5

  console.log("\n--------------------------------------------------");
  console.log("2. Quick Union");
  console.log("--------------------------------------------------");
  const qu = new QuickUnion(n);
  console.log("Initial parent:", qu.parent);
  qu.union(0, 1);
  qu.union(2, 3);
  qu.union(4, 5);
  qu.union(6, 7);
  qu.union(8, 9);
  console.log("After unions (0,1), (2,3), (4,5), (6,7), (8,9):", qu.parent);
  console.log("isConnected(0, 1):", qu.isConnected(0, 1));
  console.log("isConnected(0, 2):", qu.isConnected(0, 2));
  console.log("Number of sets:", qu.countSets());

  console.log("\n--------------------------------------------------");
  console.log("3. Weighted Quick Union");
  console.log("--------------------------------------------------");
  const wqu = new WeightedQuickUnion(n);
  console.log("Initial parent:", wqu.parent);
  console.log("Initial sizes:", wqu.size);
  wqu.union(0, 1);
  wqu.union(2, 3);
  wqu.union(4, 5);
  wqu.union(6, 7);
  wqu.union(8, 9);
  wqu.union(0, 2); // Connect 0 and 2
  console.log("After unions (0,1), (2,3), (4,5), (6,7), (8,9), (0,2):", wqu.parent);
  console.log("Sizes:", wqu.size);
  console.log("isConnected(0, 2):", wqu.isConnected(0, 2));
  console.log("Number of sets:", wqu.countSets()); // 4

  console.log("\n--------------------------------------------------");
  console.log("4. Path Compression");
  console.log("--------------------------------------------------");
  const pc = new PathCompression(n);
  pc.union(0, 1);
  pc.union(2, 3);
  pc.union(4, 5);
  pc.union(6, 7);
  pc.union(8, 9);
  pc.union(0, 2);
  console.log("Initial parent:", pc.parent);
  pc.find(1); // Perform find to trigger path compression.
  console.log("After unions and find(1):", pc.parent);
  console.log("isConnected(0, 2):", pc.isConnected(0, 2));
  console.log("Number of sets:", pc.countSets());

  console.log("\n--------------------------------------------------");
  console.log("5. Rank with Path Compression");
  console.log("--------------------------------------------------");
  const rpc = new RankPathCompression(n);
  rpc.union(0, 1);
  rpc.union(2, 3);
  rpc.union(4, 5);
  rpc.union(6, 7);
  rpc.union(8, 9);
  rpc.union(0, 2);
  console.log("Initial parent:", rpc.parent);
  console.log("Initial ranks:", rpc.rank);
  rpc.find(1);
  console.log("After unions and find(1):", rpc.parent);
  console.log("Ranks:", rpc.rank);
  console.log("isConnected(0, 2):", rpc.isConnected(0, 2));
  console.log("Number of sets:", rpc.countSets());
}

runTests();

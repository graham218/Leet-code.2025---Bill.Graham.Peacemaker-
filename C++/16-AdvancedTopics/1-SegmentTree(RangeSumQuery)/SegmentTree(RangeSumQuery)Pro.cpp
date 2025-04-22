// Segment Tree Implementation for Range Sum Query

/**
 * Approach 1: Basic Segment Tree (Bottom-Up)
 *
 * This is the most straightforward implementation.  It builds the tree
 * from the bottom up, and uses an array to store the segment tree.
 *
 * Real-world application:  Used in simple data analysis tools where
 * quick range aggregations (sum, min, max) are needed on relatively
 * static datasets.  For example, calculating daily website traffic
 * over specific date ranges.
 */
class SegmentTreeBasic {
  constructor(arr) {
    this.arr = arr;
    this.n = arr.length;
    this.tree = new Array(2 * this.n); // Size is 2n to accommodate all nodes

    this.buildTree();
  }

  buildTree() {
    // Copy the original array to the leaves of the tree
    for (let i = 0; i < this.n; i++) {
      this.tree[this.n + i] = this.arr[i];
    }
    // Build the tree from the bottom up
    for (let i = this.n - 1; i > 0; i--) {
      this.tree[i] = this.tree[2 * i] + this.tree[2 * i + 1];
    }
  }

  query(l, r) {
    // Adjust indices to be 0-based
    l += this.n;
    r += this.n;
    let sum = 0;

    while (l <= r) {
      if (l % 2 === 1) { // If l is odd, include it
        sum += this.tree[l];
        l++;
      }
      if (r % 2 === 0) { // If r is even, include it
        sum += this.tree[r];
        r--;
      }
      l = Math.floor(l / 2);
      r = Math.floor(r / 2);
    }
    return sum;
  }

  update(i, value) {
    // Update the leaf node
    i += this.n;
    this.tree[i] = value;
    // Update the parent nodes
    while (i > 0) {
      i = Math.floor(i / 2);
      this.tree[i] = this.tree[2 * i] + this.tree[2 * i + 1];
    }
  }
}

/**
 * Approach 2: Segment Tree with Lazy Propagation
 *
 * This approach is crucial for range update queries.  Instead of updating
 * every node in the range, we store the update and apply it when needed
 * (when we query a node).
 *
 * Real-world application:  Used in applications with frequent range updates,
 * such as updating prices of products within a specific category in an
 * e-commerce platform, or updating sensor readings for a range of devices.
 */
class SegmentTreeLazy {
  constructor(arr) {
    this.arr = arr;
    this.n = arr.length;
    this.tree = new Array(4 * this.n); // Size is 4n for lazy propagation
    this.lazy = new Array(4 * this.n).fill(0); // Array to store lazy values
    this.buildTree(0, this.n - 1, 1);
  }

  buildTree(start, end, node) {
    if (start === end) {
      this.tree[node] = this.arr[start];
      return;
    }
    const mid = Math.floor((start + end) / 2);
    this.buildTree(start, mid, 2 * node);
    this.buildTree(mid + 1, end, 2 * node + 1);
    this.tree[node] = this.tree[2 * node] + this.tree[2 * node + 1];
  }

  query(l, r, start = 0, end = this.n - 1, node = 1) {
    this.propagate(start, end, node); // Propagate lazy values first

    if (start > r || end < l) {
      return 0; // Out of range
    }
    if (start >= l && end <= r) {
      return this.tree[node]; // Within range
    }
    const mid = Math.floor((start + end) / 2);
    const leftSum = this.query(l, r, start, mid, 2 * node);
    const rightSum = this.query(l, r, mid + 1, end, 2 * node + 1);
    return leftSum + rightSum;
  }

  update(l, r, value, start = 0, end = this.n - 1, node = 1) {
    this.propagate(start, end, node); // Propagate lazy values first

    if (start > r || end < l) {
      return; // Out of range
    }
    if (start >= l && end <= r) {
      // Within range: update the node and set lazy value for children
      this.tree[node] += (end - start + 1) * value;
      if (start !== end) {
        this.lazy[2 * node] += value;
        this.lazy[2 * node + 1] += value;
      }
      return;
    }
    const mid = Math.floor((start + end) / 2);
    this.update(l, r, value, start, mid, 2 * node);
    this.update(l, r, value, mid + 1, end, 2 * node + 1);
    this.tree[node] = this.tree[2 * node] + this.tree[2 * node + 1];
  }

  propagate(start, end, node) {
    if (this.lazy[node] !== 0) {
      // Apply the lazy value to the current node
      this.tree[node] += (end - start + 1) * this.lazy[node];
      if (start !== end) {
        // Pass the lazy value to the children
        this.lazy[2 * node] += this.lazy[node];
        this.lazy[2 * node + 1] += this.lazy[node];
      }
      this.lazy[node] = 0; // Clear the lazy value
    }
  }
}

/**
 * Approach 3: Segment Tree with Non-Recursive Query
 *
 * This approach uses an iterative (non-recursive) method for the query
 * operation.  This can sometimes be more efficient due to avoiding
 * function call overhead.
 *
 * Real-world application: High-performance systems where query speed is
 * critical, such as real-time analytics dashboards or high-frequency
 * trading platforms.
 */
class SegmentTreeNonRecursive {
  constructor(arr) {
    this.arr = arr;
    this.n = arr.length;
    this.tree = new Array(2 * this.n);
    this.buildTree();
  }

  buildTree() {
    for (let i = 0; i < this.n; i++) {
      this.tree[this.n + i] = this.arr[i];
    }
    for (let i = this.n - 1; i > 0; i--) {
      this.tree[i] = this.tree[2 * i] + this.tree[2 * i + 1];
    }
  }

  query(l, r) {
    l += this.n;
    r += this.n;
    let sum = 0;

    while (l <= r) {
      if (l % 2 === 1) {
        sum += this.tree[l++];
      }
      if (r % 2 === 0) {
        sum += this.tree[r--];
      }
      l = Math.floor(l / 2);
      r = Math.floor(r / 2);
    }
    return sum;
  }

  update(i, value) {
    i += this.n;
    this.tree[i] = value;
    while (i > 1) {
      i = Math.floor(i / 2);
      this.tree[i] = this.tree[2 * i] + this.tree[2 * i + 1];
    }
  }
}

/**
 * Approach 4: Segment Tree for Minimum Range Query (RMQ)
 *
 * This variation of the segment tree is specifically for finding the minimum
 * value within a given range, instead of the sum.
 *
 * Real-world application:  Used in optimization problems, such as finding
 * the minimum price of a product over a period, or identifying the
 * lowest point in a geographical region.
 */
class SegmentTreeRMQ {
  constructor(arr) {
    this.arr = arr;
    this.n = arr.length;
    this.tree = new Array(2 * this.n);
    // Initialize the tree with Infinity, so the minimum is correctly calculated.
    for (let i = 0; i < 2 * this.n; i++) {
      this.tree[i] = Infinity;
    }
    this.buildTree();
  }

  buildTree() {
    for (let i = 0; i < this.n; i++) {
      this.tree[this.n + i] = this.arr[i];
    }
    for (let i = this.n - 1; i > 0; i--) {
      this.tree[i] = Math.min(this.tree[2 * i], this.tree[2 * i + 1]);
    }
  }

  query(l, r) {
    l += this.n;
    r += this.n;
    let minVal = Infinity;

    while (l <= r) {
      if (l % 2 === 1) {
        minVal = Math.min(minVal, this.tree[l++]);
      }
      if (r % 2 === 0) {
        minVal = Math.min(minVal, this.tree[r--]);
      }
      l = Math.floor(l / 2);
      r = Math.floor(r / 2);
    }
    return minVal;
  }

  update(i, value) {
    i += this.n;
    this.tree[i] = value;
    while (i > 1) {
      i = Math.floor(i / 2);
      this.tree[i] = Math.min(this.tree[2 * i], this.tree[2 * i + 1]);
    }
  }
}

/**
 * Approach 5: Persistent Segment Tree
 *
 * A persistent segment tree allows you to query previous versions of the tree.
 * Each update creates a new tree, while keeping the old ones intact.  This is
 * useful for historical data analysis.  This example shows a basic persistent
 * structure for sum queries.  Each update returns the root of the *new* tree.
 *
 * Real-world application:  Version control systems,  database query optimization
 * (querying the database as it existed at a past point in time), and
 * in some types of game development (undo functionality).
 */
class PersistentSegmentTree {
  constructor(arr) {
    this.arr = arr;
    this.n = arr.length;
    this.root = this.buildTree(0, this.n - 1);
  }

  buildTree(start, end) {
    if (start === end) {
      const node = { sum: this.arr[start], left: null, right: null };
      return node;
    }
    const mid = Math.floor((start + end) / 2);
    const left = this.buildTree(start, mid);
    const right = this.buildTree(mid + 1, end);
    const node = { sum: left.sum + right.sum, left, right };
    return node;
  }

  query(node, l, r, start = 0, end = this.n - 1) {
    if (node === null) return 0;
    if (start > r || end < l) return 0;
    if (start >= l && end <= r) return node.sum;
    const mid = Math.floor((start + end) / 2);
    const leftSum = this.query(node.left, l, r, start, mid);
    const rightSum = this.query(node.right, l, r, mid + 1, end);
    return leftSum + rightSum;
  }

  update(node, i, value, start = 0, end = this.n - 1) {
    if (start > i || end < i) {
      return node; // Return the old node if i is out of range
    }
    if (start === end) {
      const newNode = { sum: value, left: null, right: null };
      return newNode;
    }
    const mid = Math.floor((start + end) / 2);
    const newLeft = this.update(node.left, i, value, start, mid);
    const newRight = this.update(node.right, i, value, mid + 1, end);
    const newNode = { sum: newLeft.sum + newRight.sum, left: newLeft, right: newRight };
    return newNode;
  }
}

// Example Usage and Testing
const array = [1, 3, 5, 7, 9, 11];

// Approach 1: Basic Segment Tree
const stBasic = new SegmentTreeBasic(array);
console.log("Approach 1: Basic Segment Tree");
console.log("Query (1, 3):", stBasic.query(1, 3)); // Should be 3 + 5 + 7 = 15
stBasic.update(2, 6); // Update arr[2] from 5 to 6
console.log("Query (1, 3) after update:", stBasic.query(1, 3)); // Should be 3 + 6 + 7 = 16
console.log("--------------------");

// Approach 2: Segment Tree with Lazy Propagation
const stLazy = new SegmentTreeLazy(array);
console.log("Approach 2: Segment Tree with Lazy Propagation");
console.log("Query (0, 2):", stLazy.query(0, 2)); // Should be 1 + 3 + 5 = 9
stLazy.update(0, 2, 2); // Add 2 to elements in range [0, 2]
console.log("Query (0, 2) after update:", stLazy.query(0, 2)); // Should be (1+2) + (3+2) + (5+2) = 15
console.log("--------------------");

// Approach 3: Segment Tree with Non-Recursive Query
const stNonRecursive = new SegmentTreeNonRecursive(array);
console.log("Approach 3: Segment Tree with Non-Recursive Query");
console.log("Query (2, 5):", stNonRecursive.query(2, 5)); // Should be 5 + 7 + 9 + 11 = 32
stNonRecursive.update(4, 10); // Update arr[4] from 9 to 10
console.log("Query (2, 5) after update:", stNonRecursive.query(2, 5)); // Should be 5 + 7 + 10 + 11 = 33
console.log("--------------------");

// Approach 4: Segment Tree for Minimum Range Query (RMQ)
const stRMQ = new SegmentTreeRMQ(array);
console.log("Approach 4: Segment Tree for Minimum Range Query (RMQ)");
console.log("Query (0, 4):", stRMQ.query(0, 4)); // Should be 1
stRMQ.update(3, 2); // Update arr[3] from 7 to 2
console.log("Query (0, 4) after update:", stRMQ.query(0, 4)); // Should be 1
console.log("--------------------");

// Approach 5: Persistent Segment Tree
const pst = new PersistentSegmentTree(array);
console.log("Approach 5: Persistent Segment Tree");
console.log("Query (0, 5) on original:", pst.query(pst.root, 0, 5)); // Should be 1 + 3 + 5 + 7 + 9 + 11 = 36
const newRoot1 = pst.update(pst.root, 2, 10); // Update arr[2] from 5 to 10
console.log("Query (0, 5) after first update:", pst.query(newRoot1, 0, 5)); // Should be 1 + 3 + 10 + 7 + 9 + 11 = 41
const newRoot2 = pst.update(newRoot1, 4, 15); // Update arr[4] from 9 to 15
console.log("Query (0, 5) after second update:", pst.query(newRoot2, 0, 5)); // Should be 1 + 3 + 10 + 7 + 15 + 11 = 47
console.log("Query (0, 5) on original (should not change):", pst.query(pst.root, 0, 5)); // Still 36
console.log("Query (0, 5) after first update (should not change):", pst.query(newRoot1, 0, 5)); // Should be 41
console.log("--------------------");

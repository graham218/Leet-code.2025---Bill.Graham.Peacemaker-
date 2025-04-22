// Segment Tree Implementation for Range Sum Query
// 5 Different Approaches

// 1. Recursive Approach (Build and Query)
class SegmentTreeRecursive {
  constructor(arr) {
    this.arr = arr;
    this.tree = new Array(4 * arr.length); // Max size of segment tree is 4*n
    this.build(0, 0, arr.length - 1);
  }

  // Build the segment tree
  build(node, start, end) {
    if (start === end) {
      this.tree[node] = this.arr[start];
      return;
    }
    const mid = Math.floor((start + end) / 2);
    this.build(2 * node + 1, start, mid);
    this.build(2 * node + 2, mid + 1, end);
    this.tree[node] = this.tree[2 * node + 1] + this.tree[2 * node + 2];
  }

  // Range Sum Query
  query(node, start, end, left, right) {
    if (right < start || end < left) {
      return 0;
    }
    if (left <= start && end <= right) {
      return this.tree[node];
    }
    const mid = Math.floor((start + end) / 2);
    const leftSum = this.query(2 * node + 1, start, mid, left, right);
    const rightSum = this.query(2 * node + 2, mid + 1, end, left, right);
    return leftSum + rightSum;
  }

    // Update a value in the array and update the segment tree
    update(node, start, end, index, val) {
        if (start === end) {
            this.arr[start] = val;
            this.tree[node] = val;
            return;
        }
        const mid = Math.floor((start + end) / 2);
        if (index <= mid) {
            this.update(2 * node + 1, start, mid, index, val);
        } else {
            this.update(2 * node + 2, mid + 1, end, index, val);
        }
        this.tree[node] = this.tree[2 * node + 1] + this.tree[2 * node + 2];
    }
}

// 2. Iterative Approach (Build and Query)
class SegmentTreeIterative {
  constructor(arr) {
    this.arr = arr;
    const n = arr.length;
    this.tree = new Array(2 * n);
    // Copy array to the end of the tree
    for (let i = 0; i < n; i++) {
      this.tree[n + i] = arr[i];
    }
    // Build the tree from the bottom up
    for (let i = n - 1; i > 0; i--) {
      this.tree[i] = this.tree[2 * i] + this.tree[2 * i + 1];
    }
  }

  // Range Sum Query
  query(left, right) {
    let sum = 0;
    let n = this.arr.length;
    left += n;
    right += n;
    while (left <= right) {
      if (left % 2 === 1) {
        sum += this.tree[left];
        left++;
      }
      if (right % 2 === 0) {
        sum += this.tree[right];
        right--;
      }
      left = Math.floor(left / 2);
      right = Math.floor(right / 2);
    }
    return sum;
  }

    // Update the value
    update(index, val) {
        let n = this.arr.length;
        index += n;
        this.tree[index] = val;
        while (index > 1) {
            index = Math.floor(index / 2);
            this.tree[index] = this.tree[2 * index] + this.tree[2 * index + 1];
        }
    }
}

// 3. Using a Library (for demonstration - typically not for interviews)
//  This approach would normally use a library like 'segment-tree-library'
//  However, for this example, we'll just show the concept.
//  In a real application, you'd install and import the library.

class SegmentTreeLibrary {
    constructor(arr) {
        this.arr = arr;
        // In a real scenario, you would initialize the segment tree using the library
        this.tree = [...arr]; // Placeholder, the library would handle this
    }

    query(left, right) {
      // Library would handle the query
      let sum = 0;
      for (let i = left; i <= right; i++){
        sum += this.arr[i];
      }
      return sum;
    }

    update(index, val) {
        this.arr[index] = val;
    }
}

// 4.  Precomputed Cumulative Sum (Not a Segment Tree, but related)
class CumulativeSum {
  constructor(arr) {
    this.cumulativeSum = [0];
    for (let i = 0; i < arr.length; i++) {
      this.cumulativeSum.push(this.cumulativeSum[i] + arr[i]);
    }
  }

  query(left, right) {
    return this.cumulativeSum[right + 1] - this.cumulativeSum[left];
  }

    update(index, val) {
        //  Not efficient for updates.  Would require rebuilding the entire array.
        //  Included here for completeness and comparison.
        console.log("Update operation is not efficient for Cumulative Sum.  Consider using a Segment Tree for updates.");
        return; // Or you could recompute the cumulative sum array.
    }
}

// 5.  Block Sum (Square Root Decomposition) - Another related approach
class BlockSum {
    constructor(arr) {
        this.arr = arr;
        this.n = arr.length;
        this.blockSize = Math.floor(Math.sqrt(this.n));
        this.blocks = [];
        for (let i = 0; i < this.n; i++) {
            if (i % this.blockSize === 0) {
                this.blocks.push(0);
            }
            this.blocks[Math.floor(i / this.blockSize)] += arr[i];
        }
    }

    query(left, right) {
        let sum = 0;
        while (left < right && left % this.blockSize !== 0) {
            sum += this.arr[left++];
        }
        while (left + this.blockSize <= right) {
            sum += this.blocks[Math.floor(left / this.blockSize)];
            left += this.blockSize;
        }
        while (left <= right) {
            sum += this.arr[left++];
        }
        return sum;
    }

    update(index, val) {
        this.blocks[Math.floor(index / this.blockSize)] -= this.arr[index];
        this.arr[index] = val;
        this.blocks[Math.floor(index / this.blockSize)] += val;
    }
}



// Example Usage and Testing
const arr = [1, 3, 5, 7, 9, 11];
console.log("Original Array:", arr);

// Test Segment Tree - Recursive
console.log("\nSegment Tree - Recursive Approach:");
const stRecursive = new SegmentTreeRecursive(arr);
console.log("Segment Tree (Recursive):", stRecursive.tree);
console.log("Query (1, 3):", stRecursive.query(0, 0, arr.length - 1, 1, 3)); // Should be 3 + 5 + 7 = 15
stRecursive.update(0, 0, arr.length-1, 2, 6);
console.log("Updated Array:", stRecursive.arr);
console.log("Updated Segment Tree (Recursive):", stRecursive.tree);
console.log("Query (1, 3) after update:", stRecursive.query(0, 0, arr.length - 1, 1, 3));

// Test Segment Tree - Iterative
console.log("\nSegment Tree - Iterative Approach:");
const stIterative = new SegmentTreeIterative(arr);
console.log("Segment Tree (Iterative):", stIterative.tree);
console.log("Query (1, 3):", stIterative.query(1, 3));
stIterative.update(2, 5);
console.log("Updated Array:", stIterative.arr);
console.log("Updated Segment Tree (Iterative):", stIterative.tree);
console.log("Query (1, 3) after update:", stIterative.query(1, 3));

// Test Segment Tree - Library (Conceptual)
console.log("\nSegment Tree - Library Approach (Conceptual):");
const stLibrary = new SegmentTreeLibrary(arr);
console.log("Query (1, 3):", stLibrary.query(1, 3));
stLibrary.update(2, 8);
console.log("Updated Array:", stLibrary.arr);
console.log("Query (1, 3) after update:", stLibrary.query(1, 3));

// Test Cumulative Sum
console.log("\nCumulative Sum Approach:");
const cumSum = new CumulativeSum(arr);
console.log("Cumulative Sum Array:", cumSum.cumulativeSum);
console.log("Query (1, 3):", cumSum.query(1, 3));
cumSum.update(2, 10); //  Update is inefficient
console.log("Query (1, 3) after update:", cumSum.query(1, 3));

// Test Block Sum
console.log("\nBlock Sum Approach:");
const blockSum = new BlockSum(arr);
console.log("Blocks:", blockSum.blocks);
console.log("Query (1, 3):", blockSum.query(1, 3));
blockSum.update(2, 12);
console.log("Updated Array:", blockSum.arr);
console.log("Updated Blocks:", blockSum.blocks);
console.log("Query (1, 3) after update:", blockSum.query(1, 3));

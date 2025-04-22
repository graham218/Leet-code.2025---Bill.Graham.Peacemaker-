// Approach 1: Iterative Construction and Query

/**
 * Implementation of Fenwick Tree (Binary Indexed Tree) - Iterative Approach
 */
class FenwickTreeIterative {
  constructor(arr) {
    this.arr = arr; // Store the original array
    this.n = arr.length;
    this.tree = new Array(this.n + 1).fill(0); // Initialize the Fenwick Tree

    this.buildTree(); // Construct the Fenwick Tree
  }

  /**
   * Constructs the Fenwick Tree from the input array
   */
  buildTree() {
    for (let i = 0; i < this.n; i++) {
      this.update(i, this.arr[i]); // Add each element to the tree
    }
  }

  /**
   * Updates the Fenwick Tree with the difference between the new value and the old value
   * @param {number} i The index to update (0-based)
   * @param {number} val The value to add to the element at index i
   */
  update(i, val) {
    i++; // Convert to 1-based indexing for Fenwick Tree
    while (i <= this.n) {
      this.tree[i] += val;
      i += i & -i; // Move to the parent in the tree
    }
  }

  /**
   * Queries the sum of the elements from index 0 to i
   * @param {number} i The index to query (0-based)
   * @returns {number} The sum of elements from 0 to i
   */
  query(i) {
    i++; // Convert to 1-based indexing
    let sum = 0;
    while (i > 0) {
      sum += this.tree[i];
      i -= i & -i; // Move to the parent
    }
    return sum;
  }

  /**
   * Queries the sum of elements in the range [left, right] (0-based)
   * @param {number} left The left index of the range
   * @param {number} right The right index of the range
   * @returns {number} The sum of elements in the range [left, right]
   */
  rangeSum(left, right) {
    return this.query(right) - this.query(left - 1);
  }
}

// Example Usage:
const arr1 = [1, 3, 4, 8, 6, 1, 4, 2];
const ft1 = new FenwickTreeIterative(arr1);
console.log("Approach 1 - Original Array:", arr1);
console.log("Approach 1 - Fenwick Tree:", ft1.tree);
console.log("Approach 1 - Sum of first 5 elements:", ft1.query(4)); // Should be 1 + 3 + 4 + 8 + 6 = 22
console.log("Approach 1 - Sum of elements from index 2 to 6:", ft1.rangeSum(2, 6)); // Should be 4 + 8 + 6 + 1 + 4 = 23

// Update the value at index 3 (8) to 10
ft1.update(3, 2);
console.log("Approach 1 - Updated Fenwick Tree:", ft1.tree);
console.log("Approach 1 - Sum of first 5 elements after update:", ft1.query(4)); // Should be 1 + 3 + 4 + 10 + 6 = 24
console.log("Approach 1 - Sum of elements from index 2 to 6 after update:", ft1.rangeSum(2, 6));
console.log("--------------------------------------------------");

// Approach 2:  Fenwick Tree with Point Updates and Range Queries
class FenwickTree2 {
  constructor(size) {
    this.size = size;
    this.tree = new Array(size + 1).fill(0);
  }

  update(index, value) {
    index++;
    while (index <= this.size) {
      this.tree[index] += value;
      index += index & -index;
    }
  }

  query(index) {
    index++;
    let sum = 0;
    while (index > 0) {
      sum += this.tree[index];
      index -= index & -index;
    }
    return sum;
  }

  rangeSum(left, right) {
    return this.query(right) - this.query(left - 1);
  }
}

// Example usage
const arr2 = [2, 4, 5, 7, 8, 9];
const ft2 = new FenwickTree2(arr2.length);
for (let i = 0; i < arr2.length; i++) {
  ft2.update(i, arr2[i]);
}

console.log("Approach 2 - Array:", arr2);
console.log("Approach 2 - Fenwick Tree:", ft2.tree);
console.log("Approach 2 - Sum of elements from 0 to 3:", ft2.query(3)); // 2 + 4 + 5 + 7 = 18
console.log("Approach 2 - Sum of elements from 2 to 5:", ft2.rangeSum(2, 5)); // 5 + 7 + 8 + 9 = 29

ft2.update(2, 1); // Update arr2[2] from 5 to 1.  Difference is -4
console.log("Approach 2 - Fenwick Tree after update:", ft2.tree);
console.log("Approach 2 - Sum of elements from 0 to 3 after update:", ft2.query(3)); // 2 + 4 + 1 + 7 = 14
console.log("--------------------------------------------------");

// Approach 3: Using a Function to Create the Fenwick Tree

/**
 * Creates a Fenwick Tree from an input array.
 * @param {number[]} arr The input array.
 * @returns {number[]} The Fenwick Tree.
 */
function createFenwickTree(arr) {
  const n = arr.length;
  const tree = new Array(n + 1).fill(0);
  for (let i = 0; i < n; i++) {
    let index = i + 1;
    while (index <= n) {
      tree[index] += arr[i];
      index += index & -index;
    }
  }
  return tree;
}

/**
 * Queries the sum up to a given index in the original array using the Fenwick Tree.
 * @param {number[]} tree The Fenwick Tree.
 * @param {number} index The index (0-based) up to which the sum is needed.
 * @returns {number} The sum of the elements from index 0 to index in the original array.
 */
function queryFenwickTree(tree, index) {
  index++; // Convert to 1-based index
  let sum = 0;
  while (index > 0) {
    sum += tree[index];
    index -= index & -index;
  }
  return sum;
}

/**
 * Updates the Fenwick Tree and the conceptual original array.
 * @param {number[]} tree The Fenwick Tree to update.
 * @param {number} index The index (0-based) of the element to update.
 * @param {number} value The new value to add to the element at index.
 * @param {number[]} arr The original array (conceptual).
 */
function updateFenwickTree(tree, index, value, arr) {
    const n = arr.length;
    const diff = value - arr[index]; // Calculate the difference
    arr[index] = value; // Update the original array (conceptual)
    index++; // Convert to 1-based index for Fenwick Tree
    while (index <= n) {
        tree[index] += diff;
        index += index & -index;
    }
}

// Example usage
const arr3 = [1, 2, 3, 4, 5];
const ft3 = createFenwickTree(arr3);
console.log("Approach 3 - Original Array:", arr3);
console.log("Approach 3 - Fenwick Tree:", ft3);
console.log("Approach 3 - Sum of first 3 elements:", queryFenwickTree(ft3, 2)); // 1 + 2 + 3 = 6

updateFenwickTree(ft3, 1, 10, arr3); // Update arr3[1] from 2 to 10
console.log("Approach 3 - Updated Array:", arr3);
console.log("Approach 3 - Updated Fenwick Tree:", ft3);
console.log("Approach 3 - Sum of first 3 elements after update:", queryFenwickTree(ft3, 2)); // 1 + 10 + 3 = 14
console.log("--------------------------------------------------");

// Approach 4: Fenwick Tree with Range Update and Point Query
class FenwickTreeRangeUpdate {
  constructor(size) {
    this.size = size;
    this.tree = new Array(size + 1).fill(0);
  }

  update(left, right, value) {
    this._update(left, value);
    this._update(right + 1, -value);
  }

  _update(index, value) {
    index++;
    while (index <= this.size) {
      this.tree[index] += value;
      index += index & -index;
    }
  }

  query(index) {
    index++;
    let sum = 0;
    while (index > 0) {
      sum += this.tree[index];
      index -= index & -index;
    }
    return sum;
  }
}

// Example Usage:
const arr4 = [1, 2, 3, 4, 5];
const ft4 = new FenwickTreeRangeUpdate(arr4.length);

console.log("Approach 4 - Original Array:", arr4); // Not directly used, but conceptually [1,2,3,4,5]
console.log("Approach 4 - Initial Fenwick Tree:", ft4.tree);

// Range update: Add 2 to elements from index 1 to 3 ([2, 3, 4])
ft4.update(1, 3, 2);
console.log("Approach 4 - Fenwick Tree after range update:", ft4.tree);

// Point queries after range update
console.log("Approach 4 - Value at index 0:", ft4.query(0)); // 1
console.log("Approach 4 - Value at index 1:", ft4.query(1)); // 2 + 2 = 4
console.log("Approach 4 - Value at index 2:", ft4.query(2)); // 3 + 2 = 5
console.log("Approach 4 - Value at index 3:", ft4.query(3)); // 4 + 2 = 6
console.log("Approach 4 - Value at index 4:", ft4.query(4)); // 5

// Another range update
ft4.update(0, 2, -1); // Subtract 1 from elements at indices 0, 1, and 2
console.log("Approach 4 - Fenwick Tree after second range update:", ft4.tree);
console.log("Approach 4 - Value at index 0 after second update:", ft4.query(0)); // 1 - 1 = 0
console.log("Approach 4 - Value at index 1 after second update:", ft4.query(1)); // 4 - 1 = 3
console.log("Approach 4 - Value at index 2 after second update:", ft4.query(2)); // 5 - 1 = 4
console.log("Approach 4 - Value at index 3 after second update:", ft4.query(3)); // 6
console.log("Approach 4 - Value at index 4 after second update:", ft4.query(4)); // 5
console.log("--------------------------------------------------");

// Approach 5: 2D Fenwick Tree for Range Updates and Range Queries
class FenwickTree2D {
  constructor(rows, cols) {
    this.rows = rows;
    this.cols = cols;
    this.tree = Array(rows + 1)
      .fill(null)
      .map(() => Array(cols + 1).fill(0));
  }

  update(row, col, value) {
    let r = row + 1;
    while (r <= this.rows) {
      let c = col + 1;
      while (c <= this.cols) {
        this.tree[r][c] += value;
        c += c & -c;
      }
      r += r & -r;
    }
  }

  query(row, col) {
    let r = row + 1;
    let sum = 0;
    while (r > 0) {
      let c = col + 1;
      while (c > 0) {
        sum += this.tree[r][c];
        c -= c & -c;
      }
      r -= r & -r;
    }
    return sum;
  }

  rangeSum(row1, col1, row2, col2) {
    return (
      this.query(row2, col2) -
      this.query(row1 - 1, col2) -
      this.query(row2, col1 - 1) +
      this.query(row1 - 1, col1 - 1)
    );
  }
}

// Example Usage:
const matrix = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9],
];
const rows = matrix.length;
const cols = matrix[0].length;
const ft2d = new FenwickTree2D(rows, cols);

// Initialize the Fenwick Tree with values from the matrix
for (let i = 0; i < rows; i++) {
  for (let j = 0; j < cols; j++) {
    ft2d.update(i, j, matrix[i][j]);
  }
}

console.log("Approach 5 - Original Matrix:", matrix);
console.log("Approach 5 - 2D Fenwick Tree:", ft2d.tree);

// Range query: sum of submatrix from (0,0) to (1,1)
console.log("Approach 5 - Sum of submatrix (0,0) to (1,1):", ft2d.rangeSum(0, 0, 1, 1)); // 1 + 2 + 4 + 5 = 12

// Update a value in the matrix and the Fenwick Tree
ft2d.update(1, 1, 10); // Change matrix[1][1] from 5 to 10
console.log("Approach 5 - 2D Fenwick Tree after update:", ft2d.tree);
console.log("Approach 5 - Sum of submatrix (0,0) to (1,1) after update:", ft2d.rangeSum(0, 0, 1, 1)); // 1 + 2 + 4 + 10 = 17

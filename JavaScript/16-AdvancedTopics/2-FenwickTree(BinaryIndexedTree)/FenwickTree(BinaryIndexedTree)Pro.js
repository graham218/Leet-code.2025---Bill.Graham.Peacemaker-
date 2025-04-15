// Fenwick Tree (Binary Indexed Tree) Implementation in JavaScript

/**
 * A Fenwick Tree or Binary Indexed Tree (BIT) provides efficient methods
 * for calculating prefix sums in an array and updating array elements.
 *
 * Key Operations:
 * - update(index, value): Adds 'value' to the element at 'index'.
 * - getPrefixSum(index): Calculates the sum of elements from index 0 to 'index'.
 *
 * Time Complexity:
 * - update(): O(log n)
 * - getPrefixSum(): O(log n)
 *
 * Space Complexity: O(n)
 */

// Helper function to get the parent of an index in the BIT
function getParent(index) {
    return index & (index + 1);
}

// Helper function to get the next index to update in the BIT
function getNext(index) {
    return index | (index + 1);
}

/**
 * Approach 1: Basic Fenwick Tree (1-based indexing)
 * - Implements a standard Fenwick Tree with 1-based indexing.
 * - Suitable for simple prefix sum queries and updates.
 */
class FenwickTreeBasic {
    constructor(size) {
        this.size = size;
        this.tree = new Array(size + 1).fill(0); // 1-based indexing
    }

    /**
     * Updates the element at 'index' by adding 'value'.
     * @param {number} index 1-based index of the element to update
     * @param {number} value The value to add to the element
     */
    update(index, value) {
        while (index <= this.size) {
            this.tree[index] += value;
            index = getNext(index);
        }
    }

    /**
     * Calculates the prefix sum from index 1 to 'index'.
     * @param {number} index 1-based index up to which the sum is calculated
     * @returns {number} The prefix sum
     */
    getPrefixSum(index) {
        let sum = 0;
        while (index > 0) {
            sum += this.tree[index];
            index = getParent(index) - 1;
        }
        return sum;
    }

      /**
     * Calculates the range sum from index l to r (inclusive).
     * @param {number} l 1-based index of the left bound
     * @param {number} r 1-based index of the right bound
     * @returns {number} The range sum
     */
    getRangeSum(l, r) {
        if (l > r) {
            return 0; // Or throw an error: throw new Error("Invalid range");
        }
        return this.getPrefixSum(r) - this.getPrefixSum(l - 1);
    }
}

/**
 * Approach 2: Fenwick Tree with 0-based indexing
 * - Implements a Fenwick Tree with 0-based indexing.
 * - Requires slight adjustments in index calculations.
 */
class FenwickTreeZeroBased {
    constructor(size) {
        this.size = size;
        this.tree = new Array(size + 1).fill(0); // extra element for easier calculations
    }

    /**
     * Updates the element at 'index' by adding 'value'.
     * @param {number} index 0-based index of the element to update
     * @param {number} value The value to add to the element
     */
    update(index, value) {
        index++; // Convert to 1-based index for BIT operations
        while (index <= this.size) {
            this.tree[index] += value;
            index += (index & -index); // Get next index
        }
    }

    /**
     * Calculates the prefix sum from index 0 to 'index'.
     * @param {number} index 0-based index up to which the sum is calculated
     * @returns {number} The prefix sum
     */
    getPrefixSum(index) {
        index++; // Convert to 1-based index for BIT operations
        let sum = 0;
        while (index > 0) {
            sum += this.tree[index];
            index -= (index & -index); // Get parent index
        }
        return sum;
    }

    /**
      * Calculates the range sum from index l to r (inclusive).
      * @param {number} l 0-based index of the left bound
      * @param {number} r 0-based index of the right bound
      * @returns {number} The range sum
      */
    getRangeSum(l, r) {
        if (l > r) {
          return 0;
        }
        return this.getPrefixSum(r) - this.getPrefixSum(l - 1);
    }
}



/**
 * Approach 3: Fenwick Tree for Range Sum Queries (RSQ)
 * - Specifically designed for range sum queries.
 * - Uses 1-based indexing.
 */
class FenwickTreeRSQ {
    constructor(array) {
        this.size = array.length;
        this.tree = new Array(this.size + 1).fill(0); // 1-based indexing
        this.array = [...array]; // Store original array (for initialization and updates)
        this.buildTree();
    }

    /**
     * Builds the Fenwick Tree from the input array (used in constructor).
     */
    buildTree() {
        for (let i = 0; i < this.size; i++) {
            this.update(i + 1, this.array[i]); // Use 1-based index
        }
    }
    /**
     * Updates the element at 'index' by adding 'value'.
     * @param {number} index 1-based index of the element to update
     * @param {number} value The value to add to the element
     */
    update(index, value) {
        while (index <= this.size) {
            this.tree[index] += value;
            index += (index & -index);
        }
    }

    /**
     * Calculates the prefix sum from index 1 to 'index'.
     * @param {number} index 1-based index up to which the sum is calculated
     * @returns {number} The prefix sum
     */
    getPrefixSum(index) {
        let sum = 0;
        while (index > 0) {
            sum += this.tree[index];
            index -= (index & -index);
        }
        return sum;
    }

    /**
     * Calculates the range sum from index l to r (inclusive).
     * @param {number} l 1-based index of the left bound
     * @param {number} r 1-based index of the right bound
     * @returns {number} The range sum
     */
    getRangeSum(l, r) {
      if (l > r) {
        return 0;
      }
      return this.getPrefixSum(r) - this.getPrefixSum(l - 1);
    }
}

/**
 * Approach 4:  Fenwick Tree for Range Sum and Point Update
 * - Handles both range sum queries and point updates efficiently.
 * - Uses 1-based indexing.
 */
class FenwickTreeRSPU {
  constructor(arr) {
    this.size = arr.length;
    this.tree = new Array(this.size + 1).fill(0); // 1-based indexing
    this.array = [...arr]; // Store a copy of the original array
    this.buildTree();
  }

  buildTree() {
    for (let i = 0; i < this.size; i++) {
      this.update(i + 1, this.array[i]);
    }
  }

  /**
   * Updates the value at a given index in the original array and the Fenwick Tree.
   * @param {number} index 1-based index of the element to update
   * @param {number} newValue The new value for the element
   */
  update(index, newValue) {
      const diff = newValue - this.array[index-1]; //calculate the difference
      this.array[index-1] = newValue; //update the original array
      while (index <= this.size) {
          this.tree[index] += diff;
          index += (index & -index);
      }
  }

  /**
   * Calculates the prefix sum up to a given index.
   * @param {number} index 1-based index
   * @returns {number} The prefix sum
   */
  getPrefixSum(index) {
      let sum = 0;
      while (index > 0) {
          sum += this.tree[index];
          index -= (index & -index);
      }
      return sum;
  }

  /**
   * Calculates the sum of elements within a given range (inclusive).
   * @param {number} left 1-based index of the left endpoint of the range
   * @param {number} right 1-based index of the right endpoint of the range
   * @returns {number} The sum of the elements in the range
   */
    getRangeSum(left, right) {
        if (left > right) {
            return 0;
        }
        return this.getPrefixSum(right) - this.getPrefixSum(left - 1);
    }
}

/**
 * Approach 5: 2D Fenwick Tree for Range Sum Queries and Updates
 * - Implements a 2D Fenwick Tree for range sum queries and updates in a 2D matrix.
 */
class FenwickTree2D {
    constructor(matrix) {
        this.matrix = matrix;
        this.rows = matrix.length;
        this.cols = matrix[0].length;
        this.tree = Array(this.rows + 1).fill(null).map(() => Array(this.cols + 1).fill(0));
        this.buildTree();
    }

    buildTree() {
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.cols; j++) {
                this.update(i + 1, j + 1, this.matrix[i][j]);
            }
        }
    }

    /**
     * Updates the value at a given cell (row, col) by adding 'value'.
     * @param {number} row 1-based row index
     * @param {number} col 1-based column index
     * @param {number} value The value to add
     */
    update(row, col, value) {
        let i = row;
        while (i <= this.rows) {
            let j = col;
            while (j <= this.cols) {
                this.tree[i][j] += value;
                j += (j & -j);
            }
            i += (i & -i);
        }
    }

    /**
     * Calculates the sum of the submatrix from (1, 1) to (row, col).
     * @param {number} row 1-based row index
     * @param {number} col 1-based column index
     * @returns {number} The sum of the submatrix
     */
    getSum(row, col) {
        let sum = 0;
        let i = row;
        while (i > 0) {
            let j = col;
            while (j > 0) {
                sum += this.tree[i][j];
                j -= (j & -j);
            }
            i -= (i & -i);
        }
        return sum;
    }

    /**
     * Calculates the sum of the submatrix defined by the given corners.
     * @param {number} row1 1-based row index of the top-left corner
     * @param {number} col1 1-based column index of the top-left corner
     * @param {number} row2 1-based row index of the bottom-right corner
     * @param {number} col2 1-based column index of the bottom-right corner
     * @returns {number} The sum of the submatrix
     */
    getRangeSum(row1, col1, row2, col2) {
        if (row1 > row2 || col1 > col2) {
            return 0;
        }
        return this.getSum(row2, col2) - this.getSum(row1 - 1, col2) -
               this.getSum(row2, col1 - 1) + this.getSum(row1 - 1, col1 - 1);
    }
}

// Example Usage and Testing
function main() {
    console.log("Fenwick Tree Implementations\n");

    // Approach 1: Basic Fenwick Tree (1-based indexing)
    console.log("Approach 1: Basic Fenwick Tree (1-based indexing)");
    const basicFT = new FenwickTreeBasic(10);
    for (let i = 1; i <= 10; i++) {
        basicFT.update(i, i); // Initialize with values 1 to 10
    }
    console.log("Tree:", basicFT.tree); // Output: [0, 1, 3, 3, 7, 5, 11, 7, 15, 9, 19]
    console.log("Prefix Sum (5):", basicFT.getPrefixSum(5)); // Output: 15 (1+2+3+4+5)
    console.log("Range Sum (2, 4):", basicFT.getRangeSum(2, 4)); // Output 9 (2+3+4)
    basicFT.update(3, 5); // Update element at index 3 by adding 5
    console.log("Tree after update:", basicFT.tree);
    console.log("Prefix Sum (5) after update:", basicFT.getPrefixSum(5)); // Output: 20 (1+2+8+4+5)
    console.log("Range Sum (2, 4) after update:", basicFT.getRangeSum(2, 4)); // Output 14 (2+8+4)
    console.log("\n");

    // Approach 2: Fenwick Tree with 0-based indexing
    console.log("Approach 2: Fenwick Tree with 0-based indexing");
    const zeroBasedFT = new FenwickTreeZeroBased(10);
    for (let i = 0; i < 10; i++) {
        zeroBasedFT.update(i, i + 1); // Initialize with values 1 to 10
    }
    console.log("Tree:", zeroBasedFT.tree); // Output: [0, 1, 3, 3, 7, 5, 11, 7, 15, 9, 19]
    console.log("Prefix Sum (4):", zeroBasedFT.getPrefixSum(4)); // Output: 15 (1+2+3+4+5)
    console.log("Range Sum (1, 3):", zeroBasedFT.getRangeSum(1, 3)); // Output 6 (2+3+4)
    zeroBasedFT.update(2, 5); // Update element at index 2 by adding 5
    console.log("Tree after update:", zeroBasedFT.tree);
    console.log("Prefix Sum (4) after update:", zeroBasedFT.getPrefixSum(4)); // Output: 20 (1+2+8+4+5)
    console.log("Range Sum (1, 3) after update:", zeroBasedFT.getRangeSum(1, 3)); // Output 14 (2+8+4)
    console.log("\n");

    // Approach 3: Fenwick Tree for Range Sum Queries (RSQ)
    console.log("Approach 3: Fenwick Tree for Range Sum Queries (RSQ)");
    const arrayRSQ = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const rsqFT = new FenwickTreeRSQ(arrayRSQ);
    console.log("Original Array:", arrayRSQ);
    console.log("Tree:", rsqFT.tree);
    console.log("Prefix Sum (5):", rsqFT.getPrefixSum(5)); // Output: 15
    console.log("Range Sum (2, 4):", rsqFT.getRangeSum(2, 4)); // Output: 9
    rsqFT.update(3, 5); // Add 5 to the element at index 3 (original value was 3, now it's 8)
    console.log("Tree after update:", rsqFT.tree);
    console.log("Prefix Sum (5) after update:", rsqFT.getPrefixSum(5)); // Output: 20
    console.log("Range Sum (2, 4) after update:", rsqFT.getRangeSum(2, 4)); // Output: 14
    console.log("\n");

    // Approach 4: Fenwick Tree for Range Sum and Point Update
    console.log("Approach 4: Fenwick Tree for Range Sum and Point Update");
    const arrayRSPU = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const rspuFT = new FenwickTreeRSPU(arrayRSPU);
    console.log("Original Array:", arrayRSPU);
    console.log("Tree:", rspuFT.tree);
    console.log("Prefix Sum (5):", rspuFT.getPrefixSum(5));
    console.log("Range Sum (2, 4):", rspuFT.getRangeSum(2, 4));

    rspuFT.update(3, 8); // Update the value at index 3 to 8
    console.log("Updated Array:", rspuFT.array);
    console.log("Tree after update:", rspuFT.tree);
    console.log("Prefix Sum (5) after update:", rspuFT.getPrefixSum(5)); // Output: 20 (1+2+8+4+5)
    console.log("Range Sum (2, 4) after update:", rspuFT.getRangeSum(2, 4)); // Output: 14 (2+8+4)
    console.log("\n");

    // Approach 5: 2D Fenwick Tree for Range Sum Queries and Updates
    console.log("Approach 5: 2D Fenwick Tree for Range Sum Queries and Updates");
    const matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ];
    const ft2D = new FenwickTree2D(matrix);
    console.log("Original Matrix:", matrix);
    console.log("2D Tree:", ft2D.tree);
    console.log("Sum of submatrix (1,1) to (2,2):", ft2D.getRangeSum(1, 1, 2, 2)); // Output: 12 (1+2+4+5)
    ft2D.update(2, 2, 10); // Update matrix[1][1] (which is 5) to 15 (add 10)
    console.log("2D Tree after update:", ft2D.tree);
    console.log("Sum of submatrix (1,1) to (2,2) after update:", ft2D.getRangeSum(1, 1, 2, 2)); // Output: 22 (1+2+14+5)
    console.log("\n");
}

main();

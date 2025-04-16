/**
 * Five Approaches to Find the Kth Smallest Element in a Sorted Matrix
 *
 * A sorted matrix is where each row and each column are in ascending order.
 *
 * 1.  Brute Force (Flatten and Sort)
 * 2.  Min-Heap (Priority Queue)
 * 3.  Binary Search
 * 4.  Optimized Binary Search
 * 5.  Iterative Binary Search
 */

const matrix = [
    [1, 5, 9],
    [10, 11, 13],
    [12, 13, 15]
];
const k = 8;

console.log("Input Matrix:");
console.log(matrix);
console.log("K:", k);

// 1. Brute Force (Flatten and Sort)
//    - Time Complexity: O(N*M log(N*M)), where N is the number of rows and M is the number of columns.
//    - Space Complexity: O(N*M)
function kthSmallest_BruteForce(matrix, k) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    const flattened = [];

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            flattened.push(matrix[i][j]);
        }
    }

    flattened.sort((a, b) => a - b); // Sort in ascending order
    return flattened[k - 1]; // k-1 because arrays are zero-indexed
}

console.log("\n1. Brute Force:");
console.log("Kth Smallest Element:", kthSmallest_BruteForce(matrix, k));


// 2. Min-Heap (Priority Queue)
//    - Time Complexity: O(k log k) in best case (k < N), O(N*M log(k)) in worst case (k ~ N*M)
//    - Space Complexity: O(k)
function kthSmallest_MinHeap(matrix, k) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    const minHeap = new MinPriorityQueue(); // Use a min-heap (PriorityQueue)

    // Push the first column elements into the min-heap.
    for (let i = 0; i < rows; i++) {
        minHeap.enqueue({ val: matrix[i][0], row: i, col: 0 }, matrix[i][0]); // {val, row, col}
    }

    let count = 0;
    let result = 0;

    while (count < k) {
        const { val, row, col } = minHeap.dequeue().element;  // Get the smallest
        result = val;
        count++;

        if (col < cols - 1) {
            // Push the next element in the same row
            minHeap.enqueue({ val: matrix[row][col + 1], row: row, col: col + 1 }, matrix[row][col+1]);
        }
    }
    return result;
}

// Implementation of MinPriorityQueue (Simplified for this problem)
class MinPriorityQueue {
  constructor() {
    this.heap = [];
  }

  enqueue(element, priority) {
    this.heap.push({ element, priority });
    this.bubbleUp(this.heap.length - 1);
  }

  dequeue() {
    if (this.isEmpty()) return null;
    this.swap(0, this.heap.length - 1);
    const popped = this.heap.pop();
    this.bubbleDown(0);
    return popped;
  }

  isEmpty() {
    return this.heap.length === 0;
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index].priority >= this.heap[parentIndex].priority) break;
      this.swap(index, parentIndex);
      index = parentIndex;
    }
  }

  bubbleDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let smallest = index;

      if (leftChild < this.heap.length && this.heap[leftChild].priority < this.heap[smallest].priority) {
        smallest = leftChild;
      }
      if (rightChild < this.heap.length && this.heap[rightChild].priority < this.heap[smallest].priority) {
        smallest = rightChild;
      }
      if (smallest === index) break;
      this.swap(index, smallest);
      index = smallest;
    }
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }
}

console.log("\n2. Min-Heap:");
console.log("Kth Smallest Element:", kthSmallest_MinHeap(matrix, k));


// 3. Binary Search
//    - Time Complexity: O(N log(max - min) * log N), where max and min are the largest and smallest elements.
//    - Space Complexity: O(1)
function kthSmallest_BinarySearch(matrix, k) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    let low = matrix[0][0];
    let high = matrix[rows - 1][cols - 1];

    while (low < high) {
        const mid = low + Math.floor((high - low) / 2);
        let count = 0;
        let j = cols - 1;

        for (let i = 0; i < rows; i++) {
            while (j >= 0 && matrix[i][j] > mid) j--;
            count += (j + 1);
        }

        if (count < k) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

console.log("\n3. Binary Search:");
console.log("Kth Smallest Element:", kthSmallest_BinarySearch(matrix, k));



// 4. Optimized Binary Search
//     - Time Complexity: O(N log(max - min)), where max and min are the largest and smallest elements.
//     - Space Complexity: O(1)
function kthSmallest_OptimizedBinarySearch(matrix, k) {
    const n = matrix.length;
    let low = matrix[0][0];
    let high = matrix[n - 1][n - 1];

    while (low < high) {
        const mid = low + Math.floor((high - low) / 2);
        let count = 0;
        let j = n - 1;

        for (let i = 0; i < n; i++) {
            while (j >= 0 && matrix[i][j] > mid) {
                j--;
            }
            count += j + 1;
        }

        if (count < k) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

console.log("\n4. Optimized Binary Search:");
console.log("Kth Smallest Element:", kthSmallest_OptimizedBinarySearch(matrix, k));


// 5. Iterative Binary Search
//    - Time Complexity: O(N log(max - min)), where max and min are the largest and smallest elements.
//    - Space Complexity: O(1)
function kthSmallest_IterativeBinarySearch(matrix, k) {
    const n = matrix.length;
    let left = matrix[0][0];
    let right = matrix[n - 1][n - 1];

    while (left < right) {
        const mid = left + Math.floor((right - left) / 2);
        let count = 0;
        let j = n - 1;

        for (let i = 0; i < n; i++) {
            while (j >= 0 && matrix[i][j] > mid) {
                j--;
            }
            count += j + 1;
        }

        if (count < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

console.log("\n5. Iterative Binary Search:");
console.log("Kth Smallest Element:", kthSmallest_IterativeBinarySearch(matrix, k));

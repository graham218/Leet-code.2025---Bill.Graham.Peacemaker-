/**
 * Given an n x n matrix where each of the rows and columns is sorted in ascending order,
 * return the kth smallest element in the matrix.
 *
 * Note that it is guaranteed that 1 <= k <= n^2.
 *
 *
 * Example 1:
 *
 * Input:
 * matrix = [
 * [ 1,  5,  9],
 * [10, 11, 13],
 * [12, 13, 15]
 * ],
 * k = 8,
 *
 * Output:
 * 13
 *
 * Example 2:
 *
 * Input:
 * matrix = [
 * [ 5,  9],
 * [10, 11],
 * ],
 * k = 3,
 *
 * Output:
 * 10
 *
 *
 * Constraints:
 *
 * n == matrix.length
 * n == matrix[i].length
 * 1 <= n <= 300
 * -10^9 <= matrix[i][j] <= 10^9
 * All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
 * 1 <= k <= n^2
 */

/**
 * Approach 1: Brute Force (Merge and Sort)
 * - Merge all elements of the matrix into a single array.
 * - Sort the merged array.
 * - Return the (k-1)th element (since arrays are 0-indexed).
 *
 * Time Complexity: O(N^2 log N^2), where N is the number of rows/columns.
 * Space Complexity: O(N^2), for the merged array.
 */
function kthSmallestBruteForce(matrix, k) {
  const n = matrix.length;
  const mergedArray = [];

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      mergedArray.push(matrix[i][j]);
    }
  }

  mergedArray.sort((a, b) => a - b);
  return mergedArray[k - 1];
}

/**
 * Approach 2: Priority Queue (Min-Heap)
 * - Maintain a min-heap of size k.
 * - Iterate through the matrix, adding elements to the heap.
 * - If the heap size exceeds k, remove the largest element from the heap.
 * - The top element of the heap will be the kth smallest.
 *
 * Time Complexity: O(N^2 log k), where N is the number of rows/columns.
 * Space Complexity: O(k), for the heap.
 */
function kthSmallestPriorityQueue(matrix, k) {
  const n = matrix.length;
  const minHeap = new MinPriorityQueue();

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      minHeap.enqueue(matrix[i][j], matrix[i][j]); //adds element with priority
      if (minHeap.size() > k) {
        minHeap.dequeue(); //removes the min element
      }
    }
  }

  return minHeap.dequeue().element; //returns the kth smallest
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

  size() {
    return this.heap.length;
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
  peek(){
     if (this.isEmpty()) return null;
        return this.heap[0].element;
  }
}

/**
 * Approach 3: Binary Search
 * - The kth smallest element must be within the range [matrix[0][0], matrix[n-1][n-1]].
 * - Perform binary search within this range.
 * - For each mid value, count the number of elements in the matrix that are less than or equal to mid.
 * - Adjust the search range based on whether the count is less than k or greater than or equal to k.
 *
 * Time Complexity: O(N log(max - min)), where N is the number of rows/columns,
 * and max and min are the largest and smallest elements in the matrix.
 * Space Complexity: O(1).
 */
function kthSmallestBinarySearch(matrix, k) {
  const n = matrix.length;
  let low = matrix[0][0];
  let high = matrix[n - 1][n - 1];

  while (low <= high) {
    const mid = low + Math.floor((high - low) / 2);
    let count = 0;
    let j = n - 1;

    for (let i = 0; i < n; i++) {
      while (j >= 0 && matrix[i][j] > mid) j--;
      count += j + 1;
    }

    if (count < k) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return low;
}

/**
 * Approach 4: Optimized Binary Search
 * - Similar to the previous binary search approach, but optimizes the counting.
 * - Instead of counting elements <= mid for each row, we start from the bottom-left.
 * - If the current element is <= mid, we add all elements in the current column (including itself) to the count and move right.
 * - Otherwise, we move up.
 *
 * Time Complexity: O(N log(max - min)), where N is the number of rows/columns.
 * Space Complexity: O(1).
 */
function kthSmallestOptimizedBinarySearch(matrix, k) {
    const n = matrix.length;
    let low = matrix[0][0];
    let high = matrix[n - 1][n - 1];

    while (low <= high) {
        const mid = low + Math.floor((high - low) / 2);
        let count = 0;
        let row = n - 1;
        let col = 0;

        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += row + 1; // Add the entire column count
                col++;
            } else {
                row--;
            }
        }

        if (count < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

/**
 * Approach 5: Using a Max Heap of size K
 * - Build a Max Heap of the first row elements.
 * - For the remaining rows, compare the first element of each row with the top of the heap.
 * - If the element is smaller, replace the top of the heap with this element and heapify.
 * - After processing all rows, pop k-1 elements from the heap.
 * - The last element popped is the kth smallest.
 *
 * Time Complexity: O(k log k + (n-1)log k)
 * Space Complexity: O(k)
 */
function kthSmallestMaxHeap(matrix, k) {
  const n = matrix.length;
  const maxHeap = new MaxPriorityQueue();

  // Initialize the heap with the first row
  for (let j = 0; j < n; j++) {
    maxHeap.enqueue({val: matrix[0][j], row: 0, col: j}, matrix[0][j]);
  }

  let result = 0;
  // Pop k-1 times.
  for (let i = 0; i < k; i++) {
    const {val, row, col} = maxHeap.dequeue().element;
    result = val;

    if (row < n - 1) { //if there are more rows to process
      maxHeap.enqueue({val: matrix[row+1][col], row: row+1, col: col}, matrix[row+1][col]);
    }
  }
  return result;
}

// Implementation of MaxPriorityQueue (Simplified for this problem)
class MaxPriorityQueue {
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

  size() {
    return this.heap.length;
  }
    isEmpty() {
    return this.heap.length === 0;
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index].priority <= this.heap[parentIndex].priority) break; // Changed comparison
      this.swap(index, parentIndex);
      index = parentIndex;
    }
  }

  bubbleDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let largest = index; // Changed to largest

      if (leftChild < this.heap.length && this.heap[leftChild].priority > this.heap[largest].priority) { // Changed comparison
        largest = leftChild;
      }

      if (rightChild < this.heap.length && this.heap[rightChild].priority > this.heap[largest].priority) { // Changed comparison
        largest = rightChild;
      }

      if (largest === index) break;

      this.swap(index, largest);
      index = largest;
    }
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }
  peek(){
     if (this.isEmpty()) return null;
        return this.heap[0].element;
  }
}

// Example usage:
const matrix1 = [
  [1, 5, 9],
  [10, 11, 13],
  [12, 13, 15],
];
const k1 = 8;

const matrix2 = [
  [5, 9],
  [10, 11],
];
const k2 = 3;

console.log("Example 1:");
console.log("Matrix:", matrix1);
console.log("k:", k1);
console.log("Brute Force:", kthSmallestBruteForce(matrix1, k1)); // Output: 13
console.log("Priority Queue:", kthSmallestPriorityQueue(matrix1, k1)); // Output: 13
console.log("Binary Search:", kthSmallestBinarySearch(matrix1, k1)); // Output: 13
console.log("Optimized Binary Search:", kthSmallestOptimizedBinarySearch(matrix1, k1)); // Output: 13
console.log("Max Heap:", kthSmallestMaxHeap(matrix1, k1)); // Output: 13

console.log("\nExample 2:");
console.log("Matrix:", matrix2);
console.log("k:", k2);
console.log("Brute Force:", kthSmallestBruteForce(matrix2, k2)); // Output: 10
console.log("Priority Queue:", kthSmallestPriorityQueue(matrix2, k2)); // Output: 10
console.log("Binary Search:", kthSmallestBinarySearch(matrix2, k2)); // Output: 10
console.log("Optimized Binary Search:", kthSmallestOptimizedBinarySearch(matrix2, k2)); // Output: 10
console.log("Max Heap:", kthSmallestMaxHeap(matrix2, k2)); // Output: 10

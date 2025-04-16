/*
Problem: Find the kth largest element in an unsorted array. This is a common problem in software engineering,
and understanding different approaches is crucial.  We'll explore five methods, analyzing their time and space complexity.
*/

/**
 * Approach 1: Sorting
 *
 * 1.  Sort the array in descending order.
 * 2.  The kth largest element will be at index k-1.
 *
 * Time Complexity: O(n log n) - due to sorting.
 * Space Complexity: O(1) - if the sorting algorithm is in-place (e.g., quicksort), otherwise O(n) for merge sort.
 */
function findKthLargestUsingSorting(nums, k) {
    // Create a copy to avoid modifying the original array
    const sortedNums = [...nums].sort((a, b) => b - a); // Sort in descending order
    return sortedNums[k - 1];
}

/**
 * Approach 2: Min-Heap (Priority Queue)
 *
 * 1.  Create a min-heap of size k.
 * 2.  Iterate through the array:
 * -   If the current element is greater than the root of the heap,
 * replace the root with the current element and heapify.
 * 3.  The root of the heap will be the kth largest element.
 *
 * Time Complexity: O(n log k) - Building the heap takes O(k log k), and iterating through the rest of the array and
 * potentially replacing the root takes O((n-k) log k). If k is close to n, this approaches O(n log n).
 * Space Complexity: O(k) - for the heap.
 */
function findKthLargestUsingMinHeap(nums, k) {
    class MinHeap {
        constructor() {
            this.heap = [];
        }

        get size() {
            return this.heap.length;
        }

        peek() {
            return this.heap[0];
        }

        add(value) {
            this.heap.push(value);
            this.bubbleUp(this.heap.length - 1);
        }

        poll() {
            if (this.size === 0) return null;
            if (this.size === 1) return this.heap.pop();

            const min = this.heap[0];
            this.heap[0] = this.heap.pop();
            this.bubbleDown(0);
            return min;
        }

        bubbleUp(index) {
            while (index > 0) {
                const parentIndex = Math.floor((index - 1) / 2);
                if (this.heap[index] >= this.heap[parentIndex]) break;
                this.swap(index, parentIndex);
                index = parentIndex;
            }
        }

        bubbleDown(index) {
            while (true) {
                const leftChild = 2 * index + 1;
                const rightChild = 2 * index + 2;
                let smallest = index;

                if (leftChild < this.size && this.heap[leftChild] < this.heap[smallest]) {
                    smallest = leftChild;
                }
                if (rightChild < this.size && this.heap[rightChild] < this.heap[smallest]) {
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

    const minHeap = new MinHeap();

    for (let i = 0; i < nums.length; i++) {
        if (minHeap.size < k) {
            minHeap.add(nums[i]);
        } else if (nums[i] > minHeap.peek()) {
            minHeap.poll();
            minHeap.add(nums[i]);
        }
    }
    return minHeap.peek();
}

/**
 * Approach 3: Max-Heap (Priority Queue)
 *
 * 1. Build a max-heap from the input array.
 * 2. Extract the maximum element k-1 times.
 * 3. The next extracted element is the kth largest.
 *
 * Time Complexity: O(n + k log n) - Building the heap is O(n), and extracting k elements is O(k log n).
 * Space Complexity: O(n) - for the heap.
 */
function findKthLargestUsingMaxHeap(nums, k) {
    class MaxHeap {
        constructor(array) {
            this.heap = array ? [...array] : [];  //spread operator
            this.buildHeap();
        }

        get size() {
            return this.heap.length;
        }
        peek() {
            return this.heap[0];
        }

        buildHeap() {
            for (let i = Math.floor(this.size / 2) - 1; i >= 0; i--) {
                this.bubbleDown(i);
            }
        }

        bubbleDown(index) {
            while (true) {
                const leftChild = 2 * index + 1;
                const rightChild = 2 * index + 2;
                let largest = index;

                if (leftChild < this.size && this.heap[leftChild] > this.heap[largest]) {
                    largest = leftChild;
                }
                if (rightChild < this.size && this.heap[rightChild] > this.heap[largest]) {
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

        poll() {
            if (this.size === 0) return null;
            if (this.size === 1) return this.heap.pop();
            const max = this.heap[0];
            this.heap[0] = this.heap.pop();
            this.bubbleDown(0);
            return max;
        }
    }

    const maxHeap = new MaxHeap(nums);
    for (let i = 0; i < k - 1; i++) {
        maxHeap.poll();
    }
    return maxHeap.peek();
}

/**
 * Approach 4: QuickSelect (Partitioning)
 *
 * 1.  Use the partitioning logic from QuickSort.
 * 2.  Choose a pivot and partition the array such that elements greater than the pivot are on the left
 * and elements smaller than the pivot are on the right.
 * 3.  If the pivot's index is k-1, we found the kth largest.
 * 4.  If the pivot's index is less than k-1, search in the right partition.
 * 5.  If the pivot's index is greater than k-1, search in the left partition.
 *
 * Time Complexity: O(n) on average, O(n^2) in the worst case (if the pivot is consistently the smallest or largest element).
 * Space Complexity: O(1) - in-place partitioning.
 */
function findKthLargestUsingQuickSelect(nums, k) {
    function partition(arr, low, high) {
        const pivot = arr[high];
        let i = low - 1;

        for (let j = low; j < high; j++) {
            if (arr[j] >= pivot) { // Changed comparison to find kth largest
                i++;
                [arr[i], arr[j]] = [arr[j], arr[i]];
            }
        }
        [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
        return i + 1;
    }

    function quickSelect(arr, low, high, k) {
        if (low > high) return;

        const pi = partition(arr, low, high);

        if (pi === k - 1) {
            return arr[pi];
        } else if (pi < k - 1) {
            return quickSelect(arr, pi + 1, high, k);
        } else {
            return quickSelect(arr, low, pi - 1, k);
        }
    }

    // Create a copy to avoid modifying the original array
    const arr = [...nums];
    return quickSelect(arr, 0, arr.length - 1, k);
}

/**
 * Approach 5: Using Library Function (Not Recommended for Interviews)
 *
 * Most languages/libraries provide functions to efficiently find the kth element.
 * For example, in JavaScript, there isn't a direct built-in function for the kth largest,
 * but you could adapt other methods. This approach is generally NOT recommended for
 * interviews, as the goal is to demonstrate your understanding of algorithms.
 *
 * Time Complexity: Depends on the library implementation.
 * Space Complexity: Depends on the library implementation.
 */
function findKthLargestUsingLibrary(nums, k) {
    //  JavaScript doesn't have a direct, efficient kth-largest function.
    //  The best you could do with standard library functions is sort and pick, which is what approach 1 does.
    //  For demonstration, we'll just reuse the sorting approach here.
    const sortedNums = [...nums].sort((a, b) => b - a);
    return sortedNums[k-1];
}



// Example usage and testing:
const nums = [3, 2, 1, 5, 6, 4];
const k = 2;

console.log(`Array: ${nums}, k: ${k}`);
console.log("-----------------------------------");
console.log("Approach 1: Sorting:", findKthLargestUsingSorting(nums, k));
console.log("Approach 2: Min-Heap:", findKthLargestUsingMinHeap(nums, k));
console.log("Approach 3: Max-Heap:", findKthLargestUsingMaxHeap(nums, k));
console.log("Approach 4: QuickSelect:", findKthLargestUsingQuickSelect(nums, k));
console.log("Approach 5: Library Function:", findKthLargestUsingLibrary(nums, k));

// Test with a different array and k
const nums2 = [9, 3, 2, 4, 8, 6, 1, 5, 7];
const k2 = 3;
console.log(`\nArray: ${nums2}, k: ${k2}`);
console.log("-----------------------------------");
console.log("Approach 1: Sorting:", findKthLargestUsingSorting(nums2, k2));
console.log("Approach 2: Min-Heap:", findKthLargestUsingMinHeap(nums2, k2));
console.log("Approach 3: Max-Heap:", findKthLargestUsingMaxHeap(nums2, k2));
console.log("Approach 4: QuickSelect:", findKthLargestUsingQuickSelect(nums2, k2));
console.log("Approach 5: Library Function:", findKthLargestUsingLibrary(nums2, k2));

// Test with duplicate numbers
const nums3 = [3, 3, 3, 3, 4, 4, 4, 5, 5, 6];
const k3 = 3;
console.log(`\nArray: ${nums3}, k: ${k3}`);
console.log("-----------------------------------");
console.log("Approach 1: Sorting:", findKthLargestUsingSorting(nums3, k3));
console.log("Approach 2: Min-Heap:", findKthLargestUsingMinHeap(nums3, k3));
console.log("Approach 3: Max-Heap:", findKthLargestUsingMaxHeap(nums3, k3));
console.log("Approach 4: QuickSelect:", findKthLargestUsingQuickSelect(nums3, k3));
console.log("Approach 5: Library Function:", findKthLargestUsingLibrary(nums3, k3));

// Test with a large array and smaller k
const nums4 = Array.from({length: 10000}, () => Math.floor(Math.random() * 100000));
const k4 = 10;
console.log(`\nArray of size ${nums4.length}, k: ${k4}`);
console.log("-----------------------------------");
console.time("Approach 1: Sorting (Large Array)");
console.log("Approach 1: Sorting:", findKthLargestUsingSorting(nums4, k4));
console.timeEnd("Approach 1: Sorting (Large Array)");

console.time("Approach 2: Min-Heap (Large Array)");
console.log("Approach 2: Min-Heap:", findKthLargestUsingMinHeap(nums4, k4));
console.timeEnd("Approach 2: Min-Heap (Large Array)");

console.time("Approach 3: Max-Heap (Large Array)");
console.log("Approach 3: Max-Heap:", findKthLargestUsingMaxHeap(nums4, k4));
console.timeEnd("Approach 3: Max-Heap (Large Array)");

console.time("Approach 4: QuickSelect (Large Array)");
console.log("Approach 4: QuickSelect:", findKthLargestUsingQuickSelect(nums4, k4));
console.timeEnd("Approach 4: QuickSelect (Large Array)");

console.time("Approach 5: Library Function (Large Array)");
console.log("Approach 5: Library Function:", findKthLargestUsingLibrary(nums4, k4));
console.timeEnd("Approach 5: Library Function (Large Array)");

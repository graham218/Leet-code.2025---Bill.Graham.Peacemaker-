/*
Problem: Median of Two Sorted Arrays

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/

/**
 * Approach 1: Merge and Find Median
 * - Merge the two sorted arrays into a single sorted array.
 * - Calculate the median based on the length of the merged array.
 * - Time Complexity: O(m+n)
 * - Space Complexity: O(m+n)
 */
const findMedianSortedArrays_merge = (nums1, nums2) => {
    const mergedArray = [];
    let i = 0;
    let j = 0;

    while (i < nums1.length && j < nums2.length) {
        if (nums1[i] <= nums2[j]) {
            mergedArray.push(nums1[i]);
            i++;
        } else {
            mergedArray.push(nums2[j]);
            j++;
        }
    }

    while (i < nums1.length) {
        mergedArray.push(nums1[i]);
        i++;
    }

    while (j < nums2.length) {
        mergedArray.push(nums2[j]);
        j++;
    }

    const n = mergedArray.length;
    if (n % 2 === 0) {
        return (mergedArray[n / 2 - 1] + mergedArray[n / 2]) / 2;
    } else {
        return mergedArray[Math.floor(n / 2)];
    }
};

/**
 * Approach 2: Merge and Find Median (Optimized)
 * - Merge the two sorted arrays, but only store the elements needed to calculate the median.
 * - This avoids storing the entire merged array, reducing space complexity.
 * - Time Complexity: O(m+n)
 * - Space Complexity: O(1) - Optimized version uses constant space.
 */
const findMedianSortedArrays_mergeOptimized = (nums1, nums2) => {
    const m = nums1.length;
    const n = nums2.length;
    const total = m + n;
    const half = Math.floor(total / 2);
    let i = 0;
    let j = 0;
    let mid1 = 0;
    let mid2 = 0;

    for (let count = 0; count <= half; count++) {
        mid1 = mid2; // Store the previous mid2
        if (i < m && (j >= n || nums1[i] <= nums2[j])) {
            mid2 = nums1[i];
            i++;
        } else {
            mid2 = nums2[j];
            j++;
        }
    }

    if (total % 2 === 0) {
        return (mid1 + mid2) / 2.0;
    } else {
        return mid2;
    }
};


/**
 * Approach 3: Binary Search
 * - Use binary search on the smaller array to find the partition point.
 * - This approach is more efficient, especially when the arrays have significantly different sizes.
 * - Time Complexity: O(log(min(m, n)))
 * - Space Complexity: O(1)
 */
const findMedianSortedArrays_binarySearch = (nums1, nums2) => {
    const m = nums1.length;
    const n = nums2.length;
    if (m > n) {
        return findMedianSortedArrays_binarySearch(nums2, nums1); // Ensure nums1 is the smaller array
    }

    let low = 0;
    let high = m;
    const half = Math.floor((m + n + 1) / 2);

    while (low <= high) {
        const partitionX = Math.floor((low + high) / 2);
        const partitionY = half - partitionX;

        const maxLeftX = partitionX === 0 ? -Infinity : nums1[partitionX - 1];
        const minRightX = partitionX === m ? Infinity : nums1[partitionX];

        const maxLeftY = partitionY === 0 ? -Infinity : nums2[partitionY - 1];
        const minRightY = partitionY === n ? Infinity : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 === 0) {
                return (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0;
            } else {
                return Math.max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return 0; //Should not reach here, but added for the sake of completeness.
};

/**
 * Approach 4: Using a Min Heap (Priority Queue)
 * - Insert all elements from both arrays into a min heap.
 * - Pop elements from the heap until we reach the median.
 * - Time Complexity: O((m+n)log(m+n))  due to heap insertion
 * - Space Complexity: O(m+n)
 */

class MinHeap {
    constructor() {
        this.heap = [];
    }

    insert(value) {
        this.heap.push(value);
        this.bubbleUp(this.heap.length - 1);
    }

    bubbleUp(index) {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.heap[index] < this.heap[parentIndex]) {
                [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    extractMin() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();

        const min = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.bubbleDown(0);
        return min;
    }

    bubbleDown(index) {
        while (true) {
            const leftChild = 2 * index + 1;
            const rightChild = 2 * index + 2;
            let smallest = index;

            if (leftChild < this.heap.length && this.heap[leftChild] < this.heap[smallest]) {
                smallest = leftChild;
            }

            if (rightChild < this.heap.length && this.heap[rightChild] < this.heap[smallest]) {
                smallest = rightChild;
            }

            if (smallest !== index) {
                [this.heap[index], this.heap[smallest]] = [this.heap[smallest], this.heap[index]];
                index = smallest;
            } else {
                break;
            }
        }
    }

    size() {
        return this.heap.length;
    }
}

const findMedianSortedArrays_heap = (nums1, nums2) => {
    const minHeap = new MinHeap();
    for (const num of nums1) {
        minHeap.insert(num);
    }
    for (const num of nums2) {
        minHeap.insert(num);
    }

    const total = nums1.length + nums2.length;
    const half = Math.floor(total / 2);

    for (let i = 0; i < half; i++) {
        minHeap.extractMin();
    }

    if (total % 2 === 0) {
        return (minHeap.extractMin() + minHeap.extractMin()) / 2;
    } else {
        return minHeap.extractMin();
    }
};

/**
 * Approach 5: Using Javascript Array Sort (Not Recommended for Performance)
 * - Concatenate the two arrays and sort the result.
 * - Find the median of the sorted array.
 * - This is the simplest to implement but has the worst performance.
 * - Time Complexity: O((m+n)log(m+n)) due to sorting
 * - Space Complexity: O(m+n)
 */
const findMedianSortedArrays_sort = (nums1, nums2) => {
    const mergedArray = nums1.concat(nums2);
    mergedArray.sort((a, b) => a - b); // Sort numerically
    const n = mergedArray.length;
    if (n % 2 === 0) {
        return (mergedArray[n / 2 - 1] + mergedArray[n / 2]) / 2;
    } else {
        return mergedArray[Math.floor(n / 2)];
    }
};



// Example Usage and Console Logs
const nums1_1 = [1, 3];
const nums2_1 = [2];
console.log("Example 1:");
console.log("Approach 1 (Merge):", findMedianSortedArrays_merge(nums1_1, nums2_1));
console.log("Approach 2 (Merge Optimized):", findMedianSortedArrays_mergeOptimized(nums1_1, nums2_1));
console.log("Approach 3 (Binary Search):", findMedianSortedArrays_binarySearch(nums1_1, nums2_1));
console.log("Approach 4 (Heap):", findMedianSortedArrays_heap(nums1_1, nums2_1));
console.log("Approach 5 (Sort):", findMedianSortedArrays_sort(nums1_1, nums2_1));

const nums1_2 = [1, 2];
const nums2_2 = [3, 4];
console.log("\nExample 2:");
console.log("Approach 1 (Merge):", findMedianSortedArrays_merge(nums1_2, nums2_2));
console.log("Approach 2 (Merge Optimized):", findMedianSortedArrays_mergeOptimized(nums1_2, nums2_2));
console.log("Approach 3 (Binary Search):", findMedianSortedArrays_binarySearch(nums1_2, nums2_2));
console.log("Approach 4 (Heap):", findMedianSortedArrays_heap(nums1_2, nums2_2));
console.log("Approach 5 (Sort):", findMedianSortedArrays_sort(nums1_2, nums2_2));

const nums1_3 = [0, 0];
const nums2_3 = [0, 0];
console.log("\nExample 3:");
console.log("Approach 1 (Merge):", findMedianSortedArrays_merge(nums1_3, nums2_3));
console.log("Approach 2 (Merge Optimized):", findMedianSortedArrays_mergeOptimized(nums1_3, nums2_3));
console.log("Approach 3 (Binary Search):", findMedianSortedArrays_binarySearch(nums1_3, nums2_3));
console.log("Approach 4 (Heap):", findMedianSortedArrays_heap(nums1_3, nums2_3));
console.log("Approach 5 (Sort):", findMedianSortedArrays_sort(nums1_3, nums2_3));

const nums1_4 = [2];
const nums2_4 = [];
console.log("\nExample 4:");
console.log("Approach 1 (Merge):", findMedianSortedArrays_merge(nums1_4, nums2_4));
console.log("Approach 2 (Merge Optimized):", findMedianSortedArrays_mergeOptimized(nums1_4, nums2_4));
console.log("Approach 3 (Binary Search):", findMedianSortedArrays_binarySearch(nums1_4, nums2_4));
console.log("Approach 4 (Heap):", findMedianSortedArrays_heap(nums1_4, nums2_4));
console.log("Approach 5 (Sort):", findMedianSortedArrays_sort(nums1_4, nums2_4));

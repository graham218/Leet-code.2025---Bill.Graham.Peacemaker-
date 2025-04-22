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
 * Time Complexity: O(m+n)
 * Space Complexity: O(m+n)
 */
function findMedianSortedArrays_merge(nums1, nums2) {
    const merged = [];
    let i = 0;
    let j = 0;

    while (i < nums1.length && j < nums2.length) {
        if (nums1[i] <= nums2[j]) {
            merged.push(nums1[i]);
            i++;
        } else {
            merged.push(nums2[j]);
            j++;
        }
    }

    while (i < nums1.length) {
        merged.push(nums1[i]);
        i++;
    }

    while (j < nums2.length) {
        merged.push(nums2[j]);
        j++;
    }

    const mid = Math.floor(merged.length / 2);
    if (merged.length % 2 === 0) {
        return (merged[mid - 1] + merged[mid]) / 2;
    } else {
        return merged[mid];
    }
}

/**
 * Approach 2: Optimized Merge (Without Extra Array)
 * Time Complexity: O(m+n)
 * Space Complexity: O(1)
 */
function findMedianSortedArrays_optimizedMerge(nums1, nums2) {
    const m = nums1.length;
    const n = nums2.length;
    const total = m + n;
    const mid = Math.floor(total / 2);
    let i = 0;
    let j = 0;
    let left = 0;
    let right = 0;

    for (let k = 0; k <= mid; k++) {
        if (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                left = right;
                right = nums1[i];
                i++;
            } else {
                left = right;
                right = nums2[j];
                j++;
            }
        } else if (i < m) {
            left = right;
            right = nums1[i];
            i++;
        } else {
            left = right;
            right = nums2[j];
            j++;
        }
    }

    if (total % 2 === 0) {
        return (left + right) / 2;
    } else {
        return right;
    }
}


/**
 * Approach 3: Binary Search
 * Time Complexity: O(log(min(m,n)))
 * Space Complexity: O(1)
 */
function findMedianSortedArrays_binarySearch(nums1, nums2) {
    const m = nums1.length;
    const n = nums2.length;
    if (m > n) {
        return findMedianSortedArrays_binarySearch(nums2, nums1); // Ensure nums1 is shorter
    }

    let low = 0;
    let high = m;
    const total = m + n;
    const half = Math.floor(total / 2);

    while (low <= high) {
        const partitionX = Math.floor((low + high) / 2);
        const partitionY = half - partitionX;

        const maxLeftX = partitionX === 0 ? -Infinity : nums1[partitionX - 1];
        const minRightX = partitionX === m ? Infinity : nums1[partitionX];

        const maxLeftY = partitionY === 0 ? -Infinity : nums2[partitionY - 1];
        const minRightY = partitionY === n ? Infinity : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if (total % 2 === 0) {
                return (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2;
            } else {
                return Math.max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    throw new Error("Arrays are not sorted.");
}

/**
 * Approach 4: Using a Max Heap and a Min Heap
 * Time Complexity: O((m+n)log(m+n)) - due to heap insertions
 * Space Complexity: O(m+n)
 */
class MaxHeap {
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
            if (this.heap[index] <= this.heap[parentIndex]) break;
            this.swap(index, parentIndex);
            index = parentIndex;
        }
    }

    extractMax() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();
        const max = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.bubbleDown(0);
        return max;
    }

    bubbleDown(index) {
        while (true) {
            const leftChild = 2 * index + 1;
            const rightChild = 2 * index + 2;
            let largest = index;

            if (leftChild < this.heap.length && this.heap[leftChild] > this.heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < this.heap.length && this.heap[rightChild] > this.heap[largest]) {
                largest = rightChild;
            }
            if (largest === index) break;
            this.swap(index, largest);
            index = largest;
        }
    }

    peek() {
        return this.heap[0];
    }

    size() {
        return this.heap.length;
    }

    swap(i, j) {
        [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
    }
}

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
            if (this.heap[index] >= this.heap[parentIndex]) break;
            this.swap(index, parentIndex);
            index = parentIndex;
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
            if (smallest === index) break;
            this.swap(index, smallest);
            index = smallest;
        }
    }

    peek() {
        return this.heap[0];
    }

    size() {
        return this.heap.length;
    }

    swap(i, j) {
        [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
    }
}

function findMedianSortedArrays_heaps(nums1, nums2) {
    const maxHeap = new MaxHeap();
    const minHeap = new MinHeap();

    for (let num of [...nums1, ...nums2]) {
        if (maxHeap.size() === 0 || num <= maxHeap.peek()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }

        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(maxHeap.extractMax());
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.insert(minHeap.extractMin());
        }
    }

    if (maxHeap.size() === minHeap.size()) {
        return (maxHeap.peek() + minHeap.peek()) / 2;
    } else {
        return maxHeap.peek();
    }
}

/**
 * Approach 5: Using Javascript Array Sort
 * Time Complexity: O((m+n)log(m+n))
 * Space Complexity: O(m+n)
 */
function findMedianSortedArrays_sort(nums1, nums2) {
    const mergedArray = [...nums1, ...nums2].sort((a, b) => a - b);
    const len = mergedArray.length;
    const mid = Math.floor(len / 2);

    if (len % 2 === 0) {
        return (mergedArray[mid - 1] + mergedArray[mid]) / 2;
    } else {
        return mergedArray[mid];
    }
}



// Example Usage and Verification
const nums1_1 = [1, 3];
const nums2_1 = [2];
console.log("Example 1 - Merge and Find:", findMedianSortedArrays_merge(nums1_1, nums2_1));
console.log("Example 1 - Optimized Merge:", findMedianSortedArrays_optimizedMerge(nums1_1, nums2_1));
console.log("Example 1 - Binary Search:", findMedianSortedArrays_binarySearch(nums1_1, nums2_1));
console.log("Example 1 - Heaps:", findMedianSortedArrays_heaps(nums1_1, nums2_1));
console.log("Example 1 - Sort:", findMedianSortedArrays_sort(nums1_1, nums2_1));


const nums1_2 = [1, 2];
const nums2_2 = [3, 4];
console.log("Example 2 - Merge and Find:", findMedianSortedArrays_merge(nums1_2, nums2_2));
console.log("Example 2 - Optimized Merge:", findMedianSortedArrays_optimizedMerge(nums1_2, nums2_2));
console.log("Example 2 - Binary Search:", findMedianSortedArrays_binarySearch(nums1_2, nums2_2));
console.log("Example 2 - Heaps:", findMedianSortedArrays_heaps(nums1_2, nums2_2));
console.log("Example 2 - Sort:", findMedianSortedArrays_sort(nums1_2, nums2_2));

const nums1_3 = [0, 0];
const nums2_3 = [0, 0];
console.log("Example 3 - Merge and Find:", findMedianSortedArrays_merge(nums1_3, nums2_3));
console.log("Example 3 - Optimized Merge:", findMedianSortedArrays_optimizedMerge(nums1_3, nums2_3));
console.log("Example 3 - Binary Search:", findMedianSortedArrays_binarySearch(nums1_3, nums2_3));
console.log("Example 3 - Heaps:", findMedianSortedArrays_heaps(nums1_3, nums2_3));
console.log("Example 3 - Sort:", findMedianSortedArrays_sort(nums1_3, nums2_3));

const nums1_4 = [2];
const nums2_4 = [];
console.log("Example 4 - Merge and Find:", findMedianSortedArrays_merge(nums1_4, nums2_4));
console.log("Example 4 - Optimized Merge:", findMedianSortedArrays_optimizedMerge(nums1_4, nums2_4));
console.log("Example 4 - Binary Search:", findMedianSortedArrays_binarySearch(nums1_4, nums2_4));
console.log("Example 4 - Heaps:", findMedianSortedArrays_heaps(nums1_4, nums2_4));
console.log("Example 4 - Sort:", findMedianSortedArrays_sort(nums1_4, nums2_4));

const nums1_5 = [3];
const nums2_5 = [-2, -1];
console.log("Example 5 - Merge and Find:", findMedianSortedArrays_merge(nums1_5, nums2_5));
console.log("Example 5 - Optimized Merge:", findMedianSortedArrays_optimizedMerge(nums1_5, nums2_5));
console.log("Example 5 - Binary Search:", findMedianSortedArrays_binarySearch(nums1_5, nums2_5));
console.log("Example 5 - Heaps:", findMedianSortedArrays_heaps(nums1_5, nums2_5));
console.log("Example 5 - Sort:", findMedianSortedArrays_sort(nums1_5, nums2_5));

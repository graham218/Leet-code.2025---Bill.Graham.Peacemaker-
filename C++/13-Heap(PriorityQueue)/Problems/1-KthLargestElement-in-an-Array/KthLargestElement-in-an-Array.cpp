/*
    Heap (Priority Queue) >> Kth Largest Element in an Array

    Given an integer array nums and an integer k, return the kth largest element in the array.
    Note that it is the kth largest element in the sorted order, not the kth distinct element.
    You must solve it in O(n) time complexity.

    Example 1:
    Input: nums = [3,2,1,5,6,4], k = 2
    Output: 5

    Example 2:
    Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    Output: 4

    Constraints:
    1 <= k <= nums.length <= 105
    -104 <= nums[i] <= 104
*/

/**
 * Approach 1: Using Array.sort()
 * Sort the array in descending order and return the element at index k-1.
 * Time Complexity: O(n log n)
 * Space Complexity: O(1) or O(n) depending on the sorting algorithm implementation
 */
const findKthLargestUsingSort = (nums, k) => {
    const sortedNums = [...nums].sort((a, b) => b - a); // Sort in descending order
    return sortedNums[k - 1];
};

/**
 * Approach 2: Using a Max Heap (Priority Queue)
 * Build a max heap from the array, then extract the top k elements.
 * The kth largest element will be the last extracted element.
 * Time Complexity: O(n + k log n)  -> O(n) to build heap, O(k log n) to extract k elements
 * Space Complexity: O(n) for the heap
 */
const findKthLargestUsingMaxHeap = (nums, k) => {
    // Build Max Heap
    const buildMaxHeap = (arr) => {
        const n = arr.length;
        for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    };

    // Heapify function for Max Heap
    const heapify = (arr, n, i) => {
        let largest = i;
        const left = 2 * i + 1;
        const right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest !== i) {
            [arr[i], arr[largest]] = [arr[largest], arr[i]]; // Swap
            heapify(arr, n, largest);
        }
    };

    const heap = [...nums]; // Create a copy to avoid modifying the original array
    buildMaxHeap(heap);

    // Extract the k largest elements
    for (let i = 0; i < k - 1; i++) {
        [heap[0], heap[heap.length - 1]] = [heap[heap.length - 1], heap[0]];
        heap.pop();
        heapify(heap, heap.length, 0);
    }
    return heap[0];
};

/**
 * Approach 3: Using a Min Heap (Priority Queue)
 * Maintain a min heap of size k.
 * For each element in the array:
 * - If the element is greater than the root of the min heap,
 * replace the root with the element and heapify the min heap.
 * The root of the min heap will be the kth largest element.
 * Time Complexity: O(n log k)
 * Space Complexity: O(k) for the heap
 */
const findKthLargestUsingMinHeap = (nums, k) => {
    // Build Min Heap of size k
    const buildMinHeap = (arr) => {
        const n = arr.length;
        for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
            minHeapify(arr, n, i);
        }
    };

    // Heapify function for Min Heap
    const minHeapify = (arr, n, i) => {
        let smallest = i;
        const left = 2 * i + 1;
        const right = 2 * i + 2;

        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }

        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }

        if (smallest !== i) {
            [arr[i], arr[smallest]] = [arr[smallest], arr[i]]; // Swap
            minHeapify(arr, n, smallest);
        }
    };

    const minHeap = nums.slice(0, k); // Initialize minHeap with first k elements
    buildMinHeap(minHeap);

    for (let i = k; i < nums.length; i++) {
        if (nums[i] > minHeap[0]) {
            minHeap[0] = nums[i];
            minHeapify(minHeap, k, 0);
        }
    }
    return minHeap[0];
};

/**
 * Approach 4: Using QuickSelect (Optimized)
 * QuickSelect is a selection algorithm to find the kth smallest element in an unordered list.
 * It's similar to QuickSort but only partitions the necessary sub-array.
 * Average Time Complexity: O(n)
 * Worst-case Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
const findKthLargestUsingQuickSelect = (nums, k) => {
    const findKthSmallest = (arr, low, high, k) => {
        const pivotIndex = partition(arr, low, high);
        if (pivotIndex === k - 1) {
            return arr[pivotIndex];
        } else if (pivotIndex < k - 1) {
            return findKthSmallest(arr, pivotIndex + 1, high, k);
        } else {
            return findKthSmallest(arr, low, pivotIndex - 1, k);
        }
    };

    const partition = (arr, low, high) => {
        const pivot = arr[high];
        let i = low - 1;

        for (let j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                [arr[i], arr[j]] = [arr[j], arr[i]]; // Swap
            }
        }
        [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]]; // Swap
        return i + 1;
    };

    // To find the kth largest, we find the (n - k + 1)th smallest
    const n = nums.length;
    return findKthSmallest([...nums], 0, n - 1, n - k + 1);
};

/**
 * Approach 5: Using QuickSelect (Iterative)
 * Iterative version of QuickSelect
 * Average Time Complexity: O(n)
 * Worst-case Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
const findKthLargestUsingQuickSelectIterative = (nums, k) => {
    const n = nums.length;
    let low = 0;
    let high = n - 1;
    const target = n - k; // Index of the kth largest element

    while (low <= high) {
        const pivotIndex = partition(nums, low, high);
        if (pivotIndex === target) {
            return nums[pivotIndex];
        } else if (pivotIndex < target) {
            low = pivotIndex + 1;
        } else {
            high = pivotIndex - 1;
        }
    }

    function partition(arr, low, high) {
        const pivot = arr[high];
        let i = low - 1;
        for (let j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                [arr[i], arr[j]] = [arr[j], arr[i]];
            }
        }
        [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
        return i + 1;
    }
};

// Example usage and console logs
const nums1 = [3, 2, 1, 5, 6, 4];
const k1 = 2;
console.log(`Input: nums = [${nums1}], k = ${k1}`);
console.log("Approach 1 (Sort):", findKthLargestUsingSort(nums1, k1));
console.log("Approach 2 (Max Heap):", findKthLargestUsingMaxHeap(nums1, k1));
console.log("Approach 3 (Min Heap):", findKthLargestUsingMinHeap(nums1, k1));
console.log("Approach 4 (QuickSelect Recursive):", findKthLargestUsingQuickSelect(nums1, k1));
console.log("Approach 5 (QuickSelect Iterative):", findKthLargestUsingQuickSelectIterative(nums1, k1));
console.log("\n");

const nums2 = [3, 2, 3, 1, 2, 4, 5, 5, 6];
const k2 = 4;
console.log(`Input: nums = [${nums2}], k = ${k2}`);
console.log("Approach 1 (Sort):", findKthLargestUsingSort(nums2, k2));
console.log("Approach 2 (Max Heap):", findKthLargestUsingMaxHeap(nums2, k2));
console.log("Approach 3 (Min Heap):", findKthLargestUsingMinHeap(nums2, k2));
console.log("Approach 4 (QuickSelect Recursive):", findKthLargestUsingQuickSelect(nums2, k2));
console.log("Approach 5 (QuickSelect Iterative):", findKthLargestUsingQuickSelectIterative(nums2, k2));

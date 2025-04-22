/**
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 * Example 2:], k = 1
 * Output: [1]
 */

/**
 * Approach 1: Using a Hash Map and Sorting
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */
const topKFrequent1 = (nums, k) => {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const sortedFrequencies = [...frequencyMap.entries()].sort(([, freqA], [, freqB]) => freqB - freqA);
    const result = [];
    for (let i = 0; i < k; i++) {
        result.push(sortedFrequencies[i][0]);
    }
    return result;
};

/**
 * Approach 2: Using a Hash Map and Bucket Sort
 * Time Complexity: O(N) in the average case, O(N^2) in the worst case.
 * Space Complexity: O(N)
 */
const topKFrequent2 = (nums, k) => {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const bucket = [];
    for (const [num, freq] of frequencyMap) {
        if (!bucket[freq]) {
            bucket[freq] = [];
        }
        bucket[freq].push(num);
    }

    const result = [];
    for (let i = bucket.length - 1; i >= 0 && result.length < k; i--) {
        if (bucket[i]) {
            result.push(...bucket[i]);
        }
    }
    return result.slice(0, k);
};



/**
 * Approach 3: Using a Hash Map and a Priority Queue (Min-Heap)
 * Time Complexity: O(N log K)
 * Space Complexity: O(N)
 */
const topKFrequent3 = (nums, k) => {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    // Min-Heap implementation (Priority Queue)
    class MinPriorityQueue {
        constructor() {
            this.heap = [];
        }

        size() {
            return this.heap.length;
        }

        isEmpty() {
            return this.size() === 0;
        }

        peek() {
            return this.isEmpty() ? null : this.heap[0];
        }


        add(value) {
            this.heap.push(value);
            this.bubbleUp(this.size() - 1);
        }

        poll() {
            if (this.isEmpty()) return null;
            this.swap(0, this.size() - 1);
            const min = this.heap.pop();
            this.bubbleDown(0);
            return min;
        }


        bubbleUp(index) {
            while (index > 0) {
                const parent = Math.floor((index - 1) / 2);
                if (this.heap[index][1] >= this.heap[parent][1]) break;
                this.swap(index, parent);
                index = parent;
            }
        }

        bubbleDown(index) {
            while (true) {
                const left = 2 * index + 1;
                const right = 2 * index + 2;
                let smallest = index;

                if (left < this.size() && this.heap[left][1] < this.heap[smallest][1]) {
                    smallest = left;
                }
                if (right < this.size() && this.heap[right][1] < this.heap[smallest][1]) {
                    smallest = right;
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

    const minHeap = new MinPriorityQueue();

    for (const [num, freq] of frequencyMap) {
        minHeap.add([num, freq]);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
    }

    const result = [];
    while (!minHeap.isEmpty()) {
        result.push(minHeap.poll()[0]);
    }
    return result;
};

/**
 * Approach 4: Using a Hash Map and Sorting (Optimized)
 * Time Complexity: O(N + K log K) which simplifies to O(N) if K is much smaller than N
 * Space Complexity: O(N)
 */
const topKFrequent4 = (nums, k) => {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const uniqueElements = Array.from(frequencyMap.entries());  // Get unique elements with frequencies
    uniqueElements.sort(([, freqA], [, freqB]) => freqB - freqA); // Sort only the unique elements.

    const result = [];
    for (let i = 0; i < k && i < uniqueElements.length; i++) { // Ensure we don't go out of bounds
        result.push(uniqueElements[i][0]);
    }
    return result;
};


/**
 * Approach 5: Using a Hash Map and QuickSelect (Partial Sort)
 * Time Complexity: O(N) on average, O(N^2) worst case
 * Space Complexity: O(N)
 */
const topKFrequent5 = (nums, k) => {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }
    const uniqueFrequencies = Array.from(frequencyMap.entries());

    const quickSelect = (arr, low, high, k) => {
        if (low === high) return;

        const pivotIndex = partition(arr, low, high);
        const kth = arr.length - k; // Index of the kth most frequent

        if (kth === pivotIndex) {
            return; // We found the kth element
        } else if (kth < pivotIndex) {
            quickSelect(arr, low, pivotIndex - 1, k);
        } else {
            quickSelect(arr, pivotIndex + 1, high, k);
        }
    };

    const partition = (arr, low, high) => {
        const pivot = arr[high][1]; // Frequency is used for sorting
        let i = low;

        for (let j = low; j < high; j++) {
            if (arr[j][1] >= pivot) {
                // Change here to sort in descending order of frequency
                [arr[i], arr[j]] = [arr[j], arr[i]];
                i++;
            }
        }
        [arr[i], arr[high]] = [arr[high], arr[i]];
        return i;
    };

    quickSelect(uniqueFrequencies, 0, uniqueFrequencies.length - 1, k);

    const result = [];
    for (let i = 0; i < k; i++) {
        result.push(uniqueFrequencies[i][0]);
    }
    return result;
};


// Example usage and testing
const nums1 = [1, 1, 1, 2, 2, 3];
const k1 = 2;
console.log(`Input: nums = [${nums1}], k = ${k1}`);
console.log("Approach 1 (Sorting):", topKFrequent1(nums1, k1));
console.log("Approach 2 (Bucket Sort):", topKFrequent2(nums1, k1));
console.log("Approach 3 (Min-Heap):", topKFrequent3(nums1, k1));
console.log("Approach 4 (Optimized Sort):", topKFrequent4(nums1, k1));
console.log("Approach 5 (QuickSelect):", topKFrequent5(nums1, k1));
console.log("---");

const nums2 = [1];
const k2 = 1;
console.log(`Input: nums = [${nums2}], k = ${k2}`);
console.log("Approach 1 (Sorting):", topKFrequent1(nums2, k2));
console.log("Approach 2 (Bucket Sort):", topKFrequent2(nums2, k2));
console.log("Approach 3 (Min-Heap):", topKFrequent3(nums2, k2));
console.log("Approach 4 (Optimized Sort):", topKFrequent4(nums2, k2));
console.log("Approach 5 (QuickSelect):", topKFrequent5(nums2, k2));
console.log("---");

const nums3 = [4, 1, -1, 2, -1, 2, 3];
const k3 = 2;
console.log(`Input: nums = [${nums3}], k = ${k3}`);
console.log("Approach 1 (Sorting):", topKFrequent1(nums3, k3));
console.log("Approach 2 (Bucket Sort):", topKFrequent2(nums3, k3));
console.log("Approach 3 (Min-Heap):", topKFrequent3(nums3, k3));
console.log("Approach 4 (Optimized Sort):", topKFrequent4(nums3, k3));
console.log("Approach 5 (QuickSelect):", topKFrequent5(nums3, k3));
console.log("---");

// Top K Frequent Elements - 5 Approaches

// Problem Statement:
// Given an integer array nums and an integer k, return the k most frequent elements.

// Approach 1: Using Map, Sort, and Slice (Simple but O(n log n))
function topKFrequentApproach1(nums, k) {
    // Count frequencies using a Map
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    // Convert to array and sort by frequency
    const sortedEntries = Array.from(frequencyMap.entries())
        .sort((a, b) => b[1] - a[1]);

    // Extract top k elements
    return sortedEntries.slice(0, k).map(entry => entry[0]);
}

// Approach 2: Using Priority Queue (Max Heap)
class MaxHeap {
    constructor() {
        this.heap = [];
    }

    push(val, priority) {
        this.heap.push({val, priority});
        this.heapifyUp();
    }

    pop() {
        if (this.size() === 1) return this.heap.pop().val;
        const top = this.heap[0].val;
        this.heap[0] = this.heap.pop();
        this.heapifyDown();
        return top;
    }

    size() {
        return this.heap.length;
    }

    heapifyUp() {
        let current = this.heap.length - 1;
        while (current > 0) {
            const parent = Math.floor((current - 1) / 2);
            if (this.heap[parent].priority >= this.heap[current].priority) break;
            [this.heap[parent], this.heap[current]] = [this.heap[current], this.heap[parent]];
            current = parent;
        }
    }

    heapifyDown() {
        let current = 0;
        while (true) {
            let left = 2 * current + 1;
            let right = 2 * current + 2;
            let largest = current;

            if (left < this.heap.length && this.heap[left].priority > this.heap[largest].priority) {
                largest = left;
            }

            if (right < this.heap.length && this.heap[right].priority > this.heap[largest].priority) {
                largest = right;
            }

            if (largest === current) break;

            [this.heap[current], this.heap[largest]] = [this.heap[largest], this.heap[current]];
            current = largest;
        }
    }
}

function topKFrequentApproach2(nums, k) {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const maxHeap = new MaxHeap();
    for (const [num, freq] of frequencyMap.entries()) {
        maxHeap.push(num, freq);
    }

    const result = [];
    for (let i = 0; i < k; i++) {
        result.push(maxHeap.pop());
    }

    return result;
}

// Approach 3: Using Bucket Sort (O(n) time)
function topKFrequentApproach3(nums, k) {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    // Create buckets where index represents frequency
    const buckets = Array(nums.length + 1).fill().map(() => []);
    for (const [num, freq] of frequencyMap.entries()) {
        buckets[freq].push(num);
    }

    // Extract top k frequent elements from buckets
    const result = [];
    for (let i = buckets.length - 1; i >= 0 && result.length < k; i--) {
        if (buckets[i].length > 0) {
            result.push(...buckets[i]);
            if (result.length > k) {
                result.length = k; // Trim if we added too many
            }
        }
    }

    return result;
}

// Approach 4: Using Min Heap (More efficient for large n and small k)
class MinHeap {
    constructor() {
        this.heap = [];
    }

    push(val, priority) {
        this.heap.push({val, priority});
        this.heapifyUp();
    }

    pop() {
        if (this.size() === 1) return this.heap.pop().val;
        const top = this.heap[0].val;
        this.heap[0] = this.heap.pop();
        this.heapifyDown();
        return top;
    }

    peek() {
        return this.heap[0];
    }

    size() {
        return this.heap.length;
    }

    heapifyUp() {
        let current = this.heap.length - 1;
        while (current > 0) {
            const parent = Math.floor((current - 1) / 2);
            if (this.heap[parent].priority <= this.heap[current].priority) break;
            [this.heap[parent], this.heap[current]] = [this.heap[current], this.heap[parent]];
            current = parent;
        }
    }

    heapifyDown() {
        let current = 0;
        while (true) {
            let left = 2 * current + 1;
            let right = 2 * current + 2;
            let smallest = current;

            if (left < this.heap.length && this.heap[left].priority < this.heap[smallest].priority) {
                smallest = left;
            }

            if (right < this.heap.length && this.heap[right].priority < this.heap[smallest].priority) {
                smallest = right;
            }

            if (smallest === current) break;

            [this.heap[current], this.heap[smallest]] = [this.heap[smallest], this.heap[current]];
            current = smallest;
        }
    }
}

function topKFrequentApproach4(nums, k) {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const minHeap = new MinHeap();

    for (const [num, freq] of frequencyMap.entries()) {
        if (minHeap.size() < k) {
            minHeap.push(num, freq);
        } else if (freq > minHeap.peek().priority) {
            minHeap.pop();
            minHeap.push(num, freq);
        }
    }

    const result = [];
    while (minHeap.size() > 0) {
        result.push(minHeap.pop());
    }

    return result.reverse(); // To get them in descending order
}

// Approach 5: Using Quickselect (Hoare's selection algorithm)
function topKFrequentApproach5(nums, k) {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const unique = Array.from(frequencyMap.keys());

    function partition(left, right, pivotIndex) {
        const pivotFrequency = frequencyMap.get(unique[pivotIndex]);
        // Move pivot to end
        [unique[pivotIndex], unique[right]] = [unique[right], unique[pivotIndex]];

        let storeIndex = left;
        for (let i = left; i <= right; i++) {
            if (frequencyMap.get(unique[i]) > pivotFrequency) {
                [unique[storeIndex], unique[i]] = [unique[i], unique[storeIndex]];
                storeIndex++;
            }
        }

        // Move pivot to its final place
        [unique[right], unique[storeIndex]] = [unique[storeIndex], unique[right]];
        return storeIndex;
    }

    function quickselect(left, right, kSmallest) {
        if (left === right) return;

        const pivotIndex = Math.floor(Math.random() * (right - left + 1)) + left;
        const partitionIndex = partition(left, right, pivotIndex);

        if (kSmallest === partitionIndex) {
            return;
        } else if (kSmallest < partitionIndex) {
            quickselect(left, partitionIndex - 1, kSmallest);
        } else {
            quickselect(partitionIndex + 1, right, kSmallest);
        }
    }

    quickselect(0, unique.length - 1, k - 1);
    return unique.slice(0, k);
}

// Test Cases
const nums = [1, 1, 1, 2, 2, 3, 4, 4, 4, 4];
const k = 2;

console.log("Approach 1 (Map + Sort):", topKFrequentApproach1(nums, k));
console.log("Approach 2 (Max Heap):", topKFrequentApproach2(nums, k));
console.log("Approach 3 (Bucket Sort):", topKFrequentApproach3(nums, k));
console.log("Approach 4 (Min Heap):", topKFrequentApproach4(nums, k));
console.log("Approach 5 (Quickselect):", topKFrequentApproach5(nums, k));

// Performance Comparison
console.log("\nPerformance Comparison (same input):");
const testNums = Array.from({length: 10000}, () => Math.floor(Math.random() * 100));
const testK = 10;

function measurePerformance(fn, nums, k) {
    const start = performance.now();
    const result = fn(nums, k);
    const end = performance.now();
    return {result, time: end - start};
}

console.log("Approach 1:", measurePerformance(topKFrequentApproach1, testNums, testK).time.toFixed(3) + "ms");
console.log("Approach 2:", measurePerformance(topKFrequentApproach2, testNums, testK).time.toFixed(3) + "ms");
console.log("Approach 3:", measurePerformance(topKFrequentApproach3, testNums, testK).time.toFixed(3) + "ms");
console.log("Approach 4:", measurePerformance(topKFrequentApproach4, testNums, testK).time.toFixed(3) + "ms");
console.log("Approach 5:", measurePerformance(topKFrequentApproach5, testNums, testK).time.toFixed(3) + "ms");
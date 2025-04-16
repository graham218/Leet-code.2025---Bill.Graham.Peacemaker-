// Heap (Priority Queue) Implementation in JavaScript

// =================================================================================================
// 1. Min/Max Heap Using Array (Basic Implementation)
// =================================================================================================
class Heap {
  constructor(type = 'min') {
    this.heap = [];
    this.type = type; // 'min' or 'max'
  }

  /**
   * Get the parent index.
   */
  getParentIndex(index) {
    return Math.floor((index - 1) / 2);
  }

  /**
   * Get the left child index.
   */
  getLeftChildIndex(index) {
    return 2 * index + 1;
  }

  /**
   * Get the right child index.
   */
  getRightChildIndex(index) {
    return 2 * index + 2;
  }

  /**
   * Swap elements at two indices.
   */
  swap(index1, index2) {
    [this.heap[index1], this.heap[index2]] = [this.heap[index2], this.heap[index1]];
  }

  /**
   * Compare two elements based on the heap type (min or max).
   */
  compare(a, b) {
    if (this.type === 'min') {
      return a < b; // For min heap
    } else {
      return a > b; // For max heap
    }
  }

  /**
   * Heapify up (for insertion).
   */
  heapifyUp(index) {
    while (index > 0 && this.compare(this.heap[index], this.heap[this.getParentIndex(index)])) {
      this.swap(index, this.getParentIndex(index));
      index = this.getParentIndex(index);
    }
  }

  /**
   * Heapify down (for extraction).
   */
  heapifyDown(index) {
    let leftChildIndex = this.getLeftChildIndex(index);
    let rightChildIndex = this.getRightChildIndex(index);
    let extreme = index; // min or max, depending on heap type

    if (leftChildIndex < this.heap.length && this.compare(this.heap[leftChildIndex], this.heap[extreme])) {
      extreme = leftChildIndex;
    }

    if (rightChildIndex < this.heap.length && this.compare(this.heap[rightChildIndex], this.heap[extreme])) {
      extreme = rightChildIndex;
    }

    if (extreme !== index) {
      this.swap(index, extreme);
      this.heapifyDown(extreme);
    }
  }

  /**
   * Insert a new element into the heap.
   */
  insert(value) {
    this.heap.push(value);
    this.heapifyUp(this.heap.length - 1);
  }

  /**
   * Extract the root element (min or max).
   */
  extract() {
    if (this.isEmpty()) {
      return null;
    }
    if (this.heap.length === 1) {
      return this.heap.pop();
    }

    const root = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.heapifyDown(0);
    return root;
  }

  /**
   * Get the root element (min or max) without removing it.
   */
  peek() {
    if (this.isEmpty()) {
      return null;
    }
    return this.heap[0];
  }

  /**
   * Check if the heap is empty.
   */
  isEmpty() {
    return this.heap.length === 0;
  }

  /**
   * Get the size of the heap.
   */
  size() {
    return this.heap.length;
  }

  /**
   * Convert the heap to a sorted array (for min heap, ascending order; for max heap, descending order).
   * This is a non-destructive operation.
   */
  toArray() {
      const sortedArray = [];
      const tempHeap = new Heap(this.type); // Create a copy to avoid modifying the original
      tempHeap.heap = [...this.heap]; // Copy the heap elements

      while (!tempHeap.isEmpty()) {
          sortedArray.push(tempHeap.extract());
      }
      return sortedArray;
  }
  /**
   * Clear all elements from the heap.
   */
  clear() {
    this.heap = [];
  }
}

// Example usage:
console.log("1. Min/Max Heap Using Array (Basic Implementation)");
const minHeap = new Heap('min');
minHeap.insert(5);
minHeap.insert(10);
minHeap.insert(3);
minHeap.insert(12);
minHeap.insert(1);
console.log("Min Heap:", minHeap.heap); // Output: [ 1, 3, 5, 12, 10 ]
console.log("Peek:", minHeap.peek());    // Output: 1
console.log("Extract:", minHeap.extract()); // Output: 1
console.log("Min Heap after extract:", minHeap.heap); // Output:  [ 3, 5, 10, 12 ]
console.log("Size:", minHeap.size()); // 4
console.log("Is Empty:", minHeap.isEmpty()); // false
console.log("Sorted Array:", minHeap.toArray()); // [3, 5, 10, 12]

const maxHeap = new Heap('max');
maxHeap.insert(5);
maxHeap.insert(10);
maxHeap.insert(3);
maxHeap.insert(12);
maxHeap.insert(1);
console.log("Max Heap:", maxHeap.heap); // Output: [ 12, 10, 3, 5, 1 ]
console.log("Peek:", maxHeap.peek());    // Output: 12
console.log("Extract:", maxHeap.extract()); // Output: 12
console.log("Max Heap after extract:", maxHeap.heap); // Output: [ 10, 5, 3, 1 ]
console.log("Sorted Array:", maxHeap.toArray()); // [10, 5, 3, 1]
console.log("================================================================================================\n");


// =================================================================================================
// 2. Min/Max Heap Using Array with Custom Compare Function
// =================================================================================================
class HeapWithCompare {
  constructor(compareFunction) {
    this.heap = [];
    this.compare = compareFunction; // Custom compare function
  }

  getParentIndex(index) {
    return Math.floor((index - 1) / 2);
  }

  getLeftChildIndex(index) {
    return 2 * index + 1;
  }

  getRightChildIndex(index) {
    return 2 * index + 2;
  }

  swap(index1, index2) {
    [this.heap[index1], this.heap[index2]] = [this.heap[index2], this.heap[index1]];
  }

  heapifyUp(index) {
    while (index > 0 && this.compare(this.heap[index], this.heap[this.getParentIndex(index)])) {
      this.swap(index, this.getParentIndex(index));
      index = this.getParentIndex(index);
    }
  }

  heapifyDown(index) {
    let leftChildIndex = this.getLeftChildIndex(index);
    let rightChildIndex = this.getRightChildIndex(index);
    let extreme = index;

    if (leftChildIndex < this.heap.length && this.compare(this.heap[leftChildIndex], this.heap[extreme])) {
      extreme = leftChildIndex;
    }

    if (rightChildIndex < this.heap.length && this.compare(this.heap[rightChildIndex], this.heap[extreme])) {
      extreme = rightChildIndex;
    }

    if (extreme !== index) {
      this.swap(index, extreme);
      this.heapifyDown(extreme);
    }
  }

  insert(value) {
    this.heap.push(value);
    this.heapifyUp(this.heap.length - 1);
  }

  extract() {
    if (this.isEmpty()) {
      return null;
    }
    if (this.heap.length === 1) {
      return this.heap.pop();
    }
    const root = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.heapifyDown(0);
    return root;
  }

  peek() {
    if (this.isEmpty()) {
      return null;
    }
    return this.heap[0];
  }

  isEmpty() {
    return this.heap.length === 0;
  }

    toArray() {
      const sortedArray = [];
      const tempHeap = new HeapWithCompare(this.compare); // Use the same compare function
      tempHeap.heap = [...this.heap];

      while (!tempHeap.isEmpty()) {
          sortedArray.push(tempHeap.extract());
      }
      return sortedArray;
  }

  clear() {
    this.heap = [];
  }
}

// Example usage:
console.log("2. Min/Max Heap Using Array with Custom Compare Function");
// Min Heap (using a custom compare function)
const minHeapCustom = new HeapWithCompare((a, b) => a < b);
minHeapCustom.insert(5);
minHeapCustom.insert(10);
minHeapCustom.insert(3);
minHeapCustom.insert(12);
minHeapCustom.insert(1);
console.log("Min Heap (Custom):", minHeapCustom.heap);
console.log("Peek (Custom):", minHeapCustom.peek());
console.log("Extract (Custom):", minHeapCustom.extract());
console.log("Min Heap after extract (Custom):", minHeapCustom.heap);
console.log("Sorted Array (Custom):", minHeapCustom.toArray());

// Max Heap (using a custom compare function)
const maxHeapCustom = new HeapWithCompare((a, b) => a > b);
maxHeapCustom.insert(5);
maxHeapCustom.insert(10);
maxHeapCustom.insert(3);
maxHeapCustom.insert(12);
maxHeapCustom.insert(1);
console.log("Max Heap (Custom):", maxHeapCustom.heap);
console.log("Peek (Custom):", maxHeapCustom.peek());
console.log("Extract (Custom):", maxHeapCustom.extract());
console.log("Max Heap after extract (Custom):", maxHeapCustom.heap);
console.log("Sorted Array (Custom):", maxHeapCustom.toArray());
console.log("================================================================================================\n");

// =================================================================================================
// 3. Min/Max Heap Using a Class with a Size Property
// =================================================================================================
class HeapWithSize {
  constructor(type = 'min') {
    this.heap = [];
    this.type = type;
    this.size = 0; // Keep track of the size
  }

  getParentIndex(index) {
    return Math.floor((index - 1) / 2);
  }

  getLeftChildIndex(index) {
    return 2 * index + 1;
  }

  getRightChildIndex(index) {
    return 2 * index + 2;
  }

  swap(index1, index2) {
    [this.heap[index1], this.heap[index2]] = [this.heap[index2], this.heap[index1]];
  }

  compare(a, b) {
    if (this.type === 'min') {
      return a < b;
    } else {
      return a > b;
    }
  }

  heapifyUp(index) {
    while (index > 0 && this.compare(this.heap[index], this.heap[this.getParentIndex(index)])) {
      this.swap(index, this.getParentIndex(index));
      index = this.getParentIndex(index);
    }
  }

  heapifyDown(index) {
    let leftChildIndex = this.getLeftChildIndex(index);
    let rightChildIndex = this.getRightChildIndex(index);
    let extreme = index;

    if (leftChildIndex < this.size && this.compare(this.heap[leftChildIndex], this.heap[extreme])) { // Use this.size
      extreme = leftChildIndex;
    }

    if (rightChildIndex < this.size && this.compare(this.heap[rightChildIndex], this.heap[extreme])) {  // Use this.size
      extreme = rightChildIndex;
    }

    if (extreme !== index) {
      this.swap(index, extreme);
      this.heapifyDown(extreme);
    }
  }

  insert(value) {
    this.heap.push(value);
    this.heapifyUp(this.size); // Use this.size
    this.size++;
  }

  extract() {
    if (this.isEmpty()) {
      return null;
    }
    if (this.size === 1) { // Use this.size
      this.size--;
      return this.heap.pop();
    }
    const root = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.size--; // Decrement size
    this.heapifyDown(0);
    return root;
  }

  peek() {
    if (this.isEmpty()) {
      return null;
    }
    return this.heap[0];
  }

  isEmpty() {
    return this.size === 0; // Use this.size
  }

  getSize() {
    return this.size;
  }

    toArray() {
      const sortedArray = [];
      const tempHeap = new HeapWithSize(this.type);
      tempHeap.heap = [...this.heap];
      tempHeap.size = this.size; // Correctly copy the size.

      while (!tempHeap.isEmpty()) {
          sortedArray.push(tempHeap.extract());
      }
      return sortedArray;
  }

  clear() {
    this.heap = [];
    this.size = 0;
  }
}

// Example usage:
console.log("3. Min/Max Heap Using a Class with a Size Property");
const minHeapWithSize = new HeapWithSize('min');
minHeapWithSize.insert(5);
minHeapWithSize.insert(10);
minHeapWithSize.insert(3);
minHeapWithSize.insert(12);
minHeapWithSize.insert(1);
console.log("Min Heap with Size:", minHeapWithSize.heap);
console.log("Peek with Size:", minHeapWithSize.peek());
console.log("Extract with Size:", minHeapWithSize.extract());
console.log("Min Heap after extract with Size:", minHeapWithSize.heap);
console.log("Size using getSize():", minHeapWithSize.getSize()); // 4
console.log("Is Empty using isEmpty():", minHeapWithSize.isEmpty());
console.log("Sorted Array with Size:", minHeapWithSize.toArray());

const maxHeapWithSize = new HeapWithSize('max');
maxHeapWithSize.insert(5);
maxHeapWithSize.insert(10);
maxHeapWithSize.insert(3);
maxHeapWithSize.insert(12);
maxHeapWithSize.insert(1);
console.log("Max Heap with Size:", maxHeapWithSize.heap);
console.log("Peek with Size:", maxHeapWithSize.peek());
console.log("Extract with Size:", maxHeapWithSize.extract());
console.log("Max Heap after extract with Size:", maxHeapWithSize.heap);
console.log("Size using getSize():", maxHeapWithSize.getSize()); // 4
console.log("Sorted Array with Size:", maxHeapWithSize.toArray());
console.log("================================================================================================\n");

// =================================================================================================
// 4. Min/Max Heap Using an Object (More Verbose, Demonstrative)
// =================================================================================================
const HeapObject = (type = 'min') => {
  const heap = [];
  let size = 0;

  const getParentIndex = (index) => Math.floor((index - 1) / 2);
  const getLeftChildIndex = (index) => 2 * index + 1;
  const getRightChildIndex = (index) => 2 * index + 2;
  const swap = (index1, index2) => {
    [heap[index1], heap[index2]] = [heap[index2], heap[index1]];
  };
  const compare = (a, b) => (type === 'min' ? a < b : a > b);

  const heapifyUp = (index) => {
    while (index > 0 && compare(heap[index], heap[getParentIndex(index)])) {
      swap(index, getParentIndex(index));
      index = getParentIndex(index);
    }
  };

  const heapifyDown = (index) => {
    let leftChildIndex = getLeftChildIndex(index);
    let rightChildIndex = getRightChildIndex(index);
    let extreme = index;

    if (leftChildIndex < size && compare(heap[leftChildIndex], heap[extreme])) {
      extreme = leftChildIndex;
    }

    if (rightChildIndex < size && compare(heap[rightChildIndex], heap[extreme])) {
      extreme = rightChildIndex;
    }

    if (extreme !== index) {
      swap(index, extreme);
      heapifyDown(extreme);
    }
  };

  const insert = (value) => {
    heap.push(value);
    heapifyUp(size);
    size++;
  };

  const extract = () => {
    if (isEmpty()) return null;
    if (size === 1) {
      size--;
      return heap.pop();
    }
    const root = heap[0];
    heap[0] = heap.pop();
    size--;
    heapifyDown(0);
    return root;
  };

  const peek = () => (isEmpty() ? null : heap[0]);
  const isEmpty = () => size === 0;
  const getSize = () => size;
    const toArray = () => {
        const sortedArray = [];
        const tempHeap = HeapObject(type); // Create a new heap object
        tempHeap.heap = [...heap]; // Copy the heap
        tempHeap.size = size;

        while (!tempHeap.isEmpty()) {
            sortedArray.push(tempHeap.extract());
        }
        return sortedArray;
    };
  const clear = () => {
    heap.length = 0;
    size = 0;
  };

  return {
    heap, // Expose for inspection, not usually recommended for direct manipulation
    insert,
    extract,
    peek,
    isEmpty,
    getSize,
        toArray,
    clear,
  };
};

// Example usage:
console.log("4. Min/Max Heap Using an Object");
const minHeapObj = HeapObject('min');
minHeapObj.insert(5);
minHeapObj.insert(10);
minHeapObj.insert(3);
minHeapObj.insert(12);
minHeapObj.insert(1);
console.log("Min Heap (Object):", minHeapObj.heap);
console.log("Peek (Object):", minHeapObj.peek());
console.log("Extract (Object):", minHeapObj.extract());
console.log("Min Heap after extract (Object):", minHeapObj.heap);
console.log("Size (Object):", minHeapObj.getSize());
console.log("Is Empty (Object):", minHeapObj.isEmpty());
console.log("Sorted Array (Object):", minHeapObj.toArray());

const maxHeapObj = HeapObject('max');
maxHeapObj.insert(5);
maxHeapObj.insert(10);
maxHeapObj.insert(3);
maxHeapObj.insert(12);
maxHeapObj.insert(1);
console.log("Max Heap (Object):", maxHeapObj.heap);
console.log("Peek (Object):", maxHeapObj.peek());
console.log("Extract (Object):", maxHeapObj.extract());
console.log("Max Heap after extract (Object):", maxHeapObj.heap);
console.log("Size (Object):", maxHeapObj.getSize());
console.log("Sorted Array (Object):", maxHeapObj.toArray());
console.log("================================================================================================\n");

// =================================================================================================
// 5. Min/Max Heap Using a Library (e.g., js-heap) - Demonstration
// =================================================================================================
// Note: This requires the 'js-heap' library.  For this example to run
// in this environment, we'll skip the import and assume it's globally available
// (which is NOT the standard way to use libraries in modern JS).
// In a real project, you would:
// 1. Install the library: `npm install js-heap`
// 2. Import it: `const { MinHeap, MaxHeap } = require('js-heap');`
// For this example, we'll define MinHeap and MaxHeap directly for demonstration.

// Mock js-heap classes for demonstration purposes.  This is NOT how you'd
// use the library in a real project.
class MinHeap {
    constructor(arr = []) {
        this.heap = [...arr];
        this.init();
    }

    init() {
      for (let i = Math.floor(this.heap.length / 2) - 1; i >= 0; i--) {
        this.heapifyDown(i);
      }
    }

    heapifyDown(index) {
        let smallest = index;
        const left = 2 * index + 1;
        const right = 2 * index + 2;

        if (left < this.heap.length && this.heap[left] < this.heap[smallest]) {
            smallest = left;
        }

        if (right < this.heap.length && this.heap[right] < this.heap[smallest]) {
            smallest = right;
        }

        if (smallest !== index) {
            [this.heap[index], this.heap[smallest]] = [this.heap[smallest], this.heap[index]];
            this.heapifyDown(smallest);
        }
    }
    push(value) {
        this.heap.push(value);
        this.heapifyUp(this.heap.length - 1);
    }

    heapifyUp(index) {
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

    pop() {
        if (this.isEmpty()) return undefined;
        if (this.heap.length === 1) return this.heap.pop();
        const min = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.heapifyDown(0);
        return min;
    }

    peek() {
        return this.isEmpty() ? undefined : this.heap[0];
    }

    isEmpty() {
        return this.heap.length === 0;
    }

    size() {
        return this.heap.length;
    }
    toArray() {
      return [...this.heap].sort((a,b) => a-b);
    }
    clear() {
      this.heap = [];
    }
}

class MaxHeap {
  constructor(arr = []) {
        this.heap = [...arr];
        this.init();
    }

    init() {
      for (let i = Math.floor(this.heap.length / 2) - 1; i >= 0; i--) {
        this.heapifyDown(i);
      }
    }

    heapifyDown(index) {
        let largest = index;
        const left = 2 * index + 1;
        const right = 2 * index + 2;

        if (left < this.heap.length && this.heap[left] > this.heap[largest]) {
            largest = left;
        }

        if (right < this.heap.length && this.heap[right] > this.heap[largest]) {
            largest = right;
        }

        if (largest !== index) {
            [this.heap[index], this.heap[largest]] = [this.heap[largest], this.heap[index]];
            this.heapifyDown(largest);
        }
    }

    push(value) {
        this.heap.push(value);
        this.heapifyUp(this.heap.length - 1);
    }

    heapifyUp(index) {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.heap[index] > this.heap[parentIndex]) {
                [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    pop() {if (this.isEmpty()) return undefined;
        if (this.heap.length === 1) return this.heap.pop();
        const max = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.heapifyDown(0);
        return max;
    }

    peek() {
        return this.isEmpty() ? undefined : this.heap[0];
    }

    isEmpty() {
        return this.heap.length === 0;
    }

    size() {
        return this.heap.length;
    }
    toArray() {
      return [...this.heap].sort((a,b) => b-a);
    }
    clear() {
      this.heap = [];
    }
}


console.log("5. Min/Max Heap Using a Library (js-heap - Demonstration)");
// Min Heap
const minHeapLib = new MinHeap();
minHeapLib.push(5);
minHeapLib.push(10);
minHeapLib.push(3);
minHeapLib.push(12);
minHeapLib.push(1);
console.log("Min Heap (Library):", minHeapLib.heap);
console.log("Peek (Library):", minHeapLib.peek());
console.log("Extract (Library):", minHeapLib.pop());
console.log("Min Heap after extract (Library):", minHeapLib.heap);
console.log("Size (Library):", minHeapLib.size());
console.log("Is Empty (Library):", minHeapLib.isEmpty());
console.log("Sorted Array (Library):", minHeapLib.toArray());


// Max Heap
const maxHeapLib = new MaxHeap();
maxHeapLib.push(5);
maxHeapLib.push(10);
maxHeapLib.push(3);
maxHeapLib.push(12);
maxHeapLib.push(1);
console.log("Max Heap (Library):", maxHeapLib.heap);
console.log("Peek (Library):", maxHeapLib.peek());
console.log("Extract (Library):", maxHeapLib.pop());
console.log("Max Heap after extract (Library):", maxHeapLib.heap);
console.log("Size (Library):", maxHeapLib.size());
console.log("Is Empty (Library):", maxHeapLib.isEmpty());
console.log("Sorted Array (Library):", maxHeapLib.toArray());
console.log("================================================================================================");

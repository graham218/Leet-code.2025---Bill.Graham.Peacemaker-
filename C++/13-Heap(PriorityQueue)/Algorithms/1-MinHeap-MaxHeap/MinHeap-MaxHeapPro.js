// Heap (Priority Queue) Implementation in JavaScript
// Min Heap and Max Heap

// =================================================================================================
// 1. Basic Min Heap Implementation (Array-Based)
// =================================================================================================
class MinHeapBasic {
  constructor() {
    this.heap = [];
  }

  getMin() {
    return this.heap[0];
  }

  size() {
    return this.heap.length;
  }

  isEmpty() {
    return this.size() === 0;
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

  extractMin() {
    if (this.isEmpty()) return null;
    this.swap(0, this.heap.length - 1);
    const min = this.heap.pop();
    this.bubbleDown(0);
    return min;
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }

  printHeap() {
    console.log("Min Heap (Basic):", this.heap);
  }
}

// Example Usage (Basic Min Heap)
const minHeapBasic = new MinHeapBasic();
minHeapBasic.insert(5);
minHeapBasic.insert(10);
minHeapBasic.insert(3);
minHeapBasic.insert(12);
minHeapBasic.insert(1);
minHeapBasic.printHeap(); // Output: [ 1, 3, 5, 12, 10 ]
console.log("Min Value:", minHeapBasic.extractMin()); // Output: 1
minHeapBasic.printHeap(); // Output: [ 3, 5, 10, 12 ]

// =================================================================================================
// 2. Basic Max Heap Implementation (Array-Based)
// =================================================================================================
class MaxHeapBasic {
  constructor() {
    this.heap = [];
  }

  getMax() {
    return this.heap[0];
  }

  size() {
    return this.heap.length;
  }

  isEmpty() {
    return this.size() === 0;
  }

  insert(value) {
    this.heap.push(value);
    this.bubbleUp(this.heap.length - 1);
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index] <= this.heap[parentIndex]) break; // Changed comparison for Max Heap
      this.swap(index, parentIndex);
      index = parentIndex;
    }
  }

  bubbleDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let largest = index; // Changed variable name

      if (leftChild < this.heap.length && this.heap[leftChild] > this.heap[largest]) { // Changed comparison
        largest = leftChild;
      }

      if (rightChild < this.heap.length && this.heap[rightChild] > this.heap[largest]) { // Changed comparison
        largest = rightChild;
      }

      if (largest === index) break;

      this.swap(index, largest);
      index = largest;
    }
  }

  extractMax() { // Changed method name
    if (this.isEmpty()) return null;
    this.swap(0, this.heap.length - 1);
    const max = this.heap.pop(); // Changed variable name
    this.bubbleDown(0);
    return max; // Changed variable name
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }

  printHeap() {
    console.log("Max Heap (Basic):", this.heap);
  }
}

// Example Usage (Basic Max Heap)
const maxHeapBasic = new MaxHeapBasic();
maxHeapBasic.insert(5);
maxHeapBasic.insert(10);
maxHeapBasic.insert(3);
maxHeapBasic.insert(12);
maxHeapBasic.insert(1);
maxHeapBasic.printHeap();
console.log("Max Value:", maxHeapBasic.extractMax());
maxHeapBasic.printHeap();

// =================================================================================================
// 3. Min Heap with Priority (Object-Based)
// =================================================================================================
class PriorityQueueMin {
  constructor() {
    this.heap = [];
  }

  getMin() {
    return this.heap[0];
  }

  size() {
    return this.heap.length;
  }

  isEmpty() {
    return this.size() === 0;
  }

  insert(value, priority) {
    this.heap.push({ value, priority });
    this.bubbleUp(this.heap.length - 1);
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

  extractMin() {
    if (this.isEmpty()) return null;
    this.swap(0, this.heap.length - 1);
    const min = this.heap.pop();
    this.bubbleDown(0);
    return min.value; // Return only the value, not the whole object.
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }

    printHeap() {
        console.log("Min Heap with Priority:", this.heap);
    }
}

// Example Usage (Min Heap with Priority)
const priorityQueueMin = new PriorityQueueMin();
priorityQueueMin.insert("Task A", 3);
priorityQueueMin.insert("Task B", 1);
priorityQueueMin.insert("Task C", 2);
priorityQueueMin.insert("Task D", 1);
priorityQueueMin.printHeap();
console.log("Next Task:", priorityQueueMin.extractMin()); // Output: "Task B"
priorityQueueMin.printHeap();

// =================================================================================================
// 4. Max Heap with Priority (Object-Based)
// =================================================================================================
class PriorityQueueMax {
  constructor() {
    this.heap = [];
  }

  getMax() {
    return this.heap[0];
  }

  size() {
    return this.heap.length;
  }

  isEmpty() {
    return this.size() === 0;
  }

  insert(value, priority) {
    this.heap.push({ value, priority });
    this.bubbleUp(this.heap.length - 1);
  }

  bubbleUp(index) {
    while (index > 0) {
      const parentIndex = Math.floor((index - 1) / 2);
      if (this.heap[index].priority <= this.heap[parentIndex].priority) break; // Changed comparison for Max Heap
      this.swap(index, parentIndex);
      index = parentIndex;
    }
  }

  bubbleDown(index) {
    while (true) {
      const leftChild = 2 * index + 1;
      const rightChild = 2 * index + 2;
      let largest = index;

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

  extractMax() {
    if (this.isEmpty()) return null;
    this.swap(0, this.heap.length - 1);
    const max = this.heap.pop();
    this.bubbleDown(0);
    return max.value;
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }

    printHeap() {
        console.log("Max Heap with Priority:", this.heap);
    }
}

// Example Usage (Max Heap with Priority)
const priorityQueueMax = new PriorityQueueMax();
priorityQueueMax.insert("Urgent Task A", 3);
priorityQueueMax.insert("Normal Task B", 1);
priorityQueueMax.insert("Important Task C", 2);
priorityQueueMax.insert("Urgent Task D", 3);
priorityQueueMax.printHeap();
console.log("Next Task:", priorityQueueMax.extractMax());
priorityQueueMax.printHeap();

// =================================================================================================
// 5.  Using a Library (For Demonstration -  js-priority-queue)
// =================================================================================================
//  Note:  For this example, you would typically install the library
//  using npm:  npm install js-priority-queue
//  Then import it:  const PriorityQueue = require('js-priority-queue');
//  Since this is a constrained environment, I'll simulate a simplified version.

class PriorityQueue {
  constructor(options = {}) {
      this.heap = [];
      this.comparator = options.comparator || ((a, b) => a - b); // Default to min heap
  }

    enqueue(item, priority) {
        this.heap.push({item, priority});
        this.bubbleUp(this.heap.length - 1);
    }

    dequeue() {
        if (this.isEmpty()) return undefined;
        this.swap(0, this.heap.length-1);
        const dequeued = this.heap.pop();
        this.bubbleDown(0);
        return dequeued.item;
    }

  peek() {
    return this.isEmpty() ? undefined : this.heap[0].item;
  }

  isEmpty() {
      return this.heap.length === 0;
  }

    size() {
        return this.heap.length;
    }

    bubbleUp(index) {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.comparator(this.heap[index].priority, this.heap[parentIndex].priority) >= 0) break;
            this.swap(index, parentIndex);
            index = parentIndex;
        }
    }

    bubbleDown(index) {
        while(true) {
            const leftChild = 2 * index + 1;
            const rightChild = 2 * index + 2;
            let target = index;

            if (leftChild < this.heap.length && this.comparator(this.heap[leftChild].priority, this.heap[target].priority) < 0) {
                target = leftChild;
            }
             if (rightChild < this.heap.length && this.comparator(this.heap[rightChild].priority, this.heap[target].priority) < 0) {
                target = rightChild;
            }
            if (target === index) break;
            this.swap(index, target);
            index = target;
        }
    }

    swap(i, j) {
        [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
    }

    printHeap() {
        console.log("Priority Queue (Library):", this.heap);
    }
}

// Example Usage (js-priority-queue - Simulated)
const pq = new PriorityQueue({ comparator: (a, b) => a - b }); // Min Heap
pq.enqueue("Low Priority", 3);
pq.enqueue("High Priority", 1);
pq.enqueue("Medium Priority", 2);
pq.enqueue("Another High Priority", 1);
pq.printHeap();
console.log("Next from PQ:", pq.dequeue());

const pqMax = new PriorityQueue({ comparator: (a, b) => b - a }); // Max Heap
pqMax.enqueue("Low Priority", 3);
pqMax.enqueue("High Priority", 1);
pqMax.enqueue("Medium Priority", 2);
pqMax.enqueue("Another High Priority", 1);
pqMax.printHeap();
console.log("Next from PQ (Max):", pqMax.dequeue());

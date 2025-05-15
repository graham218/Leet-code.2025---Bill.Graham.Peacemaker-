import java.util.*;
import java.lang.*;

// Class to demonstrate different Heap implementations in Java
public class HeapImplementations {

    // =========================================================================
    // 1.  Using Java's built-in PriorityQueue (Min Heap by default)
    // =========================================================================
    //    * This is the simplest and most common approach for general use.
    //    * It's backed by a min-heap implementation.
    //    * Good for: Task scheduling, finding the smallest/largest element,
    //        and when you need a basic priority queue.
    //
    // Example Use Case:
    //    * A hospital emergency room where patients are prioritized based on
    //        the severity of their condition (lower value means higher priority).
    public static void priorityQueueDemo() {
        System.out.println("\n1. Using Java's built-in PriorityQueue (Min Heap):");
        // Create a PriorityQueue of Integers (defaults to Min Heap)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        // Add elements (patient priorities)
        minHeap.add(3);  // Patient with priority 3 (e.g., minor injury)
        minHeap.add(1);  // Patient with priority 1 (e.g., critical condition)
        minHeap.add(4);  // Patient with priority 4 (e.g., stable)
        minHeap.add(2);  // Patient with priority 2 (e.g., serious condition)

        // Peek and print the highest priority patient (lowest number)
        System.out.println("Highest priority patient: " + minHeap.peek()); // Output: 1

        // Process patients in order of priority (remove and print)
        System.out.print("Processing patients: ");
        while (!minHeap.isEmpty()) {
            System.out.print(minHeap.poll() + " "); // Output: 1 2 3 4
        }
        System.out.println();
    }

    // =========================================================================
    // 2.  Using PriorityQueue as a Max Heap
    // =========================================================================
    //    * To create a Max Heap, provide a custom Comparator to the PriorityQueue.
    //    * The Comparator reverses the natural ordering of the elements.
    //    * Good for: Finding the largest elements, implementing Max Priority Queues.
    //
    // Example Use Case:
    //    * Finding the top-N most frequent items in a stream of data (e.g.,
    //        top 10 most visited websites).
    public static void maxHeapDemo() {
        System.out.println("\n2. Using PriorityQueue as a Max Heap:");
        // Create a PriorityQueue with a custom comparator for Max Heap
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());

        // Add elements
        maxHeap.add(10);
        maxHeap.add(30);
        maxHeap.add(20);
        maxHeap.add(40);
        maxHeap.add(50);

        // Peek and print the largest element
        System.out.println("Largest element: " + maxHeap.peek()); // Output: 50

        // Remove and print elements in descending order
        System.out.print("Elements in descending order: ");
        while (!maxHeap.isEmpty()) {
            System.out.print(maxHeap.poll() + " "); // Output: 50 40 30 20 10
        }
        System.out.println();
    }


    // =========================================================================
    // 3.  Implementing a Min Heap from scratch using an Array
    // =========================================================================
    //    * This approach provides more control over the heap implementation.
    //    * Useful for understanding the underlying data structure.
    //    * Good for: Educational purposes, specific performance tuning if needed.
    //
    // Example Use Case:
    //     * Implementing a custom memory management system.  While Java has
    //        its own GC, you might use a heap in a lower-level system.
    public static class MinHeap {
        private int[] heap;
        private int size;
        private int capacity;

        public MinHeap(int capacity) {
            this.capacity = capacity;
            this.size = 0;
            this.heap = new int[capacity];
        }

        // Helper Methods
        private int getParentIndex(int index) { return (index - 1) / 2; }
        private int getLeftChildIndex(int index) { return (index * 2) + 1; }
        private int getRightChildIndex(int index) { return (index * 2) + 2; }

        private boolean hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
        private boolean hasRightChild(int index) { return getRightChildIndex(index) < size; }
        private boolean hasParent(int index) { return getParentIndex(index) >= 0; }

        private int leftChild(int index) { return heap[getLeftChildIndex(index)]; }
        private int rightChild(int index) { return heap[getRightChildIndex(index)]; }
        private int parent(int index) { return heap[getParentIndex(index)]; }

        private void swap(int index1, int index2) {
            int temp = heap[index1];
            heap[index1] = heap[index2];
            heap[index2] = temp;
        }

        private void ensureCapacity() {
            if (size == capacity) {
                heap = Arrays.copyOf(heap, capacity * 2);
                capacity *= 2;
            }
        }

        // Core Heap Operations
        public void add(int item) {
            ensureCapacity();
            heap[size] = item;
            size++;
            heapifyUp();
        }

        public int peek() {
            if (size == 0) throw new IllegalStateException("Heap is empty");
            return heap[0];
        }

        public int poll() {
            if (size == 0) throw new IllegalStateException("Heap is empty");
            int item = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapifyDown();
            return item;
        }

        // Heapify Methods
        private void heapifyUp() {
            int index = size - 1;
            while (hasParent(index) && parent(index) > heap[index]) {
                swap(index, getParentIndex(index));
                index = getParentIndex(index);
            }
        }

        private void heapifyDown() {
            int index = 0;
            while (hasLeftChild(index)) {
                int smallerChildIndex = getLeftChildIndex(index);
                if (hasRightChild(index) && rightChild(index) < leftChild(index)) {
                    smallerChildIndex = getRightChildIndex(index);
                }

                if (heap[index] < heap[smallerChildIndex]) {
                    break;
                } else {
                    swap(index, smallerChildIndex);
                }
                index = smallerChildIndex;
            }
        }
        public void displayHeap() {
            if (size == 0) {
                System.out.println("Heap is empty.");
                return;
            }
            System.out.print("Heap elements: ");
            for (int i = 0; i < size; i++) {
                System.out.print(heap[i] + " ");
            }
            System.out.println();
        }
    }

    public static void customMinHeapDemo() {
        System.out.println("\n3. Implementing a Min Heap from scratch using an Array:");
        MinHeap minHeap = new MinHeap(10); // Initial capacity of 10

        minHeap.add(5);
        minHeap.add(3);
        minHeap.add(8);
        minHeap.add(1);
        minHeap.add(6);
        minHeap.displayHeap(); //Added display

        System.out.println("Peek: " + minHeap.peek()); // Output: 1
        System.out.println("Poll: " + minHeap.poll()); // Output: 1
        System.out.println("Poll: " + minHeap.poll());
        minHeap.displayHeap();
    }

    // =========================================================================
    // 4. Implementing a Max Heap from scratch using an Array
    // =========================================================================
    //    * Similar to the Min Heap implementation, but with modified heapify methods.
    //    * Good for: Scenarios where a Max Heap is specifically required and
    //        you want to avoid the overhead of using `Collections.reverseOrder()`.
    //
    // Example Use Case:
    //    * Implementing a custom caching mechanism where you want to evict the
    //        least recently used items, and you need to quickly access the maximum
    //        value (e.g., for prioritizing which items to keep).
    public static class MaxHeap {
        private int[] heap;
        private int size;
        private int capacity;

        public MaxHeap(int capacity) {
            this.capacity = capacity;
            this.size = 0;
            this.heap = new int[capacity];
        }

        // Helper Methods
        private int getParentIndex(int index) { return (index - 1) / 2; }
        private int getLeftChildIndex(int index) { return (index * 2) + 1; }
        private int getRightChildIndex(int index) { return (index * 2) + 2; }

        private boolean hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
        private boolean hasRightChild(int index) { return getRightChildIndex(index) < size; }
        private boolean hasParent(int index) { return getParentIndex(index) >= 0; }

        private int leftChild(int index) { return heap[getLeftChildIndex(index)]; }
        private int rightChild(int index) { return heap[getRightChildIndex(index)]; }
        private int parent(int index) { return heap[getParentIndex(index)]; }

        private void swap(int index1, int index2) {
            int temp = heap[index1];
            heap[index1] = heap[index2];
            heap[index2] = temp;
        }

        private void ensureCapacity() {
            if (size == capacity) {
                heap = Arrays.copyOf(heap, capacity * 2);
                capacity *= 2;
            }
        }

        // Core Heap Operations
        public void add(int item) {
            ensureCapacity();
            heap[size] = item;
            size++;
            heapifyUp();
        }

        public int peek() {
            if (size == 0) throw new IllegalStateException("Heap is empty");
            return heap[0];
        }

        public int poll() {
            if (size == 0) throw new IllegalStateException("Heap is empty");
            int item = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapifyDown();
            return item;
        }

        // Heapify Methods (Modified for Max Heap)
        private void heapifyUp() {
            int index = size - 1;
            while (hasParent(index) && parent(index) < heap[index]) { // Changed to < for Max Heap
                swap(index, getParentIndex(index));
                index = getParentIndex(index);
            }
        }

        private void heapifyDown() {
            int index = 0;
            while (hasLeftChild(index)) {
                int largerChildIndex = getLeftChildIndex(index); // Changed variable name
                if (hasRightChild(index) && rightChild(index) > leftChild(index)) { // Changed to >
                    largerChildIndex = getRightChildIndex(index);
                }

                if (heap[index] > heap[largerChildIndex]) { // Changed to >
                    break;
                } else {
                    swap(index, largerChildIndex);
                }
                index = largerChildIndex;
            }
        }

        public void displayHeap() {
            if (size == 0) {
                System.out.println("Heap is empty.");
                return;
            }
            System.out.print("Heap elements: ");
            for (int i = 0; i < size; i++) {
                System.out.print(heap[i] + " ");
            }
            System.out.println();
        }
    }

    public static void customMaxHeapDemo() {
        System.out.println("\n4. Implementing a Max Heap from scratch using an Array:");
        MaxHeap maxHeap = new MaxHeap(10);

        maxHeap.add(5);
        maxHeap.add(3);
        maxHeap.add(8);
        maxHeap.add(1);
        maxHeap.add(6);
        maxHeap.displayHeap();

        System.out.println("Peek: " + maxHeap.peek());
        System.out.println("Poll: " + maxHeap.poll());
        System.out.println("Poll: " + maxHeap.poll());
        maxHeap.displayHeap();
    }

    // =========================================================================
    // 5. Using a Library (Apache Commons Collections) - Deprecated, but for reference
    // =========================================================================
    //    * The `PriorityQueue` in Apache Commons Collections 3 is deprecated
    //    * This example is for historical/reference purposes.  Prefer Java's built-in `PriorityQueue`.
    //    * Good for:  Legacy codebases that might still use it.  New code should use
    //        java.util.PriorityQueue.
    //
    // Example Use Case:
    //    * Maintaining compatibility with older systems that rely on this library.
    //
    public static void deprecatedLibraryDemo() {
        System.out.println("\n5. Using a Library (Apache Commons Collections - Deprecated):");
        System.out.println("   This example uses a deprecated library.  Use java.util.PriorityQueue instead.");

        // In a real project, you'd need the Apache Commons Collections library.
        // Since it's deprecated, we'll just show the *intended* usage (which won't compile).
        //
        //  PriorityQueue<Integer> deprecatedQueue = new PriorityQueue<>(); // Deprecated class
        //  deprecatedQueue.add(5);
        //  deprecatedQueue.add(1);
        //  System.out.println("Peek (Deprecated): " + deprecatedQueue.peek());
        //
        //  The correct way is:
        PriorityQueue<Integer> correctQueue = new PriorityQueue<>();
        correctQueue.add(5);
        correctQueue.add(1);
        System.out.println("Peek (Correct): " + correctQueue.peek());

    }

    // Main method to run all demonstrations
    public static void main(String[] args) {
        priorityQueueDemo();
        maxHeapDemo();
        customMinHeapDemo();
        customMaxHeapDemo();
        deprecatedLibraryDemo();
    }
}


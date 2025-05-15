import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Comparator;

public class HeapImplementation {

    // Approach 1: Using Java's built-in PriorityQueue (Min Heap by default)
    public static class Approach1 {
        public static void demonstrate() {
            System.out.println("\nApproach 1: Using Java's built-in PriorityQueue (Min Heap)");
            // Creates a min heap
            PriorityQueue<Integer> minHeap = new PriorityQueue<>();

            // Insert elements
            minHeap.add(5);
            minHeap.add(10);
            minHeap.add(3);
            minHeap.add(8);
            minHeap.add(1);

            // Peek and print the minimum element
            System.out.println("Minimum element: " + minHeap.peek()); // Output: 1

            // Poll (remove) and print elements in sorted order (ascending for min heap)
            System.out.print("Elements in ascending order: ");
            while (!minHeap.isEmpty()) {
                System.out.print(minHeap.poll() + " "); // Output: 1 3 5 8 10
            }
            System.out.println();
        }
    }

    // Approach 2: Using Java's built-in PriorityQueue (Max Heap using Comparator)
    public static class Approach2 {
        public static void demonstrate() {
            System.out.println("\nApproach 2: Using Java's built-in PriorityQueue (Max Heap)");
            // Creates a max heap using a custom comparator
            PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());

            // Insert elements
            maxHeap.add(5);
            maxHeap.add(10);
            maxHeap.add(3);
            maxHeap.add(8);
            maxHeap.add(1);

            // Peek and print the maximum element
            System.out.println("Maximum element: " + maxHeap.peek()); // Output: 10

            // Poll (remove) and print elements in sorted order (descending for max heap)
            System.out.print("Elements in descending order: ");
            while (!maxHeap.isEmpty()) {
                System.out.print(maxHeap.poll() + " "); // Output: 10 8 5 3 1
            }
            System.out.println();
        }
    }

    // Approach 3: Implementing a Min Heap from scratch using an ArrayList
    public static class Approach3 {

        public static class MinHeap {
            private List<Integer> heap;

            public MinHeap() {
                this.heap = new ArrayList<>();
            }

            // Helper method to get the parent index
            private int getParent(int index) {
                return (index - 1) / 2;
            }

            // Helper method to get the left child index
            private int getLeftChild(int index) {
                return 2 * index + 1;
            }

            // Helper method to get the right child index
            private int getRightChild(int index) {
                return 2 * index + 2;
            }

            // Helper method to swap two elements
            private void swap(int i, int j) {
                int temp = heap.get(i);
                heap.set(i, heap.get(j));
                heap.set(j, temp);
            }

            // Method to insert a new element into the heap
            public void insert(int value) {
                heap.add(value);
                int index = heap.size() - 1;
                // Maintain heap property (min heap)
                while (index > 0 && heap.get(index) < heap.get(getParent(index))) {
                    swap(index, getParent(index));
                    index = getParent(index);
                }
            }

            // Method to remove the minimum element from the heap
            public Integer remove() {
                if (heap.isEmpty()) {
                    return null; // Or throw an exception: throw new NoSuchElementException("Heap is empty");
                }
                if (heap.size() == 1) {
                    return heap.remove(0);
                }

                int root = heap.get(0);
                heap.set(0, heap.get(heap.size() - 1)); // Move the last element to the root
                heap.remove(heap.size() - 1);         // Remove the last element
                minHeapify(0);                   // Restore the min heap property
                return root;
            }

            // Method to maintain the min heap property (downward)
            private void minHeapify(int index) {
                int left = getLeftChild(index);
                int right = getRightChild(index);
                int smallest = index;

                if (left < heap.size() && heap.get(left) < heap.get(smallest)) {
                    smallest = left;
                }
                if (right < heap.size() && heap.get(right) < heap.get(smallest)) {
                    smallest = right;
                }

                if (smallest != index) {
                    swap(index, smallest);
                    minHeapify(smallest);
                }
            }

            // Method to peek the minimum element
            public Integer peek() {
                if (heap.isEmpty()) {
                    return null;
                }
                return heap.get(0);
            }

            public boolean isEmpty() {
                return heap.isEmpty();
            }
        }

        public static void demonstrate() {
            System.out.println("\nApproach 3: Implementing a Min Heap from scratch using an ArrayList");
            MinHeap minHeap = new MinHeap();

            minHeap.insert(5);
            minHeap.insert(10);
            minHeap.insert(3);
            minHeap.insert(8);
            minHeap.insert(1);

            System.out.println("Minimum element: " + minHeap.peek());

            System.out.print("Elements in ascending order: ");
            while (!minHeap.isEmpty()) {
                System.out.print(minHeap.remove() + " ");
            }
            System.out.println();
        }
    }

    // Approach 4: Implementing a Max Heap from scratch using an ArrayList
    public static class Approach4 {

        public static class MaxHeap {
            private List<Integer> heap;

            public MaxHeap() {
                this.heap = new ArrayList<>();
            }

            private int getParent(int index) {
                return (index - 1) / 2;
            }

            private int getLeftChild(int index) {
                return 2 * index + 1;
            }

            private int getRightChild(int index) {
                return 2 * index + 2;
            }

            private void swap(int i, int j) {
                int temp = heap.get(i);
                heap.set(i, heap.get(j));
                heap.set(j, temp);
            }

            public void insert(int value) {
                heap.add(value);
                int index = heap.size() - 1;
                while (index > 0 && heap.get(index) > heap.get(getParent(index))) {
                    swap(index, getParent(index));
                    index = getParent(index);
                }
            }

            public Integer remove() {
                if (heap.isEmpty()) {
                    return null;
                }
                if (heap.size() == 1) {
                    return heap.remove(0);
                }
                int root = heap.get(0);
                heap.set(0, heap.get(heap.size() - 1));
                heap.remove(heap.size() - 1);
                maxHeapify(0);
                return root;
            }

            private void maxHeapify(int index) {
                int left = getLeftChild(index);
                int right = getRightChild(index);
                int largest = index;

                if (left < heap.size() && heap.get(left) > heap.get(largest)) {
                    largest = left;
                }
                if (right < heap.size() && heap.get(right) > heap.get(largest)) {
                    largest = right;
                }

                if (largest != index) {
                    swap(index, largest);
                    maxHeapify(largest);
                }
            }
            public Integer peek() {
                if (heap.isEmpty()) {
                    return null;
                }
                return heap.get(0);
            }

            public boolean isEmpty() {
                return heap.isEmpty();
            }
        }

        public static void demonstrate() {
            System.out.println("\nApproach 4: Implementing a Max Heap from scratch using an ArrayList");
            MaxHeap maxHeap = new MaxHeap();

            maxHeap.insert(5);
            maxHeap.insert(10);
            maxHeap.insert(3);
            maxHeap.insert(8);
            maxHeap.insert(1);

            System.out.println("Maximum element: " + maxHeap.peek());

            System.out.print("Elements in descending order: ");
            while (!maxHeap.isEmpty()) {
                System.out.print(maxHeap.remove() + " ");
            }
            System.out.println();
        }
    }

    // Approach 5: Using heapify to build a Min Heap from an unsorted array
    public static class Approach5 {
        public static void demonstrate() {
            System.out.println("\nApproach 5: Using heapify to build a Min Heap from an unsorted array");
            int[] arr = {5, 10, 3, 8, 1};
            buildMinHeap(arr);

            System.out.print("Elements after building Min Heap: ");
            for (int value : arr) {
                System.out.print(value + " ");
            }
            System.out.println();

            System.out.print("Elements in ascending order using heap sort: ");
            int[] sortedArray = heapSort(arr.clone()); // Clone to avoid modifying the original
            for(int value : sortedArray){
                System.out.print(value + " ");
            }
            System.out.println();
        }

        // Method to build a Min Heap from an unsorted array
        public static void buildMinHeap(int[] arr) {
            int n = arr.length;
            // Start from the last non-leaf node and heapify all preceding nodes
            for (int i = n / 2 - 1; i >= 0; i--) {
                minHeapify(arr, n, i);
            }
        }

        private static void minHeapify(int[] arr, int n, int i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && arr[left] < arr[smallest]) {
                smallest = left;
            }
            if (right < n && arr[right] < arr[smallest]) {
                smallest = right;
            }

            if (smallest != i) {
                swap(arr, i, smallest);
                minHeapify(arr, n, smallest);
            }
        }

        private static void swap(int[] arr, int i, int j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        public static int[] heapSort(int[] arr) {
            int n = arr.length;

            // Build min heap (in-place)
            buildMinHeap(arr);

            // Create a new array for the sorted result
            int[] sortedArray = new int[n];
            for (int i = 0; i < n; i++) {
                sortedArray[i] = removeMin(arr, n - i); // Remove min from heap and store in sortedArray
            }
            return sortedArray;
        }

        // Function to remove the minimum element from the heap (used in heap sort)
        private static int removeMin(int[] arr, int n) {
            int min = arr[0];
            arr[0] = arr[n - 1]; // Replace root with the last element in the (reduced) heap
            minHeapify(arr, n - 1, 0); // Heapify the root
            return min;
        }
    }

    public static void main(String[] args) {
        Approach1.demonstrate(); // Min Heap using PriorityQueue
        Approach2.demonstrate(); // Max Heap using PriorityQueue
        Approach3.demonstrate(); // Min Heap from scratch
        Approach4.demonstrate(); // Max Heap from scratch
        Approach5.demonstrate(); // Build Min Heap from unsorted array and Heap Sort
    }
}


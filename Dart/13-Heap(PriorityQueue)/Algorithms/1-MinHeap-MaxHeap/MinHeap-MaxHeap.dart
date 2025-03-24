// Dart solution demonstrating Min Heap and Max Heap using 5 different approaches
import 'dart:math';

void main() {
  minHeapWithSortedList();
  maxHeapWithSortedList();
  minHeapWithBinaryHeap();
  maxHeapWithBinaryHeap();
  customHeapImplementation();
}

// Approach 1: Min Heap using a sorted list
void minHeapWithSortedList() {
  List<int> minHeap = [5, 1, 3, 8, 2];
  minHeap.sort(); // Sorting maintains the heap property (for min heap in this case)

  print("Min Heap (Sorted List):");
  while (minHeap.isNotEmpty) {
    print(minHeap.removeAt(0)); // Remove the smallest element (first element after sort)
  }
}

// Approach 2: Max Heap using a sorted list
void maxHeapWithSortedList() {
  List<int> maxHeap = [5, 1, 3, 8, 2];
  maxHeap.sort((a, b) => b.compareTo(a)); // Sort in descending order for max heap

  print("Max Heap (Sorted List):");
  while (maxHeap.isNotEmpty) {
    print(maxHeap.removeAt(0)); // Remove the largest element (first element after sort)
  }
}

// Approach 3: Min Heap using manual binary heap operations
class BinaryMinHeap {
  List<int> heap = [];

  void insert(int value) {
    heap.add(value);
    heapifyUp(); // Maintain heap property after insertion
  }

  int remove() {
    if (heap.isEmpty) throw Exception("Heap is empty");
    if (heap.length == 1) return heap.removeLast(); // Only one element, just remove it
    int min = heap.first; // Get the minimum element
    heap[0] = heap.removeLast(); // Replace root with last element
    heapifyDown(); // Maintain heap property after removal
    return min;
  }

  void heapifyUp() {
    int index = heap.length - 1;
    while (index > 0) {
      int parent = (index - 1) ~/ 2; // Calculate parent index
      if (heap[index] >= heap[parent]) break; // If parent is smaller, heap property is maintained
      swap(index, parent); // Swap if child is smaller than parent
      index = parent; // Move up to the parent
    }
  }

  void heapifyDown() {
    int index = 0;
    while (2 * index + 1 < heap.length) { // While there is at least one child
      int smallerChild = 2 * index + 1; // Left child index
      if (smallerChild + 1 < heap.length && heap[smallerChild + 1] < heap[smallerChild]) {
        smallerChild++; // Right child is smaller, choose right child
      }
      if (heap[index] <= heap[smallerChild]) break; // If parent is smaller, heap property is maintained
      swap(index, smallerChild); // Swap if child is smaller than parent
      index = smallerChild; // Move down to the smaller child
    }
  }

  void swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
}

void minHeapWithBinaryHeap() {
  BinaryMinHeap minHeap = BinaryMinHeap();
  for (var value in [5, 1, 3, 8, 2]) {
    minHeap.insert(value);
  }
  print("Min Heap (Binary Heap):");
  while (minHeap.heap.isNotEmpty) {
    print(minHeap.remove());
  }
}

// Approach 4: Max Heap using manual binary heap operations
class BinaryMaxHeap {
  List<int> heap = [];

  void insert(int value) {
    heap.add(value);
    heapifyUp(); // Maintain heap property after insertion
  }

  int remove() {
    if (heap.isEmpty) throw Exception("Heap is empty");
    if (heap.length == 1) return heap.removeLast(); // Only one element, just remove it
    int max = heap.first; // Get the maximum element
    heap[0] = heap.removeLast(); // Replace root with last element
    heapifyDown(); // Maintain heap property after removal
    return max;
  }

  void heapifyUp() {
    int index = heap.length - 1;
    while (index > 0) {
      int parent = (index - 1) ~/ 2; // Calculate parent index
      if (heap[index] <= heap[parent]) break; // If parent is larger, heap property is maintained
      swap(index, parent); // Swap if child is larger than parent
      index = parent; // Move up to the parent
    }
  }

  void heapifyDown() {
    int index = 0;
    while (2 * index + 1 < heap.length) { // While there is at least one child
      int largerChild = 2 * index + 1; // Left child index
      if (largerChild + 1 < heap.length && heap[largerChild + 1] > heap[largerChild]) {
        largerChild++; // Right child is larger, choose right child
      }
      if (heap[index] >= heap[largerChild]) break; // If parent is larger, heap property is maintained
      swap(index, largerChild); // Swap if child is larger than parent
      index = largerChild; // Move down to the larger child
    }
  }

  void swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
}

void maxHeapWithBinaryHeap() {
  BinaryMaxHeap maxHeap = BinaryMaxHeap();
  for (var value in [5, 1, 3, 8, 2]) {
    maxHeap.insert(value);
  }
  print("Max Heap (Binary Heap):");
  while (maxHeap.heap.isNotEmpty) {
    print(maxHeap.remove());
  }
}

// Approach 5: Custom Heap Implementation using sort after each insert.
class CustomHeap {
  List<int> heap = [];
  bool isMinHeap;

  CustomHeap({this.isMinHeap = true});

  void insert(int value) {
    heap.add(value);
    heap.sort((a, b) => isMinHeap ? a.compareTo(b) : b.compareTo(a)); // Sort after each insert
  }

  int remove() => heap.isNotEmpty ? heap.removeAt(0) : throw Exception("Heap is empty"); // Remove first element
}

void customHeapImplementation() {
  CustomHeap minHeap = CustomHeap();
  for (var value in [5, 1, 3, 8, 2]) {
    minHeap.insert(value);
  }
  print("Custom Min Heap:");
  while (minHeap.heap.isNotEmpty) {
    print(minHeap.remove());
  }

  CustomHeap maxHeap = CustomHeap(isMinHeap: false);
  for (var value in [5, 1, 3, 8, 2]) {
    maxHeap.insert(value);
  }
  print("Custom Max Heap:");
  while (maxHeap.heap.isNotEmpty) {
    print(maxHeap.remove());
  }
}
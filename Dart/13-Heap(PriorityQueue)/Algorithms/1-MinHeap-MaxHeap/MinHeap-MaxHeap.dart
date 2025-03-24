// Min Heap Implementation
class MinHeap {
  // The list to store the heap elements.
  List<int> heap = [];

  // Adds a value to the min heap.
  void add(int val) {
    heap.add(val); // Add the new value to the end of the list.
    _heapifyUp(heap.length - 1); // Maintain heap property by moving the new element up.
  }

  // Removes and returns the minimum value from the heap.
  int removeFirst() {
    if (heap.isEmpty) return -1; // Return -1 if the heap is empty.
    int min = heap.first; // Store the minimum value (root).
    heap[0] = heap.removeLast(); // Replace the root with the last element and remove the last element.
    _heapifyDown(0); // Maintain heap property by moving the new root down.
    return min; // Return the original minimum value.
  }

  // Gets the first element (minimum) without removing it.
  int get first => heap.isNotEmpty ? heap.first : -1;

  // Gets the number of elements in the heap.
  int get length => heap.length;

  // Helper method to maintain min heap property while adding an element.
  void _heapifyUp(int index) {
    while (index > 0) {
      int parent = (index - 1) ~/ 2; // Calculate the parent's index.  ~/: Integer division
      if (heap[parent] <= heap[index]) break; // If parent is smaller or equal, heap property is satisfied.
      _swap(index, parent); // Otherwise, swap the node with its parent.
      index = parent; // Update the index to the parent's index to continue heapifying up.
    }
  }

  // Helper method to maintain min heap property while removing the root.
  void _heapifyDown(int index) {
    int leftChild, rightChild, smallest;
    while (index < heap.length ~/ 2) { // Continue as long as the node has at least one child.
      leftChild = 2 * index + 1; // Calculate the left child's index.
      rightChild = 2 * index + 2; // Calculate the right child's index.
      smallest = leftChild; // Assume the left child is the smallest.
      if (rightChild < heap.length && heap[rightChild] < heap[leftChild]) {
        smallest = rightChild; // If the right child is smaller, update smallest.
      }
      if (heap[index] <= heap[smallest]) break; // If the current node is smaller or equal to the smallest child, heap property is satisfied.
      _swap(index, smallest); // Otherwise, swap the node with the smallest child.
      index = smallest; // Update the index to the smallest child's index to continue heapifying down.
    }
  }

  // Helper method to swap two elements in the heap.
  void _swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
}

// Max Heap Implementation
class MaxHeap {
  // The list to store the heap elements.
  List<int> heap = [];

  // Adds a value to the max heap.
  void add(int val) {
    heap.add(val); // Add the new value to the end of the list.
    _heapifyUp(heap.length - 1); // Maintain heap property by moving the new element up.
  }

  // Removes and returns the maximum value from the heap.
  int removeFirst() {
    if (heap.isEmpty) return -1; // Return -1 if the heap is empty.
    int max = heap.first; // Store the maximum value (root).
    heap[0] = heap.removeLast(); // Replace the root with the last element and remove the last element.
    _heapifyDown(0); // Maintain heap property by moving the new root down.
    return max; // Return the original maximum value.
  }

  // Gets the first element (maximum) without removing it.
  int get first => heap.isNotEmpty ? heap.first : -1;

  // Gets the number of elements in the heap.
  int get length => heap.length;

  // Helper method to maintain max heap property while adding an element.
  void _heapifyUp(int index) {
    while (index > 0) {
      int parent = (index - 1) ~/ 2; // Calculate the parent's index.
      if (heap[parent] >= heap[index]) break; // If parent is larger or equal, heap property is satisfied.
      _swap(index, parent); // Otherwise, swap the node with its parent.
      index = parent; // Update the index to the parent's index to continue heapifying up.
    }
  }

  // Helper method to maintain max heap property while removing the root.
  void _heapifyDown(int index) {
    int leftChild, rightChild, largest;
    while (index < heap.length ~/ 2) { // Continue as long as the node has at least one child.
      leftChild = 2 * index + 1; // Calculate the left child's index.
      rightChild = 2 * index + 2; // Calculate the right child's index.
      largest = leftChild; // Assume the left child is the largest.
      if (rightChild < heap.length && heap[rightChild] > heap[leftChild]) {
        largest = rightChild; // If the right child is larger, update largest.
      }
      if (heap[index] >= heap[largest]) break; // If the current node is larger or equal to the largest child, heap property is satisfied.
      _swap(index, largest); // Otherwise, swap the node with the largest child.
      index = largest; // Update the index to the largest child's index to continue heapifying down.
    }
  }

  // Helper method to swap two elements in the heap.
  void _swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
}

// Approach 1: Using Sorting
// Finds the kth largest element by sorting the entire array.
int findKthLargestSorting(List<int> nums, int k) {
  nums.sort(); // Sort the array in ascending order.
  return nums[nums.length - k]; // The kth largest element is at index (length - k).
}

// Approach 2: Using a Min Heap
// Finds the kth largest element using a min heap.
int findKthLargestMinHeap(List<int> nums, int k) {
  MinHeap minHeap = MinHeap(); // Create a new min heap.
  for (var num in nums) {
    minHeap.add(num); // Add each number from the input array to the min heap.
    if (minHeap.length > k) {
      minHeap.removeFirst(); // If the heap size exceeds k, remove the smallest element.
    }
  }
  return minHeap.first; // The root of the min heap will be the kth largest element.
}

// Approach 3: Using a Max Heap
// Finds the kth largest element using a max heap.
int findKthLargestMaxHeap(List<int> nums, int k) {
  MaxHeap maxHeap = MaxHeap(); // Create a new max heap.
  maxHeap.heap.addAll(nums);
  maxHeap.heap.sort((a, b) => b.compareTo(a));
  return maxHeap.heap[k - 1];
}

// Approach 4: Quickselect Algorithm
// Finds the kth largest element using the Quickselect algorithm (efficient).
int quickSelect(List<int> nums, int k) {
  // Partition function to rearrange the array around a pivot.
  int partition(List<int> arr, int left, int right) {
    int pivot = arr[right]; // Choose the rightmost element as the pivot.
    int pIndex = left; // Index to track the position where elements greater than pivot should go.
    for (int i = left; i < right; i++) {
      if (arr[i] >= pivot) { // If the current element is greater than or equal to the pivot.
        int temp = arr[i]; // Swap arr[i] and arr[pIndex].
        arr[i] = arr[pIndex];
        arr[pIndex] = temp;
        pIndex++; // Increment pIndex to point to the next position for a larger element.
      }
    }
    arr[right] = arr[pIndex]; // Place the pivot in its correct position.
    arr[pIndex] = pivot;
    return pIndex; // Return the index of the pivot.
  }

  int left = 0, right = nums.length - 1; // Initialize left and right pointers.
  while (true) {
    int pivotIndex = partition(nums, left, right); // Partition the array.
    if (pivotIndex == k - 1) return nums[pivotIndex]; // If the pivot is at the kth position, we found the element.
    else if (pivotIndex < k - 1) left = pivotIndex + 1; // If pivot is too small, search in the right subarray.
    else right = pivotIndex - 1; // If pivot is too large, search in the left subarray.
  }
}

// Approach 5: Using Counting Sort (for small numbers range)
// Finds the kth largest element using counting sort (efficient for limited range).
int findKthLargestCountingSort(List<int> nums, int k) {
  int maxVal = nums.reduce((a, b) => a > b ? a : b); // Find the maximum value in the array.
  int minVal = nums.reduce((a, b) => a < b ? a : b); // Find the minimum value in the array.
  List<int> count = List.filled(maxVal - minVal + 1, 0); // Create a count array to store the frequency of each number.

  for (var num in nums) {
    count[num - minVal]++; // Increment the count for the corresponding number.
  }

  int remaining = k; // Initialize the remaining count.
  for (int i = count.length - 1; i >= 0; i--) { // Iterate from the largest number to the smallest.
    remaining -= count[i]; // Subtract the count of the current number from remaining.
    if (remaining <= 0) return i + minVal; // If remaining is 0 or negative, we found the kth largest element.
  }
  return -1; // Return -1 if k is invalid.
}

void main() {
  List<int> nums = [3, 2, 3, 1, 2, 4, 5, 5, 6];
  int k = 4;
  print("Sorting Approach: ${findKthLargestSorting(List.from(nums), k)}");
  print("Min Heap Approach: ${findKthLargestMinHeap(List.from(nums), k)}");
  print("Max Heap Approach: ${findKthLargestMaxHeap(List.from(nums), k)}");
  print("Quickselect Approach: ${quickSelect(List.from(nums), k)}");
  print("Counting Sort Approach: ${findKthLargestCountingSort(List.from(nums), k)}");
}

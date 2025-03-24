// Advanced Dart Solution for Finding Kth Largest Element
// Includes Six Different Approaches with Real-World Applications

import 'dart:math';

// Approach 1: Sorting (Simple but Inefficient for Large Datasets)
// Real-world use case: Sorting leaderboards, ranking athletes
int findKthLargestSorting(List<int> nums, int k) {
  nums.sort();
  return nums[nums.length - k];
}

// Approach 2: Min Heap (Efficient for Streaming Data)
// Real-world use case: Keeping track of top 'K' scores in live competitions
class MinHeap {
  List<int> heap = [];

  void add(int val) {
    heap.add(val);
    heap.sort();
  }

  void removeFirst() {
    if (heap.isNotEmpty) heap.removeAt(0);
  }

  int get first => heap.first;
  int get length => heap.length;
}

int findKthLargestMinHeap(List<int> nums, int k) {
  MinHeap minHeap = MinHeap();
  for (var num in nums) {
    minHeap.add(num);
    if (minHeap.length > k) {
      minHeap.removeFirst();
    }
  }
  return minHeap.first;
}

// Approach 3: Quickselect (Optimized for Large Datasets)
// Real-world use case: Finding median salaries in a company database
int quickSelect(List<int> nums, int k) {
  int partition(List<int> arr, int left, int right) {
    int pivot = arr[right];
    int pIndex = left;
    for (int i = left; i < right; i++) {
      if (arr[i] >= pivot) {
        int temp = arr[i];
        arr[i] = arr[pIndex];
        arr[pIndex] = temp;
        pIndex++;
      }
    }
    arr[right] = arr[pIndex];
    arr[pIndex] = pivot;
    return pIndex;
  }

  int left = 0, right = nums.length - 1;
  while (true) {
    int pivotIndex = partition(nums, left, right);
    if (pivotIndex == k - 1) return nums[pivotIndex];
    else if (pivotIndex < k - 1) left = pivotIndex + 1;
    else right = pivotIndex - 1;
  }
}

// Approach 4: Counting Sort (Only for Small Value Ranges)
// Real-world use case: Analyzing survey data with limited response options
int findKthLargestCountingSort(List<int> nums, int k) {
  int maxVal = nums.reduce(max);
  int minVal = nums.reduce(min);
  List<int> count = List.filled(maxVal - minVal + 1, 0);

  for (var num in nums) {
    count[num - minVal]++;
  }

  int remaining = k;
  for (int i = count.length - 1; i >= 0; i--) {
    remaining -= count[i];
    if (remaining <= 0) return i + minVal;
  }
  return -1;
}

// Approach 5: Bucket Sort (Optimized for Uniformly Distributed Data)
// Real-world use case: Optimizing search results ranking
int findKthLargestBucketSort(List<int> nums, int k) {
  Map<int, int> frequency = {};
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1;
  }
  List<int> sortedKeys = frequency.keys.toList()..sort((a, b) => b.compareTo(a));
  for (var key in sortedKeys) {
    k -= frequency[key]!;
    if (k <= 0) return key;
  }
  return -1;
}

// Approach 6: Using a Balanced BST (For Dynamic Data Processing)
// Real-world use case: Managing high-frequency stock price updates
// Simulated using a sorted list as Dart does not have a built-in balanced BST
int findKthLargestBST(List<int> nums, int k) {
  nums.sort((a, b) => b.compareTo(a)); // Simulate BST ordering
  return nums[k - 1];
}

void main() {
  List<int> nums = [10, 20, 15, 30, 25, 5, 35, 40, 45, 50];
  int k = 3;

  print("Sorting Approach: ${findKthLargestSorting(List.from(nums), k)}");
  print("Min Heap Approach: ${findKthLargestMinHeap(List.from(nums), k)}");
  print("Quickselect Approach: ${quickSelect(List.from(nums), k)}");
  print("Counting Sort Approach: ${findKthLargestCountingSort(List.from(nums), k)}");
  print("Bucket Sort Approach: ${findKthLargestBucketSort(List.from(nums), k)}");
  print("Balanced BST Approach: ${findKthLargestBST(List.from(nums), k)}");
}

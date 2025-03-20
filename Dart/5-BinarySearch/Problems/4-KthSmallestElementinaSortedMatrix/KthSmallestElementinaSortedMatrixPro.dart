// Dart Advanced Solution for 'Kth Smallest Element in a Sorted Matrix'
// 6 Different Approaches with Real-World Implementations & Detailed Comments
// Applications: AI Data Processing, Search Engines, Financial Risk Analysis, Medical Imaging

import 'dart:math';
import 'package:collection/collection.dart'; // Import for PriorityQueue

// 1. Brute Force Approach (Sorting) - O(n^2 log n)
// Used in Small-Scale Data Processing like Excel Sheets Sorting
int kthSmallestBruteForce(List<List<int>> matrix, int k) {
  List<int> flattened = matrix.expand((row) => row).toList();
  flattened.sort();
  return flattened[k - 1];
}

// 2. Min Heap Approach (Priority Queue) - O(k log n)
// Used in Search Engine Query Ranking
int kthSmallestMinHeap(List<List<int>> matrix, int k) {
  final minHeap = PriorityQueue<int>((a, b) => a.compareTo(b));
  for (var row in matrix) {
    for (var num in row) {
      minHeap.addAll([num]);
    }
  }
  for (int i = 1; i < k; i++) {
    minHeap.removeFirst();
  }
  return minHeap.first;
}

// 3. Max Heap (Streaming Large Datasets) - O(n^2 log k)
// Used in Financial Market Data Processing
int kthSmallestMaxHeap(List<List<int>> matrix, int k) {
  final maxHeap = PriorityQueue<int>((a, b) => b.compareTo(a));
  for (var row in matrix) {
    for (var num in row) {
      maxHeap.addAll([num]);
      if (maxHeap.length > k) {
        maxHeap.removeFirst();
      }
    }
  }
  return maxHeap.first;
}

// 4. Binary Search (Optimized for Sorted Matrices) - O(n log max-min)
// Used in Cybersecurity Threat Intelligence
int kthSmallestBinarySearch(List<List<int>> matrix, int k) {
  int n = matrix.length;
  int left = matrix[0][0], right = matrix[n - 1][n - 1];
  while (left < right) {
    int mid = left + (right - left) ~/ 2;
    int count = 0, j = n - 1;
    for (int i = 0; i < n; i++) {
      while (j >= 0 && matrix[i][j] > mid) {
        j--;
      }
      count += (j + 1);
    }
    if (count < k) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

// 5. Merge k Sorted Lists using Min Heap - O(k log n)
// Used in Real-Time Big Data Analytics
int kthSmallestMergeHeap(List<List<int>> matrix, int k) {
  final minHeap = PriorityQueue<List<int>>((a, b) => a[0].compareTo(b[0]));
  for (int i = 0; i < matrix.length; i++) {
    minHeap.addAll([
      [matrix[i][0], i, 0]
    ]);
  }
  while (k-- > 1) {
    List<int> smallest = minHeap.removeFirst();
    int row = smallest[1], col = smallest[2];
    if (col + 1 < matrix[row].length) {
      minHeap.addAll([
        [matrix[row][col + 1], row, col + 1]
      ]);
    }
  }
  return minHeap.first[0];
}

// 6. Quick Select (Partitioning) - O(n) on Average
// Used in AI Model Feature Selection
int quickSelect(List<int> arr, int left, int right, int k) {
  if (left == right) return arr[left];
  int pivotIndex = left + Random().nextInt(right - left + 1);
  int pivotValue = arr[pivotIndex];
  int storeIndex = left;
  arr[pivotIndex] = arr[right];
  arr[right] = pivotValue;
  for (int i = left; i < right; i++) {
    if (arr[i] < pivotValue) {
      int temp = arr[i];
      arr[i] = arr[storeIndex];
      arr[storeIndex] = temp;
      storeIndex++;
    }
  }
  arr[right] = arr[storeIndex];
  arr[storeIndex] = pivotValue;
  if (k == storeIndex) return arr[k];
  if (k < storeIndex) return quickSelect(arr, left, storeIndex - 1, k);
  return quickSelect(arr, storeIndex + 1, right, k);
}

int kthSmallestQuickSelect(List<List<int>> matrix, int k) {
  List<int> flattened = matrix.expand((row) => row).toList();
  return quickSelect(flattened, 0, flattened.length - 1, k - 1);
}

// Test Cases Demonstrating Real-World Applications
void main() {
  List<List<int>> matrix = [
    [1, 5, 9],
    [10, 11, 13],
    [12, 13, 15]
  ];
  int k = 5;

  print("Brute Force: ${kthSmallestBruteForce(matrix, k)}");
  print("Min Heap: ${kthSmallestMinHeap(matrix, k)}");
  print("Max Heap: ${kthSmallestMaxHeap(matrix, k)}");
  print("Binary Search: ${kthSmallestBinarySearch(matrix, k)}");
  print("Merge K Sorted Lists: ${kthSmallestMergeHeap(matrix, k)}");
  print("Quick Select: ${kthSmallestQuickSelect(matrix, k)}");

  matrix = [
    [1, 2],
    [1, 3]
  ];
  k = 2;

  print("\nBrute Force: ${kthSmallestBruteForce(matrix, k)}");
  print("Min Heap: ${kthSmallestMinHeap(matrix, k)}");
  print("Max Heap: ${kthSmallestMaxHeap(matrix, k)}");
  print("Binary Search: ${kthSmallestBinarySearch(matrix, k)}");
  print("Merge K Sorted Lists: ${kthSmallestMergeHeap(matrix, k)}");
  print("Quick Select: ${kthSmallestQuickSelect(matrix, k)}");

  matrix = [
    [5]
  ];
  k = 1;

  print("\nBrute Force: ${kthSmallestBruteForce(matrix, k)}");
  print("Min Heap: ${kthSmallestMinHeap(matrix, k)}");
  print("Max Heap: ${kthSmallestMaxHeap(matrix, k)}");
  print("Binary Search: ${kthSmallestBinarySearch(matrix, k)}");
  print("Merge K Sorted Lists: ${kthSmallestMergeHeap(matrix, k)}");
  print("Quick Select: ${kthSmallestQuickSelect(matrix, k)}");
}
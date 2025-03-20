// Dart Solution for 'Kth Smallest Element in a Sorted Matrix'
// 5 Different Approaches with Detailed Comments and Real-World Applications
// Applications: Data Analysis, Search Engines, Financial Market Data Processing

import 'dart:collection';
import 'dart:math';
import 'package:collection/collection.dart'; // Import for PriorityQueue

// 1. Brute Force Approach (Sorting) - O(n^2 log n)
// Flattens the matrix into a single list, sorts it, and returns the kth element.
// Simple but not efficient for large matrices.
int kthSmallestBruteForce(List<List<int>> matrix, int k) {
  List<int> flattened = matrix.expand((row) => row).toList();
  flattened.sort();
  return flattened[k - 1];
}

// 2. Min Heap Approach (Priority Queue) - O(k log n)
// Uses a min heap to store all elements, then removes the smallest k-1 elements.
// Efficient for finding smaller kth elements.
int kthSmallestMinHeap(List<List<int>> matrix, int k) {
  PriorityQueue<int> minHeap = PriorityQueue<int>((a, b) => a.compareTo(b));
  for (var row in matrix) {
    for (var num in row) {
      minHeap.add(num);
    }
  }
  for (int i = 1; i < k; i++) {
    minHeap.removeFirst();
  }
  return minHeap.first;
}

// 3. Max Heap (Efficient for Large Data) - O(n^2 log k)
// Uses a max heap to store k largest elements seen so far.
// Efficient when k is much smaller than n^2.
int kthSmallestMaxHeap(List<List<int>> matrix, int k) {
  PriorityQueue<int> maxHeap = PriorityQueue<int>((a, b) => b.compareTo(a));
  for (var row in matrix) {
    for (var num in row) {
      maxHeap.add(num);
      if (maxHeap.length > k) {
        maxHeap.removeFirst();
      }
    }
  }
  return maxHeap.first;
}

// 4. Binary Search (Optimized for Sorted Matrices) - O(n log max-min)
// Performs binary search on the range of possible values, counting elements <= mid.
// Efficient for large matrices with a wide range of values.
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

// 5. Merge k Sorted Lists using Min Heap (Heap Optimization) - O(k log n)
// Treats each row as a sorted list and merges them using a min heap.
// Efficient for large matrices, especially when k is relatively small.
int kthSmallestMergeHeap(List<List<int>> matrix, int k) {
  PriorityQueue<List<int>> minHeap = PriorityQueue<List<int>>((a, b) => a[0].compareTo(b[0]));
  for (int i = 0; i < matrix.length; i++) {
    minHeap.add([matrix[i][0], i, 0]);
  }
  while (k-- > 1) {
    List<int> smallest = minHeap.removeFirst();
    int row = smallest[1], col = smallest[2];
    if (col + 1 < matrix[row].length) {
      minHeap.add([matrix[row][col + 1], row, col + 1]);
    }
  }
  return minHeap.first[0];
}

// Test Cases for Different Approaches
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

  matrix = [
    [5]
  ];
  k = 1;

  print("\nBrute Force: ${kthSmallestBruteForce(matrix, k)}");
  print("Min Heap: ${kthSmallestMinHeap(matrix, k)}");
  print("Max Heap: ${kthSmallestMaxHeap(matrix, k)}");
  print("Binary Search: ${kthSmallestBinarySearch(matrix, k)}");
  print("Merge K Sorted Lists: ${kthSmallestMergeHeap(matrix, k)}");
}
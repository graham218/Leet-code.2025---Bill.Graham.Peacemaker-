// Advanced Dart implementation of Exponential Search with real-world applications
// Exponential Search is efficient for searching in large sorted datasets, databases, logs, and unbounded lists

import 'dart:math';
import 'dart:async';

// 1. Iterative Exponential Search (Used in sorted log analysis, database indexing)
int exponentialSearch(List<int> arr, int target) {
  if (arr.isEmpty) return -1;
  if (arr[0] == target) return 0;

  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }

  return binarySearch(arr, target, bound ~/ 2, min(bound, arr.length - 1));
}

// Helper function: Iterative Binary Search
int binarySearch(List<int> arr, int target, int left, int right) {
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

// 2. Recursive Exponential Search (Used in AI/ML applications for adaptive search)
int exponentialSearchRecursive(List<int> arr, int target) {
  return _expSearchHelper(arr, target, 1);
}

int _expSearchHelper(List<int> arr, int target, int bound) {
  if (bound >= arr.length || arr[bound] >= target) {
    return binarySearch(arr, target, bound ~/ 2, min(bound, arr.length - 1));
  }
  return _expSearchHelper(arr, target, bound * 2);
}

// 3. Exponential Search with Linear Scan (Used in memory-efficient IoT applications)
int exponentialSearchLinear(List<int> arr, int target) {
  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }

  for (int i = bound ~/ 2; i <= min(bound, arr.length - 1); i++) {
    if (arr[i] == target) return i;
  }
  return -1;
}

// 4. Exponential Search for Large Data Streams (Used in real-time analytics and logging systems)
Future<int> exponentialSearchDynamic(Stream<int> stream, int target) async {
  int bound = 1;
  List<int> arr = [];
  int index = 0;

  await for (int value in stream) {
    arr.add(value);
    if (value >= target || index >= bound) break;
    index++;
    if (index == bound) bound *= 2;
  }

  return binarySearch(arr, target, arr.isEmpty ? 0: bound ~/ 2, arr.isEmpty ? -1 : arr.length -1);
}

// 5. Parallel Exponential Search (Used in distributed search engines and cloud computing)
Future<int> exponentialSearchParallel(List<int> arr, int target) async {
  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }

  return await Future.microtask(() => binarySearch(arr, target, bound ~/ 2, min(bound, arr.length - 1)));
}

// 6. Exponential Search with Jump Search Optimization (Used in large-scale dataset searching like bioinformatics)
int exponentialSearchJump(List<int> arr, int target) {
  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }

  int left = bound ~/ 2;
  int right = min(bound, arr.length - 1);
  int step = sqrt(right - left).toInt();

  for (int i = left; i <= right; i += step) {
    if (arr[i] >= target) {
      return binarySearch(arr, target, max(left, i - step), i);
    }
  }
  return -1;
}

// Test cases demonstrating real-world applications
Future<void> main() async {
  List<int> numbers = [1, 2, 3, 4, 10, 15, 20, 40, 80, 160];
  int target = 15;

  print("Iterative Exponential Search (Database Indexing): ${exponentialSearch(numbers, target)}");
  print("Recursive Exponential Search (AI/ML Adaptation): ${exponentialSearchRecursive(numbers, target)}");
  print("Exponential Search with Linear Scan (IoT Devices): ${exponentialSearchLinear(numbers, target)}");
  print("Parallel Exponential Search (Cloud Computing): ${await exponentialSearchParallel(numbers, target)}");
  print("Jump Optimized Exponential Search (Bioinformatics): ${exponentialSearchJump(numbers, target)}");

  //Dynamic Stream test
  Stream<int> dynamicStream = Stream.fromIterable(numbers);
  print("Dynamic Stream Exponential Search (Realtime Analytics): ${await exponentialSearchDynamic(dynamicStream, target)}");

  //Dynamic stream test for empty stream
  Stream<int> emptyStream = Stream.fromIterable([]);
  print("Dynamic Stream Exponential Search (Empty stream): ${await exponentialSearchDynamic(emptyStream, target)}");
}
// Dart implementation of Exponential Search with 5 different approaches
// Exponential Search is useful for searching in sorted data structures with unknown or unbounded size

import 'dart:math';

// 1. Iterative Exponential Search using Binary Search
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

// 2. Recursive Exponential Search
int exponentialSearchRecursive(List<int> arr, int target) {
  return _expSearchHelper(arr, target, 1);
}

int _expSearchHelper(List<int> arr, int target, int bound) {
  if (bound >= arr.length || arr[bound] >= target) {
    return binarySearch(arr, target, bound ~/ 2, min(bound, arr.length - 1));
  }
  return _expSearchHelper(arr, target, bound * 2);
}

// 3. Exponential Search with Iterative Jump and Linear Search
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

// 4. Modified Exponential Search for Dynamic Lists (for unknown-length streams)
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

  return binarySearch(arr, target, arr.isEmpty ? 0 : bound ~/ 2, arr.isEmpty ? -1 : arr.length - 1);
}

// 5. Parallel Exponential Search (Simulated)
Future<int> exponentialSearchParallel(List<int> arr, int target) async {
  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }

  return await Future.microtask(() => binarySearch(arr, target, bound ~/ 2, min(bound, arr.length - 1)));
}

// Test cases
Future<void> main() async {
  List<int> numbers = [1, 2, 3, 4, 10, 15, 20, 40, 80, 160];
  int target = 15;

  print("Iterative Exponential Search: ${exponentialSearch(numbers, target)}");
  print("Recursive Exponential Search: ${exponentialSearchRecursive(numbers, target)}");
  print("Exponential Search with Linear Scan: ${exponentialSearchLinear(numbers, target)}");
  print("Parallel Exponential Search: ${await exponentialSearchParallel(numbers, target)}");

  // Test for dynamic stream
  Stream<int> dynamicStream = Stream.fromIterable(numbers);
  print("Dynamic Stream Exponential Search: ${await exponentialSearchDynamic(dynamicStream, target)}");

  //Test for empty Stream
  Stream<int> emptyStream = Stream.fromIterable([]);
  print("Dynamic Stream Exponential Search on empty stream: ${await exponentialSearchDynamic(emptyStream, target)}");
}
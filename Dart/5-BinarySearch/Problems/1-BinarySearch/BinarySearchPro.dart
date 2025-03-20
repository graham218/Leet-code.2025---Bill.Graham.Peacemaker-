// Advanced Dart implementation of Binary Search with real-world applications
// Binary Search is used in databases, AI search optimizations, financial systems, and more

import 'dart:math';
import 'dart:async';

// 1. Iterative Binary Search (Used in databases and search engines)
int binarySearchIterative(List<int> arr, int target) {
  int left = 0, right = arr.length - 1;
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

// 2. Recursive Binary Search (Used in AI and machine learning hyperparameter tuning)
int binarySearchRecursive(List<int> arr, int target, int left, int right) {
  if (left > right) return -1;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] == target) return mid;
  if (arr[mid] < target) {
    return binarySearchRecursive(arr, target, mid + 1, right);
  } else {
    return binarySearchRecursive(arr, target, left, mid - 1);
  }
}

// 3. Exponential Binary Search (Used for searching in large log files and unbounded data streams)
int binarySearchExponential(List<int> arr, int target) {
  if (arr.isEmpty) return -1;
  if (arr[0] == target) return 0;

  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }
  int left = bound ~/ 2;
  int right = min(bound, arr.length) -1;
  if (right < left) return -1; //Handle case where bound is larger than the array length.
  return binarySearchIterative(arr.sublist(left, right + 1), target);
}

// 4. Floating-Point Binary Search (Used in financial applications for stock price analysis)
double binarySearchPrecision(double left, double right, double target, double precision) {
  while ((right - left) > precision) {
    double mid = left + (right - left) / 2;
    if ((mid * mid - target).abs() < precision) return mid; // check if mid * mid is close to target
    if (mid * mid < target) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

// 5. Parallel Binary Search (Used in cloud computing for distributed search queries)
Future<int> binarySearchParallel(List<int> arr, int target) async {
  return await Future.microtask(() => binarySearchIterative(arr, target));
}

// 6. Ternary Search (Used in AI algorithms for function optimization)
int ternarySearch(List<int> arr, int target) {
  int left = 0, right = arr.length - 1;
  while (left <= right) {
    int mid1 = left + (right - left) ~/ 3;
    int mid2 = right - (right - left) ~/ 3;
    if (arr[mid1] == target) return mid1;
    if (arr[mid2] == target) return mid2;
    if (target < arr[mid1]) {
      right = mid1 - 1;
    } else if (target > arr[mid2]) {
      left = mid2 + 1;
    } else {
      left = mid1 + 1;
      right = mid2 - 1;
    }
  }
  return -1;
}

// Test cases demonstrating real-world applications
Future<void> main() async {
  List<int> numbers = [1, 2, 3, 4, 10, 15, 20, 40, 80, 160];
  int target = 15;

  print("Iterative Binary Search (Database Indexing): ${binarySearchIterative(numbers, target)}");
  print("Recursive Binary Search (AI Hyperparameter Tuning): ${binarySearchRecursive(numbers, target, 0, numbers.length - 1)}");
  print("Exponential Binary Search (Log File Analysis): ${binarySearchExponential(numbers, target)}");
  print("Floating Point Binary Search (Stock Price Analysis - √2): ${binarySearchPrecision(1, 2, 2, 0.0001)}");
  print("Parallel Binary Search (Cloud Distributed Search): ${await binarySearchParallel(numbers, target)}");
  print("Ternary Search (AI Optimization Problems): ${ternarySearch(numbers, target)}");

  List<int> emptyList = [];
  print("Exponential Binary Search on empty List: ${binarySearchExponential(emptyList, target)}");
}
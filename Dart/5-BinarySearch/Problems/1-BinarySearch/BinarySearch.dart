// Dart implementation of Binary Search with 5 different approaches
// Binary Search is widely used in databases, search engines, and AI applications

import 'dart:math';

// 1. Iterative Binary Search
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

// 2. Recursive Binary Search
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

// 3. Binary Search with Exponential Expansion (useful for unbounded lists)
int binarySearchExponential(List<int> arr, int target) {
  if (arr.isEmpty) return -1;
  if (arr[0] == target) return 0;

  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }
  int left = bound ~/ 2;
  int right = min(bound, arr.length) - 1;
  if (right < left) return -1; //Handle case where bound is larger than the array length
  return binarySearchIterative(arr.sublist(left, right + 1), target);
}

// 4. Binary Search for Floating Point Numbers (Used in precision-based problems)
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

// 5. Ternary Search (Variant for unimodal functions, e.g., AI optimizations)
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

// Test cases
void main() {
  List<int> numbers = [1, 2, 3, 4, 10, 15, 20, 40, 80, 160];
  int target = 15;

  print("Iterative Binary Search: ${binarySearchIterative(numbers, target)}");
  print("Recursive Binary Search: ${binarySearchRecursive(numbers, target, 0, numbers.length - 1)}");
  print("Exponential Binary Search: ${binarySearchExponential(numbers, target)}");
  print("Binary Search for Precision (√2): ${binarySearchPrecision(1, 2, 2, 0.0001)}");
  print("Ternary Search: ${ternarySearch(numbers, target)}");

  List<int> emptyList = [];
  print("Exponential Binary Search on empty List: ${binarySearchExponential(emptyList, target)}");
}
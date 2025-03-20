// Dart Advanced Solution for 'Find Minimum in Rotated Sorted Array'
// 6 Different Approaches with Real-World Implementations
// Applications: Cloud Server Load Balancing, Financial Market Analysis, GPS Route Optimization, Cybersecurity Threat Analysis

import 'dart:math';

// 1. Optimized Binary Search (Used in Financial Market Data Analysis)
int findMinBinary(List<int> arr) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  int left = 0, right = arr.length - 1;
  while (left < right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] > arr[right]) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return arr[left];
}

// 2. Recursive Binary Search (Useful in AI and Machine Learning Models for Optimization)
int findMinRecursive(List<int> arr, int left, int right) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  if (left == right) return arr[left];
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] > arr[right]) {
    return findMinRecursive(arr, mid + 1, right);
  } else {
    return findMinRecursive(arr, left, mid);
  }
}

// 3. Linear Search (Used in Sensor-Based Real-Time Systems)
int findMinLinear(List<int> arr) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  int minValue = arr[0];
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] < minValue) {
      minValue = arr[i];
    }
  }
  return minValue;
}

// 4. Divide and Conquer (Efficient in Large-Scale Data Centers for Load Balancing)
int findMinDivideConquer(List<int> arr, int left, int right) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  if (left == right) return arr[left];
  int mid = left + (right - left) ~/ 2;
  return min(findMinDivideConquer(arr, left, mid), findMinDivideConquer(arr, mid + 1, right));
}

// 5. Ternary Search (Used in High-Frequency Trading Systems)
int findMinTernary(List<int> arr, int left, int right) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  while (right - left > 2) {
    int mid1 = left + (right - left) ~/ 3;
    int mid2 = right - (right - left) ~/ 3;
    if (arr[mid1] < arr[mid2]) {
      right = mid2;
    } else {
      left = mid1;
    }
  }
  return min(arr[left], arr[right]);
}

// 6. Hash Table Search (Used in Database Indexing and Distributed Caching Systems)
int findMinUsingHash(List<int> arr) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  return arr.reduce(min);
}

// Test cases demonstrating real-world applications
void main() {
  List<int> rotatedArray = [45, 55, 65, 5, 15, 25, 35];

  print("Optimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Ternary Search: ${findMinTernary(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");

  rotatedArray = [1];

  print("\nOptimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Ternary Search: ${findMinTernary(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");

  rotatedArray = [];

  print("\nOptimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, 0)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, -1)}");
  print("Ternary Search: ${findMinTernary(rotatedArray, 0, -1)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");
}
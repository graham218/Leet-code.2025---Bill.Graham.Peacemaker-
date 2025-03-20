// Dart Solution for 'Find Minimum in Rotated Sorted Array' with 6 Different Approaches
// Real-world applications: Financial Market Data, Cloud Server Load Balancing, GPS Navigation, Database Optimization

import 'dart:math';

// 1. Optimized Binary Search (Efficient in detecting smallest element in O(log n))
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

// 2. Recursive Binary Search (Used in AI and Decision Trees for optimization)
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

// 3. Linear Search (Useful for small datasets and sensor data analysis)
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

// 4. Divide and Conquer (Used in distributed computing to optimize search time)
int findMinDivideConquer(List<int> arr, int left, int right) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  if (left == right) return arr[left];
  int mid = left + (right - left) ~/ 2;
  return min(findMinDivideConquer(arr, left, mid), findMinDivideConquer(arr, mid + 1, right));
}

// 5. Jump Search (Efficient for indexing and financial analysis applications)
int findMinJump(List<int> arr) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  int step = sqrt(arr.length).toInt();
  int minValue = arr[0];
  for (int i = 0; i < arr.length; i += step) {
    if (arr[i] < minValue) {
      minValue = arr[i];
    }
  }
  for (int j = max(0, arr.length - step); j < arr.length; j++) {
    if (arr[j] < minValue) {
      minValue = arr[j];
    }
  }
  return minValue;
}

// 6. Hash Table Search (Efficient for databases and caching systems)
int findMinUsingHash(List<int> arr) {
  if (arr.isEmpty) {
    return -1; // Or throw an exception, or return a default value that makes sense.
  }
  return arr.reduce(min);
}

// Test cases with real-world applications
void main() {
  List<int> rotatedArray = [40, 50, 60, 10, 20, 30];

  print("Optimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Jump Search: ${findMinJump(rotatedArray)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");

  rotatedArray = [1];

  print("\nOptimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, rotatedArray.length - 1)}");
  print("Jump Search: ${findMinJump(rotatedArray)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");

  rotatedArray = [];

  print("\nOptimized Binary Search: ${findMinBinary(rotatedArray)}");
  print("Recursive Binary Search: ${findMinRecursive(rotatedArray, 0, 0)}");
  print("Linear Search: ${findMinLinear(rotatedArray)}");
  print("Divide and Conquer: ${findMinDivideConquer(rotatedArray, 0, -1)}");
  print("Jump Search: ${findMinJump(rotatedArray)}");
  print("Hash Table Search: ${findMinUsingHash(rotatedArray)}");
}
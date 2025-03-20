// Dart Advanced Solution for 'Search in Rotated Sorted Array' with 6 Different Approaches
// Real-world applications: Operating Systems Scheduling, GPS navigation, Database Indexing, Cybersecurity Threat Detection

import 'dart:math';

// 1. Optimized Binary Search (Handles Rotation Efficiently)
int searchBinaryOptimized(List<int> arr, int target) {
  int left = 0, right = arr.length - 1;
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) return mid;
    if (arr[left] <= arr[mid]) { // Left half is sorted
      if (target >= arr[left] && target < arr[mid]) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    } else { // Right half is sorted
      if (target > arr[mid] && target <= arr[right]) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }
  return -1;
}

// 2. Recursive Search (Useful in AI/ML decision trees)
int searchRecursive(List<int> arr, int target, int left, int right) {
  if (left > right) return -1;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] == target) return mid;
  if (arr[left] <= arr[mid]) {
    if (target >= arr[left] && target < arr[mid]) {
      return searchRecursive(arr, target, left, mid - 1);
    } else {
      return searchRecursive(arr, target, mid + 1, right);
    }
  } else {
    if (target > arr[mid] && target <= arr[right]) {
      return searchRecursive(arr, target, mid + 1, right);
    } else {
      return searchRecursive(arr, target, left, mid - 1);
    }
  }
}

// 3. Exponential Search (Useful for Large Unbounded Data Sets)
int searchExponential(List<int> arr, int target) {
  if (arr.isEmpty) return -1;
  if (arr[0] == target) return 0;
  int bound = 1;
  while (bound < arr.length && arr[bound] < target) {
    bound *= 2;
  }
  int left = bound ~/ 2;
  int right = min(bound, arr.length) -1;
  if (right < left) return -1; //Handle case where bound is larger than the array length.
  return searchBinaryOptimized(arr.sublist(left, right + 1), target);
}

// 4. Interpolation Search (Used in GPS and sensor-based applications)
int searchInterpolation(List<int> arr, int target) {
  int low = 0, high = arr.length - 1;
  while (low <= high && target >= arr[low] && target <= arr[high]) {
    if (low == high) {
      return arr[low] == target ? low : -1;
    }
    int pos = low + ((target - arr[low]) * (high - low) ~/ (arr[high] - arr[low]));
    if (pos < low || pos > high) break; //Handle divide by zero and out of bounds.
    if (arr[pos] == target) return pos;
    if (arr[pos] < target) {
      low = pos + 1;
    } else {
      high = pos - 1;
    }
  }
  return -1;
}

// 5. Jump Search (Used in large data indexing for fast lookups)
int searchJump(List<int> arr, int target) {
  int step = sqrt(arr.length).toInt();
  int prev = 0;
  while (prev < arr.length && arr[min(step, arr.length) - 1] < target) {
    prev = step;
    step += sqrt(arr.length).toInt();
    if (prev >= arr.length) return -1;
  }
  for (int i = prev; i < min(step, arr.length); i++) {
    if (arr[i] == target) return i;
  }
  return -1;
}

// 6. Hash Table Search (Efficient for Database and Key-Value Lookup Systems)
int searchUsingHashMap(List<int> arr, int target) {
  Map<int, int> indexMap = {};
  for (int i = 0; i < arr.length; i++) {
    indexMap[arr[i]] = i;
  }
  return indexMap.containsKey(target) ? indexMap[target]! : -1;
}

// Test cases demonstrating real-world applications
void main() {
  List<int> rotatedArray = [50, 60, 70, 10, 20, 30, 40];
  int target = 10;

  print("Optimized Binary Search: ${searchBinaryOptimized(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Exponential Search: ${searchExponential(rotatedArray, target)}");
  print("Interpolation Search: ${searchInterpolation(rotatedArray, target)}");
  print("Jump Search: ${searchJump(rotatedArray, target)}");
  print("Hash Table Search: ${searchUsingHashMap(rotatedArray, target)}");

  rotatedArray = [4,5,6,7,0,1,2];
  target = 0;

  print("\nOptimized Binary Search: ${searchBinaryOptimized(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Exponential Search: ${searchExponential(rotatedArray, target)}");
  print("Interpolation Search: ${searchInterpolation(rotatedArray, target)}");
  print("Jump Search: ${searchJump(rotatedArray, target)}");
  print("Hash Table Search: ${searchUsingHashMap(rotatedArray, target)}");

  rotatedArray = [1];
  target = 1;

  print("\nOptimized Binary Search: ${searchBinaryOptimized(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Exponential Search: ${searchExponential(rotatedArray, target)}");
  print("Interpolation Search: ${searchInterpolation(rotatedArray, target)}");
  print("Jump Search: ${searchJump(rotatedArray, target)}");
  print("Hash Table Search: ${searchUsingHashMap(rotatedArray, target)}");
}
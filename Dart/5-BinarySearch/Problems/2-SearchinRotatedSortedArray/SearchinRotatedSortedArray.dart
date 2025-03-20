// Dart solution for 'Search in Rotated Sorted Array' with 5 different approaches
// Real-world applications: OS scheduling, GPS location mapping, database indexing

import 'dart:math';

// 1. Iterative Binary Search (Handles rotation by checking left and right halves)
int searchBinary(List<int> arr, int target) {
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

// 2. Recursive Binary Search (Useful for recursive systems like AI decision trees)
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

// 3. Iterative Linear Search (Useful for small datasets and hardware memory constraints)
int searchLinear(List<int> arr, int target) {
  for (int i = 0; i < arr.length; i++) {
    if (arr[i] == target) return i;
  }
  return -1;
}

// 4. Two-Pointer Approach (Used in GPS and navigation for efficient tracking)
int searchTwoPointer(List<int> arr, int target) {
  int left = 0, right = arr.length - 1;
  while (left <= right) {
    if (arr[left] == target) return left;
    if (arr[right] == target) return right;
    left++;
    right--;
  }
  return -1;
}

// 5. HashMap Approach (Efficient for database indexing and caching systems)
int searchUsingMap(List<int> arr, int target) {
  Map<int, int> indexMap = {};
  for (int i = 0; i < arr.length; i++) {
    indexMap[arr[i]] = i;
  }
  return indexMap.containsKey(target) ? indexMap[target]! : -1;
}

// Test cases
void main() {
  List<int> rotatedArray = [30, 40, 50, 10, 20];
  int target = 10;

  print("Iterative Binary Search: ${searchBinary(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${searchLinear(rotatedArray, target)}");
  print("Two-Pointer Search: ${searchTwoPointer(rotatedArray, target)}");
  print("HashMap Search: ${searchUsingMap(rotatedArray, target)}");

  rotatedArray = [4,5,6,7,0,1,2];
  target = 0;

  print("\nIterative Binary Search: ${searchBinary(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${searchLinear(rotatedArray, target)}");
  print("Two-Pointer Search: ${searchTwoPointer(rotatedArray, target)}");
  print("HashMap Search: ${searchUsingMap(rotatedArray, target)}");

  rotatedArray = [1];
  target = 1;

  print("\nIterative Binary Search: ${searchBinary(rotatedArray, target)}");
  print("Recursive Search: ${searchRecursive(rotatedArray, target, 0, rotatedArray.length - 1)}");
  print("Linear Search: ${searchLinear(rotatedArray, target)}");
  print("Two-Pointer Search: ${searchTwoPointer(rotatedArray, target)}");
  print("HashMap Search: ${searchUsingMap(rotatedArray, target)}");

}
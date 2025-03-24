import 'dart:math';
import 'package:collection/collection.dart';
import 'dart:collection';

void main() {
  // Example usage of the different approaches:
  List<int> nums1_1 = [1, 3];
  List<int> nums2_1 = [2];
  print("Example 1:");
  print("Input: nums1 = ${nums1_1}, nums2 = ${nums2_1}");
  print(
      "Approach 1 (Merge and Sort): Median = ${findMedianSortedArrays_mergeAndSort(nums1_1, nums2_1)}");
  print(
      "Approach 2 (Binary Search): Median = ${findMedianSortedArrays_binarySearch(nums1_1, nums2_1)}");
  print(
      "Approach 3 (Using Heap): Median = ${findMedianSortedArrays_heap(nums1_1, nums2_1)}");
  print(
      "Approach 4 (Using Iterators): Median = ${findMedianSortedArrays_iterators(nums1_1, nums2_1)}");
  print(
      "Approach 5 (Optimized Binary Search): Median = ${findMedianSortedArrays_optimizedBinarySearch(nums1_1, nums2_1)}");

  List<int> nums1_2 = [1, 2];
  List<int> nums2_2 = [3, 4];
  print("\nExample 2:");
  print("Input: nums1 = ${nums1_2}, nums2 = ${nums2_2}");
  print(
      "Approach 1 (Merge and Sort): Median = ${findMedianSortedArrays_mergeAndSort(nums1_2, nums2_2)}");
  print(
      "Approach 2 (Binary Search): Median = ${findMedianSortedArrays_binarySearch(nums1_2, nums2_2)}");
  print(
      "Approach 3 (Using Heap): Median = ${findMedianSortedArrays_heap(nums1_2, nums2_2)}");
  print(
      "Approach 4 (Using Iterators): Median = ${findMedianSortedArrays_iterators(nums1_2, nums2_2)}");
  print(
      "Approach 5 (Optimized Binary Search): Median = ${findMedianSortedArrays_optimizedBinarySearch(nums1_2, nums2_2)}");

  List<int> nums1_3 = [0, 0];
  List<int> nums2_3 = [0, 0];
  print("\nExample 3:");
  print("Input: nums1 = ${nums1_3}, nums2 = ${nums2_3}");
  print(
      "Approach 1 (Merge and Sort): Median = ${findMedianSortedArrays_mergeAndSort(nums1_3, nums2_3)}");
  print(
      "Approach 2 (Binary Search): Median = ${findMedianSortedArrays_binarySearch(nums1_3, nums2_3)}");
  print(
      "Approach 3 (Using Heap): Median = ${findMedianSortedArrays_heap(nums1_3, nums2_3)}");
  print(
      "Approach 4 (Using Iterators): Median = ${findMedianSortedArrays_iterators(nums1_3, nums2_3)}");
  print(
      "Approach 5 (Optimized Binary Search): Median = ${findMedianSortedArrays_optimizedBinarySearch(nums1_3, nums2_3)}");

  List<int> nums1_4 = [];
  List<int> nums2_4 = [1];
  print("\nExample 4:");
  print("Input: nums1 = ${nums1_4}, nums2 = ${nums2_4}");
  print(
      "Approach 1 (Merge and Sort): Median = ${findMedianSortedArrays_mergeAndSort(nums1_4, nums2_4)}");
  print(
      "Approach 2 (Binary Search): Median = ${findMedianSortedArrays_binarySearch(nums1_4, nums2_4)}");
  print(
      "Approach 3 (Using Heap): Median = ${findMedianSortedArrays_heap(nums1_4, nums2_4)}");
  print(
      "Approach 4 (Using Iterators): Median = ${findMedianSortedArrays_iterators(nums1_4, nums2_4)}");
  print(
      "Approach 5 (Optimized Binary Search): Median = ${findMedianSortedArrays_optimizedBinarySearch(nums1_4, nums2_4)}");
}

// Approach 1: Merge and Sort
// Time Complexity: O((m+n)log(m+n))
// Space Complexity: O(m+n)
double findMedianSortedArrays_mergeAndSort(List<int> nums1, List<int> nums2) {
  List<int> mergedList = [...nums1, ...nums2];
  mergedList.sort(); // Sort the merged list.  Timsort is used, O(n log n)
  int length = mergedList.length;
  if (length % 2 == 0) {
    return (mergedList[length ~/ 2 - 1] + mergedList[length ~/ 2]) / 2.0;
  } else {
    return mergedList[length ~/ 2].toDouble();
  }
}

// Approach 2: Binary Search
// Time Complexity: O(log(min(m, n)))
// Space Complexity: O(1)
double findMedianSortedArrays_binarySearch(List<int> nums1, List<int> nums2) {
  if (nums1.length > nums2.length) {
    return findMedianSortedArrays_binarySearch(
        nums2, nums1); // Ensure nums1 is the shorter array
  }

  int m = nums1.length;
  int n = nums2.length;
  int low = 0;
  int high = m;

  while (low <= high) {
    int partitionX = (low + high) ~/ 2;
    int partitionY = ((m + n + 1) ~/ 2) - partitionX;

    double maxLeftX = (partitionX == 0)
        ? double.negativeInfinity
        : nums1[partitionX - 1].toDouble();
    double minRightX = (partitionX == m)
        ? double.infinity
        : nums1[partitionX].toDouble();

    double maxLeftY = (partitionY == 0)
        ? double.negativeInfinity
        : nums2[partitionY - 1].toDouble();
    double minRightY = (partitionY == n)
        ? double.infinity
        : nums2[partitionY].toDouble();

    if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
      if ((m + n) % 2 == 0) {
        return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
      } else {
        return max(maxLeftX, maxLeftY).toDouble();
      }
    } else if (maxLeftX > minRightY) {
      high = partitionX - 1;
    } else {
      low = partitionX + 1;
    }
  }
  throw Exception("Arrays are not sorted"); //Should not reach here.
}

// Approach 3: Using Heap (Priority Queue)
// Time Complexity: O((m+n)log(m+n))  due to insertion into the priority queue
// Space Complexity: O(m+n)

double findMedianSortedArrays_heap(List<int> nums1, List<int> nums2) {
  PriorityQueue<int> minHeap = PriorityQueue(); // Default is min-heap
  for (int num in nums1) {
    minHeap.add(num);
  }
  for (int num in nums2) {
    minHeap.add(num);
  }

  int length = nums1.length + nums2.length;
  List<int> sortedList = [];
  while (minHeap.isNotEmpty) {
    sortedList.add(minHeap.removeFirst());
  }

  if (length % 2 == 0) {
    return (sortedList[length ~/ 2 - 1] + sortedList[length ~/ 2]) / 2.0;
  } else {
    return sortedList[length ~/ 2].toDouble();
  }
}

// Approach 4: Using Iterators
// Time Complexity: O(m+n)
// Space Complexity: O(1)
double findMedianSortedArrays_iterators(List<int> nums1, List<int> nums2) {
  int m = nums1.length;
  int n = nums2.length;
  int i = 0;
  int j = 0;
  List<int> mergedList = [];

  while (i < m && j < n) {
    if (nums1[i] <= nums2[j]) {
      mergedList.add(nums1[i]);
      i++;
    } else {
      mergedList.add(nums2[j]);
      j++;
    }
  }

  while (i < m) {
    mergedList.add(nums1[i]);
    i++;
  }

  while (j < n) {
    mergedList.add(nums2[j]);
    j++;
  }
  int length = mergedList.length;
  if (length % 2 == 0) {
    return (mergedList[length ~/ 2 - 1] + mergedList[length ~/ 2]) / 2.0;
  } else {
    return mergedList[length ~/ 2].toDouble();
  }
}

// Approach 5: Optimized Binary Search
// Time Complexity: O(log(min(m, n)))
// Space Complexity: O(1)
double findMedianSortedArrays_optimizedBinarySearch(
    List<int> nums1, List<int> nums2) {
  if (nums1.length > nums2.length) {
    return findMedianSortedArrays_optimizedBinarySearch(nums2, nums1);
  }

  int m = nums1.length;
  int n = nums2.length;
  int low = 0;
  int high = m;

  while (low <= high) {
    int partitionX = (low + high) ~/ 2;
    int partitionY = ((m + n + 1) ~/ 2) - partitionX;

    double maxLeftX = (partitionX == 0)
        ? double.negativeInfinity
        : nums1[partitionX - 1].toDouble();
    double minRightX = (partitionX == m)
        ? double.infinity
        : nums1[partitionX].toDouble();

    double maxLeftY = (partitionY == 0)
        ? double.negativeInfinity
        : nums2[partitionY - 1].toDouble();
    double minRightY = (partitionY == n)
        ? double.infinity
        : nums2[partitionY].toDouble();

    if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
      if ((m + n) % 2 == 0) {
        return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
      } else {
        return max(maxLeftX, maxLeftY).toDouble();
      }
    } else if (maxLeftX > minRightY) {
      high = partitionX - 1;
    } else {
      low = partitionX + 1;
    }
  }
  throw Exception("Input arrays are not sorted.");
}

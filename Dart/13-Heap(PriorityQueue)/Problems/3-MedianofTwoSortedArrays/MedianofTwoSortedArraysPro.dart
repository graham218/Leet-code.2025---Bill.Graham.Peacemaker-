import 'dart:math';
import 'package:collection/collection.dart';
import 'dart:collection';

void main() {
  // Example 1: Combining sensor data from two devices
  List<double> sensor1Readings = [22.5, 23.1, 24.0, 25.2, 26.0];
  List<double> sensor2Readings = [23.0, 24.5, 25.0, 26.1, 27.0];
  print("Example 1: Sensor Readings");
  print("Sensor 1 Readings: $sensor1Readings");
  print("Sensor 2 Readings: $sensor2Readings");
  double medianSensorData =
  findMedianSortedArrays_optimizedBinarySearch(sensor1Readings, sensor2Readings); // Using the most efficient approach
  print("Combined Median Sensor Reading: $medianSensorData\n");

  // Example 2: Merging employee salaries from two departments
  List<int> deptASalaries = [50000, 60000, 75000, 90000, 100000];
  List<int> deptBSalaries = [55000, 70000, 80000, 95000, 110000];
  print("Example 2: Employee Salaries");
  print("Department A Salaries: $deptASalaries");
  print("Department B Salaries: $deptBSalaries");
  double medianSalary = findMedianSortedArrays_mergeAndSort(
      deptASalaries, deptBSalaries); // Using merge sort approach
  print("Combined Median Salary: $medianSalary\n");

  // Example 3: Combining latency measurements from two servers
  List<double> server1Latencies = [0.12, 0.15, 0.18, 0.20, 0.22];
  List<double> server2Latencies = [0.14, 0.17, 0.19, 0.21, 0.23];
  print("Example 3: Server Latencies");
  print("Server 1 Latencies: $server1Latencies");
  print("Server 2 Latencies: $server2Latencies");
  double medianLatency =
  findMedianSortedArrays_binarySearch(server1Latencies, server2Latencies);
  print("Combined Median Latency: $medianLatency\n");

  // Example 4: Stock prices from two exchanges
  List<double> exchange1Prices = [10.20, 10.50, 10.75, 11.00, 11.25];
  List<double> exchange2Prices = [10.30, 10.60, 10.80, 11.10, 11.30];
  print("Example 4: Stock Prices");
  print("Exchange 1 Prices: $exchange1Prices");
  print("Exchange 2 Prices: $exchange2Prices");
  double medianStockPrice = findMedianSortedArrays_heap(
      exchange1Prices, exchange2Prices); // Using Heap
  print("Combined Median Stock Price: $medianStockPrice\n");

  // Example 5: Customer ages from two demographics
  List<int> group1Ages = [25, 30, 35, 40, 45];
  List<int> group2Ages = [28, 32, 38, 42, 48];
  print("Example 5: Customer Ages");
  print("Group 1 Ages: $group1Ages");
  print("Group 2 Ages: $group2Ages");
  double medianCustomerAge = findMedianSortedArrays_iterators(
      group1Ages, group2Ages); // Using Iterators
  print("Combined Median Customer Age: $medianCustomerAge\n");

  // Example 6: Combining product ratings from two sources
  List<double> source1Ratings = [4.2, 4.5, 4.7, 4.8, 4.9];
  List<double> source2Ratings = [4.3, 4.6, 4.75, 4.85, 5.0];
  print("Example 6: Product Ratings");
  print("Source 1 Ratings: $source1Ratings");
  print("Source 2 Ratings: $source2Ratings");

  double medianProductRating =
  findMedianSortedArrays_optimizedBinarySearch2(source1Ratings, source2Ratings);
  print("Combined Median Product Rating: $medianProductRating\n");
}

// Approach 1: Merge and Sort
// Time Complexity: O((m+n)log(m+n))
// Space Complexity: O(m+n)
double findMedianSortedArrays_mergeAndSort(List<num> nums1, List<num> nums2) {
  List<num> mergedList = [...nums1, ...nums2];
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
double findMedianSortedArrays_binarySearch(List<num> nums1, List<num> nums2) {
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
double findMedianSortedArrays_heap(List<num> nums1, List<num> nums2) {
  PriorityQueue<num> minHeap = PriorityQueue<num>(); // Default is min-heap
  for (num val in nums1) {
    minHeap.add(val);
  }
  for (num val in nums2) {
    minHeap.add(val);
  }

  int length = nums1.length + nums2.length;
  List<num> sortedList = [];
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
double findMedianSortedArrays_iterators(List<num> nums1, List<num> nums2) {
  int m = nums1.length;
  int n = nums2.length;
  int i = 0;
  int j = 0;
  List<num> mergedList = [];

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
    List<num> nums1, List<num> nums2) {
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

// Approach 6: Optimized Binary Search 2 (Slightly different variable naming)
// Time Complexity: O(log(min(m, n)))
// Space Complexity: O(1)
double findMedianSortedArrays_optimizedBinarySearch2(
    List<num> nums1, List<num> nums2) {
  if (nums1.length > nums2.length) {
    return findMedianSortedArrays_optimizedBinarySearch2(nums2, nums1);
  }

  int m = nums1.length;
  int n = nums2.length;
  int low = 0;
  int high = m;

  while (low <= high) {
    int partitionX = (low + high) ~/ 2;
    int partitionY = ((m + n + 1) ~/ 2) - partitionX;

    double left1 = (partitionX == 0)
        ? double.negativeInfinity
        : nums1[partitionX - 1].toDouble();
    double right1 =
    (partitionX == m) ? double.infinity : nums1[partitionX].toDouble();

    double left2 = (partitionY == 0)
        ? double.negativeInfinity
        : nums2[partitionY - 1].toDouble();
    double right2 =
    (partitionY == n) ? double.infinity : nums2[partitionY].toDouble();

    if (left1 <= right2 && left2 <= right1) {
      if ((m + n) % 2 == 0) {
        return (max(left1, left2) + min(right1, right2)) / 2.0;
      } else {
        return max(left1, left2).toDouble();
      }
    } else if (left1 > right2) {
      high = partitionX - 1;
    } else {
      low = partitionX + 1;
    }
  }
  throw Exception("Input arrays are not sorted.");
}

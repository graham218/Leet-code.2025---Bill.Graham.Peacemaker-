// Advanced Dart Solution for "Dynamic Sliding Window"
// Real-world applications: Real-time analytics, adaptive video streaming, memory management, and anomaly detection.

import 'dart:collection';
import 'dart:math';

class AdvancedSlidingWindow {
  List<int> nums;
  int target;

  AdvancedSlidingWindow(this.nums, this.target);

  // Approach 1: Adaptive Window for Maximum Average Subarray (O(n))
  // Used in financial trend analysis to track optimal moving averages.
  double maxAverageSubarray(int k) {
    if (k <= 0 || k > nums.length) {
      throw ArgumentError('Invalid window size k');
    }

    double sum = nums.take(k).fold(0, (a, b) => a + b);
    double maxAvg = sum / k;

    for (int i = k; i < nums.length; i++) {
      sum += nums[i] - nums[i - k];
      maxAvg = max(maxAvg, sum / k);
    }
    return maxAvg;
  }

  // Approach 2: Dynamic Longest Subarray Sum Below Target (O(n))
  // Used in cloud computing resource allocation.
  int longestSubarraySumBelowTarget() {
    int left = 0, sum = 0, maxLength = 0;
    for (int right = 0; right < nums.length; right++) {
      sum += nums[right];
      while (sum > target && left <= right) {
        sum -= nums[left++];
      }
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }

  // Approach 3: Sliding Window with Deque for Max Element in Every Window (O(n))
  // Used in real-time video processing for peak pixel intensity detection.
  List<int> maxInEveryWindow(int k) {
    if (k <= 0 || k > nums.length) {
      throw ArgumentError('Invalid window size k');
    }

    List<int> result = [];
    Queue<int> deque = Queue();

    for (int i = 0; i < nums.length; i++) {
      while (deque.isNotEmpty && deque.first < i - k + 1) {
        deque.removeFirst();
      }
      while (deque.isNotEmpty && nums[deque.last] < nums[i]) {
        deque.removeLast();
      }
      deque.addLast(i);
      if (i >= k - 1) {
        result.add(nums[deque.first]);
      }
    }
    return result;
  }

  // Approach 4: Smallest Window with Target Sum (O(n))
  // Used in fraud detection when looking for minimal transaction sequences.
  int smallestWindowWithTargetSum() {
    int left = 0, sum = 0, minLength = nums.length + 1;
    for (int right = 0; right < nums.length; right++) {
      sum += nums[right];
      while (sum >= target && left <= right) {
        minLength = min(minLength, right - left + 1);
        sum -= nums[left++];
      }
    }
    return minLength == nums.length + 1 ? -1 : minLength;
  }

  // Approach 5: Real-Time Anomaly Detection using Moving Median (O(n log k))
  // Used in cybersecurity to detect suspicious activity windows.
  List<double> movingMedian(int k) {
    if (k <= 0 || k > nums.length) {
      throw ArgumentError('Invalid window size k');
    }

    List<double> medians = [];
    List<int> window = [];

    for (int i = 0; i < nums.length; i++) {
      window.add(nums[i]);
      if (window.length > k) {
        window.remove(nums[i - k]);
      }
      window.sort();

      if (i >= k - 1) {
        int mid = k ~/ 2;
        medians.add(k % 2 == 0
            ? (window[mid - 1] + window[mid]) / 2.0
            : window[mid].toDouble());
      }
    }
    return medians;
  }
}

void main() {
  List<int> nums = [1, 3, 2, 6, 7, 5, 8, 9, 10, 4];
  int target = 15;
  AdvancedSlidingWindow solver = AdvancedSlidingWindow(nums, target);

  print("Max Average Subarray (k=3): ${solver.maxAverageSubarray(3)}");
  print(
      "Longest Subarray Sum Below Target: ${solver.longestSubarraySumBelowTarget()}");
  print("Max in Every Window (k=3): ${solver.maxInEveryWindow(3)}");
  print("Smallest Window With Target Sum: ${solver.smallestWindowWithTargetSum()}");
  print("Moving Median (k=3): ${solver.movingMedian(3)}");
}
class FixedWindow {
  final List<int> nums; // Input array
  final int k; // Window size

  FixedWindow(this.nums, this.k);

  // Approach 1: Basic Sliding Window (O(n))
  // Calculates the sum of each fixed-size window.
  List<int> basicSlidingWindow() {
    List<int> result = [];
    int windowSum = 0;

    for (int i = 0; i < nums.length; i++) {
      windowSum += nums[i]; // Add the current element to the window sum

      // When the window reaches size k, add the sum to the result
      if (i >= k - 1) {
        result.add(windowSum);
        windowSum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }

    return result;
  }

  // Approach 2: Maximum Sum Subarray (O(n))
  // Finds the maximum sum of any fixed-size window.
  int maxSumSubarray() {
    int maxSum = 0;
    int windowSum = 0;

    for (int i = 0; i < nums.length; i++) {
      windowSum += nums[i]; // Add the current element to the window sum

      // When the window reaches size k, update the maximum sum
      if (i >= k - 1) {
        maxSum = windowSum > maxSum ? windowSum : maxSum;
        windowSum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }

    return maxSum;
  }

  // Approach 3: Minimum Sum Subarray (O(n))
  // Finds the minimum sum of any fixed-size window.
  int minSumSubarray() {
    int minSum = 1 << 60; // Initialize with a large integer value
    int windowSum = 0;

    for (int i = 0; i < nums.length; i++) {
      windowSum += nums[i]; // Add the current element to the window sum

      // When the window reaches size k, update the minimum sum
      if (i >= k - 1) {
        minSum = windowSum < minSum ? windowSum : minSum;
        windowSum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }

    return minSum;
  }

  // Approach 4: Fixed Window with Queue (O(n))
  // Uses a deque to maintain the maximum value in each window.
  List<int> maxInEachWindow() {
    List<int> result = [];
    List<int> deque = []; // Double-ended queue to store indices

    for (int i = 0; i < nums.length; i++) {
      // Remove indices of elements not in the current window
      while (deque.isNotEmpty && deque.first < i - k + 1) {
        deque.removeAt(0);
      }

      // Remove indices of all elements smaller than the current element
      while (deque.isNotEmpty && nums[deque.last] < nums[i]) {
        deque.removeLast();
      }

      // Add the current element's index to the deque
      deque.add(i);

      // When the window reaches size k, add the maximum to the result
      if (i >= k - 1) {
        result.add(nums[deque.first]);
      }
    }

    return result;
  }

  // Approach 5: Fixed Window with HashMap (O(n))
  // Computes the number of distinct elements in each window.
  List<int> distinctElementsInWindow() {
    List<int> result = [];
    Map<int, int> freqMap = {}; // Map to store element frequencies

    for (int i = 0; i < nums.length; i++) {
      // Add the current element to the frequency map
      freqMap[nums[i]] = (freqMap[nums[i]] ?? 0) + 1;

      // When the window reaches size k, add the number of distinct elements to the result
      if (i >= k - 1) {
        result.add(freqMap.length);

        // Remove the oldest element from the window
        freqMap[nums[i - k + 1]] = freqMap[nums[i - k + 1]]! - 1;
        if (freqMap[nums[i - k + 1]] == 0) {
          freqMap.remove(nums[i - k + 1]);
        }
      }
    }

    return result;
  }
}

void main() {
  List<int> nums = [1, 3, 2, 6, -1, 4, 1, 8, 2];
  int k = 3;
  FixedWindow solver = FixedWindow(nums, k);

  print("Basic Sliding Window: ${solver.basicSlidingWindow()}");
  print("Maximum Sum Subarray: ${solver.maxSumSubarray()}");
  print("Minimum Sum Subarray: ${solver.minSumSubarray()}");
  print("Max in Each Window: ${solver.maxInEachWindow()}");
  print("Distinct Elements in Each Window: ${solver.distinctElementsInWindow()}");
}
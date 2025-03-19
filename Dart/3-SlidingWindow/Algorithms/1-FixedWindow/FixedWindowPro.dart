import 'dart:collection';

class FixedWindowAdvanced {
  final List<int> nums; // Input array
  final int k; // Window size

  FixedWindowAdvanced(this.nums, this.k);

  // Approach 1: Moving Average using Sliding Window (O(n))
  // Used in stock market trend analysis
  List<double> movingAverage() {
    List<double> result = [];
    double sum = 0;
    for (int i = 0; i < nums.length; i++) {
      sum += nums[i];
      if (i >= k - 1) {
        result.add(sum / k); // Calculate the average for the current window
        sum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }
    return result;
  }

  // Approach 2: Maximum Sum in Fixed Window (Kadane’s Sliding Window Adaptation) (O(n))
  // Used in identifying peak network traffic in a fixed time interval
  int maxSumSubarray() {
    int maxSum = 0, currentSum = 0;
    for (int i = 0; i < nums.length; i++) {
      currentSum += nums[i];
      if (i >= k - 1) {
        maxSum = currentSum > maxSum ? currentSum : maxSum; // Update maxSum
        currentSum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }
    return maxSum;
  }

  // Approach 3: Dynamic Anomaly Detection using Fixed Window (O(n))
  // Used in fraud detection systems
  List<bool> detectAnomalies(int threshold) {
    List<bool> anomalies = [];
    double sum = 0;
    for (int i = 0; i < nums.length; i++) {
      sum += nums[i];
      if (i >= k - 1) {
        anomalies.add((sum / k) > threshold); // Check if the average exceeds the threshold
        sum -= nums[i - k + 1]; // Remove the oldest element from the window
      }
    }
    return anomalies;
  }

  // Approach 4: Sentiment Analysis - Count Positive Words in Fixed Window (O(n))
  // Used in natural language processing for sentiment scoring
  List<int> positiveWordCount(List<int> sentimentScores) {
    List<int> counts = [];
    int count = 0;
    for (int i = 0; i < sentimentScores.length; i++) {
      if (sentimentScores[i] > 0) count++; // Increment count for positive sentiment
      if (i >= k - 1) {
        counts.add(count); // Add the count for the current window
        if (sentimentScores[i - k + 1] > 0) count--; // Remove the oldest element's contribution
      }
    }
    return counts;
  }

  // Approach 5: Traffic Rate Calculation using Deque (O(n))
  // Used in network congestion control
  List<int> maxTrafficInWindow() {
    List<int> result = [];
    Queue<int> deque = Queue(); // Deque to store indices of elements
    for (int i = 0; i < nums.length; i++) {
      // Remove indices of elements not in the current window
      while (deque.isNotEmpty && deque.first < i - k + 1) {
        deque.removeFirst();
      }
      // Remove indices of all elements smaller than the current element
      while (deque.isNotEmpty && nums[deque.last] < nums[i]) {
        deque.removeLast();
      }
      deque.addLast(i); // Add the current element's index to the deque
      if (i >= k - 1) {
        result.add(nums[deque.first]); // Add the maximum in the current window
      }
    }
    return result;
  }
}

void main() {
  List<int> nums = [1, 3, 2, 6, -1, 4, 1, 8, 2];
  int k = 3;
  FixedWindowAdvanced solver = FixedWindowAdvanced(nums, k);

  print("Moving Average: ${solver.movingAverage()}");
  print("Maximum Sum Subarray: ${solver.maxSumSubarray()}");
  print("Anomaly Detection: ${solver.detectAnomalies(5)}");
  print("Max Traffic in Window: ${solver.maxTrafficInWindow()}");

  // Example for positiveWordCount
  List<int> sentimentScores = [1, -1, 1, 1, -1, 1, 1, 1, -1];
  print("Positive Word Count: ${solver.positiveWordCount(sentimentScores)}");
}
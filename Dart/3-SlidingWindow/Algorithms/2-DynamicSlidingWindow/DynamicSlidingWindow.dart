import 'dart:collection';

class DynamicSlidingWindow {
  final List<int> nums; // Input array
  final int target; // Target value

  DynamicSlidingWindow(this.nums, this.target);

  // Approach 1: Minimum Subarray Sum Greater Than Target (O(n))
  // Used in financial analytics for minimum investment window
  int minSubarraySum() {
    int left = 0, sum = 0, minLength = nums.length + 1;
    for (int right = 0; right < nums.length; right++) {
      sum += nums[right]; // Add the current element to the sum
      while (sum >= target) {
        minLength = (right - left + 1) < minLength ? (right - left + 1) : minLength; // Update minLength
        sum -= nums[left++]; // Remove the leftmost element from the window
      }
    }
    return minLength == nums.length + 1 ? -1 : minLength; // Return -1 if no valid subarray is found
  }

  // Approach 2: Longest Substring with K Distinct Characters (O(n))
  // Used in text compression and NLP tokenization
  int longestKDistinct(int k) {
    Map<int, int> freqMap = {}; // Map to store frequency of elements
    int left = 0, maxLength = 0;
    for (int right = 0; right < nums.length; right++) {
      freqMap[nums[right]] = (freqMap[nums[right]] ?? 0) + 1; // Update frequency of the current element
      while (freqMap.length > k) { // Shrink the window if more than k distinct elements
        freqMap[nums[left]] = freqMap[nums[left]]! - 1;
        if (freqMap[nums[left]] == 0) freqMap.remove(nums[left]);
        left++;
      }
      maxLength = maxLength > (right - left + 1) ? maxLength : (right - left + 1); // Update maxLength
    }
    return maxLength;
  }

  // Approach 3: Maximum Sum of Variable-Length Subarray (O(n))
  // Used in network congestion control for optimal bandwidth usage
  int maxSumVariableWindow() {
    int left = 0, sum = 0, maxSum = 0;
    for (int right = 0; right < nums.length; right++) {
      sum += nums[right]; // Add the current element to the sum
      while (sum > target) { // Shrink the window if sum exceeds the target
        sum -= nums[left++];
      }
      maxSum = maxSum > sum ? maxSum : sum; // Update maxSum
    }
    return maxSum;
  }

  // Approach 4: Smallest Window Containing All Elements of Target (O(n))
  // Used in fraud detection where all key indicators must appear in a time window
  int smallestWindowContaining(List<int> targetElements) {
    Map<int, int> required = {}, windowCounts = {};
    for (int num in targetElements) {
      required[num] = (required[num] ?? 0) + 1; // Initialize required frequencies
    }
    int left = 0, matched = 0, minLength = nums.length + 1;
    for (int right = 0; right < nums.length; right++) {
      int num = nums[right];
      if (required.containsKey(num)) { // If the current element is in the target
        windowCounts[num] = (windowCounts[num] ?? 0) + 1; // Update window frequency
        if (windowCounts[num] == required[num]) matched++; // Update matched count
      }
      while (matched == required.length) { // Shrink the window when all target elements are matched
        minLength = (right - left + 1) < minLength ? (right - left + 1) : minLength; // Update minLength
        if (required.containsKey(nums[left])) { // If the left element is in the target
          if (windowCounts[nums[left]] == required[nums[left]]) matched--; // Update matched count
          windowCounts[nums[left]] = windowCounts[nums[left]]! - 1; // Update window frequency
        }
        left++;
      }
    }
    return minLength == nums.length + 1 ? -1 : minLength; // Return -1 if no valid window is found
  }

  // Approach 5: Longest Balanced Subarray (O(n))
  // Used in AI sentiment analysis for identifying stable periods
  int longestBalancedSubarray() {
    int left = 0, count = 0, maxLength = 0;
    for (int right = 0; right < nums.length; right++) {
      count += nums[right] == 1 ? 1 : -1; // Update count based on the current element
      if (count == 0) maxLength = maxLength > (right - left + 1) ? maxLength : (right - left + 1); // Update maxLength
    }
    return maxLength;
  }
}

void main() {
  List<int> nums = [2, 3, 1, 2, 4, 3];
  int target = 7;
  DynamicSlidingWindow solver = DynamicSlidingWindow(nums, target);

  print("Minimum Subarray Sum: ${solver.minSubarraySum()}");
  print("Longest Subarray with 2 Distinct: ${solver.longestKDistinct(2)}");
  print("Maximum Sum of Variable Window: ${solver.maxSumVariableWindow()}");
  print("Smallest Window Containing Elements: ${solver.smallestWindowContaining([2, 3])}");
  print("Longest Balanced Subarray: ${solver.longestBalancedSubarray()}");
}
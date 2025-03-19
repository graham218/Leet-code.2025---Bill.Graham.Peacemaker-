// Dart program implementing 'Next Greater Element' problem with multiple approaches and detailed comments
// The Next Greater Element (NGE) problem finds the first greater element for each element in an array.
// This has applications in stock price forecasting, temperature trends, and workflow scheduling.

import 'dart:collection';

/// **Approach 1: Using Stack (Efficient Solution)**
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementStack(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && nums[i] > nums[stack.last]) {
      int index = stack.removeLast();
      result[index] = nums[i];
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 2: Brute Force (Naive Solution)**
/// Time Complexity: O(n^2)
/// Space Complexity: O(1)
List<int> nextGreaterElementBruteForce(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (nums[j] > nums[i]) {
        result[i] = nums[j];
        break;
      }
    }
  }
  return result;
}

/// **Approach 3: Circular Array (Next Greater in Rotating List)**
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementCircular(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < 2 * n; i++) {
    while (stack.isNotEmpty && nums[i % n] > nums[stack.last]) {
      int index = stack.removeLast();
      result[index] = nums[i % n];
    }
    if (i < n) {
      stack.add(i);
    }
  }
  return result;
}

/// **Approach 4: Using HashMap (Optimized for Queries)**
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementWithMap(List<int> nums) {
  int n = nums.length;
  Map<int, int> ngeMap = {};
  List<int> stack = [];

  for (int num in nums.reversed) {
    while (stack.isNotEmpty && stack.last <= num) {
      stack.removeLast();
    }
    ngeMap[num] = stack.isNotEmpty ? stack.last : -1;
    stack.add(num);
  }
  return nums.map((num) => ngeMap[num]!).toList();
}

/// **Approach 5: Optimized Two-Pass Traversal**
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementTwoPass(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> rightMax = List.filled(n, -1);

  for (int i = n - 2; i >= 0; i--) {
    int j = i + 1;
    while (j != -1 && nums[j] <= nums[i]) {
      j = rightMax[j];
    }
    rightMax[i] = j;
    if (j != -1) {
      result[i] = nums[j];
    }
  }
  return result;
}

void main() {
  List<int> nums = [4, 5, 2, 10, 8];
  print("Stack Approach: ${nextGreaterElementStack(nums)}");
  print("Brute Force Approach: ${nextGreaterElementBruteForce(nums)}");
  print("Circular Array Approach: ${nextGreaterElementCircular(nums)}");
  print("HashMap Approach: ${nextGreaterElementWithMap(nums)}");
  print("Two-Pass Traversal Approach: ${nextGreaterElementTwoPass(nums)}");
}
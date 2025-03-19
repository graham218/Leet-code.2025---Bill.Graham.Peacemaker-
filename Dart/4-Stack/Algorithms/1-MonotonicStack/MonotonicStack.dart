// Dart program to implement various Monotonic Stack algorithms
// Monotonic Stack is useful for solving problems related to Next Greater Element, Stock Span, Temperature trends, etc.

import 'dart:collection';

/// **Approach 1: Next Greater Element (NGE) using Monotonic Stack**
/// Finds the next greater element for each element in an array.
/// Time Complexity: O(n), Space Complexity: O(n)
List<int> nextGreaterElement(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && nums[i] > nums[stack.last]) {
      result[stack.removeLast()] = nums[i];
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 2: Next Smaller Element (NSE) using Monotonic Stack**
/// Finds the next smaller element for each element in an array.
/// Time Complexity: O(n), Space Complexity: O(n)
List<int> nextSmallerElement(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && nums[i] < nums[stack.last]) {
      result[stack.removeLast()] = nums[i];
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 3: Stock Span Problem**
/// Calculates the number of consecutive days the stock price was less than or equal to today's price.
/// Time Complexity: O(n), Space Complexity: O(n)
List<int> stockSpan(List<int> prices) {
  int n = prices.length;
  List<int> result = List.filled(n, 1);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && prices[i] >= prices[stack.last]) {
      stack.removeLast();
    }
    result[i] = stack.isEmpty ? (i + 1) : (i - stack.last);
    stack.add(i);
  }
  return result;
}

/// **Approach 4: Maximum Area Histogram (Largest Rectangle in Histogram)**
/// Finds the largest rectangular area in a histogram.
/// Time Complexity: O(n), Space Complexity: O(n)
int largestRectangleArea(List<int> heights) {
  List<int> stack = [];
  int maxArea = 0;
  int n = heights.length;

  for (int i = 0; i <= n; i++) {
    int h = (i == n) ? 0 : heights[i];
    while (stack.isNotEmpty && h < heights[stack.last]) {
      int height = heights[stack.removeLast()];
      int width = stack.isEmpty ? i : i - stack.last - 1;
      maxArea = maxArea > height * width ? maxArea : height * width;
    }
    stack.add(i);
  }
  return maxArea;
}

/// **Approach 5: Daily Temperatures (Monotonic Stack)**
/// Finds the number of days until a warmer temperature appears.
/// Time Complexity: O(n), Space Complexity: O(n)
List<int> dailyTemperatures(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && temperatures[i] > temperatures[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

// main function
void main() {
  List<int> nums = [2, 1, 2, 4, 3];
  print("Next Greater Element: ${nextGreaterElement(nums)}");
  print("Next Smaller Element: ${nextSmallerElement(nums)}");

  List<int> stockPrices = [100, 80, 60, 70, 60, 75, 85];
  print("Stock Span: ${stockSpan(stockPrices)}");

  List<int> histogram = [2, 1, 5, 6, 2, 3];
  print("Largest Rectangle in Histogram: ${largestRectangleArea(histogram)}");

  List<int> temperatures = [73, 74, 75, 71, 69, 72, 76, 73];
  print("Daily Temperatures: ${dailyTemperatures(temperatures)}");
}
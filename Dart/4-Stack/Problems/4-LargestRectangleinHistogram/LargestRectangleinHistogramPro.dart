// Dart program to solve 'Largest Rectangle in Histogram' with real-world applications
// The problem can be applied in urban planning, stock market analysis, and land use optimization.

import 'dart:math';

/// **Approach 1: Stack-Based Optimized Solution (Urban Planning - Max Park Area in Skyline)**
/// This function finds the largest possible park area in a city skyline.
/// Each building's height represents an obstruction, and we need to maximize open space.
int maxParkArea(List<int> skyline) {
  List<int> stack = [];
  int maxArea = 0;
  int n = skyline.length;

  for (int i = 0; i <= n; i++) {
    int h = (i == n) ? 0 : skyline[i];
    while (stack.isNotEmpty && h < skyline[stack.last]) {
      int height = skyline[stack.removeLast()];
      int width = stack.isEmpty ? i : i - stack.last - 1;
      maxArea = max(maxArea, height * width);
    }
    stack.add(i);
  }
  return maxArea;
}

/// **Approach 2: Brute Force Solution (Naive Approach)**
/// Checks all possible rectangular areas by iterating over all heights.
int maxHistogramBruteForce(List<int> heights) {
  int maxArea = 0;
  int n = heights.length;

  for (int i = 0; i < n; i++) {
    int minHeight = heights[i];
    for (int j = i; j < n; j++) {
      minHeight = min(minHeight, heights[j]);
      maxArea = max(maxArea, minHeight * (j - i + 1));
    }
  }
  return maxArea;
}

/// **Approach 3: Stock Market Analysis (Max Bullish Trend)**
/// Determines the longest bullish trend where stock prices stay above a given level.
int maxBullishTrend(List<int> stockPrices) {
  int n = stockPrices.length;
  List<int> left = List.filled(n, 0), right = List.filled(n, n);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && stockPrices[stack.last] >= stockPrices[i]) {
      stack.removeLast();
    }
    left[i] = stack.isEmpty ? 0 : stack.last + 1;
    stack.add(i);
  }

  stack.clear();
  for (int i = n - 1; i >= 0; i--) {
    while (stack.isNotEmpty && stockPrices[stack.last] >= stockPrices[i]) {
      stack.removeLast();
    }
    right[i] = stack.isEmpty ? n : stack.last;
    stack.add(i);
  }

  int maxTrend = 0;
  for (int i = 0; i < n; i++) {
    maxTrend = max(maxTrend, stockPrices[i] * (right[i] - left[i]));
  }
  return maxTrend;
}

/// **Approach 4: Divide and Conquer Solution**
/// Recursively finds the minimum height and computes areas on both sides.
int maxHistogramDivideAndConquer(List<int> heights, int left, int right) {
  if (left > right) return 0;
  int minIndex = left;
  for (int i = left; i <= right; i++) {
    if (heights[i] < heights[minIndex]) {
      minIndex = i;
    }
  }
  return max(
      heights[minIndex] * (right - left + 1),
      max(
          maxHistogramDivideAndConquer(heights, left, minIndex - 1),
          maxHistogramDivideAndConquer(heights, minIndex + 1, right)
      )
  );
}

/// **Approach 5: Dynamic Programming (Land Optimization - Max Farming Land)**
/// Finds the largest piece of contiguous land available for farming within city plots.
int maxFarmingLand(List<List<int>> landGrid) {
  if (landGrid.isEmpty) return 0;
  int maxArea = 0;
  List<int> heights = List.filled(landGrid[0].length, 0);

  for (List<int> row in landGrid) {
    for (int j = 0; j < row.length; j++) {
      heights[j] = row[j] == 0 ? 0 : heights[j] + 1;
    }
    maxArea = max(maxArea, maxParkArea(heights));
  }
  return maxArea;
}

/// **Approach 6: Two-Pointer Approach for Special Cases**
/// Useful when the histogram is already sorted in increasing order.
int maxHistogramTwoPointer(List<int> heights) {
  int maxArea = 0;
  int left = 0, right = heights.length - 1;

  while (left < right) {
    int height = min(heights[left], heights[right]);
    maxArea = max(maxArea, height * (right - left));
    if (heights[left] < heights[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

void main() {
  List<int> skyline = [2, 1, 5, 6, 2, 3];
  print("Max Park Area in Skyline: ${maxParkArea(skyline)}");
  print("Max Histogram Brute Force: ${maxHistogramBruteForce(skyline)}");
  print("Max Bullish Trend: ${maxBullishTrend(skyline)}");
  print("Max Histogram Divide & Conquer: ${maxHistogramDivideAndConquer(skyline, 0, skyline.length - 1)}");

  List<List<int>> landGrid = [
    [1, 0, 1, 0, 0],
    [1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 0, 0, 1, 0]
  ];
  print("Max Farming Land Area: ${maxFarmingLand(landGrid)}");

  print("Max Histogram Two-Pointer: ${maxHistogramTwoPointer(skyline)}");
}
// Dart program to solve the 'Largest Rectangle in Histogram' problem
// Given an array representing the heights of bars in a histogram,
// find the largest rectangular area that can be formed.

import 'dart:collection';

/// Approach 1: Using Stack (Optimized Solution)
/// Time Complexity: O(n)
/// Space Complexity: O(n)
int largestRectangleStack(List<int> heights) {
  int maxArea = 0;
  List<int> stack = [];
  int n = heights.length;

  for (int i = 0; i <= n; i++) {
    int h = (i == n) ? 0 : heights[i];
    while (stack.isNotEmpty && h < heights[stack.last]) {
      int height = heights[stack.removeLast()];
      int width = stack.isEmpty ? i : i - stack.last - 1;
      maxArea = maxArea > (height * width) ? maxArea : (height * width);
    }
    stack.add(i);
  }
  return maxArea;
}

/// Approach 2: Brute Force
/// Time Complexity: O(n^2)
/// Space Complexity: O(1)
int largestRectangleBruteForce(List<int> heights) {
  int maxArea = 0;
  int n = heights.length;
  for (int i = 0; i < n; i++) {
    int minHeight = heights[i];
    for (int j = i; j < n; j++) {
      minHeight = minHeight < heights[j] ? minHeight : heights[j];
      int width = j - i + 1;
      maxArea = maxArea > (minHeight * width) ? maxArea : (minHeight * width);
    }
  }
  return maxArea;
}

/// Approach 3: Divide and Conquer
/// Time Complexity: O(n log n)
/// Space Complexity: O(log n)
int largestRectangleDivideConquer(List<int> heights, int left, int right) {
  if (left > right) return 0;
  int minIndex = left;
  for (int i = left; i <= right; i++) {
    if (heights[i] < heights[minIndex]) {
      minIndex = i;
    }
  }
  int maxArea = heights[minIndex] * (right - left + 1);
  int leftArea = largestRectangleDivideConquer(heights, left, minIndex - 1);
  int rightArea = largestRectangleDivideConquer(heights, minIndex + 1, right);
  return maxArea > leftArea ? (maxArea > rightArea ? maxArea : rightArea) : (leftArea > rightArea ? leftArea : rightArea);
}

/// Approach 4: Segment Tree (Advanced)
/// Time Complexity: O(n log n) (Construction) + O(log n) (Query)
/// Space Complexity: O(n)
class SegmentTree {
  List<int> heights;
  List<int> tree;
  SegmentTree(this.heights) : tree = List.filled(4 * heights.length, 0) {
    build(0, 0, heights.length - 1);
  }
  void build(int node, int start, int end) {
    if (start == end) {
      tree[node] = start;
    } else {
      int mid = (start + end) ~/ 2;
      build(2 * node + 1, start, mid);
      build(2 * node + 2, mid + 1, end);
      tree[node] = (heights[tree[2 * node + 1]] < heights[tree[2 * node + 2]]) ? tree[2 * node + 1] : tree[2 * node + 2];
    }
  }
  int query(int node, int start, int end, int l, int r) {
    if (l > end || r < start) return -1;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) ~/ 2;
    int leftIndex = query(2 * node + 1, start, mid, l, r);
    int rightIndex = query(2 * node + 2, mid + 1, end, l, r);
    if (leftIndex == -1) return rightIndex;
    if (rightIndex == -1) return leftIndex;
    return (heights[leftIndex] < heights[rightIndex]) ? leftIndex : rightIndex;
  }
}

int largestRectangleSegmentTree(List<int> heights) {
  SegmentTree segmentTree = SegmentTree(heights);
  return _largestRectangleHelper(heights, segmentTree, 0, heights.length - 1);
}

int _largestRectangleHelper(List<int> heights, SegmentTree segmentTree, int left, int right) {
  if (left > right) return 0;
  int minIndex = segmentTree.query(0, 0, heights.length - 1, left, right);
  int maxArea = heights[minIndex] * (right - left + 1);
  int leftArea = _largestRectangleHelper(heights, segmentTree, left, minIndex - 1);
  int rightArea = _largestRectangleHelper(heights, segmentTree, minIndex + 1, right);
  return maxArea > leftArea ? (maxArea > rightArea ? maxArea : rightArea) : (leftArea > rightArea ? leftArea : rightArea);
}

/// Approach 5: Using Monotonic Queue (Alternative Stack)
/// Time Complexity: O(n)
/// Space Complexity: O(n)
int largestRectangleMonotonicQueue(List<int> heights) {
  int maxArea = 0;
  List<int> stack = [];
  int n = heights.length;
  List<int> left = List.filled(n, 0), right = List.filled(n, n);

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && heights[stack.last] >= heights[i]) {
      stack.removeLast();
    }
    left[i] = stack.isEmpty ? 0 : stack.last + 1;
    stack.add(i);
  }

  stack.clear();
  for (int i = n - 1; i >= 0; i--) {
    while (stack.isNotEmpty && heights[stack.last] >= heights[i]) {
      stack.removeLast();
    }
    right[i] = stack.isEmpty ? n : stack.last;
    stack.add(i);
  }

  for (int i = 0; i < n; i++) {
    maxArea = maxArea > (heights[i] * (right[i] - left[i])) ? maxArea : (heights[i] * (right[i] - left[i]));
  }
  return maxArea;
}

void main() {
  List<int> histogram = [2, 1, 5, 6, 2, 3];
  print("Stack Approach: ${largestRectangleStack(histogram)}");
  print("Brute Force Approach: ${largestRectangleBruteForce(histogram)}");
  print("Divide & Conquer Approach: ${largestRectangleDivideConquer(histogram, 0, histogram.length - 1)}");
  print("Segment Tree Approach: ${largestRectangleSegmentTree(histogram)}");
  print("Monotonic Queue Approach: ${largestRectangleMonotonicQueue(histogram)}");
}

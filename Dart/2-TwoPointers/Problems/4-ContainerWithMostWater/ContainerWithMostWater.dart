void main() {
  List<int> heights = [1, 8, 6, 2, 5, 4, 8, 3, 7];

  print("Two Pointers Approach: ${maxAreaTwoPointers(heights)}");
  print("Brute Force Approach: ${maxAreaBruteForce(heights)}");
  print("Optimized Brute Force Approach: ${maxAreaOptimizedBruteForce(heights)}");
  print("Divide and Conquer Approach: ${maxAreaDivideAndConquer(heights)}");
  print("Dynamic Programming Approach: ${maxAreaDynamicProgramming(heights)}");
}

// Approach 1: Two Pointers (O(n))
int maxAreaTwoPointers(List<int> heights) {
  int left = 0, right = heights.length - 1, maxArea = 0;
  while (left < right) {
    int height = heights[left] < heights[right] ? heights[left] : heights[right];
    int width = right - left;
    maxArea = height * width > maxArea ? height * width : maxArea;
    if (heights[left] < heights[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

// Approach 2: Brute Force (O(n^2))
int maxAreaBruteForce(List<int> heights) {
  int maxArea = 0;
  for (int i = 0; i < heights.length; i++) {
    for (int j = i + 1; j < heights.length; j++) {
      int area = (j - i) * (heights[i] < heights[j] ? heights[i] : heights[j]);
      maxArea = area > maxArea ? area : maxArea;
    }
  }
  return maxArea;
}

// Approach 3: Optimized Brute Force (O(n log n))
int maxAreaOptimizedBruteForce(List<int> heights) {
  List<int> sortedHeights = List.from(heights)..sort();
  int maxArea = 0;
  for (int i = 0; i < sortedHeights.length; i++) {
    for (int j = i + 1; j < sortedHeights.length; j++) {
      int width = j - i;
      int height = sortedHeights[i];
      maxArea = height * width > maxArea ? height * width : maxArea;
    }
  }
  return maxArea;
}

// Approach 4: Divide and Conquer (O(n log n))
int maxAreaDivideAndConquer(List<int> heights) {
  return _divideAndConquer(heights, 0, heights.length - 1);
}

int _divideAndConquer(List<int> heights, int left, int right) {
  if (left >= right) return 0;
  int mid = (left + right) ~/ 2;
  int leftArea = _divideAndConquer(heights, left, mid);
  int rightArea = _divideAndConquer(heights, mid + 1, right);
  int crossArea = _crossArea(heights, left, right);
  return [leftArea, rightArea, crossArea].reduce((a, b) => a > b ? a : b);
}

int _crossArea(List<int> heights, int left, int right) {
  int maxArea = 0, mid = (left + right) ~/ 2;
  int i = mid, j = mid + 1;
  while (i >= left && j <= right) {
    int height = heights[i] < heights[j] ? heights[i] : heights[j];
    int width = j - i;
    maxArea = height * width > maxArea ? height * width : maxArea;
    if (i > left) i--;
    if (j < right) j++;
  }
  return maxArea;
}

// Approach 5: Dynamic Programming (O(n^2))
int maxAreaDynamicProgramming(List<int> heights) {
  int n = heights.length;
  List<List<int>> dp = List.generate(n, (i) => List.filled(n, 0));
  int maxArea = 0;
  for (int len = 1; len < n; len++) {
    for (int i = 0; i + len < n; i++) {
      int j = i + len;
      dp[i][j] = (j - i) * (heights[i] < heights[j] ? heights[i] : heights[j]);
      maxArea = dp[i][j] > maxArea ? dp[i][j] : maxArea;
    }
  }
  return maxArea;
}
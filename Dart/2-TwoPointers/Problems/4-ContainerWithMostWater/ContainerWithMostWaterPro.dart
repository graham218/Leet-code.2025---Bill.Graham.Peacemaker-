void main() {
  List<int> heights = [1, 8, 6, 2, 5, 4, 8, 3, 7]; // Predefined input

  print("Two Pointers Approach: ${maxAreaTwoPointers(heights)}");
  print("Brute Force Approach: ${maxAreaBruteForce(heights)}");
  print("Divide and Conquer Approach: ${maxAreaDivideAndConquer(heights)}");
}

// Approach 1: Two Pointers (Optimized O(n))
int maxAreaTwoPointers(List<int> heights) {
  int left = 0, right = heights.length - 1;
  int maxArea = 0;
  while (left < right) {
    int h = heights[left] < heights[right] ? heights[left] : heights[right];
    maxArea = maxArea > h * (right - left) ? maxArea : h * (right - left);
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
      int h = heights[i] < heights[j] ? heights[i] : heights[j];
      maxArea = maxArea > h * (j - i) ? maxArea : h * (j - i);
    }
  }
  return maxArea;
}

// Approach 3: Divide and Conquer (Corrected Implementation)
int maxAreaDivideAndConquer(List<int> heights) {
  return _divideAndConquer(heights, 0, heights.length - 1);
}

int _divideAndConquer(List<int> heights, int left, int right) {
  if (left >= right) return 0;

  int mid = (left + right) ~/ 2;

  // Recursively find the maximum area in the left and right subarrays
  int leftMax = _divideAndConquer(heights, left, mid);
  int rightMax = _divideAndConquer(heights, mid + 1, right);

  // Find the maximum area across the divide
  int crossMax = _findCrossMax(heights, left, mid, right);

  // Return the maximum of the three areas
  return [leftMax, rightMax, crossMax].reduce((a, b) => a > b ? a : b);
}

int _findCrossMax(List<int> heights, int left, int mid, int right) {
  int i = mid, j = mid + 1;
  int maxArea = 0;
  int minHeight = heights[i] < heights[j] ? heights[i] : heights[j];
  maxArea = minHeight * (j - i);

  // Expand outwards from the middle to find the maximum cross area
  while (i >= left || j <= right) {
    if (i > left && (j == right || heights[i - 1] > heights[j + 1])) {
      i--;
      minHeight = minHeight < heights[i] ? minHeight : heights[i];
    } else if (j < right && (i == left || heights[j + 1] > heights[i - 1])) {
      j++;
      minHeight = minHeight < heights[j] ? minHeight : heights[j];
    } else {
      break;
    }
    maxArea = maxArea > minHeight * (j - i) ? maxArea : minHeight * (j - i);
  }

  return maxArea;
}
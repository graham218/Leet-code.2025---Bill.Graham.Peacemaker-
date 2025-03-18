// void main() {
//   List<int> heights = [1, 8, 6, 2, 5, 4, 8, 3, 7]; // Predefined input
//
//   print("Two Pointers Approach: \${maxAreaTwoPointers(heights)}");
//   print("Brute Force Approach: \${maxAreaBruteForce(heights)}");
//   print("Divide and Conquer Approach: \${maxAreaDivideAndConquer(heights)}");
// }
//
// // Approach 1: Two Pointers (Optimized O(n))
// int maxAreaTwoPointers(List<int> heights) {
//   int left = 0, right = heights.length - 1;
//   int maxArea = 0;
//   while (left < right) {
//     int h = heights[left] < heights[right] ? heights[left] : heights[right];
//     maxArea = maxArea > h * (right - left) ? maxArea : h * (right - left);
//     if (heights[left] < heights[right]) {
//       left++;
//     } else {
//       right--;
//     }
//   }
//   return maxArea;
// }
//
// // Approach 2: Brute Force (O(n^2))
// int maxAreaBruteForce(List<int> heights) {
//   int maxArea = 0;
//   for (int i = 0; i < heights.length; i++) {
//     for (int j = i + 1; j < heights.length; j++) {
//       int h = heights[i] < heights[j] ? heights[i] : heights[j];
//       maxArea = maxArea > h * (j - i) ? maxArea : h * (j - i);
//     }
//   }
//   return maxArea;
// }
//
// // Approach 3: Divide and Conquer (O(n log n))
// int maxAreaDivideAndConquer(List<int> heights) {
//   if (heights.length < 2) return 0;
//   int mid = heights.length ~/ 2;
//   int leftMax = maxAreaDivideAndConquer(heights.sublist(0, mid));
//   int rightMax = maxAreaDivideAndConquer(heights.sublist(mid));
//   return leftMax > rightMax ? leftMax : rightMax;
// }

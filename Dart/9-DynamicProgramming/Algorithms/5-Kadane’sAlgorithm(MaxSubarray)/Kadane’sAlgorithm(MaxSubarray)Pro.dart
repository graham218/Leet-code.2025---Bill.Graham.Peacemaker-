// Advanced Kadane’s Algorithm Implementations in Dart
// Six distinct approaches with real-world applications

import 'dart:math';

// 1. Classic Kadane's Algorithm (O(n) Complexity)
int kadaneClassic(List<int> arr) {
  int maxSum = arr[0], currentSum = arr[0];
  for (int i = 1; i < arr.length; i++) {
    currentSum = max(arr[i], currentSum + arr[i]);
    maxSum = max(maxSum, currentSum);
  }
  return maxSum;
}

// 2. Kadane's Algorithm with Indices (Tracking Start & End Index)
List<int> kadaneWithIndices(List<int> arr) {
  int maxSum = arr[0], currentSum = arr[0], start = 0, end = 0, tempStart = 0;
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > currentSum + arr[i]) {
      currentSum = arr[i];
      tempStart = i;
    } else {
      currentSum += arr[i];
    }
    if (currentSum > maxSum) {
      maxSum = currentSum;
      start = tempStart;
      end = i;
    }
  }
  return [maxSum, start, end];
}

// 3. Kadane's Algorithm for 2D Matrices (Max Sum Subrectangle)
int kadane2D(List<List<int>> matrix) {
  int rows = matrix.length, cols = matrix[0].length;
  int maxSum = -1 << 30;
  for (int left = 0; left < cols; left++) {
    List<int> temp = List.filled(rows, 0);
    for (int right = left; right < cols; right++) {
      for (int i = 0; i < rows; i++) {
        temp[i] += matrix[i][right];
      }
      maxSum = max(maxSum, kadaneClassic(temp));
    }
  }
  return maxSum;
}

// 4. Kadane’s Algorithm for Circular Arrays (Max Circular Subarray Sum)
int kadaneCircular(List<int> arr) {
  int maxKadane = kadaneClassic(arr);
  int totalSum = arr.reduce((a, b) => a + b);
  List<int> negArr = arr.map((e) => -e).toList();
  int maxWrap = totalSum + kadaneClassic(negArr);
  return max(maxKadane, maxWrap);
}

// 5. Real-World Application: Stock Market Maximum Profit Prediction
int maxStockProfit(List<int> prices) {
  List<int> changes = List.generate(prices.length - 1, (i) => prices[i + 1] - prices[i]);
  return max(0, kadaneClassic(changes));
}

// 6. Real-World Application: Sentiment Analysis - Maximum Positive Sentiment Streak
int maxSentimentStreak(List<int> sentiments) {
  return kadaneClassic(sentiments);
}

void main() {
  List<int> arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
  print("Classic Kadane: ${kadaneClassic(arr)}");
  print("Kadane with Indices: ${kadaneWithIndices(arr)}");
  print("Kadane Circular: ${kadaneCircular(arr)}");

  List<List<int>> matrix = [
    [1, 2, -1, -4, -20],
    [-8, -3, 4, 2, 1],
    [3, 8, 10, 1, 3],
    [-4, -1, 1, 7, -6]
  ];
  print("Kadane 2D: ${kadane2D(matrix)}");

  List<int> stockPrices = [100, 180, 260, 310, 40, 535, 695];
  print("Max Stock Profit: ${maxStockProfit(stockPrices)}");

  List<int> sentiments = [1, -1, 2, 3, -5, 4, 2, -2, 1, 3];
  print("Max Sentiment Streak: ${maxSentimentStreak(sentiments)}");
}

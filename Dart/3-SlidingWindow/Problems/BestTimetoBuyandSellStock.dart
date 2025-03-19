// Best Time to Buy and Sell Stock - Sliding Window Approaches in Dart
// The goal is to find the maximum profit from a given list of stock prices.

import 'dart:math';

// Approach 1: Brute Force (O(n^2))
// Check all possible buy-sell pairs and track the maximum profit.
int maxProfitBruteForce(List<int> prices) {
  int maxProfit = 0;
  for (int i = 0; i < prices.length - 1; i++) {
    for (int j = i + 1; j < prices.length; j++) {
      int profit = prices[j] - prices[i];
      if (profit > maxProfit) {
        maxProfit = profit;
      }
    }
  }
  return maxProfit;
}

// Approach 2: Sliding Window (Two Pointers) (O(n))
// Maintain a minimum price and compute the max profit dynamically.
int maxProfitSlidingWindow(List<int> prices) {
  if (prices.isEmpty) return 0;

  int minPrice = prices[0];
  int maxProfit = 0;
  for (int i = 1; i < prices.length; i++) {
    if (prices[i] < minPrice) {
      minPrice = prices[i];
    } else {
      maxProfit = max(maxProfit, prices[i] - minPrice);
    }
  }
  return maxProfit;
}

// Approach 3: Sliding Window with Prefix & Suffix Arrays (O(n))
// Compute min price up to each day and max price from each day, then compute profit.
int maxProfitPrefixSuffix(List<int> prices) {
  if (prices.isEmpty) return 0;

  int n = prices.length;
  List<int> minLeft = List.filled(n, 0);
  List<int> maxRight = List.filled(n, 0);

  minLeft[0] = prices[0];
  for (int i = 1; i < n; i++) {
    minLeft[i] = min(prices[i], minLeft[i - 1]);
  }

  maxRight[n - 1] = prices[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    maxRight[i] = max(prices[i], maxRight[i + 1]);
  }

  int maxProfit = 0;
  for (int i = 0; i < n; i++) {
    maxProfit = max(maxProfit, maxRight[i] - minLeft[i]);
  }
  return maxProfit;
}

// Approach 4: Kadane's Algorithm for Maximum Subarray Sum (O(n))
// Convert the problem to finding the maximum sum subarray of price changes.
int maxProfitKadane(List<int> prices) {
  if (prices.isEmpty) return 0;

  int maxCurrent = 0, maxSoFar = 0;
  for (int i = 1; i < prices.length; i++) {
    int diff = prices[i] - prices[i - 1];
    maxCurrent = max(0, maxCurrent + diff);
    maxSoFar = max(maxSoFar, maxCurrent);
  }
  return maxSoFar;
}

// Approach 5: Sliding Window with Deque (O(n))
// Uses a deque to maintain the min values dynamically.
int maxProfitDeque(List<int> prices) {
  if (prices.isEmpty) return 0;

  int maxProfit = 0;
  List<int> deque = [];
  for (int price in prices) {
    while (deque.isNotEmpty && deque.first > price) {
      deque.removeAt(0);
    }
    deque.add(price);
    maxProfit = max(maxProfit, price - deque.first);
  }
  return maxProfit;
}

// Main function to test different approaches
void main() {
  List<int> stockPrices = [7, 1, 5, 3, 6, 4];
  print("Brute Force: ${maxProfitBruteForce(stockPrices)}");
  print("Sliding Window: ${maxProfitSlidingWindow(stockPrices)}");
  print("Prefix-Suffix: ${maxProfitPrefixSuffix(stockPrices)}");
  print("Kadane's Algorithm: ${maxProfitKadane(stockPrices)}");
  print("Sliding Window with Deque: ${maxProfitDeque(stockPrices)}");
}
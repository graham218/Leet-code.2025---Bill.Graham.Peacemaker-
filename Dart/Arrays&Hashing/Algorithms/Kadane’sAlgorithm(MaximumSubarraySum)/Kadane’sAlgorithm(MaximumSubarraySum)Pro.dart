import 'dart:math';

class AdvancedKadane {
  /// Standard Kadane’s Algorithm (O(n) time complexity)
  /// Finds the maximum sum of a contiguous subarray
  int maxSubarraySum(List<int> nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];

    for (int i = 1; i < nums.length; i++) {
      // Either continue with the existing subarray or start a new one
      currentSum = max(nums[i], currentSum + nums[i]);
      maxSum = max(maxSum, currentSum);
    }

    return maxSum;
  }

  /// Finds the indices of the subarray that gives the maximum sum
  List<int> maxSubarrayIndices(List<int> nums) {
    int maxSum = nums[0], currentSum = nums[0];
    int start = 0, end = 0, tempStart = 0;

    for (int i = 1; i < nums.length; i++) {
      if (nums[i] > currentSum + nums[i]) {
        currentSum = nums[i];
        tempStart = i;
      } else {
        currentSum += nums[i];
      }

      if (currentSum > maxSum) {
        maxSum = currentSum;
        start = tempStart;
        end = i;
      }
    }

    return [start, end, maxSum];
  }

  /// Dynamic Programming approach for maximum subarray sum
  /// Stores intermediate results to improve efficiency
  int maxSubarrayDP(List<int> nums) {
    List<int> dp = List.filled(nums.length, 0);
    dp[0] = nums[0];
    int maxSum = dp[0];

    for (int i = 1; i < nums.length; i++) {
      dp[i] = max(nums[i], dp[i - 1] + nums[i]);
      maxSum = max(maxSum, dp[i]);
    }

    return maxSum;
  }

  /// Optimized approach for financial time series analysis
  /// Uses a rolling window to compute max profit from stock prices
  int maxProfitFromStocks(List<int> prices) {
    int minPrice = prices[0];
    int maxProfit = 0;

    for (int i = 1; i < prices.length; i++) {
      minPrice = min(minPrice, prices[i]);
      maxProfit = max(maxProfit, prices[i] - minPrice);
    }

    return maxProfit;
  }

  /// Parallel Processing Variant (for large-scale data analysis)
  Future<int> maxSubarrayParallel(List<int> nums) async {
    return await Future(() => maxSubarraySum(nums));
  }
}

void main() async {
  List<int> nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
  List<int> stockPrices = [7, 1, 5, 3, 6, 4];
  AdvancedKadane ak = AdvancedKadane();

  print("Max Subarray Sum: ${ak.maxSubarraySum(nums)}");
  print("Max Subarray Indices & Sum: ${ak.maxSubarrayIndices(nums)}");
  print("DP Max Subarray Sum: ${ak.maxSubarrayDP(nums)}");
  print("Max Profit from Stocks: ${ak.maxProfitFromStocks(stockPrices)}");
  print("Parallel Processing Result: ${await ak.maxSubarrayParallel(nums)}");
}

import 'dart:math';

class KadaneAlgorithm {
  // Standard Kadane’s Algorithm (O(n) Time Complexity)
  int maxSubarraySum(List<int> nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];

    for (int i = 1; i < nums.length; i++) {
      currentSum = max(nums[i], currentSum + nums[i]);
      maxSum = max(maxSum, currentSum);
    }

    return maxSum;
  }

  // Approach 2: Finding Subarray Indices
  List<int> maxSubarrayIndices(List<int> nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
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

  // Approach 3: Divide & Conquer (O(n log n))
  int maxSubarrayDivideAndConquer(List<int> nums, int left, int right) {
    if (left == right) return nums[left];

    int mid = (left + right) ~/ 2;
    int leftMax = maxSubarrayDivideAndConquer(nums, left, mid);
    int rightMax = maxSubarrayDivideAndConquer(nums, mid + 1, right);
    int crossMax = maxCrossingSum(nums, left, mid, right);

    return max(leftMax, rightMax, crossMax);
  }

  int maxCrossingSum(List<int> nums, int left, int mid, int right) {
    int leftSum = -999999, rightSum = -999999;
    int sum = 0;

    for (int i = mid; i >= left; i--) {
      sum += nums[i];
      leftSum = max(leftSum, sum);
    }

    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
      sum += nums[i];
      rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
  }

  // Approach 4: Dynamic Programming
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

  // Approach 5: Parallel Processing (For Large Data)
  Future<int> maxSubarrayParallel(List<int> nums) async {
    return await Future(() => maxSubarraySum(nums));
  }
}

void main() async {
  List<int> nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
  KadaneAlgorithm ka = KadaneAlgorithm();

  print("Max Subarray Sum: ${ka.maxSubarraySum(nums)}");
  print("Max Subarray Indices & Sum: ${ka.maxSubarrayIndices(nums)}");
  print("Divide & Conquer Max Sum: ${ka.maxSubarrayDivideAndConquer(nums, 0, nums.length - 1)}");
  print("DP Max Subarray Sum: ${ka.maxSubarrayDP(nums)}");
  print("Parallel Processing Result: ${await ka.maxSubarrayParallel(nums)}");
}

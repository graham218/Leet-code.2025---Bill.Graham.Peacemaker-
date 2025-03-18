import 'dart:math';

class MaximumSubarray {
  final List<int> nums;

  MaximumSubarray(this.nums);

  // Approach 1: Kadane's Algorithm (Optimized O(n))
  int maxSubarrayKadane() {
    int maxSum = nums[0];
    int currentSum = nums[0];

    for (int i = 1; i < nums.length; i++) {
      currentSum = max(nums[i], currentSum + nums[i]);
      maxSum = max(maxSum, currentSum);
    }
    return maxSum;
  }

  // Approach 2: Divide and Conquer (O(n log n))
  int maxSubarrayDivideConquer(int left, int right) {
    if (left == right) return nums[left];

    int mid = (left + right) ~/ 2;
    int leftMax = maxSubarrayDivideConquer(left, mid);
    int rightMax = maxSubarrayDivideConquer(mid + 1, right);
    int crossMax = maxCrossingSum(left, mid, right);

    return max(leftMax, max(rightMax, crossMax));
  }

  int maxCrossingSum(int left, int mid, int right) {
    int leftSum = -1e9.toInt(), rightSum = -1e9.toInt();
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

  // Approach 3: Dynamic Programming (O(n))
  int maxSubarrayDP() {
    List<int> dp = List.filled(nums.length, 0);
    dp[0] = nums[0];
    int maxSum = dp[0];

    for (int i = 1; i < nums.length; i++) {
      dp[i] = max(nums[i], dp[i - 1] + nums[i]);
      maxSum = max(maxSum, dp[i]);
    }
    return maxSum;
  }

  // Approach 4: Sliding Window Technique (For Non-negative Subarrays)
  int maxSubarraySlidingWindow() {
    int maxSum = 0, currentSum = 0;

    for (int num in nums) {
      currentSum = max(0, currentSum + num);
      maxSum = max(maxSum, currentSum);
    }

    return maxSum;
  }

  // Approach 5: Parallel Processing (Using Isolates for Large Data)
  Future<int> maxSubarrayParallel() async {
    return await Future(() => maxSubarrayKadane());
  }
}

void main() async {
  List<int> nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
  MaximumSubarray ms = MaximumSubarray(nums);

  print("Kadane's Algorithm: ${ms.maxSubarrayKadane()}");
  print("Divide & Conquer: ${ms.maxSubarrayDivideConquer(0, nums.length - 1)}");
  print("Dynamic Programming: ${ms.maxSubarrayDP()}");
  print("Sliding Window: ${ms.maxSubarraySlidingWindow()}");
  print("Parallel Processing: ${await ms.maxSubarrayParallel()}");
}

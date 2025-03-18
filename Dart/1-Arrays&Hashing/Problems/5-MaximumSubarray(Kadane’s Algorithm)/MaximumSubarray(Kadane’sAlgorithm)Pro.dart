import 'dart:math';
import 'dart:async';

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

  // Approach 4: Streaming Data Processing (Real-World Finance Application)
  Stream<int> maxSubarrayStreaming(Stream<int> inputStream) async* {
    int maxSum = -1e9.toInt(), currentSum = 0;
    await for (var num in inputStream) {
      currentSum = max(num, currentSum + num);
      maxSum = max(maxSum, currentSum);
      yield maxSum;
    }
  }

  // Approach 5: Cloud-Based API Processing (Real-World API Implementation)
  Future<Map<String, dynamic>> maxSubarrayAPI() async {
    return Future.delayed(Duration(seconds: 2), () => {
      "input": nums,
      "max_sum": maxSubarrayKadane(),
      "status": "success",
      "processed_at": DateTime.now().toString()
    });
  }
}

void main() async {
  List<int> nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
  MaximumSubarray ms = MaximumSubarray(nums);

  print("Kadane's Algorithm: ${ms.maxSubarrayKadane()}");
  print("Divide & Conquer: ${ms.maxSubarrayDivideConquer(0, nums.length - 1)}");
  print("Dynamic Programming: ${ms.maxSubarrayDP()}");
  print("Cloud API Response: ${await ms.maxSubarrayAPI()}");

  Stream<int> stream = Stream.fromIterable(nums);
  ms.maxSubarrayStreaming(stream).listen((value) {
    print("Streaming Max Subarray Sum: $value");
  });
}

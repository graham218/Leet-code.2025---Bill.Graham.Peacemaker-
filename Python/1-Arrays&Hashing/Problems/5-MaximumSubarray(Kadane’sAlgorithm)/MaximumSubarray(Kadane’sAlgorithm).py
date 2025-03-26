"""
Problem: Maximum Subarray (Kadane’s Algorithm and Variants)
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Approaches:
1. Kadane’s Algorithm (Standard Approach)
2. Divide and Conquer (Optimized for Large Data)
3. Dynamic Programming (Memoization Technique)
4. Sliding Window (For Non-Negative Numbers)
5. Prefix Sum Optimization (Handling Negative Values)
"""

def max_subarray_kadane(nums):
    """
    Approach 1: Kadane’s Algorithm (Iterative DP)
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    max_sum = float('-inf')
    current_sum = 0

    for num in nums:
        current_sum = max(num, current_sum + num)
        max_sum = max(max_sum, current_sum)

    return max_sum


def max_subarray_divide_and_conquer(nums):
    """
    Approach 2: Divide and Conquer
    Time Complexity: O(n log n)
    Space Complexity: O(log n) (Recursion stack)
    """
    def helper(left, right):
        if left == right:
            return nums[left]

        mid = (left + right) // 2
        left_sum = helper(left, mid)
        right_sum = helper(mid + 1, right)

        cross_sum = nums[mid]
        temp_sum = nums[mid]
        for i in range(mid - 1, left - 1, -1):
            temp_sum += nums[i]
            cross_sum = max(cross_sum, temp_sum)

        temp_sum = cross_sum
        for i in range(mid + 1, right + 1):
            temp_sum += nums[i]
            cross_sum = max(cross_sum, temp_sum)

        return max(left_sum, right_sum, cross_sum)

    return helper(0, len(nums) - 1)


def max_subarray_dp(nums):
    """
    Approach 3: Dynamic Programming (Memoization)
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    dp = [0] * len(nums)
    dp[0] = nums[0]
    max_sum = dp[0]

    for i in range(1, len(nums)):
        dp[i] = max(nums[i], dp[i - 1] + nums[i])
        max_sum = max(max_sum, dp[i])

    return max_sum


def max_subarray_sliding_window(nums):
    """
    Approach 4: Sliding Window (Only for Non-Negative Numbers)
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    max_sum, window_sum, left = 0, 0, 0

    for right in range(len(nums)):
        if nums[right] < 0:
            left = right + 1
            window_sum = 0
            continue

        window_sum += nums[right]
        max_sum = max(max_sum, window_sum)

    return max_sum if max_sum != 0 else max(nums)


def max_subarray_prefix_sum(nums):
    """
    Approach 5: Prefix Sum Optimization
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    min_prefix, max_sum, prefix_sum = 0, float('-inf'), 0

    for num in nums:
        prefix_sum += num
        max_sum = max(max_sum, prefix_sum - min_prefix)
        min_prefix = min(min_prefix, prefix_sum)

    return max_sum


# Test Cases
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
print("Kadane's Algorithm:", max_subarray_kadane(nums))
print("Divide & Conquer:", max_subarray_divide_and_conquer(nums))
print("Dynamic Programming:", max_subarray_dp(nums))
print("Sliding Window:", max_subarray_sliding_window(nums))
print("Prefix Sum Optimization:", max_subarray_prefix_sum(nums))

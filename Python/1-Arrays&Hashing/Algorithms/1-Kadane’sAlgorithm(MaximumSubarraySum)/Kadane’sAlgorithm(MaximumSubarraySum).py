"""
Problem: Maximum Subarray Sum (Kadane’s Algorithm and Variants)
Given an integer array nums, find the contiguous subarray (containing at least one number) that has the largest sum and return its sum.

Approaches:
1. Kadane’s Algorithm (Classic Dynamic Programming Solution)
2. Divide and Conquer Approach
3. Prefix Sum Optimization
4. Sliding Window for Positive Subarrays
5. Monotonic Queue Optimization
"""

def max_subarray_kadane(nums):
    """
    Approach 1: Kadane’s Algorithm
    Uses dynamic programming to find the maximum subarray sum.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    max_sum = current_sum = nums[0]
    for num in nums[1:]:
        current_sum = max(num, current_sum + num)
        max_sum = max(max_sum, current_sum)
    return max_sum

def max_subarray_divide_conquer(nums, left, right):
    """
    Approach 2: Divide and Conquer
    Recursively finds the maximum subarray sum.
    Time Complexity: O(n log n)
    Space Complexity: O(log n)
    """
    if left == right:
        return nums[left]
    mid = (left + right) // 2
    left_max = max_subarray_divide_conquer(nums, left, mid)
    right_max = max_subarray_divide_conquer(nums, mid + 1, right)
    cross_max = max_crossing_sum(nums, left, mid, right)
    return max(left_max, right_max, cross_max)

def max_crossing_sum(nums, left, mid, right):
    left_sum = float('-inf')
    total = 0
    for i in range(mid, left - 1, -1):
        total += nums[i]
        left_sum = max(left_sum, total)
    right_sum = float('-inf')
    total = 0
    for i in range(mid + 1, right + 1):
        total += nums[i]
        right_sum = max(right_sum, total)
    return left_sum + right_sum

def max_subarray_prefix_sum(nums):
    """
    Approach 3: Prefix Sum Optimization
    Uses prefix sums to calculate maximum subarray sum efficiently.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    min_prefix = 0
    max_sum = float('-inf')
    prefix_sum = 0
    for num in nums:
        prefix_sum += num
        max_sum = max(max_sum, prefix_sum - min_prefix)
        min_prefix = min(min_prefix, prefix_sum)
    return max_sum

def max_subarray_sliding_window(nums):
    """
    Approach 4: Sliding Window Optimization
    Works efficiently when only positive sums are considered.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    left = 0
    max_sum = float('-inf')
    current_sum = 0
    for right in range(len(nums)):
        current_sum += nums[right]
        while current_sum < 0 and left <= right:
            current_sum -= nums[left]
            left += 1
        max_sum = max(max_sum, current_sum)
    return max_sum

def max_subarray_monotonic_queue(nums):
    """
    Approach 5: Monotonic Queue Optimization
    Uses a deque to maintain a non-decreasing order of prefix sums.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    from collections import deque
    prefix_sum = 0
    min_prefix = deque([0])
    max_sum = float('-inf')
    for num in nums:
        prefix_sum += num
        max_sum = max(max_sum, prefix_sum - min_prefix[0])
        while min_prefix and min_prefix[-1] > prefix_sum:
            min_prefix.pop()
        min_prefix.append(prefix_sum)
    return max_sum

# Test Case
nums = [3, -1, 4, -1, 2, -5, 4]
print("Kadane’s Algorithm:", max_subarray_kadane(nums))
print("Divide and Conquer:", max_subarray_divide_conquer(nums, 0, len(nums) - 1))
print("Prefix Sum Optimization:", max_subarray_prefix_sum(nums))
print("Sliding Window Optimization:", max_subarray_sliding_window(nums))
print("Monotonic Queue Optimization:", max_subarray_monotonic_queue(nums))

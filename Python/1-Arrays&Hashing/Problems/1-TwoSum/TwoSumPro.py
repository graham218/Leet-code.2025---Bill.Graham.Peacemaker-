"""
Problem: Two Sum (Advanced Solutions)
Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.
Each input is assumed to have exactly one solution, and elements cannot be used twice.
"""

def two_sum_counter(nums, target):
    """
    Approach 1: Using Counter (Frequency Hashing)
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    from collections import Counter
    num_count = Counter(nums)
    for i, num in enumerate(nums):
        complement = target - num
        if complement in num_count:
            if complement != num or num_count[complement] > 1:
                return [i, nums.index(complement, i + 1)]
    return []

def two_sum_sorted_binary_search(nums, target):
    """
    Approach 2: Binary Search on Sorted List
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    from bisect import bisect_left
    sorted_nums = sorted((val, i) for i, val in enumerate(nums))
    for i, (val, original_index) in enumerate(sorted_nums):
        complement = target - val
        j = bisect_left(sorted_nums, (complement,))
        if j < len(sorted_nums) and sorted_nums[j][0] == complement and i != j:
            return [original_index, sorted_nums[j][1]]
    return []

def two_sum_deduplicated(nums, target):
    """
    Approach 3: Deduplicated Hashing
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    seen = {}
    for i, num in enumerate(nums):
        if num not in seen:
            seen[num] = i
        complement = target - num
        if complement in seen and seen[complement] != i:
            return [seen[complement], i]
    return []

def two_sum_xor_trick(nums, target):
    """
    Approach 4: XOR Trick (Alternative Hashing)
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    num_map = {}
    for i, num in enumerate(nums):
        xor_complement = target ^ num
        if xor_complement in num_map:
            return [num_map[xor_complement], i]
        num_map[num] = i
    return []

def two_sum_modulo(nums, target):
    """
    Approach 5: Modulo Reduction Trick
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    mod_map = {}
    for i, num in enumerate(nums):
        mod_value = target % num if num != 0 else target
        if mod_value in mod_map:
            return [mod_map[mod_value], i]
        mod_map[num] = i
    return []

def two_sum_matrix_reduction(nums, target):
    """
    Approach 6: Matrix-Based Reduction (Advanced Math)
    Time Complexity: O(n^2) (for practical use)
    Space Complexity: O(n^2) (depends on implementation)
    """
    import numpy as np
    matrix = np.array([[i + j for j in nums] for i in nums])
    indices = np.argwhere(matrix == target)
    for i, j in indices:
        if i != j:
            return [i, j]
    return []

# Test cases
nums = [3, 2, 4, 6, 7]
target = 9
print("Counter Method:", two_sum_counter(nums, target))
print("Binary Search:", two_sum_sorted_binary_search(nums, target))
print("Deduplicated Hashing:", two_sum_deduplicated(nums, target))
print("XOR Trick:", two_sum_xor_trick(nums, target))
print("Modulo Reduction:", two_sum_modulo(nums, target))
print("Matrix Reduction:", two_sum_matrix_reduction(nums, target))

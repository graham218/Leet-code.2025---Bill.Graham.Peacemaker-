"""
Problem: Two Sum
Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
"""

def two_sum_brute_force(nums, target):
    """
    Approach 1: Brute Force
    Time Complexity: O(n^2) - Nested loops checking all pairs
    Space Complexity: O(1) - No extra space used
    """
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]
    return []

def two_sum_hash_map(nums, target):
    """
    Approach 2: Hash Map
    Time Complexity: O(n) - Single pass lookup
    Space Complexity: O(n) - Extra space for hash map
    """
    num_map = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in num_map:
            return [num_map[complement], i]
        num_map[num] = i
    return []

def two_sum_two_pointer(nums, target):
    """
    Approach 3: Two Pointer (Only for sorted input)
    Time Complexity: O(n log n) - Sorting required
    Space Complexity: O(1) - No extra space used
    """
    sorted_nums = sorted(enumerate(nums), key=lambda x: x[1])
    left, right = 0, len(nums) - 1
    while left < right:
        sum_value = sorted_nums[left][1] + sorted_nums[right][1]
        if sum_value == target:
            return [sorted_nums[left][0], sorted_nums[right][0]]
        elif sum_value < target:
            left += 1
        else:
            right -= 1
    return []

def two_sum_one_pass(nums, target):
    """
    Approach 4: One-pass Hash Map
    Time Complexity: O(n) - Single pass lookup
    Space Complexity: O(n) - Extra space for hash map
    """
    num_map = {}
    for i, num in enumerate(nums):
        if target - num in num_map:
            return [num_map[target - num], i]
        num_map[num] = i
    return []

def two_sum_combinations(nums, target):
    """
    Approach 5: Using itertools.combinations
    Time Complexity: O(n^2) - Generates all pairs
    Space Complexity: O(1) - No extra space used
    """
    from itertools import combinations
    for (i, j) in combinations(range(len(nums)), 2):
        if nums[i] + nums[j] == target:
            return [i, j]
    return []

# Test cases
nums = [2, 7, 11, 15]
target = 9
print("Brute Force:", two_sum_brute_force(nums, target))
print("Hash Map:", two_sum_hash_map(nums, target))
print("Two Pointer:", two_sum_two_pointer(nums, target))
print("One Pass Hash Map:", two_sum_one_pass(nums, target))
print("Combinations:", two_sum_combinations(nums, target))

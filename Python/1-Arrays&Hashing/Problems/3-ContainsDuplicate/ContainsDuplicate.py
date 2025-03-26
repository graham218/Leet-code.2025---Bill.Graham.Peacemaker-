"""
Problem: Contains Duplicate
Given an integer array nums, return true if any value appears at least twice in the array, and false if every element is distinct.

Approaches:
1. Brute Force (Nested Loops)
2. Sorting
3. Hash Set
4. Hash Map (Dictionary with Counts)
5. Bit Manipulation (for small number ranges)
"""

def contains_duplicate_brute_force(nums):
    """
    Approach 1: Brute Force (Nested Loops)
    Compare each element with every other element.
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    """
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] == nums[j]:
                return True
    return False

def contains_duplicate_sorting(nums):
    """
    Approach 2: Sorting
    Sort the array and check for consecutive duplicates.
    Time Complexity: O(n log n)
    Space Complexity: O(1) if sorting in place, O(n) otherwise
    """
    nums.sort()
    for i in range(1, len(nums)):
        if nums[i] == nums[i - 1]:
            return True
    return False

def contains_duplicate_hash_set(nums):
    """
    Approach 3: Hash Set
    Use a hash set to track seen numbers.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    seen = set()
    for num in nums:
        if num in seen:
            return True
        seen.add(num)
    return False

def contains_duplicate_hash_map(nums):
    """
    Approach 4: Hash Map (Dictionary with Counts)
    Store frequency of each number in a dictionary.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    from collections import defaultdict
    count = defaultdict(int)
    for num in nums:
        count[num] += 1
        if count[num] > 1:
            return True
    return False

def contains_duplicate_bitwise(nums):
    """
    Approach 5: Bit Manipulation (for small number ranges)
    Works only if numbers are within a small, known range (e.g., 0 to 31).
    Uses bitwise operations to track seen numbers efficiently.
    Time Complexity: O(n)
    Space Complexity: O(1) (for small numbers)
    """
    if not nums:
        return False
    bitset = 0
    for num in nums:
        mask = 1 << num
        if bitset & mask:
            return True
        bitset |= mask
    return False

# Test cases
nums1 = [1, 2, 3, 4, 5]  # False
nums2 = [1, 2, 3, 1]  # True

print("Brute Force:", contains_duplicate_brute_force(nums1), contains_duplicate_brute_force(nums2))
print("Sorting:", contains_duplicate_sorting(nums1), contains_duplicate_sorting(nums2))
print("Hash Set:", contains_duplicate_hash_set(nums1), contains_duplicate_hash_set(nums2))
print("Hash Map:", contains_duplicate_hash_map(nums1), contains_duplicate_hash_map(nums2))
print("Bit Manipulation:", contains_duplicate_bitwise(nums1), contains_duplicate_bitwise(nums2))

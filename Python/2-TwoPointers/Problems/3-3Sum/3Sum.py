# 3Sum Problem - Multiple Approaches Using Two Pointers
# Given an array of integers, find all unique triplets that sum to zero.

from itertools import combinations # Import combinations for the brute force approach
from collections import defaultdict # Import defaultdict for the bucket counting approach

# Approach 1: Sorting + Two Pointers (Optimal Solution)
# Time Complexity: O(n^2), Space Complexity: O(1)
def three_sum_two_pointers(nums):
    """
    Finds all unique triplets in a list of integers that sum to zero using the sorting and two-pointer approach.

    This is the most efficient solution. It first sorts the array, then iterates through each number.
    For each number, it uses two pointers to find the other two numbers that sum to the negative
    of the current number.  It also handles duplicate values to ensure unique triplets.

    Args:
        nums: A list of integers.

    Returns:
        A list of unique triplets (lists of three integers) that sum to zero.
    """
    nums.sort()  # Sort the array to use the two-pointer approach
    result = []  # Initialize the result list
    for i in range(len(nums) - 2):  # Iterate through the array, leaving space for two more numbers
        if i > 0 and nums[i] == nums[i - 1]:
            continue  # Skip duplicate values of i
        left, right = i + 1, len(nums) - 1  # Initialize left and right pointers
        while left < right:  # Iterate while the left pointer is less than the right pointer
            total = nums[i] + nums[left] + nums[right]  # Calculate the sum of the triplet
            if total == 0:
                result.append([nums[i], nums[left], nums[right]])  # Add the triplet to the result
                left += 1  # Move the left pointer to the right
                right -= 1  # Move the right pointer to the left
                while left < right and nums[left] == nums[left - 1]:
                    left += 1  # Skip duplicate values of left
                while left < right and nums[right] == nums[right + 1]:
                    right -= 1  # Skip duplicate values of right
            elif total < 0:
                left += 1  # If the sum is less than zero, move the left pointer to increase the sum
            else:
                right -= 1  # If the sum is greater than zero, move the right pointer to decrease the sum
    return result  # Return the list of unique triplets

# Approach 2: Hash Map (Using Dictionary)
# Time Complexity: O(n^2), Space Complexity: O(n)
def three_sum_hash_map(nums):
    """
    Finds all unique triplets in a list of integers that sum to zero using a hash map.

    This approach sorts the array and then iterates through it. For each pair of numbers,
    it calculates the complement needed to reach zero and checks if that complement exists
    in a hash map.  A set is used to store unique triplets.

    Args:
        nums: A list of integers.

    Returns:
        A list of unique triplets (lists of three integers) that sum to zero.
    """
    nums.sort()  # Sort the array
    result = set()  # Use a set to store unique triplets
    for i in range(len(nums) - 2):  # Iterate through the array
        if i > 0 and nums[i] == nums[i - 1]:
            continue  # Skip duplicate values of i
        seen = {}  # Initialize a hash map to store seen numbers and their indices
        for j in range(i + 1, len(nums)):  # Iterate through the remaining numbers
            complement = -nums[i] - nums[j]  # Calculate the complement
            if complement in seen:
                result.add((nums[i], complement, nums[j]))  # Add the triplet to the result set
            seen[nums[j]] = j  # Store the current number and its index
    return list(map(list, result))  # Convert the set of tuples to a list of lists

# Approach 3: Brute Force (Using Combinations)
# Time Complexity: O(n^3), Space Complexity: O(n)
def three_sum_brute_force(nums):
    """
    Finds all unique triplets in a list of integers that sum to zero using brute force.

    This approach uses the combinations function from the itertools library to generate all
    possible triplets and checks if their sum is zero.  A set is used to ensure uniqueness.

    Args:
        nums: A list of integers.

    Returns:
        A list of unique triplets (lists of three integers) that sum to zero.
    """
    result = set()  # Use a set to store unique triplets
    for triplet in combinations(nums, 3):  # Generate all possible triplets
        if sum(triplet) == 0:  # Check if the sum of the triplet is zero
            result.add(tuple(sorted(triplet)))  # Add the sorted triplet as a tuple to the set
    return list(map(list, result))  # Convert the set of tuples to a list of lists

# Approach 4: Binary Search + Two Pointers
# Time Complexity: O(n^2 log n), Space Complexity: O(1)
def three_sum_binary_search(nums):
    """
    Finds all unique triplets in a list of integers that sum to zero using binary search.

    This approach sorts the array and then iterates through all possible pairs of numbers.
    For each pair, it uses binary search to find the third number that would make the sum zero.
    A set is used to store unique triplets.

    Args:
        nums: A list of integers.

    Returns:
        A list of unique triplets (lists of three integers) that sum to zero.
    """
    nums.sort()  # Sort the array
    result = set()  # Use a set to store unique triplets
    for i in range(len(nums) - 2):  # Iterate through the array
        if i > 0 and nums[i] == nums[i - 1]:
            continue  # Skip duplicate values of i
        for j in range(i + 1, len(nums) - 1):  # Iterate through the remaining numbers
            complement = -nums[i] - nums[j]  # Calculate the complement
            low, high = j + 1, len(nums) - 1  # Initialize left and right pointers for binary search
            while low <= high:  # Perform binary search
                mid = (low + high) // 2  # Calculate the middle index
                if nums[mid] == complement:
                    result.add((nums[i], nums[j], nums[mid]))  # Add the triplet to the result set
                    break  # Exit the binary search loop
                elif nums[mid] < complement:
                    low = mid + 1  # Search in the right half
                else:
                    high = mid - 1  # Search in the left half
    return list(map(list, result))  # Convert the set of tuples to a list of lists

# Approach 5: Bucket Counting (Optimized for Small Ranges)
# Time Complexity: O(n^2), Space Complexity: O(n)
def three_sum_bucket_counting(nums):
    """
    Finds all unique triplets in a list of integers that sum to zero using bucket counting.

    This approach is optimized for cases where the range of numbers is relatively small.  It counts
    the occurrences of each number using a defaultdict and then iterates through unique pairs
    to find the third number.

    Args:
        nums: A list of integers.

    Returns:
        A list of unique triplets (lists of three integers) that sum to zero.
    """
    count = defaultdict(int)  # Use a defaultdict to count occurrences of each number
    for num in nums:
        count[num] += 1  # Count the occurrences of each number
    result = set()  # Use a set to store unique triplets
    unique_nums = sorted(count.keys())  # Get sorted unique numbers
    for i, x in enumerate(unique_nums):  # Iterate through unique numbers
        for j in range(i, len(unique_nums)):  # Iterate through unique numbers starting from i
            y = unique_nums[j]  # Get the second number
            z = -(x + y)  # Calculate the third number
            if z in count:  # Check if the third number exists
                if z > y or (z == y and count[y] > 1) or (x == y == z and count[x] > 2):
                    # Condition to avoid duplicates:
                    # 1. z is greater than y, ensuring order x, y, z
                    # 2. if z == y, then y should occur more than once
                    # 3. if all are equal, then x should occur more than twice.
                    result.add(tuple(sorted([x, y, z])))  # Add the sorted triplet to the result
    return list(map(list, result))  # Convert the set of tuples to a list of lists

# Test Cases
nums = [-1, 0, 1, 2, -1, -4]
print("Two Pointers:", three_sum_two_pointers(nums))
print("Hash Map:", three_sum_hash_map(nums))
print("Brute Force:", three_sum_brute_force(nums))
print("Binary Search:", three_sum_binary_search(nums))
print("Bucket Counting:", three_sum_bucket_counting(nums))

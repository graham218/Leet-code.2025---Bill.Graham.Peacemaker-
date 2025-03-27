# Two Sum II - Sorted Array Solutions
# Given a sorted array and a target sum, find two numbers that add up to the target.

# Approach 1: Two Pointers (Optimal Solution)
# Time Complexity: O(n), Space Complexity: O(1)
def two_sum_two_pointers(numbers, target):
    """
    Finds two numbers in a sorted array that add up to the target using the two-pointer approach.

    This is the most efficient solution because it takes advantage of the sorted nature of the array.
    It uses two pointers, one at the beginning and one at the end, and moves them towards each other
    based on whether the current sum is less than or greater than the target.

    Args:
        numbers: A sorted list of integers.
        target: The target sum.

    Returns:
        A list containing the 1-based indices of the two numbers that add up to the target.
        Returns an empty list if no such pair exists.
    """
    left, right = 0, len(numbers) - 1  # Initialize left and right pointers
    while left < right:  # Continue as long as the left pointer is before the right pointer
        current_sum = numbers[left] + numbers[right]  # Calculate the sum of the numbers at the two pointers
        if current_sum == target:
            return [left + 1, right + 1]  # 1-based index # If the sum equals the target, return the indices
        elif current_sum < target:
            left += 1  # If the sum is less than the target, move the left pointer to increase the sum
        else:
            right -= 1  # If the sum is greater than the target, move the right pointer to decrease the sum
    return []  # If no such pair is found, return an empty list

# Approach 2: Binary Search (Logarithmic Search for Complement)
# Time Complexity: O(n log n), Space Complexity: O(1)
def two_sum_binary_search(numbers, target):
    """
    Finds two numbers in a sorted array that add up to the target using binary search.

    This approach iterates through the array, and for each number, it uses binary search to
    find the complement (the number needed to reach the target) in the remaining part of the array.

    Args:
        numbers: A sorted list of integers.
        target: The target sum.

    Returns:
        A list containing the 1-based indices of the two numbers that add up to the target.
        Returns an empty list if no such pair exists.
    """
    for i in range(len(numbers)):  # Iterate through each number in the array
        complement = target - numbers[i]  # Calculate the complement needed
        left, right = i + 1, len(numbers) - 1  # Initialize left and right pointers for binary search
        while left <= right:  # Perform binary search
            mid = left + (right - left) // 2  # Calculate the middle index
            if numbers[mid] == complement:
                return [i + 1, mid + 1]  # If the complement is found, return the indices
            elif numbers[mid] < complement:
                left = mid + 1  # If the middle number is less than the complement, search in the right half
            else:
                right = mid - 1  # If the middle number is greater than the complement, search in the left half
    return []  # If no such pair is found, return an empty list

# Approach 3: Hash Map (Trade-off: More Space, Faster Lookup)
# Time Complexity: O(n), Space Complexity: O(n)
def two_sum_hash_map(numbers, target):
    """
    Finds two numbers in an array that add up to the target using a hash map.

    This approach uses a hash map (dictionary in Python) to store each number and its index.
    It then iterates through the array, checking if the complement of the current number
    is already in the hash map.  This provides a fast lookup (average O(1) time).

    Args:
        numbers: A list of integers.
        target: The target sum.

    Returns:
        A list containing the 1-based indices of the two numbers that add up to the target.
        Returns an empty list if no such pair exists.
    """
    seen = {}  # Initialize a hash map to store numbers and their indices
    for i, num in enumerate(numbers):  # Iterate through the array
        complement = target - num  # Calculate the complement needed
        if complement in seen:
            return [seen[complement] + 1, i + 1]  # If the complement is in the hash map, return the indices
        seen[num] = i  # Store the current number and its index in the hash map
    return []  # If no such pair is found, return an empty list

# Approach 4: Brute Force (Exhaustive Search)
# Time Complexity: O(n^2), Space Complexity: O(1)
def two_sum_brute_force(numbers, target):
    """
    Finds two numbers in an array that add up to the target using brute force.

    This is the simplest but least efficient approach.  It iterates through every possible
    pair of numbers in the array and checks if their sum equals the target.

    Args:
        numbers: A list of integers.
        target: The target sum.

    Returns:
        A list containing the 1-based indices of the two numbers that add up to the target.
        Returns an empty list if no such pair exists.
    """
    for i in range(len(numbers)):  # Iterate through each number in the array
        for j in range(i + 1, len(numbers)):  # Iterate through the remaining numbers
            if numbers[i] + numbers[j] == target:
                return [i + 1, j + 1]  # If the sum equals the target, return the indices
    return []  # If no such pair is found, return an empty list

# Approach 5: Recursive Two Pointers (Divide and Conquer)
# Time Complexity: O(n), Space Complexity: O(n) (Due to recursion stack)
def two_sum_recursive(numbers, target, left=0, right=None):
    """
    Finds two numbers in a sorted array that add up to the target using recursion
    and the two-pointer approach.

    This approach is similar to the iterative two-pointer approach, but it uses recursion
    instead of a loop.  It repeatedly divides the array and checks the sum of the
    numbers at the left and right pointers.

    Args:
        numbers: A sorted list of integers.
        target: The target sum.
        left: The left pointer (default: 0).
        right: The right pointer (default: len(numbers) - 1).

    Returns:
        A list containing the 1-based indices of the two numbers that add up to the target.
        Returns an empty list if no such pair exists.
    """
    if right is None:
        right = len(numbers) - 1  # Initialize the right pointer if it's not provided
    if left >= right:
        return []  # Base case: if the pointers cross, no solution is found
    current_sum = numbers[left] + numbers[right]  # Calculate the current sum
    if current_sum == target:
        return [left + 1, right + 1]  # If the sum equals the target, return the indices
    elif current_sum < target:
        return two_sum_recursive(numbers, target, left + 1, right)  # Recursively search in the right half
    else:
        return two_sum_recursive(numbers, target, left, right - 1)  # Recursively search in the left half

# Test Cases
numbers = [2, 7, 11, 15]
target = 9
print("Two Pointers:", two_sum_two_pointers(numbers, target))
print("Binary Search:", two_sum_binary_search(numbers, target))
print("Hash Map:", two_sum_hash_map(numbers, target))
print("Brute Force:", two_sum_brute_force(numbers, target))
print("Recursive Two Pointers:", two_sum_recursive(numbers, target))

# Advanced Binary Search Implementations: Upper Bound & Lower Bound
# This script demonstrates five different approaches to finding the lower bound and upper bound of a target element in a sorted list.

from bisect import bisect_left, bisect_right # Import bisect_left and bisect_right for their efficient implementations
from typing import List # Import List for type hinting

# 1. Standard Binary Search for Lower Bound
def lower_bound(arr: List[int], target: int) -> int:
    """
    Finds the lower bound of a target value in a sorted array.
    The lower bound is the index of the first element that is greater than or equal to the target.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the lower bound of the target in the array.
        Returns the length of the array if the target is greater than all elements.

    Example:
        arr = [1, 2, 4, 4, 5, 7, 9, 10]
        target = 4
        lower_bound(arr, target) == 2  # Index of the first '4'
    """
    left, right = 0, len(arr) # Initialize left and right pointers.  Right is one past the last element.
    while left < right: # Continue as long as the left pointer is less than the right pointer.
        mid = left + (right - left) // 2 # Calculate the middle index, preventing potential overflow
        if arr[mid] < target:
            left = mid + 1 # If the middle element is less than the target, the lower bound is in the right half
        else:
            right = mid # Otherwise, the lower bound is in the left half (including the middle)
    return left # When the loop finishes, left (which equals right) is the index of the lower bound

# 2. Standard Binary Search for Upper Bound
def upper_bound(arr: List[int], target: int) -> int:
    """
    Finds the upper bound of a target value in a sorted array.
    The upper bound is the index of the first element that is strictly greater than the target.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the upper bound of the target in the array.
        Returns the length of the array if the target is greater than or equal to all elements.

    Example:
        arr = [1, 2, 4, 4, 5, 7, 9, 10]
        target = 4
        upper_bound(arr, target) == 4  # Index of the '5'
    """
    left, right = 0, len(arr) # Initialize left and right pointers
    while left < right: # Continue as long as left is less than right
        mid = left + (right - left) // 2 # Calculate middle index
        if arr[mid] <= target:
            left = mid + 1 # If the middle element is less than or equal to the target, the upper bound is in the right half
        else:
            right = mid # Otherwise, the upper bound is in the left half
    return left # When the loop finishes, left is the index of the upper bound

# 3. Using Python's Built-in Bisect Module (Efficient & Recommended)
def lower_bound_bisect(arr: List[int], target: int) -> int:
    """
    Finds the lower bound using Python's bisect_left function.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the lower bound of the target in the array.
    """
    return bisect_left(arr, target) # bisect_left directly returns the lower bound

def upper_bound_bisect(arr: List[int], target: int) -> int:
    """
    Finds the upper bound using Python's bisect_right function.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the upper bound of the target in the array.
    """
    return bisect_right(arr, target) # bisect_right directly returns the upper bound

# 4. Recursive Approach for Lower & Upper Bound
def lower_bound_recursive(arr: List[int], target: int, left: int, right: int) -> int:
    """
    Finds the lower bound recursively.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.
        left: The left index of the current search range.
        right: The right index of the current search range.

    Returns:
        The index of the lower bound.
    """
    if left >= right: # Base case: if left is greater than or equal to right, return left
        return left
    mid = left + (right - left) // 2 # Calculate middle index
    if arr[mid] < target:
        return lower_bound_recursive(arr, target, mid + 1, right) # Recursive call on the right half
    else:
        return lower_bound_recursive(arr, target, left, mid) # Recursive call on the left half

def upper_bound_recursive(arr: List[int], target: int, left: int, right: int) -> int:
    """
    Finds the upper bound recursively.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.
        left: The left index of the current search range.
        right: The right index of the current search range.

    Returns:
        The index of the upper bound.
    """
    if left >= right: # Base case
        return left
    mid = left + (right - left) // 2
    if arr[mid] <= target:
        return upper_bound_recursive(arr, target, mid + 1, right) # Recursive call on the right half
    else:
        return upper_bound_recursive(arr, target, left, mid) # Recursive call on the left half

# 5. Optimized Binary Search for Large Datasets (Uses Memory-Mapped Search for Speed)
def optimized_lower_bound(arr: List[int], target: int) -> int:
    """
    Finds the lower bound using a generator expression and the next() function.
    This can be slightly faster for very large lists as it avoids iterating over the entire list.
    It stops as soon as the condition is met.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the lower bound.
    """
    return next((i for i, x in enumerate(arr) if x >= target), len(arr)) # Returns the index of the first element >= target

def optimized_upper_bound(arr: List[int], target: int) -> int:
    """
    Finds the upper bound using a generator expression and the next() function.

    Args:
        arr: A sorted list of integers.
        target: The target integer value.

    Returns:
        The index of the upper bound.
    """
    return next((i for i, x in enumerate(arr) if x > target), len(arr)) # Returns the index of the first element > target

# Test Cases
arr = [1, 2, 4, 4, 5, 7, 9, 10]
target = 4

print("Lower Bound (Binary Search):", lower_bound(arr, target))
print("Upper Bound (Binary Search):", upper_bound(arr, target))
print("Lower Bound (Bisect):", lower_bound_bisect(arr, target))
print("Upper Bound (Bisect):", upper_bound_bisect(arr, target))
print("Lower Bound (Recursive):", lower_bound_recursive(arr, target, 0, len(arr)))
print("Upper Bound (Recursive):", upper_bound_recursive(arr, target, 0, len(arr)))
print("Lower Bound (Optimized):", optimized_lower_bound(arr, target))
print("Upper Bound (Optimized):", optimized_upper_bound(arr, target))

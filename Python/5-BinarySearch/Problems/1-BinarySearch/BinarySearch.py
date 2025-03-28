# Binary Search: 5 Different Approaches
# Binary search is an efficient algorithm for finding elements in a sorted array.

from typing import List # Import List for type hinting, making the code more readable
import bisect # Import the bisect module, which provides efficient implementations of binary search

# 1. Standard Iterative Binary Search
def binary_search_iterative(arr: List[int], target: int) -> int:
    """
    Performs iterative binary search on a sorted list to find the index of a target value.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value in the list if found, otherwise -1.

    Example:
        arr = [1, 3, 5, 7, 9, 11, 13]
        target = 7
        binary_search_iterative(arr, target) == 3
    """
    left, right = 0, len(arr) - 1 # Initialize left and right pointers to the start and end of the list
    while left <= right: # Continue searching as long as the left pointer is less than or equal to the right pointer
        mid = left + (right - left) // 2 # Calculate the middle index.  This avoids potential overflow issues with large lists.
        if arr[mid] == target:
            return mid # If the middle element is the target, return its index
        elif arr[mid] < target:
            left = mid + 1 # If the middle element is less than the target, search the right half of the list
        else:
            right = mid - 1 # If the middle element is greater than the target, search the left half of the list
    return -1 # If the target is not found, return -1

# 2. Recursive Binary Search
def binary_search_recursive(arr: List[int], left: int, right: int, target: int) -> int:
    """
    Performs recursive binary search on a sorted list.

    Args:
        arr: A sorted list of integers.
        left: The starting index of the search interval.
        right: The ending index of the search interval.
        target: The integer value to search for.

    Returns:
        The index of the target value in the list if found, otherwise -1.
    """
    if left > right: # Base case: if the left pointer crosses the right pointer, the target is not found
        return -1
    mid = left + (right - left) // 2 # Calculate the middle index
    if arr[mid] == target:
        return mid # If the middle element is the target, return its index
    elif arr[mid] < target:
        return binary_search_recursive(arr, mid + 1, right, target) # Recursively search the right half
    else:
        return binary_search_recursive(arr, left, mid - 1, target) # Recursively search the left half

# 3. Binary Search Using Python's Bisect Module
def binary_search_bisect(arr: List[int], target: int) -> int:
    """
    Performs binary search using Python's built-in bisect_left function.
    The bisect module provides efficient implementations of binary search.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value in the list if found, otherwise -1.
    """
    index = bisect.bisect_left(arr, target) # Use bisect_left to find the insertion point for the target
    if index < len(arr) and arr[index] == target: # Check if the element at the insertion point is the target
        return index
    return -1 # If the target is not found, return -1

# 4. Binary Search to Find the First Occurrence
def binary_search_first_occurrence(arr: List[int], target: int) -> int:
    """
    Finds the index of the first occurrence of a target value in a sorted list.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the first occurrence of the target value, or -1 if not found.
    """
    left, right = 0, len(arr) - 1
    result = -1 # Initialize the result to -1 (not found)
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            result = mid # When found, update result, and continue searching the left side
            right = mid - 1  # Keep searching on the left side for the first occurrence
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return result

# 5. Binary Search to Find the Last Occurrence
def binary_search_last_occurrence(arr: List[int], target: int) -> int:
    """
    Finds the index of the last occurrence of a target value in a sorted list.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the last occurrence of the target value, or -1 if not found.
    """
    left, right = 0, len(arr) - 1
    result = -1 # Initialize result to -1
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            result = mid # update the result
            left = mid + 1  # Keep searching on the right side for the last occurrence
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return result

# Sample Data
arr = [1, 3, 5, 5, 5, 7, 9, 11, 13]
target = 5

# Running Tests
print("Iterative Binary Search:", binary_search_iterative(arr, target))
print("Recursive Binary Search:", binary_search_recursive(arr, 0, len(arr) - 1, target))
print("Bisect Binary Search:", binary_search_bisect(arr, target))
print("First Occurrence Search:", binary_search_first_occurrence(arr, target))
print("Last Occurrence Search:", binary_search_last_occurrence(arr, target))

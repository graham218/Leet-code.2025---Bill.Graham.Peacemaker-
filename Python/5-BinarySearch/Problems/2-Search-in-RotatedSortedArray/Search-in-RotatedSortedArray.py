# Advanced Solutions for Searching in a Rotated Sorted Array
# This script includes five different approaches to solving this problem in real-world scenarios.

from typing import List # Import List for type hinting

def search_rotated_iterative(nums: List[int], target: int) -> int:
    """
    Iteratively searches for a target in a rotated sorted array.

    Args:
        nums: A rotated sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.

    Example:
        nums = [4, 5, 6, 7, 0, 1, 2]
        target = 0
        search_rotated_iterative(nums, target) == 4
    """
    left, right = 0, len(nums) - 1 # Initialize left and right pointers
    while left <= right: # Continue as long as the left pointer is less than or equal to the right pointer
        mid = (left + right) // 2 # Calculate the middle index
        if nums[mid] == target:
            return mid # Target found at middle

        # Determine which half is sorted
        if nums[left] <= nums[mid]: # Left half is sorted
            if nums[left] <= target < nums[mid]:
                right = mid - 1 # Target is in sorted left half
            else:
                left = mid + 1 # Target is in rotated right half
        else: # Right half is sorted
            if nums[mid] < target <= nums[right]:
                left = mid + 1 # Target is in sorted right half
            else:
                right = mid - 1 # Target is in rotated left half
    return -1 # Target not found

def search_rotated_recursive(nums: List[int], left: int, right: int, target: int) -> int:
    """
    Recursively searches for a target in a rotated sorted array.

    Args:
        nums: A rotated sorted list of integers.
        left: The starting index of the search range.
        right: The ending index of the search range.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    if left > right: # Base case: target not found
        return -1
    mid = (left + right) // 2 # Calculate middle index
    if nums[mid] == target:
        return mid # Target found

    # Determine which half is sorted and recursively search
    if nums[left] <= nums[mid]: # Left half is sorted
        if nums[left] <= target < nums[mid]:
            return search_rotated_recursive(nums, left, mid - 1, target) # Search left half
        else:
            return search_rotated_recursive(nums, mid + 1, right, target) # Search right half
    else: # Right half is sorted
        if nums[mid] < target <= nums[right]:
            return search_rotated_recursive(nums, mid + 1, right, target) # Search right half
        else:
            return search_rotated_recursive(nums, left, mid - 1, target) # Search left half

def search_rotated_with_duplicates(nums: List[int], target: int) -> int:
    """
    Searches for a target in a rotated sorted array that may contain duplicate elements.

    Args:
        nums: A rotated sorted list of integers with possible duplicates.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    left, right = 0, len(nums) - 1
    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            return mid

        # Handle the case with duplicates: if left, mid, and right are the same, we can't tell which side is sorted
        if nums[left] == nums[mid] == nums[right]:
            left += 1
            right -= 1
            continue # Important: continue to the next iteration of the loop

        # Determine which half is sorted
        if nums[left] <= nums[mid]: # Left half is sorted
            if nums[left] <= target < nums[mid]:
                right = mid - 1
            else:
                left = mid + 1
        else: # Right half is sorted
            if nums[mid] < target <= nums[right]:
                left = mid + 1
            else:
                right = mid - 1
    return -1

def search_rotated_find_pivot(nums: List[int]) -> int:
    """
    Finds the index of the smallest element (pivot) in a rotated sorted array.
    This is used to find the point of rotation.

    Args:
        nums: A rotated sorted list of integers.

    Returns:
        The index of the smallest element (pivot).
    """
    left, right = 0, len(nums) - 1
    while left < right: # Continue until left and right converge
        mid = (left + right) // 2
        if nums[mid] > nums[right]:
            left = mid + 1 # Pivot is in the right half
        else:
            right = mid # Pivot is mid or in the left half
    return left # Left and right converge at the pivot

def search_rotated_pivot_binary_search(nums: List[int], target: int) -> int:
    """
    Searches for a target in a rotated sorted array by first finding the pivot
    and then applying standard binary search in the two sorted halves.

    Args:
        nums: A rotated sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    if not nums:
        return -1 # Handle empty array case
    pivot = search_rotated_find_pivot(nums) # Find the pivot (index of smallest element)
    left_search = binary_search(nums[:pivot], target) # Search in the left sorted part
    if left_search != -1:
        return left_search # Target found in left part
    right_search = binary_search(nums[pivot:], target) # Search in the right sorted part
    return right_search + pivot if right_search != -1 else -1 # Return the index, adjusting for the pivot

def binary_search(arr: List[int], target: int) -> int:
    """
    Helper function for standard binary search.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

# Sample Test Cases
nums = [4, 5, 6, 7, 0, 1, 2]
target = 6

print("Iterative Search:", search_rotated_iterative(nums, target))
print("Recursive Search:", search_rotated_recursive(nums, 0, len(nums) - 1, target))
print("Search with Duplicates:", search_rotated_with_duplicates(nums, target))
print("Pivot Index:", search_rotated_find_pivot(nums))
print("Pivot-based Binary Search:", search_rotated_pivot_binary_search(nums, target))

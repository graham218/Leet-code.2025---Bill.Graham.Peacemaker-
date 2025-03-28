# Solution for Finding Minimum in a Rotated Sorted Array
# Implementing five different approaches for various use cases

from typing import List

def find_min_iterative(nums: List[int]) -> int:
    """
    Iterative binary search approach.

    This function finds the minimum element in a rotated sorted array using an iterative
    binary search algorithm.  It's efficient, with a time complexity of O(log n).

    Args:
        nums (List[int]): A list of integers representing the rotated sorted array.

    Returns:
        int: The minimum element in the array.

    Algorithm:
        1. Initialize two pointers, `left` and `right`, to the start and end of the array.
        2. While `left` is less than `right`:
            a. Calculate the middle index `mid`.
            b. If the element at `mid` is greater than the element at `right`, it means the
               minimum element is in the right half of the array, so update `left` to `mid + 1`.
            c. Otherwise, the minimum element is in the left half (including `mid`), so
               update `right` to `mid`.
        3. The loop terminates when `left` equals `right`, and this index holds the minimum.
        4. Return the element at index `left`.
    """
    left, right = 0, len(nums) - 1  # Initialize left and right pointers
    while left < right:
        mid = (left + right) // 2  # Calculate the middle index
        if nums[mid] > nums[right]:
            left = mid + 1      # Minimum is in the right half
        else:
            right = mid          # Minimum is in the left half
    return nums[left]  # Return the minimum element



def find_min_recursive(nums: List[int], left: int, right: int) -> int:
    """
    Recursive binary search approach.

    This function finds the minimum element in a rotated sorted array using a recursive
    binary search algorithm.  It has the same time complexity of O(log n) as the iterative version.

    Args:
        nums (List[int]): A list of integers representing the rotated sorted array.
        left (int): The starting index of the subarray to search.
        right (int): The ending index of the subarray to search.

    Returns:
        int: The minimum element in the array.

    Algorithm:
        1. Base case: If `left` equals `right`, the subarray has only one element,
           which is the minimum, so return `nums[left]`.
        2. Calculate the middle index `mid`.
        3. If the element at `mid` is greater than the element at `right`, recursively
           search the right half of the array (from `mid + 1` to `right`).
        4. Otherwise, recursively search the left half of the array (from `left` to `mid`).
    """
    if left == right:
        return nums[left]  # Base case: single element
    mid = (left + right) // 2  # Calculate middle index
    if nums[mid] > nums[right]:
        return find_min_recursive(nums, mid + 1, right)  # Recursive call on right half
    else:
        return find_min_recursive(nums, left, mid)      # Recursive call on left half



def find_min_with_duplicates(nums: List[int]) -> int:
    """
    Binary search approach handling duplicates.

    This function handles rotated sorted arrays that may contain duplicate elements.
    The standard binary search approach may fail in the presence of duplicates, so this
    function includes a modification to handle them.  The time complexity can degrade to
    O(n) in the worst case (when all elements are the same), but is typically better.

    Args:
        nums (List[int]): A list of integers representing the rotated sorted array,
                           possibly with duplicates.

    Returns:
        int: The minimum element in the array.

    Algorithm:
        1. Initialize two pointers, `left` and `right`, to the start and end of the array.
        2. While `left` is less than `right`:
            a. Calculate the middle index `mid`.
            b. If the element at `mid` is greater than the element at `right`, the minimum
               is in the right half, so update `left` to `mid + 1`.
            c. If the element at `mid` is less than the element at `right`, the minimum
               is in the left half, so update `right` to `mid`.
            d. If the element at `mid` equals the element at `right`, it means we can't
               determine which half contains the minimum, so we reduce the search space
               by decrementing `right`.  This is the key modification to handle duplicates.
        3. Return the element at index `left`.
    """
    left, right = 0, len(nums) - 1
    while left < right:
        mid = (left + right) // 2
        if nums[mid] > nums[right]:
            left = mid + 1
        elif nums[mid] < nums[right]:
            right = mid
        else:
            right -= 1  # Handle duplicates: reduce search space
    return nums[left]



def find_min_linear(nums: List[int]) -> int:
    """
    Simple linear scan approach for robustness.

    This function finds the minimum element using a simple linear scan.  It iterates
    through the entire array and keeps track of the minimum element found so far.
    This approach is less efficient than binary search (O(n) time complexity), but it's
    very simple and robust, and it works correctly for any array, including those that
    are not sorted or rotated.

    Args:
        nums (List[int]): A list of integers.

    Returns:
        int: The minimum element in the array.

    Algorithm:
        1. Initialize a variable `min_val` to the first element of the array.
        2. Iterate through the rest of the array (from the second element to the last).
        3. For each element, compare it with `min_val`.  If the element is smaller than
           `min_val`, update `min_val` to the current element.
        4. After iterating through the entire array, `min_val` will hold the minimum element.
        5. Return `min_val`.
    """
    min_val = nums[0]  # Initialize with the first element
    for num in nums:
        if num < min_val:
            min_val = num  # Update min_val if a smaller element is found
    return min_val



def find_min_modified_pivot(nums: List[int]) -> int:
    """
    Modified pivot detection approach.

    This function is essentially the same as the iterative binary search approach
    (find_min_iterative).  It finds the minimum element by locating the "pivot" point
    in the rotated sorted array, which is the point where the array is rotated.
    The minimum element is located immediately after this pivot point.

    Args:
        nums (List[int]): A list of integers representing the rotated sorted array.

    Returns:
        int: The minimum element in the array.

    Algorithm:
        1. Initialize two pointers, `left` and `right`, to the start and end of the array.
        2. While `left` is less than `right`:
            a. Calculate the middle index `mid`.
            b. If the element at `mid` is greater than the element at `right`, it means the
               pivot point is in the right half, so update `left` to `mid + 1`.
            c. Otherwise, the pivot point is in the left half (including `mid`), so
               update `right` to `mid`.
        3. The loop terminates when `left` equals `right`, and this index holds the minimum.
        4. Return the element at index `left`.
    """
    left, right = 0, len(nums) - 1
    while left < right:
        mid = (left + right) // 2
        if nums[mid] > nums[right]:
            left = mid + 1
        else:
            right = mid
    return nums[left]



# Sample Test Cases
nums = [4, 5, 6, 7, 0, 1, 2]
print("Iterative Search:", find_min_iterative(nums))
print("Recursive Search:", find_min_recursive(nums, 0, len(nums) - 1))
print("Search with Duplicates:", find_min_with_duplicates([2, 2, 2, 0, 1]))
print("Linear Search:", find_min_linear(nums))
print("Modified Pivot Search:", find_min_modified_pivot(nums))

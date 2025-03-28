# Python implementation of Binary Search using 5 different approaches

# 1. Iterative Binary Search
def binary_search_iterative(arr, target):
    """
    Performs binary search iteratively (using a loop).

    Args:
        arr: A sorted list of elements.
        target: The element to search for.

    Returns:
        The index of the target element if found, otherwise -1.
    """
    left, right = 0, len(arr) - 1  # Initialize left and right pointers to the start and end of the array
    while left <= right:  # Continue searching as long as the left pointer is not to the right of the right pointer
        mid = left + (right - left) // 2  # Calculate the middle index.  This avoids potential overflow issues with (left + right) // 2
        if arr[mid] == target:
            return mid  # Target found at the middle index, return the index
        elif arr[mid] < target:
            left = mid + 1  # If the middle element is less than the target, search in the right half of the array
        else:
            right = mid - 1  # If the middle element is greater than the target, search in the left half of the array
    return -1  # Target not found in the array

# 2. Recursive Binary Search
def binary_search_recursive(arr, left, right, target):
    """
    Performs binary search recursively (using function calls).

    Args:
        arr: A sorted list of elements.
        left: The starting index of the search interval.
        right: The ending index of the search interval.
        target: The element to search for.

    Returns:
        The index of the target element if found, otherwise -1.
    """
    if left > right:
        return -1  # Base case: if the left pointer crosses the right pointer, the target is not found
    mid = left + (right - left) // 2  # Calculate the middle index
    if arr[mid] == target:
        return mid  # Target found at the middle index, return the index
    elif arr[mid] < target:
        return binary_search_recursive(arr, mid + 1, right, target)  # Recursively search in the right half
    else:
        return binary_search_recursive(arr, left, mid - 1, target)  # Recursively search in the left half

# 3. Binary Search using Bisect Module (Built-in method)
import bisect  # Import the bisect module, which provides binary search functions

def binary_search_bisect(arr, target):
    """
    Performs binary search using the bisect module's bisect_left function.

    Args:
        arr: A sorted list of elements.
        target: The element to search for.

    Returns:
        The index of the target element if found, otherwise -1.
    """
    index = bisect.bisect_left(arr, target)  # Find the insertion point for the target element.  If target exists, it returns the leftmost index.
    if index < len(arr) and arr[index] == target: # check if the index is within the array bounds and the element at that index equals the target.
        return index  # Target found at the insertion point, return the index
    return -1  # Target not found

# 4. Ternary Search (Alternative search technique)
def ternary_search(arr, left, right, target):
    """
    Performs ternary search recursively.  Ternary search is similar to binary search but divides the array into three parts.
    It is used for unimodal functions (functions that increase and then decrease, or vice versa).  However, it can be used on sorted arrays as well.

    Args:
        arr: A sorted list of elements.
        left: The starting index of the search interval.
        right: The ending index of the search interval.
        target: The element to search for.

    Returns:
        The index of the target element if found, otherwise -1.
    """
    if right >= left:  # Continue searching as long as the right pointer is not to the left of the left pointer
        mid1 = left + (right - left) // 3  # Calculate the first middle index
        mid2 = right - (right - left) // 3  # Calculate the second middle index
        if arr[mid1] == target:
            return mid1  # Target found at the first middle index
        if arr[mid2] == target:
            return mid2  # Target found at the second middle index
        if target < arr[mid1]:
            return ternary_search(arr, left, mid1 - 1, target)  # Search in the left third of the array
        elif target > arr[mid2]:
            return ternary_search(arr, mid2 + 1, right, target)  # Search in the right third of the array
        else:
            return ternary_search(arr, mid1 + 1, mid2 - 1, target)  # Search in the middle third of the array
    return -1  # Target not found

# 5. Exponential Search (Uses binary search internally)
def exponential_search(arr, target):
    """
    Performs exponential search.  It is useful for unbounded/infinite arrays.
    It first finds a range where the target might be present, and then performs binary search within that range.

    Args:
        arr: A sorted list of elements.
        target: The element to search for.

    Returns:
        The index of the target element if found, otherwise -1.
    """
    if arr[0] == target:
        return 0  # Target found at the beginning of the array
    index = 1
    while index < len(arr) and arr[index] <= target:
        index *= 2  # Exponentially increase the index to find a range where the target might be present
    # Perform binary search in the range [index/2, min(index, len(arr)-1)]
    return binary_search_recursive(arr, index // 2, min(index, len(arr) - 1), target)

# Test the functions
arr = [1, 3, 5, 7, 9, 11, 13, 15]
target = 7

print("Iterative Binary Search:", binary_search_iterative(arr, target))
print("Recursive Binary Search:", binary_search_recursive(arr, 0, len(arr) - 1, target))
print("Binary Search using Bisect:", binary_search_bisect(arr, target))
print("Ternary Search:", ternary_search(arr, 0, len(arr) - 1, target))
print("Exponential Search:", exponential_search(arr, target))

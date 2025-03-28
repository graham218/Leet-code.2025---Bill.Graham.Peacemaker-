# Advanced Exponential Search Implementations with 5 Different Approaches
# Exponential search is useful for unbounded or large datasets where binary search alone is inefficient.

from typing import List # Import List for type hinting
import bisect # Import bisect for binary search

# 1. Standard Exponential Search with Binary Search
def binary_search(arr: List[int], left: int, right: int, target: int) -> int:
    """
    Performs standard binary search within a specified range of a sorted array.

    Args:
        arr: A sorted list of integers.
        left: The starting index of the search range.
        right: The ending index of the search range.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    while left <= right: # Continue searching as long as the left boundary is less than or equal to the right boundary
        mid = left + (right - left) // 2 # Calculate the middle index to avoid potential overflow
        if arr[mid] == target:
            return mid # Target found at the middle index
        elif arr[mid] < target:
            left = mid + 1 # If the middle value is less than the target, search the right half
        else:
            right = mid - 1 # If the middle value is greater than the target, search the left half
    return -1 # Target not found in the specified range

def exponential_search(arr: List[int], target: int) -> int:
    """
    Performs exponential search to find the target in a sorted array.
    This approach is suitable for unbounded arrays or when the target is likely to be near the beginning.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    if arr[0] == target:
        return 0 # If the target is at the first index, return 0
    index = 1 # Initialize the index to 1 (2^0)
    while index < len(arr) and arr[index] <= target:
        index *= 2 # Exponentially increase the index (1, 2, 4, 8, ...) until arr[index] exceeds target or index reaches the end of the array.
    # Perform binary search on the range [index/2, min(index, len(arr)-1)]
    return binary_search(arr, index // 2, min(index, len(arr) - 1), target) #  Calls the standard binary search function

# 2. Exponential Search Using Python's Bisect Module
def exponential_search_bisect(arr: List[int], target: int) -> int:
    """
    Performs exponential search using Python's bisect_left function for binary search.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    index = 1
    while index < len(arr) and arr[index] <= target:
        index *= 2
    # Use bisect_left to find the insertion point of the target in the bounded range
    pos = bisect.bisect_left(arr[:min(index, len(arr))], target) # Perform binary search using bisect_left
    return pos if pos < len(arr) and arr[pos] == target else -1 # Check if the element at the insertion point is the target

# 3. Recursive Exponential Search
def exponential_search_recursive(arr: List[int], target: int, bound: int = 1) -> int:
    """
    Performs exponential search recursively.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.
        bound: The current upper bound of the search range (starts at 1).

    Returns:
        The index of the target value if found, otherwise -1.
    """
    if bound >= len(arr) or arr[bound] > target:
        # Base case: If the bound is out of range or the element at the bound is greater than the target, perform binary search
        return binary_search(arr, bound // 2, min(bound, len(arr) - 1), target)
    # Recursive step: Otherwise, recursively call the function with the bound doubled
    return exponential_search_recursive(arr, target, bound * 2)

# 4. Exponential Search for Unbounded Data Streams
def find_target_in_stream(stream, target: int) -> int:
    """
    Performs exponential search on an unbounded data stream (simulated as a list).

    Args:
        stream: A list representing the unbounded data stream.  Note that in a true unbounded stream, you wouldn't know the length.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    index, step = 0, 1 # Initialize index and step
    while True:
        try:
            value = stream[index] # Get the value at the current index
            if value == target:
                return index # Target found
            elif value > target:
                break # If the value is greater than the target, stop the exponential search phase
            index += step # Move the index by the step
            step *= 2 # Double the step
        except IndexError:
            break # Stop if index goes out of bound (simulates end of stream)
    # Perform binary search on the found range
    return binary_search(stream, index // 2, min(index, len(stream) - 1), target)

# 5. Optimized Exponential Search with Parallel Processing
def parallel_exponential_search(arr: List[int], target: int) -> int:
    """
    Performs exponential search with parallel processing using ThreadPoolExecutor for the binary search phase.

    Args:
        arr: A sorted list of integers.
        target: The integer value to search for.

    Returns:
        The index of the target value if found, otherwise -1.
    """
    from concurrent.futures import ThreadPoolExecutor # Import ThreadPoolExecutor for parallel processing
    index = 1
    while index < len(arr) and arr[index] <= target:
        index *= 2
    with ThreadPoolExecutor() as executor: # Use a thread pool to execute the binary search in a separate thread
        future = executor.submit(binary_search, arr, index // 2, min(index, len(arr) - 1), target) # Submit the binary search task to the executor
        return future.result() # Get the result from the future object (waits for the task to complete)

# Sample Data
arr = [1, 3, 5, 7, 9, 11, 15, 19, 23, 27, 31, 35, 40, 50, 60]
target = 19

# Running Tests
print("Standard Exponential Search:", exponential_search(arr, target))
print("Bisect Exponential Search:", exponential_search_bisect(arr, target))
print("Recursive Exponential Search:", exponential_search_recursive(arr, target))
print("Parallel Exponential Search:", parallel_exponential_search(arr, target))

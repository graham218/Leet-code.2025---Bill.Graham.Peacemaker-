'''
Sliding Window Technique - Dynamic Window Size

Problem Statement:
Given an array and a target sum, find the minimum length of a contiguous subarray
whose sum is greater than or equal to the target.

We will implement this using five different approaches.
'''

# 1. Brute Force Approach (O(n^2))
def min_subarray_len_brute_force(arr, target):
    """
    Finds the minimum length of a subarray with sum >= target using brute force.
    It checks all possible subarrays.

    Args:
        arr (list): A list of integers.
        target (int): The target sum.

    Returns:
        int: The minimum length of a qualifying subarray, or 0 if none exists.
    """
    min_len = float('inf')  # Initialize min_len to infinity.
    for i in range(len(arr)):  # Iterate through all possible start indices.
        current_sum = 0  # Reset current_sum for each start index.
        for j in range(i, len(arr)):  # Iterate through all possible end indices for the current start index.
            current_sum += arr[j]  # Calculate the sum of the subarray from i to j.
            if current_sum >= target:  # If the sum is greater than or equal to the target:
                min_len = min(min_len, j - i + 1)  # Update min_len if the current subarray is shorter.
                break  # No need to check longer subarrays starting at i, since we want the minimum length.
    return min_len if min_len != float('inf') else 0  # Return the minimum length, or 0 if no such subarray exists.

# 2. Sliding Window Approach (O(n))
def min_subarray_len_sliding_window(arr, target):
    """
    Finds the minimum length of a subarray with sum >= target using the sliding window technique.

    Args:
        arr (list): A list of integers.
        target (int): The target sum.

    Returns:
        int: The minimum length of a qualifying subarray, or 0 if none exists.
    """
    left = 0  # Initialize the left pointer of the window.
    current_sum = 0  # Initialize the sum of the current window.
    min_len = float('inf')  # Initialize min_len to infinity.

    for right in range(len(arr)):  # Iterate through the array using the right pointer.
        current_sum += arr[right]  # Expand the window by adding the current element.
        while current_sum >= target:  # While the current window's sum is greater than or equal to the target:
            min_len = min(min_len, right - left + 1)  # Update min_len if the current window is shorter.
            current_sum -= arr[left]  # Shrink the window from the left.
            left += 1  # Move the left pointer to the right.

    return min_len if min_len != float('inf') else 0  # Return the minimum length, or 0 if no such subarray exists.

# 3. Two Pointer Approach (O(n))
def min_subarray_len_two_pointer(arr, target):
    """
    Finds the minimum length of a subarray with sum >= target using the two-pointer technique.
    This is essentially the same as the sliding window approach.

    Args:
        arr (list): A list of integers.
        target (int): The target sum.

    Returns:
        int: The minimum length of a qualifying subarray, or 0 if none exists.
    """
    left, right = 0, 0  # Initialize the left and right pointers.
    current_sum = 0  # Initialize the sum of the current window.
    min_len = float('inf')  # Initialize min_len to infinity.

    while right < len(arr):  # Iterate until the right pointer reaches the end of the array.
        current_sum += arr[right]  # Expand the window by moving the right pointer.
        while current_sum >= target:  # While the current window's sum is greater than or equal to the target:
            min_len = min(min_len, right - left + 1)  # Update min_len.
            current_sum -= arr[left]  # Shrink the window by moving the left pointer.
            left += 1
        right += 1  # Move the right pointer to the next element.

    return min_len if min_len != float('inf') else 0  # Return the minimum length, or 0.

# 4. Binary Search Approach (O(n log n))
from bisect import bisect_left

def min_subarray_len_binary_search(arr, target):
    """
    Finds the minimum length of a subarray with sum >= target using binary search.
    It uses prefix sums to efficiently find the end of a subarray with a given sum.

    Args:
        arr (list): A list of integers.
        target (int): The target sum.

    Returns:
        int: The minimum length of a qualifying subarray, or 0 if none exists.
    """
    prefix_sums = [0] * (len(arr) + 1)  # Create an array to store prefix sums.
    for i in range(1, len(arr) + 1):
        prefix_sums[i] = prefix_sums[i - 1] + arr[i - 1]  # Calculate prefix sums.

    min_len = float('inf')  # Initialize min_len to infinity.
    for i in range(len(arr)):  # Iterate through each possible start index of a subarray.
        target_sum = prefix_sums[i] + target  # Calculate the required sum for a subarray starting at i.
        bound = bisect_left(prefix_sums, target_sum)  # Use binary search to find the first prefix sum >= target_sum.
        if bound <= len(arr):  # If a suitable end index is found:
            min_len = min(min_len, bound - i)  # Update min_len.

    return min_len if min_len != float('inf') else 0  # Return the minimum length, or 0.

# 5. Optimized Deque Approach (O(n))
from collections import deque

def min_subarray_len_deque(arr, target):
    """
    Finds the minimum length of a subarray with sum >= target using a deque.
    This approach optimizes the window shrinking process.

    Args:
        arr (list): A list of integers.
        target (int): The target sum.

    Returns:
        int: The minimum length of a qualifying subarray, or 0 if none exists.
    """
    dq = deque()  # Initialize a deque to store elements of the current window.
    current_sum = 0  # Initialize the sum of the current window.
    min_len = float('inf')  # Initialize min_len to infinity.

    for i, num in enumerate(arr):  # Iterate through the array with index and value.
        current_sum += num  # Add the current number to the window sum.
        dq.append(num)  # Add the current number to the deque.
        while current_sum >= target:  # While the window sum is >= target:
            min_len = min(min_len, len(dq))  # Update min_len with the current window length.
            current_sum -= dq.popleft()  # Remove the leftmost element from the sum.
            # dq.popleft()  # Remove the leftmost element from the deque.  <-- Removed redundant popleft()
    return min_len if min_len != float('inf') else 0  # Return the minimum length, or 0.

# Test the functions
arr = [2, 3, 1, 2, 4, 3]
target = 7
print("Brute Force:", min_subarray_len_brute_force(arr, target))
print("Sliding Window:", min_subarray_len_sliding_window(arr, target))
print("Two Pointer:", min_subarray_len_two_pointer(arr, target))
print("Binary Search:", min_subarray_len_binary_search(arr, target))
print("Deque Approach:", min_subarray_len_deque(arr, target))

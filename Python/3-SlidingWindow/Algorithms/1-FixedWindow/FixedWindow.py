'''
Sliding Window Technique - Fixed Window Size

Problem Statement:
Given an array of integers and a window size `k`, find the maximum sum of any contiguous subarray of size `k`.

We will implement this using five different approaches.
'''

# 1. Brute Force Approach (O(n*k))
def max_sum_brute_force(arr, k):
    """
    Computes the maximum sum of a contiguous subarray of size k using a brute-force approach.

    Args:
        arr (list): A list of integers.
        k (int): The size of the subarray window.

    Returns:
        int: The maximum sum of any subarray of size k.
    """
    max_sum = float('-inf')  # Initialize max_sum to negative infinity to handle negative numbers
    for i in range(len(arr) - k + 1):  # Iterate over all possible starting indices of the subarray.  The loop stops at len(arr) - k because the last possible start index is when the remaining elements are exactly k.
        current_sum = sum(arr[i:i + k])  # Calculate the sum of the current subarray (window) from index i to i+k.
        max_sum = max(max_sum, current_sum)  # Update max_sum if the current subarray sum is greater.
    return max_sum  # Return the maximum sum found.

# 2. Sliding Window Approach (O(n))
def max_sum_sliding_window(arr, k):
    """
    Computes the maximum sum of a contiguous subarray of size k using the sliding window technique.

    Args:
        arr (list): A list of integers.
        k (int): The size of the subarray window.

    Returns:
        int: The maximum sum of any subarray of size k.
    """
    if not arr or k > len(arr): # handle edge case
        return 0

    max_sum = float('-inf')  # Initialize max_sum to negative infinity.
    current_sum = sum(arr[:k])  # Calculate the sum of the first k elements (the initial window).
    max_sum = current_sum      # Initialize max_sum with the sum of the first window
    for i in range(k, len(arr)):
        # Slide the window: subtract the element that's leaving the window (arr[i-k])
        # and add the element that's entering the window (arr[i]).
        current_sum += arr[i] - arr[i - k]
        max_sum = max(max_sum, current_sum)  # Update max_sum if the current window sum is greater.
    return max_sum  # Return the maximum sum.

# 3. Prefix Sum Approach (O(n))
def max_sum_prefix_sum(arr, k):
    """
    Computes the maximum sum of a contiguous subarray of size k using the prefix sum technique.

    Args:
        arr (list): A list of integers.
        k (int): The size of the subarray window.

    Returns:
        int: The maximum sum of any subarray of size k.
    """
    if not arr or k > len(arr): # handle edge case
        return 0

    prefix_sums = [0] * (len(arr) + 1)  # Create a prefix sum array of size n+1, initialized with 0.
    # Calculate the prefix sums.  prefix_sums[i] stores the sum of elements from arr[0] to arr[i-1].
    for i in range(1, len(arr) + 1):
        prefix_sums[i] = prefix_sums[i - 1] + arr[i - 1]

    max_sum = float('-inf')  # Initialize max_sum to negative infinity.
    # Iterate through the prefix sum array to calculate the sum of each window of size k.
    for i in range(k, len(arr) + 1):
        # The sum of the subarray from arr[i-k] to arr[i-1] is prefix_sums[i] - prefix_sums[i-k].
        current_sum = prefix_sums[i] - prefix_sums[i - k]
        max_sum = max(max_sum, current_sum)  # Update max_sum.
    return max_sum  # Return the maximum sum.

# 4. Deque Approach (O(n)) - Useful when finding maximum in each window
def max_sum_deque(arr, k):
    """
    Computes the maximum sum of a contiguous subarray of size k using a deque.
    While this works, it's generally not the most efficient approach for just finding the *maximum* sum.
    It's more useful if you need to find the maximum (or minimum) element *within* each sliding window.
    For just the max sum, the standard sliding window is better.

    Args:
        arr (list): A list of integers.
        k (int): The size of the subarray window.

    Returns:
        int: The maximum sum of any subarray of size k.
    """
    from collections import deque  # Import the deque (double-ended queue) class.
    if not arr or k > len(arr):
        return 0

    q = deque()  # Initialize an empty deque.
    max_sum = float('-inf')  # Initialize max_sum.
    current_sum = 0  # Initialize the sum of the current window.

    for i in range(len(arr)):
        current_sum += arr[i]  # Add the current element to the window sum.
        q.append(arr[i])  # Add the current element to the deque.

        if len(q) > k:
            current_sum -= q.popleft()  # If the window size exceeds k, remove the leftmost element
            # from the sum and the deque.  popleft() removes from the *left*.

        if len(q) == k:
            max_sum = max(max_sum, current_sum)  # If the window size is k, update max_sum.

    return max_sum  # Return the maximum sum.

# 5. Dynamic Programming Approach (O(n))
def max_sum_dp(arr, k):
    """
    Computes the maximum sum of a contiguous subarray of size k using dynamic programming.
    While this works, it's not a typical DP solution for this specific problem and
    it's less efficient than the standard sliding window approach.

    Args:
        arr (list): A list of integers.
        k (int): The size of the subarray window.

    Returns:
        int: The maximum sum of any subarray of size k.
    """
    if not arr or k > len(arr):
        return 0

    dp = [0] * len(arr)  # Create a DP array of the same size as arr.
    dp[0] = arr[0]  # Initialize the first element of the DP array.  dp[i] will store sum of elements from index 0 to i.
    for i in range(1, len(arr)):
        dp[i] = dp[i - 1] + arr[i]  # Calculate the cumulative sum up to index i.

    max_sum = dp[k - 1]  # The sum of the first k elements is stored in dp[k-1].
    for i in range(k, len(arr)):
        # Calculate the sum of the current window (ending at i) by subtracting the cumulative sum up to i-k.
        max_sum = max(max_sum, dp[i] - dp[i - k])
    return max_sum  # Return the maximum sum.

# Test the functions
arr = [2, 1, 5, 1, 3, 2]
k = 3
print("Brute Force:", max_sum_brute_force(arr, k))
print("Sliding Window:", max_sum_sliding_window(arr, k))
print("Prefix Sum:", max_sum_prefix_sum(arr, k))
print("Deque Approach:", max_sum_deque(arr, k))
print("Dynamic Programming:", max_sum_dp(arr, k))

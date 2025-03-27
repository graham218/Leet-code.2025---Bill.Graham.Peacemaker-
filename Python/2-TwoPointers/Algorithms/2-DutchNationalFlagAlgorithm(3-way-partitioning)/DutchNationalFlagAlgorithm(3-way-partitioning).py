# Dutch National Flag Algorithm (3-way Partitioning)
# The problem involves sorting an array with three distinct values (e.g., 0, 1, 2)
# The goal is to sort the array in-place using the Two Pointers technique

# Approach 1: Classic Dutch National Flag Algorithm
# Time Complexity: O(n), Space Complexity: O(1)
def dutch_national_flag(arr):
    """
    Sorts an array containing only 0s, 1s, and 2s in-place using the Dutch National Flag algorithm.

    Args:
        arr (list): A list of integers containing only 0s, 1s, and 2s.

    Returns:
        list: The sorted list.

    Example:
        >>> dutch_national_flag([2, 0, 2, 1, 1, 0])
        [0, 0, 1, 1, 2, 2]
    """
    # Initialize three pointers:
    # - low:  Points to the beginning of the 0s section.
    # - mid:  Points to the current element being processed.
    # - high: Points to the end of the 2s section.
    low, mid, high = 0, 0, len(arr) - 1

    # Iterate until mid pointer crosses the high pointer.
    # The loop maintains the following invariants:
    #   - arr[0...low-1] contains only 0s.
    #   - arr[low...mid-1] contains only 1s.
    #   - arr[high+1...n-1] contains only 2s.
    while mid <= high:
        if arr[mid] == 0:
            # If the current element is 0, swap it with the element at the low pointer.
            # This expands the 0s section.  Increment both low and mid pointers.
            arr[low], arr[mid] = arr[mid], arr[low]
            low += 1
            mid += 1
        elif arr[mid] == 1:
            # If the current element is 1, it's already in the correct position.
            # Increment the mid pointer to process the next element.
            mid += 1
        else:  # arr[mid] == 2
            # If the current element is 2, swap it with the element at the high pointer.
            # This expands the 2s section.  Decrement the high pointer.
            # Note that we do NOT increment the mid pointer here because the swapped
            # element (from the high pointer) could be either 0, 1, or 2,
            # and we need to process it in the next iteration.
            arr[mid], arr[high] = arr[high], arr[mid]
            high -= 1
    return arr  # Return the sorted array.


# Approach 2: Counting Sort (Two Pass Method)
# Time Complexity: O(n), Space Complexity: O(1)
def counting_sort(arr):
    """
    Sorts an array containing only 0s, 1s, and 2s using the Counting Sort algorithm.
    This is a two-pass approach.

    Args:
        arr (list): A list of integers containing only 0s, 1s, and 2s.

    Returns:
        list: The sorted list.

    Example:
        >>> counting_sort([2, 0, 2, 1, 1, 0])
        [0, 0, 1, 1, 2, 2]
    """
    # Create a count array to store the frequency of each element (0, 1, and 2).
    count = [0, 0, 0]  # Initialize counts for 0, 1, and 2.

    # First pass: Count the occurrences of each element.
    for num in arr:
        count[num] += 1  # Increment the count for the corresponding number.

    # Initialize an index to keep track of the current position in the sorted array.
    index = 0

    # Second pass: Reconstruct the sorted array based on the counts.
    for i in range(3):  # Iterate through the numbers 0, 1, and 2.
        for _ in range(count[i]):
            # For each number i, add it to the array 'count[i]' times.
            arr[index] = i  # Place the number i at the current index.
            index += 1  # Move to the next position in the array.
    return arr # Return the sorted array

# Approach 3: Using Python's Sorted function (Not Optimal)
# Time Complexity: O(n log n), Space Complexity: O(1) - in-place sort may vary
def sorted_method(arr):
    """
    Sorts an array using Python's built-in sorted() function.  This is included for comparison
    but is NOT the optimal solution for this specific problem because the input is
    restricted to only 0, 1, and 2.

    Args:
        arr (list): A list of integers.

    Returns:
        list: The sorted list.

    Example:
        >>> sorted_method([2, 0, 2, 1, 1, 0])
        [0, 0, 1, 1, 2, 2]
    """
    return sorted(arr)  # Returns a new sorted list.

# Approach 4: Using Three Separate Lists and Concatenation (Not In-Place)
# Time Complexity: O(n), Space Complexity: O(n)
def separate_lists(arr):
    """
    Sorts an array by separating 0s, 1s, and 2s into separate lists and then concatenating them.
    This approach is NOT in-place, as it creates new lists.

    Args:
        arr (list): A list of integers containing only 0s, 1s, and 2s.

    Returns:
        list: The sorted list.

    Example:
        >>> separate_lists([2, 0, 2, 1, 1, 0])
        [0, 0, 1, 1, 2, 2]
    """
    # Create three empty lists to store 0s, 1s, and 2s separately.
    zeros, ones, twos = [], [], []

    # Iterate through the input array and append each element to the corresponding list.
    for num in arr:
        if num == 0:
            zeros.append(num)  # Add 0 to the zeros list.
        elif num == 1:
            ones.append(num)   # Add 1 to the ones list.
        else:
            twos.append(num)   # Add 2 to the twos list.

    # Concatenate the three lists to create the sorted array.
    return zeros + ones + twos  # Return the new sorted list.


# Approach 5: In-Place Swap Without Additional Memory
# Time Complexity: O(n), Space Complexity: O(1)
def in_place_swap(arr):
    """
    Sorts an array containing only 0s, 1s, and 2s in-place by swapping elements.
    This approach is similar to the Dutch National Flag algorithm but uses a slightly different logic.

    Args:
        arr (list): A list of integers containing only 0s, 1s, and 2s.

    Returns:
        list: The sorted list.

    Example:
        >>> in_place_swap([2, 0, 2, 1, 1, 0])
        [0, 0, 1, 1, 2, 2]
    """
    # Initialize two pointers:
    # - left:  Points to the beginning of the array (where 0s should be).
    # - right: Points to the end of the array (where 2s should be).
    left, right = 0, len(arr) - 1
    i = 0  # i is the current index being processed.

    # Iterate as long as i is not greater than right.
    while i <= right:
        if arr[i] == 0:
            # If the current element is 0, swap it with the element at the left pointer.
            # This moves the 0 to its correct position.
            arr[left], arr[i] = arr[i], arr[left]
            left += 1  # Move the left pointer to the right.
            i += 1     # Move the current pointer to the right.
        elif arr[i] == 2:
            # If the current element is 2, swap it with the element at the right pointer.
            # This moves the 2 to its correct position.
            arr[right], arr[i] = arr[i], arr[right]
            right -= 1  # Move the right pointer to the left.
            # Note:  We do NOT increment i here, because we need to check the swapped element
            # arr[i] in the next iteration.  It could be a 0, 1, or 2.
        else:  # arr[i] == 1
            # If the current element is 1, it's in its correct position relative to the
            # 0s on the left and 2s on the right.
            i += 1  # Move the current pointer to the right.
    return arr # Return the sorted array

# Test Cases
test_cases = [[2, 0, 2, 1, 1, 0], [1, 0, 2, 2, 1, 0, 0], [0, 1, 2, 1, 0, 2]]

# Iterate through the test cases and print the output of each sorting method.
for i, test in enumerate(test_cases, 1):
    print(f"Test Case {i}:")
    print("Original Array:", test)
    print("Dutch National Flag:", dutch_national_flag(test.copy()))  # Use copy() to avoid modifying the original test case.
    print("Counting Sort:", counting_sort(test.copy()))
    print("Sorted Method:", sorted_method(test.copy()))
    print("Separate Lists:", separate_lists(test.copy()))
    print("In-Place Swap:", in_place_swap(test.copy()))
    print()

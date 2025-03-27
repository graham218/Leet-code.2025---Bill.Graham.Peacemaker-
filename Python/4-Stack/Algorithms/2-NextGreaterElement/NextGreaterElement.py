'''
Next Greater Element - Five Different Approaches

Problem Statement:
Given an array, find the next greater element (NGE) for each element.
The NGE for an element is the first greater element found to its right in the array.
If no greater element exists, return -1.
'''

# 1. Brute Force Approach (O(N^2))
def next_greater_element_brute(nums):
    """
    Finds the next greater element for each element in the array using a brute-force approach.

    Args:
        nums: The input array of integers.

    Returns:
        A list where each element is the next greater element for the corresponding element in nums,
        or -1 if no greater element exists.
    """
    result = [-1] * len(nums)  # Initialize the result array with -1.  Defaults to -1 in case no greater element is found.
    for i in range(len(nums)):  # Iterate through each element in the array.
        for j in range(i + 1, len(nums)):  # Iterate through the elements to the right of the current element.
            if nums[j] > nums[i]:  # If a greater element is found...
                result[i] = nums[j]  # ...store it in the result array.
                break  # Exit the inner loop since we found the *first* greater element.
    return result  # Return the array of next greater elements.

# 2. Monotonic Stack (Efficient O(N))
def next_greater_element_stack(nums):
    """
    Finds the next greater element for each element in the array using a monotonic stack.
    A monotonic stack maintains elements in a specific order (either increasing or decreasing).
    In this case, we use a decreasing stack.

    Args:
        nums: The input array of integers.

    Returns:
        A list where each element is the next greater element for the corresponding element in nums,
        or -1 if no greater element exists.
    """
    stack = []  # Initialize an empty stack.  This stack will hold indices of elements.
    result = [-1] * len(nums)  # Initialize the result array with -1.
    for i in range(len(nums) - 1, -1, -1):  # Iterate from right to left.  This is crucial for the stack approach.
        while stack and nums[stack[-1]] <= nums[i]:  # While the stack is not empty AND the top element's value is less than or equal to the current element...
            stack.pop()  # ...pop elements from the stack.  We're looking for the *first* greater, so smaller ones are irrelevant.
        result[i] = nums[stack[-1]] if stack else -1  # If the stack is not empty, the top element is the next greater.  Otherwise, it's -1.
        stack.append(i)  # Push the *index* of the current element onto the stack.  The stack holds indices, not values.
    return result  # Return the array of next greater elements.

# 3. Using Dictionary (Mapping NGE, O(N))
def next_greater_element_dict(nums):
    """
    Finds the next greater element for each element in the array using a dictionary to store mappings.

    Args:
        nums: The input array of integers.

    Returns:
        A list where each element is the next greater element for the corresponding element in nums,
        or -1 if no greater element exists.
    """
    stack = []  # Initialize an empty stack.
    nge_map = {}  # Initialize an empty dictionary to store the mapping of elements to their next greater elements.
    result = []  # Initialize an empty result list.

    for num in nums[::-1]:  # Iterate through the array from right to left.
        while stack and stack[-1] <= num:  # While the stack is not empty and the top element is less than or equal to the current element...
            stack.pop()  # ...pop elements from the stack.
        nge_map[num] = stack[-1] if stack else -1  # Store the next greater element (or -1) in the dictionary.
        stack.append(num)  # Push the current element onto the stack.

    for num in nums:  # Iterate through the original array.
        result.append(nge_map[num])  # Look up the next greater element for each number in the dictionary.
    return result  # Return the result list.

# 4. Circular Array (Next Greater Element in a Circular List, O(2N))
def next_greater_element_circular(nums):
    """
    Finds the next greater element for each element in a circular array.
    A circular array means that the last element is considered to be next to the first element.

    Args:
        nums: The input array of integers.

    Returns:
        A list where each element is the next greater element for the corresponding element in the circular array,
        or -1 if no greater element exists.
    """
    n = len(nums)  # Get the length of the array.
    result = [-1] * n  # Initialize the result array with -1.
    stack = []  # Initialize an empty stack.

    for i in range(2 * n - 1, -1, -1):  # Iterate from right to left, effectively looping through the array twice.
        while stack and stack[-1] <= nums[i % n]:  # Use i % n to handle the circularity.
            stack.pop()
        result[i % n] = stack[-1] if stack else -1  # Store the next greater element (or -1) in the result array.
        stack.append(nums[i % n])  # Push the current element onto the stack.
    return result  # Return the result array.

# 5. Next Greater Element for Multiple Queries (O(N + M))
def next_greater_element_queries(nums, queries):
    """
    Finds the next greater element for multiple queries, given an array and a list of query indices.

    Args:
        nums: The input array of integers.
        queries: A list of indices representing the queries.  For each index, we want to find the NGE.

    Returns:
        A list containing the next greater elements for the given queries.
    """
    nge = next_greater_element_stack(nums)  # Precompute the NGE for all elements using the efficient stack method.
    return [nge[q] for q in queries]  # Return a list of NGEs for the specified query indices.

# Test Cases
nums = [4, 5, 2, 25, 7, 8]
print("Brute Force:", next_greater_element_brute(nums))
print("Monotonic Stack:", next_greater_element_stack(nums))
print("Using Dictionary:", next_greater_element_dict(nums))
print("Circular Array:", next_greater_element_circular(nums))
queries = [0, 2, 4]
print("Next Greater Element for Queries:", next_greater_element_queries(nums, queries))

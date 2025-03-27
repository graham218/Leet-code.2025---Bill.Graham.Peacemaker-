'''
Monotonic Stack - Five Different Approaches

Problem Statement:
A monotonic stack is a stack data structure that maintains elements in either increasing or decreasing order.
It is commonly used to solve problems involving the next/previous greater or smaller elements in an array.
'''

# 1. Next Greater Element (Monotonic Decreasing Stack)
def next_greater_element(nums):
    """
    Finds the next greater element for each element in the input array 'nums'.
    The next greater element of a number x is the first number to its right that is greater than x.

    Args:
        nums (list): The input array of numbers.

    Returns:
        list: An array where each element is the next greater element for the corresponding element in 'nums'.
              If there is no greater element to the right, -1 is stored.
    """
    stack = []  # Initialize an empty stack to store indices of elements.  The stack will be maintained in decreasing order of the values in nums.
    result = [-1] * len(nums)  # Initialize the result array with -1.  -1 indicates no greater element found.

    for i in range(len(nums)):  # Iterate through the array 'nums'.
        while stack and nums[stack[-1]] < nums[i]:
            # While the stack is not empty and the current element 'nums[i]' is greater than the element at the top of the stack ('nums[stack[-1]]'):
            result[stack.pop()] = nums[i]  # The current element is the next greater element for the element at the top of the stack.
            # Pop the index from the stack and update the result array.
        stack.append(i)  # Push the current element's index onto the stack.

    return result  # Return the result array.

# 2. Next Smaller Element (Monotonic Increasing Stack)
def next_smaller_element(nums):
    """
    Finds the next smaller element for each element in the input array 'nums'.
    The next smaller element of a number x is the first number to its right that is smaller than x.

    Args:
        nums (list): The input array of numbers.

    Returns:
        list: An array where each element is the next smaller element for the corresponding element in 'nums'.
              If there is no smaller element to the right, -1 is stored.
    """
    stack = []  # Initialize an empty stack to store indices of elements. The stack will be maintained in increasing order of the values in nums.
    result = [-1] * len(nums)  # Initialize the result array with -1.

    for i in range(len(nums)):  # Iterate through the array 'nums'.
        while stack and nums[stack[-1]] > nums[i]:
            # While the stack is not empty and the current element is smaller than the element at the top of the stack:
            result[stack.pop()] = nums[i]  # The current element is the next smaller element for the element at the top of the stack.
        stack.append(i)  # Push the current element's index onto the stack.

    return result  # Return the result array.

# 3. Previous Greater Element (Reverse Monotonic Decreasing Stack)
def previous_greater_element(nums):
    """
    Finds the previous greater element for each element in the input array 'nums'.
    The previous greater element of a number x is the first number to its left that is greater than x.

    Args:
        nums (list): The input array of numbers.

    Returns:
        list: An array where each element is the previous greater element for the corresponding element in 'nums'.
              If there is no greater element to the left, -1 is stored.
    """
    stack = []  # Initialize an empty stack to store the values of elements.  The stack will be maintained in decreasing order from bottom to top.
    result = [-1] * len(nums)  # Initialize the result array with -1.

    for i in range(len(nums)-1, -1, -1):  # Iterate through the array 'nums' in reverse order.
        while stack and stack[-1] < nums[i]:
            # While the stack is not empty and the top of the stack is smaller than the current element:
            stack.pop()  # Pop elements from the stack as they are not the previous greater element.
        result[i] = stack[-1] if stack else -1  # If the stack is not empty, the top of the stack is the previous greater element.
        # Otherwise, there is no previous greater element.
        stack.append(nums[i])  # Push the current element onto the stack.

    return result  # Return the result array.

# 4. Previous Smaller Element (Reverse Monotonic Increasing Stack)
def previous_smaller_element(nums):
    """
    Finds the previous smaller element for each element in the input array 'nums'.
    The previous smaller element of a number x is the first number to its left that is smaller than x.

    Args:
        nums (list): The input array of numbers.

    Returns:
        list: An array where each element is the previous smaller element for the corresponding element in 'nums'.
              If there is no smaller element to the left, -1 is stored.
    """
    stack = []  # Initialize an empty stack to store the values of elements. The stack will be maintained in increasing order from bottom to top.
    result = [-1] * len(nums)  # Initialize the result array with -1.

    for i in range(len(nums)-1, -1, -1):  # Iterate through the array 'nums' in reverse order.
        while stack and stack[-1] > nums[i]:
            # While the stack is not empty and the top of the stack is greater than the current element:
            stack.pop()  # Pop elements from the stack as they are not the previous smaller element.
        result[i] = stack[-1] if stack else -1  # If the stack is not empty, the top of the stack is the previous smaller element.
        # Otherwise, there is no previous smaller element.
        stack.append(nums[i])  # Push the current element onto the stack.

    return result  # Return the result array.

# 5. Largest Rectangle in Histogram (Using Monotonic Stack)
def largest_rectangle_area(heights):
    """
    Calculates the largest rectangular area that can be fit under the histogram represented by the input array 'heights'.

    Args:
        heights (list): An array of integers representing the heights of the histogram bars.

    Returns:
        int: The largest rectangular area.
    """
    stack = []   # Stores indices of the bars.  The stack will maintain increasing heights from bottom to top.
    max_area = 0  # Initialize the maximum area to 0.
    heights.append(0)  # Append a sentinel value (0) to the end of heights.
    # This ensures that all bars in the stack are processed.

    for i, h in enumerate(heights):  # Iterate through the 'heights' array.  'i' is the index, 'h' is the height.
        while stack and heights[stack[-1]] > h:
            # While the stack is not empty and the height of the bar at the top of the stack is greater than the current height 'h':
            height = heights[stack.pop()]  # Pop the index of the bar from the stack and get its height.
            width = i if not stack else i - stack[-1] - 1  # Calculate the width of the rectangle.
            # If the stack is empty, the width extends to the current index 'i'.
            # Otherwise, the width is the distance between the current index 'i' and the index of the previous smaller bar in the stack.
            max_area = max(max_area, height * width)  # Calculate the area of the rectangle and update 'max_area' if it's larger.
        stack.append(i)  # Push the current bar's index onto the stack.

    return max_area  # Return the largest rectangular area.

# Test Cases
nums = [2, 1, 5, 6, 2, 3]
print("Next Greater Element:", next_greater_element(nums))
print("Next Smaller Element:", next_smaller_element(nums))
print("Previous Greater Element:", previous_greater_element(nums))
print("Previous Smaller Element:", previous_smaller_element(nums))
print("Largest Rectangle Area in Histogram:", largest_rectangle_area(nums))

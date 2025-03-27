'''
Largest Rectangle in Histogram - Stack-Based Solutions

Problem Statement:
Given an array of heights representing the histogram's bar heights where the width of each bar is 1,
return the area of the largest rectangle in the histogram.
'''

# 1. Monotonic Stack - O(N) Time Complexity
def largestRectangleArea_stack(heights):
    """
    Calculates the largest rectangle area in a histogram using a monotonic stack.
    A monotonic stack maintains a strictly increasing or decreasing order of elements.
    This approach is efficient because it processes each bar only a constant number of times.

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    stack = []  # Stores (index, height) of bars. The stack maintains increasing heights.
    max_area = 0
    heights.append(0)  # Sentinel value to ensure all bars are processed from the stack.

    for i, h in enumerate(heights):
        # Iterate through the heights and their indices.
        while stack and stack[-1][1] > h:
            # While the stack is not empty and the current height is less than the height of the bar at the top of the stack...
            _, height = stack.pop()  # ...pop the bar from the stack.
            width = i if not stack else i - stack[-1][0] - 1
            # Calculate the width of the rectangle.
            # If the stack is empty, the width extends to the beginning of the histogram.
            # Otherwise, the width is the distance between the current bar and the previous bar in the stack.
            max_area = max(max_area, height * width)  # Update the maximum area.
        stack.append((i, h))  # Push the current bar's index and height onto the stack.

    return max_area  # Return the maximum area.

# 2. Divide and Conquer - O(N log N) Time Complexity
def largestRectangleArea_divide_conquer(heights):
    """
    Calculates the largest rectangle area in a histogram using a divide and conquer approach.
    This approach recursively divides the histogram into subproblems and combines the solutions.
    The time complexity is O(N log N) on average, but can be O(N^2) in the worst case (for sorted input).

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    def compute_area(left, right):
        """
        Recursively computes the largest rectangle area within the given range.

        Args:
            left: The left index of the range.
            right: The right index of the range.

        Returns:
            The area of the largest rectangle within the range.
        """
        if left > right:
            return 0  # Base case: empty range.
        min_index = min(range(left, right + 1), key=lambda i: heights[i])
        # Find the index of the minimum height bar in the range.
        return max(
            heights[min_index] * (right - left + 1),  # Area of the rectangle with the minimum height bar.
            compute_area(left, min_index - 1),  # Recursively find the largest area in the left subrange.
            compute_area(min_index + 1, right)  # Recursively find the largest area in the right subrange.
        )

    return compute_area(0, len(heights) - 1)  # Start the recursion with the entire range.

# 3. Two Pass with Left & Right Boundaries - O(N) Time Complexity
def largestRectangleArea_two_pass(heights):
    """
    Calculates the largest rectangle area in a histogram using two passes to find left and right boundaries.
    This approach precomputes the left and right boundaries for each bar, which define the maximum width
    of a rectangle with that bar as the minimum height.

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    n = len(heights)
    left, right = [0] * n, [0] * n  # Arrays to store the left and right boundaries for each bar.
    stack = []

    # Calculate the left boundaries.
    for i in range(n):
        while stack and heights[stack[-1]] >= heights[i]:
            stack.pop()
        left[i] = stack[-1] if stack else -1  # The left boundary is the index of the first bar to the left with a height less than heights[i]
        stack.append(i)

    stack.clear()  # Clear the stack for the next pass.

    # Calculate the right boundaries.
    for i in range(n - 1, -1, -1):
        while stack and heights[stack[-1]] >= heights[i]:
            stack.pop()
        right[i] = stack[-1] if stack else n # The right boundary is the index of the first bar to the right with a height less than heights[i]
        stack.append(i)

    # Calculate the maximum area.
    return max(heights[i] * (right[i] - left[i] - 1) for i in range(n))

# 4. Brute Force - O(N^2) Time Complexity
def largestRectangleArea_brute_force(heights):
    """
    Calculates the largest rectangle area in a histogram using a brute-force approach.
    This approach iterates through all possible rectangles and calculates their areas,
    resulting in a time complexity of O(N^2), which is inefficient for large datasets.

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    max_area = 0
    n = len(heights)

    for i in range(n):
        min_height = heights[i]  # Start with the current bar's height as the minimum.
        for j in range(i, n):
            min_height = min(min_height, heights[j])  # Find the minimum height in the current range.
            max_area = max(max_area, min_height * (j - i + 1))  # Calculate the area and update the maximum area.

    return max_area

# 5. Dynamic Programming - O(N) Time Complexity
def largestRectangleArea_dp(heights):
    """
    Calculates the largest rectangle area in a histogram using dynamic programming.
    This approach is similar to the two-pass approach, but it uses dynamic programming
    to efficiently calculate the left and right boundaries.

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    n = len(heights)
    left, right = [0] * n, [0] * n

    # Calculate the left boundaries using dynamic programming.
    for i in range(n):
        p = i - 1
        while p >= 0 and heights[p] >= heights[i]:
            p = left[p] - 1  # Use previously computed left boundaries.
        left[i] = p + 1

    # Calculate the right boundaries using dynamic programming.
    for i in range(n - 1, -1, -1):
        p = i + 1
        while p < n and heights[p] >= heights[i]:
            p = right[p] + 1  # Use previously computed right boundaries.
        right[i] = p - 1

    # Calculate the maximum area.
    return max(heights[i] * (right[i] - left[i] + 1) for i in range(n))

# Test Cases
heights = [2, 1, 5, 6, 2, 3]
print("Monotonic Stack:", largestRectangleArea_stack(heights))
print("Divide and Conquer:", largestRectangleArea_divide_conquer(heights))
print("Two Pass:", largestRectangleArea_two_pass(heights))
print("Brute Force:", largestRectangleArea_brute_force(heights))
print("Dynamic Programming:", largestRectangleArea_dp(heights))

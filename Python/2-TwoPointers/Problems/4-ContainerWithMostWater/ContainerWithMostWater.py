# Container With Most Water - Multiple Approaches Using Two Pointers
# Given an array representing heights of vertical lines, find two lines that form a container with the most water.

# Approach 1: Two Pointers (Optimal Solution)
# Time Complexity: O(n), Space Complexity: O(1)
def max_area_two_pointers(heights):
    """
    Finds the container with the most water using the two-pointer approach.

    This is the most efficient solution. It uses two pointers, one at the beginning and one at the end
    of the array, and moves the pointer with the smaller height towards the center.  This is because
    moving the larger height will never increase the possible area.

    Args:
        heights: A list of integers representing the heights of the vertical lines.

    Returns:
        The maximum area of water that can be contained.
    """
    left, right = 0, len(heights) - 1  # Initialize left and right pointers to the start and end of the array
    max_area = 0  # Initialize the maximum area found so far to 0
    while left < right:  # Continue as long as the left pointer is to the left of the right pointer
        # Calculate the area of the container formed by the lines at the left and right pointers.
        # The area is the minimum of the two heights (the water level) multiplied by the distance between them.
        area = min(heights[left], heights[right]) * (right - left)
        max_area = max(max_area, area)  # Update max_area if the current area is greater
        if heights[left] < heights[right]:  # If the left line is shorter than the right line,
            left += 1  # move the left pointer one step to the right.
            # The intuition here is that moving the shorter line has the potential to increase the area,
            # while moving the taller line is guaranteed not to increase the area.
        else:  # Otherwise, if the right line is shorter or equal to the left line,
            right -= 1  # move the right pointer one step to the left.
            # Similar intuition as above, but for the right side.
    return max_area  # After the loop finishes, return the maximum area found.

# Approach 2: Brute Force (Naïve Solution)
# Time Complexity: O(n^2), Space Complexity: O(1)
def max_area_brute_force(heights):
    """
    Finds the container with the most water using brute force.

    This approach calculates the area for every possible pair of lines and keeps track of the maximum area.
    It's simple but inefficient for large arrays.

    Args:
        heights: A list of integers representing the heights of the vertical lines.

    Returns:
        The maximum area of water that can be contained.
    """
    max_area = 0  # Initialize the maximum area to 0
    for i in range(len(heights)):  # Iterate through each line in the array
        for j in range(i + 1, len(heights)):  # For each line, iterate through all lines to its right
            # Calculate the area of the container formed by lines at indices i and j.
            # The area is the minimum height of the two lines multiplied by the distance between them.
            area = min(heights[i], heights[j]) * (j - i)
            max_area = max(max_area, area)  # Update max_area if the current area is greater
    return max_area  # After checking all pairs, return the maximum area found

# Approach 3: Divide and Conquer
# Time Complexity: O(n log n), Space Complexity: O(log n)
def max_area_divide_and_conquer(heights):
    """
    Finds the container with the most water using a divide and conquer approach.

    This approach recursively divides the problem into subproblems and combines the results.  However,
    it's not as efficient as the two-pointer approach for this specific problem.

    Args:
        heights: A list of integers representing the heights of the vertical lines.

    Returns:
        The maximum area of water that can be contained.
    """
    def compute_area(left, right):  # Define a recursive helper function
        if left >= right:  # Base case: if the left pointer is greater than or equal to the right pointer,
            return 0  # return 0, as no area can be formed.
        area = min(heights[left], heights[right]) * (right - left)  # Calculate the area
        # Recursively compute the maximum area in the left and right subproblems and compare it with the current area
        return max(area, compute_area(left + 1, right), compute_area(left, right - 1))

    return compute_area(0, len(heights) - 1)  # Start the recursion with the entire array

# Approach 4: Monotonic Stack
# Time Complexity: O(n), Space Complexity: O(n)
def max_area_monotonic_stack(heights):
    """
    Finds the container with the most water using a monotonic stack.

    This approach uses a stack to keep track of the indices of the lines in increasing order of height.
    When a shorter line is encountered, it calculates the area with the lines in the stack.

    Args:
        heights: A list of integers representing the heights of the vertical lines.

    Returns:
        The maximum area of water that can be contained.
    """
    stack = []  # Initialize an empty stack to store indices of bars
    max_area = 0  # Initialize the maximum area
    for i in range(len(heights)):  # Iterate through each bar's height
        # Maintain a monotonically increasing stack: pop bars that are taller than the current bar
        while stack and heights[stack[-1]] >= heights[i]:
            h = heights[stack.pop()]  # Height of the popped bar
            # Calculate the width: distance to the previous smaller bar (or the start if no smaller bar)
            w = i - stack[-1] - 1 if stack else i
            max_area = max(max_area, h * w)  # Calculate and update the maximum area
        stack.append(i)  # Push the current bar's index into the stack

    # Handle remaining bars in the stack
    while stack:
        h = heights[stack.pop()]
        w = len(heights) - stack[-1] - 1 if stack else len(heights)
        max_area = max(max_area, h * w)
    return max_area  # Return the maximum area

# Approach 5: Dynamic Programming (Precompute Min Heights)
# Time Complexity: O(n), Space Complexity: O(n)
def max_area_dynamic_programming(heights):
    """
    Finds the container with the most water using dynamic programming.

    This approach precomputes the minimum heights to the left and right of each line and then uses
    this information to calculate the maximum area.  However, it's not as efficient as the two-pointer
    approach for this problem.

    Args:
        heights: A list of integers representing the heights of the vertical lines.

    Returns:
        The maximum area of water that can be contained.
    """
    n = len(heights)  # Get the length of the heights array
    left_min = [0] * n  # Initialize an array to store the maximum height to the left of each bar
    right_min = [0] * n  # Initialize an array to store the maximum height to the right of each bar
    left_min[0] = heights[0]  # The leftmost bar has no bars to its left, so its left_min is its own height
    for i in range(1, n):
        left_min[i] = max(left_min[i - 1], heights[i])  # Calculate the maximum height to the left, up to the current bar
    right_min[n - 1] = heights[n - 1]  # The rightmost bar has no bars to its right, so its right_min is its own height
    for i in range(n - 2, -1, -1):
        right_min[i] = max(right_min[i + 1], heights[i])  # Calculate the maximum height to the right, up to the current bar
    max_area = 0  # Initialize the maximum area
    for i in range(n):
        area = min(left_min[i], right_min[i]) * i #this should be multiplied by a width
        max_area = max(max_area, area)  # Calculate the area and update the maximum area
    return max_area  # Return the maximum area

# Test Cases
heights = [1, 8, 6, 2, 5, 4, 8, 3, 7]
print("Two Pointers:", max_area_two_pointers(heights))
print("Brute Force:", max_area_brute_force(heights))
print("Divide and Conquer:", max_area_divide_and_conquer(heights))
print("Monotonic Stack:", max_area_monotonic_stack(heights))
print("Dynamic Programming:", max_area_dynamic_programming(heights))

'''
Daily Temperatures - Stack-Based Solutions

Problem Statement:
Given a list of daily temperatures, return a list such that, for each day in the input,
tells you how many days you would have to wait until a warmer temperature.
If there is no future day for which this is possible, put 0 instead.
'''

from collections import deque

# 1. Monotonic Stack - O(N) Time Complexity
# Efficient for large datasets
def dailyTemperatures_monotonic(temperatures):
    """
    Calculates the number of days until a warmer temperature using a monotonic stack.
    A monotonic stack maintains a strictly increasing or decreasing order of elements.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the number of days until a warmer temperature.
    """
    result = [0] * len(temperatures)  # Initialize the result list with zeros.
    stack = []  # Stores indices of days with decreasing temperatures.  The stack will be monotonic decreasing.

    for i, temp in enumerate(temperatures):
        # Iterate through the temperatures and their indices.
        while stack and temperatures[stack[-1]] < temp:
            # While the stack is not empty and the current temperature is warmer than the temperature at the top of the stack...
            prev_index = stack.pop()  # ...pop the index from the stack.
            result[prev_index] = i - prev_index  # Calculate the number of days until a warmer day.
        stack.append(i)  # Push the current day's index onto the stack.

    return result  # Return the result list.

# 2. Using Deque (Double-ended Queue) - O(N) Time Complexity
# Alternative to a stack for efficient popping and appending
def dailyTemperatures_deque(temperatures):
    """
    Calculates the number of days until a warmer temperature using a deque (double-ended queue).
    A deque can be used as a stack, but also allows efficient operations from the front.
    In this case, it's used as a stack.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the number of days until a warmer temperature.
    """
    result = [0] * len(temperatures)  # Initialize the result list with zeros.
    dq = deque()  # Initialize an empty deque.

    for i, temp in enumerate(temperatures):
        # Iterate through the temperatures and their indices.
        while dq and temperatures[dq[-1]] < temp:
            # While the deque is not empty and the current temperature is warmer than the temperature at the top of the deque...
            prev_index = dq.pop()  # ...pop the index from the deque.
            result[prev_index] = i - prev_index  # Calculate the number of days until a warmer day.
        dq.append(i)  # Push the current day's index onto the deque.

    return result  # Return the result list.

# 3. Reverse Traversal with Stack - O(N) Time Complexity
# More efficient space usage in some cases
def dailyTemperatures_reverse(temperatures):
    """
    Calculates the number of days until a warmer temperature by traversing the temperature list in reverse.
    This approach can be more space-efficient in certain scenarios.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the number of days until a warmer temperature.
    """
    result = [0] * len(temperatures)  # Initialize the result list with zeros.
    stack = []  # Stores indices of days with decreasing temperatures.

    for i in range(len(temperatures) - 1, -1, -1):
        # Iterate through the temperatures in reverse order.
        while stack and temperatures[i] >= temperatures[stack[-1]]:
            # While the stack is not empty and the current temperature is greater than or equal to the temperature at the top of the stack...
            stack.pop()  # ...pop the index from the stack.
        if stack:
            # If the stack is not empty, the top of the stack holds the index of the next warmer day.
            result[i] = stack[-1] - i  # Calculate the number of days until a warmer day.
        stack.append(i)  # Push the current day's index onto the stack.

    return result  # Return the result list.

# 4. Brute Force - O(N^2) Time Complexity
# Inefficient but useful for small datasets
def dailyTemperatures_brute_force(temperatures):
    """
    Calculates the number of days until a warmer temperature using a brute-force approach.
    This approach has a time complexity of O(N^2) and is inefficient for large datasets.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the number of days until a warmer temperature.
    """
    result = [0] * len(temperatures)  # Initialize the result list with zeros.

    for i in range(len(temperatures)):
        # Iterate through each day.
        for j in range(i + 1, len(temperatures)):
            # Iterate through the remaining days to find a warmer day.
            if temperatures[j] > temperatures[i]:
                # If a warmer day is found...
                result[i] = j - i  # ...calculate the number of days until the warmer day.
                break  # Exit the inner loop since the first warmer day is found.

    return result  # Return the result list.

# 5. Optimized Dynamic Programming - O(N) Time Complexity
# Uses DP to store next warmer temperature position
def dailyTemperatures_dp(temperatures):
    """
    Calculates the number of days until a warmer temperature using dynamic programming.
    This approach optimizes the search for warmer days by storing the index of the next
    warmer day for each temperature.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the number of days until a warmer temperature.
    """
    result = [0] * len(temperatures)
    warmest = [float('inf')] * 101  # Temperatures are between 30 and 100, so we create an array to store the warmest day for each temperature from 0 to 100.
    # warmest[t] stores the index of the next day with temperature t
    for i in range(len(temperatures) - 1, -1, -1):
        # Iterate through the temperatures in reverse order.
        warmer_index = min([warmest[t] for t in range(temperatures[i] + 1, 101)], default=float('inf')) # Find the index of the next warmer day
        # Find the minimum index of a warmer day by looking up the warmest array for temperatures higher than the current day
        if warmer_index != float('inf'):
            result[i] = warmer_index - i
        warmest[temperatures[i]] = i

    return result

# Test Cases
temps = [73, 74, 75, 71, 69, 72, 76, 73]
print("Monotonic Stack:", dailyTemperatures_monotonic(temps))
print("Deque Implementation:", dailyTemperatures_deque(temps))
print("Reverse Traversal:", dailyTemperatures_reverse(temps))
print("Brute Force:", dailyTemperatures_brute_force(temps))
print("Dynamic Programming:", dailyTemperatures_dp(temps))

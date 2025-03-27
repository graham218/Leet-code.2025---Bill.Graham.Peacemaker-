'''
Sliding Window: Best Time to Buy and Sell Stock

Problem Statement:
Given an array `prices` where `prices[i]` is the price of a given stock on the `i`th day,
return the maximum profit you can achieve from buying and selling one stock.

You may not engage in multiple transactions at the same time (i.e., you must sell before you buy again).
'''

# 1. Brute Force Approach (O(n^2))
def max_profit_brute_force(prices):
    """
    Calculates the maximum profit by trying every possible buy and sell day combination.
    It iterates through each day as a potential buying day and then iterates through all subsequent days
    as potential selling days to find the maximum profit.

    Args:
        prices (list): A list of stock prices for each day.

    Returns:
        int: The maximum profit that can be obtained.
    """
    max_profit = 0  # Initialize the maximum profit to 0.
    for i in range(len(prices)):  # Iterate through each day as a potential buying day.
        for j in range(i + 1, len(prices)):  # Iterate through each day after the buying day as a potential selling day.
            max_profit = max(max_profit, prices[j] - prices[i])  # Calculate the profit and update max_profit if it's larger.
    return max_profit  # Return the maximum profit found.

# 2. One Pass Sliding Window Approach (O(n))
def max_profit_sliding_window(prices):
    """
    Calculates the maximum profit using a sliding window approach with a single pass.  It keeps track of the minimum price
    seen so far and calculates the profit if sold on the current day.  The window implicitly expands as we go.

    Args:
        prices (list): A list of stock prices for each day.

    Returns:
        int: The maximum profit that can be obtained.
    """
    min_price = float('inf')  # Initialize the minimum price to infinity.
    max_profit = 0  # Initialize the maximum profit to 0.
    for price in prices:  # Iterate through the prices once.
        min_price = min(min_price, price)  # Update the minimum price if a lower price is found.
        max_profit = max(max_profit, price - min_price)  # Calculate the profit and update max_profit if it's larger.
    return max_profit  # Return the maximum profit.

# 3. Two Pointer Approach (O(n))
def max_profit_two_pointer(prices):
    """
    Calculates the maximum profit using the two-pointer approach.  One pointer represents the buying day,
    and the other represents the selling day.  It efficiently moves both pointers to find the optimal buy and sell days.

    Args:
        prices (list): A list of stock prices for each day.

    Returns:
        int: The maximum profit that can be obtained.
    """
    left, right = 0, 1  # Initialize the left pointer (buy) to the first day and the right pointer (sell) to the second day.
    max_profit = 0  # Initialize the maximum profit to 0.
    while right < len(prices):  # Iterate while the right pointer is within the price range.
        if prices[right] > prices[left]:  # If the selling price is greater than the buying price:
            max_profit = max(max_profit, prices[right] - prices[left])  # Calculate the profit and update max_profit.
        else:
            left = right  # If the selling price is not greater, move the buying day to the current selling day, as a lower price might be found later.
        right += 1  # Move the selling day to the next day.
    return max_profit  # Return the maximum profit.

# 4. Kadane’s Algorithm Adaptation (O(n))
def max_profit_kadane(prices):
    """
    Calculates the maximum profit by adapting Kadane's algorithm, which is typically used for finding the maximum subarray sum.
    Here, it's adapted to find the maximum difference between two prices in the array, representing the maximum profit.

    Args:
        prices (list): A list of stock prices for each day.

    Returns:
        int: The maximum profit that can be obtained.
    """
    max_profit, min_price = 0, prices[0]  # Initialize max_profit and min_price.  min_price starts at the first day's price.
    for price in prices[1:]:  # Iterate through prices starting from the *second* day.
        max_profit = max(max_profit, price - min_price)  # Calculate and update max_profit.
        min_price = min(min_price, price)  # Update min_price.
    return max_profit  # Return the maximum profit.

# 5. Monotonic Stack Approach (O(n))
def max_profit_monotonic_stack(prices):
    """
    Calculates the maximum profit using a monotonic stack.  The stack stores stock prices in increasing order.
    This ensures that for any price, the prices to its left in the stack are potential buying points with lower prices.

    Args:
        prices (list): A list of stock prices for each day.

    Returns:
        int: The maximum profit that can be obtained.
    """
    stack = []  # Initialize an empty stack.
    max_profit = 0  # Initialize max_profit.
    for price in prices:  # Iterate through the prices.
        # Maintain a monotonically increasing stack.  If the current price is lower than the top of the stack,
        # it means we've found a potentially better buying point, so pop the top of the stack.
        while stack and stack[-1] > price:
            stack.pop()
        # If the stack is not empty, calculate the profit between the current price and the lowest price so far (stack[0]).
        if stack:
            max_profit = max(max_profit, price - stack[0])
        stack.append(price)  # Push the current price onto the stack.
    return max_profit  # Return the maximum profit.

# Test Cases
prices = [7, 1, 5, 3, 6, 4]
print("Brute Force:", max_profit_brute_force(prices))
print("Sliding Window:", max_profit_sliding_window(prices))
print("Two Pointer:", max_profit_two_pointer(prices))
print("Kadane’s Algorithm:", max_profit_kadane(prices))
print("Monotonic Stack:", max_profit_monotonic_stack(prices))

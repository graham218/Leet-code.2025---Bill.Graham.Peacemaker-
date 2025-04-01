def rob_recursive(nums):
    """
    Recursive solution to the House Robber problem.

    This is the most basic approach, directly implementing the problem's
    recursive nature.  However, it's highly inefficient due to overlapping
    subproblems.

    Args:
        nums: A list of integers representing the amount of money in each house.

    Returns:
        The maximum amount of money the robber can steal.
    """
    def _rob(i):
        if i < 0:
            return 0
        if i == 0:
            return nums[0]
        # Option 1: Rob the current house (i) and skip the previous (i-1)
        rob_i = nums[i] + _rob(i - 2)
        # Option 2: Skip the current house (i) and consider the previous (i-1)
        skip_i = _rob(i - 1)
        return max(rob_i, skip_i)

    return _rob(len(nums) - 1)

def rob_memoization(nums):
    """
    Memoization (top-down dynamic programming) solution to the House Robber problem.

    This approach improves upon the recursive solution by storing the results of
    subproblems in a memo (dictionary).  This prevents redundant calculations.

    Args:
        nums: A list of integers representing the amount of money in each house.

    Returns:
        The maximum amount of money the robber can steal.
    """
    memo = {}  # Use a dictionary for memoization

    def _rob(i):
        if i < 0:
            return 0
        if i == 0:
            return nums[0]
        if i in memo:  # Check if the result is already memoized
            return memo[i]
        rob_i = nums[i] + _rob(i - 2)
        skip_i = _rob(i - 1)
        memo[i] = max(rob_i, skip_i)  # Store the result in the memo
        return memo[i]

    return _rob(len(nums) - 1)


def rob_tabulation(nums):
    """
    Tabulation (bottom-up dynamic programming) solution to the House Robber problem.

    This approach iteratively builds a table (dp array) of solutions to subproblems,
    starting from the base cases and working towards the final solution.

    Args:
        nums: A list of integers representing the amount of money in each house.

    Returns:
        The maximum amount of money the robber can steal.
    """
    n = len(nums)
    if n == 0:
        return 0
    if n == 1:
        return nums[0]

    dp = [0] * n  # dp[i] stores the max loot up to house i
    dp[0] = nums[0]
    dp[1] = max(nums[0], nums[1])  # Handle the case for the first two houses

    for i in range(2, n):
        #  Same logic as memoization, but using the dp table
        dp[i] = max(nums[i] + dp[i - 2], dp[i - 1])
    return dp[n - 1]

def rob_tabulation_optimized(nums):
    """
    Optimized tabulation solution to the House Robber problem.

    This is a space-optimized version of the tabulation approach.  Instead of
    storing the results for all subproblems, it only keeps track of the
    previous two maximum amounts, reducing the space complexity from O(n) to O(1).

    Args:
        nums: A list of integers representing the amount of money in each house.

    Returns:
        The maximum amount of money the robber can steal.
    """
    n = len(nums)
    if n == 0:
        return 0
    if n == 1:
        return nums[0]

    #  prev1 stores max loot up to i-1, prev2 stores max loot up to i-2
    prev2 = nums[0]
    prev1 = max(nums[0], nums[1])

    for i in range(2, n):
        # Calculate current max loot
        current = max(nums[i] + prev2, prev1)
        # Update prev2 and prev1 for the next iteration
        prev2 = prev1
        prev1 = current
    return prev1

def rob_iterative(nums):
    """
    Iterative solution that avoids using extra space (O(1)).

    This approach is similar to the optimized tabulation method but written in a more
    straightforward iterative style. It explicitly tracks the maximum loot obtainable
    at the previous two houses and updates them as it iterates through the houses.

    Args:
        nums (list[int]): A list of integers representing the amount of money in each house.

    Returns:
        int: The maximum amount of money the robber can steal.
    """
    n = len(nums)
    if n == 0:
        return 0
    if n == 1:
        return nums[0]

    # Initialize variables to store the maximum loot at the previous two houses.
    # `rob_prev` stores the maximum loot obtainable up to the (i-1)-th house.
    # `not_rob_prev` stores the maximum loot obtainable up to the (i-2)-th house.
    rob_prev = 0
    not_rob_prev = 0

    # Iterate through the houses.
    for i in range(n):
        # Calculate the maximum loot if we rob the current house.
        rob_current = not_rob_prev + nums[i]
        # Calculate the maximum loot if we don't rob the current house.
        not_rob_current = max(rob_prev, not_rob_prev)

        # Update `rob_prev` and `not_rob_prev` for the next iteration.
        rob_prev = rob_current
        not_rob_prev = not_rob_current

    # The maximum loot is the greater of robbing the last house or not robbing it.
    return max(rob_prev, not_rob_prev)
# Example usage:
if __name__ == "__main__":
    houses = [2, 7, 9, 3, 1]
    print("Houses:", houses)

    print("\nRecursive Solution:", rob_recursive(houses))
    print("Memoization Solution:", rob_memoization(houses))
    print("Tabulation Solution:", rob_tabulation(houses))
    print("Tabulation Optimized Solution:", rob_tabulation_optimized(houses))
    print("Iterative Solution:", rob_iterative(houses))

    houses2 = [1, 2, 3, 1]
    print("\nHouses:", houses2)
    print("Recursive Solution:", rob_recursive(houses2))
    print("Memoization Solution:", rob_memoization(houses2))
    print("Tabulation Solution:", rob_tabulation(houses2))
    print("Tabulation Optimized Solution:", rob_tabulation_optimized(houses2))
    print("Iterative Solution:", rob_iterative(houses2))

    houses3 = [2, 1]
    print("\nHouses:", houses3)
    print("Recursive Solution:", rob_recursive(houses3))
    print("Memoization Solution:", rob_memoization(houses3))
    print("Tabulation Solution:", rob_tabulation(houses3))
    print("Tabulation Optimized Solution:", rob_tabulation_optimized(houses3))
    print("Iterative Solution:", rob_iterative(houses3))

    houses4 = [1]
    print("\nHouses:", houses4)
    print("Recursive Solution:", rob_recursive(houses4))
    print("Memoization Solution:", rob_memoization(houses4))
    print("Tabulation Solution:", rob_tabulation(houses4))
    print("Tabulation Optimized Solution:", rob_tabulation_optimized(houses4))
    print("Iterative Solution:", rob_iterative(houses4))

    houses5 = []
    print("\nHouses:", houses5)
    print("Recursive Solution:", rob_recursive(houses5))
    print("Memoization Solution:", rob_memoization(houses5))
    print("Tabulation Solution:", rob_tabulation(houses5))
    print("Tabulation Optimized Solution:", rob_tabulation_optimized(houses5))
    print("Iterative Solution:", rob_iterative(houses5))

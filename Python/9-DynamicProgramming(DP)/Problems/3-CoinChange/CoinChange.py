def coin_change_recursive(coins, amount):
    """
    Recursive solution for the Coin Change problem.

    This is the most basic approach, but it's also the least efficient due to
    repeated calculations of the same subproblems.  It often leads to a stack
    overflow for larger amounts or a large number of coins.

    Args:
        coins: A list of coin denominations.
        amount: The target amount to make change for.

    Returns:
        The minimum number of coins needed to make up the amount, or -1 if it's
        not possible.
    """
    if amount == 0:
        return 0
    if amount < 0:
        return -1

    min_coins = float('inf')  # Initialize with a large value
    for coin in coins:
        res = coin_change_recursive(coins, amount - coin)
        if res != -1:
            min_coins = min(min_coins, 1 + res)  # 1 + res:  1 coin used + result of subproblem

    return min_coins if min_coins != float('inf') else -1

def coin_change_memoization(coins, amount):
    """
    Memoization (Top-Down Dynamic Programming) solution for the Coin Change problem.

    This approach improves upon the recursive solution by storing the results of
    solved subproblems in a memo (dictionary).  Before computing the solution to
    a subproblem, it checks if the solution is already stored.  This avoids
    redundant calculations.

    Args:
        coins: A list of coin denominations.
        amount: The target amount to make change for.

    Returns:
        The minimum number of coins needed to make up the amount, or -1 if it's
        not possible.
    """
    memo = {}  # Use a dictionary to store results of subproblems

    def _coin_change_memo(amount):
        if amount == 0:
            return 0
        if amount < 0:
            return -1
        if amount in memo:
            return memo[amount]  # Return the stored result if it exists

        min_coins = float('inf')
        for coin in coins:
            res = _coin_change_memo(amount - coin)
            if res != -1:
                min_coins = min(min_coins, 1 + res)
        memo[amount] = min_coins if min_coins != float('inf') else -1  # Store the result
        return memo[amount]

    return _coin_change_memo(amount)


def coin_change_tabulation(coins, amount):
    """
    Tabulation (Bottom-Up Dynamic Programming) solution for the Coin Change problem.

    This approach builds a table (dp array) of solutions to subproblems, starting
    from the base case (amount 0) and iteratively computing solutions for larger
    amounts.  It avoids recursion and directly accesses previously computed
    values in the table.

    Args:
        coins: A list of coin denominations.
        amount: The target amount to make change for.

    Returns:
        The minimum number of coins needed to make up the amount, or -1 if it's
        not possible.
    """
    dp = [float('inf')] * (amount + 1)  # dp[i] stores min coins for amount i
    dp[0] = 0  # Base case: 0 coins needed for amount 0

    for i in range(1, amount + 1):  # Iterate through all amounts from 1 to amount
        for coin in coins:
            if i - coin >= 0:
                dp[i] = min(dp[i], 1 + dp[i - coin])  # Transition function

    return dp[amount] if dp[amount] != float('inf') else -1

def coin_change_optimized(coins, amount):
    """
    Optimized Tabulation (Bottom-Up DP) for Coin Change.

    This is a space-optimized version of the tabulation method.  In the standard
    tabulation method, we create a DP table of size (amount + 1).  However, we
    only need the previous subproblem results to compute the current result.
    This optimized version still uses tabulation, but it does so in a way that
    reduces the space complexity.  However, for the coin change problem, the
    standard tabulation method is already quite efficient, and further
    optimization might not be necessary for most practical cases.
    Args:
        coins: List of coin denominations.
        amount: Target amount.

    Returns:
        Minimum number of coins, or -1 if not possible.
    """
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    for i in range(1, amount + 1):
        for coin in coins:
            if i - coin >= 0:
                dp[i] = min(dp[i], 1 + dp[i - coin])
    return dp[amount] if dp[amount] != float('inf') else -1

def coin_change_iterative_dp(coins, amount):
    """
    Iterative Dynamic Programming solution for Coin Change.

    This is another iterative approach, similar to tabulation, but written slightly differently.
    It aims to be very clear and explicit in its iteration.  Like tabulation, it builds
    a table of solutions to subproblems.

    Args:
        coins: A list of coin denominations.
        amount: The target amount.

    Returns:
        The minimum number of coins needed, or -1 if not possible.
    """
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    for current_amount in range(1, amount + 1):
        for coin in coins:
            if current_amount - coin >= 0:
                remaining_amount = current_amount - coin
                dp[current_amount] = min(dp[current_amount], 1 + dp[remaining_amount])

    return dp[amount] if dp[amount] != float('inf') else -1
# Example usage:
coins = [1, 2, 5]
amount = 11

print("Recursive:", coin_change_recursive(coins, amount))
print("Memoization:", coin_change_memoization(coins, amount))
print("Tabulation:", coin_change_tabulation(coins, amount))
print("Optimized Tabulation:", coin_change_optimized(coins, amount))
print("Iterative DP:", coin_change_iterative_dp(coins, amount))

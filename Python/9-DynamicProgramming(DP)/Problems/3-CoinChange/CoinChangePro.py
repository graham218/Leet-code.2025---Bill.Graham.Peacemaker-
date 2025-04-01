import sys

def coin_change_dp_approaches(coins, amount):
    """
    Calculates the minimum number of coins needed to make up a given amount,
    using dynamic programming.  Demonstrates several approaches, each with
    real-world application nuances in the comments.

    Args:
        coins: A list of coin denominations (integers).
        amount: The target amount (integer).

    Returns:
        The minimum number of coins needed, or -1 if the amount cannot be made up.
    """

    if amount < 0:
        return -1
    if amount == 0:
        return 0

    # 1. Top-Down (Memoization) - Recursive with Caching
    def top_down(amount, memo):
        if amount == 0:
            return 0
        if amount < 0:
            return float('inf')  # Represents an impossible solution
        if amount in memo:
            return memo[amount]

        min_coins = float('inf')
        for coin in coins:
            min_coins = min(min_coins, 1 + top_down(amount - coin, memo))
        memo[amount] = min_coins
        return min_coins

    memo = {}
    result_top_down = top_down(amount, memo)
    print(f"1. Top-Down (Memoization): {result_top_down}, Memo: {memo}")
    # Real-world: Good for smaller amounts, avoids redundant calculations.  Use in scenarios
    # where the amount is not excessively large, like optimizing cash register
    # change dispensing for smaller transactions.  Memoization table can grow,
    # so it might not be suitable for very large amounts due to memory constraints.

    # 2. Bottom-Up (Tabulation) - Iterative
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0  # Base case: 0 coins needed for amount 0

    for i in range(1, amount + 1):
        for coin in coins:
            if i - coin >= 0:
                dp[i] = min(dp[i], 1 + dp[i - coin])
    result_bottom_up = dp[amount]
    print(f"2. Bottom-Up (Tabulation): {result_bottom_up}, DP Table: {dp}")
    # Real-world: More efficient than top-down for larger amounts.  Suitable for
    # financial systems calculating optimal ways to combine different
    # denominations (e.g., in ATMs).  The dp table stores intermediate results,
    # allowing for efficient lookup and preventing recalculations.

    # 3. Bottom-Up with Coin Tracking
    dp_track = [float('inf')] * (amount + 1)
    dp_track[0] = 0
    last_coin = [0] * (amount + 1) # Keep track of the last coin used

    for i in range(1, amount + 1):
        for coin in coins:
            if i - coin >= 0:
                if dp_track[i - coin] + 1 < dp_track[i]:
                    dp_track[i] = dp_track[i - coin] + 1
                    last_coin[i] = coin

    result_with_tracking = dp_track[amount]

    # Reconstruct the coins used.
    coins_used = []
    if result_with_tracking != float('inf'):
        curr_amount = amount
        while curr_amount > 0:
            coin = last_coin[curr_amount]
            coins_used.append(coin)
            curr_amount -= coin
    print(f"3. Bottom-Up with Coin Tracking: {result_with_tracking}, Coins Used: {coins_used}, DP Table: {dp_track}")
    # Real-world: Essential when you need to know *which* coins were used, not just the count.
    # Useful in point-of-sale systems to provide change breakdown to the customer
    # (e.g., "Here's one dollar, two quarters, and a nickel").

    # 4. Optimized Bottom-Up (for limited coin counts) - Not always applicable
    # If we had a maximum number of each coin available, we could adapt the bottom-up approach.
    # This is NOT the standard coin change, but a variation.  Assume we have unlimited for this example.
    # Real-world: Inventory management systems, where you want to minimize the number of
    # physical coins/bills used, given limited stock.  Not a general solution.
    result_optimized = result_bottom_up # same as bottom up in this case since we have unlimited coins.
    print(f"4. Optimized Bottom-Up (Unlimited Coins): {result_optimized}")

    # 5. Greedy Approach (Only works for specific coin sets)
    #  The greedy approach is to use the largest possible denomination at each step.
    #  It's simpler but doesn't guarantee the optimal solution for all coin sets.
    #  For US currency (1, 5, 10, 25), it happens to work, but not for all.
    def greedy_coin_change(coins, amount):
        coins.sort(reverse=True)  # Sort coins in descending order
        num_coins = 0
        remaining_amount = amount
        used_coins_greedy = []

        for coin in coins:
            while remaining_amount >= coin:
                remaining_amount -= coin
                num_coins += 1
                used_coins_greedy.append(coin)
        if remaining_amount == 0:
            return num_coins, used_coins_greedy
        else:
            return -1, []  # Indicate that the amount can't be made up

    num_coins_greedy, used_coins_greedy = greedy_coin_change(coins, amount)
    print(f"5. Greedy Approach: {num_coins_greedy}, Coins Used: {used_coins_greedy}")
    # Real-world: Fastest approach (if it works).  Used in very high-speed transaction
    # scenarios where optimality is less critical than speed (e.g., some vending machines,
    # very simple point-of-sale systems).  However, its applicability is limited.

    # 6.  Using a Library (Not strictly DP, but practical)
    # Python doesn't have a built-in library for coin change optimization.
    # For more complex scenarios (e.g., constraints on coin counts, different
    # optimization criteria), you might need to use a third-party library
    # or a more specialized optimization library (like those for linear programming).
    # This is a placeholder to indicate where you might integrate such a library.
    # Example (Conceptual - requires external library like a linear programming solver):
    # from some_optimization_library import solve_coin_change  # Hypothetical
    # result_library = solve_coin_change(coins, amount, constraints)
    result_library = "N/A - External library needed"
    print(f"6. Using a Library: {result_library}")
    # Real-world: For very complex coin change problems (e.g., minimizing number
    # of *unique* coins, or with limits on the number of each coin), a dedicated
    # optimization library is often the best approach.  This is common in
    # sophisticated financial modeling or supply chain optimization.

    # Return the result from the bottom-up approach, which is generally preferred.
    return result_bottom_up

if __name__ == "__main__":
    # Example usage:
    coins = [1, 5, 10, 25]  # US coin denominations
    amount = 49
    min_coins = coin_change_dp_approaches(coins, amount)
    print(f"Minimum coins needed for {amount}: {min_coins}")

    coins2 = [2]
    amount2 = 3
    min_coins2 = coin_change_dp_approaches(coins2, amount2)
    print(f"Minimum coins needed for {amount2}: {min_coins2}")  # Output: -1

    coins3 = [1, 2, 5]
    amount3 = 11
    min_coins3 = coin_change_dp_approaches(coins3, amount3)
    print(f"Minimum coins needed for {amount3}: {min_coins3}")  # Output: 3

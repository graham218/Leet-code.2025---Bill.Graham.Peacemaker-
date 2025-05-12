import java.util.Arrays;

public class CoinChange {

    /**
     * **1. Recursive Approach**
     *
     * This is the most basic approach, where we try all possible combinations of coins
     * to reach the target amount.  It has exponential time complexity and often leads to
     * a stack overflow for larger inputs due to excessive recursive calls.  It's inefficient
     * because it recomputes the same subproblems repeatedly.
     *
     * @param coins The array of coin denominations.
     * @param amount The target amount.
     * @return The minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeRecursive(int[] coins, int amount) {
        if (amount == 0) {
            return 0; // Base case: 0 amount needs 0 coins
        }
        if (amount < 0) {
            return -1; // Base case: Negative amount is not possible
        }

        int minCoins = Integer.MAX_VALUE;
        for (int coin : coins) {
            int subResult = coinChangeRecursive(coins, amount - coin);
            if (subResult != -1) {
                minCoins = Math.min(minCoins, subResult + 1); // Add 1 for the current coin
            }
        }
        return (minCoins == Integer.MAX_VALUE) ? -1 : minCoins;
    }

    /**
     * **2. Memoization (Top-Down DP)**
     *
     * This approach improves upon the recursive solution by storing the results of
     * subproblems in a table (memo) to avoid redundant computations.  It's still
     * recursive but much more efficient.  The time complexity is reduced to O(amount * n),
     * where n is the number of coins.
     *
     * @param coins The array of coin denominations.
     * @param amount The target amount.
     * @param memo   A memoization table to store results of subproblems.
     * @return The minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeMemoization(int[] coins, int amount, int[] memo) {
        if (amount == 0) {
            return 0;
        }
        if (amount < 0) {
            return -1;
        }
        if (memo[amount] != 0) {
            return memo[amount]; // Return the stored result if it exists
        }

        int minCoins = Integer.MAX_VALUE;
        for (int coin : coins) {
            int subResult = coinChangeMemoization(coins, amount - coin, memo);
            if (subResult != -1) {
                minCoins = Math.min(minCoins, subResult + 1);
            }
        }
        memo[amount] = (minCoins == Integer.MAX_VALUE) ? -1 : minCoins; // Store the result
        return memo[amount];
    }

    /**
     * **3. Tabulation (Bottom-Up DP)**
     *
     * This is an iterative approach where we build up a table of solutions to subproblems,
     * starting from the base case and working our way up to the target amount.  It has the
     * same time complexity as memoization (O(amount * n)) but is often more efficient in
     * practice because it avoids the overhead of recursion.
     *
     * @param coins The array of coin denominations.
     * @param amount The target amount.
     * @return The minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeTabulation(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1); // Initialize with a value greater than the maximum possible answer
        dp[0] = 0; // Base case: 0 amount needs 0 coins

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }

    /**
     * **4. Tabulation with Coin Tracking**
     *
     * This is a variation of the tabulation method that also keeps track of which coins
     * were used to achieve the minimum number.  It uses an additional array, `usedCoins`,
     * to store the last coin used for each amount.
     *
     * @param coins The array of coin denominations.
     * @param amount The target amount.
     * @return The minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeTabulationWithTracking(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        int[] usedCoins = new int[amount + 1]; // Keep track of the last coin used
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0 && dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    usedCoins[i] = coin; // Store the coin used to reach this amount
                }
            }
        }

        if (dp[amount] > amount) {
            return -1;
        } else {
            // Print the coins used (optional)
            System.out.print("Coins used: ");
            int currentAmount = amount;
            while (currentAmount > 0) {
                System.out.print(usedCoins[currentAmount] + " ");
                currentAmount -= usedCoins[currentAmount];
            }
            System.out.println();
            return dp[amount];
        }
    }

    /**
     * **5. Optimized Tabulation (Space Optimized)**
     *
     * This approach further optimizes the tabulation method by reducing the space complexity.
     * In the standard tabulation, the `dp` array stores the minimum coins needed for each
     * amount from 0 to the target amount.  However, to calculate `dp[i]`, we only need
     * values from `dp[i - coin]` for each coin. We don't need to keep the entire `dp` array.
     * This optimized version is not possible for this problem.
     *
     * @param coins The array of coin denominations.
     * @param amount The target amount.
     * @return The minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeOptimized(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        int[] coins = {1, 2, 5};
        int amount = 11;

        System.out.println("Coin Change Problem: Amount = " + amount);
        System.out.println("Coins: " + Arrays.toString(coins));
        System.out.println();

        // 1. Recursive Approach
        long startTimeRecursive = System.nanoTime();
        int resultRecursive = coinChangeRecursive(coins, amount);
        long endTimeRecursive = System.nanoTime();
        System.out.println("1. Recursive Approach: " + resultRecursive + " (Time: " + (endTimeRecursive - startTimeRecursive) + " ns)");

        // 2. Memoization Approach
        long startTimeMemoization = System.nanoTime();
        int[] memo = new int[amount + 1];
        int resultMemoization = coinChangeMemoization(coins, amount, memo);
        long endTimeMemoization = System.nanoTime();
        System.out.println("2. Memoization Approach: " + resultMemoization + " (Time: " + (endTimeMemoization - startTimeMemoization) + " ns)");

        // 3. Tabulation Approach
        long startTimeTabulation = System.nanoTime();
        int resultTabulation = coinChangeTabulation(coins, amount);
        long endTimeTabulation = System.nanoTime();
        System.out.println("3. Tabulation Approach: " + resultTabulation + " (Time: " + (endTimeTabulation - startTimeTabulation) + " ns)");

        // 4. Tabulation with Coin Tracking
        long startTimeTabulationWithTracking = System.nanoTime();
        int resultTabulationWithTracking = coinChangeTabulationWithTracking(coins, amount);
        long endTimeTabulationWithTracking = System.nanoTime();
        System.out.println("4. Tabulation with Coin Tracking: " + resultTabulationWithTracking + " (Time: " + (endTimeTabulationWithTracking - startTimeTabulationWithTracking) + " ns)");

        // 5. Optimized Tabulation Approach
        long startTimeOptimized = System.nanoTime();
        int resultOptimized = coinChangeOptimized(coins, amount);
        long endTimeOptimized = System.nanoTime();
        System.out.println("5. Optimized Tabulation Approach: " + resultOptimized + " (Time: " + (endTimeOptimized - startTimeOptimized) + " ns)");
    }
}


import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class CoinChange {

    /**
     * 1. Top-Down (Memoization) Approach
     *
     * This approach uses recursion with memoization to avoid redundant calculations.
     * It starts with the target amount and recursively tries to find the minimum number of coins
     * needed for the remaining amount after picking a coin.
     *
     * Real-world application:
     * -   Implementing a point redemption system in a loyalty program.  You want to find the fewest
     * number of reward points (coins) to give back to a customer for a specific discount amount.
     *
     * @param coins   Array of coin denominations.
     * @param amount  Target amount.
     * @param memo    Memoization table to store results of subproblems.
     * @return        Minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeTopDown(int[] coins, int amount, int[] memo) {
        if (amount == 0) {
            return 0; // Base case: no amount, no coins needed
        }
        if (amount < 0) {
            return -1; // Base case: amount is negative, not possible
        }
        if (memo[amount] != 0) {
            return memo[amount]; // Return memoized result if available
        }

        int minCoins = Integer.MAX_VALUE;
        for (int coin : coins) {
            int subResult = coinChangeTopDown(coins, amount - coin, memo);
            if (subResult != -1) {
                minCoins = Math.min(minCoins, subResult + 1); //+1 because we used one coin
            }
        }
        memo[amount] = (minCoins == Integer.MAX_VALUE) ? -1 : minCoins; //store the result
        return memo[amount];
    }

    /**
     * 2. Bottom-Up (Tabulation) Approach
     *
     * This approach builds a table of solutions to subproblems, starting from the base case (amount 0)
     * and iteratively computing the solution for larger amounts.
     *
     * Real-world application:
     * -   Calculating the minimum number of currency notes/coins required for cash withdrawal
     * from an ATM.
     *
     * @param coins   Array of coin denominations.
     * @param amount  Target amount.
     * @return        Minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeBottomUp(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1); // Initialize DP table with a value greater than the maximum possible answer.
        dp[0] = 0; // Base case: 0 coins needed for amount 0

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
     * 3. Bottom-Up with Coin Tracking
     *
     * This approach is similar to the bottom-up approach, but it also keeps track of the last coin used
     * to achieve the minimum number of coins for each amount.  This allows for reconstructing the
     * actual combination of coins used.
     *
     * Real-world application:
     * -  Generating a detailed breakdown of how change is given in a vending machine,
     * showing the exact coins dispensed.
     *
     * @param coins   Array of coin denominations.
     * @param amount  Target amount.
     * @return        An array where the first element is the minimum number of coins,
     * and the subsequent elements are the coins used.  Returns null if not possible.
     */
    public static int[] coinChangeBottomUpWithTracking(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        int[] lastCoin = new int[amount + 1]; // Keep track of the last coin used for each amount
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;
        lastCoin[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    if (dp[i - coin] + 1 < dp[i]) {
                        dp[i] = dp[i - coin] + 1;
                        lastCoin[i] = coin; // Store the coin used
                    }
                }
            }
        }

        if (dp[amount] > amount) {
            return null; // No solution
        }

        // Reconstruct the coins used
        int[] result = new int[dp[amount] + 1]; // Array to store the result, +1 for the count
        result[0] = dp[amount]; // First element is the total coin count
        int currentAmount = amount;
        for (int i = dp[amount]; i > 0; i--) {
            result[i] = lastCoin[currentAmount]; // Get the last coin used
            currentAmount -= lastCoin[currentAmount];
        }
        return result;
    }

    /**
     * 4. Optimized Bottom-Up (Iterative with Single Array)
     *
     * This is a space-optimized version of the bottom-up approach.  It uses only a single array
     * to store the minimum number of coins for each amount, iterating through the coins
     * and updating the array in place.
     *
     * Real-world application:
     * -   Embedded systems with limited memory, such as a simple electronic cash register.
     * This approach minimizes memory usage.
     *
     * @param coins   Array of coin denominations.
     * @param amount  Target amount.
     * @return        Minimum number of coins needed, or -1 if not possible.
     */
    public static int coinChangeOptimized(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;

        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) { // Iterate from coin value to amount
                dp[i] = Math.min(dp[i], dp[i - coin] + 1);
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }

    /**
     * 5.  Memoization with Coin Counts (for limited coin scenarios)
     *
     * This approach handles scenarios where there's a limited number of each coin available.
     * It uses memoization, but also tracks the count of each coin used to ensure we don't
     * exceed the available quantities.
     *
     * Real-world application:
     * -  Inventory management in a small retail store, where the cashier has a limited
     * number of each denomination in the cash drawer.
     *
     * @param coins      Array of coin denominations.
     * @param coinCounts Array of the number of available coins for each denomination.
     * @param amount     Target amount.
     * @param memo       Memoization table.  Key is the amount, value is a map of coin counts.
     * @return           A map representing the minimum number of coins needed for each denomination,
     * or null if not possible.
     */
    public static Map<Integer, Integer> coinChangeWithLimitedCoins(int[] coins, int[] coinCounts, int amount, Map<Integer, Map<Integer, Integer>> memo) {
        if (amount == 0) {
            return new HashMap<>(); // Base case: no amount, no coins
        }
        if (amount < 0) {
            return null; // Base case: amount is negative, not possible
        }

        if (memo.containsKey(amount)) {
            return memo.get(amount); // Return memoized result
        }

        Map<Integer, Integer> minCoinMap = null;
        for (int i = 0; i < coins.length; i++) {
            int coin = coins[i];
            if (coinCounts[i] > 0) { // Check if we have this coin available
                int[] newCoinCounts = coinCounts.clone(); // IMPORTANT:  Don't modify original!
                newCoinCounts[i]--; // Use one coin
                Map<Integer, Integer> subResult = coinChangeWithLimitedCoins(coins, newCoinCounts, amount - coin, memo);
                if (subResult != null) {
                    // Add the current coin to the subResult
                    subResult.put(coin, subResult.getOrDefault(coin, 0) + 1);
                    //check if this result is better than the current minimum
                    if (minCoinMap == null || subResult.size() < minCoinMap.size() ||
                            (subResult.size() == minCoinMap.size() && getCoinCount(subResult) < getCoinCount(minCoinMap))) {
                        minCoinMap = subResult;
                    }
                }
            }
        }
        memo.put(amount, minCoinMap);
        return minCoinMap;
    }

    // Helper function to get the total number of coins in a map
    private static int getCoinCount(Map<Integer, Integer> coinMap) {
        int count = 0;
        for (int value : coinMap.values()) {
            count += value;
        }
        return count;
    }

    public static void main(String[] args) {
        int[] coins = {1, 2, 5};
        int amount = 11;

        // 1. Top-Down (Memoization)
        int[] memo = new int[amount + 1];
        int result1 = coinChangeTopDown(coins, amount, memo);
        System.out.println("Top-Down: Minimum coins needed for " + amount + ": " + result1);

        // 2. Bottom-Up (Tabulation)
        int result2 = coinChangeBottomUp(coins, amount);
        System.out.println("Bottom-Up: Minimum coins needed for " + amount + ": " + result2);

        // 3. Bottom-Up with Coin Tracking
        int[] result3 = coinChangeBottomUpWithTracking(coins, amount);
        if (result3 != null) {
            System.out.print("Bottom-Up with Tracking: Minimum coins needed for " + amount + ": " + result3[0] + ", Coins: ");
            for (int i = 1; i < result3.length; i++) {
                System.out.print(result3[i] + " ");
            }
            System.out.println();
        } else {
            System.out.println("Bottom-Up with Tracking: No solution for " + amount);
        }

        // 4. Optimized Bottom-Up
        int result4 = coinChangeOptimized(coins, amount);
        System.out.println("Optimized Bottom-Up: Minimum coins needed for " + amount + ": " + result4);

        // 5. Memoization with Coin Counts
        int[] coinCounts = {3, 2, 3}; // Example: 3 ones, 2 twos, 3 fives
        Map<Integer, Map<Integer, Integer>> memo5 = new HashMap<>();
        Map<Integer, Integer> result5 = coinChangeWithLimitedCoins(coins, coinCounts, amount, memo5);
        if (result5 != null) {
            System.out.println("With Limited Coins: Coins used for " + amount + ": " + result5);
        } else {
            System.out.println("With Limited Coins: No solution for " + amount);
        }
    }
}


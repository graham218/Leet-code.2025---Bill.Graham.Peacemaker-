import java.util.Arrays;

public class BestTimeToBuySellStock {

    /**
     * Approach 1: Brute Force
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(1)
     * -   Description:
     * This is the most straightforward approach.  We iterate through each price
     * in the array and compare it with every price that comes after it to find
     * the maximum possible profit.  This involves nested loops.  It's simple
     * to understand but inefficient for large input arrays.
     * This approach directly calculates the profit for every possible pair
     * of buy and sell days.
     */
    public static int maxProfitBruteForce(int[] prices) {
        int maxProfit = 0;
        for (int i = 0; i < prices.length - 1; i++) {
            for (int j = i + 1; j < prices.length; j++) {
                int profit = prices[j] - prices[i];
                if (profit > maxProfit) {
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }

    /**
     * Approach 2: Optimized Brute Force (Slight Improvement)
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(1)
     * -   Description:
     * This is a slight optimization over the basic brute force.  It avoids
     * unnecessary comparisons by breaking the inner loop if a profit less than
     * or equal to zero is encountered. However, the time complexity remains
     * quadratic.
     */
    public static int maxProfitOptimizedBruteForce(int[] prices) {
        int maxProfit = 0;
        for (int i = 0; i < prices.length - 1; i++) {
            for (int j = i + 1; j < prices.length; j++) {
                int profit = prices[j] - prices[i];
                if (profit > maxProfit) {
                    maxProfit = profit;
                } else if (profit <= 0) { // Optimization: No need to continue if profit is not positive
                    //  This optimization does NOT change the time complexity,
                    //  it's still O(n^2), but it can be slightly faster in practice.
                    continue; // continue to the next iteration of the inner loop
                }
            }
        }
        return maxProfit;
    }

    /**
     * Approach 3: Single Pass (Greedy Approach)
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(1)
     * -   Description:
     * This is the most efficient and recommended approach.  It uses a single
     * pass through the price array.  We keep track of the minimum price
     * encountered so far and calculate the profit if we were to sell at the
     * current price.  We then update the maximum profit if the current profit
     * is greater.  This avoids redundant calculations and is very efficient.
     * This is a classic example of a greedy algorithm.
     */
    public static int maxProfitSinglePass(int[] prices) {
        int minPrice = Integer.MAX_VALUE;
        int maxProfit = 0;
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } else {
                int profit = price - minPrice;
                if (profit > maxProfit) {
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }

    /**
     * Approach 4: Dynamic Programming (DP)
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Description:
     * This approach uses dynamic programming. We create an array `dp` where
     * `dp[i]` stores the maximum profit that can be obtained by selling on day `i`.
     * The base case is `dp[0] = 0`.  For each subsequent day, we have two choices:
     * either sell on that day (and calculate the profit) or don't sell. We
     * take the maximum of these two.  While this approach has linear time
     * complexity, it uses extra space for the `dp` array and is generally
     * less efficient than the single-pass greedy approach for this specific problem.
     */
    public static int maxProfitDP(int[] prices) {
        if (prices.length == 0) {
            return 0;
        }
        int[] dp = new int[prices.length];
        dp[0] = 0; // Base case: No profit on the first day
        int minPrice = prices[0];

        for (int i = 1; i < prices.length; i++) {
            minPrice = Math.min(minPrice, prices[i]); // Track the minimum price
            dp[i] = Math.max(dp[i - 1], prices[i] - minPrice); // Max of not selling or selling today
        }
        return dp[prices.length - 1];
    }

    /**
     * Approach 5:  Simplified DP (Space Optimized)
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(1)
     * -   Description:
     * This is a space-optimized version of the dynamic programming approach.
     * Instead of using a full `dp` array, we only keep track of the maximum
     * profit seen so far.  This reduces the space complexity to O(1) while
     * maintaining the O(n) time complexity.  It's similar in concept to the
     * single-pass greedy approach but expressed using DP principles.
     */
    public static int maxProfitDPSimplified(int[] prices) {
        if (prices.length == 0) {
            return 0;
        }
        int maxProfit = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.length; i++) {
            minPrice = Math.min(minPrice, prices[i]);
            maxProfit = Math.max(maxProfit, prices[i] - minPrice);
        }
        return maxProfit;
    }

    public static void main(String[] args) {
        int[] prices = {7, 1, 5, 3, 6, 4};
        // int[] prices = {7, 6, 4, 3, 1}; // Example with decreasing prices
        // int[] prices = {2, 1, 2, 1, 0, 0, 1}; // Example from submission
        // int[] prices = {2,4,1};

        System.out.println("Prices: " + Arrays.toString(prices));
        System.out.println("Max Profit (Brute Force): " + maxProfitBruteForce(prices));
        System.out.println("Max Profit (Optimized Brute Force): " + maxProfitOptimizedBruteForce(prices));
        System.out.println("Max Profit (Single Pass): " + maxProfitSinglePass(prices));
        System.out.println("Max Profit (DP): " + maxProfitDP(prices));
        System.out.println("Max Profit (DP Simplified): " + maxProfitDPSimplified(prices));
    }
}


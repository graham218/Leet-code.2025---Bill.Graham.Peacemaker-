import java.util.*;
import java.lang.*;

class BestTimeToBuySellStock {

    // Approach 1: Brute Force
    // Description: Try every possible pair of buy and sell days and calculate the profit.
    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    public int maxProfitBruteForce(int[] prices) {
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

    // Approach 2: Optimized Brute Force
    // Description: Slightly optimized version of brute force, avoiding redundant calculations.
    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    public int maxProfitOptimizedBruteForce(int[] prices) {
        int maxProfit = 0;
        for (int i = 0; i < prices.length; i++) {
            int buyPrice = prices[i];
            for (int j = i + 1; j < prices.length; j++) {
                int sellPrice = prices[j];
                if (sellPrice > buyPrice) {
                    maxProfit = Math.max(maxProfit, sellPrice - buyPrice);
                }
            }
        }
        return maxProfit;
    }

    // Approach 3: Single Pass (Greedy)
    // Description: Keep track of the minimum price seen so far and calculate the maximum profit.
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public int maxProfitSinglePass(int[] prices) {
        int minPrice = Integer.MAX_VALUE;
        int maxProfit = 0;
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } else if (price - minPrice > maxProfit) {
                maxProfit = price - minPrice;
            }
        }
        return maxProfit;
    }

    // Approach 4: Dynamic Programming
    // Description: Use DP to store the maximum profit up to each day.
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public int maxProfitDP(int[] prices) {
        if (prices.length == 0) return 0;

        int[] dp = new int[prices.length];
        int minPrice = prices[0];
        dp[0] = 0;

        for (int i = 1; i < prices.length; i++) {
            minPrice = Math.min(minPrice, prices[i]);
            dp[i] = Math.max(dp[i - 1], prices[i] - minPrice);
        }
        return dp[prices.length - 1];
    }

    // Approach 5:  Optimized Single Pass (Most Efficient)
    // Description:  A slightly more concise version of the single pass approach.
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public int maxProfitOptimized(int[] prices) {
        int minPrice = Integer.MAX_VALUE;
        int maxProfit = 0;
        for (int price : prices) {
            minPrice = Math.min(minPrice, price);
            maxProfit = Math.max(maxProfit, price - minPrice);
        }
        return maxProfit;
    }

    public static void main(String[] args) {
        BestTimeToBuySellStock solution = new BestTimeToBuySellStock();
        int[] prices = {7, 1, 5, 3, 6, 4};

        // Brute Force
        long startTime = System.nanoTime();
        int maxProfit1 = solution.maxProfitBruteForce(prices);
        long endTime = System.nanoTime();
        System.out.println("Max Profit (Brute Force): " + maxProfit1 + ", Time: " + (endTime - startTime) + " ns");

        // Optimized Brute Force
        startTime = System.nanoTime();
        int maxProfit2 = solution.maxProfitOptimizedBruteForce(prices);
        endTime = System.nanoTime();
        System.out.println("Max Profit (Optimized Brute Force): " + maxProfit2 + ", Time: " + (endTime - startTime) + " ns");

        // Single Pass
        startTime = System.nanoTime();
        int maxProfit3 = solution.maxProfitSinglePass(prices);
        endTime = System.nanoTime();
        System.out.println("Max Profit (Single Pass): " + maxProfit3 + ", Time: " + (endTime - startTime) + " ns");

        // Dynamic Programming
        startTime = System.nanoTime();
        int maxProfit4 = solution.maxProfitDP(prices);
        endTime = System.nanoTime();
        System.out.println("Max Profit (Dynamic Programming): " + maxProfit4 + ", Time: " + (endTime - startTime) + " ns");

        // Optimized Single Pass
        startTime = System.nanoTime();
        int maxProfit5 = solution.maxProfitOptimized(prices);
        endTime = System.nanoTime();
        System.out.println("Max Profit (Optimized Single Pass): " + maxProfit5 + ", Time: " + (endTime - startTime) + " ns");
    }
}

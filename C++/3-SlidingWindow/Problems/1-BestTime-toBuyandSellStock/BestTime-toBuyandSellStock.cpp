/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done, i.e., max profit = 0.
*/

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function maxProfit1(prices) {
    let maxProfit = 0;
    for (let i = 0; i < prices.length; i++) {
        for (let j = i + 1; j < prices.length; j++) {
            const profit = prices[j] - prices[i];
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }
    return maxProfit;
}

/**
 * Approach 2: Optimized Brute Force (Slightly better)
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function maxProfit2(prices) {
    let maxProfit = 0;
    for (let i = 0; i < prices.length - 1; i++) {
        for (let j = i + 1; j < prices.length; j++) {
            if (prices[j] > prices[i]) { // Only calculate profit if selling price is higher
                maxProfit = Math.max(maxProfit, prices[j] - prices[i]);
            }
        }
    }
    return maxProfit;
}



/**
 * Approach 3: Single Pass
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function maxProfit3(prices) {
    let minPrice = prices[0];
    let maxProfit = 0;
    for (let i = 1; i < prices.length; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else if (prices[i] - minPrice > maxProfit) {
            maxProfit = prices[i] - minPrice;
        }
    }
    return maxProfit;
}

/**
 * Approach 4:  Kadane's Algorithm (Variation)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function maxProfit4(prices) {
    let currentProfit = 0;
    let maxProfit = 0;
    for (let i = 1; i < prices.length; i++) {
        const potentialProfit = prices[i] - prices[i - 1];
        currentProfit = Math.max(0, currentProfit + potentialProfit); // 핵심
        maxProfit = Math.max(maxProfit, currentProfit);
    }
    return maxProfit;
}

/**
 * Approach 5:  Dynamic Programming
 * Time Complexity: O(n)
 * Space Complexity: O(1) - can be optimized to O(1)
 */
function maxProfit5(prices) {
    if (!prices || prices.length <= 1) return 0;

    let minPrice = prices[0];
    let maxProfit = 0;

    for (let i = 1; i < prices.length; i++) {
        // Calculate the potential profit if we sell today
        const potentialProfit = prices[i] - minPrice;
        // Update maxProfit if the potential profit is greater
        maxProfit = Math.max(maxProfit, potentialProfit);
        // Update minPrice to the lowest price seen so far
        minPrice = Math.min(minPrice, prices[i]);
    }

    return maxProfit;
}



// Example usage:
const prices1 = [7, 1, 5, 3, 6, 4];
const prices2 = [7, 6, 4, 3, 1];

console.log("Example 1:");
console.log("Approach 1 (Brute Force):", maxProfit1(prices1));
console.log("Approach 2 (Optimized Brute Force):", maxProfit2(prices1));
console.log("Approach 3 (Single Pass):", maxProfit3(prices1));
console.log("Approach 4 (Kadane's Variation):", maxProfit4(prices1));
console.log("Approach 5 (Dynamic Programming):", maxProfit5(prices1));


console.log("\nExample 2:");
console.log("Approach 1 (Brute Force):", maxProfit1(prices2));
console.log("Approach 2 (Optimized Brute Force):", maxProfit2(prices2));
console.log("Approach 3 (Single Pass):", maxProfit3(prices2));
console.log("Approach 4 (Kadane's Variation):", maxProfit4(prices2));
console.log("Approach 5 (Dynamic Programming):", maxProfit5(prices2));

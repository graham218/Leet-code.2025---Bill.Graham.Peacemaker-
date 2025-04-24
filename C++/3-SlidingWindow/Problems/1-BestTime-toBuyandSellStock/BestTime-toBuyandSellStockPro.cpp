/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 *
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 * Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
 *
 * Example 2:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transactions are done and the max profit = 0.
 */

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * This approach iterates through each price and compares it with every subsequent price to find the maximum profit.
 * It's simple to understand but inefficient for large datasets.  This is like trying every possible combination of buying and selling days.
 */
function maxProfitBruteForce(prices) {
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
 * Approach 2: Optimized Brute Force (Slightly Better)
 * Time Complexity: O(n^2) - still quadratic, but with fewer iterations in some cases.
 * Space Complexity: O(1)
 *
 * This is a slight optimization of the brute force.  It's still O(n^2), but it avoids unnecessary comparisons.
 */
function maxProfitOptimizedBruteForce(prices) {
    let maxProfit = 0;
    for (let i = 0; i < prices.length - 1; i++) {
        for (let j = i + 1; j < prices.length; j++) {
            if (prices[j] > prices[i]) { // Only calculate profit if there's a chance of making money
                maxProfit = Math.max(maxProfit, prices[j] - prices[i]);
            }
        }
    }
    return maxProfit;
}



/**
 * Approach 3: Single Pass (Best Approach)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * This is the most efficient approach. It iterates through the prices array only once, keeping track of the minimum price
 * encountered so far and calculating the potential profit at each step.  This is like a smart trader who continuously looks
 * for the best buying opportunity and calculates profit if selling today.
 */
function maxProfitSinglePass(prices) {
    let minPrice = Infinity;
    let maxProfit = 0;
    for (let i = 0; i < prices.length; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else if (prices[i] - minPrice > maxProfit) {
            maxProfit = prices[i] - minPrice;
        }
    }
    return maxProfit;
}

/**
 * Approach 4: Kadane's Algorithm (for understanding max subarray problem)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Kadane's algorithm is typically used for finding the maximum subarray sum.  While this problem isn't *exactly* a maximum subarray problem,
 * we can transform it to use a similar approach.  This approach focuses on the maximum profit we can make *up to* each day.
 */
function maxProfitKadane(prices) {
    let maxSoFar = 0;
    let maxEndingHere = 0;
    for (let i = 1; i < prices.length; i++) {
        // Calculate the difference between consecutive days
        const diff = prices[i] - prices[i - 1];
        // Max ending here is either the diff or the diff plus previous max
        maxEndingHere = Math.max(0, maxEndingHere + diff);
        // Max so far is the greater of the current max and the max ending here
        maxSoFar = Math.max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

/**
 * Approach 5: Using Reduce (Functional Approach)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * This approach uses the reduce method to iterate through the prices array and calculate the maximum profit.  It's a more
 * functional way of expressing the single-pass solution.
 */
function maxProfitReduce(prices) {
    if (!prices || prices.length < 2) return 0;

    return prices.reduce((acc, price, index) => {
        if (index === 0) {
            return { minPrice: price, maxProfit: 0 };
        } else {
            const minPrice = Math.min(acc.minPrice, price);
            const maxProfit = Math.max(acc.maxProfit, price - minPrice);
            return { minPrice, maxProfit };
        }
    }, { minPrice: prices[0], maxProfit: 0 }).maxProfit;
}



// Example Usage and Output
const prices1 = [7, 1, 5, 3, 6, 4];
const prices2 = [7, 6, 4, 3, 1];
const prices3 = [2, 1, 2, 1, 0, 0, 1]; // Added test case
const prices4 = [2, 4, 1]; //Added test case

console.log("Prices 1: [7, 1, 5, 3, 6, 4]");
console.log("Brute Force:", maxProfitBruteForce(prices1));       // Output: 5
console.log("Optimized Brute Force:", maxProfitOptimizedBruteForce(prices1)); // Output: 5
console.log("Single Pass:", maxProfitSinglePass(prices1));          // Output: 5
console.log("Kadane's Algorithm:", maxProfitKadane(prices1));         // Output: 5
console.log("Reduce:", maxProfitReduce(prices1));                 // Output: 5

console.log("\nPrices 2: [7, 6, 4, 3, 1]");
console.log("Brute Force:", maxProfitBruteForce(prices2));       // Output: 0
console.log("Optimized Brute Force:", maxProfitOptimizedBruteForce(prices2)); // Output: 0
console.log("Single Pass:", maxProfitSinglePass(prices2));          // Output: 0
console.log("Kadane's Algorithm:", maxProfitKadane(prices2));         // Output: 0
console.log("Reduce:", maxProfitReduce(prices2));                 // Output: 0

console.log("\nPrices 3: [2, 1, 2, 1, 0, 0, 1]");
console.log("Brute Force:", maxProfitBruteForce(prices3));       // Output: 1
console.log("Optimized Brute Force:", maxProfitOptimizedBruteForce(prices3)); // Output: 1
console.log("Single Pass:", maxProfitSinglePass(prices3));          // Output: 1
console.log("Kadane's Algorithm:", maxProfitKadane(prices3));         // Output: 1
console.log("Reduce:", maxProfitReduce(prices3));                 // Output: 1

console.log("\nPrices 4: [2, 4, 1]");
console.log("Brute Force:", maxProfitBruteForce(prices4));
console.log("Optimized Brute Force:", maxProfitOptimizedBruteForce(prices4));
console.log("Single Pass:", maxProfitSinglePass(prices4));
console.log("Kadane's Algorithm:", maxProfitKadane(prices4));
console.log("Reduce:", maxProfitReduce(prices4));

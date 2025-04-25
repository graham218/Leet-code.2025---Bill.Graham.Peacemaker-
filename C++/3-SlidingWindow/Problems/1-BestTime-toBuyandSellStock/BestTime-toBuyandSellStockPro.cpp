#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to find the maximum profit from buying and selling a stock
// Prices are given in the 'prices' vector
// This problem is a classic example of dynamic programming and greedy algorithms

// 1. Brute Force Approach
//    - Iterate through each day (buy) and then iterate through all subsequent days (sell)
//    - Calculate the profit for each buy-sell combination
//    - Keep track of the maximum profit
//    - Time Complexity: O(n^2), where n is the number of days (length of 'prices')
//    - Space Complexity: O(1) - Constant extra space
int maxProfit_BruteForce(const vector<int>& prices) {
    int maxProfit = 0; // Initialize the maximum profit

    // Iterate through each day as a potential buying day
    for (int i = 0; i < prices.size(); ++i) {
        // Iterate through all subsequent days as potential selling days
        for (int j = i + 1; j < prices.size(); ++j) {
            // Calculate the profit for this buy-sell combination
            int profit = prices[j] - prices[i];
            // Update maxProfit if the current profit is greater
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }
    return maxProfit; // Return the maximum profit found
}

// 2. Optimized Brute Force (Slightly Better)
//    - Same logic as Brute Force, but avoids redundant comparisons
//    - Time Complexity: O(n^2), where n is the number of days.
//    - Space Complexity: O(1)
int maxProfit_OptimizedBruteForce(const vector<int>& prices) {
    int maxProfit = 0;
    for (int i = 0; i < prices.size(); ++i) {
        for (int j = i + 1; j < prices.size(); ++j) {
            if (prices[j] > prices[i]) { // Only calculate profit if selling price is higher
                maxProfit = max(maxProfit, prices[j] - prices[i]);
            }
        }
    }
    return maxProfit;
}


// 3. Single Pass Approach (Greedy Algorithm)
//    - Iterate through the prices array only once
//    - Keep track of the minimum buying price encountered so far
//    - For each day, calculate the potential profit if we sell on that day
//    - Update the maximum profit if the potential profit is greater
//    - Update the minimum buying price if the current day's price is lower
//    - Time Complexity: O(n), where n is the number of days
//    - Space Complexity: O(1) - Constant extra space
int maxProfit_SinglePass(const vector<int>& prices) {
    int maxProfit = 0; // Initialize the maximum profit
    int minPrice = numeric_limits<int>::max(); // Initialize the minimum buying price to the maximum possible integer value

    // Iterate through the prices array
    for (int price : prices) {
        // Update the minimum buying price if the current price is lower
        minPrice = min(minPrice, price);
        // Calculate the potential profit if we sell on the current day
        int profit = price - minPrice;
        // Update the maximum profit if the potential profit is greater
        maxProfit = max(maxProfit, profit);
    }
    return maxProfit; // Return the maximum profit
}

// 4. Dynamic Programming Approach
//    - Create a DP table (in this case, we can optimize it to use only two variables)
//    - dp[i] represents the maximum profit that can be made up to day i
//    - The recurrence relation is:
//      - dp[i] = max(dp[i-1], prices[i] - minPrice)
//    - Where minPrice is the minimum price seen so far.
//    - Time Complexity: O(n)
//    - Space Complexity: O(1) - Optimized to use constant space.
int maxProfit_DP(const vector<int>& prices) {
    if (prices.empty()) return 0;

    int minPrice = prices[0];  // Initialize minPrice with the first day's price
    int maxProfit = 0;     // Initialize maxProfit

    for (int i = 1; i < prices.size(); ++i) {
        // Calculate the potential profit
        int potentialProfit = prices[i] - minPrice;
        // Update maxProfit
        maxProfit = max(maxProfit, potentialProfit);
        // Update minPrice
        minPrice = min(minPrice, prices[i]);
    }
    return maxProfit;
}

// 5.  Most Readable Single Pass (Greedy)
int maxProfit_Readable(const vector<int>& prices) {
    if (prices.empty()) {
        return 0;
    }

    int buyPrice = prices[0];
    int maxProfit = 0;

    for (int i = 1; i < prices.size(); ++i) {
        int currentPrice = prices[i];
        int potentialProfit = currentPrice - buyPrice;

        maxProfit = max(maxProfit, potentialProfit); // Update maxProfit
        buyPrice = min(buyPrice, currentPrice);     // Update buyPrice
    }

    return maxProfit;
}

int main() {
    // Example usage with stock prices for a period of several days
    vector<int> stockPrices = {7, 1, 5, 3, 6, 4};

    // Call each of the functions and print the results
    cout << "Brute Force: " << maxProfit_BruteForce(stockPrices) << endl;           // Output: 5
    cout << "Optimized Brute Force: " << maxProfit_OptimizedBruteForce(stockPrices) << endl; // Output: 5
    cout << "Single Pass: " << maxProfit_SinglePass(stockPrices) << endl;             // Output: 5
    cout << "Dynamic Programming: " << maxProfit_DP(stockPrices) << endl;               // Output: 5
    cout << "Most Readable: " << maxProfit_Readable(stockPrices) << endl;               // Output: 5

    // Example with a different set of stock prices
    vector<int> stockPrices2 = {7, 6, 4, 3, 1};
    cout << "Brute Force: " << maxProfit_BruteForce(stockPrices2) << endl;         // Output: 0
    cout << "Single Pass: " << maxProfit_SinglePass(stockPrices2) << endl;           // Output: 0
    cout << "Dynamic Programming: " << maxProfit_DP(stockPrices2) << endl;             // Output: 0
    cout << "Most Readable: " << maxProfit_Readable(stockPrices2) << endl;

    vector<int> stockPrices3 = {2, 4, 1};
    cout << "Single Pass: " << maxProfit_SinglePass(stockPrices3) << endl;           // Output: 2
    cout << "Dynamic Programming: " << maxProfit_DP(stockPrices3) << endl;
    cout << "Most Readable: " << maxProfit_Readable(stockPrices3) << endl;

    return 0; // Indicate successful execution
}

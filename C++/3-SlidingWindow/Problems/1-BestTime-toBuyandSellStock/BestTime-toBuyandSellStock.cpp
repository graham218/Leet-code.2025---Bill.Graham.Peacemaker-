#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to find the maximum profit using the brute force approach.
// This approach has a time complexity of O(n^2) and a space complexity of O(1).
int maxProfitBruteForce(vector<int>& prices) {
    int maxProfit = 0;
    int n = prices.size();

    // Iterate through each possible buy day.
    for (int i = 0; i < n - 1; ++i) {
        // Iterate through each possible sell day after the buy day.
        for (int j = i + 1; j < n; ++j) {
            // Calculate the profit for the current buy and sell days.
            int profit = prices[j] - prices[i];
            // Update the maximum profit if the current profit is greater.
            maxProfit = max(maxProfit, profit);
        }
    }
    return maxProfit;
}

// Function to find the maximum profit using the optimized one-pass approach.
// This approach has a time complexity of O(n) and a space complexity of O(1).
int maxProfitOnePass(vector<int>& prices) {
    int minPrice = numeric_limits<int>::max(); // Initialize minPrice to the maximum possible integer value.
    int maxProfit = 0;
    int n = prices.size();

    // Iterate through the prices array only once.
    for (int i = 0; i < n; ++i) {
        // Update the minimum price if a lower price is found.
        minPrice = min(minPrice, prices[i]);
        // Calculate the profit if selling on the current day.
        int profit = prices[i] - minPrice;
        // Update the maximum profit if the current profit is greater.
        maxProfit = max(maxProfit, profit);
    }
    return maxProfit;
}

// Function to find the maximum profit using a modified one-pass approach
// This approach also has O(n) time complexity and O(1) space complexity.
int maxProfitOnePassOptimized(vector<int>& prices) {
    int maxProfit = 0;
    int buyPrice = prices[0]; // Assumes the first day is the initial buying day.
    int n = prices.size();

    for (int i = 1; i < n; ++i) {
        // If the current price is lower than the buying price, update the buying price.
        if (prices[i] < buyPrice) {
            buyPrice = prices[i];
        }
        // Otherwise, calculate the potential profit and update maxProfit.
        else {
            maxProfit = max(maxProfit, prices[i] - buyPrice);
        }
    }
    return maxProfit;
}

// Function to find the maximum profit using Kadane's Algorithm.
// Although Kadane's Algorithm is typically used for finding the maximum subarray sum,
// it can be adapted to solve this problem. This approach has a time complexity of O(n)
// and a space complexity of O(1).
int maxProfitKadane(vector<int>& prices) {
    int maxSoFar = 0;
    int currentMax = 0;
    int n = prices.size();

    for (int i = 1; i < n; ++i) {
        // Calculate the difference between consecutive days' prices.
        int diff = prices[i] - prices[i - 1];
        // Update currentMax.  If the difference is negative, currentMax will be 0.
        currentMax = max(0, currentMax + diff);
        // Update maxSoFar (the overall maximum profit).
        maxSoFar = max(maxSoFar, currentMax);
    }
    return maxSoFar;
}

// Function to find the maximum profit using dynamic programming.
// This approach has a time complexity of O(n) and a space complexity of O(n).  It's less
// space-efficient than the one-pass approaches, but illustrates dynamic programming.
int maxProfitDP(vector<int>& prices) {
    int n = prices.size();
    if (n == 0) return 0;

    // Create a DP table to store the maximum profit up to each day.
    vector<int> dp(n, 0);
    int minPrice = prices[0];

    // Iterate through the prices starting from the second day.
    for (int i = 1; i < n; ++i) {
        // Update the minimum price seen so far.
        minPrice = min(minPrice, prices[i]);
        // Calculate the maximum profit up to the current day.  It's either the
        // maximum profit up to the previous day, or the profit from buying at
        // the minimum price and selling today.
        dp[i] = max(dp[i - 1], prices[i] - minPrice);
    }
    // The last element of the DP table contains the overall maximum profit.
    return dp[n - 1];
}

int main() {
    // Example input: vector of stock prices.
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    // Calculate and print the maximum profit using each approach.
    cout << "Maximum profit (Brute Force): " << maxProfitBruteForce(prices) << endl;
    cout << "Maximum profit (One Pass): " << maxProfitOnePass(prices) << endl;
    cout << "Maximum profit (One Pass Optimized): " << maxProfitOnePassOptimized(prices) << endl;
    cout << "Maximum profit (Kadane's Algorithm): " << maxProfitKadane(prices) << endl;
    cout << "Maximum profit (Dynamic Programming): " << maxProfitDP(prices) << endl;

    return 0;
}

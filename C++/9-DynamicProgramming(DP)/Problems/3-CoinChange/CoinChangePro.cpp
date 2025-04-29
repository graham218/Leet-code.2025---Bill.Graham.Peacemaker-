#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// 1. Top-Down (Memoization) - Minimum Coins
// Real-world application: Optimizing cash register change dispensing
int coinChangeTopDown(vector<int>& coins, int amount, vector<int>& memo) {
    if (amount == 0) {
        return 0;
    }
    if (amount < 0) {
        return -1; // Indicate that the amount cannot be made with given coins
    }
    if (memo[amount] != -2) { // Use -2 to distinguish from the case where 0 coins are needed (amount == 0).
        return memo[amount];
    }

    int minCoins = INT_MAX;
    for (int coin : coins) {
        int subResult = coinChangeTopDown(coins, amount - coin, memo);
        if (subResult != -1) { // If the sub-problem has a valid solution
            minCoins = min(minCoins, subResult + 1);
        }
    }
    memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins; // Store the result, or -1 if no solution
    return memo[amount];
}

int coinChangeTopDown(vector<int>& coins, int amount) {
    vector<int> memo(amount + 1, -2); // Initialize memoization table with -2
    return coinChangeTopDown(coins, amount, memo);
}

// 2. Bottom-Up (Tabulation) - Minimum Coins
// Real-world application: Inventory management (minimizing number of items to fulfill an order)
int coinChangeBottomUp(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 coins needed for amount 0

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return (dp[amount] == INT_MAX) ? -1 : dp[amount];
}

// 3. Bottom-Up - Number of Combinations
// Real-world application: Counting possible ways to make payments with different denominations.
int countCoinChangeCombinations(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1; // Base case: one way to make change for amount 0 (using no coins)

    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            dp[i] += dp[i - coin];
        }
    }
    return dp[amount];
}

// 4. Top-Down (Memoization) - Number of Combinations
// Real-world application: Similar to #3, but with memoization for potentially better performance in some cases.
int countCoinChangeCombinationsTopDown(vector<int>& coins, int amount, int coinIndex, vector<vector<int>>& memo) {
    if (amount == 0) {
        return 1; // Found a valid combination
    }
    if (amount < 0 || coinIndex >= coins.size()) {
        return 0; // Invalid combination
    }

    if (memo[amount][coinIndex] != -1) {
        return memo[amount][coinIndex];
    }

    // Include the current coin, or exclude it.
    memo[amount][coinIndex] = countCoinChangeCombinationsTopDown(coins, amount - coins[coinIndex], coinIndex, memo) +
                               countCoinChangeCombinationsTopDown(coins, amount, coinIndex + 1, memo);
    return memo[amount][coinIndex];
}

int countCoinChangeCombinationsTopDown(vector<int>& coins, int amount) {
    vector<vector<int>> memo(amount + 1, vector<int>(coins.size(), -1));
    return countCoinChangeCombinationsTopDown(coins, amount, 0, memo);
}

// 5. Bottom Up - Minimum Number of Coins with Coin Tracking
// Real-world application:  ATM cash dispensing with denomination tracking.
// This version not only calculates the minimum number of coins but also tracks
// *which* coins are used.
pair<int, vector<int>> coinChangeBottomUpWithTracking(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    vector<int> parent(amount + 1, -1); // Store the "parent" amount from which we reached the current amount
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                    parent[i] = i - coins[j]; // Store where we came from
                }
            }
        }
    }

    if (dp[amount] == INT_MAX) {
        return {-1, {}}; // No solution
    }

    // Backtrack to find the coins used
    vector<int> usedCoins;
    int currentAmount = amount;
    while (currentAmount > 0) {
        int previousAmount = parent[currentAmount];
        int usedCoin = currentAmount - previousAmount;
        usedCoins.push_back(usedCoin);
        currentAmount = previousAmount;
    }
    return {dp[amount], usedCoins};
}

int main() {
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000}; // Common coin denominations in some countries
    int amount = 2035;

    cout << "Coin Change Problem" << endl;
    cout << "Coins: ";
    for (int coin : coins) {
        cout << coin << " ";
    }
    cout << endl;
    cout << "Amount: " << amount << endl << endl;

    // 1. Top-Down (Memoization) - Minimum Coins
    int minCoinsTopDown = coinChangeTopDown(coins, amount);
    cout << "1. Top-Down (Memoization) - Minimum Coins: ";
    if (minCoinsTopDown == -1) {
        cout << "No solution exists." << endl;
    } else {
        cout << minCoinsTopDown << endl;
    }

    // 2. Bottom-Up (Tabulation) - Minimum Coins
    int minCoinsBottomUp = coinChangeBottomUp(coins, amount);
    cout << "2. Bottom-Up (Tabulation) - Minimum Coins: ";
    if (minCoinsBottomUp == -1) {
        cout << "No solution exists." << endl;
    } else {
        cout << minCoinsBottomUp << endl;
    }

    // 3. Bottom-Up - Number of Combinations
    int combinationsBottomUp = countCoinChangeCombinations(coins, amount);
    cout << "3. Bottom-Up - Number of Combinations: " << combinationsBottomUp << endl;

    // 4. Top-Down - Number of Combinations
    int combinationsTopDown = countCoinChangeCombinationsTopDown(coins, amount);
    cout << "4. Top-Down - Number of Combinations: " << combinationsTopDown << endl;

     // 5. Bottom Up - Minimum Number of Coins with Coin Tracking
    pair<int, vector<int>> resultWithTracking = coinChangeBottomUpWithTracking(coins, amount);
    cout << "5. Bottom Up - Minimum Number of Coins with Coin Tracking:" << endl;
    if (resultWithTracking.first == -1) {
        cout << "   No solution exists." << endl;
    } else {
        cout << "   Minimum Coins: " << resultWithTracking.first << endl;
        cout << "   Coins Used: ";
        for (int coin : resultWithTracking.second) {
            cout << coin << " ";
        }
        cout << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric> // For std::accumulate

using namespace std;

// 1. Recursive Approach (Plain Recursion)
//    - This is the most basic approach, but it's highly inefficient due to redundant calculations.
//    - It directly implements the recursive definition of the coin change problem.
int coinChangeRecursive(vector<int>& coins, int amount) {
    // Base cases:
    if (amount == 0) {
        return 0; // If the target amount is 0, no coins are needed.
    }
    if (amount < 0) {
        return -1; // If the target amount is negative, it's impossible to make change.
    }

    int minCoins = INT_MAX; // Initialize with a large value to find the minimum.

    // Try using each coin as the last coin in the change.
    for (int coin : coins) {
        int subResult = coinChangeRecursive(coins, amount - coin); // Recursive call
        if (subResult != -1) { // If a solution exists for the subproblem...
            minCoins = min(minCoins, subResult + 1); // Update minCoins
        }
    }

    return (minCoins == INT_MAX) ? -1 : minCoins; // If no solution was found, return -1.
}

// 2. Memoization (Top-Down Dynamic Programming)
//    - This approach improves upon the recursive solution by storing the results of
//      subproblems in a table (memo) to avoid recalculating them.
//    - It's still recursive but much more efficient.
int coinChangeMemo(vector<int>& coins, int amount, vector<int>& memo) {
    // Base cases:
    if (amount == 0) {
        return 0;
    }
    if (amount < 0) {
        return -1;
    }

    // Check if the result for this amount is already memoized.
    if (memo[amount] != -1) {
        return memo[amount];
    }

    int minCoins = INT_MAX;
    for (int coin : coins) {
        int subResult = coinChangeMemo(coins, amount - coin, memo);
        if (subResult != -1) {
            minCoins = min(minCoins, subResult + 1);
        }
    }

    // Store the result in the memo table before returning.
    memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins;
    return memo[amount];
}

int coinChangeMemoization(vector<int>& coins, int amount) {
    vector<int> memo(amount + 1, -1); // Initialize memo table with -1 (indicating not calculated).
    return coinChangeMemo(coins, amount, memo);
}

// 3. Tabulation (Bottom-Up Dynamic Programming)
//    - This is an iterative approach that builds up a table of solutions to subproblems
//      from the bottom up.
//    - It's generally more efficient than memoization because it avoids recursion overhead.
int coinChangeTabulation(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX); // dp[i] stores the minimum coins needed for amount i.
    dp[0] = 0; // Base case: 0 coins are needed for amount 0.

    // Iterate through all possible amounts from 1 to the target amount.
    for (int i = 1; i <= amount; ++i) {
        // For each amount, try using each coin.
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                // If using this coin leads to a valid subproblem solution,
                // update the minimum number of coins needed for the current amount.
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return (dp[amount] == INT_MAX) ? -1 : dp[amount]; // Return the result for the target amount.
}

// 4. Tabulation with Coin Count Tracking
//    - This approach is similar to tabulation, but it also keeps track of the number
//      of times each coin is used in the optimal solution.
//    - This is useful if you need to know the actual coin combination.
int coinChangeTabulationWithCount(vector<int>& coins, int amount, vector<int>& coinCount) {
    vector<int> dp(amount + 1, INT_MAX);
    vector<int> lastCoin(amount + 1, -1); // Store the last coin used to reach amount i.
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                if (dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    lastCoin[i] = coin; // Store the coin used.
                }
            }
        }
    }

    if (dp[amount] == INT_MAX) {
        return -1;
    }

    // Reconstruct the coin combination and count the occurrences of each coin.
    int currentAmount = amount;
    while (currentAmount > 0) {
        int coin = lastCoin[currentAmount];
        for (int i = 0; i < coins.size(); ++i)
        {
            if (coins[i] == coin)
            {
                coinCount[i]++;
                break;
            }
        }
        currentAmount -= coin;
    }
    return dp[amount];
}

// 5. Optimized 1D DP
//    - A space-optimized version of the tabulation method.  It uses only a 1D DP array.
int coinChangeOptimized(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);  // Initialize with a value > max possible coins
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    cout << "Coin Change Problem: Finding the minimum number of coins to make up a given amount." << endl;
    cout << "Coins: ";
    for (int coin : coins) {
        cout << coin << " ";
    }
    cout << endl;
    cout << "Target Amount: " << amount << endl << endl;

    // 1. Recursive Approach
    cout << "1. Recursive Approach: ";
    int resultRecursive = coinChangeRecursive(coins, amount);
    if (resultRecursive != -1) {
        cout << "Minimum coins needed: " << resultRecursive << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 2. Memoization Approach
    cout << "2. Memoization Approach: ";
    int resultMemo = coinChangeMemoization(coins, amount);
    if (resultMemo != -1) {
        cout << "Minimum coins needed: " << resultMemo << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 3. Tabulation Approach
    cout << "3. Tabulation Approach: ";
    int resultTabulation = coinChangeTabulation(coins, amount);
    if (resultTabulation != -1) {
        cout << "Minimum coins needed: " << resultTabulation << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 4. Tabulation with Coin Count Tracking
    cout << "4. Tabulation with Coin Count: ";
    vector<int> coinCount(coins.size(), 0); // Initialize coin counts to 0.
    int resultTabulationWithCount = coinChangeTabulationWithCount(coins, amount, coinCount);
    if (resultTabulationWithCount != -1) {
        cout << "Minimum coins needed: " << resultTabulationWithCount << endl;
        cout << "Coin Count: ";
        for (int i = 0; i < coins.size(); ++i) {
            cout << coins[i] << ":" << coinCount[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 5. Optimized 1D DP
    cout << "5. Optimized 1D DP Approach: ";
    int resultOptimized = coinChangeOptimized(coins, amount);
    if (resultOptimized != -1) {
        cout << "Minimum coins needed: " << resultOptimized << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}


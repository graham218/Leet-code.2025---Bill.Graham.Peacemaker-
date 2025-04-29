#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// 1. Recursive Approach (Plain Recursion)
//    - This is the most basic approach, directly translating the problem's recursive nature.
//    - It has exponential time complexity, making it inefficient for larger inputs.
int knapsackRecursive(int capacity, const vector<Item>& items, int n) {
    if (n == 0 || capacity == 0) {
        return 0;
    }

    if (items[n - 1].weight > capacity) {
        return knapsackRecursive(capacity, items, n - 1);
    } else {
        return max(
            items[n - 1].value + knapsackRecursive(capacity - items[n - 1].weight, items, n - 1),
            knapsackRecursive(capacity, items, n - 1)
        );
    }
}

// 2. Memoization (Top-Down DP)
//    - This approach improves upon the recursive solution by storing the results of subproblems.
//    - It uses a table (dp array) to avoid redundant calculations.
//    - Time complexity: O(n * capacity), Space complexity: O(n * capacity) + O(n) for call stack
int knapsackMemoization(int capacity, const vector<Item>& items, int n, vector<vector<int>>& dp) {
    if (n == 0 || capacity == 0) {
        return 0;
    }

    if (dp[n][capacity] != -1) {
        return dp[n][capacity];
    }

    if (items[n - 1].weight > capacity) {
        dp[n][capacity] = knapsackMemoization(capacity, items, n - 1, dp);
        return dp[n][capacity];
    } else {
        dp[n][capacity] = max(
            items[n - 1].value + knapsackMemoization(capacity - items[n - 1].weight, items, n - 1, dp),
            knapsackMemoization(capacity, items, n - 1, dp)
        );
        return dp[n][capacity];
    }
}

// Helper function to initialize the DP table for memoization
int knapsackMemoizationHelper(int capacity, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, -1)); // Initialize DP table with -1
    return knapsackMemoization(capacity, items, n, dp);
}

// 3. Tabulation (Bottom-Up DP)
//    - This is a further optimized approach where we build the solution table iteratively.
//    - It avoids recursion, leading to better performance.
//    - Time complexity: O(n * capacity), Space complexity: O(n * capacity)
int knapsackTabulation(int capacity, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

// 4. Space Optimized Tabulation
//    - This is a space-optimized version of the tabulation method.
//    - It uses only a 1D array to store the previous row's results, reducing space complexity.
//    - Time complexity: O(n * capacity), Space complexity: O(capacity)
int knapsackSpaceOptimized(int capacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= items[i].weight; --w) {
            dp[w] = max(dp[w], items[i].value + dp[w - items[i].weight]);
        }
    }
    return dp[capacity];
}

// 5. Item-based Space Optimization
//    -  Similar to the previous optimization, but the outer loop iterates through items.
//    -  This can sometimes provide a slight performance edge depending on the data.
//    - Time complexity: O(n * capacity), Space complexity: O(capacity)
int knapsackItemOptimized(int capacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(capacity + 1, 0);

    for (const auto& item : items) {
        for (int w = capacity; w >= item.weight; --w) {
            dp[w] = max(dp[w], item.value + dp[w - item.weight]);
        }
    }
    return dp[capacity];
}

int main() {
    // Example usage
    vector<Item> items = {
        {2, 60},
        {1, 50},
        {3, 70},
        {2, 30},
        {1, 40}
    };
    int capacity = 5;
    int n = items.size();

    cout << "0/1 Knapsack Problem" << endl;
    cout << "---------------------" << endl;
    cout << "Items: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << ": Weight = " << items[i].weight << ", Value = " << items[i].value << endl;
    }
    cout << "Capacity: " << capacity << endl << endl;

    cout << "1. Recursive Approach: " << knapsackRecursive(capacity, items, n) << endl;
    cout << "2. Memoization Approach: " << knapsackMemoizationHelper(capacity, items) << endl;
    cout << "3. Tabulation Approach: " << knapsackTabulation(capacity, items) << endl;
    cout << "4. Space Optimized Tabulation Approach: " << knapsackSpaceOptimized(capacity, items) << endl;
    cout << "5. Item Optimized Approach: " << knapsackItemOptimized(capacity, items) << endl;

    return 0;
}

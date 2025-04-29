#include <iostream>
#include <vector>
#include <climits>
#include <iomanip> // Required for setw

using namespace std;

// Function to print the matrices dimensions
void printDimensions(const vector<int>& p) {
    cout << "Matrices Dimensions: ";
    for (size_t i = 0; i < p.size() - 1; ++i) {
        cout << "A" << i + 1 << ": " << p[i] << "x" << p[i + 1] << ", ";
    }
    cout << endl;
}

// 1. Recursive Solution
// This is the most basic approach, exploring all possible parenthesizations.
// It has exponential time complexity and is very inefficient.
int matrixChainMultiplicationRecursive(const vector<int>& p, int i, int j) {
    if (i == j) {
        return 0; // Cost of multiplying a single matrix is 0
    }

    int minCost = INT_MAX;
    for (int k = i; k < j; ++k) {
        // Calculate cost for each possible split
        int cost = matrixChainMultiplicationRecursive(p, i, k) +
                   matrixChainMultiplicationRecursive(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j]; // Cost of multiplying the two subproblems and the result
        minCost = min(minCost, cost); // Update minimum cost
    }
    return minCost;
}

// 2. Top-Down Dynamic Programming (Memoization)
// This approach improves upon the recursive solution by storing the results of
// subproblems to avoid redundant calculations.
// It has a time complexity of O(n^3) and space complexity of O(n^2).
int matrixChainMultiplicationMemoization(const vector<int>& p, int i, int j, vector<vector<int>>& memo) {
    if (i == j) {
        return 0;
    }

    if (memo[i][j] != -1) {
        return memo[i][j]; // Return stored result if available
    }

    int minCost = INT_MAX;
    for (int k = i; k < j; ++k) {
        int cost = matrixChainMultiplicationMemoization(p, i, k, memo) +
                   matrixChainMultiplicationMemoization(p, k + 1, j, memo) +
                   p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }
    memo[i][j] = minCost; // Store the result
    return minCost;
}

// 3. Bottom-Up Dynamic Programming (Tabulation)
// This approach systematically calculates the optimal costs for all subproblems
// in a bottom-up manner, filling a table.
// It also has a time complexity of O(n^3) and space complexity of O(n^2).
int matrixChainMultiplicationTabulation(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); // Initialize DP table

    for (int len = 2; len <= n; ++len) { // Iterate over lengths of subproblems
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n]; // The result is stored in dp[1][n]
}

// 4. Optimized Bottom-Up DP (Slightly Reduced Space)
// In the standard bottom-up approach, we fill the entire DP table. However,
// we only need the values in the upper triangle.  This version doesn't save a lot of space,
// but it can be more efficient in some implementations.  It still O(n^2) space and O(n^3) time.
int matrixChainMultiplicationOptimized(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n - 1];
}

// 5.  Divide and Conquer (Similar to Recursive, for comparison)
// This is essentially the same as the recursive approach, but it's presented
// here to explicitly show the divide-and-conquer nature of the problem.
// It's inefficient, with exponential time complexity.  It's included for completeness.
int matrixChainMultiplicationDivideAndConquer(const vector<int>& p, int i, int j) {
    if (i == j) {
        return 0;
    }
    int minCost = INT_MAX;
    for (int k = i; k < j; ++k) {
        int cost = matrixChainMultiplicationDivideAndConquer(p, i, k) +
                   matrixChainMultiplicationDivideAndConquer(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }
    return minCost;
}

int main() {
    // Example usage:
    vector<int> dimensions = {10, 30, 5, 60, 5}; // Dimensions of matrices: A1: 10x30, A2: 30x5, A3: 5x60, A4: 60x5
    int n = dimensions.size();

    printDimensions(dimensions);

    cout << "\n1. Recursive Solution:\n";
    cout << "Minimum cost: " << matrixChainMultiplicationRecursive(dimensions, 1, n - 1) << endl;

    cout << "\n2. Top-Down Dynamic Programming (Memoization):\n";
    vector<vector<int>> memo(n, vector<int>(n, -1));
    cout << "Minimum cost: " << matrixChainMultiplicationMemoization(dimensions, 1, n - 1, memo) << endl;

    cout << "\n3. Bottom-Up Dynamic Programming (Tabulation):\n";
    cout << "Minimum cost: " << matrixChainMultiplicationTabulation(dimensions) << endl;

    cout << "\n4. Optimized Bottom-Up Dynamic Programming:\n";
    cout << "Minimum cost: " << matrixChainMultiplicationOptimized(dimensions) << endl;

    cout << "\n5. Divide and Conquer:\n";
    cout << "Minimum cost: " << matrixChainMultiplicationDivideAndConquer(dimensions, 1, n - 1) << endl;

    return 0;
}

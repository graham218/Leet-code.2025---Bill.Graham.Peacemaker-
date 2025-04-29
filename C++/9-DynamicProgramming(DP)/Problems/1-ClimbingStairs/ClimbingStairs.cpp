#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// Problem:
// You are climbing a staircase. It takes n steps to reach the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

// Function to solve the climbing stairs problem using recursion
// This approach has exponential time complexity, leading to stack overflow for larger n.
int climbStairsRecursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

// Function to solve the climbing stairs problem using memoization (top-down DP)
// This approach uses a vector to store the results of subproblems.
// It has a time complexity of O(n) and a space complexity of O(n).
int climbStairsMemoization(int n, vector<int>& memo) {
    if (n <= 1) {
        return 1;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
    return memo[n];
}

// Function to solve the climbing stairs problem using tabulation (bottom-up DP)
// This approach builds a table of results from the bottom up.
// It has a time complexity of O(n) and a space complexity of O(n).
int climbStairsTabulation(int n) {
    if (n <= 1) {
        return 1;
    }
    vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// Function to solve the climbing stairs problem using tabulation with space optimization
// This approach uses only two variables to store the results of the previous two subproblems.
// It has a time complexity of O(n) and a space complexity of O(1).
int climbStairsOptimized(int n) {
    if (n <= 1) {
        return 1;
    }
    int prev1 = 1; // Represents dp[i-1]
    int prev2 = 1; // Represents dp[i-2]
    for (int i = 2; i <= n; ++i) {
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

// Function to solve the climbing stairs problem using matrix exponentiation
// This approach uses matrix exponentiation to calculate the nth Fibonacci number.
// It has a time complexity of O(log n) and a space complexity of O(1).
#include <vector>

std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    int rows_a = a.size();
    int cols_a = a[0].size();
    int cols_b = b[0].size();
    std::vector<std::vector<int>> result(rows_a, std::vector<int>(cols_b, 0));

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; ++j) {
            for (int k = 0; k < cols_a; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

std::vector<std::vector<int>> matrixPower(std::vector<std::vector<int>> base, int n) {
    std::vector<std::vector<int>> result = {{1, 0}, {0, 1}}; // Identity matrix
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, base);
        }
        base = matrixMultiply(base, base);
        n /= 2;
    }
    return result;
}

int climbStairsMatrix(int n) {
    if (n <= 1) return 1;
    std::vector<std::vector<int>> base_matrix = {{1, 1}, {1, 0}};
    std::vector<std::vector<int>> result_matrix = matrixPower(base_matrix, n - 1);
    return result_matrix[0][0];
}

int main() {
    int n = 10; // Number of stairs

    // 1. Recursive Approach
    cout << "Recursive Approach: Number of ways to climb " << n << " stairs: " << climbStairsRecursive(n) << endl;

    // 2. Memoization Approach
    vector<int> memo(n + 1, -1);
    cout << "Memoization Approach: Number of ways to climb " << n << " stairs: " << climbStairsMemoization(n, memo) << endl;

    // 3. Tabulation Approach
    cout << "Tabulation Approach: Number of ways to climb " << n << " stairs: " << climbStairsTabulation(n) << endl;

    // 4. Optimized Approach
    cout << "Optimized Approach: Number of ways to climb " << n << " stairs: " << climbStairsOptimized(n) << endl;

    // 5. Matrix Exponentiation Approach
    cout << "Matrix Exponentiation Approach: Number of ways to climb " << n << " stairs: " << climbStairsMatrix(n) << endl;

    return 0;
}

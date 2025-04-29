#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip> // for setprecision

// Structure to hold the result of matrix chain multiplication, including the optimal cost and the parenthesization string.
struct MCMResult {
    int cost;
    std::string parentheses;
};

// Helper function to print the parenthesization of the matrices.
std::string printParentheses(const std::vector<std::vector<int>>& s, int i, int j, const std::vector<std::string>& matrixNames) {
    if (i == j) {
        return matrixNames[i - 1]; // Use matrix names
    }
    std::string result = "(" + printParentheses(s, i, s[i][j], matrixNames) +
                           printParentheses(s, s[i][j] + 1, j, matrixNames) + ")";
    return result;
}

// 1. Top-Down Memoization Approach (Recursive with Caching)
//   - Implements the recursive solution with memoization to avoid redundant calculations.
//   - Uses a 2D vector (memo) to store the results of subproblems.
//   - Real-world use case: Optimizing query execution plans in database systems.  When joining multiple tables, the order of joins can drastically affect performance.  This approach can be used to find the optimal join order.
MCMResult matrixChainMultiplication_Memoized(const std::vector<int>& p, int i, int j, std::vector<std::vector<int>>& memo, std::vector<std::vector<int>>& s, const std::vector<std::string>& matrixNames) {
    if (i == j) {
        return {0, matrixNames[i-1]};
    }
    if (memo[i][j] != -1) {
        std::string par = printParentheses(s, i, j, matrixNames);
        return {memo[i][j], par};
    }

    int minCost = INT_MAX;
    int minK = -1;
    std::string bestParens;

    for (int k = i; k < j; ++k) {
        MCMResult leftResult = matrixChainMultiplication_Memoized(p, i, k, memo, s, matrixNames);
        MCMResult rightResult = matrixChainMultiplication_Memoized(p, k + 1, j, memo, s, matrixNames);
        int cost = leftResult.cost + rightResult.cost + p[i - 1] * p[k] * p[j];

        if (cost < minCost) {
            minCost = cost;
            minK = k;
            bestParens = "(" + leftResult.parentheses + rightResult.parentheses + ")";
        }
    }
    memo[i][j] = minCost;
    s[i][j] = minK;
    return {minCost, bestParens};
}

// 2. Bottom-Up Dynamic Programming Approach (Tabulation)
//   - Implements the iterative dynamic programming solution.
//   - Builds the solution table (dp) in a bottom-up manner.
//   - Real-world use case: Compiler optimization.  When generating code for a sequence of matrix multiplications, a compiler can use this approach to determine the most efficient way to parenthesize the expression.
MCMResult matrixChainMultiplication_Tabular(const std::vector<int>& p, const std::vector<std::string>& matrixNames) {
    int n = p.size() - 1;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0)); // To store split points for optimal parenthesization

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    s[i][j] = k; // Store the split point
                }
            }
        }
    }
    std::string par = printParentheses(s, 1, n, matrixNames);
    return {dp[1][n], par};
}

// 3. Divide and Conquer Approach (Recursive, Naive)
//   - Implements the basic recursive solution without memoization.
//   - This is the least efficient approach, as it recalculates the same subproblems multiple times.
//   - Real-world use case: While not efficient enough for direct use, this serves as a baseline for understanding the problem and comparing the performance of other approaches.  It can be used in educational settings to illustrate the need for dynamic programming.
MCMResult matrixChainMultiplication_Recursive(const std::vector<int>& p, int i, int j, const std::vector<std::string>& matrixNames) {
    if (i == j) {
        return {0, matrixNames[i-1]};
    }

    int minCost = INT_MAX;
    std::string bestParens;

    for (int k = i; k < j; ++k) {
        MCMResult leftResult = matrixChainMultiplication_Recursive(p, i, k, matrixNames);
        MCMResult rightResult = matrixChainMultiplication_Recursive(p, k + 1, j, matrixNames);
        int cost = leftResult.cost + rightResult.cost + p[i - 1] * p[k] * p[j];
        if (cost < minCost) {
            minCost = cost;
            bestParens = "(" + leftResult.parentheses + rightResult.parentheses + ")";
        }
    }
    return {minCost, bestParens};
}

// 4.  Optimized Bottom-Up DP (Space Optimized)
//     - A space-optimized version of the bottom-up DP.  It reduces the space complexity from O(n^2) to O(n) by observing that we only need the previous row of the DP table to calculate the current row.
//     - Real-world use case:  Large-scale matrix multiplication scenarios where memory is a significant constraint.  For example, in embedded systems or when dealing with very large matrices, this optimization can be crucial.
MCMResult matrixChainMultiplication_SpaceOptimized(const std::vector<int>& p, const std::vector<std::string>& matrixNames) {
    int n = p.size() - 1;
    std::vector<int> dp(n, 0); // Stores costs for subproblems of length i
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0));

    for (int len = 2; len <= n; ++len) {
        std::vector<int> prev_dp = dp; // Store the previous row
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = prev_dp[i] + prev_dp[k + 1 - i - 1] + p[i] * p[k] * p[j]; // k+1 -i -1 is the index of the element in the previous dp array.
                if (cost < dp[i]) {
                    dp[i] = cost;
                    s[i+1][j+1] = k+1;
                }
            }
        }
    }
    std::string par = printParentheses(s, 1, n, matrixNames);
    return {dp[0], par};
}

// 5. Hybrid Approach (Memoization with Iterative Base Cases)
//    - Combines the benefits of memoization and iteration.  It pre-computes the base cases (subproblems of size 1 and 2) iteratively and then uses memoization for larger subproblems.
//    - Real-world use case:  Balances the overhead of recursion with the efficiency of iteration.  This can be useful when dealing with a mix of small and large matrix chains, providing a good balance of performance.
MCMResult matrixChainMultiplication_Hybrid(const std::vector<int>& p, const std::vector<std::vector<int>>& baseCases, std::vector<std::vector<int>>& memo, std::vector<std::vector<int>>& s, const std::vector<std::string>& matrixNames) {
    int n = p.size() - 1;

    // Initialize base cases in memo table.
    for (int i = 1; i <= n; ++i) {
        memo[i][i] = 0;
    }
    for(int i = 1; i < n; ++i){
        memo[i][i+1] = p[i-1] * p[i] * p[i+1];
        s[i][i+1] = i;
    }

    // Now solve using memoization
    if (memo[1][n] != -1)
    {
        return {memo[1][n], printParentheses(s, 1, n, matrixNames)};
    }
    else
    {
        return matrixChainMultiplication_Memoized(p, 1, n, memo, s, matrixNames);
    }
}

int main() {
    // Example usage with a set of matrix dimensions.
    std::vector<int> dimensions = {10, 30, 5, 60, 5}; // Dimensions: A(10x30), B(30x5), C(5x60), D(60x5)
    std::vector<std::string> matrixNames = {"A", "B", "C", "D"};
    int n = dimensions.size() - 1;

    std::cout << "Matrix Dimensions: ";
    for (int i = 0; i < dimensions.size(); ++i) {
        std::cout << dimensions[i] << (i < dimensions.size() - 1 ? " x " : "");
    }
    std::cout << std::endl;

    std::cout << "\nMatrix Names: ";
    for (const auto& name : matrixNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

    // 1. Top-Down Memoization
    std::vector<std::vector<int>> memo_memo(n + 1, std::vector<int>(n + 1, -1));
    std::vector<std::vector<int>> s_memo(n + 1, std::vector<int>(n + 1, 0));
    MCMResult result_memo = matrixChainMultiplication_Memoized(dimensions, 1, n, memo_memo, s_memo, matrixNames);
    std::cout << "\n1. Top-Down Memoization:\n";
    std::cout << "Optimal Cost: " << result_memo.cost << "\n";
    std::cout << "Optimal Parenthesization: " << result_memo.parentheses << "\n";

    // 2. Bottom-Up Tabulation
    MCMResult result_tab = matrixChainMultiplication_Tabular(dimensions, matrixNames);
    std::cout << "\n2. Bottom-Up Tabulation:\n";
    std::cout << "Optimal Cost: " << result_tab.cost << "\n";
    std::cout << "Optimal Parenthesization: " << result_tab.parentheses << "\n";

    // 3. Divide and Conquer
    MCMResult result_rec = matrixChainMultiplication_Recursive(dimensions, 1, n, matrixNames);
    std::cout << "\n3. Divide and Conquer:\n";
    std::cout << "Optimal Cost: " << result_rec.cost << "\n";
    std::cout << "Optimal Parenthesization: " << result_rec.parentheses << "\n";

    // 4. Space Optimized DP
    MCMResult result_space = matrixChainMultiplication_SpaceOptimized(dimensions, matrixNames);
    std::cout << "\n4. Space Optimized DP:\n";
    std::cout << "Optimal Cost: " << result_space.cost << "\n";
    std::cout << "Optimal Parenthesization: " << result_space.parentheses << "\n";

    // 5. Hybrid Approach
    std::vector<std::vector<int>> memo_hybrid(n + 1, std::vector<int>(n + 1, -1));
    std::vector<std::vector<int>> s_hybrid(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> baseCases(n + 1, std::vector<int>(n + 1, 0)); // Not actually used in this version
    MCMResult result_hybrid = matrixChainMultiplication_Hybrid(dimensions, baseCases, memo_hybrid, s_hybrid, matrixNames);
    std::cout << "\n5. Hybrid Approach:\n";
    std::cout << "Optimal Cost: " << result_hybrid.cost << "\n";
    std::cout << "Optimal Parenthesization: " << result_hybrid.parentheses << "\n";

    return 0;
}

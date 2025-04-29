#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cmath> // Include cmath for sqrt and pow
#include <limits> // Include limits for max()

using namespace std;
using namespace std::chrono;

// Function to simulate a time-consuming task (e.g., fetching data, complex calculation)
void simulate_delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// 1. Top-Down Approach (Memoization)
//   - Real-world application: Optimizing recursive functions with overlapping subproblems,
//     such as parsing complex configuration files or evaluating expression trees.
int climbStairsTopDown(int n, unordered_map<int, int>& memo) {
    if (n <= 2) {
        return n;
    }
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    // Simulate a delay, as would happen in a real-world application.
    simulate_delay(1); // Simulate 1ms delay
    memo[n] = climbStairsTopDown(n - 1, memo) + climbStairsTopDown(n - 2, memo);
    return memo[n];
}

int climbStairsTopDown(int n) {
    unordered_map<int, int> memo;
    return climbStairsTopDown(n, memo);
}

// 2. Bottom-Up Approach (Tabulation)
//   - Real-world application: Building lookup tables for efficient data retrieval,
//     like calculating and storing financial data (e.g., stock prices, interest rates) for quick access.
int climbStairsBottomUp(int n) {
    if (n <= 2) {
        return n;
    }
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        // Simulate a delay
        simulate_delay(1);
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 3. Bottom-Up Approach with Space Optimization
//    - Real-world application: Embedded systems or mobile apps with limited memory,
//      where minimizing memory usage is crucial, such as calculating intermediate values in sensor data processing.
int climbStairsBottomUpOptimized(int n) {
    if (n <= 2) {
        return n;
    }
    int prev1 = 2;
    int prev2 = 1;
    for (int i = 3; i <= n; ++i) {
        // Simulate a delay
        simulate_delay(1);
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

// 4. Matrix Method
//    - Real-world application:  This method is more of a mathematical optimization,
//       but matrix exponentiation techniques are used in cryptography (e.g., RSA algorithm)
//       and graph theory (e.g., finding paths in a graph).  While not a *direct* application
//       to climbing stairs in a real-world scenario, the underlying matrix operations are widely used.
#include <vector>

std::vector<std::vector<long long>> matrixMultiply(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b) {
    int n = a.size();
    std::vector<std::vector<long long>> result(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

std::vector<std::vector<long long>> matrixPower(std::vector<std::vector<long long>> matrix, int n) {
    int size = matrix.size();
    std::vector<std::vector<long long>> result(size, std::vector<long long>(size, 0));
    for (int i = 0; i < size; ++i) {
        result[i][i] = 1; // Identity matrix
    }
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, matrix);
        }
        matrix = matrixMultiply(matrix, matrix);
        n /= 2;
    }
    return result;
}

int climbStairsMatrix(int n) {
    if (n <= 2) {
        return n;
    }
    std::vector<std::vector<long long>> baseMatrix = {{1, 1}, {1, 0}};
    std::vector<std::vector<long long>> resultMatrix = matrixPower(baseMatrix, n - 1);
    // Simulate Delay
    simulate_delay(1);
    return resultMatrix[0][0] + resultMatrix[1][0];
}

// 5. Fibonacci Formula (Binet's Formula)
//   - Real-world application: While this is a direct mathematical solution to the Fibonacci sequence,
//     which relates to climbing stairs, Fibonacci numbers appear in various natural phenomena and
//     are used in algorithms like the Fibonacci search technique, and in financial modeling.
//   -  Important Note:  Binet's formula can have precision issues with floating-point numbers for larger 'n'.
//      In a real-world financial application, you might need to use a library for high-precision arithmetic.
int climbStairsFibonacci(int n) {
    if (n <= 2) {
        return n;
    }
    double sqrt5 = sqrt(5);
    double fibN = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
    // Simulate delay
    simulate_delay(1);
    return static_cast<int>(round(fibN / sqrt5)); // Use round() to get the nearest integer
}

int main() {
    int n = 30; // Number of stairs

    cout << "Climbing Stairs Problem - Number of stairs: " << n << endl;

    // 1. Top-Down (Memoization)
    auto start = high_resolution_clock::now();
    int resultTopDown = climbStairsTopDown(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Top-Down (Memoization): " << resultTopDown << " in "
              << duration.count() << " microseconds" << endl;

    // 2. Bottom-Up (Tabulation)
    start = high_resolution_clock::now();
    int resultBottomUp = climbStairsBottomUp(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Bottom-Up (Tabulation): " << resultBottomUp << " in "
              << duration.count() << " microseconds" << endl;

    // 3. Bottom-Up Optimized
    start = high_resolution_clock::now();
    int resultBottomUpOptimized = climbStairsBottomUpOptimized(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Bottom-Up (Optimized): " << resultBottomUpOptimized << " in "
              << duration.count() << " microseconds" << endl;

    // 4. Matrix Method
    start = high_resolution_clock::now();
    int resultMatrix = climbStairsMatrix(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Matrix Method: " << resultMatrix << " in "
              << duration.count() << " microseconds" << endl;

    // 5. Fibonacci Formula
    start = high_resolution_clock::now();
    int resultFibonacci = climbStairsFibonacci(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Fibonacci Formula: " << resultFibonacci << " in "
              << duration.count() << " microseconds" << endl;

    return 0;
}

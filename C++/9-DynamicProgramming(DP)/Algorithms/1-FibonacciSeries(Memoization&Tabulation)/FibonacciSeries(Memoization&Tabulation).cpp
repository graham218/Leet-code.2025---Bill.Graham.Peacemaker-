#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <map>

using namespace std;
using namespace std::chrono;

// Function to calculate Fibonacci number using recursion (Naive Approach)
// This is the most basic approach, but it's very inefficient due to repeated calculations.
long long fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Function to calculate Fibonacci number using memoization (Top-Down DP)
// Memoization optimizes the recursive approach by storing the results of previously
// computed values in a cache (dp array).
long long fibonacciMemoization(int n, vector<long long>& dp) {
    if (n <= 1) {
        return n;
    }
    if (dp[n] != -1) {
        return dp[n];
    }
    dp[n] = fibonacciMemoization(n - 1, dp) + fibonacciMemoization(n - 2, dp);
    return dp[n];
}

// Function to calculate Fibonacci number using tabulation (Bottom-Up DP)
// Tabulation builds up the solution iteratively, starting from the base cases
// and storing intermediate results in a table (dp array).
long long fibonacciTabulation(int n) {
    if (n <= 1) {
        return n;
    }
    vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// Function to calculate Fibonacci number using space-optimized tabulation
// This approach further optimizes tabulation by only storing the two most recent
// Fibonacci numbers, instead of the entire table.
long long fibonacciSpaceOptimized(int n) {
    if (n <= 1) {
        return n;
    }
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Function to calculate Fibonacci using matrix exponentiation
// This method uses the property of Fibonacci numbers and matrix multiplication.
// It's one of the fastest methods for very large numbers.
long long fibonacciMatrix(int n) {
    if (n <= 1) return n;

    // Initialize the matrix
    long long F[2][2] = {{1, 1}, {1, 0}};
    long long result[2][2] = {{1, 0}, {0, 1}}; // Identity matrix

    // Function to multiply two 2x2 matrices
    auto matrixMultiply = [](long long a[2][2], long long b[2][2], long long res[2][2]) {
        long long temp[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                temp[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    temp[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        // Copy the result to the 'res' matrix
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] = temp[i][j];
            }
        }
    };

    // Function to raise the matrix to the power of n-1
    for (int i = n - 1; i > 0; i /= 2) {
        if (i % 2 != 0) {
            matrixMultiply(result, F, result); // Multiply if the power is odd
        }
        matrixMultiply(F, F, F); // Square the matrix F
    }
    return result[0][0]; // The top-left element of the result matrix is the nth Fibonacci number.
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    // Vector to store results for memoization
    vector<long long> dp(n + 1, -1);

    // Calculate and print Fibonacci numbers using different approaches
    cout << "Fibonacci Number using Recursion: " << fibonacciRecursive(n) << endl;
    cout << "Fibonacci Number using Memoization: " << fibonacciMemoization(n, dp) << endl;
    cout << "Fibonacci Number using Tabulation: " << fibonacciTabulation(n) << endl;
    cout << "Fibonacci Number using Space Optimized Tabulation: " << fibonacciSpaceOptimized(n) << endl;
    cout << "Fibonacci Number using Matrix Exponentiation: " << fibonacciMatrix(n) << endl;

    // Measure execution time for each approach
    cout << "\nExecution Times:" << endl;
    auto start = high_resolution_clock::now();
    fibonacciRecursive(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Recursion: " << duration.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    fibonacciMemoization(n, dp);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Memoization: " << duration.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    fibonacciTabulation(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Tabulation: " << duration.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    fibonacciSpaceOptimized(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Space Optimized Tabulation: " << duration.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    fibonacciMatrix(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Matrix Exponentiation: " << duration.count() << " nanoseconds" << endl;

    return 0;
}

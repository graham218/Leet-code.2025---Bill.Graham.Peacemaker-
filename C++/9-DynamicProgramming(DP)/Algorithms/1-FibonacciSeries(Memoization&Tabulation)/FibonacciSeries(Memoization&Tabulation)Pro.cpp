#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <map>
#include <cmath> // Include cmath for sqrt and pow

using namespace std;
using namespace std::chrono;

// 1. Naive Recursive Approach
//   - Directly implements the mathematical definition of the Fibonacci sequence.
//   - Extremely inefficient due to redundant calculations.
//   - Time Complexity: O(2^n)
//   - Space Complexity: O(n) (due to call stack)
long long fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// 2. Memoization (Top-Down Dynamic Programming)
//   - Stores the results of expensive function calls and reuses them when needed.
//   - Uses a table (vector) to store computed Fibonacci numbers.
//   - If a Fibonacci number has already been computed, it's returned directly from the table.
//   - Time Complexity: O(n)
//   - Space Complexity: O(n) (for the table and call stack)
long long fibonacciMemoization(int n, vector<long long>& memo) {
    if (n <= 1) {
        return n;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = fibonacciMemoization(n - 1, memo) + fibonacciMemoization(n - 2, memo);
    return memo[n];
}

// 3. Tabulation (Bottom-Up Dynamic Programming)
//   - Computes the Fibonacci numbers iteratively, starting from the base cases.
//   - Uses a table (vector) to store the computed Fibonacci numbers.
//   - Fills the table in a bottom-up manner, ensuring that the required values are already computed before they are needed.
//   - Time Complexity: O(n)
//   - Space Complexity: O(n) (for the table)
long long fibonacciTabulation(int n) {
    if (n <= 1) {
        return n;
    }
    vector<long long> table(n + 1);
    table[0] = 0;
    table[1] = 1;
    for (int i = 2; i <= n; ++i) {
        table[i] = table[i - 1] + table[i - 2];
    }
    return table[n];
}

// 4. Space-Optimized Tabulation
//   - An optimized version of the tabulation method.
//   - Instead of storing all the Fibonacci numbers in a table, it only stores the previous two numbers.
//   - This reduces the space complexity from O(n) to O(1).
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
long long fibonacciOptimized(int n) {
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

// 5. Matrix Method (Advanced - For Educational Purposes)
//    - Uses matrix exponentiation to compute the nth Fibonacci number.
//    - Based on the property that the nth Fibonacci number can be found using matrix exponentiation.
//    - This method is more complex but has a time complexity of O(log n).  Useful for very large n.
//    - Time Complexity: O(log n)
//    - Space Complexity: O(1)
void multiply(long long F[2][2], long long M[2][2]) {
    long long x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]);
    long long y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]);
    long long z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]);
    long long w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]);

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(long long F[2][2], int n) {
    if (n == 0 || n == 1)
        return;
    long long M[2][2] = {{1, 1}, {1, 0}};
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
        multiply(F, M);
}

long long fibonacciMatrix(int n) {
    long long F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}

// 6.  Using Binet's Formula (Less Practical, Good for Understanding)
//     -  Binet's formula provides a closed-form expression for the nth Fibonacci number.
//     -  It involves floating-point calculations and can have precision issues for large n.
//     -  Included for completeness and mathematical interest.  Not recommended for production.
//     -  Time Complexity: O(1)  (constant time, but with caveats)
//     -  Space Complexity: O(1)
long long fibonacciBinet(int n) {
    const double SQRT5 = sqrt(5);
    const double PHI = (1 + SQRT5) / 2;  // Golden Ratio
    const double PSI = (1 - SQRT5) / 2;  // Conjugate of the Golden Ratio

    // Handle potential issues with very large n by using logarithms.
    if (n > 70) { //  Empirical limit to avoid overflow and precision issues.
        return static_cast<long long>(round((pow(PHI, n)) / SQRT5));
    }
    return static_cast<long long>(round((pow(PHI, n) - pow(PSI, n)) / SQRT5));
}



int main() {
    int n;

    // Get the input from the user.
    cout << "Enter the value of n: ";
    cin >> n;

    if (n < 0) {
        cout << "Invalid input. n must be a non-negative integer." << endl;
        return 1;
    }

    // --- Timing and Output ---
    cout << "\nFibonacci Series for n = " << n << ":" << endl;

    // 1. Naive Recursive Approach
    auto start = high_resolution_clock::now();
    long long resultRecursive = fibonacciRecursive(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "1. Recursive:    " << resultRecursive << "  Time: " << duration.count() << " ns" << endl;

    // 2. Memoization
    start = high_resolution_clock::now();
    vector<long long> memo(n + 1, -1);
    long long resultMemoization = fibonacciMemoization(n, memo);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "2. Memoization:  " << resultMemoization << "  Time: " << duration.count() << " ns" << endl;

    // 3. Tabulation
    start = high_resolution_clock::now();
    long long resultTabulation = fibonacciTabulation(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "3. Tabulation:   " << resultTabulation << "  Time: " << duration.count() << " ns" << endl;

    // 4. Space-Optimized Tabulation
    start = high_resolution_clock::now();
    long long resultOptimized = fibonacciOptimized(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "4. Optimized:    " << resultOptimized << "  Time: " << duration.count() << " ns" << endl;

    // 5. Matrix Method
    start = high_resolution_clock::now();
    long long resultMatrix = fibonacciMatrix(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "5. Matrix:       " << resultMatrix << "  Time: " << duration.count() << " ns" << endl;

    // 6. Binet's Formula
    start = high_resolution_clock::now();
    long long resultBinet = fibonacciBinet(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "6. Binet's:      " << resultBinet << "  Time: " << duration.count() << " ns" << endl;


    cout << "\n--- Real-World Project Implementations ---" << endl;

    // 1.  Dynamic Programming for Project Scheduling (Simplified)
    //     -   In real-world project management, you might have tasks with dependencies.
    //     -   Fibonacci-like sequences can appear in simplified dependency chains.
    //     -   This example shows how DP can optimize task scheduling.
    cout << "\n1. Project Scheduling (Simplified):" << endl;
    map<int, long long> taskCompletionTimes;
    for (int i = 1; i <= n; ++i) {
      taskCompletionTimes[i] = fibonacciTabulation(i); // Assume Fibonacci for simplicity
    }
    cout << "  Task completion times (1 to " << n << "):" << endl;
    for (const auto& pair : taskCompletionTimes) {
        cout << "    Task " << pair.first << ": " << pair.second << " days" << endl;
    }

    // 2.  Dynamic Programming in Financial Modeling (Simplified)
    //     -   Consider a simplified model where investment returns in a period are related to the sum of returns in the two preceding periods (similar to Fibonacci).
    //     -   DP can help calculate cumulative returns.
    cout << "\n2. Financial Modeling (Simplified):" << endl;
    vector<long long> investmentReturns(n + 1);
    investmentReturns[0] = 0;
    investmentReturns[1] = 1;
    for (int i = 2; i <= n; ++i) {
        investmentReturns[i] = investmentReturns[i-1] + investmentReturns[i-2];
    }

    long long cumulativeReturn = 0;
    for(int i = 1; i <= n; ++i){
        cumulativeReturn += investmentReturns[i];
    }
    cout << "   Cumulative return over " << n << " periods: " << cumulativeReturn << endl;


    // 3.  Dynamic Programming in Path Planning (Simplified)
    //     -   Imagine a robot moving on a grid where the number of ways to reach a cell is the sum of the ways to reach the two cells before it (a simplified Fibonacci-like path).
    cout << "\n3. Path Planning (Simplified):" << endl;
    cout << "   Number of paths to reach destination (cell " << n << "): " << fibonacciTabulation(n) << endl;


    // 4.  Dynamic Programming in Inventory Management (Simplified)
    //     -   Consider a scenario where the optimal inventory level for a period is related to the sum of the optimal levels in the previous two periods.
    cout << "\n4. Inventory Management (Simplified):" << endl;
    vector<long long> optimalInventory(n + 1);
     optimalInventory[0] = 0;
    optimalInventory[1] = 1;
    for (int i = 2; i <= n; ++i) {
        optimalInventory[i] = optimalInventory[i - 1] + optimalInventory[i - 2];
    }
    cout << "   Optimal inventory level for period " << n << ": " << optimalInventory[n] << " units" << endl;


    // 5.  Dynamic Programming in Biological Sequence Analysis (Simplified)
    //     -   In bioinformatics, sequence alignment can use DP.  A simplified analogy:
    //     -  Assume the number of possible sequence matches at position n is related to the matches at positions n-1 and n-2.
    cout << "\n5. Biological Sequence Analysis (Simplified):" << endl;
     cout << "   Number of possible sequence matches at position " << n << ": " << fibonacciTabulation(n) << endl;

    return 0;
}

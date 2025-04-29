#include <iostream>
#include <cmath> // for the built-in pow function
#include <limits> // for checking overflow

// Function to calculate x raised to the power of n
namespace PowerFunctions {

    // 1. Iterative Approach (Handling Positive Exponents)
    // Time Complexity: O(n), Space Complexity: O(1)
    double powerIterativePositive(double x, int n) {
        if (n == 0) return 1.0;
        if (x == 0.0) return 0.0; // Handle the case where x is zero.

        double result = 1.0;
        for (int i = 0; i < n; ++i) {
            result *= x;
        }
        return result;
    }

    // 2. Iterative Approach (Handling Negative Exponents)
    // Time Complexity: O(n), Space Complexity: O(1)
    double powerIterative(double x, int n) {
        if (n == 0) return 1.0;
        if (x == 0.0) {
            return (n > 0) ? 0.0 : std::numeric_limits<double>::infinity(); // 0^n is 0 for positive n, infinity for negative n
        }

        double result = 1.0;
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                result *= x;
            }
        } else {
            for (int i = 0; i < -n; ++i) {
                result /= x;
            }
        }
        return result;
    }

    // 3. Recursive Approach
    // Time Complexity: O(n), Space Complexity: O(n) due to recursive calls
    double powerRecursive(double x, int n) {
        if (n == 0) return 1.0;
        if (x == 0.0) {
            return (n > 0) ? 0.0 : std::numeric_limits<double>::infinity();
        }

        if (n > 0) {
            return x * powerRecursive(x, n - 1);
        } else {
            return (1 / x) * powerRecursive(x, n + 1);
        }
    }

    // 4. Optimized Recursive Approach (Binary Exponentiation)
    // Time Complexity: O(log n), Space Complexity: O(log n) due to recursive calls
    double powerRecursiveOptimized(double x, int n) {
        if (n == 0) return 1.0;
        if (x == 0.0) {
            return (n > 0) ? 0.0 : std::numeric_limits<double>::infinity();
        }

        if (n < 0) {
            x = 1 / x;
            n = -n;
        }

        if (n % 2 == 0) {
            double temp = powerRecursiveOptimized(x, n / 2);
            return temp * temp;
        } else {
            return x * powerRecursiveOptimized(x, n / 2) * powerRecursiveOptimized(x, n / 2);
        }
    }

    // 5. Optimized Iterative Approach (Binary Exponentiation)
    // Time Complexity: O(log n), Space Complexity: O(1)
    double powerIterativeOptimized(double x, int n) {
        if (n == 0) return 1.0;
        if (x == 0.0) {
            return (n > 0) ? 0.0 : std::numeric_limits<double>::infinity();
        }

        if (n < 0) {
            x = 1 / x;
            n = -n;
        }

        double result = 1.0;
        while (n > 0) {
            if (n % 2 == 1) {
                result *= x;
            }
            x *= x;
            n /= 2;
        }
        return result;
    }
}

int main() {
    double x = 2.0;
    int n = 10;

    std::cout << "Testing with x = " << x << ", n = " << n << std::endl;
    std::cout << "1. Iterative (Positive): " << PowerFunctions::powerIterativePositive(x, n) << std::endl;
    std::cout << "2. Iterative: " << PowerFunctions::powerIterative(x, n) << std::endl;
    std::cout << "3. Recursive: " << PowerFunctions::powerRecursive(x, n) << std::endl;
    std::cout << "4. Optimized Recursive: " << PowerFunctions::powerRecursiveOptimized(x, n) << std::endl;
    std::cout << "5. Optimized Iterative: " << PowerFunctions::powerIterativeOptimized(x, n) << std::endl;
    std::cout << "Built-in pow: " << std::pow(x, n) << std::endl; // Compare with the built-in function

    x = 3.0;
    n = -3;
    std::cout << "\nTesting with x = " << x << ", n = " << n << std::endl;
    std::cout << "2. Iterative: " << PowerFunctions::powerIterative(x, n) << std::endl;
    std::cout << "3. Recursive: " << PowerFunctions::powerRecursive(x, n) << std::endl;
    std::cout << "4. Optimized Recursive: " << PowerFunctions::powerRecursiveOptimized(x, n) << std::endl;
    std::cout << "5. Optimized Iterative: " << PowerFunctions::powerIterativeOptimized(x, n) << std::endl;
    std::cout << "Built-in pow: " << std::pow(x, n) << std::endl;

    x = 0.0;
    n = -2;
    std::cout << "\nTesting with x = " << x << ", n = " << n << std::endl;
    std::cout << "2. Iterative: " << PowerFunctions::powerIterative(x, n) << std::endl;
    std::cout << "3. Recursive: " << PowerFunctions::powerRecursive(x, n) << std::endl;
    std::cout << "4. Optimized Recursive: " << PowerFunctions::powerRecursiveOptimized(x, n) << std::endl;
    std::cout << "5. Optimized Iterative: " << PowerFunctions::powerIterativeOptimized(x, n) << std::endl;
    std::cout << "Built-in pow: " << std::pow(x, n) << std::endl;

    x = 2.0;
    n = 0;
    std::cout << "\nTesting with x = " << x << ", n = " << n << std::endl;
    std::cout << "2. Iterative: " << PowerFunctions::powerIterative(x, n) << std::endl;
    std::cout << "3. Recursive: " << PowerFunctions::powerRecursive(x, n) << std::endl;
    std::cout << "4. Optimized Recursive: " << PowerFunctions::powerRecursiveOptimized(x, n) << std::endl;
    std::cout << "5. Optimized Iterative: " << PowerFunctions::powerIterativeOptimized(x, n) << std::endl;
    std::cout << "Built-in pow: " << std::pow(x, n) << std::endl;

    return 0;
}

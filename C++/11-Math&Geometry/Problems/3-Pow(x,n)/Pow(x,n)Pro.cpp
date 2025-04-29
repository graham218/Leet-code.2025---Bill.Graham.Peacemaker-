#include <iostream>
#include <cmath>
#include <limits> // Required for handling edge cases like overflow

// Function declarations (forward declarations)
double powerRecursive(double x, int n);
double powerIterative(double x, int n);
double powerBinaryRecursive(double x, int n);
double powerBinaryIterative(double x, int n);
double powerUsingLib(double x, int n); // Using the standard library function

// 1. Recursive Approach
//   - Basic recursive implementation.  Good for understanding recursion.
//   - Real-world use:  Simple configurations, or when a recursive style is preferred.
//   - Not the most efficient for large exponents due to function call overhead.
double powerRecursive(double x, int n) {
    if (n == 0) {
        return 1.0;
    } else if (n < 0) {
        if (x == 0) {
            return std::numeric_limits<double>::infinity(); // Handle division by zero
        }
        return 1.0 / powerRecursive(x, -n);
    } else {
        return x * powerRecursive(x, n - 1);
    }
}

// 2. Iterative Approach
//   - Uses a loop instead of recursion.  More efficient than the basic recursive approach.
//   - Real-world use: Embedded systems, where stack space is limited.  Game development for simple calculations.
double powerIterative(double x, int n) {
    double result = 1.0;
    if (n < 0) {
        if (x == 0) {
            return std::numeric_limits<double>::infinity();
        }
        x = 1.0 / x;
        n = -n;
    }
    for (int i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

// 3. Binary Exponentiation (Recursive)
//   - Exploits the property that x^n = x^(n/2) * x^(n/2) if n is even, and x * x^(n-1) if n is odd.
//   - Very efficient for large exponents (logarithmic time complexity).
//   - Real-world use: Cryptography (e.g., RSA algorithm), financial calculations.
double powerBinaryRecursive(double x, int n) {
    if (n == 0) {
        return 1.0;
    } else if (n < 0) {
        if (x == 0) {
            return std::numeric_limits<double>::infinity();
        }
        return 1.0 / powerBinaryRecursive(x, -n);
    } else if (n % 2 == 0) {
        double temp = powerBinaryRecursive(x, n / 2);
        return temp * temp;
    } else {
        return x * powerBinaryRecursive(x, n - 1);
    }
}

// 4. Binary Exponentiation (Iterative)
//   - Iterative version of binary exponentiation.  Often preferred for its efficiency and avoidance of recursion.
//   - Real-world use: High-performance computing, graphics rendering.
double powerBinaryIterative(double x, int n) {
    double result = 1.0;
    if (n < 0) {
        if (x == 0) {
            return std::numeric_limits<double>::infinity();
        }
        x = 1.0 / x;
        n = -n;
    }
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;
        }
        x *= x;
        n /= 2;
    }
    return result;
}

// 5. Using the Standard Library function
//    - Uses the std::pow function from the <cmath> library.
//    - Easiest and often the most optimized (as it's implemented by the compiler/system).
//    - Real-world use: General-purpose calculations where performance is not the *absolute* top priority, rapid prototyping.
double powerUsingLib(double x, int n) {
    return std::pow(x, n);
}

int main() {
    double x;
    int n;

    std::cout << "Enter the base (x): ";
    std::cin >> x;
    std::cout << "Enter the exponent (n): ";
    std::cin >> n;

    std::cout << "Recursive: " << powerRecursive(x, n) << std::endl;
    std::cout << "Iterative: " << powerIterative(x, n) << std::endl;
    std::cout << "Binary Recursive: " << powerBinaryRecursive(x, n) << std::endl;
    std::cout << "Binary Iterative: " << powerBinaryIterative(x, n) << std::endl;
    std::cout << "Using std::pow: " << powerUsingLib(x, n) << std::endl;

    return 0;
}

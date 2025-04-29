#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>  // For std::accumulate
#include <functional> // Add this for std::function

// Function to generate a random number within a range
long long generateRandomNumber(long long minVal, long long maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(minVal, maxVal);
    return dist(gen);
}

// Function to measure the execution time of a given function
double measureExecutionTime(const std::function<long long(long long, long long)>& func, long long base, long long exp) {
    auto start = std::chrono::high_resolution_clock::now();
    long long result = func(base, exp); // Store the result of the function call
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// 1. Iterative Binary Exponentiation (Most Common, Efficient)
//   - Concept: Exploits the binary representation of the exponent.  If the exponent's
//     ith bit is set, multiply the result by base^(2^i).
//   - Real-world use case:  Widely used in cryptography (e.g., RSA, Diffie-Hellman)
//     for efficient computation of large powers modulo a number.
long long binaryExponentiationIterative(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // If the least significant bit is 1
            result *= base;
        }
        base *= base; // Square the base
        exp /= 2;     // Right shift the exponent (divide by 2)
    }
    return result;
}

// 2. Recursive Binary Exponentiation
//   - Concept:  Recursively breaks down the exponent.
//     - If even:  base^exp = (base^(exp/2))^2
//     - If odd:   base^exp = base * (base^(exp/2))^2
//   - Real-world use case:  Can be used in compilers for optimizing power
//     calculations, though iterative is often preferred for performance.
long long binaryExponentiationRecursive(long long base, long long exp) {
    if (exp == 0) {
        return 1;
    }
    if (exp % 2 == 0) {
        long long temp = binaryExponentiationRecursive(base, exp / 2);
        return temp * temp;
    } else {
        long long temp = binaryExponentiationRecursive(base, (exp - 1) / 2);
        return base * temp * temp;
    }
}

// 3.  Exponentiation by Squaring (Optimized Recursive)
//    - Concept: A refined version of the recursive approach, often considered the classic
//      "exponentiation by squaring" algorithm. It aims to reduce redundant calculations
//      by storing the intermediate result.
//    - Real-world use case:  Used in scientific computing libraries (e.g., for
//       calculating matrix powers) and in number theory applications.
long long exponentiationBySquaring(long long base, long long exp) {
    if (exp == 0) return 1;
    if (exp == 1) return base;

    long long halfPower = exponentiationBySquaring(base, exp / 2);
    long long result = halfPower * halfPower;
    if (exp % 2 == 1) {
        result *= base;
    }
    return result;
}

// 4. Using Built-in pow() function (For Comparison and Simplicity)
//    - Concept:  Leverages the standard library's power function.
//    - Real-world use case:  When performance is not the absolute critical factor
//       and code readability/simplicity is preferred.  Good for quick calculations
//       in non-performance-sensitive parts of applications.  Often used as a
//       baseline for comparing the performance of custom implementations.
long long builtInPow(long long base, long long exp) {
    // Note: std::pow returns a double, so we cast it to long long.  This can
    // introduce slight inaccuracies for very large numbers, but it's okay for
    // demonstration and typical use.  For very large exponents, consider a
    // specialized library or implementation.  Also, std::pow is not defined
    // for negative bases and integer exponents in some cases, so be cautious
    // in its general use.  For this example, we assume positive bases.
    return static_cast<long long>(std::pow(base, exp));
}

// 5.  Left-to-Right Binary Exponentiation (Less Common, Good for Understanding)
//     - Concept:  Processes the bits of the exponent from left to right.
//     - Real-world use case:  While less common in general applications, it can be
//        useful in hardware implementations or in specific algorithms where
//        left-to-right processing is more natural.  It's also valuable for
//        educational purposes to illustrate a different approach.
long long leftToRightBinaryExponentiation(long long base, long long exp) {
    long long result = 1;
    // Find the highest set bit in the exponent
    long long mostSignificantBit = 0;
    long long temp = exp;
    while (temp > 0) {
        temp /= 2;
        mostSignificantBit++;
    }

    // Iterate through the bits from left to right
    for (long long i = mostSignificantBit - 1; i >= 0; --i) {
        result *= result; // Square the result
        if ((exp >> i) & 1) { // Check if the i-th bit is set
            result *= base;
        }
    }
    return result;
}

int main() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(1, 100); // Range for base and exponent

    // Number of test cases
    int numTestCases = 5;

    std::cout << "Running Fast Exponentiation Tests with " << numTestCases << " test cases.\n";
    std::cout << "For each test case, base and exponent are randomly generated.\n";
    std::cout << "------------------------------------------------------------------------\n";

    for (int i = 0; i < numTestCases; ++i) {
        long long base = generateRandomNumber(2, 10);   // Keep base relatively small
        long long exponent = generateRandomNumber(10, 20); // Exponent can be larger

        std::cout << "Test Case " << i + 1 << ": base = " << base << ", exponent = " << exponent << std::endl;

        // Calculate results using each method
        long long result1 = binaryExponentiationIterative(base, exponent);
        long long result2 = binaryExponentiationRecursive(base, exponent);
        long long result3 = exponentiationBySquaring(base, exponent);
        long long result4 = builtInPow(base, exponent);
        long long result5 = leftToRightBinaryExponentiation(base, exponent);

        // Measure execution times
        double time1 = measureExecutionTime(binaryExponentiationIterative, base, exponent);
        double time2 = measureExecutionTime(binaryExponentiationRecursive, base, exponent);
        double time3 = measureExecutionTime(exponentiationBySquaring, base, exponent);
        double time4 = measureExecutionTime(builtInPow, base, exponent);
        double time5 = measureExecutionTime(leftToRightBinaryExponentiation, base, exponent);

        // Print Results
        std::cout << "  Iterative Binary Exponentiation:    Result = " << result1 << ", Time = " << time1 << " seconds\n";
        std::cout << "  Recursive Binary Exponentiation:    Result = " << result2 << ", Time = " << time2 << " seconds\n";
        std::cout << "  Exponentiation by Squaring:         Result = " << result3 << ", Time = " << time3 << " seconds\n";
        std::cout << "  Built-in pow() Function:            Result = " << result4 << ", Time = " << time4 << " seconds\n";
        std::cout << "  Left-to-Right Binary Exponentiation: Result = " << result5 << ", Time = " << time5 << " seconds\n";

        // Verify correctness (optional, but good for testing)
        if (result1 != result2 || result1 != result3 || result1 != result4 || result1 != result5) {
            std::cout << "  ERROR: Results do not match!\n";
        }
        std::cout << "------------------------------------------------------------------------\n";
    }

    std::cout << "Testing complete.\n";

    return 0;
}

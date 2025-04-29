#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional> // Include the <functional> header

using namespace std;

// Function to calculate power using the naive method (iterative)
long long powerNaiveIterative(long long base, long long exp) {
    long long result = 1;
    for (long long i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// Function to calculate power using the naive method (recursive)
long long powerNaiveRecursive(long long base, long long exp) {
    if (exp == 0) {
        return 1;
    }
    return base * powerNaiveRecursive(base, exp - 1);
}

// Function to calculate power using binary exponentiation (iterative)
long long powerBinaryIterative(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // If the exponent is odd
            result *= base;
        }
        base *= base;
        exp /= 2; // Integer division by 2 (right shift)
    }
    return result;
}

// Function to calculate power using binary exponentiation (recursive)
long long powerBinaryRecursive(long long base, long long exp) {
    if (exp == 0) {
        return 1;
    }
    if (exp % 2 == 0) { // If the exponent is even
        long long temp = powerBinaryRecursive(base, exp / 2);
        return temp * temp;
    } else { // If the exponent is odd
        long long temp = powerBinaryRecursive(base, (exp - 1) / 2);
        return base * temp * temp;
    }
}

// Function to calculate power using binary exponentiation (bitwise - iterative)
long long powerBinaryBitwise(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) { // Check if the least significant bit is 1 (odd exponent)
            result *= base;
        }
        base *= base;
        exp >>= 1; // Right shift the exponent by 1 (divide by 2)
    }
    return result;
}

int main() {
    long long base, exp;
    cout << "Enter the base: ";
    cin >> base;
    cout << "Enter the exponent: ";
    cin >> exp;

    // Check for invalid input
    if (exp < 0) {
        cout << "Exponent cannot be negative. Please enter a non-negative exponent." << endl;
        return 1;
    }

    cout << "Base: " << base << ", Exponent: " << exp << endl;

    // Calculate and print results for each method
    cout << "Naive Iterative: " << powerNaiveIterative(base, exp) << endl;
    cout << "Naive Recursive: " << powerNaiveRecursive(base, exp) << endl;
    cout << "Binary Iterative: " << powerBinaryIterative(base, exp) << endl;
    cout << "Binary Recursive: " << powerBinaryRecursive(base, exp) << endl;
    cout << "Binary Bitwise: " << powerBinaryBitwise(base, exp) << endl;

    // Timing code (optional, for performance comparison)
    cout << "\nTiming Results (Optional):" << endl;
    vector<pair<string, function<long long(long long, long long)>>> functions = {
        {"Naive Iterative", powerNaiveIterative},
        {"Naive Recursive", powerNaiveRecursive},
        {"Binary Iterative", powerBinaryIterative},
        {"Binary Recursive", powerBinaryRecursive},
        {"Binary Bitwise", powerBinaryBitwise}
    };

    for (const auto& func_pair : functions) {
        auto start = chrono::high_resolution_clock::now();
        long long result = func_pair.second(base, exp); // Call the function
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << func_pair.first << ": " << duration.count() << " seconds, Result: " << result << endl;
    }
    return 0;
}

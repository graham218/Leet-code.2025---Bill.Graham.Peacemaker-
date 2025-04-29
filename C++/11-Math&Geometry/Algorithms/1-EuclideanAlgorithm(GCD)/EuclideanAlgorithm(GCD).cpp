#include <iostream>
#include <algorithm> // For std::min and std::max
#include <numeric>   // For std::gcd (C++17 and later)

// Function to calculate GCD using the standard Euclidean Algorithm (recursive)
// This is the most common and straightforward recursive implementation.
unsigned int gcd_recursive(unsigned int a, unsigned int b) {
    // Base case: if b is 0, then a is the GCD
    if (b == 0) {
        return a;
    }
    // Recursive step: reduce the problem to finding the GCD of b and the remainder of a divided by b
    return gcd_recursive(b, a % b);
}

// Function to calculate GCD using the standard Euclidean Algorithm (iterative)
// This is the iterative version of the above algorithm, often more efficient.
unsigned int gcd_iterative(unsigned int a, unsigned int b) {
    // Iterate until b becomes 0
    while (b != 0) {
        // Store the value of b
        unsigned int temp = b;
        // Calculate the new value of b (remainder of a divided by b)
        b = a % b;
        // Update a to be the previous value of b
        a = temp;
    }
    // When b is 0, a is the GCD
    return a;
}

// Function to calculate GCD using Euclidean Algorithm with subtraction (recursive)
// This version uses subtraction instead of the modulo operator.  It's less efficient
// than the standard algorithm, but demonstrates a different approach.
unsigned int gcd_subtraction_recursive(unsigned int a, unsigned int b) {
    // Base case: if a and b are equal, then that's the GCD
    if (a == b) {
        return a;
    }
    // Recursive step: subtract the smaller from the larger
    if (a > b) {
        return gcd_subtraction_recursive(a - b, b);
    } else {
        return gcd_subtraction_recursive(a, b - a);
    }
}

// Function to calculate GCD using Euclidean Algorithm with subtraction (iterative)
//  This is the iterative version of the subtraction-based method.
unsigned int gcd_subtraction_iterative(unsigned int a, unsigned int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

// Function to calculate GCD using the std::gcd from the <numeric> library (C++17 and later)
// This is the most concise way to calculate the GCD in modern C++.
unsigned int gcd_cpp17(unsigned int a, unsigned int b) {
    return std::gcd(a, b);
}

int main() {
    unsigned int num1, num2;

    // Get input from the user
    std::cout << "Enter two positive integers: ";
    std::cin >> num1 >> num2;

    // Ensure the numbers are positive.  GCD is typically defined for positive integers.
    if (num1 == 0 || num2 == 0) {
        std::cout << "GCD is undefined if both numbers are 0.  For this example, we'll treat gcd(a, 0) as a." << std::endl;
        if (num1 == 0 && num2 == 0){
             std::cout << "GCD(0, 0) = 0" << std::endl;
             return 0;
        }
    }

    // Output the GCD calculated using each method
    std::cout << "GCD(" << num1 << ", " << num2 << ") using recursive Euclidean Algorithm: " << gcd_recursive(num1, num2) << std::endl;
    std::cout << "GCD(" << num1 << ", " << num2 << ") using iterative Euclidean Algorithm: " << gcd_iterative(num1, num2) << std::endl;
    std::cout << "GCD(" << num1 << ", " << num2 << ") using recursive subtraction: " << gcd_subtraction_recursive(num1, num2) << std::endl;
    std::cout << "GCD(" << num1 << ", " << num2 << ") using iterative subtraction: " << gcd_subtraction_iterative(num1, num2) << std::endl;
    std::cout << "GCD(" << num1 << ", " << num2 << ") using std::gcd (C++17): " << gcd_cpp17(num1, num2) << std::endl;

    return 0;
}

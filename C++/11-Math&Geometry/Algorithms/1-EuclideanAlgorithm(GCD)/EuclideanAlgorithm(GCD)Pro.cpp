#include <iostream>
#include <numeric>  // For std::gcd in C++17 and later
#include <algorithm> // For std::min

// 1. Basic Recursive Euclidean Algorithm
//   - Concept: The GCD of two numbers doesn't change if the smaller number is subtracted from the larger number.
//   - Base Case: When the smaller number is 0, the larger number is the GCD.
//   - Recursion:  gcd(a, b) = gcd(b, a % b)
int recursiveGCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    return recursiveGCD(b, a % b);
}

// 2. Iterative Euclidean Algorithm
//   - Concept: Same as the recursive version, but uses a loop instead of recursion.
//   - Loop:  While b is not 0, update a and b.
int iterativeGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 3. Binary (Stein's) Algorithm
//   - Concept: More efficient than the Euclidean algorithm in some cases, especially for large numbers.  It replaces division with bitwise operations, which are often faster.
//   - Properties:
//     - If both a and b are even, gcd(a, b) = 2 * gcd(a/2, b/2).
//     - If a is even and b is odd, gcd(a, b) = gcd(a/2, b).
//     - If both a and b are odd, gcd(a, b) = gcd(|a-b|/2, min(a, b)).
int binaryGCD(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;

    int shift = 0;
    while (((a | b) & 1) == 0) { // While both a and b are even
        a >>= 1;
        b >>= 1;
        shift++;
    }

    while ((a & 1) == 0) { // While a is even
        a >>= 1;
    }

    do {
        while ((b & 1) == 0) { // While b is even
            b >>= 1;
        }
        if (a > b) {
            std::swap(a, b);
        }
        b -= a;
    } while (b != 0);

    return a << shift;
}

// 4. Using the C++ Standard Library (C++17 and later)
//    - Concept:  The C++ standard library provides a built-in function for calculating the GCD.
//    - Function: std::gcd(a, b)
int cppLibraryGCD(int a, int b) {
    return std::gcd(a, b);
}

// 5. Extended Euclidean Algorithm (Calculates GCD and coefficients x, y such that ax + by = gcd(a, b))
//    - Concept:  Finds not only the GCD of a and b, but also integers x and y that satisfy Bézout's identity.
//    - Useful for:  Finding modular inverses, solving linear Diophantine equations.
// Returns: A tuple (gcd, x, y)
std::tuple<int, int, int> extendedEuclideanAlgorithm(int a, int b) {
    if (b == 0) {
        return std::make_tuple(a, 1, 0);
    }
    int gcd, x1, y1;
    std::tie(gcd, x1, y1) = extendedEuclideanAlgorithm(b, a % b);
    int x = y1;
    int y = x1 - (a / b) * y1;
    return std::make_tuple(gcd, x, y);
}

int main() {
    int num1, num2;

    std::cout << "Enter two integers: ";
    std::cin >> num1 >> num2;

    if (num1 < 0 || num2 < 0) {
        std::cout << "Please enter non-negative integers." << std::endl;
        return 1;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Numbers: " << num1 << ", " << num2 << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 1. Recursive GCD
    int gcd1 = recursiveGCD(num1, num2);
    std::cout << "Recursive GCD: " << gcd1 << std::endl;

    // 2. Iterative GCD
    int gcd2 = iterativeGCD(num1, num2);
    std::cout << "Iterative GCD: " << gcd2 << std::endl;

    // 3. Binary GCD
    int gcd3 = binaryGCD(num1, num2);
    std::cout << "Binary GCD: " << gcd3 << std::endl;

    // 4. C++ Library GCD
    int gcd4 = cppLibraryGCD(num1, num2);
    std::cout << "C++ Library GCD: " << gcd4 << std::endl;

   // 5. Extended Euclidean Algorithm
    int gcd5, x, y;
    std::tie(gcd5, x, y) = extendedEuclideanAlgorithm(num1, num2);
    std::cout << "Extended Euclidean GCD: " << gcd5 << std::endl;
    std::cout << "Coefficients (x, y): (" << x << ", " << y << ")" << std::endl;
    std::cout << num1 << "*" << x << " + " << num2 << "*" << y << " = " << gcd5 << std::endl; // Verify Bézout's identity

    std::cout << "----------------------------------------" << std::endl;

    // Real-world examples:

    // 1. Simplifying Fractions:  Use the GCD to reduce a fraction to its simplest form.
    int numerator = 48;
    int denominator = 60;
    int commonDivisor = cppLibraryGCD(numerator, denominator); // Using the library function
    std::cout << "\nSimplifying Fraction Example:" << std::endl;
    std::cout << "Original Fraction: " << numerator << "/" << denominator << std::endl;
    std::cout << "Simplified Fraction: " << numerator / commonDivisor << "/" << denominator / commonDivisor << std::endl;

    // 2. Finding the Least Common Multiple (LCM):  LCM(a, b) = (a * b) / GCD(a, b)
     int a = 12;
     int b = 18;
     int gcd_ab = cppLibraryGCD(a,b);
     int lcm = (a * b) / gcd_ab;
     std::cout << "\nLCM Example:" << std::endl;
     std::cout << "LCM of " << a << " and " << b << " is: " << lcm << std::endl;

    // 3. Cryptography (Modular Inverse): The Extended Euclidean Algorithm is used to find the modular inverse of a number, which is essential in RSA cryptography.
    int a_crypto = 17;
    int m_crypto = 26; // Modulo
    std::tie(gcd5, x, y) = extendedEuclideanAlgorithm(a_crypto, m_crypto);
    if (gcd5 == 1) {
        // x is the modular inverse of a modulo m
        int modularInverse = (x % m_crypto + m_crypto) % m_crypto; // Ensure positive result
        std::cout << "\nModular Inverse Example (Cryptography):" << std::endl;
        std::cout << "Modular inverse of " << a_crypto << " modulo " << m_crypto << " is: " << modularInverse << std::endl;
        std::cout << a_crypto << " * " << modularInverse << " mod " << m_crypto << " = " << (a_crypto * modularInverse) % m_crypto << std::endl; //check
    } else {
        std::cout << "\nModular Inverse Example (Cryptography):" << std::endl;
        std::cout << a_crypto << " and " << m_crypto << " are not coprime, so the modular inverse does not exist." << std::endl;
    }

     // 4. Scheduling problem:
    int task1_period = 6;  // Task 1 repeats every 6 units of time
    int task2_period = 8;  // Task 2 repeats every 8 units of time
    int gcd_schedule = cppLibraryGCD(task1_period, task2_period);
    int lcm_schedule = (task1_period * task2_period) / gcd_schedule;

    std::cout << "\nScheduling Problem Example:" << std::endl;
    std::cout << "Task 1 period: " << task1_period << " units, Task 2 period: " << task2_period << " units" << std::endl;
    std::cout << "The tasks will coincide every " << lcm_schedule << " units of time." << std::endl;

    // 5. Image Processing (Resizing with Integer Ratios)
    int originalWidth = 800;
    int originalHeight = 600;
    int newWidth = 600;
    int newHeight = 450;

    int widthGCD = cppLibraryGCD(originalWidth, newWidth);
    int heightGCD = cppLibraryGCD(originalHeight, newHeight);

    std::cout << "\nImage Processing Example:" << std::endl;
    std::cout << "Original dimensions: " << originalWidth << "x" << originalHeight << std::endl;
    std::cout << "New dimensions: " << newWidth << "x" << newHeight << std::endl;
    std::cout << "Scaling ratio: " << originalWidth / widthGCD << ":" << newWidth / widthGCD
              << " (width), " << originalHeight / heightGCD << ":" << newHeight / heightGCD << " (height)" << std::endl;

    return 0;
}


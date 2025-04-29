#include <iostream>
#include <cmath>
#include <bitset> // Required for approach 5

using namespace std;

// Function to check if a number is a power of 2 using the subtraction and bitwise AND method.
// This is generally the most efficient and widely used method.
bool isPowerOfTwo_Approach1(unsigned int n) {
    if (n == 0) return false; // 0 is not a power of 2
    return (n & (n - 1)) == 0;
    // Explanation:
    // A power of 2 in binary has only one bit set (e.g., 8 = 1000, 16 = 10000).
    // Subtracting 1 from a power of 2 will result in a number with all bits set up to the original '1' bit (e.g., 8-1 = 7 = 0111, 16-1 = 15 = 01111).
    // The bitwise AND of these two numbers will be 0.
    // For example:
    //  n = 8 (1000 in binary)
    //  n - 1 = 7 (0111 in binary)
    //  n & (n - 1) = 1000 & 0111 = 0000 = 0
    // If n is not a power of 2, the result will not be 0.
    // For example:
    //  n = 6 (0110 in binary)
    //  n - 1 = 5 (0101 in binary)
    //  n & (n - 1) = 0110 & 0101 = 0100 != 0
}

// Function to check if a number is a power of 2 by counting the set bits.
// This approach iterates through the bits of the number.
bool isPowerOfTwo_Approach2(unsigned int n) {
    if (n == 0) return false;
    int count = 0;
    while (n > 0) {
        count += (n & 1); // Check the least significant bit
        n >>= 1;             // Right shift n by 1
    }
    return count == 1;
    // Explanation:
    // A power of 2 has only one bit set to 1. This method counts the number of set bits.
    // If the count is exactly 1, then the number is a power of 2.
}

// Function to check if a number is a power of 2 using the log2 function.
// This approach uses floating-point operations, which can sometimes have precision issues.
bool isPowerOfTwo_Approach3(unsigned int n) {
    if (n == 0) return false;
    double logValue = log2(n);
    return (ceil(logValue) == floor(logValue));
    // Explanation:
    // The base-2 logarithm of a power of 2 is an integer (e.g., log2(8) = 3, log2(16) = 4).
    // We calculate the log base 2 of the number. If the ceiling and floor of the result are equal,
    // then the number is a power of 2.  We use ceil and floor to handle potential
    // floating-point inaccuracies.
}

// Function to check if a number is a power of 2 using repeated division.
// This approach is straightforward but can be less efficient for large numbers.
bool isPowerOfTwo_Approach4(unsigned int n) {
    if (n == 0) return false;
    if (n == 1) return true; // 1 is a power of 2 (2^0)
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
    // Explanation:
    // We repeatedly divide the number by 2. If the number is a power of 2,
    // it will eventually become 1 after repeated division. If at any point the
    // remainder is not 0, or the final result is not 1, it's not a power of 2.
}

// Function to check if a number is a power of 2 using bitset.
bool isPowerOfTwo_Approach5(unsigned int n) {
    if (n == 0) return false;
    bitset<32> b(n); // Assuming 32-bit unsigned int
    return b.count() == 1;
    // Explanation:
    //  We convert the unsigned integer to a bitset.  The bitset's count() method
    //  returns the number of set bits.  A power of two has only one set bit.
}

int main() {
    unsigned int number;

    cout << "Enter a non-negative integer: ";
    cin >> number;

    cout << number << " is ";
    if (isPowerOfTwo_Approach1(number)) {
        cout << "a power of 2 (Approach 1: Bitwise AND)" << endl;
    } else {
        cout << "not a power of 2 (Approach 1: Bitwise AND)" << endl;
    }

    cout << number << " is ";
    if (isPowerOfTwo_Approach2(number)) {
        cout << "a power of 2 (Approach 2: Counting Set Bits)" << endl;
    } else {
        cout << "not a power of 2 (Approach 2: Counting Set Bits)" << endl;
    }

    cout << number << " is ";
    if (isPowerOfTwo_Approach3(number)) {
        cout << "a power of 2 (Approach 3: Log2)" << endl;
    } else {
        cout << "not a power of 2 (Approach 3: Log2)" << endl;
    }

    cout << number << " is ";
    if (isPowerOfTwo_Approach4(number)) {
        cout << "a power of 2 (Approach 4: Repeated Division)" << endl;
    } else {
        cout << "not a power of 2 (Approach 4: Repeated Division)" << endl;
    }

    cout << number << " is ";
    if (isPowerOfTwo_Approach5(number)) {
        cout << "a power of 2 (Approach 5: Bitset)" << endl;
    } else {
        cout << "not a power of 2 (Approach 5: Bitset)" << endl;
    }

    return 0;
}

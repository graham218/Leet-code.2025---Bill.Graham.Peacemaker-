#include <iostream>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to check if a number is a power of two using the division method.
// Real-world application: Determining if a resource allocation can be evenly divided in a system.
bool isPowerOfTwo_Division(int n) {
    if (n <= 0) {
        return false;
    }
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
}

// Function to check if a number is a power of two using the bitwise AND method.
// Real-world application: Optimizing memory allocation by ensuring chunks are powers of two.
bool isPowerOfTwo_BitwiseAND(int n) {
    if (n <= 0) {
        return false;
    }
    return (n & (n - 1)) == 0;
}

// Function to check if a number is a power of two using logarithms.
// Real-world application:  Verifying input constraints in algorithms, like FFT (Fast Fourier Transform) which often require power-of-two sizes.
bool isPowerOfTwo_Logarithm(int n) {
    if (n <= 0) {
        return false;
    }
    // Use log2, and check if the result is an integer.  Handles potential floating-point inaccuracies.
    double logResult = log2(n);
    return (logResult == floor(logResult));
}

// Function to check if a number is a power of two by counting set bits.
// Real-world application: Error detection in data transmission, where power-of-two patterns might indicate specific error states.
bool isPowerOfTwo_CountBits(int n) {
    if (n <= 0) {
        return false;
    }
    int count = 0;
    // Brian Kernighan's Algorithm to count set bits efficiently.
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count == 1;
}

// Function to check if a number is a power of two using bitset.
// Real-world application: Analyzing binary data, where power-of-two patterns might have special meaning (e.g., network addressing).
bool isPowerOfTwo_Bitset(int n) {
    if (n <= 0) {
        return false;
    }
    return bitset<32>(n).count() == 1;
    //Alternative
    // return std::bitset<std::numeric_limits<unsigned long>::digits>(n).count() == 1;
}

int main() {
    int num;

    cout << "Enter an integer: ";
    cin >> num;

    cout << num << " is ";
    if (num > 0 && ((num & (num - 1)) == 0))
    {
        cout << "a power of 2." << endl;
    }
    else
    {
        cout << "not a power of 2." << endl;
    }

    cout << "\nChecking if " << num << " is a power of two using different methods:\n";

    cout << "Division Method: " << (isPowerOfTwo_Division(num) ? "Yes" : "No") << endl;
    cout << "Bitwise AND Method: " << (isPowerOfTwo_BitwiseAND(num) ? "Yes" : "No") << endl;
    cout << "Logarithm Method: " << (isPowerOfTwo_Logarithm(num) ? "Yes" : "No") << endl;
    cout << "Counting Set Bits Method: " << (isPowerOfTwo_CountBits(num) ? "Yes" : "No") << endl;
    cout << "Bitset Method: " << (isPowerOfTwo_Bitset(num) ? "Yes" : "No") << endl;

    return 0;
}

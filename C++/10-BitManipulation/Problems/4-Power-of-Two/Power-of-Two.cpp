#include <iostream>
#include <cmath>
#include <bitset> // Required for approach 5

using namespace std;

// Function to check if a number is a power of two using method 1: Repeated Division
bool isPowerOfTwo_Method1(int n) {
    if (n <= 0) {
        return false; // Powers of two are always positive
    }
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
}

// Function to check if a number is a power of two using method 2: Using Logarithm
bool isPowerOfTwo_Method2(int n) {
    if (n <= 0) {
        return false;
    }
    // log2(n) should be an integer for powers of 2.  We check using floor and ceil.
    double logValue = log2(n);
    return (ceil(logValue) == floor(logValue));
}

// Function to check if a number is a power of two using method 3: Bitwise AND
bool isPowerOfTwo_Method3(int n) {
    if (n <= 0) {
        return false;
    }
    // A power of two has only one bit set.  n & (n-1) clears that bit.
    // If n is a power of two, the result is 0.
    return (n & (n - 1)) == 0;
}

// Function to check if a number is a power of two using method 4: Bitwise AND and check against zero
bool isPowerOfTwo_Method4(int n) {
    if (n <= 0)
        return false;
    return !(n & (n - 1));
}

// Function to check if a number is a power of two using method 5: Counting set bits
bool isPowerOfTwo_Method5(int n) {
    if (n <= 0) {
        return false;
    }
    // std::bitset<32>(n).count() returns the number of set bits in the binary representation of n.
    // For a power of two, there should be only one set bit.
    return std::bitset<32>(n).count() == 1;
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    cout << "Method 1: Repeated Division: ";
    if (isPowerOfTwo_Method1(num)) {
        cout << num << " is a power of two." << endl;
    } else {
        cout << num << " is not a power of two." << endl;
    }

    cout << "Method 2: Using Logarithm: ";
    if (isPowerOfTwo_Method2(num)) {
        cout << num << " is a power of two." << endl;
    } else {
        cout << num << " is not a power of two." << endl;
    }

    cout << "Method 3: Bitwise AND: ";
    if (isPowerOfTwo_Method3(num)) {
        cout << num << " is a power of two." << endl;
    } else {
        cout << num << " is not a power of two." << endl;
    }

    cout << "Method 4: Bitwise AND and check against zero: ";
    if (isPowerOfTwo_Method4(num)) {
        cout << num << " is a power of two." << endl;
    } else {
        cout << num << " is not a power of two." << endl;
    }

    cout << "Method 5: Counting set bits: ";
    if (isPowerOfTwo_Method5(num)) {
        cout << num << " is a power of two." << endl;
    } else {
        cout << num << " is not a power of two." << endl;
    }

    return 0;
}

#include <iostream>
#include <cmath>
#include <bitset> // Required for approach 5

using namespace std;

// Function to check if a number is a power of 2 using approach 1: Iterative Division
bool isPowerOfTwo_Approach1(int n) {
    if (n <= 0) {
        return false; // 0 and negative numbers are not powers of 2
    }
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
}

// Function to check if a number is a power of 2 using approach 2: Using Logarithm
bool isPowerOfTwo_Approach2(int n) {
    if (n <= 0) {
        return false;
    }
    // log2(n) should be an integer for powers of 2.
    double logValue = log2(n);
    return (logValue == floor(logValue)); // Check if the logarithm is an integer
}

// Function to check if a number is a power of 2 using approach 3: Bitwise AND
bool isPowerOfTwo_Approach3(int n) {
    if (n <= 0) {
        return false;
    }
    // A power of 2 has only one bit set.  n & (n-1) clears the least significant bit.
    // If n is a power of 2, then n & (n-1) will be 0.
    return (n & (n - 1)) == 0;
}

// Function to check if a number is a power of 2 using approach 4:  Check only one bit is set
bool isPowerOfTwo_Approach4(int n) {
     if (n <= 0) {
        return false;
    }
    int count = 0;
    for(int i = 0; i < 32; ++i){ // Assuming 32 bit integer
        if((n >> i) & 1){
            count++;
        }
    }
    return count == 1;
}

// Function to check if a number is a power of 2 using approach 5: Using bitset
bool isPowerOfTwo_Approach5(int n) {
    if (n <= 0) {
        return false;
    }
    bitset<32> b(n); // Convert n to a 32-bit bitset
    return b.count() == 1; // Check if only one bit is set
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    cout << "Checking if " << num << " is a power of 2 using different approaches:" << endl;

    cout << "Approach 1: Iterative Division: ";
    if (isPowerOfTwo_Approach1(num)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << "Approach 2: Using Logarithm: ";
    if (isPowerOfTwo_Approach2(num)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << "Approach 3: Bitwise AND: ";
    if (isPowerOfTwo_Approach3(num)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << "Approach 4: Counting Set Bits: ";
    if (isPowerOfTwo_Approach4(num)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << "Approach 5: Using bitset: ";
    if (isPowerOfTwo_Approach5(num)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Required for std::accumulate

using namespace std;

// Approach 1: Check if the nth bit is set (1) or not (0)
bool isNthBitSet_Approach1(int num, int n) {
    // Left shift 1 by n-1 positions.  If n = 1, shift by 0.
    int mask = 1 << (n - 1);
    // Perform bitwise AND. If the nth bit is 1, the result is non-zero.
    return (num & mask) != 0;
}

// Approach 2: Set the nth bit of a number to 1
int setNthBit_Approach2(int num, int n) {
    // Left shift 1 by n-1 positions
    int mask = 1 << (n - 1);
    // Perform bitwise OR to set the nth bit.
    return num | mask;
}

// Approach 3: Clear the nth bit of a number to 0
int clearNthBit_Approach3(int num, int n) {
    // Left shift 1 by n-1 positions
    int mask = 1 << (n - 1);
    // Invert the mask.  All bits are 1 except the nth bit, which is 0.
    mask = ~mask;
    // Perform bitwise AND to clear the nth bit.
    return num & mask;
}

// Approach 4: Toggle the nth bit of a number
int toggleNthBit_Approach4(int num, int n) {
    // Left shift 1 by n-1 positions
    int mask = 1 << (n - 1);
    // Perform bitwise XOR to toggle the nth bit.
    return num ^ mask;
}

// Approach 5: Count the number of set bits (1s) in a number (Brian Kernighan's Algorithm)
int countSetBits_Approach5(int num) {
    int count = 0;
    while (num != 0) {
        // Subtracting 1 from a number flips the least significant set bit to 0,
        // and sets all the bits to the right of it to 1.
        // ANDing with the original number clears the least significant set bit.
        num &= (num - 1);
        count++;
    }
    return count;
}

// Function to print the binary representation of a number (for better visualization)
void printBinary(int num) {
    if (num == 0) {
        cout << "0";
        return;
    }
    vector<int> bits;
    while (num > 0) {
        bits.push_back(num % 2); // Get the least significant bit
        num /= 2;             // Right shift (integer division)
    }
    reverse(bits.begin(), bits.end()); // Reverse to get correct order
    for (int bit : bits) {
        cout << bit;
    }
}

int main() {
    int num = 10;       // Example number (binary 1010)
    int n = 3;          // Example bit position (we'll work with the 3rd bit)

    cout << "Number: " << num << " (Binary: ";
    printBinary(num);
    cout << ")" << endl;

    // Approach 1: Check if the nth bit is set
    cout << "\nApproach 1: Check if the " << n << "th bit is set: ";
    if (isNthBitSet_Approach1(num, n)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    // Approach 2: Set the nth bit
    int num2 = num; // Create a copy to avoid modifying the original
    num2 = setNthBit_Approach2(num2, n);
    cout << "Approach 2: Set the " << n << "th bit: " << num2 << " (Binary: ";
    printBinary(num2);
    cout << ")" << endl;

    // Approach 3: Clear the nth bit
    int num3 = num; // Create a copy
    num3 = clearNthBit_Approach3(num3, n);
    cout << "Approach 3: Clear the " << n << "th bit: " << num3 << " (Binary: ";
    printBinary(num3);
    cout << ")" << endl;

    // Approach 4: Toggle the nth bit
    int num4 = num; // Create a copy
    num4 = toggleNthBit_Approach4(num4, n);
    cout << "Approach 4: Toggle the " << n << "th bit: " << num4 << " (Binary: ";
    printBinary(num4);
    cout << ")" << endl;

    // Approach 5: Count set bits
    cout << "Approach 5: Count set bits: " << countSetBits_Approach5(num) << endl;

    return 0;
}

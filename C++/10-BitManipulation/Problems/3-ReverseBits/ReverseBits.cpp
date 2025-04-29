#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits> // For INT_MAX

using namespace std;

// Function to print the binary representation of an unsigned integer
void printBinary(unsigned int n) {
    for (int i = 31; i >= 0; --i) {
        cout << ((n >> i) & 1);
    }
    cout << endl;
}

// Approach 1: Iterative Bit Swapping
// - Iterates through the bits of the number, swapping the i-th bit from the left with the i-th bit from the right.
// - Uses bitwise AND and OR operations to extract and set bits.
unsigned int reverseBits_Iterative(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; ++i) {
        if ((n >> i) & 1) { // Check if the i-th bit is set
            result |= (1 << (31 - i)); // Set the (31-i)-th bit in the result
        }
    }
    return result;
}

// Approach 2: Using bitset and string reversal
// - Converts the unsigned integer to a bitset.
// - Converts the bitset to a string, reverses the string, and converts it back to a bitset.
// - Finally, converts the bitset to an unsigned integer.
unsigned int reverseBits_Bitset(unsigned int n) {
    bitset<32> bs(n); // Convert the integer to a 32-bit bitset
    string s = bs.to_string(); // Convert the bitset to a string
    reverse(s.begin(), s.end()); // Reverse the string
    bitset<32> reversed_bs(s); // Create a bitset from the reversed string
    return reversed_bs.to_ulong(); // Convert the reversed bitset to an unsigned integer
}

// Approach 3: Divide and Conquer (Optimized)
// - Uses a divide-and-conquer strategy to reverse the bits in a more efficient way.
// - It performs a series of bitwise operations to swap groups of bits.
unsigned int reverseBits_DivideAndConquer(unsigned int n) {
    n = (n >> 16) | (n << 16); // Swap 16-bit halves
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8); // Swap bytes
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4); // Swap 4-bit groups
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2); // Swap 2-bit groups
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1); // Swap adjacent bits
    return n;
}

// Approach 4: Using bitwise operations and a loop
// - This method uses a while loop and bitwise operations to reverse the bits.
// - It extracts the least significant bit of the input number and adds it to the result.
unsigned int reverseBits_BitwiseLoop(unsigned int n) {
    unsigned int result = 0;
    int count = 32;
    while (count--) {
        result <<= 1; // Shift the result to the left by 1
        result |= (n & 1); // Add the least significant bit of n to result
        n >>= 1;       // Shift n to the right by 1
    }
    return result;
}

// Approach 5: Lookup Table
// - Pre-computes the reversed values for all possible 8-bit sequences.
// - Stores these reversed values in a lookup table.
// - Splits the 32-bit input into four 8-bit chunks, looks up the reversed value for each chunk in the table, and combines the results.
unsigned int reverseBits_LookupTable(unsigned int n) {
    // Create a lookup table for reversed 8-bit values
    static unsigned char reversed[256];
    static bool initialized = false;

    if (!initialized) {
        for (int i = 0; i < 256; ++i) {
            unsigned char value = i;
            unsigned char reverse = 0;
            for (int j = 0; j < 8; ++j) {
                if ((value >> j) & 1) {
                    reverse |= (1 << (7 - j));
                }
            }
            reversed[i] = reverse;
        }
        initialized = true;
    }
    // Split the input into 8-bit chunks and use the lookup table
    return  (reversed[n & 0xFF]) << 24 |
            (reversed[(n >> 8) & 0xFF]) << 16 |
            (reversed[(n >> 16) & 0xFF]) << 8 |
            (reversed[(n >> 24) & 0xFF]);
}

int main() {
    unsigned int num = 432615932; // Example input
    cout << "Original Number:     " << num << endl;
    cout << "Binary Representation: ";
    printBinary(num);

    cout << "\nReversed Bits (Iterative):             " << reverseBits_Iterative(num) << endl;
    cout << "Binary Representation: ";
    printBinary(reverseBits_Iterative(num));

    cout << "\nReversed Bits (Bitset):                " << reverseBits_Bitset(num) << endl;
    cout << "Binary Representation: ";
    printBinary(reverseBits_Bitset(num));

    cout << "\nReversed Bits (Divide and Conquer):    " << reverseBits_DivideAndConquer(num) << endl;
    cout << "Binary Representation: ";
    printBinary(reverseBits_DivideAndConquer(num));

    cout << "\nReversed Bits (Bitwise Loop):          " << reverseBits_BitwiseLoop(num) << endl;
    cout << "Binary Representation: ";
    printBinary(reverseBits_BitwiseLoop(num));

    cout << "\nReversed Bits (Lookup Table):          " << reverseBits_LookupTable(num) << endl;
    cout << "Binary Representation: ";
    printBinary(reverseBits_LookupTable(num));


    return 0;
}

#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits> // For UINT_MAX

// Function to print the binary representation of an unsigned integer
void printBinary(unsigned int n) {
    std::bitset<32> b(n); // Use 32 bits for consistency
    std::cout << b.to_string() << std::endl;
}

// 1. Iterative Approach with Bitwise Operations
//   - Reverses bits one by one.
//   - Real-world use case: Implementing a custom communication protocol where bit order is reversed.
unsigned int reverseBitsIterative(unsigned int n) {
    unsigned int reversed = 0;
    for (int i = 0; i < 32; ++i) { // Iterate through all 32 bits
        // Get the rightmost bit of n
        unsigned int bit = (n >> i) & 1;
        // Place the bit at the correct position in reversed
        reversed |= (bit << (31 - i));
    }
    return reversed;
}

// 2. Using std::bitset and string manipulation
//   - Converts the integer to a bitset, reverses the string representation, and converts it back to an integer.
//   - Real-world use case:  Processing binary data from a file or network stream where the bit order is incorrect.
unsigned int reverseBitsBitset(unsigned int n) {
    std::bitset<32> b(n);
    std::string s = b.to_string();
    std::reverse(s.begin(), s.end());
    std::bitset<32> reversed_b(s);
    return reversed_b.to_ulong();
}

// 3. Divide and Conquer Approach
//   - Efficiently reverses bits by swapping groups of bits.
//   - Real-world use case: Optimizing low-level graphics rendering or signal processing algorithms.
unsigned int reverseBitsDivideAndConquer(unsigned int n) {
    n = (n >> 16) | (n << 16);
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
    return n;
}

// 4. Lookup Table Approach
//   - Uses a precomputed table to reverse the bits of each byte, then combines the results.
//   - Real-world use case: High-performance networking applications where bit reversal needs to be extremely fast.
unsigned int reverseBitsLookupTable(unsigned int n) {
    // Precompute the reversed bits for each byte (0-255)
    static unsigned char reversedByte[256];
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < 256; ++i) {
            unsigned char reversed = 0;
            for (int j = 0; j < 8; ++j) {
                if ((i >> j) & 1) {
                    reversed |= (1 << (7 - j));
                }
            }
            reversedByte[i] = reversed;
        }
        initialized = true;
    }

    // Split the integer into bytes and use the lookup table
    return (reversedByte[n & 0xFF] << 24) |
           (reversedByte[(n >> 8) & 0xFF] << 16) |
           (reversedByte[(n >> 16) & 0xFF] << 8) |
           (reversedByte[(n >> 24) & 0xFF]);
}

// 5.  Using the intrinsic _byteswap_ulong (if available, e.g., on x86)
//   - Leverages compiler-specific intrinsic functions for optimized bit reversal.
//   - Real-world use case:  Optimizing performance-critical code for specific hardware architectures.
unsigned int reverseBitsIntrinsic(unsigned int n) {
#ifdef _MSC_VER // For Microsoft Visual C++
    return _byteswap_ulong(n);
#elif defined(__GNUC__) || defined(__clang__) // For GCC and Clang
    return __builtin_bswap32(n);
#else
    // If no intrinsic is available, fall back to a portable method (e.g., iterative)
    return reverseBitsIterative(n); // Or any other method
#endif
}

int main() {
    unsigned int num = 43261596; // Example input: 00000010100101000001111010011100 in binary

    std::cout << "Original Number: " << num << std::endl;
    printBinary(num); // Print original binary

    std::cout << "\nReversed Bits (Iterative): " << reverseBitsIterative(num) << std::endl;
    printBinary(reverseBitsIterative(num));
    std::cout << "Reversed Bits (Bitset): " << reverseBitsBitset(num) << std::endl;
    printBinary(reverseBitsBitset(num));
    std::cout << "Reversed Bits (Divide and Conquer): " << reverseBitsDivideAndConquer(num) << std::endl;
    printBinary(reverseBitsDivideAndConquer(num));
    std::cout << "Reversed Bits (Lookup Table): " << reverseBitsLookupTable(num) << std::endl;
    printBinary(reverseBitsLookupTable(num));
    std::cout << "Reversed Bits (Intrinsic): " << reverseBitsIntrinsic(num) << std::endl;
    printBinary(reverseBitsIntrinsic(num));

    return 0;
}

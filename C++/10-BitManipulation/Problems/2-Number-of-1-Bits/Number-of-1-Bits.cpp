#include <iostream>
#include <bitset> // Required for std::bitset

// Function to count the number of 1 bits in an integer using the naive approach.
// This approach iterates through each bit of the integer and checks if it is 1.
//
// Time Complexity: O(n), where n is the number of bits in the integer.
// Space Complexity: O(1).
int countSetBitsNaive(int n) {
    int count = 0;
    // Iterate through the bits of the integer.  We could also use a loop
    // while (n != 0), and check the least significant bit with (n & 1).
    for (int i = 0; i < 32; ++i) { // Assuming 32-bit integer.
        if ((n >> i) & 1) { // Check if the i-th bit is 1.
            count++;
        }
    }
    return count;
}

// Function to count the number of 1 bits using the Brian Kernighan's Algorithm.
// This algorithm works by repeatedly flipping the least significant 1 bit of the number to 0.
// The loop continues until the number becomes 0.  Each flip reduces the number
// of set bits by one, so the number of iterations is equal to the number of 1s.
//
// Time Complexity: O(k), where k is the number of 1 bits in the integer.
// Space Complexity: O(1).
int countSetBitsBrianKernighan(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Clear the least significant set bit.
        count++;
    }
    return count;
}

// Function to count the number of 1 bits using bitset.
// std::bitset is a class template that represents a fixed-size sequence of N bits.
//
// Time Complexity: O(n), where n is the number of bits in the integer.
// Space Complexity: O(n), where n is the number of bits in the integer.  Though the
//                  space used by std::bitset is generally small and fixed.
int countSetBitsBitset(int n) {
    std::bitset<32> b(n); // Convert the integer to a 32-bit bitset.
    return b.count();       // Use the count() method to get the number of set bits.
}

// Function to count set bits using a lookup table.  This approach is fast
// but uses extra memory.  We create a table storing the number of set bits
// for each possible byte value (0-255).  Then we process the integer byte by byte.
//
// Time Complexity: O(1).  It looks like O(n), but it is actually O(32/8) = O(4), so O(1)
// Space Complexity: O(256) = O(1).  The lookup table size is constant.
int countSetBitsLookupTable(int n) {
    // Create a lookup table to store the number of set bits for each byte (0-255).
    static int lookup[256]; // Static to ensure it's initialized only once.
    static bool initialized = false; // Flag to check if the table is initialized.

    if (!initialized) {
        for (int i = 0; i < 256; ++i) {
            lookup[i] = countSetBitsNaive(i); // Can use any of the other methods here.
        }
        initialized = true;
    }

    // Split the integer into bytes and use the lookup table.
    int count = 0;
    count += lookup[n & 0xFF];       // Count set bits in the first byte (least significant).
    count += lookup[(n >> 8) & 0xFF];  // Count set bits in the second byte.
    count += lookup[(n >> 16) & 0xFF]; // Count set bits in the third byte.
    count += lookup[(n >> 24) & 0xFF]; // Count set bits in the fourth byte (most significant).
    return count;
}

//  Function to count set bits using SIMD (Single Instruction, Multiple Data) instructions.
//  This approach uses  compiler intrinsics (_mm_popcnt_u32) which may not be available on all compilers.
//  It's generally the fastest method when available.
//
//  Time Complexity: O(1)
//  Space Complexity: O(1)
#ifdef __popcnt__  // Check if the __popcnt__ instruction is supported.
#include <immintrin.h> // Include the necessary header for _mm_popcnt_u32
int countSetBitsSIMD(int n) {
    return _mm_popcnt_u32(n);
}
#else
int countSetBitsSIMD(int n) {
    std::cout << "SIMD instruction not supported.  Using naive method instead.\n";
    return countSetBitsNaive(n); // Fallback to naive if SIMD is not available.
}
#endif

int main() {
    int num = 0xFFF; // Example number (15 as hexadecimal, which is 1111 in binary)
    //int num = 7; // Example number

    std::cout << "Number: " << num << std::endl;
    std::cout << "Number of 1 bits (Naive): " << countSetBitsNaive(num) << std::endl;
    std::cout << "Number of 1 bits (Brian Kernighan): " << countSetBitsBrianKernighan(num) << std::endl;
    std::cout << "Number of 1 bits (Bitset): " << countSetBitsBitset(num) << std::endl;
    std::cout << "Number of 1 bits (Lookup Table): " << countSetBitsLookupTable(num) << std::endl;
    std::cout << "Number of 1 bits (SIMD): " << countSetBitsSIMD(num) << std::endl;

    return 0;
}

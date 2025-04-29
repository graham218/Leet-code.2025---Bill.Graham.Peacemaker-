#include <iostream>
#include <bitset> // Required for std::bitset
#include <algorithm> // Required for std::count

// Function to count the number of 1 bits in an unsigned integer using the naive approach.
//
// Real-world application: This method is straightforward and can be used in simple scenarios
// where performance is not critical, such as basic data validation or when dealing with
// small sets of integers.  For example, you might use it in a logging system to count
// how many error flags are set in a status code.
int countSetBitsNaive(unsigned int n) {
    int count = 0;
    while (n != 0) {
        if (n & 1) // Check the least significant bit
            count++;
        n >>= 1;     // Right shift n by 1 (divide by 2)
    }
    return count;
}

// Function to count the number of 1 bits using Brian Kernighan's Algorithm.
//
// Real-world application: This is a very efficient method and is often used in performance-critical
// applications.  For example, it could be used in a high-performance computing application
// to count the number of active bits in a bitmask representing the state of a parallel process.
// It's also useful in embedded systems where minimizing the number of operations is crucial.
int countSetBitsBrianKernighan(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Clear the least significant bit
        count++;
    }
    return count;
}

// Function to count the number of 1 bits using the STL's bitset.
//
// Real-world application:  The `std::bitset` is useful when you have a fixed number of bits,
// known at compile time.  For example, if you're working with a specific hardware register
// that is always 32 bits, you can use `std::bitset<32>`.  This approach can improve
// code readability and may offer some performance benefits due to compiler optimizations
// for fixed-size bitsets.  It's often used in hardware simulations or when interfacing
// with hardware devices.
int countSetBitsBitset(unsigned int n) {
    std::bitset<32> b(n); // Assuming 32-bit unsigned int.  Use the correct size.
    return b.count();
}

// Function to count the number of 1 bits using the STL's count algorithm.
//
// Real-world application: This approach is more generic and can be used with any sequence
// of bits, not just those represented by an unsigned integer.  For example, you could
// use it to count the number of set bits in a large array of bytes representing a bitmap
// image.  While it might not be the most efficient for single integers, it's valuable
// when working with more complex data structures.
int countSetBitsSTLCount(unsigned int n) {
    std::bitset<32> b(n); // Again, assuming 32-bit unsigned int
    //std::count requires a range.  bitset doesn't directly provide iterators.
    //We use to_string() to convert it to a string, which *does* have iterators.
    std::string s = b.to_string();
    return std::count(s.begin(), s.end(), '1');
}

// Function to count the number of 1 bits using a lookup table.
//
// Real-world application: This method is extremely fast, especially when the same values are
// being processed repeatedly.  It's commonly used in high-performance networking applications,
// such as calculating checksums or processing network packets, where speed is paramount.
// It's also used in image processing and video encoding.  The trade-off is increased memory
// usage for the lookup table.  For 32-bit integers, you can often use a table that stores the
// count of set bits for each possible byte value (0-255).
int countSetBitsLookupTable(unsigned int n) {
    // Pre-compute the number of set bits for each byte (0-255)
    static int lookup[256]; // Static to ensure it's initialized only once
    static bool initialized = false;

    if (!initialized) {
        for (int i = 0; i < 256; ++i) {
            lookup[i] = countSetBitsNaive(i); // Can use any of the other methods here
        }
        initialized = true;
    }

    // Split the 32-bit integer into 4 bytes and use the lookup table
    return lookup[n & 0xFF] +            // Least significant byte
           lookup[(n >> 8) & 0xFF] +     // Second byte
           lookup[(n >> 16) & 0xFF] +    // Third byte
           lookup[(n >> 24) & 0xFF];    // Most significant byte
}

int main() {
    unsigned int num = 0b10110101101; // Example number (717 in decimal)

    std::cout << "Number: " << num << " (Binary: " << std::bitset<32>(num) << ")" << std::endl;

    std::cout << "Naive Method: " << countSetBitsNaive(num) << std::endl;
    std::cout << "Brian Kernighan's Algorithm: " << countSetBitsBrianKernighan(num) << std::endl;
    std::cout << "STL bitset: " << countSetBitsBitset(num) << std::endl;
    std::cout << "STL count: " << countSetBitsSTLCount(num) << std::endl;
    std::cout << "Lookup Table: " << countSetBitsLookupTable(num) << std::endl;

    return 0;
}

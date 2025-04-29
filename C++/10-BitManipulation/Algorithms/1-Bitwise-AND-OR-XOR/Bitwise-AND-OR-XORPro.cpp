#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset> // Required for some examples

// Function to print the binary representation of a number (for clarity)
void printBinary(unsigned int num) {
    std::cout << std::bitset<32>(num).to_string() << std::endl; // Use 32 bits for consistency
}

// 1. Checking if a number is a power of 2 using Bitwise AND
bool isPowerOfTwo(unsigned int n) {
    if (n == 0) return false; // 0 is not a power of 2
    // A power of 2 has only one bit set.  n & (n-1) clears the least significant bit.
    return (n & (n - 1)) == 0;
}

// 2. Counting the number of set bits in an integer using Bitwise AND
int countSetBits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Clear the least significant set bit
        count++;
    }
    return count;
}

// 3. Setting, Clearing, and Toggling a specific bit using Bitwise OR, AND, and XOR
void manipulateBit(unsigned int& num, int position, char operation) {
    // position is assumed to be 0-indexed, counting from the rightmost bit.
    unsigned int mask = 1 << position; // Create a mask with a 1 at the desired position.

    std::cout << "Original number: " << num << "  Binary: "; printBinary(num);

    switch (operation) {
        case 'S': // Set the bit (force it to 1) using OR
            num |= mask;
            std::cout << "Set bit " << position << ": " << num << "  Binary: "; printBinary(num);
            break;
        case 'C': // Clear the bit (force it to 0) using AND with the complement of the mask
            num &= (~mask);
            std::cout << "Cleared bit " << position << ": " << num << "  Binary: "; printBinary(num);
            break;
        case 'T': // Toggle the bit (flip it) using XOR
            num ^= mask;
            std::cout << "Toggled bit " << position << ": " << num << "  Binary: "; printBinary(num);
            break;
        default:
            std::cout << "Invalid operation. Use 'S' (Set), 'C' (Clear), or 'T' (Toggle)." << std::endl;
    }
}

// 4. Swapping two numbers without using a temporary variable using Bitwise XOR
void swapNumbers(int& a, int& b) {
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    a = a ^ b; // a now holds the XOR of the original a and b
    b = a ^ b; // b now holds the original a (because a ^ b ^ b = a)
    a = a ^ b; // a now holds the original b (because a ^ b ^ a = b)
    std::cout << "After swap:  a = " << a << ", b = " << b << std::endl;
}

// 5.  Efficiently calculating the parity of a number (whether it has an odd or even number of set bits) using Bitwise XOR
//    Parity is 1 if the number of set bits is odd, 0 if even
int calculateParity(unsigned int n) {
    int parity = 0;
    while (n) {
        parity ^= (n & 1); // XOR with the least significant bit
        n >>= 1;             // Right shift to process the next bit
    }
    return parity;
    // More efficient approach (Brian Kernighan's Algorithm):
    // int parity = 0;
    // while (n) {
    //   parity ^= 1;
    //   n &= (n - 1);
    // }
    // return parity;
}

int main() {
    // 1. Check if a number is a power of 2
    std::cout << "\n--- 1. Power of 2 ---" << std::endl;
    unsigned int num1 = 16;
    std::cout << num1 << " is a power of 2: " << (isPowerOfTwo(num1) ? "true" : "false") << std::endl; //true
    unsigned int num2 = 22;
    std::cout << num2 << " is a power of 2: " << (isPowerOfTwo(num2) ? "true" : "false") << std::endl; //false

    // 2. Count set bits
    std::cout << "\n--- 2. Count Set Bits ---" << std::endl;
    unsigned int num3 = 0b101101; // Binary literal for 45 (32 + 8 + 4 + 1)
    std::cout << "Number of set bits in " << num3 << " (binary 101101): " << countSetBits(num3) << std::endl; //3

    // 3. Set, Clear, and Toggle bits
    std::cout << "\n--- 3. Set, Clear, Toggle Bits ---" << std::endl;
    unsigned int num4 = 10; // Binary: 1010
    manipulateBit(num4, 1, 'S'); // Set bit 1:  1010 becomes 1010 | 0010 = 1010  (12) -> 1010 | 0010 = 1010
    manipulateBit(num4, 3, 'C'); // Clear bit 3: 1010 becomes 1010 & ~1000 = 0010 (2) -> 1010 & 0111 = 0010
    manipulateBit(num4, 2, 'T'); // Toggle bit 2: 0010 becomes 0010 ^ 0100 = 0110 (6) -> 0010 ^ 0100 = 0110
    manipulateBit(num4, 0, 'X'); // Invalid operation

    // 4. Swap numbers
    std::cout << "\n--- 4. Swap Numbers ---" << std::endl;
    int a = 5;
    int b = 10;
    swapNumbers(a, b);
    std::cout << "After swapping: a = " << a << ", b = " << b << std::endl;

   // 5. Calculate Parity
    std::cout << "\n--- 5. Calculate Parity ---" << std::endl;
    unsigned int num5 = 7; // Binary: 0111, Parity: 1 (odd number of set bits)
    unsigned int num6 = 10; // Binary 1010, Parity: 0 (even number of set bits)
    std::cout << "Parity of " << num5 << " (binary 0111): " << calculateParity(num5) << std::endl;
    std::cout << "Parity of " << num6 << " (binary 1010): " << calculateParity(num6) << std::endl;

    return 0;
}

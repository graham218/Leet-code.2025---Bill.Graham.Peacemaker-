#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric> // For std::iota

// Approach 1: Basic Sieve of Eratosthenes
// - Creates a boolean array representing numbers up to n.
// - Iterates through the array, marking multiples of primes as non-prime.
// - Time Complexity: O(n log log n)
// - Space Complexity: O(n)
std::vector<bool> sieveOfEratosthenes_basic(int n) {
    if (n <= 1) return {}; // Handle edge case

    std::vector<bool> isPrime(n + 1, true); // Initialize all numbers as prime
    isPrime[0] = isPrime[1] = false;       // 0 and 1 are not prime

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false; // Mark multiples of p as not prime
            }
        }
    }
    return isPrime;
}

// Approach 2: Sieve with Space Optimization
// - Optimizes space by only considering odd numbers after 2.
// - Maps an odd number 'x' to index (x-3)/2.
// - Time Complexity: O(n log log n)
// - Space Complexity: O(n/2)
std::vector<bool> sieveOfEratosthenes_spaceOpt(int n) {
    if (n <= 1) return {};

    if (n == 2) return {false, true}; // Special case for n=2

    std::vector<bool> isPrime((n - 1) / 2, true); // Only store odd numbers' status
    // Index i in isPrime represents the number 2*i + 3.
    // For example:
    // i = 0 represents 3
    // i = 1 represents 5
    // i = 2 represents 7, and so on.

    for (int p = 3; p * p <= n; p += 2) {
        // p starts at 3 and increments by 2 (only odd numbers)
        int pIndex = (p - 3) / 2; // Index of p in isPrime
        if (isPrime[pIndex]) {
            // Important: Mark multiples of p, starting from p*p.
            // Need to calculate the index of p*p.
            // p*p can be represented as (2*pIndex + 3) * (2*pIndex + 3)
            // Let's expand that: 4*pIndex*pIndex + 12*pIndex + 9
            // We want to find the index of this number in our isPrime array,
            // which stores only odd numbers.  So we subtract 3 and divide by 2:
            //  (4*pIndex*pIndex + 12*pIndex + 9 - 3) / 2
            // = 2*pIndex*pIndex + 6*pIndex + 3
            int startMultipleIndex = 2 * pIndex * pIndex + 6 * pIndex + 3;
            for (int i = startMultipleIndex; i < (n - 1) / 2; i += p) {
                isPrime[i] = false;
            }
        }
    }

    std::vector<bool> result(n + 1, false); // Create the result vector
    result[2] = true;                     // 2 is prime
    for (int i = 0; i < (n - 1) / 2; ++i) {
        if (isPrime[i]) {
            result[2 * i + 3] = true; // Map back from index to number and set prime status
        }
    }
    return result;
}

// Approach 3: Sieve with Bitset (Space Optimized)
// - Uses a bitset (represented by a vector of unsigned integers) to store prime status.
// - Each bit represents a number; this significantly reduces memory usage.
// - Time Complexity: O(n log log n)
// - Space Complexity: O(n/64) - much lower than approaches 1 and 2
std::vector<bool> sieveOfEratosthenes_bitset(int n) {
    if (n <= 1) return {};

    std::vector<unsigned int> bitset((n / 64) + 1, 0xFFFFFFFF); // Initialize all bits to 1 (prime)
    //  -  n/64:  Integer division, gives the number of 64-bit integers needed.
    //  -  +1   :  Ensures we have enough space.
    //  - 0xFFFFFFFF:  Represents a 64-bit integer with all bits set to 1.

    // Helper functions to set, check, and clear bits
    auto getBit = [&](int index) {
        int wordIndex = index / 32; //  Which 32-bit unsigned int contains the bit
        int bitOffset = index % 32; //  Which bit within that unsigned int
        return (bitset[wordIndex] >> bitOffset) & 1;
        //  -  Right shift the word by bitOffset.
        //  -  & 1:  Bitwise AND with 1 to isolate the least significant bit
    };

    auto clearBit = [&](int index) {
        int wordIndex = index / 32;
        int bitOffset = index % 32;
        bitset[wordIndex] &= ~(1U << bitOffset);
        //  - 1U:  Unsigned 1.
        //  - 1U << bitOffset:  Left shift 1 by bitOffset (creates a mask with a 1 at the bit to clear).
        //  - ~:    Bitwise NOT (inverts the mask).
        //  - &=:  Bitwise AND assignment (clears the bit).
    };

    // 0 and 1 are not prime.  bitset represents numbers starting from 0.
    clearBit(0);
    clearBit(1);

    for (int p = 2; p * p <= n; ++p) {
        if (getBit(p)) { // if p is prime
            for (int i = p * p; i <= n; i += p) {
                clearBit(i); // Mark multiples of p as not prime
            }
        }
    }

    std::vector<bool> result(n + 1, false);
    for (int i = 0; i <= n; ++i) {
        if (getBit(i)) {
            result[i] = true;
        }
    }
    return result;
}

// Approach 4: Sieve of Atkin
// - A faster, but more complex, algorithm for finding prime numbers up to a specified integer.
// - It's more efficient than the Sieve of Eratosthenes for larger values of n.
// - Time Complexity: O(n)
// - Space Complexity: O(n)
std::vector<bool> sieveOfAtkin(int n) {
    if (n <= 1) return {};
    std::vector<bool> isPrime(n + 1, false); // Initialize all as non-prime

    // Handle special cases for 2 and 3
    if (n > 1) isPrime[2] = true;
    if (n > 2) isPrime[3] = true;

    for (int x = 1; x * x <= n; ++x) {
        for (int y = 1; y * y <= n; ++y) {
            // Main part of Sieve of Atkin algorithm
            int num1 = (4 * x * x) + (y * y);
            if (num1 <= n && (num1 % 12 == 1 || num1 % 12 == 5))
                isPrime[num1] = !isPrime[num1]; // Toggle the primality of num1

            int num2 = (3 * x * x) + (y * y);
            if (num2 <= n && num2 % 12 == 7)
                isPrime[num2] = !isPrime[num2]; // Toggle the primality of num2

            int num3 = (3 * x * x) - (y * y);
            if (x > y && num3 <= n && num3 % 12 == 11)
                isPrime[num3] = !isPrime[num3]; // Toggle the primality of num3
        }
    }

    // Eliminate squares of primes
    for (int p = 5; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p * p)
                isPrime[i] = false;
        }
    }
    return isPrime;
}

// Approach 5: Segmented Sieve of Eratosthenes
// - Divides the range [0, n] into smaller segments to reduce memory usage.
// - Useful when n is very large.
// - Time Complexity: O(n log log n)
// - Space Complexity: O(sqrt(n))
void segmentedSieve(int n) {
    if (n <= 1) return;

    int limit = std::sqrt(n);
    std::vector<bool> isPrime(limit + 1, true); // Primes up to sqrt(n)
    std::vector<int> prime; // Stores primes found

    // Sieve of Eratosthenes to find primes up to sqrt(n)
    for (int p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }
    for (int p = 2; p <= limit; ++p) {
        if (isPrime[p])
            prime.push_back(p); // Store the primes
    }

    int segmentSize = limit; // Size of each segment
    for (int low = limit + 1; low <= n; low += segmentSize) {
        int high = std::min(low + segmentSize - 1, n); // Last number in this segment
        std::vector<bool> segment(segmentSize + 1, true); // Represent [low, high]

        for (int p : prime) {
            int firstMultiple = (low / p) * p; // Find the first multiple of p >= low
            if (firstMultiple < low)
                firstMultiple += p; // Ensure it's within the segment

            for (int i = firstMultiple; i <= high; i += p)
                segment[i - low] = false; // Mark multiples of p as non-prime
        }

        // Print primes in current segment
        for (int i = low; i <= high; ++i) {
            if (segment[i - low])
                std::cout << i << " ";
        }
    }
}

int main() {
    int n = 100;

    std::cout << "Sieve of Eratosthenes (Basic):" << std::endl;
    std::vector<bool> primes1 = sieveOfEratosthenes_basic(n);
    for (int i = 0; i <= n; ++i) {
        if (primes1[i])
            std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Sieve of Eratosthenes (Space Optimized):" << std::endl;
    std::vector<bool> primes2 = sieveOfEratosthenes_spaceOpt(n);
    for (int i = 0; i <= n; ++i) {
        if (primes2[i])
            std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Sieve of Eratosthenes (Bitset):" << std::endl;
    std::vector<bool> primes3 = sieveOfEratosthenes_bitset(n);
    for (int i = 0; i <= n; ++i) {
        if (primes3[i])
            std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Sieve of Atkin:" << std::endl;
    std::vector<bool> primes4 = sieveOfAtkin(n);
    for (int i = 0; i <= n; ++i) {
        if (primes4[i])
            std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Segmented Sieve of Eratosthenes:" << std::endl;
    segmentedSieve(n);
    std::cout << std::endl;

    return 0;
}

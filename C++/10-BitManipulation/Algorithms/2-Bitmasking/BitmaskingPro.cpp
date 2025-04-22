/*
Bit Manipulation & Bitmasking Techniques with Real-World Project Implementations
*/

console.log("Bit Manipulation and Bitmasking Techniques");

// ----------------------------------------------------------------------
// 1. Checking if a number is a power of 2
// ----------------------------------------------------------------------
console.log("\n1. Checking if a number is a power of 2:");
// Project Implementation:  Efficiently check status flags in embedded systems.
// Explanation: A power of 2 has only one bit set.  n & (n-1) clears the least significant bit.  If the result is 0, then n is a power of 2.

function isPowerOfTwo(n) {
  if (n <= 0) {
    return false;
  }
  return (n & (n - 1)) === 0;
}

let num1 = 16;
let num2 = 21;
let num3 = 0;

console.log(`${num1} is a power of 2: ${isPowerOfTwo(num1)}`); // true
console.log(`${num2} is a power of 2: ${isPowerOfTwo(num2)}`); // false
console.log(`${num3} is a power of 2: ${isPowerOfTwo(num3)}`); // false

// ----------------------------------------------------------------------
// 2. Setting, clearing, and toggling bits
// ----------------------------------------------------------------------
console.log("\n2. Setting, clearing, and toggling bits:");
// Project Implementation:  Managing user permissions in a web application.
// Explanation:  Use bitwise OR to set a bit, bitwise AND with the complement to clear, and bitwise XOR to toggle.

function setBit(n, k) {
  return n | (1 << k);
}

function clearBit(n, k) {
  return n & ~(1 << k);
}

function toggleBit(n, k) {
  return n ^ (1 << k);
}

let permissions = 0; // 0000 (Initially no permissions)
const READ = 1;    // 0001
const WRITE = 2;   // 0010
const EXECUTE = 4; // 0100

// Set READ and WRITE permissions
permissions = setBit(permissions, 0); // Set READ (bit 0)
permissions = setBit(permissions, 1); // Set WRITE (bit 1)
console.log("Permissions after setting READ and WRITE:", permissions.toString(2)); // 0011 (3 in decimal)

// Clear WRITE permission
permissions = clearBit(permissions, 1);
console.log("Permissions after clearing WRITE:", permissions.toString(2));     // 0001 (1 in decimal)

// Toggle EXECUTE permission
permissions = toggleBit(permissions, 2);
console.log("Permissions after toggling EXECUTE:", permissions.toString(2));   // 0101 (5 in decimal)

permissions = toggleBit(permissions, 2);
console.log("Permissions after toggling EXECUTE again:", permissions.toString(2));   // 0001 (1 in decimal)

// ----------------------------------------------------------------------
// 3. Checking if a specific bit is set
// ----------------------------------------------------------------------
console.log("\n3. Checking if a specific bit is set:");
// Project Implementation:  Checking hardware status flags in device drivers.
// Explanation:  Left shift 1 by k and use bitwise AND to isolate the kth bit.

function isBitSet(n, k) {
  return (n & (1 << k)) !== 0;
}

let status = 10; // 1010 in binary

console.log(`Is bit 0 set in ${status}: ${isBitSet(status, 0)}`); // false
console.log(`Is bit 1 set in ${status}: ${isBitSet(status, 1)}`); // true
console.log(`Is bit 2 set in ${status}: ${isBitSet(status, 2)}`); // false
console.log(`Is bit 3 set in ${status}: ${isBitSet(status, 3)}`); // true

// ----------------------------------------------------------------------
// 4. Counting set bits (Brian Kernighan's Algorithm)
// ----------------------------------------------------------------------
console.log("\n4. Counting set bits (Brian Kernighan's Algorithm):");
// Project Implementation:  Calculating the Hamming weight of data for error detection.
// Explanation:  Efficiently counts set bits by repeatedly clearing the least significant set bit until n becomes 0.

function countSetBits(n) {
  let count = 0;
  while (n !== 0) {
    n &= (n - 1);
    count++;
  }
  return count;
}

let value1 = 7;  // 111 in binary
let value2 = 12; // 1100 in binary
let value3 = 0;

console.log(`Number of set bits in ${value1}: ${countSetBits(value1)}`); // 3
console.log(`Number of set bits in ${value2}: ${countSetBits(value2)}`); // 2
console.log(`Number of set bits in ${value3}: ${countSetBits(value3)}`); // 0

// ----------------------------------------------------------------------
// 5. Finding the first set bit from right
// ----------------------------------------------------------------------
console.log("\n5. Finding the first set bit from right:");
// Project Implementation: Implementing a priority queue.
// Explanation:  Subtracting 1 from a number, and XORing it with the original number isolates the rightmost set bit.

function getFirstSetBitPosition(n) {
    if (n === 0) return 0;
    return Math.log2(n & -n) + 1;
}

let number1 = 10; // Binary 1010
let number2 = 18; // Binary 10010
let number3 = 0;    // Binary 0

console.log(`First set bit position in ${number1}: ${getFirstSetBitPosition(number1)}`); // 2
console.log(`First set bit position in ${number2}: ${getFirstSetBitPosition(number2)}`); // 2
console.log(`First set bit position in ${number3}: ${getFirstSetBitPosition(number3)}`); // 0

/*
Bit Manipulation - Bitmasking Techniques in JavaScript

Bitmasking is a technique that uses binary representation of numbers to efficiently represent and manipulate sets of boolean values.  Each bit in an integer can represent the presence or absence of an element in a set.

Here are 5 common bitmasking operations with examples:
*/

// 1. Check if the nth bit is set (1)
function isNthBitSet(number, n) {
  // Left shift 1 by n bits (0-based index) and perform a bitwise AND with the number.
  // If the nth bit is 1, the result will be non-zero (truthy).
  // If the nth bit is 0, the result will be 0 (falsy).
  const mask = 1 << n;
  return (number & mask) !== 0;
}

// 2. Set the nth bit to 1
function setNthBit(number, n) {
  // Left shift 1 by n bits and perform a bitwise OR with the number.
  // This will set the nth bit to 1, leaving other bits unchanged.
  const mask = 1 << n;
  return number | mask;
}

// 3. Clear the nth bit (set to 0)
function clearNthBit(number, n) {
  // Left shift 1 by n bits, invert it using the bitwise NOT operator (~),
  // and perform a bitwise AND with the number.
  // This will clear the nth bit to 0, leaving other bits unchanged.
  const mask = ~(1 << n);
  return number & mask;
}

// 4. Toggle the nth bit (flip 0 to 1, or 1 to 0)
function toggleNthBit(number, n) {
  // Left shift 1 by n bits and perform a bitwise XOR with the number.
  // XOR with 1 toggles the bit.
  const mask = 1 << n;
  return number ^ mask;
}

// 5. Get the rightmost set bit (lowest 1 bit)
function getRightmostSetBit(number) {
    //  x & -x isolates the rightmost set bit.
    //  For example:
    //  number = 101100 (44)
    // -number = 010100 (-44)  (two's complement)
    // number & -number = 000100 (4)
    return number & -number;
}

// Example Usage and Output
function main() {
  let num = 42; // Binary: 00101010
  const n = 3;

  console.log(`Original Number: ${num} (Binary: ${num.toString(2)})`);
  console.log(`----------------------------------------`);

  // Check if the 3rd bit is set (remember, index starts at 0)
  const isSet = isNthBitSet(num, n);
  console.log(`Is the ${n}th bit set? ${isSet} (Binary: ${num.toString(2)})`);

  // Set the 3rd bit
  num = setNthBit(num, n);
  console.log(`After setting the ${n}th bit: ${num} (Binary: ${num.toString(2)})`);

  // Clear the 3rd bit
  num = clearNthBit(num, n);
  console.log(`After clearing the ${n}th bit: ${num} (Binary: ${num.toString(2)})`);

  num = 42; //reset to 42
  // Toggle the 3rd bit
  num = toggleNthBit(num, n);
  console.log(`After toggling the ${n}th bit: ${num} (Binary: ${num.toString(2)})`);

  num = 40; // 101000
  const rightmostBit = getRightmostSetBit(num);
  console.log(`Rightmost set bit of ${num}: ${rightmostBit} (Binary: ${rightmostBit.toString(2)})`);
}

main();

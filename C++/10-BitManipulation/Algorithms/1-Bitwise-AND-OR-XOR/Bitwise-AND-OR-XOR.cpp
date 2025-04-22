/*
 * Bit Manipulation: Bitwise AND, OR, XOR
 *
 * This code demonstrates bitwise AND, OR, and XOR operations in JavaScript
 * using several approaches.  It's designed to illustrate the basic
 * concepts and how these operators work at the binary level.
 *
 */

// Utility function to display numbers in binary format (for clarity)
function toBinary(num) {
  // Use a fixed number of bits (e.g., 8) for better visualization
  return (num >>> 0).toString(2).padStart(8, '0');
}

// Example numbers
let a = 5;  // Binary: 00000101
let b = 3;  // Binary: 00000011

console.log(`Initial values:`);
console.log(`a = ${a} (Binary: ${toBinary(a)})`);
console.log(`b = ${b} (Binary: ${toBinary(b)})`);
console.log(`----------------------------------------`);

// Approach 1: Basic Bitwise AND, OR, XOR
// Demonstrates the most straightforward use of the operators.
console.log(`Approach 1: Basic Operations`);
let resultAND1 = a & b;
let resultOR1 = a | b;
let resultXOR1 = a ^ b;

console.log(`a & b (AND): ${resultAND1} (Binary: ${toBinary(resultAND1)})`); // 00000001 = 1
console.log(`a | b (OR):  ${resultOR1}  (Binary: ${toBinary(resultOR1)})`);  // 00000111 = 7
console.log(`a ^ b (XOR): ${resultXOR1} (Binary: ${toBinary(resultXOR1)})`); // 00000110 = 6
console.log(`----------------------------------------`);

// Approach 2: Using Variables Directly in Output
// Shows that you don't need to assign to intermediate variables.
console.log(`Approach 2: Direct Calculation in Output`);
console.log(`a & b (AND): ${a & b} (Binary: ${toBinary(a & b)})`);
console.log(`a | b (OR):  ${a | b} (Binary: ${toBinary(a | b)})`);
console.log(`a ^ b (XOR): ${a ^ b} (Binary: ${toBinary(a ^ b)})`);
console.log(`----------------------------------------`);

// Approach 3:  Bitwise AND for Checking Even/Odd
//  A common use case of bitwise AND is to check if a number is even or odd.
//  The least significant bit is 0 for even numbers and 1 for odd numbers.
console.log(`Approach 3: Check for Even/Odd using Bitwise AND`);
let num = 7;
console.log(`${num} is ${ (num & 1) === 0 ? 'even' : 'odd'}`); // Output: odd

num = 12;
console.log(`${num} is ${ (num & 1) === 0 ? 'even' : 'odd'}`); // Output: even
console.log(`----------------------------------------`);

// Approach 4: Bitwise OR to set a specific bit
// Using bitwise OR to set a specific bit (e.g., setting the 3rd bit to 1).
console.log(`Approach 4: Setting a Bit using Bitwise OR`);
let value = 10; // Binary: 00001010
let bitToSet = 2; // We want to set the 2nd bit (from the right, 0-indexed)

// Create a mask with a 1 at the position we want to set
let mask = 1 << bitToSet; // Binary: 00000100

let newValue = value | mask;
console.log(`Original value: ${value} (Binary: ${toBinary(value)})`);
console.log(`Mask:           ${mask} (Binary: ${toBinary(mask)})`);
console.log(`New value:      ${newValue} (Binary: ${toBinary(newValue)})`); // Binary: 00001110 (14)
console.log(`----------------------------------------`);

// Approach 5: Bitwise XOR to toggle a bit
// Using bitwise XOR to toggle a specific bit.
console.log(`Approach 5: Toggling a Bit using Bitwise XOR`);
let valueToToggle = 15; // Binary: 00001111
let bitToToggle = 3;

let toggleMask = 1 << bitToToggle; // Binary: 00001000
let toggledValue = valueToToggle ^ toggleMask;

console.log(`Original value:  ${valueToToggle} (Binary: ${toBinary(valueToToggle)})`);
console.log(`Toggle Mask:     ${toggleMask} (Binary: ${toBinary(toggleMask)})`);
console.log(`Toggled value:   ${toggledValue} (Binary: ${toBinary(toggledValue)})`); // Binary: 00000111 (7)

// Toggle it again to show it goes back to the original value
let toggledAgain = toggledValue ^ toggleMask;
console.log(`Toggled again: ${toggledAgain} (Binary: ${toBinary(toggledAgain)})`);
console.log(`----------------------------------------`);

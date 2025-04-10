// Fast Exponentiation (Exponentiation by Squaring)

/*
Fast exponentiation is a technique to efficiently calculate a^b, where a is the base and b is the exponent.  It reduces the number of multiplications required, especially when b is large.  This is crucial in many areas, including cryptography, scientific computing, and computer graphics.

Here are 5 different approaches, with explanations of their real-world project implementations:
*/

// 1. Recursive Approach

/*
Explanation:
   - The most intuitive approach.
   - If the exponent b is even, we can calculate a^(b/2) and square the result.
   - If the exponent b is odd, we calculate a * a^(b-1).
   - The base case is when b is 0, where the result is 1.

Real-world project implementation:
   - Implementing cryptographic algorithms like RSA.  Modular exponentiation is a core operation in RSA, and a recursive approach (or its iterative equivalent) can be used.
*/
function fastExponentiationRecursive(base, exponent) {
  if (exponent === 0) {
    return 1;
  }

  if (exponent % 2 === 0) {
    const temp = fastExponentiationRecursive(base, exponent / 2);
    return temp * temp;
  } else {
    return base * fastExponentiationRecursive(base, exponent - 1);
  }
}

// 2. Iterative Approach

/*
Explanation:
    - A non-recursive version of the fast exponentiation algorithm.
    - Uses a while loop to iterate through the bits of the exponent.
    - If the current bit is 1, multiply the result by the current power of the base.
    - Square the base in each iteration.

Real-world project implementation:
    - Optimizing numerical calculations in scientific simulations.  For example, calculating powers of matrices or complex numbers in physics simulations.  Iterative methods are often preferred for performance reasons.
*/
function fastExponentiationIterative(base, exponent) {
  let result = 1;
  let currentBase = base;
  let currentExponent = exponent;

  while (currentExponent > 0) {
    if (currentExponent % 2 === 1) {
      result = result * currentBase;
    }
    currentBase = currentBase * currentBase;
    currentExponent = Math.floor(currentExponent / 2);
  }
  return result;
}

// 3. Bitwise Approach

/*
Explanation:
    - An optimized iterative approach that uses bitwise operators.
    - Uses the right shift operator (>>) to divide the exponent by 2.
    - Uses the bitwise AND operator (&) to check if the least significant bit of the exponent is 1.

Real-world project implementation:
   - Implementing efficient algorithms in embedded systems.  Bitwise operations are very efficient at the hardware level, making this approach suitable for resource-constrained devices.
*/
function fastExponentiationBitwise(base, exponent) {
  let result = 1;
  let currentBase = base;
  let currentExponent = exponent;

  while (currentExponent > 0) {
    if (currentExponent & 1) { // Check if the last bit is 1
      result *= currentBase;
    }
    currentBase *= currentBase;
    currentExponent >>= 1; // Right shift (equivalent to dividing by 2 and discarding remainder)
  }
  return result;
}

// 4. Modular Exponentiation

/*
Explanation:
    - Calculates (base^exponent) % modulus.
    - Important in cryptography to prevent overflow when dealing with large numbers.
    - The modulus operation is applied in each step to keep the intermediate results small.

Real-world project implementation:
    - Used in cryptography, especially in Diffie-Hellman key exchange and RSA encryption.  Modular exponentiation is essential for secure communication over insecure channels.
*/
function modularExponentiation(base, exponent, modulus) {
  let result = 1;
  let currentBase = base % modulus; // Important to reduce base if it is larger than modulus
  let currentExponent = exponent;

  while (currentExponent > 0) {
    if (currentExponent % 2 === 1) {
      result = (result * currentBase) % modulus;
    }
    currentBase = (currentBase * currentBase) % modulus;
    currentExponent = Math.floor(currentExponent / 2);
  }
  return result;
}

// 5. Using Math.pow() (for comparison and simple cases)
/*
Explanation:
    - JavaScript's built-in Math.pow() function.
    - Generally efficient for smaller exponents, but can be less efficient for very large exponents compared to the above algorithms.
    - Not suitable for modular exponentiation without additional steps.

Real-world project implementation:
    -  Calculating growth rates, compound interest, or other mathematical formulas in financial applications or data analysis tools.  When performance is not critical and the exponents are within a reasonable range, Math.pow() is convenient.
*/
function fastExponentiationMathPow(base, exponent) {
  return Math.pow(base, exponent);
}



// Example usage and console logs:
const base = 2;
const exponent = 10;
const modulus = 1000000007; // A large prime number, often used in modular arithmetic

console.log(`Base: ${base}, Exponent: ${exponent}, Modulus: ${modulus}`);
console.log("--------------------------------------------------");

console.log("1. Recursive Approach:", fastExponentiationRecursive(base, exponent));
console.log("2. Iterative Approach:", fastExponentiationIterative(base, exponent));
console.log("3. Bitwise Approach:", fastExponentiationBitwise(base, exponent));
console.log("4. Modular Exponentiation:", modularExponentiation(base, exponent, modulus));
console.log("5. Using Math.pow():", fastExponentiationMathPow(base, exponent));

// Example with a larger exponent to demonstrate efficiency
const largeBase = 3;
const largeExponent = 1000000;
console.log(`\nBase: ${largeBase}, Exponent: ${largeExponent}`);
console.log("--------------------------------------------------");
console.log("1. Recursive Approach (Large Exponent):", fastExponentiationRecursive(largeBase, largeExponent)); // This may take a noticeable time
console.log("2. Iterative Approach (Large Exponent):", fastExponentiationIterative(largeBase, largeExponent));
console.log("3. Bitwise Approach (Large Exponent):", fastExponentiationBitwise(largeBase, largeExponent));
console.log("4. Modular Exponentiation (Large Exponent):", modularExponentiation(largeBase, largeExponent, modulus));
console.log("5. Using Math.pow() (Large Exponent):", fastExponentiationMathPow(largeBase, largeExponent)); //This may return Infinity

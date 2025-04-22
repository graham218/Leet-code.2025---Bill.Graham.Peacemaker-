/*
 * Math & Geometry: Pow(x, n) - JavaScript Implementation
 * ------------------------------------------------------
 * This code demonstrates 5 different approaches to calculating x^n in JavaScript.
 * Each approach is explained with a real-world project implementation example.
 *
 * Approaches:
 * 1.  Iterative Method
 * 2.  Recursive Method
 * 3.  Optimized Recursive Method (Binary Exponentiation)
 * 4.  Using JavaScript's built-in Math.pow()
 * 5.  Using BigInt for very large numbers
 */

console.log("Math & Geometry: Pow(x, n) - JavaScript Implementation\n");

// 1. Iterative Method
// --------------------
// Calculates x^n using a simple loop.
//
// Real-world example:
//   -   Calculating compound interest over a period of 'n' years.
//   -   Generating a sequence of values where each term is a power of a base.
function powerIterative(x, n) {
    if (n === 0) {
        return 1;
    }

    let result = 1;
    let absN = Math.abs(n); // Handle negative exponents

    for (let i = 0; i < absN; i++) {
        result *= x;
    }

    return n < 0 ? 1 / result : result;
}

console.log("1. Iterative Method");
console.log(`powerIterative(2, 3) = ${powerIterative(2, 3)}`);   // Output: 8
console.log(`powerIterative(2, -2) = ${powerIterative(2, -2)}`);  // Output: 0.25
console.log(`powerIterative(10, 0) = ${powerIterative(10, 0)}`); // Output: 1
console.log("\n");


// 2. Recursive Method
// --------------------
// Calculates x^n using recursion.  This is a straightforward,
// but potentially less efficient, way to express the power function.
//
// Real-world example:
//   -   Implementing a fractal drawing algorithm (e.g., Sierpinski triangle).
//   -   Solving mathematical problems with recursive definitions.
function powerRecursive(x, n) {
    if (n === 0) {
        return 1;
    }

    if (n < 0) {
        return 1 / powerRecursive(x, -n);
    }

    return x * powerRecursive(x, n - 1);
}

console.log("2. Recursive Method");
console.log(`powerRecursive(3, 4) = ${powerRecursive(3, 4)}`);   // Output: 81
console.log(`powerRecursive(2, -3) = ${powerRecursive(2, -3)}`);  // Output: 0.125
console.log(`powerRecursive(5, 0) = ${powerRecursive(5, 0)}`);   // Output: 1
console.log("\n");

// 3. Optimized Recursive Method (Binary Exponentiation)
// ------------------------------------------------------
// Calculates x^n using a more efficient recursive approach.
// It takes advantage of the fact that x^n = x^(n/2) * x^(n/2) if n is even,
// and x^n = x * x^(n-1) if n is odd.  This significantly reduces the
// number of multiplications required.
//
// Real-world example:
//   -   Cryptographic algorithms (e.g., RSA encryption) where efficient
//       modular exponentiation is crucial.
//   -   High-performance computing applications.
function powerRecursiveOptimized(x, n) {
    if (n === 0) {
        return 1;
    }

    if (n < 0) {
        return 1 / powerRecursiveOptimized(x, -n);
    }

    if (n % 2 === 0) { // n is even
        const temp = powerRecursiveOptimized(x, n / 2);
        return temp * temp;
    } else { // n is odd
        return x * powerRecursiveOptimized(x, n - 1);
    }
}

console.log("3. Optimized Recursive Method (Binary Exponentiation)");
console.log(`powerRecursiveOptimized(2, 10) = ${powerRecursiveOptimized(2, 10)}`);  // Output: 1024
console.log(`powerRecursiveOptimized(3, -2) = ${powerRecursiveOptimized(3, -2)}`); // Output: 0.1111111111111111
console.log(`powerRecursiveOptimized(7, 0) = ${powerRecursiveOptimized(7, 0)}`);  // Output: 1
console.log("\n");

// 4. Using JavaScript's built-in Math.pow()
// -----------------------------------------
// Calculates x^n using the built-in Math.pow() function.
// This is the simplest and often the most efficient way to calculate powers in JavaScript.
//
// Real-world example:
//   -   Any general-purpose calculation in a web application or script
//       where you need to raise a number to a power.  This is the standard
//       and recommended approach for most common use cases.
function powerMathPow(x, n) {
    return Math.pow(x, n);
}

console.log("4. Using JavaScript's built-in Math.pow()");
console.log(`powerMathPow(4, 3) = ${powerMathPow(4, 3)}`);    // Output: 64
console.log(`powerMathPow(2, -4) = ${powerMathPow(2, -4)}`);   // Output: 0.0625
console.log(`powerMathPow(9, 0) = ${powerMathPow(9, 0)}`);    // Output: 1
console.log("\n");

// 5. Using BigInt for very large numbers
// --------------------------------------
// Calculates x^n using BigInt for very large values of x and n,
// where the result might exceed the maximum safe integer in JavaScript.
//
// Real-world example:
//  -  Cryptographic applications dealing with very large numbers.
//  -  Financial calculations involving extremely large amounts.
//  -  Scientific computations with very high precision requirements.
function powerBigInt(x, n) {
    if (n === 0n) {
        return 1n;
    }

    if (n < 0n) {
        return 1n / powerBigInt(BigInt(x), -n); // Handles negative exponents
    }
    let result = 1n;
    let absN = n;

    for (let i = 0n; i < absN; i++) {
        result *= BigInt(x);
    }
    return result;
}

console.log("5. Using BigInt for very large numbers");
const base = 2n;
const exponent = 100n;
console.log(`powerBigInt(${base}, ${exponent}) = ${powerBigInt(base, exponent)}`); // Output: 1267650600228229401496703205376n
console.log("\n");

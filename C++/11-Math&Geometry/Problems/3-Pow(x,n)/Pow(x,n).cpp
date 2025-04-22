/*
Math & Geometry: Pow(x, n) - 5 Approaches in JavaScript
-------------------------------------------------------
This code demonstrates five different ways to calculate the power of a number (x raised to the power of n) in JavaScript.  The results of each approach are printed to the console.

Approaches:
1.  Using the Math.pow() method (built-in).
2.  Iterative method (using a loop).
3.  Recursive method (basic recursion).
4.  Recursive method (optimized - divide and conquer).
5.  Using the ** operator (ES6 feature).

For demonstration, we will calculate 2 raised to the power of 10 (2^10).
*/

// --------------------------------------------------------------------------
// 1. Using the Math.pow() method
// --------------------------------------------------------------------------
function powerUsingMathPow(x, n) {
    const result = Math.pow(x, n);
    console.log("1. Using Math.pow(x, n):", result);
    return result;
}

// --------------------------------------------------------------------------
// 2. Iterative method (using a loop)
// --------------------------------------------------------------------------
function powerIterative(x, n) {
    let result = 1;
    for (let i = 0; i < n; i++) {
        result *= x;
    }
    console.log("2. Iterative method:", result);
    return result;
}

// --------------------------------------------------------------------------
// 3. Recursive method (basic recursion)
// --------------------------------------------------------------------------
function powerRecursive(x, n) {
    if (n === 0) {
        return 1;
    } else {
        return x * powerRecursive(x, n - 1);
    }
}

function displayPowerRecursive(x,n){
    const result = powerRecursive(x,n);
    console.log("3. Recursive method (basic):", result);
    return result;
}


// --------------------------------------------------------------------------
// 4. Recursive method (optimized - divide and conquer)
// --------------------------------------------------------------------------
function powerRecursiveOptimized(x, n) {
    if (n === 0) {
        return 1;
    } else if (n % 2 === 0) { // n is even
        const temp = powerRecursiveOptimized(x, n / 2);
        return temp * temp;
    } else { // n is odd
        const temp = powerRecursiveOptimized(x, (n - 1) / 2);
        return x * temp * temp;
    }
}

function displayPowerRecursiveOptimized(x,n){
    const result = powerRecursiveOptimized(x,n);
    console.log("4. Recursive method (optimized):", result);
    return result;
}

// --------------------------------------------------------------------------
// 5. Using the ** operator (ES6 feature)
// --------------------------------------------------------------------------
function powerUsingES6(x, n) {
    const result = x ** n;
    console.log("5. Using the ** operator (ES6):", result);
    return result;
}

// --------------------------------------------------------------------------
// Demonstration
// --------------------------------------------------------------------------
const base = 2;
const exponent = 10;

powerUsingMathPow(base, exponent);
powerIterative(base, exponent);
displayPowerRecursive(base, exponent);
displayPowerRecursiveOptimized(base, exponent);
powerUsingES6(base, exponent);

// Euclidean Algorithm - 5 Approaches in JavaScript

// 1. Recursive Approach
//   - Base Case: If b is 0, the GCD is a.
//   - Recursive Step: Otherwise, the GCD of a and b is the same as the GCD of b and the remainder of a divided by b.
function gcdRecursive(a, b) {
    if (b === 0) {
        return a;
    }
    return gcdRecursive(b, a % b);
}

// 2. Iterative Approach
//   - Use a while loop.
//   - In each iteration, update a and b.
//   - When b becomes 0, a is the GCD.
function gcdIterative(a, b) {
    while (b !== 0) {
        const temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 3. Binary (Stein's) Algorithm - Recursive
//   - More efficient as it replaces division with bitwise operations and subtractions.
//   - If both a and b are even, gcd(a, b) = 2 * gcd(a/2, b/2).
//   - If a is even and b is odd, gcd(a, b) = gcd(a/2, b).
//   - If a is odd and b is even, gcd(a, b) = gcd(a, b/2).
//   - If both are odd, gcd(a, b) = gcd(|a-b|/2, min(a, b)).
function gcdBinaryRecursive(a, b) {
    if (a === 0) return b;
    if (b === 0) return a;

    if (a === b) return a;

    if ((a & 1) === 0) { // a is even
        if ((b & 1) === 0) { // b is even
            return gcdBinaryRecursive(a >> 1, b >> 1) << 1; // result * 2
        } else { // b is odd
            return gcdBinaryRecursive(a >> 1, b);
        }
    } else { // a is odd
        if ((b & 1) === 0) { // b is even
            return gcdBinaryRecursive(a, b >> 1);
        } else { // b is odd
            if (a > b) {
                return gcdBinaryRecursive((a - b) >> 1, b);
            } else {
                return gcdBinaryRecursive((b - a) >> 1, a);
            }
        }
    }
}

// 4. Binary (Stein's) Algorithm - Iterative
function gcdBinaryIterative(a, b) {
    if (a === 0) return b;
    if (b === 0) return a;

    let shift = 0;
    while (((a | b) & 1) === 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    while ((a & 1) === 0) {
        a >>= 1;
    }

    do {
        while ((b & 1) === 0) {
            b >>= 1;
        }
        if (a > b) {
            const temp = a;
            a = b;
            b = temp - b;
        } else {
            b -= a;
        }
    } while (b !== 0);

    return a << shift;
}

// 5. Using a helper function for more concise iterative version
function gcdIterative2(a, b) {
    const getGCD = (x, y) => y === 0 ? x : getGCD(y, x % y);
    return getGCD(a, b);
}

// Example Usage and Output
const num1 = 48;
const num2 = 18;

console.log(`GCD of ${num1} and ${num2} using Recursive Approach:`, gcdRecursive(num1, num2));
console.log(`GCD of ${num1} and ${num2} using Iterative Approach:`, gcdIterative(num1, num2));
console.log(`GCD of ${num1} and ${num2} using Binary Recursive Approach:`, gcdBinaryRecursive(num1, num2));
console.log(`GCD of ${num1} and ${num2} using Binary Iterative Approach:`, gcdBinaryIterative(num1, num2));
console.log(`GCD of ${num1} and ${num2} using Iterative 2 Approach:`, gcdIterative2(num1, num2));

//   Common Test Cases
console.log("--- Common Test Cases ---");
console.log("GCD of 60 and 48:", gcdRecursive(60, 48)); // Expected: 12
console.log("GCD of 100 and 25:", gcdRecursive(100, 25)); // Expected: 25
console.log("GCD of 12 and 18:", gcdRecursive(12, 18));   // Expected: 6
console.log("GCD of 15 and 25:", gcdRecursive(15, 25));   // Expected: 5
console.log("GCD of 3 and 7:", gcdRecursive(3, 7));     // Expected: 1 (Coprime)
console.log("GCD of 48 and 18:", gcdRecursive(48, 18)); // Expected: 6
console.log("GCD of 0 and 5:", gcdRecursive(0, 5));    // Expected: 5
console.log("GCD of 5 and 0:", gcdRecursive(5, 0));    // Expected: 5
console.log("GCD of 0 and 0:", gcdRecursive(0, 0));    // Expected: 0

// Test cases with larger numbers
console.log("--- Large Number Test Cases ---");
console.log("GCD of 123456789 and 987654321:", gcdRecursive(123456789, 987654321));
console.log("GCD of 1000000 and 855000:", gcdRecursive(1000000, 855000));

// Test cases with negative numbers
console.log("--- Negative Number Test Cases ---");
console.log("GCD of -12 and 18:", gcdRecursive(-12, 18));  // Expected: 6  (Handles negatives)
console.log("GCD of 12 and -18:", gcdRecursive(12, -18));  // Expected: 6
console.log("GCD of -12 and -18:", gcdRecursive(-12, -18)); // Expected: 6

// Test cases with same numbers
console.log("--- Same Number Test Cases ---");
console.log("GCD of 5 and 5:", gcdRecursive(5, 5)); // Expected: 5
console.log("GCD of 100 and 100:", gcdRecursive(100, 100)); // Expected: 100

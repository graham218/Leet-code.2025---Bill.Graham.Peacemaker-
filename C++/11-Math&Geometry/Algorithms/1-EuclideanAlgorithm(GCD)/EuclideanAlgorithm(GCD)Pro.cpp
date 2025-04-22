// Euclidean Algorithm Implementations

// 1. Basic Recursive Euclidean Algorithm
//   - Real-world application: Simplifying fractions in a calculator application.
//   - Example:  A calculator app reduces 12/18 to 2/3 by finding GCD(12, 18) = 6.
function recursiveGCD(a, b) {
    if (b === 0) {
        return a;
    }
    return recursiveGCD(b, a % b);
}

console.log("1. Recursive GCD (Simplifying Fractions):");
let num1 = 12;
let num2 = 18;
let gcd1 = recursiveGCD(num1, num2);
console.log(`GCD of ${num1} and ${num2} is: ${gcd1}`);
console.log(`Simplified fraction: ${num1 / gcd1}/${num2 / gcd1}`); // Output: 2/3


// 2. Iterative Euclidean Algorithm
//   - Real-world application:  Finding the greatest common divisor of two lengths in a CAD program to ensure proper fitting of components.
//   - Example:  A CAD program calculates the GCD of 48mm and 36mm to be 12mm, which is the largest common segment for fitting.
function iterativeGCD(a, b) {
    while (b !== 0) {
        const temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

console.log("\n2. Iterative GCD (CAD Component Fitting):");
let length1 = 48;
let length2 = 36;
let gcd2 = iterativeGCD(length1, length2);
console.log(`GCD of ${length1} and ${length2} is: ${gcd2}`);
console.log(`Largest common segment: ${gcd2}mm`); // Output: 12mm


// 3. Binary Euclidean Algorithm (Stein's Algorithm)
//   - Real-world application: Optimizing calculations in embedded systems with limited processing power.
//   - Example:  An embedded system calculates GCD of 256 and 80 efficiently using bitwise operations.
function binaryGCD(a, b) {
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
            b = temp;
        }
        b -= a;
    } while (b !== 0);

    return a << shift;
}

console.log("\n3. Binary GCD (Embedded Systems):");
let num3 = 256;
let num4 = 80;
let gcd3 = binaryGCD(num3, num4);
console.log(`GCD of ${num3} and ${num4} is: ${gcd3}`); // Output: 16


// 4. Extended Euclidean Algorithm
//    - Real-world application:  Used in cryptography (RSA algorithm) to find modular inverses.
//    - Example: Finding the modular inverse of 17 modulo 7 in RSA key generation.
function extendedGCD(a, b) {
    if (b === 0) {
        return { gcd: a, x: 1, y: 0 };
    }
    const { gcd, x, y } = extendedGCD(b, a % b);
    const newX = y;
    const newY = x - Math.floor(a / b) * y;
    return { gcd: gcd, x: newX, y: newY };
}

console.log("\n4. Extended GCD (Cryptography - RSA):");
let a = 17;
let m = 7;
let result = extendedGCD(a, m);
let gcd4 = result.gcd;
let x = result.x;

console.log(`GCD of ${a} and ${m} is: ${gcd4}`);
if (gcd4 === 1) {
    let modularInverse = (x % m + m) % m; // Ensure positive result
    console.log(`Modular inverse of ${a} modulo ${m} is: ${modularInverse}`);  // Output: 4
} else {
    console.log(`Modular inverse of ${a} modulo ${m} does not exist.`);
}



// 5.  GCD for finding the largest square tile to fit an area
//    - Real world application: Used in construction and flooring to determine the largest tile size to use.
//    - Example: Finding the largest square tile to fit a rectangular area of 720cm x 400cm.

function findLargestTile(length, width) {
  return iterativeGCD(length, width);
}

console.log("\n5. GCD for Largest Tile Size (Flooring):");
let areaLength = 720;
let areaWidth = 400;
let tileSize = findLargestTile(areaLength, areaWidth);
console.log(`Largest square tile size for an area of ${areaLength}cm x ${areaWidth}cm is: ${tileSize}cm x ${tileSize}cm`); // Output: 80cm x 80cm

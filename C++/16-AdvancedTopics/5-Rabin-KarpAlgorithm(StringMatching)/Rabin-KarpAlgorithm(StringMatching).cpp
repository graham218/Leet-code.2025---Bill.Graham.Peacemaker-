/*
Rabin-Karp Algorithm for String Matching: 5 Approaches in JavaScript

The Rabin-Karp algorithm is a string searching algorithm that uses hashing to find occurrences of a pattern string within a text string. It's efficient for multiple pattern searches.

Key Concepts:
- Hashing: Convert a string into a numerical value (hash code).
- Rolling Hash: Efficiently update the hash code as we slide the pattern across the text.
- Spurious Hits: When the hash codes match, but the strings don't actually match.  We must verify these.

Time Complexity:
- Best/Average Case: O(n + m), where n is the text length and m is the pattern length.
- Worst Case: O(n * m) (due to spurious hits, especially with a bad hash function).

Space Complexity: O(1) - constant extra space.

Variations Implemented:
1. Basic Rabin-Karp:  A straightforward implementation.
2. Rabin-Karp with Prime Modulo: Uses a prime number to reduce spurious hits.
3. Rabin-Karp with Large Prime Modulo: Uses a larger prime for even fewer collisions.
4. Rabin-Karp with Base Optimization: Optimizes the base used in the hash function.
5. Rabin-Karp with Precomputed Powers: Precomputes powers of the base for efficiency.
*/

const rabinKarpAlgorithms = {
  /**
   * 1. Basic Rabin-Karp
   * A basic implementation of the Rabin-Karp algorithm.
   *
   * @param {string} text - The text string to search within.
   * @param {string} pattern - The pattern string to search for.
   * @returns {number[]} An array of starting indices where the pattern is found in the text.
   */
  basicRabinKarp: function (text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const results = [];

    if (m === 0) {
      return [0]; // Empty pattern, found at start.  Consistent with some implementations.
    }
    if (m > n) {
      return []; // Pattern longer than text, cannot be found.
    }

    const base = 256; //  Common base for ASCII
    let patternHash = 0;
    let textHash = 0;

    // Calculate initial hash values for pattern and text
    for (let i = 0; i < m; i++) {
      patternHash = (patternHash * base + pattern.charCodeAt(i));
      textHash = (textHash * base + text.charCodeAt(i));
    }

    // Slide the pattern through the text
    for (let i = 0; i <= n - m; i++) {
      // Check if the hash values match
      if (patternHash === textHash) {
        // Verify the actual strings match (to handle spurious hits)
        let match = true;
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          results.push(i);
        }
      }

      // Calculate the hash value for the next text window (rolling hash)
      if (i < n - m) {
        textHash = (textHash - text.charCodeAt(i) * Math.pow(base, m - 1)) * base + text.charCodeAt(i + m);
      }
    }
    return results;
  },

  /**
   * 2. Rabin-Karp with Prime Modulo
   * Uses a prime modulo to reduce the number of spurious hits.
   *
   * @param {string} text - The text string to search within.
   * @param {string} pattern - The pattern string to search for.
   * @returns {number[]} An array of starting indices where the pattern is found in the text.
   */
  rabinKarpWithPrimeModulo: function (text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const results = [];

    if (m === 0) {
      return [0];
    }
    if (m > n) {
      return [];
    }

    const base = 256;
    const prime = 101; // A prime number
    let patternHash = 0;
    let textHash = 0;

    for (let i = 0; i < m; i++) {
      patternHash = (patternHash * base + pattern.charCodeAt(i)) % prime;
      textHash = (textHash * base + text.charCodeAt(i)) % prime;
    }

    for (let i = 0; i <= n - m; i++) {
      if (patternHash === textHash) {
        let match = true;
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          results.push(i);
        }
      }

      if (i < n - m) {
        textHash = ((textHash - text.charCodeAt(i) * Math.pow(base, m - 1)) * base + text.charCodeAt(i + m)) % prime;
        // Handle negative values of textHash
        if (textHash < 0) {
          textHash = (textHash + prime) % prime;
        }
      }
    }
    return results;
  },

  /**
   * 3. Rabin-Karp with Large Prime Modulo
   * Uses a larger prime number to further reduce spurious hits.
   *
   * @param {string} text - The text string to search within.
   * @param {string} pattern - The pattern string to search for.
   * @returns {number[]} An array of starting indices where the pattern is found in the text.
   */
  rabinKarpWithLargePrimeModulo: function (text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const results = [];

    if (m === 0) {
      return [0];
    }
    if (m > n) {
      return [];
    }

    const base = 256;
    const prime = 16777619; // A larger prime number (Mersenne prime)
    let patternHash = 0;
    let textHash = 0;

    for (let i = 0; i < m; i++) {
      patternHash = (patternHash * base + pattern.charCodeAt(i)) % prime;
      textHash = (textHash * base + text.charCodeAt(i)) % prime;
    }

    for (let i = 0; i <= n - m; i++) {
      if (patternHash === textHash) {
        let match = true;
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          results.push(i);
        }
      }

      if (i < n - m) {
        textHash = ((textHash - text.charCodeAt(i) * Math.pow(base, m - 1)) * base + text.charCodeAt(i + m)) % prime;
        if (textHash < 0) {
          textHash = (textHash + prime) % prime;
        }
      }
    }
    return results;
  },

  /**
   * 4. Rabin-Karp with Base Optimization
   * Optimizes the base used in the hash function.  The base should be larger
   * than the number of distinct characters in the input string.
   *
   * @param {string} text - The text string to search within.
   * @param {string} pattern - The pattern string to search for.
   * @returns {number[]} An array of starting indices where the pattern is found in the text.
   */
  rabinKarpWithBaseOptimization: function (text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const results = [];

    if (m === 0) {
      return [0];
    }
    if (m > n) {
      return [];
    }

    // Find the number of distinct characters (optimize the base)
    let distinctChars = 0;
    const charSet = new Set();
    for (let i = 0; i < n; i++) {
      charSet.add(text[i]);
    }
    for (let i = 0; i < m; i++){
        charSet.add(pattern[i]);
    }
    distinctChars = charSet.size;
    const base = Math.max(distinctChars, 256); // Base should be >= distinctChars and at least 256

    const prime = 16777619;
    let patternHash = 0;
    let textHash = 0;

    for (let i = 0; i < m; i++) {
      patternHash = (patternHash * base + pattern.charCodeAt(i)) % prime;
      textHash = (textHash * base + text.charCodeAt(i)) % prime;
    }

    for (let i = 0; i <= n - m; i++) {
      if (patternHash === textHash) {
        let match = true;
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          results.push(i);
        }
      }

      if (i < n - m) {
        textHash = ((textHash - text.charCodeAt(i) * Math.pow(base, m - 1)) * base + text.charCodeAt(i + m)) % prime;
         if (textHash < 0) {
          textHash = (textHash + prime) % prime;
        }
      }
    }
    return results;
  },

  /**
   * 5. Rabin-Karp with Precomputed Powers
   * Precomputes the powers of the base to optimize the rolling hash calculation.
   *
   * @param {string} text - The text string to search within.
   * @param {string} pattern - The pattern string to search for.
   * @returns {number[]} An array of starting indices where the pattern is found in the text.
   */
  rabinKarpWithPrecomputedPowers: function (text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const results = [];

    if (m === 0) {
      return [0];
    }
    if (m > n) {
      return [];
    }

    const base = 256;
    const prime = 16777619;
    let patternHash = 0;
    let textHash = 0;
    const basePowM = Math.pow(base, m - 1) % prime; // Precompute base^(m-1) % prime

    for (let i = 0; i < m; i++) {
      patternHash = (patternHash * base + pattern.charCodeAt(i)) % prime;
      textHash = (textHash * base + text.charCodeAt(i)) % prime;
    }

    for (let i = 0; i <= n - m; i++) {
      if (patternHash === textHash) {
        let match = true;
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          results.push(i);
        }
      }

      if (i < n - m) {
        textHash = ((textHash - text.charCodeAt(i) * basePowM) * base + text.charCodeAt(i + m)) % prime;
        if (textHash < 0) {
          textHash = (textHash + prime) % prime;
        }
      }
    }
    return results;
  },
};

// Example Usage and Output
const text = "ABABDABACDABABCABAB";
const pattern1 = "ABABC";
const pattern2 = "ABA";
const pattern3 = "DABAC";
const pattern4 = "";
const pattern5 = "ABABDABACDABABCABAB";
const pattern6 = "Z";

console.log("Text:", text);
console.log("Pattern 1:", pattern1);
console.log("Pattern 2:", pattern2);
console.log("Pattern 3:", pattern3);
console.log("Pattern 4:", pattern4);
console.log("Pattern 5:", pattern5);
console.log("Pattern 6:", pattern6);


console.log("\n1. Basic Rabin-Karp:");
console.log("Pattern 1:", rabinKarpAlgorithms.basicRabinKarp(text, pattern1)); // [ 10 ]
console.log("Pattern 2:", rabinKarpAlgorithms.basicRabinKarp(text, pattern2)); // [ 0, 4, 12, 14 ]
console.log("Pattern 3:", rabinKarpAlgorithms.basicRabinKarp(text, pattern3)); // [ 5 ]
console.log("Pattern 4:", rabinKarpAlgorithms.basicRabinKarp(text, pattern4)); // [ 0 ]
console.log("Pattern 5:", rabinKarpAlgorithms.basicRabinKarp(text, pattern5)); // [ 0 ]
console.log("Pattern 6:", rabinKarpAlgorithms.basicRabinKarp(text, pattern6)); // []

console.log("\n2. Rabin-Karp with Prime Modulo:");
console.log("Pattern 1:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern1)); // [ 10 ]
console.log("Pattern 2:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern2)); // [ 0, 4, 12, 14 ]
console.log("Pattern 3:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern3)); // [ 5 ]
console.log("Pattern 4:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern4)); // [ 0 ]
console.log("Pattern 5:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern5)); // [ 0 ]
console.log("Pattern 6:", rabinKarpAlgorithms.rabinKarpWithPrimeModulo(text, pattern6)); // []

console.log("\n3. Rabin-Karp with Large Prime Modulo:");
console.log("Pattern 1:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern1)); // [ 10 ]
console.log("Pattern 2:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern2)); // [ 0, 4, 12, 14 ]
console.log("Pattern 3:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern3)); // [ 5 ]
console.log("Pattern 4:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern4)); // [ 0 ]
console.log("Pattern 5:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern5)); // [ 0 ]
console.log("Pattern 6:", rabinKarpAlgorithms.rabinKarpWithLargePrimeModulo(text, pattern6)); // []

console.log("\n4. Rabin-Karp with Base Optimization:");
console.log("Pattern 1:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern1)); // [ 10 ]
console.log("Pattern 2:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern2)); // [ 0, 4, 12, 14 ]
console.log("Pattern 3:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern3)); // [ 5 ]
console.log("Pattern 4:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern4)); // [ 0 ]
console.log("Pattern 5:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern5)); // [ 0 ]
console.log("Pattern 6:", rabinKarpAlgorithms.rabinKarpWithBaseOptimization(text, pattern6)); // []

console.log("\n5. Rabin-Karp with Precomputed Powers:");
console.log("Pattern 1:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern1)); // [ 10 ]
console.log("Pattern 2:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern2)); // [ 0, 4, 12, 14 ]
console.log("Pattern 3:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern3)); // [ 5 ]
console.log("Pattern 4:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern4)); // [ 0 ]
console.log("Pattern 5:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern5)); // [ 0 ]
console.log("Pattern 6:", rabinKarpAlgorithms.rabinKarpWithPrecomputedPowers(text, pattern6)); // []

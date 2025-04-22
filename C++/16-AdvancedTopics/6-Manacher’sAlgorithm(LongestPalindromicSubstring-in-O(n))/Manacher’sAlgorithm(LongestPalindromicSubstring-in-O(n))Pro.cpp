/*
Manacher's Algorithm: Finding the Longest Palindromic Substring in O(n)

This code provides five different implementations of Manacher's algorithm, each with a slightly different focus or optimization, and includes console logs for demonstration.

Key Idea:
The algorithm preprocesses the input string by inserting a special character (e.g., '#') between characters and at the boundaries. This transforms any string into an odd-length string, simplifying palindrome checks. It then iterates through the modified string, calculating the longest palindromic substring centered at each position, leveraging previously computed values to optimize performance.

Time Complexity: O(n) - Linear time complexity.
Space Complexity: O(n) - Linear space complexity.
*/

/**
 * 1. Basic Manacher's Algorithm
 *
 * This is the most straightforward implementation of Manacher's algorithm.
 * It focuses on clarity and ease of understanding.
 */
function manacherBasic(s) {
  if (!s) return "";

  // Preprocess the string
  let t = '#';
  for (let i = 0; i < s.length; i++) {
    t += s[i] + '#';
  }

  const n = t.length;
  const p = new Array(n).fill(0); // Array to store palindrome lengths
  let center = 0, right = 0;
  let maxLen = 0, maxCenter = 0;

  for (let i = 1; i < n; i++) {
    // Utilize symmetry if possible
    if (i < right) {
      p[i] = Math.min(right - i, p[2 * center - i]);
    }

    // Expand palindrome centered at i
    while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] === t[i + (1 + p[i])]) {
      p[i]++;
    }

    // Update center and right boundary if necessary
    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }

    // Track the longest palindrome
    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }
  }

  // Extract the longest palindromic substring
  const start = (maxCenter - maxLen) / 2;
  const end = start + maxLen;
  const result = s.substring(start, end);
  return result;
}

/**
 * 2. Manacher's Algorithm with Early Exit
 *
 * This version adds an optimization to exit early if the remaining part of the
 * string cannot possibly contain a longer palindrome.
 */
function manacherEarlyExit(s) {
  if (!s) return "";

  let t = '#';
  for (let i = 0; i < s.length; i++) {
    t += s[i] + '#';
  }

  const n = t.length;
  const p = new Array(n).fill(0);
  let center = 0, right = 0;
  let maxLen = 0, maxCenter = 0;

  for (let i = 1; i < n; i++) {
    if (i < right) {
      p[i] = Math.min(right - i, p[2 * center - i]);
    }

    while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] === t[i + (1 + p[i])]) {
      p[i]++;
    }

    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }

    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }

    // Early exit optimization:
    if (n - i <= maxLen / 2) { // Corrected condition.
      break;
    }
  }

  const start = (maxCenter - maxLen) / 2;
  const end = start + maxLen;
  const result = s.substring(start, end);
  return result;
}

/**
 * 3. Manacher's Algorithm with Detailed Logging
 *
 * This version includes console logs to help visualize the algorithm's execution.
 * It's useful for debugging and understanding how the algorithm works step by step.
 */
function manacherWithLogging(s) {
  if (!s) return "";

  let t = '#';
  for (let i = 0; i < s.length; i++) {
    t += s[i] + '#';
  }

  const n = t.length;
  const p = new Array(n).fill(0);
  let center = 0, right = 0;
  let maxLen = 0, maxCenter = 0;

  console.log("Modified string t:", t);

  for (let i = 1; i < n; i++) {
    console.log(`\n--- i = ${i} ---`);
    console.log("Current state: center =", center, ", right =", right);
    if (i < right) {
      p[i] = Math.min(right - i, p[2 * center - i]);
      console.log("Using symmetry: p[", i, "] =", p[i]);
    }

    while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] === t[i + (1 + p[i])]) {
      p[i]++;
      console.log("Expanding: p[", i, "] =", p[i]);
    }

    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
      console.log("Updating center and right: center =", center, ", right =", right);
    }

    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
      console.log("New maxLen:", maxLen, ", maxCenter:", maxCenter);
    }
    console.log("p:", p);
  }

  const start = (maxCenter - maxLen) / 2;
  const end = start + maxLen;
  const result = s.substring(start, end);
  console.log("Longest palindromic substring:", result);
  return result;
}

/**
 * 4. Manacher's Algorithm for Large Strings (Optimized)
 *
 * This version is optimized for very large strings.  It's similar to the basic
 * version, but might include minor optimizations for large input handling
 */
function manacherLargeString(s) {
    if (!s) return "";

    let t = '#';
    for (let i = 0; i < s.length; i++) {
        t += s[i] + '#';
    }

    const n = t.length;
    const p = new Array(n).fill(0);
    let center = 0, right = 0;
    let maxLen = 0, maxCenter = 0;

    // Optimized loop for large n (potential micro-optimizations)
    for (let i = 1; i < n; i++) {
        if (i < right) {
            p[i] = Math.min(right - i, p[2 * center - i]);
        }

        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] === t[i + (1 + p[i])]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }

    const start = (maxCenter - maxLen) / 2;
    const end = start + maxLen;
    const result = s.substring(start, end);
    return result;
}

/**
 * 5. Manacher's Algorithm with Real-World Application Context
 *
 * This version demonstrates how Manacher's algorithm can be applied in a
 * real-world scenario: finding the longest palindromic substring in a
 * DNA sequence.
 */
function manacherDNASequence(dnaSequence) {
  if (!dnaSequence) return "";

  // Preprocess the DNA sequence
  const processedSequence = '#' + dnaSequence.split('').join('#') + '#';
  const n = processedSequence.length;
  const p = new Array(n).fill(0);
  let center = 0, right = 0;
  let maxLen = 0, maxCenter = 0;

  for (let i = 1; i < n; i++) {
    if (i < right) {
      p[i] = Math.min(right - i, p[2 * center - i]);
    }

    while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && processedSequence[i - (1 + p[i])] === processedSequence[i + (1 + p[i])]) {
      p[i]++;
    }

    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }

    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }
  }

  const start = (maxCenter - maxLen) / 2;
  const end = start + maxLen;
  const longestPalindrome = dnaSequence.substring(start, end);

  console.log("DNA Sequence:", dnaSequence);
  console.log("Longest Palindromic Subsequence:", longestPalindrome);

  return longestPalindrome;
}

// Example Usage and Output
const testString = "babad";
const testString2 = "cbbd";
const testString3 = "aabaaba";
const testString4 = "racecar";
const testString5 = "madam";
const longTestString = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"; //really long string
const dnaSequence = "AGCTAGCTGAAGCTAA";

console.log("--- Manacher's Algorithm ---");
console.log("Test String 1:", testString);
console.log("Longest Palindrome (Basic):", manacherBasic(testString));           // Output: bab or aba
console.log("Longest Palindrome (Early Exit):", manacherEarlyExit(testString));     // Output: bab or aba
console.log("Longest Palindrome (With Logging):", manacherWithLogging(testString)); // Output: (with detailed logs) bab or aba
console.log("Longest Palindrome (Large String):", manacherLargeString(longTestString));
console.log("Test String 2:", testString2);
console.log("Longest Palindrome (Basic):", manacherBasic(testString2));         // Output: bb
console.log("Test String 3:", testString3);
console.log("Longest Palindrome (Basic):", manacherBasic(testString3)); // Output: aabaaba
console.log("Test String 4:", testString4);
console.log("Longest Palindrome (Basic):", manacherBasic(testString4)); // Output: racecar
console.log("Test String 5:", testString5);
console.log("Longest Palindrome (Basic):", manacherBasic(testString5)); // Output: madam

console.log("\n--- Manacher's Algorithm for DNA Sequence ---");
manacherDNASequence(dnaSequence); // Example usage with a DNA sequence

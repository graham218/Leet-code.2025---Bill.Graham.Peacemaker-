/*
Manacher's Algorithm: Finding the Longest Palindromic Substring in O(n)

This code provides five different approaches to solving the Longest Palindromic Substring problem,
with the Manacher's algorithm implementation optimized for O(n) time complexity.  Each approach is
explained with comments, and the output of each is displayed using console.log.

Approaches:

1.  Manacher's Algorithm (Optimized): The core implementation of Manacher's algorithm,
    optimized for linear time complexity.  This is the most efficient approach.

2.  Manacher's with Detailed Logging:  Same as #1, but with added console.log statements
    to help visualize the algorithm's execution step-by-step.

3.  Brute Force Approach: A simple, but inefficient, approach that checks all possible
    substrings for being palindromes.  This has a time complexity of O(n^3).

4.  Dynamic Programming Approach: An improvement over brute force, this approach
    uses dynamic programming to store palindrome information and avoid redundant
    calculations.  Time complexity is O(n^2).

5.  Expand Around Center Approach:  A more intuitive approach than Manacher's, it expands
    outwards from each character in the string to find the longest palindrome centered
    at that character.  Time complexity is O(n^2).
*/

// 1. Manacher's Algorithm (Optimized)
//
// Finds the longest palindromic substring in O(n) time.
// Preprocesses the input string by inserting a special character ('#') between each
// character, including before the first character and after the last.  This
// transforms any string into an odd-length string, simplifying the palindrome checks.
// The algorithm maintains an array `p` where p[i] stores the radius of the longest
// palindrome centered at the (i)th position in the modified string.  It uses the
// symmetry property of palindromes to avoid redundant calculations.
function manachersAlgorithm(s) {
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

        while (i - p[i] >= 0 && i + p[i] < n && t[i - p[i]] === t[i + p[i]]) {
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

    const start = (maxCenter - maxLen + 1) / 2;
    const end = start + maxLen - 1;
    return s.substring(start, end);
}



// 2. Manacher's Algorithm with Detailed Logging
//
// Same as the optimized version, but includes console.log statements to provide
// a step-by-step visualization of the algorithm's execution.  Useful for
// understanding how the algorithm works.
function manachersAlgorithmWithLogging(s) {
    if (!s) return "";

    let t = '#';
    for (let i = 0; i < s.length; i++) {
        t += s[i] + '#';
    }
    console.log("Modified string t:", t);

    const n = t.length;
    const p = new Array(n).fill(0);
    let center = 0, right = 0;
    let maxLen = 0, maxCenter = 0;

    for (let i = 1; i < n; i++) {
        console.log("\n--- i:", i, "---");
        console.log("Current state: center =", center, ", right =", right, ", p =", p);

        if (i < right) {
            p[i] = Math.min(right - i, p[2 * center - i]);
            console.log("i < right, p[i] set to:", p[i], " (min of", right-i, "and", p[2*center - i], ")");
        }

        while (i - p[i] >= 0 && i + p[i] < n && t[i - p[i]] === t[i + p[i]]) {
            p[i]++;
            console.log("Expanding palindrome at i, p[i] now:", p[i]);
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
            console.log("Updating center to", center, "and right to", right);
        }

        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
            console.log("New maxLen:", maxLen, "at maxCenter:", maxCenter);
        }
    }

    const start = (maxCenter - maxLen + 1) / 2;
    const end = start + maxLen - 1;
    const result = s.substring(start, end);
    console.log("\nFinal p array:", p);
    console.log("Longest palindrome center:", maxCenter, "length:", maxLen);
    console.log("Result:", result);
    return result;
}



// 3. Brute Force Approach
//
// Checks every possible substring to see if it's a palindrome.  This is the
// simplest approach, but also the least efficient, with a time complexity of O(n^3).
function bruteForceLongestPalindrome(s) {
    if (!s) return "";

    let maxLen = 0;
    let longestPalindrome = "";

    for (let i = 0; i < s.length; i++) {
        for (let j = i; j < s.length; j++) {
            const sub = s.substring(i, j + 1);
            if (isPalindrome(sub) && sub.length > maxLen) {
                maxLen = sub.length;
                longestPalindrome = sub;
            }
        }
    }
    return longestPalindrome;
}

// Helper function to check if a string is a palindrome
function isPalindrome(str) {
    let left = 0;
    let right = str.length - 1;
    while (left < right) {
        if (str[left] !== str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}



// 4. Dynamic Programming Approach
//
// Uses a 2D table (dp) to store whether a substring s[i...j] is a palindrome.
// dp[i][j] is true if s[i...j] is a palindrome, and false otherwise.  The table
// is filled in a bottom-up manner.  Time complexity is O(n^2), space complexity is O(n^2).
function dynamicProgrammingLongestPalindrome(s) {
    if (!s) return "";

    const n = s.length;
    const dp = Array(n).fill(null).map(() => Array(n).fill(false));
    let maxLen = 1;
    let start = 0;

    // Base case: single characters are palindromes
    for (let i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // Base case: two-character substrings
    for (let i = 0; i < n - 1; i++) {
        if (s[i] === s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

    // Check for palindromes of length 3 and greater
    for (let k = 3; k <= n; k++) {
        for (let i = 0; i < n - k + 1; i++) {
            const j = i + k - 1;
            if (s[i] === s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (k > maxLen) {
                    start = i;
                    maxLen = k;
                }
            }
        }
    }
    return s.substring(start, start + maxLen);
}



// 5. Expand Around Center Approach
//
// For each character in the string, expand outwards to the left and right to find
// the longest palindrome centered at that character.  This approach handles both
// odd-length and even-length palindromes. Time complexity is O(n^2).
function expandAroundCenterLongestPalindrome(s) {
    if (!s) return "";

    let maxLen = 0;
    let start = 0;

    function expandAroundCenter(left, right) {
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            left--;
            right++;
        }
        return right - left - 1; // Length of the palindrome
    }

    for (let i = 0; i < s.length; i++) {
        // Odd length palindromes
        let len1 = expandAroundCenter(i, i);
        if (len1 > maxLen) {
            maxLen = len1;
            start = i - Math.floor(len1 / 2);
        }

        // Even length palindromes
        let len2 = expandAroundCenter(i, i + 1);
        if (len2 > maxLen) {
            maxLen = len2;
            start = i - Math.floor(len2 / 2) + 1; // Corrected start index for even length
        }
    }
    return s.substring(start, start + maxLen);
}



// Example usage and output:
const testString = "babad";
const testString2 = "cbbd";
const testString3 = "a";
const testString4 = "ac";
const testString5 = "racecar";
const testString6 = "madam";
const testString7 = "bananas";


console.log("Test String:", testString);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString));

console.log("\nTest String:", testString2);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString2));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString2);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString2));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString2));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString2));

console.log("\nTest String:", testString3);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString3));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString3);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString3));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString3));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString3));

console.log("\nTest String:", testString4);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString4));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString4);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString4));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString4));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString4));

console.log("\nTest String:", testString5);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString5));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString5);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString5));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString5));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString5));

console.log("\nTest String:", testString6);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString6));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString6);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString6));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString6));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString6));

console.log("\nTest String:", testString7);
console.log("1. Manacher's Algorithm (Optimized):", manachersAlgorithm(testString7));
console.log("2. Manacher's Algorithm (Detailed Logging):");
manachersAlgorithmWithLogging(testString7);
console.log("3. Brute Force Approach:", bruteForceLongestPalindrome(testString7));
console.log("4. Dynamic Programming Approach:", dynamicProgrammingLongestPalindrome(testString7));
console.log("5. Expand Around Center Approach:", expandAroundCenterLongestPalindrome(testString7));

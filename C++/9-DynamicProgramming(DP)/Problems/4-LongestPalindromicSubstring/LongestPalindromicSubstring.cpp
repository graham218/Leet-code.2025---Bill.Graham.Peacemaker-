/*
Dynamic Programming (DP) - Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: "cbbd"
Output: "bb"

Constraints:
1 <= s.length <= 1000
s consist of only digits and English letters.
*/

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^3)
 * Space Complexity: O(1)
 */
function longestPalindromeBruteForce(s) {
    if (!s || s.length === 0) return "";

    let longest = "";
    for (let i = 0; i < s.length; i++) {
        for (let j = i; j < s.length; j++) {
            const sub = s.substring(i, j + 1);
            if (isPalindrome(sub) && sub.length > longest.length) {
                longest = sub;
            }
        }
    }
    return longest;
}

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

/**
 * Approach 2: Dynamic Programming
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */
function longestPalindromeDP(s) {
    if (!s || s.length === 0) return "";

    const n = s.length;
    const dp = Array(n).fill(null).map(() => Array(n).fill(false));
    let longestStart = 0;
    let longestLength = 1;

    // Base case: single characters are palindromes
    for (let i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // Base case: two-character substrings
    for (let i = 0; i < n - 1; i++) {
        if (s[i] === s[i + 1]) {
            dp[i][i + 1] = true;
            longestStart = i;
            longestLength = 2;
        }
    }

    // Check for longer palindromes
    for (let len = 3; len <= n; len++) {
        for (let i = 0; i <= n - len; i++) {
            const j = i + len - 1;
            if (s[i] === s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (len > longestLength) {
                    longestStart = i;
                    longestLength = len;
                }
            }
        }
    }

    return s.substring(longestStart, longestStart + longestLength);
}

/**
 * Approach 3: Expand Around Center
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function longestPalindromeExpand(s) {
    if (!s || s.length === 0) return "";

    let longestStart = 0;
    let longestLength = 1;

    function expandAroundCenter(left, right) {
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            left--;
            right++;
        }
        // The loop stops when s[left] !== s[right], so the actual palindrome length is right - left - 1
        const length = right - left - 1;
        if (length > longestLength) {
            longestLength = length;
            longestStart = left + 1; // Start of the palindrome
        }
    }

    for (let i = 0; i < s.length; i++) {
        // Odd length palindromes
        expandAroundCenter(i, i);
        // Even length palindromes
        expandAroundCenter(i, i + 1);
    }

    return s.substring(longestStart, longestStart + longestLength);
}

/**
 * Approach 4: Manacher's Algorithm
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function longestPalindromeManacher(s) {
    if (!s || s.length === 0) return "";

    // Preprocess the string to handle even length palindromes
    const processedString = `#${s.split('').join('#')}#`; // e.g., "aba" -> "#a#b#a#" , "bb" -> "#b#b#"
    const n = processedString.length;
    const p = Array(n).fill(0); // Array to store palindrome lengths at each center
    let center = 0;
    let right = 0;
    let longestStart = 0;
    let longestLength = 1;

    for (let i = 1; i < n; i++) {
        // Use symmetry to initialize p[i]
        if (i < right) {
            const mirror = 2 * center - i;
            p[i] = Math.min(right - i, p[mirror]);
        }

        // Expand around center i
        let left = i - (1 + p[i]);
        let r = i + (1 + p[i]);
        while (left >= 0 && r < n && processedString[left] === processedString[r]) {
            p[i]++;
            left--;
            r++;
        }
        // Update center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Track the longest palindrome
        if (p[i] > longestLength) {
            longestLength = p[i];
            longestStart = (i - longestLength) / 2; // Map back to original string index, divide by 2 because of '#'
        }
    }

    return s.substring(longestStart, longestStart + longestLength);
}

/**
 * Approach 5: Optimized Dynamic Programming (Space Optimized)
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
function longestPalindromeOptimizedDP(s) {
    if (!s || s.length === 0) return "";

    const n = s.length;
    let longestStart = 0;
    let longestLength = 1;
    let dp = Array(n).fill(0); // Use a 1D array

    for (let i = n - 1; i >= 0; i--) {
        for (let j = i; j < n; j++) {
            if (s[i] === s[j] && (j - i <= 2 || dp[j - 1])) { // j-i <=2 handles single and double char palindromes
                dp[j] = 1; // Mark as palindrome
                if (j - i + 1 > longestLength) {
                    longestLength = j - i + 1;
                    longestStart = i;
                }
            } else {
                dp[j] = 0; // Mark as not palindrome
            }
        }
    }
    return s.substring(longestStart, longestStart + longestLength);
}

// Test Cases
const testCases = [
    "babad",
    "cbbd",
    "a",
    "ac",
    "racecar",
    "madam",
    "level",
    "noon",
    "abbba",
    "abaxyzzyxf",
    "tattarrattat", // Added a longer palindrome test
    "forgeeksskeegfor", // Added another test case
    "bananas"
];

testCases.forEach((testCase, index) => {
    console.log(`\nTest Case ${index + 1}: ${testCase}`);
    console.log("Input String:", testCase);

    console.log("Brute Force:", longestPalindromeBruteForce(testCase));
    console.log("Dynamic Programming:", longestPalindromeDP(testCase));
    console.log("Expand Around Center:", longestPalindromeExpand(testCase));
    console.log("Manacher's Algorithm:", longestPalindromeManacher(testCase));
    console.log("Optimized DP:", longestPalindromeOptimizedDP(testCase));
});

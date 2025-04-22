/*
    Longest Palindromic Substring Problem:

    Given a string 's', find the longest palindromic substring in 's'.
    A palindromic substring is a string that reads the same backward as forward.

    For example:
    - Input: "babad"
    - Output: "bab" (or "aba")

    This problem can be solved using dynamic programming.  We will explore several approaches,
    from a basic dynamic programming solution to more optimized methods.
*/

/**
 * 1. Brute Force Approach
 * - Generate all possible substrings and check if each is a palindrome.
 * - Keep track of the longest palindromic substring found.
 *
 * - Time Complexity: O(n^3), where n is the length of the string.
 * - Space Complexity: O(1)
 */
function longestPalindromeBruteForce(s) {
    if (!s) return "";

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
 * 2. Dynamic Programming Approach
 * - Create a 2D table `dp` where `dp[i][j]` is true if the substring `s[i...j]` is a palindrome.
 * - Base case: `dp[i][i]` is always true (single characters are palindromes).
 * - Recurrence relation:
 * - `dp[i][j] = true` if `s[i] === s[j]` and (`j - i <= 2` or `dp[i+1][j-1] === true`)
 * - Track the start and end indices of the longest palindromic substring.
 *
 * - Time Complexity: O(n^2)
 * - Space Complexity: O(n^2)
 */
function longestPalindromeDP(s) {
    if (!s) return "";

    const n = s.length;
    const dp = Array(n).fill(null).map(() => Array(n).fill(false));
    let start = 0;
    let maxLength = 1;

    // Base case: Single characters are palindromes
    for (let i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // Check for palindromes of length 2
    for (let i = 0; i < n - 1; i++) {
        if (s[i] === s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check for palindromes of length greater than 2
    for (let k = 3; k <= n; k++) {
        for (let i = 0; i <= n - k; i++) {
            const j = i + k - 1;
            if (s[i] === s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }

    return s.substring(start, start + maxLength);
}



/**
 * 3. Optimized Dynamic Programming (Space Optimized)
 * - Instead of a full n x n table, we can optimize the space complexity to O(n)
 * - This approach is still DP, but it reduces memory usage.  It's more complex to implement.
 * - It uses a rolling array or a single 1D array to store the previous row's information.
 * - This optimization is valuable when memory is a significant constraint.
 *
 * - Time Complexity: O(n^2)
 * - Space Complexity: O(n) - Optimized
 */
function longestPalindromeDPSpaceOptimized(s) {
    if (!s) return "";

    const n = s.length;
    let longestStart = 0;
    let longestLength = 1;
    let dp = Array(n).fill(false); // 1D array

    for (let j = 0; j < n; j++) {
        for (let i = 0; i <= j; i++) {
            // dp[i] represents whether s[i...j] is a palindrome
            if (s[i] === s[j] && (j - i <= 2 || dp[i + 1])) {
                dp[i] = true; // s[i...j] is a palindrome
                if (j - i + 1 > longestLength) {
                    longestLength = j - i + 1;
                    longestStart = i;
                }
            } else {
                dp[i] = false; // s[i...j] is not a palindrome.
            }
        }
    }
    return s.substring(longestStart, longestStart + longestLength);
}



/**
 * 4. Expand Around Center Approach
 * - For each character in the string, consider it as the center of a potential palindrome.
 * - Expand outwards from the center (both left and right) and check for matching characters.
 * - This approach avoids the need for a full DP table.
 * - Handles both odd and even length palindromes.
 *
 * - Time Complexity: O(n^2)
 * - Space Complexity: O(1)
 */
function longestPalindromeExpandAroundCenter(s) {
    if (!s) return "";

    let start = 0;
    let end = 0;

    function expandAroundCenter(left, right) {
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            left--;
            right++;
        }
        return right - left - 1; // Length of the palindrome
    }

    for (let i = 0; i < s.length; i++) {
        // Odd length palindrome
        const len1 = expandAroundCenter(i, i);
        // Even length palindrome
        const len2 = expandAroundCenter(i, i + 1);
        const len = Math.max(len1, len2);
        if (len > end - start + 1) {
            start = i - Math.floor((len - 1) / 2);
            end = i + Math.floor(len / 2);
        }
    }
    return s.substring(start, end + 1);
}

/**
 * 5. Manacher's Algorithm
 * - The most efficient algorithm for finding the longest palindromic substring.
 * - Linear time complexity.
 * - It preprocesses the input string to handle even and odd length palindromes uniformly
 * - Uses an array to store the length of the palindrome centered at each position.
 *
 * - Time Complexity: O(n) - Linear time
 * - Space Complexity: O(n)
 */
function longestPalindromeManacher(s) {
    if (!s) return "";

    // Preprocess the string to handle even and odd lengths
    const processedString = `#${s.split('').join('#')}#`;  // e.g., "aba" becomes "#a#b#a#"
    const n = processedString.length;
    const p = Array(n).fill(0); // Array to store palindrome lengths
    let center = 0;
    let right = 0;
    let maxLen = 0;
    let maxCenter = 0;

    for (let i = 1; i < n; i++) {
        // Utilize symmetry
        if (i < right) {
            const mirror = 2 * center - i;
            p[i] = Math.min(right - i, p[mirror]);
        }

        // Expand around center i
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && processedString[i - (1 + p[i])] === processedString[i + (1 + p[i])]) {
            p[i]++;
        }

        // Update center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Track the maximum palindrome length
        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }
    // Extract the longest palindrome substring from the processed string
    const start = Math.floor((maxCenter - maxLen) / 2);
    return s.substring(start, start + maxLen);
}



// Example Usage and Verification
const testString = "babad";
const testString2 = "cbbd";
const testString3 = "a";
const testString4 = "ac";
const testString5 = "racecar";
const testString6 = "madam";
const testString7 = "civic";
const testString8 = "bananas";


console.log(`Input: "${testString}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString));       // Output: "bab" or "aba"
console.log("DP:", longestPalindromeDP(testString));                     // Output: "bab" or "aba"
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString)); // Output: "bab" or "aba"
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString)); // Output: "bab" or "aba"
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString));       // Output: "bab" or "aba"
console.log("\n");

console.log(`Input: "${testString2}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString2));       // Output: "bb"
console.log("DP:", longestPalindromeDP(testString2));                     // Output: "bb"
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString2)); // Output: "bb"
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString2)); // Output: "bb"
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString2));       // Output: "bb"
console.log("\n");

console.log(`Input: "${testString3}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString3));
console.log("DP:", longestPalindromeDP(testString3));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString3));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString3));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString3));
console.log("\n");

console.log(`Input: "${testString4}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString4));
console.log("DP:", longestPalindromeDP(testString4));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString4));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString4));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString4));
console.log("\n");

console.log(`Input: "${testString5}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString5));
console.log("DP:", longestPalindromeDP(testString5));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString5));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString5));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString5));
console.log("\n");

console.log(`Input: "${testString6}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString6));
console.log("DP:", longestPalindromeDP(testString6));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString6));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString6));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString6));
console.log("\n");

console.log(`Input: "${testString7}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString7));
console.log("DP:", longestPalindromeDP(testString7));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString7));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString7));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString7));
console.log("\n");

console.log(`Input: "${testString8}"`);
console.log("Brute Force:", longestPalindromeBruteForce(testString8));
console.log("DP:", longestPalindromeDP(testString8));
console.log("DP Space Optimized:", longestPalindromeDPSpaceOptimized(testString8));
console.log("Expand Around Center:", longestPalindromeExpandAroundCenter(testString8));
console.log("Manacher's Algorithm:", longestPalindromeManacher(testString8));
console.log("\n");

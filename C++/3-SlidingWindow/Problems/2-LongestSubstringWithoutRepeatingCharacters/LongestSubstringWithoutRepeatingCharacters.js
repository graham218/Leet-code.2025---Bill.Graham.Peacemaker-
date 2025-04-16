/*
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^3)
 * Space Complexity: O(min(n, m)) where m is the size of the character set
 */
function lengthOfLongestSubstringBruteForce(s) {
    if (!s) return 0;
    let longest = 0;
    for (let i = 0; i < s.length; i++) {
        for (let j = i; j < s.length; j++) {
            if (isUnique(s, i, j)) {
                longest = Math.max(longest, j - i + 1);
            }
        }
    }
    return longest;
}

function isUnique(s, start, end) {
    const set = new Set();
    for (let i = start; i <= end; i++) {
        if (set.has(s[i])) {
            return false;
        }
        set.add(s[i]);
    }
    return true;
}

/**
 * Approach 2: Sliding Window with Set
 * Time Complexity: O(n)
 * Space Complexity: O(min(m, n))
 */
function lengthOfLongestSubstringSlidingSet(s) {
    if (!s) return 0;
    let longest = 0;
    let left = 0;
    const set = new Set();
    for (let right = 0; right < s.length; right++) {
        while (set.has(s[right])) {
            set.delete(s[left]);
            left++;
        }
        set.add(s[right]);
        longest = Math.max(longest, right - left + 1);
    }
    return longest;
}

/**
 * Approach 3: Sliding Window with Map
 * Time Complexity: O(n)
 * Space Complexity: O(min(m, n))
 */
function lengthOfLongestSubstringSlidingMap(s) {
    if (!s) return 0;
    let longest = 0;
    let left = 0;
    const map = new Map();
    for (let right = 0; right < s.length; right++) {
        if (map.has(s[right])) {
            left = Math.max(left, map.get(s[right]) + 1);
        }
        map.set(s[right], right);
        longest = Math.max(longest, right - left + 1);
    }
    return longest;
}

/**
 * Approach 4: Optimized Sliding Window with ASCII Map (for ASCII strings)
 * Time Complexity: O(n)
 * Space Complexity: O(1) -  256 for ASCII characters
 */
function lengthOfLongestSubstringOptimized(s) {
    if (!s) return 0;
    let longest = 0;
    let left = 0;
    const charMap = new Array(256).fill(-1); // Assume ASCII characters
    for (let right = 0; right < s.length; right++) {
        const charCode = s.charCodeAt(right);
        if (charMap[charCode] >= left) {
            left = charMap[charCode] + 1;
        }
        charMap[charCode] = right;
        longest = Math.max(longest, right - left + 1);
    }
    return longest;
}

/**
 * Approach 5:  Sliding Window with Last Seen Array
 * Time Complexity: O(n)
 * Space Complexity: O(m) - where m is the size of the character set (e.g., 128 for ASCII, larger for Unicode)
 */
function lengthOfLongestSubstringLastSeen(s) {
    if (!s) return 0;

    const lastSeen = new Array(128).fill(-1); // Assuming ASCII characters
    let longest = 0;
    let start = 0;

    for (let i = 0; i < s.length; i++) {
        const charCode = s.charCodeAt(i);
        if (lastSeen[charCode] !== -1) {
            start = Math.max(start, lastSeen[charCode] + 1);
        }
        lastSeen[charCode] = i;
        longest = Math.max(longest, i - start + 1);
    }
    return longest;
}

// Test Cases
const testCases = [
    "abcabcbb",
    "bbbbb",
    "pwwkew",
    "",
    " ",
    "au",
    "dvdf",
    "abcdaefgb",
    "aab",
    "abba"
];

console.log("Longest Substring Without Repeating Characters");
console.log("---------------------------------------------");

testCases.forEach((testCase, index) => {
    console.log(`Test Case ${index + 1}: "${testCase}"`);
    console.log(`Brute Force: ${lengthOfLongestSubstringBruteForce(testCase)}`);
    console.log(`Sliding Window (Set): ${lengthOfLongestSubstringSlidingSet(testCase)}`);
    console.log(`Sliding Window (Map): ${lengthOfLongestSubstringSlidingMap(testCase)}`);
    console.log(`Optimized Sliding Window (ASCII): ${lengthOfLongestSubstringOptimized(testCase)}`);
    console.log(`Sliding Window (Last Seen Array): ${lengthOfLongestSubstringLastSeen(testCase)}`);
    console.log("---------------------------------------------");
});

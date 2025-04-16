/*
Problem: Longest Substring Without Repeating Characters

Given a string `s`, find the length of the longest substring without repeating characters.

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
0 <= s.length <= 5 * 10^4
s consists of English letters, digits, symbols and spaces.
*/

/**
 * Approach 1: Brute Force
 *
 * This approach iterates through all possible substrings and checks if each substring has repeating characters.
 * It's straightforward but has a time complexity of O(n^3), making it inefficient for large strings.
 *
 * Time Complexity: O(n^3) -  Three nested loops: two for generating substrings, one for checking uniqueness.
 * Space Complexity: O(min(n, m)) -  Space for the set is at most the size of the string or the character set.
 */
function longestSubstringWithoutRepeatingCharactersBruteForce(s) {
  if (!s) {
    console.log("Approach 1 (Brute Force): Input string is empty, returning 0.");
    return 0;
  }

  let longestLength = 0;
  const n = s.length;

  for (let i = 0; i < n; i++) {
    for (let j = i; j < n; j++) {
      const substring = s.substring(i, j + 1);
      if (isUnique(substring)) {
        longestLength = Math.max(longestLength, substring.length);
      }
    }
  }
  console.log(`Approach 1 (Brute Force): Longest substring length: ${longestLength}`);
  return longestLength;
}

/**
 * Helper function to check if a string has unique characters.
 *
 * Time Complexity: O(n) - Iterates through the string once.
 * Space Complexity: O(min(n, m)) -  Space for the set is at most the size of the string or the character set.
 */
function isUnique(str) {
  const charSet = new Set();
  for (let i = 0; i < str.length; i++) {
    const char = str[i];
    if (charSet.has(char)) {
      return false;
    }
    charSet.add(char);
  }
  return true;
}

/**
 * Approach 2: Sliding Window with Set
 *
 * This approach uses a sliding window and a Set to keep track of the characters in the current window.
 * If a repeating character is found, the window's start is moved to the right until the repeating character is removed.
 * This is more efficient than the brute force approach, with a time complexity of O(n).
 *
 * Time Complexity: O(n) -  Each character is visited at most twice (once by left, once by right).
 * Space Complexity: O(min(n, m)) -  Space for the set is at most the size of the string or the character set.
 */
function longestSubstringWithoutRepeatingCharactersSlidingWindowSet(s) {
  if (!s) {
    console.log("Approach 2 (Sliding Window with Set): Input string is empty, returning 0.");
    return 0;
  }

  let longestLength = 0;
  let left = 0;
  let right = 0;
  const charSet = new Set();
  const n = s.length;

  while (right < n) {
    const char = s[right];
    if (!charSet.has(char)) {
      charSet.add(char);
      longestLength = Math.max(longestLength, right - left + 1);
      right++;
    } else {
      charSet.delete(s[left]);
      left++;
    }
  }

  console.log(`Approach 2 (Sliding Window with Set): Longest substring length: ${longestLength}`);
  return longestLength;
}

/**
 * Approach 3: Sliding Window with Map
 *
 * Similar to the previous approach, but uses a Map to store the character indices.  This allows for more efficient
 * updating of the left pointer when a duplicate is found.  Instead of incrementing left one by one, we can jump it
 * to the position after the previous occurrence of the character.
 *
 * Time Complexity: O(n) - Each character is visited at most once.
 * Space Complexity: O(min(n, m)) -  Space for the map is at most the size of the string or the character set.
 */
function longestSubstringWithoutRepeatingCharactersSlidingWindowMap(s) {
  if (!s) {
    console.log("Approach 3 (Sliding Window with Map): Input string is empty, returning 0.");
    return 0;
  }

  let longestLength = 0;
  let left = 0;
  let right = 0;
  const charIndexMap = new Map();
  const n = s.length;

  while (right < n) {
    const char = s[right];
    if (charIndexMap.has(char)) {
      left = Math.max(left, charIndexMap.get(char) + 1); // Important:  Move left to *after* the previous occurrence
    }
    charIndexMap.set(char, right); // Store the *current* index of char
    longestLength = Math.max(longestLength, right - left + 1);
    right++;
  }

  console.log(`Approach 3 (Sliding Window with Map): Longest substring length: ${longestLength}`);
  return longestLength;
}

/**
 * Approach 4: Optimized Sliding Window with ASCII Character Set Assumption
 *
 * This approach optimizes the sliding window technique specifically for ASCII character sets (128 characters).
 * It uses a fixed-size array (instead of a Map or Set) to store the last seen index of each character.
 * This can be slightly faster in practice for ASCII strings due to the direct access provided by the array.
 *
 * Time Complexity: O(n) -  Each character is visited at most once.
 * Space Complexity: O(1) -  The character array has a fixed size of 128.
 */
function longestSubstringWithoutRepeatingCharactersSlidingWindowAscii(s) {
  if (!s) {
    console.log("Approach 4 (Optimized Sliding Window - ASCII): Input string is empty, returning 0.");
    return 0;
  }

  let longestLength = 0;
  let left = 0;
  let right = 0;
  const charIndexArray = new Array(128).fill(-1); // Assume ASCII character set
  const n = s.length;

  while (right < n) {
    const charCode = s.charCodeAt(right);
    if (charIndexArray[charCode] !== -1) {
      left = Math.max(left, charIndexArray[charCode] + 1);
    }
    charIndexArray[charCode] = right;
    longestLength = Math.max(longestLength, right - left + 1);
    right++;
  }

  console.log(`Approach 4 (Optimized Sliding Window - ASCII): Longest substring length: ${longestLength}`);
  return longestLength;
}

/**
 * Approach 5: Sliding Window with Last Occurrence Tracking (Generalized)
 *
 * This approach generalizes the idea of tracking the last occurrence of characters,
 * but it's designed to handle the full range of Unicode characters correctly.  It uses a Map.
 * It's similar to Approach 3, but explicitly handles edge cases and provides clear, modern JavaScript.
 *
 * Time Complexity: O(n) -  Single pass through the string.
 * Space Complexity: O(min(n, m)) -  Space for the map, where m is the size of the character set.
 */
function longestSubstringWithoutRepeatingCharactersSlidingWindow(s) {
    if (!s || s.length === 0) {
        console.log("Approach 5: (Sliding Window with Last Occurrence) Input string is empty, returning 0.");
        return 0;
    }

    let start = 0;
    let maxLength = 0;
    const charIndexMap = new Map();

    for (let end = 0; end < s.length; end++) {
        const currentChar = s[end];
        const lastSeenIndex = charIndexMap.get(currentChar);

        if (lastSeenIndex !== undefined && lastSeenIndex >= start) {
            start = lastSeenIndex + 1; // Move 'start' to the character after the last occurrence
        }

        charIndexMap.set(currentChar, end); // Update last seen index
        maxLength = Math.max(maxLength, end - start + 1);
    }

    console.log(`Approach 5: (Sliding Window with Last Occurrence) Longest substring length: ${maxLength}`);
    return maxLength;
}



// Test Cases
const testCases = [
  "abcabcbb",
  "bbbbb",
  "pwwkew",
  "",
  " ",
  "aab",
  "dvdf",
  "abcdeafbcd",
  "你好世界你好世界", // Test with non-ASCII characters
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+", //Long string
];

testCases.forEach((testCase, index) => {
  console.log(`\nTest Case ${index + 1}: Input: "${testCase}"`);
  longestSubstringWithoutRepeatingCharactersBruteForce(testCase);
  longestSubstringWithoutRepeatingCharactersSlidingWindowSet(testCase);
  longestSubstringWithoutRepeatingCharactersSlidingWindowMap(testCase);
  longestSubstringWithoutRepeatingCharactersSlidingWindowAscii(testCase);
  longestSubstringWithoutRepeatingCharactersSlidingWindow(testCase);
});

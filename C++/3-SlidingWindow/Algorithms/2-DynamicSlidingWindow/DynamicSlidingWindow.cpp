// Sliding Window - Dynamic Sliding Window - JavaScript Solutions

/*
Sliding Window Technique:
A powerful technique used to solve problems involving arrays or strings.  It reduces time complexity from O(n^2) or O(n^3) to O(n) by maintaining a "window" of elements.

Dynamic Sliding Window:
The size of the window can change (expand or contract) based on the problem's conditions.
*/

// --------------------------------------------------------------------------
// 1. Fixed Size Window Example: Find the maximum sum of a subarray of size k
// --------------------------------------------------------------------------

function maxSubarraySum(arr, k) {
  if (arr.length < k) {
    return null; // Handle invalid input
  }

  let maxSum = 0;
  let currentSum = 0;

  // Calculate the sum of the first window
  for (let i = 0; i < k; i++) {
    currentSum += arr[i];
  }
  maxSum = currentSum;

  // Slide the window through the rest of the array
  for (let i = k; i < arr.length; i++) {
    currentSum = currentSum - arr[i - k] + arr[i]; // Subtract the first element of the window and add the next element.
    maxSum = Math.max(maxSum, currentSum);       // Update the maximum sum if needed.
  }

  return maxSum;
}

// Example usage:
const arr1 = [1, 4, 2, 10, 2, 3, 1, 0, 20];
const k1 = 4;
console.log("1. Fixed Size Window - Max Subarray Sum:", maxSubarraySum(arr1, k1)); // Output: 24 (10 + 2 + 3 + 9) k=3, [10,2,3,1] k = 4


// --------------------------------------------------------------------------
// 2. Dynamic Window - Find the minimum window substring
// --------------------------------------------------------------------------
/*
Given a string s and a string t, find the minimum window in s which will contain all the characters in t.

Example:
s = "ADOBECODEBANC", t = "ABC"
Minimum window: "BANC"
*/
function minWindowSubstring(s, t) {
  if (s.length < t.length) return "";

  let tMap = new Map();
  for (let char of t) {
    tMap.set(char, (tMap.get(char) || 0) + 1);
  }

  let requiredChars = tMap.size;
  let windowStart = 0;
  let windowEnd = 0;
  let formedChars = 0;
  let windowCounts = new Map();
  let minWindowStart = 0;
  let minWindowLength = Infinity;

  while (windowEnd < s.length) {
    const char = s[windowEnd];
    windowCounts.set(char, (windowCounts.get(char) || 0) + 1);

    if (tMap.has(char) && windowCounts.get(char) === tMap.get(char)) {
      formedChars++;
    }

    while (formedChars === requiredChars && windowStart <= windowEnd) {
      const windowLength = windowEnd - windowStart + 1;
      if (windowLength < minWindowLength) {
        minWindowLength = windowLength;
        minWindowStart = windowStart;
      }

      const startChar = s[windowStart];
      windowCounts.set(startChar, windowCounts.get(startChar) - 1);
      if (tMap.has(startChar) && windowCounts.get(startChar) < tMap.get(startChar)) {
        formedChars--;
      }
      windowStart++;
    }
    windowEnd++;
  }
  return minWindowLength === Infinity ? "" : s.substring(minWindowStart, minWindowStart + minWindowLength);
}

// Example usage:
const s2 = "ADOBECODEBANC";
const t2 = "ABC";
console.log("2. Dynamic Window - Minimum Window Substring:", minWindowSubstring(s2, t2)); // Output: "BANC"

// --------------------------------------------------------------------------
// 3. Dynamic Window - Longest Substring Without Repeating Characters
// --------------------------------------------------------------------------
/*
Given a string, find the length of the longest substring without repeating characters.
Example:
Input: "abcabcbb"
Output: 3  (Longest substring: "abc")
*/

function longestUniqueSubstring(s) {
  let start = 0;
  let end = 0;
  let maxLength = 0;
  let charIndexMap = new Map(); // Store the last seen index of each character

  while (end < s.length) {
    const currentChar = s[end];

    if (charIndexMap.has(currentChar)) {
      // If the character is repeated, move the start pointer to the right of the previous occurrence
      start = Math.max(start, charIndexMap.get(currentChar) + 1);
    }

    charIndexMap.set(currentChar, end); // Update the last seen index of the character
    maxLength = Math.max(maxLength, end - start + 1); // Calculate the current substring length and update max
    end++;
  }
  return maxLength;
}

// Example usage:
const s3 = "abcabcbb";
console.log("3. Dynamic Window - Longest Substring Without Repeating Characters:", longestUniqueSubstring(s3)); // Output: 3

// --------------------------------------------------------------------------
// 4. Dynamic Window -  Maximum Sum Subarray of Size K (Handles Negative Numbers)
// --------------------------------------------------------------------------
function maxSumSubarray(arr, k) {
  if (arr.length < k) {
    return null;
  }

  let maxSum = -Infinity; // Initialize maxSum to negative infinity to handle arrays with negative numbers
  let currentSum = 0;

  for (let i = 0; i < k; i++) {
    currentSum += arr[i];
  }
  maxSum = currentSum;

  for (let i = k; i < arr.length; i++) {
    currentSum = currentSum - arr[i - k] + arr[i];
    maxSum = Math.max(maxSum, currentSum);
  }
  return maxSum;
}

// Example usage:
const arr4 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
const k4 = 3;
console.log("4. Dynamic Window - Maximum Sum Subarray of Size K (Handles Negative Numbers):", maxSumSubarray(arr4, k4)); // Output: 6

// --------------------------------------------------------------------------
// 5. Dynamic Window -  Longest Substring with At Most K Distinct Characters
// --------------------------------------------------------------------------

function longestSubstringWithKDistinctCharacters(s, k) {
  let start = 0;
  let end = 0;
  let maxLength = 0;
  let charCountMap = new Map();

  while (end < s.length) {
    const rightChar = s[end];
    charCountMap.set(rightChar, (charCountMap.get(rightChar) || 0) + 1);

    while (charCountMap.size > k) {
      const leftChar = s[start];
      charCountMap.set(leftChar, charCountMap.get(leftChar) - 1);
      if (charCountMap.get(leftChar) === 0) {
        charCountMap.delete(leftChar);
      }
      start++;
    }
    maxLength = Math.max(maxLength, end - start + 1);
    end++;
  }
  return maxLength;
}
// Example usage:
const s5 = "eceba";
const k5 = 2;
console.log("5. Dynamic Window - Longest Substring with At Most K Distinct Characters:", longestSubstringWithKDistinctCharacters(s5, k5)); // Output: 3

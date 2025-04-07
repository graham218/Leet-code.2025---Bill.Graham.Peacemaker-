/*
Sliding Window - Dynamic Sliding Window - JavaScript Solutions

The sliding window technique is used to reduce the time complexity of algorithms that involve contiguous subarrays or substrings.  A dynamic sliding window is one where the size of the window can increase or decrease based on the problem's constraints.

Here are 5 different approaches with real-world project implementations:
*/

// 1. Longest Substring Without Repeating Characters (LeetCode #3)
//   - Problem: Given a string, find the length of the longest substring without repeating characters.
//   - Implementation: Used in text editors, IDEs, and search engines for syntax highlighting, code completion, and query optimization.
//   - Example: "abcabcbb" -> 3 ("abc")
function longestSubstringWithoutRepeatingCharacters(s) {
  let start = 0;
  let end = 0;
  let maxLength = 0;
  const charIndexMap = {}; // Store the most recent index of each character

  while (end < s.length) {
    const currentChar = s[end];

    if (charIndexMap[currentChar] !== undefined && charIndexMap[currentChar] >= start) {
      // If the character is found within the current window, move the start of the window
      start = charIndexMap[currentChar] + 1;
    }

    charIndexMap[currentChar] = end; // Update the index of the current character
    maxLength = Math.max(maxLength, end - start + 1); // Calculate max length
    end++;
  }
  return maxLength;
}

// 2. Minimum Window Substring (LeetCode #76)
//   - Problem: Given a string S and a string T, find the minimum window in S which will contain all the characters in T.
//   - Implementation: Used in search engines, data mining, and bioinformatics for pattern matching, sequence alignment, and anomaly detection.
//   - Example: S = "ADOBECODEBANC", T = "ABC" -> "BANC"
function minWindowSubstring(s, t) {
  if (s.length < t.length) return "";

  const tCharCounts = {}; // Count occurrences of characters in T
  const windowCharCounts = {}; // Count occurrences of characters in the current window
  let requiredChars = 0; // Number of distinct characters needed from T
  let formedChars = 0; // Number of distinct characters from T that are satisfied in the window

  // Initialize tCharCounts
  for (const char of t) {
    if (!tCharCounts[char]) {
      tCharCounts[char] = 0;
      requiredChars++;
    }
    tCharCounts[char]++;
  }

  let start = 0;
  let end = 0;
  let minWindowLength = Infinity;
  let minWindowStart = 0;

  while (end < s.length) {
    const currentChar = s[end];
    windowCharCounts[currentChar] = (windowCharCounts[currentChar] || 0) + 1;

    if (tCharCounts[currentChar] && windowCharCounts[currentChar] === tCharCounts[currentChar]) {
      formedChars++;
    }

    while (start <= end && formedChars === requiredChars) {
      // Try to minimize the window size
      if (end - start + 1 < minWindowLength) {
        minWindowLength = end - start + 1;
        minWindowStart = start;
      }

      const startChar = s[start];
      windowCharCounts[startChar]--;

      if (tCharCounts[startChar] && windowCharCounts[startChar] < tCharCounts[startChar]) {
        formedChars--;
      }
      start++;
    }
    end++;
  }
  return minWindowLength === Infinity ? "" : s.substring(minWindowStart, minWindowStart + minWindowLength);
}

// 3. Longest Substring with At Most K Distinct Characters (LeetCode #340)
//   - Problem: Given a string s and an integer k, find the length of the longest substring of s that contains at most k distinct characters.
//   - Implementation: Used in data compression, text analysis, and network routing for data stream processing, quality of service (QoS) management, and traffic shaping.
//   - Example: s = "eceba", k = 2 -> 3 ("ece")
function longestSubstringWithAtMostKDistinctCharacters(s, k) {
  let start = 0;
  let end = 0;
  let maxLength = 0;
  const charCounts = {}; // Store character frequencies
  let distinctChars = 0;

  while (end < s.length) {
    const currentChar = s[end];
    if (!charCounts[currentChar]) {
      charCounts[currentChar] = 0;
      distinctChars++;
    }
    charCounts[currentChar]++;

    while (distinctChars > k) {
      // Shrink the window if it has more than k distinct characters
      const startChar = s[start];
      charCounts[startChar]--;
      if (charCounts[startChar] === 0) {
        delete charCounts[startChar];
        distinctChars--;
      }
      start++;
    }

    maxLength = Math.max(maxLength, end - start + 1);
    end++;
  }
  return maxLength;
}

// 4.  Maximum Sum Subarray of Size K (Fixed Window, but showing dynamic window concepts)
//   - Problem: Given an array of integers and a number k, find the maximum sum of a subarray of size k.
//   - Implementation: Used in financial analysis, signal processing, and image processing for trend analysis, moving averages, and feature extraction.
//   - Example: arr = [1, 4, 2, 10, 23, 3, 1, 0, 20], k = 4 -> 39 ( [10, 23, 3, 1] )
function maximumSumSubarray(arr, k) {
  if (arr.length < k) {
    return null; // Handle the case where the array is smaller than k
  }

  let maxSum = 0;
  let currentSum = 0;

  // Calculate the sum of the first k elements
  for (let i = 0; i < k; i++) {
    currentSum += arr[i];
  }
  maxSum = currentSum;

  // Slide the window through the rest of the array
  for (let i = k; i < arr.length; i++) {
    currentSum = currentSum - arr[i - k] + arr[i]; // Subtract the first element of the previous window and add the last element of the current window.
    maxSum = Math.max(maxSum, currentSum);
  }
  return maxSum;
}

// 5.  Find Longest Subarray with Sum Equal to K
//   - Problem: Given an array of integers and a target sum k, find the length of the longest subarray whose elements sum to k.
//   - Implementation: Used in network traffic analysis, log processing, and database query optimization.
//   - Example:  arr = [1, -1, 5, -2, 3], k = 3  -> 4 ([1, -1, 5, -2])
function longestSubarrayWithSumEqualToK(arr, k) {
    let maxLength = 0;
    let currentSum = 0;
    const sumIndexMap = {0: -1}; // Store the first occurrence of each sum, initialize 0 at index -1

    for (let i = 0; i < arr.length; i++) {
        currentSum += arr[i];

        if (sumIndexMap[currentSum - k] !== undefined) {
            maxLength = Math.max(maxLength, i - sumIndexMap[currentSum - k]);
        }

        if (sumIndexMap[currentSum] === undefined) {
            sumIndexMap[currentSum] = i; // Store first occurrence
        }
    }
    return maxLength;
}

// Test Cases and Output
console.log("1. Longest Substring Without Repeating Characters:");
console.log(longestSubstringWithoutRepeatingCharacters("abcabcbb")); // 3
console.log(longestSubstringWithoutRepeatingCharacters("bbbbb"));    // 1
console.log(longestSubstringWithoutRepeatingCharacters("pwwkew"));   // 3
console.log(longestSubstringWithoutRepeatingCharacters(""));       // 0

console.log("\n2. Minimum Window Substring:");
console.log(minWindowSubstring("ADOBECODEBANC", "ABC")); // "BANC"
console.log(minWindowSubstring("a", "a"));             // "a"
console.log(minWindowSubstring("a", "aa"));            // ""

console.log("\n3. Longest Substring with At Most K Distinct Characters:");
console.log(longestSubstringWithAtMostKDistinctCharacters("eceba", 2)); // 3
console.log(longestSubstringWithAtMostKDistinctCharacters("aa", 1));    // 2
console.log(longestSubstringWithAtMostKDistinctCharacters("abaccc", 2)); // 4
console.log(longestSubstringWithAtMostKDistinctCharacters("abaccc", 3)); // 6

console.log("\n4. Maximum Sum Subarray of Size K:");
console.log(maximumSumSubarray([1, 4, 2, 10, 23, 3, 1, 0, 20], 4)); // 39
console.log(maximumSumSubarray([100, 200, 300, 400], 2));          // 700
console.log(maximumSumSubarray([-1, -2, -3, -4], 2));             // -3
console.log(maximumSumSubarray([1, 2, 3, 4, 5], 6));             // null

console.log("\n5. Find Longest Subarray with Sum Equal to K:");
console.log(longestSubarrayWithSumEqualToK([1, -1, 5, -2, 3], 3));       // 4
console.log(longestSubarrayWithSumEqualToK([2, -1, 2, -3, 4, 5, 1, -1, 2, -3], 3)); // 4
console.log(longestSubarrayWithSumEqualToK([1, 2, 3, 4, 5], 15));             // 5
console.log(longestSubarrayWithSumEqualToK([1, 2, 3, 4, 5], 0));              // 0

/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is a substring of s2.

Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:
1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters.
*/

/**
 * Approach 1: Brute Force (Checking all permutations of s1)
 *
 * Time Complexity: O(N! * M), where N is the length of s1 and M is the length of s2.  (N! to generate permutations, M to check if a permutation is a substring)
 * Space Complexity: O(N), for storing the current permutation.
 */
const checkInclusionBruteForce = (s1, s2) => {
  const getPermutations = (str) => {
    if (str.length === 1) {
      return [str];
    }
    const permutations = [];
    for (let i = 0; i < str.length; i++) {
      const char = str[i];
      const remainingChars = str.slice(0, i) + str.slice(i + 1);
      const subPermutations = getPermutations(remainingChars);
      for (const subPermutation of subPermutations) {
        permutations.push(char + subPermutation);
      }
    }
    return permutations;
  };

  const permutations = getPermutations(s1);
  for (const permutation of permutations) {
    if (s2.includes(permutation)) {
      return true;
    }
  }
  return false;
};



/**
 * Approach 2: Using HashMap (Character Frequency Counting)
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(N), for the hash map to store character frequencies of s1.
 */
const checkInclusionHashMap = (s1, s2) => {
  if (s1.length > s2.length) {
    return false;
  }

  const s1Freq = {};
  for (const char of s1) {
    s1Freq[char] = (s1Freq[char] || 0) + 1;
  }

  for (let i = 0; i <= s2.length - s1.length; i++) {
    const s2Freq = {};
    for (let j = 0; j < s1.length; j++) {
      const char = s2[i + j];
      s2Freq[char] = (s2Freq[char] || 0) + 1;
    }
    if (Object.keys(s1Freq).length === Object.keys(s2Freq).length) { // Important optimization
        let match = true;
        for (const char in s1Freq) {
          if (s1Freq[char] !== s2Freq[char]) {
            match = false;
            break;
          }
        }
        if (match) return true;
    }
  }
  return false;
};



/**
 * Approach 3: Sliding Window (Optimized HashMap)
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(N), for the hash map to store character frequencies of s1.
 */
const checkInclusionSlidingWindow = (s1, s2) => {
  if (s1.length > s2.length) {
    return false;
  }

  const s1Freq = {};
  for (const char of s1) {
    s1Freq[char] = (s1Freq[char] || 0) + 1;
  }

  const s2Freq = {};
  let left = 0;
  let right = 0;
  let matchCount = 0;

  while (right < s2.length) {
    const rightChar = s2[right];
    s2Freq[rightChar] = (s2Freq[rightChar] || 0) + 1;

    if (s1Freq[rightChar] && s2Freq[rightChar] <= s1Freq[rightChar]) {
      matchCount++;
    }

    if (right - left + 1 === s1.length) {
      if (matchCount === s1.length) {
        return true;
      }

      const leftChar = s2[left];
      if (s1Freq[leftChar] && s2Freq[leftChar] <= s1Freq[leftChar]) {
        matchCount--;
      }
      s2Freq[leftChar]--;
      left++;
    }
    right++;
  }
  return false;
};

/**
 * Approach 4: Using Arrays for Frequency Counting (Optimized for lowercase English letters)
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(1), because the array size is fixed (26 for lowercase English letters).
 */
const checkInclusionArray = (s1, s2) => {
  if (s1.length > s2.length) {
    return false;
  }

  const s1Freq = new Array(26).fill(0);
  const s2Freq = new Array(26).fill(0);

  for (const char of s1) {
    s1Freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
  }

  for (let i = 0; i < s1.length; i++) {
    s2Freq[s2[i].charCodeAt(0) - 'a'.charCodeAt(0)]++;
  }

  for (let i = 0; i <= s2.length - s1.length; i++) {
    let match = true;
    for (let j = 0; j < 26; j++) {
      if (s1Freq[j] !== s2Freq[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      return true;
    }
    if (i < s2.length - s1.length) { // Important: Don't go out of bounds!
        s2Freq[s2[i].charCodeAt(0) - 'a'.charCodeAt(0)]--;
        s2Freq[s2[i + s1.length].charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

  }
  return false;
};

/**
 * Approach 5: Sliding Window with Array (Optimized for lowercase English letters)
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(1), because the array size is fixed (26 for lowercase English letters).
 */
const checkInclusionSlidingWindowArray = (s1, s2) => {
    if (s1.length > s2.length) return false;

    const s1Freq = new Array(26).fill(0);
    const s2Freq = new Array(26).fill(0);

    for (let i = 0; i < s1.length; i++) {
        s1Freq[s1[i].charCodeAt(0) - 'a'.charCodeAt(0)]++;
        s2Freq[s2[i].charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let matches = 0;
    for (let i = 0; i < 26; i++) {
        if (s1Freq[i] === s2Freq[i]) {
            matches++;
        }
    }

    let left = 0;
    for (let right = s1.length; right < s2.length; right++) {
        if (matches === 26) return true;

        let rightCharIndex = s2[right].charCodeAt(0) - 'a'.charCodeAt(0);
        let leftCharIndex = s2[left].charCodeAt(0) - 'a'.charCodeAt(0);

        s2Freq[rightCharIndex]++;
        if (s2Freq[rightCharIndex] === s1Freq[rightCharIndex]) {
            matches++;
        } else if (s2Freq[rightCharIndex] === s1Freq[rightCharIndex] + 1) {
            matches--;
        }

        s2Freq[leftCharIndex]--;
        if (s2Freq[leftCharIndex] === s1Freq[leftCharIndex]) {
            matches++;
        } else if (s2Freq[leftCharIndex] === s1Freq[leftCharIndex] - 1) {
            matches--;
        }
        left++;
    }
    return matches === 26;
};



// Example Usage and Verification
const s1 = "ab";
const s2 = "eidbaooo";
const s3 = "eidboaoo";

console.log("Input:");
console.log("s1:", s1);
console.log("s2:", s2);
console.log("s3:", s3);
console.log("\nOutput:");

// Brute Force
console.log("\nApproach 1: Brute Force");
console.log("s2 contains permutation of s1:", checkInclusionBruteForce(s1, s2)); // true
console.log("s3 contains permutation of s1:", checkInclusionBruteForce(s1, s3)); // false

// HashMap
console.log("\nApproach 2: Using HashMap");
console.log("s2 contains permutation of s1:", checkInclusionHashMap(s1, s2)); // true
console.log("s3 contains permutation of s1:", checkInclusionHashMap(s1, s3)); // false

// Sliding Window
console.log("\nApproach 3: Sliding Window");
console.log("s2 contains permutation of s1:", checkInclusionSlidingWindow(s1, s2)); // true
console.log("s3 contains permutation of s1:", checkInclusionSlidingWindow(s1, s3)); // false

// Array
console.log("\nApproach 4: Using Arrays");
console.log("s2 contains permutation of s1:", checkInclusionArray(s1, s2)); // true
console.log("s3 contains permutation of s1:", checkInclusionArray(s1, s3)); // false

// Sliding Window Array
console.log("\nApproach 5: Sliding Window with Array");
console.log("s2 contains permutation of s1:", checkInclusionSlidingWindowArray(s1, s2)); // true
console.log("s3 contains permutation of s1:", checkInclusionSlidingWindowArray(s1, s3)); // false

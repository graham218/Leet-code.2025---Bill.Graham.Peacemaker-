/*
Sliding Window - Minimum Window Substring
----------------------------------------

Given two strings `s` and `t`, find the minimum window in `s` which will contain all the characters in `t`.

For example:
s = "ADOBECODEBANC"
t = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in s that covers all characters in t, return the empty string "".
If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in s.

Here are 5 different approaches to solve this problem:
1. Brute Force
2. Sliding Window with Hash Map
3. Sliding Window with Array as Frequency Counter
4. Optimized Sliding Window with Two Pointers
5. Sliding Window with Character Frequency Matching
*/

/**
 * 1. Brute Force Approach
 * -----------------------
 * Generate all possible substrings of `s` and check if each substring contains all the characters of `t`.
 * Keep track of the minimum window found so far.
 *
 * Time Complexity: O(n^3) - where n is the length of string `s`
 * Space Complexity: O(m) - where m is the length of string `t`
 */
function minWindowBruteForce(s, t) {
  if (s.length < t.length) return "";

  let minWindow = "";

  for (let i = 0; i < s.length; i++) {
    for (let j = i; j < s.length; j++) {
      const sub = s.substring(i, j + 1);
      if (containsAllChars(sub, t)) {
        if (minWindow === "" || sub.length < minWindow.length) {
          minWindow = sub;
        }
      }
    }
  }
  return minWindow;
}

function containsAllChars(sub, t) {
  const tCharCount = {};
  for (const char of t) {
    tCharCount[char] = (tCharCount[char] || 0) + 1;
  }

  const subCharCount = {};
  for (const char of sub) {
    subCharCount[char] = (subCharCount[char] || 0) + 1;
  }

  for (const char in tCharCount) {
    if (!subCharCount[char] || subCharCount[char] < tCharCount[char]) {
      return false;
    }
  }
  return true;
}



/**
 * 2. Sliding Window with Hash Map
 * -----------------------------
 * Use a hash map to store the frequency of characters in `t`.
 * Use a sliding window to iterate through `s`.
 * Expand the window until it contains all the characters in `t`.
 * Contract the window to find the minimum window.
 *
 * Time Complexity: O(n) - where n is the length of string `s`
 * Space Complexity: O(m) - where m is the length of string `t`
 */
function minWindowHashMap(s, t) {
  if (s.length < t.length) return "";

  const tCharCount = {};
  for (const char of t) {
    tCharCount[char] = (tCharCount[char] || 0) + 1;
  }

  let left = 0;
  let right = 0;
  let minWindow = "";
  let requiredChars = Object.keys(tCharCount).length;
  let formedChars = 0;
  const windowCharCount = {};

  while (right < s.length) {
    const char = s[right];
    windowCharCount[char] = (windowCharCount[char] || 0) + 1;

    if (tCharCount[char] && windowCharCount[char] === tCharCount[char]) {
      formedChars++;
    }

    while (left <= right && formedChars === requiredChars) {
      const window = s.substring(left, right + 1);
      if (minWindow === "" || window.length < minWindow.length) {
        minWindow = window;
      }

      const leftChar = s[left];
      windowCharCount[leftChar]--;
      if (tCharCount[leftChar] && windowCharCount[leftChar] < tCharCount[leftChar]) {
        formedChars--;
      }
      left++;
    }
    right++;
  }
  return minWindow;
}



/**
 * 3. Sliding Window with Array as Frequency Counter
 * -----------------------------------------------
 * Use an array of size 128 (assuming ASCII characters) to store the frequency of characters in `t`.
 * Use a sliding window to iterate through `s`.
 * Expand the window until it contains all the characters in `t`.
 * Contract the window to find the minimum window.
 *
 * Time Complexity: O(n) - where n is the length of string `s`
 * Space Complexity: O(1) -  O(128) which simplifies to O(1)
 */
function minWindowArray(s, t) {
  if (s.length < t.length) return "";

  const tCharCount = new Array(128).fill(0);
  for (const char of t) {
    tCharCount[char.charCodeAt(0)]++;
  }

  let left = 0;
  let right = 0;
  let minWindow = "";
  let requiredChars = t.length;
  let formedChars = 0;
  const windowCharCount = new Array(128).fill(0);

  while (right < s.length) {
    const charCode = s[right].charCodeAt(0);
    windowCharCount[charCode]++;

    if (tCharCount[charCode] > 0 && windowCharCount[charCode] <= tCharCount[charCode]) {
      formedChars++;
    }

    while (left <= right && formedChars === requiredChars) {
      const window = s.substring(left, right + 1);
      if (minWindow === "" || window.length < minWindow.length) {
        minWindow = window;
      }

      const leftCharCode = s[left].charCodeAt(0);
      windowCharCount[leftCharCode]--;
      if (tCharCount[leftCharCode] > 0 && windowCharCount[leftCharCode] < tCharCount[leftCharCode]) {
        formedChars--;
      }
      left++;
    }
    right++;
  }
  return minWindow;
}



/**
 * 4. Optimized Sliding Window with Two Pointers
 * --------------------------------------------
 * Similar to the sliding window approach, but optimizes the window contraction.
 * Use two pointers, `left` and `right`, to maintain the window.
 * Move the `right` pointer to expand the window until it contains all the characters in `t`.
 * Move the `left` pointer to contract the window while maintaining the condition.
 *
 * Time Complexity: O(n) - where n is the length of string `s`
 * Space Complexity: O(m) - where m is the length of string `t`
 */
function minWindowTwoPointers(s, t) {
  if (s.length < t.length) return "";

  const tCharCount = {};
  for (const char of t) {
    tCharCount[char] = (tCharCount[char] || 0) + 1;
  }

  let left = 0;
  let right = 0;
  let minWindow = "";
  let requiredChars = Object.keys(tCharCount).length;
  let formedChars = 0;
  const windowCharCount = {};
  const filteredS = [];
  const filteredSIndex = [];

  // Filter the string s to only include characters in t, along with their indices.
  for (let i = 0; i < s.length; i++) {
    if (tCharCount[s[i]]) {
      filteredS.push(s[i]);
      filteredSIndex.push(i);
    }
  }
  while (right < filteredS.length) {
    const char = filteredS[right];
    windowCharCount[char] = (windowCharCount[char] || 0) + 1;

    if (tCharCount[char] && windowCharCount[char] === tCharCount[char]) {
      formedChars++;
    }

    while (left <= right && formedChars === requiredChars) {
      const start = filteredSIndex[left];
      const end = filteredSIndex[right];
      const window = s.substring(start, end + 1);
      if (minWindow === "" || window.length < minWindow.length) {
        minWindow = window;
      }

      const leftChar = filteredS[left];
      windowCharCount[leftChar]--;
      if (tCharCount[leftChar] && windowCharCount[leftChar] < tCharCount[leftChar]) {
        formedChars--;
      }
      left++;
    }
    right++;
  }
  return minWindow;
}

/**
 * 5. Sliding Window with Character Frequency Matching
 * ------------------------------------------------
 * Uses a slightly different approach to check if the window contains all required characters.
 * It maintains a count of matched characters and updates it as the window slides.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(m)
 */
function minWindowFreqMatch(s, t) {
    if (s.length < t.length) return "";

    const tFreq = {};
    for (const char of t) {
        tFreq[char] = (tFreq[char] || 0) + 1;
    }

    let left = 0, right = 0;
    let minWindow = "";
    let matched = 0;
    const windowFreq = {};

    while (right < s.length) {
        const char = s[right];
        if (tFreq[char]) {
            windowFreq[char] = (windowFreq[char] || 0) + 1;
            if (windowFreq[char] === tFreq[char]) {
                matched++;
            }
        }

        while (left <= right && matched === Object.keys(tFreq).length) {
            const window = s.substring(left, right + 1);
            if (minWindow === "" || window.length < minWindow.length) {
                minWindow = window;
            }

            const leftChar = s[left];
            if (tFreq[leftChar]) {
                windowFreq[leftChar]--;
                if (windowFreq[leftChar] < tFreq[leftChar]) {
                    matched--;
                }
            }
            left++;
        }
        right++;
    }
    return minWindow;
}



// Example Usage and console logs
const s = "ADOBECODEBANC";
const t = "ABC";

console.log("Input: s = 'ADOBECODEBANC', t = 'ABC'");
console.log("----------------------------------------");
console.log("1. Brute Force:", minWindowBruteForce(s, t)); // Output: "BANC"
console.log("2. Sliding Window with Hash Map:", minWindowHashMap(s, t)); // Output: "BANC"
console.log("3. Sliding Window with Array:", minWindowArray(s, t)); // Output: "BANC"
console.log("4. Optimized Sliding Window:", minWindowTwoPointers(s, t)); // Output: "BANC"
console.log("5. Sliding Window with Frequency Matching:", minWindowFreqMatch(s, t)); // Output: "BANC"

const s2 = "aab";
const t2 = "a";
console.log("\nInput: s = 'aab', t = 'a'");
console.log("----------------------------------------");
console.log("1. Brute Force:", minWindowBruteForce(s2, t2));
console.log("2. Sliding Window with Hash Map:", minWindowHashMap(s2, t2));
console.log("3. Sliding Window with Array:", minWindowArray(s2, t2));
console.log("4. Optimized Sliding Window:", minWindowTwoPointers(s2, t2));
console.log("5. Sliding Window with Frequency Matching:", minWindowFreqMatch(s2, t2));

const s3 = "cabwefgewcwaefgcf";
const t3 = "cae";
console.log("\nInput: s = 'cabwefgewcwaefgcf', t = 'cae'");
console.log("----------------------------------------");
console.log("1. Brute Force:", minWindowBruteForce(s3, t3));
console.log("2. Sliding Window with Hash Map:", minWindowHashMap(s3, t3));
console.log("3. Sliding Window with Array:", minWindowArray(s3, t3));
console.log("4. Optimized Sliding Window:", minWindowTwoPointers(s3, t3));
console.log("5. Sliding Window with Frequency Matching:", minWindowFreqMatch(s3, t3));

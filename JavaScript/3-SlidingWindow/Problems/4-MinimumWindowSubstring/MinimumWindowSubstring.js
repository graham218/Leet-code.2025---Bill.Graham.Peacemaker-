/**
 * Sliding Window - Minimum Window Substring
 *
 * Given two strings s and t, find the minimum window in s which will contain all the characters in t.
 *
 * Example:
 *
 * s = "ADOBECODEBANC"
 * t = "ABC"
 *
 * Minimum window is "BANC".
 *
 * Note:
 * If there is no such window in s that covers all characters in t, return the empty string "".
 * If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in s.
 */

/**
 * Approach 1: Brute Force
 *
 * Generate all possible substrings of s and check if each substring contains all the characters in t.
 * Keep track of the minimum window found so far.
 *
 * Time Complexity: O(n^3) - where n is the length of s
 * Space Complexity: O(m) - where m is the length of t
 */
function minWindowBruteForce(s, t) {
  if (s.length < t.length) {
    return "";
  }

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

/**
 * Helper function to check if a substring contains all characters of t
 */
function containsAllChars(sub, t) {
  const tCharCount = {};
  for (const char of t) {
    tCharCount[char] = (tCharCount[char] || 0) + 1;
  }

  const subCharCount = {};
  for (const char of sub) {
    subCharCount[char] = (subCharCount[char] || 0) + 1;
  }

  for (const char of t) {
    if (!subCharCount[char] || subCharCount[char] < tCharCount[char]) {
      return false;
    }
  }
  return true;
}

/**
 * Approach 2: Sliding Window with Hash Map
 *
 * Use a sliding window to keep track of the characters in the current window.
 * Use a hash map to store the frequency of characters in t.
 * Expand the window until it contains all the characters in t.
 * Then, contract the window until it no longer contains all the characters in t.
 * Keep track of the minimum window found so far.
 *
 * Time Complexity: O(n) - where n is the length of s
 * Space Complexity: O(m) - where m is the length of t
 */
function minWindowSlidingWindow(s, t) {
  if (s.length < t.length) {
    return "";
  }

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
 * Approach 3: Optimized Sliding Window with Hash Map
 *
 * Similar to approach 2, but with some optimizations:
 * - Use two pointers, start and end, to represent the window.
 * - Use a map to store the required characters and their counts.
 * - Use a counter to track the number of satisfied characters.
 * - Move the end pointer to expand the window until all required characters are satisfied.
 * - Move the start pointer to shrink the window while maintaining the satisfied condition.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(m)
 */

function minWindowOptimized(s, t) {
    if (s.length < t.length) return "";

    const need = new Map();
    for (const char of t) {
        need.set(char, (need.get(char) || 0) + 1);
    }

    let left = 0;
    let right = 0;
    let minLen = Infinity;
    let minStart = 0;
    let formed = 0;

    while (right < s.length) {
        const char = s[right];
        if (need.has(char)) {
            need.set(char, need.get(char) - 1);
            if (need.get(char) === 0) {
                formed++;
            }
        }

        while (left <= right && formed === need.size) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            const leftChar = s[left];
            if (need.has(leftChar)) {
                need.set(leftChar, need.get(leftChar) + 1);
                if (need.get(leftChar) > 0) {
                    formed--;
                }
            }
            left++;
        }
        right++;
    }
    return minLen === Infinity ? "" : s.substring(minStart, minStart + minLen);
}


/**
 * Approach 4: Sliding Window with Array as Hash Map (for ASCII chars)
 *
 * If the characters are within the ASCII range (0-255), we can use an array instead of a hash map
 * to store the frequency of characters. This can be slightly faster in some cases.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) -  O(256) which is constant.
 */
function minWindowASCII(s, t) {
  if (s.length < t.length) {
    return "";
  }

  const tCharCount = new Array(256).fill(0);
  for (const char of t) {
    tCharCount[char.charCodeAt(0)]++;
  }

  let left = 0;
  let right = 0;
  let minWindow = "";
  let requiredChars = t.length;

  while (right < s.length) {
    const charCode = s.charCodeAt(right);
    if (tCharCount[charCode] > 0) {
      requiredChars--;
    }
    tCharCount[charCode]--;

    while (requiredChars === 0) {
      const window = s.substring(left, right + 1);
      if (minWindow === "" || window.length < minWindow.length) {
        minWindow = window;
      }

      const leftCharCode = s.charCodeAt(left);
      tCharCount[leftCharCode]++;
      if (tCharCount[leftCharCode] > 0) {
        requiredChars++;
      }
      left++;
    }
    right++;
  }
  return minWindow;
}

/**
 * Approach 5: Template
 *
 * A more generalized template for the sliding window problem.
 */
function minWindowTemplate(s, t) {
    if (s.length < t.length) return "";

    const need = new Map();
    for (const char of t) need.set(char, (need.get(char) || 0) + 1);

    let left = 0, right = 0;
    let missing = t.length; // Number of characters still needed
    let start = 0, end = 0;     // Start and end of the minimum window

    while (right < s.length) {
        // Expand the window
        const charR = s[right];
        if (need.has(charR)) {
            need.set(charR, need.get(charR) - 1);
            if (need.get(charR) >= 0) missing--; // Important: >= 0
        }
        right++;

        // Contract the window
        while (left < right && missing === 0) {
            if (end === 0 || right - left < end - start) { // end===0 for first time
                start = left;
                end = right;
            }

            const charL = s[left];
            if (need.has(charL)) {
                need.set(charL, need.get(charL) + 1);
                if (need.get(charL) > 0) missing++;
            }
            left++;
        }
    }
    return end === 0 ? "" : s.substring(start, end);
}



// Example usage:
const s = "ADOBECODEBANC";
const t = "ABC";

console.log("Input: s =", s, ", t =", t);
console.log("Approach 1: Brute Force:", minWindowBruteForce(s, t)); // Output: "BANC"
console.log("Approach 2: Sliding Window:", minWindowSlidingWindow(s, t)); // Output: "BANC"
console.log("Approach 3: Optimized Sliding Window:", minWindowOptimized(s, t)); // Output: "BANC"
console.log("Approach 4: Sliding Window with Array (ASCII):", minWindowASCII(s, t)); // Output: "BANC"
console.log("Approach 5: Template:", minWindowTemplate(s, t)); // Output: "BANC"

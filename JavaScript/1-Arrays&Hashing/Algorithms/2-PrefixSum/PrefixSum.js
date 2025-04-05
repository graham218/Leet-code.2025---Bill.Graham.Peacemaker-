/**
 * 242. Arrays & Hashing >> Valid Anagram
 *
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
 *
 * Example 1:
 *
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 *
 * Example 2:
 *
 * Input: s = "rat", t = "car"
 * Output: false
 *
 * Constraints:
 *
 * 1 <= s.length, t.length <= 5 * 104
 * s and t consist of lowercase English letters.
 */

/**
 * Approach 1: Sorting
 *
 * Time Complexity: O(n log n) - due to sorting
 * Space Complexity: O(n) -  depending on the sorting algorithm implementation
 *
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
const isAnagramSort = (s, t) => {
  if (s.length !== t.length) {
    return false;
  }
  const sortedS = s.split('').sort().join('');
  const sortedT = t.split('').sort().join('');
  return sortedS === sortedT;
};

/**
 * Approach 2: Hash Map (Frequency Counting)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) -  The map will store at most 26 key-value pairs (lowercase English letters).
 *
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
const isAnagramHashMap = (s, t) => {
  if (s.length !== t.length) {
    return false;
  }

  const map = new Map();

  // Count character frequencies in s
  for (const char of s) {
    map.set(char, (map.get(char) || 0) + 1);
  }

  // Decrement character frequencies in t
  for (const char of t) {
    if (!map.has(char)) {
      return false; // Character not in s
    }
    const count = map.get(char) - 1;
    if (count < 0) {
      return false; // Too many of this character in t
    }
    map.set(char, count);
  }

  // If all counts are zero, it's an anagram
  for (const count of map.values()) {
    if (count !== 0) {
      return false;
    }
  }
  return true;
};

/**
 * Approach 3: Array as a Hash Table (Frequency Counting)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) -  Uses a fixed-size array of 26
 *
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
const isAnagramArray = (s, t) => {
  if (s.length !== t.length) {
    return false;
  }

  const charCounts = new Array(26).fill(0); // For lowercase English letters

  // Count character frequencies in s
  for (const char of s) {
    const charCode = char.charCodeAt(0) - 'a'.charCodeAt(0);
    charCounts[charCode]++;
  }

  // Decrement character frequencies in t
  for (const char of t) {
    const charCode = char.charCodeAt(0) - 'a'.charCodeAt(0);
    charCounts[charCode]--;
    if (charCounts[charCode] < 0) {
      return false; // Too many of this character in t
    }
  }

  // If all counts are zero, it's an anagram.  Not strictly necessary, as the previous loop
  // already checks for negative counts, but kept for clarity.
  for (const count of charCounts) {
    if (count !== 0) {
      return false;
    }
  }
  return true;
};

/**
 * Approach 4:  Using Object (Frequency Counting)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) - The object will store at most 26 key-value pairs.
 *
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
const isAnagramObject = (s, t) => {
  if (s.length !== t.length) {
    return false;
  }

  const sCharCounts = {};
  const tCharCounts = {};

  for (const char of s) {
    sCharCounts[char] = (sCharCounts[char] || 0) + 1;
  }

  for (const char of t) {
    tCharCounts[char] = (tCharCounts[char] || 0) + 1;
  }

  for (const char in sCharCounts) {
    if (sCharCounts[char] !== (tCharCounts[char] || 0)) {
      return false;
    }
  }

  for (const char in tCharCounts) {
     if (tCharCounts[char] !== (sCharCounts[char] || 0)) {
      return false;
    }
  }

  return true;
};

/**
 * Approach 5:  Using Regular Expression and Replace (Least Efficient)
 *
 * Time Complexity: O(n^2) in the worst case due to replace
 * Space Complexity: O(n)
 *
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
const isAnagramRegex = (s, t) => {
  if (s.length !== t.length) {
    return false;
  }

  let tempT = t;
  for (const char of s) {
    const index = tempT.indexOf(char);
    if (index === -1) {
      return false;
    }
    tempT = tempT.slice(0, index) + tempT.slice(index + 1); // Remove char from tempT
  }
  return tempT === "";
};



// Example Usage and Output
const s1 = "anagram";
const t1 = "nagaram";
console.log(`Input: s = "${s1}", t = "${t1}"`);
console.log(`Sorting: ${isAnagramSort(s1, t1)}`); // Output: true
console.log(`Hash Map: ${isAnagramHashMap(s1, t1)}`); // Output: true
console.log(`Array: ${isAnagramArray(s1, t1)}`); // Output: true
console.log(`Object: ${isAnagramObject(s1, t1)}`); // Output: true
console.log(`Regex: ${isAnagramRegex(s1, t1)}`);     // Output: true

const s2 = "rat";
const t2 = "car";
console.log(`\nInput: s = "${s2}", t = "${t2}"`);
console.log(`Sorting: ${isAnagramSort(s2, t2)}`); // Output: false
console.log(`Hash Map: ${isAnagramHashMap(s2, t2)}`); // Output: false
console.log(`Array: ${isAnagramArray(s2, t2)}`); // Output: false
console.log(`Object: ${isAnagramObject(s2, t2)}`); // Output: false
console.log(`Regex: ${isAnagramRegex(s2, t2)}`);     // Output: false

const s3 = "aacc";
const t3 = "ccac";
console.log(`\nInput: s = "${s3}", t = "${t3}"`);
console.log(`Sorting: ${isAnagramSort(s3, t3)}`);
console.log(`Hash Map: ${isAnagramHashMap(s3, t3)}`);
console.log(`Array: ${isAnagramArray(s3, t3)}`);
console.log(`Object: ${isAnagramObject(s3, t3)}`);
console.log(`Regex: ${isAnagramRegex(s3, t3)}`);

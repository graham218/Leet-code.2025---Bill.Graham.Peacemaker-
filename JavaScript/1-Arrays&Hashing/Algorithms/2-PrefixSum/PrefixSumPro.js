/**
 * 1. Arrays & Hashing >> Valid Anagram
 *
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * Example 1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 *
 * Example 2:
 * Input: s = "rat", t = "car"
 * Output: false
 *
 * Constraints:
 * 1 <= s.length, t.length <= 5 * 10^4
 * s and t consist of lowercase English letters.
 */

/**
 * Approach 1: Sorting
 *
 * Time Complexity: O(n log n), where n is the length of the strings.
 * Space Complexity: O(n) in JavaScript (due to the string sort), but could be O(1) in other languages.
 *
 * Description:
 * The simplest approach is to sort both strings. If the sorted strings are equal, then t is an anagram of s.
 *
 * Real-world application:
 * This approach is useful in scenarios where you need to compare if two sets of data are the same, regardless of order.
 * For example, you could use this to check if two playlists contain the same songs, or if two sets of database query
 * results contain the same records (when order doesn't matter).
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
 * Approach 2: Character Counting with Object
 *
 * Time Complexity: O(n), where n is the length of the strings.
 * Space Complexity: O(1), because the size of the object is limited by the alphabet size (26 in this case).
 *
 * Description:
 * This approach uses a hash map (JavaScript object) to count the frequency of each character in the first string.
 * Then, it iterates through the second string, decrementing the counts for each character. If a count goes negative
 * or if the counts object has non-zero values at the end, the strings are not anagrams.
 *
 * Real-world application:
 * This is a common technique for analyzing text data. For example, you could use it to determine if two search queries
 * are composed of the same keywords, or to check if two documents have a similar distribution of characters.  It's
 * used in text processing, search engines, and data analysis.
 */
const isAnagramCharacterCountObject = (s, t) => {
    if (s.length !== t.length) {
        return false;
    }

    const charCounts = {};

    for (const char of s) {
        charCounts[char] = (charCounts[char] || 0) + 1;
    }

    for (const char of t) {
        if (!charCounts[char]) {
            return false;
        }
        charCounts[char]--;
    }

    for (const char in charCounts) {
        if (charCounts[char] !== 0) {
            return false;
        }
    }

    return true;
};

/**
 * Approach 3: Character Counting with Map
 *
 * Time Complexity: O(n), where n is the length of the strings.
 * Space Complexity: O(1), because the size of the map is limited by the alphabet size (26 in this case).
 *
 * Description:
 * Similar to the object approach, but uses a Map.
 *
 * Real-world application:
 * Like the object approach, this is useful for text analysis.  Using a Map might be preferred in scenarios
 * where you need the features of a Map (e.g., guaranteed key order, ability to use objects as keys),
 * or if you're working in a code style that favors Maps.
 */
const isAnagramCharacterCountMap = (s, t) => {
    if (s.length !== t.length) {
        return false;
    }

    const charCounts = new Map();

    for (const char of s) {
        charCounts.set(char, (charCounts.get(char) || 0) + 1);
    }

    for (const char of t) {
        if (!charCounts.has(char)) {
            return false;
        }
        charCounts.set(char, charCounts.get(char) - 1);
    }

    for (const count of charCounts.values()) {
        if (count !== 0) {
            return false;
        }
    }

    return true;
};

/**
 * Approach 4: Using Array.prototype.reduce()
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Description:
 * This approach uses the reduce method to create the character count object for string s,
 * and then checks the counts while iterating through string t.
 *
 * Real-world application:
 * This demonstrates a functional approach to the problem.  It can be useful in data processing pipelines
 * where you want to transform data using functional methods.
 */
const isAnagramReduce = (s, t) => {
    if (s.length !== t.length) {
        return false;
    }

    const charCounts = s.split('').reduce((counts, char) => {
        counts[char] = (counts[char] || 0) + 1;
        return counts;
    }, {});

    for (const char of t) {
        if (!charCounts[char]) {
            return false;
        }
        charCounts[char]--;
    }

     for (const char in charCounts) {
        if (charCounts[char] !== 0) {
            return false;
        }
    }

    return true;
};

/**
 * Approach 5: Bitwise Operations (Only for lowercase alphabets)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Description:
 * This approach uses bitwise operations to track the characters present in both strings.  It's highly optimized
 * for space, but only works for lowercase English letters.  We use a single integer to represent the presence
 * of each letter.  This approach is clever, but less general.
 *
 * Real-world application:
 * This kind of bit manipulation is very efficient and can be used in performance-critical scenarios
 * where memory is extremely constrained.  For example, it might be used in embedded systems programming
 * or in low-level graphics processing.  However, it's less common in general application development
 * due to its limitations (like only working with lowercase letters here).
 */
const isAnagramBitwise = (s, t) => {
    if (s.length !== t.length) {
        return false;
    }

    let sMask = 0;
    let tMask = 0;

    for (let i = 0; i < s.length; i++) {
        sMask |= 1 << (s.charCodeAt(i) - 'a'.charCodeAt(0));
        tMask |= 1 << (t.charCodeAt(i) - 'a'.charCodeAt(0));
    }
    if (sMask !== tMask) return false;

    const charCounts = {};

    for (const char of s) {
        charCounts[char] = (charCounts[char] || 0) + 1;
    }

    for (const char of t) {
        charCounts[char]--;
    }
      for (const char in charCounts) {
        if (charCounts[char] !== 0) {
            return false;
        }
    }

    return true;
};

/**
 * Approach 6: Using JSON.stringify
 *
 * Time Complexity: O(n log n)  due to sorting within the character count object.
 * Space Complexity: O(n)
 *
 * Description:
 * This approach creates character count objects for both strings and then stringifies them.
 * If the stringified objects are equal, the strings are anagrams.
 *
 * Real-world application:
 * This approach is less efficient than the dedicated character counting methods, but it demonstrates
 * a different way to compare data structures.  It might be used in a situation where you need to quickly
 * compare the *contents* of two objects without regard to the order of properties, and you already
 * have a utility function that stringifies objects.  However, it's generally not the most performant
 * solution for the anagram problem.
 */
const isAnagramJSONStringify = (s, t) => {
    if (s.length !== t.length) {
        return false;
    }

    const getCharCounts = (str) => {
        const counts = {};
        for (const char of str) {
            counts[char] = (counts[char] || 0) + 1;
        }
        // Sort the keys to ensure consistent stringification
        const sortedCounts = {};
        Object.keys(counts).sort().forEach(key => {
            sortedCounts[key] = counts[key];
        });
        return sortedCounts;
    };

    const sCounts = getCharCounts(s);
    const tCounts = getCharCounts(t);

    return JSON.stringify(sCounts) === JSON.stringify(tCounts);
};

// Example Usage
const s1 = "anagram";
const t1 = "nagaram";

const s2 = "rat";
const t2 = "car";

console.log("Example 1:");
console.log("Sorting:", isAnagramSort(s1, t1));                           // Output: true
console.log("Character Counting (Object):", isAnagramCharacterCountObject(s1, t1));  // Output: true
console.log("Character Counting (Map):", isAnagramCharacterCountMap(s1, t1));      // Output: true
console.log("Reduce:", isAnagramReduce(s1, t1));                           // Output: true
console.log("Bitwise:", isAnagramBitwise(s1, t1));                         // Output: true
console.log("JSON.stringify:", isAnagramJSONStringify(s1, t1));           // Output: true

console.log("\nExample 2:");
console.log("Sorting:", isAnagramSort(s2, t2));                           // Output: false
console.log("Character Counting (Object):", isAnagramCharacterCountObject(s2, t2));  // Output: false
console.log("Character Counting (Map):", isAnagramCharacterCountMap(s2, t2));      // Output: false
console.log("Reduce:", isAnagramReduce(s2, t2));                           // Output: false
console.log("Bitwise:", isAnagramBitwise(s2, t2));                         // Output: false
console.log("JSON.stringify:", isAnagramJSONStringify(s2, t2));           // Output: false

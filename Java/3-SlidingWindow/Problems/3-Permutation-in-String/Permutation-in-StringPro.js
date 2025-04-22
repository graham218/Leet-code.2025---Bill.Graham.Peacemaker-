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
 * Approach 1: Brute Force (Basic Approach for Understanding)
 *
 * This approach generates all permutations of s1 and checks if any of them are a substring of s2.
 * It's highly inefficient but helps to understand the problem.  This would *never* be used in a real-world scenario due to performance.
 *
 * Time Complexity: O(N! * M), where N is the length of s1 and M is the length of s2.  N! for generating permutations.
 * Space Complexity: O(N!), to store the permutations.
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
 * Approach 2: Using Hash Maps (Frequency Counting)
 *
 * This approach uses hash maps (objects in JavaScript) to store the frequency of characters in s1 and the sliding window of s2.
 * It's more efficient than the brute force approach.  This is a very common and practical approach.
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(N), for the hash map of s1.
 */
const checkInclusionHashMap = (s1, s2) => {
    if (s1.length > s2.length) {
        return false;
    }

    const s1Freq = {};
    const s2Freq = {};

    // Build frequency map for s1
    for (const char of s1) {
        s1Freq[char] = (s1Freq[char] || 0) + 1;
    }

    // Initial frequency map for the first window in s2
    for (let i = 0; i < s1.length; i++) {
        s2Freq[s2[i]] = (s2Freq[s2[i]] || 0) + 1;
    }

    // Slide the window and compare frequency maps
    for (let i = 0; i <= s2.length - s1.length; i++) {
        if (areMapsEqual(s1Freq, s2Freq)) {
            return true;
        }
        // Slide the window: remove the leftmost char, add the rightmost
        if (i + s1.length < s2.length) { // Make sure we don't go out of bounds.
            s2Freq[s2[i]]--;
            if (s2Freq[s2[i]] === 0) {
                delete s2Freq[s2[i]];
            }
            s2Freq[s2[i + s1.length]] = (s2Freq[s2[i + s1.length]] || 0) + 1;
        }
    }

    return false;
};

// Helper function to compare two frequency maps
const areMapsEqual = (map1, map2) => {
    if (Object.keys(map1).length !== Object.keys(map2).length) {
        return false;
    }
    for (const key in map1) {
        if (map1[key] !== map2[key]) {
            return false;
        }
    }
    return true;
};

/**
 * Approach 3: Optimized Hash Map (Single Array)
 *
 * This approach optimizes the hash map approach by using a single array of size 26 (for lowercase English letters)
 * instead of two separate hash maps. This significantly improves performance and reduces memory usage.
 * This is a production-ready approach.
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(1), constant space for the array of size 26.
 */
const checkInclusionOptimized = (s1, s2) => {
    if (s1.length > s2.length) {
        return false;
    }

    const s1Freq = new Array(26).fill(0);
    const s2Freq = new Array(26).fill(0);

    // Build frequency array for s1
    for (const char of s1) {
        s1Freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    // Initial frequency array for the first window in s2
    for (let i = 0; i < s1.length; i++) {
        s2Freq[s2[i].charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    // Slide the window and compare frequency arrays
    for (let i = 0; i <= s2.length - s1.length; i++) {
        if (areArraysEqual(s1Freq, s2Freq)) {
            return true;
        }
        // Slide the window
        if (i + s1.length < s2.length) {
            s2Freq[s2[i].charCodeAt(0) - 'a'.charCodeAt(0)]--;
            s2Freq[s2[i + s1.length].charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }
    }

    return false;
};

// Helper function to compare two frequency arrays
const areArraysEqual = (arr1, arr2) => {
    for (let i = 0; i < arr1.length; i++) {
        if (arr1[i] !== arr2[i]) {
            return false;
        }
    }
    return true;
};

/**
 * Approach 4: Sliding Window with Counter
 *
 * This approach uses a sliding window and a counter to keep track of the number of matching characters.
 * It's efficient and avoids the need to compare entire frequency maps or arrays in each iteration.
 * This is a very efficient and commonly used approach in real projects.
 *
 * Time Complexity: O(N + M), where N is the length of s1 and M is the length of s2.
 * Space Complexity: O(1), constant space for the frequency array.
 */
const checkInclusionSlidingWindow = (s1, s2) => {
    if (s1.length > s2.length) {
        return false;
    }

    const s1Freq = new Array(26).fill(0);
    for (const char of s1) {
        s1Freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let left = 0;
    let right = 0;
    let matches = 0;

    while (right < s2.length) {
        // Expand the window
        const charCodeRight = s2[right].charCodeAt(0) - 'a'.charCodeAt(0);
        if (s1Freq[charCodeRight] > 0) {
            matches++;
        }
        s1Freq[charCodeRight]--;
        right++;

        // Check if window size is equal to s1 length
        if (right - left === s1.length) {
            if (matches === s1.length) {
                return true;
            }

            // Shrink the window
            const charCodeLeft = s2[left].charCodeAt(0) - 'a'.charCodeAt(0);
            s1Freq[charCodeLeft]++;
            if (s1Freq[charCodeLeft] > 0) {
                matches--;
            }
            left++;
        }
    }
    return false;
};

/**
 * Approach 5: Early Exit Optimization
 *
 * This approach builds upon the optimized hash map approach (Approach 3) but adds an early exit condition.
 * If at any point the count of a character in the sliding window exceeds its count in s1,
 * we can immediately move the window's left pointer to the next possible starting position.
 * This can provide a performance boost in some cases.
 *
 * Time Complexity: O(M) in the best case (where M is the length of s2) and O(N+M) in the worst case, where N is the length of s1.
 * Space Complexity: O(1), constant space for the frequency array.
 */
const checkInclusionEarlyExit = (s1, s2) => {
    if (s1.length > s2.length) return false;

    const s1Freq = new Array(26).fill(0);
    const s2Freq = new Array(26).fill(0);

    for (let char of s1) {
        s1Freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let left = 0;
    let right = 0;
    let required = s1.length;

    while (right < s2.length) {
        const charCode = s2[right].charCodeAt(0) - 'a'.charCodeAt(0);

        if (s1Freq[charCode] > 0) {
            required--;
        }
        s2Freq[charCode]++;
        right++;

        while (s2Freq[charCode] > s1Freq[charCode]) {
            const leftCharCode = s2[left].charCodeAt(0) - 'a'.charCodeAt(0);
            s2Freq[leftCharCode]--;
            if (s1Freq[leftCharCode] > 0) {
                required++;
            }
            left++;
        }
        if (required === 0) return true;
    }
    return false;
};



// Test cases
const s1 = "ab";
const s2 = "eidbaooo";
const s3 = "eidboaoo";

console.log("Test Case 1:");
console.log(`Input: s1 = "${s1}", s2 = "${s2}"`);
console.log("Brute Force:", checkInclusionBruteForce(s1, s2)); // Output: true
console.log("Hash Map:", checkInclusionHashMap(s1, s2));       // Output: true
console.log("Optimized Hash Map:", checkInclusionOptimized(s1, s2)); // Output: true
console.log("Sliding Window:", checkInclusionSlidingWindow(s1, s2));   // Output: true
console.log("Early Exit:", checkInclusionEarlyExit(s1, s2));       // Output: true

console.log("\nTest Case 2:");
console.log(`Input: s1 = "${s1}", s2 = "${s3}"`);
console.log("Brute Force:", checkInclusionBruteForce(s1, s3)); // Output: false
console.log("Hash Map:", checkInclusionHashMap(s1, s3));       // Output: false
console.log("Optimized Hash Map:", checkInclusionOptimized(s1, s3)); // Output: false
console.log("Sliding Window:", checkInclusionSlidingWindow(s1, s3));   // Output: false
console.log("Early Exit:", checkInclusionEarlyExit(s1, s3));       // Output: false

const s4 = "abc";
const s5 = "ccccbbaabdddaacb";
console.log("\nTest Case 3:");
console.log(`Input: s1 = "${s4}", s2 = "${s5}"`);
console.log("Brute Force:", checkInclusionBruteForce(s4, s5));
console.log("Hash Map:", checkInclusionHashMap(s4, s5));
console.log("Optimized Hash Map:", checkInclusionOptimized(s4, s5));
console.log("Sliding Window:", checkInclusionSlidingWindow(s4, s5));
console.log("Early Exit:", checkInclusionEarlyExit(s4, s5));

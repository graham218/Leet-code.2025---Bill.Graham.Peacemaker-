/*
 * Suffix Arrays & Z-Algorithm Implementation in JavaScript
 *
 * This code provides implementations of different approaches to solve problems related to suffix arrays and the Z-algorithm.  It focuses on demonstrating the core logic with clear examples and console output.
 */

/**
 * 1. Suffix Array Construction - Naive Approach (O(n^2 log n))
 *
 * Builds a suffix array for a given string.  This approach sorts all suffixes
 * directly using a string comparison, which is relatively slow for large strings.
 *
 * @param {string} str The input string.
 * @returns {number[]} The suffix array (array of starting indices of sorted suffixes).
 */
function buildSuffixArrayNaive(str) {
    const suffixes = [];
    for (let i = 0; i < str.length; i++) {
        suffixes.push({ index: i, suffix: str.substring(i) });
    }

    suffixes.sort((a, b) => a.suffix.localeCompare(b.suffix));

    const suffixArray = suffixes.map(item => item.index);
    return suffixArray;
}

/**
 * 2. Suffix Array Construction - Using Built-in sort with index tracking (O(n log n) in many JS engines)
 *
 * A slightly improved version that's often faster in practice due to optimized
 * built-in sort functions in JavaScript engines. It still relies on string comparison,
 * but the sorting is generally more efficient.
 *
 * @param {string} str The input string.
 * @returns {number[]} The suffix array.
 */
function buildSuffixArraySort(str) {
    const n = str.length;
    const suffixes = Array.from({ length: n }, (_, i) => ({ index: i, suffix: str.substring(i) }));

    suffixes.sort((a, b) => a.suffix.localeCompare(b.suffix));
    const suffixArray = suffixes.map(s => s.index);
    return suffixArray;
}


/**
 * 3. Longest Common Prefix (LCP) - Iterative Comparison (O(n^2))
 *
 * Calculates the Longest Common Prefix (LCP) array from a string and its suffix array.
 * This version calculates LCP by direct string comparison.  It's inefficient
 * for large inputs.
 *
 * @param {string} str The input string.
 * @param {number[]} suffixArray The suffix array for the string.
 * @returns {number[]} The LCP array.
 */
function calculateLCP(str, suffixArray) {
    const n = str.length;
    if (n === 0) return [];
    const lcp = Array(n).fill(0);

    for (let i = 1; i < n; i++) {
        let j = 0;
        const s1 = str.substring(suffixArray[i - 1]);
        const s2 = str.substring(suffixArray[i]);
        while (j < s1.length && j < s2.length && s1[j] === s2[j]) {
            j++;
        }
        lcp[i] = j;
    }
    return lcp;
}

/**
 * 4. Z-Algorithm (O(n))
 *
 * Computes the Z array for a given string. The Z array stores the length of the
 * longest substring starting from each position that is also a prefix of the string.
 *
 * @param {string} str The input string.
 * @returns {number[]} The Z array.
 */
function zAlgorithm(str) {
    const n = str.length;
    if (n === 0) return [];
    const z = Array(n).fill(0);
    let l = 0, r = 0;

    for (let i = 1; i < n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && str[r - l] === str[r]) {
                r++;
            }
            z[i] = r - l;
            r--;
        } else {
            let k = i - l;
            if (z[k] < r - i + 1) {
                z[i] = z[k];
            } else {
                l = i;
                while (r < n && str[r - l] === str[r]) {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
    return z;
}

/**
 * 5. Find the Longest Repeating Substring using Suffix Array and LCP (O(n^2 log n) worst case, often faster)
 *
 * Finds the longest repeating substring in a given string using the suffix array
 * and LCP array.
 *
 * @param {string} str The input string.
 * @returns {string} The longest repeating substring.
 */
function longestRepeatingSubstring(str) {
    const n = str.length;
    if (n <= 1) return "";

    const suffixArray = buildSuffixArrayNaive(str); // Can be replaced with buildSuffixArraySort for better average performance
    const lcp = calculateLCP(str, suffixArray);

    let maxLength = 0;
    let maxIndex = -1;

    for (let i = 1; i < n; i++) {
        if (lcp[i] > maxLength) {
            maxLength = lcp[i];
            maxIndex = suffixArray[i];
        }
    }

    return maxLength > 0 ? str.substring(maxIndex, maxIndex + maxLength) : "";
}



// Example Usage and Output
const text = "banana";

console.log("Input String:", text);

// 1. Naive Suffix Array
const naiveSuffixArray = buildSuffixArrayNaive(text);
console.log("\n1. Naive Suffix Array:", naiveSuffixArray);

// 2. Suffix Array using sort
const sortSuffixArray = buildSuffixArraySort(text);
console.log("\n2. Suffix Array using Sort:", sortSuffixArray);

// 3. LCP Array
const lcpArray = calculateLCP(text, naiveSuffixArray); // Use either naiveSuffixArray or sortSuffixArray
console.log("\n3. LCP Array:", lcpArray);

// 4. Z-Algorithm
const zArray = zAlgorithm(text);
console.log("\n4. Z-Array:", zArray);

// 5. Longest Repeating Substring
const longestRepeat = longestRepeatingSubstring(text);
console.log("\n5. Longest Repeating Substring:", longestRepeat);

const text2 = "aabaabaa";
console.log("\nInput String:", text2);
const zArray2 = zAlgorithm(text2);
console.log("\n4. Z-Array for 'aabaabaa':", zArray2);

const text3 = "ABABABAB";
console.log("\nInput String:", text3);
const longestRepeat3 = longestRepeatingSubstring(text3);
console.log("\n5. Longest Repeating Substring for 'ABABABAB':", longestRepeat3);

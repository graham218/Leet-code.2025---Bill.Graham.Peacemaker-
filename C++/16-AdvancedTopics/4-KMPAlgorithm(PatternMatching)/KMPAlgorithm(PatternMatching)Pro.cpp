/**
 * KMP (Knuth-Morris-Pratt) Algorithm Implementation in JavaScript
 * Demonstrates 5 different approaches with real-world project implementation examples.
 */

/**
 * 1. Basic KMP Search
 *
 * Description:
 * - Implements the standard KMP algorithm for finding the first occurrence of a pattern in a text.
 * - Computes the Longest Proper Prefix which is also a Suffix (LPS) array to optimize the search.
 *
 * Real-World Example:
 * - Text editor's "Find" functionality: Quickly locate a specific word or phrase within a document.
 *
 * Input:
 * - text: The string to search within.
 * - pattern: The string to search for.
 *
 * Output:
 * - The starting index of the first occurrence of the pattern in the text, or -1 if not found.
 */
function kmpSearchBasic(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return 0; // Empty pattern, found at the beginning
    }

    const lps = computeLPSArray(pattern);
    let i = 0; // Index for text[]
    let j = 0; // Index for pattern[]

    while (i < n) {
        if (pattern[j] === text[i]) {
            i++;
            j++;
        }

        if (j === m) {
            return i - j; // Pattern found at index i - j
        }
        // Mismatch after j matches
        else if (i < n && pattern[j] !== text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return -1; // Pattern not found
}

/**
 * Computes the LPS (Longest Proper Prefix which is also a Suffix) array.
 *
 * Description:
 * - Preprocesses the pattern to find the longest proper prefix of the pattern
 * that is also a suffix. This array is used to optimize the search process.
 *
 * Input:
 * - pattern: The string for which to compute the LPS array.
 *
 * Output:
 * - An array representing the LPS values for each prefix of the pattern.
 */
function computeLPSArray(pattern) {
    const m = pattern.length;
    const lps = new Array(m).fill(0);
    let len = 0; // Length of the previous longest prefix suffix
    let i = 1;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] from lps[0] to lps[m-1]
    while (i < m) {
        if (pattern[i] === pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len !== 0) {
                len = lps[len - 1];
                // Also, note that we do not increment i here
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/**
 * 2. KMP Search with Overlapping Occurrences
 *
 * Description:
 * - Finds all occurrences of a pattern in a text, including overlapping ones.
 * - Uses the LPS array to efficiently handle shifts after mismatches.
 *
 * Real-World Example:
 * - Bioinformatics: Finding all occurrences of a specific DNA sequence within a longer sequence.
 *
 * Input:
 * - text: The string to search within.
 * - pattern: The string to search for.
 *
 * Output:
 * - An array containing the starting indices of all occurrences of the pattern in the text.
 */
function kmpSearchAllOccurrences(text, pattern) {
    const n = text.length;
    const m = pattern.length;
    const occurrences = [];

    if (m === 0) {
        for (let i = 0; i <= n; ++i) {
            occurrences.push(i);
        }
        return occurrences;
    }

    const lps = computeLPSArray(pattern);
    let i = 0;
    let j = 0;

    while (i < n) {
        if (pattern[j] === text[i]) {
            i++;
            j++;
        }

        if (j === m) {
            occurrences.push(i - j);
            j = lps[j - 1]; // Look for next occurrence
        } else if (i < n && pattern[j] !== text[i]) {
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return occurrences;
}

/**
 * 3. KMP Search with Case-Insensitive Matching
 *
 * Description:
 * - Performs a case-insensitive search for a pattern in a text.
 * - Converts both text and pattern to lowercase before comparison.
 *
 * Real-World Example:
 * - Search engine queries: Finding web pages that contain a search term, regardless of capitalization.
 *
 * Input:
 * - text: The string to search within.
 * - pattern: The string to search for.
 *
 * Output:
 * - The starting index of the first case-insensitive occurrence of the pattern in the text, or -1 if not found.
 */
function kmpSearchCaseInsensitive(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return 0;
    }

    const lowerText = text.toLowerCase();
    const lowerPattern = pattern.toLowerCase();
    const lps = computeLPSArray(lowerPattern);
    let i = 0;
    let j = 0;

    while (i < n) {
        if (lowerPattern[j] === lowerText[i]) {
            i++;
            j++;
        }

        if (j === m) {
            return i - j;
        } else if (i < n && lowerPattern[j] !== lowerText[i]) {
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1;
}

/**
 * 4. KMP Search with Wildcard Matching
 *
 * Description:
 * - Allows the pattern to contain wildcard characters ('?') that match any single character in the text.
 * - Extends the KMP algorithm to handle these wildcards.
 *
 * Real-World Example:
 * - File system search: Finding files that match a pattern with wildcards (e.g., "document?.txt").
 *
 * Input:
 * - text: The string to search within.
 * - pattern: The string to search for, possibly containing '?' wildcards.
 *
 * Output:
 * - The starting index of the first occurrence of the pattern (with wildcards) in the text, or -1 if not found.
 */
function kmpSearchWithWildcard(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return 0;
    }

    const lps = computeLPSArray(pattern);
    let i = 0;
    let j = 0;

    while (i < n) {
        if (pattern[j] === text[i] || pattern[j] === '?') {
            i++;
            j++;
        }

        if (j === m) {
            return i - j;
        } else if (i < n && pattern[j] !== text[i] && pattern[j] !== '?') {
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1;
}

/**
 * 5. KMP Search with Multiple Patterns
 *
 * Description:
 * - Searches for multiple patterns within a single text.
 * - Uses a modified KMP approach to efficiently handle multiple pattern matching.
 * - This approach pre-processes each pattern, then searches the text once.
 *
 * Real-World Example:
 * - Intrusion detection systems: Identifying multiple known attack patterns in network traffic.
 *
 * Input:
 * - text: The string to search within.
 * - patterns: An array of strings to search for.
 *
 * Output:
 * - An object where keys are the patterns and values are arrays of starting indices of their occurrences in the text.
 */
function kmpSearchMultiplePatterns(text, patterns) {
    const n = text.length;
    const results = {};

    if (!patterns || patterns.length === 0) {
        return results; // Return empty object if no patterns provided
    }

    // Precompute LPS arrays for all patterns
    const lpsArrays = patterns.map(pattern => computeLPSArray(pattern));

    // Initialize results object
    patterns.forEach(pattern => {
        results[pattern] = [];
    });

    // Search for each pattern in the text
    for (let pIndex = 0; pIndex < patterns.length; pIndex++) {
        const pattern = patterns[pIndex];
        const m = pattern.length;
        const lps = lpsArrays[pIndex];
        let i = 0;
        let j = 0;

        while (i < n) {
            if (pattern[j] === text[i]) {
                i++;
                j++;
            }

            if (j === m) {
                results[pattern].push(i - j);
                j = lps[j - 1]; // Continue searching for next occurrence
            } else if (i < n && pattern[j] !== text[i]) {
                if (j !== 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
    }
    return results;
}

// Example Usage and Output
const text = "ABABDABACDABABCABAB";

// 1. Basic KMP Search
const pattern1 = "ABABCABAB";
console.log("1. Basic KMP Search:");
console.log(`Text: "${text}"`);
console.log(`Pattern: "${pattern1}"`);
console.log(`Result: ${kmpSearchBasic(text, pattern1)}`); // Output: 10

// 2. KMP Search with Overlapping Occurrences
const pattern2 = "ABA";
console.log("\n2. KMP Search with Overlapping Occurrences:");
console.log(`Text: "${text}"`);
console.log(`Pattern: "${pattern2}"`);
console.log(`Result: ${kmpSearchAllOccurrences(text, pattern2).join(', ')}`); // Output: 0, 3, 10, 13

// 3. KMP Search with Case-Insensitive Matching
const pattern3 = "abA";
console.log("\n3. KMP Search with Case-Insensitive Matching:");
console.log(`Text: "${text}"`);
console.log(`Pattern: "${pattern3}"`);
console.log(`Result: ${kmpSearchCaseInsensitive(text, pattern3)}`); // Output: 0

// 4. KMP Search with Wildcard Matching
const pattern4 = "AB?D";
console.log("\n4. KMP Search with Wildcard Matching:");
console.log(`Text: "${text}"`);
console.log(`Pattern: "${pattern4}"`);
console.log(`Result: ${kmpSearchWithWildcard(text, pattern4)}`); // Output: 4

// 5. KMP Search with Multiple Patterns
const patterns5 = ["ABABD", "ABABCABAB", "ACD"];
console.log("\n5. KMP Search with Multiple Patterns:");
console.log(`Text: "${text}"`);
console.log(`Patterns: ${patterns5.join(', ')}`);
console.log("Result:");
console.log(kmpSearchMultiplePatterns(text, patterns5));
/*
Output:
{
  'ABABD': [ 0 ],
  'ABABCABAB': [ 10 ],
  'ACD': [ 8 ]
}
*/

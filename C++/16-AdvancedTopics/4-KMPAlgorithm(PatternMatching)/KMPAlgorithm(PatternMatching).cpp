/**
 * KMP Algorithm (Pattern Matching) - 5 Approaches in JavaScript
 *
 * The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm
 * that searches for occurrences of a "word" (pattern) within a main "text string"
 * by employing the observation that when a mismatch occurs, the word itself embodies
 * sufficient information to determine the next position where matching could begin,
 * thus bypassing re-examination of previously matched characters.
 */

// Helper function to compute the Longest Proper Prefix Suffix (LPS) array
// This is the core of the KMP algorithm.  The LPS array helps to avoid
// redundant comparisons during the search.
function computeLPSArray(pattern) {
    const m = pattern.length;
    const lps = new Array(m).fill(0); // Initialize LPS array with 0s
    let len = 0; // Length of the previous longest prefix suffix
    let i = 1; // Index for the pattern string

    lps[0] = 0; // LPS[0] is always 0

    while (i < m) {
        if (pattern[i] === pattern[len]) {
            // If characters match, increment len and assign it to LPS[i]
            len++;
            lps[i] = len;
            i++;
        } else {
            // If characters do not match
            if (len !== 0) {
                // Important: This is the key optimization.  Instead of going back to the beginning
                // of the pattern, we use the information in the LPS array to jump to the
                // correct position.
                len = lps[len - 1]; // Also can be written as len = lps[--len];
                // Note that we do not increment i here.
            } else {
                // If len is 0, there is no proper prefix which is also a suffix,
                // so set LPS[i] to 0 and increment i.
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/**
 * Approach 1: Classic KMP Algorithm
 * - Computes the LPS array.
 * - Uses the LPS array to efficiently search for the pattern in the text.
 */
function kmpSearchClassic(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return []; // Handle empty pattern case
    }

    const lps = computeLPSArray(pattern);
    let i = 0; // Index for text
    let j = 0; // Index for pattern
    const occurrences = []; // Array to store starting indices of matches

    while (i < n) {
        if (pattern[j] === text[i]) {
            // If characters match, increment both indices
            j++;
            i++;
        }

        if (j === m) {
            // If the entire pattern is matched
            occurrences.push(i - j); // Store the starting index of the match
            j = lps[j - 1]; // Prepare to check for the next occurrence
        } else if (i < n && pattern[j] !== text[i]) {
            // If characters do not match
            if (j !== 0) {
                // Use LPS array to find the next position to compare
                j = lps[j - 1];
            } else {
                // If j is 0, no prefix matches, so move to the next character in text
                i++;
            }
        }
    }
    return occurrences;
}

/**
 * Approach 2: KMP Search with Detailed Logging
 * - Same as the classic KMP, but with added console logs for illustration.
 */
function kmpSearchWithLogging(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        console.log("Pattern is empty. Returning empty array.");
        return [];
    }

    const lps = computeLPSArray(pattern);
    console.log("LPS Array:", lps);

    let i = 0;
    let j = 0;
    const occurrences = [];

    console.log("Text:", text);
    console.log("Pattern:", pattern);

    while (i < n) {
        console.log(`Comparing text[${i}] ('${text[i]}') and pattern[${j}] ('${pattern[j]}')`);
        if (pattern[j] === text[i]) {
            j++;
            i++;
            console.log("Match! j =", j, "i =", i);
        }

        if (j === m) {
            console.log("Pattern found at index:", i - j);
            occurrences.push(i - j);
            j = lps[j - 1];
            console.log("j updated to:", j, "from LPS array");
        } else if (i < n && pattern[j] !== text[i]) {
            if (j !== 0) {
                console.log("Mismatch! j =", j, "i =", i);
                j = lps[j - 1];
                console.log("j updated to:", j, "from LPS array");
            } else {
                i++;
                console.log("Mismatch and j is 0. Incrementing i. i =", i);
            }
        }
    }
    console.log("Occurrences:", occurrences);
    return occurrences;
}

/**
 * Approach 3: KMP Search with Early Exit on First Match
 * - Stops searching after finding the first occurrence of the pattern.
 */
function kmpSearchFirstOccurrence(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return -1; // Return -1 to indicate no match (consistent with not found)
    }

    const lps = computeLPSArray(pattern);
    let i = 0;
    let j = 0;

    while (i < n) {
        if (pattern[j] === text[i]) {
            j++;
            i++;
        }

        if (j === m) {
            return i - j; // Return the starting index of the first match
        } else if (i < n && pattern[j] !== text[i]) {
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1; // Return -1 if no match is found
}

/**
 * Approach 4: KMP Search using a Class
 * - Encapsulates the KMP algorithm within a class for better organization.
 */
class KMP {
    constructor(pattern) {
        this.pattern = pattern;
        this.m = pattern.length;
        this.lps = this.m > 0 ? computeLPSArray(pattern) : []; // Compute LPS only if pattern is not empty.
    }

    search(text) {
        const n = text.length;
        if (this.m === 0) return [];

        let i = 0;
        let j = 0;
        const occurrences = [];

        while (i < n) {
            if (this.pattern[j] === text[i]) {
                j++;
                i++;
            }

            if (j === this.m) {
                occurrences.push(i - j);
                j = this.lps[j - 1];
            } else if (i < n && this.pattern[j] !== text[i]) {
                if (j !== 0) {
                    j = this.lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }
}

/**
 * Approach 5: KMP Search with Overlapping Matches Count
 * - Returns the number of overlapping matches.
 */
function kmpSearchOverlappingCount(text, pattern) {
    const n = text.length;
    const m = pattern.length;

    if (m === 0) {
        return 0;
    }

    const lps = computeLPSArray(pattern);
    let i = 0;
    let j = 0;
    let count = 0;

    while (i < n) {
        if (pattern[j] === text[i]) {
            j++;
            i++;
        }

        if (j === m) {
            count++;
            j = lps[j - 1]; // Allow overlapping matches.
        } else if (i < n && pattern[j] !== text[i]) {
            if (j !== 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

// Example Usage and Output
const text = "ABABDABACDABABCABAB";
const pattern = "ABABCABAB";

console.log("Text:", text);
console.log("Pattern:", pattern);

console.log("\nApproach 1: Classic KMP Search");
console.log("Occurrences:", kmpSearchClassic(text, pattern)); // Output: [ 10 ]

console.log("\nApproach 2: KMP Search with Detailed Logging");
kmpSearchWithLogging(text, pattern); // Output: (Detailed logs showing the process)

console.log("\nApproach 3: KMP Search - First Occurrence");
console.log("First Occurrence at index:", kmpSearchFirstOccurrence(text, pattern)); // Output: 10

const kmpInstance = new KMP(pattern);
console.log("\nApproach 4: KMP Search using a Class");
console.log("Occurrences:", kmpInstance.search(text)); // Output: [ 10 ]

console.log("\nApproach 5: KMP Search - Overlapping Matches Count");
console.log("Overlapping Matches Count:", kmpSearchOverlappingCount(text, pattern)); // Output: 1

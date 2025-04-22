/*
Rabin-Karp Algorithm for String Matching in JavaScript

The Rabin-Karp algorithm is a string searching algorithm that uses hashing to find occurrences of a pattern string within a text string. It's efficient for large texts and multiple pattern searches.

Key Concepts:

-   Hashing: Convert strings to numerical values (hash codes).
-   Rolling Hash: Efficiently update the hash code as we slide the pattern across the text.
-   Spurious Hits: The hash codes match, but the strings don't.  We must verify the match in these cases.

Time Complexity:
-   Average Case: O(n + m), where n is the text length and m is the pattern length.
-   Worst Case: O(n * m) (due to spurious hits, especially with poor hash functions).

Space Complexity: O(1) -  Constant space for variables.

*/

// Helper function to calculate the hash value of a string
function calculateHash(str, base, modulus) {
    let hash = 0;
    for (let i = 0; i < str.length; i++) {
        hash = (hash * base + str.charCodeAt(i)) % modulus;
    }
    return hash;
}

// Helper function to update the hash value for the next window
function updateHash(prevHash, prevChar, nextChar, patternLength, base, modulus) {
    let newHash = prevHash - prevChar.charCodeAt(0) * Math.pow(base, patternLength - 1);
    newHash = (newHash * base + nextChar.charCodeAt(0)) % modulus;
    // Ensure the hash is non-negative
    return (newHash + modulus) % modulus;
}

/**
 * Rabin-Karp Algorithm Implementation
 *
 * @param {string} text The text string to search within.
 * @param {string} pattern The pattern string to search for.
 * @param {number} base The base for the hash function (e.g., 256 for ASCII).
 * @param {number} modulus A large prime number to keep the hash values manageable.
 * @returns {number[]} An array of starting indices where the pattern is found in the text.
 */
function rabinKarp(text, pattern, base, modulus) {
    const n = text.length;
    const m = pattern.length;
    const occurrences = [];

    if (m === 0) {
        return []; // Handle empty pattern case
    }
    if (m > n) {
        return []; // Pattern cannot be longer than text
    }

    let patternHash = calculateHash(pattern, base, modulus);
    let textHash = calculateHash(text.substring(0, m), base, modulus);

    for (let i = 0; i <= n - m; i++) {
        if (patternHash === textHash) {
            // Potential match: Verify character by character to avoid spurious hits
            let match = true;
            for (let j = 0; j < m; j++) {
                if (text[i + j] !== pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                occurrences.push(i);
            }
        }

        if (i < n - m) {
            // Update the hash for the next window of text
            textHash = updateHash(textHash, text[i], text[i + m], m, base, modulus);
        }
    }
    return occurrences;
}

// --------------------------------------------------------------------------------------------------------------------
// 1. Basic String Matching
// --------------------------------------------------------------------------------------------------------------------
function basicStringMatching() {
    const text = "ABABDABACDABABCABAB";
    const pattern = "ABABC";
    const base = 256; // Common base for ASCII
    const modulus = 101; // A prime number

    const occurrences = rabinKarp(text, pattern, base, modulus);
    console.log("1. Basic String Matching:");
    console.log(`   Text:    "${text}"`);
    console.log(`   Pattern: "${pattern}"`);
    console.log(`   Occurrences at indices: ${occurrences.join(", ")}`); // Output: 10
}

// --------------------------------------------------------------------------------------------------------------------
// 2. Case-Insensitive Matching
// --------------------------------------------------------------------------------------------------------------------
function caseInsensitiveMatching() {
    const text = "This is a Test String with tEsT in it";
    const pattern = "test";
    const base = 256;
    const modulus = 101;

    // Preprocess both text and pattern to lowercase for case-insensitive matching
    const lowerCaseText = text.toLowerCase();
    const lowerCasePattern = pattern.toLowerCase();

    const occurrences = rabinKarp(lowerCaseText, lowerCasePattern, base, modulus);
    console.log("\n2. Case-Insensitive Matching:");
    console.log(`   Text:    "${text}"`);
    console.log(`   Pattern: "${pattern}"`);
    console.log(`   Occurrences at indices: ${occurrences.join(", ")}`); // Output: 10, 27
}

// --------------------------------------------------------------------------------------------------------------------
// 3. Matching with Overlapping Patterns
// --------------------------------------------------------------------------------------------------------------------
function overlappingPatternMatching() {
    const text = "abababa";
    const pattern = "aba";
    const base = 256;
    const modulus = 101;

    const occurrences = rabinKarp(text, pattern, base, modulus);
    console.log("\n3. Matching with Overlapping Patterns:");
    console.log(`   Text:    "${text}"`);
    console.log(`   Pattern: "${pattern}"`);
    console.log(`   Occurrences at indices: ${occurrences.join(", ")}`); // Output: 0, 2, 4
}

// --------------------------------------------------------------------------------------------------------------------
// 4. DNA Sequence Matching
// --------------------------------------------------------------------------------------------------------------------
function dnaSequenceMatching() {
    const dnaText = "ACGTACGTACGTACGT";
    const dnaPattern = "CGTA";
    const base = 4; // DNA has 4 bases: A, C, G, T
    const modulus = 101;  // A prime number

    const occurrences = rabinKarp(dnaText, dnaPattern, base, modulus);
    console.log("\n4. DNA Sequence Matching:");
    console.log(`   DNA Text:    "${dnaText}"`);
    console.log(`   DNA Pattern: "${dnaPattern}"`);
    console.log(`   Occurrences at indices: ${occurrences.join(", ")}`); // Output: 2, 6, 10
}

// --------------------------------------------------------------------------------------------------------------------
// 5. Large Text File Search (Simulated)
// --------------------------------------------------------------------------------------------------------------------
function largeTextFileSearch() {
    // Simulate reading a large text file in chunks (for demonstration)
    const largeText = "This is a very large text string.  It contains multiple occurrences of the target pattern, including this one: target.  The target pattern may also appear at the end: target";
    const pattern = "target";
    const base = 256;
    const modulus = 101;

    // In a real application, you would read the file in chunks.  Here, we just split the string.
    const chunkSize = 50;
    let totalOccurrences = [];
    for (let i = 0; i < largeText.length; i += chunkSize) {
        const chunk = largeText.substring(i, i + chunkSize);
        const occurrencesInChunk = rabinKarp(chunk, pattern, base, modulus);
        // Adjust the indices to be relative to the whole text, not the chunk
        const adjustedOccurrences = occurrencesInChunk.map(index => index + i);
        totalOccurrences = totalOccurrences.concat(adjustedOccurrences);
    }

    console.log("\n5. Large Text File Search (Simulated):");
    console.log(`   Simulated Text (first 80 chars): "${largeText.substring(0, 80)}..."`);
    console.log(`   Pattern: "${pattern}"`);
    console.log(`   Occurrences at indices: ${totalOccurrences.join(", ")}`); // Output: 67, 127
}

// Run the examples
basicStringMatching();
caseInsensitiveMatching();
overlappingPatternMatching();
dnaSequenceMatching();
largeTextFileSearch();

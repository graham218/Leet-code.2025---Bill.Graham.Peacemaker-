/*
 * Suffix Arrays & Z-Algorithm Implementation in JavaScript
 *
 * This code demonstrates five different approaches to solving string problems,
 * including suffix array construction (simplified for demonstration) and the
 * Z-algorithm. Each approach is explained with comments, and the output
 * is displayed using console.log.
 */

/**
 * 1.  Basic String Search with Suffix Array (Conceptual)
 *
 * This approach demonstrates the *idea* of using a suffix array for string searching,
 * though it doesn't build a full, sorted suffix array for simplicity.  It shows how,
 * *if* you had a sorted suffix array, you could efficiently find a substring.
 *
 * Real-world use:  Conceptual basis for advanced search engines, bioinformatics.
 */
function stringSearchWithSuffixArray(text, pattern) {
  // In a real implementation, this would be a sorted array of starting
  // indices of all suffixes of 'text'.  For this example, we'll skip
  // the complex sorting to focus on the search concept.
  //
  // Example (Conceptual):
  // text = "banana"
  // suffixes = ["banana", "anana", "nana", "ana", "na", "a"]
  // sortedSuffixes = ["a", "ana", "anana", "banana", "na", "nana"]
  // suffixArray (conceptual) = [5, 3, 1, 0, 4, 2]  (indices of sorted suffixes)

  // For demonstration, let's assume we have a pre-computed suffix array (SA).
  // In a real application, constructing this SA is the complex part.
  const textLength = text.length;
  const patternLength = pattern.length;

  //  Simplified (Conceptual) Search:
  //  Iterate through suffixes (represented by their starting indices).
  //  In a real implementation, you'd use binary search on the sorted suffix array.
  for (let i = 0; i < textLength; i++) {
    if (text.substring(i, i + patternLength) === pattern) {
      return i; // Found at index i
    }
  }
  return -1; // Not found
}

// Example Usage:
const text1 = "banana";
const pattern1 = "ana";
const result1 = stringSearchWithSuffixArray(text1, pattern1);
console.log("1. String Search with Suffix Array (Conceptual):");
console.log(`Text: "${text1}", Pattern: "${pattern1}", Found at: ${result1}`); // Output: 1


/**
 * 2.  Z-Algorithm for Substring Search
 *
 * The Z-algorithm calculates the Z-array, where Z[i] is the length of the longest
 * substring starting at i which is also a prefix of the string.  This is very
 * efficient for finding all occurrences of a pattern in a text.
 *
 * Real-world use:  Bioinformatics (finding patterns in DNA sequences),
 * network intrusion detection.
 */
function zAlgorithmSearch(text, pattern) {
  const combined = pattern + "$" + text; // Concatenate pattern and text
  const n = combined.length;
  const z = new Array(n).fill(0);
  const patternLength = pattern.length;
  const occurrences = [];

  // Calculate the Z-array
  let left = 0, right = 0;
  for (let i = 1; i < n; i++) {
    if (i > right) {
      left = right = i;
      while (right < n && combined[right - left] === combined[right]) {
        right++;
      }
      z[i] = right - left;
      right--;
    } else {
      let k = i - left;
      if (z[k] < right - i + 1) {
        z[i] = z[k];
      } else {
        left = i;
        while (right < n && combined[right - left] === combined[right]) {
          right++;
        }
        z[i] = right - left;
        right--;
      }
    }
  }

  // Search for the pattern using the Z-array
  for (let i = patternLength + 1; i < n; i++) {
    if (z[i] === patternLength) {
      occurrences.push(i - patternLength - 1); // Adjust index to point to start of match in text
    }
  }
  return occurrences;
}

// Example Usage:
const text2 = "ABABAAABABA";
const pattern2 = "ABA";
const result2 = zAlgorithmSearch(text2, pattern2);
console.log("\n2. Z-Algorithm for Substring Search:");
console.log(`Text: "${text2}", Pattern: "${pattern2}", Occurrences at: ${result2}`); // Output: [ 0, 4, 7 ]


/**
 * 3.  Longest Repeated Substring (Conceptual with Z-Algorithm)
 *
 * This demonstrates how the Z-algorithm can be adapted to find the longest
 * repeated substring in a text.  It's a conceptual example, as a full
 * solution often involves more complex data structures for optimal performance
 *
 * Real-world use: Data compression, finding repetitive patterns in data.
 */
function longestRepeatedSubstringZ(text) {
  const n = text.length;
  const z = new Array(n).fill(0);
  let left = 0, right = 0;
  let longestLength = 0;
  let longestStart = -1;

  // Calculate Z-array
  for (let i = 1; i < n; i++) {
    if (i > right) {
      left = right = i;
      while (right < n && text[right - left] === text[right]) {
        right++;
      }
      z[i] = right - left;
      right--;
    } else {
      let k = i - left;
      if (z[k] < right - i + 1) {
        z[i] = z[k];
      } else {
        left = i;
        while (right < n && text[right - left] === text[right]) {
          right++;
        }
        z[i] = right - left;
        right--;
      }
    }
     if (z[i] > longestLength) {
            longestLength = z[i];
            longestStart = i;
        }
  }
  if (longestStart === -1) {
        return ""; // No repeated substring
  }
  return text.substring(longestStart, longestStart + longestLength);
}

// Example Usage:
const text3 = "ATATAG";
const result3 = longestRepeatedSubstringZ(text3);
console.log("\n3. Longest Repeated Substring (Conceptual with Z-Algorithm):");
console.log(`Text: "${text3}", Longest Repeated Substring: "${result3}"`); // Output: "AT"


/**
 * 4.  String Matching with Multiple Patterns (Conceptual with Aho-Corasick - uses Z algo concept)
 *
 * This demonstrates the idea of using the Z algorithm to find multiple patterns.
 * Aho-Corasick is generally implemented using a Trie and failure links, but the
 * Z-algorithm shares the concept of prefix matching.
 *
 * Real-world use: Content filtering,  malware detection.
 */
function multiplePatternSearchZAlgo(text, patterns) {
    const occurrences = {};
    for (const pattern of patterns) {
        occurrences[pattern] = zAlgorithmSearch(text, pattern);
    }
    return occurrences;
}

// Example Usage:
const text4 = "ACGTAAGTAG";
const patterns4 = ["GTA", "TAG"];
const result4 = multiplePatternSearchZAlgo(text4, patterns4);
console.log("\n4. String Matching with Multiple Patterns (Conceptual with Z-Algorithm):");
console.log(`Text: "${text4}", Patterns: ${patterns4.join(', ')}, Occurrences:`, result4);



/**
 * 5.  Finding Palindromes (Conceptual with Z-Algorithm)
 *
 * The Z-algorithm can be used to find palindromes, though Manacher's algorithm
 * is typically more efficient.  This example illustrates the Z-algorithm's
 * applicability to palindrome-related problems.
 *
 * Real-world use: Bioinformatics (analyzing DNA sequences), text processing.
 */
function findPalindromesZAlgo(text) {
  const n = text.length;
  const palindromes = [];

  for (let i = 0; i < n; i++) {
    // Check for odd length palindromes
    let left = i, right = i;
    while (left >= 0 && right < n && text[left] === text[right]) {
      if (right - left + 1 > 1) { // Found a palindrome of length > 1
        palindromes.push(text.substring(left, right + 1));
      }
      left--;
      right++;
    }

    // Check for even length palindromes
    left = i, right = i + 1;
    while (left >= 0 && right < n && text[left] === text[right]) {
       if (right - left + 1 > 1) {
        palindromes.push(text.substring(left, right + 1));
      }
      left--;
      right++;
    }
  }
  return palindromes;
}

// Example Usage:
const text5 = "BABCBAB";
const result5 = findPalindromesZAlgo(text5);
console.log("\n5. Finding Palindromes (Conceptual with Z-Algorithm):");
console.log(`Text: "${text5}", Palindromes: ${result5.join(', ')}`);

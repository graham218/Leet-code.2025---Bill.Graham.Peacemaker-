#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstring> // For std::memset

// Function to print a vector
template <typename T>
void printVector(const std::vector<T>& vec, const std::string& prefix = "") {
    std::cout << prefix;
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// 1. Suffix Array Construction - Naive Approach
//   - Time Complexity: O(n^2 log n)
//   - Description: Generates all suffixes, sorts them lexicographically.
std::vector<int> constructSuffixArrayNaive(const std::string& text) {
    int n = text.size();
    std::vector<std::string> suffixes(n);
    std::vector<int> suffixArray(n);

    // Generate all suffixes
    for (int i = 0; i < n; ++i) {
        suffixes[i] = text.substr(i);
    }

    // Create an array of indices [0, 1, 2, ..., n-1]
    std::iota(suffixArray.begin(), suffixArray.end(), 0);

    // Sort the indices based on the lexicographical order of the corresponding suffixes
    std::sort(suffixArray.begin(), suffixArray.end(),
              [&](int i, int j) { return suffixes[i] < suffixes[j]; });

    return suffixArray;
}

// 2. Suffix Array Construction - Using Sorting (Optimized)
//   - Time Complexity: O(n log^2 n)  (Can be further optimized to O(n log n) using more complex algorithms)
//   - Description:  A slightly optimized version where we avoid creating explicit suffix strings.  We sort the indices directly using a custom comparator.
std::vector<int> constructSuffixArraySort(const std::string& text) {
    int n = text.size();
    std::vector<int> suffixArray(n);

    // Initialize suffix array with indices
    std::iota(suffixArray.begin(), suffixArray.end(), 0);

    // Sort the indices based on the suffixes they represent
    std::sort(suffixArray.begin(), suffixArray.end(), [&](int i, int j) {
        return text.substr(i) < text.substr(j); // Compare substrings directly
    });

    return suffixArray;
}

// 3. Suffix Array Construction -  Using Radix Sort (Sketch - Simplified for Explanation)
//   - Time Complexity: O(n log n)  (This is a simplified sketch; a full radix sort implementation for suffix arrays is more involved)
//   - Description:  This is a conceptual sketch.  Efficient suffix array construction often involves radix sort, but the implementation is complex.  This shows the basic idea of sorting based on characters.  A true radix sort implementation for suffix arrays involves multiple passes and careful handling of varying suffix lengths.
std::vector<int> constructSuffixArrayRadixSort(const std::string& text) {
    int n = text.size();
    std::vector<int> suffixArray(n);
    std::iota(suffixArray.begin(), suffixArray.end(), 0);

    // This is a simplified version.  Real radix sort for suffix arrays is more complex.
    // 1.  Sort based on the first character.
     std::sort(suffixArray.begin(), suffixArray.end(), [&](int i, int j) {
        return text[i] < text[j];
    });

    // 2.  In a real radix sort, you'd repeat this process for increasing lengths
    //     (doubling the length considered in each pass) and use counting sort
    //     for each character position.  This would handle the fact that suffixes
    //     have different lengths.

    //  A full implementation requires handling groups of suffixes that have the same
    //  initial characters and then refining the sorting based on longer and longer contexts.

    return suffixArray; //  This is a simplified result.
}



// 4. Z-Algorithm - Efficient Pattern Matching
//   - Time Complexity: O(n + m), where n is the length of the text and m is the length of the pattern.
//   - Description: Computes the Z-array, where Z[i] is the length of the longest substring starting at i
//                which is also a prefix of the string.  Used for efficient pattern matching.
std::vector<int> zAlgorithm(const std::string& text) {
    int n = text.size();
    std::vector<int> z(n, 0);
    int left = 0, right = 0;

    for (int i = 1; i < n; ++i) {
        if (i > right) {
            // Case 1: i is outside the current Z-box
            left = right = i;
            while (right < n && text[right - left] == text[right]) {
                right++;
            }
            z[i] = right - left;
            right--;
        } else {
            // Case 2: i is inside the current Z-box
            int k = i - left;
            if (z[k] < right - i + 1) {
                // Case 2a: Z[i] is within the Z-box
                z[i] = z[k];
            } else {
                // Case 2b: Z[i] extends beyond the Z-box
                left = i;
                while (right < n && text[right - left] == text[right]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            }
        }
    }
    return z;
}

// Function to find occurrences of a pattern in a text using the Z-algorithm
std::vector<int> findPatternZAlgorithm(const std::string& text, const std::string& pattern) {
    std::string combinedString = pattern + "$" + text; // Concatenate pattern and text with a separator
    std::vector<int> z = zAlgorithm(combinedString);
    std::vector<int> occurrences;
    int patternLength = pattern.size();

    for (int i = patternLength + 1; i < combinedString.size(); ++i) {
        if (z[i] == patternLength) {
            occurrences.push_back(i - patternLength - 1); // Calculate the starting index in the text
        }
    }
    return occurrences;
}

// 5. Longest Common Prefix (LCP) Array Calculation using Suffix Array and Kasai's Algorithm
//   - Time Complexity: O(n)
//   - Description:  Computes the Longest Common Prefix (LCP) array from a suffix array.
//      LCP[i] is the length of the longest common prefix between the suffixes pointed to by suffixArray[i] and suffixArray[i-1].
std::vector<int> calculateLCP(const std::string& text, const std::vector<int>& suffixArray) {
    int n = text.size();
    std::vector<int> lcp(n, 0);
    std::vector<int> rank(n, 0);

    // Compute the inverse suffix array (rank array)
    for (int i = 0; i < n; ++i) {
        rank[suffixArray[i]] = i;
    }

    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suffixArray[rank[i] + 1]; // Get the next suffix in the suffix array
        while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
        if (k > 0) {
            k--; // Important optimization
        }
    }
    return lcp;
}

int main() {
    std::string text = "banana";
    std::string pattern = "ana";

    // 1. Suffix Array - Naive Approach
    std::cout << "\n1. Suffix Array (Naive):" << std::endl;
    std::vector<int> suffixArrayNaive = constructSuffixArrayNaive(text);
    printVector(suffixArrayNaive, "Suffix Array: "); // Output: 5 3 1 0 4 2

    // 2. Suffix Array - Using Sorting
    std::cout << "\n2. Suffix Array (Sort):" << std::endl;
    std::vector<int> suffixArraySort = constructSuffixArraySort(text);
    printVector(suffixArraySort, "Suffix Array: "); // Output: 5 3 1 0 4 2

    // 3. Suffix Array - Using Radix Sort (Sketch)
    std::cout << "\n3. Suffix Array (Radix Sort - Sketch):" << std::endl;
    std::vector<int> suffixArrayRadix = constructSuffixArrayRadixSort(text);
    printVector(suffixArrayRadix, "Suffix Array: "); // Output:  (Output will be partially sorted)

    // 4. Z-Algorithm
    std::cout << "\n4. Z-Algorithm:" << std::endl;
    std::vector<int> zArray = zAlgorithm(text);
    printVector(zArray, "Z-Array: "); // Output: 0 0 0 3 0 1

    // Pattern Matching using Z-Algorithm
    std::cout << "\n   Pattern Matching using Z-Algorithm:" << std::endl;
    std::vector<int> occurrences = findPatternZAlgorithm(text, pattern);
    if (occurrences.empty()) {
        std::cout << "   Pattern not found" << std::endl;
    } else {
        printVector(occurrences, "   Pattern occurrences at indices: "); // Output: 1 3
    }
    // 5. LCP Array
    std::cout << "\n5. LCP Array:" << std::endl;
    std::vector<int> lcpArray = calculateLCP(text, suffixArraySort);
    printVector(lcpArray, "LCP Array: "); // Output: 0 1 3 0 0 2

    return 0;
}

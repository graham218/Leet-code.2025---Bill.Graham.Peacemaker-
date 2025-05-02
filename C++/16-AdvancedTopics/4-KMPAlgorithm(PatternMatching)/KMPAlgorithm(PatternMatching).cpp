#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::search

// Approach 1: Basic KMP with Standard Library Output
// This version calculates the longest proper prefix suffix (LPS) array and then
// uses it to find the first occurrence of the pattern in the text.
void kmpSearch1(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) {
        std::cout << "Pattern is empty.  Found at index: 0" << std::endl;
        return;
    }
    if (n == 0) {
        std::cout << "Text is empty. Pattern not found." << std::endl;
        return;
    }

    std::vector<int> lps(m); // LPS array to store longest proper prefix suffix values

    // Preprocess the pattern (calculate LPS array)
    lps[0] = 0; // Base case: LPS for the first character is always 0
    int len = 0; // Length of the previous longest prefix suffix
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else { // (pattern[i] != pattern[len])
            if (len != 0) {
                len = lps[len - 1]; // Also, note that we do not increment i here
            } else { // if (len == 0)
                lps[i] = 0;
                i++;
            }
        }
    }

    // Search for the pattern in the text
    i = 0; // Index for text[]
    int j = 0; // Index for pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = lps[j - 1]; // j is updated using lps
        }
        // mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // we will match lps[j-1] characters.  Consider the example
            // “ABABDABACDABABCABAB” and pattern “ABABCABAB”.
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    //If the pattern is not found.
    if (j != m)
        std::cout << "Pattern not found" << std::endl;
}

// Approach 2: KMP returning the index of the first match, or -1 if not found.
// This version returns the starting index of the first match,
// or -1 if the pattern is not found in the text.
int kmpSearch2(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return 0; // Empty pattern found at index 0
    if (n == 0) return -1; // Empty text, no match

    std::vector<int> lps(m);
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            return i - j; // Return the starting index of the match
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1; // Pattern not found
}

// Approach 3: KMP to find all occurrences of the pattern.
// This version finds all occurrences of the pattern in the text and
// returns a vector of the starting indices of each match.
std::vector<int> kmpSearch3(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> occurrences;

    if (m == 0) {
        occurrences.push_back(0); // Empty pattern matches at index 0
        return occurrences;
    }
    if (n == 0) return occurrences; // Empty text, no matches

    std::vector<int> lps(m);
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - j); // Store the starting index
            j = lps[j - 1]; // Look for the next occurrence
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return occurrences;
}

// Approach 4: KMP using std::search (for comparison)
// This version uses the std::search algorithm from the C++ standard library
// to find the first occurrence of the pattern.  This is NOT the KMP algorithm itself,
// but provides a way to compare the results.
void kmpSearch4(const std::string& text, const std::string& pattern) {
    size_t pos = text.find(pattern); // simplest possible implementation
    if (pos != std::string::npos) {
        std::cout << "Pattern found at index: " << pos << std::endl;
    }
    else
        std::cout << "Pattern not found" << std::endl;
}

// Approach 5: KMP with detailed output.
// This version prints detailed information about the KMP search process,
// including the LPS array and the matching process.
void kmpSearch5(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) {
        std::cout << "Pattern is empty. Found at index: 0" << std::endl;
        return;
    }
    if (n == 0) {
        std::cout << "Text is empty. Pattern not found." << std::endl;
        return;
    }

    std::vector<int> lps(m);
    lps[0] = 0;
    int len = 0;
    int i = 1;
    std::cout << "Calculating LPS Array:\n";
    while (i < m) {
        std::cout << "  Comparing pattern[" << i << "] (" << pattern[i] << ") and pattern[" << len << "] (" << pattern[len] << ")\n";
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            std::cout << "  Match found. lps[" << i << "] = " << len << "\n";
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                std::cout << "  Mismatch.  len = lps[" << len - 1 << "] = " << len << "\n";
            } else {
                lps[i] = 0;
                std::cout << "  Mismatch. len = 0. lps[" << i << "] = 0\n";
                i++;
            }
        }
    }

    std::cout << "LPS Array: ";
    for (int val : lps) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    i = 0;
    int j = 0;
    std::cout << "Searching for pattern in text:\n";
    while (i < n) {
        std::cout << "  Comparing text[" << i << "] (" << text[i] << ") and pattern[" << j << "] (" << pattern[j] << ")\n";
        if (pattern[j] == text[i]) {
            i++;
            j++;
            std::cout << "  Match found. i = " << i << ", j = " << j << "\n";
        }
        if (j == m) {
            std::cout << "  Pattern found at index " << i - j << std::endl;
            j = lps[j - 1];
            std::cout << "  j = lps[" << j - 1 << "] = " << j << " (Continuing search)\n";
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
                std::cout << "  Mismatch. j = lps[" << j - 1 << "] = " << j << "\n";
            } else {
                i = i + 1;
                std::cout << "  Mismatch. j = 0. i = " << i << "\n";
            }
        }
    }
    if (j != m)
        std::cout << "  Pattern not found" << std::endl;
}

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl << std::endl;

    std::cout << "Approach 1: Basic KMP with Standard Library Output\n";
    kmpSearch1(text, pattern);
    std::cout << std::endl;

    std::cout << "Approach 2: KMP returning the index of the first match, or -1 if not found.\n";
    int index = kmpSearch2(text, pattern);
    if (index != -1) {
        std::cout << "Pattern found at index: " << index << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Approach 3: KMP to find all occurrences of the pattern.\n";
    std::vector<int> occurrences = kmpSearch3(text, pattern);
    if (occurrences.empty()) {
        std::cout << "Pattern not found" << std::endl;
    } else {
        std::cout << "Pattern found at indices: ";
        for (int pos : occurrences) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Approach 4: KMP using std::search (for comparison)\n";
    kmpSearch4(text, pattern);
    std::cout << std::endl;

    std::cout << "Approach 5: KMP with detailed output\n";
    kmpSearch5(text, pattern);
    std::cout << std::endl;

    // Example with empty pattern
    std::cout << "Example with empty pattern:\n";
    std::string emptyPattern = "";
    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << emptyPattern << std::endl;
    kmpSearch1(text, emptyPattern);

    return 0;
}

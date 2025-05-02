#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

// Approach 1: Basic Manacher's Algorithm (Explicit Expansion)
// This is the most straightforward implementation of Manacher's algorithm.
// It explicitly expands around each center to find the palindrome length.
std::string longestPalindromeManacher1(const std::string& s) {
    if (s.empty()) return "";

    // Preprocess the string to handle even length palindromes.
    // Insert '#' between characters and at the beginning and end.
    std::string processed_s = "^"; // Start with a dummy character to avoid edge cases
    for (char c : s) {
        processed_s += '#';
        processed_s += c;
    }
    processed_s += "#$"; // End with '#' and another dummy character
    // Example: "aba" becomes "^#a#b#a#$"

    int n = processed_s.length();
    std::vector<int> p(n, 0); // Array to store palindrome lengths centered at each position
    int center = 0, right = 0;  // center: Center of the rightmost palindrome, right: Right boundary of that palindrome

    for (int i = 1; i < n - 1; ++i) { // Iterate through the processed string (excluding the dummy start and end)
        // Use symmetry to initialize p[i] if i is within the right boundary
        int mirror = 2 * center - i; // Mirror position of i with respect to center
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]); // Take the minimum of the distance to the right boundary and the palindrome length at the mirror position.
        }

        // Attempt to expand palindrome centered at i
        while (processed_s[i + (1 + p[i])] == processed_s[i - (1 + p[i])]) { // Expand as long as characters on both sides are equal
            p[i]++;
        }

        // If the expansion goes beyond the right boundary, update center and right
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    // Find the maximum palindrome length and its center
    int max_length = 0;
    int center_index = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (p[i] > max_length) {
            max_length = p[i];
            center_index = i;
        }
    }

    // Extract the original palindrome string from the processed string
    int start = (center_index - max_length) / 2; // Calculate the start index in the original string.
    return s.substr(start, max_length);
}

// Approach 2: Manacher's Algorithm with Early Exit
//  This version adds a condition to exit early if the maximum possible palindrome
//  centered at the current position cannot exceed the current longest palindrome.
std::string longestPalindromeManacher2(const std::string& s) {
    if (s.empty()) return "";

    std::string processed_s = "^";
    for (char c : s) {
        processed_s += '#';
        processed_s += c;
    }
    processed_s += "#$";

    int n = processed_s.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int max_length = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }

        // Early exit condition:
        // If the maximum possible palindrome centered at i cannot exceed the current max_length, skip expansion.
        if (p[i] <= max_length / 2) { // Optimization: check against half of max_length
            while (processed_s[i + (1 + p[i])] == processed_s[i - (1 + p[i])]) {
                p[i]++;
            }

            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }

            if (p[i] > max_length) {
                max_length = p[i];
                center_index = i;
            }
        }
    }
    int start = (center_index - max_length) / 2;
    return s.substr(start, max_length);
}


// Approach 3: Manacher's Algorithm with Optimized Expansion
// This version optimizes the expansion step by using a tighter loop condition.
std::string longestPalindromeManacher3(const std::string& s) {
    if (s.empty()) return "";

    std::string processed_s = "^";
    for (char c : s) {
        processed_s += '#';
        processed_s += c;
    }
    processed_s += "#$";

    int n = processed_s.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int max_length = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }

        // Optimized expansion condition.  It combines the check and increment.
        while (i + (1 + p[i]) < n && i - (1 + p[i]) >= 0 && processed_s[i + (1 + p[i])] == processed_s[i - (1 + p[i])]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > max_length) {
            max_length = p[i];
            center_index = i;
        }
    }

    int start = (center_index - max_length) / 2;
    return s.substr(start, max_length);
}

// Approach 4: Manacher's Algorithm with Precomputed Max Length
// This approach precomputes and stores the maximum palindrome length found so far,
// to avoid redundant calculations in the loop.
std::string longestPalindromeManacher4(const std::string& s) {
    if (s.empty()) return "";

    std::string processed_s = "^";
    for (char c : s) {
        processed_s += '#';
        processed_s += c;
    }
    processed_s += "#$";

    int n = processed_s.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int max_length = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }

        while (processed_s[i + (1 + p[i])] == processed_s[i - (1 + p[i])]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Update max_length and center_index only if a longer palindrome is found.
        if (p[i] > max_length) {
            max_length = p[i];
            center_index = i;
        }
    }

    int start = (center_index - max_length) / 2;
    return s.substr(start, max_length);
}

// Approach 5: Manacher's Algorithm with Boundary Checks Inside Loop
// This version moves the boundary checks (i + p[i] < n and i - p[i] >= 0)
// directly into the while loop condition, making it more concise.
std::string longestPalindromeManacher5(const std::string& s) {
    if (s.empty()) return "";

    std::string processed_s = "^";
    for (char c : s) {
        processed_s += '#';
        processed_s += c;
    }
    processed_s += "#$";

    int n = processed_s.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int max_length = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }

        // Boundary checks are now part of the while loop condition.
        while (i + (1 + p[i]) < n && i - (1 + p[i]) >= 0 && processed_s[i + (1 + p[i])] == processed_s[i - (1 + p[i])]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > max_length) {
            max_length = p[i];
            center_index = i;
        }
    }

    int start = (center_index - max_length) / 2;
    return s.substr(start, max_length);
}

int main() {
    std::string test_string = "babad";
    std::cout << "Original String: " << test_string << std::endl;

    std::cout << "Longest Palindrome (Manacher 1): " << longestPalindromeManacher1(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 2): " << longestPalindromeManacher2(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 3): " << longestPalindromeManacher3(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 4): " << longestPalindromeManacher4(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 5): " << longestPalindromeManacher5(test_string) << std::endl;

    test_string = "cbbd";
    std::cout << "\nOriginal String: " << test_string << std::endl;
    std::cout << "Longest Palindrome (Manacher 1): " << longestPalindromeManacher1(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 2): " << longestPalindromeManacher2(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 3): " << longestPalindromeManacher3(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 4): " << longestPalindromeManacher4(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 5): " << longestPalindromeManacher5(test_string) << std::endl;

    test_string = "a";
    std::cout << "\nOriginal String: " << test_string << std::endl;
    std::cout << "Longest Palindrome (Manacher 1): " << longestPalindromeManacher1(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 2): " << longestPalindromeManacher2(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 3): " << longestPalindromeManacher3(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 4): " << longestPalindromeManacher4(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 5): " << longestPalindromeManacher5(test_string) << std::endl;

    test_string = "acbbca";
    std::cout << "\nOriginal String: " << test_string << std::endl;
    std::cout << "Longest Palindrome (Manacher 1): " << longestPalindromeManacher1(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 2): " << longestPalindromeManacher2(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 3): " << longestPalindromeManacher3(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 4): " << longestPalindromeManacher4(test_string) << std::endl;
    std::cout << "Longest Palindrome (Manacher 5): " << longestPalindromeManacher5(test_string) << std::endl;

    return 0;
}

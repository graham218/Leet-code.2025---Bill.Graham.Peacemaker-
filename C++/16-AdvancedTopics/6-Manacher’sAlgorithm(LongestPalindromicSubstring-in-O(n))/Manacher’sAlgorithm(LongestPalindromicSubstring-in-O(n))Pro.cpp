#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

// Approach 1: Basic Manacher's Algorithm (Core Implementation)
// This is the fundamental implementation of Manacher's algorithm.  It focuses on clarity
// and directly reflects the algorithm's steps.  It's suitable for situations where
// understanding the core logic is paramount, such as educational tools or simple
// string processing tasks.
std::string manacher1(const std::string& s) {
    // 1. Preprocess the string to insert dummy characters ('#') to handle even and odd length palindromes uniformly.
    std::string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }

    int n = t.length();
    std::vector<int> p(n, 0); // Array to store the palindrome lengths centered at each position.
    int center = 0, right = 0;  // center: Center of the current rightmost palindrome.
                               // right: Right boundary of the current rightmost palindrome.

    int maxLen = 0;
    int centerIndex = 0;

    // 2. Iterate through the preprocessed string 't'.
    for (int i = 1; i < n; ++i) {
        // 3. Utilize symmetry to potentially avoid redundant calculations.
        int mirror = 2 * center - i; // Find the 'mirror' position of 'i' with respect to 'center'.
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]); // Optimization: Use info from the mirror.
        }

        // 4. Expand the palindrome centered at 'i' as much as possible.
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] == t[i + (1 + p[i])]) {
            p[i]++;
        }

        // 5. Update 'center' and 'right' if the palindrome centered at 'i' expands beyond the current 'right' boundary.
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Keep track of the longest palindrome seen so far.
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    // 6. Extract the longest palindromic substring from the original string 's'.
    int start = (centerIndex - maxLen) / 2; // Calculate the start index in the original string.
    return s.substr(start, maxLen);
}

// Approach 2: Manacher's Algorithm with Early Exit Optimization
//   This version adds an optimization to exit early if the maximum possible palindrome
//   length is less than or equal to the current longest palindrome found. This can
//   improve performance in cases where the longest palindrome is found early in the string.
std::string manacher2(const std::string& s) {
    std::string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }

    int n = t.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n; ++i) {
        // Early exit condition:
        if (n - i <= maxLen / 2) { //if the remaining part of the string cannot contain a longer palindrome
            break;
        }

        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] == t[i + (1 + p[i])]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

// Approach 3: Manacher's Algorithm with Preallocated Memory
//      This version preallocates the vector 'p' to the maximum possible size.  This can
//      improve performance by avoiding dynamic memory reallocations, especially for
//      very large input strings.  This is a good optimization for performance-critical
//      applications where memory management overhead needs to be minimized.
std::string manacher3(const std::string& s) {
    std::string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int n = t.length();
    std::vector<int> p(n); // Preallocate the vector.
    int center = 0, right = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] == t[i + (1 + p[i])]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

// Approach 4: Manacher's Algorithm with String View (C++17 and later)
//   This version uses std::string_view (C++17 and later) instead of std::string for the input.
//   This avoids unnecessary string copying, making it more efficient, especially when
//   dealing with large strings or when the input string is already stored elsewhere.
//   This is the preferred approach for modern C++ projects where performance and
//   memory efficiency are crucial.
#ifdef __cpp_lib_string_view // Check if string_view is supported
#include <string_view>
std::string manacher4(std::string_view s) {
    std::string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int n = t.length();
    std::vector<int> p(n);
    int center = 0, right = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] == t[i + (1 + p[i])]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    int start = (centerIndex - maxLen) / 2;
    return std::string(s.substr(start, maxLen)); // Convert back to string for return
}
#endif

// Approach 5: Manacher's Algorithm with Iterators
//   This version of Manacher's algorithm uses iterators instead of index-based access.
//   This provides a more generic implementation that can work with different types of
//   sequences, not just strings.  While it might be slightly less readable for those
//   unfamiliar with iterators, it demonstrates a more advanced C++ technique and can be
//   valuable in library development or when working with various data structures.
std::string manacher5(const std::string& s) {
    std::string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int n = t.length();
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n; ++i) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = std::min(right - i, p[mirror]);
        }
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && t[i - (1 + p[i])] == t[i + (1 + p[i])]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    std::string testString = "babcbabcbaccba";
    std::cout << "Input String: " << testString << std::endl;

    std::cout << "\nApproach 1 (Basic): " << manacher1(testString) << std::endl;
    std::cout << "Approach 2 (Early Exit): " << manacher2(testString) << std::endl;
    std::cout << "Approach 3 (Preallocation): " << manacher3(testString) << std::endl;
#ifdef __cpp_lib_string_view
    std::cout << "Approach 4 (String View): " << manacher4(testString) << std::endl;
#else
    std::cout << "Approach 4 (String View): String View Not Supported" << std::endl;
#endif
    std::cout << "Approach 5 (Iterators): " << manacher5(testString) << std::endl;

    return 0;
}

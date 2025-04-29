#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to print the Longest Palindromic Substring and its length
void printResult(const string& s, int start, int end) {
    cout << "Longest Palindromic Substring: ";
    for (int i = start; i <= end; ++i) {
        cout << s[i];
    }
    cout << endl;
    cout << "Length: " << end - start + 1 << endl;
}

// 1. Brute Force Approach
//   - Iterate through all possible substrings and check if each is a palindrome.
//   - Time Complexity: O(n^3), Space Complexity: O(1)
string longestPalindromeBruteForce(const string& s) {
    int n = s.length();
    if (n == 0) return "";
    int start = 0, maxLength = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            bool isPalindrome = true;
            for (int k = 0; k < (j - i + 1) / 2; ++k) {
                if (s[i + k] != s[j - k]) {
                    isPalindrome = false;
                    break;
                }
            }
            if (isPalindrome && (j - i + 1) > maxLength) {
                start = i;
                maxLength = j - i + 1;
            }
        }
    }
    return s.substr(start, maxLength);
}

// 2. Dynamic Programming Approach
//   - Create a 2D table where dp[i][j] is true if the substring s[i...j] is a palindrome.
//   - Build the table bottom-up.
//   - Time Complexity: O(n^2), Space Complexity: O(n^2)
string longestPalindromeDP(const string& s) {
    int n = s.length();
    if (n == 0) return "";
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0, maxLength = 1;

    // Base cases: single characters are palindromes
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // Check for substrings of length 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check for substrings of length 3 or greater
    for (int k = 3; k <= n; ++k) {
        for (int i = 0; i < n - k + 1; ++i) {
            int j = i + k - 1; // Ending index of the substring
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
    return s.substr(start, maxLength);
}

// 3. Expand Around Center Approach
//   - For each character in the string, consider it as the center of a palindrome and expand in both directions.
//   - Handle both odd and even length palindromes.
//   - Time Complexity: O(n^2), Space Complexity: O(1)
string longestPalindromeExpandAroundCenter(const string& s) {
    int n = s.length();
    if (n == 0) return "";
    int start = 0, end = 0;

    for (int i = 0; i < n; ++i) {
        // For odd length palindromes
        int left = i, right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > end - start + 1) {
                start = left;
                end = right;
            }
            left--;
            right++;
        }

        // For even length palindromes
        left = i, right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > end - start + 1) {
                start = left;
                end = right;
            }
            left--;
            right++;
        }
    }
    return s.substr(start, end - start + 1);
}

// 4. Manacher's Algorithm
//   - A linear time algorithm to find the longest palindromic substring.
//   - It uses a transformed string and an array to store palindrome lengths.
//   - Time Complexity: O(n), Space Complexity: O(n)
string longestPalindromeManacher(const string& s) {
    int n = s.length();
    if (n == 0) return "";

    // Transform the string to handle even and odd length palindromes uniformly
    string t = "^"; // Start boundary
    for (int i = 0; i < n; ++i) {
        t += "#";
        t += s[i];
    }
    t += "#$"; // End boundary
    int m = t.length();

    vector<int> p(m, 0); // Array to store palindrome lengths at each center
    int center = 0, right = 0;
    int start = 0, maxLength = 0;

    for (int i = 1; i < m - 1; ++i) {
        int mirror = 2 * center - i; // Mirror position of i with respect to center

        if (i < right) {
            p[i] = min(right - i, p[mirror]); // Take minimum of mirror's value and right boundary
        }

        // Expand around center i
        while (t[i + (1 + p[i])] == t[i - (1 + p[i])]) {
            p[i]++;
        }

        // If current palindrome expands past right, adjust center and right
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Update maxLength and start index
        if (p[i] > maxLength) {
            maxLength = p[i];
            start = (i - maxLength) / 2; // Original start position
        }
    }
    return s.substr(start, maxLength);
}

// 5. Optimized Dynamic Programming Approach (Space Optimized)
//   - Similar to the DP approach, but optimizes space complexity to O(n) by using only two rows of the DP table.
//   - Time Complexity: O(n^2), Space Complexity: O(n)
string longestPalindromeOptimizedDP(const string& s) {
    int n = s.length();
    if (n == 0) return "";
    vector<bool> prevRow(n, false);
    vector<bool> currRow(n, false);
    int start = 0, maxLength = 1;

    // Base case: single characters are palindromes
    for (int i = 0; i < n; ++i) {
        prevRow[i] = true;
    }

    // Check for substrings of length 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            currRow[i] = true;
            start = i;
            maxLength = 2;
        } else {
            currRow[i] = false;
        }
    }
    prevRow = currRow; // Copy currRow to prevRow for next iteration

    // Check for substrings of length 3 or greater
    for (int k = 3; k <= n; ++k) {
        currRow.assign(n, false); // Reset currRow for each k
        for (int i = 0; i < n - k + 1; ++i) {
            int j = i + k - 1;
            if (s[i] == s[j] && prevRow[i + 1]) {
                currRow[i] = true;
                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
        prevRow = currRow; // Copy currRow to prevRow for next iteration
    }
    return s.substr(start, maxLength);
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    cout << "\n--- Brute Force Approach ---" << endl;
    string resultBruteForce = longestPalindromeBruteForce(s);
    printResult(s, s.find(resultBruteForce), s.find(resultBruteForce) + resultBruteForce.length() - 1);

    cout << "\n--- Dynamic Programming Approach ---" << endl;
    string resultDP = longestPalindromeDP(s);
    printResult(s, s.find(resultDP), s.find(resultDP) + resultDP.length() - 1);

    cout << "\n--- Expand Around Center Approach ---" << endl;
    string resultExpandAroundCenter = longestPalindromeExpandAroundCenter(s);
    printResult(s, s.find(resultExpandAroundCenter), s.find(resultExpandAroundCenter) + resultExpandAroundCenter.length() - 1);

    cout << "\n--- Manacher's Algorithm ---" << endl;
    string resultManacher = longestPalindromeManacher(s);
    printResult(s, s.find(resultManacher), s.find(resultManacher) + resultManacher.length() - 1);

    cout << "\n--- Optimized Dynamic Programming Approach ---" << endl;
    string resultOptimizedDP = longestPalindromeOptimizedDP(s);
    printResult(s, s.find(resultOptimizedDP), s.find(resultOptimizedDP) + resultOptimizedDP.length() - 1);

    return 0;
}

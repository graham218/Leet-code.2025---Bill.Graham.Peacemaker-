#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional> // Include this for std::function

using namespace std;

// Function to print the Longest Palindromic Substring and its length
void printResult(const string& s, int start, int maxLength) {
    cout << "Longest Palindromic Substring: ";
    for (int i = start; i < start + maxLength; ++i) {
        cout << s[i];
    }
    cout << endl;
    cout << "Length: " << maxLength << endl;
}

// 1. Dynamic Programming - Tabulation (Bottom-Up)
// Time Complexity: O(n^2), Space Complexity: O(n^2)
string longestPalindromeDP(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    // Create a table to store whether a substring s[i...j] is a palindrome
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // All single characters are palindromes
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // Check for palindromes of length 2
    int maxLength = 1;
    int start = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check for palindromes of length greater than 2
    for (int k = 3; k <= n; ++k) {
        for (int i = 0; i <= n - k; ++i) {
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

// 2. Optimized Dynamic Programming - Tabulation (Bottom-Up)
// Time Complexity: O(n^2), Space Complexity: O(n^2) - but often faster in practice due to simpler logic
string longestPalindromeDPOptimized(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLength = 1;
    int start = 0;

    for (int i = n - 1; i >= 0; --i) { // Iterate from the end
        for (int j = i; j < n; ++j) {
            if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
                if (j - i + 1 > maxLength) {
                    maxLength = j - i + 1;
                    start = i;
                }
            }
        }
    }
    return s.substr(start, maxLength);
}

// 3. Expand Around Center Approach
// Time Complexity: O(n^2), Space Complexity: O(1)
string longestPalindromeExpand(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    int start = 0;
    int maxLength = 1;

    for (int i = 0; i < n; ++i) {
        // For odd length palindromes
        int left = i, right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLength) {
                start = left;
                maxLength = right - left + 1;
            }
            --left;
            ++right;
        }

        // For even length palindromes
        left = i, right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLength) {
                start = left;
                maxLength = right - left + 1;
            }
            --left;
            ++right;
        }
    }
    return s.substr(start, maxLength);
}

// 4. Manacher's Algorithm
// Time Complexity: O(n), Space Complexity: O(n)
// This is the most efficient algorithm, linear time complexity
string longestPalindromeManacher(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    // Preprocess the string to handle even length palindromes
    string processedString = "^";  // Start and end markers to avoid boundary checks
    for (char c : s) {
        processedString += c;
        processedString += "#";
    }
    processedString += "$";

    int processedLength = processedString.size();
    vector<int> p(processedLength, 0); // Array to store palindrome lengths at each center
    int center = 0, right = 0;
    int maxLen = 0, start = 0;

    for (int i = 1; i < processedLength - 1; ++i) {
        int mirror = 2 * center - i; // Mirror position of i with respect to center

        if (i < right) {
            p[i] = min(right - i, p[mirror]); // Take minimum of mirror's length and right boundary
        }

        // Expand around center i
        while (processedString[i + (1 + p[i])] == processedString[i - (1 + p[i])]) {
            p[i]++;
        }

        // If current palindrome expands past right, update center and right
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Update maxLen and start
        if (p[i] > maxLen) {
            maxLen = p[i];
            start = (i - maxLen) / 2; // Original start position
        }
    }
    return s.substr(start, maxLen);
}

// 5. Recursive Approach with Memoization (Top-Down Dynamic Programming)
// Time Complexity: O(n^2), Space Complexity: O(n^2)
string longestPalindromeRecursive(const string& s) {
    int n = s.size();
    if (n <= 1) return s;

    // Memoization table
    vector<vector<int>> memo(n, vector<int>(n, -1));
    int start = 0;
    int maxLength = 1;

    std::function<bool(int, int)> isPalindrome = [&](int i, int j) {
        if (i > j) return true;
        if (memo[i][j] != -1) return memo[i][j] == 1; // Return memoized result as bool
        // Removed the else condition and simplified
        if (s[i] == s[j]) {
            memo[i][j] = isPalindrome(i + 1, j - 1) ? 1 : 0;
        }
        else{
             memo[i][j] = 0;
        }
        return memo[i][j] == 1;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (isPalindrome(i, j) && (j - i + 1 > maxLength)) {
                maxLength = j - i + 1;
                start = i;
            }
        }
    }
    return s.substr(start, maxLength);
}

int main() {
    string s = "babad"; // Example string
    cout << "Input String: " << s << endl << endl;

    // 1. Dynamic Programming - Tabulation
    cout << "1. Dynamic Programming - Tabulation:" << endl;
    string resultDP = longestPalindromeDP(s);
    cout << "Longest Palindromic Substring: " << resultDP << endl;

    // 2. Optimized Dynamic Programming - Tabulation
    cout << "\n2. Optimized Dynamic Programming - Tabulation:" << endl;
    string resultDPOptimized = longestPalindromeDPOptimized(s);
    cout << "Longest Palindromic Substring: " << resultDPOptimized << endl;

    // 3. Expand Around Center
    cout << "\n3. Expand Around Center:" << endl;
    string resultExpand = longestPalindromeExpand(s);
    cout << "Longest Palindromic Substring: " << resultExpand << endl;

    // 4. Manacher's Algorithm
    cout << "\n4. Manacher's Algorithm:" << endl;
    string resultManacher = longestPalindromeManacher(s);
    cout << "Longest Palindromic Substring: " << resultManacher << endl;

    // 5. Recursive with Memoization
    cout << "\n5. Recursive Approach with Memoization:" << endl;
    string resultRecursive = longestPalindromeRecursive(s);
    cout << "Longest Palindromic Substring: " << resultRecursive << endl;

    return 0;
}

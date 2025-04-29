#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// 1. Recursive Approach for LCS
//    - Base Case: If either string is empty, LCS is 0.
//    - Recursive Step:
//      - If characters match, add 1 to LCS of prefixes.
//      - Else, take the maximum of LCS of (s1 prefix, s2) and (s1, s2 prefix).
int lcsRecursive(const string& s1, const string& s2, int i, int j) {
    if (i == 0 || j == 0) {
        return 0;
    }
    if (s1[i - 1] == s2[j - 1]) {
        return 1 + lcsRecursive(s1, s2, i - 1, j - 1);
    } else {
        return max(lcsRecursive(s1, s2, i, j - 1), lcsRecursive(s1, s2, i - 1, j));
    }
}

// Wrapper function for the recursive approach
int lcsRecursive(const string& s1, const string& s2) {
    return lcsRecursive(s1, s2, s1.length(), s2.length());
}

// 2. Memoization (Top-Down DP) for LCS
//    - Uses a 2D vector to store results of subproblems.
//    - Initialize the DP table with -1 (indicating not computed).
//    - Base case and recursive step are the same as the recursive approach.
//    - Before computing, check if the result is already stored.
//    - Store the computed result in the DP table.
int lcsMemoization(const string& s1, const string& s2, int i, int j, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = 1 + lcsMemoization(s1, s2, i - 1, j - 1, dp);
    } else {
        dp[i][j] = max(lcsMemoization(s1, s2, i, j - 1, dp), lcsMemoization(s1, s2, i - 1, j, dp));
    }
    return dp[i][j];
}

// Wrapper function for the memoization approach
int lcsMemoization(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return lcsMemoization(s1, s2, n, m, dp);
}

// 3. Tabulation (Bottom-Up DP) for LCS
//    - Creates a 2D vector (DP table) of size (n+1) x (m+1).
//    - DP table is filled in a bottom-up manner.
//    - dp[i][j] stores the length of the LCS of s1[0..i-1] and s2[0..j-1].
//    - Initialization: dp[0][j] = 0 and dp[i][0] = 0 for all i and j.
//    - Iteration:
//      - If s1[i-1] == s2[j-1], dp[i][j] = dp[i-1][j-1] + 1.
//      - Else, dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
int lcsTabulation(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// 4. Space Optimized DP for LCS
//    - Uses only two rows of the DP table at a time.
//    - Reduces space complexity from O(n*m) to O(min(n, m)).
//    - `prev` stores the previous row's values, and `curr` stores the current row's values.
int lcsSpaceOptimized(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();

    // Ensure that s2 is the shorter string.  This is crucial for space optimization.
    if (n < m) {
        return lcsSpaceOptimized(s2, s1); // Swap s1 and s2
    }

    vector<int> prev(m + 1, 0); // Previous row
    vector<int> curr(m + 1, 0); // Current row

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr; // Update prev to be the current row.
    }
    return prev[m];
}

// 5.  Finding the LCS String (Tabulation with String Reconstruction)
//     -  This approach is based on the tabulation method.
//     -  After filling the DP table, it backtracks to construct the LCS string.
string findLCS(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Backtrack to construct the LCS string
    int i = n, j = m;
    string lcs = "";
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs; // Prepend the character to the LCS string
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    return lcs;
}

int main() {
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << endl;

    cout << "1. Recursive LCS Length: " << lcsRecursive(s1, s2) << endl;
    cout << "2. Memoization LCS Length: " << lcsMemoization(s1, s2) << endl;
    cout << "3. Tabulation LCS Length: " << lcsTabulation(s1, s2) << endl;
    cout << "4. Space Optimized LCS Length: " << lcsSpaceOptimized(s1, s2) << endl;
    cout << "5. LCS String: " << findLCS(s1, s2) << endl;

    return 0;
}

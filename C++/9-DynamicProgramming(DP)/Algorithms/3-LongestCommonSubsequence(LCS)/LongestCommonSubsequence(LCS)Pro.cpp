#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // for std::accumulate

using namespace std;

// 1. Recursive Approach (Basic, not optimized)
//   - Conceptually simple, but has exponential time complexity.
//   - Useful for understanding the basic idea of LCS.
//   - Not suitable for large strings due to performance issues.
int lcsRecursive(const string& text1, const string& text2, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (text1[m - 1] == text2[n - 1]) {
        return 1 + lcsRecursive(text1, text2, m - 1, n - 1);
    } else {
        return max(lcsRecursive(text1, text2, m, n - 1), lcsRecursive(text1, text2, m - 1, n));
    }
}

// 2. Memoization (Top-Down DP)
//   - Uses a table to store results of subproblems to avoid redundant calculations.
//   - Still recursive, but much more efficient than the pure recursive approach.
//   - Suitable for moderate-sized strings.
int lcsMemoization(const string& text1, const string& text2, int m, int n, vector<vector<int>>& dp) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (dp[m][n] != -1) {
        return dp[m][n];
    }
    if (text1[m - 1] == text2[n - 1]) {
        dp[m][n] = 1 + lcsMemoization(text1, text2, m - 1, n - 1, dp);
    } else {
        dp[m][n] = max(lcsMemoization(text1, text2, m, n - 1, dp), lcsMemoization(text1, text2, m - 1, n, dp));
    }
    return dp[m][n];
}

// 3. Tabulation (Bottom-Up DP)
//   - Builds the DP table iteratively, starting from the base cases.
//   - Generally more efficient than memoization as it avoids recursion overhead.
//   - Preferred approach for most LCS problems.
int lcsTabulation(const string& text1, const string& text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    return dp[m][n];
}

// 4. Space Optimized Tabulation (1D DP)
//   - Further optimizes the tabulation approach by using only one 1D array.
//   - Reduces space complexity from O(m*n) to O(min(m, n)).
//   - Useful when memory is a concern.
int lcsSpaceOptimized(const string& text1, const string& text2) {
    int m = text1.length();
    int n = text2.length();

    // Ensure that 'dp' array size is equal to the smaller string length
    if (m < n) {
        return lcsSpaceOptimized(text2, text1); // Swap to make text1 longer
    }
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        int prev = 0; // Store the value of dp[j-1] from the previous iteration
        for (int j = 1; j <= n; ++j) {
            int temp = dp[j]; // Store current dp[j] before it is overwritten
            if (text1[i - 1] == text2[j - 1]) {
                dp[j] = 1 + prev; // Use 'prev' instead of dp[j-1]
            } else {
                dp[j] = max(dp[j], dp[j - 1]);
            }
            prev = temp; // Update 'prev' for the next iteration
        }
    }
    return dp[n];
}

// 5.  Finding the LCS String (Tabulation with Backtracking)
//    -  Extends the tabulation method to reconstruct the actual LCS string.
//    -  Useful when you need the sequence of characters, not just the length.
string findLCS(const string& text1, const string& text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build the DP table (same as tabulation)
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    // Backtrack to find the LCS string
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (text1[i - 1] == text2[j - 1]) {
            lcs = text1[i - 1] + lcs; // Prepend the character
            --i;
            --j;
        } else if (dp[i][j - 1] > dp[i - 1][j]) {
            --j;
        } else {
            --i;
        }
    }
    return lcs;
}

int main() {
    string text1 = "AGGTAB";
    string text2 = "GXTXAYB";

    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;
    cout << endl;

    // 1. Recursive Approach
    cout << "1. Recursive Approach: " << lcsRecursive(text1, text2, text1.length(), text2.length()) << endl;

    // 2. Memoization
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    cout << "2. Memoization: " << lcsMemoization(text1, text2, m, n, dp) << endl;

    // 3. Tabulation
    cout << "3. Tabulation: " << lcsTabulation(text1, text2) << endl;

    // 4. Space Optimized Tabulation
    cout << "4. Space Optimized Tabulation: " << lcsSpaceOptimized(text1, text2) << endl;

     // 5. Finding the LCS String
    cout << "5. LCS String: " << findLCS(text1, text2) << endl;

    return 0;
}

/*
**Real-World Applications of Longest Common Subsequence (LCS):**

1.  **Bioinformatics (Genome Sequencing):**
    * LCS is used to identify similarities between DNA sequences.
    * By finding the longest common subsequence of two DNA strands, researchers can determine evolutionary relationships and identify conserved regions, which may have functional significance.
    * **Code Example:** The `findLCS` function can be adapted to return the actual common sequence, which is crucial in bioinformatics.  The alignment of the LCS helps visualize where the sequences match.

2.  **Version Control Systems (Git):**
    * Git uses LCS to determine the differences between versions of a file (diff command).
    * The longest common part of the two files is identified, and the rest is marked as added or deleted.  This is the core of how Git merges changes.
    * **Code Example:** The `lcsTabulation` or `lcsSpaceOptimized` functions provide the length, which is essential for calculating the percentage of similarity or the number of changes.  Git's diff algorithm is more complex, but LCS is a fundamental part of it.

3.  **Spell Checkers and Text Comparison:**
    * LCS can be used to identify the similarity between two words or sentences.
    * This is useful for spell checkers to suggest corrections or for plagiarism detection software to find similarities between documents.
     * **Code Example**:  Imagine comparing "intention" and "execution".  The LCS helps identify the common "ention".  The differing parts help in suggesting corrections.

4.  **Data Compression:**
     * While not a direct application, the concept of finding common patterns (which is what LCS does) is used in some data compression techniques.  By identifying repeating sequences, data can be stored more efficiently.
     * **Example**:  If you have many files with similar headers, an LCS-like approach can help identify the common header for efficient storage.

5.  **User Interface Design (Diff Utilities):**
    * Many UI tools show the difference between two versions of a document or code.  LCS helps in highlighting the changes (additions and deletions) in a user-friendly way.
    * **Code Example:** The `findLCS` function, along with the DP table from `lcsTabulation`, can be used to not only find the LCS but also the parts that are *not* in the LCS, which represent the differences.

**Key Improvements and Considerations:**
* **Error Handling:** In real-world applications, you'd add error handling (e.g., checking for null or empty input strings).
* **Large Inputs:** For very large inputs, consider more advanced techniques or libraries optimized for sequence alignment (especially in bioinformatics).
* **Optimization:** The space-optimized version is crucial for scenarios with memory constraints.
* **Unicode:** The code assumes ASCII strings.  For real-world text processing, you'd need to handle Unicode correctly.
* **Visualization:** In UI applications, the LCS and the differences are often visualized (e.g., highlighting the common parts).
*/

import java.util.Arrays;

public class LCS {

    /**
     * **Project 1: Bioinformatics - Genome Sequencing Comparison**
     *
     * **Problem:** In bioinformatics, comparing DNA sequences is crucial for understanding evolutionary relationships,
     * identifying conserved regions, and detecting mutations. The Longest Common Subsequence (LCS) algorithm
     * can be used to find the longest sequence of nucleotides (A, C, G, T) that are common to two DNA strands.
     *
     * **Approach 1: Recursive Approach (Conceptual - Inefficient for Large Sequences)**
     *
     * **Explanation:** This is the most basic approach, where we recursively check for common characters
     * in the two sequences.  If the last characters match, we include them in the LCS and recursively
     * find the LCS of the remaining prefixes. If they don't match, we recursively find the LCS of the
     * two possible pairs of prefixes (excluding the last character of either sequence).
     *
     * **Code:**
     */
    public static int lcsRecursive(String s1, String s2, int m, int n) {
        if (m == 0 || n == 0) {
            return 0; // Base case: If either sequence is empty, the LCS is 0.
        }
        if (s1.charAt(m - 1) == s2.charAt(n - 1)) {
            // If the last characters match, include them in the LCS and recurse.
            return 1 + lcsRecursive(s1, s2, m - 1, n - 1);
        } else {
            // If the last characters don't match, take the maximum of two possibilities:
            // 1. Exclude the last character of s1 and find LCS.
            // 2. Exclude the last character of s2 and find LCS.
            return Math.max(lcsRecursive(s1, s2, m - 1, n), lcsRecursive(s1, s2, m, n - 1));
        }
    }

    /**
     * **Project 2: Software Development - Version Control Diff Utility**
     *
     * **Problem:** A diff utility in version control systems (like Git) needs to identify the differences
     * between two versions of a file.  The LCS can be used to find the longest sequence of lines that
     * are common to both versions.  These common lines represent the parts of the file that haven't changed,
     * while the remaining lines are insertions or deletions.
     *
     * **Approach 2: Top-Down Dynamic Programming with Memoization**
     *
     * **Explanation:** This approach is similar to the recursive approach, but it uses a table (memo) to
     * store the results of previously computed subproblems. This avoids redundant computations and
     * significantly improves performance, especially for larger sequences.
     *
     * **Code:**
     */
    public static int lcsMemoization(String s1, String s2, int m, int n, int[][] memo) {
        if (m == 0 || n == 0) {
            return 0; // Base case: If either sequence is empty, the LCS is 0.
        }
        if (memo[m][n] != -1) {
            return memo[m][n]; // Return the stored result if it has already been computed.
        }
        if (s1.charAt(m - 1) == s2.charAt(n - 1)) {
            // If the last characters match, include them in the LCS and recurse.
            memo[m][n] = 1 + lcsMemoization(s1, s2, m - 1, n - 1, memo);
            return memo[m][n];
        } else {
            // If the last characters don't match, take the maximum of two possibilities:
            // 1. Exclude the last character of s1 and find LCS.
            // 2. Exclude the last character of s2 and find LCS.
            memo[m][n] = Math.max(lcsMemoization(s1, s2, m - 1, n, memo), lcsMemoization(s1, s2, m, n - 1, memo));
            return memo[m][n];
        }
    }

    /**
     * **Project 3: Text Editing - Spell Checker Suggestion Generation**
     *
     * **Problem:** A spell checker needs to suggest possible corrections for misspelled words.  While edit distance is more common,
     * LCS can help identify the longest part of a potentially misspelled word that is a valid prefix or substring
     * of words in a dictionary.  This can be used as one factor in ranking suggested corrections.
     *
     * **Approach 3: Bottom-Up Dynamic Programming (Tabulation)**
     *
     * **Explanation:** This is the most common and efficient dynamic programming approach for LCS.  It builds a table
     * (dp) in a bottom-up manner, where dp[i][j] stores the length of the LCS of the first i characters of s1
     * and the first j characters of s2.  The table is filled iteratively, starting from the base cases (empty prefixes)
     * and building up to the solution for the complete sequences.
     *
     * **Code:**
     */
    public static int lcsTabulation(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        // Initialize the first row and column of the table to 0 (base cases).
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }

        // Fill the table in a bottom-up manner.
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    // If the characters match, extend the LCS by 1.
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // If the characters don't match, take the maximum of the two possibilities.
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n]; // The result is in the bottom-right corner of the table.
    }

    /**
     * **Project 4: Data Compression - File Comparison for Patch Generation**
     *
     * **Problem:** In data compression, especially when generating patches for updating files, it's important to find
     * the common parts between the old and new versions of a file.  LCS can be adapted to find the longest
     * sequence of identical bytes (or lines) between the two files, allowing for efficient calculation of the
     * differences that need to be included in the patch.  This reduces the size of the patch and the amount of
     * data that needs to be transferred.
     *
     * **Approach 4: Space-Optimized Dynamic Programming (Tabulation with 1D Array)**
     *
     * **Explanation:** The tabulation method uses a 2D array, but we can optimize the space complexity to O(n)
     * by using only two rows at a time.  We can further optimize it to use only one 1D array. This is because to calculate
     * `dp[i][j]`, we only need `dp[i-1][j]`, `dp[i][j-1]`, and `dp[i-1][j-1]`.
     *
     * **Code:**
     */
    public static int lcsSpaceOptimized(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[] dp = new int[n + 1];

        for (int i = 1; i <= m; i++) {
            int prev = 0; // Store the value of dp[i-1][j-1]
            for (int j = 1; j <= n; j++) {
                int temp = dp[j]; // Store the current dp[j] (which is dp[i-1][j])
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[j] = prev + 1; // Use 'prev' instead of dp[j-1]
                } else {
                    dp[j] = Math.max(dp[j], dp[j - 1]);
                }
                prev = temp; // Update 'prev' for the next iteration
            }
        }
        return dp[n];
    }

    /**
     * **Project 5: Information Retrieval - Query Expansion with Synonym Identification**
     *
     * **Problem:** In information retrieval, when a user searches for something, the system might want to expand the
     * query with synonyms to improve search results.  LCS can be used in a simplified way to find the longest
     * common prefix or substring between the query and words in a thesaurus.  While more sophisticated techniques
     * exist, this demonstrates a potential application of LCS in text analysis.
     *
     * **Approach 5:  Finding the LCS String (Reconstruction)**
     *
     * **Explanation:** Instead of just finding the *length* of the LCS, this approach reconstructs the actual
     * LCS string.  It uses the dp table from the tabulation method to backtrack and identify the characters
     * that are part of the LCS.
     *
     * **Code:**
     */
    public static String lcsString(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        // Build the dp table as in the tabulation method.
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Backtrack to reconstruct the LCS string.
        int i = m, j = n;
        StringBuilder lcs = new StringBuilder();
        while (i > 0 && j > 0) {
            if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                lcs.append(s1.charAt(i - 1)); // Or s2.charAt(j-1), they are the same.
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        return lcs.reverse().toString(); // Reverse the string to get the correct order.
    }

    public static void main(String[] args) {
        String s1 = "AGGTAB";
        String s2 = "GXTXAYB";
        int m = s1.length();
        int n = s2.length();

        // Approach 1: Recursive
        System.out.println("Longest Common Subsequence (Recursive): " + lcsRecursive(s1, s2, m, n)); // Output: 4

        // Approach 2: Memoization
        int[][] memo = new int[m + 1][n + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        System.out.println("Longest Common Subsequence (Memoization): " + lcsMemoization(s1, s2, m, n, memo)); // Output: 4

        // Approach 3: Tabulation
        System.out.println("Longest Common Subsequence (Tabulation): " + lcsTabulation(s1, s2)); // Output: 4

        // Approach 4: Space Optimization
        System.out.println("Longest Common Subsequence (Space Optimized): " + lcsSpaceOptimized(s1, s2)); // Output: 4

        // Approach 5: LCS String Reconstruction
        System.out.println("Longest Common Subsequence String: " + lcsString(s1, s2)); // Output: GTAB
    }
}


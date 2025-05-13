import java.util.Arrays;

public class LCS {

    public static void main(String[] args) {
        String s1 = "AGGTAB";
        String s2 = "GXTXAYB";

        System.out.println("String 1: " + s1);
        System.out.println("String 2: " + s2);

        // 1. Recursive Approach
        System.out.println("\n1. Recursive Approach:");
        System.out.println("Length of LCS: " + lcsRecursive(s1, s2, s1.length(), s2.length()));

        // 2. Recursive Approach with Memoization
        System.out.println("\n2. Recursive Approach with Memoization:");
        int[][] memo = new int[s1.length() + 1][s2.length() + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        System.out.println("Length of LCS: " + lcsMemoization(s1, s2, s1.length(), s2.length(), memo));

        // 3. Dynamic Programming - Tabulation (Bottom-Up)
        System.out.println("\n3. Dynamic Programming - Tabulation (Bottom-Up):");
        System.out.println("Length of LCS: " + lcsTabulation(s1, s2));

        // 4. Space Optimized DP (1D Array)
        System.out.println("\n4. Space Optimized DP (1D Array):");
        System.out.println("Length of LCS: " + lcsSpaceOptimized(s1, s2));

        // 5. Print LCS String
        System.out.println("\n5. Print LCS String:");
        System.out.println("LCS String: " + printLCS(s1, s2));
    }

    // 1. Recursive Approach
    // Time Complexity: O(2^n), where n is the length of the shorter string.
    // Space Complexity: O(n) - due to the call stack.
    public static int lcsRecursive(String s1, String s2, int m, int n) {
        if (m == 0 || n == 0) {
            return 0;
        }
        if (s1.charAt(m - 1) == s2.charAt(n - 1)) {
            return 1 + lcsRecursive(s1, s2, m - 1, n - 1);
        } else {
            return Math.max(lcsRecursive(s1, s2, m - 1, n), lcsRecursive(s1, s2, m, n - 1));
        }
    }

    // 2. Recursive Approach with Memoization
    // Time Complexity: O(m * n), where m and n are lengths of the strings.
    // Space Complexity: O(m * n) + O(n) - for memoization table and call stack
    public static int lcsMemoization(String s1, String s2, int m, int n, int[][] memo) {
        if (m == 0 || n == 0) {
            return 0;
        }
        if (memo[m][n] != -1) {
            return memo[m][n];
        }
        if (s1.charAt(m - 1) == s2.charAt(n - 1)) {
            memo[m][n] = 1 + lcsMemoization(s1, s2, m - 1, n - 1, memo);
        } else {
            memo[m][n] = Math.max(lcsMemoization(s1, s2, m - 1, n, memo), lcsMemoization(s1, s2, m, n - 1, memo));
        }
        return memo[m][n];
    }

    // 3. Dynamic Programming - Tabulation (Bottom-Up)
    // Time Complexity: O(m * n), where m and n are lengths of the strings.
    // Space Complexity: O(m * n)
    public static int lcsTabulation(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 0;
                } else if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }

    // 4. Space Optimized DP (1D Array)
    // Time Complexity: O(m * n), where m and n are lengths of the strings.
    // Space Complexity: O(min(m, n))
    public static int lcsSpaceOptimized(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();

        // Ensure s1 is the shorter string to optimize space
        if (m < n) {
            String temp = s1;
            s1 = s2;
            s2 = temp;
            m = s1.length();
            n = s2.length();
        }

        int[] dp = new int[n + 1];

        for (int i = 1; i <= m; i++) {
            int prev = 0; // Store the value of dp[j-1] from the previous row
            for (int j = 1; j <= n; j++) {
                int temp = dp[j]; // Store current dp[j] before it's overwritten
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[j] = 1 + prev;
                } else {
                    dp[j] = Math.max(dp[j], dp[j - 1]);
                }
                prev = temp; // Update prev for the next iteration
            }
        }
        return dp[n];
    }

    // 5. Print LCS String
    // Time Complexity: O(m * n), where m and n are lengths of the strings.
    // Space Complexity: O(m * n)
    public static String printLCS(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        // Same as LCS Tabulation to fill the dp table
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 0;
                } else if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Backtrack from dp[m][n] to find the LCS string
        int i = m;
        int j = n;
        StringBuilder lcs = new StringBuilder();
        while (i > 0 && j > 0) {
            if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                lcs.append(s1.charAt(i - 1));
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        return lcs.reverse().toString(); // Reverse the string to get the correct order
    }
}


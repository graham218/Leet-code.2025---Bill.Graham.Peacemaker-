import java.util.Arrays;

public class LongestPalindromicSubstring {

    /**
     * Approach 1: Brute Force
     * -   Checks every possible substring for being a palindrome.
     * -   Time Complexity: O(n^3), where n is the length of the string.
     * -   Space Complexity: O(1).
     * -   Real-world application: Simple string processing in low-resource environments
     * where code simplicity is prioritized over performance, and input sizes are small.
     * For example, checking user input for palindromic properties in a very basic application.
     */
    public static String longestPalindromeBruteForce(String s) {
        if (s == null || s.length() < 1) return "";
        String longest = "";
        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                String sub = s.substring(i, j + 1);
                if (isPalindrome(sub) && sub.length() > longest.length()) {
                    longest = sub;
                }
            }
        }
        return longest;
    }

    private static boolean isPalindrome(String s) {
        int left = 0;
        int right = s.length() - 1;
        while (left < right) {
            if (s.charAt(left) != s.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    /**
     * Approach 2: Dynamic Programming
     * -   Creates a 2D table where dp[i][j] is true if the substring s[i...j] is a palindrome.
     * -   Time Complexity: O(n^2).
     * -   Space Complexity: O(n^2).
     * -   Real-world application: Bioinformatics for sequence alignment, text editing
     * software for advanced text analysis, and data compression algorithms.
     */
    public static String longestPalindromeDP(String s) {
        if (s == null || s.length() < 1) return "";
        int n = s.length();
        boolean[][] dp = new boolean[n][n];
        int start = 0;
        int maxLen = 1;

        // Base cases: single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }

        // Check for palindromes of length greater than 2
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s.charAt(i) == s.charAt(j) && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    if (len > maxLen) {
                        start = i;
                        maxLen = len;
                    }
                }
            }
        }
        return s.substring(start, start + maxLen);
    }


    /**
     * Approach 3: Expand Around Center
     * -   For each character, expand outwards to find the longest palindrome with that character as the center.
     * -   Time Complexity: O(n^2).
     * -   Space Complexity: O(1).
     * -    Real-world application: Used in text processing applications, such as
     * detecting palindromic words or phrases in a document, and in bioinformatics
     * for analyzing DNA sequences.
     */
    public static String longestPalindromeExpandAroundCenter(String s) {
        if (s == null || s.length() < 1) return "";
        int start = 0;
        int maxLen = 1;
        for (int i = 0; i < s.length(); i++) {
            // For odd length palindromes
            int len1 = expandAroundCenter(s, i, i);
            // For even length palindromes
            int len2 = expandAroundCenter(s, i, i + 1);
            int len = Math.max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substring(start, start + maxLen);
    }

    private static int expandAroundCenter(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    /**
     * Approach 4: Manacher's Algorithm
     * -   A linear time complexity algorithm to find the longest palindromic substring.
     * -   Time Complexity: O(n).
     * -   Space Complexity: O(n).
     * -   Real-world application: High-performance text processing, advanced bioinformatics
     * research, and specialized string manipulation libraries.  This is the most
     * efficient algorithm, but it's also the most complex.
     */
    public static String longestPalindromeManacher(String s) {
        if (s == null || s.length() < 1) return "";
        // Preprocess the string to handle even length palindromes
        String processedS = preprocess(s);
        int n = processedS.length();
        int[] p = new int[n]; // Array to store palindrome lengths at each center
        int center = 0, right = 0; // center and right boundary of the rightmost palindrome
        int start = 0, maxLen = 1;

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i; // Mirror position of i with respect to center
            if (i < right) {
                p[i] = Math.min(right - i, p[mirror]); // Take minimum of mirror's length and right boundary
            }

            // Expand around center i
            while (processedS.charAt(i + (1 + p[i])) == processedS.charAt(i - (1 + p[i]))) {
                p[i]++;
            }

            // If current palindrome expands past right, update center and right
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }

            // Update maxLen and start if current palindrome is longer
            if (p[i] > maxLen) {
                maxLen = p[i];
                start = (i - maxLen) / 2; // Original start index in s
            }
        }
        return s.substring(start, start + maxLen);
    }

    private static String preprocess(String s) {
        if (s == null || s.length() == 0) return "^$";  // Handle empty string case
        StringBuilder sb = new StringBuilder("^"); // Start with a dummy character
        for (int i = 0; i < s.length(); i++) {
            sb.append("#").append(s.charAt(i)); // Insert '#' between characters
        }
        sb.append("#$"); // End with '#' and a dummy character
        return sb.toString();
    }

    /**
     * Approach 5: Optimized Dynamic Programming (Space Optimized)
     * -   Optimizes the space complexity of the DP approach by using only two rows
     * of the DP table at a time.
     * -   Time Complexity: O(n^2).
     * -   Space Complexity: O(n).
     * -   Real-world application: Mobile applications or embedded systems with limited memory.
     */
    public static String longestPalindromeOptimizedDP(String s) {
        if (s == null || s.length() < 1) return "";
        int n = s.length();
        boolean[][] dp = new boolean[2][n]; // Only two rows are needed
        int start = 0;
        int maxLen = 1;
        int currentRow = 0;

        // Base cases: single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[currentRow][i] = true;
        }

        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                dp[currentRow][i] = true;
                start = i;
                maxLen = 2;
            } else {
                dp[currentRow][i] = false; // Important:  Need to set this for the loop below
            }
        }

        // Check for palindromes of length greater than 2
        for (int len = 3; len <= n; len++) {
            int prevRow = currentRow; // Store the previous row
            currentRow = 1 - currentRow; // Switch to the other row (0 or 1)

            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s.charAt(i) == s.charAt(j) && dp[prevRow][i + 1]) {
                    dp[currentRow][i] = true;
                    if (len > maxLen) {
                        start = i;
                        maxLen = len;
                    }
                } else {
                    dp[currentRow][i] = false;
                }
            }
        }
        return s.substring(start, start + maxLen);
    }

    public static void main(String[] args) {
        String testString = "babad";
        System.out.println("Input string: " + testString);

        System.out.println("\nLongest Palindromic Substring - Brute Force: " + longestPalindromeBruteForce(testString));
        System.out.println("Longest Palindromic Substring - Dynamic Programming: " + longestPalindromeDP(testString));
        System.out.println("Longest Palindromic Substring - Expand Around Center: " + longestPalindromeExpandAroundCenter(testString));
        System.out.println("Longest Palindromic Substring - Manacher's Algorithm: " + longestPalindromeManacher(testString));
        System.out.println("Longest Palindromic Substring - Optimized DP: " + longestPalindromeOptimizedDP(testString));

        String testString2 = "cbbd";
        System.out.println("\nInput string: " + testString2);

        System.out.println("\nLongest Palindromic Substring - Brute Force: " + longestPalindromeBruteForce(testString2));
        System.out.println("Longest Palindromic Substring - Dynamic Programming: " + longestPalindromeDP(testString2));
        System.out.println("Longest Palindromic Substring - Expand Around Center: " + longestPalindromeExpandAroundCenter(testString2));
        System.out.println("Longest Palindromic Substring - Manacher's Algorithm: " + longestPalindromeManacher(testString2));
        System.out.println("Longest Palindromic Substring - Optimized DP: " + longestPalindromeOptimizedDP(testString2));

        String testString3 = "a";
        System.out.println("\nInput string: " + testString3);
        System.out.println("\nLongest Palindromic Substring - Brute Force: " + longestPalindromeBruteForce(testString3));
        System.out.println("Longest Palindromic Substring - Dynamic Programming: " + longestPalindromeDP(testString3));
        System.out.println("Longest Palindromic Substring - Expand Around Center: " + longestPalindromeExpandAroundCenter(testString3));
        System.out.println("Longest Palindromic Substring - Manacher's Algorithm: " + longestPalindromeManacher(testString3));
        System.out.println("Longest Palindromic Substring - Optimized DP: " + longestPalindromeOptimizedDP(testString3));

        String testString4 = "ac";
        System.out.println("\nInput string: " + testString4);
        System.out.println("\nLongest Palindromic Substring - Brute Force: " + longestPalindromeBruteForce(testString4));
        System.out.println("Longest Palindromic Substring - Dynamic Programming: " + longestPalindromeDP(testString4));
        System.out.println("Longest Palindromic Substring - Expand Around Center: " + longestPalindromeExpandAroundCenter(testString4));
        System.out.println("Longest Palindromic Substring - Manacher's Algorithm: " + longestPalindromeManacher(testString4));
        System.out.println("Longest Palindromic Substring - Optimized DP: " + longestPalindromeOptimizedDP(testString4));
    }
}


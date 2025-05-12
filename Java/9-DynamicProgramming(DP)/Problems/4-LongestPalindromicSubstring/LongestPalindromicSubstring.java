import java.util.Arrays;

public class LongestPalindromicSubstring {

    /**
     * Approach 1: Brute Force
     * -   Time Complexity: O(n^3)
     * -   Space Complexity: O(1)
     *
     * Iterates through all possible substrings and checks if each one is a palindrome.
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

    /**
     * Helper function to check if a string is a palindrome.
     */
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
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(n^2)
     *
     * Creates a 2D table where dp[i][j] is true if the substring s[i...j] is a palindrome.
     */
    public static String longestPalindromeDP(String s) {
        if (s == null || s.length() < 1) return "";
        int n = s.length();
        boolean[][] dp = new boolean[n][n];
        int start = 0;
        int maxLen = 1;

        // Base case: single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        // Base case: two-character substrings
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }

        // Check for palindromes of length 3 and greater
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
     * Approach 3: Optimized Dynamic Programming
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(n^2)
     *
     * Same as DP, but with a slightly different way of filling the table.
     */
    public static String longestPalindromeDPOptimized(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }

        int n = s.length();
        boolean[][] dp = new boolean[n][n];
        int maxLen = 1;
        int start = 0;

        for (int j = 0; j < n; j++) {
            for (int i = 0; i <= j; i++) {
                if (s.charAt(i) == s.charAt(j) && (j - i <= 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        return s.substring(start, start + maxLen);
    }



    /**
     * Approach 4: Expand Around Center
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(1)
     *
     * Considers each character as a potential center of a palindrome and expands around it.
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

    /**
     * Helper function to expand around the center of a potential palindrome.
     */
    private static int expandAroundCenter(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    /**
     * Approach 5: Manacher's Algorithm
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     *
     * The most efficient approach.  Transforms the string to handle even/odd lengths,
     * and uses an array to store palindrome lengths.
     */
    public static String longestPalindromeManacher(String s) {
        if (s == null || s.length() < 1) return "";

        // Preprocess the string to handle even and odd length palindromes
        String processedString = preprocess(s); // O(n)
        int n = processedString.length();
        int[] p = new int[n]; // Array to store palindrome lengths
        int center = 0, right = 0;
        int maxLen = 0, maxCenter = 0;

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;  // Get the mirror of i around the center.

            if (i < right) {
                p[i] = Math.min(right - i, p[mirror]); // Take min of right bound and mirror's p.
            }

            // Expand around center i.
            while (processedString.charAt(i + (1 + p[i])) == processedString.charAt(i - (1 + p[i]))) {
                p[i]++;
            }

            // If current palindrome expands past right, adjust center and right.
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }

            // Track the maximum palindrome length.
            if (p[i] > maxLen) {
                maxLen = p[i];
                maxCenter = i;
            }
        }
        // Extract the original longest palindrome substring.
        int start = (maxCenter - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    /**
     * Helper function to preprocess the string for Manacher's Algorithm.
     * Inserts '#' between characters and at the beginning and end.
     * Example: "aba" -> "^#a#b#a#$"
     */
    private static String preprocess(String s) {
        if (s == null || s.length() == 0) return "^$"; // Handle empty string
        StringBuilder sb = new StringBuilder("^");
        for (int i = 0; i < s.length(); i++) {
            sb.append("#").append(s.charAt(i));
        }
        sb.append("#$");
        return sb.toString();
    }

    public static void main(String[] args) {
        String s = "babad";
        //String s = "cbbd";
        //String s = "a";
        //String s = "ac";

        System.out.println("Input: " + s);
        System.out.println("Longest Palindromic Substring (Brute Force): " + longestPalindromeBruteForce(s));
        System.out.println("Longest Palindromic Substring (Dynamic Programming): " + longestPalindromeDP(s));
        System.out.println("Longest Palindromic Substring (DP Optimized): " + longestPalindromeDPOptimized(s));
        System.out.println("Longest Palindromic Substring (Expand Around Center): " + longestPalindromeExpandAroundCenter(s));
        System.out.println("Longest Palindromic Substring (Manacher's Algorithm): " + longestPalindromeManacher(s));
    }
}


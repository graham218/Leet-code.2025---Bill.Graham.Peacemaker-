import java.util.Arrays;

public class LongestPalindromicSubstring {

    /**
     * Approach 1: Brute Force
     * Time Complexity: O(n^3) - O(n^2) for iterating through all substrings, O(n) for checking if each is a palindrome.
     * Space Complexity: O(1) (excluding string creation for substring, which can be O(n) in worst case for many substrings)
     *
     * This method checks every possible substring and verifies if it's a palindrome.
     * It keeps track of the longest palindrome found so far.
     */
    public String longestPalindromeBruteForce(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }

        String longestPalindrome = "";
        int maxLength = 0;

        // Iterate through all possible starting indices
        for (int i = 0; i < s.length(); i++) {
            // Iterate through all possible ending indices
            for (int j = i; j < s.length(); j++) {
                String sub = s.substring(i, j + 1); // Get the current substring
                if (isPalindrome(sub)) { // Check if it's a palindrome
                    if (sub.length() > maxLength) { // If it's longer than the current longest
                        maxLength = sub.length();
                        longestPalindrome = sub;
                    }
                }
            }
        }
        return longestPalindrome;
    }

    /**
     * Helper method to check if a string is a palindrome.
     * Time Complexity: O(n) where n is the length of the string.
     */
    private boolean isPalindrome(String str) {
        int left = 0;
        int right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left) != str.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }


    /**
     * Approach 2: Dynamic Programming
     * Time Complexity: O(n^2) - We fill an n x n DP table.
     * Space Complexity: O(n^2) - For the 2D boolean array.
     *
     * This method uses a 2D boolean array `dp[i][j]` where `dp[i][j]` is true if
     * the substring `s[i...j]` is a palindrome, and false otherwise.
     *
     * Base Cases:
     * 1. `dp[i][i] = true` (single characters are palindromes).
     * 2. `dp[i][i+1] = (s.charAt(i) == s.charAt(i+1))` (two characters).
     *
     * Recurrence Relation:
     * `dp[i][j] = (s.charAt(i) == s.charAt(j) && dp[i+1][j-1])`
     * A substring `s[i...j]` is a palindrome if `s[i]` equals `s[j]` AND the inner substring `s[i+1...j-1]` is also a palindrome.
     */
    public String longestPalindromeDP(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }

        int n = s.length();
        boolean[][] dp = new boolean[n][n]; // dp[i][j] is true if s[i...j] is a palindrome

        String longestPalindrome = "";
        int maxLength = 0;

        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            if (1 > maxLength) { // Update for single character palindromes
                maxLength = 1;
                longestPalindrome = s.substring(i, i + 1);
            }
        }

        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == s.charAt(i + 1)) {
                dp[i][i + 1] = true;
                if (2 > maxLength) { // Update for two character palindromes
                    maxLength = 2;
                    longestPalindrome = s.substring(i, i + 2);
                }
            }
        }

        // Check for palindromes of length 3 or more
        // `len` represents the length of the substring
        for (int len = 3; len <= n; len++) {
            // `i` represents the starting index of the substring
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1; // `j` represents the ending index of the substring

                // A substring s[i...j] is a palindrome if s[i] == s[j]
                // AND the inner substring s[i+1...j-1] is also a palindrome.
                if (s.charAt(i) == s.charAt(j) && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    if (len > maxLength) { // If current palindrome is longer
                        maxLength = len;
                        longestPalindrome = s.substring(i, j + 1);
                    }
                }
            }
        }
        return longestPalindrome;
    }


    /**
     * Approach 3: Expand Around Center
     * Time Complexity: O(n^2) - In the worst case (e.g., "aaaaa"), each expansion can take O(n) time,
     * and there are O(n) centers.
     * Space Complexity: O(1)
     *
     * This method considers every character as a potential center of an odd-length palindrome
     * and every pair of adjacent characters as a potential center of an even-length palindrome.
     * It then expands outwards from these centers to find the longest palindrome.
     */
    public String longestPalindromeExpandAroundCenter(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }

        int start = 0; // Starting index of the longest palindrome
        int end = 0;   // Ending index of the longest palindrome

        for (int i = 0; i < s.length(); i++) {
            // Case 1: Odd length palindrome (center is s[i])
            int len1 = expandAroundCenter(s, i, i);
            // Case 2: Even length palindrome (center is s[i] and s[i+1])
            int len2 = expandAroundCenter(s, i, i + 1);

            int len = Math.max(len1, len2); // Get the maximum length from both cases

            // If the current palindrome is longer than the previously found longest
            if (len > (end - start + 1)) {
                // Calculate new start and end indices
                // For odd length: i - (len - 1) / 2
                // For even length: i - (len / 2) + 1
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
        return s.substring(start, end + 1);
    }

    /**
     * Helper method to expand around a given center and return the length of the palindrome.
     * `left` and `right` are the initial center indices.
     */
    private int expandAroundCenter(String s, int left, int right) {
        // Expand as long as the indices are within bounds and characters match
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        // The length of the palindrome is (right - 1) - (left + 1) + 1
        // which simplifies to right - left - 1
        return right - left - 1;
    }


    /**
     * Approach 4: Manacher's Algorithm (Standard Implementation)
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * Manacher's algorithm is an optimized dynamic programming approach that finds the
     * longest palindromic substring in linear time. It cleverly handles both odd and
     * even length palindromes by transforming the string.
     *
     * Steps:
     * 1. Preprocessing: Transform the string `s` into a new string `T` by inserting a
     * special character (e.g., '#') between every character, and unique characters
     * at the very beginning and end (e.g., '$' and '@'). This ensures all palindromes
     * in `T` are of odd length, simplifying the logic.
     * Example: "aba" -> "$#a#b#a#@". "abba" -> "$#a#b#b#a#@".
     *
     * 2. `P` Array: Create an array `P` of the same size as `T`. `P[i]` stores the
     * radius of the longest palindrome centered at `T[i]`. If `P[i] = k`, it means
     * the palindrome centered at `T[i]` extends `k` characters to its left and right,
     * i.e., `T[i-k ... i+k]` is a palindrome.
     *
     * 3. Iteration with Optimization:
     * - `center`: The center of the palindrome that extends furthest to the right.
     * - `rightBoundary`: The rightmost boundary of the palindrome centered at `center`.
     * `rightBoundary = center + P[center]`.
     * - For each `i` (current center candidate):
     * - `mirror = 2 * center - i`: This is the mirror image of `i` with respect to `center`.
     * - If `i < rightBoundary`, then `P[i]` can be initialized based on `P[mirror]`.
     * Specifically, `P[i] = Math.min(rightBoundary - i, P[mirror])`. This is the
     * key optimization that avoids redundant checks.
     * - Expand around `i`: Try to extend the palindrome centered at `i` as much as possible.
     * `while (T.charAt(i + P[i] + 1) == T.charAt(i - P[i] - 1)) P[i]++;`
     * - Update `center` and `rightBoundary` if the current palindrome extends beyond `rightBoundary`.
     *
     * 4. Find Max: Keep track of the maximum value in `P` and its corresponding center index.
     *
     * 5. Post-processing: Use the maximum radius and its center in `T` to extract the
     * original longest palindromic substring from `s`.
     */
    public String longestPalindromeManacher(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }

        // Step 1: Preprocessing the string
        // Example: "aba" -> "$#a#b#a#@"
        // Example: "abba" -> "$#a#b#b#a#@"
        StringBuilder sb = new StringBuilder();
        sb.append('$'); // Start delimiter
        for (int i = 0; i < s.length(); i++) {
            sb.append('#');
            sb.append(s.charAt(i));
        }
        sb.append('#');
        sb.append('@'); // End delimiter
        String T = sb.toString(); // Transformed string

        int n = T.length();
        int[] P = new int[n]; // P[i] stores the radius of the palindrome centered at T[i]

        int center = 0;        // Center of the palindrome that extends furthest to the right
        int rightBoundary = 0; // Rightmost boundary of the palindrome centered at 'center' (center + P[center])

        int maxLen = 0;       // Maximum radius found in P
        int centerIndex = 0;  // Center index in T corresponding to maxLen

        // Iterate through the transformed string T
        // We start from 1 and go up to n-2 to avoid the '$' and '@' delimiters
        for (int i = 1; i < n - 1; i++) {
            // Calculate mirror index: mirror = center - (i - center) = 2 * center - i
            int mirror = 2 * center - i;

            // If current index `i` is within the `rightBoundary` of the palindrome centered at `center`
            // We can potentially leverage the palindrome information from its mirror.
            if (i < rightBoundary) {
                // P[i] is at least the minimum of:
                // 1. The distance from `i` to `rightBoundary` (rightBoundary - i)
                // 2. The radius of the palindrome at `mirror` (P[mirror])
                P[i] = Math.min(rightBoundary - i, P[mirror]);
            } else {
                // If `i` is outside or at `rightBoundary`, we can't leverage previous info directly.
                // Start with a minimum radius of 0 (just the center character itself).
                P[i] = 0;
            }

            // Attempt to expand palindrome centered at `i`
            // We check T[i + P[i] + 1] and T[i - P[i] - 1]
            // These are the characters immediately outside the current assumed palindrome.
            while (T.charAt(i + P[i] + 1) == T.charAt(i - P[i] - 1)) {
                P[i]++; // Expand the radius
            }

            // If the current palindrome centered at `i` extends beyond `rightBoundary`
            // Update `center` and `rightBoundary`
            if (i + P[i] > rightBoundary) {
                center = i;
                rightBoundary = i + P[i];
            }

            // Keep track of the maximum palindrome radius and its center
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        // Step 5: Post-processing to reconstruct the original substring
        // The length of the longest palindrome in the original string `s` is `maxLen`.
        // The start index in `T` is `centerIndex - maxLen`.
        // The characters in `T` at odd indices (1, 3, 5, ...) correspond to original characters.
        // The characters in `T` at even indices (0, 2, 4, ...) are '#' or delimiters.
        // So, the start index in the original string `s` can be calculated as:
        // (centerIndex - maxLen) / 2
        int originalStartIndex = (centerIndex - maxLen) / 2;

        return s.substring(originalStartIndex, originalStartIndex + maxLen);
    }


    /**
     * Approach 5: Manacher's Algorithm (Detailed & Refined Implementation)
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * This version provides even more detailed comments and a clear breakdown
     * of the preprocessing and how the `P` array values map back to the
     * original string.
     */
    public String longestPalindromeManacherDetailed(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }

        // --- Step 1: Preprocessing the input string ---
        // The goal is to transform the string such that all palindromes,
        // whether odd or even length in the original string, become odd length
        // palindromes in the transformed string.
        // We insert a special character (e.g., '#') between every character,
        // and add unique boundary characters ('$' at start, '@' at end)
        // to prevent out-of-bounds access during expansion.
        // Example: "aba" -> "$#a#b#a#@" (length 2*N + 3)
        // Example: "abba" -> "$#a#b#b#a#@" (length 2*N + 3)
        StringBuilder transformedBuilder = new StringBuilder();
        transformedBuilder.append('$'); // Unique start boundary
        for (char c : s.toCharArray()) {
            transformedBuilder.append('#'); // Separator
            transformedBuilder.append(c);   // Original character
        }
        transformedBuilder.append('#');     // Last separator
        transformedBuilder.append('@');     // Unique end boundary
        String T = transformedBuilder.toString();

        int n = T.length(); // Length of the transformed string
        int[] P = new int[n]; // P[i] will store the radius of the palindrome centered at T[i]
        // A radius of `k` means the palindrome extends `k` characters
        // to the left and right of T[i], i.e., T[i-k ... i+k] is a palindrome.
        // Note: P[i] corresponds to the length of the palindrome in the original
        // string if the center is an original character, or 0 if it's a '#'.
        // More precisely, P[i] is the length of the palindrome in T, divided by 2.

        int center = 0;        // `center` is the center of the palindrome that currently
        // extends furthest to the right.
        int rightBoundary = 0; // `rightBoundary` is the rightmost index reached by the palindrome
        // centered at `center`. It's calculated as `center + P[center]`.

        int maxPalindromeLength = 0; // Stores the maximum radius found in P[], which is the length
        // of the longest palindrome in the original string.
        int centerOfMaxPalindrome = 0; // Stores the index in T of the center of this longest palindrome.

        // --- Step 2: Iterate through the transformed string to populate the P array ---
        // We iterate from index 1 to n-2, skipping the '$' and '@' boundary characters.
        for (int i = 1; i < n - 1; i++) {
            // Calculate `mirror`: The index symmetric to `i` with respect to `center`.
            // `mirror = center - (i - center) = 2 * center - i`.
            int mirror = 2 * center - i;

            // Optimization: If `i` is within the current `rightBoundary` (i.e., `i < rightBoundary`),
            // we can initialize `P[i]` based on `P[mirror]`.
            // The intuition is that the palindrome centered at `mirror` might provide
            // a lower bound for the palindrome centered at `i`.
            // We take the minimum of:
            // 1. The remaining distance to `rightBoundary` from `i`: `rightBoundary - i`.
            //    This is the maximum possible radius for `P[i]` without extending beyond `rightBoundary`.
            // 2. The radius of the palindrome at `mirror`: `P[mirror]`.
            //    If the palindrome at `mirror` is fully contained within the palindrome centered at `center`,
            //    then the palindrome at `i` will have at least the same radius as `P[mirror]`.
            if (i < rightBoundary) {
                P[i] = Math.min(rightBoundary - i, P[mirror]);
            } else {
                // If `i` is outside or at the `rightBoundary`, we cannot use the mirror optimization.
                // We start with a radius of 0 (meaning just the character T[i] itself).
                P[i] = 0;
            }

            // --- Step 3: Expand around the current center `i` ---
            // We try to expand the palindrome centered at `i` as much as possible.
            // We check if characters `T[i + P[i] + 1]` and `T[i - P[i] - 1]` are equal.
            // These are the characters immediately outside the current assumed palindrome.
            // The `+1` and `-1` are crucial because `P[i]` is the current radius,
            // so `i + P[i]` and `i - P[i]` are the current boundaries.
            // We also need to ensure we don't go out of bounds of `T`.
            while (T.charAt(i + P[i] + 1) == T.charAt(i - P[i] - 1)) {
                P[i]++; // Increment the radius if characters match
            }

            // --- Step 4: Update `center` and `rightBoundary` ---
            // If the palindrome centered at `i` extends beyond the current `rightBoundary`,
            // it means we've found a new palindrome that reaches further to the right.
            // We update `center` to `i` and `rightBoundary` to `i + P[i]`.
            if (i + P[i] > rightBoundary) {
                center = i;
                rightBoundary = i + P[i];
            }

            // --- Step 5: Track the longest palindrome found so far ---
            // `P[i]` directly gives us the radius of the palindrome in `T`.
            // This radius `P[i]` is also the length of the corresponding palindrome
            // in the original string `s`.
            if (P[i] > maxPalindromeLength) {
                maxPalindromeLength = P[i];
                centerOfMaxPalindrome = i;
            }
        }

        // --- Step 6: Extract the longest palindromic substring from the original string ---
        // `maxPalindromeLength` is the length of the longest palindrome in `s`.
        // `centerOfMaxPalindrome` is the center index in `T`.
        //
        // To find the starting index in the original string `s`:
        // Consider the transformed string `T`: $ # c1 # c2 # c3 # ... # cN # @
        // The characters from the original string `s` are at odd indices in `T` (1, 3, 5, ...).
        // The center `centerOfMaxPalindrome` is an index in `T`.
        // The left boundary of the longest palindrome in `T` is `centerOfMaxPalindrome - maxPalindromeLength`.
        //
        // If `centerOfMaxPalindrome - maxPalindromeLength` is `k` in `T`,
        // then the original character corresponding to `T[k]` is `s[k/2]`.
        // So, the start index in `s` is `(centerOfMaxPalindrome - maxPalindromeLength) / 2`.
        int originalStartIndex = (centerOfMaxPalindrome - maxPalindromeLength) / 2;

        return s.substring(originalStartIndex, originalStartIndex + maxPalindromeLength);
    }


    public static void main(String[] args) {
        LongestPalindromicSubstring solver = new LongestPalindromicSubstring();

        String s1 = "babad";
        String s2 = "cbbd";
        String s3 = "a";
        String s4 = "ac";
        String s5 = "racecar";
        String s6 = "madam";
        String s7 = "aaaaa";
        String s8 = "forgeeksskeegfor";

        System.out.println("--- Brute Force ---");
        System.out.println(s1 + " -> " + solver.longestPalindromeBruteForce(s1)); // Output: bab or aba
        System.out.println(s2 + " -> " + solver.longestPalindromeBruteForce(s2)); // Output: bb
        System.out.println(s3 + " -> " + solver.longestPalindromeBruteForce(s3)); // Output: a
        System.out.println(s4 + " -> " + solver.longestPalindromeBruteForce(s4)); // Output: a or c
        System.out.println(s5 + " -> " + solver.longestPalindromeBruteForce(s5)); // Output: racecar
        System.out.println(s6 + " -> " + solver.longestPalindromeBruteForce(s6)); // Output: madam
        System.out.println(s7 + " -> " + solver.longestPalindromeBruteForce(s7)); // Output: aaaaa
        System.out.println(s8 + " -> " + solver.longestPalindromeBruteForce(s8)); // Output: geeksskeeg

        System.out.println("\n--- Dynamic Programming ---");
        System.out.println(s1 + " -> " + solver.longestPalindromeDP(s1)); // Output: bab or aba
        System.out.println(s2 + " -> " + solver.longestPalindromeDP(s2)); // Output: bb
        System.out.println(s3 + " -> " + solver.longestPalindromeDP(s3)); // Output: a
        System.out.println(s4 + " -> " + solver.longestPalindromeDP(s4)); // Output: a or c
        System.out.println(s5 + " -> " + solver.longestPalindromeDP(s5)); // Output: racecar
        System.out.println(s6 + " -> " + solver.longestPalindromeDP(s6)); // Output: madam
        System.out.println(s7 + " -> " + solver.longestPalindromeDP(s7)); // Output: aaaaa
        System.out.println(s8 + " -> " + solver.longestPalindromeDP(s8)); // Output: geeksskeeg

        System.out.println("\n--- Expand Around Center ---");
        System.out.println(s1 + " -> " + solver.longestPalindromeExpandAroundCenter(s1)); // Output: bab or aba
        System.out.println(s2 + " -> " + solver.longestPalindromeExpandAroundCenter(s2)); // Output: bb
        System.out.println(s3 + " -> " + solver.longestPalindromeExpandAroundCenter(s3)); // Output: a
        System.out.println(s4 + " -> " + solver.longestPalindromeExpandAroundCenter(s4)); // Output: a or c
        System.out.println(s5 + " -> " + solver.longestPalindromeExpandAroundCenter(s5)); // Output: racecar
        System.out.println(s6 + " -> " + solver.longestPalindromeExpandAroundCenter(s6)); // Output: madam
        System.out.println(s7 + " -> " + solver.longestPalindromeExpandAroundCenter(s7)); // Output: aaaaa
        System.out.println(s8 + " -> " + solver.longestPalindromeExpandAroundCenter(s8)); // Output: geeksskeeg

        System.out.println("\n--- Manacher's Algorithm (Standard) ---");
        System.out.println(s1 + " -> " + solver.longestPalindromeManacher(s1)); // Output: bab or aba
        System.out.println(s2 + " -> " + solver.longestPalindromeManacher(s2)); // Output: bb
        System.out.println(s3 + " -> " + solver.longestPalindromeManacher(s3)); // Output: a
        System.out.println(s4 + " -> " + solver.longestPalindromeManacher(s4)); // Output: a or c
        System.out.println(s5 + " -> " + solver.longestPalindromeManacher(s5)); // Output: racecar
        System.out.println(s6 + " -> " + solver.longestPalindromeManacher(s6)); // Output: madam
        System.out.println(s7 + " -> " + solver.longestPalindromeManacher(s7)); // Output: aaaaa
        System.out.println(s8 + " -> " + solver.longestPalindromeManacher(s8)); // Output: geeksskeeg

        System.out.println("\n--- Manacher's Algorithm (Detailed & Refined) ---");
        System.out.println(s1 + " -> " + solver.longestPalindromeManacherDetailed(s1)); // Output: bab or aba
        System.out.println(s2 + " -> " + solver.longestPalindromeManacherDetailed(s2)); // Output: bb
        System.out.println(s3 + " -> " + solver.longestPalindromeManacherDetailed(s3)); // Output: a
        System.out.println(s4 + " -> " + solver.longestPalindromeManacherDetailed(s4)); // Output: a or c
        System.out.println(s5 + " -> " + solver.longestPalindromeManacherDetailed(s5)); // Output: racecar
        System.out.println(s6 + " -> " + solver.longestPalindromeManacherDetailed(s6)); // Output: madam
        System.out.println(s7 + " -> " + solver.longestPalindromeManacherDetailed(s7)); // Output: aaaaa
        System.out.println(s8 + " -> " + solver.longestPalindromeManacherDetailed(s8)); // Output: geeksskeeg
    }
}

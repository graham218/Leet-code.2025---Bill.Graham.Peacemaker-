import java.util.*;
import java.io.*;

class SlidingWindow {

    // =================================================================================================
    // 1. Fixed Size Sliding Window - Maximum Sum Subarray
    // =================================================================================================
    /**
     * Given an array of integers and a window size, find the maximum sum of any contiguous subarray of the given size.
     *
     * Project Implementation:
     * -   Real-time stock price analysis: Calculate the moving average of stock prices over a fixed window (e.g., last 5 days) to identify trends.
     * -   Network traffic monitoring: Analyze network packets in fixed-size intervals to detect anomalies or spikes in traffic.
     *
     * Time Complexity: O(n) - Linear, where n is the length of the array.
     * Space Complexity: O(1) - Constant, as we only use a few variables.
     *
     * @param arr    The input array of integers.
     * @param windowSize The size of the sliding window.
     * @return The maximum sum of any subarray of the given size.  Returns Integer.MIN_VALUE if
     * the input array is null or the window size is invalid.
     */
    public static int maxSumSubarray(int[] arr, int windowSize) {
        if (arr == null || arr.length < windowSize || windowSize <= 0) {
            return Integer.MIN_VALUE; // Handle invalid input
        }

        int maxSum = 0;
        int currentSum = 0;

        // Calculate the sum of the first window
        for (int i = 0; i < windowSize; i++) {
            currentSum += arr[i];
        }
        maxSum = currentSum; // Initialize maxSum

        // Slide the window through the rest of the array
        for (int i = windowSize; i < arr.length; i++) {
            currentSum = currentSum - arr[i - windowSize] + arr[i]; // Subtract the element going out of the window and add the new element
            maxSum = Math.max(maxSum, currentSum); // Update maxSum if needed
        }

        return maxSum;
    }

    // =================================================================================================
    // 2. Dynamic Sliding Window - Minimum Window Substring
    // =================================================================================================
    /**
     * Given a string `s` and a string `t`, find the minimum window in `s` which will contain all the characters in `t`.
     *
     * Project Implementation:
     * -   Text search and analysis: Find the smallest section of a document containing all keywords.
     * -   Bioinformatics: Locate the shortest DNA sequence containing a set of specific genes.
     *
     * Time Complexity: O(n + m) - where n is the length of string `s`, and m is the length of string `t`.
     * Space Complexity: O(m) -  where m is the length of string `t` (for the character frequency maps).
     *
     * @param s The string to search in.
     * @param t The string containing the characters to find.
     * @return The minimum window substring in `s` that contains all characters from `t`.
     * Returns an empty string if no such window exists.
     */
    public static String minWindowSubstring(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return ""; // Handle invalid input
        }

        Map<Character, Integer> targetMap = new HashMap<>(); // Frequency of characters in t
        for (char c : t.toCharArray()) {
            targetMap.put(c, targetMap.getOrDefault(c, 0) + 1);
        }

        int left = 0;
        int right = 0;
        int minLength = Integer.MAX_VALUE;
        int start = 0;
        int matched = 0; // Count of characters matched

        Map<Character, Integer> windowMap = new HashMap<>(); // Frequency of characters in the current window

        while (right < s.length()) {
            char c = s.charAt(right);
            windowMap.put(c, windowMap.getOrDefault(c, 0) + 1);

            if (targetMap.containsKey(c) && windowMap.get(c).intValue() == targetMap.get(c).intValue()) {
                matched++;
            }

            // Try to minimize the window size
            while (left <= right && matched == targetMap.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    start = left;
                }

                char leftChar = s.charAt(left);
                windowMap.put(leftChar, windowMap.get(leftChar) - 1);
                if (targetMap.containsKey(leftChar) && windowMap.get(leftChar).intValue() < targetMap.get(leftChar).intValue()) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minLength == Integer.MAX_VALUE ? "" : s.substring(start, start + minLength);
    }

    // =================================================================================================
    // 3. Dynamic Sliding Window - Longest Substring Without Repeating Characters
    // =================================================================================================
    /**
     * Given a string, find the length of the longest substring without repeating characters.
     *
     * Project Implementation:
     * -   Data compression: Identify patterns in data streams for efficient compression algorithms.
     * -   Bioinformatics: Analyze DNA sequences to find the longest unique sequence.
     *
     * Time Complexity: O(n) - where n is the length of the string.
     * Space Complexity: O(min(m, n)) - where n is the length of the string, and m is the size of the character set.
     *
     * @param s The input string.
     * @return The length of the longest substring without repeating characters.
     */
    public static int longestSubstringWithoutRepeatingCharacters(String s) {
        if (s == null || s.isEmpty()) {
            return 0;
        }

        int left = 0;
        int right = 0;
        int maxLength = 0;
        Set<Character> charSet = new HashSet<>();

        while (right < s.length()) {
            char c = s.charAt(right);
            if (!charSet.contains(c)) {
                charSet.add(c);
                maxLength = Math.max(maxLength, right - left + 1);
                right++;
            } else {
                char leftChar = s.charAt(left);
                charSet.remove(leftChar);
                left++;
            }
        }
        return maxLength;
    }

    // =================================================================================================
    // 4. Dynamic Sliding Window -  Longest Substring with At Most K Distinct Characters
    // =================================================================================================

    /**
     * Given a string `s` and an integer `k`, find the length of the longest substring of `s` with at most `k` distinct characters.
     *
     * Project Implementation:
     * -   Genomics: Analyzing DNA sequences with a limited number of mutations.
     * -   Data stream processing:  Finding patterns in real-time data with constraints on unique elements.
     *
     * Time Complexity: O(n) - where n is the length of the string.
     * Space Complexity: O(k) - where k is the maximum number of distinct characters allowed.
     *
     * @param s The input string.
     * @param k The maximum number of distinct characters allowed in the substring.
     * @return The length of the longest substring with at most k distinct characters.
     */
    public static int longestSubstringWithAtMostKDistinctCharacters(String s, int k) {
        if (s == null || s.isEmpty() || k <= 0) {
            return 0; // Handle invalid input
        }

        int left = 0;
        int right = 0;
        int maxLength = 0;
        Map<Character, Integer> charFrequencyMap = new HashMap<>(); // Character frequencies

        while (right < s.length()) {
            char c = s.charAt(right);
            charFrequencyMap.put(c, charFrequencyMap.getOrDefault(c, 0) + 1);

            // If the number of distinct characters exceeds k, shrink the window
            while (charFrequencyMap.size() > k) {
                char leftChar = s.charAt(left);
                charFrequencyMap.put(leftChar, charFrequencyMap.get(leftChar) - 1);
                if (charFrequencyMap.get(leftChar) == 0) {
                    charFrequencyMap.remove(leftChar);
                }
                left++;
            }

            // Update the maximum length
            maxLength = Math.max(maxLength, right - left + 1);
            right++;
        }
        return maxLength;
    }

    // =================================================================================================
    // 5. Dynamic Sliding Window -  Count Occurrences of Anagrams
    // =================================================================================================
    /**
     * Given a text `txt` and a pattern `pat`, find the number of times the anagram of pattern appears in text.
     *
     * Project Implementation:
     * -   Intrusion detection: Detect suspicious patterns in log files.
     * -   Plagiarism detection: Identify sections of text that are anagrams of other sources.
     *
     * Time Complexity: O(n) - where n is the length of the text `txt`.
     * Space Complexity: O(m) - where m is the length of the pattern `pat`.
     *
     * @param txt The text to search in.
     * @param pat The pattern to find anagrams of.
     * @return The number of times the anagram of pattern appears in text.
     */
    public static int countAnagramOccurrences(String txt, String pat) {
        if (txt == null || pat == null || txt.length() < pat.length()) {
            return 0;
        }

        Map<Character, Integer> patternMap = new HashMap<>(); // Frequency of characters in pat
        for (char c : pat.toCharArray()) {
            patternMap.put(c, patternMap.getOrDefault(c, 0) + 1);
        }

        int left = 0;
        int right = 0;
        int count = 0;
        int matched = 0; // Count of characters matched

        Map<Character, Integer> windowMap = new HashMap<>(); // Frequency of characters in the current window

        while (right < txt.length()) {
            char c = txt.charAt(right);
            windowMap.put(c, windowMap.getOrDefault(c, 0) + 1);

            if (patternMap.containsKey(c) && windowMap.get(c).intValue() == patternMap.get(c).intValue()) {
                matched++;
            }

            if (right - left + 1 == pat.length()) { // Window size equals pattern length
                if (matched == patternMap.size()) {
                    count++;
                }

                char leftChar = txt.charAt(left);
                windowMap.put(leftChar, windowMap.get(leftChar) - 1);
                if (patternMap.containsKey(leftChar) && windowMap.get(leftChar).intValue() < patternMap.get(leftChar).intValue()) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return count;
    }

    // =================================================================================================
    // Main Method - Test Cases
    // =================================================================================================

    public static void main(String[] args) {
        // Test Case 1: Fixed Size Sliding Window
        int[] arr1 = {1, 3, -2, 6, -1, 4, 1, 8, 2};
        int windowSize1 = 3;
        System.out.println("Maximum Sum Subarray (Fixed Size): " + maxSumSubarray(arr1, windowSize1)); // Expected Output: 15

        // Test Case 2: Minimum Window Substring
        String s2 = "ADOBECODEBANC";
        String t2 = "ABC";
        System.out.println("Minimum Window Substring: " + minWindowSubstring(s2, t2)); // Expected Output: "BANC"

        // Test Case 3: Longest Substring Without Repeating Characters
        String s3 = "abcabcbb";
        System.out.println("Longest Substring Without Repeating Characters: " + longestSubstringWithoutRepeatingCharacters(s3)); // Expected Output: 3

        // Test Case 4: Longest Substring with At Most K Distinct Characters
        String s4 = "eceba";
        int k4 = 2;
        System.out.println("Longest Substring with At Most K Distinct Characters: " + longestSubstringWithAtMostKDistinctCharacters(s4, k4)); // Expected Output: 3

        // Test Case 5: Count Occurrences of Anagrams
        String txt5 = "BACDGABCDAABCD";
        String pat5 = "ABCD";
        System.out.println("Count Occurrences of Anagrams: " + countAnagramOccurrences(txt5, pat5)); // Expected Output: 3

        // Additional test cases for edge scenarios
        System.out.println("Maximum Sum Subarray (Empty array): " + maxSumSubarray(new int[]{}, 2)); // Should return Integer.MIN_VALUE
        System.out.println("Maximum Sum Subarray (Invalid window size): " + maxSumSubarray(arr1, 0)); // Should return Integer.MIN_VALUE
        System.out.println("Minimum Window Substring (Empty s): " + minWindowSubstring("", t2)); //""
        System.out.println("Minimum Window Substring (Empty t): " + minWindowSubstring(s2, "")); //""
        System.out.println("Longest Substring Without Repeating Characters (Empty string): " + longestSubstringWithoutRepeatingCharacters("")); // 0
        System.out.println("Longest Substring with At Most K Distinct Characters (k=0): " + longestSubstringWithAtMostKDistinctCharacters(s4, 0)); //0
        System.out.println("Count Occurrences of Anagrams (Empty txt): " + countAnagramOccurrences("", pat5));  // 0
        System.out.println("Count Occurrences of Anagrams (Empty pat): " + countAnagramOccurrences(txt5, ""));  // 0
        System.out.println("Count Occurrences of Anagrams (pat longer than txt): " + countAnagramOccurrences("AB", "ABCD")); //0
    }
}


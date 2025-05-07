import java.util.*;
import java.lang.*;

class SlidingWindow {

    /**
     * Approach 1: Basic Sliding Window (for demonstration)
     * This approach demonstrates a simple sliding window technique where the window size is fixed.
     * It's not a "dynamic" window in the strictest sense, but it's a good starting point to understand the concept.
     *
     * Problem: Given an array and a window size 'k', find the maximum sum of any subarray of size 'k'.
     */
    public static int maxSubarraySum(int[] arr, int k) {
        if (arr == null || arr.length < k) {
            return -1; // Or throw an exception: throw new IllegalArgumentException("Invalid input");
        }

        int maxSum = 0;
        int windowSum = 0;

        // Calculate the sum of the first window
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        maxSum = windowSum;

        // Slide the window through the rest of the array
        for (int i = k; i < arr.length; i++) {
            windowSum = windowSum - arr[i - k] + arr[i]; // Subtract the element going out of the window and add the new element
            maxSum = Math.max(maxSum, windowSum);       // Update maxSum if needed
        }

        return maxSum;
    }

    /**
     * Approach 2: Dynamic Sliding Window - Minimum Window Substring
     * Problem:
     * Given a string 's' and a string 't', find the minimum window in 's' which will contain all the characters in 't'.
     *
     * Example:
     * s = "ADOBECODEBANC", t = "ABC"
     * Result: "BANC"
     */
    public static String minWindowSubstring(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }

        Map<Character, Integer> targetMap = new HashMap<>(); // Store the frequency of characters in 't'
        for (char c : t.toCharArray()) {
            targetMap.put(c, targetMap.getOrDefault(c, 0) + 1);
        }

        int left = 0;
        int right = 0;
        int minLength = Integer.MAX_VALUE;
        int start = 0; // Start index of the minimum window
        int matched = 0; // Count of characters in 's' that match the characters in 't'
        Map<Character, Integer> windowMap = new HashMap<>(); // Store the frequency of characters in the current window

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
                left++; // Shrink the window
            }
            right++; // Expand the window
        }
        return minLength == Integer.MAX_VALUE ? "" : s.substring(start, start + minLength);
    }

    /**
     * Approach 3: Dynamic Sliding Window - Longest Substring Without Repeating Characters
     * Problem:
     * Given a string, find the length of the longest substring without repeating characters.
     *
     * Example:
     * s = "abcabcbb"
     * Result: 3 ("abc")
     */
    public static int longestSubstringWithoutRepeatingCharacters(String s) {
        if (s == null || s.length() == 0) {
            return 0;
        }

        int left = 0;
        int right = 0;
        int maxLength = 0;
        Set<Character> charSet = new HashSet<>(); // Use a set to track characters in the current window

        while (right < s.length()) {
            char c = s.charAt(right);
            if (!charSet.contains(c)) {
                charSet.add(c);
                maxLength = Math.max(maxLength, right - left + 1);
                right++; // Expand the window
            } else {
                // Shrink the window until the repeating character is removed
                while (left < right && s.charAt(left) != c) {
                    charSet.remove(s.charAt(left));
                    left++;
                }
                left++; // Move past the repeating character
                right++;
            }
        }
        return maxLength;
    }

    /**
     * Approach 4: Dynamic Sliding Window -  Maximum Sum Subarray of Size K (Handles Negative Numbers)
     * Problem: Find the maximum sum of a subarray of size 'k' in an array that may contain negative numbers.
     *
     * This approach is similar to approach 1, but it explicitly handles negative numbers and edge cases.
     */
    public static int maxSumSubarrayK(int[] arr, int k) {
        if (arr == null || arr.length < k || k <= 0) {
            return Integer.MIN_VALUE; // Handle invalid input
        }

        int maxSum = Integer.MIN_VALUE; // Initialize maxSum to the smallest possible integer
        int windowSum = 0;

        // Calculate the sum of the first window
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        maxSum = windowSum; // Initialize maxSum with the first window's sum

        // Slide the window through the rest of the array
        for (int i = k; i < arr.length; i++) {
            windowSum = windowSum - arr[i - k] + arr[i];
            maxSum = Math.max(maxSum, windowSum); // 핵심: Use Math.max to handle negative sums correctly
        }

        return maxSum;
    }

    /**
     * Approach 5: Dynamic Sliding Window - Longest Substring with At Most K Distinct Characters
     * Problem:
     * Given a string 's' and an integer 'k', find the length of the longest substring of 's' with at most 'k' distinct characters.
     *
     * Example:
     * s = "eceba", k = 2
     * Result: 3 ("ece" or "eba")
     */
    public static int longestSubstringWithAtMostKDistinctCharacters(String s, int k) {
        if (s == null || s.length() == 0 || k <= 0) {
            return 0;
        }

        int left = 0;
        int right = 0;
        int maxLength = 0;
        Map<Character, Integer> charFrequencyMap = new HashMap<>(); // Store the frequency of characters in the current window

        while (right < s.length()) {
            char c = s.charAt(right);
            charFrequencyMap.put(c, charFrequencyMap.getOrDefault(c, 0) + 1);

            // If the number of distinct characters exceeds 'k', shrink the window
            while (charFrequencyMap.size() > k) {
                char leftChar = s.charAt(left);
                charFrequencyMap.put(leftChar, charFrequencyMap.get(leftChar) - 1);
                if (charFrequencyMap.get(leftChar) == 0) {
                    charFrequencyMap.remove(leftChar);
                }
                left++; // Shrink the window
            }

            maxLength = Math.max(maxLength, right - left + 1); // Update max length
            right++; // Expand the window
        }
        return maxLength;
    }

    public static void main(String[] args) {
        // Example usage for each approach
        int[] arr = {1, 4, 2, 10, 23, 3, 1, 0, 20};
        int k = 4;
        System.out.println("Approach 1 - Max Subarray Sum (k=" + k + "): " + maxSubarraySum(arr, k)); // Output: 39

        String s1 = "ADOBECODEBANC";
        String t = "ABC";
        System.out.println("Approach 2 - Minimum Window Substring: " + minWindowSubstring(s1, t)); // Output: BANC

        String s2 = "abcabcbb";
        System.out.println("Approach 3 - Longest Substring Without Repeating Characters: " + longestSubstringWithoutRepeatingCharacters(s2)); // Output: 3

        int[] arr2 = { -1, -2, -3, -4, -5, -6 };
        int k2 = 2;
        System.out.println("Approach 4 - Max Sum Subarray of Size K (Negative Numbers, k=" + k2 + "): " + maxSumSubarrayK(arr2, k2)); // Output: -3

        String s3 = "eceba";
        int k3 = 2;
        System.out.println("Approach 5 - Longest Substring with At Most K Distinct Characters (k=" + k3 + "): " + longestSubstringWithAtMostKDistinctCharacters(s3, k3)); // Output: 3
        String s4 = "aa";
        int k4 = 1;
        System.out.println("Approach 5 - Longest Substring with At Most K Distinct Characters (k=" + k4 + ", s=" + s4 + "): " + longestSubstringWithAtMostKDistinctCharacters(s4, k4));
    }
}


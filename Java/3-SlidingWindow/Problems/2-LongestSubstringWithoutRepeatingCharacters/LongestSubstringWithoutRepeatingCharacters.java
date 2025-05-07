import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class Solution {

    /**
     * Approach 1: Brute Force
     * -   Time Complexity: O(n^3) - Three nested loops.
     * -   Space Complexity: O(min(m, n)) -  Space for the character set. 'm' is the size of the character set.
     * -   Description:
     * Iterates through all possible substrings and checks if each substring has repeating characters.
     * It uses a helper function `hasRepeatingCharacters` to determine if a substring is unique.
     */
    public int lengthOfLongestSubstring_BruteForce(String s) {
        int n = s.length();
        int maxLength = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!hasRepeatingCharacters(s, i, j)) {
                    maxLength = Math.max(maxLength, j - i);
                }
            }
        }
        return maxLength;
    }

    private boolean hasRepeatingCharacters(String s, int start, int end) {
        Set<Character> charSet = new HashSet<>();
        for (int i = start; i < end; i++) {
            char c = s.charAt(i);
            if (charSet.contains(c)) {
                return true;
            }
            charSet.add(c);
        }
        return false;
    }

    /**
     * Approach 2: Sliding Window with Set
     * -   Time Complexity: O(n) - Single pass through the string.
     * -   Space Complexity: O(min(m, n)) - Space for the character set.
     * -   Description:
     * Uses a sliding window approach with a set to keep track of characters in the current window.
     * If a repeating character is found, the window's start is moved to the right until the repeating character is removed.
     */
    public int lengthOfLongestSubstring_SlidingWindowSet(String s) {
        int n = s.length();
        int maxLength = 0;
        int start = 0;
        int end = 0;
        Set<Character> charSet = new HashSet<>();

        while (end < n) {
            char c = s.charAt(end);
            if (!charSet.contains(c)) {
                charSet.add(c);
                end++;
                maxLength = Math.max(maxLength, end - start);
            } else {
                charSet.remove(s.charAt(start));
                start++;
            }
        }
        return maxLength;
    }

    /**
     * Approach 3: Sliding Window with Map
     * -   Time Complexity: O(n) - Single pass through the string.
     * -   Space Complexity: O(min(m, n)) - Space for the character map.
     * -   Description:
     * Uses a sliding window approach with a map to store the last seen index of each character.
     * When a repeating character is found, the start of the window is moved to the position after the last occurrence of that character.
     */
    public int lengthOfLongestSubstring_SlidingWindowMap(String s) {
        int n = s.length();
        int maxLength = 0;
        int start = 0;
        Map<Character, Integer> charMap = new HashMap<>();

        for (int end = 0; end < n; end++) {
            char c = s.charAt(end);
            if (charMap.containsKey(c)) {
                start = Math.max(start, charMap.get(c) + 1); // Move start to the right of the previous occurrence
            }
            charMap.put(c, end);
            maxLength = Math.max(maxLength, end - start + 1);
        }
        return maxLength;
    }

    /**
     * Approach 4: Optimized Sliding Window with Array (for ASCII characters)
     * -   Time Complexity: O(n) - Single pass through the string.
     * -   Space Complexity: O(1) -  Constant space for the character array (assuming ASCII characters).
     * -   Description:
     * Optimizes the sliding window approach for ASCII characters by using an integer array as a lookup table.
     * The array stores the last seen index of each character.  This is more efficient than a HashMap for a limited character set.
     */
    public int lengthOfLongestSubstring_OptimizedSlidingWindow(String s) {
        int n = s.length();
        int maxLength = 0;
        int start = 0;
        int[] charIndex = new int[128]; // Assuming ASCII characters

        for (int i = 0; i < 128; i++) {
            charIndex[i] = -1;  // Initialize all entries to -1
        }

        for (int end = 0; end < n; end++) {
            char c = s.charAt(end);
            start = Math.max(start, charIndex[c] + 1); // Move start
            charIndex[c] = end;
            maxLength = Math.max(maxLength, end - start + 1);
        }
        return maxLength;
    }

    /**
     * Approach 5: Sliding Window with Previous Array
     * - Time Complexity: O(n)
     * - Space Complexity: O(min(m, n))
     * - Description:
     * Uses a sliding window, similar to Approach 3, but with a slightly different way of tracking
     * the last seen position of each character.  It iterates through the string, updating the 'start'
     * of the window based on the 'previous' array, and updating the 'previous' array itself.
     */
    public int lengthOfLongestSubstring_SlidingWindowPrevious(String s) {
        int n = s.length();
        int maxLength = 0;
        int start = 0;
        int[] previous = new int[256]; // Assuming ASCII characters

        for (int i = 0; i < 256; i++) {
            previous[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            char currentChar = s.charAt(i);
            if (previous[currentChar] != -1) {
                start = Math.max(start, previous[currentChar] + 1);
            }
            previous[currentChar] = i;
            maxLength = Math.max(maxLength, i - start + 1);
        }
        return maxLength;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        String s = "abcabcbb";
        System.out.println("Input: " + s);

        System.out.println("Brute Force: " + solution.lengthOfLongestSubstring_BruteForce(s)); // 3
        System.out.println("Sliding Window with Set: " + solution.lengthOfLongestSubstring_SlidingWindowSet(s)); // 3
        System.out.println("Sliding Window with Map: " + solution.lengthOfLongestSubstring_SlidingWindowMap(s)); // 3
        System.out.println("Optimized Sliding Window: " + solution.lengthOfLongestSubstring_OptimizedSlidingWindow(s)); // 3
        System.out.println("Sliding Window with Previous Array: " + solution.lengthOfLongestSubstring_SlidingWindowPrevious(s)); //3

        s = "bbbbb";
        System.out.println("\nInput: " + s);
        System.out.println("Brute Force: " + solution.lengthOfLongestSubstring_BruteForce(s)); // 1
        System.out.println("Sliding Window with Set: " + solution.lengthOfLongestSubstring_SlidingWindowSet(s)); // 1
        System.out.println("Sliding Window with Map: " + solution.lengthOfLongestSubstring_SlidingWindowMap(s)); // 1
        System.out.println("Optimized Sliding Window: " + solution.lengthOfLongestSubstring_OptimizedSlidingWindow(s)); // 1
        System.out.println("Sliding Window with Previous Array: " + solution.lengthOfLongestSubstring_SlidingWindowPrevious(s));

        s = "pwwkew";
        System.out.println("\nInput: " + s);
        System.out.println("Brute Force: " + solution.lengthOfLongestSubstring_BruteForce(s)); // 3
        System.out.println("Sliding Window with Set: " + solution.lengthOfLongestSubstring_SlidingWindowSet(s)); // 3
        System.out.println("Sliding Window with Map: " + solution.lengthOfLongestSubstring_SlidingWindowMap(s)); // 3
        System.out.println("Optimized Sliding Window: " + solution.lengthOfLongestSubstring_OptimizedSlidingWindow(s)); // 3
        System.out.println("Sliding Window with Previous Array: " + solution.lengthOfLongestSubstring_SlidingWindowPrevious(s));
    }
}


import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class Solution {

    /**
     * Approach 1: Brute Force
     *
     * Description:
     * - Iterates through all possible substrings and checks each for repeating characters.
     * - Uses a helper function `hasRepeatingCharacters` to determine if a substring has repeating characters.
     * - Keeps track of the longest substring found so far.
     *
     * Time Complexity: O(n^3) -  Nested loops for substring generation (O(n^2)), and O(n) for checking repeating characters.
     * Space Complexity: O(n) -  In the worst case, the substring can be of length n.
     */
    public int lengthOfLongestSubstring_BruteForce(String s) {
        int n = s.length();
        int maxLength = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                String sub = s.substring(i, j);
                if (!hasRepeatingCharacters(sub)) {
                    maxLength = Math.max(maxLength, sub.length());
                }
            }
        }
        return maxLength;
    }

    private boolean hasRepeatingCharacters(String s) {
        Set<Character> charSet = new HashSet<>();
        for (char c : s.toCharArray()) {
            if (charSet.contains(c)) {
                return true;
            }
            charSet.add(c);
        }
        return false;
    }

    /**
     * Approach 2: Sliding Window with HashSet
     *
     * Description:
     * - Uses a sliding window approach with a HashSet to keep track of characters in the current window.
     * - If a repeating character is found, the left boundary of the window is moved to the right
     * until the repeating character is removed.
     * - The maximum window size (without repeating characters) is tracked.
     *
     * Time Complexity: O(n) - Each character is visited at most twice (once by the right pointer,
     * and possibly once by the left pointer).
     * Space Complexity: O(min(m, n)) -  The space required is determined by the size of the set,
     * which is limited by the number of unique characters (m) in the string
     * or the length of the string (n), whichever is smaller.
     */
    public int lengthOfLongestSubstring_SlidingWindowSet(String s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        Set<Character> charSet = new HashSet<>();

        for (int right = 0; right < n; right++) {
            char currentChar = s.charAt(right);
            while (charSet.contains(currentChar)) {
                charSet.remove(s.charAt(left));
                left++;
            }
            charSet.add(currentChar);
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }

    /**
     * Approach 3: Sliding Window with HashMap
     *
     * Description:
     * - Similar to the sliding window with HashSet, but uses a HashMap to store the most recent index of each character.
     * - When a repeating character is found, the left pointer can jump directly to the position after the previous occurrence
     * of the repeating character.
     * - This avoids unnecessary iterations.
     *
     * Time Complexity: O(n) - Each character is visited at most once.
     * Space Complexity: O(min(m, n)) -  The space required is determined by the size of the map,
     * which is limited by the number of unique characters (m) in the string
     * or the length of the string (n), whichever is smaller.
     */
    public int lengthOfLongestSubstring_SlidingWindowMap(String s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        Map<Character, Integer> charMap = new HashMap<>();

        for (int right = 0; right < n; right++) {
            char currentChar = s.charAt(right);
            if (charMap.containsKey(currentChar)) {
                left = Math.max(left, charMap.get(currentChar) + 1);
            }
            charMap.put(currentChar, right);
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }

    /**
     * Approach 4: Optimized Sliding Window with Array (for ASCII characters)
     *
     * Description:
     * - Optimized for ASCII characters (0-255).  Uses an integer array as a lookup table
     * to store the last seen index of each character.
     * - This is faster than using a HashMap for a limited character set.
     * - The rest of the logic is similar to the sliding window with HashMap.
     *
     * Time Complexity: O(n) -  Each character is visited at most once.
     * Space Complexity: O(1) -  The space required is constant (256 for ASCII characters).
     */
    public int lengthOfLongestSubstring_Optimized(String s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        int[] charIndex = new int[256]; // Assuming ASCII characters

        // Initialize the array to -1, indicating no previous occurrence
        for (int i = 0; i < 256; i++) {
            charIndex[i] = -1;
        }

        for (int right = 0; right < n; right++) {
            char currentChar = s.charAt(right);
            left = Math.max(left, charIndex[currentChar] + 1);
            charIndex[currentChar] = right;
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }

    /**
     * Approach 5:  Sliding Window with Explicit Left Boundary Tracking
     *
     * Description:
     * - This approach explicitly tracks the left boundary of the sliding window.
     * - It iterates through the string, and for each character, it checks if the character is already in the current window.
     * - If the character is found in the window, it updates the left boundary to be one position after the previous occurrence
     * of that character.
     * - It uses a HashMap to store the last seen position of each character.
     *
     * Time Complexity: O(n) - Each character is processed at most once.
     * Space Complexity: O(min(m, n)) -  The space required is determined by the size of the map,
     * which is limited by the number of unique characters (m) in the string
     * or the length of the string (n), whichever is smaller.
     */
    public int lengthOfLongestSubstring_ExplicitLeft(String s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        Map<Character, Integer> seenChars = new HashMap<>();

        for (int i = 0; i < n; i++) {
            char currentChar = s.charAt(i);
            if (seenChars.containsKey(currentChar)) {
                left = Math.max(left, seenChars.get(currentChar) + 1);
            }
            seenChars.put(currentChar, i);
            maxLength = Math.max(maxLength, i - left + 1);
        }
        return maxLength;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        String testString = "abcabcbb"; // Example string
        int result;

        // Brute Force
        result = solution.lengthOfLongestSubstring_BruteForce(testString);
        System.out.println("Brute Force: Longest substring length of \"" + testString + "\" is: " + result); // Output: 3

        // Sliding Window with HashSet
        result = solution.lengthOfLongestSubstring_SlidingWindowSet(testString);
        System.out.println("Sliding Window (Set): Longest substring length of \"" + testString + "\" is: " + result); // Output: 3

        // Sliding Window with HashMap
        result = solution.lengthOfLongestSubstring_SlidingWindowMap(testString);
        System.out.println("Sliding Window (Map): Longest substring length of \"" + testString + "\" is: " + result); // Output: 3

        // Optimized Sliding Window
        result = solution.lengthOfLongestSubstring_Optimized(testString);
        System.out.println("Optimized Sliding Window: Longest substring length of \"" + testString + "\" is: " + result); // Output: 3

        // Sliding Window with Explicit Left
        result = solution.lengthOfLongestSubstring_ExplicitLeft(testString);
        System.out.println("Sliding Window (Explicit Left): Longest substring length of \"" + testString + "\" is: " + result); // Output: 3

        String testString2 = "bbbbb";
        // Brute Force
        result = solution.lengthOfLongestSubstring_BruteForce(testString2);
        System.out.println("Brute Force: Longest substring length of \"" + testString2 + "\" is: " + result);

        // Sliding Window with HashSet
        result = solution.lengthOfLongestSubstring_SlidingWindowSet(testString2);
        System.out.println("Sliding Window (Set): Longest substring length of \"" + testString2 + "\" is: " + result);

        // Sliding Window with HashMap
        result = solution.lengthOfLongestSubstring_SlidingWindowMap(testString2);
        System.out.println("Sliding Window (Map): Longest substring length of \"" + testString2 + "\" is: " + result);

        // Optimized Sliding Window
        result = solution.lengthOfLongestSubstring_Optimized(testString2);
        System.out.println("Optimized Sliding Window: Longest substring length of \"" + testString2 + "\" is: " + result);

        // Sliding Window with Explicit Left
        result = solution.lengthOfLongestSubstring_ExplicitLeft(testString2);
        System.out.println("Sliding Window (Explicit Left): Longest substring length of \"" + testString2 + "\" is: " + result);

        String testString3 = "pwwkew";
        // Brute Force
        result = solution.lengthOfLongestSubstring_BruteForce(testString3);
        System.out.println("Brute Force: Longest substring length of \"" + testString3 + "\" is: " + result);

        // Sliding Window with HashSet
        result = solution.lengthOfLongestSubstring_SlidingWindowSet(testString3);
        System.out.println("Sliding Window (Set): Longest substring length of \"" + testString3 + "\" is: " + result);

        // Sliding Window with HashMap
        result = solution.lengthOfLongestSubstring_SlidingWindowMap(testString3);
        System.out.println("Sliding Window (Map): Longest substring length of \"" + testString3 + "\" is: " + result);

        // Optimized Sliding Window
        result = solution.lengthOfLongestSubstring_Optimized(testString3);
        System.out.println("Optimized Sliding Window: Longest substring length of \"" + testString3 + "\" is: " + result);

        // Sliding Window with Explicit Left
        result = solution.lengthOfLongestSubstring_ExplicitLeft(testString3);
        System.out.println("Sliding Window (Explicit Left): Longest substring length of \"" + testString3 + "\" is: " + result);
    }
}


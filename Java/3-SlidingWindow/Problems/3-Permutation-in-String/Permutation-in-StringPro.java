import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class PermutationInString {

    /**
     * **Approach 1: Brute Force**
     *
     * * Description:* Generate all permutations of `s1` and check if any of them are a substring of `s2`.
     * * Time Complexity:* O(n! * m), where n is the length of `s1` and m is the length of `s2`.  This is because generating all permutations of s1 is n! and then we check if each permutation is a substring of s2, which takes O(m) time.
     * * Space Complexity:* O(n), for storing the current permutation.
     * * Real-World Considerations:* This approach is extremely inefficient and not suitable for real-world use with non-trivial input sizes.  It's mainly for academic comparison.  Avoid this in production code.
     *
     * @param s1 The string representing the permutation.
     * @param s2 The string to search within.
     * @return True if `s2` contains a permutation of `s1`, false otherwise.
     */
    public boolean checkInclusionBruteForce(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        // Generate all permutations of s1
        return permuteAndCheck(s1, s2, 0);
    }

    private boolean permuteAndCheck(String s1, String s2, int l) {
        if (l == s1.length()) {
            if (s2.contains(s1)) { //The contains method internally uses string matching algorithm.
                return true;
            }
            return false;
        }
        for (int i = l; i < s1.length(); i++) {
            s1 = swap(s1, l, i);
            if(permuteAndCheck(s1, s2, l + 1)){
                return true; //Early return optimization.
            }
            s1 = swap(s1, l, i); // Backtrack
        }
        return false;
    }

    private String swap(String s, int i, int j) {
        char[] chars = s.toCharArray();
        char temp = chars[i];
        chars[i] = chars[j];
        chars[j] = temp;
        return new String(chars);
    }

    /**
     * **Approach 2: Sorting**
     *
     * * Description:* Sort `s1` and then iterate through all substrings of `s2` of the same length as `s1`, sorting each substring and comparing it to the sorted `s1`.
     * * Time Complexity:* O(n log n + (m - n) * n log n), where n is the length of `s1` and m is the length of `s2`.  Sorting s1 takes n log n.  There are (m-n+1) substrings in s2, and sorting each takes n log n.
     * * Space Complexity:* O(n), for the sorted arrays.
     * * Real-World Considerations:* Still not very efficient due to repeated sorting.  Better than brute force, but not ideal for large inputs.
     *
     * @param s1 The string representing the permutation.
     * @param s2 The string to search within.
     * @return True if `s2` contains a permutation of `s1`, false otherwise.
     */
    public boolean checkInclusionSorting(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        char[] sortedS1 = s1.toCharArray();
        Arrays.sort(sortedS1);
        String sortedS1String = new String(sortedS1);

        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            String sub = s2.substring(i, i + s1.length());
            char[] sortedSub = sub.toCharArray();
            Arrays.sort(sortedSub);
            String sortedSubString = new String(sortedSub);
            if (sortedS1String.equals(sortedSubString)) {
                return true;
            }
        }
        return false;
    }

    /**
     * **Approach 3: Character Counting (Array)**
     *
     * * Description:* Use two arrays of size 26 to store the character counts of `s1` and the current window in `s2`.  Slide the window and compare the arrays.
     * * Time Complexity:* O(n + (m - n) * k), where n is the length of `s1`, m is the length of `s2`, and k is the size of the character set (26 for lowercase English letters).  O(n) to build the initial s1 frequency and O(m-n) to slide the window.  The comparison of the two arrays is O(k).
     * * Space Complexity:* O(k), for the two count arrays.
     * * Real-World Considerations:* A significant improvement.  This is a very common and efficient approach for this type of problem.  It's suitable for real-world use, especially when the character set is limited.
     *
     * @param s1 The string representing the permutation.
     * @param s2 The string to search within.
     * @return True if `s2` contains a permutation of `s1`, false otherwise.
     */
    public boolean checkInclusionCharacterCountArray(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        int[] s1Count = new int[26];
        int[] s2Count = new int[26];

        for (char c : s1.toCharArray()) {
            s1Count[c - 'a']++;
        }

        for (int i = 0; i < s2.length(); i++) {
            s2Count[s2.charAt(i) - 'a']++;
            if (i >= s1.length()) {
                s2Count[s2.charAt(i - s1.length()) - 'a']--;
            }
            if (i >= s1.length() - 1) {
                if (Arrays.equals(s1Count, s2Count)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * **Approach 4: Character Counting (HashMap)**
     *
     * * Description:* Use HashMaps to store the character counts of `s1` and the current window in `s2`.  Slide the window and compare the HashMaps.
     * * Time Complexity:* O(n + (m - n) * k), where n is the length of `s1`, m is the length of `s2`, and k is the number of unique characters in `s1`.  Similar to the array approach, but the comparison in the worst case can be O(k), where k is the number of unique characters.
     * * Space Complexity:* O(k), for the HashMaps.
     * * Real-World Considerations:* This is a good approach, especially when the character set is large or unknown, as HashMaps can handle any character set.  Slightly less efficient than the array approach for small character sets but more versatile.
     *
     * @param s1 The string representing the permutation.
     * @param s2 The string to search within.
     * @return True if `s2` contains a permutation of `s1`, false otherwise.
     */
    public boolean checkInclusionCharacterCountHashMap(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        Map<Character, Integer> s1Count = new HashMap<>();
        Map<Character, Integer> s2Count = new HashMap<>();

        for (char c : s1.toCharArray()) {
            s1Count.put(c, s1Count.getOrDefault(c, 0) + 1);
        }

        for (int i = 0; i < s2.length(); i++) {
            char c = s2.charAt(i);
            s2Count.put(c, s2Count.getOrDefault(c, 0) + 1);
            if (i >= s1.length()) {
                char removeChar = s2.charAt(i - s1.length());
                s2Count.put(removeChar, s2Count.get(removeChar) - 1);
                if (s2Count.get(removeChar) == 0) {
                    s2Count.remove(removeChar);
                }
            }
            if (i >= s1.length() - 1) {
                if (s1Count.equals(s2Count)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * **Approach 5: Optimized Character Counting (Single Array with Sliding Window)**
     *
     * * Description:* Use a single array to store the character counts of `s1`.  Maintain a sliding window in `s2` and adjust the counts.  Use a `matches` variable to track how many characters have the required count.
     * * Time Complexity:* O(n + m), where n is the length of `s1` and m is the length of `s2`.  This is the most efficient approach.
     * * Space Complexity:* O(k), for the count array (where k is the size of the character set).
     * * Real-World Considerations:* This is the most optimized and recommended approach for real-world applications.  It's efficient and easy to understand.
     *
     * @param s1 The string representing the permutation.
     * @param s2 The string to search within.
     * @return True if `s2` contains a permutation of `s1`, false otherwise.
     */
    public boolean checkInclusionOptimized(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        int[] s1Count = new int[26];
        for (char c : s1.toCharArray()) {
            s1Count[c - 'a']++;
        }

        int[] s2Count = new int[26];
        int matches = 0;
        for (int i = 0; i < s2.length(); i++) {
            char c = s2.charAt(i);
            s2Count[c - 'a']++;

            if (s2Count[c - 'a'] == s1Count[c - 'a']) {
                matches++;
            }

            if (i >= s1.length()) {
                char removeChar = s2.charAt(i - s1.length());
                s2Count[removeChar - 'a']--;
                if (s2Count[removeChar - 'a'] < s1Count[removeChar - 'a']) {
                    matches--;
                }
            }

            if (matches == 26) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        PermutationInString solution = new PermutationInString();

        // Test cases
        String s1 = "ab";
        String s2 = "eidbaooo";
        System.out.println("Test Case 1: s1 = \"ab\", s2 = \"eidbaooo\"");
        System.out.println("Brute Force: " + solution.checkInclusionBruteForce(s1, s2)); // false
        System.out.println("Sorting: " + solution.checkInclusionSorting(s1, s2));       // true
        System.out.println("Character Count (Array): " + solution.checkInclusionCharacterCountArray(s1, s2)); // true
        System.out.println("Character Count (HashMap): " + solution.checkInclusionCharacterCountHashMap(s1, s2)); // true
        System.out.println("Optimized: " + solution.checkInclusionOptimized(s1, s2));       // true

        s1 = "ab";
        s2 = "eidboaoo";
        System.out.println("\nTest Case 2: s1 = \"ab\", s2 = \"eidboaoo\"");
        System.out.println("Brute Force: " + solution.checkInclusionBruteForce(s1, s2)); // false
        System.out.println("Sorting: " + solution.checkInclusionSorting(s1, s2));       // false
        System.out.println("Character Count (Array): " + solution.checkInclusionCharacterCountArray(s1, s2)); // false
        System.out.println("Character Count (HashMap): " + solution.checkInclusionCharacterCountHashMap(s1, s2)); // false
        System.out.println("Optimized: " + solution.checkInclusionOptimized(s1, s2));       // false

        s1 = "hello";
        s2 = "ooolleoooleh";
        System.out.println("\nTest Case 3: s1 = \"hello\", s2 = \"ooolleoooleh\"");
        System.out.println("Brute Force: " + solution.checkInclusionBruteForce(s1, s2));
        System.out.println("Sorting: " + solution.checkInclusionSorting(s1, s2));
        System.out.println("Character Count (Array): " + solution.checkInclusionCharacterCountArray(s1, s2));
        System.out.println("Character Count (HashMap): " + solution.checkInclusionCharacterCountHashMap(s1, s2));
        System.out.println("Optimized: " + solution.checkInclusionOptimized(s1, s2));

        s1 = "abc";
        s2 = "ccccbbaaa";
        System.out.println("\nTest Case 4: s1 = \"abc\", s2 = \"ccccbbaaa\"");
        System.out.println("Brute Force: " + solution.checkInclusionBruteForce(s1, s2));
        System.out.println("Sorting: " + solution.checkInclusionSorting(s1, s2));
        System.out.println("Character Count (Array): " + solution.checkInclusionCharacterCountArray(s1, s2));
        System.out.println("Character Count (HashMap): " + solution.checkInclusionCharacterCountHashMap(s1, s2));
        System.out.println("Optimized: " + solution.checkInclusionOptimized(s1, s2));
    }
}


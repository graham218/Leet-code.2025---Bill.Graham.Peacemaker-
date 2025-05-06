import java.util.Locale;

public class ValidPalindrome {

    /**
     * **Approach 1: Two Pointers (Optimized)**
     *
     * * **Core Idea:** This is the most efficient approach.  It uses two pointers, one starting at the beginning of the string and the other at the end.  It iterates through the string, comparing characters at these pointers, skipping non-alphanumeric characters.
     * * **Real-World Use Case:** This is the preferred method in most real-world applications where performance is critical, such as validating user input in real-time (e.g., in a registration form) or in performance-sensitive backend services.
     * * **Time Complexity:** O(n), where n is the length of the string.
     * **Space Complexity:** O(1), constant space.
     *
     * @param s The input string.
     * @return `true` if the string is a palindrome, `false` otherwise.
     */
    public boolean isPalindromeTwoPointers(String s) {
        if (s == null) {
            return true; // Or throw an IllegalArgumentException, depending on requirements
        }
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Skip non-alphanumeric characters from the left
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }
            // Skip non-alphanumeric characters from the right
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }
            // Compare characters, ignoring case
            if (left < right && Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                return false;
            }
            // Move pointers
            left++;
            right--;
        }
        return true;
    }

    /**
     * **Approach 2: Using StringBuilder (Less Efficient)**
     *
     * * **Core Idea:** This approach filters the input string to keep only alphanumeric characters, reverses the filtered string, and then compares the filtered string with its reversed version.
     * * **Real-World Use Case:** While less efficient, this approach is sometimes used when the original string needs to be preserved and a modified version is needed for comparison.  For example, in some data processing pipelines where the original input string is part of an audit trail.  However, the two pointers approach is generally preferred.
     * * **Time Complexity:** O(n), where n is the length of the string (due to filtering and reversing).
     * **Space Complexity:** O(n), for the filtered and reversed strings.
     *
     * @param s The input string.
     * @return `true` if the string is a palindrome, `false` otherwise.
     */
    public boolean isPalindromeStringBuilder(String s) {
        if (s == null) {
            return true;
        }

        StringBuilder filteredString = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                filteredString.append(Character.toLowerCase(c));
            }
        }

        StringBuilder reversedString = new StringBuilder(filteredString).reverse();
        return filteredString.toString().equals(reversedString.toString());
    }

    /**
     * **Approach 3: Using Regular Expressions (Potentially Inefficient for Large Strings)**
     *
     * * **Core Idea:** This approach uses a regular expression to remove all non-alphanumeric characters from the string and then compares the cleaned string with its reversed version.
     * * **Real-World Use Case:** Regular expressions can be concise, but they can be less efficient, especially for very long strings.  This approach might be used in situations where code conciseness is prioritized over raw performance, or where the input strings are relatively short and simple.  For example, in some scripting scenarios or quick data cleaning tasks.  However, be cautious about using this in performance-critical applications.
     * * **Time Complexity:** Depends on the regex engine.  In the worst case, the regex part could be O(n), and string reversal is O(n).
     * **Space Complexity:** O(n) for the cleaned string.
     *
     * @param s The input string.
     * @return `true` if the string is a palindrome, `false` otherwise.
     */
    public boolean isPalindromeRegex(String s) {
        if (s == null) {
            return true;
        }
        // Remove non-alphanumeric characters using regex
        String cleanedString = s.replaceAll("[^A-Za-z0-9]", "").toLowerCase();
        String reversedString = new StringBuilder(cleanedString).reverse().toString();
        return cleanedString.equals(reversedString);
    }

    /**
     * **Approach 4: Recursive Approach (Not Recommended for Performance)**
     *
     * * **Core Idea:** This approach uses recursion to check if the string is a palindrome.  It repeatedly compares the first and last characters and recursively checks the substring without those characters.
     * * **Real-World Use Case:** Recursion is generally not the most efficient way to solve this problem due to the overhead of function calls.  It can lead to stack overflow errors for very long strings.  This approach is mainly for educational purposes or for very short strings where performance is not a concern.  In production code, iterative solutions are almost always preferred for palindromes.
     * * **Time Complexity:** O(n), where n is the length of the string (in the best case, it can be less, but in the worst case, it's O(n)).
     * **Space Complexity:** O(n) due to the call stack in recursion.
     *
     * @param s The input string.
     * @return `true` if the string is a palindrome, `false` otherwise.
     */
    public boolean isPalindromeRecursive(String s) {
        if (s == null) {
            return true;
        }
        String cleanedString = s.replaceAll("[^A-Za-z0-9]", "").toLowerCase();
        return isPalindromeRecursiveHelper(cleanedString, 0, cleanedString.length() - 1);
    }

    private boolean isPalindromeRecursiveHelper(String s, int left, int right) {
        if (left >= right) {
            return true; // Base case: empty or single character string is a palindrome
        }
        if (s.charAt(left) != s.charAt(right)) {
            return false; // Characters don't match
        }
        // Recursive call with updated pointers
        return isPalindromeRecursiveHelper(s, left + 1, right - 1);
    }

    /**
     * **Approach 5: Using Character.codePointAt (Handles Unicode Correctly)**
     * * **Core Idea:** This approach is similar to the two-pointer approach but uses `Character.codePointAt` to handle Unicode characters correctly.  This is important because some Unicode characters are represented by more than one char in Java.
     * * **Real-World Use Case:** This is crucial for applications that need to support a wide range of languages and character sets, such as internationalized web applications, multilingual document processing, or any system that handles user input in various languages.  If you're dealing with potentially non-ASCII text, this approach is highly recommended.
     * * **Time Complexity:** O(n), where n is the length of the string.
     * **Space Complexity:** O(1), constant space.
     *
     * @param s The input string
     * @return `true` if the string is a palindrome, `false` otherwise
     */
    public boolean isPalindromeUnicode(String s) {
        if (s == null) {
            return true;
        }

        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Use codePointAt to handle Unicode correctly
            while (left < right && !isAlphanumeric(Character.codePointAt(s, left))) {
                left += Character.charCount(Character.codePointAt(s, left));
            }
            while (left < right && !isAlphanumeric(Character.codePointAt(s, right))) {
                right -= Character.charCount(Character.codePointAt(s, right));
            }

            if (left < right && Character.toLowerCase(Character.codePointAt(s, left)) != Character.toLowerCase(Character.codePointAt(s, right))) {
                return false;
            }

            left += Character.charCount(Character.codePointAt(s, left));
            right -= Character.charCount(Character.codePointAt(s, right));
        }
        return true;
    }

    private boolean isAlphanumeric(int codePoint) {
        return Character.isLetterOrDigit(codePoint);
    }

    public static void main(String[] args) {
        ValidPalindrome validator = new ValidPalindrome();

        // Test cases
        String test1 = "A man, a plan, a canal: Panama";
        String test2 = "race a car";
        String test3 = " ";
        String test4 = "Madam, I'm Adam!";
        String test5 = "Was it a car or a cat I saw?";
        String test6 = "121";
        String test7 = "hello";
        String test8 = ".,";
        String test9 = "Α man, a plan, a canal: Panama"; // Test with non-ASCII characters
        String test10 = "你好，世界！界世，好你！";  // Test with Chinese characters

        System.out.println("Test Cases for Valid Palindrome:");
        System.out.println("----------------------------------");

        // Testing Approach 1: Two Pointers (Optimized)
        System.out.println("Two Pointers (Optimized):");
        System.out.println("Test 1: " + validator.isPalindromeTwoPointers(test1)); // true
        System.out.println("Test 2: " + validator.isPalindromeTwoPointers(test2)); // false
        System.out.println("Test 3: " + validator.isPalindromeTwoPointers(test3)); // true
        System.out.println("Test 4: " + validator.isPalindromeTwoPointers(test4)); // true
        System.out.println("Test 5: " + validator.isPalindromeTwoPointers(test5)); // true
        System.out.println("Test 6: " + validator.isPalindromeTwoPointers(test6)); // true
        System.out.println("Test 7: " + validator.isPalindromeTwoPointers(test7)); // false
        System.out.println("Test 8: " + validator.isPalindromeTwoPointers(test8)); // true
        System.out.println("Test 9: " + validator.isPalindromeTwoPointers(test9)); // true
        System.out.println("Test 10: " + validator.isPalindromeTwoPointers(test10)); // true
        System.out.println();

        // Testing Approach 2: Using StringBuilder
        System.out.println("StringBuilder:");
        System.out.println("Test 1: " + validator.isPalindromeStringBuilder(test1)); // true
        System.out.println("Test 2: " + validator.isPalindromeStringBuilder(test2)); // false
        System.out.println("Test 3: " + validator.isPalindromeStringBuilder(test3)); // true
        System.out.println("Test 4: " + validator.isPalindromeStringBuilder(test4)); // true
        System.out.println("Test 5: " + validator.isPalindromeStringBuilder(test5)); // true
        System.out.println("Test 6: " + validator.isPalindromeStringBuilder(test6)); // true
        System.out.println("Test 7: " + validator.isPalindromeStringBuilder(test7)); // false
        System.out.println("Test 8: " + validator.isPalindromeStringBuilder(test8)); // true
        System.out.println("Test 9: " + validator.isPalindromeStringBuilder(test9)); // true
        System.out.println("Test 10: " + validator.isPalindromeStringBuilder(test10)); // true
        System.out.println();

        // Testing Approach 3: Using Regular Expressions
        System.out.println("Regular Expressions:");
        System.out.println("Test 1: " + validator.isPalindromeRegex(test1)); // true
        System.out.println("Test 2: " + validator.isPalindromeRegex(test2)); // false
        System.out.println("Test 3: " + validator.isPalindromeRegex(test3)); // true
        System.out.println("Test 4: " + validator.isPalindromeRegex(test4)); // true
        System.out.println("Test 5: " + validator.isPalindromeRegex(test5)); // true
        System.out.println("Test 6: " + validator.isPalindromeRegex(test6)); // true
        System.out.println("Test 7: " + validator.isPalindromeRegex(test7)); // false
        System.out.println("Test 8: " + validator.isPalindromeRegex(test8)); // true
        System.out.println("Test 9: " + validator.isPalindromeRegex(test9)); // true
        System.out.println("Test 10: " + validator.isPalindromeRegex(test10)); // true
        System.out.println();

        // Testing Approach 4: Recursive Approach
        System.out.println("Recursive Approach:");
        System.out.println("Test 1: " + validator.isPalindromeRecursive(test1)); // true
        System.out.println("Test 2: " + validator.isPalindromeRecursive(test2)); // false
        System.out.println("Test 3: " + validator.isPalindromeRecursive(test3)); // true
        System.out.println("Test 4: " + validator.isPalindromeRecursive(test4)); // true
        System.out.println("Test 5: " + validator.isPalindromeRecursive(test5)); // true
        System.out.println("Test 6: " + validator.isPalindromeRecursive(test6)); // true
        System.out.println("Test 7: " + validator.isPalindromeRecursive(test7)); // false
        System.out.println("Test 8: " + validator.isPalindromeRecursive(test8)); // true
        System.out.println("Test 9: " + validator.isPalindromeRecursive(test9)); // true
        System.out.println("Test 10: " + validator.isPalindromeRecursive(test10)); // true
        System.out.println();

        // Testing Approach 5: Using Character.codePointAt (Handles Unicode)
        System.out.println("Using Character.codePointAt (Handles Unicode):");
        System.out.println("Test 1: " + validator.isPalindromeUnicode(test1));
        System.out.println("Test 2: " + validator.isPalindromeUnicode(test2));
        System.out.println("Test 3: " + validator.isPalindromeUnicode(test3));
        System.out.println("Test 4: " + validator.isPalindromeUnicode(test4));
        System.out.println("Test 5: " + validator.isPalindromeUnicode(test5));
        System.out.println("Test 6: " + validator.isPalindromeUnicode(test6));
        System.out.println("Test 7: " + validator.isPalindromeUnicode(test7));
        System.out.println("Test 8: " + validator.isPalindromeUnicode(test8));
        System.out.println("Test 9: " + validator.isPalindromeUnicode(test9)); // true
        System.out.println("Test 10: " + validator.isPalindromeUnicode(test10)); // true
    }
}

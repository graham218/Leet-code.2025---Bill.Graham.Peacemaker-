/**
 * # Two Pointers: Valid Palindrome
 *
 * A palindrome is a word, phrase, number, or other sequence of characters which reads the same backward as forward.
 *
 * Given a string `s`, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * ## Problem Constraints
 *
 * -   `1 <= s.length <= 2 * 10^5`
 * -   `s` consists only of printable ASCII characters.
 *
 * ## Examples
 *
 * ### Example 1
 *
 * ```
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 * ```
 *
 * ### Example 2
 *
 * ```
 * Input: s = "race a car"
 * Output: false
 * Explanation: "raceacar" is not a palindrome.
 * ```
 *
 * ### Example 3
 *
 * ```
 * Input: s = " "
 * Output: true
 * Explanation: An empty string is considered a palindrome.
 * ```
 */

/**
 * ---
 * 1.  **Two Pointers (Optimized)**
 *
 * -   **Approach:**
 * -   Initialize two pointers, `left` at the beginning and `right` at the end of the string.
 * -   Iterate while `left < right`.
 * -   In each iteration, move `left` to the right until it points to an alphanumeric character.
 * -   Similarly, move `right` to the left until it points to an alphanumeric character.
 * -   Compare the characters at `left` and `right` (case-insensitive). If they are not equal, the string is not a palindrome.
 * -   If the characters are equal, move `left` to the right and `right` to the left.
 * -   If the loop finishes without finding any mismatched characters, the string is a palindrome.
 * -   **Real-World Project:**
 * -   Text editors or IDEs for checking if a user's input is a valid palindrome for specific features (e.g., variable names, special syntax).
 * -   **Complexity Analysis:**
 * -   Time Complexity: O(n), where n is the length of the string.
 * -   Space Complexity: O(1), constant extra space.
 * -   **Explanation:**
 * This approach efficiently skips non-alphanumeric characters, directly comparing only the relevant characters.  It's optimized for speed and uses minimal memory.
 */
function isPalindromeTwoPointers(s) { // Removed the type annotation ": string"
    let left = 0;
    let right = s.length - 1;

    while (left < right) {
        // Skip non-alphanumeric characters from the left
        while (left < right && !isAlphaNumeric(s[left])) {
            left++;
        }
        // Skip non-alphanumeric characters from the right
        while (left < right && !isAlphaNumeric(s[right])) {
            right--;
        }

        // Compare characters (case-insensitive)
        if (left < right && s[left].toLowerCase() !== s[right].toLowerCase()) {
            return false;
        }

        // Move pointers
        left++;
        right--;
    }

    return true;
}

/**
 * Helper function to check if a character is alphanumeric.
 */
function isAlphaNumeric(char) { // Removed the type annotation ": string"
    const code = char.charCodeAt(0);
    return (
        (code >= 48 && code <= 57) || // 0-9
        (code >= 65 && code <= 90) || // A-Z
        (code >= 97 && code <= 122)   // a-z
    );
}

/**
 * ---
 * 2.  **Two Pointers (Simplified)**
 * -   **Approach:**
 * -   Similar to the optimized two-pointer approach, but combines the character validation and comparison into a single, more concise loop.
 * -   It initializes two pointers, `left` and `right`, at the start and end of the string.
 * -   The loop continues as long as `left < right`.
 * -   Inside the loop, it checks if the characters at `left` and `right` are alphanumeric. If not, it moves the respective pointer and continues.
 * -   If both characters are alphanumeric, it compares them (case-insensitively). If they don't match, it returns `false`.
 * -   If they match, it moves both pointers towards the center.
 * -   If the loop finishes without finding mismatches, it returns `true`.
 * -   **Real-World Project:**
 * -   Used in data validation within web applications to ensure user-provided strings (e.g., usernames, IDs) adhere to palindrome rules, enhancing data integrity.
 * -   **Complexity Analysis:**
 * -   Time Complexity: O(n), where n is the length of the string.
 * -   Space Complexity: O(1), constant extra space.
 */
function isPalindromeTwoPointersSimple(s) { // Removed the type annotation ": string"
    let left = 0;
    let right = s.length - 1;

    while (left < right) {
        const leftChar = s[left];
        const rightChar = s[right];

        if (!isAlphaNumeric(leftChar)) {
            left++;
        } else if (!isAlphaNumeric(rightChar)) {
            right--;
        } else if (leftChar.toLowerCase() !== rightChar.toLowerCase()) {
            return false;
        } else {
            left++;
            right--;
        }
    }
    return true;
}

/**
 * ---
 * 3.  **Using Built-in Functions (Filter and Reverse)**
 * -   **Approach:**
 * -   Filter the input string to keep only alphanumeric characters.
 * -   Convert the filtered string to lowercase.
 * -   Reverse the filtered string.
* -  Compare the filtered string with its reversed version.
 * -   **Real-World Project:**
 * -   Used in natural language processing (NLP) tasks for text normalization before palindrome checks, ensuring that only relevant characters are considered.
 * -   **Complexity Analysis:**
 * -   Time Complexity: O(n), where n is the length of the string.  Filtering and reversing are linear operations.
 * -   Space Complexity: O(n), as a new string is created to store the filtered characters and the reversed string.
 */
function isPalindromeFilterReverse(s) { // Removed the type annotation ": string"
    const filteredChars = s.toLowerCase().split('').filter(isAlphaNumeric);
    const reversedChars = [...filteredChars].reverse(); //spread syntax to create new array.
    return filteredChars.join('') === reversedChars.join('');
}

/**
 * ---
 * 4.  **Using Regular Expression and Reverse**
 * -   **Approach:**
 * -   Use a regular expression to remove all non-alphanumeric characters from the string.
 * -   Convert the cleaned string to lowercase.
 * -   Reverse the cleaned string.
 * -   Compare the cleaned string with its reversed version.
 * -   **Real-World Project:**
 * -   Used in data cleaning processes to validate if user inputs (e.g., names, addresses) are palindromes after removing irrelevant symbols or formatting.
 * -   **Complexity Analysis:**
 * -   Time Complexity: O(n), where n is the length of the string.  Regular expression matching and reversing are linear.
 * -   Space Complexity: O(n), for the cleaned string and the reversed string.
 */
function isPalindromeRegExp(s) { // Removed the type annotation ": string"
    const cleanedString = s.replace(/[^a-zA-Z0-9]/g, '').toLowerCase();
    const reversedString = cleanedString.split('').reverse().join('');
    return cleanedString === reversedString;
}

/**
 * ---
 * 5.  **Recursive Approach**
 * -   **Approach:**
 * - Define a recursive function that takes the string and two pointers (left, right) as arguments.
 * - In each recursive call:
* - If left >= right, the substring is a palindrome (base case), return true
 * -  Move left and right inwards, skipping non-alphanumeric characters.
 * -  If the characters at left and right are different, return false.
 * -  Otherwise, recursively call the function with the updated left and right pointers.

 * -   **Real-World Project:**
 * -   While less common for simple palindrome checks, recursion can be adapted for more complex, nested data structures where palindrome-like properties need to be validated.
 * -   **Complexity Analysis:**
 * -   Time Complexity: O(n), where n is the length of the string.
 * -   Space Complexity: O(n) in the worst case, due to the call stack in recursion.
 */

function isPalindromeRecursive(s) { // Removed the type annotation ": string"
  function solve(str, left, right) { // Removed type annotations ": string", ": number", ": number"
    if (left >= right) {
      return true;
    }

    while (left < right && !isAlphaNumeric(str[left])) {
      left++;
    }
    while (left < right && !isAlphaNumeric(str[right])) {
      right--;
    }

    if (left < right && str[left].toLowerCase() !== str[right].toLowerCase()) {
      return false;
    }

    return solve(str, left + 1, right - 1);
  }
  return solve(s, 0, s.length - 1);
}

/**
 * 6. **Using Array.every()**
 * - **Approach:**
 * - Filter the string to keep only alphanumeric characters and convert it to lowercase.
 * - Use the `every()` method to check if each character in the filtered string is equal to its corresponding character from the end of the string.
 * - **Real-world project:**
 * - Useful in data validation scenarios where you need to check a property for all elements in a list, and that property is whether the element is a palindrome.
 * - **Complexity Analysis:**
 * - Time complexity: O(n), where n is the length of the string.
 * - Space complexity: O(n), to store the filtered string.
 */
function isPalindromeEvery(s) { // Removed the type annotation ": string"
    const cleanStr = s.toLowerCase().split('').filter(isAlphaNumeric);
    return cleanStr.every((char, i) => char === cleanStr[cleanStr.length - 1 - i]);
}

// ---
// ## Test Cases
//
// The following test cases cover various scenarios, including empty strings, strings with non-alphanumeric characters, and palindromes/non-palindromes of different lengths.
//
function runTestCases() {
    const testCases = [
        { input: "A man, a plan, a canal: Panama", expected: true },
        { input: "race a car", expected: false },
        { input: " ", expected: true },
        { input: "Madam, I'm Adam!", expected: true },
        { input: "121", expected: true },
        { input: "123", expected: false },
        { input: "0P", expected: false},
        { input: "a.", expected: true},
        { input: "", expected: true }, // Empty string
        { input: "ab", expected: false },
        { input: "aba", expected: true },
        { input: "abba", expected: true },
        { input: "Aba", expected: true },  //Mixed case
    ];

    const implementations = [
        { name: "Two Pointers (Optimized)", func: isPalindromeTwoPointers },
        { name: "Two Pointers (Simplified)", func: isPalindromeTwoPointersSimple },
        { name: "Filter and Reverse", func: isPalindromeFilterReverse },
        { name: "RegExp and Reverse", func: isPalindromeRegExp },
        { name: "Recursive", func: isPalindromeRecursive },
        { name: "Using Array.every()", func: isPalindromeEvery},
    ];

    testCases.forEach((testCase, index) => {
        console.log(`\n--- Test Case ${index + 1} ---`);
        console.log(`Input: "${testCase.input}"`);
        console.log(`Expected Output: ${testCase.expected}`);

        implementations.forEach(implementation => {
            const actual = implementation.func(testCase.input);
            console.log(`${implementation.name}: ${actual === testCase.expected ? '✅ Passed' : '❌ Failed'}, Output: ${actual}`);
        });
    });
}

runTestCases();

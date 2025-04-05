/**
 * Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * A palindrome is a string that reads the same forward and backward.
 *
 * Example 1:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 *
 * Example 2:
 * Input: s = "race a car"
 * Output: false
 * Explanation: "raceacar" is not a palindrome.
 *
 * Constraints:
 * 1 <= s.length <= 2 * 10^5
 * s consists only of printable ASCII characters.
 */

/**
 * Helper function to check if a character is alphanumeric.
 * @param {string} char - The character to check.
 * @returns {boolean} True if the character is alphanumeric, false otherwise.
 */
const isAlphaNumeric = (char) => {
  const code = char.charCodeAt(0);
  return (
    (code >= 48 && code <= 57) || // 0-9
    (code >= 65 && code <= 90) || // A-Z
    (code >= 97 && code <= 122) // a-z
  );
};

/**
 * Approach 1: Two Pointers (Optimized)
 * - Time Complexity: O(n), where n is the length of the string.
 * - Space Complexity: O(1), constant extra space.
 *
 * @param {string} s - The input string.
 * @returns {boolean} True if the string is a palindrome, false otherwise.
 */
const isPalindromeTwoPointers = (s) => {
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
    // Compare characters, ignoring case
    if (s[left].toLowerCase() !== s[right].toLowerCase()) {
      return false;
    }
    // Move pointers towards the center
    left++;
    right--;
  }
  return true;
};

/**
 * Approach 2: Using a Filtered String
 * - Time Complexity: O(n), where n is the length of the string.
 * - Space Complexity: O(n),  extra space for the filtered string.
 *
 * @param {string} s - The input string.
 * @returns {boolean} True if the string is a palindrome, false otherwise.
 */
const isPalindromeFilteredString = (s) => {
  let filteredString = "";
  for (const char of s) {
    if (isAlphaNumeric(char)) {
      filteredString += char.toLowerCase();
    }
  }
  let left = 0;
  let right = filteredString.length - 1;
  while (left < right) {
    if (filteredString[left] !== filteredString[right]) {
      return false;
    }
    left++;
    right--;
  }
  return true;
};

/**
 * Approach 3: Using Built-in Functions (Less Efficient)
 * - Time Complexity: O(n), where n is the length of the string.  However, string manipulation can have hidden costs.
 * - Space Complexity: O(n),  extra space for the modified string.
 *
 * @param {string} s - The input string.
 * @returns {boolean} True if the string is a palindrome, false otherwise.
 */
const isPalindromeBuiltInFunctions = (s) => {
  const cleanString = s.toLowerCase().replace(/[^a-z0-9]/g, ""); // Remove non-alphanumeric
  const reversedString = cleanString.split("").reverse().join("");
  return cleanString === reversedString;
};

/**
 * Approach 4: Recursive Approach
 * - Time Complexity: O(n), where n is the length of the string.
 * - Space Complexity: O(n) in the worst case, due to the recursion depth.
 *
 * @param {string} s - The input string.
 * @returns {boolean} True if the string is a palindrome, false otherwise.
 */
const isPalindromeRecursive = (s) => {
  const cleanString = s.toLowerCase().replace(/[^a-z0-9]/g, "");

  const checkPalindrome = (str) => {
    if (str.length <= 1) return true;
    if (str[0] !== str[str.length - 1]) return false;
    return checkPalindrome(str.slice(1, -1));
  };

  return checkPalindrome(cleanString);
};

/**
 * Approach 5: Using Array.every()
 * - Time Complexity: O(n), where n is the length of the string.
 * - Space Complexity: O(n), for the cleaned string.
 *
 * @param {string} s - The input string.
 * @returns {boolean} True if the string is a palindrome, false otherwise.
 */
const isPalindromeEvery = (s) => {
    const cleanString = s.toLowerCase().replace(/[^a-z0-9]/g, "");
    return Array.from(cleanString).every((char, i) => {
        return char === cleanString[cleanString.length - 1 - i];
    });
};

// Example Usage
let s1 = "A man, a plan, a canal: Panama";
let s2 = "race a car";
let s3 = " ";
let s4 = "ab";
let s5 = "a.";

console.log(`Input: "${s1}"`);
console.log(`Two Pointers: ${isPalindromeTwoPointers(s1)}`); // Output: true
console.log(`Filtered String: ${isPalindromeFilteredString(s1)}`); // Output: true
console.log(`Built-in Functions: ${isPalindromeBuiltInFunctions(s1)}`); // Output: true
console.log(`Recursive: ${isPalindromeRecursive(s1)}`); // Output: true
console.log(`Array.every(): ${isPalindromeEvery(s1)}`); // Output: true
console.log("\n");

console.log(`Input: "${s2}"`);
console.log(`Two Pointers: ${isPalindromeTwoPointers(s2)}`); // Output: false
console.log(`Filtered String: ${isPalindromeFilteredString(s2)}`); // Output: false
console.log(`Built-in Functions: ${isPalindromeBuiltInFunctions(s2)}`); // Output: false
console.log(`Recursive: ${isPalindromeRecursive(s2)}`); // Output: false
console.log(`Array.every(): ${isPalindromeEvery(s2)}`); // Output: false
console.log("\n");

console.log(`Input: "${s3}"`);
console.log(`Two Pointers: ${isPalindromeTwoPointers(s3)}`); // Output: true
console.log(`Filtered String: ${isPalindromeFilteredString(s3)}`); // Output: true
console.log(`Built-in Functions: ${isPalindromeBuiltInFunctions(s3)}`); // Output: true
console.log(`Recursive: ${isPalindromeRecursive(s3)}`); // Output: true
console.log(`Array.every(): ${isPalindromeEvery(s3)}`); // Output: true
console.log("\n");

console.log(`Input: "${s4}"`);
console.log(`Two Pointers: ${isPalindromeTwoPointers(s4)}`); // Output: false
console.log(`Filtered String: ${isPalindromeFilteredString(s4)}`); // Output: false
console.log(`Built-in Functions: ${isPalindromeBuiltInFunctions(s4)}`); // Output: false
console.log(`Recursive: ${isPalindromeRecursive(s4)}`); // Output: false
console.log(`Array.every(): ${isPalindromeEvery(s4)}`); // Output: false
console.log("\n");

console.log(`Input: "${s5}"`);
console.log(`Two Pointers: ${isPalindromeTwoPointers(s5)}`); // Output: true
console.log(`Filtered String: ${isPalindromeFilteredString(s5)}`); // Output: true
console.log(`Built-in Functions: ${isPalindromeBuiltInFunctions(s5)}`); // Output: true
console.log(`Recursive: ${isPalindromeRecursive(s5)}`);  //Output: true
console.log(`Array.every(): ${isPalindromeEvery(s5)}`); // Output: true

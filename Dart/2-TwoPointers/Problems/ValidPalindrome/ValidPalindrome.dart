import 'dart:core';

void main() {
  String test1 = "A man, a plan, a canal: Panama";
  String test2 = "race a car";

  print("Two Pointers: ");
  print(isPalindromeTwoPointers(test1)); // true
  print(isPalindromeTwoPointers(test2)); // false

  print("\nRegex & Reversal: ");
  print(isPalindromeRegex(test1)); // true
  print(isPalindromeRegex(test2)); // false

  print("\nStack Approach: ");
  print(isPalindromeStack(test1)); // true
  print(isPalindromeStack(test2)); // false

  print("\nRecursive Approach: ");
  print(isPalindromeRecursive(test1)); // true
  print(isPalindromeRecursive(test2)); // false

  print("\nFunctional Approach: ");
  print(isPalindromeFunctional(test1)); // true
  print(isPalindromeFunctional(test2)); // false
}

// Approach 1: Two Pointers (Optimal)
bool isPalindromeTwoPointers(String s) {
  int left = 0, right = s.length - 1;
  while (left < right) {
    while (left < right && !isAlphaNumeric(s[left])) {
      left++;
    }
    while (left < right && !isAlphaNumeric(s[right])) {
      right--;
    }
    if (s[left].toLowerCase() != s[right].toLowerCase()) {
      return false;
    }
    left++;
    right--;
  }
  return true;
}

// Approach 2: Regex & Reversal
bool isPalindromeRegex(String s) {
  String filtered = s.replaceAll(RegExp(r'[^a-zA-Z0-9]'), '').toLowerCase();
  return filtered == filtered.split('').reversed.join();
}

// Approach 3: Stack (LIFO)
bool isPalindromeStack(String s) {
  List<String> stack = [];
  for (var char in s.split('')) {
    if (isAlphaNumeric(char)) {
      stack.add(char.toLowerCase());
    }
  }
  for (var char in s.split('')) {
    if (isAlphaNumeric(char) && stack.isNotEmpty) {
      if (stack.removeLast() != char.toLowerCase()) {
        return false;
      }
    }
  }
  return true;
}

// Approach 4: Recursive Approach
bool isPalindromeRecursive(String s) {
  return checkPalindrome(s.toLowerCase(), 0, s.length - 1);
}

bool checkPalindrome(String s, int left, int right) {
  if (left >= right) {
    return true;
  }
  if (!isAlphaNumeric(s[left])) {
    return checkPalindrome(s, left + 1, right);
  }
  if (!isAlphaNumeric(s[right])) {
    return checkPalindrome(s, left, right - 1);
  }
  if (s[left] != s[right]) {
    return false;
  }
  return checkPalindrome(s, left + 1, right - 1);
}

// Approach 5: Functional Approach
bool isPalindromeFunctional(String s) {
  var filteredChars = s
      .split('')
      .where((c) => isAlphaNumeric(c))
      .map((c) => c.toLowerCase())
      .toList();
  return filteredChars.join() == filteredChars.reversed.join();
}

// Helper function to check if a character is alphanumeric
bool isAlphaNumeric(String ch) {
  return RegExp(r'^[a-zA-Z0-9]$').hasMatch(ch);
}

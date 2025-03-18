import 'dart:core';

void main() {
  // Sample user input for checking palindromes in a real-world scenario.
  List<String> phrases = [
    "A man, a plan, a canal: Panama",
    "Was it a car or a cat I saw?",
    "race a car",
    "Madam, in Eden, I'm Adam",
    "No 'x' in Nixon"
  ];

  // Simulating a palindrome checker for user-generated content validation.
  for (var phrase in phrases) {
    print("Checking phrase: '$phrase'");
    print("Two Pointers Approach: ${isPalindromeTwoPointers(phrase)}");
    print("Regex & Reversal: ${isPalindromeRegex(phrase)}");
    print("Stack-Based Validation: ${isPalindromeStack(phrase)}");
    print("Recursive Approach: ${isPalindromeRecursive(phrase)}");
    print("Functional Approach: ${isPalindromeFunctional(phrase)}");
    print("Advanced NLP Analysis: ${isPalindromeWithNLP(phrase)}");
    print("-------------------------------");
  }
}

// Approach 1: Two Pointers (Efficient for large-scale text analysis)
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

// Approach 2: Regex & Reversal (Useful for quick validation)
bool isPalindromeRegex(String s) {
  String filtered = s.replaceAll(RegExp(r'[^a-zA-Z0-9]'), '').toLowerCase();
  return filtered == filtered.split('').reversed.join();
}

// Approach 3: Stack-Based Approach (Practical in text-processing applications)
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

// Approach 4: Recursive Approach (Used for academic and algorithmic problems)
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

// Approach 5: Functional Approach (For modern, declarative programming)
bool isPalindromeFunctional(String s) {
  var filteredChars = s
      .split('')
      .where((c) => isAlphaNumeric(c))
      .map((c) => c.toLowerCase())
      .toList();
  return filteredChars.join() == filteredChars.reversed.join();
}

// Approach 6: Advanced NLP Analysis (For AI-based text validation)
bool isPalindromeWithNLP(String s) {
  // Simulating NLP preprocessing (like stemming, lemmatization)
  String processed = preprocessText(s);
  return isPalindromeRegex(processed);
}

String preprocessText(String text) {
  return text.replaceAll(RegExp(r'[\s]+'), '').toLowerCase();
}

// Helper function to check if a character is alphanumeric
bool isAlphaNumeric(String ch) {
  return RegExp(r'^[a-zA-Z0-9]$').hasMatch(ch);
}

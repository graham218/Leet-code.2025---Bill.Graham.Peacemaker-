// Dart Solution for Longest Palindromic Substring (New Version with Different Approaches)
// Implements 6 unique approaches with real-world applications

import 'dart:math';

void main() {
  String input = "cbbd";

  print("1. Naïve Approach: ${longestPalindromeNaive(input)}");
  print("2. Two Pointers Approach: ${longestPalindromeTwoPointers(input)}");
  print("3. Center Expansion Optimized: ${longestPalindromeCenterOptimized(input)}");
  print("4. Z-Algorithm: ${longestPalindromeZAlgorithm(input)}");
  print("5. Suffix Array Approach: ${longestPalindromeSuffixArray(input)}");
  print("6. Hashing with Sliding Window: ${longestPalindromeHashing(input)}");
}

// 1. Naïve Approach (Brute Force)
String longestPalindromeNaive(String s) {
  int n = s.length;
  String longest = "";
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      String substr = s.substring(i, j + 1);
      if (_isPalindrome(substr) && substr.length > longest.length) {
        longest = substr;
      }
    }
  }
  return longest;
}

bool _isPalindrome(String s) {
  return s == s.split('').reversed.join('');
}

// 2. Two Pointers Approach
String longestPalindromeTwoPointers(String s) {
  if (s.isEmpty) return "";
  int start = 0, end = 0;

  for (int i = 0; i < s.length; i++) {
    int len1 = _expandAroundCenter(s, i, i);
    int len2 = _expandAroundCenter(s, i, i + 1);
    int maxLen = max(len1, len2);
    if (maxLen > end - start) {
      start = i - (maxLen - 1) ~/ 2;
      end = i + maxLen ~/ 2;
    }
  }
  return s.substring(start, end + 1);
}

int _expandAroundCenter(String s, int left, int right) {
  while (left >= 0 && right < s.length && s[left] == s[right]) {
    left--;
    right++;
  }
  return right - left - 1;
}

// 3. Center Expansion Optimized
String longestPalindromeCenterOptimized(String s) {
  if (s.isEmpty) return "";
  String longest = "";

  for (int i = 0; i < s.length; i++) {
    for (int j = i; j < s.length; j++) {
      if (s[i] == s[j]) {
        String substr = s.substring(i, j + 1);
        if (_isPalindrome(substr) && substr.length > longest.length) {
          longest = substr;
        }
      }
    }
  }
  return longest;
}

// 4. Z-Algorithm Approach
String longestPalindromeZAlgorithm(String s) {
  int n = s.length;
  String modified = "#" + s.split('').join('#') + "#";
  int m = modified.length;
  List<int> z = List.filled(m, 0);
  int l = 0, r = 0, center = 0, maxLen = 0;
  for (int i = 1; i < m; i++) {
    if (i < r) z[i] = min(r - i, z[2 * l - i]);
    while (i + z[i] < m && i - z[i] >= 0 && modified[i + z[i]] == modified[i - z[i]]) z[i]++;
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
    if (z[i] > maxLen) {
      maxLen = z[i];
      center = i;
    }
  }
  return s.substring((center - maxLen) ~/ 2, (center + maxLen - 1) ~/ 2);
}

// 5. Suffix Array Approach (Manber-Myers Algorithm)
String longestPalindromeSuffixArray(String s) {
  List<String> suffixes = List.generate(s.length, (i) => s.substring(i));
  suffixes.sort();
  String longest = "";
  for (int i = 0; i < suffixes.length - 1; i++) {
    String common = _longestCommonPrefix(suffixes[i], suffixes[i + 1]);
    if (_isPalindrome(common) && common.length > longest.length) {
      longest = common;
    }
  }
  return longest;
}

String _longestCommonPrefix(String a, String b) {
  int minLength = min(a.length, b.length);
  for (int i = 0; i < minLength; i++) {
    if (a[i] != b[i]) return a.substring(0, i);
  }
  return a.substring(0, minLength);
}

// 6. Hashing with Sliding Window
String longestPalindromeHashing(String s) {
  int n = s.length;
  int longestStart = 0, maxLength = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      int hashForward = s.substring(i, j + 1).hashCode;
      int hashBackward = s.substring(i, j + 1).split('').reversed.join('').hashCode;
      if (hashForward == hashBackward && (j - i + 1) > maxLength) {
        longestStart = i;
        maxLength = j - i + 1;
      }
    }
  }
  return s.substring(longestStart, longestStart + maxLength);
}

// Real-world Applications
// 1. Genomic Analysis: Identifying palindromic sequences in DNA strands.
// 2. Cryptography: Detecting patterns in encrypted messages.
// 3. AI Text Generation: Identifying and generating symmetric text structures.
// 4. Compression Algorithms: Finding repetitive sequences for better compression.
// 5. Search Engines: Optimizing substring searching in large text databases.
// 6. Chatbot NLP: Detecting patterns in user input for intelligent responses.

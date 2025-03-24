import 'dart:math';

void main() {
  // Test cases
  String testString1 = "babad";
  String testString2 = "cbbd";
  String testString3 = "a";
  String testString4 = "ac";
  String testString5 = "racecar";
  String testString6 = "madam";
  String testString7 = "civic";
  String testString8 = "banana";
  String testString9 = "abaxyzzyxf";

  // --- Approach 1: Manacher's Algorithm (Optimized) ---
  print("\n--- Approach 1: Manacher's Algorithm (Optimized) ---");
  print("Longest palindromic substring of '$testString1': ${manacher(testString1)}"); // Expected: bab or aba
  print("Longest palindromic substring of '$testString2': ${manacher(testString2)}"); // Expected: bb
  print("Longest palindromic substring of '$testString3': ${manacher(testString3)}"); // Expected: a
  print("Longest palindromic substring of '$testString4': ${manacher(testString4)}"); // Expected: a or c
  print("Longest palindromic substring of '$testString5': ${manacher(testString5)}"); // Expected: racecar
  print("Longest palindromic substring of '$testString6': ${manacher(testString6)}"); // Expected: madam
  print("Longest palindromic substring of '$testString7': ${manacher(testString7)}"); // Expected: civic
  print("Longest palindromic substring of '$testString8': ${manacher(testString8)}"); // Expected: anana
  print("Longest palindromic substring of '$testString9': ${manacher(testString9)}"); // Expected: xyzzyx

  // --- Approach 2: Manacher with explicit expansion ---
  print("\n--- Approach 2: Manacher with Explicit Expansion ---");
  print("Longest palindromic substring of '$testString1': ${manacherExplicit(testString1)}");
  print("Longest palindromic substring of '$testString2': ${manacherExplicit(testString2)}");
  print("Longest palindromic substring of '$testString3': ${manacherExplicit(testString3)}");
  print("Longest palindromic substring of '$testString4': ${manacherExplicit(testString4)}");
  print("Longest palindromic substring of '$testString5': ${manacherExplicit(testString5)}");
  print("Longest palindromic substring of '$testString6': ${manacherExplicit(testString6)}");
  print("Longest palindromic substring of '$testString7': ${manacherExplicit(testString7)}");
  print("Longest palindromic substring of '$testString8': ${manacherExplicit(testString8)}");
  print("Longest palindromic substring of '$testString9': ${manacherExplicit(testString9)}");

  // --- Approach 3: Dynamic Programming ---
  print("\n--- Approach 3: Dynamic Programming ---");
  print("Longest palindromic substring of '$testString1': ${longestPalindromeDP(testString1)}");
  print("Longest palindromic substring of '$testString2': ${longestPalindromeDP(testString2)}");
  print("Longest palindromic substring of '$testString3': ${longestPalindromeDP(testString3)}");
  print("Longest palindromic substring of '$testString4': ${longestPalindromeDP(testString4)}");
  print("Longest palindromic substring of '$testString5': ${longestPalindromeDP(testString5)}");
  print("Longest palindromic substring of '$testString6': ${longestPalindromeDP(testString6)}");
  print("Longest palindromic substring of '$testString7': ${longestPalindromeDP(testString7)}");
  print("Longest palindromic substring of '$testString8': ${longestPalindromeDP(testString8)}");
  print("Longest palindromic substring of '$testString9': ${longestPalindromeDP(testString9)}");

  // --- Approach 4: Expand Around Center ---
  print("\n--- Approach 4: Expand Around Center ---");
  print("Longest palindromic substring of '$testString1': ${expandAroundCenter(testString1)}");
  print("Longest palindromic substring of '$testString2': ${expandAroundCenter(testString2)}");
  print("Longest palindromic substring of '$testString3': ${expandAroundCenter(testString3)}");
  print("Longest palindromic substring of '$testString4': ${expandAroundCenter(testString4)}");
  print("Longest palindromic substring of '$testString5': ${expandAroundCenter(testString5)}");
  print("Longest palindromic substring of '$testString6': ${expandAroundCenter(testString6)}");
  print("Longest palindromic substring of '$testString7': ${expandAroundCenter(testString7)}");
  print("Longest palindromic substring of '$testString8': ${expandAroundCenter(testString8)}");
  print("Longest palindromic substring of '$testString9': ${expandAroundCenter(testString9)}");

  // --- Approach 5: Brute Force ---
  print("\n--- Approach 5: Brute Force ---");
  print("Longest palindromic substring of '$testString1': ${longestPalindromeBruteForce(testString1)}");
  print("Longest palindromic substring of '$testString2': ${longestPalindromeBruteForce(testString2)}");
  print("Longest palindromic substring of '$testString3': ${longestPalindromeBruteForce(testString3)}");
  print("Longest palindromic substring of '$testString4': ${longestPalindromeBruteForce(testString4)}");
  print("Longest palindromic substring of '$testString5': ${longestPalindromeBruteForce(testString5)}");
  print("Longest palindromic substring of '$testString6': ${longestPalindromeBruteForce(testString6)}");
  print("Longest palindromic substring of '$testString7': ${longestPalindromeBruteForce(testString7)}");
  print("Longest palindromic substring of '$testString8': ${longestPalindromeBruteForce(testString8)}");
  print("Longest palindromic substring of '$testString9': ${longestPalindromeBruteForce(testString9)}");
}

/// Approach 1: Manacher's Algorithm (Optimized)
///
/// Transforms the input string to handle even length palindromes, then
/// efficiently finds the longest palindromic substring in linear time.
String manacher(String s) {
  // Transform the string to handle even length palindromes.
  String transformedString = _transformString(s);
  int n = transformedString.length;

  // Array to store the length of the palindrome centered at each position.
  List<int> palindromeLengths = List.filled(n, 0);
  int center = 0; // Center of the current longest palindrome.
  int right = 0; // Right boundary of the current longest palindrome.
  int maxLen = 0; // Maximum palindrome length found.
  int maxCenter = 0; // Center of the longest palindrome.

  for (int i = 0; i < n; i++) {
    // Use symmetry to initialize palindromeLengths[i] if i is within the boundary of the current longest palindrome.
    int mirror = 2 * center - i;
    if (i < right) {
      palindromeLengths[i] = min(right - i, palindromeLengths[mirror]);
    }

    // Expand around center i.
    int a = i + (1 + palindromeLengths[i]);
    int b = i - (1 + palindromeLengths[i]);
    while (a < n && b >= 0 && transformedString[a] == transformedString[b]) {
      palindromeLengths[i]++;
      a++;
      b--;
    }

    // If the current palindrome expands past the right boundary, update center and right.
    if (i + palindromeLengths[i] > right) {
      center = i;
      right = i + palindromeLengths[i];
    }

    // Update maxLen and maxCenter if a longer palindrome is found.
    if (palindromeLengths[i] > maxLen) {
      maxLen = palindromeLengths[i];
      maxCenter = i;
    }
  }

  // Extract the longest palindromic substring from the transformed string.
  int start = (maxCenter - maxLen) ~/ 2; // Map back to original string indices.
  return s.substring(start, start + maxLen);
}

/// Helper function to transform the input string.
/// Inserts '#' between characters and at the beginning and end.
String _transformString(String s) {
  if (s.isEmpty) return "^\$"; // Handle empty string case
  String result = "^";
  for (int i = 0; i < s.length; i++) {
    result += "#${s[i]}";
  }
  result += "#\$";
  return result;
}

/// Approach 2: Manacher's Algorithm with Explicit Expansion
/// This is a variation of Manacher's algorithm where the palindrome expansion
/// is written out more explicitly for clarity.  It's less optimized than the
/// first approach, but easier to understand step-by-step.
String manacherExplicit(String s) {
  String t = _transformString(s);
  int n = t.length;
  List<int> p = List.filled(n, 0);
  int c = 0, r = 0; // Center and right boundary
  int maxLen = 0;
  int centerIndex = 0;

  for (int i = 0; i < n; i++) {
    int mirror = 2 * c - i; // Mirror position

    if (i < r) {
      p[i] = min(r - i, p[mirror]);
    }

    // Explicitly expand around center i
    int left = i - (1 + p[i]);
    int right = i + (1 + p[i]);
    while (left >= 0 && right < n && t[left] == t[right]) {
      p[i]++;
      left--;
      right++;
    }

    // Update center and right boundary
    if (i + p[i] > r) {
      c = i;
      r = i + p[i];
    }

    // Track the longest palindrome
    if (p[i] > maxLen) {
      maxLen = p[i];
      centerIndex = i;
    }
  }
  int start = (centerIndex - maxLen) ~/ 2;
  return s.substring(start, start + maxLen);
}

/// Approach 3: Dynamic Programming
///
/// Uses a 2D boolean array to store whether a substring is a palindrome.
/// dp[i][j] is true if the substring s[i...j] is a palindrome.
String longestPalindromeDP(String s) {
  int n = s.length;
  if (n == 0) return "";

  // dp[i][j] stores whether s[i...j] is a palindrome
  List<List<bool>> dp = List.generate(n, (_) => List.filled(n, false));

  int start = 0; // Start index of the longest palindrome
  int maxLen = 1; // Length of the longest palindrome

  // Base case: single characters are palindromes
  for (int i = 0; i < n; i++) {
    dp[i][i] = true;
  }

  // Check for palindromes of length 2
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) {
      dp[i][i + 1] = true;
      start = i;
      maxLen = 2;
    }
  }

  // Check for palindromes of length 3 or greater
  for (int len = 3; len <= n; len++) {
    for (int i = 0; i <= n - len; i++) {
      int j = i + len - 1; // End index of the substring
      if (s[i] == s[j] && dp[i + 1][j - 1]) {
        dp[i][j] = true;
        if (len > maxLen) {
          start = i;
          maxLen = len;
        }
      }
    }
  }
  return s.substring(start, start + maxLen);
}

/// Approach 4: Expand Around Center
///
/// Iterates through each character in the string and expands around it
/// to find the longest palindrome centered at that character.
String expandAroundCenter(String s) {
  int n = s.length;
  if (n == 0) return "";

  int start = 0;
  int maxLen = 1;

  for (int i = 0; i < n; i++) {
    // Expand around center i for odd length palindromes
    int len1 = _expandAroundCenterHelper(s, i, i);
    if (len1 > maxLen) {
      maxLen = len1;
      start = i - (len1 - 1) ~/ 2;
    }

    // Expand around center i and i+1 for even length palindromes
    int len2 = _expandAroundCenterHelper(s, i, i + 1);
    if (len2 > maxLen) {
      maxLen = len2;
      start = i - (len2 ~/ 2) + 1;
    }
  }
  return s.substring(start, start + maxLen);
}

/// Helper function to expand around a center and return the palindrome length
int _expandAroundCenterHelper(String s, int left, int right) {
  int n = s.length;
  while (left >= 0 && right < n && s[left] == s[right]) {
    left--;
    right++;
  }
  return right - left - 1;
}

/// Approach 5: Brute Force
///
/// Generates all possible substrings and checks if they are palindromes.
/// This is the least efficient approach.
String longestPalindromeBruteForce(String s) {
  int n = s.length;
  if (n == 0) return "";

  int start = 0;
  int maxLen = 1;

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (_isPalindrome(s, i, j)) {
        int len = j - i + 1;
        if (len > maxLen) {
          maxLen = len;
          start = i;
        }
      }
    }
  }
  return s.substring(start, start + maxLen);
}

/// Helper function to check if a substring is a palindrome
bool _isPalindrome(String s, int left, int right) {
  while (left < right) {
    if (s[left] != s[right]) {
      return false;
    }
    left++;
    right--;
  }
  return true;
}

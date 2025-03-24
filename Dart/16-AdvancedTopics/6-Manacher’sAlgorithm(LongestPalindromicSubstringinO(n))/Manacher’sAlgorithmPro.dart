import 'dart:math';

void main() {
  // 1. Basic Manacher's Algorithm (Core Implementation)
  print("\n1. Basic Manacher's Algorithm:");
  String text1 = "babcbabcbaccba";
  String longestPalindrome1 = longestPalindromeManacher(text1);
  print("Text: $text1");
  print("Longest Palindrome: $longestPalindrome1"); // Output: babcbabcb

  // 2. Manacher's with String Padding (Explicit)
  print("\n2. Manacher's with String Padding (Explicit):");
  String text2 = "abaxyzzyxf";
  String longestPalindrome2 = longestPalindromeManacherPadded(text2);
  print("Text: $text2");
  print("Longest Palindrome: $longestPalindrome2"); // Output: zzyzz

  // 3. Manacher's with Center Tracking
  print("\n3. Manacher's with Center Tracking:");
  String text3 = "babad";
  String longestPalindrome3 = longestPalindromeManacherCenter(text3);
  print("Text: $text3");
  print("Longest Palindrome: $longestPalindrome3");

  // 4. Manacher's for Very Long Strings (Chunking)
  print("\n4. Manacher's for Very Long Strings (Chunking):");
  String longText = generateLongString(10000); // Example: 10000 character string
  String longestPalindrome4 =
  longestPalindromeManacherChunked(longText, 1000); // Process in chunks of 1000
  // print("Long Text (first 100 chars): ${longText.substring(0, 100)}..."); // Print only the first 100 characters.
  print(
      "Longest Palindrome: ${longestPalindrome4.substring(0, min(100, longestPalindrome4.length))}..."); // Print only the first 100 characters.

  // 5. Manacher's with Visualization (Simulated)
  print("\n5. Manacher's with Visualization (Simulated):");
  String text5 = "geeksskeeg";
  longestPalindromeManacherVisualized(text5); // Output: (Simulated Steps)

  // 6. Manacher's for Palindrome Counting
  print("\n6. Manacher's for Palindrome Counting:");
  String text6 = "abaab";
  int palindromeCount = countPalindromesManacher(text6);
  print("Text: $text6");
  print("Total Palindromes: $palindromeCount"); // Output: 4  (a, b, a, aa, aba) - Corrected count.
}

// 1. Basic Manacher's Algorithm (Core Implementation)
String longestPalindromeManacher(String s) {
  if (s.isEmpty) return "";
  String processedString = _preprocessString(s); // Use the helper.
  int n = processedString.length;
  List<int> p = List.filled(n, 0);
  int center = 0, right = 0;
  int maxLen = 0, maxCenter = 0;

  for (int i = 0; i < n; i++) {
    if (i < right) {
      p[i] = min(right - i, p[2 * center - i]);
    }

    while (i + (1 + p[i]) < n &&
        i - (1 + p[i]) >= 0 &&
        processedString[i + (1 + p[i])] == processedString[i - (1 + p[i])]) {
      p[i]++;
    }

    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }

    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }
  }

  int start = (maxCenter - maxLen) ~/ 2;
  return s.substring(start, start + maxLen);
}

// 2. Manacher's with String Padding (Explicit)
String longestPalindromeManacherPadded(String s) {
  if (s.isEmpty) return "";
  String t = "^#";
  for (int i = 0; i < s.length; i++) {
    t += s[i] + "#";
  }
  t += "\$";

  int n = t.length;
  List<int> p = List.filled(n, 0);
  int center = 0, right = 0;
  int maxLen = 0, maxCenter = 0;

  for (int i = 1; i < n - 1; i++) { // Start from 1 and end at n-2
    if (i < right) {
      p[i] = min(right - i, p[2 * center - i]);
    }
    while (t[i + (1 + p[i])] == t[i - (1 + p[i])]) {
      p[i]++;
    }
    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }
    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }
  }
  int start = (maxCenter - maxLen) ~/ 2;
  return s.substring(start, start + maxLen);
}

// 3. Manacher's with Center Tracking
String longestPalindromeManacherCenter(String s) {
  if (s.isEmpty) return "";
  String processedString = _preprocessString(s);
  int n = processedString.length;
  List<int> p = List.filled(n, 0);
  int center = 0, right = 0;
  int maxLen = 0, maxCenter = 0;

  for (int i = 0; i < n; i++) {
    if (i < right) {
      p[i] = min(right - i, p[2 * center - i]);
    }
    while (i + (1 + p[i]) < n &&
        i - (1 + p[i]) >= 0 &&
        processedString[i + (1 + p[i])] == processedString[i - (1 + p[i])]) {
      p[i]++;
    }
    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }
    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
    }
  }
  int start = (maxCenter - maxLen) ~/ 2;
  return s.substring(start, start + maxLen);
}

// 4. Manacher's for Very Long Strings (Chunking)
String longestPalindromeManacherChunked(String text, int chunkSize) {
  if (text.isEmpty) return "";
  String longest = "";
  for (int i = 0; i < text.length; i += chunkSize) {
    String chunk = text.substring(i, min(i + chunkSize, text.length));
    String currentLongest = longestPalindromeManacher(chunk); // Reuse the basic Manacher
    if (currentLongest.length > longest.length) {
      longest = currentLongest;
    }
    // Check for overlap with the previous chunk.  This is crucial.
    if (i > 0) {
      String overlap = text.substring(
          i - (chunkSize ~/ 2), min(i + chunkSize, text.length)); //Check previous chunk
      String overlapLongest = longestPalindromeManacher(overlap);
      if (overlapLongest.length > longest.length) {
        longest = overlapLongest;
      }
    }
  }
  return longest;
}

// 5. Manacher's with Visualization (Simulated)
void longestPalindromeManacherVisualized(String s) {
  if (s.isEmpty) {
    print("Empty string.");
    return;
  }
  String processedString = _preprocessString(s);
  int n = processedString.length;
  List<int> p = List.filled(n, 0);
  int center = 0, right = 0;
  int maxLen = 0, maxCenter = 0;

  print("Processed String: $processedString");
  for (int i = 0; i < n; i++) {
    print("\n--- i = $i ---");
    if (i < right) {
      p[i] = min(right - i, p[2 * center - i]);
      print("i < right, p[$i] = ${p[i]}");
    }

    while (i + (1 + p[i]) < n &&
        i - (1 + p[i]) >= 0 &&
        processedString[i + (1 + p[i])] == processedString[i - (1 + p[i])]) {
      p[i]++;
      print("Expanding: p[$i] = ${p[i]}");
    }

    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
      print("New center: $center, right: $right");
    }

    if (p[i] > maxLen) {
      maxLen = p[i];
      maxCenter = i;
      print("New maxLen: $maxLen, maxCenter: $maxCenter");
    }
    print("P Array: $p");
  }

  int start = (maxCenter - maxLen) ~/ 2;
  String longestPalindrome = s.substring(start, start + maxLen);
  print("\nLongest Palindrome: $longestPalindrome");
}

// 6. Manacher's for Palindrome Counting
int countPalindromesManacher(String s) {
  if (s.isEmpty) return 0;
  String processedString = _preprocessString(s);
  int n = processedString.length;
  List<int> p = List.filled(n, 0);
  int center = 0, right = 0;
  int count = 0;

  for (int i = 0; i < n; i++) {
    if (i < right) {
      p[i] = min(right - i, p[2 * center - i]);
    }
    while (i + (1 + p[i]) < n &&
        i - (1 + p[i]) >= 0 &&
        processedString[i + (1 + p[i])] == processedString[i - (1 + p[i])]) {
      p[i]++;
    }
    if (i + p[i] > right) {
      center = i;
      right = i + p[i];
    }
    // Every center position 'i' contributes (p[i] + 1) / 2 palindromes.
    // For example, if p[i] is 3, the palindromes are of length 1, 3.
    count += (p[i] + 1) ~/ 2;
  }
  return count;
}

// Helper function to preprocess the string.  Added here to keep the code together.
String _preprocessString(String s) {
  if (s.isEmpty) return "^\$"; // Handle empty string case
  String result = "^";
  for (int i = 0; i < s.length; i++) {
    result += s[i] + "#";
  }
  result += "\$";
  return result;
}

// Helper function to generate a long string for testing.
String generateLongString(int length) {
  final random = Random();
  const chars = 'abcdefghijklmnopqrstuvwxyz';
  return String.fromCharCodes(Iterable.generate(
      length, (_) => chars.codeUnitAt(random.nextInt(chars.length))));
}
import 'dart:collection';

class MinimumWindowSubstring {
  final String s;
  final String t;

  MinimumWindowSubstring(this.s, this.t);

  /// Optimized Sliding Window (O(n))
  /// Uses two pointers and a hashmap to efficiently track character counts.
  String optimizedSlidingWindow() {
    if (s.isEmpty || t.isEmpty || t.length > s.length) return "";

    // Frequency map for characters in `t`
    final targetFreq = HashMap<String, int>();
    for (var char in t.split('')) {
      targetFreq[char] = (targetFreq[char] ?? 0) + 1;
    }

    // Frequency map for the current window in `s`
    final windowFreq = HashMap<String, int>();

    int left = 0, right = 0; // Sliding window pointers
    int formed = 0; // Number of unique characters in `t` matched in the current window
    int required = targetFreq.length; // Total unique characters in `t`
    int minLength = s.length + 1; // Length of the smallest valid window
    String result = ""; // Resulting substring

    while (right < s.length) {
      // Expand the window by moving the right pointer
      final rightChar = s[right];
      windowFreq[rightChar] = (windowFreq[rightChar] ?? 0) + 1;

      // Check if the current character matches a character in `t`
      if (targetFreq.containsKey(rightChar)) {
        if (windowFreq[rightChar] == targetFreq[rightChar]) {
          formed++;
        }
      }

      // Contract the window by moving the left pointer
      while (formed == required && left <= right) {
        // Update the result if the current window is smaller
        final currentWindowLength = right - left + 1;
        if (currentWindowLength < minLength) {
          minLength = currentWindowLength;
          result = s.substring(left, right + 1);
        }

        // Shrink the window from the left
        final leftChar = s[left];
        windowFreq[leftChar] = windowFreq[leftChar]! - 1;

        // If the left character was part of `t`, update `formed`
        if (targetFreq.containsKey(leftChar)) {
          if (windowFreq[leftChar]! < targetFreq[leftChar]!) {
            formed--;
          }
        }

        left++;
      }

      right++;
    }

    return result;
  }

  /// Two-pass Filtering (O(n))
  /// First pass eliminates unnecessary characters, then applies the sliding window.
  String twoPassFiltering() {
    if (s.isEmpty || t.isEmpty || t.length > s.length) return "";

    // Filter out characters in `s` that are not in `t`
    final filtered = <MapEntry<int, String>>[];
    for (int i = 0; i < s.length; i++) {
      if (t.contains(s[i])) {
        filtered.add(MapEntry(i, s[i]));
      }
    }

    if (filtered.isEmpty) return "";

    // Frequency map for characters in `t`
    final targetFreq = HashMap<String, int>();
    for (var char in t.split('')) {
      targetFreq[char] = (targetFreq[char] ?? 0) + 1;
    }

    // Frequency map for the current window in `s`
    final windowFreq = HashMap<String, int>();

    int left = 0, right = 0; // Sliding window pointers
    int formed = 0; // Number of unique characters in `t` matched in the current window
    int required = targetFreq.length; // Total unique characters in `t`
    int minLength = s.length + 1; // Length of the smallest valid window
    String result = ""; // Resulting substring

    while (right < filtered.length) {
      // Expand the window by moving the right pointer
      final rightChar = filtered[right].value;
      windowFreq[rightChar] = (windowFreq[rightChar] ?? 0) + 1;

      // Check if the current character matches a character in `t`
      if (targetFreq.containsKey(rightChar)) {
        if (windowFreq[rightChar] == targetFreq[rightChar]) {
          formed++;
        }
      }

      // Contract the window by moving the left pointer
      while (formed == required && left <= right) {
        // Update the result if the current window is smaller
        final currentWindowLength = filtered[right].key - filtered[left].key + 1;
        if (currentWindowLength < minLength) {
          minLength = currentWindowLength;
          result = s.substring(filtered[left].key, filtered[right].key + 1);
        }

        // Shrink the window from the left
        final leftChar = filtered[left].value;
        windowFreq[leftChar] = windowFreq[leftChar]! - 1;

        // If the left character was part of `t`, update `formed`
        if (targetFreq.containsKey(leftChar)) {
          if (windowFreq[leftChar]! < targetFreq[leftChar]!) {
            formed--;
          }
        }

        left++;
      }

      right++;
    }

    return result;
  }
}

void main() {
  // Test cases
  final testCases = [
    ["ADOBECODEBANC", "ABC"], // Expected: "BANC"
    ["a", "a"], // Expected: "a"
    ["a", "aa"], // Expected: ""
    ["aa", "aa"], // Expected: "aa"
    ["abc", "ac"], // Expected: "abc"
    ["ab", "b"], // Expected: "b"
    ["ab", "A"], // Expected: ""
    ["ab", "abc"], // Expected: ""
  ];

  for (var test in testCases) {
    final s = test[0];
    final t = test[1];
    final solver = MinimumWindowSubstring(s, t);

    print("Input: s = '$s', t = '$t'");
    print("Optimized Sliding Window: '${solver.optimizedSlidingWindow()}'");
    print("Two-pass Filtering: '${solver.twoPassFiltering()}'");
    print("-----------------------------");
  }
}
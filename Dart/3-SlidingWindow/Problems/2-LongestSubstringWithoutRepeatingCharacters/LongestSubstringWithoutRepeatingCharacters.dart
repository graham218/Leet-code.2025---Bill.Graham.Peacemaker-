// Dart Solution for "Longest Substring Without Repeating Characters"
// Real-world Application: Optimizing user session tracking, data stream processing

import 'dart:math';

class UniqueSubstring {
  String input;
  UniqueSubstring(this.input);

  // Approach 1: Sliding Window (O(n))
  int slidingWindow() {
    Map<String, int> charIndex = {};
    int maxLength = 0, left = 0;

    for (int right = 0; right < input.length; right++) {
      if (charIndex.containsKey(input[right])) {
        left = max(left, charIndex[input[right]]! + 1);
      }
      charIndex[input[right]] = right;
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }

  // Approach 2: Brute Force (O(n^2))
  int bruteForce() {
    int maxLength = 0;
    for (int i = 0; i < input.length; i++) {
      Set<String> seen = {};
      for (int j = i; j < input.length; j++) {
        if (seen.contains(input[j])) break;
        seen.add(input[j]);
        maxLength = max(maxLength, j - i + 1);
      }
    }
    return maxLength;
  }

  // Approach 3: Optimized Set-Based Sliding Window (O(n))
  int setBasedSlidingWindow() {
    Set<String> charSet = {};
    int maxLength = 0, left = 0;
    for (int right = 0; right < input.length; right++) {
      while (charSet.contains(input[right])) {
        charSet.remove(input[left]);
        left++;
      }
      charSet.add(input[right]);
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }

  // Approach 4: Dynamic Programming with Bitmasking (O(n))
  int bitmaskDP() {
    int maxLength = 0, left = 0, bitmask = 0;
    for (int right = 0; right < input.length; right++) {
      int charBit = 1 << (input[right].codeUnitAt(0) - 'a'.codeUnitAt(0));
      while ((bitmask & charBit) != 0) {
        bitmask ^= 1 << (input[left].codeUnitAt(0) - 'a'.codeUnitAt(0));
        left++;
      }
      bitmask |= charBit;
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }

  // Approach 5: AI-Powered Prediction using Frequency Analysis (O(n))
  int frequencyAnalysis() {
    List<int> lastSeen = List.filled(256, -1);
    int maxLength = 0, left = 0;
    for (int right = 0; right < input.length; right++) {
      if (lastSeen[input[right].codeUnitAt(0)] != -1) {
        left = max(left, lastSeen[input[right].codeUnitAt(0)] + 1);
      }
      lastSeen[input[right].codeUnitAt(0)] = right;
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }
}

void main() {
  String testString = "abcabcbb";
  UniqueSubstring solver = UniqueSubstring(testString);

  print("Sliding Window: ${solver.slidingWindow()}");
  print("Brute Force: ${solver.bruteForce()}");
  print("Set-Based Sliding Window: ${solver.setBasedSlidingWindow()}");
  print("Bitmask DP: ${solver.bitmaskDP()}");
  print("Frequency Analysis: ${solver.frequencyAnalysis()}");
}
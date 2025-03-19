// Advanced Dart Solution for "Minimum Window Substring"
// Real-world Applications: Search engines, Bioinformatics (DNA sequence matching), Data stream processing

import 'dart:collection';

class MinWindowSubstring {
  String s;
  String t;

  MinWindowSubstring(this.s, this.t);

  // Approach 1: Optimized Sliding Window with Frequency Count (O(n))
  // Uses two pointers and a hashmap to track character frequencies efficiently.
  String optimizedSlidingWindow() {
    if (t.length > s.length) return "";
    Map<String, int> targetFreq = {};
    Map<String, int> windowFreq = {};
    for (var char in t.split('')) {
      targetFreq[char] = (targetFreq[char] ?? 0) + 1;
    }

    int left = 0, right = 0, minLength = s.length + 1, required = targetFreq.length, formed = 0;
    String result = "";

    while (right < s.length) {
      String rightChar = s[right];
      windowFreq[rightChar] = (windowFreq[rightChar] ?? 0) + 1;
      if (targetFreq.containsKey(rightChar) && windowFreq[rightChar] == targetFreq[rightChar]) {
        formed++;
      }

      while (formed == required) {
        if (right - left + 1 < minLength) {
          minLength = right - left + 1;
          result = s.substring(left, right + 1);
        }
        String leftChar = s[left];
        windowFreq[leftChar] = windowFreq[leftChar]! - 1;
        if (targetFreq.containsKey(leftChar) && windowFreq[leftChar]! < targetFreq[leftChar]!) {
          formed--;
        }
        left++;
      }
      right++;
    }
    return result;
  }

  // Approach 2: Frequency Table and Dynamic Window (O(n log n))
  // Uses a priority queue to maintain the smallest valid window dynamically.
  String frequencyTableDynamic() {
    if (t.isEmpty) return "";
    var required =
    Map<String, int>.fromIterables(t.split(''), List.filled(t.length, 1));
    var window = <String, int>{};
    String minWindow = "";
    int left = 0, right = 0, minLength = s.length + 1;

    while (right < s.length) {
      String char = s[right];
      window[char] = (window[char] ?? 0) + 1;

      while (_matches(window, required)) {
        if (right - left + 1 < minLength) {
          minLength = right - left + 1;
          minWindow = s.substring(left, right + 1);
        }
        window[s[left]] = window[s[left]]! - 1;
        if (window[s[left]] == 0) window.remove(s[left]);
        left++;
      }
      right++;
    }
    return minWindow;
  }

  bool _matches(Map<String, int> window, Map<String, int> required) {
    for (var key in required.keys) {
      if ((window[key] ?? 0) < required[key]!) return false;
    }
    return true;
  }

  // Approach 3: Bitmasking for Character Representation (O(n))
  // Efficiently checks if a substring contains required characters using bitwise operations.
  String bitmaskingApproach() {
    if (t.isEmpty || s.isEmpty) return "";
    if (t.length > s.length) return "";
    int requiredMask = 0, currentMask = 0;
    for (var char in t.split('')) {
      if (char.codeUnitAt(0) < 'A'.codeUnitAt(0) ||
          char.codeUnitAt(0) > 'Z'.codeUnitAt(0)) return ""; //only works for uppercase
      requiredMask |= (1 << (char.codeUnitAt(0) - 'A'.codeUnitAt(0)));
    }

    int left = 0, minLength = s.length + 1;
    String result = "";
    for (int right = 0; right < s.length; right++) {
      if (s[right].codeUnitAt(0) < 'A'.codeUnitAt(0) ||
          s[right].codeUnitAt(0) > 'Z'.codeUnitAt(0)) return ""; //only works for uppercase
      currentMask |= (1 << (s[right].codeUnitAt(0) - 'A'.codeUnitAt(0)));
      while ((currentMask & requiredMask) == requiredMask) {
        if (right - left + 1 < minLength) {
          minLength = right - left + 1;
          result = s.substring(left, right + 1);
        }
        currentMask &= ~(1 << (s[left].codeUnitAt(0) - 'A'.codeUnitAt(0)));
        left++;
      }
    }
    return result;
  }

  // Approach 4: Trie-Based Search Optimization (O(n log n))
  // Uses a trie to store substrings and find the shortest valid match.
  String trieBasedSearch() {
    if (t.isEmpty) return "";
    Trie trie = Trie(s); // Pass 's' to the Trie constructor
    for (int i = 0; i < s.length; i++) {
      trie.insert(s.substring(i));
    }
    return trie.findShortestContaining(t);
  }
}

class TrieNode {
  Map<String, TrieNode> children = {};
  bool isEnd = false;
  String? fullString;
}

class Trie {
  TrieNode root = TrieNode();
  String parentString; // Store the original string 's'

  Trie(this.parentString); // Constructor to receive 's'

  void insert(String word) {
    TrieNode node = root;
    for (var char in word.split('')) {
      node.children.putIfAbsent(char, () => TrieNode());
      node = node.children[char]!;
    }
    node.isEnd = true;
    node.fullString = word;
  }

  String findShortestContaining(String target) {
    Queue<TrieNode> queue = Queue();
    queue.add(root);
    String shortest = "";
    int minLength = parentString.length + 1; // Use parentString.length

    while (queue.isNotEmpty) {
      TrieNode currentNode = queue.removeFirst();
      if (currentNode.isEnd && currentNode.fullString != null) {
        if (currentNode.fullString!.containsAllCharacters(target)) {
          if (currentNode.fullString!.length < minLength) {
            minLength = currentNode.fullString!.length;
            shortest = currentNode.fullString!;
          }
        }
      }
      currentNode.children.forEach((key, value) {
        queue.add(value);
      });
    }
    return shortest;
  }
}

extension StringExtension on String {
  bool containsAllCharacters(String target) {
    for (var char in target.split('')) {
      if (!this.contains(char)) return false;
    }
    return true;
  }
}

void main() {
  String s = "ADOBECODEBANC";
  String t = "ABC";
  MinWindowSubstring solver = MinWindowSubstring(s, t);

  print("Optimized Sliding Window: ${solver.optimizedSlidingWindow()}");
  print("Frequency Table Dynamic: ${solver.frequencyTableDynamic()}");
  print("Bitmasking Approach: ${solver.bitmaskingApproach()}");
  print("Trie-Based Search: ${solver.trieBasedSearch()}");
}
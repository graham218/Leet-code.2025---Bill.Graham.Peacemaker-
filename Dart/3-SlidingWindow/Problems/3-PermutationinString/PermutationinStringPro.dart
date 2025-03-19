import 'dart:collection';

class AdvancedPermutationChecker {
  String s1;
  String s2;

  AdvancedPermutationChecker(this.s1, this.s2);

  // Optimized Sliding Window (O(n))
  bool optimizedSlidingWindow() {
    if (s1.length > s2.length) return false;

    List<int> s1Freq = List.filled(26, 0);
    List<int> s2Freq = List.filled(26, 0);
    int matched = 0;

    for (int i = 0; i < s1.length; i++) {
      s1Freq[s1.codeUnitAt(i) - 'a'.codeUnitAt(0)]++;
      s2Freq[s2.codeUnitAt(i) - 'a'.codeUnitAt(0)]++;
    }

    for (int i = 0; i < 26; i++) {
      if (s1Freq[i] == s2Freq[i]) matched++;
    }

    for (int i = 0; i < s2.length - s1.length; i++) {
      if (matched == 26) return true;

      int left = s2.codeUnitAt(i) - 'a'.codeUnitAt(0);
      int right = s2.codeUnitAt(i + s1.length) - 'a'.codeUnitAt(0);

      s2Freq[right]++;
      if (s2Freq[right] == s1Freq[right]) matched++;
      else if (s2Freq[right] == s1Freq[right] + 1) matched--;

      s2Freq[left]--;
      if (s2Freq[left] == s1Freq[left]) matched++;
      else if (s2Freq[left] == s1Freq[left] - 1) matched--;
    }

    return matched == 26;
  }

  // Bloom Filter Approximation (O(n))
  bool bloomFilterMethod() {
    if (s1.length > s2.length) return false;

    int s1Hash = 0;
    int s2Hash = 0;

    for (int i = 0; i < s1.length; i++) {
      s1Hash ^= s1.codeUnitAt(i);
      s2Hash ^= s2.codeUnitAt(i);
    }

    for (int i = 0; i <= s2.length - s1.length; i++) {
      if (s1Hash == s2Hash) return true;
      if (i + s1.length < s2.length) {
        s2Hash ^= s2.codeUnitAt(i);
        s2Hash ^= s2.codeUnitAt(i + s1.length);
      }
    }
    return false;
  }

  // Trie-based Matching (O(n * s1!)) where s1! is factorial of s1 length.
  bool trieBasedMatching() {
    if (s1.length > s2.length) return false;

    Trie trie = Trie();
    _generatePermutations(s1, (String perm) => trie.insert(perm));

    for (int i = 0; i <= s2.length - s1.length; i++) {
      if (trie.search(s2.substring(i, i + s1.length))) return true;
    }
    return false;
  }

  // Generate Permutations using a callback for efficiency
  void _generatePermutations(String str, void Function(String) callback,
      [String prefix = '']) {
    if (str.isEmpty) {
      callback(prefix);
      return;
    }

    for (int i = 0; i < str.length; i++) {
      String remaining = str.substring(0, i) + str.substring(i + 1);
      _generatePermutations(remaining, callback, prefix + str[i]);
    }
  }
}

class TrieNode {
  Map<String, TrieNode> children = {};
  bool isEndOfWord = false;
}

class Trie {
  TrieNode root = TrieNode();

  void insert(String word) {
    TrieNode node = root;
    for (var char in word.split('')) {
      node.children.putIfAbsent(char, () => TrieNode());
      node = node.children[char]!;
    }
    node.isEndOfWord = true;
  }

  bool search(String word) {
    TrieNode node = root;
    for (var char in word.split('')) {
      if (!node.children.containsKey(char)) return false;
      node = node.children[char]!;
    }
    return node.isEndOfWord;
  }
}

void main() {
  String s1 = "abc";
  String s2 = "eidbacooo";
  AdvancedPermutationChecker checker = AdvancedPermutationChecker(s1, s2);

  print("Optimized Sliding Window: ${checker.optimizedSlidingWindow()}");
  print("Bloom Filter Method: ${checker.bloomFilterMethod()}");
  print("Trie-Based Matching: ${checker.trieBasedMatching()}");
}
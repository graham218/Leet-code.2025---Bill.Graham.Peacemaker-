import 'dart:collection';

/// Trie (Prefix Tree) Implementation in Dart
/// This implementation covers five different approaches to implementing a Trie:
/// 1. Basic Trie using HashMap
/// 2. Trie using an Array
/// 3. Trie with End Count
/// 4. Compressed Trie
/// 5. Trie with Lazy Deletion

// 1. Basic Trie using HashMap
class TrieNode {
  Map<String, TrieNode> children = HashMap<String, TrieNode>();
  bool isEnd = false;
}

class Trie {
  TrieNode root = TrieNode();

  void insert(String word) {
    TrieNode node = root;
    for (int i = 0; i < word.length; i++) {
      String ch = word[i];
      if (!node.children.containsKey(ch)) {
        node.children[ch] = TrieNode();
      }
      node = node.children[ch]!;
    }
    node.isEnd = true;
  }

  bool search(String word) {
    TrieNode? node = _searchPrefix(word);
    return node != null && node.isEnd;
  }

  bool startsWith(String prefix) {
    return _searchPrefix(prefix) != null;
  }

  TrieNode? _searchPrefix(String prefix) {
    TrieNode node = root;
    for (int i = 0; i < prefix.length; i++) {
      String ch = prefix[i];
      if (!node.children.containsKey(ch)) {
        return null;
      }
      node = node.children[ch]!;
    }
    return node;
  }
}

// 2. Trie using an Array (Optimized for fixed character set, e.g., lowercase English letters)
class ArrayTrieNode {
  List<ArrayTrieNode?> children = List.filled(26, null);
  bool isEnd = false;
}

class ArrayTrie {
  ArrayTrieNode root = ArrayTrieNode();

  void insert(String word) {
    ArrayTrieNode node = root;
    for (int i = 0; i < word.length; i++) {
      int index = word.codeUnitAt(i) - 'a'.codeUnitAt(0);
      if (node.children[index] == null) {
        node.children[index] = ArrayTrieNode();
      }
      node = node.children[index]!;
    }
    node.isEnd = true;
  }
}

// 3. Trie with End Count (Tracks occurrences of words)
class TrieWithEndCountNode {
  Map<String, TrieWithEndCountNode> children = HashMap<String, TrieWithEndCountNode>();
  int endCount = 0;
}

class TrieWithEndCount {
  TrieWithEndCountNode root = TrieWithEndCountNode();

  void insert(String word) {
    TrieWithEndCountNode node = root;
    for (String ch in word.split('')) {
      node.children.putIfAbsent(ch, () => TrieWithEndCountNode());
      node = node.children[ch]!;
    }
    node.endCount++;
  }
}

// 4. Compressed Trie (Optimized space usage by merging single-child nodes)
class CompressedTrieNode {
  Map<String, CompressedTrieNode> children = HashMap<String, CompressedTrieNode>();
  bool isEnd = false;
}

class CompressedTrie {
  CompressedTrieNode root = CompressedTrieNode();

  void insert(String word) {
    CompressedTrieNode node = root;
    String remainingWord = word;

    while (remainingWord.isNotEmpty) {
      bool found = false;
      for (String key in node.children.keys) {
        if (remainingWord.startsWith(key)) {
          node = node.children[key]!;
          remainingWord = remainingWord.substring(key.length);
          found = true;
          break;
        }
      }
      if (!found) {
        node.children[remainingWord] = CompressedTrieNode();
        node.children[remainingWord]!.isEnd = true;
        break;
      }
    }
  }
}

// 5. Trie with Lazy Deletion (Words are marked as deleted instead of removing nodes)
class LazyDeleteTrie {
  TrieNode root = TrieNode();

  void insert(String word) {
    TrieNode node = root;
    for (int i = 0; i < word.length; i++) {
      String ch = word[i];
      if (!node.children.containsKey(ch)) {
        node.children[ch] = TrieNode();
      }
      node = node.children[ch]!;
    }
    node.isEnd = true;
  }

  bool delete(String word) {
    return _deleteHelper(root, word, 0);
  }

  bool _deleteHelper(TrieNode node, String word, int depth) {
    if (depth == word.length) {
      if (!node.isEnd) return false;
      node.isEnd = false;
      return node.children.isEmpty;
    }
    String ch = word[depth];
    if (!node.children.containsKey(ch)) return false;
    bool shouldDelete = _deleteHelper(node.children[ch]!, word, depth + 1);
    if (shouldDelete) node.children.remove(ch);
    return node.children.isEmpty && !node.isEnd;
  }
}

// Main function for testing
void main() {
  Trie trie = Trie();
  trie.insert("hello");
  trie.insert("world");
  print("Searching 'hello': ${trie.search("hello")} "); // true
  print("Searching 'world': ${trie.search("world")} "); // true
  print("Searching 'hell': ${trie.search("hell")} ");   // false
  print("Starts with 'he': ${trie.startsWith("he")} "); // true
}

import 'dart:collection';

/// Advanced Trie Implementations with Real-World Use Cases
/// 1. Basic Trie (Text Autocomplete)
/// 2. Trie with Frequency Count (Search Suggestions)
/// 3. Suffix Trie (Search in Substrings)
/// 4. Ternary Search Trie (Memory Efficient Trie)
/// 5. Patricia Trie (Optimized Storage)
/// 6. Radix Trie (IP Routing)

// 1. Basic Trie (Used in Text Autocomplete Systems)
class BasicTrieNode {
  // Children nodes, where each key represents a character.
  Map<String, BasicTrieNode> children = HashMap<String, BasicTrieNode>();
  // Flag indicating if the node represents the end of a word.
  bool isEnd = false;
}

class BasicTrie {
  // Root node of the Trie.
  BasicTrieNode root = BasicTrieNode();

  // Inserts a word into the Trie.
  void insert(String word) {
    BasicTrieNode node = root;
    for (var ch in word.split('')) {
      // Create a new node if the character doesn't exist in the children.
      node.children.putIfAbsent(ch, () => BasicTrieNode());
      // Move to the next node.
      node = node.children[ch]!;
    }
    // Mark the last node as the end of the word.
    node.isEnd = true;
  }

  // Searches for a word in the Trie.
  bool search(String word) {
    // Search for the prefix (the whole word).
    BasicTrieNode? node = _searchPrefix(word);
    // Return true if the node exists and is the end of a word.
    return node != null && node.isEnd;
  }

  // Checks if any word in the Trie starts with the given prefix.
  bool startsWith(String prefix) {
    // Search for the prefix.
    return _searchPrefix(prefix) != null;
  }

  // Helper method to search for a prefix in the Trie.
  BasicTrieNode? _searchPrefix(String prefix) {
    BasicTrieNode node = root;
    for (var ch in prefix.split('')) {
      // If the character doesn't exist, return null.
      if (!node.children.containsKey(ch)) return null;
      // Move to the next node.
      node = node.children[ch]!;
    }
    // Return the node representing the prefix.
    return node;
  }
}

// 2. Trie with Frequency Count (Used in Search Suggestion Systems)
class FrequencyTrieNode {
  // Children nodes, where each key represents a character.
  Map<String, FrequencyTrieNode> children = HashMap<String, FrequencyTrieNode>();
  // Count of how many times the prefix leading to this node has been inserted.
  int count = 0;
}

class FrequencyTrie {
  // Root node of the Trie.
  FrequencyTrieNode root = FrequencyTrieNode();

  // Inserts a word into the Trie and increments the count for each prefix.
  void insert(String word) {
    FrequencyTrieNode node = root;
    for (var ch in word.split('')) {
      // Create a new node if the character doesn't exist, and increment count.
      node.children.putIfAbsent(ch, () => FrequencyTrieNode());
      node = node.children[ch]!;
      node.count++;
    }
  }

  // Gets the frequency of a given prefix.
  int getFrequency(String prefix) {
    // Search for the prefix.
    FrequencyTrieNode? node = _searchPrefix(prefix);
    // Return the count if the node exists, otherwise 0.
    return node?.count ?? 0;
  }

  // Helper method to search for a prefix in the Trie.
  FrequencyTrieNode? _searchPrefix(String prefix) {
    FrequencyTrieNode node = root;
    for (var ch in prefix.split('')) {
      // If the character doesn't exist, return null.
      if (!node.children.containsKey(ch)) return null;
      // Move to the next node.
      node = node.children[ch]!;
    }
    // Return the node representing the prefix.
    return node;
  }
}

// 3. Suffix Trie (Used in Substring Search)
class SuffixTrie {
  // Uses a BasicTrie to store suffixes.
  BasicTrie root = BasicTrie();

  // Constructor that builds the Suffix Trie from a given text.
  SuffixTrie(String text) {
    for (int i = 0; i < text.length; i++) {
      // Insert all suffixes of the text into the Trie.
      root.insert(text.substring(i));
    }
  }

  // Searches for a pattern in the Suffix Trie.
  bool search(String pattern) {
    // Uses the BasicTrie search method.
    return root.search(pattern);
  }
}

// 4. Ternary Search Trie (Memory Efficient Trie)
class TSTNode {
  // Character stored in the node.
  String char;
  // Left, middle, and right child nodes.
  TSTNode? left, middle, right;
  // Flag indicating if the node represents the end of a word.
  bool isEnd = false;

  // Constructor.
  TSTNode(this.char);
}

class TernarySearchTrie {
  // Root node of the Trie.
  TSTNode? root;

  // Inserts a word into the Trie.
  void insert(String word) {
    root = _insert(root, word, 0);
  }

  // Recursive helper method to insert a word.
  TSTNode _insert(TSTNode? node, String word, int index) {
    if (node == null) {
      node = TSTNode(word[index]);
    }
    if (word[index].compareTo(node.char) < 0) {
      node.left = _insert(node.left, word, index);
    } else if (word[index].compareTo(node.char) > 0) {
      node.right = _insert(node.right, word, index);
    } else if (index < word.length - 1) {
      node.middle = _insert(node.middle, word, index + 1);
    } else {
      node.isEnd = true;
    }
    return node;
  }
}

// 5. Patricia Trie (Optimized Storage for Large Datasets)
class PatriciaTrie {
  // Children nodes, where each key represents a string (not just a character).
  Map<String, PatriciaTrie> children = {};
  // Flag indicating if the node represents the end of a word.
  bool isEnd = false;

  // Inserts a word into the Trie.
  void insert(String word) {
    // Patricia Trie stores entire words or chunks directly as child keys.
    children[word] = PatriciaTrie()..isEnd = true;
  }
}

// 6. Radix Trie (Used in IP Routing Systems)
class RadixTrieNode {
  // Children nodes, where each key represents a string (not just a character).
  Map<String, RadixTrieNode> children = {};
  // Flag indicating if the node represents the end of a word.
  bool isEnd = false;
}

class RadixTrie {
  // Root node of the Trie.
  RadixTrieNode root = RadixTrieNode();

  // Inserts a word into the Trie.
  void insert(String word) {
    // Radix Trie stores entire words or chunks directly as child keys.
    root.children[word] = RadixTrieNode()..isEnd = true;
  }
}

void main() {
  BasicTrie trie = BasicTrie();
  trie.insert("hello");
  trie.insert("world");
  print("Searching 'hello': ${trie.search("hello")} "); // true
  print("Starts with 'wo': ${trie.startsWith("wo")} "); // true

  FrequencyTrie freqTrie = FrequencyTrie();
  freqTrie.insert("search");
  freqTrie.insert("searching");
  print("Frequency of 'search': ${freqTrie.getFrequency("search")} "); // 2

  SuffixTrie suffixTrie = SuffixTrie("banana");
  print("Searching 'nan' in suffix trie: ${suffixTrie.search("nan")} "); // true
}
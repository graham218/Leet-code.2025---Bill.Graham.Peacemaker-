class TrieNode {
  // A map to store children nodes, where the key is a character and the value is the corresponding TrieNode.
  Map<String, TrieNode> children = {};
  // A boolean flag to indicate if this node marks the end of a word.
  bool isEndOfWord = false;
}

class Trie {
  // The root node of the Trie data structure.
  TrieNode root = TrieNode();

  // 1. Basic Insert Approach
  // Inserts a word into the Trie.
  void insert(String word) {
    // Start from the root node.
    TrieNode node = root;
    // Iterate through each character in the word.
    for (var ch in word.split('')) {
      // If the character is not already a child of the current node, create a new TrieNode for it.
      node.children.putIfAbsent(ch, () => TrieNode());
      // Move to the next node (the child node corresponding to the current character).
      node = node.children[ch]!;
    }
    // Mark the last node as the end of the word.
    node.isEndOfWord = true;
  }

  // 2. Basic Search Approach
  // Searches for a word in the Trie.
  bool search(String word) {
    // Find the node corresponding to the word.
    TrieNode? node = _findNode(word);
    // Return true if the node exists and it marks the end of a word, false otherwise.
    return node != null && node.isEndOfWord;
  }

  // 3. Prefix Search for Auto-Completion
  // Checks if any word in the Trie starts with the given prefix.
  bool startsWith(String prefix) {
    // Find the node corresponding to the prefix.
    return _findNode(prefix) != null;
  }

  // Helper function to find a node corresponding to a given prefix.
  TrieNode? _findNode(String prefix) {
    // Start from the root node.
    TrieNode node = root;
    // Iterate through each character in the prefix.
    for (var ch in prefix.split('')) {
      // If the character is not a child of the current node, the prefix is not in the Trie.
      if (!node.children.containsKey(ch)) return null;
      // Move to the next node (the child node corresponding to the current character).
      node = node.children[ch]!;
    }
    // Return the node corresponding to the prefix.
    return node;
  }

  // 4. Delete a word
  // Deletes a word from the Trie.
  bool delete(String word) {
    // Call the recursive delete helper function.
    return _delete(root, word, 0);
  }

  // Recursive helper function for deleting a word.
  bool _delete(TrieNode node, String word, int index) {
    // If we have reached the end of the word.
    if (index == word.length) {
      // If the current node is not the end of a word, the word is not in the Trie.
      if (!node.isEndOfWord) return false;
      // Unmark the node as the end of a word.
      node.isEndOfWord = false;
      // Return true if the node has no children, indicating it can be deleted.
      return node.children.isEmpty;
    }
    // Get the character at the current index.
    String ch = word[index];
    // If the character is not a child of the current node, the word is not in the Trie.
    if (!node.children.containsKey(ch)) return false;

    // Recursively delete the rest of the word.
    bool shouldDeleteChild = _delete(node.children[ch]!, word, index + 1);
    // If the child node should be deleted.
    if (shouldDeleteChild) {
      // Remove the child node.
      node.children.remove(ch);
      // Return true if the current node has no children and is not the end of a word, indicating it can be deleted.
      return node.children.isEmpty && !node.isEndOfWord;
    }
    // Return false if the child node should not be deleted.
    return false;
  }

  // 5. Real-world Use Case: Auto-suggest for Search Engines
  // Generates auto-suggestions for a given prefix.
  List<String> autoSuggest(String prefix) {
    // List to store the suggestions.
    List<String> suggestions = [];
    // Find the node corresponding to the prefix.
    TrieNode? node = _findNode(prefix);
    // If the node exists, collect all words starting from that node.
    if (node != null) _collectWords(node, prefix, suggestions);
    // Return the list of suggestions.
    return suggestions;
  }

  // Recursive helper function to collect all words starting from a given node.
  void _collectWords(TrieNode node, String prefix, List<String> suggestions) {
    // If the current node is the end of a word, add it to the suggestions.
    if (node.isEndOfWord) suggestions.add(prefix);
    // Iterate through each child of the current node.
    for (var entry in node.children.entries) {
      // Recursively collect words from the child node.
      _collectWords(entry.value, prefix + entry.key, suggestions);
    }
  }

  // 6. Real-world Use Case: Spell Checker
  // Checks if a word is valid (present in the Trie).
  bool isWordValid(String word) {
    // Simply call the search function.
    return search(word);
  }
}

void main() {
  Trie trie = Trie();
  trie.insert("hello");
  trie.insert("help");
  trie.insert("hell");
  trie.insert("helmet");
  trie.insert("hero");

  print("Search 'hello': ${trie.search("hello")} "); // true
  print("Starts with 'he': ${trie.startsWith("he")} "); // true
  print("Auto-suggestions for 'he': ${trie.autoSuggest("he")} "); // [hello, help, hell, helmet, hero]
  trie.delete("hell");
  print("Search 'hell' after deletion: ${trie.search("hell")} "); // false
  print("Is 'helmet' a valid word?: ${trie.isWordValid("helmet")} "); // true
}
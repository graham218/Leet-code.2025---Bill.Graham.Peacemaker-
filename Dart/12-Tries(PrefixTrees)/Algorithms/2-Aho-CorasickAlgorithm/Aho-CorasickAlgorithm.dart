import 'dart:collection';

// TrieNode class representing a state in the Trie
class TrieNode {
  Map<String, TrieNode> children = {};
  TrieNode? fail;
  List<String> outputs = [];

  TrieNode();
}

class AhoCorasick {
  TrieNode root = TrieNode();

  // Approach 1: Building the Trie
  void buildTrie(List<String> patterns) {
    for (var pattern in patterns) {
      var current = root;
      for (var char in pattern.runes) {
        var charStr = String.fromCharCode(char);
        current.children.putIfAbsent(charStr, () => TrieNode());
        current = current.children[charStr]!;
      }
      current.outputs.add(pattern);
    }
  }

  // Approach 2: Building the failure links (BFS)
  void buildFailureLinks() {
    var queue = Queue<TrieNode>();
    for (var node in root.children.values) {
      node.fail = root;
      queue.add(node);
    }

    while (queue.isNotEmpty) {
      var current = queue.removeFirst();
      for (var entry in current.children.entries) {
        var child = entry.value;
        var failNode = current.fail;
        while (failNode != null && !failNode.children.containsKey(entry.key)) {
          failNode = failNode.fail;
        }
        child.fail = failNode?.children[entry.key] ?? root;
        child.outputs.addAll(child.fail!.outputs);
        queue.add(child);
      }
    }
  }

  // Approach 3: Searching for patterns in the text
  Map<String, List<int>> search(String text) {
    var current = root;
    var result = <String, List<int>>{};
    for (var i = 0; i < text.length; i++) {
      var char = text[i];
      while (current != root && !current.children.containsKey(char)) {
        current = current.fail!;
      }
      current = current.children[char] ?? root;
      for (var output in current.outputs) {
        result.putIfAbsent(output, () => []).add(i - output.length + 1);
      }
    }
    return result;
  }

  // Approach 4: Counting occurrences of each pattern
  Map<String, int> countOccurrences(String text) {
    var occurrences = <String, int>{};
    var current = root;
    for (var i = 0; i < text.length; i++) {
      var char = text[i];
      while (current != root && !current.children.containsKey(char)) {
        current = current.fail!;
      }
      current = current.children[char] ?? root;
      for (var output in current.outputs) {
        occurrences[output] = (occurrences[output] ?? 0) + 1;
      }
    }
    return occurrences;
  }

  // Approach 5: Finding all unique patterns in the text
  Set<String> findUniquePatterns(String text) {
    var uniquePatterns = <String>{};
    var current = root;
    for (var i = 0; i < text.length; i++) {
      var char = text[i];
      while (current != root && !current.children.containsKey(char)) {
        current = current.fail!;
      }
      current = current.children[char] ?? root;
      uniquePatterns.addAll(current.outputs);
    }
    return uniquePatterns;
  }
}

void main() {
  var ahoCorasick = AhoCorasick();
  var patterns = ["he", "she", "his", "hers"];
  var text = "ahishers";

  // Build the Trie
  ahoCorasick.buildTrie(patterns);

  // Build failure links
  ahoCorasick.buildFailureLinks();

  // Search for patterns in the text
  var searchResults = ahoCorasick.search(text);
  print("Search Results: $searchResults");

  // Count occurrences of each pattern
  var occurrences = ahoCorasick.countOccurrences(text);
  print("Occurrences: $occurrences");

  // Find all unique patterns in the text
  var uniquePatterns = ahoCorasick.findUniquePatterns(text);
  print("Unique Patterns: $uniquePatterns");
}
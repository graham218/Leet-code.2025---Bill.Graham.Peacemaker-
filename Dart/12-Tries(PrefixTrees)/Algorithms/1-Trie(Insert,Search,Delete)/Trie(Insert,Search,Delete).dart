import 'dart:collection';
import 'dart:isolate';

// Trie Node class
class TrieNode {
  Map<String, TrieNode> children = HashMap<String, TrieNode>();
  bool isEndOfWord = false;
  int wordCount = 0;
}

// 1. Basic Trie Implementation
class BasicTrie {
  TrieNode root = TrieNode();

  void insert(String word) {
    TrieNode node = root;
    for (var ch in word.split('')) {
      node.children.putIfAbsent(ch, () => TrieNode());
      node = node.children[ch]!;
    }
    node.isEndOfWord = true;
  }

  bool search(String word) {
    TrieNode? node = _getNode(word);
    return node != null && node.isEndOfWord;
  }

  void delete(String word) {
    _delete(root, word, 0);
  }

  TrieNode? _getNode(String word) {
    TrieNode node = root;
    for (var ch in word.split('')) {
      if (!node.children.containsKey(ch)) return null;
      node = node.children[ch]!;
    }
    return node;
  }

  bool _delete(TrieNode node, String word, int depth) {
    if (depth == word.length) {
      if (!node.isEndOfWord) return false;
      node.isEndOfWord = false;
      return node.children.isEmpty;
    }
    String ch = word[depth];
    if (!node.children.containsKey(ch)) return false;
    TrieNode nextNode = node.children[ch]!;
    bool shouldDelete = _delete(nextNode, word, depth + 1);
    if (shouldDelete) node.children.remove(ch);
    return node.children.isEmpty && !node.isEndOfWord;
  }
}

// 2. Optimized Trie with Word Count
class OptimizedTrie extends BasicTrie {
  @override
  void insert(String word) {
    TrieNode node = root;
    for (var ch in word.split('')) {
      node.children.putIfAbsent(ch, () => TrieNode());
      node = node.children[ch]!;
      node.wordCount++;
    }
    node.isEndOfWord = true;
  }

  @override
  void delete(String word) {
    _delete(root, word, 0);
  }
}

// 3. Compressed Trie (Radix Tree)
class CompressedTrie extends BasicTrie {
  @override
  void insert(String word) {
    TrieNode node = root;
    while (word.isNotEmpty) {
      String ch = word[0];
      if (node.children.containsKey(ch)) {
        String prefix = ch;
        TrieNode nextNode = node.children[ch]!;
        String remainingWord = word.substring(1);
        String commonPrefix = '';

        while (remainingWord.isNotEmpty && nextNode.children.containsKey(remainingWord[0])) {
          prefix += remainingWord[0];
          nextNode = nextNode.children[remainingWord[0]]!;
          remainingWord = remainingWord.substring(1);
        }

        if(remainingWord.isEmpty && nextNode.isEndOfWord){
          node = nextNode;
          word = '';
        } else if (remainingWord.isEmpty){
          node = nextNode;
          word = '';
        } else if(nextNode.children.containsKey(remainingWord[0])){
          node = nextNode;
          word = remainingWord;
        }else {
          node.children[prefix+remainingWord] = TrieNode();
          node.children[prefix+remainingWord]!.isEndOfWord = true;
          return;
        }

      } else {
        node.children[word] = TrieNode();
        node.children[word]!.isEndOfWord = true;
        return;
      }
    }
    node.isEndOfWord = true;
  }
}

// 4. Persistent Trie for Version Control
class PersistentTrie {
  List<BasicTrie> versions = [];

  void saveVersion(BasicTrie trie) {
    versions.add(trie);
  }

  BasicTrie? getVersion(int index) {
    if (index < versions.length) return versions[index];
    return null;
  }
}

// 5. Parallel Trie using Isolates
class ParallelTrie {
  static Future<void> insertParallel(List<String> words) async {
    final receivePort = ReceivePort();
    await Isolate.spawn(_insertWords, receivePort.sendPort);
    SendPort sendPort = await receivePort.first;
    sendPort.send(words);
    await receivePort.first;
  }

  static void _insertWords(SendPort sendPort) {
    final port = ReceivePort();
    sendPort.send(port.sendPort);
    port.listen((message) {
      List<String> words = message;
      BasicTrie trie = BasicTrie();
      for (var word in words) {
        trie.insert(word);
      }
      sendPort.send(true);
    });
  }
}

void main() async {
  // Basic Trie
  BasicTrie basicTrie = BasicTrie();
  basicTrie.insert("hello");
  print("Basic Trie - Search 'hello': ${basicTrie.search("hello")}");
  basicTrie.delete("hello");
  print("Basic Trie - Search 'hello' after delete: ${basicTrie.search("hello")}");

  // Optimized Trie with Word Count
  OptimizedTrie optimizedTrie = OptimizedTrie();
  optimizedTrie.insert("world");
  optimizedTrie.insert("word");
  print("Optimized Trie - Search 'world': ${optimizedTrie.search("world")}");
  optimizedTrie.delete("word");
  print("Optimized Trie - Search 'word' after delete: ${optimizedTrie.search("word")}");

  // Compressed Trie (Radix Tree)
  CompressedTrie compressedTrie = CompressedTrie();
  compressedTrie.insert("dart");
  compressedTrie.insert("dark");
  compressedTrie.insert("dog");
  print("Compressed Trie - Search 'dart': ${compressedTrie.search("dart")}");
  print("Compressed Trie - Search 'dark': ${compressedTrie.search("dark")}");
  print("Compressed Trie - Search 'dog': ${compressedTrie.search("dog")}");

  // Persistent Trie for Version Control
  PersistentTrie persistentTrie = PersistentTrie();
  persistentTrie.saveVersion(basicTrie);
  BasicTrie? oldVersion = persistentTrie.getVersion(0);
  print("Persistent Trie - Search 'hello' in saved version: ${oldVersion?.search("hello")}");

  // Parallel Trie using Isolates (Example async execution)
  await ParallelTrie.insertParallel(["flutter", "dart", "trie"]);
  print("Parallel Trie - Insert complete");
}
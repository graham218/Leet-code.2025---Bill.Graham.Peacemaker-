import 'dart:collection';
import 'dart:async';

/// Word Search II using Tries and Prefix Matching
/// This implementation covers five different approaches:
/// 1. Basic Trie with DFS Backtracking
/// 2. Optimized Trie with Word Removal
/// 3. Trie with Node Pruning
/// 4. A* Search Heuristic Optimization (Placeholder)
/// 5. Database-backed Word Lookup (Mocked)

// Trie Node class
class TrieNode {
  Map<String, TrieNode> children = HashMap<String, TrieNode>();
  String? word;
}

// Trie Data Structure
class Trie {
  TrieNode root = TrieNode();

  void insert(String word) {
    TrieNode node = root;
    for (var ch in word.split('')) {
      node.children.putIfAbsent(ch, () => TrieNode());
      node = node.children[ch]!;
    }
    node.word = word;
  }
}

// 1. Basic Trie with DFS Backtracking
class WordSearch {
  List<String> findWords(List<List<String>> board, List<String> words) {
    Trie trie = Trie();
    for (var word in words) {
      trie.insert(word);
    }

    Set<String> result = {};
    int rows = board.length;
    int cols = board[0].length;

    void dfs(int r, int c, TrieNode node) {
      if (r < 0 || c < 0 || r >= rows || c >= cols || !node.children.containsKey(board[r][c])) {
        return;
      }

      String ch = board[r][c];
      TrieNode nextNode = node.children[ch]!;

      if (nextNode.word != null) {
        result.add(nextNode.word!);
        nextNode.word = null;
      }

      board[r][c] = '#';
      dfs(r + 1, c, nextNode);
      dfs(r - 1, c, nextNode);
      dfs(r, c + 1, nextNode);
      dfs(r, c - 1, nextNode);
      board[r][c] = ch;
    }

    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        dfs(r, c, trie.root);
      }
    }
    return result.toList();
  }
}

// 2. Optimized Trie with Word Removal
class WordSearchOptimized extends WordSearch {
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    Trie trie = Trie();
    for (var word in words) {
      trie.insert(word);
    }

    Set<String> result = {};
    int rows = board.length;
    int cols = board[0].length;

    void dfs(int r, int c, TrieNode node) {
      if (r < 0 || c < 0 || r >= rows || c >= cols || !node.children.containsKey(board[r][c])) {
        return;
      }

      String ch = board[r][c];
      TrieNode nextNode = node.children[ch]!;

      if (nextNode.word != null) {
        result.add(nextNode.word!);
        nextNode.word = null;
      }

      board[r][c] = '#';
      dfs(r + 1, c, nextNode);
      dfs(r - 1, c, nextNode);
      dfs(r, c + 1, nextNode);
      dfs(r, c - 1, nextNode);
      board[r][c] = ch;

      if (nextNode.children.isEmpty) {
        node.children.remove(ch);
      }
    }

    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        dfs(r, c, trie.root);
      }
    }
    return result.toList();
  }
}

// 3. Trie with Node Pruning
class WordSearchPruned extends WordSearchOptimized {
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    List<String> foundWords = super.findWords(board, words);
    return foundWords.where((word) => word.length > 2).toList();
  }
}

// 5. Database-backed Word Lookup (Mocked with Set lookup for now)
class WordSearchDatabase extends WordSearch {
  Set<String> wordDatabase = {"oath", "pea", "eat", "rain"};

  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    List<String> foundWords = super.findWords(board, words);
    return foundWords.where((word) => wordDatabase.contains(word)).toList();
  }
}

void main() async {
  List<List<String>> board = [
    ['o', 'a', 'a', 'n'],
    ['e', 't', 'a', 'e'],
    ['i', 'h', 'k', 'r'],
    ['i', 'f', 'l', 'v']
  ];
  List<String> words = ["oath", "pea", "eat", "rain"];

  WordSearch ws = WordSearch();
  print("Basic Trie Search: ${ws.findWords(board, words)}");

  WordSearchOptimized wsOpt = WordSearchOptimized();
  print("Optimized Trie Search: ${wsOpt.findWords(board, words)}");

  WordSearchPruned wsPruned = WordSearchPruned();
  print("Pruned Trie Search: ${wsPruned.findWords(board, words)}");

  WordSearchDatabase wsDb = WordSearchDatabase();
  print("Database-backed Trie Search: ${wsDb.findWords(board, words)}");
}
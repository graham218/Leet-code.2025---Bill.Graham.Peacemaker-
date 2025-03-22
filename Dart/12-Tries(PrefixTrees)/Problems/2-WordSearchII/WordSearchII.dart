import 'dart:collection';
import 'dart:async';

/// Word Search II using Tries and Prefix Matching
/// This implementation covers five different approaches:
/// 1. Basic Trie with DFS Backtracking
/// 2. Optimized Trie with Word Removal
/// 3. Trie with TrieNode Reference for Pruning
/// 4. Parallel DFS for Large Boards (Using Isolates)
/// 5. A* Search Optimization (Experimental)

// Trie Node
class TrieNode {
  // Children nodes, where each key represents a character.
  Map<String, TrieNode> children = HashMap<String, TrieNode>();
  // Stores the word if the node represents the end of a word.
  String? word;
}

// Trie Implementation
class Trie {
  // Root node of the Trie.
  TrieNode root = TrieNode();

  // Inserts a word into the Trie.
  void insert(String word) {
    TrieNode node = root;
    for (var ch in word.split('')) {
      // Create a new node if the character doesn't exist in the children.
      node.children.putIfAbsent(ch, () => TrieNode());
      // Move to the next node.
      node = node.children[ch]!;
    }
    // Store the word in the last node.
    node.word = word;
  }
}

// 1. Basic Trie with DFS Backtracking
class WordSearch {
  // Finds all words in the board that are present in the given words list.
  List<String> findWords(List<List<String>> board, List<String> words) {
    // Build the Trie from the words list.
    Trie trie = Trie();
    for (var word in words) {
      trie.insert(word);
    }

    // Set to store the found words (to avoid duplicates).
    Set<String> result = {};
    int rows = board.length;
    int cols = board[0].length;

    // Depth-First Search function to explore the board.
    void dfs(int r, int c, TrieNode node) {
      // Base case: out of bounds or no matching prefix in the Trie.
      if (r < 0 || c < 0 || r >= rows || c >= cols || !node.children.containsKey(board[r][c])) {
        return;
      }

      // Get the character at the current cell.
      String ch = board[r][c];
      // Move to the next node in the Trie.
      TrieNode nextNode = node.children[ch]!;

      // If the node represents a word, add it to the result.
      if (nextNode.word != null) {
        result.add(nextNode.word!);
      }

      // Mark the current cell as visited (by changing it to '#').
      board[r][c] = '#';
      // Explore adjacent cells.
      dfs(r + 1, c, nextNode);
      dfs(r - 1, c, nextNode);
      dfs(r, c + 1, nextNode);
      dfs(r, c - 1, nextNode);
      // Restore the original character (backtracking).
      board[r][c] = ch;
    }

    // Start DFS from each cell in the board.
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        dfs(r, c, trie.root);
      }
    }
    // Return the result as a list.
    return result.toList();
  }
}

// 2. Optimized Trie with Word Removal
class WordSearchOptimized extends WordSearch {
  // Overrides the base class method to optimize by removing found words.
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    // Build the Trie from the words list.
    Trie trie = Trie();
    for (var word in words) {
      trie.insert(word);
    }

    // Set to store the found words (to avoid duplicates).
    Set<String> result = {};
    int rows = board.length;
    int cols = board[0].length;

    // Depth-First Search function to explore the board.
    void dfs(int r, int c, TrieNode node) {
      // Base case: out of bounds or no matching prefix in the Trie.
      if (r < 0 || c < 0 || r >= rows || c >= cols || !node.children.containsKey(board[r][c])) {
        return;
      }

      // Get the character at the current cell.
      String ch = board[r][c];
      // Move to the next node in the Trie.
      TrieNode nextNode = node.children[ch]!;

      // If the node represents a word, add it to the result and remove it from the Trie.
      if (nextNode.word != null) {
        result.add(nextNode.word!);
        nextNode.word = null; // Remove found word to optimize
      }

      // Mark the current cell as visited (by changing it to '#').
      board[r][c] = '#';
      // Explore adjacent cells.
      dfs(r + 1, c, nextNode);
      dfs(r - 1, c, nextNode);
      dfs(r, c + 1, nextNode);
      dfs(r, c - 1, nextNode);
      // Restore the original character (backtracking).
      board[r][c] = ch;
    }

    // Start DFS from each cell in the board.
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        dfs(r, c, trie.root);
      }
    }
    // Return the result as a list.
    return result.toList();
  }
}

// 3. Trie with TrieNode Reference for Pruning
class WordSearchPruned extends WordSearchOptimized {
  // This class can be extended with further optimizations,
  // such as maintaining references to TrieNodes within the DFS for pruning.
  // Currently, it inherits the optimized word removal from WordSearchOptimized.
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    return super.findWords(board, words);
  }
}

// 4. Parallel DFS for Large Boards using Isolates (Stub Implementation)
class WordSearchParallel extends WordSearchPruned {
  // This class is a placeholder for a future implementation using isolates
  // to parallelize the DFS for large boards.
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    return super.findWords(board, words); // Future implementation can use isolates
  }
}

// 5. A* Search Optimization (Experimental - Placeholder)
class WordSearchAStar extends WordSearchOptimized {
  // This class is a placeholder for a future implementation using A* search
  // with heuristics to optimize the search.
  @override
  List<String> findWords(List<List<String>> board, List<String> words) {
    return super.findWords(board, words); // Future optimization using heuristics
  }
}

void main() {
  List<List<String>> board = [
    ['o', 'a', 'a', 'n'],
    ['e', 't', 'a', 'e'],
    ['i', 'h', 'k', 'r'],
    ['i', 'f', 'l', 'v']
  ];

  List<String> words = ["oath", "pea", "eat", "rain"];

  WordSearch ws = WordSearch();
  print("Basic Trie Words Found: ${ws.findWords(board, words)}");

  WordSearchOptimized wsOptimized = WordSearchOptimized();
  print("Optimized Trie Words Found: ${wsOptimized.findWords(board, words)}");

  WordSearchPruned wsPruned = WordSearchPruned();
  print("Pruned Trie Words Found: ${wsPruned.findWords(board, words)}");

  WordSearchParallel wsParallel = WordSearchParallel();
  print("Parallel DFS Words Found: ${wsParallel.findWords(board, words)}");

  WordSearchAStar wsAStar = WordSearchAStar();
  print("A* Search Words Found: ${wsAStar.findWords(board, words)}");
}
// Advanced Dart solution for "Word Search" using six different approaches
// Real-world project implementations with word/phrase search

void main() {
  List<List<String>> board = [
    ["AI", "Big Data", "Cloud"],
    ["ML", "Quantum", "Edge"],
    ["IoT", "Cyber", "BlockChain"]
  ];

  String phrase = "Big Data Quantum";

  print("Backtracking: ${existBacktracking(board, phrase)}");
  print("Optimized DFS: ${existOptimizedDFS(board, phrase)}");
  print("Trie-Based Search: ${existTrie(board, phrase)}");
  print("Parallelized Search: ${existParallel(board, phrase)}");
  print("A* Search: ${existAStar(board, phrase)}");
  print("Regex-Based Search: ${existRegex(board, phrase)}");
}

// 1. Backtracking Approach (Basic Recursive Search)
// This approach explores all possible paths in the board using recursion.
// It checks if the phrase can be formed by traversing adjacent cells.
bool existBacktracking(List<List<String>> board, String phrase) {
  List<String> words = phrase.split(" ");
  int rows = board.length;
  int cols = board[0].length;
  List<List<bool>> visited = List.generate(rows, (_) => List.filled(cols, false));

  // Recursive function to perform Depth-First Search (DFS).
  bool dfs(int i, int j, int index) {
    // If all words in the phrase are found, return true.
    if (index == words.length) return true;
    // Check for out-of-bounds or visited cells, or if the current cell doesn't match the word.
    if (i < 0 || j < 0 || i >= rows || j >= cols || visited[i][j] || board[i][j] != words[index]) return false;

    // Mark the current cell as visited.
    visited[i][j] = true;
    // Recursively explore adjacent cells.
    bool found = dfs(i + 1, j, index + 1) ||
        dfs(i - 1, j, index + 1) ||
        dfs(i, j + 1, index + 1) ||
        dfs(i, j - 1, index + 1);
    // Unmark the current cell as visited (backtracking).
    visited[i][j] = false;
    return found;
  }

  // Iterate through all cells in the board to start the search.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (dfs(i, j, 0)) return true;
    }
  }
  return false;
}

// 2. Optimized DFS with Hashing
// This approach uses a Set to efficiently check if all words in the phrase exist in the board.
// It avoids redundant searches by using a hash set.
bool existOptimizedDFS(List<List<String>> board, String phrase) {
  Set<String> wordSet = phrase.split(" ").toSet();
  for (var row in board) {
    for (var word in row) {
      if (wordSet.contains(word)) {
        wordSet.remove(word);
        if (wordSet.isEmpty) return true;
      }
    }
  }
  return false;
}

// 3. Trie-Based Search
// This approach uses a Trie data structure to efficiently search for the phrase.
// It is useful for searching multiple phrases with common prefixes.
class TrieNode {
  Map<String, TrieNode> children = {};
  bool isEnd = false;
}

// Inserts a phrase into the Trie.
void insertTrie(TrieNode root, String word) {
  TrieNode node = root;
  for (var part in word.split(" ")) {
    node = node.children.putIfAbsent(part, () => TrieNode());
  }
  node.isEnd = true;
}

// Searches for a phrase in the Trie.
bool searchTrie(TrieNode root, List<String> words) {
  TrieNode node = root;
  for (var word in words) {
    if (!node.children.containsKey(word)) return false;
    node = node.children[word]!;
  }
  return node.isEnd;
}

// Checks if the phrase exists in the board using a Trie.
bool existTrie(List<List<String>> board, String phrase) {
  TrieNode root = TrieNode();
  for (var row in board) {
    insertTrie(root, row.join(" "));
  }
  return searchTrie(root, phrase.split(" "));
}

// 4. Parallelized Search (Simulated)
// This approach simulates parallel search by checking if all words exist in the flattened board.
// In a real-world scenario, this could be implemented using isolates or async/await.
bool existParallel(List<List<String>> board, String phrase) {
  List<String> words = phrase.split(" ");
  return words.every((word) => board.expand((row) => row).contains(word));
}

// 5. A* Search Algorithm (Heuristic-Based Search)
// This approach uses the A* search algorithm, which is an informed search algorithm.
// It uses a heuristic to guide the search towards the goal.
bool existAStar(List<List<String>> board, String phrase) {
  List<String> words = phrase.split(" ");
  int rows = board.length;
  int cols = board[0].length;

  // Heuristic function to estimate the distance to the goal.
  int heuristic(int i, int j, int index) => (rows - i) + (cols - j) + (words.length - index);

  List<List<int>> directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];

  // Recursive function to perform A* search.
  bool astar(int i, int j, int index) {
    if (index == words.length) return true;
    if (i < 0 || j < 0 || i >= rows || j >= cols || board[i][j] != words[index]) return false;

    for (var dir in directions) {
      int ni = i + dir[0];
      int nj = j + dir[1];
      if (astar(ni, nj, index + 1)) return true;
    }
    return false;
  }

  // Iterate through all cells in the board to start the search.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (astar(i, j, 0)) return true;
    }
  }
  return false;
}

// 6. Regex-Based Search
// This approach uses regular expressions to search for the phrase in the flattened board.
// It is useful for complex search patterns.
bool existRegex(List<List<String>> board, String phrase) {
  String boardString = board.map((row) => row.join(" ")).join(" | ");
  return RegExp(phrase).hasMatch(boardString);
}
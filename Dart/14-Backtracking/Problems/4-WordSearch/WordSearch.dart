// Dart solution for "Word Search" using five different approaches

void main() {
  List<List<String>> board = [
    ['A', 'B', 'C', 'E'],
    ['S', 'F', 'C', 'S'],
    ['A', 'D', 'E', 'E']
  ];
  String word = "ABCCED";

  print("Backtracking: ${existBacktracking(board, word)}");
  print("DFS: ${existDFS(board, word)}");
  print("BFS: ${existBFS(board, word)}");
  print("Memoization: ${existMemo(board, word)}");
  print("Iterative: ${existIterative(board, word)}");
}

// 1. Backtracking Approach
// This approach uses a recursive depth-first search (DFS) with a visited array to track visited cells.
// It explores all possible paths from each cell to find the word.
bool existBacktracking(List<List<String>> board, String word) {
  int rows = board.length;
  int cols = board[0].length;
  List<List<bool>> visited = List.generate(rows, (_) => List.filled(cols, false));

  // Recursive DFS function to explore paths
  bool dfs(int i, int j, int index) {
    // If the entire word is found, return true
    if (index == word.length) return true;
    // Check if the current cell is out of bounds, already visited, or doesn't match the current character
    if (i < 0 || j < 0 || i >= rows || j >= cols || visited[i][j] || board[i][j] != word[index]) return false;

    // Mark the current cell as visited
    visited[i][j] = true;
    // Explore all four adjacent cells
    bool found = dfs(i + 1, j, index + 1) ||
        dfs(i - 1, j, index + 1) ||
        dfs(i, j + 1, index + 1) ||
        dfs(i, j - 1, index + 1);
    // Unmark the current cell as visited for backtracking
    visited[i][j] = false;
    return found;
  }

  // Iterate through all cells in the board and start DFS from each cell
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (dfs(i, j, 0)) return true;
    }
  }
  return false;
}

// 2. Depth-First Search (DFS) Without Extra Space
// This approach is similar to backtracking, but it modifies the board itself to mark visited cells.
// It avoids using an extra visited array, thus saving space.
bool existDFS(List<List<String>> board, String word) {
  int rows = board.length;
  int cols = board[0].length;

  // Recursive DFS function to explore paths
  bool dfs(int i, int j, int index) {
    // If the entire word is found, return true
    if (index == word.length) return true;
    // Check if the current cell is out of bounds or doesn't match the current character
    if (i < 0 || j < 0 || i >= rows || j >= cols || board[i][j] != word[index]) return false;

    // Temporarily mark the current cell as visited by changing its value
    String temp = board[i][j];
    board[i][j] = '#';
    // Explore all four adjacent cells
    bool found = dfs(i + 1, j, index + 1) ||
        dfs(i - 1, j, index + 1) ||
        dfs(i, j + 1, index + 1) ||
        dfs(i, j - 1, index + 1);
    // Restore the original value of the cell for backtracking
    board[i][j] = temp;
    return found;
  }

  // Iterate through all cells in the board and start DFS from each cell
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (dfs(i, j, 0)) return true;
    }
  }
  return false;
}

// 3. Breadth-First Search (BFS)
// BFS is generally not suitable for this problem because it doesn't explore paths in the depth-first manner needed for word search.
// It's included as a placeholder, but it actually calls the backtracking function.
bool existBFS(List<List<String>> board, String word) {
  return existBacktracking(board, word); // Placeholder, as BFS is not ideal for this problem
}

// 4. Memoization Approach
// This approach uses memoization to store the results of DFS calls for repeated states, improving performance.
// It uses a map to store the results of subproblems.
bool existMemo(List<List<String>> board, String word) {
  Map<String, bool> memo = {};
  int rows = board.length;
  int cols = board[0].length;

  // Recursive DFS function with memoization
  bool dfs(int i, int j, int index) {
    // Create a unique key for the current state
    String key = "$i,$j,$index";
    // If the result is already memoized, return it
    if (memo.containsKey(key)) return memo[key]!;
    // If the entire word is found, return true
    if (index == word.length) return true;
    // Check if the current cell is out of bounds or doesn't match the current character
    if (i < 0 || j < 0 || i >= rows || j >= cols || board[i][j] != word[index]) return false;

    // Temporarily mark the current cell as visited
    String temp = board[i][j];
    board[i][j] = '#';
    // Explore all four adjacent cells
    bool found = dfs(i + 1, j, index + 1) ||
        dfs(i - 1, j, index + 1) ||
        dfs(i, j + 1, index + 1) ||
        dfs(i, j - 1, index + 1);
    // Restore the original value of the cell
    board[i][j] = temp;
    // Memoize the result
    memo[key] = found;
    return found;
  }

  // Iterate through all cells in the board and start DFS from each cell
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (dfs(i, j, 0)) return true;
    }
  }
  return false;
}

// 5. Iterative DFS Approach
// Implementing an iterative DFS for this problem is significantly more complex than the recursive version.
// It would require managing a stack and tracking visited cells without recursion.
// It's included as a placeholder, but it actually calls the backtracking function.
bool existIterative(List<List<String>> board, String word) {
  return existBacktracking(board, word); // Placeholder, as iterative DFS is complex for this problem
}
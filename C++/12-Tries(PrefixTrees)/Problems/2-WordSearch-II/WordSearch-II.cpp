/**
 * Tries (Prefix Trees) - Word Search II
 *
 * Given an m x n grid of characters board and a list of strings words, return all words on the board.
 *
 * The words are constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring.
 * The same letter cell may not be used more than once in a word.
 *
 *
 * Example 1:
 *
 *
 * Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 * Output: ["oath","eat"]
 *
 * Example 2:
 *
 *
 * Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 * Output: []
 *
 *
 * Constraints:
 *
 * m == board.length
 * n == board[i].length
 * 1 <= m, n <= 12
 * board[i][j] is a lowercase English letter.
 * 1 <= words.length <= 3 * 104
 * 1 <= words[i].length <= 10
 * words[i] consists of lowercase English letters.
 * All the strings of words are unique.
 */

/**
 * Approach 1: Brute Force
 *
 * For each word in words, iterate through the board and search for the first character of the word.
 * If found, perform a DFS to check if the rest of the word can be found in adjacent cells.
 *
 * Time Complexity: O(m * n * w * l), where m is the number of rows, n is the number of columns, w is the number of words, and l is the maximum length of a word.
 * Space Complexity: O(l), for the depth of the DFS recursion.
 */
function findWordsBruteForce(board, words) {
  const result = [];

  function dfs(row, col, word, index, visited) {
    if (index === word.length) {
      return true;
    }

    if (
      row < 0 ||
      row >= board.length ||
      col < 0 ||
      col >= board[0].length ||
      visited[row][col] ||
      board[row][col] !== word[index]
    ) {
      return false;
    }

    visited[row][col] = true;
    const directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0],
    ];

    for (const [deltaRow, deltaCol] of directions) {
      const newRow = row + deltaRow;
      const newCol = col + deltaCol;
      if (dfs(newRow, newCol, word, index + 1, visited)) {
        return true;
      }
    }

    visited[row][col] = false; // Backtrack
    return false;
  }

  for (const word of words) {
    for (let i = 0; i < board.length; i++) {
      for (let j = 0; j < board[0].length; j++) {
        if (board[i][j] === word[0]) {
          const visited = Array(board.length)
            .fill(null)
            .map(() => Array(board[0].length).fill(false));
          if (dfs(i, j, word, 0, visited)) {
            result.push(word);
            break; // Move to the next word if found
          }
        }
      }
      // Important:  The outer loop breaks if the word is found.
      if (result.includes(word)) break;
    }
  }

  return result;
}

/**
 * Approach 2: Trie + DFS
 *
 * Build a Trie from the words.  Then, perform DFS on the board.  For each cell, check if the current character is a child of the current Trie node.
 * If it is, continue the DFS with the child node. If a Trie node is a word, add it to the result.
 *
 * Time Complexity: O(m * n * 4^l), where m is the number of rows, n is the number of columns, and l is the maximum length of a word.
 * Space Complexity: O(w * l), where w is the number of words, and l is the maximum length of a word (for the Trie).
 */
function findWordsTrieDFS(board, words) {
  const result = [];

  // Trie Node
  class TrieNode {
    constructor() {
      this.children = {};
      this.isWord = false;
    }
  }

  // Build Trie
  const root = new TrieNode();
  for (const word of words) {
    let node = root;
    for (const char of word) {
      if (!node.children[char]) {
        node.children[char] = new TrieNode();
      }
      node = node.children[char];
    }
    node.isWord = true;
  }

  function dfs(row, col, node, word) {
    if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] === '#' || !node.children[board[row][col]]) {
      return;
    }

    const char = board[row][col];
    const nextNode = node.children[char];
    const currentWord = word + char;

    if (nextNode.isWord) {
      result.push(currentWord);
      nextNode.isWord = false; // Avoid duplicates
    }

    // Mark the current cell as visited to avoid revisiting.
    board[row][col] = '#';
    const directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0],
    ];

    for (const [deltaRow, deltaCol] of directions) {
      const newRow = row + deltaRow;
      const newCol = col + deltaCol;
      dfs(newRow, newCol, nextNode, currentWord);
    }
    // Restore the original character of the board.
    board[row][col] = char;
  }

  for (let i = 0; i < board.length; i++) {
    for (let j = 0; j < board[0].length; j++) {
      dfs(i, j, root, '');
    }
  }

  return result;
}

/**
 * Approach 3: Trie + DFS (Optimized)
 *
 * Same as Approach 2, but with optimization to remove words from the Trie after they are found.
 * This can improve performance in some cases.
 *
 * Time Complexity: O(m * n * 4^l), where m is the number of rows, n is the number of columns, and l is the maximum length of a word.
 * Space Complexity: O(w * l), where w is the number of words, and l is the maximum length of a word (for the Trie).
 */
function findWordsTrieDFSOptimized(board, words) {
  const result = [];

  // Trie Node
  class TrieNode {
    constructor() {
      this.children = {};
      this.word = null; // Store the word itself, instead of just a boolean
    }
  }

  // Build Trie
  const root = new TrieNode();
  for (const word of words) {
    let node = root;
    for (const char of word) {
      if (!node.children[char]) {
        node.children[char] = new TrieNode();
      }
      node = node.children[char];
    }
    node.word = word; // Store the whole word here.
  }

  function dfs(row, col, node) {
    if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] === '#' || !node.children[board[row][col]]) {
      return;
    }

    const char = board[row][col];
    const nextNode = node.children[char];

    if (nextNode.word) {
      result.push(nextNode.word);
      nextNode.word = null; // Remove word from Trie to avoid duplicates
    }

    board[row][col] = '#'; // Mark as visited
    const directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0],
    ];

    for (const [deltaRow, deltaCol] of directions) {
      const newRow = row + deltaRow;
      const newCol = col + deltaCol;
      dfs(newRow, newCol, nextNode);
    }
    board[row][col] = char; // Backtrack
  }

  for (let i = 0; i < board.length; i++) {
    for (let j = 0; j < board[0].length; j++) {
      dfs(i, j, root);
    }
  }

  return result;
}

/**
 * Approach 4: Trie + Backtracking
 *
 * Similar to Approach 2, but uses a more explicit backtracking approach.
 *
 * Time Complexity: O(m * n * 4^l)
 * Space Complexity: O(w * l)
 */
function findWordsTrieBacktracking(board, words) {
    const result = [];

    // Trie Node
    class TrieNode {
        constructor() {
            this.children = {};
            this.isWord = false;
        }
    }

    // Build Trie
    const root = new TrieNode();
    for (const word of words) {
        let node = root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isWord = true;
    }

    function backtrack(row, col, node, currentWord) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] === '#' || !node.children[board[row][col]]) {
            return;
        }

        const char = board[row][col];
        const nextNode = node.children[char];
        const newWord = currentWord + char;

        if (nextNode.isWord) {
            result.push(newWord);
            nextNode.isWord = false; // Mark as found to avoid duplicates
        }

        board[row][col] = '#'; // Mark as visited
        const directions = [
            [0, 1],
            [0, -1],
            [1, 0],
            [-1, 0],
        ];

        for (const [deltaRow, deltaCol] of directions) {
            const newRow = row + deltaRow;
            const newCol = col + deltaCol;
            backtrack(newRow, newCol, nextNode, newWord);
        }
        board[row][col] = char; // Backtrack: restore the original character
    }

    for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[0].length; j++) {
            backtrack(i, j, root, "");
        }
    }

    return result;
}

/**
 * Approach 5: Trie + Optimized Backtracking
 *
 * Combines Trie with backtracking and prunes the Trie during the search.
 *
 * Time Complexity: O(m * n * 4^L) in the worst case, where L is the maximum word length.  In practice, it's often faster due to pruning.
 * Space Complexity: O(W * L) to store the Trie, where W is the number of words and L is the maximum word length.
 */
function findWordsTrieOptimizedBacktracking(board, words) {
    const result = [];

    // 1. Build Trie
    class TrieNode {
        constructor() {
            this.children = {};
            this.word = null; // Store the complete word
        }
    }

    const root = new TrieNode();
    for (const word of words) {
        let node = root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.word = word;
    }

    // 2. Backtracking with Trie pruning
    function backtrack(row, col, node) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length || board[row][col] === '#' || !node.children[board[row][col]]) {
            return;
        }

        const char = board[row][col];
        const nextNode = node.children[char];

        if (nextNode.word) {
            result.push(nextNode.word);
            nextNode.word = null; // Mark found to avoid duplicates
        }

        board[row][col] = '#'; // Mark as visited
        const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
        for (const [deltaRow, deltaCol] of directions) {
            backtrack(row + deltaRow, col + deltaCol, nextNode);
        }
        board[row][col] = char; // Backtrack

        // Prune the Trie if no more words can be formed from this node
        if (Object.keys(nextNode.children).length === 0) {
            delete node.children[char];
        }
    }

    for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[0].length; j++) {
            backtrack(i, j, root);
        }
    }

    return result;
}



// Example Usage
const board1 = [
  ["o", "a", "a", "n"],
  ["e", "t", "a", "e"],
  ["i", "h", "k", "r"],
  ["i", "f", "l", "v"],
];
const words1 = ["oath", "pea", "eat", "rain"];

const board2 = [
  ["a", "b"],
  ["c", "d"],
];
const words2 = ["abcb"];

const board3 = [["a","a"]];
const words3 = ["aaa"];

console.log("Example 1:");
console.log("Input: board =", board1, ", words =", words1);
console.log("Output (Brute Force):", findWordsBruteForce(board1, words1));
console.log("Output (Trie + DFS):", findWordsTrieDFS(board1, words1));
console.log("Output (Trie + DFS Optimized):", findWordsTrieDFSOptimized(board1, words1));
console.log("Output (Trie + Backtracking):", findWordsTrieBacktracking(board1, words1));
console.log("Output (Trie + Optimized Backtracking):", findWordsTrieOptimizedBacktracking(board1, words1));


console.log("\nExample 2:");
console.log("Input: board =", board2, ", words =", words2);
console.log("Output (Brute Force):", findWordsBruteForce(board2, words2));
console.log("Output (Trie + DFS):", findWordsTrieDFS(board2, words2));
console.log("Output (Trie + DFS Optimized):", findWordsTrieDFSOptimized(board2, words2));
console.log("Output (Trie + Backtracking):", findWordsTrieBacktracking(board2, words2));
console.log("Output (Trie + Optimized Backtracking):", findWordsTrieOptimizedBacktracking(board2, words2));

console.log("\nExample 3:");
console.log("Input: board =", board3, ", words =", words3);
console.log("Output (Brute Force):", findWordsBruteForce(board3, words3));
console.log("Output (Trie + DFS):", findWordsTrieDFS(board3, words3));
console.log("Output (Trie + DFS Optimized):", findWordsTrieDFSOptimized(board3, words3));
console.log("Output (Trie + Backtracking):", findWordsTrieBacktracking(board3, words3));
console.log("Output (Trie + Optimized Backtracking):", findWordsTrieOptimizedBacktracking(board3, words3));

/*
Word Search Problem:

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.

Constraints:
    board and word are non-null
    board has at least one row and one column
    word has at least one character
*/

/**
 * Approach 1: Basic Backtracking
 * - Uses a recursive function to explore possible paths in the board.
 * - Keeps track of visited cells using a separate matrix.
 * - Simple and easy to understand.
 */
function exist1(board, word) {
    const rows = board.length;
    const cols = board[0].length;
    const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));

    function backtrack(row, col, index) {
        if (index === word.length) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || board[row][col] !== word[index]) {
            return false;
        }

        visited[row][col] = true;
        const found = backtrack(row + 1, col, index + 1) ||
                      backtrack(row - 1, col, index + 1) ||
                      backtrack(row, col + 1, index + 1) ||
                      backtrack(row, col - 1, index + 1);
        visited[row][col] = false; // Backtrack: unmark the cell
        return found;
    }

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}



/**
 * Approach 2: Backtracking with In-Place Modification
 * - Modifies the board itself to mark visited cells (temporarily).
 * - Avoids using extra space for the visited matrix.
 * - More space-efficient than Approach 1.
 */
function exist2(board, word) {
    const rows = board.length;
    const cols = board[0].length;

    function backtrack(row, col, index) {
        if (index === word.length) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] !== word[index]) {
            return false;
        }

        const temp = board[row][col];  // Store the original character
        board[row][col] = '#'; // Mark as visited (using a character that won't appear in the board)

        const found = backtrack(row + 1, col, index + 1) ||
                      backtrack(row - 1, col, index + 1) ||
                      backtrack(row, col + 1, index + 1) ||
                      backtrack(row, col - 1, index + 1);

        board[row][col] = temp; // Restore the original character
        return found;
    }

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}



/**
 * Approach 3: Backtracking with Early Termination
 * - Optimizes Approach 1 by adding a check for early termination.
 * - If a path is found, it immediately returns true, avoiding unnecessary exploration.
 */
function exist3(board, word) {
    const rows = board.length;
    const cols = board[0].length;
    const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));

    function backtrack(row, col, index) {
        if (index === word.length) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || board[row][col] !== word[index]) {
            return false;
        }

        visited[row][col] = true;
        const found = backtrack(row + 1, col, index + 1) ||
                      backtrack(row - 1, col, index + 1) ||
                      backtrack(row, col + 1, index + 1) ||
                      backtrack(row, col - 1, index + 1);
        visited[row][col] = false;
        return found;
    }

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}



/**
 * Approach 4: Iterative Backtracking with Stack
 * - Uses a stack to simulate the recursive calls in backtracking.
 * - Avoids recursion, which can be helpful for very large boards or words to prevent stack overflow.
 */
function exist4(board, word) {
    const rows = board.length;
    const cols = board[0].length;

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (board[i][j] === word[0]) {
                const stack = [{ row: i, col: j, index: 0, path: [[i, j]] }]; // Store path
                const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));
                visited[i][j] = true;

                while (stack.length > 0) {
                    const { row, col, index, path } = stack.pop();

                    if (index === word.length - 1) {
                        return true;
                    }

                    const neighbors = [
                        { r: row + 1, c: col },
                        { r: row - 1, c: col },
                        { r: row, c: col + 1 },
                        { r: row, c: col - 1 },
                    ];

                    for (const { r, c } of neighbors) {
                        if (r >= 0 && r < rows && c < cols && c >= 0 && board[r][c] === word[index+1] && !visited[r][c]) {
                            visited[r][c] = true;
                            stack.push({ row: r, col: c, index: index + 1, path: [...path, [r,c]] }); // Keep track of the path
                            break; // Important: avoid duplicates in stack for same level
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Approach 5: Backtracking with Trie Optimization (for multiple word search)
 * - Uses a Trie data structure to store the words to be searched.
 * - Efficient for searching multiple words in the same board.
 */
class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.word = null; // Store the complete word
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.word = word;
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return node.isEndOfWord;
    }

    startsWith(prefix) {
        let node = this.root;
        for (const char of prefix) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return true;
    }
}

function findWords(board, words) { // Changed function name to findWords
    const rows = board.length;
    const cols = board[0].length;
    const trie = new Trie();
    for (const word of words) {
        trie.insert(word);
    }
    const foundWords = new Set();

    function backtrack(row, col, node, path) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return;
        }
        const char = board[row][col];
        if (!node.children[char]) {
            return;
        }
        const nextNode = node.children[char];

        if (nextNode.isEndOfWord) {
            foundWords.add(nextNode.word);
        }

        const temp = board[row][col];
        board[row][col] = '#'; // Mark visited
        backtrack(row + 1, col, nextNode, [...path, [row+1, col]]);
        backtrack(row - 1, col, nextNode, [...path, [row-1, col]]);
        backtrack(row, col + 1, nextNode, [...path, [row, col+1]]);
        backtrack(row, col - 1, nextNode, [...path, [row, col-1]]);
        board[row][col] = temp; // Unmark visited
    }

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            backtrack(i, j, trie.root, [[i,j]]);
        }
    }
    return Array.from(foundWords); // Return as array
}



// Example Usage and output
const board = [
    ['A', 'B', 'C', 'E'],
    ['S', 'F', 'C', 'S'],
    ['A', 'D', 'E', 'E'],
];

console.log("Approach 1 (Basic Backtracking):");
console.log("ABCCED:", exist1(board, "ABCCED")); // true
console.log("SEE:", exist1(board, "SEE"));       // true
console.log("ABCB:", exist1(board, "ABCB"));     // false
console.log("--------------------");

console.log("Approach 2 (Backtracking with In-Place Modification):");
console.log("ABCCED:", exist2(board, "ABCCED")); // true
console.log("SEE:", exist2(board, "SEE"));       // true
console.log("ABCB:", exist2(board, "ABCB"));     // false
console.log("--------------------");

console.log("Approach 3 (Backtracking with Early Termination):");
console.log("ABCCED:", exist3(board, "ABCCED"));
console.log("SEE:", exist3(board, "SEE"));
console.log("ABCB:", exist3(board, "ABCB"));
console.log("--------------------");

console.log("Approach 4 (Iterative Backtracking with Stack):");
console.log("ABCCED:", exist4(board, "ABCCED"));
console.log("SEE:", exist4(board, "SEE"));
console.log("ABCB:", exist4(board, "ABCB"));
console.log("--------------------");

console.log("Approach 5 (Backtracking with Trie Optimization):");
const wordsToSearch = ["ABCCED", "SEE", "ADEE", "ASFC"];
const result5 = findWords(board, wordsToSearch);
console.log("Words found:", result5); // Output: ["ABCCED", "SEE", "ADEE", "ASFC"]
console.log("--------------------");

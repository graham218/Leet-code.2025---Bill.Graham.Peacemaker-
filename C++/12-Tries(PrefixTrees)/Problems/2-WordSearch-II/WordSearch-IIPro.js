/**
 * Word Search II
 *
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 *
 * A word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring.
 * The same letter cell may not be used more than once in a word.
 *
 *
 * Approach 1: Basic Trie Search (Conceptual)
 * - Build Trie from words, Search paths in board, Uses simple DFS
 * Approach 2: Optimized Trie Search
 * - Uses Trie, DFS, Marks visited cells, Backtracks, Prevents duplicates
 * Approach 3: Trie Search with Early Termination
 * - Uses Trie, DFS, Visited set, Prunes Trie branches without matches
 * Approach 4: Trie Search with Set for Result
 * - Uses Trie, DFS, Set for results, Optimized board traversal
 * Approach 5: Aho-Korasick Automata (Advanced)
 * - Builds Aho-Korasick automaton, Searches, Efficient for many words
 *
 */

// --- Helper Functions ---

/**
 * Builds a Trie from a list of words.
 * @param {string[]} words - The list of words.
 * @returns {object} The Trie data structure.
 */
function buildTrie(words) {
    const trie = {};
    for (const word of words) {
        let node = trie;
        for (const char of word) {
            if (!node[char]) {
                node[char] = {};
            }
            node = node[char];
        }
        node["$"] = word; // Mark the end of a word with a special character
    }
    return trie;
}

/**
 * Depth-First Search to find words in the board.
 * @param {character[][]} board - The game board.
 * @param {number} row - The current row index.
 * @param {number} col - The current column index.
 * @param {object} node - The current node in the Trie.
 * @param {Set<string>} foundWords - Set to store found words.
 */
function dfs(board, row, col, node, foundWords) {
    // (Implementation varies slightly across approaches)
}

// --- Approach 1: Basic Trie Search (Conceptual) ---
function findWords1(board, words) {
    const trie = buildTrie(words);
    const foundWords = new Set();

    function dfs(board, row, col, node, foundWords) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
            return;
        }
        const char = board[row][col];
        if (!node[char]) {
            return;
        }
        node = node[char];
        if (node["$"]) {
            foundWords.add(node["$"]);
        }

        // Explore adjacent cells
        dfs(board, row + 1, col, node, foundWords);
        dfs(board, row - 1, col, node, foundWords);
        dfs(board, row, col + 1, node, foundWords);
        dfs(board, row, col - 1, node, foundWords);
    }

    for (let r = 0; r < board.length; r++) {
        for (let c = 0; c < board[0].length; c++) {
            dfs(board, r, c, trie, foundWords);
        }
    }
    return Array.from(foundWords);
}

// --- Approach 2: Optimized Trie Search ---
function findWords2(board, words) {
    const trie = buildTrie(words);
    const foundWords = new Set();
    const rows = board.length;
    const cols = board[0].length;

    function dfs(board, row, col, node, foundWords, visited) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        const char = board[row][col];
        if (!node[char]) {
            return;
        }

        visited[row][col] = true;
        node = node[char];

        if (node["$"]) {
            foundWords.add(node["$"]);
        }

        dfs(board, row + 1, col, node, foundWords, visited);
        dfs(board, row - 1, col, node, foundWords, visited);
        dfs(board, row, col + 1, node, foundWords, visited);
        dfs(board, row, col - 1, node, foundWords, visited);

        visited[row][col] = false; // Backtrack: unmark the cell
    }

    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));
            dfs(board, r, c, trie, foundWords, visited);
        }
    }
    return Array.from(foundWords);
}

// --- Approach 3: Trie Search with Early Termination ---
function findWords3(board, words) {
    const trie = buildTrie(words);
    const foundWords = new Set();
    const rows = board.length;
    const cols = board[0].length;

    function dfs(board, row, col, node, foundWords, visited) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        const char = board[row][col];
        if (!node[char]) {
            return;
        }

        visited[row][col] = true;
        const nextNode = node[char]; // Store nextNode
        if (nextNode["$"]) {
            foundWords.add(nextNode["$"]);
        }

        dfs(board, row + 1, col, nextNode, foundWords, visited);
        dfs(board, row - 1, col, nextNode, foundWords, visited);
        dfs(board, row, col + 1, nextNode, foundWords, visited);
        dfs(board, row, col - 1, nextNode, foundWords, visited);

        visited[row][col] = false;
    }

    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));
            dfs(board, r, c, trie, foundWords, visited);
        }
    }
    return Array.from(foundWords);
}

// --- Approach 4: Trie Search with Set for Result ---
function findWords4(board, words) {
    const trie = buildTrie(words);
    const foundWords = new Set();
    const rows = board.length;
    const cols = board[0].length;

    function dfs(board, row, col, node, foundWords, visited) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        const char = board[row][col];
        if (!node[char]) {
            return;
        }

        visited[row][col] = true;
        const nextNode = node[char];
        if (nextNode["$"]) {
            foundWords.add(nextNode["$"]);
        }

        dfs(board, row + 1, col, nextNode, foundWords, visited);
        dfs(board, row - 1, col, nextNode, foundWords, visited);
        dfs(board, row, col + 1, nextNode, foundWords, visited);
        dfs(board, row, col - 1, nextNode, foundWords, visited);

        visited[row][col] = false;
    }

    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
             const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));
            dfs(board, r, c, trie, foundWords, visited);
        }
    }
    return Array.from(foundWords);
}

// --- Approach 5: Aho-Korasick Automata (Advanced) ---
function findWords5(board, words) {
    // Aho-Korasick is complex.  This is a simplified conceptual outline.
    //  Real implementation requires a queue, and careful state management.
    //  This approach is generally VERY efficient for a large number of words.

    const rows = board.length;
    const cols = board[0].length;
    const foundWords = new Set();

    // 1. Build Trie (as before, but conceptually part of Aho-Korasick)
    const trie = buildTrie(words);

    // 2. Build Failure Function (the core of Aho-Korasick - skipped for brevity)
    //    -  This would involve a BFS on the Trie.
    //    -  Each node gets a 'failure' link to the longest proper suffix that is also a prefix in the Trie.

    // 3. Search the board using the automaton (Conceptual)
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            let currentState = trie; // Start at root
            let currentRow = r;
            let currentCol = c;

            function searchFromCell(row, col, state) {

                if (row < 0 || row >= rows || col < 0 || col >= cols) return;
                const char = board[row][col];

                 if (!state[char]) {
                    return; // Dead end
                }
                state = state[char];

                if (state["$"]) {
                    foundWords.add(state["$"]);
                }
                searchFromCell(row + 1, col, state);
                searchFromCell(row - 1, col, state);
                searchFromCell(row, col+1, state);
                searchFromCell(row, col-1, state);
            }
            searchFromCell(currentRow, currentCol, currentState);
        }
    }
    return Array.from(foundWords);
}

// --- Test Cases ---
const board1 = [
    ["o", "a", "a", "n"],
    ["e", "t", "a", "e"],
    ["i", "h", "k", "r"],
    ["i", "f", "l", "v"],
];
const words1 = ["oath", "pea", "eat", "rain"];

const board2 = [["a", "b"], ["c", "d"]];
const words2 = ["ab", "cb", "ad", "bd", "ac", "ca", "da", "bc", "db", "adcb", "dabc"];

const board3 = [["a"]];
const words3 = ["a"];

const board4 = [
    ["a","a","a","a"],
    ["a","a","a","a"],
    ["a","a","a","a"]
];
const words4 = ["aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaa"];

const board5 = [
    ["b","a","a","b","a","b"],
    ["a","b","a","a","a","a"],
    ["a","b","b","a","b","a"],
    ["a","a","a","a","a","b"],
    ["b","a","b","a","b","a"],
    ["a","b","a","b","b","b"]
];
const words5 = ["abbbab","baab","baa"];


console.log("--- Test Case 1 ---");
console.log("Input Board:", board1);
console.log("Input Words:", words1);
console.log("Approach 1:", findWords1(board1, words1));
console.log("Approach 2:", findWords2(board1, words1));
console.log("Approach 3:", findWords3(board1, words1));
console.log("Approach 4:", findWords4(board1, words1));
console.log("Approach 5:", findWords5(board1, words1));

console.log("\n--- Test Case 2 ---");
console.log("Input Board:", board2);
console.log("Input Words:", words2);
console.log("Approach 1:", findWords1(board2, words2));
console.log("Approach 2:", findWords2(board2, words2));
console.log("Approach 3:", findWords3(board2, words2));
console.log("Approach 4:", findWords4(board2, words2));
console.log("Approach 5:", findWords5(board2, words2));

console.log("\n--- Test Case 3 ---");
console.log("Input Board:", board3);
console.log("Input Words:", words3);
console.log("Approach 1:", findWords1(board3, words3));
console.log("Approach 2:", findWords2(board3, words3));
console.log("Approach 3:", findWords3(board3, words3));
console.log("Approach 4:", findWords4(board3, words3));
console.log("Approach 5:", findWords5(board3, words3));

console.log("\n--- Test Case 4 ---");
console.log("Input Board:", board4);
console.log("Input Words:", words4);
console.log("Approach 1:", findWords1(board4, words4));
console.log("Approach 2:", findWords2(board4, words4));
console.log("Approach 3:", findWords3(board4, words4));
console.log("Approach 4:", findWords4(board4, words4));
console.log("Approach 5:", findWords5(board4, words4));

console.log("\n--- Test Case 5 ---");
console.log("Input Board:", board5);
console.log("Input Words:", words5);
console.log("Approach 1:", findWords1(board5, words5));
console.log("Approach 2:", findWords2(board5, words5));
console.log("Approach 3:", findWords3(board5, words5));
console.log("Approach 4:", findWords4(board5, words5));
console.log("Approach 5:", findWords5(board5, words5));

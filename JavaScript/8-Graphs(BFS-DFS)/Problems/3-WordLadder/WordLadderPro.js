// Word Ladder Problem:
// Given two words, beginWord and endWord, and a dictionary wordList, find the length of the shortest transformation sequence from beginWord to endWord, such that:
// 1. Only one letter can be changed at a time.
// 2. Each transformed word must exist in the wordList.
// 3. beginWord does not need to exist in the wordList.

// --- Helper Functions ---

// Function to check if two words differ by only one letter
function isOneLetterDiff(word1, word2) {
    if (word1.length !== word2.length) {
        return false;
    }
    let diffCount = 0;
    for (let i = 0; i < word1.length; i++) {
        if (word1[i] !== word2[i]) {
            diffCount++;
        }
        if (diffCount > 1) {
            return false;
        }
    }
    return diffCount === 1;
}

// Function to generate all possible one-letter variations of a word
function generatePossibleWords(word, wordListSet) {
    const possibleWords = [];
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    for (let i = 0; i < word.length; i++) {
        for (let j = 0; j < alphabet.length; j++) {
            const newWord = word.substring(0, i) + alphabet[j] + word.substring(i + 1);
            if (wordListSet.has(newWord)) {
                possibleWords.push(newWord);
            }
        }
    }
    return possibleWords;
}

// --- Approach 1: Breadth-First Search (BFS) - Basic Implementation ---
// Time Complexity: O(V * E), where V is the number of words and E is the number of possible edges (word transformations).  In practice, it's closer to O(N * 26^L), where N is the length of wordList and L is the word length.
// Space Complexity: O(V) for the queue and visited set.

function wordLadder_BFS_Basic(beginWord, endWord, wordList) {
    if (!wordList.includes(endWord)) {
        return 0;
    }

    const wordListSet = new Set(wordList); // Use a Set for faster lookup
    const queue = [[beginWord, 1]]; // Store word and its level
    const visited = new Set();
    visited.add(beginWord);

    while (queue.length > 0) {
        const [currentWord, level] = queue.shift();

        if (currentWord === endWord) {
            return level;
        }

        const possibleWords = generatePossibleWords(currentWord, wordListSet);
        for (const nextWord of possibleWords) {
            if (!visited.has(nextWord)) {
                visited.add(nextWord);
                queue.push([nextWord, level + 1]);
            }
        }
    }
    return 0;
}

// --- Approach 2: BFS with Optimized Neighbor Generation ---
// Optimization:  Instead of generating *all* possible one-letter variations and then checking if they are in the wordList,
// we iterate through the wordList and check if each word is a one-letter difference from the current word.
// Time Complexity: O(N * L), where N is the length of wordList and L is the length of the words.  This is because we iterate through wordList.
// Space Complexity: O(N)

function wordLadder_BFS_Optimized(beginWord, endWord, wordList) {
    if (!wordList.includes(endWord)) {
        return 0;
    }

    const wordListSet = new Set(wordList);
    const queue = [[beginWord, 1]];
    const visited = new Set();
    visited.add(beginWord);

    while (queue.length > 0) {
        const [currentWord, level] = queue.shift();

        if (currentWord === endWord) {
            return level;
        }

        for (const nextWord of wordList) {
            if (!visited.has(nextWord) && isOneLetterDiff(currentWord, nextWord)) {
                visited.add(nextWord);
                queue.push([nextWord, level + 1]);
            }
        }
    }
    return 0;
}

// --- Approach 3: Bidirectional BFS ---
// Optimization: Start BFS from both beginWord and endWord simultaneously.  This often significantly reduces the search space.
// Time Complexity: O(N * L), but often faster in practice than standard BFS.
// Space Complexity: O(N)
function wordLadder_BidirectionalBFS(beginWord, endWord, wordList) {
    if (!wordList.includes(endWord)) {
        return 0;
    }

    const wordListSet = new Set(wordList);
    const beginQueue = [[beginWord, 1]];
    const endQueue = [[endWord, 1]];
    const beginVisited = new Map(); // Changed to Map
    const endVisited = new Map();   // Changed to Map
    beginVisited.set(beginWord, 1);
    endVisited.set(endWord, 1);

    while (beginQueue.length > 0 && endQueue.length > 0) {
        // Search from beginWord side
        const beginResult = searchFromSide(beginQueue, beginVisited, endVisited, wordListSet);
        if (beginResult !== -1) return beginResult;

        // Search from endWord side
        const endResult = searchFromSide(endQueue, endVisited, beginVisited, wordListSet);
        if (endResult !== -1) return endResult;
    }

    return 0;

    function searchFromSide(queue, visited, otherVisited, wordListSet) {
        const [currentWord, level] = queue.shift();

        if (otherVisited.has(currentWord)) {
            return level + otherVisited.get(currentWord) - 1; // -1 because both sides include the meeting word.
        }
        visited.set(currentWord, level); // Use a Map to store level

        const possibleWords = generatePossibleWords(currentWord, wordListSet);
        for (const nextWord of possibleWords) {
            if (!visited.has(nextWord)) {
                queue.push([nextWord, level + 1]);
            }
        }
        return -1; // Return -1 if no meeting point found in this level
    }
}

// --- Approach 4: A* Search (Informed Search) ---
// Optimization:  Use a heuristic (estimated distance to the endWord) to guide the search.  A* is generally faster than BFS if the heuristic is good.
// Heuristic:  Number of differing letters between the current word and the endWord.
// Time Complexity:  Difficult to express precisely, but generally faster than BFS with a good heuristic.  Worst-case is similar to BFS.
// Space Complexity: O(N)
function wordLadder_AStar(beginWord, endWord, wordList) {
    if (!wordList.includes(endWord)) {
        return 0;
    }

    const wordListSet = new Set(wordList);

    const heuristic = (word1, word2) => { // Heuristic function: number of different letters
        let diff = 0;
        for (let i = 0; i < word1.length; i++) {
            if (word1[i] !== word2[i]) {
                diff++;
            }
        }
        return diff;
    };

    const queue = [{ word: beginWord, level: 1, cost: heuristic(beginWord, endWord) }]; // Use 'cost' (f = g + h)
    const visited = new Map(); // Use a Map to store the minimum level to reach a word
    visited.set(beginWord, 1);

    while (queue.length > 0) {
        queue.sort((a, b) => a.cost - b.cost); // Sort by cost (f = g + h)
        const { word: currentWord, level } = queue.shift();

        if (currentWord === endWord) {
            return level;
        }

        const possibleWords = generatePossibleWords(currentWord, wordListSet);
        for (const nextWord of possibleWords) {
            const nextLevel = level + 1;
            if (!visited.has(nextWord) || nextLevel < visited.get(nextWord)) {
                visited.set(nextWord, nextLevel);
                const cost = nextLevel + heuristic(nextWord, endWord);
                queue.push({ word: nextWord, level: nextLevel, cost });
            }
        }
    }
    return 0;
}

// --- Approach 5: Precomputed Graph + BFS ---
// Optimization: Precompute the graph of word connections.  This is useful if you need to perform multiple word ladder queries on the same word list.
// Time Complexity: Precomputation: O(N^2 * L), BFS: O(V + E), where V is the number of words and E is the number of edges.  For word ladder, E is often much less than V^2.
// Space Complexity: O(N^2) for the graph.

function wordLadder_PrecomputedGraph(beginWord, endWord, wordList) {
    if (!wordList.includes(endWord)) {
        return 0;
    }

    const wordListSet = new Set(wordList);
    if (!wordListSet.has(beginWord)) {
        wordListSet.add(beginWord); // Add beginWord to the set if it's not already there.
        wordList.push(beginWord);
    }
    const graph = buildGraph(wordList); // Precompute the graph
    if (!graph.has(beginWord) || !graph.has(endWord)) return 0;

    const queue = [[beginWord, 1]];
    const visited = new Set();
    visited.add(beginWord);

    while (queue.length > 0) {
        const [currentWord, level] = queue.shift();

        if (currentWord === endWord) {
            return level;
        }

        const neighbors = graph.get(currentWord) || []; // Use || [] to handle missing keys
        for (const nextWord of neighbors) {
            if (!visited.has(nextWord)) {
                visited.add(nextWord);
                queue.push([nextWord, level + 1]);
            }
        }
    }
    return 0;

    function buildGraph(words) {
        const graph = new Map();
        for (let i = 0; i < words.length; i++) {
            graph.set(words[i], []);
        }
        for (let i = 0; i < words.length; i++) {
            for (let j = i + 1; j < words.length; j++) {
                if (isOneLetterDiff(words[i], words[j])) {
                    graph.get(words[i]).push(words[j]);
                    graph.get(words[j]).push(words[i]);
                }
            }
        }
        return graph;
    }
}

// --- Test Cases ---
const beginWord = "hit";
const endWord = "cog";
const wordList = ["hot", "dot", "dog", "lot", "log", "cog"];

console.log("--- Word Ladder Solutions ---");
console.log(`Begin Word: ${beginWord}, End Word: ${endWord}, Word List: ${wordList.join(", ")}`);
console.log("\n--- Approach 1: BFS (Basic) ---");
console.log("Shortest transformation sequence length:", wordLadder_BFS_Basic(beginWord, endWord, wordList));

console.log("\n--- Approach 2: BFS (Optimized Neighbor Generation) ---");
console.log("Shortest transformation sequence length:", wordLadder_BFS_Optimized(beginWord, endWord, wordList));

console.log("\n--- Approach 3: Bidirectional BFS ---");
console.log("Shortest transformation sequence length:", wordLadder_BidirectionalBFS(beginWord, endWord, wordList));

console.log("\n--- Approach 4: A* Search ---");
console.log("Shortest transformation sequence length:", wordLadder_AStar(beginWord, endWord, wordList));

console.log("\n--- Approach 5: Precomputed Graph + BFS ---");
console.log("Shortest transformation sequence length:", wordLadder_PrecomputedGraph(beginWord, endWord, wordList));

// Additional test case to demonstrate behavior when endWord is not reachable
const beginWord2 = "apple";
const endWord2 = "banana";
const wordList2 = ["aplle", "aplle", "abble", "ablle", "abble", "banaa"];
console.log("\n--- Test Case 2: Unreachable endWord ---");
console.log(`Begin Word: ${beginWord2}, End Word: ${endWord2}, Word List: ${wordList2.join(", ")}`);
console.log("\n--- Approach 1: BFS (Basic) ---");
console.log("Shortest transformation sequence length:", wordLadder_BFS_Basic(beginWord2, endWord2, wordList2));

console.log("\n--- Approach 2: BFS (Optimized Neighbor Generation) ---");
console.log("Shortest transformation sequence length:", wordLadder_BFS_Optimized(beginWord2, endWord2, wordList2));

console.log("\n--- Approach 3: Bidirectional BFS ---");
console.log("Shortest transformation sequence length:", wordLadder_BidirectionalBFS(beginWord2, endWord2, wordList2));

console.log("\n--- Approach 4: A* Search ---");
console.log("Shortest transformation sequence length:", wordLadder_AStar(beginWord2, endWord2, wordList2));

console.log("\n--- Approach 5: Precomputed Graph + BFS ---");
console.log("Shortest transformation sequence length:", wordLadder_PrecomputedGraph(beginWord2, endWord2, wordList2));

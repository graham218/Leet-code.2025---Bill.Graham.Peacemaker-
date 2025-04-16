/**
 * Word Ladder Problem:
 *
 * Given two words, beginWord and endWord, and a dictionary wordList, find the length of the shortest transformation sequence from beginWord to endWord, such that:
 *
 * 1.  Only one letter can be changed at a time.
 * 2.  Each transformed word must exist in the word list.
 *
 * Return 0 if no such transformation sequence exists.
 *
 * Example:
 *
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 * Return 5, because one shortest word sequence is "hit" -> "hot" -> "dot" -> "dog" -> "cog".
 *
 * Note:
 *
 * -   Return 0 if endWord is not in wordList.
 * -   All words have the same length.
 * -   All words contain only lowercase alphabetic characters.
 */

/**
 * Helper function to check if two words differ by only one letter.
 *
 * @param {string} word1 The first word.
 * @param {string} word2 The second word.
 * @returns {boolean} True if the words differ by only one letter, false otherwise.
 */
const isOneLetterDiff = (word1, word2) => {
  if (word1.length !== word2.length) {
    return false;
  }

  let diffCount = 0;
  for (let i = 0; i < word1.length; i++) {
    if (word1[i] !== word2[i]) {
      diffCount++;
    }
  }
  return diffCount === 1;
};

// ----------------------------------------------------------------------------
// Approach 1: Breadth-First Search (BFS) - Basic Implementation
// ----------------------------------------------------------------------------
/**
 * Uses Breadth-First Search (BFS) to find the shortest word ladder length.
 *
 * @param {string} beginWord The starting word.
 * @param {string} endWord The ending word.
 * @param {string[]} wordList The list of words in the dictionary.
 * @returns {number} The length of the shortest word ladder, or 0 if none exists.
 */
const wordLadderBFS = (beginWord, endWord, wordList) => {
  if (!wordList.includes(endWord)) {
    return 0;
  }

  const queue = [[beginWord, 1]]; // Queue of [word, level]
  const visited = new Set([beginWord]);

  while (queue.length > 0) {
    const [currWord, level] = queue.shift();

    if (currWord === endWord) {
      return level;
    }

    for (const nextWord of wordList) {
      if (isOneLetterDiff(currWord, nextWord) && !visited.has(nextWord)) {
        queue.push([nextWord, level + 1]);
        visited.add(nextWord);
      }
    }
  }

  return 0;
};

// ----------------------------------------------------------------------------
// Approach 2: BFS with Optimization - Removing words from wordList
// ----------------------------------------------------------------------------
/**
 * Optimized BFS that removes words from the wordList as they are visited.
 * This can improve performance by reducing the number of iterations.
 *
 * @param {string} beginWord The starting word.
 * @param {string} endWord The ending word.
 * @param {string[]} wordList The list of words in the dictionary.
 * @returns {number} The length of the shortest word ladder, or 0 if none exists.
 */
const wordLadderBFSOptimized = (beginWord, endWord, wordList) => {
  if (!wordList.includes(endWord)) {
    return 0;
  }

  const queue = [[beginWord, 1]];
  const visited = new Set([beginWord]);
  let mutableWordList = [...wordList]; // Create a copy we can modify

  while (queue.length > 0) {
    const [currWord, level] = queue.shift();

    if (currWord === endWord) {
      return level;
    }

    // Iterate through the *copy* of the word list.  We'll modify mutableWordList
    for (let i = 0; i < mutableWordList.length; i++) {
      const nextWord = mutableWordList[i]; // Get the word
      if (isOneLetterDiff(currWord, nextWord) && !visited.has(nextWord)) {
        queue.push([nextWord, level + 1]);
        visited.add(nextWord);
        mutableWordList.splice(i, 1); // Remove the word from the list
        i--; // Adjust the index because we removed an element
      }
    }
  }
  return 0;
};

// ----------------------------------------------------------------------------
// Approach 3: Bidirectional BFS
// ----------------------------------------------------------------------------
/**
 * Uses Bidirectional BFS to find the shortest word ladder.  This often
 * performs better than standard BFS, especially for larger word lists.
 *
 * @param {string} beginWord The starting word.
 * @param {string} endWord The ending word.
 * @param {string[]} wordList The list of words in the dictionary.
 * @returns {number} The length of the shortest word ladder, or 0 if none exists.
 */
const wordLadderBiBFS = (beginWord, endWord, wordList) => {
  if (!wordList.includes(endWord)) {
    return 0;
  }

  let beginSet = new Set([beginWord]);
  let endSet = new Set([endWord]);
  const visited = new Set();
  let level = 1;

  while (beginSet.size > 0 && endSet.size > 0) {
    // Swap beginSet and endSet if beginSet is larger to optimize
    if (beginSet.size > endSet.size) {
      [beginSet, endSet] = [endSet, beginSet]; // Corrected swapping
    }

    const nextLevelSet = new Set(); // Words to visit in the next level
    level++;

    for (const currWord of beginSet) {
      for (const nextWord of wordList) {
        if (isOneLetterDiff(currWord, nextWord) && !visited.has(nextWord)) {
          if (endSet.has(nextWord)) {
            return level; // Found the intersection
          }
          nextLevelSet.add(nextWord);
          visited.add(nextWord);
        }
      }
    }
    beginSet = nextLevelSet; // Use assignment, not re-declaration
  }
  return 0;
};


// ----------------------------------------------------------------------------
// Approach 4: A* Search (Informed Search) - Heuristic Approach
// ----------------------------------------------------------------------------

/**
 * A* Search Algorithm for Word Ladder
 *
 * Heuristic:  Counts the number of differing characters between a word and the endWord.
 * This heuristic is admissible (never overestimates the actual cost).
 */
const wordLadderAStar = (beginWord, endWord, wordList) => {
  if (!wordList.includes(endWord)) {
    return 0;
  }

  const getHeuristic = (word, target) => {
    let diff = 0;
    for (let i = 0; i < word.length; i++) {
      if (word[i] !== target[i]) {
        diff++;
      }
    }
    return diff;
  };

  const priorityQueue = [{ word: beginWord, cost: 0, level: 1 }]; // {word, cost, level}
  const visited = new Set([beginWord]);

  while (priorityQueue.length > 0) {
    priorityQueue.sort((a, b) => a.cost - b.cost); // Sort by cost (f = g + h)
    const { word: currWord, level } = priorityQueue.shift();

    if (currWord === endWord) {
      return level;
    }

    for (const nextWord of wordList) {
      if (isOneLetterDiff(currWord, nextWord) && !visited.has(nextWord)) {
        const cost = level + 1 + getHeuristic(nextWord, endWord); // f = g + h
        priorityQueue.push({ word: nextWord, cost, level: level + 1 });
        visited.add(nextWord);
      }
    }
  }
  return 0;
};

// ----------------------------------------------------------------------------
// Approach 5: Precompute Adjacency List + BFS
// ----------------------------------------------------------------------------

/**
 * Precomputes an adjacency list of which words are one letter apart, and then
 * uses BFS.  This can be faster for multiple queries on the same word list.
 */
const wordLadderPrecomputeBFS = (beginWord, endWord, wordList) => {
  if (!wordList.includes(endWord)) {
    return 0;
  }

  const adjList = new Map();

  // Add beginWord to wordList if it's not already there to ensure it's in the graph.
  const allWords = wordList.includes(beginWord) ? wordList : [beginWord, ...wordList];

  // 1. Precompute the adjacency list:
  for (let i = 0; i < allWords.length; i++) {
    const word1 = allWords[i];
    adjList.set(word1, []); // Initialize with empty array
    for (let j = 0; j < allWords.length; j++) {
      if (i !== j) {
        const word2 = allWords[j];
        if (isOneLetterDiff(word1, word2)) {
          adjList.get(word1).push(word2);
        }
      }
    }
  }

  // 2. Perform BFS using the precomputed adjacency list:
  const queue = [[beginWord, 1]];
  const visited = new Set([beginWord]);

  while (queue.length > 0) {
    const [currWord, level] = queue.shift();

    if (currWord === endWord) {
      return level;
    }

    const neighbors = adjList.get(currWord) || []; // Get neighbors, handle undefined
    for (const nextWord of neighbors) {
      if (!visited.has(nextWord)) {
        queue.push([nextWord, level + 1]);
        visited.add(nextWord);
      }
    }
  }
  return 0;
};

// ----------------------------------------------------------------------------
// Main - Example Usage
// ----------------------------------------------------------------------------

const beginWord = "hit";
const endWord = "cog";
const wordList = ["hot", "dot", "dog", "lot", "log", "cog"];

console.log("Input:");
console.log("beginWord:", beginWord);
console.log("endWord:", endWord);
console.log("wordList:", wordList);
console.log("\n");

// Approach 1: BFS - Basic
const result1 = wordLadderBFS(beginWord, endWord, wordList);
console.log("Approach 1: BFS - Basic");
console.log("Shortest ladder length:", result1);

// Approach 2: BFS - Optimized (Removing words from wordList)
const result2 = wordLadderBFSOptimized(beginWord, endWord, wordList);
console.log("\nApproach 2: BFS - Optimized");
console.log("Shortest ladder length:", result2);

// Approach 3: Bidirectional BFS
const result3 = wordLadderBiBFS(beginWord, endWord, wordList);
console.log("\nApproach 3: Bidirectional BFS");
console.log("Shortest ladder length:", result3);

// Approach 4: A* Search
const result4 = wordLadderAStar(beginWord, endWord, wordList);
console.log("\nApproach 4: A* Search");
console.log("Shortest ladder length:", result4);

// Approach 5: Precompute Adjacency List + BFS
const result5 = wordLadderPrecomputeBFS(beginWord, endWord, wordList);
console.log("\nApproach 5: Precompute Adjacency List + BFS");
console.log("Shortest ladder length:", result5);

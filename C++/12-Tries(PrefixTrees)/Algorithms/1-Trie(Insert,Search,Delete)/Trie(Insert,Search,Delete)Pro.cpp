/*
Tries (Prefix Trees) - JavaScript Implementation with 5 Approaches

A Trie, also known as a prefix tree, is a tree-like data structure used for efficient storage and retrieval of strings.  It excels at prefix-based searches.

Here are five different approaches to implementing a Trie in JavaScript, each with a slightly different focus and potential use case.  Each approach includes insert, search, and delete methods, along with example usage and console.log output.

Key Concepts:

* Node: Each node in a Trie represents a character.
* Root: The starting point of the Trie (often empty).
* Children: Each node has children, representing the next possible characters in a string.
* isEndOfWord: A boolean flag indicating if a node marks the end of a complete word.

*/

// ----------------------------------------------------------------------------------------------------
// 1. Basic Trie Implementation (Object-Based)
// ----------------------------------------------------------------------------------------------------
class TrieNode1 {
    constructor() {
        this.children = {}; // Using an object for children (more common in JS)
        this.isEndOfWord = false;
    }
}

class Trie1 {
    constructor() {
        this.root = new TrieNode1();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode1();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return node && node.isEndOfWord;
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


    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
        if (index === word.length) {
            if (!node.isEndOfWord) {
                return false; // Word not found
            }
            node.isEndOfWord = false; // Unmark the end of the word
            return Object.keys(node.children).length === 0; // Return true if node has no children
        }

        const char = word[index];
        const nextNode = node.children[char];

        if (!nextNode) {
            return false; // Word not found
        }

        const shouldDeleteChild = this._deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char]; // Delete the child node
            return Object.keys(node.children).length === 0; // Return true if node has no children
        }

        return false; // No deletion happened at this level
    }
}

// Example Usage (Trie 1)
const trie1 = new Trie1();
trie1.insert("apple");
trie1.insert("app");
trie1.insert("banana");

console.log("--- Trie 1 (Object-Based) ---");
console.log("Search 'apple':", trie1.search("apple")); // true
console.log("Search 'app':", trie1.search("app"));     // true
console.log("Search 'banana':", trie1.search("banana")); // true
console.log("Search 'orange':", trie1.search("orange")); // false
console.log("Starts with 'ap':", trie1.startsWith("ap")); // true
console.log("Starts with 'ba':", trie1.startsWith("ba")); // true

trie1.delete("apple");
console.log("After deleting 'apple', search 'apple':", trie1.search("apple")); // false
console.log("After deleting 'apple', search 'app':", trie1.search("app"));       // true
console.log("Search 'apple' after delete:", trie1.search("apple")); // false
console.log("Search 'app' after delete:", trie1.search("app"));     // true

// ----------------------------------------------------------------------------------------------------
// 2. Trie with Array-Based Children
// ----------------------------------------------------------------------------------------------------
const ALPHABET_SIZE = 26; // For lowercase English letters

class TrieNode2 {
    constructor() {
        this.children = new Array(ALPHABET_SIZE).fill(null);
        this.isEndOfWord = false;
    }
}

class Trie2 {
    constructor() {
        this.root = new TrieNode2();
    }

    _charToIndex(char) {
        return char.charCodeAt(0) - 'a'.charCodeAt(0);
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            const index = this._charToIndex(char);
            if (!node.children[index]) {
                node.children[index] = new TrieNode2();
            }
            node = node.children[index];
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            const index = this._charToIndex(char);
            if (!node.children[index]) {
                return false;
            }
            node = node.children[index];
        }
        return node && node.isEndOfWord;
    }
      startsWith(prefix) {
        let node = this.root;
        for (const char of prefix) {
            const index = this._charToIndex(char);
            if (!node.children[index]) {
                return false;
            }
            node = node.children[index];
        }
        return true;
    }

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
        if (index === word.length) {
            if (!node.isEndOfWord) {
                return false;
            }
            node.isEndOfWord = false;
            return this._hasNoChildren(node);
        }

        const charIndex = this._charToIndex(word[index]);
        const nextNode = node.children[charIndex];

        if (!nextNode) {
            return false;
        }

        const shouldDeleteChild = this._deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            node.children[charIndex] = null;
            return this._hasNoChildren(node);
        }
        return false;
    }

      _hasNoChildren(node) {
        for (let i = 0; i < ALPHABET_SIZE; i++) {
            if (node.children[i] !== null) {
                return false;
            }
        }
        return true;
    }
}

// Example Usage (Trie 2)
const trie2 = new Trie2();
trie2.insert("apple");
trie2.insert("app");
trie2.insert("banana");

console.log("\n--- Trie 2 (Array-Based Children) ---");
console.log("Search 'apple':", trie2.search("apple"));
console.log("Search 'app':", trie2.search("app"));
console.log("Search 'banana':", trie2.search("banana"));
console.log("Search 'orange':", trie2.search("orange"));
console.log("Starts with 'ap':", trie2.startsWith("ap"));
console.log("Starts with 'ba':", trie2.startsWith("ba"));

trie2.delete("apple");
console.log("After deleting 'apple', search 'apple':", trie2.search("apple")); // false
console.log("After deleting 'apple', search 'app':", trie2.search("app"));       // true

// ----------------------------------------------------------------------------------------------------
// 3. Trie with Custom Alphabet
// ----------------------------------------------------------------------------------------------------
class TrieNode3 {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class Trie3 {
    constructor(alphabet) {
        this.root = new TrieNode3();
        this.alphabet = alphabet;
        this.alphabetMap = new Map(); // For efficient character to index mapping
        for (let i = 0; i < alphabet.length; i++) {
          this.alphabetMap.set(alphabet[i], i);
        }
    }

    _charToIndex(char) {
        const index = this.alphabetMap.get(char);
        if (index === undefined) {
            throw new Error(`Character "${char}" not in alphabet`);
        }
        return index;
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            const index = this._charToIndex(char);
            if (!node.children[char]) {
                node.children[char] = new TrieNode3();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            const index = this._charToIndex(char);
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return node && node.isEndOfWord;
    }

    startsWith(prefix) {
      let node = this.root;
      for (const char of prefix) {
          const index = this._charToIndex(char);
          if (!node.children[char]) {
              return false;
          }
          node = node.children[char];
      }
      return true;
    }

    delete(word) {
      this._deleteHelper(this.root, word, 0);
    }

  _deleteHelper(node, word, index) {
        if (index === word.length) {
            if (!node.isEndOfWord) {
                return false;
            }
            node.isEndOfWord = false;
            return Object.keys(node.children).length === 0;
        }

        const char = word[index];
        const nextNode = node.children[char];

        if (!nextNode) {
            return false;
        }

        const shouldDeleteChild = this._deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char];
            return Object.keys(node.children).length === 0;
        }
        return false;
    }
}

// Example Usage (Trie 3)
const alphabet = "abcdefghijklmnopqrstuvwxyz' "; // Example: Allow spaces and apostrophes
const trie3 = new Trie3(alphabet);
trie3.insert("apple");
trie3.insert("app");
trie3.insert("banana");
trie3.insert("don't");
trie3.insert("hello world");

console.log("\n--- Trie 3 (Custom Alphabet) ---");
console.log("Search 'apple':", trie3.search("apple"));
console.log("Search 'app':", trie3.search("app"));
console.log("Search 'banana':", trie3.search("banana"));
console.log("Search 'don't':", trie3.search("don't"));
console.log("Search 'hello world':", trie3.search("hello world"));
console.log("Search 'orange':", trie3.search("orange"));
console.log("Starts with 'ap':", trie3.startsWith("ap"));
console.log("Starts with 'do':", trie3.startsWith("do"));
console.log("Starts with 'hello':", trie3.startsWith("hello"));

trie3.delete("apple");
console.log("After deleting 'apple', search 'apple':", trie3.search("apple"));
console.log("After deleting 'apple', search 'app':", trie3.search("app"));

// ----------------------------------------------------------------------------------------------------
// 4. Trie with Node IDs (for Graph-like Applications)
// ----------------------------------------------------------------------------------------------------
let nextNodeId = 0; // Simple global ID counter for demonstration

class TrieNode4 {
    constructor() {
        this.id = nextNodeId++; // Assign a unique ID to each node
        this.children = {};
        this.isEndOfWord = false;
    }
}

class Trie4 {
    constructor() {
        this.root = new TrieNode4();
        this.nodeMap = new Map(); // Store nodes by their IDs if needed
        this.nodeMap.set(this.root.id, this.root);
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                const newNode = new TrieNode4();
                node.children[char] = newNode;
                this.nodeMap.set(newNode.id, newNode); // Store the new node
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

      search(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return node && node.isEndOfWord;
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

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
         if (index === word.length) {
            if (!node.isEndOfWord) {
                return false;
            }
            node.isEndOfWord = false;
            return Object.keys(node.children).length === 0;
        }

        const char = word[index];
        const nextNode = node.children[char];

        if (!nextNode) {
            return false;
        }

        const shouldDeleteChild = this._deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char];
            return Object.keys(node.children).length === 0;
        }
        return false;
    }

    getNode(nodeId) {
      return this.nodeMap.get(nodeId);
    }
}

// Example Usage (Trie 4)
const trie4 = new Trie4();
trie4.insert("apple");
trie4.insert("app");
trie4.insert("banana");

console.log("\n--- Trie 4 (With Node IDs) ---");
console.log("Search 'apple':", trie4.search("apple"));
console.log("Search 'app':", trie4.search("app"));
console.log("Search 'banana':", trie4.search("banana"));
console.log("Node ID of root:", trie4.root.id);
const appleNode = trie4.getNode(trie4.root.children['a'].id);
console.log("Node after 'a' in 'apple':", appleNode);
console.log("Starts with 'ap':", trie4.startsWith("ap"));
console.log("Starts with 'ba':", trie4.startsWith("ba"));

trie4.delete("apple");
console.log("After deleting 'apple', search 'apple':", trie4.search("apple"));
console.log("After deleting 'apple', search 'app':", trie4.search("app"));

// ----------------------------------------------------------------------------------------------------
// 5. Trie with Word Frequency Counting
// ----------------------------------------------------------------------------------------------------
class TrieNode5 {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.wordFrequency = 0; // Added for frequency counting
    }
}

class Trie5 {
    constructor() {
        this.root = new TrieNode5();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode5();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.wordFrequency++; // Increment frequency
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                return { found: false, frequency: 0 }; // Return an object
            }
            node = node.children[char];
        }
        return { found: node && node.isEndOfWord, frequency: node ? node.wordFrequency : 0 }; // Return an object
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

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

      _deleteHelper(node, word, index) {
        if (index === word.length) {
            if (!node.isEndOfWord) {
                return false;
            }
            node.isEndOfWord = false;
             if (node.wordFrequency > 0) {
                node.wordFrequency--;
             }
            return Object.keys(node.children).length === 0;
        }

        const char = word[index];
        const nextNode = node.children[char];

        if (!nextNode) {
            return false;
        }

        const shouldDeleteChild = this._deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char];
            return Object.keys(node.children).length === 0;
        }
        return false;
    }
}

// Example Usage (Trie 5)
const trie5 = new Trie5();
trie5.insert("apple");
trie5.insert("apple");
trie5.insert("app");
trie5.insert("banana");
trie5.insert("apple"); // Insert "apple" again

console.log("\n--- Trie 5 (Word Frequency Counting) ---");
console.log("Search 'apple':", trie5.search("apple")); // { found: true, frequency: 3 }
console.log("Search 'app':", trie5.search("app"));     // { found: true, frequency: 1 }
console.log("Search 'banana':", trie5.search("banana")); // { found: true, frequency: 1 }
console.log("Search 'orange':", trie5.search("orange")); // { found: false, frequency: 0 }
console.log("Starts with 'ap':", trie5.startsWith("ap"));
console.log("Starts with 'ba':", trie5.startsWith("ba"));

trie5.delete("apple");
console.log("After deleting 'apple' once, search 'apple':", trie5.search("apple")); // { found: true, frequency: 2 }
trie5.delete("apple");
console.log("After deleting 'apple' twice, search 'apple':", trie5.search("apple"));
console.log("After deleting 'apple' twice, search 'app':", trie5.search("app"));

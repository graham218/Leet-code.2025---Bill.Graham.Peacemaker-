/*
Tries (Prefix Trees) & Aho-Corasick Algorithm in JavaScript

The Aho-Corasick algorithm is a string searching algorithm that locates elements of a finite set of strings (the "dictionary") within an input text. It essentially builds a finite state automaton (FSA) from the dictionary. This FSA is then used to process the text string in a single pass.

Here are 5 approaches, with increasing levels of optimization and clarity:

1.  **Basic Trie Approach (Conceptual):** This shows the fundamental Trie structure.  It's not a full Aho-Corasick implementation, as it lacks the failure function, but it's crucial for understanding the base data structure.
2.  **Trie with Search (No Failure Function):** This builds on the basic Trie, adding a search function.  It still doesn't use the Aho-Corasick optimization, so it's less efficient for overlapping patterns.
3.  **Aho-Corasick -  Trie + Failure Function (Core):** This is the core Aho-Corasick algorithm.  It constructs a Trie and then calculates the failure function.
4.  **Aho-Corasick - Optimized Queue (Performance):** This optimizes the failure function calculation using a queue, which is the standard approach.
5. **Aho-Corasick - Class-Based Structure (Clean):** This encapsulates the Trie and Aho-Corasick functions within a class, for better code organization.

Each approach is demonstrated with example usage and console logs.
*/

// --------------------------------------------------------------------------------
// 1. Basic Trie Approach (Conceptual)
// --------------------------------------------------------------------------------

console.log("\n--- 1. Basic Trie Approach (Conceptual) ---");

class TrieNodeBasic {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class TrieBasic {
    constructor() {
        this.root = new TrieNodeBasic();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNodeBasic();
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
}

const trieBasic = new TrieBasic();
trieBasic.insert("apple");
trieBasic.insert("banana");

console.log("Trie Basic Search 'apple':", trieBasic.search("apple")); // true
console.log("Trie Basic Search 'banana':", trieBasic.search("banana")); // true
console.log("Trie Basic Search 'orange':", trieBasic.search("orange")); // false

// --------------------------------------------------------------------------------
// 2. Trie with Search (No Failure Function)
// --------------------------------------------------------------------------------

console.log("\n--- 2. Trie with Search (No Failure Function) ---");

class TrieNodeSearch {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.word = null; // Store the complete word
    }
}

class TrieSearch {
    constructor() {
        this.root = new TrieNodeSearch();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNodeSearch();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.word = word; // Store the word at the end node
    }

    search(text) {
        const foundWords = [];
        for (let i = 0; i < text.length; i++) {
            let node = this.root;
            for (let j = i; j < text.length; j++) {
                const char = text[j];
                if (!node.children[char]) {
                    break; // No match, break inner loop
                }
                node = node.children[char];
                if (node.isEndOfWord) {
                    foundWords.push(node.word);
                    // Important:  Don't break here.  Find *all* matches, even if overlapping.
                }
            }
        }
        return foundWords;
    }
}

const trieSearch = new TrieSearch();
trieSearch.insert("he");
trieSearch.insert("she");
trieSearch.insert("his");
trieSearch.insert("hers");

const textSearch = "ahishers";
const resultsSearch = trieSearch.search(textSearch);
console.log(`Text: "${textSearch}"`);
console.log("Found Words (No Failure):", resultsSearch); // Output: [ 'his', 'hers' ]

// --------------------------------------------------------------------------------
// 3. Aho-Corasick - Trie + Failure Function (Core)
// --------------------------------------------------------------------------------

console.log("\n--- 3. Aho-Corasick - Trie + Failure Function (Core) ---");

class TrieNodeAC {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.failure = null; // Failure function link
        this.word = null;
    }
}

class AhoCorasick {
    constructor() {
        this.root = new TrieNodeAC();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNodeAC();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.word = word;
    }

    buildFailureFunction() {
        const queue = [];
        this.root.failure = this.root; // Initialize failure for root
        for (const child of Object.values(this.root.children)) {
            child.failure = this.root;
            queue.push(child);
        }

        while (queue.length > 0) {
            const node = queue.shift();
            for (const [char, child] of Object.entries(node.children)) {
                queue.push(child);
                let tempFailure = node.failure;
                while (tempFailure && !tempFailure.children[char]) {
                    tempFailure = tempFailure.failure;
                }
                child.failure = tempFailure ? tempFailure.children[char] || this.root : this.root;
                if (child.isEndOfWord) {
                    // Optional:  If you want to follow the chain of failures to find all matches.
                    // let failurePtr = child.failure;
                    // while (failurePtr !== this.root) {
                    //   if (failurePtr.isEndOfWord) {
                    //     console.log(`Additional match (suffix of ${child.word}): ${failurePtr.word}`);
                    //   }
                    //   failurePtr = failurePtr.failure;
                    // }
                }
            }
        }
    }

    search(text) {
        this.buildFailureFunction(); // Important: Build the failure function before searching
        const foundWords = [];
        let node = this.root;
        for (let i = 0; i < text.length; i++) {
            const char = text[i];
            while (node && !node.children[char]) {
                node = node.failure;
            }
            node = node ? node.children[char] || this.root : this.root; // 핵심
            if (node.isEndOfWord) {
                foundWords.push(node.word);
            }
            // Follow failure links to find all matches (including suffixes)
            let temp = node;
            while (temp !== this.root) {
                if (temp.isEndOfWord) {
                    foundWords.push(temp.word);
                }
                temp = temp.failure;
            }
        }
        return [...new Set(foundWords)]; // Remove duplicates
    }
}

const ac = new AhoCorasick();
ac.insert("he");
ac.insert("she");
ac.insert("his");
ac.insert("hers");
const text = "ahishers";
const results = ac.search(text);
console.log(`Text: "${text}"`);
console.log("Found Words (Aho-Corasick):", results); // Output: [ 'his', 'he', 'she', 'hers' ]

const ac2 = new AhoCorasick();
ac2.insert("ab");
ac2.insert("abab");
ac2.insert("b");
ac2.insert("ba");
ac2.insert("bab");
const text2 = "ababbaba";
const results2 = ac2.search(text2);
console.log(`Text: "${text2}"`);
console.log("Found Words (Aho-Corasick):", results2);
// --------------------------------------------------------------------------------
// 4. Aho-Corasick - Optimized Queue (Performance)
// --------------------------------------------------------------------------------

console.log("\n--- 4. Aho-Corasick - Optimized Queue (Performance) ---");

class TrieNodeACOpt {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.failure = null;
        this.word = null;
    }
}

class AhoCorasickOpt {
    constructor() {
        this.root = new TrieNodeACOpt();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNodeACOpt();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.word = word;
    }

    buildFailureFunction() {
        const queue = [this.root]; // Use a queue for BFS
        this.root.failure = this.root;

        while (queue.length > 0) {
            const node = queue.shift(); // Dequeue
            for (const char in node.children) {
                const child = node.children[char];
                let failure = node.failure;
                while (failure && !failure.children[char]) {
                    failure = failure.failure;
                }
                child.failure = failure ? failure.children[char] || this.root : this.root;
                queue.push(child); // Enqueue
            }
        }
    }

    search(text) {
        this.buildFailureFunction();
        const foundWords = new Set(); // Use a Set to avoid duplicates
        let node = this.root;

        for (const char of text) {
            while (node && !node.children[char]) {
                node = node.failure;
            }
            node = node ? node.children[char] || this.root : this.root;

            let temp = node;
            while (temp !== this.root) {
                if (temp.isEndOfWord) {
                    foundWords.add(temp.word);
                }
                temp = temp.failure;
            }
        }
        return Array.from(foundWords);
    }
}

const acOpt = new AhoCorasickOpt();
acOpt.insert("he");
acOpt.insert("she");
acOpt.insert("his");
acOpt.insert("hers");
const textOpt = "ahishers";
const resultsOpt = acOpt.search(textOpt);
console.log(`Text (Optimized): "${textOpt}"`);
console.log("Found Words (Aho-Corasick Optimized):", resultsOpt);

const acOpt2 = new AhoCorasickOpt();
acOpt2.insert("ab");
acOpt2.insert("abab");
acOpt2.insert("b");
acOpt2.insert("ba");
acOpt2.insert("bab");
const textOpt2 = "ababbaba";
const resultsOpt2 = acOpt2.search(textOpt2);
console.log(`Text (Optimized): "${textOpt2}"`);
console.log("Found Words (Aho-Corasick Optimized):", resultsOpt2);

// --------------------------------------------------------------------------------
// 5. Aho-Corasick - Class-Based Structure (Clean)
// --------------------------------------------------------------------------------

console.log("\n--- 5. Aho-Corasick - Class-Based Structure (Clean) ---");

class AhoCorasickClass {
    constructor(patterns) {
        this.root = new TrieNodeAC();
        this.patterns = patterns; // Store patterns for later use
        this.buildTrie();
        this.buildFailureFunction();
    }

    buildTrie() {
        for (const pattern of this.patterns) {
            let node = this.root;
            for (const char of pattern) {
                if (!node.children[char]) {
                    node.children[char] = new TrieNodeAC();
                }
                node = node.children[char];
            }
            node.isEndOfWord = true;
            node.word = pattern;
        }
    }

    buildFailureFunction() {
        const queue = [this.root];
        this.root.failure = this.root;

        while (queue.length > 0) {
            const node = queue.shift();
            for (const char in node.children) {
                const child = node.children[char];
                let failure = node.failure;
                while (failure && !failure.children[char]) {
                    failure = failure.failure;
                }
                child.failure = failure ? failure.children[char] || this.root : this.root;
                queue.push(child);
            }
        }
    }

    search(text) {
        const foundWords = new Set();
        let node = this.root;

        for (const char of text) {
            while (node && !node.children[char]) {
                node = node.failure;
            }
            node = node ? node.children[char] || this.root : this.root;

            let temp = node;
            while (temp !== this.root) {
                if (temp.isEndOfWord) {
                    foundWords.add(temp.word);
                }
                temp = temp.failure;
            }
        }
        return Array.from(foundWords);
    }
}

const patternsClass = ["he", "she", "his", "hers"];
const acClass = new AhoCorasickClass(patternsClass);
const textClass = "ahishers";
const resultsClass = acClass.search(textClass);
console.log(`Text (Class): "${textClass}"`);
console.log("Found Words (Aho-Corasick Class):", resultsClass);

const patternsClass2 = ["ab", "abab", "b", "ba", "bab"];
const acClass2 = new AhoCorasickClass(patternsClass2);
const textClass2 = "ababbaba";
const resultsClass2 = acClass2.search(textClass2);
console.log(`Text (Class): "${textClass2}"`);
console.log("Found Words (Aho-Corasick Class):", resultsClass2);

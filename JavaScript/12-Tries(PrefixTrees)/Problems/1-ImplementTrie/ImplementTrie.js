// Trie (Prefix Tree) Implementation in JavaScript

/**
 * Approach 1: Using Object as Node (Basic)
 */
class TrieNode1 {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class Trie1 {
    constructor() {
        this.root = new TrieNode1();
    }

    insert(word) {
        let node = this.root;
        for (let char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode1();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (let char of word) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return node && node.isEndOfWord;
    }

    startsWith(prefix) {
        let node = this.root;
        for (let char of prefix) {
            if (!node.children[char]) {
                return false;
            }
            node = node.children[char];
        }
        return true;
    }
}



/**
 * Approach 2: Using Map as Node
 */
class TrieNode2 {
    constructor() {
        this.children = new Map();
        this.isEndOfWord = false;
    }
}

class Trie2 {
    constructor() {
        this.root = new TrieNode2();
    }

    insert(word) {
        let node = this.root;
        for (let char of word) {
            if (!node.children.has(char)) {
                node.children.set(char, new TrieNode2());
            }
            node = node.children.get(char);
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (let char of word) {
            if (!node.children.has(char)) {
                return false;
            }
            node = node.children.get(char);
        }
        return node && node.isEndOfWord;
    }

    startsWith(prefix) {
        let node = this.root;
        for (let char of prefix) {
            if (!node.children.has(char)) {
                return false;
            }
            node = node.children.get(char);
        }
        return true;
    }
}



/**
 * Approach 3: Array of Children with Fixed Size (for lowercase alphabets)
 */
class TrieNode3 {
    constructor() {
        this.children = new Array(26).fill(null); // for 'a' to 'z'
        this.isEndOfWord = false;
    }

    // Get the index for a character ('a' -> 0, 'b' -> 1, ..., 'z' -> 25)
    getIndex(char) {
        return char.charCodeAt(0) - 'a'.charCodeAt(0);
    }
}

class Trie3 {
    constructor() {
        this.root = new TrieNode3();
    }

    insert(word) {
        let node = this.root;
        for (let char of word) {
            let index = node.getIndex(char);
            if (!node.children[index]) {
                node.children[index] = new TrieNode3();
            }
            node = node.children[index];
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (let char of word) {
            let index = node.getIndex(char);
            if (!node.children[index]) {
                return false;
            }
            node = node.children[index];
        }
        return node && node.isEndOfWord;
    }

    startsWith(prefix) {
        let node = this.root;
        for (let char of prefix) {
            let index = node.getIndex(char);
            if (!node.children[index]) {
                return false;
            }
            node = node.children[index];
        }
        return true;
    }
}

/**
 * Approach 4: Using a Single Object for Trie (Less Memory, potentially slower)
 * This approach uses a single object to store the entire trie, where keys are
 * the path (e.g., "apple", "ap", "a") and values indicate end of word.
 */
class Trie4 {
    constructor() {
        this.trie = {};
    }

    insert(word) {
        this.trie[word] = true; // Mark the word as complete
        let prefix = '';
        for (let char of word) {
            prefix += char;
            if (this.trie[prefix] === undefined) {
                this.trie[prefix] = false; // Mark prefixes, but not complete words
            }
        }
    }

    search(word) {
        return this.trie[word] === true;
    }

    startsWith(prefix) {
        return this.trie[prefix] !== undefined;
    }
}

/**
 * Approach 5:  Optimized Map with Array for Children and Boolean for End of Word
 */
class TrieNode5 {
    constructor() {
        this.children = new Map();
        this.isEndOfWord = false;
    }
}

class Trie5 {
    constructor() {
        this.root = new TrieNode5();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children.has(char)) {
                node.children.set(char, new TrieNode5());
            }
            node = node.children.get(char);
        }
        node.isEndOfWord = true;
    }

    search(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children.has(char)) {
                return false;
            }
            node = node.children.get(char);
        }
        return node !== null && node.isEndOfWord;
    }

    startsWith(prefix) {
        let node = this.root;
        for (const char of prefix) {
            if (!node.children.has(char)) {
                return false;
            }
            node = node.children.get(char);
        }
        return node !== null;
    }
}



// Test Cases
function runTestCases() {
    const words = ["apple", "app", "apricot", "banana", "bat", "car"];

    console.log("--- Trie 1 (Object) ---");
    const trie1 = new Trie1();
    words.forEach(word => trie1.insert(word));
    console.log("Search 'apple':", trie1.search("apple"));       // true
    console.log("Search 'app':", trie1.search("app"));           // false
    console.log("Search 'apricot':", trie1.search("apricot"));   // true
    console.log("Search 'banana':", trie1.search("banana"));     // true
    console.log("Search 'car':", trie1.search("car"));           // true
    console.log("Search 'cart':", trie1.search("cart"));         // false
    console.log("StartsWith 'ap':", trie1.startsWith("ap"));    // true
    console.log("StartsWith 'ba':", trie1.startsWith("ba"));    // true
    console.log("StartsWith 'ca':", trie1.startsWith("ca"));    // true
    console.log("StartsWith 'co':", trie1.startsWith("co"));    // false


    console.log("\n--- Trie 2 (Map) ---");
    const trie2 = new Trie2();
    words.forEach(word => trie2.insert(word));
    console.log("Search 'apple':", trie2.search("apple"));
    console.log("Search 'app':", trie2.search("app"));
    console.log("Search 'apricot':", trie2.search("apricot"));
    console.log("Search 'banana':", trie2.search("banana"));
    console.log("Search 'car':", trie2.search("car"));
    console.log("Search 'cart':", trie2.search("cart"));
    console.log("StartsWith 'ap':", trie2.startsWith("ap"));
    console.log("StartsWith 'ba':", trie2.startsWith("ba"));
    console.log("StartsWith 'ca':", trie2.startsWith("ca"));
    console.log("StartsWith 'co':", trie2.startsWith("co"));

    console.log("\n--- Trie 3 (Array) ---");
    const trie3 = new Trie3();
    words.forEach(word => trie3.insert(word));
    console.log("Search 'apple':", trie3.search("apple"));
    console.log("Search 'app':", trie3.search("app"));
    console.log("Search 'apricot':", trie3.search("apricot"));
    console.log("Search 'banana':", trie3.search("banana"));
    console.log("Search 'car':", trie3.search("car"));
    console.log("Search 'cart':", trie3.search("cart"));
    console.log("StartsWith 'ap':", trie3.startsWith("ap"));
    console.log("StartsWith 'ba':", trie3.startsWith("ba"));
    console.log("StartsWith 'ca':", trie3.startsWith("ca"));
    console.log("StartsWith 'co':", trie3.startsWith("co"));

    console.log("\n--- Trie 4 (Single Object) ---");
    const trie4 = new Trie4();
    words.forEach(word => trie4.insert(word));
    console.log("Search 'apple':", trie4.search("apple"));
    console.log("Search 'app':", trie4.search("app"));
    console.log("Search 'apricot':", trie4.search("apricot"));
    console.log("Search 'banana':", trie4.search("banana"));
    console.log("Search 'car':", trie4.search("car"));
    console.log("Search 'cart':", trie4.search("cart"));
    console.log("StartsWith 'ap':", trie4.startsWith("ap"));
    console.log("StartsWith 'ba':", trie4.startsWith("ba"));
    console.log("StartsWith 'ca':", trie4.startsWith("ca"));
    console.log("StartsWith 'co':", trie4.startsWith("co"));

    console.log("\n--- Trie 5 (Optimized Map) ---");
    const trie5 = new Trie5();
    words.forEach(word => trie5.insert(word));
    console.log("Search 'apple':", trie5.search("apple"));
    console.log("Search 'app':", trie5.search("app"));
    console.log("Search 'apricot':", trie5.search("apricot"));
    console.log("Search 'banana':", trie5.search("banana"));
    console.log("Search 'car':", trie5.search("car"));
    console.log("Search 'cart':", trie5.search("cart"));
    console.log("StartsWith 'ap':", trie5.startsWith("ap"));
    console.log("StartsWith 'ba':", trie5.startsWith("ba"));
    console.log("StartsWith 'ca':", trie5.startsWith("ca"));
    console.log("StartsWith 'co':", trie5.startsWith("co"));
}

runTestCases();

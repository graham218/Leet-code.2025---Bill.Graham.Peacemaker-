/*
Tries (Prefix Trees) - Implementation in JavaScript

A Trie, also known as a prefix tree, is a tree-like data structure used for efficient storage and retrieval of strings.  It's particularly useful for:

-   **Autocomplete:** Suggesting words as the user types.
-   **Spell checking:** Verifying if a word is in a dictionary.
-   **IP routing:** Finding the longest prefix match for an IP address.
-   **Storing a dictionary:** Efficiently storing a large set of words.

Key Concepts:

-   **Node:** Each node in a Trie represents a character.
-   **Root:** The starting point of the Trie.
-   **Edge:** A connection between nodes, representing a character.
-   **isEndOfWord:** A boolean flag indicating if a node represents the end of a complete word.

Basic Trie Structure (Common to all approaches):
*/

class TrieNode {
    constructor() {
        this.children = {}; // Use an object (hash map) for efficient character lookup
        this.isEndOfWord = false;
    }
}

/*
Approach 1: Iterative Insertion, Search, and Delete (Basic)
-   This is the most straightforward and common implementation.
-   Insertion: Iterate through the characters of the word, creating nodes as needed.
-   Search:  Iterate through the characters, returning false if any character is not found.
-   Delete: Iterative deletion.  Handles cases where the word is not in the trie,
            and where the word is a prefix of another word.
*/
class Trie1 {
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

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
        if (!node) return false;

        if (index === word.length) {
            if (!node.isEndOfWord) return false; // Word not in trie
            node.isEndOfWord = false; // Unmark the end of the word
            return Object.keys(node.children).length === 0; // Return true if no children
        }

        const char = word[index];
        const shouldDeleteChild = this._deleteHelper(node.children[char], word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char]; // Delete the child node
            return Object.keys(node.children).length === 0; // Return true if no children
        }

        return false;
    }
}



/*
Approach 2: Recursive Insertion, Iterative Search, Recursive Delete
-   Insertion:  Uses recursion to add nodes.
-   Search:   Uses iteration to find a word.
-   Delete:   Uses recursion.
*/
class Trie2 {
    constructor() {
        this.root = new TrieNode();
    }

    insert(word, node = this.root, index = 0) {
        if (index === word.length) {
            node.isEndOfWord = true;
            return;
        }
        const char = word[index];
        if (!node.children[char]) {
            node.children[char] = new TrieNode();
        }
        this.insert(word, node.children[char], index + 1);
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

    delete(word) {
        this.root = this._deleteHelper2(this.root, word, 0);
    }

    _deleteHelper2(node, word, index) {
        if (!node) return null;

        if (index === word.length) {
            if (node.isEndOfWord) {
                node.isEndOfWord = false;
            } else {
                return node; // Word not found
            }

            if (Object.keys(node.children).length === 0) {
                return null; // Delete node if it has no children
            }
            return node;
        }

        const char = word[index];
        node.children[char] = this._deleteHelper2(node.children[char], word, index + 1);

        if (node.children[char] === null && Object.keys(node.children).length === 0) {
            return null;
        }
        return node;
    }
}


/*
Approach 3: Iterative Insert, Recursive Search, Iterative Delete with Stack
- Insertion: Iterative
- Search: Recursive
- Delete: Iterative with a stack to track the path
*/
class Trie3 {
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
    }

    search(word, node = this.root, index = 0) {
        if (!node) return false;
        if (index === word.length) return node.isEndOfWord;
        const char = word[index];
        return this.search(word, node.children[char], index + 1);
    }

    delete(word) {
        const stack = [];
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) return; // Word not found
            stack.push({ node, char });
            node = node.children[char];
        }

        if (!node.isEndOfWord) return; // Word not found
        node.isEndOfWord = false;

        while (stack.length > 0) {
            const { node: parent, char } = stack.pop();
            if (Object.keys(node.children).length === 0 && !node.isEndOfWord) {
                delete parent.children[char];
            } else {
                break; // Stop deleting when a node has other children or is the end of another word
            }
            node = parent;
        }
    }
}

/*
Approach 4: Using Map for Children and a size property
-  Uses Map instead of a plain object for children.
-  Adds a 'size' property to each node to track the number of children.  This can be useful for certain optimizations, though not strictly necessary for basic Trie functionality.
*/
class Trie4 {
    constructor() {
        this.root = new TrieNode4();
    }

    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children.has(char)) {
                node.children.set(char, new TrieNode4());
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
        return node && node.isEndOfWord;
    }

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
        if (!node) return false;

        if (index === word.length) {
            if (!node.isEndOfWord) return false;
            node.isEndOfWord = false;
            return node.children.size === 0;
        }

        const char = word[index];
        const shouldDeleteChild = this._deleteHelper(node.children.get(char), word, index + 1);

        if (shouldDeleteChild) {
            node.children.delete(char);
            return node.children.size === 0;
        }
        return false;
    }
}

class TrieNode4 {
    constructor() {
        this.children = new Map();
        this.isEndOfWord = false;
    }
}


/*
Approach 5:  Object.create(null) for children
- Uses Object.create(null) to create children objects. This can provide a very minor performance improvement in some JavaScript engines because it avoids the overhead of the prototype chain.  However, it can also lead to unexpected behavior if you're not careful about inherited properties.
*/
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

    delete(word) {
        this._deleteHelper(this.root, word, 0);
    }

    _deleteHelper(node, word, index) {
        if (!node) return false;

        if (index === word.length) {
            if (!node.isEndOfWord) return false;
            node.isEndOfWord = false;
            return Object.keys(node.children).length === 0;
        }

        const char = word[index];
        const shouldDeleteChild = this._deleteHelper(node.children[char], word, index + 1);

        if (shouldDeleteChild) {
            delete node.children[char];
            return Object.keys(node.children).length === 0;
        }
        return false;
    }
}

class TrieNode5 {
    constructor() {
        this.children = Object.create(null); // No prototype chain!
        this.isEndOfWord = false;
    }
}



// Test Cases (for all Trie implementations)
function runTestCases(TrieClass, trieName) {
    console.log(`\nTesting ${trieName}:`);
    const trie = new TrieClass();

    // Insertion
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("application");
    trie.insert("apricot");

    console.log(`  Inserted: apple, app, banana, application, apricot`);

    // Search
    console.log(`  Search "apple": ${trie.search("apple")}`); // true
    console.log(`  Search "app": ${trie.search("app")}`);     // true
    console.log(`  Search "banana": ${trie.search("banana")}`); // true
    console.log(`  Search "application": ${trie.search("application")}`); // true
    console.log(`  Search "ap": ${trie.search("ap")}`);       // false
    console.log(`  Search "appl": ${trie.search("appl")}`);     // false
    console.log(`  Search "orange": ${trie.search("orange")}`);   // false

    // Deletion
    console.log(`  Delete "apple"`);
    trie.delete("apple");
    console.log(`  Search "apple" after deletion: ${trie.search("apple")}`); // false
    console.log(`  Search "app" after deleting "apple": ${trie.search("app")}`);       // true - "app" should still be present
    console.log(`  Search "application" after deleting "apple": ${trie.search("application")}`); //true

    console.log(`  Delete "application"`);
    trie.delete("application")
    console.log(`  Search "application" after deletion: ${trie.search("application")}`); // false
    console.log(`  Search "app" after deleting "application": ${trie.search("app")}`); // true

    console.log(`  Delete "app"`);
    trie.delete("app");
    console.log(`  Search "app" after deletion: ${trie.search("app")}`); // false - "app" should be deleted

    console.log(`  Search "apricot": ${trie.search("apricot")}`);
    trie.delete("apricot");
    console.log(`  Search "apricot" after deletion: ${trie.search("apricot")}`);
    console.log(`  Search "banana": ${trie.search("banana")}`); // true
}

// Run tests for each implementation
runTestCases(Trie1, "Trie1 (Iterative)");
runTestCases(Trie2, "Trie2 (Recursive Insert, Recursive Delete)");
runTestCases(Trie3, "Trie3 (Iterative Insert, Recursive Search, Iterative Delete with Stack)");
runTestCases(Trie4, "Trie4 (Using Map for Children)");
runTestCases(Trie5, "Trie5 (Object.create(null) for children)");

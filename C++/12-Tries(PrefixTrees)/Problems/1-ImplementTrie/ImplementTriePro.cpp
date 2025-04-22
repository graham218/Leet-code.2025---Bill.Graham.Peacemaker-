/**
 * Trie (Prefix Tree) Implementations - 5 Approaches
 *
 * 1. Basic Trie Implementation
 * 2. Trie with Frequency Count (for autocomplete)
 * 3. Trie with Word Storage (for dictionary)
 * 4. Compressed Trie (memory optimized)
 * 5. Ternary Search Trie (space/time tradeoff)
 */

console.log("=== Trie Implementations ===");

// ==============================================
// 1. Basic Trie Implementation
// ==============================================
class BasicTrieNode {
  constructor() {
    this.children = {};
    this.isEndOfWord = false;
  }
}

class BasicTrie {
  constructor() {
    this.root = new BasicTrieNode();
  }

  insert(word) {
    let node = this.root;
    for (const char of word) {
      if (!node.children[char]) {
        node.children[char] = new BasicTrieNode();
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

// Test Basic Trie
console.log("\n1. Basic Trie Implementation:");
const basicTrie = new BasicTrie();
basicTrie.insert("apple");
console.log("Search 'apple':", basicTrie.search("apple"));   // true
console.log("Search 'app':", basicTrie.search("app"));       // false
console.log("StartsWith 'app':", basicTrie.startsWith("app")); // true
basicTrie.insert("app");
console.log("Search 'app' after insertion:", basicTrie.search("app")); // true

// ==============================================
// 2. Trie with Frequency Count (for autocomplete)
// ==============================================
class FrequencyTrieNode {
  constructor() {
    this.children = {};
    this.isEndOfWord = false;
    this.frequency = 0;
  }
}

class FrequencyTrie {
  constructor() {
    this.root = new FrequencyTrieNode();
  }

  insert(word, frequency = 1) {
    let node = this.root;
    for (const char of word) {
      if (!node.children[char]) {
        node.children[char] = new FrequencyTrieNode();
      }
      node = node.children[char];
    }
    node.isEndOfWord = true;
    node.frequency += frequency;
  }

  getTopSuggestions(prefix, limit = 5) {
    let node = this.root;
    for (const char of prefix) {
      if (!node.children[char]) {
        return [];
      }
      node = node.children[char];
    }

    const suggestions = [];
    this._dfsCollect(node, prefix, suggestions);

    // Sort by frequency and get top results
    return suggestions
      .sort((a, b) => b.frequency - a.frequency)
      .slice(0, limit)
      .map(item => item.word);
  }

  _dfsCollect(node, prefix, suggestions) {
    if (node.isEndOfWord) {
      suggestions.push({ word: prefix, frequency: node.frequency });
    }

    for (const [char, childNode] of Object.entries(node.children)) {
      this._dfsCollect(childNode, prefix + char, suggestions);
    }
  }
}

// Test Frequency Trie
console.log("\n2. Trie with Frequency Count (for autocomplete):");
const freqTrie = new FrequencyTrie();
freqTrie.insert("apple", 10);
freqTrie.insert("app", 5);
freqTrie.insert("application", 8);
freqTrie.insert("apt", 3);
freqTrie.insert("apricot", 2);
freqTrie.insert("banana", 7);

console.log("Top suggestions for 'ap':", freqTrie.getTopSuggestions("ap"));
console.log("Top suggestions for 'app':", freqTrie.getTopSuggestions("app"));
console.log("Top suggestions for 'b':", freqTrie.getTopSuggestions("b"));

// ==============================================
// 3. Trie with Word Storage (for dictionary)
// ==============================================
class DictionaryTrieNode {
  constructor() {
    this.children = {};
    this.definition = null;
  }
}

class DictionaryTrie {
  constructor() {
    this.root = new DictionaryTrieNode();
  }

  insert(word, definition) {
    let node = this.root;
    for (const char of word) {
      if (!node.children[char]) {
        node.children[char] = new DictionaryTrieNode();
      }
      node = node.children[char];
    }
    node.definition = definition;
  }

  search(word) {
    let node = this.root;
    for (const char of word) {
      if (!node.children[char]) {
        return null;
      }
      node = node.children[char];
    }
    return node.definition;
  }

  getAllWords() {
    const words = [];
    this._dfsCollectWords(this.root, "", words);
    return words;
  }

  _dfsCollectWords(node, currentWord, words) {
    if (node.definition !== null) {
      words.push({ word: currentWord, definition: node.definition });
    }

    for (const [char, childNode] of Object.entries(node.children)) {
      this._dfsCollectWords(childNode, currentWord + char, words);
    }
  }
}

// Test Dictionary Trie
console.log("\n3. Trie with Word Storage (for dictionary):");
const dictTrie = new DictionaryTrie();
dictTrie.insert("apple", "A sweet fruit that grows on trees");
dictTrie.insert("app", "Short for application");
dictTrie.insert("application", "A program or piece of software");
dictTrie.insert("apt", "Appropriate or suitable in the circumstances");

console.log("Definition of 'apple':", dictTrie.search("apple"));
console.log("Definition of 'app':", dictTrie.search("app"));
console.log("Definition of 'nonexistent':", dictTrie.search("nonexistent"));

console.log("All words in dictionary:");
console.log(dictTrie.getAllWords());

// ==============================================
// 4. Compressed Trie (memory optimized)
// ==============================================
class CompressedTrieNode {
  constructor() {
    this.children = {}; // key: string, value: {node: CompressedTrieNode, prefix: string}
    this.isEndOfWord = false;
  }
}

class CompressedTrie {
  constructor() {
    this.root = new CompressedTrieNode();
  }

  insert(word) {
    this._insertHelper(this.root, word);
  }

  _insertHelper(node, word) {
    if (!word) {
      node.isEndOfWord = true;
      return;
    }

    // Find a child with a common prefix
    for (const [prefix, child] of Object.entries(node.children)) {
      const commonLen = this._commonPrefixLength(prefix, word);

      if (commonLen > 0) {
        if (commonLen < prefix.length) {
          // Split the existing node
          const remainingPrefix = prefix.slice(commonLen);
          const newChild = new CompressedTrieNode();

          // Move the existing child to the new node
          newChild.children[remainingPrefix] = child;

          // Replace the existing child with the new node
          node.children[word.slice(0, commonLen)] = {
            node: newChild,
            prefix: word.slice(0, commonLen)
          };
          delete node.children[prefix];

          // Continue inserting the remaining part of the word
          this._insertHelper(newChild, word.slice(commonLen));
          return;
        } else {
          // Full prefix matches, continue with the child
          this._insertHelper(child.node, word.slice(commonLen));
          return;
        }
      }
    }

    // No common prefix found, create a new child
    const newNode = new CompressedTrieNode();
    node.children[word] = { node: newNode, prefix: word };
    newNode.isEndOfWord = true;
  }

  search(word) {
    return this._searchHelper(this.root, word);
  }

  _searchHelper(node, word) {
    if (!word) return node.isEndOfWord;

    for (const [prefix, child] of Object.entries(node.children)) {
      if (word.startsWith(prefix)) {
        return this._searchHelper(child.node, word.slice(prefix.length));
      }
    }

    return false;
  }

  _commonPrefixLength(a, b) {
    let i = 0;
    while (i < a.length && i < b.length && a[i] === b[i]) {
      i++;
    }
    return i;
  }
}

// Test Compressed Trie
console.log("\n4. Compressed Trie (memory optimized):");
const compressedTrie = new CompressedTrie();
compressedTrie.insert("apple");
compressedTrie.insert("app");
compressedTrie.insert("application");
compressedTrie.insert("aptitude");

console.log("Search 'apple':", compressedTrie.search("apple")); // true
console.log("Search 'app':", compressedTrie.search("app"));     // true
console.log("Search 'apt':", compressedTrie.search("apt"));     // false
console.log("Search 'aptitude':", compressedTrie.search("aptitude")); // true

// ==============================================
// 5. Ternary Search Trie (space/time tradeoff)
// ==============================================
class TSTNode {
  constructor(char) {
    this.char = char;
    this.left = null;
    this.middle = null;
    this.right = null;
    this.value = null; // or isEndOfWord flag
  }
}

class TernarySearchTrie {
  constructor() {
    this.root = null;
  }

  insert(word, value = true) {
    this.root = this._insertHelper(this.root, word, 0, value);
  }

  _insertHelper(node, word, index, value) {
    const char = word[index];

    if (!node) {
      node = new TSTNode(char);
    }

    if (char < node.char) {
      node.left = this._insertHelper(node.left, word, index, value);
    } else if (char > node.char) {
      node.right = this._insertHelper(node.right, word, index, value);
    } else {
      if (index < word.length - 1) {
        node.middle = this._insertHelper(node.middle, word, index + 1, value);
      } else {
        node.value = value;
      }
    }

    return node;
  }

  search(word) {
    const node = this._searchHelper(this.root, word, 0);
    return node !== null && node.value !== null;
  }

  _searchHelper(node, word, index) {
    if (!node) return null;

    const char = word[index];

    if (char < node.char) {
      return this._searchHelper(node.left, word, index);
    } else if (char > node.char) {
      return this._searchHelper(node.right, word, index);
    } else {
      if (index < word.length - 1) {
        return this._searchHelper(node.middle, word, index + 1);
      } else {
        return node;
      }
    }
  }

  startsWith(prefix) {
    const node = this._getPrefixNode(this.root, prefix, 0);
    return node !== null;
  }

  _getPrefixNode(node, prefix, index) {
    if (!node) return null;

    const char = prefix[index];

    if (char < node.char) {
      return this._getPrefixNode(node.left, prefix, index);
    } else if (char > node.char) {
      return this._getPrefixNode(node.right, prefix, index);
    } else {
      if (index < prefix.length - 1) {
        return this._getPrefixNode(node.middle, prefix, index + 1);
      } else {
        return node;
      }
    }
  }
}

// Test Ternary Search Trie
console.log("\n5. Ternary Search Trie (space/time tradeoff):");
const tst = new TernarySearchTrie();
tst.insert("apple");
tst.insert("orange");
tst.insert("banana");
tst.insert("app");

console.log("Search 'apple':", tst.search("apple"));   // true
console.log("Search 'app':", tst.search("app"));      // true
console.log("Search 'orange':", tst.search("orange")); // true
console.log("Search 'pea':", tst.search("pea"));      // false
console.log("StartsWith 'app':", tst.startsWith("app")); // true
console.log("StartsWith 'ora':", tst.startsWith("ora")); // true
console.log("StartsWith 'pea':", tst.startsWith("pea")); // false

console.log("\n=== All Trie Implementations Tested ===");
/*
 * Java Implementation of Trie (Prefix Tree)
 * Five different real-world style implementations:
 * 1. Basic Trie with Insert and Search (Text Autocomplete)
 * 2. Trie with Delete functionality (Dictionary Management)
 * 3. Trie with word frequency count (Search Engine Suggestion Ranking)
 * 4. Trie with wildcard support (Search with pattern like '?', '*')
 * 5. Trie with compressed nodes (Radix Tree for memory efficiency)
 */

import java.util.*;

// Usage example (Can be removed in production code)
public class TrieExamples {
    public static void main(String[] args) {
        BasicTrie trie = new BasicTrie();
        trie.insert("hello");
        System.out.println(trie.search("hello")); // true

        TrieWithDelete deleteTrie = new TrieWithDelete();
        deleteTrie.insert("world");
        deleteTrie.delete("world");
        System.out.println(deleteTrie.search("world")); // false

        TrieWithFrequency freqTrie = new TrieWithFrequency();
        freqTrie.insert("google");
        freqTrie.insert("google");
        System.out.println(freqTrie.getFrequency("google")); // 2

        TrieWithWildcard wildcardTrie = new TrieWithWildcard();
        wildcardTrie.insert("hat");
        System.out.println(wildcardTrie.search("h.t")); // true

        CompressedTrie compressedTrie = new CompressedTrie();
        compressedTrie.insert("interview");
        System.out.println(compressedTrie.search("interview")); // true
    }
}
class BasicTrie {
    protected final TrieNode root;

    public BasicTrie() {
        root = new TrieNode();
    }

    // Insert a word
    public void insert(String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            node.children.putIfAbsent(ch, new TrieNode());
            node = node.children.get(ch);
        }
        node.isEndOfWord = true;
    }

    // Search a word
    public boolean search(String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            node = node.children.get(ch);
            if (node == null) return false;
        }
        return node.isEndOfWord;
    }
}

// 2. Trie with Delete: Used in Dictionary Management Systems
class TrieWithDelete extends BasicTrie {
    public boolean delete(String word) {
        return deleteHelper(root, word, 0);
    }

    private boolean deleteHelper(TrieNode current, String word, int index) {
        if (index == word.length()) {
            if (!current.isEndOfWord) return false;
            current.isEndOfWord = false;
            return current.children.isEmpty();
        }
        char ch = word.charAt(index);
        TrieNode node = current.children.get(ch);
        if (node == null) return false;

        boolean shouldDeleteCurrentNode = deleteHelper(node, word, index + 1);

        if (shouldDeleteCurrentNode) {
            current.children.remove(ch);
            return current.children.isEmpty() && !current.isEndOfWord;
        }
        return false;
    }
}

// 3. Trie with Word Frequency: Used in search ranking
class TrieNodeWithFrequency {
    Map<Character, TrieNodeWithFrequency> children = new HashMap<>();
    int frequency = 0;
    boolean isEndOfWord;
}

class TrieWithFrequency {
    private final TrieNodeWithFrequency root = new TrieNodeWithFrequency();

    public void insert(String word) {
        TrieNodeWithFrequency node = root;
        for (char ch : word.toCharArray()) {
            node.children.putIfAbsent(ch, new TrieNodeWithFrequency());
            node = node.children.get(ch);
        }
        node.isEndOfWord = true;
        node.frequency++;
    }

    public int getFrequency(String word) {
        TrieNodeWithFrequency node = root;
        for (char ch : word.toCharArray()) {
            node = node.children.get(ch);
            if (node == null) return 0;
        }
        return node.isEndOfWord ? node.frequency : 0;
    }
}

// 4. Trie with Wildcard Support: Used in Pattern Matching
class TrieWithWildcard {
    private final TrieNode root = new TrieNode();

    public void insert(String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            node.children.putIfAbsent(ch, new TrieNode());
            node = node.children.get(ch);
        }
        node.isEndOfWord = true;
    }

    public boolean search(String word) {
        return searchWildcard(root, word, 0);
    }

    private boolean searchWildcard(TrieNode node, String word, int index) {
        if (index == word.length()) return node.isEndOfWord;
        char ch = word.charAt(index);
        if (ch == '.') {
            for (char c : node.children.keySet()) {
                if (searchWildcard(node.children.get(c), word, index + 1)) return true;
            }
            return false;
        } else {
            TrieNode next = node.children.get(ch);
            return next != null && searchWildcard(next, word, index + 1);
        }
    }
}

// 5. Compressed Trie (Radix Tree): Memory-efficient implementation
class RadixNode {
    String key;
    boolean isEndOfWord;
    Map<String, RadixNode> children = new HashMap<>();

    public RadixNode(String key) {
        this.key = key;
    }
}

class CompressedTrie {
    private final RadixNode root = new RadixNode("");

    public void insert(String word) {
        insertHelper(root, word);
    }

    private void insertHelper(RadixNode node, String word) {
        for (String childKey : new HashSet<>(node.children.keySet())) {
            int i = 0;
            while (i < Math.min(childKey.length(), word.length()) && childKey.charAt(i) == word.charAt(i)) {
                i++;
            }
            if (i > 0) {
                String commonPrefix = childKey.substring(0, i);
                String remainingOld = childKey.substring(i);
                String remainingNew = word.substring(i);

                RadixNode oldChild = node.children.remove(childKey);
                RadixNode newIntermediate = new RadixNode(commonPrefix);
                node.children.put(commonPrefix, newIntermediate);

                oldChild.key = remainingOld;
                newIntermediate.children.put(remainingOld, oldChild);

                if (!remainingNew.isEmpty()) {
                    newIntermediate.children.put(remainingNew, new RadixNode(remainingNew));
                } else {
                    newIntermediate.isEndOfWord = true;
                }
                return;
            }
        }
        node.children.put(word, new RadixNode(word));
        node.children.get(word).isEndOfWord = true;
    }

    public boolean search(String word) {
        return searchHelper(root, word);
    }

    private boolean searchHelper(RadixNode node, String word) {
        for (String childKey : node.children.keySet()) {
            if (word.startsWith(childKey)) {
                if (word.equals(childKey)) return node.children.get(childKey).isEndOfWord;
                return searchHelper(node.children.get(childKey), word.substring(childKey.length()));
            }
        }
        return false;
    }
}

// 1. Basic Trie: Used in Text Autocomplete
class TrieNode {
    Map<Character, TrieNode> children = new HashMap<>();
    boolean isEndOfWord;
}
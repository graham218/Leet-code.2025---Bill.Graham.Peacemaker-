import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;

// Trie (Prefix Tree) Implementation in Java - 5 Approaches

/**
 * A Trie (also known as a prefix tree) is a tree-like data structure
 * used for efficient storage and retrieval of strings.  It allows for
 * fast prefix-based search and is commonly used for applications like
 * autocomplete, spell checking, and IP routing.
 */

// Approach 1: Basic Trie Implementation with HashMap
class TrieNode1 {
    Map<Character, TrieNode1> children;
    boolean isEndOfWord;

    public TrieNode1() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

class Trie1 {
    private TrieNode1 root;

    public Trie1() {
        root = new TrieNode1();
    }

    /**
     * Inserts a word into the trie.
     *
     * @param word The word to insert.
     * Time Complexity: O(n), where n is the length of the word.
     * Space Complexity: O(n), in the worst case, if the word is distinct.
     */
    public void insert(String word) {
        TrieNode1 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                current.children.put(ch, new TrieNode1());
            }
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    /**
     * Searches for a word in the trie.
     *
     * @param word The word to search for.
     * @return True if the word exists in the trie, false otherwise.
     * Time Complexity: O(n), where n is the length of the word.
     * Space Complexity: O(1)
     */
    public boolean search(String word) {
        TrieNode1 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    /**
     * Checks if there is any word in the trie that starts with the given prefix.
     *
     * @param prefix The prefix to search for.
     * @return True if there is a word with the given prefix, false otherwise.
     * Time Complexity: O(m), where m is the length of the prefix.
     * Space Complexity: O(1)
     */
    public boolean startsWith(String prefix) {
        TrieNode1 current = root;
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }
}

// Approach 2: Trie Implementation with Array (for lowercase English letters)
class TrieNode2 {
    TrieNode2[] children;
    boolean isEndOfWord;

    public TrieNode2() {
        children = new TrieNode2[26]; // For 'a' to 'z'
        isEndOfWord = false;
    }
}

class Trie2 {
    private TrieNode2 root;

    public Trie2() {
        root = new TrieNode2();
    }

    public void insert(String word) {
        TrieNode2 current = root;
        for (char ch : word.toCharArray()) {
            int index = ch - 'a';
            if (current.children[index] == null) {
                current.children[index] = new TrieNode2();
            }
            current = current.children[index];
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode2 current = root;
        for (char ch : word.toCharArray()) {
            int index = ch - 'a';
            if (current.children[index] == null) {
                return false;
            }
            current = current.children[index];
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode2 current = root;
        for (char ch : prefix.toCharArray()) {
            int index = ch - 'a';
            if (current.children[index] == null) {
                return false;
            }
            current = current.children[index];
        }
        return true;
    }
}

// Approach 3: Trie Implementation with Optimized Node (Reduced Memory)
class TrieNode3 {
    // Using a map, but optimizing the node structure itself.
    Map<Character, TrieNode3> children;
    boolean isEndOfWord;

    public TrieNode3() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

class Trie3 {
    private TrieNode3 root;

    public Trie3() {
        root = new TrieNode3();
    }

    public void insert(String word) {
        TrieNode3 current = root;
        for (char ch : word.toCharArray()) {
            current.children.computeIfAbsent(ch, k -> new TrieNode3());
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode3 current = root;
        for (char ch : word.toCharArray()) {
            if (current.children == null || !current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode3 current = root;
        for (char ch : prefix.toCharArray()) {
            if (current.children == null || !current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }
}

// Approach 4: Trie with Node Pooling (Memory Efficiency)
class TrieNode4 {
    Map<Character, TrieNode4> children;
    boolean isEndOfWord;

    public TrieNode4() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

class Trie4 {
    private TrieNode4 root;
    private List<TrieNode4> nodePool;
    private int poolIndex;

    public Trie4() {
        root = new TrieNode4();
        nodePool = new ArrayList<>();
        nodePool.add(root); // Add the root node to the pool
        poolIndex = 1;
    }

    private TrieNode4 getNodeFromPool() {
        if (poolIndex < nodePool.size()) {
            return nodePool.get(poolIndex++);
        } else {
            TrieNode4 newNode = new TrieNode4();
            nodePool.add(newNode);
            poolIndex++;
            return newNode;
        }
    }

    public void insert(String word) {
        TrieNode4 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                current.children.put(ch, getNodeFromPool());
            }
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode4 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode4 current = root;
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }
}

// Approach 5: Trie with Deletion
class TrieNode5 {
    Map<Character, TrieNode5> children;
    boolean isEndOfWord;

    public TrieNode5() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

class Trie5 {
    private TrieNode5 root;

    public Trie5() {
        root = new TrieNode5();
    }

    public void insert(String word) {
        TrieNode5 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                current.children.put(ch, new TrieNode5());
            }
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode5 current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode5 current = root;
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }

    /**
     * Deletes a word from the trie.
     *
     * @param word The word to delete.
     * @return True if the word was deleted, false otherwise.
     */
    public boolean delete(String word) {
        return deleteHelper(root, word, 0);
    }

    private boolean deleteHelper(TrieNode5 current, String word, int index) {
        if (index == word.length()) {
            if (!current.isEndOfWord) {
                return false; // Word not found
            }
            current.isEndOfWord = false; // Unmark the end of the word.
            return current.children.isEmpty(); // Return true if this node can be deleted
        }

        char ch = word.charAt(index);
        TrieNode5 nextNode = current.children.get(ch);
        if (nextNode == null) {
            return false; // Word not found
        }

        boolean shouldDeleteChild = deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            current.children.remove(ch); // Remove the child node
            return current.children.isEmpty() && !current.isEndOfWord; // Return true if this node can be deleted
        }

        return false;
    }
}

// Main class to demonstrate the Trie implementations
public class Main {
    public static void main(String[] args) {
        // Example Usage for Approach 1
        System.out.println("Approach 1: Basic Trie with HashMap");
        Trie1 trie1 = new Trie1();
        trie1.insert("apple");
        trie1.insert("app");
        System.out.println("Search 'apple': " + trie1.search("apple")); // true
        System.out.println("Search 'app': " + trie1.search("app"));     // true
        System.out.println("Search 'ap': " + trie1.search("ap"));       // false
        System.out.println("StartsWith 'ap': " + trie1.startsWith("ap")); // true
        System.out.println();

        // Example Usage for Approach 2
        System.out.println("Approach 2: Trie with Array");
        Trie2 trie2 = new Trie2();
        trie2.insert("apple");
        trie2.insert("app");
        System.out.println("Search 'apple': " + trie2.search("apple"));
        System.out.println("Search 'app': " + trie2.search("app"));
        System.out.println("Search 'ap': " + trie2.search("ap"));
        System.out.println("StartsWith 'ap': " + trie2.startsWith("ap"));
        System.out.println();

        // Example Usage for Approach 3
        System.out.println("Approach 3: Optimized Node");
        Trie3 trie3 = new Trie3();
        trie3.insert("apple");
        trie3.insert("app");
        System.out.println("Search 'apple': " + trie3.search("apple"));
        System.out.println("Search 'app': " + trie3.search("app"));
        System.out.println("Search 'ap': " + trie3.search("ap"));
        System.out.println("StartsWith 'ap': " + trie3.startsWith("ap"));
        System.out.println();

        // Example Usage for Approach 4: Trie with Node Pooling
        System.out.println("Approach 4: Trie with Node Pooling");
        Trie4 trie4 = new Trie4();
        trie4.insert("apple");
        trie4.insert("app");
        trie4.insert("application");
        System.out.println("Search 'apple': " + trie4.search("apple"));
        System.out.println("Search 'app': " + trie4.search("app"));
        System.out.println("Search 'application': " + trie4.search("application"));
        System.out.println("StartsWith 'app': " + trie4.startsWith("app"));
        System.out.println("StartsWith 'appl': " + trie4.startsWith("appl"));

        // Example Usage for Approach 5: Trie with Deletion
        System.out.println("\nApproach 5: Trie with Deletion");
        Trie5 trie5 = new Trie5();
        trie5.insert("apple");
        trie5.insert("app");
        trie5.insert("application");

        System.out.println("Search 'apple' before deletion: " + trie5.search("apple")); // true
        System.out.println("Search 'app' before deletion: " + trie5.search("app"));     // true
        System.out.println("Search 'application' before deletion: " + trie5.search("application")); // true

        trie5.delete("apple");
        System.out.println("Search 'apple' after deleting 'apple': " + trie5.search("apple"));     // false
        System.out.println("Search 'app' after deleting 'apple': " + trie5.search("app"));         // true (should still be present)
        System.out.println("Search 'application' after deleting 'apple': " + trie5.search("application"));  //true

        trie5.delete("app");
        System.out.println("Search 'app' after deleting 'app': " + trie5.search("app"));  // false
        System.out.println("Search 'application' after deleting 'app': " + trie5.search("application")); // true

        trie5.delete("application");
        System.out.println("Search 'application' after deleting 'application': " + trie5.search("application")); // false
        System.out.println("Search 'appl': " + trie5.search("appl")); // false
        System.out.println("StartsWith 'a': " + trie5.startsWith("a")); // false.  The trie is empty

    }
}

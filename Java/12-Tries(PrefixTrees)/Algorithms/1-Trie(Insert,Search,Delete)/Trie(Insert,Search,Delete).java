import java.util.HashMap;
import java.util.Map;
import java.util.Stack;


// Trie class
public class Trie {
    public static void main(String[] args) {
        Trie trie = new Trie();

        // Insertion
        trie.insertIterative("apple");
        trie.insertRecursive("banana");
        trie.insertIterative("app");
        trie.insertRecursive("orange");

        // Search
        System.out.println("Search 'apple' (Iterative): " + trie.searchIterative("apple")); // true
        System.out.println("Search 'app' (Recursive): " + trie.searchRecursive("app"));     // true
        System.out.println("Search 'banana' (Iterative): " + trie.searchIterative("banana")); // true
        System.out.println("Search 'orange' (Recursive): " + trie.searchRecursive("orange")); // true
        System.out.println("Search 'appl' (Iterative): " + trie.searchIterative("appl"));   // false
        System.out.println("Search 'grape' (Recursive): " + trie.searchRecursive("grape"));  // false

        // Deletion
        trie.delete("apple");
        System.out.println("Search 'apple' after deletion (Iterative): " + trie.searchIterative("apple")); // false
        System.out.println("Search 'app' after deleting 'apple'(Recursive): " + trie.searchRecursive("app"));       // true, 'app' should still exist
        trie.delete("app");
        System.out.println("Search 'app' after deleting 'app': " + trie.searchIterative("app")); // false
        System.out.println("Search 'banana' after deleting other words: " + trie.searchIterative("banana")); // true
    }


    private TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    // 1. Iterative Insert
    public void insertIterative(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                current.children.put(ch, new TrieNode());
            }
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    // 2. Recursive Insert
    public void insertRecursive(String word) {
        insertRecursiveHelper(root, word, 0);
    }

    private void insertRecursiveHelper(TrieNode node, String word, int index) {
        if (index == word.length()) {
            node.isEndOfWord = true;
            return;
        }
        char ch = word.charAt(index);
        if (!node.children.containsKey(ch)) {
            node.children.put(ch, new TrieNode());
        }
        insertRecursiveHelper(node.children.get(ch), word, index + 1);
    }

    // 3. Iterative Search
    public boolean searchIterative(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    // 4. Recursive Search
    public boolean searchRecursive(String word) {
        return searchRecursiveHelper(root, word, 0);
    }

    private boolean searchRecursiveHelper(TrieNode node, String word, int index) {
        if (index == word.length()) {
            return node.isEndOfWord;
        }
        char ch = word.charAt(index);
        if (!node.children.containsKey(ch)) {
            return false;
        }
        return searchRecursiveHelper(node.children.get(ch), word, index + 1);
    }

    // 5. Delete Operation
    public void delete(String word) {
        deleteHelper(root, word, 0);
    }

    private boolean deleteHelper(TrieNode node, String word, int index) {
        if (index == word.length()) {
            if (!node.isEndOfWord) {
                return false; // Word not in trie
            }
            node.isEndOfWord = false; // Unmark end of word
            return node.children.isEmpty(); // Return true if node has no children
        }

        char ch = word.charAt(index);
        TrieNode nextNode = node.children.get(ch);
        if (nextNode == null) {
            return false; // Word not in trie
        }

        boolean shouldDeleteChild = deleteHelper(nextNode, word, index + 1);

        if (shouldDeleteChild) {
            node.children.remove(ch);
            return node.children.isEmpty(); // Return true if node has no children
        }
        return false;
    }
}

// Trie Node class
class TrieNode {
    Map<Character, TrieNode> children;
    boolean isEndOfWord;

    public TrieNode() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

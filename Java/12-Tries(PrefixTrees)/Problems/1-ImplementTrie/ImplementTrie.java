import java.util.HashMap;
import java.util.Map;

// Implementation of Trie Data Structure in Java

// Approach 1: Using a Simple Array (for lowercase English alphabets)
class TrieNode1 {
    TrieNode1[] children;
    boolean isEndOfWord;

    public TrieNode1() {
        children = new TrieNode1[26]; // For 'a' to 'z'
        isEndOfWord = false;
    }
}

class Trie1 {
    private TrieNode1 root;

    public Trie1() {
        root = new TrieNode1();
    }

    // Inserts a word into the trie.
    public void insert(String word) {
        TrieNode1 node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                node.children[index] = new TrieNode1();
            }
            node = node.children[index];
        }
        node.isEndOfWord = true;
    }

    // Returns if the word is in the trie.
    public boolean search(String word) {
        TrieNode1 node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                return false;
            }
            node = node.children[index];
        }
        return node.isEndOfWord;
    }

    // Returns if there is any word in the trie that starts with the given prefix.
    public boolean startsWith(String prefix) {
        TrieNode1 node = root;
        for (char c : prefix.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                return false;
            }
            node = node.children[index];
        }
        return true;
    }
}

// Approach 2: Using a HashMap (for larger character sets)
class TrieNode2 {
    Map<Character, TrieNode2> children;
    boolean isEndOfWord;

    public TrieNode2() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

class Trie2 {
    private TrieNode2 root;

    public Trie2() {
        root = new TrieNode2();
    }

    public void insert(String word) {
        TrieNode2 node = root;
        for (char c : word.toCharArray()) {
            if (!node.children.containsKey(c)) {
                node.children.put(c, new TrieNode2());
            }
            node = node.children.get(c);
        }
        node.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode2 node = root;
        for (char c : word.toCharArray()) {
            if (!node.children.containsKey(c)) {
                return false;
            }
            node = node.children.get(c);
        }
        return node.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode2 node = root;
        for (char c : prefix.toCharArray()) {
            if (!node.children.containsKey(c)) {
                return false;
            }
            node = node.children.get(c);
        }
        return true;
    }
}

// Approach 3: Using a more space-optimized node structure (less memory per node)
class TrieNode3 {
    char data;
    TrieNode3[] children;
    boolean isEndOfWord;
    int count; // Number of words sharing this prefix

    public TrieNode3(char data) {
        this.data = data;
        this.children = new TrieNode3[26]; // For lowercase alphabets
        this.isEndOfWord = false;
        this.count = 0;
    }
}

class Trie3 {
    private TrieNode3 root;

    public Trie3() {
        root = new TrieNode3('\0'); // Root doesn't store a character
    }

    public void insert(String word) {
        TrieNode3 node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                node.children[index] = new TrieNode3(c);
            }
            node = node.children[index];
            node.count++;
        }
        node.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode3 node = root;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                return false;
            }
            node = node.children[index];
        }
        return node.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode3 node = root;
        for (char c : prefix.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                return false;
            }
            node = node.children[index];
        }
        return true;
    }

    public int countWordsWithPrefix(String prefix) {
        TrieNode3 node = root;
        for (char c : prefix.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null) {
                return 0;
            }
            node = node.children[index];
        }
        return node.count;
    }
}

// Approach 4: Using a LinkedList for children (Good for very sparse tries) - Not usually recommended for tries.
class TrieNode4 {
    char data;
    LinkedListNode child; // Head of the linked list of children
    boolean isEndOfWord;

    public TrieNode4(char data) {
        this.data = data;
        this.child = null;
        this.isEndOfWord = false;
    }
}

class LinkedListNode {
    TrieNode4 node;
    LinkedListNode next;

    public LinkedListNode(TrieNode4 node) {
        this.node = node;
        this.next = null;
    }
}

class Trie4 {
    private TrieNode4 root;

    public Trie4() {
        root = new TrieNode4('\0');
    }

    public void insert(String word) {
        TrieNode4 current = root;
        for (char c : word.toCharArray()) {
            LinkedListNode childNode = current.child;
            TrieNode4 nextNode = null;
            while (childNode != null) {
                if (childNode.node.data == c) {
                    nextNode = childNode.node;
                    break;
                }
                childNode = childNode.next;
            }
            if (nextNode == null) {
                nextNode = new TrieNode4(c);
                LinkedListNode newNode = new LinkedListNode(nextNode);
                newNode.next = current.child;
                current.child = newNode;
            }
            current = nextNode;
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode4 current = root;
        for (char c : word.toCharArray()) {
            LinkedListNode childNode = current.child;
            boolean found = false;
            while (childNode != null) {
                if (childNode.node.data == c) {
                    current = childNode.node;
                    found = true;
                    break;
                }
                childNode = childNode.next;
            }
            if (!found) {
                return false;
            }
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode4 current = root;
        for (char c : prefix.toCharArray()) {
            LinkedListNode childNode = current.child;
            boolean found = false;
            while (childNode != null) {
                if (childNode.node.data == c) {
                    current = childNode.node;
                    found = true;
                    break;
                }
                childNode = childNode.next;
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
}

// Approach 5: Using a compressed Trie (Radix Trie) -  Improves space efficiency for long common prefixes
class RadixTrieNode {
    String prefix;
    RadixTrieNode[] children;
    boolean isEndOfWord;

    public RadixTrieNode(String prefix) {
        this.prefix = prefix;
        this.children = new RadixTrieNode[26];
        this.isEndOfWord = false;
    }
}

class RadixTrie {
    private RadixTrieNode root;

    public RadixTrie() {
        root = new RadixTrieNode("");
    }

    public void insert(String word) {
        RadixTrieNode current = root;
        int index = 0;

        while (index < word.length()) {
            boolean foundMatch = false;
            for (int i = 0; i < 26; i++) {
                if (current.children[i] != null) {
                    String childPrefix = current.children[i].prefix;
                    int matchLength = commonPrefixLength(word, index, childPrefix);

                    if (matchLength > 0) {
                        foundMatch = true;
                        if (matchLength == childPrefix.length()) {
                            // Continue down the child node
                            index += matchLength;
                            current = current.children[i];
                            break; // Exit the inner loop and continue with the next character in word
                        } else {
                            // Split the child node
                            RadixTrieNode newChild = new RadixTrieNode(childPrefix.substring(matchLength));
                            newChild.isEndOfWord = current.children[i].isEndOfWord;
                            newChild.children = current.children[i].children;

                            current.children[i].prefix = childPrefix.substring(0, matchLength);
                            current.children[i].isEndOfWord = false;
                            current.children[i].children = new RadixTrieNode[26];
                            current.children[i].children[childPrefix.charAt(matchLength) - 'a'] = newChild;

                            index += matchLength;
                            current = current.children[i];
                            break;
                        }
                    }
                }
            }
            if (!foundMatch) {
                // No matching child found, create a new child
                String remaining = word.substring(index);
                RadixTrieNode newNode = new RadixTrieNode(remaining);
                int childIndex = word.charAt(index) - 'a';
                current.children[childIndex] = newNode;
                index = word.length(); // Exit the loop
            }
        }
        current.isEndOfWord = true;
    }

    private int commonPrefixLength(String word, int wordIndex, String prefix) {
        int length = 0;
        while (wordIndex + length < word.length() && length < prefix.length()
                && word.charAt(wordIndex + length) == prefix.charAt(length)) {
            length++;
        }
        return length;
    }

    public boolean search(String word) {
        RadixTrieNode current = root;
        int index = 0;

        while (index < word.length()) {
            boolean foundMatch = false;
            for (int i = 0; i < 26; i++) {
                if (current.children[i] != null) {
                    String childPrefix = current.children[i].prefix;
                    int matchLength = commonPrefixLength(word, index, childPrefix);
                    if (matchLength > 0) {
                        foundMatch = true;
                        if (matchLength == childPrefix.length()) {
                            index += matchLength;
                            current = current.children[i];
                            break;
                        } else {
                            return false; // Prefix doesn't fully match
                        }
                    }
                }
            }
            if (!foundMatch) {
                return false;
            }
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        RadixTrieNode current = root;
        int index = 0;

        while (index < prefix.length()) {
            boolean foundMatch = false;
            for (int i = 0; i < 26; i++) {
                if (current.children[i] != null) {
                    String childPrefix = current.children[i].prefix;
                    int matchLength = commonPrefixLength(prefix, index, childPrefix);
                    if (matchLength > 0) {
                        foundMatch = true;
                        if (matchLength <= childPrefix.length()) {
                            index += matchLength;
                            current = current.children[i];
                            if(matchLength == childPrefix.length() && index == prefix.length()){
                                return true;
                            }
                            break;
                        }
                    }
                }
            }
            if (!foundMatch) {
                return false;
            }
        }
        return true;
    }
}

// Example Usage (for Approach 1 - you can change it to use other approaches)
public class Main {
    public static void main(String[] args) {
        //Test code for Trie1
        Trie1 trie1 = new Trie1();
        trie1.insert("apple");
        trie1.insert("app");
        System.out.println("Search 'apple': " + trie1.search("apple")); // true
        System.out.println("Search 'app': " + trie1.search("app"));     // true
        System.out.println("Search 'ap': " + trie1.search("ap"));       // false
        System.out.println("StartsWith 'app': " + trie1.startsWith("app")); // true
        System.out.println("StartsWith 'ap': " + trie1.startsWith("ap"));  // true

        // Test code for Trie2
        Trie2 trie2 = new Trie2();
        trie2.insert("hello");
        trie2.insert("world");
        trie2.insert("he");
        System.out.println("\nSearch 'hello': " + trie2.search("hello")); // true
        System.out.println("Search 'world': " + trie2.search("world")); // true
        System.out.println("Search 'hell': " + trie2.search("hell"));   // false
        System.out.println("StartsWith 'he': " + trie2.startsWith("he"));  // true
        System.out.println("StartsWith 'hel': " + trie2.startsWith("hel")); // true

        // Test code for Trie3
        Trie3 trie3 = new Trie3();
        trie3.insert("cat");
        trie3.insert("car");
        trie3.insert("cattle");
        System.out.println("\nSearch 'cat': " + trie3.search("cat"));       // true
        System.out.println("Search 'car': " + trie3.search("car"));       // true
        System.out.println("Search 'cattle': " + trie3.search("cattle"));    // true
        System.out.println("Search 'ca': " + trie3.search("ca"));        // false
        System.out.println("StartsWith 'ca': " + trie3.startsWith("ca"));    // true
        System.out.println("Count words with prefix 'ca': " + trie3.countWordsWithPrefix("ca")); // 3

        // Test code for Trie4
        Trie4 trie4 = new Trie4();
        trie4.insert("dog");
        trie4.insert("door");
        trie4.insert("done");
        System.out.println("\nSearch 'dog': " + trie4.search("dog"));   // true
        System.out.println("Search 'door': " + trie4.search("door"));  // true
        System.out.println("Search 'done': " + trie4.search("done"));  // true
        System.out.println("Search 'do': " + trie4.search("do"));    // false
        System.out.println("StartsWith 'do': " + trie4.startsWith("do"));  // true

        // Test code for RadixTrie (Trie 5)
        RadixTrie trie5 = new RadixTrie();
        trie5.insert("flower");
        trie5.insert("flow");
        trie5.insert("flight");
        System.out.println("\nSearch 'flower': " + trie5.search("flower"));   // true
        System.out.println("Search 'flow': " + trie5.search("flow"));     // true
        System.out.println("Search 'flight': " + trie5.search("flight"));   // true
        System.out.println("Search 'flo': " + trie5.search("flo"));      // false
        System.out.println("StartsWith 'fl': " + trie5.startsWith("fl"));     // true
        System.out.println("StartsWith 'flo': " + trie5.startsWith("flo"));    // true
        System.out.println("StartsWith 'flower': " + trie5.startsWith("flower")); //true
    }
}

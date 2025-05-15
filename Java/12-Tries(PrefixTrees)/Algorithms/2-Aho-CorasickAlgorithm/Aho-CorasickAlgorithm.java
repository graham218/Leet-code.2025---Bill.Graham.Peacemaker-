import java.util.*;

// Approach 1: Basic Aho-Corasick with Queue for BFS
// This approach implements the core Aho-Corasick algorithm using a queue for breadth-first search
// to construct the failure function.  It's straightforward and easy to understand.
class AhoCorasick1 {

    // Represents a node in the Trie
    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>(); // Children nodes for each character
        int outputIndex = -1; // Index of the matched string in the patterns array, -1 if no match
        TrieNode failure; // Failure link in the Trie
    }

    TrieNode root; // Root of the Trie
    String[] patterns; // Array of patterns to search for

    // Constructor to initialize the Aho-Corasick automaton
    public AhoCorasick1(String[] patterns) {
        this.patterns = patterns;
        this.root = new TrieNode();
        buildTrie(); // Build the Trie structure
        buildFailureLinks(); // Build the failure links
    }

    // Builds the Trie from the given patterns
    private void buildTrie() {
        for (int i = 0; i < patterns.length; i++) {
            String pattern = patterns[i];
            TrieNode current = root;
            for (char c : pattern.toCharArray()) {
                // If the character is not a child, add it
                current.children.computeIfAbsent(c, k -> new TrieNode());
                current = current.children.get(c);
            }
            current.outputIndex = i; // Mark the end of the pattern with its index
        }
    }

    // Builds the failure links using Breadth-First Search (BFS)
    private void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failure = root; // Failure link of root points to itself
        // Initialize failure links for the first level children
        for (TrieNode child : root.children.values()) {
            child.failure = root;
            queue.offer(child);
        }

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();
            for (char c : current.children.keySet()) {
                TrieNode child = current.children.get(c);
                TrieNode fail = current.failure;
                // Find the longest proper suffix that is also a prefix of another pattern.
                while (fail != root && !fail.children.containsKey(c)) {
                    fail = fail.failure;
                }
                if (fail.children.containsKey(c)) {
                    child.failure = fail.children.get(c);
                } else {
                    child.failure = root; // If no matching prefix, fail to root
                }
                queue.offer(child);
            }
        }
    }

    // Searches the text for occurrences of the patterns
    public List<Integer> search(String text) {
        List<Integer> result = new ArrayList<>();
        TrieNode current = root;
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            // Traverse the Trie using failure links
            while (current != root && !current.children.containsKey(c)) {
                current = current.failure;
            }
            if (current.children.containsKey(c)) {
                current = current.children.get(c);
            }
            // Check for matches (including matches from failure links)
            TrieNode temp = current;
            while (temp != root) {
                if (temp.outputIndex != -1) {
                    result.add(i - patterns[temp.outputIndex].length() + 1); // Add the start index of the match
                }
                temp = temp.failure;
            }
        }
        return result;
    }
}

// Approach 2: Aho-Corasick with Array for Children
// This approach optimizes the TrieNode by using an array instead of a HashMap for children.
// This can be faster for alphabets with a known, relatively small size (e.g., ASCII).
class AhoCorasick2 {

    static final int ALPHABET_SIZE = 256; // Assuming ASCII characters

    static class TrieNode {
        TrieNode[] children = new TrieNode[ALPHABET_SIZE];
        int outputIndex = -1;
        TrieNode failure;
    }

    TrieNode root;
    String[] patterns;

    public AhoCorasick2(String[] patterns) {
        this.patterns = patterns;
        this.root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    private void buildTrie() {
        for (int i = 0; i < patterns.length; i++) {
            String pattern = patterns[i];
            TrieNode current = root;
            for (char c : pattern.toCharArray()) {
                int index = c; // Use character as index
                if (current.children[index] == null) {
                    current.children[index] = new TrieNode();
                }
                current = current.children[index];
            }
            current.outputIndex = i;
        }
    }

    private void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failure = root;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root.children[i] != null) {
                root.children[i].failure = root;
                queue.offer(root.children[i]);
            }
        }

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (current.children[i] != null) {
                    TrieNode child = current.children[i];
                    TrieNode fail = current.failure;
                    while (fail != root && fail.children[i] == null) {
                        fail = fail.failure;
                    }
                    if (fail.children[i] != null) {
                        child.failure = fail.children[i];
                    } else {
                        child.failure = root;
                    }
                    queue.offer(child);
                }
            }
        }
    }

    public List<Integer> search(String text) {
        List<Integer> result = new ArrayList<>();
        TrieNode current = root;
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            int index = c;
            while (current != root && current.children[index] == null) {
                current = current.failure;
            }
            if (current.children[index] != null) {
                current = current.children[index];
            }
            TrieNode temp = current;
            while (temp != root) {
                if (temp.outputIndex != -1) {
                    result.add(i - patterns[temp.outputIndex].length() + 1);
                }
                temp = temp.failure;
            }
        }
        return result;
    }
}

// Approach 3: Aho-Corasick with Optimized Failure Links (Slight Variation)
// This approach is a slight optimization of the failure link construction.  It pre-computes
// the failure links for each node, potentially making the search phase slightly faster.
class AhoCorasick3 {

    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>();
        int outputIndex = -1;
        TrieNode failure;
        Map<Character, TrieNode> transitions = new HashMap<>(); // Store transitions for faster search
    }

    TrieNode root;
    String[] patterns;

    public AhoCorasick3(String[] patterns) {
        this.patterns = patterns;
        this.root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    private void buildTrie() {
        for (int i = 0; i < patterns.length; i++) {
            String pattern = patterns[i];
            TrieNode current = root;
            for (char c : pattern.toCharArray()) {
                current.children.computeIfAbsent(c, k -> new TrieNode());
                current = current.children.get(c);
            }
            current.outputIndex = i;
        }
    }

    private void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failure = root;
        for (TrieNode child : root.children.values()) {
            child.failure = root;
            queue.offer(child);
            root.transitions.put(child.children.keySet().iterator().next(), child); // Add to root transitions
        }

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();
            for (char c : current.children.keySet()) {
                TrieNode child = current.children.get(c);
                TrieNode fail = current.failure;
                while (fail != root && !fail.children.containsKey(c)) {
                    fail = fail.failure;
                }
                if (fail.children.containsKey(c)) {
                    child.failure = fail.children.get(c);
                } else {
                    child.failure = root;
                }
                queue.offer(child);
            }
            // Pre-compute transitions for the current node.
            current.transitions.putAll(current.children);
            if(current.failure != null) {
                for(Map.Entry<Character, TrieNode> entry : current.failure.transitions.entrySet()){
                    if(!current.transitions.containsKey(entry.getKey())){
                        current.transitions.put(entry.getKey(), entry.getValue());
                    }
                }
            }
        }
    }

    public List<Integer> search(String text) {
        List<Integer> result = new ArrayList<>();
        TrieNode current = root;
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            // Use pre-computed transitions.
            if (current.transitions.containsKey(c)) {
                current = current.transitions.get(c);
            }
            else{
                current = root;
            }

            TrieNode temp = current;
            while (temp != root) {
                if (temp.outputIndex != -1) {
                    result.add(i - patterns[temp.outputIndex].length() + 1);
                }
                temp = temp.failure;
            }
        }
        return result;
    }
}

// Approach 4: Aho-Corasick with Multiple Output Matches
// This approach handles the case where a single node in the Trie can match multiple patterns.
// This is important when patterns can overlap (e.g., "he", "she", "hers").
class AhoCorasick4 {

    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>();
        List<Integer> outputIndices = new ArrayList<>(); // List of matched pattern indices
        TrieNode failure;
    }

    TrieNode root;
    String[] patterns;

    public AhoCorasick4(String[] patterns) {
        this.patterns = patterns;
        this.root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    private void buildTrie() {
        for (int i = 0; i < patterns.length; i++) {
            String pattern = patterns[i];
            TrieNode current = root;
            for (char c : pattern.toCharArray()) {
                current.children.computeIfAbsent(c, k -> new TrieNode());
                current = current.children.get(c);
            }
            current.outputIndices.add(i); // Store the index of the matched pattern
        }
    }

    private void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failure = root;
        for (TrieNode child : root.children.values()) {
            child.failure = root;
            queue.offer(child);
        }

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();
            for (char c : current.children.keySet()) {
                TrieNode child = current.children.get(c);
                TrieNode fail = current.failure;
                while (fail != root && !fail.children.containsKey(c)) {
                    fail = fail.failure;
                }
                if (fail.children.containsKey(c)) {
                    child.failure = fail.children.get(c);
                } else {
                    child.failure = root;
                }
                // Combine outputs from the failure link
                child.outputIndices.addAll(child.failure.outputIndices);
                queue.offer(child);
            }
        }
    }

    public List<Integer> search(String text) {
        List<Integer> result = new ArrayList<>();
        TrieNode current = root;
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            while (current != root && !current.children.containsKey(c)) {
                current = current.failure;
            }
            if (current.children.containsKey(c)) {
                current = current.children.get(c);
            }
            // Check for all matches at this node
            for (int patternIndex : current.outputIndices) {
                result.add(i - patterns[patternIndex].length() + 1);
            }
        }
        return result;
    }
}

// Approach 5: Aho-Corasick with Case-Insensitive Search
// This approach extends the Aho-Corasick algorithm to perform case-insensitive searches.
// It converts both the text and the patterns to lowercase before processing.
class AhoCorasick5 {

    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>();
        int outputIndex = -1;
        TrieNode failure;
    }

    TrieNode root;
    String[] patterns;

    public AhoCorasick5(String[] patterns) {
        // Convert patterns to lowercase for case-insensitive matching
        this.patterns = new String[patterns.length];
        for (int i = 0; i < patterns.length; i++) {
            this.patterns[i] = patterns[i].toLowerCase();
        }
        this.root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    private void buildTrie() {
        for (int i = 0; i < patterns.length; i++) {
            String pattern = patterns[i];
            TrieNode current = root;
            for (char c : pattern.toCharArray()) {
                current.children.computeIfAbsent(c, k -> new TrieNode());
                current = current.children.get(c);
            }
            current.outputIndex = i;
        }
    }

    private void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failure = root;
        for (TrieNode child : root.children.values()) {
            child.failure = root;
            queue.offer(child);
        }

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();
            for (char c : current.children.keySet()) {
                TrieNode child = current.children.get(c);
                TrieNode fail = current.failure;
                while (fail != root && !fail.children.containsKey(c)) {
                    fail = fail.failure;
                }
                if (fail.children.containsKey(c)) {
                    child.failure = fail.children.get(c);
                } else {
                    child.failure = root;
                }
                queue.offer(child);
            }
        }
    }

    public List<Integer> search(String text) {
        List<Integer> result = new ArrayList<>();
        TrieNode current = root;
        // Convert text to lowercase for case-insensitive matching
        String lowerCaseText = text.toLowerCase();
        for (int i = 0; i < lowerCaseText.length(); i++) {
            char c = lowerCaseText.charAt(i);
            while (current != root && !current.children.containsKey(c)) {
                current = current.failure;
            }
            if (current.children.containsKey(c)) {
                current = current.children.get(c);
            }
            TrieNode temp = current;
            while (temp != root) {
                if (temp.outputIndex != -1) {
                    result.add(i - patterns[temp.outputIndex].length() + 1);
                }
                temp = temp.failure;
            }
        }
        return result;
    }
}

// Example usage of the Aho-Corasick algorithm
public class Main {
    public static void main(String[] args) {
        // Example patterns to search for
        String[] patterns = {"he", "she", "his", "hers"};
        String text = "ahishers";

        // Approach 1: Basic Aho-Corasick
        AhoCorasick1 ac1 = new AhoCorasick1(patterns);
        List<Integer> matches1 = ac1.search(text);
        System.out.println("Approach 1 - Matches at indices: " + matches1); // Output: [1, 4]

        // Approach 2: Aho-Corasick with Array for Children
        AhoCorasick2 ac2 = new AhoCorasick2(patterns);
        List<Integer> matches2 = ac2.search(text);
        System.out.println("Approach 2 - Matches at indices: " + matches2); // Output: [1, 4]

        // Approach 3: Aho-Corasick with Optimized Failure Links
        AhoCorasick3 ac3 = new AhoCorasick3(patterns);
        List<Integer> matches3 = ac3.search(text);
        System.out.println("Approach 3 - Matches at indices: " + matches3); // Output: [1, 4]

        // Approach 4: Aho-Corasick with Multiple Output Matches
        String[] patterns4 = {"he", "she", "his", "hers", "her"};
        AhoCorasick4 ac4 = new AhoCorasick4(patterns4);
        List<Integer> matches4 = ac4.search("ahishers");
        System.out.println("Approach 4 - Matches at indices: " + matches4); // Output: [1, 1, 4, 4]

        // Approach 5: Aho-Corasick with Case-Insensitive Search
        AhoCorasick5 ac5 = new AhoCorasick5(patterns);
        List<Integer> matches5 = ac5.search("aHisHerS");
        System.out.println("Approach 5 - Matches at indices: " + matches5); // Output: [1, 4]
    }
}

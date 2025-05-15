import java.util.*;

// Class for Trie
class Trie {
    public static void main(String[] args) { // Added main method
        WordSearchII solution = new WordSearchII();
        char[][] board = {
                {'o', 'a', 'a', 'n'},
                {'e', 't', 'a', 'e'},
                {'i', 'h', 'k', 'r'},
                {'i', 'f', 'l', 'v'}
        };
        String[] words = {"oath", "pea", "eat", "rain"};

        // Approach 1
        List<String> result1 = solution.findWords1(board, words);
        System.out.println("Approach 1: " + result1);

        // Approach 2
        List<String> result2 = solution.findWords2(board, words);
        System.out.println("Approach 2: " + result2);

        // Approach 3
        List<String> result3 = solution.findWords3(board, words);
        System.out.println("Approach 3: " + result3);

        // Approach 4
        List<String> result4 = solution.findWords4(board, words);
        System.out.println("Approach 4: " + result4);

        // Approach 5
        List<String> result5 = solution.findWords5(board, words);
        System.out.println("Approach 5: " + result5);
    }

    TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    public void insert(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            if (!node.children.containsKey(c)) {
                node.children.put(c, new TrieNode());
            }
            node = node.children.get(c);
        }
        node.word = word; // Mark the end of the word
        node.isWord = true;
    }

    // Search for a word in the Trie
    public boolean search(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            if (!node.children.containsKey(c)) {
                return false;
            }
            node = node.children.get(c);
        }
        return node.isWord;
    }

    // Check if there is any word in the trie starting with the given prefix.
    public boolean startsWith(String prefix) {
        TrieNode node = root;
        for (char c : prefix.toCharArray()) {
            if (!node.children.containsKey(c)) {
                return false;
            }
            node = node.children.get(c);
        }
        return true;
    }
}

public class WordSearchII {

    // 1.  Backtracking with Trie (Optimized)
    //    - Builds a Trie from the words, then performs DFS on the board.
    //    - Uses the Trie to efficiently check for word prefixes and complete words.
    //    - Avoids redundant searches by marking visited cells.
    //    - Prunes search paths that don't lead to any word.
    public List<String> findWords1(char[][] board, String[] words) {
        List<String> result = new ArrayList<>();
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs1(board, i, j, trie.root, visited, result);
            }
        }
        return result;
    }

    private void dfs1(char[][] board, int row, int col, TrieNode node, boolean[][] visited, List<String> result) {
        int rows = board.length;
        int cols = board[0].length;

        // Base cases: out of bounds or already visited
        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        char c = board[row][col];
        if (!node.children.containsKey(c)) {
            return; // No word with this prefix
        }

        node = node.children.get(c);
        if (node.isWord) { //if (node.word != null)
            if(!result.contains(node.word)) // Avoid duplicates
                result.add(node.word);
        }

        visited[row][col] = true; // Mark as visited
        int[] dr = {0, 0, 1, -1};
        int[] dc = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            dfs1(board, row + dr[i], col + dc[i], node, visited, result);
        }
        visited[row][col] = false; // Backtrack: unmark for other paths
    }



    // 2. Backtracking with Trie and Optimized Pruning
    //    - Similar to Approach 1, but with more aggressive pruning during Trie traversal.
    //    - After finding a word, the corresponding node in the Trie is marked (or removed).
    //    - This prevents finding the same word multiple times and avoids unnecessary exploration.
    public List<String> findWords2(char[][] board, String[] words) {
        List<String> result = new ArrayList<>();
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs2(board, i, j, trie.root, visited, result);
            }
        }
        return result;
    }

    private void dfs2(char[][] board, int row, int col, TrieNode node, boolean[][] visited, List<String> result) {
        int rows = board.length;
        int cols = board[0].length;

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        char c = board[row][col];
        TrieNode nextNode = node.children.get(c);
        if (nextNode == null) {
            return;
        }

        visited[row][col] = true;
        if (nextNode.isWord) {
            result.add(nextNode.word);
            nextNode.isWord = false; //important
        }

        int[] dr = {0, 0, 1, -1};
        int[] dc = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            dfs2(board, row + dr[i], col + dc[i], nextNode, visited, result);
        }
        visited[row][col] = false;
    }



    // 3. Backtracking with Trie and Deletion
    //    - Similar to Approach 2, but instead of just marking a word as found, it deletes the word from the Trie.
    //    - This is the most aggressive pruning, ensuring that no duplicate words are found.
    //    - Can modify the original Trie, so if the Trie is needed elsewhere, a copy should be used.
    public List<String> findWords3(char[][] board, String[] words) {
        List<String> result = new ArrayList<>();
        Trie trie = new Trie();
        for (String word : words) {
            trie.insert(word);
        }

        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs3(board, i, j, trie.root, visited, result);
            }
        }
        return result;
    }

    private void dfs3(char[][] board, int row, int col, TrieNode node, boolean[][] visited, List<String> result) {
        int rows = board.length;
        int cols = board[0].length;

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        char c = board[row][col];
        TrieNode nextNode = node.children.get(c);
        if (nextNode == null) {
            return;
        }

        visited[row][col] = true;
        if (nextNode.isWord) {
            result.add(nextNode.word);
            removeWord(node, c); // Remove the word from Trie
            return; //important
        }

        int[] dr = {0, 0, 1, -1};
        int[] dc = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            dfs3(board, row + dr[i], col + dc[i], nextNode, visited, result);
        }
        visited[row][col] = false;
    }

    private void removeWord(TrieNode parent, char c) {
        TrieNode node = parent.children.get(c);
        if (node == null) return;

        if (node.children.isEmpty()) {
            parent.children.remove(c);
        } else {
            node.isWord = false;
            node.word = null;
        }
    }


    // 4. Using HashSet and Backtracking (Basic)
    //    -  A basic approach that uses a HashSet to store the words.
    //    -  Performs backtracking on the board and checks if any formed string is present in the HashSet.
    //    -  Less efficient than Trie-based approaches, as it checks the entire word against the set in each step.
    public List<String> findWords4(char[][] board, String[] words) {
        Set<String> wordSet = new HashSet<>(Arrays.asList(words));
        List<String> result = new ArrayList<>();
        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];
        StringBuilder currentWord = new StringBuilder();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs4(board, i, j, wordSet, visited, currentWord, result);
            }
        }
        return result;
    }

    private void dfs4(char[][] board, int row, int col, Set<String> wordSet, boolean[][] visited, StringBuilder currentWord, List<String> result) {
        int rows = board.length;
        int cols = board[0].length;

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        visited[row][col] = true;
        currentWord.append(board[row][col]);
        String currentString = currentWord.toString();

        if (wordSet.contains(currentString)) {
            if(!result.contains(currentString))
                result.add(currentString);
        }

        int[] dr = {0, 0, 1, -1};
        int[] dc = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            dfs4(board, row + dr[i], col + dc[i], wordSet, visited, currentWord, result);
        }

        visited[row][col] = false;
        currentWord.deleteCharAt(currentWord.length() - 1); // Backtrack
    }



    // 5.  Backtracking with Prefix Checking (Optimization of Approach 4)
    //     - Optimizes Approach 4 by checking if the current string is a prefix of any word in the word list.
    //     - This optimization reduces unnecessary exploration when the current path cannot lead to a valid word.
    public List<String> findWords5(char[][] board, String[] words) {
        Set<String> wordSet = new HashSet<>(Arrays.asList(words));
        List<String> result = new ArrayList<>();
        int rows = board.length;
        int cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];
        StringBuilder currentWord = new StringBuilder();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs5(board, i, j, wordSet, visited, currentWord, result, words);
            }
        }
        return result;
    }

    private void dfs5(char[][] board, int row, int col, Set<String> wordSet, boolean[][] visited, StringBuilder currentWord, List<String> result, String[] words) {
        int rows = board.length;
        int cols = board[0].length;

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col]) {
            return;
        }

        visited[row][col] = true;
        currentWord.append(board[row][col]);
        String currentString = currentWord.toString();

        if (wordSet.contains(currentString)) {
            if(!result.contains(currentString))
                result.add(currentString);
        }

        if (isPrefix(currentString, words)) { // Optimization: Check if it's a prefix
            int[] dr = {0, 0, 1, -1};
            int[] dc = {1, -1, 0, 0};
            for (int i = 0; i < 4; i++) {
                dfs5(board, row + dr[i], col + dc[i], wordSet, visited, currentWord, result, words);
            }
        }


        visited[row][col] = false;
        currentWord.deleteCharAt(currentWord.length() - 1);
    }

    private boolean isPrefix(String str, String[] words) {
        for (String word : words) {
            if (word.startsWith(str)) {
                return true;
            }
        }
        return false;
    }
}

// Class for Trie Node
class TrieNode {
    Map<Character, TrieNode> children;
    String word; // Stores the complete word if this node is the end of a word
    boolean isWord; //redundant, but kept for clarity
    public TrieNode() {
        children = new HashMap<>();
        word = null;
        isWord = false;
    }
}
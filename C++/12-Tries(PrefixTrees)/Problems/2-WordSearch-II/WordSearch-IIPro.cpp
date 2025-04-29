#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue> // Include the queue header

using namespace std;

// Approach 1: Basic Trie with DFS
// - Builds a Trie from the words.
// - Performs DFS on the board, checking for word prefixes in the Trie.
// - Simple to understand, but can be slow for large boards and word lists.

struct TrieNode1 {
    unordered_map<char, TrieNode1*> children;
    bool isWord = false;
    string word; // Store the complete word here
    TrieNode1() {}
};

class Trie1 {
public:
    TrieNode1* root;
    Trie1() {
        root = new TrieNode1();
    }

    void insert(string word) {
        TrieNode1* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode1();
            }
            node = node->children[c];
        }
        node->isWord = true;
        node->word = word; // Store the word at the leaf
    }
};

class Solution1 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie1 trie;
        for (string word : words) {
            trie.insert(word);
        }

        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, i, j, trie.root, visited, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int row, int col, TrieNode1* node, vector<vector<bool>>& visited, vector<string>& result) {
        int rows = board.size();
        int cols = board[0].size();

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || !node->children[board[row][col]]) {
            return;
        }

        visited[row][col] = true;
        node = node->children[board[row][col]];

        if (node->isWord) {
            result.push_back(node->word);
            node->isWord = false; // Avoid duplicates
        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            dfs(board, row + dr[i], col + dc[i], node, visited, result);
        }
        visited[row][col] = false;
    }
};

// Approach 2: Optimized Trie with Visited Tracking in TrieNode
// - Similar to Approach 1, but tracks visited status in the TrieNode itself.
// - Avoids the extra `visited` matrix, potentially improving performance.

struct TrieNode2 {
    unordered_map<char, TrieNode2*> children;
    bool isWord = false;
    string word;
    bool visited = false; // Track visited status in TrieNode
    TrieNode2() {}
};

class Trie2 {
public:
    TrieNode2* root;
    Trie2() {
        root = new TrieNode2();
    }

    void insert(string word) {
        TrieNode2* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode2();
            }
            node = node->children[c];
        }
        node->isWord = true;
        node->word = word;
    }
};

class Solution2 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie2 trie;
        for (string word : words) {
            trie.insert(word);
        }

        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, i, j, trie.root, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int row, int col, TrieNode2* node, vector<string>& result) {
        int rows = board.size();
        int cols = board[0].size();

        if (row < 0 || row >= rows || col < 0 || col >= cols || !node->children[board[row][col]]) {
            return;
        }

        node = node->children[board[row][col]];
        if(node->visited) return; //if the node is visited, stop exploring

        if (node->isWord) {
            result.push_back(node->word);
            node->isWord = false; // prevent duplicate
            node->visited = true; // Mark the word as found

        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            dfs(board, row + dr[i], col + dc[i], node, result);
        }
        node->visited = false; // Backtrack: unmark visited for other paths
    }
};

// Approach 3: Trie with Prefix Hashing Optimization
// - Uses a Trie, but optimizes prefix checking with hashing.
// - Stores hashes of prefixes in the Trie nodes.
// - Faster prefix checks can improve overall performance.
//   This approach is more complex and might not always provide a significant
//   performance boost in all cases, but it's a good example of a potential
//   optimization technique.

struct TrieNode3 {
    unordered_map<char, TrieNode3*> children;
    bool isWord = false;
    string word;
    size_t prefixHash = 0; // Store hash of the prefix
    TrieNode3() {}
};

class Trie3 {
public:
    TrieNode3* root;
    hash<string> str_hash;

    Trie3() {
        root = new TrieNode3();
    }

    void insert(string word) {
        TrieNode3* node = root;
        string prefix = "";
        for (char c : word) {
            prefix += c;
            if (!node->children[c]) {
                node->children[c] = new TrieNode3();
            }
            node = node->children[c];
            node->prefixHash = str_hash(prefix); // Calculate prefix hash
        }
        node->isWord = true;
        node->word = word;
    }

    size_t getPrefixHash(const string& prefix) {
        return str_hash(prefix);
    }
};

class Solution3 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie3 trie;
        for (string word : words) {
            trie.insert(word);
        }

        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, i, j, trie.root, visited, result, "");
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int row, int col, TrieNode3* node, vector<vector<bool>>& visited, vector<string>& result, string currentPrefix) {
        int rows = board.size();
        int cols = board[0].size();

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || !node->children[board[row][col]]) {
            return;
        }

        visited[row][col] = true;
        char currentChar = board[row][col];
        currentPrefix += currentChar;
        TrieNode3* nextNode = node->children[currentChar];

        if (nextNode->prefixHash != trie.getPrefixHash(currentPrefix)) {
             visited[row][col] = false;
             return;
        }

        node = nextNode;

        if (node->isWord) {
            result.push_back(node->word);
            node->isWord = false;
        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            dfs(board, row + dr[i], col + dc[i], node, visited, result, currentPrefix);
        }
        visited[row][col] = false;
    }
    Trie3 trie;
};

// Approach 4: Aho-Corasick Algorithm
// - Implements the Aho-Corasick algorithm for efficient multi-pattern searching.
// - Builds a state machine (Trie with failure links).
// - Processes the board in a single pass, finding all matching words.
// - Generally the most efficient approach for this problem.

struct TrieNode4 {
    unordered_map<char, TrieNode4*> children;
    bool isWord = false;
    string word;
    TrieNode4* failure = nullptr; // Failure link for Aho-Corasick
    TrieNode4() {}
};

class Trie4 {
public:
    TrieNode4* root;
    Trie4() {
        root = new TrieNode4();
    }

    void insert(string word) {
        TrieNode4* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode4();
            }
            node = node->children[c];
        }
        node->isWord = true;
        node->word = word;
    }

    void buildFailureLinks() {
        queue<TrieNode4*> q; // Use std::queue
        root->failure = root; // Failure link for root is itself.
        for (auto& pair : root->children) {
            TrieNode4* child = pair.second;
            child->failure = root;
            q.push(child);
        }

        while (!q.empty()) {
            TrieNode4* node = q.front();
            q.pop();
            for (auto& pair : node->children) {
                char c = pair.first;
                TrieNode4* child = pair.second;
                TrieNode4* failure = node->failure;
                while (failure != root && !failure->children[c]) {
                    failure = failure->failure;
                }
                if (failure->children[c]) {
                    child->failure = failure->children[c];
                } else {
                    child->failure = root;
                }
                q.push(child);
            }
        }
    }
};

class Solution4 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie4 trie;
        for (string word : words) {
            trie.insert(word);
        }
        trie.buildFailureLinks();

        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;
        unordered_set<string> foundWords; // Use a set to avoid duplicates.

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                findMatches(board, i, j, trie.root, foundWords);
            }
        }
        for (const string& word : foundWords) {
            result.push_back(word);
        }
        return result;
    }

    void findMatches(vector<vector<char>>& board, int row, int col, TrieNode4* node, unordered_set<string>& foundWords) {
        int rows = board.size();
        int cols = board[0].size();
        if (row < 0 || row >= rows || col < 0 || col >= cols) return;

        char c = board[row][col];
        while (node != nullptr && !node->children[c]) {
            node = node->failure;
        }
        if (node == nullptr) return;  // No match

        node = node->children[c];
        TrieNode4* temp = node; // Important: Use a temporary pointer

        while (temp != nullptr) {
            if (temp->isWord) {
                foundWords.insert(temp->word);
                temp->isWord = false; // Remove word to avoid duplicates
            }
            temp = temp->failure;
        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            findMatches(board, row + dr[i], col + dc[i], node, foundWords);
        }
    }
};

// Approach 5: Optimized Aho-Corasick with Backtracking Pruning
// - Combines Aho-Corasick with pruning of the search space during backtracking.
// - Uses a modified DFS to explore the board, guided by the Aho-Corasick state machine.
// - Prunes branches that cannot lead to any word matches, improving efficiency.

struct TrieNode5 {
    unordered_map<char, TrieNode5*> children;
    bool isWord = false;
    string word;
    TrieNode5* failure = nullptr;
    bool hasChildren = false; // Optimization: Track if node has children
    TrieNode5() {}
};

class Trie5 {
public:
    TrieNode5* root;
    Trie5() {
        root = new TrieNode5();
    }

    void insert(string word) {
        TrieNode5* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode5();
            }
            node = node->children[c];
            node->hasChildren = true; // Set hasChildren for parent
        }
        node->isWord = true;
        node->word = word;
    }

    void buildFailureLinks() {
        queue<TrieNode5*> q; // Use std::queue
        root->failure = root;
        for (auto& pair : root->children) {
            TrieNode5* child = pair.second;
            child->failure = root;
            q.push(child);
        }

        while (!q.empty()) {
            TrieNode5* node = q.front();
            q.pop();
            for (auto& pair : node->children) {
                char c = pair.first;
                TrieNode5* child = pair.second;
                TrieNode5* failure = node->failure;
                while (failure != root && !failure->children[c]) {
                    failure = failure->failure;
                }
                if (failure->children[c]) {
                    child->failure = failure->children[c];
                } else {
                    child->failure = root;
                }
                q.push(child);
            }
        }
    }
};

class Solution5 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie5 trie;
        for (string word : words) {
            trie.insert(word);
        }
        trie.buildFailureLinks();

        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;
        unordered_set<string> foundWords;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, i, j, trie.root, foundWords);
            }
        }
        for (const string& word : foundWords) {
            result.push_back(word);
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int row, int col, TrieNode5* node, unordered_set<string>& foundWords) {
        int rows = board.size();
        int cols = board[0].size();
        if (row < 0 || row >= rows || col < 0 || col >= cols) return;

        char c = board[row][col];
        TrieNode5* nextNode = node->children[c];
        if (!nextNode) return;

        node = nextNode;

        TrieNode5* temp = node;
         while (temp != nullptr) {
            if (temp->isWord) {
                foundWords.insert(temp->word);
                temp->isWord = false;
            }
            temp = temp->failure;
        }

        // Pruning: Only explore if the current node has children
        if (node->hasChildren) {
            int dr[] = {0, 0, 1, -1};
            int dc[] = {1, -1, 0, 0};
            for (int i = 0; i < 4; ++i) {
                dfs(board, row + dr[i], col + dc[i], node, foundWords);
            }
        }
    }
};

int main() {
    // Example usage
    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };
    vector<string> words = {"oath", "pea", "eat", "rain"};

    Solution1 sol1;
    vector<string> result1 = sol1.findWords(board, words);
    cout << "Approach 1: ";
    for (string word : result1) {
        cout << word << " ";
    }
    cout << endl;

    Solution2 sol2;
    vector<string> result2 = sol2.findWords(board, words);
    cout << "Approach 2: ";
    for (string word : result2) {
        cout << word << " ";
    }
    cout << endl;

    Solution3 sol3;
    vector<string> result3 = sol3.findWords(board, words);
    cout << "Approach 3: ";
    for (string word : result3) {
        cout << word << " ";
    }
    cout << endl;

    Solution4 sol4;
    vector<string> result4 = sol4.findWords(board, words);
    cout << "Approach 4: ";
    for (string word : result4) {
        cout << word << " ";
    }
    cout << endl;

    Solution5 sol5;
    vector<string> result5 = sol5.findWords(board, words);
    cout << "Approach 5: ";
    for (string word : result5) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}

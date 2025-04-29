#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

// Approach 1: Brute Force (Time Limit Exceeded)
// For each word, iterate through the board and check if the word exists.
// Time Complexity: O(m * n * k * l), where m and n are board dimensions, k is the number of words, and l is the average word length.
// Space Complexity: O(1)
class Solution1 {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, int i, int j, string& word, int index) {
        if (index == word.length()) {
            return true;
        }

        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) {
            return false;
        }

        char temp = board[i][j];
        board[i][j] = '#'; // Mark as visited to avoid revisiting in the same path.
        bool found =  dfs(board, i + 1, j, word, index + 1) ||
                       dfs(board, i - 1, j, word, index + 1) ||
                       dfs(board, i, j + 1, word, index + 1) ||
                       dfs(board, i, j - 1, word, index + 1);
        board[i][j] = temp; // Backtrack: Restore the original character.
        return found;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        for (string word : words) {
            if (exist(board, word)) {
                result.push_back(word);
            }
        }
        return result;
    }
};

// Approach 2: Using HashSet (Optimization of Approach 1)
// Same as Brute Force but uses a HashSet to store the found words to avoid duplicates.
// Time Complexity: O(m * n * k * l), where m and n are board dimensions, k is the number of words, and l is the average word length.
// Space Complexity: O(min(k, m*n*l)),  where k is the number of words
class Solution2 {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, int i, int j, string& word, int index) {
        if (index == word.length()) {
            return true;
        }

        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) {
            return false;
        }

        char temp = board[i][j];
        board[i][j] = '#';
        bool found =  dfs(board, i + 1, j, word, index + 1) ||
                       dfs(board, i - 1, j, word, index + 1) ||
                       dfs(board, i, j + 1, word, index + 1) ||
                       dfs(board, i, j - 1, word, index + 1);
        board[i][j] = temp;
        return found;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_set<string> result_set;
        for (string word : words) {
            if (exist(board, word)) {
                result_set.insert(word);
            }
        }
        return vector<string>(result_set.begin(), result_set.end());
    }
};

// Approach 3: Trie + DFS
// Build a Trie from the word list.  Then, perform DFS on the board, checking for Trie prefixes.
// Time Complexity: O(m * n * 4^L), where m and n are board dimensions, and L is the maximum word length.
// Space Complexity: O(N), where N is the total number of characters in all words.
struct TrieNode {
    vector<TrieNode*> children;
    string word; // Stores the complete word if this node is the end of a word.

    TrieNode() : children(26, nullptr), word("") {}

    ~TrieNode() {
        for (TrieNode* child : children) {
            if (child) {
                delete child;
            }
        }
    }
};

class Solution3 {
private:
    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                int index = c - 'a';
                if (!node->children[index]) {
                    node->children[index] = new TrieNode();
                }
                node = node->children[index];
            }
            node->word = word; // Mark the end of the word.
        }
        return root;
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, unordered_set<string>& result) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '#' || !node) {
            return;
        }

        char c = board[i][j];
        int index = c - 'a';
        TrieNode* nextNode = node->children[index];
        if (!nextNode) return;

        if (nextNode->word != "") { // Found a word
            result.insert(nextNode->word);
        }

        board[i][j] = '#'; // Mark as visited
        dfs(board, i + 1, j, nextNode, result);
        dfs(board, i - 1, j, nextNode, result);
        dfs(board, i, j + 1, nextNode, result);
        dfs(board, i, j - 1, nextNode, result);
        board[i][j] = c; // Backtrack
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = buildTrie(words);
        unordered_set<string> result_set;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, result_set);
            }
        }
        delete root;
        return vector<string>(result_set.begin(), result_set.end());
    }
};

// Approach 4: Trie + DFS (Optimized - No word storage in Trie)
// Optimized Trie approach.  Instead of storing the entire word in the TrieNode, check for word completion during DFS.
// Time Complexity: O(m * n * 4^L), where m and n are board dimensions, and L is the maximum word length.
// Space Complexity: O(N), where N is the total number of characters in all words.
struct TrieNode4 {
    vector<TrieNode4*> children;
    bool isWord;

    TrieNode4() : children(26, nullptr), isWord(false) {}
      ~TrieNode4() {
        for (TrieNode4* child : children) {
            if (child) {
                delete child;
            }
        }
    }
};

class Solution4 {
private:
    TrieNode4* buildTrie(vector<string>& words) {
        TrieNode4* root = new TrieNode4();
        for (string& word : words) {
            TrieNode4* node = root;
            for (char c : word) {
                int index = c - 'a';
                if (!node->children[index]) {
                    node->children[index] = new TrieNode4();
                }
                node = node->children[index];
            }
            node->isWord = true;
        }
        return root;
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode4* node, string& currentWord, unordered_set<string>& result, vector<string>& words) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '#' || !node) {
            return;
        }

        char c = board[i][j];
        int index = c - 'a';
        TrieNode4* nextNode = node->children[index];
        if (!nextNode) return;

        currentWord += c;
        if (nextNode->isWord) {
            result.insert(currentWord);
        }

        board[i][j] = '#';
        dfs(board, i + 1, j, nextNode, currentWord, result, words);
        dfs(board, i - 1, j, nextNode, currentWord, result, words);
        dfs(board, i, j + 1, nextNode, currentWord, result, words);
        dfs(board, i, j - 1, nextNode, currentWord, result, words);
        board[i][j] = c;
        currentWord.pop_back();
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode4* root = buildTrie(words);
        unordered_set<string> result_set;
        string currentWord = "";
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, currentWord, result_set, words);
            }
        }
        delete root;
        return vector<string>(result_set.begin(), result_set.end());
    }
};

// Approach 5: Trie + Optimized DFS (Early Stopping)
// Further optimization: Stop DFS traversal as soon as it's clear no word can be formed.
// Time Complexity: O(m * n * 4^L), where m and n are board dimensions, and L is the maximum word length.
// Space Complexity: O(N), where N is the total number of characters in all words.

struct TrieNode5 {
    vector<TrieNode5*> children;
    bool isWord;
    int count; // Keep track of the number of words with this prefix

    TrieNode5() : children(26, nullptr), isWord(false), count(0) {}
      ~TrieNode5() {
        for (TrieNode5* child : children) {
            if (child) {
                delete child;
            }
        }
    }
};

class Solution5 {
private:
    TrieNode5* buildTrie(vector<string>& words) {
        TrieNode5* root = new TrieNode5();
        for (string& word : words) {
            TrieNode5* node = root;
            for (char c : word) {
                int index = c - 'a';
                if (!node->children[index]) {
                    node->children[index] = new TrieNode5();
                }
                node = node->children[index];
                node->count++;
            }
            node->isWord = true;
        }
        return root;
    }

     void dfs(vector<vector<char>>& board, int i, int j, TrieNode5* node, string& currentWord, unordered_set<string>& result) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '#' || !node || node->count == 0) {
            return;
        }

        char c = board[i][j];
        int index = c - 'a';
        TrieNode5* nextNode = node->children[index];
        if (!nextNode) return;

        currentWord += c;
        if (nextNode->isWord) {
            result.insert(currentWord);
        }

        board[i][j] = '#';
        nextNode->count--; // Important: Decrement count as we traverse

        dfs(board, i + 1, j, nextNode, currentWord, result);
        dfs(board, i - 1, j, nextNode, currentWord, result);
        dfs(board, i, j + 1, nextNode, currentWord, result);
        dfs(board, i, j - 1, nextNode, currentWord, result);

        board[i][j] = c;
        currentWord.pop_back();
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode5* root = buildTrie(words);
        unordered_set<string> result_set;
        string currentWord = "";
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, currentWord, result_set);
            }
        }
        delete root;
        return vector<string>(result_set.begin(), result_set.end());
    }
};

int main() {
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

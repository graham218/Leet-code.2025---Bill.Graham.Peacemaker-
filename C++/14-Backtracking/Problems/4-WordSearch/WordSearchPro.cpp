#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

// Approach 1: Classic Backtracking with visited matrix
// Suitable for most cases, clear and easy to understand
class Solution1 {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty() || board[0].empty()) return false;

        int m = board.size(), n = board[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int index,
             int i, int j, std::vector<std::vector<bool>>& visited) {
        if (index == word.size()) return true; // All characters matched
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            visited[i][j] || board[i][j] != word[index]) {
            return false;
        }

        visited[i][j] = true; // Mark as visited

        // Explore 4 directions
        bool found = dfs(board, word, index + 1, i + 1, j, visited) ||
                     dfs(board, word, index + 1, i - 1, j, visited) ||
                     dfs(board, word, index + 1, i, j + 1, visited) ||
                     dfs(board, word, index + 1, i, j - 1, visited);

        visited[i][j] = false; // Backtrack
        return found;
    }
};

// Approach 2: Backtracking with board modification (no extra space)
// More memory efficient but modifies the original board
class Solution2 {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty() || board[0].empty()) return false;

        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int index, int i, int j) {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }

        char temp = board[i][j];
        board[i][j] = '#'; // Mark as visited by changing the value

        bool found = dfs(board, word, index + 1, i + 1, j) ||
                     dfs(board, word, index + 1, i - 1, j) ||
                     dfs(board, word, index + 1, i, j + 1) ||
                     dfs(board, word, index + 1, i, j - 1);

        board[i][j] = temp; // Backtrack by restoring the original value
        return found;
    }
};

// Approach 3: Backtracking with early pruning (check if all letters exist first)
// Optimized for cases where the word has letters not in the board
class Solution3 {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty() || board[0].empty()) return false;

        // Early pruning: check if all letters in word exist in board
        if (!checkLetters(board, word)) {
            return false;
        }

        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // Checks if all letters in the word exist in the board with sufficient frequency
    bool checkLetters(const std::vector<std::vector<char>>& board, const std::string& word) {
        std::unordered_multiset<char> boardLetters;
        std::unordered_multiset<char> wordLetters(word.begin(), word.end());

        for (const auto& row : board) {
            for (char c : row) {
                boardLetters.insert(c);
            }
        }

        for (char c : wordLetters) {
            if (boardLetters.count(c) < wordLetters.count(c)) {
                return false;
            }
        }
        return true;
    }

    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int index, int i, int j) {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }

        char temp = board[i][j];
        board[i][j] = '#';

        bool found = dfs(board, word, index + 1, i + 1, j) ||
                     dfs(board, word, index + 1, i - 1, j) ||
                     dfs(board, word, index + 1, i, j + 1) ||
                     dfs(board, word, index + 1, i, j - 1);

        board[i][j] = temp;
        return found;
    }
};

// Approach 4: Backtracking with direction vectors (cleaner direction handling)
// More maintainable when directions might change or expand
class Solution4 {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty() || board[0].empty()) return false;

        int m = board.size(), n = board[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        // Define 4 possible directions: up, down, left, right
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, 0, i, j, visited, directions)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int index,
             int i, int j, std::vector<std::vector<bool>>& visited,
             const std::vector<std::pair<int, int>>& directions) {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            visited[i][j] || board[i][j] != word[index]) {
            return false;
        }

        visited[i][j] = true;

        // Explore all directions
        for (const auto& dir : directions) {
            if (dfs(board, word, index + 1, i + dir.first, j + dir.second, visited, directions)) {
                return true;
            }
        }

        visited[i][j] = false;
        return false;
    }
};

// Approach 5: Backtracking with prefix check (optimized for large boards with dictionary)
// Useful when searching for multiple words (like in Boggle)
class Solution5 {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty() || board[0].empty()) return false;

        int m = board.size(), n = board[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        // First check if first and last characters exist in sufficient quantity
        if (count(board, word[0]) >
            count(board, word.back())) {
            std::reverse(word.begin(), word.end());
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0] &&
                    dfs(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int index,
             int i, int j, std::vector<std::vector<bool>>& visited) {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            visited[i][j] || board[i][j] != word[index]) {
            return false;
        }

        visited[i][j] = true;

        bool found = dfs(board, word, index + 1, i + 1, j, visited) ||
                     dfs(board, word, index + 1, i - 1, j, visited) ||
                     dfs(board, word, index + 1, i, j + 1, visited) ||
                     dfs(board, word, index + 1, i, j - 1, visited);

        visited[i][j] = false;
        return found;
    }

    // Counts the occurrences of a character in the entire board
    int count(const std::vector<std::vector<char>>& board, char c) {
        int cnt = 0;
        for (const auto& row : board) {
            cnt += std::count(row.begin(), row.end(), c);
        }
        return cnt;
    }
};

// Test cases
void testWordSearch() {
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    std::string word1 = "ABCCED";
    std::string word2 = "SEE";
    std::string word3 = "ABCB";

    std::cout << "Testing Solution1 (Classic Backtracking):" << std::endl;
    Solution1 s1;
    std::cout << "ABCCED: " << (s1.exist(board, word1) ? "Found" : "Not Found") << std::endl;
    std::cout << "SEE: " << (s1.exist(board, word2) ? "Found" : "Not Found") << std::endl;
    std::cout << "ABCB: " << (s1.exist(board, word3) ? "Found" : "Not Found") << std::endl;

    std::cout << "\nTesting Solution2 (Board Modification):" << std::endl;
    Solution2 s2;
    std::cout << "ABCCED: " << (s2.exist(board, word1) ? "Found" : "Not Found") << std::endl;
    std::cout << "SEE: " << (s2.exist(board, word2) ? "Found" : "Not Found") << std::endl;
    std::cout << "ABCB: " << (s2.exist(board, word3) ? "Found" : "Not Found") << std::endl;

    std::cout << "\nTesting Solution3 (Early Pruning):" << std::endl;
    Solution3 s3;
    std::cout << "ABCCED: " << (s3.exist(board, word1) ? "Found" : "Not Found") << std::endl;
    std::cout << "SEE: " << (s3.exist(board, word2) ? "Found" : "Not Found") << std::endl;
    std::cout << "ABCB: " << (s3.exist(board, word3) ? "Found" : "Not Found") << std::endl;

    std::cout << "\nTesting Solution4 (Direction Vectors):" << std::endl;
    Solution4 s4;
    std::cout << "ABCCED: " << (s4.exist(board, word1) ? "Found" : "Not Found") << std::endl;
    std::cout << "SEE: " << (s4.exist(board, word2) ? "Found" : "Not Found") << std::endl;
    std::cout << "ABCB: " << (s4.exist(board, word3) ? "Found" : "Not Found") << std::endl;

    std::cout << "\nTesting Solution5 (Prefix Check):" << std::endl;
    Solution5 s5;
    std::cout << "ABCCED: " << (s5.exist(board, word1) ? "Found" : "Not Found") << std::endl;
    std::cout << "SEE: " << (s5.exist(board, word2) ? "Found" : "Not Found") << std::endl;
    std::cout << "ABCB: " << (s5.exist(board, word3) ? "Found" : "Not Found") << std::endl;
}

int main() {
    testWordSearch();
    return 0;
}
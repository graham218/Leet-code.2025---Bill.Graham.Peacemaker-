#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional> // Include for std::function
#include <stack>    // Include for std::stack
#include <tuple>    // Include for std::tuple

using namespace std;

// Approach 1: Basic Backtracking
// - Uses a recursive function to explore possible paths in the board.
// - Marks visited cells to avoid cycles.
// - Simple and easy to understand.
bool exist_basic(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();

    // Helper function for backtracking
    std::function<bool(int, int, int)> backtrack =  // Use std::function
        [&](int row, int col, int index) {
        // Base case: If the whole word is found, return true
        if (index == word.size()) {
            return true;
        }

        // Check boundaries and if the current cell matches the character in the word
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != word[index]) {
            return false;
        }

        // Mark the current cell as visited (by changing it temporarily)
        char temp = board[row][col];
        board[row][col] = '#'; // Using '#' as a visited marker

        // Explore all four directions: up, down, left, right
        bool found = backtrack(row + 1, col, index + 1) ||
                       backtrack(row - 1, col, index + 1) ||
                       backtrack(row, col + 1, index + 1) ||
                       backtrack(row, col - 1, index + 1);

        // Backtrack: Restore the original character of the cell
        board[row][col] = temp;
        return found;
    };

    // Start the search from each cell in the board
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

// Approach 2: Backtracking with Visited Array
// - Uses a separate boolean array to track visited cells.
// - Avoids modifying the original board.
// - More memory efficient in terms of not modifying the input.
bool exist_visited(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    std::function<bool(int, int, int)> backtrack =  // Use std::function
        [&](int row, int col, int index) {
        if (index == word.size()) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || board[row][col] != word[index]) {
            return false;
        }

        visited[row][col] = true; // Mark as visited
        bool found = backtrack(row + 1, col, index + 1) ||
                       backtrack(row - 1, col, index + 1) ||
                       backtrack(row, col + 1, index + 1) ||
                       backtrack(row, col - 1, index + 1);
        visited[row][col] = false; // Backtrack
        return found;
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

// Approach 3: Backtracking with Early Termination
// - Optimizes the backtracking by adding checks for early termination.
// - If a path is found to be invalid, it stops exploring that path immediately.
// - Potentially faster for larger boards and longer words.
bool exist_early_termination(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    std::function<bool(int, int, int)> backtrack =  // Use std::function
        [&](int row, int col, int index) {
        if (index == word.size()) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || board[row][col] != word[index]) {
            return false;
        }

        visited[row][col] = true;
        bool found = false; // Initialize found to false
        found = found || backtrack(row + 1, col, index + 1);
        if (!found) found = found || backtrack(row - 1, col, index + 1); // Only check if not found yet
        if (!found) found = found || backtrack(row, col + 1, index + 1);
        if (!found) found = found || backtrack(row, col - 1, index + 1);
        visited[row][col] = false;
        return found;
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (backtrack(i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

// Approach 4: Backtracking with Word Reversal
// - Explores the board for both the original word and its reverse.
// - Can potentially find the word faster in some cases.
// - Adds a bit of complexity but can improve performance.
bool exist_word_reversal(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();
    string reversedWord = word;
    reverse(reversedWord.begin(), reversedWord.end()); // Reverse the word

    std::function<bool(int, int, int, const string&)> backtrack =  // Use std::function
        [&](int row, int col, int index, const string& currentWord) {
        if (index == currentWord.size()) {
            return true;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != currentWord[index]) {
            return false;
        }

        char temp = board[row][col];
        board[row][col] = '#';
        bool found = backtrack(row + 1, col, index + 1, currentWord) ||
                       backtrack(row - 1, col, index + 1, currentWord) ||
                       backtrack(row, col + 1, index + 1, currentWord) ||
                       backtrack(row, col - 1, index + 1, currentWord);
        board[row][col] = temp;
        return found;
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (backtrack(i, j, 0, word) || backtrack(i, j, 0, reversedWord)) { // Search for both
                return true;
            }
        }
    }
    return false;
}

// Approach 5: Iterative Backtracking (using a stack) - More complex, generally NOT recommended for Word Search
//   - Uses a stack to simulate the recursive calls.
//   - More complex to implement than the recursive approaches.
//   - Generally, recursive backtracking is preferred for word search due to its clarity.
//   - Included for completeness and to show an alternative approach.  This is less efficient and harder to understand
bool exist_iterative(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();
    int wordLength = word.length();

    for (int startRow = 0; startRow < rows; ++startRow) {
        for (int startCol = 0; startCol < cols; ++startCol) {
            if (board[startRow][startCol] == word[0]) { // Start only if the first character matches.

                std::stack<std::tuple<int, int, int>> path; // {row, col, index}  Use std::stack and std::tuple
                path.push({startRow, startCol, 0});
                vector<vector<bool>> visited(rows, vector<bool>(cols, false));
                visited[startRow][startCol] = true;

                while (!path.empty()) {
                    auto [row, col, index] = path.top();
                    path.pop();

                    if (index == wordLength - 1) {
                        return true; // Found the word
                    }

                    // Explore neighbors
                    int dr[] = {0, 0, 1, -1};
                    int dc[] = {1, -1, 0, 0};
                    for (int i = 0; i < 4; ++i) {
                        int nextRow = row + dr[i];
                        int nextCol = col + dc[i];

                        if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols &&
                            !visited[nextRow][nextCol] && board[nextRow][nextCol] == word[index + 1]) {
                            path.push({nextRow, nextCol, index + 1});
                            visited[nextRow][nextCol] = true;
                            break; // Important:  Go to the next cell
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    // Example usage
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word = "ABCCED";

    cout << "Board:" << endl;
    for (const auto& row : board) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "Word: " << word << endl;

    cout << "Approach 1 (Basic Backtracking): " << (exist_basic(board, word) ? "Found" : "Not Found") << endl;

    // Reset the board for the other approaches (Important as Approach 1 modifies the board)
    board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    cout << "Approach 2 (Visited Array): " << (exist_visited(board, word) ? "Found" : "Not Found") << endl;

    board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    cout << "Approach 3 (Early Termination): " << (exist_early_termination(board, word) ? "Found" : "Not Found") << endl;

    board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
     cout << "Approach 4 (Word Reversal): " << (exist_word_reversal(board, word) ? "Found" : "Not Found") << endl;

    board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    cout << "Approach 5 (Iterative): " << (exist_iterative(board, word) ? "Found" : "Not Found") << endl;


    return 0;
}

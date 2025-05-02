// Sudoku Solver - Multiple Backtracking Approaches in C++
// Each approach showcases real-world project implementation strategies
// Common across all is the usage of 9x9 sudoku board

#include <iostream>
#include <vector>
#include <unordered_set>
#include <array>
using namespace std;

typedef vector<vector<char>> Board;

// Utility: Check if placing a number is valid
bool isValid(Board &board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == c || board[i][col] == c ||
            board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
            return false;
    }
    return true;
}

// Approach 1: Simple Recursive Backtracking
bool solveSudoku1(Board &board) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; ++c) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        if (solveSudoku1(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Approach 2: Backtracking with Heuristic - Minimum Remaining Value (MRV)
struct Cell {
    int row, col, options;
};

bool solveSudoku2(Board &board) {
    Cell best{-1, -1, 10};
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.') {
                int count = 0;
                for (char ch = '1'; ch <= '9'; ++ch)
                    if (isValid(board, r, c, ch)) count++;
                if (count < best.options) best = {r, c, count};
            }
        }
    }
    if (best.row == -1) return true;

    for (char ch = '1'; ch <= '9'; ++ch) {
        if (isValid(board, best.row, best.col, ch)) {
            board[best.row][best.col] = ch;
            if (solveSudoku2(board)) return true;
            board[best.row][best.col] = '.';
        }
    }
    return false;
}

// Approach 3: Constraint Propagation with Backtracking
bool isConsistent(Board &board, vector<vector<unordered_set<char>>> &candidates) {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (board[r][c] == '.' && candidates[r][c].empty())
                return false;
    return true;
}

bool solveSudoku3(Board &board, vector<vector<unordered_set<char>>> &candidates) {
    int minOpts = 10, row = -1, col = -1;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.' && candidates[r][c].size() < minOpts) {
                minOpts = candidates[r][c].size();
                row = r; col = c;
            }
        }
    }
    if (row == -1) return true;

    for (char ch : candidates[row][col]) {
        board[row][col] = ch;
        vector<vector<unordered_set<char>>> temp = candidates;
        for (int i = 0; i < 9; ++i) {
            temp[row][i].erase(ch);
            temp[i][col].erase(ch);
            temp[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3].erase(ch);
        }
        if (isConsistent(board, temp) && solveSudoku3(board, temp)) return true;
        board[row][col] = '.';
    }
    return false;
}

// Approach 4: Backtracking with Bitmask Optimization (Memory Efficient)
bool solveSudoku4(Board &board, array<short, 9> &rows, array<short, 9> &cols, array<array<short, 3>, 3> &boxes) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.') {
                for (int d = 1; d <= 9; ++d) {
                    short mask = 1 << d;
                    if (!(rows[i] & mask) && !(cols[j] & mask) && !(boxes[i/3][j/3] & mask)) {
                        board[i][j] = d + '0';
                        rows[i] |= mask;
                        cols[j] |= mask;
                        boxes[i/3][j/3] |= mask;
                        if (solveSudoku4(board, rows, cols, boxes)) return true;
                        board[i][j] = '.';
                        rows[i] ^= mask;
                        cols[j] ^= mask;
                        boxes[i/3][j/3] ^= mask;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Approach 5: Backtracking with Forward Checking
bool forwardCheck(Board &board, vector<vector<unordered_set<char>>> &domain) {
    bool changed = false;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] != '.') {
                char val = board[r][c];
                for (int i = 0; i < 9; ++i) {
                    changed |= domain[r][i].erase(val);
                    changed |= domain[i][c].erase(val);
                    changed |= domain[3*(r/3)+i/3][3*(c/3)+i%3].erase(val);
                }
            }
        }
    }
    return changed;
}

bool solveSudoku5(Board &board, vector<vector<unordered_set<char>>> &domain) {
    int row = -1, col = -1, minSize = 10;
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (board[r][c] == '.' && domain[r][c].size() < minSize) {
                row = r; col = c; minSize = domain[r][c].size();
            }
    if (row == -1) return true;

    for (char val : domain[row][col]) {
        board[row][col] = val;
        auto newDomain = domain;
        if (forwardCheck(board, newDomain) && solveSudoku5(board, newDomain))
            return true;
        board[row][col] = '.';
    }
    return false;
}

// Utility: Print Sudoku Board
void printBoard(const Board &board) {
    for (const auto &row : board) {
        for (char c : row) cout << c << ' ';
        cout << '\n';
    }
}

// Sample usage: choose which approach to use
int main() {
    Board board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    cout << "Original Sudoku:\n";
    printBoard(board);

    // Choose a solver to run (Uncomment one at a time)
    // solveSudoku1(board);
    // solveSudoku2(board);
    // vector<vector<unordered_set<char>>> candidates(9, vector<unordered_set<char>>(9));
    // for (int r = 0; r < 9; ++r)
    //     for (int c = 0; c < 9; ++c)
    //         if (board[r][c] == '.')
    //             for (char ch = '1'; ch <= '9'; ++ch)
    //                 if (isValid(board, r, c, ch)) candidates[r][c].insert(ch);
    // solveSudoku3(board, candidates);

    // array<short, 9> rows{}, cols{};
    // array<array<short, 3>, 3> boxes{};
    // for (int i = 0; i < 9; ++i)
    //     for (int j = 0; j < 9; ++j)
    //         if (board[i][j] != '.') {
    //             int d = board[i][j] - '0';
    //             short mask = 1 << d;
    //             rows[i] |= mask; cols[j] |= mask; boxes[i/3][j/3] |= mask;
    //         }
    // solveSudoku4(board, rows, cols, boxes);

    // vector<vector<unordered_set<char>>> domain(9, vector<unordered_set<char>>(9));
    // for (int r = 0; r < 9; ++r)
    //     for (int c = 0; c < 9; ++c)
    //         if (board[r][c] == '.')
    //             for (char ch = '1'; ch <= '9'; ++ch)
    //                 domain[r][c].insert(ch);
    // solveSudoku5(board, domain);

    cout << "\nSolved Sudoku:\n";
    printBoard(board);
    return 0;
}

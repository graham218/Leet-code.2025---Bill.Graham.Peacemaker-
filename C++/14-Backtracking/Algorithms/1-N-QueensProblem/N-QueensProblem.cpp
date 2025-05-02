// N-Queens Problem - Multiple Backtracking Approaches in C++
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

// Approach 1: Basic Backtracking using board representation
bool isSafeBasic(const vector<string>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q') return false;
    }
    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q') return false;
    }
    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}

void solveBasic(int row, int n, vector<string>& board, vector<vector<string>>& res) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafeBasic(board, row, col, n)) {
            board[row][col] = 'Q';
            solveBasic(row + 1, n, board, res);
            board[row][col] = '.'; // Backtrack
        }
    }
}

// Approach 2: Using HashSets to optimize diagonal/column checks
void solveHashSet(int row, int n, vector<string>& board, vector<vector<string>>& res,
                  set<int>& cols, set<int>& diag1, set<int>& diag2) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col)) continue;
        cols.insert(col);
        diag1.insert(row - col);
        diag2.insert(row + col);
        board[row][col] = 'Q';
        solveHashSet(row + 1, n, board, res, cols, diag1, diag2);
        board[row][col] = '.'; // Backtrack
        cols.erase(col);
        diag1.erase(row - col);
        diag2.erase(row + col);
    }
}

// Approach 3: Bitmasking (efficient for n <= 32)
void solveBitmask(int n, int row, int cols, int diag1, int diag2,
                  vector<string>& board, vector<vector<string>>& res) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);
    while (available) {
        int bit = available & -available; // get rightmost 1-bit
        available ^= bit; // remove the placed queen from available positions
        int col = __builtin_ctz(bit);
        board[row][col] = 'Q';
        solveBitmask(n, row + 1, cols | bit, (diag1 | bit) << 1, (diag2 | bit) >> 1, board, res);
        board[row][col] = '.'; // Backtrack
    }
}

// Approach 4: Permutations (generate all column permutations and check diagonal conflicts)
bool isValidDiag(const vector<int>& perm) {
    int n = perm.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (abs(i - j) == abs(perm[i] - perm[j])) return false;
        }
    }
    return true;
}

void solvePermutation(int n, vector<vector<string>>& res) {
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;
    do {
        if (isValidDiag(perm)) {
            vector<string> board(n, string(n, '.'));
            for (int i = 0; i < n; ++i)
                board[i][perm[i]] = 'Q';
            res.push_back(board);
        }
    } while (next_permutation(perm.begin(), perm.end()));
}

// Approach 5: Class-based object-oriented backtracking
class NQueensSolver {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        backtrack(0, n, board, res);
        return res;
    }
private:
    bool isSafe(const vector<string>& board, int row, int col, int n) {
        // Check column
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q') return false;
        }
        // Check upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q') return false;
        }
        // Check upper right diagonal
        for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }

    void backtrack(int row, int n, vector<string>& board, vector<vector<string>>& res) {
        if (row == n) {
            res.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                backtrack(row + 1, n, board, res);
                board[row][col] = '.'; // Backtrack
            }
        }
    }
};

int main() {
    int n = 8; // Change this value for different board sizes
    vector<vector<string>> result;

    // Choose one approach to run:
    cout << "Running Basic Backtracking (Approach 1):" << endl;
    vector<string> boardBasic(n, string(n, '.'));
    solveBasic(0, n, boardBasic, result);
    cout << "Total solutions (Basic): " << result.size() << endl << endl;
    result.clear();

    cout << "Running HashSet Optimization (Approach 2):" << endl;
    vector<string> boardHashSet(n, string(n, '.'));
    set<int> colsHashSet, diag1HashSet, diag2HashSet;
    solveHashSet(0, n, boardHashSet, result, colsHashSet, diag1HashSet, diag2HashSet);
    cout << "Total solutions (HashSet): " << result.size() << endl << endl;
    result.clear();

    cout << "Running Bitmasking (Approach 3):" << endl;
    vector<string> boardBitmask(n, string(n, '.'));
    solveBitmask(n, 0, 0, 0, 0, boardBitmask, result);
    cout << "Total solutions (Bitmask): " << result.size() << endl << endl;
    result.clear();

    cout << "Running Permutation (Approach 4):" << endl;
    solvePermutation(n, result);
    cout << "Total solutions (Permutation): " << result.size() << endl << endl;
    result.clear();

    cout << "Running Class-based Backtracking (Approach 5):" << endl;
    NQueensSolver solver;
    result = solver.solveNQueens(n);
    cout << "Total solutions (Class-based): " << result.size() << endl << endl;

    // Print results of the last executed approach (Class-based in this example)
    cout << "Solutions for N = " << n << " (Class-based):" << endl;
    for (const auto& solution : result) {
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << "\n";
    }

    return 0;
}
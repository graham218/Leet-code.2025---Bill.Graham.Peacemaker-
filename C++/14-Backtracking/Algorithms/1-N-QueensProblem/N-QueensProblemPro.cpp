// C++ Solutions to the N-Queens Problem using Backtracking
// This file contains 5 different real-world applicable implementations
// with detailed comments for clarity and practical use.

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// Utility function to print the board
void printBoard(const vector<string>& board) {
    for (const auto& row : board) {
        cout << row << endl;
    }
    cout << endl;
}

////////////////////////////////////////////////////////////
// 1. Basic Backtracking Approach (Educational Tools)
////////////////////////////////////////////////////////////

void solveNQueensBasic(int row, int n, vector<string>& board, vector<vector<string>>& solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        bool safe = true;
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q' ||
                (col - (row - i) >= 0 && board[i][col - (row - i)] == 'Q') ||
                (col + (row - i) < n && board[i][col + (row - i)] == 'Q')) {
                safe = false;
                break;
            }
        }
        if (safe) {
            board[row][col] = 'Q';
            solveNQueensBasic(row + 1, n, board, solutions);
            board[row][col] = '.'; // backtrack
        }
    }
}

////////////////////////////////////////////////////////////
// 2. Optimized with Hash Sets (AI Search Algorithms)
////////////////////////////////////////////////////////////

void solveNQueensHash(int row, int n, vector<string>& board, vector<vector<string>>& solutions,
                      set<int>& cols, set<int>& diag1, set<int>& diag2) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col)) continue;
        board[row][col] = 'Q';
        cols.insert(col);
        diag1.insert(row - col);
        diag2.insert(row + col);
        solveNQueensHash(row + 1, n, board, solutions, cols, diag1, diag2);
        board[row][col] = '.';
        cols.erase(col);
        diag1.erase(row - col);
        diag2.erase(row + col);
    }
}

////////////////////////////////////////////////////////////
// 3. Bitmask Optimization (Used in Game Engines)
////////////////////////////////////////////////////////////

void solveNQueensBitmask(int n, int row, int cols, int diag1, int diag2, vector<string>& board, vector<vector<string>>& solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);
    while (available) {
        int pos = available & -available;
        available -= pos;
        int col = __builtin_ctz(pos);
        board[row][col] = 'Q';
        solveNQueensBitmask(n, row + 1, cols | pos, (diag1 | pos) << 1, (diag2 | pos) >> 1, board, solutions);
        board[row][col] = '.';
    }
}

////////////////////////////////////////////////////////////
// 4. Early Exit on First Solution (Constraint Solvers)
////////////////////////////////////////////////////////////

bool solveNQueensOneSolution(int row, int n, vector<string>& board, vector<bool>& cols, vector<bool>& d1, vector<bool>& d2) {
    if (row == n) return true;
    for (int col = 0; col < n; ++col) {
        if (cols[col] || d1[row - col + n - 1] || d2[row + col]) continue;
        board[row][col] = 'Q';
        cols[col] = d1[row - col + n - 1] = d2[row + col] = true;
        if (solveNQueensOneSolution(row + 1, n, board, cols, d1, d2)) return true;
        board[row][col] = '.';
        cols[col] = d1[row - col + n - 1] = d2[row + col] = false;
    }
    return false;
}

////////////////////////////////////////////////////////////
// 5. Count Number of Solutions Only (Analytics/Reports)
////////////////////////////////////////////////////////////

void countNQueensSolutions(int row, int n, vector<bool>& cols, vector<bool>& d1, vector<bool>& d2, int& count) {
    if (row == n) {
        ++count;
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols[col] || d1[row - col + n - 1] || d2[row + col]) continue;
        cols[col] = d1[row - col + n - 1] = d2[row + col] = true;
        countNQueensSolutions(row + 1, n, cols, d1, d2, count);
        cols[col] = d1[row - col + n - 1] = d2[row + col] = false;
    }
}

////////////////////////////////////////////////////////////
// Main function to demonstrate all implementations
////////////////////////////////////////////////////////////

int main() {
    int n = 8; // Change for different board sizes
    vector<vector<string>> solutions;

    // 1. Basic
    vector<string> board1(n, string(n, '.'));
    solveNQueensBasic(0, n, board1, solutions);
    cout << "Basic Backtracking Solutions: " << solutions.size() << endl;
    solutions.clear();

    // 2. Hash Sets
    vector<string> board2(n, string(n, '.'));
    set<int> cols, d1, d2;
    solveNQueensHash(0, n, board2, solutions, cols, d1, d2);
    cout << "Hash Sets Solutions: " << solutions.size() << endl;
    solutions.clear();

    // 3. Bitmask
    vector<string> board3(n, string(n, '.'));
    solveNQueensBitmask(n, 0, 0, 0, 0, board3, solutions);
    cout << "Bitmask Solutions: " << solutions.size() << endl;
    solutions.clear();

    // 4. One Solution
    vector<string> board4(n, string(n, '.'));
    vector<bool> c(n, false), d11(2 * n - 1, false), d22(2 * n - 1, false);
    if (solveNQueensOneSolution(0, n, board4, c, d11, d22)) {
        cout << "First Valid Solution (Constraint Solver):\n";
        printBoard(board4);
    }

    // 5. Count Only
    int count = 0;
    vector<bool> c2(n, false), d13(2 * n - 1, false), d23(2 * n - 1, false);
    countNQueensSolutions(0, n, c2, d13, d23, count);
    cout << "Total Number of Solutions: " << count << endl;

    return 0;
}

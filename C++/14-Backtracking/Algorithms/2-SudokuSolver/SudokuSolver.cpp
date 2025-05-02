#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <chrono> // For timing
#include <queue> // Required for AC-3

using namespace std;

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0) {
            cout << "--------+---------+--------" << endl;
        }
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a number can be placed in a cell
bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    // Check row
    for (int x = 0; x < 9; ++x) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < 9; ++x) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// 1. Backtracking (Basic)
bool solveSudokuBacktracking(vector<vector<int>>& board) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudokuBacktracking(board)) {
                            return true;
                        }
                        else {
                            board[row][col] = 0; // Backtrack
                        }
                    }
                }
                return false; // No valid number found
            }
        }
    }
    return true; // Puzzle solved
}

// 2. Backtracking with Forward Checking
bool solveSudokuForwardCheckingHelper(vector<vector<int>>& board, vector<vector<set<int>>>& possibleValues) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                // Iterate through possible values for the current cell.
                for (int num : possibleValues[row][col]) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        // Create a copy to prevent modifying the original
                        vector<vector<set<int>>> nextPossibleValues = possibleValues;
                        // Remove 'num' from possible values of cells in the same row, column, and block
                        for (int i = 0; i < 9; ++i) {
                            nextPossibleValues[row][i].erase(num);
                            nextPossibleValues[i][col].erase(num);
                        }
                        int startRow = row - row % 3;
                        int startCol = col - col % 3;
                        for (int i = 0; i < 3; ++i) {
                            for (int j = 0; j < 3; ++j) {
                                nextPossibleValues[startRow + i][startCol + j].erase(num);
                            }
                        }
                        if (solveSudokuForwardCheckingHelper(board, nextPossibleValues)) {
                            return true;
                        }
                        else {
                            board[row][col] = 0; // Backtrack
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuForwardChecking(vector<vector<int>>& board) {
    // possibleValues[row][col] stores the possible numbers that can be placed at board[row][col]
    vector<vector<set<int>>> possibleValues(9, vector<set<int>>(9));

    // Initialize possible values for each cell
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        possibleValues[row][col].insert(num);
                    }
                }
            }
        }
    }

    return solveSudokuForwardCheckingHelper(board, possibleValues);
}

// 3. Backtracking with Minimum Remaining Values (MRV) Heuristic
bool solveSudokuMRV(vector<vector<int>>& board) {
    int minRow = -1, minCol = -1, minRemaining = 10; // Initialize minRemaining to a value > 9

    // Find the cell with the minimum remaining possible values
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                int count = 0;
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        count++;
                    }
                }
                if (count < minRemaining) {
                    minRemaining = count;
                    minRow = row;
                    minCol = col;
                }
            }
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (minRow == -1 && minCol == -1) {
        return true;
    }

    for (int num = 1; num <= 9; ++num) {
        if (isValid(board, minRow, minCol, num)) {
            board[minRow][minCol] = num;
            if (solveSudokuMRV(board)) {
                return true;
            }
            else {
                board[minRow][minCol] = 0;
            }
        }
    }
    return false;
}

// 4. Backtracking with Constraint Propagation (AC-3)
bool solveSudokuAC3Backtracking(vector<vector<int>>& board, vector<vector<set<int>>>& domains) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num : domains[row][col]) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        vector<vector<set<int>>> nextDomains = domains; // Copy domains
                        // Remove values from the domains of related cells.
                        for (int i = 0; i < 9; ++i) {
                            nextDomains[row][i].erase(num);
                            nextDomains[i][col].erase(num);
                        }
                        int startRow = row - row % 3;
                        int startCol = col - col % 3;
                        for (int i = 0; i < 3; ++i) {
                            for (int j = 0; j < 3; ++j) {
                                nextDomains[startRow + i][startCol + j].erase(num);
                            }
                        }

                        if (solveSudokuAC3Backtracking(board, nextDomains)) {
                            return true;
                        }
                        else {
                            board[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuAC3(vector<vector<int>>& board) {
    // Initialize domains for each cell (1-9 for empty cells, fixed value for filled cells)
    vector<vector<set<int>>> domains(9, vector<set<int>>(9));
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    domains[row][col].insert(num);
                }
            }
            else {
                domains[row][col].insert(board[row][col]);
            }
        }
    }

    // Function to get the neighbors of a cell (cells in the same row, column, or block)
    auto getNeighbors = [&](int row, int col) -> vector<pair<int, int>> {
        vector<pair<int, int>> neighbors;
        for (int i = 0; i < 9; ++i) {
            if (i != col) neighbors.push_back({row, i}); // Row
            if (i != row) neighbors.push_back({i, col}); // Column
        }
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (startRow + i != row || startCol + j != col) {
                    neighbors.push_back({startRow + i, startCol + j});
                }
            }
        }
        return neighbors;
    };

    // AC-3 Algorithm
    queue<pair<int, int>> q;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                q.push({i, j}); // Start with all empty cells
            }
        }
    }

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int row = current.first;
        int col = current.second;

        for (pair<int, int> neighbor : getNeighbors(row, col)) {
            int nRow = neighbor.first;
            int nCol = neighbor.second;
            if (board[nRow][nCol] == 0) { // Only consider neighbors that are also unassigned.
                bool removed = false;
                for (int val : domains[row][col]) {
                    bool foundMatch = false;
                    for (int nVal : domains[nRow][nCol]) {
                        if (val != nVal) { // There exists a value in neighbor's domain that is different
                            foundMatch = true;
                            break;
                        }
                    }
                    if (!foundMatch) {
                        domains[row][col].erase(val); // Remove the value from domain
                        removed = true;
                        break; // Important:  Only remove ONCE per value in current cell's domain.
                    }
                }
                if (removed) {
                    if (domains[row][col].empty()) {
                        return false; // Domain wipeout: no solution
                    }
                    q.push({row, col}); // Re-add to queue if domain is reduced
                }
            }
        }
    }

    // Backtracking search with updated domains
    return solveSudokuAC3Backtracking(board, domains);
}

// 5. Optimized Backtracking (Combining MRV and Forward Checking) -  Most Efficient
bool solveSudokuOptimizedHelper(vector<vector<int>>& board, vector<vector<set<int>>>& possibleValues) {
    int minRow = -1, minCol = -1, minRemaining = 10;

    // Find cell with Minimum Remaining Values (MRV)
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                int count = possibleValues[row][col].size();
                if (count < minRemaining) {
                    minRemaining = count;
                    minRow = row;
                    minCol = col;
                }
            }
        }
    }

    if (minRow == -1 && minCol == -1) {
        return true; // Solved
    }

    // Iterate through possible values of the cell with MRV
    for (int num : possibleValues[minRow][minCol]) {
        if (isValid(board, minRow, minCol, num)) {
            board[minRow][minCol] = num;
            vector<vector<set<int>>> nextPossibleValues = possibleValues;

            // Forward checking: update possible values for related cells
            for (int i = 0; i < 9; ++i) {
                nextPossibleValues[minRow][i].erase(num);
                nextPossibleValues[i][minCol].erase(num);
            }
            int startRow = minRow - minRow % 3;
            int startCol = minCol - minCol % 3;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    nextPossibleValues[startRow + i][startCol + j].erase(num);
                }
            }
            if (solveSudokuOptimizedHelper(board, nextPossibleValues)) {
                return true;
            }
            else {
                board[minRow][minCol] = 0;
            }
        }
    }
    return false;
}

bool solveSudokuOptimized(vector<vector<int>>& board) {
    vector<vector<set<int>>> possibleValues(9, vector<set<int>>(9));

    // Initialize possible values
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        possibleValues[row][col].insert(num);
                    }
                }
            }
        }
    }
    return solveSudokuOptimizedHelper(board, possibleValues);
}

int main() {
    // Example Sudoku board (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku Board:" << endl;
    printBoard(board);

    // Create a copy for each algorithm
    vector<vector<int>> board1 = board;
    vector<vector<int>> board2 = board;
    vector<vector<int>> board3 = board;
    vector<vector<int>> board4 = board;
    vector<vector<int>> board5 = board;

    // 1. Backtracking
    cout << "1. Backtracking:" << endl;
    auto start1 = chrono::high_resolution_clock::now();
    if (solveSudokuBacktracking(board1)) {
        auto stop1 = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
        cout << "Solved:" << endl;
        printBoard(board1);
        cout << "Time taken: " << duration1.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 2. Backtracking with Forward Checking
    cout << "2. Backtracking with Forward Checking:" << endl;
    auto start2 = chrono::high_resolution_clock::now();
    if (solveSudokuForwardChecking(board2)) {
        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << "Solved:" << endl;
        printBoard(board2);
        cout << "Time taken: " << duration2.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 3. Backtracking with MRV
    cout << "3. Backtracking with MRV:" << endl;
    auto start3 = chrono::high_resolution_clock::now();
    if (solveSudokuMRV(board3)) {
        auto stop3 = chrono::high_resolution_clock::now();
        auto duration3 = chrono::duration_cast<chrono::microseconds>(stop3 - start3);
        cout << "Solved:" << endl;
        printBoard(board3);
        cout << "Time taken: " << duration3.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 4. Backtracking with AC-3
    cout << "4. Backtracking with AC-3:" << endl;
    auto start4 = chrono::high_resolution_clock::now();
    if (solveSudokuAC3(board4)) {
        auto stop4 = chrono::high_resolution_clock::now();
        auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
        cout << "Solved:" << endl;
        printBoard(board4);
        cout << "Time taken: " << duration4.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // 5. Optimized Backtracking (MRV + Forward Checking)
    cout << "5. Optimized Backtracking (MRV + Forward Checking):" << endl;
    auto start5 = chrono::high_resolution_clock::now();
    if (solveSudokuOptimized(board5)) {
        auto stop5 = chrono::high_resolution_clock::now();
        auto duration5 = chrono::duration_cast<chrono::microseconds>(stop5 - start5);
        cout << "Solved:" << endl;
        printBoard(board5);
        cout << "Time taken: " << duration5.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}


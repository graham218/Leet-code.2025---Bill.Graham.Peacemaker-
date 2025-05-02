#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional> // Include for std::function

using namespace std;

// Function to solve the Gas Station problem using the Greedy Approach
int canCompleteCircuit_Greedy(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    int start = 0;
    int currentGas = 0;
    int totalDeficit = 0;

    for (int i = 0; i < n; ++i) {
        currentGas += gas[i] - cost[i];
        if (currentGas < 0) {
            totalDeficit += currentGas;
            start = i + 1;
            currentGas = 0;
        }
    }

    if (currentGas + totalDeficit >= 0) {
        return start % n;
    } else {
        return -1;
    }
}

// Function to solve the Gas Station problem using Brute Force Approach
int canCompleteCircuit_BruteForce(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    for (int start = 0; start < n; ++start) {
        int currentGas = 0;
        int currentStation = start;
        int stationsVisited = 0;
        bool possible = true;

        while (stationsVisited < n) {
            currentGas += gas[currentStation];
            currentGas -= cost[currentStation];
            if (currentGas < 0) {
                possible = false;
                break;
            }
            currentStation = (currentStation + 1) % n;
            stationsVisited++;
        }
        if (possible) {
            return start;
        }
    }
    return -1;
}

// Function to solve Gas Station problem using Optimized Brute Force
int canCompleteCircuit_OptimizedBruteForce(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    for (int start = 0; start < n; ++start) {
        int currentGas = 0;
        int currentStation = start;
        int stationsVisited = 0;
        bool possible = true;

        while (stationsVisited < n) {
            currentGas += gas[currentStation];
            currentGas -= cost[currentStation];
            if (currentGas < 0) {
                possible = false;
                break;
            }
            currentStation = (currentStation + 1) % n;
            stationsVisited++;
        }
        if (possible) {
            return start;
        }
    }
    return -1;
}

// Function to solve Gas Station problem using Dynamic Programming (Memoization)
int canCompleteCircuit_DP(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    // Create a memoization table to store results of subproblems
    vector<vector<int>> memo(n, vector<int>(n + 1, -2)); // -2: unvisited, -1: impossible, >=0: possible

    std::function<int(int, int, int)> solve =  // Fix: Use std::function
        [&](int start, int currentStation, int stationsVisited) -> int {
        if (stationsVisited == n) {
            return 1;
        }

        if (memo[start][stationsVisited] != -2) {
            return memo[start][stationsVisited];
        }

        int currentGas = 0;
        if (stationsVisited == 0) {
            currentGas = 0;
        } else {
            currentGas = memo[start][stationsVisited - 1];
        }

        currentGas += gas[currentStation];
        currentGas -= cost[currentStation];
        if (currentGas < 0) {
            memo[start][stationsVisited] = -1;
            return -1;
        }

        int nextStation = (currentStation + 1) % n;
        int result = solve(start, nextStation, stationsVisited + 1);
        memo[start][stationsVisited] = result;
        return result;
    };

    for (int start = 0; start < n; ++start) {
        if (solve(start, start, 0) == 1) {
            return start;
        }
    }
    return -1;
}

// Function using Kadane's Algorithm (variation)
int canCompleteCircuit_Kadane(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    int totalGas = 0;
    int currentGas = 0;
    int start = 0;

    for (int i = 0; i < n; ++i) {
        totalGas += gas[i] - cost[i];
        currentGas += gas[i] - cost[i];
        if (currentGas < 0) {
            start = i + 1;
            currentGas = 0;
        }
    }

    if (totalGas < 0) {
        return -1;
    } else {
        return start;
    }
}

int main() {
    // Example input
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    // Test with the Greedy approach
    int start1 = canCompleteCircuit_Greedy(gas, cost);
    cout << "Greedy Approach: Starting station = " << start1 << endl;

    // Test with Brute Force approach
    int start2 = canCompleteCircuit_BruteForce(gas, cost);
    cout << "Brute Force Approach: Starting station = " << start2 << endl;

    // Test with Optimized Brute Force
    int start3 = canCompleteCircuit_OptimizedBruteForce(gas, cost);
    cout << "Optimized Brute Force Approach: Starting station = " << start3 << endl;

    // Test with Dynamic Programming
    int start4 = canCompleteCircuit_DP(gas, cost);
    cout << "Dynamic Programming Approach: Starting station = " << start4 << endl;

    // Test with Kadane's Algorithm
    int start5 = canCompleteCircuit_Kadane(gas, cost);
    cout << "Kadane's Algorithm Approach: Starting station = " << start5 << endl;

    return 0;
}

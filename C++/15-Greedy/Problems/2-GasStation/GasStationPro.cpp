#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <limits>  // For std::numeric_limits

using namespace std;

// 1. Brute Force Approach
//   - Concept: Try every gas station as a starting point and simulate the journey.
//   - Time Complexity: O(n^2), where n is the number of gas stations.
//   - Space Complexity: O(1)
int canCompleteCircuit_BruteForce(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    for (int start = 0; start < n; ++start) {
        int currentGas = 0;
        int currentPosition = start;
        int stationsVisited = 0;

        do {
            currentGas += gas[currentPosition];
            currentGas -= cost[currentPosition];
            if (currentGas < 0) break; // Cannot reach the next station
            currentPosition = (currentPosition + 1) % n; // Move to the next station (circular)
            stationsVisited++;
        } while (currentPosition != start && stationsVisited <= n); // Stop if we complete the circuit or visit all stations

        if (stationsVisited == n) {
            return start; // Found a valid starting station
        }
    }
    return -1; // No valid starting station
}

// 2. Optimized Brute Force (Slight Improvement)
//   - Concept: If starting from a station 'i' fails, starting from any station between 'i' and the failing point will also fail.
//   - Time Complexity: O(n^2) in the worst case, but often faster than the pure brute force.
//   - Space Complexity: O(1)
int canCompleteCircuit_OptimizedBruteForce(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    for (int start = 0; start < n;) { // Note the 'start' increment inside the loop
        int currentGas = 0;
        int currentPosition = start;
        int stationsVisited = 0;

        do {
            currentGas += gas[currentPosition];
            currentGas -= cost[currentPosition];
            if (currentGas < 0) break;
            currentPosition = (currentPosition + 1) % n;
            stationsVisited++;
        } while (currentPosition != start && stationsVisited <= n);

        if (stationsVisited == n) {
            return start;
        } else {
            // Optimization: If we fail at station 'currentPosition',
            // we can skip all stations between 'start' and 'currentPosition'.
            start = currentPosition + 1;
        }
    }
    return -1;
}


// 3. Greedy Approach
//   - Concept:  If the total gas is less than the total cost, no solution exists. Otherwise, there is a unique starting station.
//              Start from station 0, and keep track of the current gas and the deficit. If the gas becomes negative,
//              reset the starting station to the next station and add the deficit to the total deficit.
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
int canCompleteCircuit_Greedy(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    int totalGas = accumulate(gas.begin(), gas.end(), 0);
    int totalCost = accumulate(cost.begin(), cost.end(), 0);
    if (totalGas < totalCost) return -1; // Not possible to complete the circuit

    int start = 0;
    int currentGas = 0;
    int deficit = 0;

    for (int i = 0; i < n; ++i) {
        currentGas += gas[i];
        currentGas -= cost[i];
        if (currentGas < 0) {
            deficit += currentGas; // Keep track of the deficit
            start = i + 1;     // Reset the starting station
            currentGas = 0;     // Reset current gas
        }
    }
    return start;
}

// 4. Dynamic Programming (Not Efficient for this Problem, but shown for completeness)
//    - Concept:  Use DP to store whether a path is possible from station i to j.  This is generally *not* a good approach
//               for this problem because of the space complexity and the fact that the greedy solution is optimal.
//    - Time Complexity: O(n^2)
//    - Space Complexity: O(n^2)
int canCompleteCircuit_DP(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    // dp[i][j] stores true if it's possible to travel from station i to station j
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Base case: Traveling from a station to itself is always possible
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    for (int start = 0; start < n; ++start) {
        for (int end = start + 1; end < n + start; ++end) {
            int current = start;
            int next = end % n;
            int currentGas = 0;
            bool possible = true;
            int stationsVisited = 0;

             do {
                currentGas += gas[current];
                currentGas -= cost[current];
                if(currentGas < 0) {
                    possible = false;
                    break;
                }
                current = (current + 1) % n;
                stationsVisited++;
             } while(current != next && stationsVisited <= n);
            dp[start][end % n] = possible && stationsVisited == (end - start + n) % n;
        }
    }
    // Check for a station that can complete the circuit
    for (int i = 0; i < n; ++i) {
        if (dp[i][(i - 1 + n) % n]) { // Check if we can go from i to the station before i.
            return i;
        }
    }

    return -1;
}

// 5. Using Prefix Sums (More of an optimization than a different approach)
//   - Concept: Calculate prefix sums of gas and cost differences.  This can help optimize the brute force or other approaches,
//               but doesn't fundamentally change the core logic in the same way as the greedy approach.
//   - Time Complexity: O(n) for calculating prefix sums, then depends on the algorithm used (e.g., O(n^2) for brute force with prefix sums).
//   - Space Complexity: O(n) for the prefix sum array.
int canCompleteCircuit_PrefixSum(const vector<int>& gas, const vector<int>& cost) {
    int n = gas.size();
    if (n == 0) return -1;

    vector<int> diff(n); // Store the difference between gas and cost at each station
    for (int i = 0; i < n; ++i) {
        diff[i] = gas[i] - cost[i];
    }

    vector<int> prefixSum(n + 1, 0); // prefixSum[i] stores the sum of diff[0...i-1]
    for (int i = 0; i < n; ++i) {
        prefixSum[i + 1] = prefixSum[i] + diff[i];
    }

    for (int start = 0; start < n; ++start) {
        bool possible = true;
        for (int j = 0; j < n; ++j) {
            int currentStation = (start + j) % n;
            // Using prefix sums to calculate the gas available up to currentStation
            int gasAvailable = prefixSum[currentStation + 1] - prefixSum[start];
            if (j > 0) {
               gasAvailable = prefixSum[(start + j) % n + 1] - prefixSum[start];
               if(start + j >= n){
                    gasAvailable = prefixSum[n] - prefixSum[start] + prefixSum[(start + j) % n + 1];
               }
            }

            if (gasAvailable < 0) {
                possible = false;
                break;
            }
        }
        if (possible) {
            return start;
        }
    }
    return -1;
}

int main() {
    // Example usage
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    cout << "Gas: ";
    for (int g : gas) cout << g << " ";
    cout << "\nCost: ";
    for (int c : cost) cout << c << " ";
    cout << endl;

    int start1 = canCompleteCircuit_BruteForce(gas, cost);
    cout << "Brute Force: Starting station = " << start1 << endl;

    int start2 = canCompleteCircuit_OptimizedBruteForce(gas, cost);
    cout << "Optimized Brute Force: Starting station = " << start2 << endl;

    int start3 = canCompleteCircuit_Greedy(gas, cost);
    cout << "Greedy: Starting station = " << start3 << endl;

    int start4 = canCompleteCircuit_DP(gas, cost);
    cout << "Dynamic Programming: Starting station = " << start4 << endl;

    int start5 = canCompleteCircuit_PrefixSum(gas, cost);
    cout << "Prefix Sum: Starting station = " << start5 << endl;


    // Example where no solution exists
    vector<int> noSolutionGas = {2, 3, 4};
    vector<int> noSolutionCost = {3, 4, 5};

    cout << "\nGas: ";
    for (int g : noSolutionGas) cout << g << " ";
    cout << "\nCost: ";
    for (int c : noSolutionCost) cout << c << " ";
    cout << endl;
    int noSolution = canCompleteCircuit_Greedy(noSolutionGas, noSolutionCost);
    cout << "Greedy (No Solution): Starting station = " << noSolution << endl; // Should output -1

    return 0;
}

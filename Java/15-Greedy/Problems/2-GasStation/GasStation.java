import java.util.Arrays;

public class GasStation {

    /**
     * **Approach 1: Brute Force**
     *
     * * Iterates through each gas station as a potential starting point.
     * * Simulates a complete trip around the circuit, checking if enough gas is available.
     * * Returns the starting station index if a successful trip is found.
     * * Time Complexity: O(n^2), where n is the number of gas stations.
     * * Space Complexity: O(1)
     */
    public int canCompleteCircuitBruteForce(int[] gas, int[] cost) {
        int n = gas.length;
        // Iterate through each gas station as a potential starting point
        for (int start = 0; start < n; start++) {
            int currentGas = 0;
            int currentPosition = start;
            int stationsVisited = 0;

            // Simulate a complete trip around the circuit
            while (stationsVisited < n) {
                currentGas += gas[currentPosition]; // Add gas from the current station
                currentGas -= cost[currentPosition]; // Subtract cost to reach the next station
                // If gas is negative, this start position is invalid
                if (currentGas < 0) {
                    break;
                }
                currentPosition = (currentPosition + 1) % n; // Move to the next station
                stationsVisited++;
            }
            // If a complete trip is possible, return the starting index
            if (stationsVisited == n && currentGas >= 0) {
                return start;
            }
        }
        // If no valid starting point is found, return -1
        return -1;
    }

    /**
     * **Approach 2: Optimized Brute Force**
     *
     * * Similar to the brute force approach, but with an optimization.
     * * If a starting position fails at a certain station, it tries to start from the next station.
     * * It avoids checking stations between the previous start and the failing point.
     * * Time Complexity: O(n^2) in the worst case, but often faster than the basic brute force.
     * * Space Complexity: O(1)
     */
    public int canCompleteCircuitOptimizedBruteForce(int[] gas, int[] cost) {
        int n = gas.length;
        for (int start = 0; start < n;) { // Notice start is not incremented in the loop condition
            int currentGas = 0;
            int currentPosition = start;
            int stationsVisited = 0;
            while (stationsVisited < n) {
                currentGas += gas[currentPosition];
                currentGas -= cost[currentPosition];
                if (currentGas < 0) {
                    // Optimization: Jump to the next possible starting point.
                    start = currentPosition + 1; // Try starting from the station after the failure.
                    break; // Exit the inner loop
                }
                currentPosition = (currentPosition + 1) % n;
                stationsVisited++;
            }
            if (stationsVisited == n && currentGas >= 0) {
                return start;
            }
            if (stationsVisited == n && currentGas < 0){
                start++;
            }

        }
        return -1;
    }

    /**
     * **Approach 3: Greedy Approach**
     *
     * * Calculates the total gas and total cost. If total gas is less than total cost, no solution exists.
     * * Iterates through the stations, tracking the current gas and potential starting point.
     * * If the current gas becomes negative, resets the starting point to the next station.
     * * Time Complexity: O(n), where n is the number of gas stations.
     * * Space Complexity: O(1)
     */
    public int canCompleteCircuitGreedy(int[] gas, int[] cost) {
        int n = gas.length;
        int totalGas = 0;
        int totalCost = 0;
        int currentGas = 0;
        int startingStation = 0;

        // Calculate the total gas and total cost
        for (int i = 0; i < n; i++) {
            totalGas += gas[i];
            totalCost += cost[i];
        }

        // If total gas is less than total cost, no solution exists
        if (totalGas < totalCost) {
            return -1;
        }

        // Iterate through the stations to find the starting point
        for (int i = 0; i < n; i++) {
            currentGas += gas[i] - cost[i]; // Update current gas
            if (currentGas < 0) {
                // If current gas is negative, reset starting station and current gas
                startingStation = i + 1;
                currentGas = 0;
            }
        }
        // Return the starting station
        return startingStation;
    }

    /**
     * **Approach 4: Dynamic Programming (Inefficient - for demonstration)**
     *
     * * Creates a 2D DP table to store whether a trip is possible from each starting station to each destination.
     * * dp[i][j] stores true if it is possible to travel from station i to station j
     * * Fills the table based on the gas and cost at each station.
     * * This approach is inefficient for this problem but demonstrates DP.
     * * Time Complexity: O(n^2), where n is the number of gas stations.
     * * Space Complexity: O(n^2)
     */
    public int canCompleteCircuitDP(int[] gas, int[] cost) {
        int n = gas.length;
        boolean[][] dp = new boolean[n][n];

        // Initialize the DP table
        for (int i = 0; i < n; i++) {
            dp[i][i] = true; // It's always possible to reach the starting station itself.
        }

        // Iterate through all possible starting stations
        for (int start = 0; start < n; start++) {
            // Iterate through all possible ending stations
            for (int end = 0; end < n; end++) {
                if (start == end) continue;
                int currentGas = 0;
                int currentPosition = start;
                int stationsVisited = 0;

                while(stationsVisited < n){
                    currentGas += gas[currentPosition];
                    currentGas -= cost[currentPosition];
                    if(currentGas < 0){
                        break;
                    }
                    currentPosition = (currentPosition + 1) % n;
                    stationsVisited++;
                    if(currentPosition == end){
                        dp[start][end] = true;
                        break;
                    }

                }
            }
        }

        // Check for a starting station that can complete a full circuit
        for (int i = 0; i < n; i++) {
            boolean canComplete = true;
            for(int j = 0; j < n; j++){
                if(!dp[i][j]){
                    canComplete = false;
                    break;
                }
            }
            if (canComplete) {
                return i;
            }
        }
        return -1;
    }



    /**
     * **Approach 5: Using Prefix Sum (More Detailed Explanation)**
     *
     * * This approach is similar to the Greedy approach but provides a more in-depth explanation
     * * Calculates the difference between gas and cost at each station (gas[i] - cost[i]).
     * * Computes the cumulative sum of these differences.
     * * If the total sum is negative, no solution exists.
     * * The starting station is the station where the cumulative sum is the lowest.
     * * Time Complexity: O(n), where n is the number of gas stations.
     * * Space Complexity: O(1)
     */
    public int canCompleteCircuitPrefixSum(int[] gas, int[] cost) {
        int n = gas.length;
        int totalSum = 0;
        int currentSum = 0;
        int startingStation = 0;

        for (int i = 0; i < n; i++) {
            int diff = gas[i] - cost[i]; // Calculate difference
            totalSum += diff;           // Accumulate total difference
            currentSum += diff;         // Accumulate current difference

            if (currentSum < 0) {
                // If current sum is negative, update starting station and reset current sum
                startingStation = i + 1;
                currentSum = 0;
            }
        }

        if (totalSum < 0) {
            return -1; // Not possible to complete the circuit
        } else {
            return startingStation; // Return the optimal starting station
        }
    }

    public static void main(String[] args) {
        GasStation gasStation = new GasStation();
        int[] gas = {1, 2, 3, 4, 5};
        int[] cost = {3, 4, 5, 1, 2};

        // Example usage of each approach
        System.out.println("Brute Force: " + gasStation.canCompleteCircuitBruteForce(gas, cost)); // Output: 3
        System.out.println("Optimized Brute Force: " + gasStation.canCompleteCircuitOptimizedBruteForce(gas, cost)); // Output: 3
        System.out.println("Greedy: " + gasStation.canCompleteCircuitGreedy(gas, cost)); // Output: 3
        System.out.println("Dynamic Programming: " + gasStation.canCompleteCircuitDP(gas, cost)); // Output: 3
        System.out.println("Prefix Sum: " + gasStation.canCompleteCircuitPrefixSum(gas, cost)); // Output: 3

        // Example where no solution exists
        int[] gas2 = {2, 3, 4, 3, 1};
        int[] cost2 = {4, 5, 1, 5, 3};
        System.out.println("Brute Force (No Solution): " + gasStation.canCompleteCircuitBruteForce(gas2, cost2)); // Output: -1
        System.out.println("Optimized Brute Force (No Solution): " + gasStation.canCompleteCircuitOptimizedBruteForce(gas2, cost2)); // Output: -1
        System.out.println("Greedy (No Solution): " + gasStation.canCompleteCircuitGreedy(gas2, cost2)); // Output: -1
        System.out.println("Dynamic Programming (No Solution): " + gasStation.canCompleteCircuitDP(gas2, cost2)); // Output: -1
        System.out.println("Prefix Sum (No Solution): " + gasStation.canCompleteCircuitPrefixSum(gas2, cost2)); // Output: -1
    }
}


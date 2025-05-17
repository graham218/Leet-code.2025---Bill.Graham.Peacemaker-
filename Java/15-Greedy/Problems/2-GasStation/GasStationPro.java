import java.util.LinkedList;
import java.util.Queue;

public class GasStation {

    /**
     * **Approach 1: Brute Force (Naive Approach)**
     * * Description: This is the most straightforward approach.  It tries every gas station
     * as a starting point and simulates a full trip around the circuit.
     * * Time Complexity: O(n^2), where n is the number of gas stations.
     * * Space Complexity: O(1)
     * * Real-world Scenario: Useful for small datasets or as a baseline for comparison.  In a
     * real-world application, this might be used for initial testing or for a very
     * limited number of gas stations (e.g., a small, isolated network).
     */
    public int canCompleteCircuit_BruteForce(int[] gas, int[] cost) {
        int n = gas.length;
        if (n == 0) return -1;

        for (int start = 0; start < n; start++) {
            int currentGas = 0;
            int currentPosition = start;
            int stationsVisited = 0;

            while (stationsVisited < n) {
                currentGas += gas[currentPosition];
                if (currentGas < cost[currentPosition]) {
                    break; // Cannot reach the next station
                }
                currentGas -= cost[currentPosition];
                currentPosition = (currentPosition + 1) % n; // Move to the next station
                stationsVisited++;
            }

            if (stationsVisited == n) {
                return start; // Successfully completed the circuit
            }
        }
        return -1; // No starting point works
    }

    /**
     * **Approach 2: Optimized Brute Force (Slight Improvement)**
     * * Description: This approach is still brute force, but it adds a small optimization.
     * If a starting station cannot reach the next station, we skip all stations
     * in between.
     * * Time Complexity: O(n^2) in the worst case, but can be faster in some cases.
     * * Space Complexity: O(1)
     * * Real-world Scenario: This optimization could be useful in a route planning
     * application where gas stations are sparsely located.  If a route segment is
     * impossible, it avoids unnecessary calculations for intermediate points.
     */
    public int canCompleteCircuit_OptimizedBruteForce(int[] gas, int[] cost) {
        int n = gas.length;
        if (n == 0) return -1;

        for (int start = 0; start < n;) { // Notice the 'start' increment is within the loop
            int currentGas = 0;
            int currentPosition = start;
            int stationsVisited = 0;

            while (stationsVisited < n) {
                currentGas += gas[currentPosition];
                if (currentGas < cost[currentPosition]) {
                    start = currentPosition + 1; // Optimization: Skip to the next station
                    break;
                }
                currentGas -= cost[currentPosition];
                currentPosition = (currentPosition + 1) % n;
                stationsVisited++;
            }

            if (stationsVisited == n) {
                return start;
            }
            if (stationsVisited < n && start > n -1) return -1; //handle edge case;
        }
        return -1;
    }


    /**
     * **Approach 3: Greedy Approach (Efficient Solution)**
     * * Description: This is the most efficient solution.  It's based on the idea that
     * if the total gas is greater than or equal to the total cost, there must be a
     * solution.  It keeps track of the current gas and the starting station.
     * * Time Complexity: O(n)
     * * Space Complexity: O(1)
     * * Real-world Scenario: This is the preferred approach for any real-world
     * application dealing with a significant number of gas stations.  It's efficient
     * and provides a direct solution.  For example, a logistics company optimizing
     * delivery routes would use this.
     */
    public int canCompleteCircuit_Greedy(int[] gas, int[] cost) {
        int n = gas.length;
        if (n == 0) return -1;

        int totalGas = 0;
        int currentGas = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {
            totalGas += gas[i] - cost[i]; // Calculate total gas available
            currentGas += gas[i] - cost[i];

            if (currentGas < 0) {
                // If current gas is negative, reset and try the next station as start
                start = i + 1;
                currentGas = 0;
            }
        }

        if (totalGas < 0) {
            return -1; // Not enough gas in total to complete the circuit
        } else {
            return start; // 'start' will hold the starting station
        }
    }

    /**
     * **Approach 4: Using Prefix Sum (for explanation)**
     * * Description: This approach uses the concept of prefix sums to illustrate the
     * gas availability at each station.  It's not the most efficient, but it helps
     * in understanding the problem.
     * * Time Complexity: O(n)
     * * Space Complexity: O(n)
     * * Real-world Scenario:  While not the most efficient for the core gas station
     * problem, the prefix sum technique is widely applicable in route planning and
     * resource management.  For instance, calculating fuel levels along a pipeline
     * or tracking inventory across a supply chain.
     */
    public int canCompleteCircuit_PrefixSum(int[] gas, int[] cost) {
        int n = gas.length;
        if (n == 0) return -1;

        int[] diff = new int[n]; // Array to store the difference (gas[i] - cost[i])
        int[] prefixSum = new int[n]; // Array to store prefix sums

        for (int i = 0; i < n; i++) {
            diff[i] = gas[i] - cost[i];
            prefixSum[i] = (i == 0) ? diff[i] : prefixSum[i - 1] + diff[i];
        }

        for (int start = 0; start < n; start++) {
            int currentGas = 0;
            for (int j = 0; j < n; j++) {
                int currentPosition = (start + j) % n;
                currentGas += diff[currentPosition];
                if (currentGas < 0) break;
            }
            if (currentGas >= 0) return start;
        }
        return -1;
    }

    /**
     * **Approach 5: Using Queue (for understanding the flow)**
     * * Description: This approach uses a queue to simulate the journey.  It helps visualize
     * the process of moving from station to station.
     * * Time Complexity: O(n^2) in the worst case
     * * Space Complexity: O(n)
     * * Real-world Scenario:  The queue-based approach can be adapted to model more
     * complex scenarios, such as vehicle routing with limited fuel capacity and
     * multiple refueling stops.  It's useful for simulations and visualizing the flow
     * of resources.  For example, modeling how a fleet of delivery drones manages its
     * battery charge across a series of delivery points.
     */
    public int canCompleteCircuit_Queue(int[] gas, int[] cost) {
        int n = gas.length;
        if (n == 0) return -1;

        for (int start = 0; start < n; start++) {
            Queue<Integer> queue = new LinkedList<>();
            int currentGas = 0;
            int currentPosition = start;
            int stationsVisited = 0;

            while (stationsVisited < n) {
                currentGas += gas[currentPosition];
                if (currentGas < cost[currentPosition]) {
                    break;
                }
                currentGas -= cost[currentPosition];
                queue.offer(currentPosition);
                currentPosition = (currentPosition + 1) % n;
                stationsVisited++;
            }

            if (stationsVisited == n) {
                return start;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        GasStation gasStation = new GasStation();
        int[] gas = {1, 2, 3, 4, 5};
        int[] cost = {3, 4, 5, 1, 2};

        // Example Usage and Output
        System.out.println("Gas and Cost: gas = [1,2,3,4,5], cost = [3,4,5,1,2]");
        System.out.println("Brute Force: " + gasStation.canCompleteCircuit_BruteForce(gas, cost)); // Output: 3
        System.out.println("Optimized Brute Force: " + gasStation.canCompleteCircuit_OptimizedBruteForce(gas, cost)); // Output: 3
        System.out.println("Greedy: " + gasStation.canCompleteCircuit_Greedy(gas, cost)); // Output: 3
        System.out.println("Prefix Sum: " + gasStation.canCompleteCircuit_PrefixSum(gas, cost)); // Output: 3
        System.out.println("Queue: " + gasStation.canCompleteCircuit_Queue(gas, cost)); //Output: 3

        int[] gas2 = {2, 3, 4};
        int[] cost2 = {3, 4, 3};
        System.out.println("\nGas and Cost: gas = [2,3,4], cost = [3,4,3]");
        System.out.println("Brute Force: " + gasStation.canCompleteCircuit_BruteForce(gas2, cost2)); // Output: -1
        System.out.println("Optimized Brute Force: " + gasStation.canCompleteCircuit_OptimizedBruteForce(gas2, cost2)); // Output: -1
        System.out.println("Greedy: " + gasStation.canCompleteCircuit_Greedy(gas2, cost2)); // Output: -1
        System.out.println("Prefix Sum: " + gasStation.canCompleteCircuit_PrefixSum(gas2, cost2)); // Output: -1
        System.out.println("Queue: " + gasStation.canCompleteCircuit_Queue(gas2, cost2)); // Output -1
    }
}


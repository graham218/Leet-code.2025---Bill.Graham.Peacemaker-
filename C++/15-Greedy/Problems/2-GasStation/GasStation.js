/*
Problem: Gas Station

There are n gas stations along a circular route, where the amount of gas at the i-th station is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the i-th station to the next (i+1)th station.
You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction; otherwise, return -1. If there exists a solution, it is guaranteed to be unique.

Example 1:
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at the station with index 3 (index 0 is the first station).
- After filling the tank with 4 liters of gas, you have 4 liters of gas in the tank.
- You drive to the next station, spending 1 liter of gas.  Now you have 3 liters of gas.
- You fill the tank with 5 liters of gas, so you have 8 liters of gas.
- You drive to the next station, spending 2 liters of gas.  Now you have 6 liters of gas.
- You fill the tank with 1 liter of gas, so you have 7 liters of gas.
- You drive to the next station, spending 3 liters of gas.  Now you have 4 liters of gas.
- You fill the tank with 2 liters of gas, so you have 6 liters of gas.
- You drive to the next station, spending 4 liters of gas.  Now you have 2 liters of gas.
- You drive to the starting station, spending 5 liters of gas. You have reached the end.
- Therefore, the starting station's index is 3.

Example 2:
Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Start at station 2. You have 4 liters of gas. After traveling to the next station, you have 1 liter of gas. You cannot continue to the next gas station as you don't have enough gas.
*/

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function canCompleteCircuitBruteForce(gas, cost) {
    const n = gas.length;
    for (let start = 0; start < n; start++) {
        let currentGas = 0;
        let currentStation = start;
        let traveledStations = 0;

        while (traveledStations < n) {
            currentGas += gas[currentStation];
            if (currentGas < cost[currentStation]) {
                break; // Cannot reach the next station
            }
            currentGas -= cost[currentStation];
            currentStation = (currentStation + 1) % n; // Move to the next station in a circular manner
            traveledStations++;
        }

        if (traveledStations === n) {
            return start; // Successfully completed the circuit
        }
    }
    return -1; // No starting station works
}

/**
 * Approach 2: Optimized Brute Force
 * Time Complexity: O(n^2) -  Worst case is still O(n^2), but often performs better.
 * Space Complexity: O(1)
 */
function canCompleteCircuitOptimizedBruteForce(gas, cost) {
    const n = gas.length;
    for (let start = 0; start < n; start++) {
        let currentGas = 0;
        let currentStation = start;
        let traveledStations = 0;

        // First, check if the starting station has enough gas to reach the *next* station.
        if (gas[start] < cost[start]) {
            continue; // Optimization: Skip starting stations that clearly don't work.
        }

        while (traveledStations < n) {
            currentGas += gas[currentStation];
            if (currentGas < cost[currentStation]) {
                break;
            }
            currentGas -= cost[currentStation];
            currentStation = (currentStation + 1) % n;
            traveledStations++;
        }

        if (traveledStations === n) {
            return start;
        }
    }
    return -1;
}



/**
 * Approach 3: Greedy Approach 1
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function canCompleteCircuitGreedy1(gas, cost) {
    const n = gas.length;
    let totalGas = 0;
    let totalCost = 0;
    let startingStation = 0;
    let currentGas = 0;

    for (let i = 0; i < n; i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        currentGas += gas[i] - cost[i];

        if (currentGas < 0) {
            // If currentGas becomes negative, it means we cannot reach the next station from the current starting station.
            // So, we reset currentGas and try the next station as the starting station.
            startingStation = i + 1;
            currentGas = 0;
        }
    }

    if (totalGas < totalCost) {
        return -1; // If total gas is less than total cost, it's impossible to complete the circuit.
    } else {
        return startingStation; // Otherwise, the startingStation we found is the answer.
    }
}

/**
 * Approach 4: Greedy Approach 2 (Similar to Approach 3, but with more detailed comments)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function canCompleteCircuitGreedy2(gas, cost) {
    const n = gas.length;
    let start = 0; // Potential starting station
    let remainingGas = 0; // Track remaining gas in the tank
    let totalRemaining = 0; // Track total remaining gas

    for (let i = 0; i < n; i++) {
        remainingGas += gas[i] - cost[i]; // Calculate gas after visiting station i
        totalRemaining += gas[i] - cost[i]; // Accumulate the gas difference

        if (remainingGas < 0) {
            // If we run out of gas before reaching the next station,
            start = i + 1;      // the next station is the new potential start
            remainingGas = 0;  // and we reset the remaining gas
        }
    }

    if (totalRemaining < 0) {
        return -1; // If the total gas difference is negative, no solution exists
    } else {
        return start; // Otherwise, 'start' is the valid starting station
    }
}

/**
 * Approach 5: Using Array Reduce
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function canCompleteCircuitReduce(gas, cost) {
    const n = gas.length;
    let totalRemaining = 0;
    let start = 0;
    let remainingGas = 0;

    gas.reduce((acc, val, index) => {
        totalRemaining += val - cost[index];
        remainingGas += val - cost[index];
        if (remainingGas < 0) {
            start = index + 1;
            remainingGas = 0;
        }
        return acc + val - cost[index];
    }, 0);

    return totalRemaining < 0 ? -1 : start;
}

// Example usage:
const gas1 = [1, 2, 3, 4, 5];
const cost1 = [3, 4, 5, 1, 2];
const gas2 = [2, 3, 4];
const cost2 = [3, 4, 3];

console.log("Example 1:");
console.log("Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]");
console.log("Brute Force:", canCompleteCircuitBruteForce(gas1, cost1)); // Output: 3
console.log("Optimized Brute Force:", canCompleteCircuitOptimizedBruteForce(gas1, cost1)); // Output: 3
console.log("Greedy 1:", canCompleteCircuitGreedy1(gas1, cost1)); // Output: 3
console.log("Greedy 2:", canCompleteCircuitGreedy2(gas1, cost1)); // Output: 3
console.log("Reduce:", canCompleteCircuitReduce(gas1, cost1));   // Output: 3


console.log("\nExample 2:");
console.log("Input: gas = [2,3,4], cost = [3,4,3]");
console.log("Brute Force:", canCompleteCircuitBruteForce(gas2, cost2)); // Output: -1
console.log("Optimized Brute Force:", canCompleteCircuitOptimizedBruteForce(gas2, cost2)); // Output: -1
console.log("Greedy 1:", canCompleteCircuitGreedy1(gas2, cost2)); // Output: -1
console.log("Greedy 2:", canCompleteCircuitGreedy2(gas2, cost2)); // Output: -1
console.log("Reduce:", canCompleteCircuitReduce(gas2, cost2));   // Output: -1

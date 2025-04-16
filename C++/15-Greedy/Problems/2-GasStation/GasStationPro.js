/*
The "Gas Station" problem:

You are given an array of gas stations along a circular route, where gas[i] is the amount of gas available at the i-th station, and cost[i] is the amount of gas required to travel from the i-th station to the (i+1)-th station.  Determine the starting gas station index if you can complete one full circuit.

Problem Variations and Real-World Applications:

Here are five variations of the Gas Station problem, along with real-world applications and JavaScript implementations:

1.  **Basic Gas Station Problem:**
    * **Description:** Find a starting station to complete the circuit.
    * **Real-World Application:** Route planning for delivery trucks with fuel constraints.
*/
/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @return {number}
 */
const canCompleteCircuit = function (gas, cost) {
    const n = gas.length;
    let totalGas = 0;
    let currentGas = 0;
    let startingStation = 0;

    for (let i = 0; i < n; i++) {
        totalGas += gas[i] - cost[i];
        currentGas += gas[i] - cost[i];
        if (currentGas < 0) {
            startingStation = i + 1;
            currentGas = 0;
        }
    }

    return totalGas >= 0 ? startingStation : -1;
};

// Example usage:
const gas1 = [1, 2, 3, 4, 5];
const cost1 = [3, 4, 5, 1, 2];
console.log("Basic Gas Station Problem:");
console.log(canCompleteCircuit(gas1, cost1)); // Output: 3

const gas2 = [2, 3, 4];
const cost2 = [3, 4, 3];
console.log(canCompleteCircuit(gas2, cost2)); // Output: -1

/*
2.  **Gas Station with Limited Tank Capacity:**
    * **Description:** You have a limited fuel tank capacity.  Can you complete the circuit?
    * **Real-World Application:** Planning routes for drones with limited battery capacity.
*/
/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @param {number} tankCapacity
 * @return {boolean}
 */
const canCompleteCircuitWithTank = function (gas, cost, tankCapacity) {
    const n = gas.length;
    let currentGas = 0;
    let startingStation = 0;
    let traveledStations = 0; // Keep track of how many stations we've visited

    for (let i = 0; i < n * 2; i++) { // Iterate twice the length to simulate circularity
        const stationIndex = i % n; // Use modulo to handle circular array
        currentGas += gas[stationIndex];

        if (currentGas < cost[stationIndex]) {
            // Cannot reach the next station
            if (traveledStations >= n) return false; // Circuit cannot be completed
            startingStation = stationIndex + 1;
            currentGas = 0;
            traveledStations = 0; // Reset count when starting from new station
        } else {
            currentGas -= cost[stationIndex];
            traveledStations++;
            if (currentGas > tankCapacity) {
                return false; // Exceeds tank capacity
            }
            if (traveledStations >= n) {
                return true; // Completed the circuit
            }
        }
    }
    return false; //cannot complete
};

// Example usage:
const gas3 = [1, 2, 3, 4, 5];
const cost3 = [3, 4, 5, 1, 2];
const tankCapacity1 = 5;
console.log("\nGas Station Problem with Limited Tank:");
console.log(canCompleteCircuitWithTank(gas3, cost3, tankCapacity1)); // Output: true (Starting at 3, gas at each station: 4, 6, 9, 8, 6. Cost: 1, 2, 3, 4, 5)

const gas4 = [2, 3, 4];
const cost4 = [3, 4, 3];
const tankCapacity2 = 4;
console.log(canCompleteCircuitWithTank(gas4, cost4, tankCapacity2)); // Output: false

const gas5 = [1, 5, 3, 4, 5];
const cost5 = [3, 4, 5, 1, 2];
const tankCapacity3 = 6;
console.log(canCompleteCircuitWithTank(gas5, cost5, tankCapacity3)); //Output: false

/*
3.  **Gas Station with Variable Costs:**
    * **Description:** The cost of gas varies at each station. Find the cheapest starting point.
    * **Real-World Application:** Optimizing refueling stops for long-haul trucks to minimize fuel expenses.
*/

/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @param {number[]} pricePerGallon
 * @return {number}
 */
const findCheapestStartingStation = function (gas, cost, pricePerGallon) {
    const n = gas.length;
    let minCost = Infinity;
    let cheapestStartingStation = -1;

    for (let start = 0; start < n; start++) {
        let currentGas = 0;
        let currentCost = 0;
        let possible = true;

        for (let i = 0; i < n; i++) {
            const stationIndex = (start + i) % n;
            currentGas += gas[stationIndex];
            if (currentGas < cost[stationIndex]) {
                possible = false;
                break;
            }
            currentGas -= cost[stationIndex];
            currentCost += cost[stationIndex] * pricePerGallon[stationIndex];
        }

        if (possible && currentCost < minCost) {
            minCost = currentCost;
            cheapestStartingStation = start;
        }
    }

    return cheapestStartingStation;
};

// Example usage:
const gas6 = [1, 2, 3, 4, 5];
const cost6 = [3, 4, 5, 1, 2];
const pricePerGallon1 = [2, 3, 4, 1, 2]; // Price of gas at each station
console.log("\nGas Station Problem with Variable Costs:");
console.log(findCheapestStartingStation(gas6, cost6, pricePerGallon1)); // Output: 3

const gas7 = [2, 3, 4];
const cost7 = [3, 4, 3];
const pricePerGallon2 = [5, 2, 1];
console.log(findCheapestStartingStation(gas7, cost7, pricePerGallon2)); // Output: -1

const gas8 = [1, 2, 3, 4, 5];
const cost8 = [3, 4, 5, 1, 2];
const pricePerGallon3 = [2, 3, 4, 1, 5];
console.log(findCheapestStartingStation(gas8, cost8, pricePerGallon3));
/*
4.  **Gas Station with Two-Way Roads:**
    * **Description:** You can travel between stations in both directions. Find the shortest path.
    * **Real-World Application:** Optimizing routes in a city with two-way streets and varying gas prices.
*/
/**
 * @param {number[]} gas
 * @param {number[][]} costMatrix // costMatrix[i][j] is cost from i to j
 * @return {number[]} [startingStation, minCost]
 */
const findShortestPathTwoWay = function (gas, costMatrix) {
    const n = gas.length;
    let minCost = Infinity;
    let shortestPath = [-1, -1];

    for (let start = 0; start < n; start++) {
        let currentGas = 0;
        let currentCost = 0;
        let possible = true;
        const visited = new Array(n).fill(false);
        let currentStation = start;
        let stationsVisited = 0;

        while (stationsVisited < n) {
            visited[currentStation] = true;
            stationsVisited++;
            let nextStation = -1;
            let minNextCost = Infinity;

            for (let j = 0; j < n; j++) {
                if (!visited[j]) {
                    if (currentGas + gas[currentStation] >= costMatrix[currentStation][j]) {
                        if (costMatrix[currentStation][j] < minNextCost) {
                            minNextCost = costMatrix[currentStation][j];
                            nextStation = j;
                        }
                    }
                }
            }
            if (nextStation === -1) {
                possible = false;
                break;
            }
            currentGas += gas[currentStation] - costMatrix[currentStation][nextStation];
            currentCost += costMatrix[currentStation][nextStation];
            currentStation = nextStation;
        }
        if (possible && currentStation === start && currentCost < minCost) {
            minCost = currentCost;
            shortestPath = [start, minCost];
        }
    }
    return shortestPath;
};

// Example usage:
const gas9 = [10, 2, 3, 6, 5];
const costMatrix1 = [
    [0, 2, 10, 12, 5],
    [2, 0, 5, 8, 4],
    [10, 5, 0, 3, 9],
    [12, 8, 3, 0, 6],
    [5, 4, 9, 6, 0]
];
console.log("\nGas Station Problem with Two-Way Roads:");
console.log(findShortestPathTwoWay(gas9, costMatrix1));

const gas10 = [1, 2, 3];
const costMatrix2 = [
    [0, 5, 10],
    [5, 0, 3],
    [10, 3, 0]
];
console.log(findShortestPathTwoWay(gas10, costMatrix2));

/*
5. **Gas Station with Service Time:**
* **Description**: Each gas station has a service time.  Find the optimal starting station to minimize total time.
* **Real-world application**: Route optimization for emergency vehicles (ambulances, fire trucks) where time is critical.
*/

/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @param {number[]} serviceTime
 * @return {number}
 */
const findOptimalStartingStationWithServiceTime = function (gas, cost, serviceTime) {
    const n = gas.length;
    let minTotalTime = Infinity;
    let optimalStartingStation = -1;

    for (let start = 0; start < n; start++) {
        let currentGas = 0;
        let totalTime = 0;
        let possible = true;

        for (let i = 0; i < n; i++) {
            const stationIndex = (start + i) % n;
            currentGas += gas[stationIndex];
            if (currentGas < cost[stationIndex]) {
                possible = false;
                break;
            }
            currentGas -= cost[stationIndex];
            totalTime += cost[stationIndex] + serviceTime[stationIndex];
        }

        if (possible && totalTime < minTotalTime) {
            minTotalTime = totalTime;
            optimalStartingStation = start;
        }
    }

    return optimalStartingStation;
};

// Example Usage
const gas11 = [1, 2, 3, 4, 5];
const cost11 = [3, 4, 5, 1, 2];
const serviceTime1 = [2, 3, 1, 4, 2];
console.log("\nGas Station Problem with Service Time:");
console.log(findOptimalStartingStationWithServiceTime(gas11, cost11, serviceTime1));

const gas12 = [2, 3, 4];
const cost12 = [3, 4, 3];
const serviceTime2 = [1, 2, 1];
console.log(findOptimalStartingStationWithServiceTime(gas12, cost12, serviceTime2));

const gas13 = [10, 2, 5, 4, 5];
const cost13 = [3, 4, 5, 1, 2];
const serviceTime3 = [5, 1, 2, 3, 1];
console.log(findOptimalStartingStationWithServiceTime(gas13, cost13, serviceTime3));

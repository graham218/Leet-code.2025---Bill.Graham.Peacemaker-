// Prefix Sum - Five Approaches with Real-World Examples

/*
Prefix Sum is a technique that allows us to quickly calculate the sum of a contiguous subarray (a portion of an array).  It involves creating a new array, often called the prefix sum array, where each element represents the sum of all elements up to that index in the original array.

Why is it useful?
    * Efficiency:  Calculating subarray sums becomes O(1) time complexity after the prefix sum array is built (which is O(n)).  Without it, calculating subarray sums repeatedly would be O(n) each time.
    * Real-World Applications:  Very common in data analysis, image processing, and game development.
*/

// Approach 1: Basic Prefix Sum (for single queries)
// Example: Calculating cumulative sales totals.
function basicPrefixSum(arr) {
    const n = arr.length;
    const prefixSum = new Array(n);

    if (n === 0) return [];

    prefixSum[0] = arr[0]; // The first element is the same.
    for (let i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i]; // Sum up to the current element.
    }
    return prefixSum;
}

function getSum(prefixSum, left, right) {
    // Handle edge cases:
    if (left < 0 || right >= prefixSum.length || left > right) {
        return "Invalid input"; // Or throw an error, depending on the application.
    }
    if (left === 0) {
        return prefixSum[right]; // Sum from the start.
    }
    return prefixSum[right] - prefixSum[left - 1]; //  The core logic.
}

// --- Example 1: Cumulative Sales ---
const monthlySales = [200, 350, 150, 400, 250, 300]; // Sales for each month
const cumulativeSales = basicPrefixSum(monthlySales);
console.log("Cumulative Sales:", cumulativeSales); // Output: [200, 550, 700, 1100, 1350, 1650]

// Get total sales from month 2 to 4 (months are 1-indexed, so indices 1 to 3)
const salesFromMonth2To4 = getSum(cumulativeSales, 1, 3);
console.log("Sales from Month 2 to 4:", salesFromMonth2To4); // Output: 900



// Approach 2: Prefix Sum with Multiple Queries (Optimized)
// Example:  Analyzing website traffic over different date ranges.
function prefixSumMultipleQueries(arr) {
  const n = arr.length;
  const prefixSum = new Array(n + 1); // One extra element.
  prefixSum[0] = 0; // Important:  Makes calculations cleaner.

  for (let i = 1; i <= n; i++) {
    prefixSum[i] = prefixSum[i - 1] + arr[i - 1];
  }
  return prefixSum;
}

function getSumMultipleQueries(prefixSum, left, right) {
    // Handle edge cases:
    if (left < 1 || right > prefixSum.length - 1 || left > right) {
        return "Invalid input";
    }
    return prefixSum[right] - prefixSum[left - 1]; // Simpler formula.
}

// --- Example 2: Website Traffic Analysis ---
const dailyTraffic = [120, 150, 200, 180, 250, 300, 280];  // Daily website visits
const trafficPrefixSum = prefixSumMultipleQueries(dailyTraffic);
console.log("Traffic Prefix Sum:", trafficPrefixSum); // Output: [0, 120, 270, 470, 650, 900, 1200, 1480]

// Get total traffic from day 3 to 5 (days are 1-indexed)
const trafficDay3To5 = getSumMultipleQueries(trafficPrefixSum, 3, 5);
console.log("Traffic from Day 3 to 5:", trafficDay3To5); // Output: 630

// Get total traffic from day 1 to 7
const trafficDay1To7 = getSumMultipleQueries(trafficPrefixSum, 1, 7);
console.log("Traffic from Day 1 to 7:", trafficDay1To7); // Output: 1480



// Approach 3: 2D Prefix Sum (for matrices)
// Example: Image processing (calculating the sum of pixel intensities in a region).
function prefixSum2D(matrix) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    const prefixSum = Array(rows + 1).fill(null).map(() => Array(cols + 1).fill(0)); // Extra row and column of 0s.

    for (let i = 1; i <= rows; i++) {
        for (let j = 1; j <= cols; j++) {
            prefixSum[i][j] = matrix[i - 1][j - 1] +
                              prefixSum[i - 1][j] +
                              prefixSum[i][j - 1] -
                              prefixSum[i - 1][j - 1];
        }
    }
    return prefixSum;
}

function getSum2D(prefixSum, row1, col1, row2, col2) {
    // Handle edge cases:
    if (row1 < 1 || col1 < 1 || row2 > prefixSum.length - 1 || col2 > prefixSum[0].length - 1 || row1 > row2 || col1 > col2) {
        return "Invalid input";
    }
    return prefixSum[row2][col2] -
           prefixSum[row1 - 1][col2] -
           prefixSum[row2][col1 - 1] +
           prefixSum[row1 - 1][col1 - 1];
}

// --- Example 3: Image Processing ---
const imageMatrix = [
    [20, 30, 40],
    [50, 60, 70],
    [80, 90, 100]
]; // Pixel intensities
const imagePrefixSum = prefixSum2D(imageMatrix);
console.log("2D Prefix Sum:", imagePrefixSum);
/* Output:
[
  [0, 0, 0, 0],
  [0, 20, 50, 90],
  [0, 70, 160, 270],
  [0, 150, 330, 510]
]
*/

// Get sum of pixel intensities in the sub-rectangle from (1,1) to (2,2)  (1-indexed)
const sumRegion11To22 = getSum2D(imagePrefixSum, 1, 1, 2, 2);
console.log("Sum of region (1,1) to (2,2):", sumRegion11To22); // Output: 180



// Approach 4:  Prefix Sum with Updates (using a difference array)
// Example:  Managing a range of resources with updates and queries.
function prefixSumWithUpdates(arr) {
    const n = arr.length;
    const prefixSum = [...arr]; // Start with a copy
    for (let i = 1; i < n; i++) {
        prefixSum[i] += prefixSum[i - 1];
    }
    return prefixSum;
}

function updateRange(arr, prefixSum, left, right, value) {
    // Handle edge cases:
    if (left < 0 || right >= arr.length || left > right) {
        return "Invalid input";
    }

    // Method 1: Update original array, and recalculate prefix sum (simpler)
     for (let i = left; i <= right; i++) {
         arr[i] += value;
     }
     //Recalculate the prefix sum
     for(let i = 1; i< arr.length; i++){
        prefixSum[i] = prefixSum[i-1] + arr[i];
     }


    // Method 2: Using Difference Array (More efficient for many updates) - commented out
    // diff[i] stores the difference between arr[i] and arr[i-1]
    /*
    const diff = new Array(arr.length);
    diff[0] = arr[0];
    for (let i = 1; i < arr.length; i++) {
        diff[i] = arr[i] - arr[i - 1];
    }

    diff[left] += value;
    if (right + 1 < arr.length) {
        diff[right + 1] -= value;
    }

    // Reconstruct the array and prefix sum
    arr[0] = diff[0];
    prefixSum[0] = diff[0];
    for (let i = 1; i < arr.length; i++) {
        arr[i] = arr[i - 1] + diff[i];
        prefixSum[i] = prefixSum[i-1] + arr[i];
    }
    */
}

function getSumWithUpdates(prefixSum, left, right) {
    if (left < 0 || right >= prefixSum.length || left > right) {
        return "Invalid input";
    }
    if (left === 0) {
        return prefixSum[right];
    }
    return prefixSum[right] - prefixSum[left - 1];
}



// --- Example 4: Resource Management ---
let resources = [10, 15, 20, 25, 30]; // Initial resource allocation
let resourcePrefixSum = prefixSumWithUpdates(resources);
console.log("Initial Resource Prefix Sum:", resourcePrefixSum); // Output: [10, 25, 45, 70, 100]

// Update resources from index 1 to 3 (inclusive) by adding 5
updateRange(resources, resourcePrefixSum, 1, 3, 5);
console.log("Resources after update:", resources); // Output: [10, 20, 25, 30, 30]
console.log("Resource Prefix Sum after update:", resourcePrefixSum); // Output: [10, 30, 55, 85, 115]

// Get the total resources from index 0 to 2
const totalResources0To2 = getSumWithUpdates(resourcePrefixSum, 0, 2);
console.log("Total resources from 0 to 2:", totalResources0To2); // Output: 65



// Approach 5: Online Prefix Sum (for streaming data)
// Example:  Real-time monitoring of stock prices.
class OnlinePrefixSum {
    constructor() {
        this.sum = 0;
        this.values = []; // Store the incoming values
    }

    addValue(value) {
        this.sum += value;
        this.values.push(value);
    }

    getSum() {
        return this.sum;
    }

    getSumRange(left, right) {
        if (left < 0 || right >= this.values.length || left > right) {
             return "Invalid input";
        }
        let rangeSum = 0;
        for(let i = left; i <= right; i++){
            rangeSum += this.values[i];
        }
        return rangeSum;
    }
}

// --- Example 5: Stock Price Monitoring ---
const stockMonitor = new OnlinePrefixSum();

stockMonitor.addValue(100); // Stock price at time 1
stockMonitor.addValue(105); // Stock price at time 2
stockMonitor.addValue(110); // Stock price at time 3
stockMonitor.addValue(108); // Stock price at time 4

console.log("Current Total Stock Value:", stockMonitor.getSum()); // Output: 423
console.log("Sum of stock prices from time 2 to 4:", stockMonitor.getSumRange(1,3)); // Output 323

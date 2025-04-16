/**
 * You are given an array of integers temperatures representing daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to
 * wait after the ith day to get a warmer temperature. If there is no future day
 * for which this is possible, keep answer[i] == 0 instead.
 *
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 *
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 *
 * Constraints:
 * 1 <= temperatures.length <= 105
 * 30 <= temperatures[i] <= 100
 */

/**
 * Approach 1: Brute Force (Project: Weather Data Analysis - Historical Comparison)
 *
 * This approach is straightforward and easy to understand, making it suitable for
 * initial data exploration or when dealing with small datasets.  In a real-world
 * scenario, this could be used to compare daily temperatures against a small
 * historical dataset to find the next warmer day.  For example, you might use
 * this to find the next warmer day in the past week.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
const dailyTemperaturesBruteForce = (temperatures) => {
  const n = temperatures.length;
  const result = new Array(n).fill(0);

  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      if (temperatures[j] > temperatures[i]) {
        result[i] = j - i;
        break;
      }
    }
  }

  return result;
};

/**
 * Approach 2: Stack (Project: Weather Forecasting - Near Future Prediction)
 *
 * This approach uses a stack to keep track of the indices of days with
 * decreasing temperatures.  It's more efficient than brute force and is
 * well-suited for applications where performance is important, such as in
 * a weather forecasting system that needs to quickly predict the next
 * warmer day for a large number of locations.  This is very common and
 * efficient.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperaturesStack = (temperatures) => {
  const n = temperatures.length;
  const result = new Array(n).fill(0);
  const stack = [];

  for (let i = 0; i < n; i++) {
    while (stack.length > 0 && temperatures[i] > temperatures[stack[stack.length - 1]]) {
      const prevIndex = stack.pop();
      result[prevIndex] = i - prevIndex;
    }
    stack.push(i);
  }

  return result;
};

/**
 * Approach 3: Optimized Brute Force (Project: Climate Change Analysis - Trend Identification)
 *
 * This approach optimizes the brute force method slightly by avoiding unnecessary
 * comparisons.  It's still O(n^2), but it can be faster in practice for some
 * datasets.  This could be used in climate change analysis to identify trends
 * in temperature increases over time, where you might be looking for the next
 * warmer day within a specific window (e.g., the next year).
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
const dailyTemperaturesOptimizedBruteForce = (temperatures) => {
    const n = temperatures.length;
    const result = new Array(n).fill(0);

    for (let i = 0; i < n; i++) {
        let foundWarmer = false;
        for (let j = i + 1; j < n; j++) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i;
                foundWarmer = true;
                break;
            }
        }
        if (!foundWarmer) { // Optimization: avoid inner loop if warmer day already found
            result[i] = 0;
        }
    }
    return result;
};


/**
 * Approach 4: Dynamic Programming (Project: Smart Agriculture - Crop Monitoring)
 *
 * This approach uses dynamic programming to store the number of days until a
 * warmer temperature for each day.  It's efficient but uses extra space.  In a
 * smart agriculture context, this could be used to monitor crop health and
 * predict future temperature conditions to optimize irrigation or other
 * interventions.  For example, if you know how many days until a significantly
 * warmer temperature, you could schedule watering accordingly.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperaturesDP = (temperatures) => {
  const n = temperatures.length;
  const result = new Array(n).fill(0);
  const nextWarmer = new Array(101).fill(0); // Assuming temperatures are within [30, 100]

  for (let i = n - 1; i >= 0; i--) {
    let temp = temperatures[i];
    let minDays = Infinity;
    for (let t = temp + 1; t <= 100; t++) {
      if (nextWarmer[t] > 0) {
        minDays = Math.min(minDays, nextWarmer[t] - i);
      }
    }
    if (minDays !== Infinity) {
      result[i] = minDays;
    }
    nextWarmer[temp] = i;
  }
  return result;
};

/**
 * Approach 5: Monotonic Stack (Project: Energy Consumption Prediction - HVAC Optimization)
 *
 * This is another stack-based approach, similar to Approach 2, but with a slightly
 * different way of thinking about the problem.  It maintains a monotonically
 * decreasing stack.  This could be used in energy consumption prediction for
 * HVAC systems, where you need to anticipate temperature changes to optimize
 * heating and cooling schedules.  For example, knowing how many days until a
 * warmer temperature can help you adjust the HVAC system to reduce energy
 * consumption.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperaturesMonotonicStack = (temperatures) => {
    const n = temperatures.length;
    const result = new Array(n).fill(0);
    const stack = []; // Stack of indices, decreasing temperatures

    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && temperatures[i] > temperatures[stack[stack.length - 1]]) {
            const index = stack.pop();
            result[index] = i - index;
        }
        stack.push(i);
    }
    return result;
};



// Example Usage and Output
const temperatures = [73, 74, 75, 71, 69, 72, 76, 73];

console.log("Input Temperatures:", temperatures);
console.log("Brute Force:", dailyTemperaturesBruteForce(temperatures));
console.log("Stack:", dailyTemperaturesStack(temperatures));
console.log("Optimized Brute Force:", dailyTemperaturesOptimizedBruteForce(temperatures));
console.log("Dynamic Programming:", dailyTemperaturesDP(temperatures));
console.log("Monotonic Stack:", dailyTemperaturesMonotonicStack(temperatures));

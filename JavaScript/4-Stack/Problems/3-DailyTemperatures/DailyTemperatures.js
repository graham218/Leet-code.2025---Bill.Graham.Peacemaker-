/*
Daily Temperatures
Given an array of integers temperatures representing daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:
Input: temperatures = [30,60,90]
Output: [1,1,0]

Constraints:
1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
*/

/**
 * Approach 1: Brute Force
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
const dailyTemperatures1 = (temperatures) => {
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
 * Approach 2: Stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperatures2 = (temperatures) => {
  const n = temperatures.length;
  const result = new Array(n).fill(0);
  const stack = []; // Store indices

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
 * Approach 3: Optimized Stack (Slightly more efficient)
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperatures3 = (temperatures) => {
    const n = temperatures.length;
    const result = new Array(n).fill(0);
    const stack = [];

    for (let i = n - 1; i >= 0; i--) { // Iterate from the end
        while (stack.length > 0 && temperatures[i] >= temperatures[stack[stack.length - 1]]) {
            stack.pop();
        }
        if (stack.length > 0) {
            result[i] = stack[stack.length - 1] - i;
        }
        stack.push(i);
    }
    return result;
};

/**
 * Approach 4: Using Array.from and forEach
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperatures4 = (temperatures) => {
    const n = temperatures.length;
    const result = Array.from({ length: n }, () => 0);
    const stack = [];

    temperatures.forEach((temp, i) => {
        while (stack.length > 0 && temp > temperatures[stack[stack.length - 1]]) {
            const prevIndex = stack.pop();
            result[prevIndex] = i - prevIndex;
        }
        stack.push(i);
    });

    return result;
};

/**
 * Approach 5: Monotonic Stack (Most concise)
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
const dailyTemperatures5 = (temperatures) => {
    const n = temperatures.length;
    const ans = new Array(n).fill(0);
    const stack = [];
    for (let i = n - 1; i >= 0; i--) {
        while (stack.length && temperatures[i] >= temperatures[stack[stack.length - 1]]) stack.pop();
        ans[i] = stack.length ? stack[stack.length - 1] - i : 0;
        stack.push(i);
    }
    return ans;
};



// Example usage:
const temperatures1 = [73, 74, 75, 71, 69, 72, 76, 73];
const temperatures2 = [30, 40, 50, 60];
const temperatures3 = [30, 60, 90];

console.log("Input 1: [73, 74, 75, 71, 69, 72, 76, 73]");
console.log("Approach 1 (Brute Force):", dailyTemperatures1(temperatures1));
console.log("Approach 2 (Stack):", dailyTemperatures2(temperatures1));
console.log("Approach 3 (Optimized Stack):", dailyTemperatures3(temperatures1));
console.log("Approach 4 (forEach):", dailyTemperatures4(temperatures1));
console.log("Approach 5 (Monotonic Stack):", dailyTemperatures5(temperatures1));

console.log("\nInput 2: [30, 40, 50, 60]");
console.log("Approach 1 (Brute Force):", dailyTemperatures1(temperatures2));
console.log("Approach 2 (Stack):", dailyTemperatures2(temperatures2));
console.log("Approach 3 (Optimized Stack):", dailyTemperatures3(temperatures2));
console.log("Approach 4 (forEach):", dailyTemperatures4(temperatures2));
console.log("Approach 5 (Monotonic Stack):", dailyTemperatures5(temperatures2));

console.log("\nInput 3: [30, 60, 90]");
console.log("Approach 1 (Brute Force):", dailyTemperatures1(temperatures3));
console.log("Approach 2 (Stack):", dailyTemperatures2(temperatures3));
console.log("Approach 3 (Optimized Stack):", dailyTemperatures3(temperatures3));
console.log("Approach 4 (forEach):", dailyTemperatures4(temperatures3));
console.log("Approach 5 (Monotonic Stack):", dailyTemperatures5(temperatures3));

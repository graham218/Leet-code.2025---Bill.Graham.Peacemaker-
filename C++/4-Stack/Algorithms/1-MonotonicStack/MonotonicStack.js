/*
Monotonic Stack: A stack where the elements are always in sorted order (either non-increasing or non-decreasing).

Applications:
1.  Next/Previous Smaller/Greater Element: Efficiently find the next or previous smaller/greater element for each element in an array.
2.  Largest Rectangular Area in Histogram: Calculate the largest rectangular area under a histogram.
3.  Stock Span Problem: Determine the number of consecutive days the stock price is less than or equal to the current day's price.
4.  Removing K Digits: Remove k digits from a number to get the smallest possible number.
5.  Water Trapping Problem: Calculate the amount of water that can be trapped between bars in a histogram.

Explanation:
A monotonic stack maintains a sorted order of elements.  When a new element is encountered:
    -   If the order is maintained, push the element onto the stack.
    -   If the order is violated, pop elements from the stack until the order is restored, then push the new element.

Time Complexity: O(n) - Each element is pushed and popped at most once.
Space Complexity: O(n) - In the worst case, the stack can hold all the elements.
*/

console.log("Monotonic Stack Examples in JavaScript");

// ------------------------------------------------------------------------------------------------------------------------
// 1. Next Smaller Element (NSE)
// ------------------------------------------------------------------------------------------------------------------------
/*
Problem: Given an array, find the next smaller element for each element.
Input:  [4, 5, 2, 10, 8]
Output: [2, 2, -1, 8, -1]  (where -1 indicates no smaller element to the right)
*/
function nextSmallerElement(arr) {
    const stack = [];
    const result = new Array(arr.length).fill(-1); // Initialize result array with -1

    for (let i = arr.length - 1; i >= 0; i--) {
        // Maintain a decreasing stack
        while (stack.length > 0 && arr[i] <= arr[stack[stack.length - 1]]) {
            stack.pop();
        }
        if (stack.length > 0) {
            result[i] = arr[stack[stack.length - 1]];
        }
        stack.push(i); // Store index, not value
    }
    return result;
}

const arr1 = [4, 5, 2, 10, 8];
const nseResult = nextSmallerElement(arr1);
console.log("\n1. Next Smaller Element:");
console.log("Input:", arr1);
console.log("Output:", nseResult); // Output: [ 2, 2, -1, 8, -1 ]

// ------------------------------------------------------------------------------------------------------------------------
// 2. Previous Smaller Element (PSE)
// ------------------------------------------------------------------------------------------------------------------------
/*
Problem: Given an array, find the previous smaller element for each element.
Input:  [4, 5, 2, 10, 8]
Output: [-1, 4, -1, 2, 2]
*/
function previousSmallerElement(arr) {
    const stack = [];
    const result = new Array(arr.length).fill(-1);

    for (let i = 0; i < arr.length; i++) {
        // Maintain a decreasing stack
        while (stack.length > 0 && arr[i] <= arr[stack[stack.length - 1]]) {
            stack.pop();
        }
        if (stack.length > 0) {
            result[i] = arr[stack[stack.length - 1]];
        }
        stack.push(i);
    }
    return result;
}

const arr2 = [4, 5, 2, 10, 8];
const pseResult = previousSmallerElement(arr2);
console.log("\n2. Previous Smaller Element:");
console.log("Input:", arr2);
console.log("Output:", pseResult); // Output: [ -1, 4, -1, 2, 2 ]

// ------------------------------------------------------------------------------------------------------------------------
// 3. Largest Rectangular Area in Histogram
// ------------------------------------------------------------------------------------------------------------------------
/*
Problem: Given an array of bar heights, find the largest rectangular area that can be formed within the histogram.
Input:  [2, 1, 5, 6, 2, 3]
Output: 10 (Area of rectangle with height 5 and width 2: 5 * 2 = 10)
*/
function largestRectangularArea(heights) {
    const stack = [];
    let maxArea = 0;
    let i = 0;

    while (i < heights.length || stack.length > 0) { //stack can have values left
        if (i < heights.length && (stack.length === 0 || heights[i] >= heights[stack[stack.length - 1]])) {
            stack.push(i);
            i++;
        } else {
            const top = stack.pop();
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            const area = heights[top] * width;
            maxArea = Math.max(maxArea, area);
        }
    }
    return maxArea;
}

const heights = [2, 1, 5, 6, 2, 3];
const largestArea = largestRectangularArea(heights);
console.log("\n3. Largest Rectangular Area in Histogram:");
console.log("Input:", heights);
console.log("Output:", largestArea); // Output: 10

// ------------------------------------------------------------------------------------------------------------------------
// 4. Stock Span Problem
// ------------------------------------------------------------------------------------------------------------------------
/*
Problem: Given an array of stock prices, find the span of each day's price.
The span of a stock's price for a given day is the maximum number of consecutive days
(including today) for which the stock's price is less than or equal to today's price.
Input:  [100, 80, 60, 70, 60, 75, 85]
Output: [  1,  1,  1,  2,  1,  4,  6]
*/
function stockSpan(prices) {
    const stack = [];
    const spans = new Array(prices.length).fill(1); // Initialize spans with 1

    for (let i = 0; i < prices.length; i++) {
        while (stack.length > 0 && prices[i] >= prices[stack[stack.length - 1]]) {
            stack.pop();
        }
        spans[i] = stack.length === 0 ? i + 1 : i - stack[stack.length - 1];
        stack.push(i);
    }
    return spans;
}

const prices = [100, 80, 60, 70, 60, 75, 85];
const spans = stockSpan(prices);
console.log("\n4. Stock Span Problem:");
console.log("Input:", prices);
console.log("Output:", spans); // Output: [ 1, 1, 1, 2, 1, 4, 6 ]

// ------------------------------------------------------------------------------------------------------------------------
// 5. Removing K Digits
// ------------------------------------------------------------------------------------------------------------------------
/*
Problem: Given a non-negative integer num represented as a string, remove k digits from the number
        so that the new number is the smallest possible.
Input:  num = "1432219", k = 3
Output: "121"
*/
function removeKdigits(num, k) {
    if (k === num.length) return "0";
    const stack = [];

    for (const digit of num) {
        while (k > 0 && stack.length > 0 && stack[stack.length - 1] > digit) {
            stack.pop();
            k--;
        }
        stack.push(digit);
    }

    // Remove remaining k digits from the end
    while (k > 0) {
        stack.pop();
        k--;
    }

    // Remove leading zeros
    while (stack.length > 1 && stack[0] === '0') {
        stack.shift();
    }
    return stack.length === 0 ? "0" : stack.join("");
}

const num = "1432219";
const k = 3;
const smallestNum = removeKdigits(num, k);
console.log("\n5. Removing K Digits:");
console.log("Input: num =", num, ", k =", k);
console.log("Output:", smallestNum); // Output: 121

/*
Monotonic Stack:

A monotonic stack is a stack where the elements are always in sorted order, either
monotonically increasing or monotonically decreasing.  It's useful for solving
problems that involve finding the nearest smaller or larger element for each
element in an array.

Here are 5 different approaches with real-world project implementations:
*/

// 1. Monotonically Increasing Stack - Stock Price Prediction
//
//    Problem: Given a list of daily stock prices, find the span for each day.
//    The span of a stock's price today is defined as the maximum number of
//    consecutive days (including today) for which the stock's price is less than or
//    equal to today's price.
//
//    Real-world application:  Algorithmic trading, financial analysis.
//
//    Example:
//    Input:  prices = [100, 80, 60, 70, 60, 75, 85]
//    Output: spans   = [  1,  1,  1,  2,  1,  4,  6]
//
function stockSpan(prices) {
    const stack = []; // Stack to store indices of prices
    const spans = [];
    for (let i = 0; i < prices.length; i++) {
        let span = 1;
        // Pop elements from stack until a greater price is found
        while (stack.length > 0 && prices[stack[stack.length - 1]] <= prices[i]) {
            stack.pop();
        }
        // Calculate span:
        // If stack is empty, the current price is greater than all previous
        if (stack.length === 0) {
            span = i + 1;
        } else {
            // Otherwise, the span is the distance to the previous greater price
            span = i - stack[stack.length - 1];
        }
        spans.push(span);
        stack.push(i); // Push the current index
    }
    return spans;
}

const stockPrices = [100, 80, 60, 70, 60, 75, 85];
const stockSpans = stockSpan(stockPrices);
console.log("1. Stock Price Span:");
console.log("   Prices:", stockPrices);
console.log("   Spans: ", stockSpans); // Output: [1, 1, 1, 2, 1, 4, 6]


// 2. Monotonically Decreasing Stack - Largest Rectangle in Histogram
//
//    Problem: Given an array of integers heights representing the histogram's bar
//    height where the width of each bar is 1, calculate the area of the largest
//    rectangle in the histogram.
//
//    Real-world application:  Image processing, urban planning (analyzing building heights).
//
//    Example:
//    Input:  heights = [2, 1, 5, 6, 2, 3]
//    Output: 10 (The largest rectangle has height 5 and width 2)
//
function largestRectangleArea(heights) {
    const stack = []; // Stack to store indices of heights
    let maxArea = 0;
    // Add a 0 to the end to ensure all bars are processed
    const extendedHeights = [...heights, 0];

    for (let i = 0; i < extendedHeights.length; i++) {
        // Pop bars from the stack if the current bar is shorter
        while (stack.length > 0 && extendedHeights[i] < extendedHeights[stack[stack.length - 1]]) {
            const height = extendedHeights[stack.pop()];
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            maxArea = Math.max(maxArea, height * width);
        }
        stack.push(i); // Push the current index
    }
    return maxArea;
}

const histogramHeights = [2, 1, 5, 6, 2, 3];
const largestArea = largestRectangleArea(histogramHeights);
console.log("\n2. Largest Rectangle in Histogram:");
console.log("   Heights:", histogramHeights);
console.log("   Area:   ", largestArea); // Output: 10


// 3. Monotonic Stack for Next Greater Element
//
//    Problem: Given an array, find the next greater element for each element.
//    The next greater element for an element x is the first greater element to the
//    right of x in the array. If it doesn't exist, return -1.
//
//    Real-world application:  Data analysis, signal processing.
//
//    Example:
//    Input:  nums = [1, 2, 1]
//    Output: [2, -1, 2]
//
function nextGreaterElements(nums) {
    const stack = [];
    const result = new Array(nums.length).fill(-1);
    // Iterate twice to simulate circular array
    for (let i = 0; i < 2 * nums.length; i++) {
        const num = nums[i % nums.length]; // Use modulo for circular array
        // Pop elements from stack until a greater element is found
        while (stack.length > 0 && num > nums[stack[stack.length - 1]]) {
            const index = stack.pop();
            result[index] = num;
        }
        // Only push the index if it's in the first iteration
        if (i < nums.length) {
            stack.push(i);
        }
    }
    return result;
}

const numbers = [1, 2, 1];
const nextGreater = nextGreaterElements(numbers);
console.log("\n3. Next Greater Element:");
console.log("   Numbers:", numbers);
console.log("   Next Greater:", nextGreater); // Output: [2, -1, 2]



// 4. Monotonic Stack for Removing K Digits
//
//    Problem: Given a non-negative integer num represented as a string, remove k digits
//    from the number so that the new number is the smallest possible.
//
//    Real-world application:  Optimization problems, financial calculations.
//
//    Example:
//    Input:  num = "1432219", k = 3
//    Output: "1219"
//
function removeKdigits(num, k) {
    if (k === num.length) return "0";

    const stack = [];
    for (const digit of num) {
        // Pop larger digits from the stack
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
    let result = stack.join('').replace(/^0+/, '');
    return result === "" ? "0" : result;
}

const numberStr = "1432219";
const digitsToRemove = 3;
const smallestNumber = removeKdigits(numberStr, digitsToRemove);
console.log("\n4. Remove K Digits:");
console.log("   Number:", numberStr);
console.log("   K:", digitsToRemove);
console.log("   Smallest Number:", smallestNumber); // Output: "1219"



// 5. Monotonic Stack for Trapping Rain Water
//
//    Problem: Given n non-negative integers representing an elevation map where the
//    width of each bar is 1, compute how much water it can trap after raining.
//
//    Real-world application:  Civil engineering, environmental science.
//
//    Example:
//    Input:  heights = [0,1,0,2,1,0,1,3,2,1,2,1]
//    Output: 6
//
function trapRainWater(heights) {
    let water = 0;
    const stack = []; // Stack to store indices

    for (let i = 0; i < heights.length; i++) {
        // Calculate water for each bar
        while (stack.length > 0 && heights[i] > heights[stack[stack.length - 1]]) {
            const top = stack.pop(); // Index of the top of the "valley"
            if (stack.length === 0) break; // If no left boundary, can't trap water
            const distance = i - stack[stack.length - 1] - 1;
            const boundedHeight = Math.min(heights[i], heights[stack[stack.length - 1]]) - heights[top];
            water += distance * boundedHeight;
        }
        stack.push(i); // Push current index
    }
    return water;
}

const elevationMap = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1];
const trappedWater = trapRainWater(elevationMap);
console.log("\n5. Trapping Rain Water:");
console.log("   Heights:", elevationMap);
console.log("   Trapped Water:", trappedWater); // Output: 6

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

// ----------------------------------------------------------------------------
// 1. Basic Monotonic Stack (Increasing) - Stock Span Problem
// ----------------------------------------------------------------------------
//   * Problem:
//     The stock span problem is a financial problem where we have a series of daily
//     stock prices, and for each day, we need to find the span of the stock's
//     price for that day. The span is defined as the maximum number of consecutive
//     days (including the current day) for which the current day's price is greater
//     than or equal to the price on each of those days.
//
//   * Real-World Application:
//     Algorithmic trading, financial analysis.  Identifying trends in stock prices.
//
//   * Function: stockSpan()
//     Calculates the span for each day's stock price using a monotonic increasing stack.
//
//   * Example:
//     prices: [100, 80, 60, 70, 60, 75, 85]
//     span:   [  1,  1,  1,  2,  1,  4,  6]
// ----------------------------------------------------------------------------
std::vector<int> stockSpan(const std::vector<int>& prices) {
    std::vector<int> span(prices.size());
    std::stack<int> st; // Stack to store indices of days with higher prices

    for (size_t i = 0; i < prices.size(); ++i) {
        // Pop days with prices lower than or equal to the current day's price
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }

        // Calculate the span:
        // If the stack is empty, the current price is the highest so far,
        // so the span is i + 1.  Otherwise, the span is the difference
        // between the current day's index and the index of the nearest
        // day with a higher price.
        span[i] = st.empty() ? (i + 1) : (i - st.top());

        // Push the current day's index onto the stack
        st.push(i);
    }
    return span;
}

// ----------------------------------------------------------------------------
// 2. Monotonic Stack (Decreasing) - Largest Rectangle in Histogram
// ----------------------------------------------------------------------------
//   * Problem:
//     Given an array of integers representing the heights of the bars in a histogram
//     where the width of each bar is 1, find the area of the largest rectangle in the histogram.
//
//   * Real-World Application:
//     Image processing (finding maximum area regions),  resource allocation.
//
//   * Function: largestRectangleArea()
//     Calculates the largest rectangular area in a histogram using a monotonic decreasing stack.
//
//   * Example:
//     heights: [2, 1, 5, 6, 2, 3]
//     largest area: 10 (5 * 2)
// ----------------------------------------------------------------------------
int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) { // Iterate one past the end to handle remaining bars
        // Use a sentinel value of 0 at the end to ensure the stack is emptied.
        int h = (i == n) ? 0 : heights[i];

        while (!st.empty() && h < heights[st.top()]) {
            int top = st.top();
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1); // Calculate width
            maxArea = std::max(maxArea, heights[top] * width);
        }
        st.push(i);
    }
    return maxArea;
}

// ----------------------------------------------------------------------------
// 3. Monotonic Stack with Custom Class -  Maximum Water Trapped
// ----------------------------------------------------------------------------
//   * Problem:
//     Given an array of non-negative integers representing the heights of walls,
//     calculate how much water can be trapped between the walls after the rain.
//
//   * Real-World Application:
//      Flood control,  reservoir management,  civil engineering.
//
//   * Function: trap()
//     Calculates the trapped water using a monotonic decreasing stack.
//
//   * Example:
//      heights: [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
//      trapped water: 6
// ----------------------------------------------------------------------------
int trap(const std::vector<int>& height) {
    std::stack<int> st;
    int water = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();
            if (st.empty()) break; // Important: No left boundary
            int distance = i - st.top() - 1;
            int boundedHeight = std::min(height[i], height[st.top()]) - height[top];
            water += distance * boundedHeight;
        }
        st.push(i);
    }
    return water;
}

// ----------------------------------------------------------------------------
// 4. Monotonic Stack with Pair - Next Smaller Element
// ----------------------------------------------------------------------------
// * Problem:
//   Given an array, find the next smaller element for every element in the array.
//   The next smaller element for an element x is the first element to the right
//   of x in the array that is smaller than x. If no such element exists, return -1.
//
// * Real-World Application:
//   Data analysis, query optimization, and time-series analysis.
//
// * Function: nextSmallerElements()
//   Calculates the next smaller element for each element in the array.
//
// * Example:
//   Input:  arr[] = {4, 5, 2, 10, 8}
//   Output: {2, 2, -1, 8, -1}
// ----------------------------------------------------------------------------
std::vector<int> nextSmallerElements(const std::vector<int>& arr) {
    int n = arr.size();
    std::vector<int> result(n, -1); // Initialize result with -1
    std::stack<std::pair<int, int>> stack; // Store element and its index

    for (int i = n - 1; i >= 0; --i) {
        while (!stack.empty() && arr[i] < stack.top().first) {
            result[stack.top().second] = arr[i]; // Found next smaller
            stack.pop();
        }
        stack.push({arr[i], i}); // Push current element and index
    }
    return result;
}

// ----------------------------------------------------------------------------
// 5. Monotonic Stack for Expression Evaluation - Basic Calculator (No Parentheses)
// ----------------------------------------------------------------------------
// * Problem:
//   Implement a basic calculator to evaluate a simple string expression.
//   The expression string contains only non-negative integers, '+', '-', '*', '/' operators,
//   and spaces. Assume the input expression is always valid.  No parentheses.
//
// * Real-World Application:
//   Compiler design,  interpreters,  and general expression parsing.
//
// * Function: calculate()
//   Evaluates the given arithmetic expression using a monotonic stack.
//
// * Example:
//   Input:  "3+2*2"
//   Output: 7
// ----------------------------------------------------------------------------
int calculate(const std::string& s) {
    std::stack<int> nums;
    int num = 0;
    char op = '+'; // Initialize with '+' to handle the first number
    int n = s.size();

    for (int i = 0; i < n; ++i) {
        if (std::isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == n - 1) {
            if (op == '+') {
                nums.push(num);
            } else if (op == '-') {
                nums.push(-num);
            } else if (op == '*') {
                int top = nums.top();
                nums.pop();
                nums.push(top * num);
            } else if (op == '/') {
                int top = nums.top();
                nums.pop();
                if (num == 0) {
                    return std::numeric_limits<int>::max(); // handle division by zero.
                }
                nums.push(top / num);
            }
            op = s[i];
            num = 0;
        }
    }

    int result = 0;
    while (!nums.empty()) {
        result += nums.top();
        nums.pop();
    }
    return result;
}

// ----------------------------------------------------------------------------
// Main Function (Driver)
// ----------------------------------------------------------------------------
int main() {
    // 1. Stock Span Problem
    std::cout << "\n1. Stock Span Problem:\n";
    std::vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    std::vector<int> span = stockSpan(prices);
    std::cout << "Prices: ";
    for (int price : prices) std::cout << price << " ";
    std::cout << "\nSpan:   ";
    for (int s : span) std::cout << s << " ";
    std::cout << "\n";

    // 2. Largest Rectangle in Histogram
    std::cout << "\n2. Largest Rectangle in Histogram:\n";
    std::vector<int> heights = {2, 1, 5, 6, 2, 3};
    int maxArea = largestRectangleArea(heights);
    std::cout << "Heights: ";
    for (int h : heights) std::cout << h << " ";
    std::cout << "\nLargest Area: " << maxArea << "\n";

    // 3. Trapping Rain Water
    std::cout << "\n3. Trapping Rain Water:\n";
    std::vector<int> waterHeights = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int trappedWater = trap(waterHeights);
    std::cout << "Heights: ";
    for (int h : waterHeights) std::cout << h << " ";
    std::cout << "\nTrapped Water: " << trappedWater << "\n";

    // 4. Next Smaller Element
    std::cout << "\n4. Next Smaller Element:\n";
    std::vector<int> arr = {4, 5, 2, 10, 8};
    std::vector<int> nextSmaller = nextSmallerElements(arr);
    std::cout << "Array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\nNext Smaller Elements: ";
    for (int nse : nextSmaller) std::cout << nse << " ";
    std::cout << "\n";

    // 5. Basic Calculator
    std::cout << "\n5. Basic Calculator:\n";
    std::string expression = "3+2*2";
    int result = calculate(expression);
    std::cout << "Expression: " << expression << "\nResult: " << result << "\n";

    return 0;
}

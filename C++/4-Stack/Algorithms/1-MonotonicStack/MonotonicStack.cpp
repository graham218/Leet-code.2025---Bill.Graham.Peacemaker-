#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Approach 1: Basic Monotonic Increasing Stack (Find Next Greater Element)
// Problem: Given an array, find the next greater element for each element.
// Solution: Use a monotonic increasing stack.
vector<int> nextGreaterElement1(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1); // Initialize result with -1 (default for no greater element)
    stack<int> st; // Stack to store indices, not the elements themselves

    for (int i = 0; i < n; ++i) {
        // While the stack is not empty and the current element is greater than the element at the top of the stack
        while (!st.empty() && arr[i] > arr[st.top()]) {
            result[st.top()] = arr[i]; // The current element is the next greater element for the top of the stack
            st.pop(); // Pop the index from the stack
        }
        st.push(i); // Push the current element's index onto the stack
    }
    return result;
}

// Approach 2: Monotonic Decreasing Stack (Find Previous Smaller Element)
// Problem: Given an array, find the previous smaller element for each element.
// Solution: Use a monotonic decreasing stack.
vector<int> previousSmallerElement(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1); // Initialize result with -1
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        // While the stack is not empty and the current element is smaller than the element at the top of the stack
        while (!st.empty() && arr[i] < arr[st.top()]) {
            st.pop(); // Pop the index from the stack
        }
        if (!st.empty()) {
            result[i] = arr[st.top()]; // The element at the top of the stack is the previous smaller element
        }
        st.push(i);
    }
    return result;
}

// Approach 3: Monotonic Stack for finding Largest Rectangle in Histogram
// Problem: Given an array of heights representing a histogram, find the largest rectangular area.
// Solution: Use a monotonic increasing stack to store indices.
int largestRectangleArea(const vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;
    int i = 0;

    while (i < n || !st.empty()) { // Iterate until the end of the array AND the stack is empty
        if (st.empty() || (i < n && heights[i] >= heights[st.top()])) {
            st.push(i++); // Push the *index*
        } else {
            int top = st.top();
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1; // Calculate width
            int area = heights[top] * width;
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// Approach 4: Monotonic Stack to find the maximum area submatrix of 1's
// Problem: Given a binary matrix, find the largest square submatrix with all 1s.
// Solution: Adapt the largestRectangleArea approach for each row.
int maxAreaSubmatrix(const vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return 0;
    }
    int rows = matrix.size();
    int cols = matrix[0].size();
    int maxArea = 0;

    vector<int> histogram(cols, 0); // Keep track of the histogram for each row

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 1) {
                histogram[j] += 1; // If it's a 1, add to the histogram height
            } else {
                histogram[j] = 0; // If it's a 0, reset the height
            }
        }
        // Calculate the largest rectangle area for the current histogram
        maxArea = max(maxArea, largestRectangleArea(histogram));
    }
    return maxArea;
}

// Approach 5: Using monotonic stack to solve Online Stock Span Problem
// Problem: The stock span problem is a financial problem where we have a series of daily
//            stock prices and we need to calculate the span of the stock's price for each day.
//            The span of the stock's price for a given day is defined as the maximum number of
//            consecutive days (including the current day) that the price of the stock on the current
//            day is less than or equal to the price of the stock on that day.
// Solution: Use a monotonic decreasing stack.
vector<int> stockSpan(const vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> st; // Stack to store indices

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && prices[i] >= prices[st.top()]) {
            st.pop();
        }
        span[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
    return span;
}

int main() {
    // Example usage for each approach
    cout << "Example Usage of Monotonic Stack Approaches:\n";

    // Approach 1
    vector<int> arr1 = {4, 5, 2, 10, 8};
    vector<int> result1 = nextGreaterElement1(arr1);
    cout << "Next Greater Elements: ";
    for (int x : result1) cout << x << " "; // Output: 5 10 10 -1 -1
    cout << endl;

    // Approach 2
    vector<int> arr2 = {10, 4, 2, 5, 12, 3};
    vector<int> result2 = previousSmallerElement(arr2);
    cout << "Previous Smaller Elements: ";
    for (int x : result2) cout << x << " "; // Output: -1 -1 -1 2 5 2
    cout << endl;

    // Approach 3
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    int maxArea = largestRectangleArea(heights);
    cout << "Largest Rectangle Area in Histogram: " << maxArea << endl; // Output: 10

    // Approach 4
    vector<vector<int>> matrix = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 0}
    };
    int maxSubmatrixArea = maxAreaSubmatrix(matrix);
    cout << "Largest Submatrix Area: " << maxSubmatrixArea << endl; // Output: 8

    // Approach 5
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = stockSpan(prices);
    cout << "Stock Span: ";
    for (int x : span) cout << x << " ";  // Output: 1 1 1 2 1 4 6
    cout << endl;

    return 0;
}

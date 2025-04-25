#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits> // For INT_MIN

using namespace std;

// Approach 1: Brute Force
// For each bar, consider it as the minimum height and expand left and right.
int largestRectangleArea_BruteForce(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; ++i) {
        int minHeight = heights[i];
        for (int j = i; j < n; ++j) {
            minHeight = min(minHeight, heights[j]); // Find the minimum height in the current range
            maxArea = max(maxArea, minHeight * (j - i + 1)); // Calculate area and update maxArea
        }
    }
    return maxArea;
}

// Approach 2: Brute Force Optimized
// Slightly optimized version of the brute force approach.
int largestRectangleArea_BruteForceOptimized(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; ++i) {
        int minHeight = heights[i];
        // Calculate area with current bar height as minimum
        for (int j = i; j < n; ++j) {
            minHeight = min(minHeight, heights[j]);
            maxArea = max(maxArea, minHeight * (j - i + 1));
        }
    }
    return maxArea;
}

// Approach 3: Divide and Conquer
// Recursively divide the histogram and find the largest rectangle.
int largestRectangleArea_DivideAndConquer(vector<int>& heights, int start, int end) {
    if (start > end) {
        return 0; // Base case: empty range
    }
    if (start == end) {
        return heights[start]; // Base case: single bar
    }

    int minIndex = start;
    for (int i = start + 1; i <= end; ++i) {
        if (heights[i] < heights[minIndex]) {
            minIndex = i; // Find the index of the minimum height bar
        }
    }
    // Recursively find the largest rectangle in the left and right sub-histograms
    int leftArea = largestRectangleArea_DivideAndConquer(heights, start, minIndex - 1);
    int rightArea = largestRectangleArea_DivideAndConquer(heights, minIndex + 1, end);
    // Calculate the area of the rectangle with the minimum height bar
    int currentArea = heights[minIndex] * (end - start + 1);

    return max(currentArea, max(leftArea, rightArea)); // Return the maximum of the three areas
}

int largestRectangleArea_DivideAndConquer(vector<int>& heights) {
    return largestRectangleArea_DivideAndConquer(heights, 0, heights.size() - 1);
}

// Approach 4: Stack
// Use a stack to keep track of increasing heights and calculate area when a smaller height is encountered.
int largestRectangleArea_Stack(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();
    int i = 0;

    while (i < n || !s.empty()) { // Iterate through the heights and the stack
        if (s.empty() || (i < n && heights[i] >= heights[s.top()])) {
            s.push(i++); // Push the index of the current bar if it's taller or equal to the top of the stack
        } else {
            int top = s.top();
            s.pop(); // Pop the top of the stack
            // Calculate the area with the popped bar as the minimum height
            int area = heights[top] * (s.empty() ? i : i - s.top() - 1);
            maxArea = max(maxArea, area); // Update maxArea
        }
    }
    return maxArea;
}

// Approach 5: Stack Optimized
// Optimized version of the stack approach.  Adds 0 to the beginning and end
int largestRectangleArea_StackOptimized(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();
    // Add 0 to the beginning and end of the heights vector to handle edge cases
    vector<int> modifiedHeights(n + 2);
    modifiedHeights[0] = 0;
    for (int i = 0; i < n; ++i) {
        modifiedHeights[i + 1] = heights[i];
    }
    modifiedHeights[n + 1] = 0;
    n = modifiedHeights.size();

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && modifiedHeights[i] < modifiedHeights[s.top()]) {
            int top = s.top();
            s.pop();
            maxArea = max(maxArea, modifiedHeights[top] * (i - s.empty() ? s.top() + 1 : 0));
        }
        s.push(i);
    }
    return maxArea;
}

int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};

    cout << "Largest Rectangle Area (Brute Force): " << largestRectangleArea_BruteForce(heights) << endl;
    cout << "Largest Rectangle Area (Brute Force Optimized): " << largestRectangleArea_BruteForceOptimized(heights) << endl;
    cout << "Largest Rectangle Area (Divide and Conquer): " << largestRectangleArea_DivideAndConquer(heights) << endl;
    cout << "Largest Rectangle Area (Stack): " << largestRectangleArea_Stack(heights) << endl;
    cout << "Largest Rectangle Area (Stack Optimized): " << largestRectangleArea_StackOptimized(heights) << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to print the histogram (for visualization)
void printHistogram(const vector<int>& heights) {
    cout << "Histogram: ";
    for (int height : heights) {
        cout << height << " ";
    }
    cout << endl;
}

// 1. Brute Force Approach
//    - Calculate area for every possible rectangle.
//    - Time Complexity: O(n^2), Space Complexity: O(1)
int largestRectangleArea_BruteForce(const vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int minHeight = heights[i];
            for (int k = i; k <= j; ++k) {
                minHeight = min(minHeight, heights[k]);
            }
            maxArea = max(maxArea, minHeight * (j - i + 1));
        }
    }
    return maxArea;
}

// 2. Divide and Conquer Approach
//    - Recursively divide the histogram and find the minimum height bar.
//    - The largest rectangle can be:
//      a) entirely to the left of the minimum bar
//      b) entirely to the right of the minimum bar
//      c) include the minimum bar.
//    - Time Complexity: O(n log n) in average case, O(n^2) in worst case, Space Complexity: O(n)
int largestRectangleArea_DivideAndConquer(const vector<int>& heights, int start, int end) {
    if (start > end) {
        return 0;
    }
    if (start == end) {
        return heights[start];
    }

    int minIndex = start;
    for (int i = start + 1; i <= end; ++i) {
        if (heights[i] < heights[minIndex]) {
            minIndex = i;
        }
    }

    int leftArea = largestRectangleArea_DivideAndConquer(heights, start, minIndex - 1);
    int rightArea = largestRectangleArea_DivideAndConquer(heights, minIndex + 1, end);
    int currentArea = heights[minIndex] * (end - start + 1);

    return max(max(leftArea, rightArea), currentArea);
}

int largestRectangleArea_DivideAndConquer(const vector<int>& heights) {
    return largestRectangleArea_DivideAndConquer(heights, 0, heights.size() - 1);
}

// 3. Stack-Based Approach
//    - Use a stack to keep track of increasing heights.
//    - When a smaller height is encountered, calculate the area with the previous heights.
//    - Time Complexity: O(n), Space Complexity: O(n)
int largestRectangleArea_Stack(const vector<int>& heights) {
    int maxArea = 0;
    stack<int> s;
    int n = heights.size();
    int i = 0;

    while (i < n || !s.empty()) { // Modified loop condition
        if (s.empty() || (i < n && heights[i] >= heights[s.top()])) {
            s.push(i++);
        } else {
            int top = s.top();
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, heights[top] * width);
        }
    }
    return maxArea;
}

// 4. Optimized Stack-Based Approach
//    - Similar to the previous stack approach, but adds dummy 0 height bars at the beginning and end
//      of the heights vector to simplify the logic and avoid handling edge cases.
//    - Time Complexity: O(n), Space Complexity: O(n)
int largestRectangleArea_StackOptimized(const vector<int>& heights) {
    int maxArea = 0;
    stack<int> s;
    vector<int> modifiedHeights;
    modifiedHeights.push_back(0); // Add 0 at the beginning
    modifiedHeights.insert(modifiedHeights.end(), heights.begin(), heights.end());
    modifiedHeights.push_back(0); // Add 0 at the end
    int n = modifiedHeights.size();

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && modifiedHeights[i] < modifiedHeights[s.top()]) {
            int top = s.top();
            s.pop();
            int width = i - s.top() - 1;
            maxArea = max(maxArea, modifiedHeights[top] * width);
        }
        s.push(i);
    }
    return maxArea;
}

// 5. Using Nearest Smaller Elements (NSE)
//    - Find the nearest smaller element to the left and right for each bar.
//    - Calculate area using the width between the smaller elements.
//    - Time Complexity: O(n), Space Complexity: O(n)
vector<int> findNSL(const vector<int>& heights) {
    int n = heights.size();
    vector<int> nsl(n);
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        nsl[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
    return nsl;
}

vector<int> findNSR(const vector<int>& heights) {
    int n = heights.size();
    vector<int> nsr(n);
    stack<int> s;

    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        nsr[i] = s.empty() ? n : s.top();
        s.push(i);
    }
    return nsr;
}

int largestRectangleArea_NSE(const vector<int>& heights) {
    int n = heights.size();
    vector<int> nsl = findNSL(heights);
    vector<int> nsr = findNSR(heights);
    int maxArea = 0;

    for (int i = 0; i < n; ++i) {
        int width = nsr[i] - nsl[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    return maxArea;
}

int main() {
    vector<int> histogram = {2, 1, 5, 6, 2, 3};
    printHistogram(histogram);

    cout << "Largest Rectangle Area (Brute Force): " << largestRectangleArea_BruteForce(histogram) << endl;
    cout << "Largest Rectangle Area (Divide and Conquer): " << largestRectangleArea_DivideAndConquer(histogram) << endl;
    cout << "Largest Rectangle Area (Stack): " << largestRectangleArea_Stack(histogram) << endl;
    cout << "Largest Rectangle Area (Stack Optimized): " << largestRectangleArea_StackOptimized(histogram) << endl;
    cout << "Largest Rectangle Area (Nearest Smaller Elements): " << largestRectangleArea_NSE(histogram) << endl;

    return 0;
}

/*
Explanation:

1. Brute Force Approach:
   - This is the simplest approach, but also the least efficient.  It iterates through all possible pairs of bars (i, j) and calculates the area of the rectangle with the minimum height bar within that range.
   - Real-world use case: Good for understanding the problem and for very small input sizes where performance is not critical.  For example, in a very basic internal tool with limited data.

2. Divide and Conquer Approach:
   - This approach recursively divides the histogram into subproblems.  It finds the minimum height bar and calculates the largest rectangle area that includes that bar.  The problem is then solved recursively for the left and right subhistograms.
   - Real-world use case:  This approach can be used in scenarios where the data can be divided into smaller chunks and processed in parallel.  For example, in a distributed computing environment for processing large datasets of histograms.

3. Stack-Based Approach:
   - This approach uses a stack to efficiently keep track of the bars that could potentially form the largest rectangle.  It maintains a stack of increasing bar heights. When a smaller bar is encountered, it calculates the area of the rectangle formed by the previous bars in the stack.
   - Real-world use case:  This is a very efficient approach and is suitable for real-time applications where performance is critical, such as processing streaming data of stock prices to find the largest price range within a given time window.

4. Optimized Stack-Based Approach:
    - This is an optimized version of the stack-based approach. By adding dummy bars of height 0 at the beginning and end of the histogram, we simplify the logic and avoid the need for special handling of the boundaries of the histogram.
    - Real-world use case: This optimized version is often preferred in production systems for its robustness and efficiency.  For example, in a high-performance web server for analyzing website traffic patterns.

5. Using Nearest Smaller Elements (NSE):
   - This approach pre-computes the nearest smaller elements to the left and right for each bar in the histogram.  Then, for each bar, it calculates the area of the largest rectangle that can be formed using that bar as the minimum height, with the left and right boundaries defined by the nearest smaller elements.
   - Real-world use case:  This approach is useful when the nearest smaller elements need to be used for other calculations as well.  For example, in financial analysis where you need to find price support and resistance levels.
*/

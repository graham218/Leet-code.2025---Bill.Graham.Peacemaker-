#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// 1. Brute Force Approach
//   - Concept: Calculate the area for every possible pair of lines and find the maximum.
//   - Real-world application: Useful for testing the correctness of more optimized solutions.  It's a simple,
//     straightforward way to guarantee you've checked everything, even if it's slow.  Good for a small dataset
//     where performance isn't critical.  For example, in a very small batch processing job.
int maxArea_BruteForce(const vector<int>& height) {
    int maxArea = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int width = j - i;
            int h = min(height[i], height[j]);
            int area = width * h;
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// 2. Two Pointers Approach
//   - Concept: Start with the widest possible container and shrink the width, always keeping the taller side.
//   - Real-world application: This is the most common and efficient approach.  Think of optimizing resource allocation.
//     If you have a constraint (the width), you try to maximize the other dimension (height) under that constraint.
//     For example, maximizing the amount of water collected in a reservoir with adjustable walls.
int maxArea_TwoPointers(const vector<int>& height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        int area = width * h;
        maxArea = max(maxArea, area);

        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
    }
    return maxArea;
}

// 3. Optimized Two Pointers (Slightly different traversal)
//   - Concept: Similar to the two-pointers approach, but with a more concise way to move the pointers.
//   - Real-world application:  Micro-optimization of the two-pointer technique.  In performance-critical systems
//      (like high-frequency trading or real-time data processing), even small efficiency gains can be valuable.
int maxArea_OptimizedTwoPointers(const vector<int>& height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxArea = max(maxArea, width * h);
        (height[left] < height[right]) ? ++left : --right; // More compact pointer movement
    }
    return maxArea;
}

// 4. Divide and Conquer (Less practical for this specific problem, but shown for illustration)
//   - Concept: Divide the problem into smaller subproblems, solve them recursively, and combine the results.
//   - Real-world application: Divide and conquer is a fundamental algorithm design paradigm.  While not optimal here,
//     it's crucial in many areas:
//     -  Parallel processing: Breaking down a large task into smaller ones to be executed concurrently.
//     -  Merge sort/Quick sort: Efficient sorting algorithms.
//     -  Fractal generation.
int maxArea_DivideAndConquer(const vector<int>& height, int left, int right) {
    if (left >= right) {
        return 0; // Base case: No area
    }

    int mid = left + (right - left) / 2; // Prevent overflow
    int maxAreaLeft = maxArea_DivideAndConquer(height, left, mid);
    int maxAreaRight = maxArea_DivideAndConquer(height, mid + 1, right);

    // Calculate max area that crosses the midpoint
    int maxCrossArea = 0;
    for (int i = left; i <= mid; ++i) {
        for (int j = mid + 1; j <= right; ++j) {
            maxCrossArea = max(maxCrossArea, (j - i) * min(height[i], height[j]));
        }
    }
    return max(max(maxAreaLeft, maxAreaRight), maxCrossArea);
}

// Wrapper function for Divide and Conquer
int maxArea_DivideAndConquer(const vector<int>& height) {
    return maxArea_DivideAndConquer(height, 0, height.size() - 1);
}

// 5.  Precomputed Heights (Optimization for scenarios with frequent queries, less common)
//   - Concept: Precompute the maximum height seen so far from the left and right.  This can speed up calculations
//     if you need to find the maximum area for many different width constraints on the *same* height array.
//   - Real-world application:  This is a form of caching or memoization.  If you have a data set that doesn't change
//      frequently, but you need to perform the same calculation many times with different parameters, precomputation
//      can save a lot of time.
//      -  Example:  Imagine you have a fixed terrain profile (the `height` vector), and you want to quickly calculate
//         the maximum water that can be contained between any two points on that terrain, for many different pairs
//         of points.
int maxArea_Precomputed(const vector<int>& height) {
    int n = height.size();
    if (n <= 1) return 0;

    vector<int> leftMax(n);  // max height to the left, inclusive
    vector<int> rightMax(n); // max height to the right, inclusive

    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
        leftMax[i] = max(leftMax[i - 1], height[i]);
    }

    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int width = j - i;
            int h = min(leftMax[i], rightMax[j]); // Use precomputed values
            maxArea = max(maxArea, width * h);
        }
    }
    return maxArea;
}

int main() {
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    cout << "Brute Force: " << maxArea_BruteForce(height) << endl;
    cout << "Two Pointers: " << maxArea_TwoPointers(height) << endl;
    cout << "Optimized Two Pointers: " << maxArea_OptimizedTwoPointers(height) << endl;
    cout << "Divide and Conquer: " << maxArea_DivideAndConquer(height) << endl;
    cout << "Precomputed Heights: " << maxArea_Precomputed(height) << endl;

    return 0;
}

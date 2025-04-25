#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to calculate the area of a container given two heights and the distance between them.
int calculateArea(int height1, int height2, int distance) {
    return min(height1, height2) * distance;
}

// Approach 1: Brute Force
// - Iterate through all possible pairs of lines (i, j).
// - Calculate the area for each pair.
// - Keep track of the maximum area found so far.
// - Time Complexity: O(n^2), where n is the number of lines.
// - Space Complexity: O(1).
int maxWaterArea_BruteForce(const vector<int>& height) {
    int maxArea = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int area = calculateArea(height[i], height[j], j - i);
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// Approach 2: Brute Force Optimized
//  - Slightly optimized version of Brute Force
// - Iterate through all possible pairs of lines (i, j).
// - Calculate the area for each pair.
// - Keep track of the maximum area found so far.
// - Time Complexity: O(n^2), where n is the number of lines.
// - Space Complexity: O(1).
int maxWaterArea_BruteForceOptimized(const vector<int>& height) {
    int maxArea = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j > i; --j) { // Start from the end, potentially larger width
            int area = calculateArea(height[i], height[j], j - i);
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}


// Approach 3: Two Pointers
// - Initialize two pointers, one at the beginning (left) and one at the end (right) of the array.
// - Calculate the area between the lines pointed to by the two pointers.
// - Move the pointer with the smaller height towards the center.
// - Update the maximum area if the current area is greater.
// - Repeat until the two pointers meet.
// - Time Complexity: O(n), where n is the number of lines.
// - Space Complexity: O(1).
int maxWaterArea_TwoPointers(const vector<int>& height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int area = calculateArea(height[left], height[right], right - left);
        maxArea = max(maxArea, area);

        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}

// Approach 4: Two Pointers Optimized
// - Optimized version of the Two Pointers approach.
// - Same logic as Two Pointers, but with a slight optimization to potentially skip some iterations.
// - Time Complexity: O(n), where n is the number of lines.
// - Space Complexity: O(1).
int maxWaterArea_TwoPointersOptimized(const vector<int>& height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int area = calculateArea(height[left], height[right], right - left);
        maxArea = max(maxArea, area);

        if (height[left] < height[right]) {
            int currentLeftHeight = height[left];
            while (left < right && height[left] <= currentLeftHeight) {
                left++; // Skip smaller heights
            }
        } else {
            int currentRightHeight = height[right];
            while (left < right && height[right] <= currentRightHeight) {
                right--; // Skip smaller heights
            }
        }
    }
    return maxArea;
}

// Approach 5:  Most Optimal (Same as Approach 3, but with more detailed comments)
// - This is the most efficient approach.
// - It uses the two-pointer technique to minimize the number of calculations.
// - The key idea is that the area is limited by the shorter line.  By moving the pointer
//   associated with the shorter line, we have the potential to find a larger container.
// - Time Complexity: O(n), where n is the number of lines in the input vector.  This is because
//   each pointer (left and right) traverses the array at most once.
// - Space Complexity: O(1), as we only use a constant amount of extra space to store variables
//   (left, right, maxArea, area).  The space used does not depend on the size of the input.
int maxWaterArea_Optimal(const vector<int>& height) {
    // Initialize the maximum area found so far to 0.
    int maxArea = 0;

    // Initialize two pointers:
    // - 'left' starts at the beginning of the height vector (index 0).
    // - 'right' starts at the end of the height vector (index height.size() - 1).
    int left = 0;
    int right = height.size() - 1;

    // Continue the loop as long as the left pointer is to the left of the right pointer.
    // When they meet, there are no more possible containers to consider.
    while (left < right) {
        // Calculate the area of the container formed by the lines at 'left' and 'right'.
        // The width of the container is the distance between the two pointers (right - left).
        // The height of the container is limited by the shorter of the two lines
        // (min(height[left], height[right])).
        int area = min(height[left], height[right]) * (right - left);

        // Update 'maxArea' to store the largest area found so far.
        // The max() function returns the greater of the two values.
        maxArea = max(maxArea, area);

        // The key idea of the two-pointer approach:
        // Move the pointer that points to the shorter line.
        // Why?  Because moving the taller line will always result in a smaller or equal area.
        // Moving the shorter line gives us the possibility of finding a taller line,
        // which could potentially increase the area.
        if (height[left] < height[right]) {
            left++; // Move the left pointer one step to the right.
        } else {
            right--; // Move the right pointer one step to the left.
        }
    }

    // After the loop finishes, 'maxArea' contains the maximum possible area of a container.
    return maxArea;
}


int main() {
    // Example usage of the different approaches.
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    cout << "Heights: ";
    for (int h : height) {
        cout << h << " ";
    }
    cout << endl;

    cout << "Max Area (Brute Force): " << maxWaterArea_BruteForce(height) << endl;
    cout << "Max Area (Brute Force Optimized): " << maxWaterArea_BruteForceOptimized(height) << endl;
    cout << "Max Area (Two Pointers): " << maxWaterArea_TwoPointers(height) << endl;
    cout << "Max Area (Two Pointers Optimized): " << maxWaterArea_TwoPointersOptimized(height) << endl;
    cout << "Max Area (Optimal): " << maxWaterArea_Optimal(height) << endl; // Expected: 49

    // Example with all same heights
    vector<int> sameHeights = {5, 5, 5, 5, 5, 5};
    cout << "\nHeights: ";
    for(int h : sameHeights){
        cout << h << " ";
    }
    cout << endl;
    cout << "Max Area (Optimal - Same Heights): " << maxWaterArea_Optimal(sameHeights) << endl; // Expected 25

    // Example with increasing heights
     vector<int> increasingHeights = {1, 2, 3, 4, 5, 6};
    cout << "\nHeights: ";
    for(int h : increasingHeights){
        cout << h << " ";
    }
    cout << endl;
    cout << "Max Area (Optimal - Increasing Heights): " << maxWaterArea_Optimal(increasingHeights) << endl; // Expected 9

    // Example with decreasing heights
    vector<int> decreasingHeights = {6, 5, 4, 3, 2, 1};
    cout << "\nHeights: ";
    for(int h : decreasingHeights){
        cout << h << " ";
    }
    cout << endl;
    cout << "Max Area (Optimal - Decreasing Heights): " << maxWaterArea_Optimal(decreasingHeights) << endl; // Expected 9

    // Example with empty vector
    vector<int> emptyHeights = {};
    cout << "\nHeights: ";
    for(int h : emptyHeights){
        cout << h << " ";
    }
    cout << endl;
    cout << "Max Area (Optimal - Empty Heights): " << maxWaterArea_Optimal(emptyHeights) << endl; // Expected 0

    // Example with single element
    vector<int> singleHeight = {10};
    cout << "\nHeights: ";
    for(int h : singleHeight){
        cout << h << " ";
    }
    cout << endl;
    cout << "Max Area (Optimal - Single Height): " << maxWaterArea_Optimal(singleHeight) << endl; // Expected 0

    return 0;
}

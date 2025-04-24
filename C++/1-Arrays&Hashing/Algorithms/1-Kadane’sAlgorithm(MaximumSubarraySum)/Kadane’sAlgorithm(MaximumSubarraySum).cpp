#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MIN

using namespace std;

// 1. Kadane's Algorithm (Standard) - Most efficient and common
// This approach iterates through the array, keeping track of the maximum subarray sum ending at each position.
// It updates the global maximum sum whenever a larger sum is found.
int kadaneStandard(const vector<int>& nums) {
    int maxSoFar = INT_MIN;  // Initialize the maximum sum found so far to the smallest possible integer.
    int maxEndingHere = 0;    // Initialize the maximum sum ending at the current position.

    for (int num : nums) {
        maxEndingHere = max(num, maxEndingHere + num); // Decide to either start a new subarray from the current element, or extend the previous subarray.
        maxSoFar = max(maxSoFar, maxEndingHere);       // Update the global maximum sum if the current subarray sum is greater.
    }
    return maxSoFar; // Return the maximum subarray sum.
}

// 2. Kadane's Algorithm with Start and End Indices -  Finds the subarray range
// This version keeps track of the start and end indices of the maximum subarray.
// This is useful if you need to know *which* subarray has the maximum sum, not just the sum itself.
pair<int, pair<int, int>> kadaneWithIndices(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int start = 0;
    int end = 0;
    int currentStart = 0; // Keep track of the start of the current subarray.

    for (int i = 0; i < nums.size(); ++i) {
        int num = nums[i];
        if (num > maxEndingHere + num) { // Start a new subarray if the current element is greater than the current sum + the new element
            maxEndingHere = num;
            currentStart = i; // Update the start index of the current subarray.
        } else {
            maxEndingHere = maxEndingHere + num; // Extend the current subarray
        }

        if (maxEndingHere > maxSoFar) { // Update maxSoFar and the start/end indices.
            maxSoFar = maxEndingHere;
            start = currentStart;
            end = i;
        }
    }
    return {maxSoFar, {start, end}}; // Return the maximum sum and the start/end indices as a pair.
}

// 3. Kadane's Algorithm with Negative Number Handling - Handles all negative arrays
//  This version explicitly handles the case where the array contains all negative numbers.
//  In that case, the function returns the largest negative number.
int kadaneHandleNegative(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    bool allNegative = true; // Flag to check if all numbers are negative.

    for (int num : nums) {
        if (num > 0) {
            allNegative = false; // If we find a positive number, set the flag to false.
        }
        maxEndingHere = max(num, maxEndingHere + num);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    if (allNegative) {
        // If all numbers are negative, find the largest negative number.
        for (int num : nums) {
            maxSoFar = max(maxSoFar, num);
        }
    }
    return maxSoFar;
}

// 4. Kadane's Algorithm (Verbose) - Demonstrates the algorithm's steps with cout
// This version prints out the intermediate values of maxEndingHere and maxSoFar at each step.
// This can be helpful for understanding how the algorithm works.  Not suitable for production.
int kadaneVerbose(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;

    cout << "Kadane's Algorithm (Verbose):\n";
    for (int i = 0; i < nums.size(); ++i) {
        int num = nums[i];
        cout << "Current Number: " << num << "\n";
        maxEndingHere = max(num, maxEndingHere + num);
        cout << "Max Ending Here: " << maxEndingHere << "\n";
        maxSoFar = max(maxSoFar, maxEndingHere);
        cout << "Max So Far: " << maxSoFar << "\n";
        cout << "--------------------\n";
    }
    return maxSoFar;
}

// 5. Kadane's Algorithm using a function pointer
// This approach uses a function pointer to Kadane's algorithm.
// While it doesn't offer a different algorithmic approach, it demonstrates how to use function pointers in C++.
int kadaneFunctionPointer(const vector<int>& nums, int (*kadaneFunc)(const vector<int>&)) {
    return kadaneFunc(nums);
}

int main() {
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<int> nums2 = {1};
    vector<int> nums3 = {-2, -3, -4, -5};
    vector<int> nums4 = {5, 4, -1, 7, 8};
    vector<int> nums5 = {-10, -5, 0, 5, 10};

    cout << "Test Case 1: {-2, 1, -3, 4, -1, 2, 1, -5, 4}\n";
    cout << "Standard Kadane's: " << kadaneStandard(nums1) << endl;
    pair<int, pair<int, int>> result1 = kadaneWithIndices(nums1);
    cout << "Kadane's with Indices: Max Sum = " << result1.first << ", Start = " << result1.second.first << ", End = " << result1.second.second << endl;
    cout << "Kadane's with Negative Handling: " << kadaneHandleNegative(nums1) << endl;
    cout << "Kadane's Verbose: " << kadaneVerbose(nums1) << endl;
    int (*kadanePtr)(const vector<int>&) = kadaneStandard; // Function pointer to kadaneStandard
    cout << "Kadane's with Function Pointer: " << kadaneFunctionPointer(nums1, kadanePtr) << endl;

    cout << "\nTest Case 2: {1}\n";
    cout << "Standard Kadane's: " << kadaneStandard(nums2) << endl;
    pair<int, pair<int, int>> result2 = kadaneWithIndices(nums2);
    cout << "Kadane's with Indices: Max Sum = " << result2.first << ", Start = " << result2.second.first << ", End = " << result2.second.second << endl;
    cout << "Kadane's with Negative Handling: " << kadaneHandleNegative(nums2) << endl;
    cout << "Kadane's Verbose: " << kadaneVerbose(nums2) << endl;
    cout << "Kadane's with Function Pointer: " << kadaneFunctionPointer(nums2, kadanePtr) << endl;

    cout << "\nTest Case 3: {-2, -3, -4, -5}\n";
    cout << "Standard Kadane's: " << kadaneStandard(nums3) << endl;
    pair<int, pair<int, int>> result3 = kadaneWithIndices(nums3);
    cout << "Kadane's with Indices: Max Sum = " << result3.first << ", Start = " << result3.second.first << ", End = " << result3.second.second << endl;
    cout << "Kadane's with Negative Handling: " << kadaneHandleNegative(nums3) << endl;
    cout << "Kadane's Verbose: " << kadaneVerbose(nums3) << endl;
    cout << "Kadane's with Function Pointer: " << kadaneFunctionPointer(nums3, kadanePtr) << endl;

    cout << "\nTest Case 4: {5, 4, -1, 7, 8}\n";
    cout << "Standard Kadane's: " << kadaneStandard(nums4) << endl;
    pair<int, pair<int, int>> result4 = kadaneWithIndices(nums4);
    cout << "Kadane's with Indices: Max Sum = " << result4.first << ", Start = " << result4.second.first << ", End = " << result4.second.second << endl;
    cout << "Kadane's with Negative Handling: " << kadaneHandleNegative(nums4) << endl;
    cout << "Kadane's Verbose: " << kadaneVerbose(nums4) << endl;
    cout << "Kadane's with Function Pointer: " << kadaneFunctionPointer(nums4, kadanePtr) << endl;

    cout << "\nTest Case 5: {-10, -5, 0, 5, 10}\n";
    cout << "Standard Kadane's: " << kadaneStandard(nums5) << endl;
    pair<int, pair<int, int>> result5 = kadaneWithIndices(nums5);
    cout << "Kadane's with Indices: Max Sum = " << result5.first << ", Start = " << result5.second.first << ", End = " << result5.second.second << endl;
    cout << "Kadane's with Negative Handling: " << kadaneHandleNegative(nums5) << endl;
    cout << "Kadane's Verbose: " << kadaneVerbose(nums5) << endl;
    cout << "Kadane's with Function Pointer: " << kadaneFunctionPointer(nums5, kadanePtr) << endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm> // For std::lower_bound and std::upper_bound

using namespace std;

// Function to find the lower bound of a target value in a sorted array using binary search.
// The lower bound is the first element in the array that is not less than the target.
//
// Example:
// arr: [2, 3, 3, 5, 5, 5, 8, 9]
// target: 5
// lower_bound: 3 (index of the first 5)
int lowerBoundBinarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size(); // Corrected: right should be arr.size() for this implementation
    int result = -1; // Initialize result to -1, indicating target not found

    while (left < right) { // Changed condition to left < right
        int mid = left + (right - left) / 2; // Prevent potential overflow
        if (arr[mid] == target) {
            result = mid;      // Found a match, try to find an earlier one
            right = mid;         // Shrink the right boundary, crucial for finding *first* occurrence
        } else if (arr[mid] < target) {
            left = mid + 1;     // Target is in the right half
        } else {
            right = mid;        // Target is in the left half
        }
    }
    return result;
}

// Function to find the upper bound of a target value in a sorted array using binary search.
// The upper bound is the first element in the array that is greater than the target.
//
// Example:
// arr: [2, 3, 3, 5, 5, 5, 8, 9]
// target: 5
// upper_bound: 6 (index of the 8)
int upperBoundBinarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size(); // Corrected: right should be arr.size()
    int result = -1;

    while (left < right) { // Changed condition to left < right
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;    // Move left to search for a *later* occurrence
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return result;
}

// Function to find the lower bound using a slightly different approach.
int lowerBoundBinarySearchAlt(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Key difference: Search left for lower bound
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Function to find the upper bound using a slightly different approach.
int upperBoundBinarySearchAlt(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Key difference: Search right for upper bound
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    vector<int> arr = {2, 3, 3, 5, 5, 5, 8, 9};
    int target = 5;

    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Target: " << target << endl;

    // Using the first versions of lowerBound and upperBound
    int lowerBound1 = lowerBoundBinarySearch(arr, target);
    int upperBound1 = upperBoundBinarySearch(arr, target);
    cout << "Lower Bound (Version 1): " << lowerBound1 << endl;
    cout << "Upper Bound (Version 1): " << upperBound1 << endl;

     // Using the second versions of lowerBound and upperBound
    int lowerBound2 = lowerBoundBinarySearchAlt(arr, target);
    int upperBound2 = upperBoundBinarySearchAlt(arr, target);
    cout << "Lower Bound (Version 2): " << lowerBound2 << endl;
    cout << "Upper Bound (Version 2): " << upperBound2 << endl;

    // Using the STL's built-in functions for comparison
    auto lower = lower_bound(arr.begin(), arr.end(), target);
    auto upper = upper_bound(arr.begin(), arr.end(), target);

    cout << "Lower Bound (STL): " << (lower != arr.end() ? (int)(lower - arr.begin()) : -1) << endl;
    cout << "Upper Bound (STL): " << (upper != arr.end() ? (int)(upper - arr.begin()) : -1) << endl;

    return 0;
}

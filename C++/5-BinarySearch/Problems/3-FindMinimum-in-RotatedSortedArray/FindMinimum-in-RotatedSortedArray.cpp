#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to find the minimum element in a rotated sorted array.

// Approach 1: Linear Search
// - Iterate through the entire array and keep track of the minimum element.
// - Time Complexity: O(n), where n is the size of the array.
// - Space Complexity: O(1).
int findMin_linearSearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle empty array case.  Consider throwing an exception instead.
    }
    int minElement = nums[0]; // Initialize with the first element.
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < minElement) {
            minElement = nums[i]; // Update minElement if a smaller element is found.
        }
    }
    return minElement;
}

// Approach 2: Using STL's min_element (Similar to linear search, but uses library function)
// - Utilize the std::min_element function from the C++ Standard Template Library (STL).
// - This function iterates through the range and returns an iterator to the smallest element.
// - Time Complexity: O(n), where n is the size of the array.
// - Space Complexity: O(1).
int findMin_stl(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle empty array
    }
    auto minIt = min_element(nums.begin(), nums.end()); // Get iterator to min
    return *minIt; // Dereference the iterator to get the value.
}

// Approach 3: Binary Search (Optimized for Rotated Sorted Array)
// - Apply binary search, but with a modification to handle the rotation.
// - The key idea is to check which half of the array is sorted.
// - If the left half is sorted, the minimum element is either the first element
//   or in the unsorted right half.
// - If the right half is sorted, the minimum element is in the unsorted left half.
// - Time Complexity: O(log n), where n is the size of the array.
// - Space Complexity: O(1).
int findMin_binarySearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle empty array
    }
    int left = 0;
    int right = nums.size() - 1;

    // If the array is not rotated, the first element is the minimum.
    if (nums[left] <= nums[right]) {
        return nums[left];
    }

    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow

        // Check if mid is the minimum element
        if (mid > 0 && nums[mid] < nums[mid - 1]) {
            return nums[mid];
        }
        // Check if mid+1 is the minimum element
        if (mid < nums.size() - 1 && nums[mid + 1] < nums[mid]) {
            return nums[mid + 1];
        }

        // Determine which half is unsorted
        if (nums[left] <= nums[mid]) { // Left half is sorted
            left = mid + 1;       // Minimum is in the right half
        } else {                   // Right half is sorted
            right = mid - 1;      // Minimum is in the left half
        }
    }
    return -1; // Should not reach here, but added for completeness.
}

// Approach 4: Recursive Binary Search
// - Implement the binary search approach recursively.
// - This approach mirrors the iterative binary search but uses function calls
//   to divide the search space.
// - Time Complexity: O(log n)
// - Space Complexity: O(log n) due to the recursive call stack.
int findMin_recursiveBinarySearchHelper(const vector<int>& nums, int left, int right) {
    // Base cases:
    if (left > right) {
        return -1; // Not found (shouldn't happen in a rotated sorted array)
    }
    if (left == right) {
        return nums[left];
    }
     if (nums[left] <= nums[right]) {
        return nums[left];
    }

    int mid = left + (right - left) / 2;

      if (mid > 0 && nums[mid] < nums[mid - 1]) {
            return nums[mid];
        }
        if (mid < nums.size() - 1 && nums[mid + 1] < nums[mid]) {
            return nums[mid + 1];
        }


    if (nums[left] <= nums[mid]) {
        return findMin_recursiveBinarySearchHelper(nums, mid + 1, right);
    } else {
        return findMin_recursiveBinarySearchHelper(nums, left, mid - 1);
    }
}

int findMin_recursiveBinarySearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1;
    }
    return findMin_recursiveBinarySearchHelper(nums, 0, nums.size() - 1);
}

// Approach 5: Using lower_bound (C++ STL)
// -  The std::lower_bound function finds the first element not less than a value.
// -  In a rotated sorted array, applying lower_bound to the entire array
//    gives an iterator to the minimum element.
// - Time Complexity: O(log n) in general, but O(n) in the worst case for some implementations.
// - Space Complexity: O(1)
int findMin_lowerBound(const vector<int>& nums) {
     if (nums.empty()) {
        return -1;
    }
    auto min_iter = std::lower_bound(nums.begin(), nums.end(), nums[0],
                                     [](int a, int b) { return a > b; });
    return *min_iter;
}
int main() {
    // Example test cases
    vector<int> nums1 = {3, 4, 5, 1, 2};
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    vector<int> nums3 = {10, 1, 2, 3, 4, 5, 6};
    vector<int> nums4 = {11, 13, 15, 17}; // Not rotated
    vector<int> nums5 = {1};  // Single element
    vector<int> nums6 = {}; // Empty vector

    cout << "Test Case 1: [3, 4, 5, 1, 2]" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums1) << endl;
    cout << "STL min_element: " << findMin_stl(nums1) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums1) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums1) << endl;
    cout << "Lower Bound: " << findMin_lowerBound(nums1) << endl;

    cout << "\nTest Case 2: [4, 5, 6, 7, 0, 1, 2]" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums2) << endl;
    cout << "STL min_element: " << findMin_stl(nums2) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums2) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums2) << endl;
     cout << "Lower Bound: " << findMin_lowerBound(nums2) << endl;

    cout << "\nTest Case 3: [10, 1, 2, 3, 4, 5, 6]" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums3) << endl;
    cout << "STL min_element: " << findMin_stl(nums3) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums3) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums3) << endl;
    cout << "Lower Bound: " << findMin_lowerBound(nums3) << endl;

    cout << "\nTest Case 4: [11, 13, 15, 17] (Not Rotated)" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums4) << endl;
    cout << "STL min_element: " << findMin_stl(nums4) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums4) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums4) << endl;
    cout << "Lower Bound: " << findMin_lowerBound(nums4) << endl;

    cout << "\nTest Case 5: [1] (Single Element)" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums5) << endl;
    cout << "STL min_element: " << findMin_stl(nums5) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums5) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums5) << endl;
    cout << "Lower Bound: " << findMin_lowerBound(nums5) << endl;

    cout << "\nTest Case 6: [] (Empty Vector)" << endl;
    cout << "Linear Search: " << findMin_linearSearch(nums6) << endl;
    cout << "STL min_element: " << findMin_stl(nums6) << endl;
    cout << "Binary Search: " << findMin_binarySearch(nums6) << endl;
    cout << "Recursive Binary Search: " << findMin_recursiveBinarySearch(nums6) << endl;
    cout << "Lower Bound: " << findMin_lowerBound(nums6) << endl;

    return 0;
}

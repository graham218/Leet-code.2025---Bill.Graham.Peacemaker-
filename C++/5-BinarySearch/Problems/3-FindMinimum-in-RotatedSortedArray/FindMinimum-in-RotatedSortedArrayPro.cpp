#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to find the minimum element in a rotated sorted array.

// Approach 1: Linear Search
// Description:  This is the most basic approach. Iterate through the entire array
//               and keep track of the smallest element encountered.
//               While simple, it's not the most efficient, especially for large arrays.
// Time Complexity: O(n) - where n is the number of elements in the array.
// Space Complexity: O(1) - constant extra space.
int findMin_LinearSearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle the edge case of an empty array.  Returning -1 to indicate an error.  Could also throw an exception.
    }

    int minElement = nums[0]; // Initialize with the first element.
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < minElement) {
            minElement = nums[i]; // Update minElement if a smaller element is found.
        }
    }
    return minElement;
}

// Approach 2: Using STL's min_element
// Description:  This approach leverages the C++ Standard Template Library (STL)
//               function `min_element`.  It provides a concise way to find the minimum
//               element in a range.
// Time Complexity: O(n) -  `min_element` performs a linear search.
// Space Complexity: O(1) - constant extra space.
int findMin_STL(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle empty array
    }
    return *min_element(nums.begin(), nums.end());
}

// Approach 3: Binary Search (Optimized)
// Description:  This is the most efficient approach.  It utilizes the property
//               of the rotated sorted array: it's sorted in two parts.  We can
//               use binary search to find the point where the rotation occurs,
//               which is where the minimum element resides.
// Time Complexity: O(log n) -  Binary search reduces the search space by half at each step.
// Space Complexity: O(1) -  Constant extra space.
int findMin_BinarySearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1; // Handle empty array
    }

    int left = 0;
    int right = nums.size() - 1;

    // If the array is not rotated, the first element is the minimum.
    if (nums[left] <= nums[right]) {
        return nums[left];
    }

    while (left < right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow.

        if (nums[mid] > nums[right]) {
            // The minimum element is in the right half.
            left = mid + 1;
        } else {
            // The minimum element is in the left half (including mid).
            right = mid;
        }
    }
    // 'left' and 'right' converge to the minimum element.
    return nums[left];
}

// Approach 4: Recursive Binary Search
// Description: A recursive implementation of the binary search approach.
//              This approach provides an alternative way to implement
//              the divide-and-conquer strategy of binary search.
// Time Complexity: O(log n)
// Space Complexity: O(log n) - Due to the recursive call stack.
int findMin_RecursiveBinarySearchHelper(const vector<int>& nums, int left, int right) {
    if (left >= right) {
        return nums[left];
    }

    int mid = left + (right - left) / 2;

     if (nums[left] <= nums[right]) { // added this condition
        return nums[left];
    }

    if (nums[mid] > nums[right]) {
        return findMin_RecursiveBinarySearchHelper(nums, mid + 1, right);
    } else {
        return findMin_RecursiveBinarySearchHelper(nums, left, mid);
    }
}

int findMin_RecursiveBinarySearch(const vector<int>& nums) {
    if (nums.empty()) {
        return -1;
    }
    return findMin_RecursiveBinarySearchHelper(nums, 0, nums.size() - 1);
}

// Approach 5:  Binary Search with Duplicate Handling
// Description: This approach handles the case where the rotated sorted array
//              contains duplicate elements.  Duplicates can make it harder to
//              determine which half of the array contains the minimum element.
// Time Complexity: O(log n) in the average case, but O(n) in the worst case
//                  (when there are many duplicate elements).
// Space Complexity: O(1)
int findMin_BinarySearchDuplicates(const vector<int>& nums) {
    if (nums.empty()) {
        return -1;
    }

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            // Handle the case where nums[mid] == nums[right].
            // We can't be sure which side the minimum is on, so we
            // reduce the search space by one.
            right--;
        }
    }
    return nums[left];
}

int main() {
    // Example usage of the different approaches.
    vector<int> rotatedArray1 = {4, 5, 6, 7, 0, 1, 2};
    vector<int> rotatedArray2 = {3, 4, 5, 1, 2};
    vector<int> rotatedArray3 = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> rotatedArray4 = {2, 2, 2, 0, 1}; // Example with duplicates
    vector<int> rotatedArray5 = {1, 1, 0, 1, 1, 1};
    vector<int> emptyArray = {};

    cout << "Rotated Array 1: ";
    for (int num : rotatedArray1) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(rotatedArray1) << endl;
    cout << "STL's min_element: " << findMin_STL(rotatedArray1) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(rotatedArray1) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(rotatedArray1) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(rotatedArray1) << endl;

    cout << "\nRotated Array 2: ";
     for (int num : rotatedArray2) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(rotatedArray2) << endl;
    cout << "STL's min_element: " << findMin_STL(rotatedArray2) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(rotatedArray2) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(rotatedArray2) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(rotatedArray2) << endl;

    cout << "\nRotated Array 3: ";
    for (int num : rotatedArray3) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(rotatedArray3) << endl;
    cout << "STL's min_element: " << findMin_STL(rotatedArray3) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(rotatedArray3) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(rotatedArray3) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(rotatedArray3) << endl;

    cout << "\nRotated Array 4 (with duplicates): ";
    for (int num : rotatedArray4) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(rotatedArray4) << endl;
    cout << "STL's min_element: " << findMin_STL(rotatedArray4) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(rotatedArray4) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(rotatedArray4) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(rotatedArray4) << endl;

    cout << "\nRotated Array 5 (with duplicates): ";
    for (int num : rotatedArray5) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(rotatedArray5) << endl;
    cout << "STL's min_element: " << findMin_STL(rotatedArray5) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(rotatedArray5) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(rotatedArray5) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(rotatedArray5) << endl;

    cout << "\nEmpty Array: ";
    for (int num : emptyArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Linear Search: " << findMin_LinearSearch(emptyArray) << endl;
    cout << "STL's min_element: " << findMin_STL(emptyArray) << endl;
    cout << "Binary Search: " << findMin_BinarySearch(emptyArray) << endl;
    cout << "Recursive Binary Search: " << findMin_RecursiveBinarySearch(emptyArray) << endl;
    cout << "Binary Search with Duplicates: " << findMin_BinarySearchDuplicates(emptyArray) << endl;

    return 0;
}

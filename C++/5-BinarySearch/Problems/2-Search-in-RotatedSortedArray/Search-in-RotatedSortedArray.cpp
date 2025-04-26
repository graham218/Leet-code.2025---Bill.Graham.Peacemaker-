#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to print the array (for debugging purposes)
void printArray(const vector<int>& arr) {
    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Approach 1: Linear Search (Brute Force)
// - Iterate through the entire array and check if the target element is present.
// - Time Complexity: O(n), where n is the size of the array.
// - Space Complexity: O(1).
int searchRotatedArray_LinearSearch(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) {
            return i;
        }
    }
    return -1;
}

// Approach 2: Using STL's find (Similar to Linear Search)
// - Utilize the std::find function from the C++ Standard Template Library.
// - This approach is essentially a more concise version of linear search.
// - Time Complexity: O(n) in the worst case.
// - Space Complexity: O(1).
int searchRotatedArray_STLFind(const vector<int>& nums, int target) {
    auto it = find(nums.begin(), nums.end(), target);
    if (it != nums.end()) {
        return distance(nums.begin(), it); // Returns the index
    }
    return -1;
}


// Approach 3:  Binary Search with Extra Logic
// - Find the pivot (the index of the smallest element) using binary search.
// - Perform binary search in the sorted part of the array.
// - Time Complexity: O(log n)
// - Space Complexity: O(1)
int searchRotatedArray_BinarySearch(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent overflow
        if (nums[mid] == target)
            return mid;

        if (nums[low] <= nums[mid]) { // Left part is sorted
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right part is sorted
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// Approach 4: Optimized Binary Search (Most Efficient)
// - Combines finding the pivot and searching into a single binary search.
// - Avoids the extra step of explicitly finding the pivot.
// - Time Complexity: O(log n)
// - Space Complexity: O(1)
int searchRotatedArray_OptimizedBinarySearch(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) { // Left half is sorted
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// Approach 5: Using min_element and Binary Search
// 1. Find the index of the minimum element using min_element. This is the pivot point.
// 2. Perform a binary search in the appropriate sorted half based on the target value.
// - Time Complexity: O(n) for finding min element, O(log n) for binary search.  Overall: O(n)
// - Space Complexity: O(1)
int searchRotatedArray_MinElementBinarySearch(const vector<int>& nums, int target) {
     if (nums.empty()) return -1;

    // Find the index of the minimum element (pivot)
    int minIndex = min_element(nums.begin(), nums.end()) - nums.begin();

    int left, right;
    if (target >= nums[minIndex] && target <= nums.back()) {
        // Target is in the right sorted part
        left = minIndex;
        right = nums.size() - 1;
    } else {
        // Target is in the left sorted part
        left = 0;
        right = minIndex - 1;
    }

    // Standard binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    // Example usage
    vector<int> rotatedArray = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    cout << "Rotated Sorted Array: ";
    for (int num : rotatedArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Target: " << target << endl;

    cout << "\nApproach 1: Linear Search" << endl;
    int index1 = searchRotatedArray_LinearSearch(rotatedArray, target);
    cout << "Index: " << index1 << endl;

    cout << "\nApproach 2: Using STL's find" << endl;
    int index2 = searchRotatedArray_STLFind(rotatedArray, target);
    cout << "Index: " << index2 << endl;

    cout << "\nApproach 3: Binary Search" << endl;
    int index3 = searchRotatedArray_BinarySearch(rotatedArray, target);
    cout << "Index: " << index3 << endl;

    cout << "\nApproach 4: Optimized Binary Search" << endl;
    int index4 = searchRotatedArray_OptimizedBinarySearch(rotatedArray, target);
    cout << "Index: " << index4 << endl;

    cout << "\nApproach 5: Using min_element and Binary Search" << endl;
    int index5 = searchRotatedArray_MinElementBinarySearch(rotatedArray, target);
    cout << "Index: " << index5 << endl;

    return 0;
}

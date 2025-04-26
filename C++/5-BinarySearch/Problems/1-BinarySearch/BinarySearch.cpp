#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Binary Search - Iterative Approach 1
// Uses a standard iterative approach with integer mid calculation.
int binarySearchIterative1(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow
        if (arr[mid] == target) {
            return mid; // Target found, return the index
        } else if (arr[mid] < target) {
            left = mid + 1; // Target is in the right half
        } else {
            right = mid - 1; // Target is in the left half
        }
    }
    return -1; // Target not found
}

// Binary Search - Iterative Approach 2
// Similar to the first iterative approach, but with a slight variation in the loop condition.
int binarySearchIterative2(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) { // Loop continues as long as there are at least two elements to check
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid; // Important: right is set to mid, not mid-1
        }
    }
    // After the loop, left == right, and it's the potential target
    if (arr[left] == target) {
        return left;
    }
    return -1;
}


// Binary Search - Recursive Approach 1
// A straightforward recursive implementation.
int binarySearchRecursive1Helper(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1; // Base case: target not found
    }
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive1Helper(arr, target, mid + 1, right); // Recursive call on right half
    } else {
        return binarySearchRecursive1Helper(arr, target, left, mid - 1); // Recursive call on left half
    }
}

int binarySearchRecursive1(const std::vector<int>& arr, int target) {
    return binarySearchRecursive1Helper(arr, target, 0, arr.size() - 1);
}

// Binary Search - Recursive Approach 2
// Tail-recursive version (often optimized by compilers).  Less common, but good to know.
int binarySearchRecursive2Helper(const std::vector<int>& arr, int target, int left, int right, int& result) {
    if (left > right) {
        return -1; // Base case: target not found.  Return value doesn't matter here, result is used.
    }
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
        result = mid; // Store the result
        return mid; // early return
    } else if (arr[mid] < target) {
        return binarySearchRecursive2Helper(arr, target, mid + 1, right, result);
    } else {
        return binarySearchRecursive2Helper(arr, target, left, mid - 1, result);
    }
}

int binarySearchRecursive2(const std::vector<int>& arr, int target) {
    int result = -1;
    binarySearchRecursive2Helper(arr, target, 0, arr.size() - 1, result);
    return result;
}

// Binary Search - Using STL (std::lower_bound)
// Demonstrates using the C++ Standard Template Library's lower_bound function
// which performs a binary search.  Returns an iterator.
int binarySearchSTL(const std::vector<int>& arr, int target) {
    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end() && *it == target) {
        return std::distance(arr.begin(), it); // Calculate the index
    }
    return -1;
}

int main() {
    std::vector<int> sortedArray = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int targetValue = 23;

    std::cout << "Array: ";
    for (int num : sortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Target: " << targetValue << std::endl;

    // Test each binary search implementation
    int index1 = binarySearchIterative1(sortedArray, targetValue);
    std::cout << "Iterative 1: Index of " << targetValue << " is " << index1 << std::endl;

    int index2 = binarySearchIterative2(sortedArray, targetValue);
    std::cout << "Iterative 2: Index of " << targetValue << " is " << index2 << std::endl;

    int index3 = binarySearchRecursive1(sortedArray, targetValue);
    std::cout << "Recursive 1: Index of " << targetValue << " is " << index3 << std::endl;

    int index4 = binarySearchRecursive2(sortedArray, targetValue);
    std::cout << "Recursive 2: Index of " << targetValue << " is " << index4 << std::endl;

    int index5 = binarySearchSTL(sortedArray, targetValue);
    std::cout << "STL: Index of " << targetValue << " is " << index5 << std::endl;

    // Test case where the target is not in the array
    targetValue = 100;
    std::cout << "\nTarget: " << targetValue << std::endl;
    index1 = binarySearchIterative1(sortedArray, targetValue);
    std::cout << "Iterative 1: Index of " << targetValue << " is " << index1 << std::endl;

    index2 = binarySearchIterative2(sortedArray, targetValue);
    std::cout << "Iterative 2: Index of " << targetValue << " is " << index2 << std::endl;

    index3 = binarySearchRecursive1(sortedArray, targetValue);
    std::cout << "Recursive 1: Index of " << targetValue << " is " << index3 << std::endl;

    index4 = binarySearchRecursive2(sortedArray, targetValue);
    std::cout << "Recursive 2: Index of " << targetValue << " is " << index4 << std::endl;

    index5 = binarySearchSTL(sortedArray, targetValue);
    std::cout << "STL: Index of " << targetValue << " is " << index5 << std::endl;

    return 0;
}

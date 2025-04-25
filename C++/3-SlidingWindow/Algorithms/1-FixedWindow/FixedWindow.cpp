#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

// Function to solve the "Two Pointers - Fixed Window" problem using different approaches
// The problem: Given an array and a window size 'k', find something about the subarrays of size 'k'
// (e.g., max sum, min element, etc.).  This template provides that structure.

// Approach 1: Basic Sliding Window (Sum of Subarrays)
// Time Complexity: O(n), Space Complexity: O(1)
int findMaxSumSubarray_Basic(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return -1; // Handle invalid input
    }

    int max_sum = numeric_limits<int>::min();
    int current_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    max_sum = current_sum;

    // Slide the window through the rest of the array
    for (int i = k; i < arr.size(); ++i) {
        current_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}

// Approach 2: Sliding Window with Minimum Element Tracking
// Time Complexity: O(n), Space Complexity: O(1)
int findMinElementSubarray_MinTracking(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return -1; // Handle invalid input
    }

    int min_element = numeric_limits<int>::max();
    int current_min = numeric_limits<int>::max();

    // Calculate min of the first window
    for (int i = 0; i < k; ++i) {
        current_min = min(current_min, arr[i]);
    }
    min_element = current_min;

    for (int i = k; i < arr.size(); ++i) {
        // Efficiently update current_min:
        // 1. If the outgoing element was the current min, recalculate the min for the new window.
        // 2. Otherwise, the current min might still be valid, just compare with the new element.
        if (arr[i - k] == current_min) {
            current_min = numeric_limits<int>::max(); // Reset to find min in new window
            for (int j = i - k + 1; j <= i; ++j) {
                current_min = min(current_min, arr[j]);
            }
        } else {
            current_min = min(current_min, arr[i]);
        }
        min_element = min(min_element, current_min);
    }
    return min_element;
}


// Approach 3: Sliding Window with Average Calculation
// Time Complexity: O(n), Space Complexity: O(1)
double findMaxAverageSubarray(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return -1.0; // Handle invalid input
    }

    double max_average = numeric_limits<double>::lowest();
    double current_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    max_average = current_sum / k;

    // Slide the window
    for (int i = k; i < arr.size(); ++i) {
        current_sum += arr[i] - arr[i - k];
        max_average = max(max_average, current_sum / k);
    }

    return max_average;
}

// Approach 4: Sliding Window with Product Calculation
// Time Complexity: O(n), Space Complexity: O(1)
long long findMaxProductSubarray(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return -1; // Handle invalid input
    }

    long long max_product = numeric_limits<long long>::min();
    long long current_product = 1;

    // Calculate the product of the first window
    for (int i = 0; i < k; ++i) {
        current_product *= arr[i];
    }
    max_product = current_product;

    // Slide the window
    for (int i = k; i < arr.size(); ++i) {
        current_product = (current_product / arr[i - k]) * arr[i];
        max_product = max(max_product, current_product);
    }
    return max_product;
}

// Approach 5: Check if all elements in the window are positive
// Time Complexity: O(n), Space Complexity: O(1)
bool isAllPositiveSubarray(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return false; // Handle invalid input
    }

    // Check the first window
    for (int i = 0; i < k; ++i) {
        if (arr[i] <= 0) {
            return false;
        }
    }

    // Slide the window
    for (int i = k; i < arr.size(); ++i) {
        if (arr[i] <= 0) {
            bool foundNonPositive = false;
            for (int j = i - k + 1; j < i; ++j) {
                if (arr[j] <= 0) {
                    foundNonPositive = true;
                    break;
                }
            }
            if (!foundNonPositive)
                return false;
        }
    }
    return true;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;

    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Window size (k): " << k << endl;

    // Example Usage of the functions
    cout << "Approach 1 - Max Sum of Subarray of size k: " << findMaxSumSubarray_Basic(arr, k) << endl;
    cout << "Approach 2 - Min Element of Subarray of size k: " << findMinElementSubarray_MinTracking(arr, k) << endl;
    cout << "Approach 3 - Max Average of Subarray of size k: " << findMaxAverageSubarray(arr, k) << endl;
    cout << "Approach 4 - Max Product of Subarray of size k: " << findMaxProductSubarray(arr, k) << endl;
    cout << "Approach 5 - All Positive Subarray of size k: " << (isAllPositiveSubarray(arr, k) ? "Yes" : "No") << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <climits> // For INT_MAX and INT_MIN

using namespace std;

// Function to solve the sliding window problem using a basic loop.
// This approach directly calculates the sum for each window.
//
// Time Complexity: O(n * k), where n is the size of the array and k is the window size.
// Space Complexity: O(1) - Constant extra space.
int slidingWindowBasicLoop(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return INT_MIN; // Handle invalid input: window size too big or non-positive
    }

    int max_sum = INT_MIN; // Initialize max_sum to the smallest possible integer
    for (int i = 0; i <= arr.size() - k; ++i) {
        int current_sum = 0;
        for (int j = 0; j < k; ++j) {
            current_sum += arr[i + j];
        }
        max_sum = max(max_sum, current_sum); // Update max_sum if needed
    }
    return max_sum;
}

// Function to solve the sliding window problem using a slightly optimized loop.
// This approach avoids redundant calculations by subtracting the leaving element
// and adding the entering element.  However, it's still O(n*k) in the worst case.
//
// Time Complexity: O(n * k), where n is the size of the array and k is the window size.
// Space Complexity: O(1)
int slidingWindowOptimizedLoop(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return INT_MIN;
    }

    int max_sum = INT_MIN;
    // Calculate the sum of the first window
    int current_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    max_sum = current_sum; // Initialize max_sum

    // Slide the window through the rest of the array
    for (int i = k; i < arr.size(); ++i) {
        current_sum = current_sum - arr[i - k] + arr[i]; // Subtract leaving, add entering
        max_sum = max(max_sum, current_sum);
    }
    return max_sum;
}

// Function to solve the sliding window problem using the std::accumulate function.
// This approach uses the accumulate function to efficiently calculate the sum of each window.
//
// Time Complexity: O(n * k), where n is the size of the array and k is the window size.  Although accumulate is often linear, it's called k times.
// Space Complexity: O(1)
int slidingWindowAccumulate(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return INT_MIN;
    }

    int max_sum = INT_MIN;
    for (int i = 0; i <= arr.size() - k; ++i) {
        int current_sum = accumulate(arr.begin() + i, arr.begin() + i + k, 0); // Use accumulate
        max_sum = max(max_sum, current_sum);
    }
    return max_sum;
}

// Function to solve the sliding window problem with optimal time complexity.
// This is the standard, efficient sliding window approach.
//
// Time Complexity: O(n), where n is the size of the array.
// Space Complexity: O(1)
int slidingWindowOptimal(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return INT_MIN;
    }

    int max_sum = INT_MIN;
    // Calculate the sum of the first window
    int current_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    max_sum = current_sum;

    // Slide the window
    for (int i = k; i < arr.size(); ++i) {
        current_sum -= arr[i - k]; // Subtract the element going out of the window
        current_sum += arr[i];     // Add the new element coming into the window
        max_sum = max(max_sum, current_sum); // Update the maximum sum
    }
    return max_sum;
}

// Function to solve the sliding window problem using a lambda function.
// This approach encapsulates the window sum calculation within a lambda,
// offering a more functional style.
//
// Time Complexity: O(n * k), where n is the size of the array and k is the window size.
// Space Complexity: O(1)
int slidingWindowLambda(const vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return INT_MIN;
    }

    int max_sum = INT_MIN;
    // Define a lambda function to calculate the sum of a window
    auto window_sum = [&](int start_index) {
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += arr[start_index + i];
        }
        return sum;
    };

    for (int i = 0; i <= arr.size() - k; ++i) {
        max_sum = max(max_sum, window_sum(i)); // Use the lambda
    }
    return max_sum;
}

int main() {
    // Example usage of the sliding window functions
    vector<int> arr = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k = 4;

    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Window size: " << k << endl << endl;

    // Call each of the sliding window functions and print the results
    cout << "Maximum sum of a subarray of size " << k << " is:" << endl;
    cout << "Basic Loop: " << slidingWindowBasicLoop(arr, k) << endl;
    cout << "Optimized Loop: " << slidingWindowOptimizedLoop(arr, k) << endl;
    cout << "Accumulate: " << slidingWindowAccumulate(arr, k) << endl;
    cout << "Optimal: " << slidingWindowOptimal(arr, k) << endl;
    cout << "Lambda: " << slidingWindowLambda(arr, k) << endl;

    return 0;
}

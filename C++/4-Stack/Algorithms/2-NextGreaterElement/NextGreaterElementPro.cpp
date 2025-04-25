#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// 1. Brute Force Approach
//   - Conceptually simple, good for understanding the problem.
//   - In a real-world scenario, this could be used for a small, non-performance-critical utility within a larger system.  For example, calculating next higher price in a very limited dataset.
//   - Time Complexity: O(n^2)
//   - Space Complexity: O(n) - for the result vector
vector<int> nextGreaterElement_BruteForce(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1); // Initialize result with -1

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[i]) {
                result[i] = arr[j];
                break; // Found the next greater, no need to continue inner loop
            }
        }
        // If no greater element was found, result[i] remains -1
    }
    return result;
}

// 2. Stack Approach (Optimized)
//   - Efficient solution, widely used in competitive programming and technical interviews.
//   - Real-world application: Processing stock prices to find the next day with a higher price.  This is very common in financial applications.
//   - Time Complexity: O(n) - Each element is pushed and popped at most once.
//   - Space Complexity: O(n) - In the worst case, the stack might hold all elements.
vector<int> nextGreaterElement_Stack(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> s;

    for (int i = n - 1; i >= 0; --i) { // Iterate from right to left
        // Pop elements from the stack that are not greater than the current element
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }
        // If the stack is not empty, the top element is the next greater element
        if (!s.empty()) {
            result[i] = s.top();
        }
        s.push(arr[i]); // Push the current element onto the stack
    }
    return result;
}

// 3. Using a Circular Array (Stack Approach)
//   - Handles the case where the next greater element might be at the beginning of the array.
//   - Real-world application: Analyzing cyclical data, such as server performance metrics over a 24-hour period.  If you need to know the next time a server exceeds its current load, you would treat the data as circular.
//   - Time Complexity: O(n)
//   - Space Complexity: O(n)
vector<int> nextGreaterElement_Circular(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> s;

    for (int i = 2 * n - 1; i >= 0; --i) { // Iterate twice the array length to simulate circularity
        while (!s.empty() && s.top() <= arr[i % n]) {
            s.pop();
        }
        if (!s.empty()) {
            result[i % n] = s.top();
        }
        s.push(arr[i % n]);
    }
    return result;
}

// 4. Using Stack and Pair (for index tracking)
//   -  This approach not only finds the next greater element but also its index.
//   -  Real-world application:  In a system that tracks events or alerts, you might want to know *when* the next critical event occurred after a specific event.  This approach lets you find the next greater event and its timestamp (index).
//   - Time Complexity: O(n)
//   - Space Complexity: O(n)
vector<pair<int, int>> nextGreaterElement_WithIndex(const vector<int>& arr) {
    int n = arr.size();
    vector<pair<int, int>> result(n, {-1, -1}); // {value, index}, -1 for not found
    stack<pair<int, int>> s; // Store {element, index}

    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && s.top().first <= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            result[i] = {s.top().first, s.top().second};
        }
        s.push({arr[i], i});
    }
    return result;
}

// 5. Using Monotonic Stack with Custom Class
//   - Encapsulates the logic in a reusable class.
//   - Real-world application: Creating a reusable library or module for time-series analysis.  If you're building a system that frequently needs to find next greater values in various datasets, a class makes the code cleaner and easier to maintain.
//   - Time Complexity: O(n) per query
//   - Space Complexity: O(n)
class MonotonicStack {
private:
    stack<int> s;
    vector<int> data;

public:
    MonotonicStack(const vector<int>& arr) : data(arr) {}

    vector<int> getNextGreaterElements() {
        int n = data.size();
        vector<int> result(n, -1);
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && s.top() <= data[i]) {
                s.pop();
            }
            if (!s.empty()) {
                result[i] = s.top();
            }
            s.push(data[i]);
        }
        return result;
    }
};

int main() {
    vector<int> arr = {4, 5, 2, 25, 7, 8, 1, 15};
    int n = arr.size();

    cout << "Original Array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // 1. Brute Force
    vector<int> result1 = nextGreaterElement_BruteForce(arr);
    cout << "Next Greater Elements (Brute Force): ";
    for (int x : result1) {
        cout << x << " ";
    }
    cout << endl;

    // 2. Stack Approach
    vector<int> result2 = nextGreaterElement_Stack(arr);
    cout << "Next Greater Elements (Stack): ";
    for (int x : result2) {
        cout << x << " ";
    }
    cout << endl;

    // 3. Circular Array
    vector<int> result3 = nextGreaterElement_Circular(arr);
    cout << "Next Greater Elements (Circular): ";
    for (int x : result3) {
        cout << x << " ";
    }
    cout << endl;

     // 4. Stack with Index
    vector<pair<int, int>> result4 = nextGreaterElement_WithIndex(arr);
    cout << "Next Greater Elements with Indices: ";
    for (const auto& p : result4) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;

    // 5. Monotonic Stack Class
    MonotonicStack ms(arr);
    vector<int> result5 = ms.getNextGreaterElements();
    cout << "Next Greater Elements (Monotonic Stack Class): ";
    for (int x : result5) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

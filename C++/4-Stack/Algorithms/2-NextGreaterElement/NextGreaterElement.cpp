#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to print the elements of a vector
void printVector(const vector<int>& arr) {
    for (int element : arr) {
        cout << element << " ";
    }
    cout << endl;
}

// Approach 1: Brute Force
// For each element, iterate through the rest of the array to find the next greater element.
// - Time Complexity: O(n^2)
// - Space Complexity: O(1)
vector<int> nextGreaterElement_BruteForce(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        result[i] = -1; // Default value if no greater element is found
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[i]) {
                result[i] = arr[j];
                break; // Found the next greater element, no need to continue searching
            }
        }
    }
    return result;
}

// Approach 2: Stack
// Use a stack to keep track of elements for which we haven't found the next greater element yet.
// - Time Complexity: O(n)
// - Space Complexity: O(n) (worst case)
vector<int> nextGreaterElement_Stack(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> s;

    // Iterate from right to left
    for (int i = n - 1; i >= 0; --i) {
        // Pop elements from the stack that are not greater than the current element
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }

        // If the stack is empty, there is no greater element to the right
        if (s.empty()) {
            result[i] = -1;
        } else {
            // The top of the stack is the next greater element
            result[i] = s.top();
        }

        // Push the current element onto the stack
        s.push(arr[i]);
    }
    return result;
}

// Approach 3: Using a Stack (Iterating Forward)
// Similar to approach 2, but iterates forward and stores indices in the stack.
// - Time Complexity: O(n)
// - Space Complexity: O(n)
vector<int> nextGreaterElement_StackForward(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1); // Initialize result vector with -1
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        // While the stack is not empty and the current element is greater than the element at the top of the stack
        while (!s.empty() && arr[i] > arr[s.top()]) {
            // The current element is the next greater element for the element at the top of the stack
            result[s.top()] = arr[i];
            s.pop(); // Remove the index from the stack
        }
        s.push(i); // Push the index of the current element onto the stack
    }
    return result;
}

// Approach 4:  Circular Array, Stack Solution
// Handles the case where the array is circular (the next greater element can be on the left).
// - Time Complexity: O(n)
// - Space Complexity: O(n)
vector<int> nextGreaterElement_Circular(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> s;

    for (int i = 2 * n - 1; i >= 0; --i) {
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

// Approach 5: Using Monotonic Stack (Optimized)
// A slight optimization of the stack approach, making it more explicit.
vector<int> nextGreaterElement_MonotonicStack(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> stack;

    for (int i = 0; i < n; i++) {
        while (!stack.empty() && arr[i] > arr[stack.top()]) {
            result[stack.top()] = arr[i];
            stack.pop();
        }
        stack.push(i);
    }
    return result;
}

int main() {
    vector<int> arr = {1, 3, 2, 4};

    cout << "Original Array: ";
    printVector(arr);

    cout << "\nNext Greater Element (Brute Force): ";
    printVector(nextGreaterElement_BruteForce(arr));

    cout << "Next Greater Element (Stack): ";
    printVector(nextGreaterElement_Stack(arr));

    cout << "Next Greater Element (Stack Forward): ";
    printVector(nextGreaterElement_StackForward(arr));

    cout << "Next Greater Element (Circular Array): ";
    printVector(nextGreaterElement_Circular(arr));

    cout << "Next Greater Element (Monotonic Stack): ";
    printVector(nextGreaterElement_MonotonicStack(arr));

    return 0;
}

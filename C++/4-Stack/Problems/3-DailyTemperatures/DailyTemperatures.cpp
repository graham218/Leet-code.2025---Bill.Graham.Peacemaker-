#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits> // For INT_MAX

using namespace std;

// 1. Brute Force Approach
// - Iterate through each day.
// - For each day, iterate through the following days until a warmer day is found.
// - Time Complexity: O(n^2), Space Complexity: O(n) (for the result vector)
vector<int> dailyTemperaturesBruteForce(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0); // Initialize the result vector with 0s.  Good practice.

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i; // Store the number of days until a warmer temperature.
                break; // Once we find a warmer day, we can stop searching.
            }
        }
        // If no warmer day is found, result[i] remains 0.
    }
    return result;
}

// 2. Stack Approach
// - Use a stack to keep track of the indices of days with decreasing temperatures.
// - Iterate through the temperatures array.
// - For each day, while the stack is not empty and the current temperature is greater than the temperature at the top of the stack,
//   pop the stack and update the result for the popped index.
// - Push the current day's index onto the stack.
// - Time Complexity: O(n), Space Complexity: O(n) (for the stack and result vector)
vector<int> dailyTemperaturesStack(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> stack;

    for (int i = 0; i < n; ++i) {
        while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
            int prevIndex = stack.top();
            stack.pop();
            result[prevIndex] = i - prevIndex;
        }
        stack.push(i);
    }
    return result;
}

// 3. Optimized Stack Approach (Slightly more efficient)
// - Same logic as the previous stack approach, but with a minor optimization.
// - Avoids unnecessary checks within the inner while loop.
vector<int> dailyTemperaturesStackOptimized(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> stack;

    for (int i = 0; i < n; ++i) {
        while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
            result[stack.top()] = i - stack.top();
            stack.pop();
        }
        stack.push(i);
    }
    return result;
}

// 4. Using a Decreasing Stack (Similar to 2 and 3, but with more descriptive variable names)
vector<int> dailyTemperaturesDecreasingStack(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> decreasingStack;

    for (int i = 0; i < n; ++i) {
        while (!decreasingStack.empty() && temperatures[i] > temperatures[decreasingStack.top()]) {
            int previousIndex = decreasingStack.top();
            decreasingStack.pop();
            result[previousIndex] = i - previousIndex;
        }
        decreasingStack.push(i);
    }
    return result;
}

// 5.  Iterating Backwards with Next Warmer Index
// - Iterate through the temperatures array from right to left.
// - For each day, keep track of the index of the next warmer day.
// - Use the result vector itself to store the next warmer day's index.
// - If a warmer day is found, the distance is simply the difference between the indices.
// - This approach is still O(n), but can be slightly faster in practice due to better cache locality.
vector<int> dailyTemperaturesBackward(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);

    for (int i = n - 2; i >= 0; --i) { // Iterate from the second-to-last day to the first day.
        for (int j = i + 1; j < n; ) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i;
                break;
            } else if (result[j] == 0) { // If result[j] is 0, it means no warmer day after j
                result[i] = 0;
                break;
            } else {
                j += result[j]; // Jump to the next warmer day's index.
            }
        }
    }
    return result;
}

int main() {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    cout << "Temperatures: ";
    for (int temp : temperatures) {
        cout << temp << " ";
    }
    cout << endl;

    // Test each solution and print the results
    cout << "\nBrute Force Approach: ";
    vector<int> result1 = dailyTemperaturesBruteForce(temperatures);
    for (int day : result1) {
        cout << day << " ";
    }
    cout << endl;

    cout << "Stack Approach: ";
    vector<int> result2 = dailyTemperaturesStack(temperatures);
    for (int day : result2) {
        cout << day << " ";
    }
    cout << endl;

    cout << "Optimized Stack Approach: ";
    vector<int> result3 = dailyTemperaturesStackOptimized(temperatures);
    for (int day : result3) {
        cout << day << " ";
    }
    cout << endl;

    cout << "Decreasing Stack Approach: ";
    vector<int> result4 = dailyTemperaturesDecreasingStack(temperatures);
    for (int day : result4) {
        cout << day << " ";
    }
    cout << endl;

    cout << "Backward Iteration Approach: ";
    vector<int> result5 = dailyTemperaturesBackward(temperatures);
    for (int day : result5) {
        cout << day << " ";
    }
    cout << endl;

    return 0;
}

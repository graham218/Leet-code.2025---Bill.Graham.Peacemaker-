#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <climits> // For INT_MAX and INT_MIN
#include <numeric> // for std::accumulate

using namespace std;

// 1. Brute Force Approach
//   - For each day, iterate through the following days to find the first warmer day.
//   - Time Complexity: O(n^2), Space Complexity: O(n) for the result vector.
vector<int> dailyTemperatures_bruteForce(const vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i;
                break;
            }
        }
    }
    return result;
}

// 2. Stack Approach
//   - Use a stack to keep track of the indices of days with decreasing temperatures.
//   - When a warmer day is encountered, pop the days with lower temperatures from the stack.
//   - Time Complexity: O(n), Space Complexity: O(n) for the stack and result vector.
vector<int> dailyTemperatures_stack(const vector<int>& temperatures) {
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

// 3. Optimized Stack Approach (Slightly more concise)
//   - Similar to the previous stack approach, but combines some operations.
vector<int> dailyTemperatures_stackOptimized(const vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && temperatures[i] >= temperatures[s.top()]) {
            s.pop();
        }
        result[i] = s.empty() ? 0 : s.top() - i;
        s.push(i);
    }
    return result;
}

// 4. Using a Deque
//   - A deque can be used similarly to a stack in this problem.
//   - We maintain the deque in decreasing order of temperatures (from back to front).
vector<int> dailyTemperatures_deque(const vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    deque<int> dq;

    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && temperatures[i] > temperatures[dq.back()]) {
            int prevIndex = dq.back();
            dq.pop_back();
            result[prevIndex] = i - prevIndex;
        }
        dq.push_back(i);
    }
    return result;
}

// 5. Monotonic Stack with Early Stopping Optimization
//    - This approach uses a monotonic stack but adds an optimization to potentially
//    - reduce unnecessary iterations in some cases.
vector<int> dailyTemperatures_monotonicStackEarlyStop(const vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> stack;

    for (int i = 0; i < n; ++i) {
        while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
            int prevIndex = stack.top();
            stack.pop();
            result[prevIndex] = i - prevIndex;
        }
        // Optimization: If the current temperature is less than or equal to the temperature
        // at the top of the stack, and the difference between their indices is 1,
        // we can potentially skip some checks.  This is because we know the next warmer day
        // for stack.top() is i, and we might be able to avoid some comparisons later.
        if (!stack.empty() && temperatures[i] <= temperatures[stack.top()] && i - stack.top() == 1) {
             continue; // Skip to the next iteration
        }
        stack.push(i);
    }
    return result;
}

// Function to print the result
void printResult(const vector<int>& result) {
    cout << "Result: ";
    for (int day : result) {
        cout << day << " ";
    }
    cout << endl;
}

int main() {
    // Example input
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    cout << "Input Temperatures: ";
    for (int temp : temperatures) {
        cout << temp << " ";
    }
    cout << endl;

    // Test each approach and print the result
    cout << "\nBrute Force Approach:" << endl;
    vector<int> result1 = dailyTemperatures_bruteForce(temperatures);
    printResult(result1);

    cout << "\nStack Approach:" << endl;
    vector<int> result2 = dailyTemperatures_stack(temperatures);
    printResult(result2);

    cout << "\nOptimized Stack Approach:" << endl;
    vector<int> result3 = dailyTemperatures_stackOptimized(temperatures);
    printResult(result3);

    cout << "\nDeque Approach:" << endl;
    vector<int> result4 = dailyTemperatures_deque(temperatures);
    printResult(result4);

     cout << "\nMonotonic Stack with Early Stopping:" << endl;
    vector<int> result5 = dailyTemperatures_monotonicStackEarlyStop(temperatures);
    printResult(result5);

    return 0;
}

#include <iostream>
#include <stack>
#include <vector>
#include <climits> // For INT_MAX and INT_MIN
#include <algorithm> // For std::min

// Approach 1: Using a pair (value, min) in the stack
// This approach stores the current minimum value along with each element in the stack.
// It provides fast O(1) retrieval of the minimum element but uses more memory.
class MinStack1 {
private:
    std::stack<std::pair<int, int>> s; // Stack of pairs (value, currentMin)

public:
    MinStack1() {
        // Constructor is optional, but good practice to be explicit.
    }

    void push(int val) {
        if (s.empty()) {
            s.push({val, val}); // First element, min is itself.
        } else {
            int currentMin = s.top().second; // Get the current minimum.
            s.push({val, std::min(val, currentMin)}); // Store value and the minimum.
        }
    }

    void pop() {
        if (!s.empty()) {
            s.pop();
        }
    }

    int top() {
        if (!s.empty()) {
            return s.top().first; // Return the top value.
        }
        return -1; // Or throw an exception, depending on the desired behavior for an empty stack.
    }

    int getMin() {
        if (!s.empty()) {
            return s.top().second; // Return the stored minimum.
        }
        return INT_MAX; // Or throw an exception.  Returning INT_MAX is common for error indication.
    }
};

// Approach 2: Using two stacks (one for values, one for minimums)
// This approach uses one stack to store all values and another stack to store the minimum values encountered so far.
// It also provides O(1) retrieval of the minimum element, and uses a bit less memory than Approach 1 in some cases,
// but might use more memory in other cases (for example, when many duplicate minimum values are pushed).
class MinStack2 {
private:
    std::stack<int> s;       // Stack for values
    std::stack<int> minStack; // Stack for minimums

public:
    MinStack2() {
    }

    void push(int val) {
        s.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val); // Only push to minStack if it's a new minimum.
        }
    }

    void pop() {
        if (!s.empty()) {
            int popped = s.top();
            s.pop();
            if (!minStack.empty() && popped == minStack.top()) {
                minStack.pop(); // Important:  Pop from minStack *only* if it's the current minimum.
            }
        }
    }

    int top() {
        if (!s.empty()) {
            return s.top();
        }
        return -1;
    }

    int getMin() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        return INT_MAX;
    }
};

// Approach 3: Optimized two-stack approach (Slightly more space-efficient)
// This approach is a variation of Approach 2, optimizing the minStack.  It only pushes a new min
// if the new value is strictly less than the current min.  When popping, it checks if the popped
// value is equal to the top of the minStack, and pops from minStack if they are equal.
class MinStack3 {
private:
    std::stack<int> dataStack;
    std::stack<int> minStack;

public:
    MinStack3() {}

    void push(int val) {
        dataStack.push(val);
        if (minStack.empty() || val < minStack.top()) { // Important: Only push if strictly less.
            minStack.push(val);
        }
    }

    void pop() {
        if (!dataStack.empty()) {
            int poppedValue = dataStack.top();
            dataStack.pop();
            if (poppedValue == minStack.top()) { // Correctly handle the case where the min is popped.
                minStack.pop();
            }
        }
    }

    int top() {
        if (!dataStack.empty()) {
            return dataStack.top();
        }
        return -1;
    }

    int getMin() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        return INT_MAX;
    }
};

// Approach 4: Using a single stack and encoding the minimum
// This approach uses a single stack, but instead of storing pairs, it cleverly encodes
// the minimum value within the stack elements themselves.  This is the most space-efficient
// of the stack-based approaches, but the logic is more complex.
class MinStack4 {
private:
    std::stack<long long> s; // Use long long to avoid overflow issues

    long long minVal; // Store the current minimum value

public:
    MinStack4() : minVal(INT_MAX) {
        // Initialize minVal to the maximum possible integer value
    }

    void push(int val) {
        if (s.empty()) {
            minVal = val;
            s.push(val); // First element
        } else {
            // If the new value is less than the current minimum,
            // store the encoded value (2 * val - minVal) in the stack.
            if (val < minVal) {
                s.push(2LL * val - minVal); // Use 2LL to ensure long long calculation
                minVal = val;             // Update minVal
            } else {
                s.push(val); // Otherwise, just push the value
            }
        }
    }

    void pop() {
        if (!s.empty()) {
            long long top = s.top();
            s.pop();
            // If the top value is an encoded minimum value,
            // update minVal to the previous minimum.
            if (top < minVal) {
                minVal = 2 * minVal - top; // Reverse the encoding: prevMin = 2*currentMin - encodedVal
            }
        }
    }

    int top() {
        if (!s.empty()) {
            long long top = s.top();
            // If the top value is an encoded minimum, return minVal.
            if (top < minVal) {
                return (int)minVal; // Cast back to int
            } else {
                return (int)top; // Otherwise, return the top value.
            }
        }
        return -1;
    }

    int getMin() {
        return (int)minVal;
    }
};

// Approach 5: Using a vector of pairs (for demonstration and comparison)
// This approach uses a vector of pairs, similar to Approach 1, but using a vector.
// This is generally *not* recommended for a stack implementation, as vectors do not
// provide the same performance characteristics (specifically, O(1) push and pop at the end)
// as stacks.  This is included primarily for comparison and demonstration.  For a true
// stack implementation, use std::stack.
class MinStack5 {
private:
    std::vector<std::pair<int, int>> data; // Vector of pairs (value, min)

public:
    MinStack5() {
    }

    void push(int val) {
        if (data.empty()) {
            data.push_back({val, val});
        } else {
            int currentMin = data.back().second;
            data.push_back({val, std::min(val, currentMin)});
        }
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    int top() {
        if (!data.empty()) {
            return data.back().first;
        }
        return -1;
    }

    int getMin() {
        if (!data.empty()) {
            return data.back().second;
        }
        return INT_MAX;
    }
};

int main() {
    // Example Usage (for all approaches)
    std::cout << "Approach 1: Using a pair (value, min) in the stack\n";
    MinStack1 ms1;
    ms1.push(-2);
    ms1.push(0);
    ms1.push(-3);
    std::cout << "Min: " << ms1.getMin() << std::endl; // Output: -3
    std::cout << "Top: " << ms1.top() << std::endl;     // Output: -3
    ms1.pop();
    std::cout << "Top: " << ms1.top() << std::endl;     // Output: 0
    std::cout << "Min: " << ms1.getMin() << std::endl; // Output: -2

    std::cout << "\nApproach 2: Using two stacks (one for values, one for minimums)\n";
    MinStack2 ms2;
    ms2.push(-2);
    ms2.push(0);
    ms2.push(-3);
    std::cout << "Min: " << ms2.getMin() << std::endl;
    std::cout << "Top: " << ms2.top() << std::endl;
    ms2.pop();
    std::cout << "Top: " << ms2.top() << std::endl;
    std::cout << "Min: " << ms2.getMin() << std::endl;

    std::cout << "\nApproach 3: Optimized two-stack approach\n";
    MinStack3 ms3;
    ms3.push(-2);
    ms3.push(0);
    ms3.push(-3);
    std::cout << "Min: " << ms3.getMin() << std::endl;
    std::cout << "Top: " << ms3.top() << std::endl;
    ms3.pop();
    std::cout << "Top: " << ms3.top() << std::endl;
    std::cout << "Min: " << ms3.getMin() << std::endl;

    std::cout << "\nApproach 4: Using a single stack and encoding the minimum\n";
    MinStack4 ms4;
    ms4.push(-2);
    ms4.push(0);
    ms4.push(-3);
    std::cout << "Min: " << ms4.getMin() << std::endl;
    std::cout << "Top: " << ms4.top() << std::endl;
    ms4.pop();
    std::cout << "Top: " << ms4.top() << std::endl;
    std::cout << "Min: " << ms4.getMin() << std::endl;

    std::cout << "\nApproach 5: Using a vector of pairs\n";
    MinStack5 ms5;
    ms5.push(-2);
    ms5.push(0);
    ms5.push(-3);
    std::cout << "Min: " << ms5.getMin() << std::endl;
    std::cout << "Top: " << ms5.top() << std::endl;
    ms5.pop();
    std::cout << "Top: " << ms5.top() << std::endl;
    std::cout << "Min: " << ms5.getMin() << std::endl;

    return 0;
}

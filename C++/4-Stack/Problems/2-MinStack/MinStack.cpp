#include <iostream>
#include <stack>
#include <vector>
#include <climits> // For INT_MAX and INT_MIN
#include <algorithm> // For min()

using namespace std;

// Approach 1: Using a pair (value, min) in the stack
// For every element, store the current minimum along with the element itself.
class MinStack1 {
private:
    stack<pair<int, int>> s; // Stack of pairs: (value, currentMin)

public:
    MinStack1() {
        // Constructor is empty
    }

    void push(int val) {
        if (s.empty()) {
            s.push({val, val}); // First element: min is the value itself
        } else {
            int currentMin = min(val, s.top().second); // Calculate the new minimum
            s.push({val, currentMin});             // Push the value and the minimum
        }
    }

    void pop() {
        s.pop(); // Simply pop the top element
    }

    int top() {
        return s.top().first; // Return the value at the top
    }

    int getMin() {
        return s.top().second; // Return the minimum value at the top
    }
};

// Approach 2: Using two stacks (one for values, one for minimums)
// One stack stores all values, the other stores the minimums encountered so far.
class MinStack2 {
private:
    stack<int> s;      // Stack for storing the values
    stack<int> minStack; // Stack for storing the minimums

public:
    MinStack2() {
        // Constructor is empty
    }

    void push(int val) {
        s.push(val); // Push the value onto the value stack
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val); // Push to minStack if it's empty or the new value is <= current min
        }
    }

    void pop() {
        if (s.top() == minStack.top()) {
            minStack.pop(); // Pop from minStack if the top value is the current minimum
        }
        s.pop(); // Always pop from the value stack
    }

    int top() {
        return s.top(); // Return the top value
    }

    int getMin() {
        return minStack.top(); // Return the top of the minimum stack
    }
};

// Approach 3: Using a single stack and encoding the min value
//  Clever approach: When a new min is found, store the *difference* between
//  the new min and the *previous* min, rather than the min itself.
class MinStack3 {
private:
    stack<long long> s;
    long long minVal; // Keep track of the global minimum

public:
    MinStack3() {
        minVal = INT_MAX;
    }

    void push(int val) {
        if (s.empty()) {
            minVal = val;
            s.push(val);
        } else {
            if (val < minVal) {
                s.push(2LL * val - minVal); // Store the difference (encoded min)
                minVal = val;             // Update the global minimum
            } else {
                s.push(val); // If not a new min, store the original value
            }
        }
    }

    void pop() {
        if (s.empty()) return;

        long long top = s.top();
        s.pop();

        if (top < minVal) {
            // If the top was an encoded min, update minVal
            minVal = 2 * minVal - top;
        }
    }

    int top() {
        if (s.empty()) return -1; // Or throw an exception
        long long top = s.top();
        if (top < minVal) {
            return (int)minVal; // return the minVal
        }
        return (int)top;
    }

    int getMin() {
        return (int)minVal;
    }
};

// Approach 4: Using a vector and a min variable.
// This approach uses a vector to store the elements and a separate variable to store the minimum value.
class MinStack4 {
private:
    vector<int> data;
    int minVal;

public:
    MinStack4() {
        minVal = INT_MAX;
    }

    void push(int val) {
        data.push_back(val);
        if (val < minVal) {
            minVal = val;
        }
    }

    void pop() {
        if (data.empty()) return;
        int poppedVal = data.back();
        data.pop_back();
        if (poppedVal == minVal) {
            // Need to find the new minimum
            minVal = INT_MAX; // Reset to max, and find min again.
            for (int val : data) {
                minVal = min(minVal, val);
            }
            if(data.empty()) {
               minVal = INT_MAX;
            }
        }
    }

    int top() {
        if (data.empty()) return -1;
        return data.back();
    }

    int getMin() {
        return minVal;
    }
};

// Approach 5: Using a linked list and a min variable.
// This approach uses a linked list to store the elements and a separate variable to store the minimum value.
class MinStack5 {
private:
    struct Node {
        int val;
        Node* next;
        int minVal; // Minimum value seen so far *including* this node
        Node(int x, int min) : val(x), next(nullptr), minVal(min) {}
    };
    Node* head;
    //int minVal; // Not needed, its in the Node.

public:
    MinStack5() : head(nullptr) {
        //minVal = INT_MAX;
    }

    void push(int val) {
        if (!head) {
            head = new Node(val, val);
            //minVal = val;
        } else {
            int currentMin = min(val, head->minVal);
            head = new Node(val, currentMin);
            head->next = head;
            head = head->next;
            head = new Node(val, currentMin); // Corrected: Create a new node, insert at the head.
            head->next = head->next;       // Make the new node point to the *old* head
            head = head->next;                 // Update head to the new node.
        }
    }

    void pop() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int top() {
        if (!head) return -1;
        return head->val;
    }

    int getMin() {
        if (!head) return INT_MAX;
        return head->minVal;
    }
};

int main() {
    // Example usage of each MinStack implementation:
    cout << "Approach 1: Using a pair (value, min) in the stack" << endl;
    MinStack1 ms1;
    ms1.push(3);
    ms1.push(5);
    ms1.push(2);
    ms1.push(1);
    cout << "Top: " << ms1.top() << endl;       // Output: 1
    cout << "Min: " << ms1.getMin() << endl; // Output: 1
    ms1.pop();
    cout << "Top: " << ms1.top() << endl;       // Output: 2
    cout << "Min: " << ms1.getMin() << endl; // Output: 2

    cout << "\nApproach 2: Using two stacks (one for values, one for minimums)" << endl;
    MinStack2 ms2;
    ms2.push(3);
    ms2.push(5);
    ms2.push(2);
    ms2.push(1);
    cout << "Top: " << ms2.top() << endl;       // Output: 1
    cout << "Min: " << ms2.getMin() << endl; // Output: 1
    ms2.pop();
    cout << "Top: " << ms2.top() << endl;       // Output: 2
    cout << "Min: " << ms2.getMin() << endl; // Output: 2

    cout << "\nApproach 3: Using a single stack and encoding the min value" << endl;
    MinStack3 ms3;
    ms3.push(3);
    ms3.push(5);
    ms3.push(2);
    ms3.push(1);
    cout << "Top: " << ms3.top() << endl;       // Output: 1
    cout << "Min: " << ms3.getMin() << endl; // Output: 1
    ms3.pop();
    cout << "Top: " << ms3.top() << endl;       // Output: 2
    cout << "Min: " << ms3.getMin() << endl; // Output: 2

    cout << "\nApproach 4: Using a vector and a min variable." << endl;
    MinStack4 ms4;
    ms4.push(3);
    ms4.push(5);
    ms4.push(2);
    ms4.push(1);
    cout << "Top: " << ms4.top() << endl;       // Output: 1
    cout << "Min: " << ms4.getMin() << endl; // Output: 1
    ms4.pop();
    cout << "Top: " << ms4.top() << endl;       // Output: 2
    cout << "Min: " << ms4.getMin() << endl; // Output: 2

    cout << "\nApproach 5: Using a linked list and a min variable." << endl;
    MinStack5 ms5;
    ms5.push(3);
    ms5.push(5);
    ms5.push(2);
    ms5.push(1);
    cout << "Top: " << ms5.top() << endl;
    cout << "Min: " << ms5.getMin() << endl;
    ms5.pop();
    cout << "Top: " << ms5.top() << endl;
    cout << "Min: " << ms5.getMin() << endl;

    return 0;
}

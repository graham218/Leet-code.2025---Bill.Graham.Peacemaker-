#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Function to calculate the sum of the squares of the digits of a number
int sumOfSquaredDigits(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

// Approach 1: Using a set to detect cycles
//  - Real-world application: Detecting infinite loops in iterative processes, such as in financial modeling or simulations.
bool isHappy_set(int n) {
    unordered_set<int> seenNumbers;
    while (n != 1 && seenNumbers.find(n) == seenNumbers.end()) {
        seenNumbers.insert(n);
        n = sumOfSquaredDigits(n);
    }
    return n == 1;
}

// Approach 2: Floyd's Cycle Detection (Tortoise and Hare)
//  - Real-world application: Optimizing memory usage in large dataset processing, such as finding loops in linked lists or data streams.
bool isHappy_floyd(int n) {
    int slow = n;
    int fast = n;
    do {
        slow = sumOfSquaredDigits(slow);
        fast = sumOfSquaredDigits(sumOfSquaredDigits(fast));
    } while (slow != fast);
    return slow == 1;
}

// Approach 3: Using a vector to store the sequence (for demonstration and analysis)
//   - Real-world application:  Debugging and analyzing iterative algorithms, tracking the sequence of values to understand behavior.
bool isHappy_vector(int n) {
    vector<int> sequence;
    while (n != 1) {
        if (find(sequence.begin(), sequence.end(), n) != sequence.end()) {
            return false; // Cycle detected
        }
        sequence.push_back(n);
        n = sumOfSquaredDigits(n);
    }
    return true;
}

// Approach 4:  Using string conversion and avoiding extra data structures
//   - Real-world application:  Embedded systems or environments with limited memory, where minimizing memory footprint is crucial.
bool isHappy_string(int n) {
    while (n != 1) {
        string s = to_string(n);
        int sum = 0;
        for (char c : s) {
            int digit = c - '0';
            sum += digit * digit;
        }
        n = sum;
        if (n == 4) return false; // The number 4 is the start of the infinite loop for non-happy numbers.
    }
    return true;
}

// Approach 5: Using Recursion
// - Real-world application: Implementing mathematical functions or algorithms that have a natural recursive definition.
bool isHappy_recursive(int n) {
    if (n == 1) return true;
    if (n == 4) return false; // Base case for non-happy numbers
    return isHappy_recursive(sumOfSquaredDigits(n));
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    cout << "Using Set: " << (isHappy_set(num) ? "Happy" : "Not Happy") << endl;
    cout << "Using Floyd's Cycle Detection: " << (isHappy_floyd(num) ? "Happy" : "Not Happy") << endl;
    cout << "Using Vector: " << (isHappy_vector(num) ? "Happy" : "Not Happy") << endl;
    cout << "Using String: " << (isHappy_string(num) ? "Happy" : "Not Happy") << endl;
    cout << "Using Recursion: " << (isHappy_recursive(num) ? "Happy" : "Not Happy") << endl;

    return 0;
}

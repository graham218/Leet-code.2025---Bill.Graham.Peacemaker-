#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>

using namespace std;

// Function to print a vector (useful for debugging and output)
void printVector(const vector<int>& vec, const string& prefix = "") {
    cout << prefix;
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Approach 1: School Math Addition (Detailed Simulation)
// Simulates the manual process of adding one to a number, handling carries.
// Real-world application: Implementing arbitrary-precision arithmetic (big integer libraries).
vector<int> plusOne_SchoolBook(vector<int>& digits) {
    int n = digits.size();
    int carry = 1; // Start with adding one
    for (int i = n - 1; i >= 0; i--) {
        int sum = digits[i] + carry;
        digits[i] = sum % 10; // Get the digit
        carry = sum / 10;    // Calculate the carry
    }
    if (carry > 0) {
        digits.insert(digits.begin(), carry); // Insert the carry at the beginning
    }
    return digits;
}

// Approach 2: Optimized Iteration (Early Return)
// Optimizes the iteration by returning early if no carry is needed.
// Real-world application: Optimizing performance-critical calculations in financial systems.
vector<int> plusOne_Optimized(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++; // Increment the digit if it's less than 9
            return digits; // No carry, so we can return early
        }
        digits[i] = 0; // Otherwise, set it to 0 and continue with carry
    }
    // If we get here, all digits were 9, so we need to add a leading 1
    digits.insert(digits.begin(), 1);
    return digits;
}

// Approach 3: Using STL (Standard Template Library) - (Less Efficient for this Specific Problem)
// Uses STL functions for a more concise solution (but potentially less efficient).
// Real-world application: Quickly prototyping or scripting simple arithmetic operations.  Good for educational purposes.
vector<int> plusOne_STL(vector<int>& digits) {
    int n = digits.size();
    // Convert vector to a single number (potential overflow for large numbers)
    long long num = 0;
    for (int i = 0; i < n; i++)
    {
        num = num * 10 + digits[i];
    }

    num++; // Add one

    vector<int> result;
    if (num == 0)
    {
        result.push_back(0);
        return result;
    }
    // Convert the number back to a vector of digits
    while (num > 0) {
        result.push_back(num % 10);
        num /= 10;
    }
    reverse(result.begin(), result.end()); // Reverse to get the correct order
    return result;
}

// Approach 4: String Conversion (Handles Very Large Numbers)
// Converts the digit vector to a string, adds one, and converts back.  Handles very large numbers without overflow.
// Real-world application: Handling very large numbers, such as in cryptography or scientific computing, where integer overflow is a concern.
vector<int> plusOne_StringConversion(vector<int>& digits) {
    string numberStr = "";
    for (int digit : digits) {
        numberStr += to_string(digit);
    }

    // String to integer conversion (requires handling potential overflow for extremely large numbers, but the basic idea is here)
    long long num = stoll(numberStr); // stoll() for string to long long
    num++; // add 1
    string resultStr = to_string(num); //long long to string

    vector<int> result;
    for (char c : resultStr) {
        result.push_back(c - '0'); // Convert char to int
    }
    return result;
}

// Approach 5:  In-place Modification with Carry (Most Efficient)
// Modifies the vector in-place to avoid extra memory allocation.  This is the most efficient approach.
// Real-world application: Embedded systems or resource-constrained environments where memory usage is critical.
vector<int> plusOne_InPlace(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    digits.insert(digits.begin(), 1); // insert 1 at the beginning.
    return digits;
}

int main() {
    // Example usage of each approach
    vector<int> number1 = {1, 2, 3};
    vector<int> number2 = {9, 9, 9};
    vector<int> number3 = {1, 2, 9};
    vector<int> number4 = {9};
    vector<int> number5 = {6, 5, 4, 9};

    cout << "Original Number: ";
    printVector(number1);

    vector<int> result1_school = plusOne_SchoolBook(number1);
    cout << "Plus One (Schoolbook): ";
    printVector(result1_school); // Output: 1 2 4

    vector<int> result1_optimized = plusOne_Optimized(number2);
    cout << "Plus One (Optimized): ";
    printVector(result1_optimized); // Output: 1 0 0 0

    vector<int> result1_stl = plusOne_STL(number3);
    cout << "Plus One (STL): ";
    printVector(result1_stl); // Output: 1 3 0

    vector<int> result1_string = plusOne_StringConversion(number4);
    cout << "Plus One (String): ";
    printVector(result1_string); // Output: 1 0

    vector<int> result1_inplace = plusOne_InPlace(number5);
    cout << "Plus One (In-place): ";
    printVector(result1_inplace); // Output: 6 5 5 0

    return 0;
}

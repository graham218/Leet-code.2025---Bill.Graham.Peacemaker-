#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Required for std::accumulate in approach 5

using namespace std;

// Function to print the vector
void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

// Approach 1: Iterative with Carry (Most Common)
// - Iterates from the least significant digit.
// - Adds one and handles the carry-over.
// - Efficient and intuitive.
vector<int> plusOne_iterative(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        } else {
            digits[i] = 0; // Set to 0, carry-over
        }
    }
    // If the loop finishes, it means all digits were 9.
    digits.insert(digits.begin(), 1); // Add a '1' at the beginning
    return digits;
}

// Approach 2: Using std::reverse (Less Common, but Shows STL Usage)
// - Reverses the vector, adds one, and handles carry, then reverses back.
// - Demonstrates using standard library functions.
vector<int> plusOne_reverse(vector<int>& digits) {
    reverse(digits.begin(), digits.end()); // Reverse the digits
    int carry = 1;
    for (int i = 0; i < digits.size(); i++) {
        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        digits.push_back(carry); // Add the carry at the end
    }
    reverse(digits.begin(), digits.end()); // Reverse back to original order
    return digits;
}

// Approach 3:  Using Recursion (Illustrative, Can be Less Efficient)
// - Recursively adds one to the least significant digit.
// - Handles the carry in the recursive calls.
vector<int> plusOne_recursive(vector<int>& digits, int index = 0) {
    if (index == digits.size()) {
        digits.insert(digits.begin(), 1);
        return digits;
    }
    if (index == digits.size() - 1)
    {
        if (digits[index] < 9)
        {
            digits[index]++;
            return digits;
        }
        else
        {
            digits[index] = 0;
            return plusOne_recursive(digits, index -1);
        }
    }
    else
    {
        if (digits[index] < 9)
        {
            digits[index]++;
            return digits;
        }
        else
        {
            digits[index] = 0;
            return plusOne_recursive(digits, index - 1);
        }
    }
}

// Approach 4:  Using a While Loop (Similar to Iterative, but Different Structure)
// - Uses a while loop to iterate through the digits.
// - Adds one and handles the carry.
vector<int> plusOne_while(vector<int>& digits) {
    int n = digits.size();
    int i = n - 1;
    while (i >= 0) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
        i--;
    }
    digits.insert(digits.begin(), 1);
    return digits;
}

// Approach 5:  Using std::accumulate (More Complex, Not Recommended for This)
// - Converts the digit vector to a single number, adds one, and converts it back to a vector.
// -  Demonstrates numeric operations, but is less efficient and harder to understand for this problem.
vector<int> plusOne_accumulate(vector<int>& digits) {
    long long number = 0;
    long long multiplier = 1;
    for (int i = digits.size() - 1; i >= 0; i--) {
        number += digits[i] * multiplier;
        multiplier *= 10;
    }
    number++; // Add one to the number.

    vector<int> result;
    if (number == 0)
    {
        result.push_back(0);
        return result;
    }
    while (number > 0) {
        result.push_back(number % 10);
        number /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<int> digits1 = {1, 2, 3};
    cout << "Original digits1: ";
    printVector(digits1);

    vector<int> result1_iterative = plusOne_iterative(digits1);
    cout << "Result (Iterative): ";
    printVector(result1_iterative);

    vector<int> result1_reverse = plusOne_reverse(digits1);
    cout << "Result (Reverse): ";
    printVector(result1_reverse);

    vector<int> result1_recursive = plusOne_recursive(digits1);
    cout << "Result (Recursive): ";
    printVector(result1_recursive);

    vector<int> result1_while = plusOne_while(digits1);
    cout << "Result (While): ";
    printVector(result1_while);

    vector<int> result1_accumulate = plusOne_accumulate(digits1);
    cout << "Result (Accumulate): ";
    printVector(result1_accumulate);
    cout << endl;

    vector<int> digits2 = {9, 9, 9};
    cout << "Original digits2: ";
    printVector(digits2);

    vector<int> result2_iterative = plusOne_iterative(digits2);
    cout << "Result (Iterative): ";
    printVector(result2_iterative);

    vector<int> result2_reverse = plusOne_reverse(digits2);
    cout << "Result (Reverse): ";
    printVector(result2_reverse);

    vector<int> result2_recursive = plusOne_recursive(digits2);
    cout << "Result (Recursive): ";
    printVector(result2_recursive);

    vector<int> result2_while = plusOne_while(digits2);
    cout << "Result (While): ";
    printVector(result2_while);

    vector<int> result2_accumulate = plusOne_accumulate(digits2);
    cout << "Result (Accumulate): ";
    printVector(result2_accumulate);

    return 0;
}

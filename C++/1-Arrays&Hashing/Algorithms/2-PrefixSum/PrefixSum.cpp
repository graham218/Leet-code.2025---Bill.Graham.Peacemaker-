#include <iostream>
#include <vector>
#include <numeric> // For std::partial_sum

// Function to print a vector
void printVector(const std::vector<int>& vec, const std::string& prefix = "") {
    std::cout << prefix;
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Approach 1: Iterative Prefix Sum
// Calculates the prefix sum of a vector using a simple loop.
//
// Time Complexity: O(n), where n is the size of the input vector.
// Space Complexity: O(1) - modifies the input vector in place.  If you create a new vector, it would be O(n).
std::vector<int> iterativePrefixSum(std::vector<int> arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        arr[i] += arr[i - 1]; // Update each element with the sum of itself and the previous element.
    }
    return arr;
}

// Approach 2: Iterative Prefix Sum (with a new vector)
// Calculates the prefix sum and stores it in a new vector.
//
// Time Complexity: O(n)
// Space Complexity: O(n) - creates a new vector to store the prefix sums.
std::vector<int> iterativePrefixSumNewVector(const std::vector<int>& arr) {
    std::vector<int> prefixSum(arr.size());
    if (arr.empty()) return prefixSum; //handle empty input
    prefixSum[0] = arr[0]; // The first element of the prefix sum is the same as the first element of the original array.
    for (size_t i = 1; i < arr.size(); ++i) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }
    return prefixSum;
}

// Approach 3: Using std::partial_sum (from the <numeric> library)
//  Calculates the prefix sum using the std::partial_sum algorithm.
//
// Time Complexity: O(n)
// Space Complexity: O(1) if modifying in place, O(n) if using a new vector.
std::vector<int> partialSumPrefixSum(std::vector<int> arr) {
    std::partial_sum(arr.begin(), arr.end(), arr.begin()); // In-place modification
    return arr;
}

// Approach 4: Using std::partial_sum (with a new vector)
// Calculates prefix sum into a new vector
// Time Complexity: O(n)
// Space Complexity: O(n)
std::vector<int> partialSumPrefixSumNewVector(const std::vector<int>& arr) {
    std::vector<int> prefixSum(arr.size());
    std::partial_sum(arr.begin(), arr.end(), prefixSum.begin());
    return prefixSum;
}

// Approach 5:  Recursive Approach (Less efficient, for demonstration)
// Calculates the prefix sum recursively.  This is generally *not* recommended
// for large arrays due to potential stack overflow and its inefficiency.
//
// Time Complexity: O(n) - Each element is visited once, but the overhead is larger.
// Space Complexity: O(n) - Due to the recursion depth.
std::vector<int> recursivePrefixSum(const std::vector<int>& arr, int index = -1) {
    if (index == -1) index = arr.size() - 1; //start at the end
    std::vector<int> prefixSum(arr.size());
    if (index < 0) {
        return prefixSum; // Base case: empty array
    }
    if (index == 0) {
        prefixSum[0] = arr[0];
        return prefixSum;
    }

    std::vector<int> prevPrefixSum = recursivePrefixSum(arr, index - 1); // Recursive call
    for(int i = 0; i < index; ++i){
        prefixSum[i] = prevPrefixSum[i];
    }
    prefixSum[index] = prevPrefixSum[index - 1] + arr[index];
    return prefixSum;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> emptyArr = {};

    std::cout << "Original Array: ";
    printVector(arr);

    // Approach 1: Iterative Prefix Sum (in-place)
    std::vector<int> result1 = iterativePrefixSum(arr);
    std::cout << "Iterative Prefix Sum (in-place): ";
    printVector(result1); // The original 'arr' is now modified.

    // Reset arr for other tests
    arr = {1, 2, 3, 4, 5};

    // Approach 2: Iterative Prefix Sum (new vector)
    std::vector<int> result2 = iterativePrefixSumNewVector(arr);
    std::cout << "Iterative Prefix Sum (new vector): ";
    printVector(result2);

     // Test with empty array
    std::vector<int> emptyResult2 = iterativePrefixSumNewVector(emptyArr);
    std::cout << "Iterative Prefix Sum (new vector) - Empty Array: ";
    printVector(emptyResult2);

    // Approach 3: Using std::partial_sum (in-place)
    std::vector<int> result3 = partialSumPrefixSum(arr);
    std::cout << "std::partial_sum (in-place): ";
    printVector(result3); // The original 'arr' is modified again.

    // Reset arr
    arr = {1, 2, 3, 4, 5};

    // Approach 4: Using std::partial_sum (new vector)
    std::vector<int> result4 = partialSumPrefixSumNewVector(arr);
    std::cout << "std::partial_sum (new vector): ";
    printVector(result4);

    // Approach 5: Recursive
    std::vector<int> result5 = recursivePrefixSum(arr);
    std::cout << "Recursive Prefix Sum: ";
    printVector(result5);

    // Test the recursive function with an empty array
    std::vector<int> emptyResult = recursivePrefixSum(emptyArr);
    std::cout << "Recursive Prefix Sum (Empty Array): ";
    printVector(emptyResult);

    return 0;
}

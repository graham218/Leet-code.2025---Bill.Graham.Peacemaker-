#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> // for std::rand(), std::srand()
#include <ctime>   // for std::time()

// Function to print the vector
void printVector(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to generate a random vector of 0s, 1s, and 2s
std::vector<int> generateRandomVector(int size) {
    std::vector<int> arr(size);
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 3; // Generate random numbers 0, 1, or 2
    }
    return arr;
}

// Approach 1: Using Counting Sort (Not in-place, not optimal for DNF, but conceptually related)
//  - Counts occurrences of 0, 1, and 2.
//  - Overwrites the original array with the counted values.
//  - Time Complexity: O(n)
//  - Space Complexity: O(1) (since we only use a fixed-size count array of 3 elements)
void dutchFlagSort_CountingSort(std::vector<int>& arr) {
    int count0 = 0, count1 = 0, count2 = 0;
    for (int num : arr) {
        if (num == 0) ++count0;
        else if (num == 1) ++count1;
        else ++count2;
    }
    int index = 0;
    while (count0--) arr[index++] = 0;
    while (count1--) arr[index++] = 1;
    while (count2--) arr[index++] = 2;
}

// Approach 2:  Two Pointers (Incorrect for general DNF, but shows a basic idea)
// This approach is NOT correct for the Dutch National Flag problem in its general form
// where the elements are not strictly 0, 1, and 2.  It's included here for illustration
// of the two-pointer concept, but it will not correctly partition the array in all cases.
// It assumes that if you swap a non-zero to the left, it is a zero.
//  - Uses two pointers, `low` and `high`.
//  - Moves all 0s to the left and 2s to the right, but doesn't handle 1s correctly in between.
//  - Time Complexity: O(n) in the best and average case, O(n^2) in the worst case.
//  - Space Complexity: O(1)
void dutchFlagSort_TwoPointers(std::vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    while (low < high) {
        if (arr[low] == 0) {
            low++;
        } else if (arr[high] == 2) {
            high--;
        } else {
            std::swap(arr[low], arr[high]); // Potentially swaps a 1 and a 2.
        }
    }
}

// Approach 3: Three Pointers (The standard, correct solution)
//  - Uses three pointers: `low`, `mid`, and `high`.
//  - `low`:  Keeps track of the boundary between 0s and others.
//  - `mid`:  The current element being examined.
//  - `high`: Keeps track of the boundary between 2s and others.
//  - Iterates through the array, swapping elements as needed to partition it.
//  - Time Complexity: O(n)
//  - Space Complexity: O(1)
void dutchFlagSort_ThreePointers(std::vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;
    while (mid <= high) {
        if (arr[mid] == 0) {
            std::swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else { // arr[mid] == 2
            std::swap(arr[mid], arr[high]);
            high--;
            // Note: mid does NOT increment here because the swapped element
            // from 'high' could be a 0, 1, or 2, and needs to be processed.
        }
    }
}

// Approach 4:  Three Pointers - Optimized (Slightly different order, but functionally the same)
//  - Uses three pointers: `low`, `mid`, and `high`.
//  - This version aims to minimize the number of swaps.
//  - Time Complexity: O(n)
//  - Space Complexity: O(1)
void dutchFlagSort_ThreePointersOptimized(std::vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;
    while (mid <= high) {
        switch (arr[mid]) {
            case 0:
                std::swap(arr[low++], arr[mid++]);
                break;
            case 1:
                mid++;
                break;
            case 2:
                std::swap(arr[mid], arr[high--]);
                break;
        }
    }
}

// Approach 5: Using std::partition (Illustrative, but not the typical DNF solution)
// - Uses the std::partition algorithm from the C++ standard library.
// - Partitions the array into three sections based on lambda conditions.
// - This approach is less efficient and less clear than the 3-pointer solution.
// - Time Complexity: O(n)
// - Space Complexity: O(1) (in-place)
void dutchFlagSort_Partition(std::vector<int>& arr) {
    auto boundary1 = std::partition(arr.begin(), arr.end(), [](int x){ return x == 0; }); //after this, all 0s are before boundary1
    std::partition(boundary1, arr.end(), [](int x){ return x == 1; }); //after this, all 1s are before the new boundary, and 2s are after.
}

int main() {
    // Seed the random number generator.  This should only be done once at the start of the program.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Dutch National Flag Problem" << std::endl;

    // Test with a randomly generated vector
    std::vector<int> arr = generateRandomVector(10);
    std::cout << "Original Array: ";
    printVector(arr);

    std::vector<int> arr1 = arr; // Copy for each approach
    std::vector<int> arr2 = arr;
    std::vector<int> arr3 = arr;
    std::vector<int> arr4 = arr;
    std::vector<int> arr5 = arr;

    std::cout << "\nApproach 1: Counting Sort" << std::endl;
    dutchFlagSort_CountingSort(arr1);
    std::cout << "Sorted Array: ";
    printVector(arr1);

    std::cout << "\nApproach 2: Two Pointers (Incorrect)" << std::endl;
    dutchFlagSort_TwoPointers(arr2);
    std::cout << "Sorted Array: ";
    printVector(arr2); //This will not be correctly sorted in all cases.

    std::cout << "\nApproach 3: Three Pointers" << std::endl;
    dutchFlagSort_ThreePointers(arr3);
    std::cout << "Sorted Array: ";
    printVector(arr3);

    std::cout << "\nApproach 4: Three Pointers Optimized" << std::endl;
    dutchFlagSort_ThreePointersOptimized(arr4);
    std::cout << "Sorted Array: ";
    printVector(arr4);

    std::cout << "\nApproach 5: Using std::partition" << std::endl;
    dutchFlagSort_Partition(arr5);
    std::cout << "Sorted Array: ";
    printVector(arr5);

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random> // For generating random numbers

// Function to print the vector
void printVector(const std::vector<int>& arr, const std::string& message = "") {
    if (!message.empty()) {
        std::cout << message << ": ";
    }
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// 1. Basic Dutch National Flag Algorithm
//   - Uses three pointers: low, mid, and high.
//   - Iterates through the array, swapping elements to partition it.
//   - Real-world application: Sorting elements in an array with limited distinct values (e.g., sorting pixels by color components - Red, Green, Blue).
void dutchNationalFlag1(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

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

// 2. Dutch National Flag with explicit comparisons
//    - Same logic as the first approach, but uses explicit if-else statements
//    - Useful when you want to add more detailed logging or debugging information for each case.
void dutchNationalFlag2(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            std::swap(arr[low++], arr[mid++]);
        } else if (arr[mid] == 1) {
            mid++;
        } else { // arr[mid] == 2
            std::swap(arr[mid], arr[high--]);
        }
    }
}

// 3. Dutch National Flag using a helper function for swapping
//    - Encapsulates the swap operation into a separate function.
//    - Improves code readability and maintainability, especially if the swap operation is used multiple times.
void swapElements(std::vector<int>& arr, int i, int j) {
    std::swap(arr[i], arr[j]);
}

void dutchNationalFlag3(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            swapElements(arr, low++, mid++);
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swapElements(arr, mid, high--);
        }
    }
}

// 4. Dutch National Flag with error handling
//   - Includes checks for invalid input (e.g., elements not being 0, 1, or 2).
//   - More robust, suitable for production environments where you need to handle unexpected data.
void dutchNationalFlag4(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            std::swap(arr[low++], arr[mid++]);
        } else if (arr[mid] == 1) {
            mid++;
        } else if (arr[mid] == 2) {
            std::swap(arr[mid], arr[high--]);
        } else {
            // Handle the error:  In a real application, you might throw an exception,
            // log the error, or use a more sophisticated error handling mechanism.
            std::cerr << "Error: Invalid input.  Array elements must be 0, 1, or 2." << std::endl;
            return; // Exit the function.  The array is corrupted.
        }
    }
}

// 5. Dutch National Flag using STL
//  - Uses std::partition to achieve the sorting.
//  - Demonstrates how to leverage the C++ Standard Template Library (STL) for a more concise solution.
//  - This approach might be slightly less efficient than the manual implementations for this specific problem,
//    but it showcases a different way to solve it and can be useful for more complex partitioning scenarios.
void dutchNationalFlag5(std::vector<int>& arr) {
    // Partition the array into three sections: 0s, 1s, and 2s
    auto it1 = std::partition(arr.begin(), arr.end(), [](int x) { return x == 0; }); // elements equal to 0 are placed before it1
    auto it2 = std::partition(it1, arr.end(), [](int x) { return x == 1; }); // elements equal to 1 are placed before it2. elements after it2 are 2.
    // The array is now partitioned as required.
}

int main() {
    // Seed for the random number generator.  Good practice.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2); // Distribution for 0, 1, and 2

    // Test the different implementations
    std::cout << "Dutch National Flag Algorithm Implementations" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    // 1. Test with a random array
    std::vector<int> arr1(10);
    for (int i = 0; i < arr1.size(); ++i) {
        arr1[i] = dist(gen); // Fill vector with random 0, 1, 2
    }
    std::vector<int> arr1_copy1 = arr1;
    std::vector<int> arr1_copy2 = arr1;
    std::vector<int> arr1_copy3 = arr1;
    std::vector<int> arr1_copy4 = arr1;
    std::vector<int> arr1_copy5 = arr1;

    printVector(arr1, "Original Array");

    dutchNationalFlag1(arr1_copy1);
    printVector(arr1_copy1, "After dutchNationalFlag1");

    dutchNationalFlag2(arr1_copy2);
    printVector(arr1_copy2, "After dutchNationalFlag2");

    dutchNationalFlag3(arr1_copy3);
    printVector(arr1_copy3, "After dutchNationalFlag3");

    dutchNationalFlag4(arr1_copy4);
    printVector(arr1_copy4, "After dutchNationalFlag4");

    dutchNationalFlag5(arr1_copy5);
    printVector(arr1_copy5, "After dutchNationalFlag5");
    std::cout << "--------------------------------------------" << std::endl;
    // 2. Test with an array that is already sorted
    std::vector<int> arr2 = {0, 0, 1, 1, 2, 2, 2};
    std::vector<int> arr2_copy1 = arr2;
    std::vector<int> arr2_copy2 = arr2;
    std::vector<int> arr2_copy3 = arr2;
    std::vector<int> arr2_copy4 = arr2;
    std::vector<int> arr2_copy5 = arr2;
    printVector(arr2, "Already Sorted Array");

    dutchNationalFlag1(arr2_copy1);
    printVector(arr2_copy1, "After dutchNationalFlag1");

    dutchNationalFlag2(arr2_copy2);
    printVector(arr2_copy2, "After dutchNationalFlag2");

    dutchNationalFlag3(arr2_copy3);
    printVector(arr2_copy3, "After dutchNationalFlag3");

    dutchNationalFlag4(arr2_copy4);
    printVector(arr2_copy4, "After dutchNationalFlag4");

    dutchNationalFlag5(arr2_copy5);
    printVector(arr2_copy5, "After dutchNationalFlag5");
     std::cout << "--------------------------------------------" << std::endl;

    // 3. Test with an array that is reverse sorted
    std::vector<int> arr3 = {2, 2, 1, 1, 0, 0, 0};
    std::vector<int> arr3_copy1 = arr3;
    std::vector<int> arr3_copy2 = arr3;
    std::vector<int> arr3_copy3 = arr3;
    std::vector<int> arr3_copy4 = arr3;
    std::vector<int> arr3_copy5 = arr3;
    printVector(arr3, "Reverse Sorted Array");

    dutchNationalFlag1(arr3_copy1);
    printVector(arr3_copy1, "After dutchNationalFlag1");

    dutchNationalFlag2(arr3_copy2);
    printVector(arr3_copy2, "After dutchNationalFlag2");

    dutchNationalFlag3(arr3_copy3);
    printVector(arr3_copy3, "After dutchNationalFlag3");

    dutchNationalFlag4(arr3_copy4);
    printVector(arr3_copy4, "After dutchNationalFlag4");

    dutchNationalFlag5(arr3_copy5);
    printVector(arr3_copy5, "After dutchNationalFlag5");
    std::cout << "--------------------------------------------" << std::endl;

    // 4. Test with an array containing only 0s
    std::vector<int> arr4 = {0, 0, 0, 0, 0};
    std::vector<int> arr4_copy1 = arr4;
    std::vector<int> arr4_copy2 = arr4;
    std::vector<int> arr4_copy3 = arr4;
    std::vector<int> arr4_copy4 = arr4;
    std::vector<int> arr4_copy5 = arr4;
    printVector(arr4, "Array with only 0s");

    dutchNationalFlag1(arr4_copy1);
    printVector(arr4_copy1, "After dutchNationalFlag1");

    dutchNationalFlag2(arr4_copy2);
    printVector(arr4_copy2, "After dutchNationalFlag2");

    dutchNationalFlag3(arr4_copy3);
    printVector(arr4_copy3, "After dutchNationalFlag3");

    dutchNationalFlag4(arr4_copy4);
    printVector(arr4_copy4, "After dutchNationalFlag4");

    dutchNationalFlag5(arr4_copy5);
    printVector(arr4_copy5, "After dutchNationalFlag5");
    std::cout << "--------------------------------------------" << std::endl;

    // 5. Test with an array containing an invalid element
    std::vector<int> arr5 = {0, 1, 2, 0, 3, 1}; // Contains a 3, which is invalid
    std::vector<int> arr5_copy1 = arr5;
    std::vector<int> arr5_copy2 = arr5;
    std::vector<int> arr5_copy3 = arr5;
    std::vector<int> arr5_copy4 = arr5;
    std::vector<int> arr5_copy5 = arr5;
    printVector(arr5, "Array with an invalid element");

    dutchNationalFlag1(arr5_copy1);
    printVector(arr5_copy1, "After dutchNationalFlag1");

    dutchNationalFlag2(arr5_copy2);
    printVector(arr5_copy2, "After dutchNationalFlag2");

    dutchNationalFlag3(arr5_copy3);
    printVector(arr5_copy3, "After dutchNationalFlag3");

    dutchNationalFlag4(arr5_copy4); // This version will print an error message.
    printVector(arr5_copy4, "After dutchNationalFlag4");

    dutchNationalFlag5(arr5_copy5);
    printVector(arr5_copy5, "After dutchNationalFlag5");
    std::cout << "--------------------------------------------" << std::endl;
    return 0;
}

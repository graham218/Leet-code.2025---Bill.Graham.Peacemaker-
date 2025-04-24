#include <iostream>
#include <vector>
#include <algorithm>
#include <random> // For generating random numbers

// Function to print a vector
void printVector(const std::vector<int>& arr) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// 1. Merge Sort (Recursive)
// Merge two sorted subarrays into a single sorted array
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function for Merge Sort
void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2; // More robust to prevent overflow

        // Recursively sort the first and second halves
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Wrapper function for Merge Sort
void mergeSort(std::vector<int>& arr) {
    mergeSortRecursive(arr, 0, arr.size() - 1);
}

// 2. Merge Sort (Iterative)
void mergeSortIterative(std::vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}

// 3. Quick Sort (Recursive, Lomuto Partition)
// Function to partition the array using Lomuto partition scheme
int partitionLomuto(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = (low - 1);    // Index of smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Main function for Quick Sort (Recursive)
void quickSortRecursiveLomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at the correct place
        int pi = partitionLomuto(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortRecursiveLomuto(arr, low, pi - 1);
        quickSortRecursiveLomuto(arr, pi + 1, high);
    }
}

// Wrapper for Quick Sort (Lomuto)
void quickSortLomuto(std::vector<int>& arr) {
    quickSortRecursiveLomuto(arr, 0, arr.size() - 1);
}

// 4. Quick Sort (Recursive, Hoare Partition)
int partitionHoare(std::vector<int>& arr, int low, int high) {
    int pivot = arr[(low + high) / 2]; // Choose the middle element as the pivot
    int i = low - 1, j = high + 1;

    while (true) {
        // Find leftmost element greater than or equal to pivot
        do {
            i++;
        } while (arr[i] < pivot);

        // Find rightmost element less than or equal to pivot
        do {
            j--;
        } while (arr[j] > pivot);

        // Check if pointers cross
        if (i >= j)
            return j;

        std::swap(arr[i], arr[j]);
    }
}

void quickSortRecursiveHoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortRecursiveHoare(arr, low, pi);
        quickSortRecursiveHoare(arr, pi + 1, high);
    }
}

// Wrapper for Quick Sort (Hoare)
void quickSortHoare(std::vector<int>& arr) {
    quickSortRecursiveHoare(arr, 0, arr.size() - 1);
}

// 5. Quick Sort (Iterative)
void quickSortIterative(std::vector<int>& arr) {
    std::vector<std::pair<int, int>> stack;
    int low = 0;
    int high = arr.size() - 1;

    stack.push_back(std::make_pair(low, high));

    while (!stack.empty()) {
        std::pair<int, int> top = stack.back();
        stack.pop_back();
        low = top.first;
        high = top.second;

        if (low < high) {
            int pi = partitionLomuto(arr, low, high);

            stack.push_back(std::make_pair(low, pi - 1));
            stack.push_back(std::make_pair(pi + 1, high));
        }
    }
}

int main() {
    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100); // Range for random numbers

    // Create a vector of random integers
    std::vector<int> arr(10);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = dist(gen); // Generate a random number
    }

    std::vector<int> arrCopy; // To hold a copy for each sort

    // Test Merge Sort (Recursive)
    arrCopy = arr;
    std::cout << "Original array:      ";
    printVector(arrCopy);
    mergeSort(arrCopy);
    std::cout << "Merge Sort (Recursive): ";
    printVector(arrCopy);

    // Test Merge Sort (Iterative)
    arrCopy = arr;
    std::cout << "Original array:      ";
    printVector(arrCopy);
    mergeSortIterative(arrCopy);
    std::cout << "Merge Sort (Iterative): ";
    printVector(arrCopy);

    // Test Quick Sort (Recursive, Lomuto)
    arrCopy = arr;
    std::cout << "Original array:      ";
    printVector(arrCopy);
    quickSortLomuto(arrCopy);
    std::cout << "Quick Sort (Lomuto):   ";
    printVector(arrCopy);

    // Test Quick Sort (Recursive, Hoare)
    arrCopy = arr;
    std::cout << "Original array:        ";
    printVector(arrCopy);
    quickSortHoare(arrCopy);
    std::cout << "Quick Sort (Hoare):    ";
    printVector(arrCopy);

     // Test Quick Sort (Iterative)
    arrCopy = arr;
    std::cout << "Original array:        ";
    printVector(arrCopy);
    quickSortIterative(arrCopy);
    std::cout << "Quick Sort (Iterative):    ";
    printVector(arrCopy);

    return 0;
}

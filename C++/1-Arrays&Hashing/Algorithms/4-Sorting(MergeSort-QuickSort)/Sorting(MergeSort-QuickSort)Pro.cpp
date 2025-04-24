#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <future>

// Function to print a vector
void printVector(const std::vector<int>& arr) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// 1. Merge Sort - Top-Down (Recursive)
//   - Divide: Split the array into two halves.
//   - Conquer: Recursively sort each half.
//   - Combine: Merge the two sorted halves.
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

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// 2. Merge Sort - Bottom-Up (Iterative)
//   - Iteratively merge sub-arrays of increasing size.
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

// 3. Quick Sort - Recursive (Lomuto Partition)
//   - Divide: Pick an element as pivot and partition the array around the pivot.
//   - Conquer: Recursively sort the sub-array before and after the partition.
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

void quickSortRecursiveLomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partitionLomuto(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortRecursiveLomuto(arr, low, pi - 1);
        quickSortRecursiveLomuto(arr, pi + 1, high);
    }
}

// 4. Quick Sort - Recursive (Hoare Partition)
// Lomuto's partition is less efficient than Hoare's partition because
// in the worst case, Lomuto's partition can result in O(n^2) time complexity,
// while Hoare's partition is more balanced and generally performs better.
int partitionHoare(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low];
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
        quickSortRecursiveHoare(arr, low, pi);
        quickSortRecursiveHoare(arr, pi + 1, high);
    }
}

// 5. Quick Sort - Iterative
//   - Uses a stack to simulate the recursive calls.  This avoids
//     the overhead of recursive function calls, and can be
//     important in systems with limited stack space.
void quickSortIterative(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Create a stack to store sub-array boundaries
    std::vector<std::pair<int, int>> stack(n); // Maximum stack size n for worst case
    int top = -1;

    // Push initial values of low and high to stack
    stack[++top] = {0, n - 1};

    // Keep popping from stack while it's not empty
    while (top >= 0) {
        // Pop low and high
        int high = stack[top].second;
        int low = stack[top--].first;

        // Partition the array
        int pi = partitionLomuto(arr, low, high);

        // If there are elements on the left side of pivot,
        // push left side to stack
        if (pi - 1 > low) {
            stack[++top] = {low, pi - 1};
        }

        // If there are elements on the right side of pivot,
        // push right side to stack
        if (pi + 1 < high) {
            stack[++top] = {pi + 1, high};
        }
    }
}

// Function to generate a random vector of integers
std::vector<int> generateRandomVector(int size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    std::vector<int> randomVector(size);
    for (int i = 0; i < size; ++i) {
        randomVector[i] = dist(gen);
    }
    return randomVector;
}

int main() {
    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create a vector of random integers
    int size = 20;
    std::vector<int> arr = generateRandomVector(size, 1, 100);

    std::cout << "Original array: ";
    printVector(arr);

    // 1. Merge Sort - Top-Down
    std::vector<int> arr1 = arr; // Copy the original array
    mergeSort(arr1, 0, arr1.size() - 1);
    std::cout << "Merge Sort (Top-Down): ";
    printVector(arr1);

    // 2. Merge Sort - Bottom-Up
    std::vector<int> arr2 = arr;
    mergeSortIterative(arr2);
    std::cout << "Merge Sort (Bottom-Up): ";
    printVector(arr2);

    // 3. Quick Sort - Recursive (Lomuto Partition)
    std::vector<int> arr3 = arr;
    quickSortRecursiveLomuto(arr3, 0, arr3.size() - 1);
    std::cout << "Quick Sort (Recursive - Lomuto): ";
    printVector(arr3);

    // 4. Quick Sort - Recursive (Hoare Partition)
    std::vector<int> arr4 = arr;
    quickSortRecursiveHoare(arr4, 0, arr4.size() - 1);
    std::cout << "Quick Sort (Recursive - Hoare): ";
    printVector(arr4);

    // 5. Quick Sort - Iterative
    std::vector<int> arr5 = arr;
    quickSortIterative(arr5);
    std::cout << "Quick Sort (Iterative): ";
    printVector(arr5);

    return 0;
}

/*
 * Explanation of Approaches and Real-World Project Implementations:
 *
 * 1. Merge Sort - Top-Down (Recursive):
 * - Concept: Classic recursive divide-and-conquer approach.
 * - Real-World Use Case: External sorting (sorting large files that don't fit in memory),
 * stable sorting (maintaining the relative order of equal elements).  Good for
 * large datasets where stability is important.
 * - Advantages: Stable sort, guaranteed O(n log n) time complexity.
 * - Disadvantages: Requires extra space for merging, recursive overhead.
 *
 * 2. Merge Sort - Bottom-Up (Iterative):
 * - Concept: Iterative version of merge sort, merging smaller sub-arrays
 * to larger ones.
 * - Real-World Use Case: Similar to top-down merge sort, but avoids recursion,
 * which can be beneficial in environments with limited stack space. Useful in
 * embedded systems or scenarios where recursion depth is a concern.
 * - Advantages: Stable sort, guaranteed O(n log n) time complexity, no recursion overhead.
 * - Disadvantages: Requires extra space for merging.
 *
 * 3. Quick Sort - Recursive (Lomuto Partition):
 * - Concept: Recursive divide-and-conquer, partitions around a pivot.  Lomuto's
 * partition scheme is simpler but can be less efficient with certain inputs.
 * - Real-World Use Case: General-purpose sorting, often used in libraries
 * (e.g., in some implementations of std::sort).  Good for in-memory sorting
 * when average-case performance is critical.
 * - Advantages: Generally fast (average case O(n log n)), low overhead.
 * - Disadvantages: Worst-case O(n^2) time complexity (rare with randomized pivot),
 * not stable.
 *
 * 4. Quick Sort - Recursive (Hoare Partition):
 * - Concept: Similar to Lomuto, but uses a more efficient partitioning scheme
 * (Hoare's).
 * - Real-World Use Case: Preferred over Lomuto in many implementations due to
 * better average-case performance.  Used in high-performance sorting
 * scenarios.
 * - Advantages: Generally faster than Lomuto, average case O(n log n).
 * - Disadvantages: Worst-case O(n^2) time complexity, not stable, slightly more
 * complex to implement than Lomuto.
 *
 * 5. Quick Sort - Iterative:
 * - Concept: Iterative implementation of quick sort using a stack.
 * - Real-World Use Case: Useful when recursion is limited or expensive, such as in
 * embedded systems or certain programming environments.  Can also be
 * optimized for tail-call optimization in some languages (though C++ doesn't
 * guarantee it).
 * - Advantages: Avoids recursion overhead, can be more space-efficient in some cases.
 * - Disadvantages: More complex to implement than recursive quicksort, still has
 * worst-case O(n^2) time complexity, not stable.
 *
 * Key Considerations for Real-World Projects:
 *
 * - Input Data: The characteristics of the input data (size, distribution,
 * pre-sortedness) can significantly impact performance.  Quick sort's performance
 * can degrade with sorted or nearly sorted data if the pivot is not chosen
 * carefully.
 * - Memory Usage: Merge sort requires additional memory for the merge operation,
 * which can be a concern for very large datasets.  Quick sort is generally
 * in-place (or requires only a small amount of extra memory for the stack in
 * the iterative version).
 * - Stability: If the order of equal elements needs to be preserved, a stable
 * sorting algorithm like merge sort should be used.  Quick sort is not stable.
 * - Recursion Depth: Recursive algorithms can lead to stack overflow errors for
 * very large datasets.  Iterative versions of merge sort and quick sort can
 * mitigate this issue.
 * - Hybrid Approaches: In practice, sorting implementations often use hybrid
 * approaches. For example, a quicksort implementation might switch to insertion
 * sort for small sub-arrays (because insertion sort is more efficient for small
 * inputs) or use a different pivot selection strategy to avoid worst-case
 * behavior.  Introsort is a common hybrid that starts with quicksort and
 * switches to heapsort if the recursion depth gets too large (indicating a
 * potential worst-case scenario).
* - Parallelism: For very large datasets, parallel sorting algorithms can
* significantly improve performance.  Both merge sort and quick sort can be
* parallelized.
 */

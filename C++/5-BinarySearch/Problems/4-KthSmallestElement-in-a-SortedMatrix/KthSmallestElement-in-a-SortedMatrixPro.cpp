#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Function to print the matrix (for debugging purposes)
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Approach 1: Using Max Heap (Priority Queue)
// - Time Complexity: O(k log k)
// - Space Complexity: O(k)
// - Suitable for: When k is much smaller than n (k << n).  Good for finding a few smallest elements.
int kthSmallest_MaxHeap(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    // max-heap (priority queue) to store the k largest elements seen so far
    priority_queue<int> maxHeap;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            maxHeap.push(matrix[i][j]); // Add current element to the heap
            if (maxHeap.size() > k) {
                maxHeap.pop(); // If heap size exceeds k, remove the largest
            }
        }
    }
    return maxHeap.top(); // The top of the heap is the kth smallest
}

// Approach 2: Using Min Heap (Priority Queue)
// - Time Complexity: O(n^2 log k)  -> Can be optimized to O(k log n)
// - Space Complexity: O(k) -> Can be optimized to O(n)
// - Suitable for:  Not the most efficient in general, but demonstrates heap usage. Can be optimized.
int kthSmallest_MinHeap(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min Heap

    // Insert all elements into the min heap.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            minHeap.push(matrix[i][j]);
        }
    }

    // Pop k-1 elements. The kth element from the top will be the kth smallest.
    for (int i = 0; i < k - 1; i++) {
        minHeap.pop();
    }
    return minHeap.top();
}

// Approach 3: Binary Search
// - Time Complexity: O(n log(maxVal - minVal)) where maxVal and minVal are the maximum and minimum elements in the matrix.
// - Space Complexity: O(1)
// - Suitable for: Efficient for larger matrices.  A very common and efficient approach.
int kthSmallest_BinarySearch(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0];             // Smallest element
    int right = matrix[n - 1][n - 1];     // Largest element

    while (left < right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        int count = 0; // Count of elements <= mid

        // Count elements <= mid
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] <= mid) {
                    ++count;
                }
            }
        }

        if (count < k) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid;     // Search in the left half
        }
    }
    return left; // or right, they will be equal
}

// Approach 4: Optimized Binary Search
// - Time Complexity: O(n log(maxVal - minVal))  (Improved count calculation)
// - Space Complexity: O(1)
// - Suitable for:  Most efficient approach for larger matrices.  Standard in interviews.
int kthSmallest_OptimizedBinarySearch(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int low = matrix[0][0];
    int high = matrix[n - 1][n - 1];

    while (low < high) {
        int mid = low + (high - low) / 2;
        int count = 0;
        int j = n - 1;

        // Optimized counting: Start from top-right, move left/down
        for (int i = 0; i < n; ++i) {
            while (j >= 0 && matrix[i][j] > mid) {
                --j; // Move left if current element is too big
            }
            count += (j + 1); // Add the number of elements in this row <= mid
        }

        if (count < k) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

// Approach 5: Merge Sort Variation (Using Priority Queue)
// - Time Complexity: O(k log n)
// - Space Complexity: O(n)
// - Suitable for: Efficient when k is not too large, and the matrix is very large.
//   Breaks down the problem into merging sorted lists (rows).
struct MatrixElement {
    int val;
    int row;
    int col;
};

struct Compare {
    bool operator()(const MatrixElement& a, const MatrixElement& b) {
        return a.val > b.val; // min-heap
    }
};

int kthSmallest_MergeSort(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    priority_queue<MatrixElement, vector<MatrixElement>, Compare> minHeap;

    // Push the first element of each row into the min-heap
    for (int i = 0; i < n; ++i) {
        minHeap.push({matrix[i][0], i, 0});
    }

    MatrixElement result;
    for (int i = 0; i < k; ++i) {
        result = minHeap.top();
        minHeap.pop();

        int nextCol = result.col + 1;
        int row = result.row;
        if (nextCol < n) {
            // Push the next element from the same row
            minHeap.push({matrix[row][nextCol], row, nextCol});
        }
    }
    return result.val;
}

int main() {
    // Example sorted matrix
    vector<vector<int>> matrix = {
        {2,  6,  8},
        {7,  8,  10},
        {2,  5,  9}
    };
    int k = 5;

    cout << "Matrix:" << endl;
    printMatrix(matrix);
    cout << "k = " << k << endl;

    // Use a vector of function pointers for cleaner output
    vector<pair<string, int (*)(const vector<vector<int>>&, int)>> approaches = {
        {"Approach 1: Using Max Heap", kthSmallest_MaxHeap},
        {"Approach 2: Using Min Heap", kthSmallest_MinHeap},
        {"Approach 3: Binary Search", kthSmallest_BinarySearch},
        {"Approach 4: Optimized Binary Search", kthSmallest_OptimizedBinarySearch},
        {"Approach 5: Merge Sort Variation", kthSmallest_MergeSort}
    };

    // Print the results in a table format
    cout << "\nResults:\n";
    cout << "--------------------------------------------------\n";
    cout << "Approach                       | Result\n";
    cout << "--------------------------------------------------\n";
    for (const auto& approach : approaches) {
        cout << approach.first << " | " << approach.second(matrix, k) << endl;
    }
    cout << "--------------------------------------------------\n";

    return 0;
}

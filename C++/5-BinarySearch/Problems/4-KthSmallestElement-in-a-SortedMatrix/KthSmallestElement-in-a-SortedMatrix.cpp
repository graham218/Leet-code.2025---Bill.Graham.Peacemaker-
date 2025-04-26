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

// Approach 1: Using a Max Heap (Priority Queue)
// Time Complexity: O(k log k) -  We add at most k elements to the heap, and heap operations are O(log k).
// Space Complexity: O(k) - The heap stores at most k elements.
int kthSmallest_MaxHeap(const vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix.size() * matrix[0].size() < k) {
        return -1; // Handle invalid input
    }

    priority_queue<int> maxHeap; // Max heap to store the k smallest elements

    for (const auto& row : matrix) {
        for (int val : row) {
            maxHeap.push(val); // Add the current element to the heap
            if (maxHeap.size() > k) {
                maxHeap.pop(); // If the heap size exceeds k, remove the largest element
            }
        }
    }
    return maxHeap.top(); // The top of the max heap is the kth smallest element
}

// Approach 2: Using Binary Search
// Time Complexity: O(n log(maxVal - minVal)) where n is the number of rows/columns. Binary search on the range of values.
// Space Complexity: O(1) - Constant extra space.
int kthSmallest_BinarySearch(const vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix.size() * matrix[0].size() < k) {
        return -1; // Handle invalid input
    }

    int n = matrix.size();
    int low = matrix[0][0];         // Smallest element in the matrix
    int high = matrix[n - 1][n - 1]; // Largest element in the matrix

    while (low <= high) {
        int mid = low + (high - low) / 2; // Calculate the middle value
        int count = 0;                   // Count of elements less than or equal to mid

        // Count elements <= mid
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] <= mid) {
                    count++;
                }
                else
                {
                    break; //optimization, since each row is sorted.
                }
            }
        }

        if (count < k) {
            low = mid + 1; // If count is less than k, search in the higher range
        } else {
            high = mid - 1; // If count is greater than or equal to k, search in the lower range
        }
    }
    return low; // 'low' will eventually be the kth smallest element
}

// Approach 3: Using Merge Sort (Merging all rows)
// Time Complexity: O(N log N), where N is the total number of elements in the matrix (n*n).
// Space Complexity: O(N), for the merged array.
int kthSmallest_MergeSort(const vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix.size() * matrix[0].size() < k) {
        return -1;
    }

    vector<int> mergedArray;
    for (const auto& row : matrix) {
        mergedArray.insert(mergedArray.end(), row.begin(), row.end()); //copy all elements.
    }
    sort(mergedArray.begin(), mergedArray.end()); // Sort the merged array

    return mergedArray[k - 1]; // Return the (k-1)th element (0-based indexing)
}

// Approach 4: Optimized Binary Search (Efficient Counting)
// Time Complexity: O(n log(maxVal - minVal)), where n is the number of rows/columns.  Improved counting within the binary search.
// Space Complexity: O(1)
int kthSmallest_OptimizedBinarySearch(const vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix.size() * matrix[0].size() < k) {
        return -1;
    }

    int n = matrix.size();
    int low = matrix[0][0];
    int high = matrix[n - 1][n - 1];

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = 0;
        int j = n - 1; // Start from the last column

        for (int i = 0; i < n; ++i) {
            // For each row, find the rightmost element <= mid
            while (j >= 0 && matrix[i][j] > mid) {
                j--;
            }
            count += (j + 1); // Add the count of elements <= mid in this row
        }

        if (count < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// Approach 5: Using a Min Heap (Priority Queue) - Optimized for Sorted Matrix
// Time Complexity: O(k log n) -  We add at most k elements to the heap, and heap operations are O(log n).  n is the dimension of matrix.
// Space Complexity: O(n) - The heap stores at most n elements (one from each row).
int kthSmallest_MinHeap(const vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix.size() * matrix[0].size() < k) {
        return -1;
    }

    int n = matrix.size();
    // Use a min heap to store elements of the matrix.  The pair is (value, {row, col}).
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minHeap;

    // Push the first element of each row into the min heap.
    for (int i = 0; i < n; ++i) {
        minHeap.push({matrix[i][0], {i, 0}});
    }

    int count = 0;
    int result = 0;
    while (!minHeap.empty() && count < k) {
        pair<int, pair<int, int>> current = minHeap.top();
        minHeap.pop();
        result = current.first; // Get the smallest element
        count++;

        int row = current.second.first;
        int col = current.second.second;

        if (col + 1 < n) {
            // Push the next element from the same row into the heap
            minHeap.push({matrix[row][col + 1], {row, col + 1}});
        }
    }
    return result;
}

int main() {
    vector<vector<int>> matrix = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int k = 8;

    cout << "Matrix:" << endl;
    printMatrix(matrix);
    cout << "k = " << k << endl << endl;

    cout << "1. Using Max Heap: " << kthSmallest_MaxHeap(matrix, k) << endl;
    cout << "2. Using Binary Search: " << kthSmallest_BinarySearch(matrix, k) << endl;
    cout << "3. Using Merge Sort: " << kthSmallest_MergeSort(matrix, k) << endl;
    cout << "4. Using Optimized Binary Search: " << kthSmallest_OptimizedBinarySearch(matrix, k) << endl;
    cout << "5. Using Min Heap: " << kthSmallest_MinHeap(matrix, k) << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <numeric> // For std::partial_sum
#include <chrono>  // For timing execution
#include <random> // For generating random numbers

using namespace std;
using namespace std::chrono;

// Function to generate a random vector of integers
vector<int> generateRandomVector(int size, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}

// 1. Basic Prefix Sum
//   - Computes the prefix sum of a vector.
//   - Useful for: Preprocessing data for range queries (e.g., sum of elements in a given range).
//   - Real-world application: Calculating cumulative sales figures over time.
vector<int> prefixSumBasic(const vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    if (n == 0) return prefix; // Handle empty array case
    prefix[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    return prefix;
}

// 2. Prefix Sum with In-Place Modification
//   - Computes the prefix sum directly in the input vector, modifying it.
//   - Useful for: Situations where memory usage needs to be minimized, and the original array is no longer needed.
//   - Real-world application: Updating an array of resource counts to store cumulative counts, optimizing memory in embedded systems.
void prefixSumInPlace(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        arr[i] += arr[i - 1];
    }
    // No return needed, as the input vector is modified directly.
}

// 3. Prefix Sum using STL's partial_sum
//   - Uses the std::partial_sum algorithm from the C++ Standard Template Library.
//   - Useful for: Leveraging optimized and generic implementations provided by the STL.
//   - Real-world application: Calculating running totals in financial data analysis.
vector<int> prefixSumSTL(const vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    if (n == 0) return prefix;
    partial_sum(arr.begin(), arr.end(), prefix.begin());
    return prefix;
}

// 4. Prefix Sum for 2D Arrays (Matrix)
//   - Computes the prefix sum for each row in a 2D array (matrix).
//   - Useful for: Efficiently calculating the sum of elements within a submatrix.
//   - Real-world application: Image processing, where you need to calculate the sum of pixel intensities in a rectangular region.
vector<vector<int>> prefixSum2D(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return {};
    int cols = matrix[0].size();
    vector<vector<int>> prefix(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        prefix[i][0] = matrix[i][0];
        for (int j = 1; j < cols; ++j) {
            prefix[i][j] = prefix[i][j - 1] + matrix[i][j];
        }
    }
    return prefix;
}

// 5.  Prefix Sum with Range Queries
//   - Computes prefix sum and answers range sum queries efficiently.
//   - Useful for: Interactive applications where users repeatedly ask for the sum of elements within a specified range.
//   - Real-world application: Analyzing website traffic data, where you need to quickly find the number of visits within specific date ranges.
int rangeSumQuery(const vector<int>& prefixSum, int left, int right) {
    if (left == 0) {
        return prefixSum[right];
    } else {
        return prefixSum[right] - prefixSum[left - 1];
    }
}

int main() {
    // Example Usage
    vector<int> data = generateRandomVector(10, 1, 10); // Example data
    cout << "Original Data: ";
    for (int x : data) {
        cout << x << " ";
    }
    cout << endl;

    // 1. Basic Prefix Sum
    vector<int> prefixSum1 = prefixSumBasic(data);
    cout << "Basic Prefix Sum: ";
    for (int x : prefixSum1) {
        cout << x << " ";
    }
    cout << endl;

    // 2. Prefix Sum with In-Place Modification
    vector<int> data2 = data; // Create a copy to preserve original
    prefixSumInPlace(data2);
    cout << "In-Place Prefix Sum: ";
    for (int x : data2) {
        cout << x << " ";
    }
    cout << endl;

     // 3. Prefix Sum using STL's partial_sum
    vector<int> prefixSum3 = prefixSumSTL(data);
    cout << "STL Prefix Sum: ";
    for (int x : prefixSum3) {
        cout << x << " ";
    }
    cout << endl;

    // 4. Prefix Sum for 2D Arrays (Matrix)
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Original Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << endl;
    }
    vector<vector<int>> prefixSum2DMatrix = prefixSum2D(matrix);
    cout << "2D Prefix Sum Matrix:" << endl;
    for (const auto& row : prefixSum2DMatrix) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << endl;
    }

    // 5. Prefix Sum with Range Queries
    vector<int> prefixSum4 = prefixSumBasic(data); // Use basic for range queries
    int left = 2;
    int right = 5;
    int sumInRange = rangeSumQuery(prefixSum4, left, right);
    cout << "Sum in range [" << left << ", " << right << "]: " << sumInRange << endl;

    // Timing the execution of different methods.
    int numIterations = 100000;
    vector<int> largeData = generateRandomVector(1000, 1, 100); // Larger data set

    // Time basic prefix sum
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        prefixSumBasic(largeData);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time for Basic Prefix Sum (" << numIterations << " iterations): " << duration.count() << " microseconds" << endl;

    // Time in-place prefix sum
    start = high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        vector<int> temp = largeData; // Need a copy because in-place modifies
        prefixSumInPlace(temp);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time for In-Place Prefix Sum (" << numIterations << " iterations): " << duration.count() << " microseconds" << endl;

    // Time STL prefix sum
     start = high_resolution_clock::now();
      for (int i = 0; i < numIterations; ++i) {
        prefixSumSTL(largeData);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time for STL Prefix Sum (" << numIterations << " iterations): " << duration.count() << " microseconds" << endl;

    return 0;
}

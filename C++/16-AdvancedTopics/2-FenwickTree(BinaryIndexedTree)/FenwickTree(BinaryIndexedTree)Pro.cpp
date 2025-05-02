#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::lower_bound

// Approach 1: Basic Fenwick Tree (Using a vector)
// This approach uses a vector to represent the Fenwick Tree.  It's the most straightforward
// implementation, focusing on the core concepts of update and query.
class FenwickTree1 {
public:
    std::vector<int> tree; // The Fenwick Tree array
    int n;                   // Size of the input array

    // Constructor: Initializes the Fenwick Tree with the given size.
    FenwickTree1(int size) : n(size), tree(size + 1, 0) {} // 1-based indexing

    // Function to update the Fenwick Tree at a given index.
    // Adds 'val' to the element at index 'idx' and propagates the change to its ancestors.
    void update(int idx, int val) {
        // Index in Fenwick Tree is 1-based.
        while (idx <= n) {
            tree[idx] += val;
            idx += (idx & -idx); // Move to the parent in the tree
        }
    }

    // Function to calculate the prefix sum up to a given index.
    // Returns the sum of elements from index 1 to 'idx'.
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx); // Move to the next relevant node
        }
        return sum;
    }

     // Function to get the element at a given index
    int getElement(const std::vector<int>& arr, int idx) {
        if (idx < 1 || idx > n) {
            return 0; // Or throw an exception, depending on the desired behavior
        }
        return query(idx) - query(idx - 1);
    }

    // Function to set the element at a given index
    void setElement(const std::vector<int>& arr, int idx, int val) {
        if (idx < 1 || idx > n) {
             return; // Or throw an exception.
        }
        int currentVal = getElement(arr, idx);
        update(idx, val - currentVal); //update by the difference
    }
};

// Approach 2: Fenwick Tree with Range Updates (Lazy Propagation)
// This approach extends the basic Fenwick Tree to handle range updates efficiently.
// It uses an auxiliary tree to store the updates.  Note: This approach does *not*
// use lazy propagation in the traditional sense, but rather a difference array
// technique combined with two Fenwick Trees.
class FenwickTree2 {
public:
    std::vector<long long> tree1, tree2; // Two Fenwick Trees
    int n;

    FenwickTree2(int size) : n(size), tree1(size + 1, 0), tree2(size + 1, 0) {}

    // Function to update a range [l, r] with a value 'val'.
    // Uses two Fenwick Trees to handle the range update.
    void updateRange(int l, int r, long long val) {
        for (int i = l; i <= n; i += (i & -i)) {
            tree1[i] += val;
            tree2[i] += val * (l - 1);
        }
        for (int i = r + 1; i <= n; i += (i & -i)) {
            tree1[i] -= val;
            tree2[i] -= val * r;
        }
    }

    // Function to query the value at a single index 'idx'.
    // Calculates the value at 'idx' after applying all range updates.
    long long query(int idx) {
        long long sum = 0;
        int i = idx;
        while (i > 0) {
            sum += tree1[i] * idx - tree2[i];
            i -= (i & -i);
        }
        return sum;
    }
    // Function to get the element at a given index
    long long getElement(const std::vector<int>& arr, int idx) {
        if (idx < 1 || idx > n) {
            return 0;
        }
        return query(idx);
    }

     // Function to set the element at a given index
    void setElement(const std::vector<int>& arr, int idx, long long val) {
        if (idx < 1 || idx > n) {
            return;
        }
        long long currentVal = getElement(arr, idx);
        updateRange(idx, idx, val - currentVal);
    }
};

// Approach 3: Fenwick Tree with Templates (Generic Type)
// This approach uses C++ templates to make the Fenwick Tree work with any data type
// that supports addition.  This improves code reusability.
template <typename T>
class FenwickTree3 {
public:
    std::vector<T> tree;
    int n;

    FenwickTree3(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, T val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    T query(int idx) {
        T sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

     T getElement(const std::vector<T>& arr, int idx) {
        if (idx < 1 || idx > n) {
            return 0;
        }
        return query(idx) - query(idx - 1);
    }

    void setElement(const std::vector<T>& arr, int idx, T val) {
        if (idx < 1 || idx > n) {
             return;
        }
        T currentVal = getElement(arr, idx);
        update(idx, val - currentVal);
    }
};

// Approach 4: Fenwick Tree for Minimum Queries
// This variation of the Fenwick Tree is adapted to handle minimum range queries
// instead of sum queries.  It requires the operation to be associative.
// Note:  This approach has limitations.  Standard Fenwick Trees are best suited
// for sum queries.  For general minimum range queries, segment trees are usually preferred.
// This approach works for cases where updates are only decreasing.
class FenwickTree4 {
public:
    std::vector<int> tree;
    int n;
    const int INF = 1e9; // Represents infinity, used for minimum

    FenwickTree4(int size) : n(size), tree(size + 1, INF) {}

    void update(int idx, int val) {
        while (idx <= n) {
            tree[idx] = std::min(tree[idx], val); // Changed to min
            idx += (idx & -idx);
        }
    }

    int query(int idx) {
        int minVal = INF; // Initialize with infinity
        while (idx > 0) {
            minVal = std::min(minVal, tree[idx]); // Changed to min
            idx -= (idx & -idx);
        }
        return minVal;
    }
    int getElement(const std::vector<int>& arr, int idx) {
        if (idx < 1 || idx > n) {
            return 0;
        }
        int result = query(idx);
        // To get the element, we need to find the minimum in the range [1,idx]
        // excluding the minimum in the range [1,idx-1]. This is tricky with min queries
        // and a Fenwick Tree.  For simplicity, we'll return the minimum directly.
        //  This assumes that the updates are only decreasing.  If updates can increase
        //  you cannot accurately get the value of a single element with a Min Fenwick Tree.
        if(idx > 1){
           result = std::min(result, arr[idx-1]); //comparing with the previous element.
        }
        return result;
    }

    void setElement(const std::vector<int>& arr, int idx, int val) {
        if (idx < 1 || idx > n) {
            return;
        }
        //  It's complex to directly "set" an element in a Min Fenwick Tree
        //  without rebuilding part of the tree.  For simplicity, we'll update
        //  the Fenwick Tree with the new value, but this assumes that all
        //  previous values at this index were greater than or equal to the new value.
        //  If not, the tree will not reflect the correct minimum.
        update(idx, val);
    }
};

// Approach 5: 2D Fenwick Tree
//  This approach implements a 2D Fenwick Tree, which can be used to efficiently
//  handle queries and updates on a 2D grid.
class FenwickTree2D {
public:
    std::vector<std::vector<int>> tree;
    int n, m; // Dimensions of the 2D grid

    FenwickTree2D(int rows, int cols) : n(rows), m(cols), tree(rows + 1, std::vector<int>(cols + 1, 0)) {}

    void update(int row, int col, int val) {
        for (int i = row; i <= n; i += (i & -i)) {
            for (int j = col; j <= m; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    int query(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= (i & -i)) {
            for (int j = col; j > 0; j -= (j & -j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // Function to get the element at a given index
    int getElement(const std::vector<std::vector<int>>& arr, int row, int col) {
        if (row < 1 || row > n || col < 1 || col > m) {
            return 0;
        }
        return query(row, col) - query(row - 1, col) - query(row, col - 1) + query(row - 1, col - 1);
    }

    // Function to set the element at a given index
    void setElement(const std::vector<std::vector<int>>& arr, int row, int col, int val) {
        if (row < 1 || row > n || col < 1 || col > m) {
            return;
        }
        int currentVal = getElement(arr, row, col);
        update(row, col, val - currentVal);
    }
};

int main() {
    // Example Usage
    std::cout << "Example Usage of Fenwick Tree Approaches\n";
    std::cout << "----------------------------------------\n";

    // Approach 1: Basic Fenwick Tree
    std::cout << "\nApproach 1: Basic Fenwick Tree\n";
    int n1 = 5;
    FenwickTree1 ft1(n1);
    std::vector<int> arr1 = {0, 1, 2, 3, 4, 5}; // 1-based indexing is assumed
    for (int i = 1; i <= n1; ++i) {
        ft1.update(i, arr1[i]);
    }
    std::cout << "Sum of first 3 elements: " << ft1.query(3) << std::endl; // Output: 6
    std::cout << "Element at index 2: " << ft1.getElement(arr1, 2) << std::endl; //2
    ft1.setElement(arr1, 2, 10);
    std::cout << "Element at index 2 after update: " << ft1.getElement(arr1, 2) << std::endl; //10
    std::cout << "Sum of first 3 elements after update: " << ft1.query(3) << std::endl; // 14

    // Approach 2: Fenwick Tree with Range Updates
    std::cout << "\nApproach 2: Fenwick Tree with Range Updates\n";
    int n2 = 5;
    FenwickTree2 ft2(n2);
    std::vector<int> arr2 = {0, 1, 2, 3, 4, 5};
     for (int i = 1; i <= n2; ++i) {
        ft2.updateRange(i, i, arr2[i]); // Initialize the tree
    }
    ft2.updateRange(2, 4, 3); // Add 3 to elements from index 2 to 4
    std::cout << "Value at index 3: " << ft2.query(3) << std::endl; // Output: 8 (3 + 3 + 2)
    std::cout << "Element at index 3: " << ft2.getElement(arr2, 3) << std::endl;
    ft2.setElement(arr2, 3, 12);
    std::cout << "Element at index 3 after set: " << ft2.getElement(arr2, 3) << std::endl;

    // Approach 3: Fenwick Tree with Templates
    std::cout << "\nApproach 3: Fenwick Tree with Templates\n";
    int n3 = 5;
    FenwickTree3<double> ft3(n3); // Using double
    std::vector<double> arr3 = {0, 1.5, 2.5, 3.5, 4.5, 5.5};
    for (int i = 1; i <= n3; ++i) {
        ft3.update(i, arr3[i]);
    }
    std::cout << "Sum of first 4 elements: " << ft3.query(4) << std::endl; // Output: 12
    std::cout << "Element at index 4: " << ft3.getElement(arr3, 4) << std::endl;
    ft3.setElement(arr3, 4, 10.5);
    std::cout << "Element at index 4 after set: " << ft3.getElement(arr3, 4) << std::endl;

    // Approach 4: Fenwick Tree for Minimum Queries
    std::cout << "\nApproach 4: Fenwick Tree for Minimum Queries\n";
    int n4 = 5;
    FenwickTree4 ft4(n4);
    std::vector<int> arr4 = {0, 5, 2, 8, 1, 9};
    for (int i = 1; i <= n4; ++i) {
        ft4.update(i, arr4[i]);
    }
    std::cout << "Minimum of first 4 elements: " << ft4.query(4) << std::endl; // Output: 1
    std::cout << "Element at index 4: " << ft4.getElement(arr4, 4) << std::endl;
    ft4.setElement(arr4, 4, 0);
    std::cout << "Element at index 4 after set: " << ft4.getElement(arr4, 4) << std::endl;

    // Approach 5: 2D Fenwick Tree
    std::cout << "\nApproach 5: 2D Fenwick Tree\n";
    int n5 = 3, m5 = 3;
    FenwickTree2D ft5(n5, m5);
    std::vector<std::vector<int>> arr5 = {
        {0, 0, 0, 0},
        {0, 1, 2, 3},
        {0, 4, 5, 6},
        {0, 7, 8, 9}
    };
    for (int i = 1; i <= n5; ++i) {
        for (int j = 1; j <= m5; ++j) {
            ft5.update(i, j, arr5[i][j]);
        }
    }
    std::cout << "Sum of submatrix (1,1) to (2,2): " << ft5.query(2, 2) << std::endl; // Output: 12
     std::cout << "Element at (2,2): " << ft5.getElement(arr5, 2, 2) << std::endl;
    ft5.setElement(arr5, 2, 2, 10);
    std::cout << "Element at (2,2) after update: " << ft5.getElement(arr5, 2, 2) << std::endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <numeric> // For std::iota
#include <algorithm> // For std::partial_sum
#include <random> // For generating test data
#include <chrono> // For performance measurement

// Namespace to encapsulate Fenwick Tree implementations
namespace FenwickTree {

    /**
     * @brief Base class for Fenwick Tree implementations.
     * Provides common utility functions.
     */
    class BaseFenwickTree {
    protected:
        // Helper function to get the parent of an index in the Fenwick Tree
        int parent(int index) {
            return index & (index - 1);
        }

        // Helper function to get the next index to update in the Fenwick Tree
        int next(int index) {
            return index + (index & -index);
        }
    };

    /**
     * @brief Approach 1: Basic Fenwick Tree (Binary Indexed Tree)
     *
     * This is the standard implementation of a Fenwick Tree, supporting
     * point updates and range queries (prefix sums).
     *
     * Real-world application:
     * -   Real-time analytics:  Calculating cumulative metrics (e.g., website traffic,
     * sales figures) over a sliding window.  Fast updates when new data arrives,
     * and fast queries for the current cumulative value.
     */
    class BasicFenwickTree : public BaseFenwickTree {
    public:
        std::vector<int> tree; // The Fenwick Tree array

        /**
         * @brief Constructor for the BasicFenwickTree.
         * @param size The size of the input array (not the size of the tree).
         */
        BasicFenwickTree(int size) : tree(size + 1, 0) {} // 1-based indexing

        /**
         * @brief Adds a value to a specific element in the original array.
         * This updates the Fenwick Tree to reflect the change.
         * @param index The index of the element to update (1-based).
         * @param value The value to add to the element.
         */
        void update(int index, int value) {
            while (index < tree.size()) {
                tree[index] += value;
                index = next(index);
            }
        }

        /**
         * @brief Calculates the prefix sum up to a given index.
         * @param index The index up to which to calculate the sum (1-based).
         * @return The sum of the elements from index 1 to index 'index'.
         */
        int query(int index) {
            int sum = 0;
            while (index > 0) {
                sum += tree[index];
                index = parent(index);
            }
            return sum;
        }

        /**
         * @brief Builds the Fenwick Tree from an input array.
         * This is an alternative to performing individual updates.  More efficient
         * for initializing the tree with a known array.
         * @param array The input array (0-based).  The tree will be sized based on this.
         */
        void build(const std::vector<int>& array) {
            tree.assign(array.size() + 1, 0); // Resize and reset the tree
            for (size_t i = 0; i < array.size(); ++i) {
                for (int j = i + 1; j <= array.size(); j = next(j)) {
                    tree[j] += array[i];
                }
            }
        }
    };

    /**
     * @brief Approach 2: Fenwick Tree for Range Queries and Point Updates
     *
     * This implementation supports range queries (sum of elements in a range)
     * and point updates (modifying a single element).  It uses two Fenwick Trees.
     *
     * Real-world application:
     * -   Database systems:  Efficiently handling range queries and single-record updates
     * in a database table. For example, calculating the sum of sales for a product
     * within a specific date range, and updating the sales figure for a single day.
     */
    class RangeQueryPointUpdateFT : public BaseFenwickTree {
    public:
        std::vector<int> tree1; // First Fenwick Tree
        std::vector<int> tree2; // Second Fenwick Tree
        int n;

        /**
         * @brief Constructor for the RangeQueryPointUpdateFT.
         * @param size The size of the input array.
         */
        RangeQueryPointUpdateFT(int size) : n(size), tree1(size + 1, 0), tree2(size + 1, 0) {}

        /**
         * @brief Updates a single element in the array.
         * @param index The index of the element to update (1-based).
         * @param value The new value of the element.
         */
        void update(int index, int value) {
            int prev_value = query(index, index); // Get previous value to calculate the difference.
            int diff = value - prev_value;
            updateRange(index, n, diff);
        }

        /**
         * @brief Updates a range of elements (adds 'value' to elements in the range).
         * @param index The starting index of the range (1-based).
         * @param value The value to add to the elements in the range.
         */
        void updateRange(int index, int end, int value) {
            while (index <= n) {
                tree1[index] += value;
                tree2[index] -= value * (index - 1);
                index = next(index);
            }
        }

        /**
         * @brief Queries the sum of elements in a given range [1, index].
         * @param index The ending index of the range (1-based).
         * @return The sum of the elements in the range.
         */
        int query(int index) {
            int sum = 0;
            int originalIndex = index; // Store original index for tree2
            while (index > 0) {
                sum += tree1[index] * originalIndex + tree2[index];
                index = parent(index);
            }
            return sum;
        }

        /**
         * @brief Queries the sum of elements in the range [left, right].
         * @param left The starting index of the range (1-based).
         * @param right The ending index of the range (1-based).
         * @return The sum of the elements in the range [left, right].
         */
        int query(int left, int right) {
            return query(right) - query(left - 1);
        }
    };

    /**
     * @brief Approach 3: Fenwick Tree for Range Updates and Point Queries
     *
     * This implementation supports range updates (adding a value to a range of
     * elements) and point queries (retrieving the value of a single element).
     * It also uses two Fenwick Trees.
     *
     * Real-world application:
     * -   Graphics rendering:  Updating the color or other attributes of a range of pixels
     * on a screen, and then querying the attribute of a specific pixel.
     */
    class RangeUpdatePointQueryFT : public BaseFenwickTree {
    public:
        std::vector<int> tree1; // First Fenwick Tree
        std::vector<int> tree2; // Second Fenwick Tree
        int n;

        /**
         * @brief Constructor
         * @param size The size of the input array.
         */
        RangeUpdatePointQueryFT(int size) : n(size), tree1(size + 1, 0), tree2(size + 1, 0) {}

        /**
         * @brief Updates the values in the given range.
         * @param left The starting index of the range (1-based).
         * @param right The ending index of the range (1-based).
         * @param value The value to add to the elements in the range.
         */
        void update(int left, int right, int value) {
            updateRange(left, value);
            updateRange(right + 1, -value);
        }

        /**
        * @brief Helper function to update a range
        * @param index The index to start the update
        * @param value The value to update by
        */
        void updateRange(int index, int value) {
            while (index <= n) {
                tree1[index] += value;
                tree2[index] += value * index;
                index = next(index);
            }
        }

        /**
         * @brief Queries the value at a single index.
         * @param index The index to query (1-based).
         * @return The value of the element at the given index.
         */
        int query(int index) {
            int sum = 0;
            int originalIndex = index;
            while (index > 0) {
                sum += tree1[index] * originalIndex - tree2[index];
                index = parent(index);
            }
            return sum;
        }
    };

    /**
     * @brief Approach 4: 2D Fenwick Tree for Range Queries and Point Updates
     *
     * This implementation extends the Fenwick Tree to two dimensions, supporting
     * range queries and point updates in a 2D grid.
     *
     * Real-world application:
     * -   Image processing:  Calculating the sum of pixel intensities in a rectangular
     * region of an image, and updating the intensity of a single pixel.
     */
    class FenwickTree2D {
    public:
        std::vector<std::vector<int>> tree; // The 2D Fenwick Tree
        int rows;
        int cols;

        /**
         * @brief Constructor for the 2D Fenwick Tree.
         * @param numRows The number of rows in the grid.
         * @param numCols The number of columns in the grid.
         */
        FenwickTree2D(int numRows, int numCols) : rows(numRows), cols(numCols), tree(numRows + 1, std::vector<int>(numCols + 1, 0)) {}

        /**
         * @brief Updates the value of a single cell in the 2D grid.
         * @param row The row index of the cell (1-based).
         * @param col The column index of the cell (1-based).
         * @param value The value to add to the cell.
         */
        void update(int row, int col, int value) {
            for (int i = row; i <= rows; i += (i & -i)) {
                for (int j = col; j <= cols; j += (j & -j)) {
                    tree[i][j] += value;
                }
            }
        }

        /**
         * @brief Queries the sum of values in the rectangle from (1, 1) to (row, col).
         * @param row The row index of the bottom-right corner of the rectangle (1-based).
         * @param col The column index of the bottom-right corner of the rectangle (1-based).
         * @return The sum of the values in the rectangle.
         */
        int query(int row, int col) {
            int sum = 0;
            for (int i = row; i > 0; i -= (i & -i)) {
                for (int j = col; j > 0; j -= (j & -j)) {
                    sum += tree[i][j];
                }
            }
            return sum;
        }

        /**
         * @brief Queries the sum of values in the rectangle defined by (row1, col1) and (row2, col2).
         * @param row1 The row index of the top-left corner of the rectangle (1-based).
         * @param col1 The column index of the top-left corner of the rectangle (1-based).
         * @param row2 The row index of the bottom-right corner of the rectangle (1-based).
         * @param col2 The column index of the bottom-right corner of the rectangle (1-based).
         * @return The sum of the values in the rectangle.
         */
        int query(int row1, int col1, int row2, int col2) {
            return query(row2, col2) - query(row1 - 1, col2) - query(row2, col1 - 1) + query(row1 - 1, col1 - 1);
        }
    };

    /**
     * Approach 5: Fenwick Tree to find the k-th smallest element
     *
     * This implementation uses a Fenwick tree to efficiently find the k-th
     * smallest element in a dynamic set of numbers.  The Fenwick tree
     * stores the frequency of each number.  This approach assumes the numbers
     * are within a reasonable range (here, 0 to MAX_VALUE).
     *
     * Real-world application:
     * -   Online gaming:  Tracking player rankings in real-time.  When a player's
     * score changes, their rank needs to be updated, and we might want to
     * quickly find the k-th highest scorer.
     */
    class KthSmallestFinder {
    public:
        static const int MAX_VALUE = 100000; // Maximum possible value (adjust as needed)
        std::vector<int> tree;             // Fenwick Tree storing frequencies

        /**
         * @brief Constructor.
         */
        KthSmallestFinder() : tree(MAX_VALUE + 1, 0) {}

        /**
         * @brief Adds a number to the set (or increments its frequency).
         * @param number The number to add.
         */
        void add(int number) {
            update(number, 1);
        }

        /**
         * @brief Removes a number from the set (or decrements its frequency).
         * @param number The number to remove.
         */
        void remove(int number) {
            update(number, -1);
        }

        /**
         * @brief Finds the k-th smallest element.
         * @param k The desired rank (1-based).
         * @return The k-th smallest element, or -1 if k is invalid.
         */
        int findKthSmallest(int k) {
            if (k <= 0 || k > query(MAX_VALUE)) {
                return -1; // Invalid k
            }

            int low = 0, high = MAX_VALUE;
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (query(mid) < k) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
            return low;
        }

    private:
        /**
         * @brief Updates the Fenwick Tree.
         * @param index The index to update (number itself).
         * @param value The value to add (frequency change).
         */
        void update(int index, int value) {
            while (index <= MAX_VALUE) {
                tree[index] += value;
                index += (index & -index);
            }
        }

        /**
         * @brief Queries the prefix sum (cumulative frequency).
         * @param index The index to query.
         * @return The sum of frequencies up to 'index'.
         */
        int query(int index) {
            int sum = 0;
            while (index > 0) {
                sum += tree[index];
                index -= (index & -index);
            }
            return sum;
        }
    };
} // namespace FenwickTree

// Function to generate a random array of a given size
std::vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
    return arr;
}

// Function to test the performance of the Fenwick Tree
void testFenwickTreePerformance(int size, int numQueries) {
    // Generate a random array
    std::vector<int> array = generateRandomArray(size, 1, 1000);

    // Initialize the Fenwick Tree
    FenwickTree::BasicFenwickTree ft(size);
    ft.build(array); // Build the tree from the array

    // Generate random queries (updates and sums)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> indexDist(1, size);
    std::uniform_int_distribution<> valueDist(1, 100);

    // Measure the execution time of the queries
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numQueries; ++i) {
        // Randomly choose between update and query
        if (std::rand() % 2 == 0) {
            // Update a random element
            int index = indexDist(gen);
            int value = valueDist(gen);
            ft.update(index, value);
        } else {
            // Query a random prefix sum
            int index = indexDist(gen);
            ft.query(index);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Fenwick Tree (Basic) Performance Test:\n";
    std::cout << "Array size: " << size << "\n";
    std::cout << "Number of queries: " << numQueries << "\n";
    std::cout << "Execution time: " << duration.count() << " seconds\n";
    std::cout << std::endl;
}

// Function to test the correctness of the RangeQueryPointUpdateFT
void testRangeQueryPointUpdate() {
    std::cout << "Testing RangeQueryPointUpdateFT...\n";
    std::vector<int> initialArray = {1, 2, 3, 4, 5};
    int n = initialArray.size();
    FenwickTree::RangeQueryPointUpdateFT ft(n);
    // Initialize Fenwick Tree.  Important:  The Fenwick Tree is initialized empty.
    // You must use update() to set initial values.
    for (int i = 0; i < n; ++i) {
        ft.update(i + 1, initialArray[i]); // Add each element of initialArray
    }

    // Test point update and range query
    ft.update(2, 10); // Update the 2nd element to 10 (originally 2).
    std::cout << "Sum[1, 2]: " << ft.query(1, 2) << " (Expected: 11)\n"; // 1 + 10 = 11
    std::cout << "Sum[2, 4]: " << ft.query(2, 4) << " (Expected: 10 + 3 + 4 = 17)\n";

    // Test range update and range query
    ft.updateRange(1, 3, 2); // Add 2 to elements from index 1 to 3.
    std::cout << "Sum[1, 3]: " << ft.query(1, 3) << " (Expected: 3 + 12 + 5 = 20)\n"; // (1+2) + (10+2) + (3+2)

    // Test single element query after range update
    std::cout << "Value at index 2: " << ft.query(2,2) << " (Expected 12)\n";

    std::cout << "RangeQueryPointUpdateFT test complete.\n\n";
}

// Function to test RangeUpdatePointQueryFT
void testRangeUpdatePointQuery() {
    std::cout << "Testing RangeUpdatePointQueryFT...\n";

    // Initialize with an example array (implicitly {1, 2, 3, 4, 5})
    FenwickTree::RangeUpdatePointQueryFT ft(5);

    // Initial state (all zeros, because we didn't use build)
    std::cout << "Initial value at index 1: " << ft.query(1) << " (Expected 0)\n";
    std::cout << "Initial value at index 3: " << ft.query(3) << " (Expected 0)\n";


    // Range update [2, 4] by adding 3.  Now the implicit array is {0, 3, 3, 3, 0}
    ft.update(2, 4, 3);
    std::cout << "Value at index 1 after range update: " << ft.query(1) << " (Expected 0)\n";
    std::cout << "Value at index 2 after range update: " << ft.query(2) << " (Expected 3)\n";
    std::cout << "Value at index 3 after range update: " << ft.query(3) << " (Expected 3)\n";
    std::cout << "Value at index 4 after range update: " << ft.query(4) << " (Expected 3)\n";
    std::cout << "Value at index 5 after range update: " << ft.query(5) << " (Expected 0)\n";


    // Another range update: Add -1 to [1, 3].  Array becomes {-1, 2, 2, 3, 0}
    ft.update(1, 3, -1);
    std::cout << "Value at index 1 after second update: " << ft.query(1) << " (Expected -1)\n";
    std::cout << "Value at index 2 after second update: " << ft.query(2) << " (Expected 2)\n";
    std::cout << "Value at index 3 after second update: " << ft.query(3) << " (Expected 2)\n";
    std::cout << "Value at index 4 after second update: " << ft.query(4) << " (Expected 3)\n";
    std::cout << "Value at index 5 after second update: " << ft.query(5) << " (Expected 0)\n";

    std::cout << "RangeUpdatePointQueryFT test complete.\n\n";
}

// Function to test the 2D Fenwick Tree
void testFenwickTree2D() {
    std::cout << "Testing FenwickTree2D...\n";
    FenwickTree::FenwickTree2D ft(4, 5); // 4 rows, 5 columns

    // Initial state (all zeros)
    std::cout << "Sum[1,1,2,2]: " << ft.query(1, 1, 2, 2) << " (Expected 0)\n";

    // Update some cells
    ft.update(1, 1, 1);
    ft.update(2, 2, 2);
    ft.update(3, 3, 3);
    ft.update(4, 4, 4);
    ft.update(4, 5, 5);

    // Test queries
    std::cout << "Sum[1,1,4,5]: " << ft.query(1, 1, 4, 5) << " (Expected 15)\n"; // 1 + 2 + 3 + 4 + 5
    std::cout << "Sum[1,1,2,2]: " << ft.query(1, 1, 2, 2) << " (Expected 3)\n";     // 1 + 2
    std::cout << "Sum[3,3,4,4]: " << ft.query(3, 3, 4, 4) << " (Expected 7)\n";     // 3 + 4
    std::cout << "Sum[1,2,4,5]: " << ft.query(1, 2, 4, 5) << " (Expected 14)\n";

    // Test update and query
    ft.update(2, 2, -1); // Change (2,2) from 2 to 1
    std::cout << "Sum[1,1,4,5]: " << ft.query(1, 1, 4, 5) << " (Expected 14)\n"; // 1 + 1 + 3 + 4 + 5
    std::cout << "Sum[1,1,2,2]: " << ft.query(1, 1, 2, 2) << " (Expected 2)\n";
    std::cout << "Sum[2,2,2,2]: " << ft.query(2, 2, 2, 2) << " (Expected 1)\n";

    std::cout << "FenwickTree2D test complete.\n\n";
}

// Function to test KthSmallestFinder
void testKthSmallestFinder() {
    std::cout << "Testing KthSmallestFinder...\n";
    FenwickTree::KthSmallestFinder finder;

    // Add elements
    finder.add(5);
    finder.add(2);
    finder.add(8);
    finder.add(2);
    finder.add(10);
    finder.add(1);

    // Find k-th smallest
    std::cout << "1st smallest: " << finder.findKthSmallest(1) << " (Expected 1)\n";
    std::cout << "2nd smallest: " << finder.findKthSmallest(2) << " (Expected 2)\n";
    std::cout << "3rd smallest: " << finder.findKthSmallest(3) << " (Expected 2)\n";
    std::cout << "4th smallest: " << finder.findKthSmallest(4) << " (Expected 5)\n";
    std::cout << "5th smallest: " << finder.findKthSmallest(5) << " (Expected 8)\n";
    std::cout << "6th smallest: " << finder.findKthSmallest(6) << " (Expected 10)\n";
    std::cout << "7th smallest: " << finder.findKthSmallest(7) << " (Expected -1)\n"; // Out of bounds

    // Remove an element and find k-th smallest
    finder.remove(2);
    std::cout << "2nd smallest after removing 2: " << finder.findKthSmallest(2) << " (Expected 2)\n";
    std::cout << "3rd smallest after removing 2: " << finder.findKthSmallest(3) << " (Expected 5)\n";

    // Add more elements
    finder.add(3);
    finder.add(7);
    std::cout << "3rd smallest after adding 3 and 7: " << finder.findKthSmallest(3) << " (Expected 3)\n";
    std::cout << "4th smallest after adding 3 and 7: " << finder.findKthSmallest(4) << " (Expected 5)\n";
    std::cout << "KthSmallestFinder test complete.\n\n";
}

int main() {
    // Test the performance of the basic Fenwick Tree
    testFenwickTreePerformance(100000, 1000000); // Large values for meaningful measurement

    // Test the correctness of the RangeQueryPointUpdateFT
    testRangeQueryPointUpdate();

    // Test the correctness of the RangeUpdatePointQueryFT
    testRangeUpdatePointQuery();

    // Test the 2D Fenwick Tree
    testFenwickTree2D();

    // Test KthSmallestFinder
    testKthSmallestFinder();

    return 0;
}

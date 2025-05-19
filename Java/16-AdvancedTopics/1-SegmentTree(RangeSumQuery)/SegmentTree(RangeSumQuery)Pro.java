import java.util.Arrays;

// Class to demonstrate Segment Tree implementations
public class SegmentTree {

    // Main method to run and test the Segment Tree implementations
    public static void main(String[] args) {
        int[] arr = {1, 3, 5, 7, 9, 11}; // Sample input array

        // 1. Basic Segment Tree (Array Representation)
        System.out.println("1. Basic Segment Tree (Array Representation):");
        BasicSegmentTree basicTree = new BasicSegmentTree(arr);
        basicTree.buildTree(0, 0, arr.length - 1);
        System.out.println("Sum in range [1, 3]: " + basicTree.query(0, 0, arr.length - 1, 1, 3)); // Expected: 15
        basicTree.update(0, 0, arr.length - 1, 1, 10); // Update element at index 1 to 10
        System.out.println("Sum in range [1, 3] after update: " + basicTree.query(0, 0, arr.length - 1, 1, 3)); // Expected: 22
        System.out.println();

        // 2. Segment Tree with Lazy Propagation
        System.out.println("2. Segment Tree with Lazy Propagation:");
        LazySegmentTree lazyTree = new LazySegmentTree(arr);
        lazyTree.buildTree(0, 0, arr.length - 1);
        System.out.println("Sum in range [2, 4]: " + lazyTree.query(0, 0, arr.length - 1, 2, 4)); // Expected: 21
        lazyTree.updateRange(0, 0, arr.length - 1, 2, 4, 2); // Add 2 to elements in range [2, 4]
        System.out.println("Sum in range [2, 4] after update: " + lazyTree.query(0, 0, arr.length - 1, 2, 4)); // Expected: 27
        System.out.println();

        // 3. Segment Tree using Class
        System.out.println("3. Segment Tree using Class:");
        SegmentTreeClass treeClass = new SegmentTreeClass(arr);
        System.out.println("Sum in range [0, 2]: " + treeClass.rangeSumQuery(0, 2));
        treeClass.update(1, 2);
        System.out.println("Sum in range [0, 2] after update: " + treeClass.rangeSumQuery(0, 2));
        System.out.println();

        // 4.  Segment Tree for Minimum Range Query
        System.out.println("4. Segment Tree for Minimum Range Query:");
        MinRangeQuerySegmentTree minRangeTree = new MinRangeQuerySegmentTree(arr);
        minRangeTree.buildTree(0, 0, arr.length - 1);
        System.out.println("Minimum in range [1, 4]: " + minRangeTree.query(0, 0, arr.length - 1, 1, 4));
        minRangeTree.update(0, 0, arr.length - 1, 3, 2);
        System.out.println("Minimum in range [1, 4] after update: " + minRangeTree.query(0, 0, arr.length - 1, 1, 4));
        System.out.println();

        // 5. Segment Tree with Non-Recursive Query
        System.out.println("5. Segment Tree with Non-Recursive Query:");
        NonRecursiveSegmentTree nonRecTree = new NonRecursiveSegmentTree(arr);
        System.out.println("Sum in range [1, 3]: " + nonRecTree.rangeSumQuery(1, 3));
        nonRecTree.update(1, 10);
        System.out.println("Sum in range [1, 3] after update: " + nonRecTree.rangeSumQuery(1, 3));
    }

    // 1. Basic Segment Tree Implementation (Array Representation)
    //    - Uses a simple array to store the segment tree.
    //    - Suitable for static arrays where updates are infrequent.
    //    - Real-world application: Simple data analysis where you need to quickly query sums
    //      over different ranges of data, and the underlying data doesn't change often.
    static class BasicSegmentTree {
        int[] tree;
        int[] arr; // Store the original array

        public BasicSegmentTree(int[] arr) {
            this.arr = arr;
            tree = new int[4 * arr.length]; // Allocate memory for the segment tree.  Size is 4*n in the worst case
        }

        // Builds the segment tree recursively
        void buildTree(int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start]; // Leaf node stores the array element
            } else {
                int mid = (start + end) / 2;
                buildTree(2 * node + 1, start, mid); // Build left subtree
                buildTree(2 * node + 2, mid + 1, end); // Build right subtree
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Internal node stores the sum
            }
        }

        // Performs a range sum query
        int query(int node, int start, int end, int left, int right) {
            if (right < start || end < left) {
                return 0; // Range is outside the query range
            }
            if (left <= start && end <= right) {
                return tree[node]; // Range is completely inside the query range
            }
            int mid = (start + end) / 2;
            int leftSum = query(2 * node + 1, start, mid, left, right); // Query left subtree
            int rightSum = query(2 * node + 2, mid + 1, end, left, right); // Query right subtree
            return leftSum + rightSum; // Return the sum of the two halves
        }

        // Updates a single element in the array and the segment tree
        void update(int node, int start, int end, int index, int value) {
            if (start == end) {
                arr[index] = value; // Update the original array
                tree[node] = value; // Update the leaf node
            } else {
                int mid = (start + end) / 2;
                if (index <= mid) {
                    update(2 * node + 1, start, mid, index, value); // Update in left subtree
                } else {
                    update(2 * node + 2, mid + 1, end, index, value); // Update in right subtree
                }
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Update the sum in the internal node
            }
        }
    }

    // 2. Segment Tree with Lazy Propagation
    //    - Efficiently handles range updates (e.g., add a value to all elements in a range).
    //    - Uses a 'lazy' array to store pending updates.
    //    - Real-world application: Processing a large number of range updates
    //      in a data warehousing scenario, such as updating prices for a range of products.
    static class LazySegmentTree {
        int[] tree;
        int[] lazy;
        int[] arr;

        public LazySegmentTree(int[] arr) {
            this.arr = arr;
            tree = new int[4 * arr.length];
            lazy = new int[4 * arr.length];
        }

        void buildTree(int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                int mid = (start + end) / 2;
                buildTree(2 * node + 1, start, mid);
                buildTree(2 * node + 2, mid + 1, end);
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
            }
        }

        // Propagates the lazy value to the children nodes
        void propagate(int node, int start, int end) {
            if (lazy[node] != 0) {
                tree[node] += (end - start + 1) * lazy[node]; // Update the current node

                if (start != end) {
                    lazy[2 * node + 1] += lazy[node]; // Update left child's lazy value
                    lazy[2 * node + 2] += lazy[node]; // Update right child's lazy value
                }
                lazy[node] = 0; // Clear the lazy value
            }
        }

        int query(int node, int start, int end, int left, int right) {
            propagate(node, start, end); // Propagate lazy values before query

            if (right < start || end < left) {
                return 0;
            }
            if (left <= start && end <= right) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            int leftSum = query(2 * node + 1, start, mid, left, right);
            int rightSum = query(2 * node + 2, mid + 1, end, left, right);
            return leftSum + rightSum;
        }

        void updateRange(int node, int start, int end, int left, int right, int value) {
            propagate(node, start, end); // Propagate lazy values before update

            if (right < start || end < left) {
                return;
            }
            if (left <= start && end <= right) {
                lazy[node] += value; // Update the lazy value for the current node
                propagate(node, start, end);     // Propagate immediately after updating lazy
                return;
            }
            int mid = (start + end) / 2;
            updateRange(2 * node + 1, start, mid, left, right, value);
            updateRange(2 * node + 2, mid + 1, end, left, right, value);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    // 3. Segment Tree Implementation using Class
    //    - Encapsulates the segment tree logic within a class for better organization.
    //    - Uses a node class to represent nodes in the segment tree.
    //  - Real world application: Building a reusable component for a library or framework.
    static class SegmentTreeClass {
        class Node {
            int sum;
            int start, end;
            Node left, right;

            public Node(int start, int end) {
                this.start = start;
                this.end = end;
                this.sum = 0;
            }
        }

        Node root;
        int[] arr;

        public SegmentTreeClass(int[] arr) {
            this.arr = arr;
            this.root = buildTree(0, arr.length - 1);
        }

        Node buildTree(int start, int end) {
            if (start == end) {
                Node node = new Node(start, end);
                node.sum = arr[start];
                return node;
            }
            int mid = (start + end) / 2;
            Node left = buildTree(start, mid);
            Node right = buildTree(mid + 1, end);
            Node node = new Node(start, end);
            node.left = left;
            node.right = right;
            node.sum = left.sum + right.sum;
            return node;
        }

        int rangeSumQuery(int left, int right) {
            return rangeSumQuery(root, left, right);
        }

        int rangeSumQuery(Node node, int left, int right) {
            if (node.start > right || node.end < left) {
                return 0;
            }
            if (node.start >= left && node.end <= right) {
                return node.sum;
            }
            return rangeSumQuery(node.left, left, right) + rangeSumQuery(node.right, left, right);
        }

        void update(int index, int value) {
            update(root, index, value);
            arr[index] = value; // Keep original array updated
        }

        void update(Node node, int index, int value) {
            if (node.start == node.end) {
                node.sum = value;
                return;
            }
            int mid = (node.start + node.end) / 2;
            if (index <= mid) {
                update(node.left, index, value);
            } else {
                update(node.right, index, value);
            }
            node.sum = node.left.sum + node.right.sum;
        }
    }

    // 4. Segment Tree for Minimum Range Query
    //    - Specifically designed to find the minimum value in a given range.
    //    - Can be adapted for other range queries like maximum or product.
    // Real-world application: Finding the minimum price of a product over a specific period in e-commerce.
    static class MinRangeQuerySegmentTree {
        int[] tree;
        int[] arr;

        public MinRangeQuerySegmentTree(int[] arr) {
            this.arr = arr;
            tree = new int[4 * arr.length];
        }

        void buildTree(int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                int mid = (start + end) / 2;
                buildTree(2 * node + 1, start, mid);
                buildTree(2 * node + 2, mid + 1, end);
                tree[node] = Math.min(tree[2 * node + 1], tree[2 * node + 2]); // Store the minimum
            }
        }

        int query(int node, int start, int end, int left, int right) {
            if (right < start || end < left) {
                return Integer.MAX_VALUE; // Return a large value for minimum query
            }
            if (left <= start && end <= right) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            int leftMin = query(2 * node + 1, start, mid, left, right);
            int rightMin = query(2 * node + 2, mid + 1, end, left, right);
            return Math.min(leftMin, rightMin);
        }

        void update(int node, int start, int end, int index, int value) {
            if (start == end) {
                arr[index] = value;
                tree[node] = value;
            } else {
                int mid = (start + end) / 2;
                if (index <= mid) {
                    update(2 * node + 1, start, mid, index, value);
                } else {
                    update(2 * node + 2, mid + 1, end, index, value);
                }
                tree[node] = Math.min(tree[2 * node + 1], tree[2 * node + 2]); // Update the minimum
            }
        }
    }

    // 5. Segment Tree with Non-Recursive Query
    //    - Performs queries iteratively instead of recursively.
    //    - Can be more efficient in some cases due to reduced function call overhead.
    // Real-world application: High-performance systems where minimizing function calls is crucial,
    //      such as in certain types of game servers or real-time data processing.
    static class NonRecursiveSegmentTree {
        int[] tree;
        int[] arr;
        int n;

        public NonRecursiveSegmentTree(int[] arr) {
            this.arr = arr;
            this.n = arr.length;
            tree = new int[2 * n]; //  Size is 2 * n
            // Copy the original array to the end of the tree array
            for (int i = 0; i < n; i++) {
                tree[n + i] = arr[i];
            }
            // Build the tree from the bottom up
            for (int i = n - 1; i > 0; i--) {
                tree[i] = tree[2 * i] + tree[2 * i + 1];
            }
        }

        int rangeSumQuery(int left, int right) {
            // Adjust left and right to be 0-based index and offset for the tree array.
            left += n;
            right += n;
            int sum = 0;

            while (left <= right) {
                if ((left & 1) == 1) { // If left is odd, add it to the sum and move left to the right
                    sum += tree[left++];
                }
                if ((right & 1) == 0) { // If right is even, add it to the sum and move right to the left
                    sum += tree[right--];
                }
                left /= 2;  // Move left pointer to its parent
                right /= 2; // Move right pointer to its parent
            }
            return sum;
        }

        void update(int index, int value) {
            index += n; // Offset the index to the leaf node in the tree array
            tree[index] = value; // Update the leaf node
            arr[index - n] = value; // Also update the original array

            // Update the parent nodes
            while (index > 0) {
                int left = index;
                int right = index;
                if ((index & 1) == 1) { // If index is odd, left is index, right is index + 1
                    right = index + 1;
                } else {            // If index is even, left is index -1, right is index
                    left = index - 1;
                }
                // Move up to the parent
                index /= 2;
                tree[index] = tree[left] + tree[right];
            }
        }
    }
}


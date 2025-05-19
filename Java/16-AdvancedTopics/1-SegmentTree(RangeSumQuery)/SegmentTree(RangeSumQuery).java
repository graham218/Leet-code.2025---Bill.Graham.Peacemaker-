import java.util.Arrays;

public class SegmentTree {

    // Main function to demonstrate the usage of different Segment Tree approaches
    public static void main(String[] args) {
        int[] arr = {1, 3, 5, 7, 9, 11}; // Input array
        int n = arr.length;

        // 1. Recursive Approach
        System.out.println("1. Recursive Approach:");
        SegmentTreeRecursive stRecursive = new SegmentTreeRecursive(arr);
        System.out.println("Sum of range (1, 3): " + stRecursive.rangeSumQuery(1, 3)); // Expected: 15 (3 + 5 + 7)
        stRecursive.update(1, 10); // Update element at index 1 to 10
        System.out.println("Sum of range (1, 3) after update: " + stRecursive.rangeSumQuery(1, 3)); // Expected: 22 (10 + 5 + 7)
        System.out.println();

        // 2. Iterative Approach
        System.out.println("2. Iterative Approach:");
        SegmentTreeIterative stIterative = new SegmentTreeIterative(arr);
        System.out.println("Sum of range (1, 3): " + stIterative.rangeSumQuery(1, 3));
        stIterative.update(1, 10);
        System.out.println("Sum of range (1, 3) after update: " + stIterative.rangeSumQuery(1, 3));
        System.out.println();

        // 3. Lazy Propagation Approach
        System.out.println("3. Lazy Propagation Approach:");
        SegmentTreeLazy stLazy = new SegmentTreeLazy(arr);
        System.out.println("Sum of range (1, 3): " + stLazy.rangeSumQuery(1, 3));
        stLazy.updateRange(1, 3, 2); // Add 2 to elements in range [1, 3]
        System.out.println("Sum of range (1, 3) after range update: " + stLazy.rangeSumQuery(1, 3)); //Expected 28 (12 + 7 + 9)
        stLazy.update(1, 5);
        System.out.println("Sum of range (1, 3) after point update: " + stLazy.rangeSumQuery(1, 3));
        System.out.println();

        // 4. Using Segment Tree Library (No explicit implementation, demonstrates conceptual usage)
        System.out.println("4. Using Segment Tree Library (Conceptual):");
        System.out.println("  (Library usage would simplify the process, but no standard Java library exists.  " +
                "  Libraries in other languages like C++'s STL or some competitive programming libraries " +
                "  provide segment tree implementations.  This would handle the tree construction, " +
                "  updates, and queries internally.)");
        System.out.println("  Conceptual Example:");
        System.out.println("  SegmentTree st = new SegmentTree(arr);  // Initialize with array");
        System.out.println("  int sum = st.query(1, 3);             // Get sum from index 1 to 3");
        System.out.println("  st.update(1, 10);                    // Update value at index 1 to 10");
        System.out.println();

        // 5.  Bottom-Up Iterative Approach
        System.out.println("5. Bottom-Up Iterative Approach:");
        SegmentTreeBottomUp stBottomUp = new SegmentTreeBottomUp(arr);
        System.out.println("Sum of range (1, 3): " + stBottomUp.rangeSumQuery(1, 3));
        stBottomUp.update(1, 10);
        System.out.println("Sum of range (1, 3) after update: " + stBottomUp.rangeSumQuery(1, 3));
        System.out.println();
    }

    // 1. Recursive Approach
    // =====================
    static class SegmentTreeRecursive {
        private int[] tree; // Segment tree array
        private int n;     // Size of the input array

        public SegmentTreeRecursive(int[] arr) {
            n = arr.length;
            tree = new int[4 * n]; // Allocate memory for the segment tree (max 4*n nodes)
            buildTree(arr, 0, 0, n - 1); // Build the segment tree
        }

        // Recursive function to build the segment tree
        private void buildTree(int[] arr, int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start]; // Leaf node: store the array element
            } else {
                int mid = (start + end) / 2;
                buildTree(arr, 2 * node + 1, start, mid); // Build left subtree
                buildTree(arr, 2 * node + 2, mid + 1, end); // Build right subtree
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Internal node: store the sum of children
            }
        }

        // Recursive function to perform range sum query
        public int rangeSumQuery(int left, int right) {
            return rangeSumQuery(0, 0, n - 1, left, right);
        }

        private int rangeSumQuery(int node, int start, int end, int left, int right) {
            if (right < start || end < left) {
                return 0; // No overlap: return 0
            } else if (left <= start && end <= right) {
                return tree[node]; // Total overlap: return the value in the segment tree node
            } else {
                int mid = (start + end) / 2;
                int sumLeft = rangeSumQuery(2 * node + 1, start, mid, left, right); // Query left subtree
                int sumRight = rangeSumQuery(2 * node + 2, mid + 1, end, left, right); // Query right subtree
                return sumLeft + sumRight; // Partial overlap: return the sum of the two halves
            }
        }

        // Recursive function to update an element in the array
        public void update(int index, int value) {
            update(0, 0, n - 1, index, value);
        }

        private void update(int node, int start, int end, int index, int value) {
            if (start == end) {
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

    // 2. Iterative Approach
    // =====================
    static class SegmentTreeIterative {
        private int[] tree;
        private int n;

        public SegmentTreeIterative(int[] arr) {
            n = arr.length;
            tree = new int[2 * n]; // Allocate memory.  Iterative approach uses 2*n size.
            // Copy the original array to the leaves of the tree
            for (int i = 0; i < n; i++) {
                tree[n + i] = arr[i];
            }
            // Build the tree from the bottom up
            for (int i = n - 1; i > 0; i--) {
                tree[i] = tree[2 * i] + tree[2 * i + 1];
            }
        }

        public int rangeSumQuery(int left, int right) {
            // Adjust left and right for 0-based indexing and to access the leaves
            left += n;
            right += n;
            int sum = 0;

            while (left <= right) {
                if ((left & 1) == 1) { // If left is odd, add the value and move left to the right
                    sum += tree[left++];
                }
                if ((right & 1) == 0) { // If right is even, add the value and move right to the left
                    sum += tree[right--];
                }
                left /= 2;  // Move up to the parent
                right /= 2; // Move up to the parent
            }
            return sum;
        }

        public void update(int index, int value) {
            index += n; // Get the index of the leaf node
            tree[index] = value; // Update the leaf node

            // Update the parent nodes
            while (index > 1) {
                index /= 2;
                tree[index] = tree[2 * index] + tree[2 * index + 1];
            }
        }
    }

    // 3. Lazy Propagation Approach
    // =============================
    static class SegmentTreeLazy {
        private int[] tree;
        private int[] lazy; // Array to store lazy update values
        private int n;

        public SegmentTreeLazy(int[] arr) {
            n = arr.length;
            tree = new int[4 * n];
            lazy = new int[4 * n];
            buildTree(arr, 0, 0, n - 1);
        }

        private void buildTree(int[] arr, int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                int mid = (start + end) / 2;
                buildTree(arr, 2 * node + 1, start, mid);
                buildTree(arr, 2 * node + 2, mid + 1, end);
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
            }
        }

        private void propagate(int node, int start, int end) {
            if (lazy[node] != 0) { // If there is a lazy update
                tree[node] += (end - start + 1) * lazy[node]; // Update the current node

                if (start != end) { // If it is not a leaf node, propagate to children
                    lazy[2 * node + 1] += lazy[node];
                    lazy[2 * node + 2] += lazy[node];
                }
                lazy[node] = 0; // Clear the lazy value
            }
        }

        public void updateRange(int left, int right, int value) {
            updateRange(0, 0, n - 1, left, right, value);
        }

        private void updateRange(int node, int start, int end, int left, int right, int value) {
            propagate(node, start, end); // Propagate any pending lazy updates

            if (right < start || end < left) {
                return; // No overlap
            } else if (left <= start && end <= right) {
                lazy[node] += value; // Apply lazy update
                propagate(node, start, end);     // Propagate immediately after applying lazy value
            } else {
                int mid = (start + end) / 2;
                updateRange(2 * node + 1, start, mid, left, right, value);
                updateRange(2 * node + 2, mid + 1, end, left, right, value);
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Update the current node
            }
        }

        public void update(int index, int value) {
            update(0, 0, n - 1, index, value);
        }

        private void update(int node, int start, int end, int index, int value) {
            propagate(node, start, end);

            if (start == end) {
                tree[node] = value;
            } else {
                int mid = (start + end) / 2;
                if (index <= mid) {
                    update(2 * node + 1, start, mid, index, value);
                } else {
                    update(2 * node + 2, mid + 1, end, index, value);
                }
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
            }
        }

        public int rangeSumQuery(int left, int right) {
            return rangeSumQuery(0, 0, n - 1, left, right);
        }

        private int rangeSumQuery(int node, int start, int end, int left, int right) {
            propagate(node, start, end); // Propagate lazy updates

            if (right < start || end < left) {
                return 0;
            } else if (left <= start && end <= right) {
                return tree[node];
            } else {
                int mid = (start + end) / 2;
                int sumLeft = rangeSumQuery(2 * node + 1, start, mid, left, right);
                int sumRight = rangeSumQuery(2 * node + 2, mid + 1, end, left, right);
                return sumLeft + sumRight;
            }
        }
    }

    // 5. Bottom-Up Iterative Approach
    // =============================
    static class SegmentTreeBottomUp {
        private int[] tree;
        private int n;

        public SegmentTreeBottomUp(int[] arr) {
            n = arr.length;
            tree = new int[2 * n];
            // Copy array to the leaves
            for (int i = 0; i < n; ++i)
                tree[n + i] = arr[i];
            // build the tree bottom-up
            for (int i = n - 1; i > 0; --i)
                tree[i] = tree[i<<1] + tree[i<<1 | 1];
        }

        public void update(int index, int value) {
            int pos = index + n;
            tree[pos] = value;
            while (pos > 1) {
                tree[pos >> 1] = tree[pos] + tree[pos ^ 1];
                pos >>= 1;
            }
        }

        public int rangeSumQuery(int left, int right) {
            int l = left + n;
            int r = right + n;
            int sum = 0;

            while (l <= r) {
                if ((l & 1) == 1) sum += tree[l++];
                if ((r & 1) == 0) sum += tree[r--];
                l >>= 1;
                r >>= 1;
            }
            return sum;
        }
    }
}


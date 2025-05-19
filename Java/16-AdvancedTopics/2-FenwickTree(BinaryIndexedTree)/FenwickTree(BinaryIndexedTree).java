import java.util.Arrays;

// Class to represent a Fenwick Tree (Binary Indexed Tree)
class FenwickTree {
    private int[] tree; // Array representing the Fenwick Tree
    private int n;     // Size of the input array

    // 1. Constructor: Initialize the Fenwick Tree with a given size
    public FenwickTree(int n) {
        this.n = n;
        this.tree = new int[n + 1]; // 1-based indexing, so size is n+1
    }

    // 2. Constructor: Initialize Fenwick Tree from an input array (Efficient)
    public FenwickTree(int[] nums) {
        this.n = nums.length;
        this.tree = new int[n + 1];
        // Build the Fenwick Tree in O(n) time
        for (int i = 0; i < n; i++) {
            update(i + 1, nums[i]); // Add nums[i] to the appropriate nodes
        }
    }

    // Helper function to get the parent of an index in the Fenwick Tree
    private int parent(int index) {
        return index - (index & -index); // equivalent to index & (index - 1) but faster.
    }

    // Helper function to get the next index to update in the Fenwick Tree
    private int next(int index) {
        return index + (index & -index);
    }

    // 3. Method: update(index, value) - Update the value at a given index by adding 'value'
    //    Adds 'value' to the element at index 'index' and propagates the change to its ancestors in the tree
    public void update(int index, int value) {
        if (index <= 0 || index > n) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        while (index <= n) {
            tree[index] += value; // Add 'value' to the current node
            index = next(index);    // Move to the next node (parent) to update
        }
    }

    // 4. Method: getSum(index) - Get the prefix sum up to a given index
    //    Calculates the sum of elements from index 1 to 'index' (inclusive)
    public int getSum(int index) {
        if (index < 0 || index > n)
        {
            throw new IllegalArgumentException("Index out of bounds");
        }
        int sum = 0;
        while (index > 0) {
            sum += tree[index];      // Add the value of the current node
            index = parent(index);    // Move to the parent node
        }
        return sum;
    }

    // 5. Method: rangeSum(left, right) - Get the sum of elements within a given range [left, right] (inclusive)
    //    Calculates the sum of elements from index 'left' to 'right' (inclusive) using prefix sums
    public int rangeSum(int left, int right) {
        if (left > right || left < 1 || right > n) {
            throw new IllegalArgumentException("Invalid range");
        }
        return getSum(right) - getSum(left - 1); // Sum[left, right] = Sum[1, right] - Sum[1, left-1]
    }

    // Method to get the entire tree array (for demonstration/debugging)
    public int[] getTreeArray() {
        return Arrays.copyOf(tree, tree.length);
    }
}

// Main class to demonstrate the usage of Fenwick Tree
public class Main {
    public static void main(String[] args) {
        // Example usage with an initial array
        int[] initialArray = {3, 2, -1, 6, 5, 4, -3, 3};
        int n = initialArray.length;

        // Create a Fenwick Tree using the efficient constructor
        FenwickTree ft = new FenwickTree(initialArray);

        System.out.println("Initial Array: " + Arrays.toString(initialArray));
        System.out.println("Fenwick Tree Array: " + Arrays.toString(ft.getTreeArray())); // Print the underlying tree array

        // Example queries and updates
        System.out.println("\nSum of first 5 elements: " + ft.getSum(5)); // Sum from index 1 to 5
        System.out.println("Sum of elements from index 2 to 6: " + ft.rangeSum(2, 6)); // Sum from index 2 to 6

        ft.update(3, 3); // Update the element at index 3 by adding 3
        System.out.println("Updated Fenwick Tree Array: " + Arrays.toString(ft.getTreeArray()));
        System.out.println("Sum of first 5 elements after update: " + ft.getSum(5));
        System.out.println("Sum of elements from index 2 to 6 after update: " + ft.rangeSum(2, 6));

        // Example 2: Demonstrate the basic constructor and updates
        FenwickTree ft2 = new FenwickTree(8); // Create a Fenwick Tree of size 8
        ft2.update(1, 1);
        ft2.update(2, 2);
        ft2.update(3, 3);
        ft2.update(4, 4);
        ft2.update(5, 5);
        ft2.update(6, 6);
        ft2.update(7, 7);
        ft2.update(8, 8);

        System.out.println("\nFenwick Tree 2 Array: " + Arrays.toString(ft2.getTreeArray()));
        System.out.println("Sum of first 7 elements: " + ft2.getSum(7));
        System.out.println("Sum of elements from index 2 to 4: " + ft2.rangeSum(2, 4));

        // Test with negative values
        int[] negativeArray = {-1, -2, -3, -4, -5};
        FenwickTree ft3 = new FenwickTree(negativeArray);
        System.out.println("\nInitial negative array: " + Arrays.toString(negativeArray));
        System.out.println("Sum of first 3 elements: " + ft3.getSum(3));  // Should be -6
        System.out.println("Sum of elements from 1 to 5: " + ft3.rangeSum(1, 5)); // Should be -15

        ft3.update(2, 5); //update index 2 by adding 5.  -2 + 5 = 3
        System.out.println("Sum of first 3 elements after update: " + ft3.getSum(3)); // Should be -1 + 3 + -3 = -1

        // Test with zeros
        int[] zeroArray = {0, 0, 0, 0, 0};
        FenwickTree ft4 = new FenwickTree(zeroArray);
        System.out.println("\nInitial zero array: " + Arrays.toString(zeroArray));
        System.out.println("Sum of first 4 elements: " + ft4.getSum(4)); // Should be 0
        ft4.update(4, 10);
        System.out.println("Sum of first 4 elements after update: " + ft4.getSum(4)); // Should be 10

        //Example of a larger array
        int[] largeArray = new int[1000];
        for (int i = 0; i < 1000; i++)
        {
            largeArray[i] = i + 1;
        }
        FenwickTree ft5 = new FenwickTree(largeArray);
        System.out.println("\nSum of first 100 elements of large array: " + ft5.getSum(100));

        System.out.println("Sum of elements from index 500 to 750: " + ft5.rangeSum(500, 750));
    }
}


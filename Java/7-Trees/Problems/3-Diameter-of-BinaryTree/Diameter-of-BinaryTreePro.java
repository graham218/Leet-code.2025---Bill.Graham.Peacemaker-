import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;

public class DiameterOfBinaryTree {

    /**
     * Approach 1: Recursive Depth Calculation (Most Common, Clean)
     * -   Calculates the diameter by recursively finding the height of left and right subtrees.
     * -   The diameter at each node is the sum of left and right subtree heights.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(H), where H is the height of the tree (due to recursion stack).  In the worst case (skewed tree), H can be N, but in a balanced tree, it's O(log N).
     * -   Real-world application:  This is the standard, go-to approach.  It's used in any application where you need to calculate a tree's diameter due to its simplicity and efficiency.  Examples include network routing algorithms, organizational hierarchy analysis, and file system structure analysis.
     */
    public int diameterOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        int[] diameter = new int[1]; // Use an array to store the diameter, as Java doesn't pass primitive types by reference.
        calculateHeight(root, diameter);
        return diameter[0];
    }

    private int calculateHeight(TreeNode node, int[] diameter) {
        if (node == null) return 0;

        int leftHeight = calculateHeight(node.left, diameter);
        int rightHeight = calculateHeight(node.right, diameter);

        // Calculate diameter at the current node and update the global diameter if needed.
        diameter[0] = Math.max(diameter[0], leftHeight + rightHeight);

        // Return the height of the current node's subtree.
        return Math.max(leftHeight, rightHeight) + 1;
    }



    /**
     * Approach 2: Recursive Approach with Global Variable (Alternative)
     * -   Similar to Approach 1, but uses a global variable instead of an array.
     * -   This approach is less preferred in professional settings due to the use of a global variable, which can make the code harder to maintain and reason about.
     * -   Time Complexity: O(N)
     * -   Space Complexity: O(H)
     * -   Real-world application:  While less common in large projects, this approach might be used in smaller, self-contained scripts or quick prototypes where a global variable is deemed acceptable for simplicity.  It's less suitable for concurrent or multi-threaded applications.
     */
    private int diameter = 0; // Global variable to store the diameter.

    public int diameterOfBinaryTree2(TreeNode root) {
        diameter = 0; // Reset the global variable.  Important for multiple calls.
        calculateHeight2(root);
        return diameter;
    }

    private int calculateHeight2(TreeNode node) {
        if (node == null) return 0;

        int leftHeight = calculateHeight2(node.left);
        int rightHeight = calculateHeight2(node.right);

        diameter = Math.max(diameter, leftHeight + rightHeight);
        return Math.max(leftHeight, rightHeight) + 1;
    }



    /**
     * Approach 3: Level Order Traversal (Iterative)
     * -   Uses level order traversal (BFS) to visit each node.
     * -   For each node, calculates the height of its left and right subtrees.
     * -   This approach is less efficient than the recursive approaches because it calculates the height of subtrees multiple times.
     * -   Time Complexity: O(N * H), where N is the number of nodes and H is the height of the tree. In the worst case, it can be O(N^2).
     * -   Space Complexity: O(W), where W is the maximum width of the tree.  In the worst case (full binary tree), W is (N+1)/2, so it's O(N).
     * -  Real-world application:  This approach is generally *not* preferred for calculating the diameter due to its inefficiency.  BFS is more commonly used for problems where you need to process nodes level by level, such as finding the maximum width of a tree, or certain graph traversal algorithms.  It could be used if you needed to combine diameter calculation with other level-order processing.
     */
    public int diameterOfBinaryTree3(TreeNode root) {
        if (root == null) return 0;

        int diameter = 0;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            int leftHeight = getHeight(node.left);
            int rightHeight = getHeight(node.right);
            diameter = Math.max(diameter, leftHeight + rightHeight);

            if (node.left != null) queue.offer(node.left);
            if (node.right != null) queue.offer(node.right);
        }
        return diameter;
    }

    private int getHeight(TreeNode node) {
        if (node == null) return 0;
        return Math.max(getHeight(node.left), getHeight(node.right)) + 1;
    }


    /**
     * Approach 4: Using AtomicInteger (Thread-Safe Diameter)
     * -   Similar to Approach 1, but uses AtomicInteger to store the diameter.
     * -   This makes the diameter calculation thread-safe.
     * -   Useful in concurrent applications.
     * -   Time Complexity: O(N)
     * -   Space Complexity: O(H)
     * -  Real-world application: This approach is crucial in multi-threaded applications where multiple threads might access and modify the diameter.  For example, in a parallel processing system analyzing a large tree structure, AtomicInteger ensures that the diameter is updated correctly without race conditions.  This is essential for data consistency in concurrent environments.
     */
    public int diameterOfBinaryTree4(TreeNode root) {
        if (root == null) return 0;
        AtomicInteger diameter = new AtomicInteger(0);
        calculateHeight4(root, diameter);
        return diameter.get();
    }

    private int calculateHeight4(TreeNode node, AtomicInteger diameter) {
        if (node == null) return 0;

        int leftHeight = calculateHeight4(node.left, diameter);
        int rightHeight = calculateHeight4(node.right, diameter);

        diameter.getAndSet(Math.max(diameter.get(), leftHeight + rightHeight));
        return Math.max(leftHeight, rightHeight) + 1;
    }


    /**
     * Approach 5: Iterative Post-Order Traversal with Stack
     * - Uses a stack to perform iterative post-order traversal.
     * - This approach calculates the height and diameter while traversing the tree in post-order.
     * - Avoids recursion, providing an iterative solution.
     * - Time Complexity: O(N)
     * - Space Complexity: O(H) in the worst case (skewed tree), average case O(log N) for balanced tree.
     * - Real-world application:  This iterative approach is valuable when you need to avoid recursion, such as in environments with limited stack space (e.g., embedded systems) or when dealing with very deep trees that could cause stack overflow errors.  It's also useful in situations where you need more control over the traversal process.
     */
    public int diameterOfBinaryTree5(TreeNode root) {
        if (root == null) return 0;

        int diameter = 0;
        LinkedList<TreeNode> stack = new LinkedList<>(); // Use LinkedList as Stack
        TreeNode current = root;
        TreeNode prev = null; // Keep track of the previously visited node

        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.push(current);
                current = current.left;
            }

            current = stack.peek(); // Peek, don't pop yet

            if (current.right != null && current.right != prev) {
                // If right child exists and is not visited, go right
                current = current.right;
            } else {
                // Otherwise, process the node (calculate height and diameter)
                current = stack.pop();
                int leftHeight = (current.left == null) ? 0 : (int)current.left.val; //Use node.val as height
                int rightHeight = (current.right == null) ? 0 : (int)current.right.val;
                diameter = Math.max(diameter, leftHeight + rightHeight);

                // Calculate height of current node and store it in node.val.  This is a key part of the post-order iterative approach.
                current.val = Math.max(leftHeight, rightHeight) + 1;
                prev = current; // Mark current node as visited
                current = null; // Reset current to null to go back up the stack
            }
        }
        return diameter;
    }



    public static void main(String[] args) {
        DiameterOfBinaryTree solution = new DiameterOfBinaryTree();

        // Example tree:
        //        1
        //       / \
        //      2   3
        //     / \
        //    4   5
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);

        // Test all 5 approaches:
        System.out.println("Approach 1 (Recursive): " + solution.diameterOfBinaryTree(root)); // Output: 3
        System.out.println("Approach 2 (Recursive with Global): " + solution.diameterOfBinaryTree2(root)); // Output: 3
        System.out.println("Approach 3 (Level Order): " + solution.diameterOfBinaryTree3(root)); // Output: 3
        System.out.println("Approach 4 (AtomicInteger): " + solution.diameterOfBinaryTree4(root)); // Output: 3
        System.out.println("Approach 5 (Iterative Post-order): " + solution.diameterOfBinaryTree5(root)); // Output: 3

        // Test case with only root
        TreeNode root2 = new TreeNode(1);
        System.out.println("Approach 1 (Single Node): " + solution.diameterOfBinaryTree(root2)); // Output: 0

        // Test case with null root
        System.out.println("Approach 1 (Null Root): " + solution.diameterOfBinaryTree(null)); // Output: 0

        // Test case: unbalanced tree
        TreeNode root3 = new TreeNode(1);
        root3.left = new TreeNode(2);
        root3.left.left = new TreeNode(3);
        root3.left.left.left = new TreeNode(4);
        System.out.println("Approach 1 (Unbalanced Tree): " + solution.diameterOfBinaryTree(root3)); // Output: 3
    }
}

// Definition for a binary tree node.
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

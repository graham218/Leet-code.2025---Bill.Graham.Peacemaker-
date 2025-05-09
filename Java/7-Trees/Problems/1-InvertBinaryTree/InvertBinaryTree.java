import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


public class InvertBinaryTree {

    /**
     * Approach 1: Recursive Approach
     *
     * This is the most intuitive approach.  We recursively swap the left and right children
     * of each node, starting from the root.  The base case is when we reach a null node.
     *
     * Time Complexity: O(n), where n is the number of nodes in the tree.  We visit each node once.
     * Space Complexity: O(h), where h is the height of the tree.  In the worst case (skewed tree),
     * h = n, so the space complexity can be O(n).  In the best case (balanced tree),
     * h = log n, so the space complexity is O(log n).
     */
    public TreeNode invertTreeRecursive(TreeNode root) {
        if (root == null) {
            return null; // Base case: nothing to do for a null node
        }

        // Recursively invert the left and right subtrees
        TreeNode left = invertTreeRecursive(root.left);
        TreeNode right = invertTreeRecursive(root.right);

        // Swap the left and right children of the current node
        root.left = right;
        root.right = left;

        return root; // Return the modified root
    }

    /**
     * Approach 2: Iterative Approach using a Queue (Breadth-First Search)
     *
     * We can also invert the tree iteratively using a queue.  This is essentially a
     * Breadth-First Search (BFS) traversal.  We start by adding the root to the queue.
     * Then, while the queue is not empty, we dequeue a node, swap its children, and
     * enqueue its children (if they exist).
     *
     * Time Complexity: O(n), where n is the number of nodes in the tree.  We visit each node once.
     * Space Complexity: O(w), where w is the maximum width of the tree.  In the worst case
     * (a full binary tree), w = n, so the space complexity can be O(n).
     * In the best case (a skewed tree), w = 1, so the space complexity is O(1).
     */
    public TreeNode invertTreeIterativeQueue(TreeNode root) {
        if (root == null) {
            return null; // Handle the empty tree case
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root); // Add the root to the queue

        while (!queue.isEmpty()) {
            TreeNode current = queue.poll(); // Dequeue a node

            // Swap the left and right children
            TreeNode temp = current.left;
            current.left = current.right;
            current.right = temp;

            // Enqueue the left child if it exists
            if (current.left != null) {
                queue.offer(current.left);
            }
            // Enqueue the right child if it exists
            if (current.right != null) {
                queue.offer(current.right);
            }
        }

        return root; // Return the modified root
    }


    /**
     * Approach 3: Iterative Approach using a Stack (Depth-First Search)
     *
     * We can also invert the tree iteratively using a stack. This is essentially a
     * Depth-First Search (DFS) traversal. We start by pushing the root to the stack.
     * Then, while the stack is not empty, we pop a node, swap its children, and
     * push its children (if they exist).  The order in which we push the children
     * affects the order in which we visit them.
     *
     * Time Complexity: O(n), where n is the number of nodes in the tree. We visit each node once.
     * Space Complexity: O(h), where h is the height of the tree. In the worst case (skewed tree),
     * h = n, so the space complexity can be O(n). In the best case (balanced tree),
     * h = log n, so the space complexity is O(log n).
     */
    public TreeNode invertTreeIterativeStack(TreeNode root) {
        if (root == null) {
            return null;
        }

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode current = stack.pop();

            // Swap children
            TreeNode temp = current.left;
            current.left = current.right;
            current.right = temp;

            // Push children onto the stack.  Push right first so left is processed next.
            if (current.right != null) {
                stack.push(current.right);
            }
            if (current.left != null) {
                stack.push(current.left);
            }
        }
        return root;
    }

    /**
     * Approach 4: Recursive Approach (Alternative)
     * This is a slightly different way to write the recursive solution.
     * It might be a bit more concise for some.
     */
    public TreeNode invertTreeRecursiveAlt(TreeNode root) {
        if (root == null) return null;
        TreeNode temp = root.left;
        root.left = invertTreeRecursiveAlt(root.right);
        root.right = invertTreeRecursiveAlt(temp);
        return root;
    }

    /**
     * Approach 5: Level Order Traversal with Modification
     * This approach uses level order traversal (BFS) but modifies the tree
     * as it goes.  It's similar to the iterative queue approach, but
     * the swapping logic is slightly different and more compact.
     */
    public TreeNode invertTreeLevelOrder(TreeNode root) {
        if (root == null) return null;
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                // Swap the children using a concise syntax
                TreeNode temp = node.left;
                node.left = node.right;
                node.right = temp;

                if (node.left != null) q.offer(node.left);
                if (node.right != null) q.offer(node.right);
            }
        }
        return root;
    }



    public static void main(String[] args) {
        // Example usage:
        // Create a sample binary tree:
        //      4
        //    /   \
        //   2     7
        //  / \   / \
        // 1   3 6   9
        TreeNode root = new TreeNode(4,
                new TreeNode(2, new TreeNode(1), new TreeNode(3)),
                new TreeNode(7, new TreeNode(6), new TreeNode(9)));

        InvertBinaryTree solution = new InvertBinaryTree();

        // Test each of the 5 approaches:
        System.out.println("Original Tree (for comparison):");
        printTree(root); // Helper method to print the tree

        // Approach 1: Recursive
        TreeNode invertedRoot1 = solution.invertTreeRecursive(copyTree(root)); // Create a copy to avoid modifying the original
        System.out.println("\nInverted Tree (Recursive):");
        printTree(invertedRoot1);

        // Approach 2: Iterative (Queue)
        TreeNode invertedRoot2 = solution.invertTreeIterativeQueue(copyTree(root));
        System.out.println("\nInverted Tree (Iterative - Queue):");
        printTree(invertedRoot2);

        // Approach 3: Iterative (Stack)
        TreeNode invertedRoot3 = solution.invertTreeIterativeStack(copyTree(root));
        System.out.println("\nInverted Tree (Iterative - Stack):");
        printTree(invertedRoot3);

        // Approach 4: Recursive Alternative
        TreeNode invertedRoot4 = solution.invertTreeRecursiveAlt(copyTree(root));
        System.out.println("\nInverted Tree (Recursive Alternative):");
        printTree(invertedRoot4);

        // Approach 5: Level Order
        TreeNode invertedRoot5 = solution.invertTreeLevelOrder(copyTree(root));
        System.out.println("\nInverted Tree (Level Order):");
        printTree(invertedRoot5);
    }

    // Helper method to print the tree in a readable format (in-order traversal)
    //  This is just for demonstration and testing.
    static void printTree(TreeNode root) {
        if (root == null) {
            System.out.print("null ");
            return;
        }
        printTree(root.left);
        System.out.print(root.val + " ");
        printTree(root.right);
    }

    // Helper method to create a deep copy of the tree.  This is important
    //  so that we can test each inversion method on the *same* original tree.
    static TreeNode copyTree(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode newNode = new TreeNode(root.val);
        newNode.left = copyTree(root.left);
        newNode.right = copyTree(root.right);
        return newNode;
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


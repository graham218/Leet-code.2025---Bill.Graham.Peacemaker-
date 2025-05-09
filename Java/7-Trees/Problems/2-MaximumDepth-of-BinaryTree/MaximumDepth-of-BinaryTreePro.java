import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


public class MaximumDepthBinaryTree {

    /**
     * Approach 1: Recursive Depth-First Search (DFS)
     *
     * This is the classic, most intuitive approach.  It recursively explores the left and right subtrees
     * and returns the maximum depth.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.
     * Space Complexity: O(H), where H is the height of the tree.  In the worst case (skewed tree), H = N,
     * and in the best case (balanced tree), H = log N.  This is due to the call stack.
     *
     * Real-world considerations:
     * -  Simple and easy to understand, making it good for maintainability.
     * -  Can lead to stack overflow for very deep trees, so it might not be suitable for extremely large datasets
     * without modification (see iterative approaches).
     */
    public int maxDepthRecursive(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int leftDepth = maxDepthRecursive(root.left);
        int rightDepth = maxDepthRecursive(root.right);
        return Math.max(leftDepth, rightDepth) + 1;
    }

    /**
     * Approach 2: Iterative Breadth-First Search (BFS)
     *
     * This approach uses a queue to perform a level-order traversal.  The depth is incremented at each level.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.
     * Space Complexity: O(W), where W is the maximum width of the tree.  In the worst case (complete binary tree),
     * W = N/2, so the space complexity is O(N).  In the best case (skewed tree), W = 1, so
     * the space complexity is O(1).
     *
     * Real-world considerations:
     * -  Avoids stack overflow issues of the recursive approach.
     * -  Generally preferred for very large trees.
     * -  Slightly more complex to code than the recursive approach.
     */
    public int maxDepthBFS(TreeNode root) {
        if (root == null) {
            return 0;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int depth = 0;
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
            depth++;
        }
        return depth;
    }

    /**
     * Approach 3: Iterative Depth-First Search (DFS) with Stack
     *
     * This approach uses a stack to simulate the recursive calls of the DFS approach.  It keeps track of the
     * depth of each node as it traverses the tree.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.
     * Space Complexity: O(H), where H is the height of the tree.  In the worst case (skewed tree), H = N, and
     * in the best case (balanced tree), H = log N.
     *
     * Real-world considerations:
     * -  Avoids stack overflow issues of the recursive approach.
     * -  More memory-efficient than BFS in cases where the tree is deep but not very wide.
     * -  Can be slightly less intuitive than the recursive approach.
     */
    public int maxDepthIterativeDFS(TreeNode root) {
        if (root == null) {
            return 0;
        }
        Stack<Pair<TreeNode, Integer>> stack = new Stack<>();
        stack.push(new Pair<>(root, 1));
        int maxDepth = 0;
        while (!stack.isEmpty()) {
            Pair<TreeNode, Integer> pair = stack.pop();
            TreeNode node = pair.node;
            int depth = pair.depth;
            maxDepth = Math.max(maxDepth, depth);
            if (node.right != null) {
                stack.push(new Pair<>(node.right, depth + 1));
            }
            if (node.left != null) {
                stack.push(new Pair<>(node.left, depth + 1));
            }
        }
        return maxDepth;
    }

    // Helper class to store the node and its depth.  Using a generic Pair class for clarity.
    private static class Pair<T, U> {
        T node;
        U depth;
        Pair(T node, U depth) {
            this.node = node;
            this.depth = depth;
        }
    }

    /**
     * Approach 4:  Recursive DFS with Tail Recursion (Optimized - Not directly applicable in Java)
     *
     * Tail recursion is a specific form of recursion where the recursive call is the last operation
     * in the function.  Compilers can optimize tail recursion by turning it into iteration, thus avoiding
     * stack overflow.  However, Java does NOT perform tail call optimization.  This method is included for
     * conceptual completeness and for comparison with languages that do optimize tail recursion.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1) in languages that optimize tail recursion, O(H) in Java.
     *
     * Real-world considerations:
     * -  In Java, this offers no advantage over standard recursion.
     * -  In languages that *do* optimize tail recursion, this can be very efficient.
     */
    public int maxDepthTailRecursive(TreeNode root) {
        return maxDepthTailRecursiveHelper(root, 0);
    }

    private int maxDepthTailRecursiveHelper(TreeNode node, int depth) {
        if (node == null) {
            return depth;
        }
        int leftDepth = maxDepthTailRecursiveHelper(node.left, depth + 1);
        int rightDepth = maxDepthTailRecursiveHelper(node.right, depth + 1);
        return Math.max(leftDepth, rightDepth);
    }



    /**
     * Approach 5:  Level Order Traversal with Level Tracking (Similar to BFS, but with explicit level)
     *
     * This approach is very similar to BFS, but it explicitly tracks the level of each node as it's
     * being processed.  This makes the logic very clear for determining the maximum depth.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(W), where W is the maximum width of the tree.
     *
     * Real-world considerations:
     * - Very clear and easy to understand.
     * - Avoids recursion, so it's suitable for large trees.
     * - Slightly more verbose than the basic BFS, but the added clarity can be beneficial in complex projects.
     */
    public int maxDepthLevelOrder(TreeNode root) {
        if (root == null) {
            return 0;
        }

        Queue<Pair<TreeNode, Integer>> queue = new LinkedList<>();
        queue.offer(new Pair<>(root, 1)); // Start at level 1
        int maxDepth = 0;

        while (!queue.isEmpty()) {
            Pair<TreeNode, Integer> current = queue.poll();
            TreeNode node = current.node;
            int level = current.depth;

            maxDepth = Math.max(maxDepth, level); // Update maxDepth

            if (node.left != null) {
                queue.offer(new Pair<>(node.left, level + 1));
            }
            if (node.right != null) {
                queue.offer(new Pair<>(node.right, level + 1));
            }
        }
        return maxDepth;
    }



    public static void main(String[] args) {
        // Create a sample binary tree for testing
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);
        root.left.left.left = new TreeNode(7);


        MaximumDepthBinaryTree solution = new MaximumDepthBinaryTree();

        // Test the different approaches
        System.out.println("Max Depth (Recursive DFS): " + solution.maxDepthRecursive(root)); // Output: 4
        System.out.println("Max Depth (Iterative BFS): " + solution.maxDepthBFS(root));     // Output: 4
        System.out.println("Max Depth (Iterative DFS): " + solution.maxDepthIterativeDFS(root));  // Output: 4
        System.out.println("Max Depth (Tail Recursive): " + solution.maxDepthTailRecursive(root)); // Output: 4
        System.out.println("Max Depth (Level Order): " + solution.maxDepthLevelOrder(root));       // Output: 4
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


import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.atomic.AtomicInteger;


public class InvertBinaryTree {

    /**
     * 1. Recursive Approach (Classic)
     * -   Time Complexity: O(n), where n is the number of nodes.
     * -   Space Complexity: O(h), where h is the height of the tree (stack space).  In the worst case of a skewed tree, h can be n, so O(n).  For a balanced tree, it's O(log n).
     * -   Core Concept: Recursively swap the left and right children of each node.
     * -   Real-world application: Simple and efficient for most binary tree manipulations where stack overflow is not a concern for reasonably balanced trees.  Good for quick, in-place tree transformations.
     */
    public TreeNode invertTreeRecursive(TreeNode root) {
        if (root == null) {
            return null;
        }

        // Swap left and right children
        TreeNode temp = root.left;
        root.left = root.right;
        root.right = temp;

        // Recursively invert the left and right subtrees
        invertTreeRecursive(root.left);
        invertTreeRecursive(root.right);

        return root;
    }

    /**
     * 2. Iterative Approach using a Queue (Breadth-First Search)
     * -   Time Complexity: O(n), where n is the number of nodes.
     * -   Space Complexity: O(w), where w is the maximum width of the tree.  In the worst case (a full binary tree), w is approximately n/2, so O(n). For a balanced tree, it's closer to O(2^(h-1)).
     * -   Core Concept: Use a queue to perform a level-order traversal, swapping children at each level.
     * -   Real-world application: Useful when you want to avoid recursion, such as in environments with limited stack space or when integrating with systems that prefer iterative processing.  Also good for level-by-level processing of a tree.
     */
    public TreeNode invertTreeIterativeQueue(TreeNode root) {
        if (root == null) {
            return null;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();

            // Swap left and right children
            TreeNode temp = current.left;
            current.left = current.right;
            current.right = temp;

            // Add children to the queue
            if (current.left != null) {
                queue.offer(current.left);
            }
            if (current.right != null) {
                queue.offer(current.right);
            }
        }
        return root;
    }

    /**
     * 3. Iterative Approach using a Stack (Depth-First Search)
     * -   Time Complexity: O(n), where n is the number of nodes.
     * -   Space Complexity: O(h), where h is the height of the tree.  In the worst case (skewed tree), this becomes O(n).
     * -   Core Concept: Use a stack to perform a depth-first traversal, swapping nodes as they are visited.
     * -    Real-world application: Provides an alternative iterative approach with DFS characteristics.  Useful when you need to control the order of node processing (depth-first).
     */
    public TreeNode invertTreeIterativeStack(TreeNode root) {
        if (root == null) {
            return null;
        }

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode current = stack.pop();

            // Swap left and right children
            TreeNode temp = current.left;
            current.left = current.right;
            current.right = temp;

            // Push children onto the stack (right first to maintain left-to-right processing)
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
     * 4. Recursive Approach with Early Exit for Leaf Nodes
     * -   Time Complexity: O(n), where n is the number of nodes.  *Slightly* better in *some* cases because it avoids unnecessary swaps at leaf nodes.
     * -   Space Complexity: O(h), where h is the height of the tree.
     * -   Core Concept: Optimized recursive approach that checks if a node is a leaf before swapping.
     * -   Real-world application: This optimization can be beneficial in scenarios where the tree has many leaf nodes, potentially saving some computational effort.  It's a good example of micro-optimization for performance-critical applications, though the actual savings might not always be significant.
     */
    public TreeNode invertTreeRecursiveOptimized(TreeNode root) {
        if (root == null) {
            return null;
        }

        if (root.left != null || root.right != null) { // Only swap if it's not a leaf node
            // Swap left and right children
            TreeNode temp = root.left;
            root.left = root.right;
            root.right = temp;

            // Recursively invert the left and right subtrees
            invertTreeRecursiveOptimized(root.left);
            invertTreeRecursiveOptimized(root.right);
        }
        return root;
    }

    /**
     * 5. Parallel Recursive Approach using Fork/Join Framework (for very large trees)
     * -   Time Complexity: O(n) in the worst case, but with potential speedup due to parallelism.  Ideally, it approaches O(n/p) where p is the number of available processors, but with overhead.
     * -   Space Complexity: O(h), where h is the height of the tree.  The ForkJoinPool manages threads, but the recursion depth is still limited by the tree's height.
     * -   Core Concept: Utilize the Fork/Join framework to parallelize the tree inversion process for very large trees.  This approach divides the task into smaller subtasks that can be processed concurrently.
     * -   Real-world application:  This is the most complex approach, but it's designed for situations where you need to invert extremely large binary trees and performance is critical.  It's suitable for high-performance computing environments where you can leverage multiple processor cores.  The threshold for using this approach depends on the size of the tree and the overhead of thread management.
     */
    public TreeNode invertTreeParallel(TreeNode root) {
        if (root == null) {
            return null;
        }

        ForkJoinPool forkJoinPool = ForkJoinPool.commonPool(); //Or create a dedicated pool.
        forkJoinPool.invoke(new InvertTask(root));
        return root;
    }

    // RecursiveAction for the Fork/Join framework
    private static class InvertTask extends RecursiveAction {
        private final TreeNode node;

        InvertTask(TreeNode node) {
            this.node = node;
        }

        @Override
        protected void compute() {
            if (node == null) {
                return;
            }

            // Swap left and right children
            TreeNode temp = node.left;
            node.left = node.right;
            node.right = temp;

            if (node.left != null || node.right != null) {
                // Create subtasks for left and right subtrees
                InvertTask leftTask = new InvertTask(node.left);
                InvertTask rightTask = new InvertTask(node.right);

                // Invoke them in parallel
                invokeAll(leftTask, rightTask);
            }
        }
    }

    // Helper method to create a sample binary tree for testing
    public static TreeNode createSampleTree() {
        TreeNode root = new TreeNode(4);
        root.left = new TreeNode(2);
        root.right = new TreeNode(7);
        root.left.left = new TreeNode(1);
        root.left.right = new TreeNode(3);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(9);
        return root;
    }

    public static void main(String[] args) {
        InvertBinaryTree solution = new InvertBinaryTree();
        TreeNode root = createSampleTree();

        // 1. Recursive Approach
        TreeNode invertedTreeRecursive = solution.invertTreeRecursive(TreeNode.cloneTree(root)); // Need to clone to avoid modifying the original
        System.out.println("Recursive Inverted Tree: " + TreePrinter.toString(invertedTreeRecursive));

        // 2. Iterative Approach using Queue
        TreeNode invertedTreeIterativeQueue = solution.invertTreeIterativeQueue(TreeNode.cloneTree(root));
        System.out.println("Iterative Queue Inverted Tree: " + TreePrinter.toString(invertedTreeIterativeQueue));

        // 3. Iterative Approach using Stack
        TreeNode invertedTreeIterativeStack = solution.invertTreeIterativeStack(TreeNode.cloneTree(root));
        System.out.println("Iterative Stack Inverted Tree: " + TreePrinter.toString(invertedTreeIterativeStack));

        // 4. Optimized Recursive
        TreeNode invertedTreeRecursiveOptimized = solution.invertTreeRecursiveOptimized(TreeNode.cloneTree(root));
        System.out.println("Optimized Recursive Inverted Tree: " + TreePrinter.toString(invertedTreeRecursiveOptimized));

        // 5. Parallel Recursive (Fork/Join)
        TreeNode invertedTreeParallel = solution.invertTreeParallel(TreeNode.cloneTree(root));
        System.out.println("Parallel Recursive Inverted Tree: " + TreePrinter.toString(invertedTreeParallel));
    }

    // Helper class to deeply clone a TreeNode.  Prevents modification of the original tree during testing.
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }

        // Deep copy constructor
        TreeNode(TreeNode other) {
            this.val = other.val;
            this.left = (other.left != null) ? new TreeNode(other.left) : null;
            this.right = (other.right != null) ? new TreeNode(other.right) : null;
        }

        // Method to create a deep copy of a TreeNode
        public static TreeNode cloneTree(TreeNode root) {
            if (root == null) {
                return null;
            }
            return new TreeNode(root);
        }

        @Override
        public String toString() {
            return "TreeNode{" +
                    "val=" + val +
                    ", left=" + (left == null ? "null" : left.val) + // Avoid infinite recursion
                    ", right=" + (right == null ? "null" : right.val) +
                    "}";
        }
    }

    // Helper class to print the tree in a structured format
    static class TreePrinter {

        static String toString(TreeNode root) {
            if (root == null) return "null";
            return toStringHelper(root, "", "", false);
        }

        private static String toStringHelper(TreeNode node, String indent, String prefix, boolean isLeft) {
            StringBuilder sb = new StringBuilder();
            if (node != null) {
                sb.append(indent).append(prefix);
                sb.append(isLeft ? "├── " : "└── ");
                sb.append(node.val).append("\n");
                indent += isLeft ? "│   " : "    ";
                sb.append(toStringHelper(node.left, indent, "", true));
                sb.append(toStringHelper(node.right, indent, "", false));
            } else {
                sb.append(indent).append(prefix);
                sb.append("└── null\n");
            }
            return sb.toString();
        }
    }
}

// Definition for a binary tree node.
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode() {
    }

    TreeNode(int val) {
        this.val = val;
    }

    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }

    @Override
    public String toString() {
        return "TreeNode{" +
                "val=" + val +
                ", left=" + (left == null ? "null" : left.val) + // Avoid infinite recursion
                ", right=" + (right == null ? "null" : right.val) +
                "}";
    }
}


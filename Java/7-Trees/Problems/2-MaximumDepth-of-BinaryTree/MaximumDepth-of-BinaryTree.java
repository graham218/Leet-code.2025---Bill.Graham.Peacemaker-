import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


public class MaximumDepthOfBinaryTree {

    public static void main(String[] args) {
        // Create a sample binary tree for testing
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);

        // Test the different approaches
        System.out.println("Maximum depth (Recursive DFS): " + maxDepthRecursiveDFS(root)); // Output: 3
        System.out.println("Maximum depth (Iterative DFS): " + maxDepthIterativeDFS(root)); // Output: 3
        System.out.println("Maximum depth (BFS): " + maxDepthBFS(root)); // Output: 3
        System.out.println("Maximum depth (Recursive DFS - Optimized): " + maxDepthRecursiveDFSOptimized(root)); // Output: 3
        System.out.println("Maximum depth (Iterative Level Order): " + maxDepthIterativeLevelOrder(root)); // Output: 3

    }

    // 1. Recursive Depth-First Search (DFS)
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree (due to recursion stack).  In the worst case, H=N for a skewed tree.
    public static int maxDepthRecursiveDFS(TreeNode root) {
        if (root == null) {
            return 0; // Base case: an empty tree has a depth of 0
        } else {
            // Recursively calculate the depth of the left and right subtrees
            int leftDepth = maxDepthRecursiveDFS(root.left);
            int rightDepth = maxDepthRecursiveDFS(root.right);
            // The depth of the current node is 1 + the maximum of the left and right depths
            return 1 + Math.max(leftDepth, rightDepth);
        }
    }

    // 2. Iterative Depth-First Search (DFS) using a stack
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree.  In the worst case, H=N for a skewed tree.
    public static int maxDepthIterativeDFS(TreeNode root) {
        if (root == null) {
            return 0;
        }

        Stack<Pair<TreeNode, Integer>> stack = new Stack<>();
        stack.push(new Pair<>(root, 1)); // Start with the root and depth 1
        int maxDepth = 0;

        while (!stack.isEmpty()) {
            Pair<TreeNode, Integer> current = stack.pop();
            TreeNode node = current.key;
            int depth = current.value;
            maxDepth = Math.max(maxDepth, depth); // Update maxDepth

            if (node.left != null) {
                stack.push(new Pair<>(node.left, depth + 1)); // Push left child with increased depth
            }
            if (node.right != null) {
                stack.push(new Pair<>(node.right, depth + 1)); // Push right child with increased depth
            }
        }
        return maxDepth;
    }

    // Helper class to store a node and its depth
    private static class Pair<K, V> {
        K key;
        V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    // 3. Breadth-First Search (BFS) using a queue
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(W), where W is the maximum width of the tree.  In the worst case, W=N/2 for a complete binary tree.
    public static int maxDepthBFS(TreeNode root) {
        if (root == null) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root); // Start with the root node
        int depth = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size(); // Number of nodes at the current level
            depth++; // Increment depth for each level

            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll(); // Dequeue a node
                if (node.left != null) {
                    queue.offer(node.left); // Enqueue left child
                }
                if (node.right != null) {
                    queue.offer(node.right); // Enqueue right child
                }
            }
        }
        return depth;
    }

    // 4. Recursive Depth-First Search (DFS) - Optimized
    // This approach is essentially the same as the first recursive approach, but it's written more concisely.
    // It doesn't offer a significant performance improvement, but it's a common way to express the recursion.
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree.
    public static int maxDepthRecursiveDFSOptimized(TreeNode root) {
        if (root == null) {
            return 0;
        }
        return 1 + Math.max(maxDepthRecursiveDFSOptimized(root.left), maxDepthRecursiveDFSOptimized(root.right));
    }

    // 5. Iterative Level Order Traversal
    // This is another way to implement Breadth-First Search (BFS).
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(W), where W is the maximum width of the tree.
    public static int maxDepthIterativeLevelOrder(TreeNode root) {
        if (root == null) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int depth = 0;

        while (!queue.isEmpty()) {
            depth++;
            int levelLength = queue.size();

            for (int i = 0; i < levelLength; i++) {
                TreeNode current = queue.poll();
                if (current.left != null) {
                    queue.offer(current.left);
                }
                if (current.right != null) {
                    queue.offer(current.right);
                }
            }
        }
        return depth;
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
}


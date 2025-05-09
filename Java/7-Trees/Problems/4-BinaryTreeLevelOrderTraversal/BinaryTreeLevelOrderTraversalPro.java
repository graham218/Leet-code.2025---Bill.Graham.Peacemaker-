import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class BinaryTreeLevelOrderTraversal {

    /**
     * Approach 1: Iterative using Queue (Standard Level Order Traversal)
     * -   Uses a queue to process nodes level by level.
     * -   This is the most common and efficient approach for level order traversal.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(W), where W is the maximum width of the tree.
     *
     * Project Implementation:
     * -   Useful in applications where you need to process nodes in a breadth-first manner.
     * -   Example: Displaying nodes in a UI, processing nodes in a game tree,
     * or implementing certain graph algorithms (since a tree is a graph).
     */
    public List<List<Integer>> levelOrderIterative(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            List<Integer> currentLevel = new ArrayList<>();
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            result.add(currentLevel);
        }
        return result;
    }

    /**
     * Approach 2: Recursive Approach
     * -   Uses recursion to traverse the tree.
     * -   Helper function takes the node and the level as input.
     * -   Nodes are added to the result list based on their level.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(H), where H is the height of the tree (due to recursion stack).
     *
     * Project Implementation:
     * -   Can be used when a recursive approach is more natural or when
     * the call stack depth is not a concern.
     * -   Example:  Configuration file processing where tree-like structures are defined recursively.
     */
    public List<List<Integer>> levelOrderRecursive(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;
        levelOrderHelper(root, 0, result);
        return result;
    }

    private void levelOrderHelper(TreeNode node, int level, List<List<Integer>> result) {
        if (node == null) return;

        if (level >= result.size()) {
            result.add(new ArrayList<>());
        }
        result.get(level).add(node.val);
        levelOrderHelper(node.left, level + 1, result);
        levelOrderHelper(node.right, level + 1, result);
    }

    /**
     * Approach 3: Modified Iterative with Level Information in Queue
     * -   Stores nodes and their level information in the queue.
     * -   Avoids the inner loop to track level size.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(W), where W is the maximum width of the tree.
     *
     * Project Implementation:
     * -   Useful when you need to know the level of each node during traversal.
     * -   Example:  Visualizing tree structures with level numbers,
     * or in game development for level-based logic.
     */
    public List<List<Integer>> levelOrderIterativeWithLevel(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<Pair> queue = new LinkedList<>();
        queue.offer(new Pair(root, 0)); // Store node and its level

        while (!queue.isEmpty()) {
            Pair current = queue.poll();
            TreeNode node = current.node;
            int level = current.level;

            if (level >= result.size()) {
                result.add(new ArrayList<>());
            }
            result.get(level).add(node.val);

            if (node.left != null) queue.offer(new Pair(node.left, level + 1));
            if (node.right != null) queue.offer(new Pair(node.right, level + 1));
        }
        return result;
    }

    // Helper class to store node and level together.
    private static class Pair {
        TreeNode node;
        int level;
        Pair(TreeNode node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    /**
     * Approach 4: Using a Stack and Two Queues (Reverse Level Order)
     * -   Uses one queue to traverse level by level, and a stack to reverse the order.
     * -   First, do a normal level order, but push each level's result into a stack.
     * -   Then, pop from the stack to get the level order in reverse.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(N), where N is the number of nodes (for stack in worst case).
     *
     * Project Implementation:
     * -   Useful when you need the level order traversal in reverse.
     * -   Example:  Bottom-up rendering of a tree in a UI,
     * or processing dependencies in a project where lower levels need to be processed first.
     */
    public List<List<Integer>> levelOrderBottom(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new LinkedList<>();
        Stack<List<Integer>> stack = new Stack<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            List<Integer> currentLevel = new ArrayList<>();
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            stack.push(currentLevel); // Push each level to the stack
        }

        while (!stack.isEmpty()) {
            result.add(stack.pop()); // Pop levels from the stack
        }
        return result;
    }

    /**
     * Approach 5: Morris Traversal (Threaded Binary Tree) -  *Without* using extra space
     *
     * -   The Morris traversal is a way to traverse a binary tree without using
     * a stack or recursion. It modifies the tree temporarily by creating threads.
     * -   A thread is a link from a node to its inorder successor.
     * -   This approach is tricky and modifies the tree structure.  It's included
     * for completeness and to show a different traversal technique.
     * -   **Important:** This method modifies the original tree.  If you need to
     * preserve the tree structure, make a copy first.  This is generally NOT
     * recommended for typical production code unless you *fully* understand
     * the implications and have a specific need for in-place modification.
     * -  Time complexity: O(N)
     * -  Space complexity: O(1)
     *
     * Project Implementation:
     * -   This is a space-optimized traversal.
     * -  Very specialized use cases where memory is extremely limited
     * -  NOT typically used in standard application development due to its complexity
     * and the modification of the tree structure.  Use with caution.
     */
    public List<List<Integer>> levelOrderMorris(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        TreeNode current = root;
        int level = 0;
        List<Integer> currentLevelList = new ArrayList<>();

        while (current != null) {
            if (current.left == null) {
                currentLevelList.add(current.val);
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    predecessor.right = current; // Create the thread
                    currentLevelList.add(current.val);
                    current = current.left;
                } else { // predecessor.right == current
                    predecessor.right = null; // Remove the thread

                    // End of the current level
                    result.add(currentLevelList);
                    currentLevelList = new ArrayList<>();
                    level++;
                    current = current.right;
                }
            }
        }
        if (currentLevelList.size() > 0)
        {
            result.add(currentLevelList);
        }

        return result;
    }

    public static void main(String[] args) {
        // Create a sample binary tree for testing
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        BinaryTreeLevelOrderTraversal solution = new BinaryTreeLevelOrderTraversal();

        // Test Approach 1: Iterative using Queue
        System.out.println("Level Order Traversal (Iterative): " + solution.levelOrderIterative(root));

        // Test Approach 2: Recursive Approach
        System.out.println("Level Order Traversal (Recursive): " + solution.levelOrderRecursive(root));

        // Test Approach 3: Iterative with Level Info
        System.out.println("Level Order Traversal (Iterative with Level): " + solution.levelOrderIterativeWithLevel(root));

        // Test Approach 4: Reverse Level Order
        System.out.println("Level Order Traversal (Reverse): " + solution.levelOrderBottom(root));

        // Test Approach 5: Morris Traversal
        System.out.println("Level Order Traversal (Morris): " + solution.levelOrderMorris(root));
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

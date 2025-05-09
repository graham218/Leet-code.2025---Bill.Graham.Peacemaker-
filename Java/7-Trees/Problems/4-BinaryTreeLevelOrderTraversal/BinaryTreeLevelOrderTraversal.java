import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class BinaryTreeLevelOrderTraversal {

    /**
     * Approach 1: Iterative using Queue (Standard BFS)
     * - Time Complexity: O(N), where N is the number of nodes in the tree.
     * - Space Complexity: O(W), where W is the maximum width of the tree.
     *
     * @param root The root of the binary tree.
     * @return A list of lists representing the level order traversal of the tree.
     */
    public List<List<Integer>> levelOrderIterative(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            List<Integer> currentLevel = new ArrayList<>();

            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);

                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
            result.add(currentLevel);
        }
        return result;
    }

    /**
     * Approach 2: Recursive Depth-First Search (DFS) with level tracking
     * - Time Complexity: O(N), where N is the number of nodes.
     * - Space Complexity: O(H), where H is the height of the tree (due to recursion stack).  In the worst case of a skewed tree, H can be N, but in a balanced tree, it's log(N).
     *
     * @param root The root of the binary tree.
     * @return A list of lists representing the level order traversal.
     */
    public List<List<Integer>> levelOrderRecursive(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        levelOrderHelper(root, 0, result);
        return result;
    }

    private void levelOrderHelper(TreeNode node, int level, List<List<Integer>> result) {
        if (node == null) {
            return;
        }

        // If the level doesn't exist in the result list, create a new list for it.
        if (level >= result.size()) {
            result.add(new ArrayList<>());
        }

        // Add the current node's value to the list corresponding to its level.
        result.get(level).add(node.val);

        // Recursively process the left and right children, incrementing the level.
        levelOrderHelper(node.left, level + 1, result);
        levelOrderHelper(node.right, level + 1, result);
    }

    /**
     * Approach 3: Modified Iterative using Queue, without using levelSize
     * - Time Complexity: O(N), where N is the number of nodes.
     * - Space Complexity: O(W), where W is the maximum width of the tree.
     * This approach might have a slightly better constant factor in space
     * compared to the standard BFS because it doesn't explicitly store the
     * number of nodes at each level.
     *
     * @param root The root of the binary tree.
     * @return A list of lists representing the level order traversal.
     */
    public List<List<Integer>> levelOrderIterative2(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        queue.offer(null); // Delimiter to mark the end of a level

        List<Integer> currentLevel = new ArrayList<>();
        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            if (node == null) {
                // End of level
                if (!currentLevel.isEmpty()) { // Avoid adding empty lists
                    result.add(currentLevel);
                    currentLevel = new ArrayList<>(); // Start a new level list
                    if (!queue.isEmpty()) {
                        queue.offer(null); // Add delimiter for the next level
                    }
                }
            } else {
                // Process the node
                currentLevel.add(node.val);
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
        }
        return result;
    }

    /**
     * Approach 4: Iterative using a Queue and a count variable.
     * - Time Complexity: O(N), where N is the number of nodes in the tree.
     * - Space Complexity: O(W), where W is the maximum width of the tree.
     *
     * @param root The root of the binary tree.
     * @return A list of lists representing the level order traversal of the tree.
     */
    public List<List<Integer>> levelOrderIterative3(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int nodesInCurrentLevel = 1; // Initialize count for the root level

        while (!queue.isEmpty()) {
            int nodesInNextLevel = 0; // Count for the next level
            List<Integer> currentLevel = new ArrayList<>();

            for (int i = 0; i < nodesInCurrentLevel; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);

                if (node.left != null) {
                    queue.offer(node.left);
                    nodesInNextLevel++;
                }
                if (node.right != null) {
                    queue.offer(node.right);
                    nodesInNextLevel++;
                }
            }
            result.add(currentLevel);
            nodesInCurrentLevel = nodesInNextLevel; // Update count for the next level
        }
        return result;
    }

    /**
     * Approach 5: Using a Stack to reverse the result from standard level order traversal
     * - Time Complexity: O(N), where N is the number of nodes in the tree.
     * - Space Complexity: O(W + H), where W is the maximum width of the tree (for queue)
     * and H is the height of the tree (for stack). In the worst case, W can be close to N/2 and H can be N.
     * So in worst case Space Complexity is O(N).
     *
     * @param root The root of the binary tree.
     * @return A list of lists representing the level order traversal of the tree.
     */
    public List<List<Integer>> levelOrderUsingStack(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        Stack<List<Integer>> stack = new Stack<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            List<Integer> currentLevel = new ArrayList<>();

            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);

                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
            stack.push(currentLevel); // Push the current level to the stack
        }

        // Pop elements from the stack to reverse the order (bottom-up)
        while (!stack.isEmpty()) {
            result.add(stack.pop());
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

        // Test and print the results for each approach
        System.out.println("Level Order Traversal (Iterative): " + solution.levelOrderIterative(root));
        System.out.println("Level Order Traversal (Recursive): " + solution.levelOrderRecursive(root));
        System.out.println("Level Order Traversal (Iterative 2): " + solution.levelOrderIterative2(root));
        System.out.println("Level Order Traversal (Iterative 3): " + solution.levelOrderIterative3(root));
        System.out.println("Level Order Traversal (Using Stack): " + solution.levelOrderUsingStack(root));
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

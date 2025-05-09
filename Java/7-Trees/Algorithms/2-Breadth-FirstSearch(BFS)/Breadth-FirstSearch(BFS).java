import java.util.LinkedList;
import java.util.Queue;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class BinaryTreeBFS {

    // Approach 1: Iterative BFS using a Queue (Standard)
    // - Uses a queue to process nodes level by level.
    // -是最常见的 BFS 方法
    public List<List<Integer>> levelOrder1(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root); // Enqueue the root node

        while (!queue.isEmpty()) {
            int levelSize = queue.size(); // Number of nodes at the current level
            List<Integer> currentLevel = new ArrayList<>();

            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll(); // Dequeue a node
                currentLevel.add(node.val); // Add its value to the current level list

                if (node.left != null) queue.offer(node.left); // Enqueue left child if it exists
                if (node.right != null) queue.offer(node.right); // Enqueue right child if it exists
            }
            result.add(currentLevel); // Add the current level list to the result
        }
        return result;
    }

    // Approach 2: Iterative BFS with Level Information
    // - Similar to Approach 1, but keeps track of the level of each node.
    public List<List<Integer>> levelOrder2(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<Pair<TreeNode, Integer>> queue = new LinkedList<>();
        queue.offer(new Pair<>(root, 0)); // Enqueue the root with level 0

        while (!queue.isEmpty()) {
            Pair<TreeNode, Integer> current = queue.poll();
            TreeNode node = current.getKey();
            int level = current.getValue();

            // If the level doesn't exist in the result list, add a new list for it.
            if (result.size() <= level) {
                result.add(new ArrayList<>());
            }
            result.get(level).add(node.val); // Add the node's value to the corresponding level

            if (node.left != null) queue.offer(new Pair<>(node.left, level + 1));
            if (node.right != null) queue.offer(new Pair<>(node.right, level + 1));
        }
        return result;
    }

    // Helper class to store a node and its level.  Using a generic Pair class.
    private static class Pair<K, V> {
        private final K key;
        private final V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }
    }

    // Approach 3: Recursive BFS (using level)
    // - Uses recursion, but simulates BFS by processing level by level.
    // - Not a typical recursive BFS, but achieves level-order traversal recursively.
    public List<List<Integer>> levelOrder3(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        int height = getHeight(root); // Get the height of the tree.

        for (int level = 0; level < height; level++) {
            List<Integer> currentLevel = new ArrayList<>();
            processLevel(root, level, currentLevel); // Process each level
            result.add(currentLevel);
        }
        return result;
    }

    // Helper function to get the height of the tree.
    private int getHeight(TreeNode node) {
        if (node == null) return 0;
        return 1 + Math.max(getHeight(node.left), getHeight(node.right));
    }

    // Helper function to process nodes at a given level.
    private void processLevel(TreeNode node, int level, List<Integer> currentLevel) {
        if (node == null) return;
        if (level == 0) {
            currentLevel.add(node.val);
        } else if (level > 0) {
            processLevel(node.left, level - 1, currentLevel);
            processLevel(node.right, level - 1, currentLevel);
        }
    }

    // Approach 4: Modified Iterative BFS for Zigzag Traversal
    // - Performs a Breadth-First Search but alternates the order of nodes
    //   in each level (left-to-right, right-to-left).
    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        boolean leftToRight = true; // Flag to indicate traversal direction

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
            if (!leftToRight) {
                Collections.reverse(currentLevel); // Reverse for right-to-left traversal
            }
            result.add(currentLevel);
            leftToRight = !leftToRight; // Toggle the direction
        }
        return result;
    }

    // Approach 5: BFS to find level with maximum width
    // Finds the level in the binary tree that has the most nodes.
    public int maxWidth(TreeNode root) {
        if (root == null) return 0;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int maxWidth = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            maxWidth = Math.max(maxWidth, levelSize); // Update max width
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
        }
        return maxWidth;
    }

    public static void main(String[] args) {
        // Create a sample binary tree
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);
        root.left.left.left = new TreeNode(7);


        BinaryTreeBFS bfs = new BinaryTreeBFS();

        // Test Approach 1
        System.out.println("Level Order Traversal (Approach 1): " + bfs.levelOrder1(root));

        // Test Approach 2
        System.out.println("Level Order Traversal (Approach 2): " + bfs.levelOrder2(root));

        // Test Approach 3
        System.out.println("Level Order Traversal (Approach 3): " + bfs.levelOrder3(root));

        // Test Approach 4
        System.out.println("Zigzag Level Order Traversal (Approach 4): " + bfs.zigzagLevelOrder(root));

        // Test Approach 5
        System.out.println("Maximum Width of Tree (Approach 5): " + bfs.maxWidth(root));
    }
}

// Definition of a binary tree node.
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
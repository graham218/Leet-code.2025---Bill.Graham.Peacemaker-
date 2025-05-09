import java.util.LinkedList;
import java.util.Queue;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;

public class TreeBFS {

    public static void main(String[] args) {
        // Create a sample binary tree for testing
        TreeNode<Integer> root = new TreeNode<>(1);
        root.left = new TreeNode<>(2);
        root.right = new TreeNode<>(3);
        root.left.left = new TreeNode<>(4);
        root.left.right = new TreeNode<>(5);
        root.right.left = new TreeNode<>(6);
        root.right.right = new TreeNode<>(7);
        root.left.left.left = new TreeNode<>(8);
        root.left.left.right = new TreeNode<>(9);

        System.out.println("Tree structure for testing:");
        printTree(root); // Helper method to visualize the tree structure

        System.out.println("\n1. Basic BFS Traversal:");
        List<Integer> bfsResult = basicBFS(root);
        System.out.println(bfsResult); // Output: [1, 2, 3, 4, 5, 6, 7, 8, 9]

        System.out.println("\n2. BFS with Level Information:");
        List<List<Integer>> bfsWithLevelResult = bfsWithLevel(root);
        System.out.println(bfsWithLevelResult); // Output: [[1], [2, 3], [4, 5, 6, 7], [8, 9]]

        System.out.println("\n3. BFS for Searching a Value (Returns true if found):");
        boolean found = bfsSearch(root, 5);
        System.out.println("Found 5? " + found); // Output: true
        boolean notFound = bfsSearch(root, 10);
        System.out.println("Found 10? " + notFound); // Output: false

        System.out.println("\n4. BFS to find maximum width of tree:");
        int maxWidth = findMaxWidth(root);
        System.out.println("Maximum width of tree is: " + maxWidth);

        System.out.println("\n5. BFS for Tree Serialization/Deserialization (Conceptual - prints level order):");
        //  This shows the level order traversal, which is the core of serialization/deserialization
        List<Integer> serialized = serializeTree(root);
        System.out.println("Serialized (Level Order): " + serialized);
        // Deserialization would involve reconstructing the tree from this level order,
        // but that's a more complex process and is beyond the scope of a simple BFS example.
        // It's included as a conceptual application.
    }

    // Helper method to print the tree structure (for visualization)
    public static void printTree(TreeNode<?> root) {
        if (root == null) return;
        Queue<TreeNode<?>> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode<?> node = queue.poll();
                System.out.print(node.val + " ");
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            System.out.println(); // Move to the next level
        }
    }

    /**
     * 1. Basic Breadth-First Search (BFS) Traversal
     *
     * -   Performs a standard BFS traversal of the binary tree.
     * -   Visits nodes level by level, from left to right.
     * -   Uses a queue to maintain the order of nodes to visit.
     * -   Returns a list containing the values of the nodes in the order they were visited.
     * -   Real-world application:
     * -   Crawling a website:  BFS can be used to traverse the pages of a website,
     * starting from the home page and following links to other pages.
     *
     * @param root The root of the binary tree to traverse.
     * @return A list of node values in BFS order.  Returns an empty list if the root is null.
     */
    public static List<Integer> basicBFS(TreeNode<Integer> root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        queue.offer(root); // Add the root node to the queue

        while (!queue.isEmpty()) {
            TreeNode<Integer> node = queue.poll(); // Dequeue the front node
            result.add(node.val); // Process the node's value

            // Enqueue the left and right children, if they exist
            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
        }
        return result;
    }

    /**
     * 2. BFS Traversal with Level Information
     *
     * -   Performs a BFS traversal, but also keeps track of the level of each node.
     * -   Returns a list of lists, where each inner list represents a level of the tree.
     * -   Nodes within each level are ordered from left to right.
     * -  Real-world application:
     * - Network Routing:  Finding the shortest path between two nodes in a network
     * can be implemented using a modified BFS that considers network topology.
     *
     * @param root The root of the binary tree.
     * @return A list of lists, where each inner list contains the node values at that level.
     * Returns an empty list if the root is null.
     */
    public static List<List<Integer>> bfsWithLevel(TreeNode<Integer> root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int level = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size(); // Number of nodes at the current level
            List<Integer> currentLevel = new ArrayList<>();
            for (int i = 0; i < levelSize; i++) {
                TreeNode<Integer> node = queue.poll();
                currentLevel.add(node.val);

                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
            result.add(currentLevel);
            level++;
        }
        return result;
    }

    /**
     * 3. BFS for Searching a Value
     *
     * -   Performs a BFS traversal to search for a specific value within the tree.
     * -   Returns true if the value is found, false otherwise.
     * -   This is an adaptation of BFS for a search problem, not just traversal.
     * -   Real-world application:
     * -   Social Network Search: Searching for a user in a social network, where
     * nodes represent users and edges represent connections.
     *
     * @param root The root of the tree to search in.
     * @param target The value to search for.
     * @return True if the value is found, false otherwise.
     */
    public static boolean bfsSearch(TreeNode<Integer> root, int target) {
        if (root == null) {
            return false;
        }

        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode<Integer> node = queue.poll();
            if (node.val == target) {
                return true; // Value found!
            }

            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
        }
        return false; // Value not found after traversing the entire tree
    }

    /**
     * 4. BFS to find maximum width of tree
     *
     * - Uses BFS to find the maximum width of the binary tree.
     * - The width of a level is the number of nodes at that level.
     * - Real world application:
     * - UI layout: Determining the maximum width of a widget or element
     * in a hierarchical user interface structure.
     *
     * @param root - root node of the tree
     * @return - returns the maximum width
     */

    public static int findMaxWidth(TreeNode<Integer> root) {
        if (root == null) {
            return 0;
        }

        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int maxWidth = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size(); // Get the size of the current level
            maxWidth = Math.max(maxWidth, levelSize); // Update maxWidth if current level is wider

            for (int i = 0; i < levelSize; i++) {
                TreeNode<Integer> node = queue.poll();
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
        }
        return maxWidth;
    }

    /**
     * 5. BFS for Tree Serialization/Deserialization (Conceptual)
     *
     * -   Demonstrates how BFS can be used conceptually for tree serialization.
     * -   Serialization is the process of converting a tree into a linear format
     * (e.g., a string or a list) so that it can be stored or transmitted.
     * -   BFS provides a level-order traversal, which is a common way to serialize a tree.
     * -   Deserialization is the reverse process: constructing the tree from the linear format.
     * -   This method focuses on the serialization aspect (using BFS to get level order).
     * -   Real-world application:
     * -   Data storage and retrieval:  Serializing a tree allows it to be stored in a file
     * or database, and then deserialized to reconstruct the tree in memory when needed.
     * -   Distributed systems:  Trees can be serialized to be transmitted over a network
     * between different systems.
     *
     * @param root The root of the tree to serialize.
     * @return A list of Integers representing the level order traversal of the tree.
     */
    public static List<Integer> serializeTree(TreeNode<Integer> root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode<Integer> node = queue.poll();
            result.add(node.val); // Add the value, NOT the node.

            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
        }
        return result;
    }
}

// Definition of a generic TreeNode class.  This is used across all the examples.
class TreeNode<T> {
    T val;
    TreeNode<T> left;
    TreeNode<T> right;

    public TreeNode(T val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }

    public TreeNode(T val, TreeNode<T> left, TreeNode<T> right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }

    @Override
    public String toString() {
        return "TreeNode{" +
                "val=" + val +
                ", left=" + (left == null ? "null" : left.val) + // Avoid infinite recursion in toString
                ", right=" + (right == null ? "null" : right.val) +
                "}";
    }
}
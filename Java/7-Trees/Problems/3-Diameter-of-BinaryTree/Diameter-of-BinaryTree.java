import java.util.*;
import java.lang.*;

class Solution {

    /**
     * Approach 1: Recursive with Global Variable
     * -   Calculates the diameter by recursively finding the height of left and right subtrees.
     * -   Updates a global variable `diameter` whenever a larger diameter is found.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(H), where H is the height of the tree (call stack).  In the worst case, H = N for a skewed tree.
     */
    int diameter = 0; // Global variable to store the diameter

    public int diameterOfBinaryTree_approach1(TreeNode root) {
        if (root == null) return 0;
        diameter = 0; // Reset diameter
        height(root);
        return diameter;
    }

    private int height(TreeNode node) {
        if (node == null) return 0;

        int leftHeight = height(node.left);
        int rightHeight = height(node.right);

        // Calculate diameter at each node and update the global variable if needed.
        diameter = Math.max(diameter, leftHeight + rightHeight);

        return Math.max(leftHeight, rightHeight) + 1;
    }



    /**
     * Approach 2: Recursive without Global Variable
     * -   Similar to Approach 1, but avoids using a global variable.
     * -   Instead, the diameter is calculated and returned directly from the recursive function.
     * -   Uses a helper function that returns an array: [height, diameter].
     * -   Time Complexity: O(N)
     * -   Space Complexity: O(H)
     */
    public int diameterOfBinaryTree_approach2(TreeNode root) {
        if (root == null) return 0;
        int[] result = heightAndDiameter(root);
        return result[1];
    }

    private int[] heightAndDiameter(TreeNode node) {
        if (node == null) {
            return new int[] {0, 0}; // {height, diameter}
        }

        int[] leftResult = heightAndDiameter(node.left);
        int[] rightResult = heightAndDiameter(node.right);

        int currentHeight = Math.max(leftResult[0], rightResult[0]) + 1;
        int currentDiameter = Math.max(leftResult[0] + rightResult[0], Math.max(leftResult[1], rightResult[1]));

        return new int[] {currentHeight, currentDiameter};
    }



    /**
     * Approach 3: Iterative using Stack (Post-order Traversal)
     * -   Uses a stack to perform a post-order traversal of the tree.
     * -   A HashMap stores the height of each node.
     * -   Calculates the diameter while traversing the tree.
     * -   Time Complexity: O(N)
     * -   Space Complexity: O(N) (for stack and HashMap)
     */
    public int diameterOfBinaryTree_approach3(TreeNode root) {
        if (root == null) return 0;

        Stack<TreeNode> stack = new Stack<>();
        HashMap<TreeNode, Integer> heightMap = new HashMap<>();
        int diameter = 0;
        TreeNode current = root;

        while (current != null || !stack.isEmpty()) {
            if (current != null) {
                stack.push(current);
                current = current.left;
            } else {
                TreeNode top = stack.peek();
                if (top.right != null && heightMap.get(top.right) == null) {
                    current = top.right;
                } else {
                    stack.pop();
                    int leftHeight = (top.left != null) ? heightMap.get(top.left) : 0;
                    int rightHeight = (top.right != null) ? heightMap.get(top.right) : 0;
                    diameter = Math.max(diameter, leftHeight + rightHeight);
                    heightMap.put(top, Math.max(leftHeight, rightHeight) + 1);
                }
            }
        }
        return diameter;
    }

    /**
     * Approach 4: Level Order Traversal (BFS)
     * - Uses Breadth-First Search (BFS) to traverse the tree level by level.
     * - For each node, calculates its height, and the diameter passing through that node.
     * - Time Complexity: O(N^2) in worst case.  For each node, we calculate the height, which can take O(N) in a skewed tree.
     * - Space Complexity: O(W) where W is the maximum width of the tree.  O(N) in the worst case (full binary tree).
     */
    public int diameterOfBinaryTree_approach4(TreeNode root) {
        if (root == null) return 0;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int diameter = 0;

        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            int leftHeight = calculateHeight(node.left);
            int rightHeight = calculateHeight(node.right);
            diameter = Math.max(diameter, leftHeight + rightHeight);

            if (node.left != null) queue.offer(node.left);
            if (node.right != null) queue.offer(node.right);
        }
        return diameter;
    }

    private int calculateHeight(TreeNode node) {
        if (node == null) return 0;
        return Math.max(calculateHeight(node.left), calculateHeight(node.right)) + 1;
    }


    /**
     * Approach 5: Divide and Conquer (Optimized Recursion)
     * -   This is a refined recursive approach that efficiently calculates both height and diameter in a single pass.
     * -   It avoids redundant height calculations by returning both values from each recursive call.
     * -   Time Complexity: O(N), where N is the number of nodes.
     * -   Space Complexity: O(H), where H is the height of the tree (call stack).
     */
    public int diameterOfBinaryTree_approach5(TreeNode root) {
        if (root == null) {
            return 0;
        }
        return postOrder(root)[1];
    }

    private int[] postOrder(TreeNode node) {
        if (node == null) {
            return new int[]{0, 0}; // {height, diameter}
        }

        int[] left = postOrder(node.left);
        int[] right = postOrder(node.right);

        int height = Math.max(left[0], right[0]) + 1;
        int diameter = Math.max(left[0] + right[0], Math.max(left[1], right[1]));

        return new int[]{height, diameter};
    }


    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example usage:
        // Create a sample binary tree:
        //      1
        //     / \
        //    2   3
        //   / \
        //  4   5
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);

        // Approach 1
        System.out.println("Approach 1: Diameter of Binary Tree: " + solution.diameterOfBinaryTree_approach1(root)); // Expected Output: 3

        // Approach 2
        System.out.println("Approach 2: Diameter of Binary Tree: " + solution.diameterOfBinaryTree_approach2(root)); // Expected Output: 3

        // Approach 3
        System.out.println("Approach 3: Diameter of Binary Tree: " + solution.diameterOfBinaryTree_approach3(root)); // Expected Output: 3

        // Approach 4
        System.out.println("Approach 4: Diameter of Binary Tree: " + solution.diameterOfBinaryTree_approach4(root)); // Expected Output: 3

        // Approach 5
        System.out.println("Approach 5: Diameter of Binary Tree: " + solution.diameterOfBinaryTree_approach5(root)); // Expected Output: 3
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

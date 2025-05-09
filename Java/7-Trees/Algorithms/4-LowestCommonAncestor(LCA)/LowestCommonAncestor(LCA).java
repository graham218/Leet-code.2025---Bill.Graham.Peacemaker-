import java.util.*;


public class LowestCommonAncestor {

    public static void main(String[] args) {
        // Create a sample binary tree
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);

        TreeNode p = root.left; // Node with value 5
        TreeNode q = root.right; // Node with value 1

        // Approach 1: Recursive Approach
        TreeNode lca1 = findLCAUsingRecursion(root, p, q);
        System.out.println("LCA using Recursion: " + (lca1 != null ? lca1.val : "null")); // Output: 3

        // Approach 2: Iterative using Parent Pointers
        TreeNode lca2 = findLCAUsingParentPointers(root, p, q);
        System.out.println("LCA using Parent Pointers: " + (lca2 != null ? lca2.val : "null")); // Output: 3

        // Approach 3: Using Node Paths
        TreeNode lca3 = findLCAUsingNodePaths(root, p, q);
        System.out.println("LCA using Node Paths: " + (lca3 != null ? lca3.val : "null")); // Output: 3

        // Approach 4: Optimized Recursive Approach
        TreeNode lca4 = findLCAOptimized(root, p, q);
        System.out.println("LCA using Optimized Recursion: " + (lca4 != null ? lca4.val : "null")); // Output: 3

        // Approach 5: Iterative using Stack
        TreeNode lca5 = findLCAUsingStack(root, p, q);
        System.out.println("LCA using Stack: " + (lca5 != null ? lca5.val : "null")); // Output: 3
    }

    // Approach 1: Recursive Approach
    // Time Complexity: O(N), where N is the number of nodes in the tree.
    // Space Complexity: O(H), where H is the height of the tree (due to recursion stack).  In the worst case, H can be equal to N.
    public static TreeNode findLCAUsingRecursion(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) {
            return null;
        }

        // If either p or q is found, return the current node (it could be the LCA)
        if (root == p || root == q) {
            return root;
        }

        // Recursively check the left and right subtrees
        TreeNode leftLCA = findLCAUsingRecursion(root.left, p, q);
        TreeNode rightLCA = findLCAUsingRecursion(root.right, p, q);

        // If both left and right subtrees return a non-null node, then the current node is the LCA
        if (leftLCA != null && rightLCA != null) {
            return root;
        }

        // If only one subtree returns a non-null node, return that node
        return (leftLCA != null) ? leftLCA : rightLCA;
    }


    // Approach 2: Iterative using Parent Pointers
    // Time Complexity: O(N), where N is the number of nodes in the tree.
    // Space Complexity: O(N), to store the parent pointers in the map.
    public static TreeNode findLCAUsingParentPointers(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) return null;

        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        Queue<TreeNode> queue = new LinkedList<>();
        parentMap.put(root, null); // Parent of root is null
        queue.offer(root);

        // Build the parent map using Breadth-First Search (BFS)
        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            if (node.left != null) {
                parentMap.put(node.left, node);
                queue.offer(node.left);
            }
            if (node.right != null) {
                parentMap.put(node.right, node);
                queue.offer(node.right);
            }
        }

        // Get the ancestors of p
        Set<TreeNode> ancestorsOfP = new HashSet<>();
        while (p != null) {
            ancestorsOfP.add(p);
            p = parentMap.get(p);
        }

        // Find the first common ancestor of q
        while (q != null) {
            if (ancestorsOfP.contains(q)) {
                return q;
            }
            q = parentMap.get(q);
        }

        return null; // Should not reach here in a valid tree
    }

    // Approach 3: Using Node Paths
    // Time Complexity: O(N), where N is the number of nodes.  Finding paths is O(N) and comparing them is also O(N)
    // Space Complexity: O(N), to store the paths to p and q.
    public static TreeNode findLCAUsingNodePaths(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) return null;

        List<TreeNode> pathP = new ArrayList<>();
        List<TreeNode> pathQ = new ArrayList<>();

        // Find the paths to p and q
        if (!findPath(root, p, pathP) || !findPath(root, q, pathQ)) {
            return null; // p or q not found
        }

        // Find the last common node in the paths
        TreeNode lca = null;
        for (int i = 0; i < Math.min(pathP.size(), pathQ.size()); i++) {
            if (pathP.get(i) == pathQ.get(i)) {
                lca = pathP.get(i);
            } else {
                break;
            }
        }
        return lca;
    }

    // Helper function to find the path from root to a given node
    private static boolean findPath(TreeNode root, TreeNode target, List<TreeNode> path) {
        if (root == null) {
            return false;
        }

        path.add(root);

        if (root == target) {
            return true;
        }

        if (findPath(root.left, target, path) || findPath(root.right, target, path)) {
            return true;
        }

        path.remove(path.size() - 1); // Backtrack if target is not found in this path
        return false;
    }

    // Approach 4: Optimized Recursive Approach
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree.
    public static TreeNode findLCAOptimized(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q) {
            return root;
        }

        TreeNode leftLCA = findLCAOptimized(root.left, p, q);
        TreeNode rightLCA = findLCAOptimized(root.right, p, q);

        if (leftLCA != null && rightLCA != null) {
            return root;
        }

        return (leftLCA != null) ? leftLCA : rightLCA;
    }

    // Approach 5: Iterative using Stack
    // Time Complexity: O(N), where N is the number of nodes in the tree.
    // Space Complexity: O(N), in worst case, the stack can contain all nodes
    public static TreeNode findLCAUsingStack(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) return null;

        Stack<TreeNode> stackP = new Stack<>();
        Stack<TreeNode> stackQ = new Stack<>();

        // Find paths to p and q using stacks
        findPathUsingStack(root, p, stackP);
        findPathUsingStack(root, q, stackQ);

        // If either stack is empty, then either p or q is not in the tree.
        if (stackP.isEmpty() || stackQ.isEmpty()) {
            return null;
        }
        // Find the LCA
        TreeNode lca = null;
        while (!stackP.isEmpty() && !stackQ.isEmpty() && stackP.peek() == stackQ.peek()) {
            lca = stackP.pop();
            stackQ.pop();
        }
        return lca;
    }

    // Helper function to find path to target using a stack
    private static boolean findPathUsingStack(TreeNode root, TreeNode target, Stack<TreeNode> stack) {
        if (root == null) {
            return false;
        }

        stack.push(root);

        if (root == target) {
            return true;
        }

        if (findPathUsingStack(root.left, target, stack) || findPathUsingStack(root.right, target, stack)) {
            return true;
        }

        stack.pop(); // Backtrack
        return false;
    }
}

// Definition for a binary tree node.
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}
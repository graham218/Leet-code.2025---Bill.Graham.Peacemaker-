import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class MorrisTraversal {

    /*
     * Morris Traversal is an efficient way to traverse a binary tree without using recursion or a stack.
     * It's a threaded binary tree traversal that uses the unused right pointers of leaf nodes
     * to create temporary links (threads) to the inorder successor of the node.
     */

    // 1. Morris Inorder Traversal (Iterative with Threading)
    //    - Time Complexity: O(n), Space Complexity: O(1)
    public List<Integer> morrisInorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;

        while (current != null) {
            if (current.left == null) {
                result.add(current.val);
                current = current.right;
            } else {
                // Find the inorder predecessor
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    // Create the thread
                    predecessor.right = current;
                    current = current.left;
                } else {
                    // Remove the thread and process the current node
                    predecessor.right = null;
                    result.add(current.val);
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 2. Morris Preorder Traversal (Iterative with Threading)
    //    - Time Complexity: O(n), Space Complexity: O(1)
    public List<Integer> morrisPreorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;

        while (current != null) {
            if (current.left == null) {
                result.add(current.val); // Visit before moving to right
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    predecessor.right = current;
                    result.add(current.val); // Visit before moving to left
                    current = current.left;
                } else {
                    predecessor.right = null;
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 3. Morris Postorder Traversal (Iterative with Threading) - Tricky
    //    - Time Complexity: O(n), Space Complexity: O(1)
    public List<Integer> morrisPostorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode dummy = new TreeNode(0); // Dummy node for easier processing
        dummy.left = root;
        TreeNode current = dummy;
        TreeNode prev = null;

        while (current != null) {
            if (current.left == null) {
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    predecessor.right = current;
                    current = current.left;
                } else {
                    predecessor.right = null;
                    // Reverse and add the reversed left subtree to the result
                    reverseAndAdd(current.left, result);
                    current = current.right;
                }
            }
        }
        return result;
    }

    // Helper function to reverse a linked list (used in Morris Postorder) and add to result
    private void reverseAndAdd(TreeNode node, List<Integer> result) {
        TreeNode prev = null;
        TreeNode current = node;
        while (current != null) {
            TreeNode next = current.right;
            current.right = prev;
            prev = current;
            current = next;
        }
        // prev now points to the head of the reversed list, which was the tail
        current = prev;
        while (current != null) {
            result.add(current.val);
            current = current.right;
        }
        // Restore the original tree structure (optional, but good practice)
        prev = null;
        current = node;
        while (current != null) {
            TreeNode next = current.right;
            current.right = prev;
            prev = current;
            current = next;
        }
    }

    // 4. Inorder Traversal using Stack (Iterative) - Comparison for Morris
    //    - Time Complexity: O(n), Space Complexity: O(h) where h is the height of the tree.
    public List<Integer> inorderWithStack(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        TreeNode current = root;

        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.push(current);
                current = current.left;
            }
            current = stack.pop();
            result.add(current.val);
            current = current.right;
        }
        return result;
    }

    // 5. Preorder Traversal using Stack (Iterative) - Comparison for Morris
    //    - Time Complexity: O(n), Space Complexity: O(h) where h is the height of the tree.
    public List<Integer> preorderWithStack(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode current = stack.pop();
            result.add(current.val);

            if (current.right != null) {
                stack.push(current.right);
            }
            if (current.left != null) {
                stack.push(current.left);
            }
        }
        return result;
    }

    public static void main(String[] args) {
        // Create a sample binary tree
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(7);

        MorrisTraversal traversal = new MorrisTraversal();

        // Example Usage and Output
        System.out.println("Morris Inorder Traversal: " + traversal.morrisInorder(root));
        System.out.println("Morris Preorder Traversal: " + traversal.morrisPreorder(root));
        System.out.println("Morris Postorder Traversal: " + traversal.morrisPostorder(root));
        System.out.println("Inorder Traversal with Stack: " + traversal.inorderWithStack(root));
        System.out.println("Preorder Traversal with Stack: " + traversal.preorderWithStack(root));
    }
}

// Definition of a binary tree node.
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
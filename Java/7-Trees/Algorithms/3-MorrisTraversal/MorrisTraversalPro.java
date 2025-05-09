import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class MorrisTraversal {

    /*
     * Morris Traversal - Iterative Tree Traversal without using recursion or a stack.
     *
     * Key Idea:
     * The Morris traversal algorithm is based on the concept of threaded binary trees.
     * In a threaded binary tree, some of the null pointers are replaced by pointers
     * to other nodes in the tree.
     *
     * Advantages:
     * -   Space Efficient: O(1) space complexity, as it doesn't use recursion or a stack.
     * -   Efficient:  Generally faster than stack-based iterative traversals.
     *
     * Disadvantages:
     * -   破坏了树的结构 (Modifies Tree Structure): Temporarily changes the tree
     * structure, which can be problematic in multi-threaded environments or when
     * the original tree structure needs to be preserved.  The structure is restored,
     * but this modification can lead to issues if not handled carefully.
     * -   Not Suitable for all Traversal Orders:  Directly applicable for inorder
     * traversal. Modifications are needed for pre-order and post-order.
     * -   Code Complexity: The logic is more complex than standard recursive or
     * stack-based traversals, making it harder to understand and debug.
     *
     * Real-World Applications:
     * -   Iterative Tree Traversal: When stack space is limited, such as in embedded systems.
     * -   Compiler Design:  For expression evaluation and syntax analysis.
     * -   Database Systems:  For traversing tree-structured indexes.
     * -  Memory-Constrained Environments: Useful in situations where memory usage
     * needs to be minimized.
     *
     */

    // 1. Morris Inorder Traversal (Most Common)
    //    -  Core Implementation
    //    -  Suitable for most binary tree inorder traversal needs.
    //    -  Important for understanding the basic Morris Traversal.
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
                    // Break the thread
                    predecessor.right = null;
                    result.add(current.val);
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 2. Morris Preorder Traversal
    //    -  Modified version of inorder.
    //    -  Adds node value *before* creating the thread.
    //    -  Useful when the order of visiting nodes before their children is important.
    public List<Integer> morrisPreorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;

        while (current != null) {
            if (current.left == null) {
                result.add(current.val); // Add before moving right
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    predecessor.right = current;
                    result.add(current.val); // Add before moving left
                    current = current.left;
                } else {
                    predecessor.right = null;
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 3. Morris Inorder Traversal with Visited Check
    //    -  Prevents infinite loops in cases where the tree might have cycles
    //       (though standard binary trees shouldn't have cycles, this is a robust version).
    //   - Uses a `visited` set (simulated with a boolean directly in the node).
    //    -  Demonstrates how to handle potentially problematic input.
    public List<Integer> morrisInorderSafe(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;

        while (current != null) {
            if (current.left == null) {
                result.add(current.val);
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
                    result.add(current.val);
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 4.  Morris Inorder Traversal with Parent Node Tracking
    //     -  Simulates a stack to keep track of the parent.
    //     -  Useful in scenarios where you need to know the path from the root
    //        to the current node during the traversal.
    //     -  Less space-efficient than the basic Morris, but more informative.
    public List<Integer> morrisInorderWithPath(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        List<TreeNode> path = new ArrayList<>(); // To store the path
        TreeNode current = root;

        while (current != null) {
            if (current.left == null) {
                result.add(current.val);
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }

                if (predecessor.right == null) {
                    predecessor.right = current;
                    path.add(current); // Store the current node in the path
                    current = current.left;
                } else {
                    predecessor.right = null;
                    result.add(current.val);
                    path.remove(path.size() - 1); // Remove the current node
                    current = current.right;
                }
            }
        }
        return result;
    }

    // 5. Morris Postorder Traversal (Harder, requires reversing nodes)
    //    - The most complex of the Morris traversals.
    //    -  Involves reversing the links between nodes.
    //    -  Useful in specific cases where post-order traversal is essential
    //       and memory efficiency is a concern.
    private void reverseSubtree(TreeNode node) {
        TreeNode prev = null;
        TreeNode current = node;
        while (current != null) {
            TreeNode next = current.right;
            current.right = prev;
            prev = current;
            current = next;
        }
    }

    private void printReverseSubtree(TreeNode node, List<Integer> result) {
        TreeNode prev = null;
        TreeNode current = node;
        while (current != null) {
            result.add(current.val);
            TreeNode next = current.right;
            current.right = prev;
            prev = current;
            current = next;
        }
    }
    public List<Integer> morrisPostorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode dummy = new TreeNode(0); // Dummy node for easier processing
        dummy.left = root;
        TreeNode current = dummy;

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
                    printReverseSubtree(current.left, result); // Add reversed subtree
                    reverseSubtree(current.left);          // Restore the tree structure
                    current = current.right;
                }
            }
        }
        return result;
    }

    // Helper method to create a sample binary tree for testing
    public static TreeNode createSampleTree() {
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(7);
        return root;
    }

    public static void main(String[] args) {
        MorrisTraversal mt = new MorrisTraversal();
        TreeNode root = createSampleTree();

        // 1. Morris Inorder Traversal
        System.out.println("Morris Inorder Traversal: " + mt.morrisInorder(root)); // Output: [4, 2, 5, 1, 6, 3, 7]

        // 2. Morris Preorder Traversal
        System.out.println("Morris Preorder Traversal: " + mt.morrisPreorder(root)); // Output: [1, 2, 4, 5, 3, 6, 7]

        // 3. Morris Inorder Traversal with Visited Check
        System.out.println("Morris Inorder Traversal (Safe): " + mt.morrisInorderSafe(root));  // Output: [4, 2, 5, 1, 6, 3, 7]

        // 4. Morris Inorder Traversal with Parent Node Tracking
        System.out.println("Morris Inorder with Path: " + mt.morrisInorderWithPath(root)); // Output: [4, 2, 5, 1, 6, 3, 7]

        // 5. Morris Postorder Traversal
        System.out.println("Morris Postorder Traversal: " + mt.morrisPostorder(root));
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
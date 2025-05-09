import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class DFSExample {

    public static void main(String[] args) {
        // Create a sample binary tree
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(7);

        System.out.println("DFS Traversal (Recursive - Preorder):");
        dfsRecursivePreorder(root); // Output: 1 2 4 5 3 6 7
        System.out.println();

        System.out.println("DFS Traversal (Recursive - Inorder):");
        dfsRecursiveInorder(root); // Output: 4 2 5 1 6 3 7
        System.out.println();

        System.out.println("DFS Traversal (Recursive - Postorder):");
        dfsRecursivePostorder(root); // Output: 4 2 5 6 3 7 1
        System.out.println();

        System.out.println("DFS Traversal (Iterative - Stack):");
        dfsIterativeStack(root); // Output: 1 2 4 5 3 6 7 (Preorder equivalent)
        System.out.println();

        System.out.println("DFS Traversal (Iterative - Stack - Postorder):");
        dfsIterativeStackPostorder(root);
        System.out.println();

        System.out.println("DFS Traversal (Iterative - Stack - Inorder):");
        dfsIterativeStackInorder(root);
        System.out.println();
    }

    // 1. Recursive Depth-First Search (Preorder Traversal: Root -> Left -> Right)
    //   - Time Complexity: O(N), where N is the number of nodes in the tree.
    //   - Space Complexity: O(H), where H is the height of the tree (due to the call stack).  In the worst case (skewed tree), H can be N, so it can be O(N).  In a balanced tree, it's O(log N).
    public static void dfsRecursivePreorder(TreeNode node) {
        if (node == null) {
            return; // Base case: if the node is null, we've reached the end of a branch, so we stop.
        }

        System.out.print(node.val + " "); // Process the current node (Root).
        dfsRecursivePreorder(node.left);  // Recursively traverse the left subtree.
        dfsRecursivePreorder(node.right); // Recursively traverse the right subtree.
    }

    // 2. Recursive Depth-First Search (Inorder Traversal: Left -> Root -> Right)
    public static void dfsRecursiveInorder(TreeNode node) {
        if (node == null) {
            return;
        }
        dfsRecursiveInorder(node.left);
        System.out.print(node.val + " ");
        dfsRecursiveInorder(node.right);
    }

    // 3. Recursive Depth-First Search (Postorder Traversal: Left -> Right -> Root)
    public static void dfsRecursivePostorder(TreeNode node) {
        if (node == null) {
            return;
        }
        dfsRecursivePostorder(node.left);
        dfsRecursivePostorder(node.right);
        System.out.print(node.val + " ");
    }



    // 4. Iterative Depth-First Search (Preorder Traversal using a Stack)
    //   - Time Complexity: O(N), where N is the number of nodes.
    //   - Space Complexity: O(H), where H is the height of the tree.  In the worst case, O(N) for a skewed tree.
    public static void dfsIterativeStack(TreeNode root) {
        if (root == null) {
            return;
        }

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root); // Start by pushing the root onto the stack.

        while (!stack.isEmpty()) {
            TreeNode node = stack.pop(); // Get the top node from the stack.
            System.out.print(node.val + " "); // Process the node.

            // Important: Push the right child first, so the left child is processed next.
            if (node.right != null) {
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
            //This ensures that the left child is processed before the right child, maintaining the Preorder traversal order.
        }
    }

    // 5. Iterative Depth-First Search (Postorder Traversal using two Stacks)
    public static void dfsIterativeStackPostorder(TreeNode root) {
        if (root == null)
            return;

        Stack<TreeNode> stack1 = new Stack<>();
        Stack<TreeNode> stack2 = new Stack<>();

        stack1.push(root);

        while (!stack1.isEmpty()) {
            TreeNode temp = stack1.pop();
            stack2.push(temp);

            if (temp.left != null)
                stack1.push(temp.left);
            if (temp.right != null)
                stack1.push(temp.right);
        }

        while (!stack2.isEmpty()) {
            System.out.print(stack2.pop().val + " ");
        }
    }

    // 6. Iterative Depth-First Search (Inorder Traversal using Stack)
    public static void dfsIterativeStackInorder(TreeNode root) {
        if (root == null) {
            return;
        }

        Stack<TreeNode> stack = new Stack<>();
        TreeNode curr = root;

        while (curr != null || !stack.isEmpty()) {
            // Keep going left until you find a null
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }

            // Process the top of the stack
            curr = stack.pop();
            System.out.print(curr.val + " ");

            // Go right
            curr = curr.right;
        }
    }
}

// Definition of a binary tree node.
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
    }
}
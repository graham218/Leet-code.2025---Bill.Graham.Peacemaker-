import java.util.Stack;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;

public class TreeDFS<T> {

    // 1. Recursive DFS - Basic Implementation
    //   - Simplest to understand, uses system stack.
    //   - Good for smaller trees.  Can cause StackOverflowError on very deep trees.
    //   - Real-world use case:  Traversing a file system directory structure.
    public void recursiveDFS(TreeNode<T> node, List<T> result) {
        if (node == null) {
            return; // Base case:  Important to prevent NullPointerExceptions and infinite recursion.
        }
        result.add(node.data); // "Visit" the node (process its data) - PRE-ORDER
        for (TreeNode<T> child : node.children) {
            recursiveDFS(child, result); // Recursively visit each child
        }
        // If you wanted a POST-ORDER traversal, you'd add  result.add(node.data); here instead
        // If you wanted an IN-ORDER traversal (which only makes sense for a *binary* tree),
        // you'd have two children (left and right), and do this:
        // recursiveDFS(node.left, result);
        // result.add(node.data);
        // recursiveDFS(node.right, result);
    }

    // 2. Iterative DFS with Stack - Mimics Recursive Pre-Order
    //   - Uses a stack to avoid recursion, good for larger trees.
    //   - More complex to understand than recursion, but more memory-efficient for deep trees.
    //   - Real-world use case:  Crawling a website (though breadth-first is often preferred to avoid getting stuck in one area).
    public List<T> iterativeDFS(TreeNode<T> root) {
        List<T> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Stack<TreeNode<T>> stack = new Stack<>();
        stack.push(root); // Start with the root node

        while (!stack.isEmpty()) {
            TreeNode<T> node = stack.pop(); // Get the next node
            result.add(node.data);          // Visit the node (pre-order)

            // VERY IMPORTANT:  Push children in *reverse* order to the stack.
            // This ensures they are processed in the correct order (left to right).
            for (int i = node.children.size() - 1; i >= 0; i--) {
                stack.push(node.children.get(i));
            }
        }
        return result;
    }

    // 3. Iterative DFS with Stack - Post-Order Traversal
    //   - A more complex iterative approach.
    //   - Uses two stacks to simulate post-order traversal without recursion.
    //   - Useful when you need to process children *before* the parent.
    //   - Real-world use case:  Evaluating expressions in a compiler.
    public List<T> iterativeDFSPostOrder(TreeNode<T> root) {
        List<T> result = new ArrayList<>();
        if (root == null) return result;

        Stack<TreeNode<T>> stack1 = new Stack<>();
        Stack<TreeNode<T>> stack2 = new Stack<>();

        stack1.push(root);

        while (!stack1.isEmpty()) {
            TreeNode<T> node = stack1.pop();
            stack2.push(node); // Push to the second stack
            for (TreeNode<T> child : node.children) {
                stack1.push(child);
            }
        }
        while (!stack2.isEmpty()) {
            result.add(stack2.pop().data); // Pop from the second stack to get post-order
        }
        return result;
    }

    // 4. DFS with Visited Set (for graphs, but adaptable to trees with cycles)
    //   - Handles cases where the tree might have cycles (though standard trees don't).
    //   - Uses a `visited` set to prevent infinite loops.
    //   - Real-world use case:  Traversing a network graph (where cycles are common).  Useful if you *think* your tree might have back-edges.
    public List<T> dfsWithVisited(TreeNode<T> root) {
        List<T> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Stack<TreeNode<T>> stack = new Stack<>();
        stack.push(root);
        // Using a List<TreeNode<T>> as a visited set.  A HashSet<TreeNode<T>> would be more efficient,
        // but for simplicity and to avoid introducing another data structure, we'll use a List.
        List<TreeNode<T>> visited = new ArrayList<>();

        while (!stack.isEmpty()) {
            TreeNode<T> node = stack.pop();

            if (visited.contains(node)) {
                continue; // Skip if already visited
            }

            visited.add(node);  // Mark as visited
            result.add(node.data); // Visit (pre-order)

            for (int i = node.children.size() - 1; i >= 0; i--) {
                stack.push(node.children.get(i));
            }
        }
        return result;
    }

    // 5.  DFS to find a specific node (Targeted DFS)
    //    -  Stops the search as soon as the target node is found.
    //    -  More efficient than traversing the entire tree if you only need one node.
    //    - Real-world use case:  Searching for a specific file in a directory structure,
    //                           or finding a particular user in a hierarchical organization.
    public TreeNode<T> findNodeDFS(TreeNode<T> root, T target) {
        if (root == null) {
            return null; // Base case: Target not found in this branch
        }

        if (root.data.equals(target)) {
            return root; // Found the target node!
        }

        for (TreeNode<T> child : root.children) {
            TreeNode<T> found = findNodeDFS(child, target); // Recursive call
            if (found != null) {
                return found; // Target found in a child's subtree
            }
        }
        return null; // Target not found in this subtree
    }

    public static void main(String[] args) {
        // Create a sample tree for testing
        TreeNode<String> root = new TreeNode<>("A");
        TreeNode<String> b = new TreeNode<>("B");
        TreeNode<String> c = new TreeNode<>("C");
        TreeNode<String> d = new TreeNode<>("D");
        TreeNode<String> e = new TreeNode<>("E");
        TreeNode<String> f = new TreeNode<>("F");
        TreeNode<String> g = new TreeNode<>("G");

        root.addChild(b);
        root.addChild(c);
        root.addChild(d);
        b.addChild(e);
        b.addChild(f);
        d.addChild(g);

        TreeDFS<String> dfs = new TreeDFS<>();

        // 1. Recursive DFS
        List<String> result1 = new ArrayList<>();
        dfs.recursiveDFS(root, result1);
        System.out.println("Recursive DFS: " + result1); // Output: [A, B, E, F, C, D, G]

        // 2. Iterative DFS
        List<String> result2 = dfs.iterativeDFS(root);
        System.out.println("Iterative DFS: " + result2); // Output: [A, B, E, F, C, D, G]

        // 3. Iterative DFS Post-Order
        List<String> result3 = dfs.iterativeDFSPostOrder(root);
        System.out.println("Iterative DFS Post-Order: " + result3); // Output: [E, F, B, C, G, D, A]

        // 4. DFS with Visited Set (No cycles in this tree, but demonstrates the approach)
        List<String> result4 = dfs.dfsWithVisited(root);
        System.out.println("DFS with Visited Set: " + result4);  // Output: [A, B, E, F, C, D, G]

        // 5. Targeted DFS
        TreeNode<String> foundNode = dfs.findNodeDFS(root, "F");
        if (foundNode != null) {
            System.out.println("Found node with data 'F': " + foundNode.data); // Output: Found node with data 'F': F
        } else {
            System.out.println("Node with data 'F' not found.");
        }

        TreeNode<String> notFoundNode = dfs.findNodeDFS(root, "X");
        if (notFoundNode != null){
            System.out.println("Found node with data 'X': " + notFoundNode.data);
        } else {
            System.out.println("Node with data 'X' not found."); // Output: Node with data 'X' not found.
        }
    }
}

// Definition of a generic tree node.  Using a generic type allows this to work
// with various data types (Integer, String, etc.)
class TreeNode<T> {
    T data;
    List<TreeNode<T>> children;

    public TreeNode(T data) {
        this.data = data;
        this.children = new ArrayList<>();
    }

    public TreeNode(T data, List<TreeNode<T>> children) {
        this.data = data;
        this.children = children;
    }

    // Added method to add children, makes code cleaner.
    public void addChild(TreeNode<T> child) {
        this.children.add(child);
    }
}

// Definition of a binary tree node (used for all approaches)
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

// Helper function to create a sample binary tree for testing
function createSampleTree() {
    const root = new TreeNode(4);
    root.left = new TreeNode(2);
    root.right = new TreeNode(7);
    root.left.left = new TreeNode(1);
    root.left.right = new TreeNode(3);
    root.right.left = new TreeNode(6);
    root.right.right = new TreeNode(9);
    return root;
}

// Helper function to print the tree in a readable format (Inorder Traversal)
function printTree(node) {
  if (!node) {
    return "null";
  }
  return `${node.val} (Left: ${printTree(node.left)}, Right: ${printTree(node.right)})`;
}

// Approach 1: Recursive Approach
function invertTreeRecursive(root) {
    if (!root) {
        return null;
    }
    // Swap left and right children
    let temp = root.left;
    root.left = root.right;
    root.right = temp;

    // Recursively invert the left and right subtrees
    invertTreeRecursive(root.left);
    invertTreeRecursive(root.right);

    return root;
}

// Approach 2: Iterative Approach using a Stack
function invertTreeIterativeStack(root) {
    if (!root) {
        return null;
    }

    const stack = [root];
    while (stack.length > 0) {
        const node = stack.pop();

        // Swap left and right children
        let temp = node.left;
        node.left = node.right;
        node.right = temp;

        // Push the left and right children onto the stack if they exist
        if (node.left) {
            stack.push(node.left);
        }
        if (node.right) {
            stack.push(node.right);
        }
    }
    return root;
}

// Approach 3: Iterative Approach using a Queue (Breadth-First Search)
function invertTreeIterativeQueue(root) {
    if (!root) {
        return null;
    }

    const queue = [root];
    while (queue.length > 0) {
        const node = queue.shift(); // Dequeue

        // Swap left and right children
        let temp = node.left;
        node.left = node.right;
        node.right = temp;

        // Enqueue the left and right children if they exist
        if (node.left) {
            queue.push(node.left);
        }
        if (node.right) {
            queue.push(node.right);
        }
    }
    return root;
}

// Approach 4: Recursive Approach (Alternative Swap)
function invertTreeRecursiveAlt(root) {
    if (!root) return null;
    [root.left, root.right] = [invertTreeRecursiveAlt(root.right), invertTreeRecursiveAlt(root.left)];
    return root;
}

// Approach 5: Using a helper function and recursion
function invertTreeHelper(root) {
  if (!root) {
    return null;
  }

  function invert(node) {
    if (!node) return;
    let temp = node.left;
    node.left = node.right;
    node.right = temp;
    invert(node.left);
    invert(node.right);
  }
  invert(root);
  return root;
}

// Example usage and output
const originalTree = createSampleTree();

console.log("Original Tree:", printTree(originalTree));

// Approach 1: Recursive
const invertedTreeRecursive = invertTreeRecursive(createSampleTree()); // Create a new tree to avoid modifying the original
console.log("Inverted Tree (Recursive):", printTree(invertedTreeRecursive));

// Approach 2: Iterative (Stack)
const invertedTreeIterativeStackResult = invertTreeIterativeStack(createSampleTree());
console.log("Inverted Tree (Iterative - Stack):", printTree(invertedTreeIterativeStackResult));

// Approach 3: Iterative (Queue)
const invertedTreeIterativeQueueResult = invertTreeIterativeQueue(createSampleTree());
console.log("Inverted Tree (Iterative - Queue):", printTree(invertedTreeIterativeQueueResult));

// Approach 4: Recursive (Alternative Swap)
const invertedTreeRecursiveAltResult = invertTreeRecursiveAlt(createSampleTree());
console.log("Inverted Tree (Recursive - Alternative Swap):", printTree(invertedTreeRecursiveAltResult));

// Approach 5: Helper Function
const invertedTreeHelperResult = invertTreeHelper(createSampleTree());
console.log("Inverted Tree (Helper Function):", printTree(invertedTreeHelperResult));

/**
 * Invert Binary Tree - 5 Approaches
 *
 * A binary tree node has a value, a left child, and a right child.
 *
 * 1. Recursive Approach
 * 2. Iterative Approach (using a stack)
 * 3. Iterative Approach (using a queue)
 * 4. Recursive Approach (Simplified)
 * 5. Morris Traversal (Threaded Tree) - [Advanced, for discussion]
 */

// Definition of a binary tree node.
function TreeNode(val, left, right) {
  this.val = (val === undefined ? 0 : val);
  this.left = (left === undefined ? null : left);
  this.right = (right === undefined ? null : right);
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

// Helper function to perform an inorder traversal (Left, Root, Right)
// Used to verify the tree structure after inversion
function inorderTraversal(root) {
  const result = [];
  if (root) {
    result.push(...inorderTraversal(root.left));
    result.push(root.val);
    result.push(...inorderTraversal(root.right));
  }
  return result;
}

// Helper function to visualize the tree structure (for debugging)
function visualizeTree(root, indent = "") {
  if (root) {
    console.log(indent + root.val);
    visualizeTree(root.left, indent + "  ");
    visualizeTree(root.right, indent + "  ");
  }
}

/**
 * 1. Recursive Approach
 *
 * - Base Case: If the node is null, return.
 * - Recursive Step:
 * - Swap the left and right children of the current node.
 * - Recursively call the function for the left and right children.
 *
 * Time Complexity: O(n), where n is the number of nodes in the tree.
 * Space Complexity: O(h), where h is the height of the tree (due to the call stack).  In the worst case (skewed tree), h = n, so O(n).  In the best case (balanced tree), h = log n, so O(log n).
 */
function invertTreeRecursive(root) {
  if (!root) {
    return null;
  }

  // Swap left and right children
  const temp = root.left;
  root.left = root.right;
  root.right = temp;

  // Recursively invert the left and right subtrees
  invertTreeRecursive(root.left);
  invertTreeRecursive(root.right);

  return root;
}

/**
 * 2. Iterative Approach (using a stack)
 *
 * - Use a stack to store nodes to be processed.
 * - Push the root node onto the stack.
 * - While the stack is not empty:
 * - Pop a node from the stack.
 * - Swap the left and right children of the node.
 * - Push the left and right children (if they exist) onto the stack.
 *
 * Time Complexity: O(n), where n is the number of nodes in the tree.
 * Space Complexity: O(h), where h is the height of the tree.  In the worst case (skewed tree), h = n, so O(n). In the best case (balanced tree), h = log n, so O(log n).
 */
function invertTreeIterativeStack(root) {
  if (!root) {
    return null;
  }

  const stack = [root];

  while (stack.length > 0) {
    const node = stack.pop();

    // Swap left and right children
    const temp = node.left;
    node.left = node.right;
    node.right = temp;

    // Push children onto the stack
    if (node.left) {
      stack.push(node.left);
    }
    if (node.right) {
      stack.push(node.right);
    }
  }

  return root;
}

/**
 * 3. Iterative Approach (using a queue)
 *
 * - Use a queue to store nodes to be processed.
 * - Enqueue the root node.
 * - While the queue is not empty:
 * - Dequeue a node from the queue.
 * - Swap the left and right children of the node.
 * - Enqueue the left and right children (if they exist) into the queue.
 *
 * Time Complexity: O(n), where n is the number of nodes in the tree.
 * Space Complexity: O(w), where w is the maximum width of the tree. In the worst case (complete binary tree), w = n/2, so O(n). In the best case (skewed tree), w = 1, so O(1).
 */
function invertTreeIterativeQueue(root) {
  if (!root) {
    return null;
  }

  const queue = [root];

  while (queue.length > 0) {
    const node = queue.shift(); // Dequeue

    // Swap left and right children
    const temp = node.left;
    node.left = node.right;
    node.right = temp;

    // Enqueue children
    if (node.left) {
      queue.push(node.left);
    }
    if (node.right) {
      queue.push(node.right);
    }
  }

  return root;
}

/**
 * 4. Recursive Approach (Simplified)
 *
 * This is a more concise version of the recursive approach.
 */
function invertTreeRecursiveSimplified(root) {
  if (!root) return null;
  [root.left, root.right] = [invertTreeRecursiveSimplified(root.right), invertTreeRecursiveSimplified(root.left)];
  return root;
}

/**
 * 5. Morris Traversal (Threaded Tree) - [Advanced, for discussion]
 *
 * - This approach inverts the tree in-place without using recursion or a stack/queue.
 * - It modifies the tree structure temporarily by creating "threads" (links from a node's right child to its inorder successor).
 * - After inversion, the threads are removed to restore the original tree structure.
 * - This method is more space-efficient (O(1) space) but is more complex to implement.
 *
 * Time Complexity: O(n), where n is the number of nodes in the tree.
 * Space Complexity: O(1) - Constant space.
 *
 * **Note:** Morris traversal modifies the tree structure during the process.  It's generally not recommended for scenarios where you need to preserve the original tree structure, unless you make a copy first.  This is more of an academic exercise or an optimization for very specific use cases where memory is extremely limited and in-place modification is acceptable.  It's more complex and harder to debug.
 */
function invertTreeMorris(root) {
  let current = root;
  while (current) {
    if (current.left) {
      let predecessor = current.left;
      while (predecessor.right && predecessor.right !== current) {
        predecessor = predecessor.right;
      }

      if (!predecessor.right) {
        // Create the thread
        predecessor.right = current;

        // Move to the left child
        current = current.left;
      } else {
        // Remove the thread
        predecessor.right = null;

        // Swap children and move to the right child
        const temp = current.left;
        current.left = current.right;
        current.right = temp;
        current = current.right;
      }
    } else {
      // No left child, swap children and move to the right
      const temp = current.left;
      current.left = current.right;
      current.right = temp;
      current = current.right;
    }
  }
  return root;
}



// --- Test Cases and Output ---
const initialTree = createSampleTree();

console.log("Original Tree (Visualization):");
visualizeTree(initialTree);
console.log("Original Tree (Inorder Traversal):", inorderTraversal(initialTree));
console.log("\n");

// 1. Recursive Approach
const tree1 = createSampleTree(); // Get a fresh copy
const invertedTree1 = invertTreeRecursive(tree1);
console.log("1. Recursive Inversion (Visualization):");
visualizeTree(invertedTree1);
console.log("1. Recursive Inversion (Inorder Traversal):", inorderTraversal(invertedTree1));
console.log("\n");

// 2. Iterative Approach (Stack)
const tree2 = createSampleTree();  // Get a fresh copy
const invertedTree2 = invertTreeIterativeStack(tree2);
console.log("2. Iterative Inversion (Stack) (Visualization):");
visualizeTree(invertedTree2);
console.log("2. Iterative Inversion (Stack) (Inorder Traversal):", inorderTraversal(invertedTree2));
console.log("\n");

// 3. Iterative Approach (Queue)
const tree3 = createSampleTree(); // Get a fresh copy
const invertedTree3 = invertTreeIterativeQueue(tree3);
console.log("3. Iterative Inversion (Queue) (Visualization):");
visualizeTree(invertedTree3);
console.log("3. Iterative Inversion (Queue) (Inorder Traversal):", inorderTraversal(invertedTree3));
console.log("\n");

// 4. Recursive Approach (Simplified)
const tree4 = createSampleTree();
const invertedTree4 = invertTreeRecursiveSimplified(tree4);
console.log("4. Recursive Inversion (Simplified) (Visualization):");
visualizeTree(invertedTree4);
console.log("4. Recursive Inversion (Simplified) (Inorder Traversal):", inorderTraversal(invertedTree4));
console.log("\n");

// 5. Morris Traversal (Threaded Tree)
const tree5 = createSampleTree();
const invertedTree5 = invertTreeMorris(tree5);
console.log("5. Morris Traversal Inversion (Visualization):");
visualizeTree(invertedTree5);
console.log("5. Morris Traversal Inversion (Inorder Traversal):", inorderTraversal(invertedTree5));
console.log("\n");

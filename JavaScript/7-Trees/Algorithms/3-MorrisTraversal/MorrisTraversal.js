// Definition of a binary tree node (used across all approaches)
class TreeNode {
  constructor(val) {
    this.val = val;
    this.left = null;
    this.right = null;
  }
}

// Helper function to create a sample binary tree
function createSampleTree() {
  const root = new TreeNode(1);
  root.left = new TreeNode(2);
  root.right = new TreeNode(3);
  root.left.left = new TreeNode(4);
  root.left.right = new TreeNode(5);
  root.right.left = new TreeNode(6);
  root.right.right = new TreeNode(7);
  return root;
}

// Approach 1: Morris Inorder Traversal (Iterative with Threaded Tree)
function morrisInorder(root) {
  const result = [];
  let current = root;

  while (current) {
    if (!current.left) {
      result.push(current.val);
      current = current.right;
    } else {
      let predecessor = current.left;
      while (predecessor.right && predecessor.right !== current) {
        predecessor = predecessor.right;
      }

      if (!predecessor.right) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        result.push(current.val);
        current = current.right;
      }
    }
  }
  return result;
}

// Approach 2: Morris Preorder Traversal (Iterative with Threaded Tree)
function morrisPreorder(root) {
  const result = [];
  let current = root;

  while (current) {
    if (!current.left) {
      result.push(current.val); // Visit before moving right
      current = current.right;
    } else {
      let predecessor = current.left;
      while (predecessor.right && predecessor.right !== current) {
        predecessor = predecessor.right;
      }

      if (!predecessor.right) {
        predecessor.right = current;
        result.push(current.val); // Visit before moving left
        current = current.left;
      } else {
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  return result;
}

// Approach 3: Morris Postorder Traversal (Iterative with Reverse) - Tricky
function morrisPostorder(root) {
  const result = [];
  let current = root;

  while (current) {
    if (!current.right) {
      result.unshift(current.val); // Add to the beginning for postorder-like visit
      current = current.left;
    } else {
      let successor = current.right;
      while (successor.left && successor.left !== current) {
        successor = successor.left;
      }

      if (!successor.left) {
        successor.left = current;
        current = current.right;
      } else {
        successor.left = null;
        // Reverse and add the reversed nodes.
        const tempResult = [];
        let temp = current.right;
        let prev = current;

        while (temp)
        {
          let next = temp.left;
          temp.left = prev;
          prev = temp;
          temp = next;
        }

        temp = prev;
        while(temp != current)
        {
          tempResult.push(temp.val);
          temp = temp.left;
        }
        result.unshift(...tempResult); // Add to the beginning
        current = current.left;
      }
    }
  }
  return result;
}

// Approach 4:  Inorder Traversal using Stack (Comparison for Morris)
function inorderWithStack(root) {
    const result = [];
    const stack = [];
    let current = root;

    while (current || stack.length > 0) {
        while (current) {
            stack.push(current);
            current = current.left;
        }
        current = stack.pop();
        result.push(current.val);
        current = current.right;
    }
    return result;
}

// Approach 5: Preorder Traversal using Stack (Comparison for Morris)
function preorderWithStack(root) {
  const result = [];
  const stack = [root];

  if (!root) return result;

  while (stack.length > 0) {
    const node = stack.pop();
    result.push(node.val); // Visit the node

    if (node.right) {
      stack.push(node.right);
    }
    if (node.left) {
      stack.push(node.left);
    }
  }
  return result;
}

// Main function to demonstrate the traversals
function main() {
  const root = createSampleTree();

  console.log("Sample Tree (for reference):");
  // You can't directly print the tree structure in a pretty format with console.log
  //  but you could use a visualizer or a custom printing function if needed.

  console.log("\n1. Morris Inorder Traversal:", morrisInorder(root));
  console.log("   Inorder Traversal (Stack):", inorderWithStack(root)); // For comparison

  console.log("\n2. Morris Preorder Traversal:", morrisPreorder(root));
  console.log("   Preorder Traversal (Stack):", preorderWithStack(root)); // For comparison

  console.log("\n3. Morris Postorder Traversal:", morrisPostorder(root));
  // No simple stack-based postorder for direct comparison, it's more complex.
}

// Run the main function
main();

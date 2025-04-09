// Define the TreeNode class
class TreeNode {
  constructor(val) {
    this.val = val;
    this.left = null;
    this.right = null;
  }
}

// 1. Morris Traversal for Inorder (Iterative, Threaded Binary Tree)
//   - Real-world application:  Iterating through a sorted list of products in an e-commerce system.  In-order traversal ensures products are displayed in the correct order (e.g., by price, name).
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

// 2. Morris Traversal for Preorder (Iterative, Threaded Binary Tree)
//   - Real-world application:  Serializing a hierarchical data structure (like a document with nested sections) for storage or transmission. Pre-order traversal ensures that parent nodes are processed before their children, preserving the structure.
function morrisPreorder(root) {
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
        result.push(current.val); // Key difference for Preorder: visit *before* creating the thread
        current = current.left;
      } else {
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  return result;
}

// 3.  Morris Traversal for Postorder (Iterative, Threaded Binary Tree) - Tricky one!
//   - Real-world application:  Evaluating expressions in a compiler.  Post-order traversal allows you to process operands before operators.  Less common with Morris, usually stack-based, but possible.
function morrisPostorder(root) {
    const result = [];
    let current = root;

    while (current) {
        if (!current.right) {
            result.unshift(current.val); // Add to the *beginning* for postorder
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
                 // Reverse the path and add nodes
                const tempResult = [];
                let temp = current.right;
                while (temp !== successor) {
                    tempResult.unshift(temp.val);
                    temp = temp.left;
                }
                tempResult.unshift(successor.val);  // Add the successor's value
                result.unshift(...tempResult);
                result.unshift(current.val); // Add current node value
                current = current.left;
            }
        }
    }
    return result;
}



// 4. Morris Traversal for finding the Kth smallest element
//   - Real-world application:  Finding the median or specific percentile of data in a database without sorting the entire dataset.  This is useful for performance optimization in large databases.
function morrisKthSmallest(root, k) {
  let count = 0;
  let result = null;
  let current = root;

  while (current) {
    if (!current.left) {
      count++;
      if (count === k) {
        result = current.val;
        break;
      }
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
        count++;
        if (count === k) {
          result = current.val;
          break;
        }
        current = current.right;
      }
    }
  }
  return result;
}

// 5. Morris Traversal for checking if a binary tree is a Binary Search Tree (BST)
//  - Real-world application:  Validating user-uploaded data to ensure it conforms to a specific hierarchical structure, such as organizational charts or configuration files represented as trees.
function isBST(root) {
    let current = root;
    let prev = -Infinity; // Initialize prev to negative infinity
    let isBSTResult = true;

    while (current) {
        if (!current.left) {
            if (current.val <= prev) {
                isBSTResult = false;
                break;
            }
            prev = current.val;
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
                if (current.val <= prev) {
                    isBSTResult = false;
                    break;
                }
                prev = current.val;
                current = current.right;
            }
        }
    }
    return isBSTResult;
}



// Create a sample binary tree
const root = new TreeNode(4);
root.left = new TreeNode(2);
root.right = new TreeNode(6);
root.left.left = new TreeNode(1);
root.left.right = new TreeNode(3);
root.right.left = new TreeNode(5);
root.right.right = new TreeNode(7);

// Create a sample non-BST tree
const root2 = new TreeNode(1);
root2.left = new TreeNode(2);
root2.right = new TreeNode(3);
root2.left.left = new TreeNode(4);
root2.left.right = new TreeNode(5);
root2.right.left = new TreeNode(6);
root2.right.right = new TreeNode(7);


// Perform Morris Inorder Traversal
console.log("Morris Inorder Traversal:", morrisInorder(root)); // Output: [1, 2, 3, 4, 5, 6, 7]

// Perform Morris Preorder Traversal
console.log("Morris Preorder Traversal:", morrisPreorder(root)); // Output: [4, 2, 1, 3, 6, 5, 7]

// Perform Morris Postorder Traversal
console.log("Morris Postorder Traversal:", morrisPostorder(root));

// Find the 3rd smallest element
const k = 3;
console.log(`Kth smallest (${k}):`, morrisKthSmallest(root, k)); // Output: 3

// Check if the tree is a BST
console.log("Is BST:", isBST(root));
console.log("Is BST:", isBST(root2));

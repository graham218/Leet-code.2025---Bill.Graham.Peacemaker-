// Definition of a binary tree node (used across all approaches)
function TreeNode(val) {
    this.val = val;
    this.left = null;
    this.right = null;
}

// Helper function to build a sample binary tree for testing
function buildSampleTree() {
    const root = new TreeNode(3);
    root.left = new TreeNode(5);
    root.right = new TreeNode(1);
    root.left.left = new TreeNode(6);
    root.left.right = new TreeNode(2);
    root.right.left = new TreeNode(0);
    root.right.right = new TreeNode(8);
    root.left.right.left = new TreeNode(7);
    root.left.right.right = new TreeNode(4);
    return root;
}

let treeRoot = buildSampleTree(); // Build the tree once, use it for all methods
let p = treeRoot.left; // Node with value 5
let q = treeRoot.right; // Node with value 1
let p2 = treeRoot.left.left; // Node with value 6
let q2 = treeRoot.left.right.right; // Node with value 4

// 1. Recursive Approach
//   - Find paths to p and q, then compare them to find the last common node.
function findPath(root, target, path) {
    if (!root) return false;

    path.push(root);

    if (root === target) return true;

    if (findPath(root.left, target, path) || findPath(root.right, target, path)) {
        return true;
    }

    path.pop();
    return false;
}

function lowestCommonAncestorRecursive(root, p, q) {
    const pathP = [];
    const pathQ = [];

    findPath(root, p, pathP);
    findPath(root, q, pathQ);

    let lca = null;
    let i = 0;
    while (i < pathP.length && i < pathQ.length && pathP[i] === pathQ[i]) {
        lca = pathP[i];
        i++;
    }
    return lca;
}

console.log("1. Recursive Approach:");
console.log("LCA (5, 1):", lowestCommonAncestorRecursive(treeRoot, p, q).val); // Output: 3
console.log("LCA (6, 4):", lowestCommonAncestorRecursive(treeRoot, p2, q2).val); // Output: 5

// 2. Iterative Approach using Parent Pointers
//   - Use a stack to traverse the tree, keeping track of parent nodes.
//   - Store parent pointers for each node in a map.
//   - Find the paths to p and q using the parent pointers.
//   - Find the LCA by comparing the paths.

function lowestCommonAncestorIterative(root, p, q) {
    const stack = [root];
    const parentMap = new Map();
    parentMap.set(root, null); // Parent of root is null

    // Iterate until we find both p and q
    while (!parentMap.has(p) || !parentMap.has(q)) {
        const node = stack.pop();

        if (node.left) {
            parentMap.set(node.left, node);
            stack.push(node.left);
        }
        if (node.right) {
            parentMap.set(node.right, node);
            stack.push(node.right);
        }
    }

    // Get the path to p
    const pathP = [];
    while (p) {
        pathP.push(p);
        p = parentMap.get(p);
    }

    // Get the path to q
    const pathQ = [];
    while (q) {
        pathQ.push(q);
        q = parentMap.get(q);
    }

    // Find the LCA
    let lca = null;
    let i = pathP.length - 1;
    let j = pathQ.length - 1;
    while (i >= 0 && j >= 0 && pathP[i] === pathQ[j]) {
        lca = pathP[i];
        i--;
        j--;
    }
    return lca;
}

console.log("\n2. Iterative Approach using Parent Pointers:");
console.log("LCA (5, 1):", lowestCommonAncestorIterative(treeRoot, p, q).val); // Output: 3
console.log("LCA (6, 4):", lowestCommonAncestorIterative(treeRoot, p2, q2).val); // Output: 5

// 3. Optimized Recursive Approach (Without Path Storage)
//    - A more efficient recursive approach that doesn't require storing paths.
//    - If the current node is either p or q, or if the LCA is found in one subtree,
//      return the current node.
function lowestCommonAncestorOptimized(root, p, q) {
    if (!root || root === p || root === q) {
        return root;
    }

    const leftLCA = lowestCommonAncestorOptimized(root.left, p, q);
    const rightLCA = lowestCommonAncestorOptimized(root.right, p, q);

    if (leftLCA && rightLCA) {
        return root; // Found LCA: p and q are in different subtrees
    }

    return leftLCA || rightLCA; // p and q are in the same subtree, or one is the ancestor of the other
}

console.log("\n3. Optimized Recursive Approach:");
console.log("LCA (5, 1):", lowestCommonAncestorOptimized(treeRoot, p, q).val); // Output: 3
console.log("LCA (6, 4):", lowestCommonAncestorOptimized(treeRoot, p2, q2).val); // Output: 5

// 4. Iterative Approach using Morris Traversal
//    -  A tree traversal without using stack or recursion.  It's more complex.
//    -  Find LCA of two nodes in a binary tree using Morris traversal.
function lowestCommonAncestorMorris(root, p, q) {
  let current = root;
  let pAncestor = null;
  let qAncestor = null;

  // Function to find a node and store its ancestors
  const findNodeAndAncestors = (target) => {
    current = root;
    let ancestor = null;
    while (current) {
      if (current === target) {
        ancestor = current;
        break;
      } else if (target.val < current.val) {
        ancestor = current;
        current = current.left;
      } else {
        ancestor = current;
        current = current.right;
      }
    }
    return ancestor;
  };

  pAncestor = findNodeAndAncestors(p);
  qAncestor = findNodeAndAncestors(q);

  if (!pAncestor || !qAncestor) return null; // Handle cases where p or q is not in the tree

  const getPath = (node) => {
        const path = [];
        current = root;
        while(current && current != node){
            path.push(current);
            if(node.val < current.val){
                current = current.left;
            }
            else{
                current = current.right;
            }
        }
        path.push(node);
        return path;
  }
  const pathP = getPath(p);
  const pathQ = getPath(q);

  let lca = null;
  let i = 0;
  while (i < pathP.length && i < pathQ.length && pathP[i] === pathQ[i]) {
    lca = pathP[i];
    i++;
  }
  return lca;
}

console.log("\n4. Iterative Approach using Morris Traversal:");
console.log("LCA (5, 1):", lowestCommonAncestorMorris(treeRoot, p, q).val);
console.log("LCA (6, 4):", lowestCommonAncestorMorris(treeRoot, p2, q2).val);

// 5. Using Lowest Common Ancestor of a Binary Tree III (with parent pointers)
//    -  This approach is specifically for trees where each node has a parent pointer.
//    -  The provided example tree does not have parent pointers, so we'll create a new one.
//    -  This is NOT a standard LCA solution, but a solution to a specific problem.
function TreeNodeWithParent(val) {
        this.val = val;
        this.left = null;
        this.right = null;
        this.parent = null;
}

function buildTreeWithParentPointers() {
    const root = new TreeNodeWithParent(3);
    const node5 = new TreeNodeWithParent(5);
    const node1 = new TreeNodeWithParent(1);
    const node6 = new TreeNodeWithParent(6);
    const node2 = new TreeNodeWithParent(2);
    const node0 = new TreeNodeWithParent(0);
    const node8 = new TreeNodeWithParent(8);
    const node7 = new TreeNodeWithParent(7);
    const node4 = new TreeNodeWithParent(4);

    root.left = node5;
    root.right = node1;
    node5.left = node6;
    node5.right = node2;
    node1.left = node0;
    node1.right = node8;
    node2.left = node7;
    node2.right = node4;

    node5.parent = root;
    node1.parent = root;
    node6.parent = node5;
    node2.parent = node5;
    node0.parent = node1;
    node8.parent = node1;
    node7.parent = node2;
    node4.parent = node2;

    return root;
}
function lowestCommonAncestorWithParentPointers(p, q) {
    const pathP = [];
    const pathQ = [];

    // Traverse up to the root from p and q, storing the path
    while (p) {
        pathP.push(p);
        p = p.parent;
    }
    while (q) {
        pathQ.push(q);
        q = q.parent;
    }

    // Find the common ancestor
    let lca = null;
    let i = pathP.length - 1;
    let j = pathQ.length - 1;
    while (i >= 0 && j >= 0 && pathP[i] === pathQ[j]) {
        lca = pathP[i];
        i--;
        j--;
    }
    return lca;
}
let treeRootWithParent = buildTreeWithParentPointers();
let pWithParent = treeRootWithParent.left;  // Node 5
let qWithParent = treeRootWithParent.right; // Node 1
let p2WithParent = treeRootWithParent.left.left; // Node 6
let q2WithParent = treeRootWithParent.left.right.right;  // Node 4

console.log("\n5. Using Parent Pointers:");
console.log("LCA (5, 1):", lowestCommonAncestorWithParentPointers(pWithParent, qWithParent).val);
console.log("LCA (6, 4):", lowestCommonAncestorWithParentPointers(p2WithParent, q2WithParent).val);

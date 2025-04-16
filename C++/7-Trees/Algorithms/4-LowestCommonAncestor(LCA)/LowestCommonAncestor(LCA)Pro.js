// Definition of a binary tree node (used across all approaches)
class TreeNode {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
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

let sampleTreeRoot = buildSampleTree(); // Build the tree once, use it for all examples
let p = sampleTreeRoot.left; // Node with value 5
let q = sampleTreeRoot.right; // Node with value 1

// Approach 1: Recursive Approach with Parent Pointers (Common in Tree Data Structure Libraries)
//  - Uses a helper to find the path to each node, then compares paths.
//  - Not the most efficient, but very clear.
function findPath(root, target, path) {
    if (!root) {
        return false;
    }

    path.push(root);

    if (root === target) {
        return true;
    }

    if (findPath(root.left, target, path) || findPath(root.right, target, path)) {
        return true;
    }

    path.pop(); // Backtrack if target not found in this subtree
    return false;
}

function lowestCommonAncestor1(root, p, q) {
    const pathP = [];
    const pathQ = [];

    findPath(root, p, pathP);
    findPath(root, q, pathQ);

    let i = 0;
    while (i < pathP.length && i < pathQ.length && pathP[i] === pathQ[i]) {
        i++;
    }
    return pathP[i - 1];
}

// Approach 2: Recursive Approach (Most Common Interview Solution)
//   - Efficiently traverses the tree only as needed.
//   - Directly finds the LCA during the traversal.
function lowestCommonAncestor2(root, p, q) {
    if (!root || root === p || root === q) {
        return root;
    }

    const leftLCA = lowestCommonAncestor2(root.left, p, q);
    const rightLCA = lowestCommonAncestor2(root.right, p, q);

    if (leftLCA && rightLCA) {
        return root; // Found LCA: one node in each subtree
    } else {
        return leftLCA || rightLCA; // One node is ancestor of the other, or both in one subtree
    }
}


// Approach 3: Iterative with Parent Pointers (Useful when the tree allows modification)
//    - Uses a stack
//    - Requires extra space for the stack and the parent pointers, but is iterative.
function lowestCommonAncestor3(root, p, q) {
    const stack = [root];
    const parentMap = new Map(); // Node -> Parent
    parentMap.set(root, null);

    // 1. Build parent pointers for all nodes needed to reach p and q.
    while ((!parentMap.has(p) || !parentMap.has(q)) && stack.length > 0) {
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

    // 2. Trace path from p to root, storing visited nodes.
    const pAncestors = new Set();
    while (p) {
        pAncestors.add(p);
        p = parentMap.get(p);
    }

    // 3. Trace path from q to root, finding the first common ancestor.
    while (q) {
        if (pAncestors.has(q)) {
            return q;
        }
        q = parentMap.get(q);
    }

    return null; // Should not reach here in a valid tree
}

// Approach 4:  Morris Traversal (Threaded Binary Tree) - Space Optimized (Advanced)
//     -  Most space-efficient, modifies the tree temporarily (good for in-place).
//     -  More complex to understand but important for systems with limited memory.
function lowestCommonAncestor4(root, p, q) {
    let current = root;
    let lca = null;

    while (current) {
        if (isAncestor(current, p) && isAncestor(current, q)) {
            lca = current;
            if (current.val > p.val && current.val > q.val) {
                current = current.left;
            }
            else{
                current = current.right;
            }
        }
        else if (isAncestor(current, p))
        {
             current = current.right;
        }
        else if (isAncestor(current, q)){
            current = current.right
        }
        else {
            current = (current.val > p.val && current.val > q.val) ? current.left : current.right;
        }
    }
    return lca;
}

function isAncestor(ancestor, node) {
    if (!ancestor) return false;
    if (ancestor === node) return true;
    return isAncestor(ancestor.left, node) || isAncestor(ancestor.right, node);
}

// Approach 5: Using Lowest Common Ancestor with Parent Array (Useful for specific tree problems)
function lowestCommonAncestor5(root, p, q) {
    const parent = new Map();
    const depth = new Map();
    let maxDepth = 0;

    function dfs(node, d, par) {
        if (!node) return;
        parent.set(node, par);
        depth.set(node, d);
        maxDepth = Math.max(maxDepth, d);
        dfs(node.left, d + 1, node);
        dfs(node.right, d + 1, node);
    }

    dfs(root, 0, null);

    let pDepth = depth.get(p);
    let qDepth = depth.get(q);

    while (pDepth > qDepth) {
        p = parent.get(p);
        pDepth--;
    }

    while (qDepth > pDepth) {
        q = parent.get(q);
        qDepth--;
    }

    while (p !== q) {
        p = parent.get(p);
        q = parent.get(q);
    }

    return p;
}

// Example usage and output using console.log
console.log("Approach 1 (Recursive with Path):", lowestCommonAncestor1(sampleTreeRoot, p, q));
console.log("Approach 2 (Recursive):", lowestCommonAncestor2(sampleTreeRoot, p, q));
console.log("Approach 3 (Iterative with Parent Pointers):", lowestCommonAncestor3(sampleTreeRoot, p, q));
console.log("Approach 4 (Morris Traversal):", lowestCommonAncestor4(sampleTreeRoot, p, q));
console.log("Approach 5 (Parent Array):", lowestCommonAncestor5(sampleTreeRoot, p, q));

// Additional test case to show LCA when one node is the ancestor of the other
let p2 = sampleTreeRoot.left; // Node 5
let q2 = sampleTreeRoot.left.right.left; // Node 7
console.log("\nAdditional Test Case (5 and 7):");
console.log("Approach 1 (Recursive with Path):", lowestCommonAncestor1(sampleTreeRoot, p2, q2));
console.log("Approach 2 (Recursive):", lowestCommonAncestor2(sampleTreeRoot, p2, q2));
console.log("Approach 3 (Iterative with Parent Pointers):", lowestCommonAncestor3(sampleTreeRoot, p2, q2));
console.log("Approach 4 (Morris Traversal):", lowestCommonAncestor4(sampleTreeRoot, p2, q2));
console.log("Approach 5 (Parent Array):", lowestCommonAncestor5(sampleTreeRoot, p2, q2));

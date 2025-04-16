// Definition for a binary tree node.
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

/**
 * Given the root of a binary tree, return its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 3
 *
 * Example 2:
 *
 * Input: root = [1,null,2]
 * Output: 2
 *
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [0, 104].
 * -100 <= Node.val <= 100
 */

// Approach 1: Recursive Depth First Search (DFS)
const maxDepthDFS = (root) => {
    if (!root) {
        return 0;
    }
    const leftDepth = maxDepthDFS(root.left);
    const rightDepth = maxDepthDFS(root.right);
    return Math.max(leftDepth, rightDepth) + 1;
};

// Approach 2: Iterative Breadth First Search (BFS)
const maxDepthBFS = (root) => {
    if (!root) {
        return 0;
    }
    let queue = [root];
    let depth = 0;

    while (queue.length > 0) {
        depth++;
        const levelSize = queue.length;
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            if (node.left) {
                queue.push(node.left);
            }
            if (node.right) {
                queue.push(node.right);
            }
        }
    }
    return depth;
};

// Approach 3: Recursive Depth First Search (DFS) - alternative
const maxDepthDFSAlt = (root, depth = 0) => {
  if (!root) {
    return depth;
  }
  const leftDepth = maxDepthDFSAlt(root.left, depth + 1);
  const rightDepth = maxDepthDFSAlt(root.right, depth + 1);
  return Math.max(leftDepth, rightDepth);
};

// Approach 4: Iterative DFS using a stack
const maxDepthDFSIterative = (root) => {
    if (!root) return 0;

    const stack = [[root, 1]]; // Store node and its depth
    let maxDepth = 0;

    while (stack.length > 0) {
        const [node, depth] = stack.pop();
        maxDepth = Math.max(maxDepth, depth);

        if (node.left) {
            stack.push([node.left, depth + 1]);
        }
        if (node.right) {
            stack.push([node.right, depth + 1]);
        }
    }
    return maxDepth;
};

// Approach 5: Using a helper function for recursion
const maxDepthHelper = (root) => {
    if (!root) return 0;

    function dfs(node) {
        if (!node) return 0;
        let leftDepth = dfs(node.left);
        let rightDepth = dfs(node.right);
        return Math.max(leftDepth, rightDepth) + 1;
    }
    return dfs(root);
};
// Create a sample binary tree for testing
const root = new TreeNode(3);
root.left = new TreeNode(9);
root.right = new TreeNode(20);
root.right.left = new TreeNode(15);
root.right.right = new TreeNode(7);

// Test the functions and print the output
console.log("Maximum Depth (DFS):", maxDepthDFS(root));
console.log("Maximum Depth (BFS):", maxDepthBFS(root));
console.log("Maximum Depth (DFS Alternative):", maxDepthDFSAlt(root));
console.log("Maximum Depth (DFS Iterative):", maxDepthDFSIterative(root));
console.log("Maximum Depth (Helper):", maxDepthHelper(root));

// Create another sample binary tree for testing
const root2 = new TreeNode(1);
root2.right = new TreeNode(2);

console.log("Maximum Depth (DFS) - case 2:", maxDepthDFS(root2));
console.log("Maximum Depth (BFS) - case 2:", maxDepthBFS(root2));
console.log("Maximum Depth (DFS Alternative) - case 2:", maxDepthDFSAlt(root2));
console.log("Maximum Depth (DFS Iterative) - case 2:", maxDepthDFSIterative(root2));
console.log("Maximum Depth (Helper) - case 2:", maxDepthHelper(root2));

const emptyTree = null;
console.log("Maximum Depth (DFS) - empty tree:", maxDepthDFS(emptyTree));
console.log("Maximum Depth (BFS) - empty tree:", maxDepthBFS(emptyTree));
console.log("Maximum Depth (DFS Alternative) - empty tree:", maxDepthDFSAlt(emptyTree));
console.log("Maximum Depth (DFS Iterative) - empty tree:", maxDepthDFSIterative(emptyTree));
console.log("Maximum Depth (Helper) - empty tree:", maxDepthHelper(emptyTree));

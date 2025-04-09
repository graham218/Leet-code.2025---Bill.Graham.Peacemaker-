// Definition for a binary tree node.
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

/**
 * Diameter of a Binary Tree
 *
 * Given the root of a binary tree, return the length of the diameter of the tree.
 *
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges between them.
 *
 * Example 1:
 *
 * Input: root = [1,2,3,4,5]
 * Output: 3
 * Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
 *
 * Example 2:
 *
 * Input: root = [1,2]
 * Output: 1
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * 0 <= Node.val <= 100
 */

// Approach 1: Recursive with Global Variable
// Time Complexity: O(N), Space Complexity: O(H) where H is the height of the tree.
var diameterOfBinaryTree1 = function(root) {
    let diameter = 0;

    function dfs(node) {
        if (!node) {
            return 0;
        }

        let leftHeight = dfs(node.left);
        let rightHeight = dfs(node.right);

        diameter = Math.max(diameter, leftHeight + rightHeight);
        return Math.max(leftHeight, rightHeight) + 1;
    }

    dfs(root);
    return diameter;
};

// Approach 2: Recursive with Returning an Array
// Time Complexity: O(N), Space Complexity: O(H)
var diameterOfBinaryTree2 = function(root) {
    function dfs(node) {
        if (!node) {
            return [0, 0]; // [height, diameter]
        }

        let [leftHeight, leftDiameter] = dfs(node.left);
        let [rightHeight, rightDiameter] = dfs(node.right);

        let height = Math.max(leftHeight, rightHeight) + 1;
        let diameter = Math.max(leftDiameter, rightDiameter, leftHeight + rightHeight);
        return [height, diameter];
    }

    const result = dfs(root);
    return result[1];
};

// Approach 3: Iterative using Stack (Post-order Traversal)
// Time Complexity: O(N), Space Complexity: O(H)
var diameterOfBinaryTree3 = function(root) {
    if (!root) return 0;

    let stack = [];
    let diameter = 0;
    let nodeHeights = new Map();

    stack.push(root);
    let prev = null;

    while (stack.length > 0) {
        let curr = stack[stack.length - 1];

        if (!curr.left && !curr.right || prev && (prev === curr.left || prev === curr.right)) {
            stack.pop();

            let leftHeight = nodeHeights.get(curr.left) || 0;
            let rightHeight = nodeHeights.get(curr.right) || 0;

            diameter = Math.max(diameter, leftHeight + rightHeight);
            nodeHeights.set(curr, Math.max(leftHeight, rightHeight) + 1);
            prev = curr;
        } else {
            if (curr.right) stack.push(curr.right);
            if (curr.left) stack.push(curr.left);
        }
    }
    return diameter;
};

// Approach 4: Using a Class to store the diameter
class TreeInfo {
  constructor() {
    this.diameter = 0;
  }
}

var diameterOfBinaryTree4 = function(root) {
    const treeInfo = new TreeInfo();

    function dfs(node, treeInfo) {
        if (!node) {
            return 0;
        }

        let leftHeight = dfs(node.left, treeInfo);
        let rightHeight = dfs(node.right, treeInfo);

        treeInfo.diameter = Math.max(treeInfo.diameter, leftHeight + rightHeight);
        return Math.max(leftHeight, rightHeight) + 1;
    }

    dfs(root, treeInfo);
    return treeInfo.diameter;
};

// Approach 5:  Similar to approach 1, but with slight optimization in variable naming
var diameterOfBinaryTree5 = function(root) {
    let maxDiameter = 0;

    function calculateHeight(node) {
        if (!node) return 0;

        const leftHeight = calculateHeight(node.left);
        const rightHeight = calculateHeight(node.right);

        maxDiameter = Math.max(maxDiameter, leftHeight + rightHeight);
        return Math.max(leftHeight, rightHeight) + 1;
    }

    calculateHeight(root);
    return maxDiameter;
};

// Test Cases
const root1 = new TreeNode(1,
    new TreeNode(2,
        new TreeNode(4),
        new TreeNode(5)),
    new TreeNode(3));

const root2 = new TreeNode(1, new TreeNode(2));

const root3 = new TreeNode(1,
    new TreeNode(2,
        new TreeNode(4, new TreeNode(6), new TreeNode(7)),
        new TreeNode(5)),
    new TreeNode(3,
        new TreeNode(8),
        new TreeNode(9)));

console.log("Test Case 1:");
console.log("Approach 1:", diameterOfBinaryTree1(root1)); // Output: 3
console.log("Approach 2:", diameterOfBinaryTree2(root1)); // Output: 3
console.log("Approach 3:", diameterOfBinaryTree3(root1)); // Output: 3
console.log("Approach 4:", diameterOfBinaryTree4(root1)); // Output: 3
console.log("Approach 5:", diameterOfBinaryTree5(root1)); // Output: 3

console.log("\nTest Case 2:");
console.log("Approach 1:", diameterOfBinaryTree1(root2)); // Output: 1
console.log("Approach 2:", diameterOfBinaryTree2(root2)); // Output: 1
console.log("Approach 3:", diameterOfBinaryTree3(root2)); // Output: 1
console.log("Approach 4:", diameterOfBinaryTree4(root2)); // Output: 1
console.log("Approach 5:", diameterOfBinaryTree5(root2)); // Output: 1

console.log("\nTest Case 3:");
console.log("Approach 1:", diameterOfBinaryTree1(root3)); // Output: 4
console.log("Approach 2:", diameterOfBinaryTree2(root3)); // Output: 4
console.log("Approach 3:", diameterOfBinaryTree3(root3)); // Output: 4
console.log("Approach 4:", diameterOfBinaryTree4(root3)); // Output: 4
console.log("Approach 5:", diameterOfBinaryTree5(root3)); // Output: 4

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 * this.val = (val===undefined ? 0 : val)
 * this.left = (left===undefined ? null : left)
 * this.right = (right===undefined ? null : right)
 * }
 */

/**
 * Diameter of Binary Tree
 *
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges between them.
 *
 * Example 1:
 * Input: root = [1,2,3,4,5]
 * Output: 3
 * Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
 *
 * Example 2:
 * Input: root = [1,2]
 * Output: 1
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 10^4].
 * -100 <= Node.val <= 100
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

// Approach 2: Recursive with Object
// Time Complexity: O(N), Space Complexity: O(H)
var diameterOfBinaryTree2 = function(root) {
    function dfs(node, diameterObj) { // Pass an object
        if (!node) {
            return 0;
        }

        let leftHeight = dfs(node.left, diameterObj);
        let rightHeight = dfs(node.right, diameterObj);

        diameterObj.diameter = Math.max(diameterObj.diameter, leftHeight + rightHeight);

        return Math.max(leftHeight, rightHeight) + 1;
    }

    let diameterObj = { diameter: 0 }; // Use an object to store diameter
    dfs(root, diameterObj);
    return diameterObj.diameter;
};

// Approach 3: Iterative using Stack (Post-order Traversal)
// Time Complexity: O(N), Space Complexity: O(H) in worst case, where H is the height of the tree
var diameterOfBinaryTree3 = function(root) {
    if (!root) return 0;

    let stack = [];
    let diameter = 0;
    let nodeHeights = new Map(); // Store node heights

    stack.push(root);

    while (stack.length > 0) {
        let node = stack[stack.length - 1]; // Peek

        if (node.left && !nodeHeights.has(node.left)) {
            stack.push(node.left);
        } else if (node.right && !nodeHeights.has(node.right)) {
            stack.push(node.right);
        } else {
            stack.pop(); // Process the node
            let leftHeight = nodeHeights.get(node.left) || 0;
            let rightHeight = nodeHeights.get(node.right) || 0;

            diameter = Math.max(diameter, leftHeight + rightHeight);
            nodeHeights.set(node, Math.max(leftHeight, rightHeight) + 1);
        }
    }
    return diameter;
};

// Approach 4: Using a Class to store diameter
// Time Complexity: O(N), Space Complexity: O(H)
class DiameterResult {
    constructor() {
        this.diameter = 0;
    }
}

var diameterOfBinaryTree4 = function(root) {
    const result = new DiameterResult();

    function dfs(node, result) {
        if (!node) {
            return 0;
        }

        let leftHeight = dfs(node.left, result);
        let rightHeight = dfs(node.right, result);

        result.diameter = Math.max(result.diameter, leftHeight + rightHeight);

        return Math.max(leftHeight, rightHeight) + 1;
    }

    dfs(root, result);
    return result.diameter;
};

// Approach 5:  Most Concise Recursive Solution
var diameterOfBinaryTree5 = function(root) {
    let diameter = 0;
    function maxDepth(node) {
        if (!node) return 0;
        let left = maxDepth(node.left);
        let right = maxDepth(node.right);
        diameter = Math.max(diameter, left + right);
        return 1 + Math.max(left, right);
    }
    maxDepth(root);
    return diameter;
};

// Helper function to create a binary tree for testing
function createBinaryTree(arr) {
    if (!arr || arr.length === 0) return null;

    function TreeNode(val, left, right) {
        this.val = (val===undefined ? 0 : val)
        this.left = (left===undefined ? null : left)
        this.right = (right===undefined ? null : right)
    }

    const nodes = arr.map(val => val !== null ? new TreeNode(val) : null);
    const n = nodes.length;
    for (let i = 0; i < n; i++) {
        if (nodes[i]) {
            const leftIndex = 2 * i + 1;
            const rightIndex = 2 * i + 2;
            nodes[i].left = leftIndex < n ? nodes[leftIndex] : null;
            nodes[i].right = rightIndex < n ? nodes[rightIndex] : null;
        }
    }
    return nodes[0];
}

// Test Cases
const testCases = [
    { input: [1,2,3,4,5], expected: 3 },
    { input: [1,2], expected: 1 },
    { input: [1,2,null,4,5], expected: 3 },
    { input: [1], expected: 0 },
    { input: [], expected: 0 },
    { input: [4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2], expected: 8}
];

// Function to run tests and print results
function runTests() {
    testCases.forEach((test, index) => {
        const root = createBinaryTree(test.input);

        console.log(`\nTest Case ${index + 1}:`);
        console.log(`Input: ${JSON.stringify(test.input)}`);

        // Approach 1
        const result1 = diameterOfBinaryTree1(root);
        console.log(`Approach 1: Recursive with Global Variable - Diameter: ${result1}, Expected: ${test.expected}, Result: ${result1 === test.expected ? 'PASS' : 'FAIL'}`);

        // Approach 2
        const result2 = diameterOfBinaryTree2(root);
        console.log(`Approach 2: Recursive with Object - Diameter: ${result2}, Expected: ${test.expected}, Result: ${result2 === test.expected ? 'PASS' : 'FAIL'}`);

        // Approach 3
        const result3 = diameterOfBinaryTree3(root);
        console.log(`Approach 3: Iterative using Stack - Diameter: ${result3}, Expected: ${test.expected}, Result: ${result3 === test.expected ? 'PASS' : 'FAIL'}`);

        // Approach 4
        const result4 = diameterOfBinaryTree4(root);
        console.log(`Approach 4: Using a Class - Diameter: ${result4}, Expected: ${test.expected}, Result: ${result4 === test.expected ? 'PASS' : 'FAIL'}`);

        // Approach 5
        const result5 = diameterOfBinaryTree5(root);
        console.log(`Approach 5: Concise Recursive - Diameter: ${result5}, Expected: ${test.expected}, Result: ${result5 === test.expected ? 'PASS' : 'FAIL'}`);
    });
}

runTests();

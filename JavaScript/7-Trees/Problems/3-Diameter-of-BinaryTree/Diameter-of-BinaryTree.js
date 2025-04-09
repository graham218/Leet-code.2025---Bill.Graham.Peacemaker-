/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 * this.val = (val===undefined ? 0 : val)
 * this.left = (left===undefined ? null : left)
 * this.right = (right===undefined ? null : right)
 * }
 */

// Helper function to create a TreeNode
function TreeNode(val, left, right) {
    this.val = (val === undefined ? 0 : val);
    this.left = (left === undefined ? null : left);
    this.right = (right === undefined ? null : right);
}

// Helper function to build a tree from an array (for testing)
function buildTreeFromArray(arr) {
    if (!arr || arr.length === 0) {
        return null;
    }

    const nodes = arr.map(val => val === null ? null : new TreeNode(val));
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

/*
 * Approach 1: Recursive with Global Variable
 * - Calculate the height of the left and right subtrees recursively.
 * - The diameter at each node is the sum of the heights of its left and right subtrees.
 * - Use a global variable to keep track of the maximum diameter found so far.
 */
function diameterOfBinaryTree1(root) {
    let maxDiameter = 0;

    function getHeight(node) {
        if (!node) {
            return 0;
        }

        const leftHeight = getHeight(node.left);
        const rightHeight = getHeight(node.right);
        maxDiameter = Math.max(maxDiameter, leftHeight + rightHeight);
        return Math.max(leftHeight, rightHeight) + 1;
    }

    getHeight(root);
    return maxDiameter;
}

/*
 * Approach 2: Recursive with Return Value
 * - Similar to approach 1, but instead of using a global variable,
 * return the diameter along with the height from the recursive function.
 * - This approach is cleaner as it avoids modifying external state.
 */
function diameterOfBinaryTree2(root) {
    function getHeightAndDiameter(node) {
        if (!node) {
            return { height: 0, diameter: 0 };
        }

        const leftResult = getHeightAndDiameter(node.left);
        const rightResult = getHeightAndDiameter(node.right);
        const height = Math.max(leftResult.height, rightResult.height) + 1;
        const diameter = Math.max(
            leftResult.diameter,
            rightResult.diameter,
            leftResult.height + rightResult.height
        );
        return { height, diameter };
    }

    const result = getHeightAndDiameter(root);
    return result.diameter;
}

/*
 * Approach 3: Iterative using Stack (Post-order Traversal)
 * - Use a stack to perform a post-order traversal of the tree.
 * - Store the height of each node in a map.
 * - Calculate the diameter at each node while popping it from the stack.
 */
function diameterOfBinaryTree3(root) {
    if (!root) return 0;

    const stack = [];
    const nodeHeights = new Map();
    let maxDiameter = 0;
    let curr = root;

    while (curr || stack.length > 0) {
        if (curr) {
            stack.push(curr);
            curr = curr.left;
        } else {
            const node = stack[stack.length - 1];
            if (node.right && node.right !== curr) {
                curr = node.right;
            } else {
                stack.pop();
                const leftHeight = nodeHeights.get(node.left) || 0;
                const rightHeight = nodeHeights.get(node.right) || 0;
                maxDiameter = Math.max(maxDiameter, leftHeight + rightHeight);
                nodeHeights.set(node, Math.max(leftHeight, rightHeight) + 1);
                curr = null; // Corrected: Avoid infinite loop.
            }
        }
    }
    return maxDiameter;
}

/*
 * Approach 4: Iterative using Morris Traversal (No Stack, No Map)
 * - Morris traversal is a way to traverse a tree without using a stack or recursion.
 * - It works by modifying the tree structure temporarily.
 * - This approach is more space-efficient than the stack-based approach.
 */
function diameterOfBinaryTree4(root) {
    let maxDiameter = 0;
    let curr = root;

    while (curr) {
        if (!curr.left) {
            curr = curr.right;
        } else {
            let predecessor = curr.left;
            while (predecessor.right && predecessor.right !== curr) {
                predecessor = predecessor.right;
            }

            if (!predecessor.right) {
                predecessor.right = curr;
                curr = curr.left;
            } else {
                predecessor.right = null; // Restore the tree structure
                const leftHeight = getHeight(curr.left); // Corrected: use helper
                const rightHeight = getHeight(curr.right); // Corrected: use helper.
                maxDiameter = Math.max(maxDiameter, leftHeight + rightHeight);
                curr = curr.right;
            }
        }
    }

    function getHeight(node) { // Corrected: added helper function
        if (!node) return 0;
        return Math.max(getHeight(node.left), getHeight(node.right)) + 1;
    }

    return maxDiameter;
}

/*
 * Approach 5: Optimized Recursive (Slightly more efficient)
 * - Combines the efficiency of calculating height and diameter in one pass,
 * - Uses a single recursive function, similar to Approach 2, but potentially
 * with slightly improved performance due to reduced function call overhead
 */

function diameterOfBinaryTree5(root) {
    let diameter = 0;

    function calculateHeight(node) {
        if (!node) {
            return 0;
        }

        const leftHeight = calculateHeight(node.left);
        const rightHeight = calculateHeight(node.right);

        diameter = Math.max(diameter, leftHeight + rightHeight);

        return Math.max(leftHeight, rightHeight) + 1;
    }

    calculateHeight(root);
    return diameter;
}

// Example Usage and Testing
const testCases = [
    [1, 2, 3, 4, 5],
    [1, 2, 3, null, null, 4, 5],
    [1],
    [],
    [1, 2],
    [1, null, 2, 3, 4, null, null, 5, 6], // More complex case
    [4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2], //From LeetCode
    [2,null,3,null,4,null,5,null,6] // another test
];

testCases.forEach((arr, index) => {
    const root = buildTreeFromArray(arr);
    console.log(`\nTest Case ${index + 1}: Input Array = ${JSON.stringify(arr)}`);

    // Approach 1
    console.log(`Approach 1: Recursive with Global Variable - Diameter: ${diameterOfBinaryTree1(root)}`);

    // Approach 2
    console.log(`Approach 2: Recursive with Return Value - Diameter: ${diameterOfBinaryTree2(root)}`);

    // Approach 3
    console.log(`Approach 3: Iterative using Stack - Diameter: ${diameterOfBinaryTree3(root)}`);

    // Approach 4
    console.log(`Approach 4: Iterative using Morris Traversal - Diameter: ${diameterOfBinaryTree4(root)}`);

     // Approach 5
    console.log(`Approach 5: Optimized Recursive - Diameter: ${diameterOfBinaryTree5(root)}`);
});

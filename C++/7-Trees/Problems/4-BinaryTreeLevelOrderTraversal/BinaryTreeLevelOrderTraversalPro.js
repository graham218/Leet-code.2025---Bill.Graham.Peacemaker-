// Definition for a binary tree node.
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

// Helper function to create a sample binary tree for testing
function createSampleTree() {
    const root = new TreeNode(3);
    root.left = new TreeNode(9);
    root.right = new TreeNode(20);
    root.right.left = new TreeNode(15);
    root.right.right = new TreeNode(7);
    return root;
}

/**
 * Approach 1: Iterative using Queue (Most Common)
 * - Uses a queue to process nodes level by level.
 * - This is the standard, efficient approach for level order traversal.
 * - Time Complexity: O(N), Space Complexity: O(W) (where W is the maximum width of the tree)
 */
function levelOrderIterative(root) {
    if (!root) return [];
    const queue = [root];
    const result = [];

    while (queue.length > 0) {
        const levelSize = queue.length;
        const currentLevel = [];
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            currentLevel.push(node.val);
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        result.push(currentLevel);
    }
    return result;
}

/**
 * Approach 2: Recursive
 * - Uses recursion to traverse the tree level by level.
 * - Helper function `helper` is used to process each level.
 * - Time Complexity: O(N), Space Complexity: O(H) (where H is the height of the tree)
 */
function levelOrderRecursive(root) {
    if (!root) return [];
    const result = [];

    function helper(node, level) {
        if (!node) return;
        if (result.length <= level) {
            result.push([]);
        }
        result[level].push(node.val);
        helper(node.left, level + 1);
        helper(node.right, level + 1);
    }

    helper(root, 0);
    return result;
}

/**
 * Approach 3: Iterative with Level Tracking in Queue
 * - Similar to the iterative approach, but stores node and level in the queue.
 * - Avoids the extra loop to determine level size.
 * - Time Complexity: O(N), Space Complexity: O(W)
 */
function levelOrderIterativeWithLevel(root) {
    if (!root) return [];
    const queue = [{ node: root, level: 0 }];
    const result = [];

    while (queue.length > 0) {
        const { node, level } = queue.shift();
        if (result.length <= level) {
            result.push([]);
        }
        result[level].push(node.val);
        if (node.left) queue.push({ node: node.left, level: level + 1 });
        if (node.right) queue.push({ node: node.right, level: level + 1 });
    }
    return result;
}

/**
 * Approach 4: Using a Pre-Order Traversal and Level Map
 * - Performs a pre-order traversal of the tree.
 * - Uses a map to store nodes at each level.
 * - Time Complexity: O(N), Space Complexity: O(N)
 */
function levelOrderPreorderWithMap(root) {
    if (!root) return [];
    const levelMap = new Map();

    function preOrder(node, level) {
        if (!node) return;
        if (!levelMap.has(level)) {
            levelMap.set(level, []);
        }
        levelMap.get(level).push(node.val);
        preOrder(node.left, level + 1);
        preOrder(node.right, level + 1);
    }

    preOrder(root, 0);
    const result = [];
    for (let level = 0; levelMap.has(level); level++) {
        result.push(levelMap.get(level));
    }
    return result;
}


/**
 * Approach 5: Morris Traversal (Without Extra Space) - Tricky and not always practical
 * -  A tree traversal algorithm that does not use recursion or a queue.
 * -  It modifies the tree structure temporarily (and restores it).
 * -  Not commonly used in practical level order traversal, more for inorder.
 * -  **Does NOT produce correct level order, but shows the Morris Traversal Concept.  Correct Level order with Morris is very complex.**
 * -  Time Complexity: O(N), Space Complexity: O(1)
 */
function levelOrderMorris(root) {
    const result = [];
    let current = root;

    while (current) {
        if (!current.left) {
            result.push([current.val]); // Simplified: pushes each node in its own level array.  NOT correct level order.
            current = current.right;
        } else {
            let predecessor = current.left;
            while (predecessor.right && predecessor.right !== current) {
                predecessor = predecessor.right;
            }
            if (!predecessor.right) {
                predecessor.right = current;
                result.push([current.val]); // Simplified: pushes each node in its own level array.  NOT correct level order.
                current = current.left;
            } else {
                predecessor.right = null;
                current = current.right;
            }
        }
    }
    return result; //  This will NOT be correct level order.
}



// Example usage:
const tree = createSampleTree();

console.log("Binary Tree Level Order Traversal - Iterative (Queue):", levelOrderIterative(tree));
console.log("Binary Tree Level Order Traversal - Recursive:", levelOrderRecursive(tree));
console.log("Binary Tree Level Order Traversal - Iterative with Level:", levelOrderIterativeWithLevel(tree));
console.log("Binary Tree Level Order Traversal - Preorder with Map:", levelOrderPreorderWithMap(tree));
console.log("Binary Tree Level Order Traversal - Morris Traversal (Incorrect Level Order):", levelOrderMorris(tree)); // Note: Incorrect level order
/*
Expected output for the first 4 approaches:
[
  [ 3 ],
  [ 9, 20 ],
  [ 15, 7 ]
]
*/

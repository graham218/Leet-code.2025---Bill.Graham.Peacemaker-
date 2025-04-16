// Definition for a binary tree node.
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

/**
 * Iterative Approach using Queue
 * Time Complexity: O(N), Space Complexity: O(W) where W is the maximum width of the tree
 */
function levelOrderIterative(root) {
    if (!root) {
        return [];
    }

    const queue = [root];
    const result = [];

    while (queue.length > 0) {
        const levelSize = queue.length;
        const currentLevel = [];

        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            currentLevel.push(node.val);

            if (node.left) {
                queue.push(node.left);
            }
            if (node.right) {
                queue.push(node.right);
            }
        }
        result.push(currentLevel);
    }
    return result;
}

/**
 * Recursive Approach 1:  Helper function to traverse and store by level
 * Time Complexity: O(N), Space Complexity: O(H) where H is the height of the tree
 */
function levelOrderRecursive1(root) {
    const result = [];
    function traverse(node, level) {
        if (!node) return;
        if (!result[level]) result[level] = [];
        result[level].push(node.val);
        traverse(node.left, level + 1);
        traverse(node.right, level + 1);
    }
    traverse(root, 0);
    return result;
}

/**
 * Recursive Approach 2: Similar to Recursive 1, but slightly different structure
 * Time Complexity: O(N), Space Complexity: O(H)
 */
function levelOrderRecursive2(root) {
    const result = [];

    function traverse(node, level) {
        if (!node) {
            return;
        }

        if (result.length <= level) {
            result.push([]);
        }

        result[level].push(node.val);
        traverse(node.left, level + 1);
        traverse(node.right, level + 1);
    }

    traverse(root, 0);
    return result;
}


/**
 * Iterative Approach using Queue and Level Tracking
 * Time Complexity: O(N), Space Complexity: O(W)
 */
function levelOrderIterativeWithLevel(root) {
    if (!root) {
        return [];
    }

    const queue = [{ node: root, level: 0 }];
    const result = [];

    while (queue.length > 0) {
        const { node, level } = queue.shift();

        if (!result[level]) {
            result[level] = [];
        }
        result[level].push(node.val);

        if (node.left) {
            queue.push({ node: node.left, level: level + 1 });
        }
        if (node.right) {
            queue.push({ node: node.right, level: level + 1 });
        }
    }
    return result;
}

/**
 * Morris Traversal Approach (Without using extra space)
 * Time Complexity: O(N), Space Complexity: O(1)
 */
function levelOrderMorris(root) {
    const result = [];
    let level = 0;
    let currentLevel = [];
    let current = root;
    let prev = null;

    while (current) {
        if (!current.left) {
            currentLevel.push(current.val);
            current = current.right;
        } else {
            prev = current.left;
            while (prev.right && prev.right !== current) {
                prev = prev.right;
            }

            if (!prev.right) {
                prev.right = current;
                currentLevel.push(current.val);
                current = current.left;
            } else {
                prev.right = null;
                current = current.right;
            }
        }
        // Check for end of level, using rightmost node of the level
        if (!current || (current && !current.left && !current.right && prev === current.parent))
        {
          result.push(currentLevel);
          currentLevel = [];
          level++;
        }
    }
    if (currentLevel.length > 0)
    {
        result.push(currentLevel);
    }
    return result;
}



// Example Usage:
// Create a sample binary tree
const root = new TreeNode(3);
root.left = new TreeNode(9);
root.right = new TreeNode(20);
root.right.left = new TreeNode(15);
root.right.right = new TreeNode(7);
root.left.left = new TreeNode(8);
root.left.right = new TreeNode(10);


console.log("Input Tree:");
console.dir(root);

console.log("\nLevel Order Traversal - Iterative:");
console.log(levelOrderIterative(root));

console.log("\nLevel Order Traversal - Recursive 1:");
console.log(levelOrderRecursive1(root));

console.log("\nLevel Order Traversal - Recursive 2:");
console.log(levelOrderRecursive2(root));

console.log("\nLevel Order Traversal - Iterative with Level:");
console.log(levelOrderIterativeWithLevel(root));

console.log("\nLevel Order Traversal - Morris Traversal:");
console.log(levelOrderMorris(root));

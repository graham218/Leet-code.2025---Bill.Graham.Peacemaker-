/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 * this.val = (val===undefined ? 0 : val)
 * this.left = (left===undefined ? null : left)
 * this.right = (right===undefined ? null : right)
 * }
 */

// Helper function to create a TreeNode (useful for testing)
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val)
    this.left = (left===undefined ? null : left)
    this.right = (right===undefined ? null : right)
}

/**
 * Given the root of a binary tree, find its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 *
 *
 * Example 1:
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

/**
 * Approach 1: Recursive Depth First Search (DFS)
 *
 * Time Complexity: O(N), where N is the number of nodes in the tree.
 * Space Complexity: O(H), where H is the height of the tree.  In the worst case (skewed tree), H can be N, so O(N).  In the best case (balanced tree), H is logN, so O(logN).
 *
 * This is the most common and straightforward approach.  It recursively explores the left and right subtrees
 * and returns the maximum depth.  This is similar to how you might traverse a file system directory structure.
 */
const maxDepth_RecursiveDFS = function(root) {
    if (!root) {
        return 0;
    }
    const leftDepth = maxDepth_RecursiveDFS(root.left);
    const rightDepth = maxDepth_RecursiveDFS(root.right);
    return Math.max(leftDepth, rightDepth) + 1;
};



/**
 * Approach 2: Iterative Depth First Search (DFS) using a Stack
 *
 * Time Complexity: O(N), where N is the number of nodes in the tree.
 * Space Complexity: O(H), where H is the height of the tree.  In the worst case, O(N). In the best case, O(logN).
 *
 * This approach uses a stack to simulate the recursive calls of the DFS approach.  It's useful when you want to
 * avoid recursion, which can sometimes lead to stack overflow errors in very deep trees.  This is similar to how
 * an iterative file system crawler might use a stack to keep track of directories to visit.
 */
const maxDepth_IterativeDFS = function(root) {
    if (!root) {
        return 0;
    }
    const stack = [[root, 1]]; // Stack stores [node, depth] pairs
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



/**
 * Approach 3: Breadth First Search (BFS) using a Queue
 *
 * Time Complexity: O(N), where N is the number of nodes in the tree.
 * Space Complexity: O(W), where W is the maximum width of the tree. In the worst case (a full binary tree), W is approximately N/2, so O(N).  In the best case (a skewed tree), W is 1, so O(1).
 *
 * This approach uses a queue to traverse the tree level by level.  It's useful when you need to process nodes
 * in a breadth-first order.  This is similar to how a web crawler might explore links level by level.
 */
const maxDepth_BFS = function(root) {
    if (!root) {
        return 0;
    }
    const queue = [root]; // Queue stores nodes to visit
    let depth = 0;

    while (queue.length > 0) {
        depth++;
        const levelSize = queue.length; // Number of nodes at the current level

        // Process all nodes at the current level before moving to the next level
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

/**
 * Approach 4:  Morris Traversal (Iterative, In-place) -  Non-standard for depth, but showing tree traversal
 *
 * Time Complexity: O(N), where N is the number of nodes in the tree.
 * Space Complexity: O(1).  This is the key advantage of Morris traversal. It's done in-place.
 *
 * Morris traversal is a way to traverse a binary tree without using recursion or a stack.  It modifies the tree
 * temporarily to keep track of the traversal.  While it's not typically used to find the maximum depth
 * directly, it's an important technique for in-place tree traversal.  We adapt it here to calculate depth,
 * although it's not the most efficient way to do so.
 *
 * Key Idea:  For each node, find its inorder predecessor.  If the predecessor's right child is null,
 * make the predecessor's right child point to the current node (to create a temporary link).
 * If the predecessor's right child is the current node, remove the link and process the current node.
 *
 */
const maxDepth_Morris = function(root) {
    let depth = 0;
    let current = root;
    let levelStart = root; // Keep track of the start of each level
    let levelNodes = 0;

    while (current) {
        if (!current.left) {
            levelNodes++;
            current = current.right;
        } else {
            let predecessor = current.left;
            while (predecessor.right && predecessor.right !== current) {
                predecessor = predecessor.right;
            }

            if (!predecessor.right) {
                // Create the temporary link
                predecessor.right = current;
                levelNodes++;
                current = current.left;
            } else {
                // Remove the link and process the current node
                predecessor.right = null;
                current = current.right;
            }
        }
        if (!current) { // end of level
            depth++;
            levelNodes = 0;
            if (levelStart) {
                let nextLevelStart = null;
                const queue = [levelStart];
                while(queue.length > 0){
                    const node = queue.shift();
                    if(node.left){
                        nextLevelStart = nextLevelStart || node.left;
                        queue.push(node.left);
                    }
                    if(node.right){
                        nextLevelStart = nextLevelStart || node.right;
                        queue.push(node.right)
                    }
                }
                levelStart = nextLevelStart;
                current = levelStart;
            }
        }
    }
    return depth;
};


/**
 * Approach 5: Recursive DFS with Memoization
 *
 * Time Complexity: O(N), where N is the number of nodes.  Each node is visited only once.
 * Space Complexity: O(N + H), where N is the space used for the memoization map, and H is the recursion depth.
 *
 * This approach is similar to the basic recursive DFS, but it uses a map (memo) to store the depth of each node
 * as it's calculated.  This prevents redundant calculations for nodes that are visited multiple times
 * in the recursion.  While it doesn't change the overall time complexity, it can improve performance in
 * practice, especially for trees with overlapping subproblems.  This is a classic dynamic programming
 * technique.
 */
const maxDepth_MemoizationDFS = function(root) {
    const memo = new Map(); // Map to store node depths

    const calculateDepth = (node) => {
        if (!node) {
            return 0;
        }
        if (memo.has(node)) {
            return memo.get(node);
        }

        const leftDepth = calculateDepth(node.left);
        const rightDepth = calculateDepth(node.right);
        const depth = Math.max(leftDepth, rightDepth) + 1;
        memo.set(node, depth);
        return depth;
    };

    return calculateDepth(root);
};



// Example Usage (for testing)
const tree1 = new TreeNode(3,
    new TreeNode(9),
    new TreeNode(20,
        new TreeNode(15),
        new TreeNode(7)
    )
);
const tree2 = new TreeNode(1, null, new TreeNode(2));
const tree3 = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3, null, new TreeNode(6)));
const tree4 = null; // Empty tree
const tree5 = new TreeNode(1, new TreeNode(2, new TreeNode(4, new TreeNode(8), null), new TreeNode(5)), new TreeNode(3, new TreeNode(6), new TreeNode(7, null, new TreeNode(9))));


console.log("Example Trees:");
console.log("Tree 1:", tree1);
console.log("Tree 2:", tree2);
console.log("Tree 3:", tree3);
console.log("Tree 4:", tree4);
console.log("Tree 5:", tree5);


console.log("\nMaximum Depth of Binary Tree:");
console.log("--------------------------");

console.log("Tree 1 - Recursive DFS:", maxDepth_RecursiveDFS(tree1)); // Output: 3
console.log("Tree 2 - Recursive DFS:", maxDepth_RecursiveDFS(tree2)); // Output: 2
console.log("Tree 3 - Recursive DFS:", maxDepth_RecursiveDFS(tree3)); // Output: 3
console.log("Tree 4 - Recursive DFS:", maxDepth_RecursiveDFS(tree4)); // Output: 0
console.log("Tree 5 - Recursive DFS:", maxDepth_RecursiveDFS(tree5)); // Output: 4


console.log("\nTree 1 - Iterative DFS:", maxDepth_IterativeDFS(tree1)); // Output: 3
console.log("Tree 2 - Iterative DFS:", maxDepth_IterativeDFS(tree2)); // Output: 2
console.log("Tree 3 - Iterative DFS:", maxDepth_IterativeDFS(tree3)); // Output: 3
console.log("Tree 4 - Iterative DFS:", maxDepth_IterativeDFS(tree4)); // Output: 0
console.log("Tree 5 - Iterative DFS:", maxDepth_IterativeDFS(tree5)); // Output: 4

console.log("\nTree 1 - BFS:", maxDepth_BFS(tree1)); // Output: 3
console.log("Tree 2 - BFS:", maxDepth_BFS(tree2)); // Output: 2
console.log("Tree 3 - BFS:", maxDepth_BFS(tree3)); // Output: 3
console.log("Tree 4 - BFS:", maxDepth_BFS(tree4)); // Output: 0
console.log("Tree 5 - BFS:", maxDepth_BFS(tree5)); // Output: 4

console.log("\nTree 1 - Morris Traversal:", maxDepth_Morris(tree1)); // Output: 3
console.log("Tree 2 - Morris Traversal:", maxDepth_Morris(tree2)); // Output: 2
console.log("Tree 3 - Morris Traversal:", maxDepth_Morris(tree3)); // Output: 3
console.log("Tree 4 - Morris Traversal:", maxDepth_Morris(tree4)); // Output: 0
console.log("Tree 5 - Morris Traversal:", maxDepth_Morris(tree5)); // Output: 4

console.log("\nTree 1 - Memoization DFS:", maxDepth_MemoizationDFS(tree1)); // Output: 3
console.log("Tree 2 - Memoization DFS:", maxDepth_MemoizationDFS(tree2)); // Output: 2
console.log("Tree 3 - Memoization DFS:", maxDepth_MemoizationDFS(tree3)); // Output: 3
console.log("Tree 4 - Memoization DFS:", maxDepth_MemoizationDFS(tree4)); // Output: 0
console.log("Tree 5 - Memoization DFS:", maxDepth_MemoizationDFS(tree5)); // Output: 4

// Definition of a TreeNode (assuming a simple binary tree structure)
class TreeNode {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

// 1. Iterative BFS using a Queue (Most Common)
function bfsIterative(root) {
    if (!root) {
        return [];
    }

    const queue = [root];
    const result = [];

    while (queue.length > 0) {
        const levelSize = queue.length; // Important for level-by-level traversal
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
        result.push(currentLevel); // Store each level's values
    }
    return result;
}

// 2. Iterative BFS with Separator (for level indication)
function bfsWithSeparator(root) {
    if (!root) return [];

    const queue = [root, null]; // Use null as a level separator
    const result = [];
    let currentLevel = [];

    while (queue.length > 0) {
        const node = queue.shift();

        if (node === null) {
            result.push(currentLevel);
            currentLevel = [];
            if (queue.length > 0) { // Add separator for the next level
                queue.push(null);
            }
        } else {
            currentLevel.push(node.val);
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
    }
    return result;
}

// 3. Recursive BFS using Level by Level Traversal
function bfsRecursive(root) {
  if (!root) {
    return [];
  }

  const result = [];
  let level = 0;

  function traverseLevel(node, currentLevel) {
    if (!node) return;

    if (!result[currentLevel]) {
      result[currentLevel] = [];
    }
    result[currentLevel].push(node.val);

    traverseLevel(node.left, currentLevel + 1);
    traverseLevel(node.right, currentLevel + 1);
  }

  traverseLevel(root, level);
  return result;
}

// 4.  BFS using a Map to store nodes at each level
function bfsUsingMap(root) {
    if (!root) {
        return [];
    }

    const nodeMap = new Map();
    const queue = [{ node: root, level: 0 }];

    while (queue.length > 0) {
        const { node, level } = queue.shift();

        if (!nodeMap.has(level)) {
            nodeMap.set(level, []);
        }
        nodeMap.get(level).push(node.val);

        if (node.left) {
            queue.push({ node: node.left, level: level + 1 });
        }
        if (node.right) {
            queue.push({ node: node.right, level: level + 1 });
        }
    }

    // Convert the map to the expected array format
    const result = [];
    for (const [level, nodes] of nodeMap.entries()) {
        result.push(nodes);
    }
    return result;
}

// 5. BFS using a Queue and Level Count
function bfsWithLevelCount(root) {
    if (!root) return [];

    const queue = [root];
    const result = [];
    let nodesInCurrentLevel = 1;
    let nodesInNextLevel = 0;
    let currentLevel = [];

    while (queue.length > 0) {
        const node = queue.shift();
        nodesInCurrentLevel--;
        currentLevel.push(node.val);

        if (node.left) {
            queue.push(node.left);
            nodesInNextLevel++;
        }
        if (node.right) {
            queue.push(node.right);
            nodesInNextLevel++;
        }

        if (nodesInCurrentLevel === 0) {
            result.push(currentLevel);
            currentLevel = [];
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
    return result;
}



// Create a sample binary tree for testing
const root = new TreeNode(1);
root.left = new TreeNode(2);
root.right = new TreeNode(3);
root.left.left = new TreeNode(4);
root.left.right = new TreeNode(5);
root.right.left = new TreeNode(6);
root.right.right = new TreeNode(7);
root.left.left.left = new TreeNode(8);
root.left.left.right = new TreeNode(9);

// Test and display the results from each BFS implementation
console.log("BFS Iterative (Most Common):", bfsIterative(root));
console.log("BFS with Separator:", bfsWithSeparator(root));
console.log("BFS Recursive:", bfsRecursive(root));
console.log("BFS using Map:", bfsUsingMap(root));
console.log("BFS with Level Count:", bfsWithLevelCount(root));

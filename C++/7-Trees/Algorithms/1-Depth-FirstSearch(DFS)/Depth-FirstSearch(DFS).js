// Definition of a TreeNode (assuming a basic binary tree structure)
class TreeNode {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

// Create a sample binary tree for testing
const createSampleTree = () => {
    const root = new TreeNode(1);
    root.left = new TreeNode(2);
    root.right = new TreeNode(3);
    root.left.left = new TreeNode(4);
    root.left.right = new TreeNode(5);
    root.right.left = new TreeNode(6);
    root.right.right = new TreeNode(7);
    return root;
};

const treeRoot = createSampleTree();

// 1. DFS - Recursive (Pre-order)
//    - Visit the current node first, then the left subtree, then the right subtree.
function dfsRecursivePreOrder(node) {
    if (!node) {
        return;
    }
    console.log("Pre-order (Recursive):", node.val); // Process the current node
    dfsRecursivePreOrder(node.left);  // Recurse on the left child
    dfsRecursivePreOrder(node.right); // Recurse on the right child
}

// 2. DFS - Recursive (In-order)
//    - Visit the left subtree first, then the current node, then the right subtree.
function dfsRecursiveInOrder(node) {
    if (!node) {
        return;
    }
    dfsRecursiveInOrder(node.left);  // Recurse on the left child
    console.log("In-order (Recursive):", node.val); // Process the current node
    dfsRecursiveInOrder(node.right); // Recurse on the right child
}

// 3. DFS - Recursive (Post-order)
//   - Visit the left subtree first, then the right subtree, then the current node.
function dfsRecursivePostOrder(node) {
    if (!node) {
        return;
    }
    dfsRecursivePostOrder(node.left);  // Recurse on the left child
    dfsRecursivePostOrder(node.right); // Recurse on the right child
    console.log("Post-order (Recursive):", node.val); // Process the current node
}

// 4. DFS - Iterative (using a stack, Pre-order)
function dfsIterativePreOrder(root) {
    if (!root) return;

    const stack = [root]; // Initialize stack with the root node
    const visited = [];

    while (stack.length > 0) {
        const node = stack.pop(); // Pop the top node
        console.log("Pre-order (Iterative):", node.val);
        visited.push(node.val); //push to visited

        // Push right child first, so left child is processed first
        if (node.right) {
            stack.push(node.right);
        }
        if (node.left) {
            stack.push(node.left);
        }
    }
     return visited;
}

// 5. DFS - Iterative (using a stack, In-order)
function dfsIterativeInOrder(root) {
    if (!root) return;

    const stack = [];
    let curr = root;

    while (curr || stack.length > 0) {
        while (curr) {
            stack.push(curr);
            curr = curr.left;
        }
        curr = stack.pop();
        console.log("In-order (Iterative):", curr.val);
        curr = curr.right;
    }
}



// --- Execution ---
console.log("--- DFS Traversal ---");
console.log("--- Recursive DFS ---");
console.log("1. Pre-order Traversal (Recursive):");
dfsRecursivePreOrder(treeRoot);
console.log("2. In-order Traversal (Recursive):");
dfsRecursiveInOrder(treeRoot);
console.log("3. Post-order Traversal (Recursive):");
dfsRecursivePostOrder(treeRoot);

console.log("--- Iterative DFS ---");
console.log("4. Pre-order Traversal (Iterative):");
dfsIterativePreOrder(treeRoot);
console.log("5. In-order Traversal (Iterative):");
dfsIterativeInOrder(treeRoot);

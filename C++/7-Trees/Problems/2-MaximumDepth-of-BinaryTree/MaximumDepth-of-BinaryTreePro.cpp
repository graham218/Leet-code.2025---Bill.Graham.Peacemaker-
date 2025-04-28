#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <memory> // For smart pointers

// Definition for a binary tree node.
struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 1. Recursive Depth-First Search (DFS)
//   - Simplest and most intuitive approach.
//   - Directly translates the recursive definition of tree depth.
//   - Uses the call stack to keep track of the current path.
int maxDepthRecursive(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return 0; // Base case: empty tree has depth 0
    }
    // Recursively calculate the depth of the left and right subtrees.
    int leftDepth = maxDepthRecursive(root->left);
    int rightDepth = maxDepthRecursive(root->right);
    // The depth of the current node is 1 (for the node itself) + the maximum depth of its subtrees.
    return 1 + std::max(leftDepth, rightDepth);
}

// 2. Iterative Depth-First Search (DFS) with Stack
//   - Avoids recursion, useful for very deep trees to prevent stack overflow.
//   - Uses a stack to simulate the recursive calls.
//   - Stores both the node and its depth in the stack.
int maxDepthIterativeDFS(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return 0;
    }

    std::stack<std::pair<std::shared_ptr<TreeNode>, int>> nodeStack;
    nodeStack.push({root, 1}); // Start with the root and depth 1
    int maxDepth = 0;

    while (!nodeStack.empty()) {
        std::shared_ptr<TreeNode> node = nodeStack.top().first;
        int depth = nodeStack.top().second;
        nodeStack.pop(); // Get the node

        maxDepth = std::max(maxDepth, depth); // Update the maximum depth

        // Push the right child first, so the left child is processed first (like in recursive DFS)
        if (node->right) {
            nodeStack.push({node->right, depth + 1});
        }
        if (node->left) {
            nodeStack.push({node->left, depth + 1});
        }
    }
    return maxDepth;
}

// 3. Breadth-First Search (BFS) with Queue
//   - Uses a queue to traverse the tree level by level.
//   - The depth is equal to the number of levels in the tree.
//   - More memory-intensive than DFS for wide trees, but guarantees finding the shortest path in unweighted graphs (though not relevant here).
int maxDepthBFS(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return 0;
    }

    std::queue<std::shared_ptr<TreeNode>> nodeQueue;
    nodeQueue.push(root);
    int depth = 0;

    while (!nodeQueue.empty()) {
        int levelSize = nodeQueue.size(); // Number of nodes at the current level
        depth++; // Increment depth for each level

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            std::shared_ptr<TreeNode> node = nodeQueue.front();
            nodeQueue.pop();

            if (node->left) {
                nodeQueue.push(node->left);
            }
            if (node->right) {
                nodeQueue.push(node->right);
            }
        }
    }
    return depth;
}

// 4. Optimized BFS (Slightly More Efficient)
int maxDepthBFSOptimized(std::shared_ptr<TreeNode> root) {
    if (!root) return 0;

    std::queue<std::pair<std::shared_ptr<TreeNode>, int>> q;
    q.push({root, 1});
    int maxDepth = 0;

    while (!q.empty()) {
        std::shared_ptr<TreeNode> node = q.front().first;
        int depth = q.front().second;
        q.pop();
        maxDepth = std::max(maxDepth, depth);
        if (node->left)  q.push({node->left,  depth + 1});
        if (node->right) q.push({node->right, depth + 1});
    }
    return maxDepth;
}

// 5. Morris Traversal (Threaded Tree) -  Most Space Efficient
//   - A more advanced technique that doesn't use recursion or a stack/queue.
//   - Modifies the tree structure temporarily (creates threads) to allow traversal without extra memory.
//   - Restores the original tree structure before finishing.
//   - Best space complexity: O(1)
int maxDepthMorris(std::shared_ptr<TreeNode> root) {
    int maxDepth = 0;
    std::shared_ptr<TreeNode> current = root;
    int currentDepth = 0;

    while (current) {
        if (!current->left) {
            currentDepth++;
            maxDepth = std::max(maxDepth, currentDepth);
            current = current->right;
        } else {
            std::shared_ptr<TreeNode> predecessor = current->left;
            int steps = 1;
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
                steps++;
            }

            if (!predecessor->right) {
                predecessor->right = current; // Create the thread
                currentDepth++;
                current = current->left;
            } else { // predecessor->right == current
                predecessor->right = nullptr; // Remove the thread
                maxDepth = std::max(maxDepth, currentDepth);
                currentDepth -= steps;
                current = current->right;
            }
        }
    }
    return maxDepth;
}

// Helper function to create a sample binary tree (for testing)
std::shared_ptr<TreeNode> createSampleTree() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);
    root->right->right = std::make_shared<TreeNode>(6);
    root->left->left->left = std::make_shared<TreeNode>(7);
    return root;
}

int main() {
    // Create a sample binary tree
    std::shared_ptr<TreeNode> root = createSampleTree();

    // Calculate and print the maximum depth using each method
    std::cout << "Maximum Depth (Recursive DFS): " << maxDepthRecursive(root) << std::endl;
    std::cout << "Maximum Depth (Iterative DFS): " << maxDepthIterativeDFS(root) << std::endl;
    std::cout << "Maximum Depth (BFS): " << maxDepthBFS(root) << std::endl;
    std::cout << "Maximum Depth (BFS Optimized): " << maxDepthBFSOptimized(root) << std::endl;
    std::cout << "Maximum Depth (Morris Traversal): " << maxDepthMorris(root) << std::endl;

    return 0;
}

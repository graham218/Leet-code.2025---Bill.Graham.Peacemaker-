#include <iostream>
#include <queue>
#include <stack>
#include <algorithm> // For std::swap

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Function to print the tree (for testing purposes) - Inorder Traversal
void printTree(TreeNode* root) {
    if (root == nullptr) return;
    printTree(root->left);
    std::cout << root->val << " ";
    printTree(root->right);
}

// Function to delete the tree nodes (to prevent memory leaks)
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 1. Recursive Approach
// Time Complexity: O(n), where n is the number of nodes.
// Space Complexity: O(h), where h is the height of the tree (due to the call stack).  In the worst case of a skewed tree, h = n, so it would be O(n).  In a balanced tree, h = log n, so it would be O(log n).
TreeNode* invertTree_recursive(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    // Swap the left and right subtrees.
    std::swap(root->left, root->right);
    // Recursively invert the left and right subtrees.
    invertTree_recursive(root->left);
    invertTree_recursive(root->right);
    return root;
}

// 2. Iterative Approach using a Queue (Breadth-First Search)
// Time Complexity: O(n), where n is the number of nodes.
// Space Complexity: O(w), where w is the maximum width of the tree. In the worst case (a complete binary tree), w = (n+1)/2, so it's O(n).  For a balanced tree, the maximum width is closer to n/2 at the deepest level.
TreeNode* invertTree_iterative_queue(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        // Swap the left and right children of the current node.
        std::swap(current->left, current->right);

        // Enqueue the left and right children if they exist.
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    return root;
}

// 3. Iterative Approach using a Stack (Depth-First Search)
// Time Complexity: O(n), where n is the number of nodes.
// Space Complexity: O(h), where h is the height of the tree.  Similar to the recursive approach, this can range from O(log n) for a balanced tree to O(n) for a skewed tree.
TreeNode* invertTree_iterative_stack(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    std::stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
        TreeNode* current = s.top();
        s.pop();
        // Swap the left and right children of the current node.
        std::swap(current->left, current->right);

        // Push the right child first so the left child is processed next (DFS).
        if (current->right) {
            s.push(current->right);
        }
        if (current->left) {
            s.push(current->left);
        }
    }
    return root;
}

// 4. Optimized Recursive Approach (Slightly more concise)
// Time Complexity: O(n)
// Space Complexity: O(h)
TreeNode* invertTree_recursive_optimized(TreeNode* root) {
    if (root) {
        std::swap(root->left, root->right);
        invertTree_recursive_optimized(root->left);
        invertTree_recursive_optimized(root->right);
    }
    return root;
}

// 5. Morris Traversal Approach (Iterative, Threaded Tree) -  No extra space
// Time Complexity: O(n), where n is the number of nodes.
// Space Complexity: O(1), constant extra space.  This is the key advantage of Morris traversal.
TreeNode* invertTree_morris(TreeNode* root) {
    TreeNode* current = root;
    TreeNode* prev = nullptr;

    while (current != nullptr) {
        if (current->left == nullptr) {
            // Swap left and right children.
            std::swap(current->left, current->right);
            current = current->right;
        } else {
            // Find the inorder predecessor.
            prev = current->left;
            while (prev->right != nullptr && prev->right != current) {
                prev = prev->right;
            }

            if (prev->right == nullptr) {
                // Create the thread.
                prev->right = current;
                // Swap left and right children *before* moving to the left.
                std::swap(current->left, current->right);
                current = current->left;
            } else {
                // Remove the thread and move to the right child.
                prev->right = nullptr;
                current = current->right;
            }
        }
    }
    return root;
}

int main() {
    // Create a sample binary tree for testing.
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    std::cout << "Original Tree (Inorder): ";
    printTree(root);
    std::cout << std::endl << std::endl;

    TreeNode* invertedRoot;

    // 1. Recursive
    invertedRoot = invertTree_recursive(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9)))); // Create a new tree for each test
    std::cout << "1. Recursive Inverted Tree (Inorder): ";
    printTree(invertedRoot);
    std::cout << std::endl;
    deleteTree(invertedRoot);

    // 2. Iterative Queue
    invertedRoot = invertTree_iterative_queue(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9))));
    std::cout << "2. Iterative Queue Inverted Tree (Inorder): ";
    printTree(invertedRoot);
    std::cout << std::endl;
    deleteTree(invertedRoot);

    // 3. Iterative Stack
    invertedRoot = invertTree_iterative_stack(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9))));
    std::cout << "3. Iterative Stack Inverted Tree (Inorder): ";
    printTree(invertedRoot);
    std::cout << std::endl;
    deleteTree(invertedRoot);

    // 4. Optimized Recursive
    invertedRoot = invertTree_recursive_optimized(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9))));
    std::cout << "4. Optimized Recursive Inverted Tree (Inorder): ";
    printTree(invertedRoot);
    std::cout << std::endl;
    deleteTree(invertedRoot);

    // 5. Morris Traversal
    invertedRoot = invertTree_morris(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9))));
    std::cout << "5. Morris Traversal Inverted Tree (Inorder): ";
    printTree(invertedRoot);
    std::cout << std::endl;
    deleteTree(invertedRoot);

    return 0;
}

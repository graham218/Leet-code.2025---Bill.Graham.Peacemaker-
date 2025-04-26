#include <iostream>
#include <stack>
#include <vector>
#include <memory> // for smart pointers

// Basic structure for a tree node
struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    // Constructor for convenience
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// 1. Recursive DFS - Preorder Traversal (Root, Left, Right)
//   - Simpler to understand and implement for basic DFS
void dfsRecursivePreorder(std::shared_ptr<TreeNode> node, std::vector<int>& result) {
    if (!node) return; // Base case: if the node is null, return

    result.push_back(node->val);      // Process the root (current node)
    dfsRecursivePreorder(node->left, result);  // Traverse the left subtree
    dfsRecursivePreorder(node->right, result); // Traverse the right subtree
}

// 2. Recursive DFS - Inorder Traversal (Left, Root, Right)
void dfsRecursiveInorder(std::shared_ptr<TreeNode> node, std::vector<int>& result) {
    if (!node) return;

    dfsRecursiveInorder(node->left, result);
    result.push_back(node->val);
    dfsRecursiveInorder(node->right, result);
}

// 3. Recursive DFS - Postorder Traversal (Left, Right, Root)
void dfsRecursivePostorder(std::shared_ptr<TreeNode> node, std::vector<int>& result) {
    if (!node) return;

    dfsRecursivePostorder(node->left, result);
    dfsRecursivePostorder(node->right, result);
    result.push_back(node->val);
}

// 4. Iterative DFS - Preorder Traversal using a Stack
//    - More complex than recursion, but avoids stack overflow for deep trees
//    - Uses a stack to mimic the call stack of the recursive approach
void dfsIterativePreorder(std::shared_ptr<TreeNode> root, std::vector<int>& result) {
    if (!root) return;

    std::stack<std::shared_ptr<TreeNode>> stack;
    stack.push(root); // Push the root onto the stack

    while (!stack.empty()) {
        std::shared_ptr<TreeNode> node = stack.top(); // Get the top node
        stack.pop();                            // Remove the top node
        result.push_back(node->val);              // Process the node

        // Push the right child first, so the left child is processed first (LIFO)
        if (node->right) {
            stack.push(node->right);
        }
        if (node->left) {
            stack.push(node->left);
        }
    }
}

// 5. Iterative DFS - Inorder Traversal using a Stack
void dfsIterativeInorder(std::shared_ptr<TreeNode> root, std::vector<int>& result) {
    if (!root) return;

    std::stack<std::shared_ptr<TreeNode>> stack;
    std::shared_ptr<TreeNode> curr = root;

    while (curr || !stack.empty()) {
        // Keep going left until we find a null
        while (curr) {
            stack.push(curr);
            curr = curr->left;
        }
        // Now, process the top of the stack (the leftmost node)
        curr = stack.top();
        stack.pop();
        result.push_back(curr->val);
        // Go right
        curr = curr->right;
    }
}

int main() {
    // Create a sample binary tree using smart pointers
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(7);

    std::vector<int> result;

    // 1. Recursive Preorder DFS
    result.clear();
    dfsRecursivePreorder(root, result);
    std::cout << "Recursive Preorder DFS: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output: 1 2 4 5 3 6 7

    // 2. Recursive Inorder DFS
    result.clear();
    dfsRecursiveInorder(root, result);
    std::cout << "Recursive Inorder DFS: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output: 4 2 5 1 6 3 7

    // 3. Recursive Postorder DFS
    result.clear();
    dfsRecursivePostorder(root, result);
    std::cout << "Recursive Postorder DFS: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output: 4 5 2 6 7 3 1

    // 4. Iterative Preorder DFS
    result.clear();
    dfsIterativePreorder(root, result);
    std::cout << "Iterative Preorder DFS: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output: 1 2 4 5 3 6 7

    // 5. Iterative Inorder DFS
    result.clear();
    dfsIterativeInorder(root, result);
    std::cout << "Iterative Inorder DFS: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output: 4 2 5 1 6 3 7

    return 0;
}

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

// Function to print the tree (for testing purposes) - using level order traversal
void printTree(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            std::shared_ptr<TreeNode> current = q.front();
            q.pop();

            if (current) {
                std::cout << current->val << " ";
                q.push(current->left);
                q.push(current->right);
            } else {
                std::cout << "null ";
            }
        }
        std::cout << std::endl; // Move to the next level
    }
}

// Approach 1: Recursive Approach
// - Classic and concise.  Good for understanding the basic concept.
// - Real-world use: Simple inverting of tree structures where performance is not critical.  Configuration file manipulation, simple data transformations.
std::shared_ptr<TreeNode> invertTree_Recursive(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return nullptr;
    }
    // Swap left and right children.
    std::swap(root->left, root->right);
    // Recursively invert the left and right subtrees.
    invertTree_Recursive(root->left);
    invertTree_Recursive(root->right);
    return root;
}

// Approach 2: Iterative Approach using a Queue (Level Order Traversal)
// - Uses a queue for breadth-first traversal.
// - Real-world use:  Inverting trees where you need to process nodes level by level.  Good for wider trees.  Useful in UI updates, processing scene graph nodes in a game engine.
std::shared_ptr<TreeNode> invertTree_Iterative_Queue(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return nullptr;
    }

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(root);

    while (!q.empty()) {
        std::shared_ptr<TreeNode> current = q.front();
        q.pop();
        std::swap(current->left, current->right); // Swap the children

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    return root;
}

// Approach 3: Iterative Approach using a Stack (Depth First Traversal)
// - Uses a stack for depth-first traversal.
// - Real-world use: Inverting trees where you need to process nodes in a depth-first manner.  Good for deep trees.  Useful in compiler design, inverting expression trees.
std::shared_ptr<TreeNode> invertTree_Iterative_Stack(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return nullptr;
    }

    std::stack<std::shared_ptr<TreeNode>> s;
    s.push(root);

    while (!s.empty()) {
        std::shared_ptr<TreeNode> current = s.top();
        s.pop();
        std::swap(current->left, current->right); // Swap the children.

        if (current->left) {
            s.push(current->left);
        }
        if (current->right) {
            s.push(current->right);
        }
    }
    return root;
}

// Approach 4: Optimized Recursive (Slightly more efficient in some cases)
// - Tail-recursive in *some* compiler implementations (though C++ doesn't guarantee it), potentially optimizing stack usage.
// - Real-world use: When you want a recursive approach, but are concerned about stack overflow with very deep trees.  May not always provide a performance advantage in C++.
std::shared_ptr<TreeNode> invertTree_Recursive_Optimized(std::shared_ptr<TreeNode> root) {
    if (!root) {
        return nullptr;
    }

    std::shared_ptr<TreeNode> left = invertTree_Recursive_Optimized(root->left);
    std::shared_ptr<TreeNode> right = invertTree_Recursive_Optimized(root->right);
    std::swap(root->left, root->right);
    return root;
}

// Approach 5: Using std::function and a visit function (Generalized)
// - Uses a function object to visit each node, allowing for more flexible tree traversals.
// - Real-world use:  Highly flexible, good for complex tree manipulations where you want to separate the traversal logic from the node processing.  Useful in AI, complex data structure manipulation.
#include <functional>

std::shared_ptr<TreeNode> invertTree_Generalized(std::shared_ptr<TreeNode> root) {
    if (!root) return nullptr;

    std::function<void(std::shared_ptr<TreeNode>)> visit;
    std::stack<std::shared_ptr<TreeNode>> stack;
    stack.push(root);

    visit = [&](std::shared_ptr<TreeNode> node) {
        if (node) {
            std::swap(node->left, node->right); // Invert here
            if (node->left) stack.push(node->left);
            if (node->right) stack.push(node->right);
        }
    };

    while (!stack.empty()) {
        visit(stack.top());
        stack.pop();
    }
    return root;
}

int main() {
    // Create a sample binary tree using smart pointers
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(4);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(7);
    root->left->left = std::make_shared<TreeNode>(1);
    root->left->right = std::make_shared<TreeNode>(3);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(9);

    std::cout << "Original Tree (Level Order):" << std::endl;
    printTree(root);

    std::cout << "\nInverted Tree (Recursive):" << std::endl;
    std::shared_ptr<TreeNode> invertedRootRecursive = invertTree_Recursive(root);
    printTree(invertedRootRecursive);

    // Reset the tree
    root = std::make_shared<TreeNode>(4);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(7);
    root->left->left = std::make_shared<TreeNode>(1);
    root->left->right = std::make_shared<TreeNode>(3);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(9);
    std::cout << "\nInverted Tree (Iterative Queue):" << std::endl;
    std::shared_ptr<TreeNode> invertedRootQueue = invertTree_Iterative_Queue(root);
    printTree(invertedRootQueue);

    // Reset the tree
    root = std::make_shared<TreeNode>(4);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(7);
    root->left->left = std::make_shared<TreeNode>(1);
    root->left->right = std::make_shared<TreeNode>(3);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(9);
    std::cout << "\nInverted Tree (Iterative Stack):" << std::endl;
    std::shared_ptr<TreeNode> invertedRootStack = invertTree_Iterative_Stack(root);
    printTree(invertedRootStack);

    root = std::make_shared<TreeNode>(4);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(7);
    root->left->left = std::make_shared<TreeNode>(1);
    root->left->right = std::make_shared<TreeNode>(3);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(9);
    std::cout << "\nInverted Tree (Recursive Optimized):" << std::endl;
    std::shared_ptr<TreeNode> invertedRootOptimized = invertTree_Recursive_Optimized(root);
    printTree(invertedRootOptimized);

    root = std::make_shared<TreeNode>(4);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(7);
    root->left->left = std::make_shared<TreeNode>(1);
    root->left->right = std::make_shared<TreeNode>(3);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(9);
    std::cout << "\nInverted Tree (Generalized):" << std::endl;
    std::shared_ptr<TreeNode> invertedRootGeneralized = invertTree_Generalized(root);
    printTree(invertedRootGeneralized);

    return 0;
}

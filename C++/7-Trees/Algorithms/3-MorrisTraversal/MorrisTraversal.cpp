#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits> // Required for numeric_limits

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Function to create a sample binary tree for testing
TreeNode* createSampleTree() {
    // Create nodes
    TreeNode* root = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);

    // Connect nodes to form the tree
    root->left = node2;
    root->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;

    return root;
}

// Function to print the tree in inorder (for verification)
void printInorder(TreeNode* root) {
    if (root == nullptr) return;
    printInorder(root->left);
    std::cout << root->val << " ";
    printInorder(root->right);
}

// 1. Morris Inorder Traversal - Iterative, No Stack
// Traverses the tree in inorder without using a stack or recursion.
// It modifies the tree structure temporarily to keep track of the path.
//
// Key Idea:
// - For each node, find its inorder predecessor (the rightmost node in its left subtree).
// - If the predecessor's right child is null, make the predecessor's right child point to the current node, and move to the left child.
// - If the predecessor's right child is the current node, restore the tree (remove the link) and move to the right child.
//
// Time Complexity: O(n) - Each node is visited at most twice.
// Space Complexity: O(1) - Constant extra space.
std::vector<int> morrisInorderTraversal(TreeNode* root) {
    std::vector<int> result;
    TreeNode* current = root;

    while (current != nullptr) {
        if (current->left == nullptr) {
            result.push_back(current->val);
            current = current->right;
        } else {
            // Find the inorder predecessor
            TreeNode* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                // Create the link to the current node
                predecessor->right = current;
                current = current->left;
            } else {
                // Restore the tree and process the current node
                predecessor->right = nullptr; // Remove the link
                result.push_back(current->val);
                current = current->right;
            }
        }
    }
    return result;
}

// 2. Morris Preorder Traversal
// Traverses the tree in preorder without using recursion or a stack.
// It utilizes the same threaded tree concept as Morris inorder traversal but differs in when the node value is processed.
//
// Key Idea:
// - The core idea is similar to Morris inorder. We find the predecessor.
// - The difference is that we process the node (add to result) *before* creating the thread.
// - When the thread is removed, we don't process the node again.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
std::vector<int> morrisPreorderTraversal(TreeNode* root) {
    std::vector<int> result;
    TreeNode* current = root;

    while (current != nullptr) {
        if (current->left == nullptr) {
            result.push_back(current->val); // Process before moving
            current = current->right;
        } else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                result.push_back(current->val); // Process before creating thread
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                current = current->right;
            }
        }
    }
    return result;
}

// 3. Morris Postorder Traversal (Tricky)
//  Morris postorder traversal is more complex than inorder or preorder because postorder requires visiting the children before the parent.
//  This implementation involves reversing the links of the right subtree of the predecessor and then reversing them back.
//
// Key Idea:
//  1.  Find the predecessor.
//  2.  If predecessor's right is null, create a thread to the current node.
//  3.  If predecessor's right is the current node:
//      a.  Reverse the right links of the left subtree of the current node.
//      b.  Add the reversed nodes to the result.
//      c.  Reverse the links back to their original state.
//      d.  Remove the thread.
//  4.  Move to the right child.
//
// Time Complexity: O(n) - Each node is visited a constant number of times.
// Space Complexity: O(1) - Constant extra space.
std::vector<int> morrisPostorderTraversal(TreeNode* root) {
    std::vector<int> result;
    TreeNode* dummy = new TreeNode(0); // Dummy node for easier processing of the root
    dummy->left = root;
    TreeNode* current = dummy;
    TreeNode* prev = nullptr;

    while (current) {
        if (current->left == nullptr) {
            current = current->right;
        } else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                // Reverse the right links of the left subtree and add to result
                TreeNode* temp = current->left;
                TreeNode* tail = temp;
                TreeNode* next = nullptr;
                prev = nullptr;
                while (tail != nullptr)
                {
                    next = tail->right;
                    tail->right = prev;
                    prev = tail;
                    tail = next;
                }
                tail = prev; // tail now points to the last node of reversed list
                while (tail != nullptr)
                {
                    result.push_back(tail->val);
                    next = tail->right;
                    tail->right = prev;
                    prev = tail;
                    tail = next;
                }
                current = current->right;
            }
        }
    }
    return result;
}

// 4. Morris Level Order Traversal (Not a standard Morris Traversal)
//    Morris traversal, in its standard form, is primarily designed for inorder, preorder, and postorder traversals, which are depth-first traversals.
//    Level order traversal, on the other hand, is a breadth-first traversal.  Therefore, a true "Morris" level order traversal,
//    which avoids extra space, is not directly possible.
//    This implementation uses a queue, which is the standard approach for level order.
//
// Time Complexity: O(n)
// Space Complexity: O(w) where w is the maximum width of the tree.  In the worst case, w can be n/2, so it's O(n).
std::vector<int> levelOrderTraversal(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) return result;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        result.push_back(current->val);

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    return result;
}

// 5.  Inorder Traversal using Stack (Iterative)
// Performs an inorder traversal using a stack.  This is a standard iterative approach,
// included here for comparison and completeness.  It's not a Morris traversal,
// but it's a common way to do inorder traversal without recursion.
//
// Time Complexity: O(n) - Each node is visited at most twice (once when pushed, once when popped).
// Space Complexity: O(h) - Where h is the height of the tree.  In the worst case (skewed tree), h can be n, so it's O(n).  In the average case (balanced tree), it's O(log n).
std::vector<int> inorderTraversalWithStack(TreeNode* root) {
    std::vector<int> result;
    std::stack<TreeNode*> stack;
    TreeNode* current = root;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        result.push_back(current->val);
        current = current->right;
    }
    return result;
}

int main() {
    TreeNode* root = createSampleTree();

    std::cout << "Original Tree (Inorder): ";
    printInorder(root);
    std::cout << std::endl;

    std::cout << "\n1. Morris Inorder Traversal: ";
    std::vector<int> inorderResult = morrisInorderTraversal(root);
    for (int val : inorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\n2. Morris Preorder Traversal: ";
    std::vector<int> preorderResult = morrisPreorderTraversal(root);
    for (int val : preorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\n3. Morris Postorder Traversal: ";
    std::vector<int> postorderResult = morrisPostorderTraversal(root);
    for (int val : postorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\n4. Level Order Traversal: ";
    std::vector<int> levelOrderResult = levelOrderTraversal(root);
    for (int val : levelOrderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\n5. Inorder Traversal with Stack: ";
    std::vector<int> stackInorderResult = inorderTraversalWithStack(root);
    for (int val : stackInorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}

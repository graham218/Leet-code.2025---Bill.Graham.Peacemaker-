#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <tuple> // Required for std::tie

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Approach 1: Iterative using Queue (Standard Level Order Traversal)
    // - Time Complexity: O(N), where N is the number of nodes in the tree.
    // - Space Complexity: O(W), where W is the maximum width of the tree.
    std::vector<std::vector<int>> levelOrder1(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) return result;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            std::vector<int> currentLevel;

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(currentLevel);
        }
        return result;
    }

    // Approach 2: Iterative using Queue (Optimized)
    // - Time Complexity: O(N), where N is the number of nodes.
    // - Space Complexity: O(W), where W is the maximum width of the tree.
    std::vector<std::vector<int>> levelOrder2(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) return result;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            std::vector<int> currentLevel;
            // Get the number of nodes at the current level.
            for (int i = q.size(); i > 0; --i) { // Important: use q.size() here
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(currentLevel);
        }
        return result;
    }


    // Approach 3: Recursive (Pre-order Traversal with Level)
    // - Time Complexity: O(N), where N is the number of nodes.
    // - Space Complexity: O(H), where H is the height of the tree (due to recursion stack).
    void levelOrderRecursiveHelper(TreeNode* node, int level, std::vector<std::vector<int>>& result) {
        if (!node) return;

        if (level >= result.size()) {
            result.push_back({}); // Create a new level if it doesn't exist
        }
        result[level].push_back(node->val); // Add node's value to the corresponding level
        levelOrderRecursiveHelper(node->left, level + 1, result); // Recurse for left child
        levelOrderRecursiveHelper(node->right, level + 1, result); // Recurse for right child
    }

    std::vector<std::vector<int>> levelOrder3(TreeNode* root) {
        std::vector<std::vector<int>> result;
        levelOrderRecursiveHelper(root, 0, result);
        return result;
    }



    // Approach 4: Using a pair in queue to store node and level.
    // - Time Complexity: O(N), where N is the number of nodes.
    // - Space Complexity: O(W), where W is the maximum width of the tree.
    std::vector<std::vector<int>> levelOrder4(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) return result;

        std::queue<std::pair<TreeNode*, int>> q;
        q.push({root, 0}); // Store the root node and its level (0)

        while (!q.empty()) {
            TreeNode* node = q.front().first;
            int level = q.front().second;
            q.pop();

            if (level >= result.size()) {
                result.push_back({}); // Create a new level if needed
            }
            result[level].push_back(node->val);

            if (node->left)  q.push({node->left,  level + 1});
            if (node->right) q.push({node->right, level + 1});
        }
        return result;
    }

    // Approach 5: Morris Traversal (Without extra space, but modifies tree)
    // This approach is more complex and modifies the tree structure temporarily.
    // It's generally NOT recommended for standard level order traversal in interviews
    // unless you are explicitly asked to do it without extra space.  It's included
    // here for completeness.
    // - Time Complexity: O(N), where N is the number of nodes.
    // - Space Complexity: O(1) (constant), but modifies the tree.
    std::vector<std::vector<int>> levelOrder5(TreeNode* root) {
        std::vector<std::vector<int>> result;
        TreeNode* current = root;

        while (current) {
            // `head` will point to the leftmost node of current level.
            TreeNode* head = current;
            std::vector<int> currentLevel;

            // Traverse the current level using the 'next' pointer
            while (head)
            {
                currentLevel.push_back(head->val);
                head = head->right;
            }
            result.push_back(currentLevel);

            TreeNode* nextLevelStart = nullptr;
            TreeNode* prev = nullptr;
            TreeNode* temp = current;

            while (temp)
            {
                if (temp->left)
                {
                    if (!nextLevelStart)
                        nextLevelStart = temp->left;

                    TreeNode* rightMost = temp->left;
                    while (rightMost->right && rightMost->right != temp)
                        rightMost = rightMost->right;

                    if (!rightMost->right)
                    {
                        rightMost->right = temp;
                        TreeNode* toProcess = temp;
                        temp = temp->left;
                        continue;
                    }
                    else
                    {
                        rightMost->right = nullptr;
                    }
                }
                temp = temp->right;
            }
            current = nextLevelStart;
        }
        return result;
    }
};

// Helper function to create a binary tree for testing
TreeNode* createTree(const std::vector<int>& values, int index, int n) {
    if (index >= n || values[index] == -1) { // -1 represents null
        return nullptr;
    }
    TreeNode* node = new TreeNode(values[index]);
    node->left = createTree(values, 2 * index + 1, n);
    node->right = createTree(values, 2 * index + 2, n);
    return node;
}

// Helper function to print the level order traversal result
void printLevelOrder(const std::vector<std::vector<int>>& result) {
    std::cout << "Level Order Traversal:" << std::endl;
    for (const auto& level : result) {
        for (int val : level) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Solution solution;

    // Example usage:
    // Create a binary tree: [3,9,20,null,null,15,7]  (where null is represented as -1)
    std::vector<int> treeValues = {3, 9, 20, -1, -1, 15, 7};
    TreeNode* root = createTree(treeValues, 0, treeValues.size());

    // Approach 1: Iterative using Queue
    std::vector<std::vector<int>> result1 = solution.levelOrder1(root);
    std::cout << "Approach 1:\n";
    printLevelOrder(result1);

    // Approach 2: Iterative using Queue (Optimized)
    std::vector<std::vector<int>> result2 = solution.levelOrder2(root);
    std::cout << "\nApproach 2:\n";
    printLevelOrder(result2);

    // Approach 3: Recursive
    std::vector<std::vector<int>> result3 = solution.levelOrder3(root);
    std::cout << "\nApproach 3:\n";
    printLevelOrder(result3);

    // Approach 4: Using a pair in queue
    std::vector<std::vector<int>> result4 = solution.levelOrder4(root);
    std::cout << "\nApproach 4:\n";
    printLevelOrder(result4);

    // Approach 5: Morris Traversal (Modifies the tree)
    std::vector<std::vector<int>> result5 = solution.levelOrder5(root);
    std::cout << "\nApproach 5:\n";
    printLevelOrder(result5);
    // The tree is modified by levelOrder5, so further operations on 'root' might be incorrect.

    return 0;
}

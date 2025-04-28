#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>
#include <vector>

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
    // Approach 1: Recursive Depth First Search (DFS)
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree.  In the worst case, H=N (skewed tree), in the best case, H=logN (balanced tree).
    int maxDepthRecursive(TreeNode* root) {
        if (root == nullptr) {
            return 0; // Base case: an empty tree has a depth of 0.
        }
        // Recursively calculate the depth of the left and right subtrees.
        int leftDepth = maxDepthRecursive(root->left);
        int rightDepth = maxDepthRecursive(root->right);
        // The depth of the current node is 1 + the maximum depth of its subtrees.
        return 1 + std::max(leftDepth, rightDepth);
    }

    // Approach 2: Iterative Breadth First Search (BFS) using a queue
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(W), where W is the maximum width of the tree.  In the worst case, W=N (complete binary tree).
    int maxDepthBFS(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            int levelSize = q.size(); // Number of nodes at the current level.
            depth++; // Increment depth for each level.

            // Process all nodes at the current level.
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return depth;
    }

    // Approach 3: Iterative Depth First Search (DFS) using a stack
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(H), where H is the height of the tree.  In the worst case, H=N (skewed tree).
    int maxDepthDFS(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        std::stack<std::pair<TreeNode*, int>> s; // Store node and its depth.
        s.push({root, 1}); // Start with the root node at depth 1.
        int maxDepth = 0;

        while (!s.empty()) {
            TreeNode* node = s.top().first;
            int depth = s.top().second;
            s.pop();

            maxDepth = std::max(maxDepth, depth); // Update maxDepth if necessary.

            if (node->left) {
                s.push({node->left, depth + 1}); // Push left child with increased depth.
            }
            if (node->right) {
                s.push({node->right, depth + 1}); // Push right child with increased depth.
            }
        }
        return maxDepth;
    }

     // Approach 4: Using a vector to store nodes at each level (similar to BFS but without queue)
    int maxDepthVector(TreeNode* root) {
        if (!root) return 0;

        std::vector<TreeNode*> currentLevel;
        currentLevel.push_back(root);
        int depth = 0;

        while (!currentLevel.empty()) {
            depth++;
            std::vector<TreeNode*> nextLevel;
            for (TreeNode* node : currentLevel) {
                if (node->left)  nextLevel.push_back(node->left);
                if (node->right) nextLevel.push_back(node->right);
            }
            currentLevel = nextLevel; // Move to the next level
        }
        return depth;
    }

    // Approach 5: Morris Traversal (Depth Calculation during Traversal) - Tricky and modifies the tree
    // Time Complexity: O(N), where N is the number of nodes.
    // Space Complexity: O(1) - Constant space.  This approach modifies the tree structure temporarily.
    int maxDepthMorris(TreeNode* root) {
        int maxDepth = 0;
        int currentDepth = 0;
        TreeNode* current = root;

        while (current) {
            if (!current->left) {
                currentDepth++;
                maxDepth = std::max(maxDepth, currentDepth);
                current = current->right;
            } else {
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }

                if (!predecessor->right) {
                    predecessor->right = current; // Create the threaded link
                    currentDepth++;
                    current = current->left;
                } else { // predecessor->right == current
                    predecessor->right = nullptr; // Remove the threaded link
                    maxDepth = std::max(maxDepth, currentDepth);
                    currentDepth--; // Backtrack one level
                    current = current->right;
                }
            }
        }
        return maxDepth;
    }
};

// Helper function to create a binary tree for testing
TreeNode* createTree(const std::vector<int>& values, int index) {
    if (index >= values.size() || values[index] == -1) { // -1 represents null
        return nullptr;
    }
    TreeNode* node = new TreeNode(values[index]);
    node->left = createTree(values, 2 * index + 1);
    node->right = createTree(values, 2 * index + 2);
    return node;
}

// Helper function to print the tree (inorder traversal)
void printTree(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "-1 "; // Represent null nodes as -1
        return;
    }
    printTree(root->left);
    std::cout << root->val << " ";
    printTree(root->right);
}

// Helper function to delete the binary tree.  Prevents memory leaks.
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution sol;

    // Example usage:
    // Create a binary tree: [3,9,20,-1,-1,15,7] where -1 represents null
    std::vector<int> treeValues = {3, 9, 20, -1, -1, 15, 7};
    TreeNode* root = createTree(treeValues, 0);

    std::cout << "Tree (Inorder Traversal): ";
    printTree(root);
    std::cout << std::endl;

    // Test the different approaches
    std::cout << "Maximum Depth (Recursive DFS): " << sol.maxDepthRecursive(root) << std::endl;
    std::cout << "Maximum Depth (Iterative BFS): " << sol.maxDepthBFS(root) << std::endl;
    std::cout << "Maximum Depth (Iterative DFS): " << sol.maxDepthDFS(root) << std::endl;
    std::cout << "Maximum Depth (Vector): " << sol.maxDepthVector(root) << std::endl;
    std::cout << "Maximum Depth (Morris Traversal): " << sol.maxDepthMorris(root) << std::endl;

    // Remember to delete the tree to free memory.
    deleteTree(root);

    return 0;
}

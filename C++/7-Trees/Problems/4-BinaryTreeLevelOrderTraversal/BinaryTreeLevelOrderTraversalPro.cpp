#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <map> // Include the map header

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
    // Approach 1: Iterative using Queue (Most Common and Efficient)
    // - Uses a queue to store nodes at each level.
    // - Processes nodes level by level, adding their children to the queue.
    // - Time Complexity: O(N), Space Complexity: O(W) (where W is the maximum width of the tree)
    std::vector<std::vector<int>> levelOrder_iterative_queue(TreeNode* root) {
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

                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(currentLevel);
        }
        return result;
    }

    // Approach 2: Recursive Depth-First Search (DFS)
    // - Uses recursion to traverse the tree.
    // - Keeps track of the level of each node.
    // - Expands the result vector as needed.
    // - Time Complexity: O(N), Space Complexity: O(H) (where H is the height of the tree)
    std::vector<std::vector<int>> levelOrder_recursive_dfs(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) return result;
        levelOrderHelper(root, 0, result);
        return result;
    }

    void levelOrderHelper(TreeNode* node, int level, std::vector<std::vector<int>>& result) {
        if (!node) return;

        if (level >= result.size()) {
            result.push_back({}); // Create a new level if it doesn't exist
        }

        result[level].push_back(node->val);
        levelOrderHelper(node->left, level + 1, result);
        levelOrderHelper(node->right, level + 1, result);
    }

    // Approach 3: Iterative with Level Tracking (No Queue Size)
    // - Iterative approach using a queue.
    // - Tracks the current level and the next level's nodes.
    // - Avoids using q.size() in the inner loop.
    // - Time Complexity: O(N), Space Complexity: O(W)
    std::vector<std::vector<int>> levelOrder_iterative_level_tracking(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) return result;

        std::queue<TreeNode*> q;
        q.push(root);
        int currentLevelNodes = 1; // Number of nodes at the current level
        int nextLevelNodes = 0;    // Number of nodes at the next level

        while (!q.empty()) {
            std::vector<int> currentLevel;
            for (int i = 0; i < currentLevelNodes; ++i) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);

                if (node->left) {
                    q.push(node->left);
                    nextLevelNodes++;
                }
                if (node->right) {
                    q.push(node->right);
                    nextLevelNodes++;
                }
            }
            result.push_back(currentLevel);
            currentLevelNodes = nextLevelNodes; // Move to the next level
            nextLevelNodes = 0;                // Reset for the next level
        }
        return result;
    }

    // Approach 4: Modified DFS with Level Map (Pre-order Traversal)
    // - Uses a modified DFS (pre-order) to traverse the tree.
    // - Stores nodes at each level in a map.
    // - Converts the map to a vector of vectors.
    // - Time Complexity: O(N), Space Complexity: O(N)
    std::vector<std::vector<int>> levelOrder_dfs_level_map(TreeNode* root) {
        std::map<int, std::vector<int>> levelMap;
        if (!root) return {};

        dfsWithLevelMap(root, 0, levelMap);

        std::vector<std::vector<int>> result;
        for (const auto& pair : levelMap) {
            result.push_back(pair.second);
        }
        return result;
    }

    void dfsWithLevelMap(TreeNode* node, int level, std::map<int, std::vector<int>>& levelMap) {
        if (!node) return;

        levelMap[level].push_back(node->val); // Store the node's value at its level
        dfsWithLevelMap(node->left, level + 1, levelMap);
        dfsWithLevelMap(node->right, level + 1, levelMap);
    }
};

// Helper function to create a binary tree for testing
TreeNode* createTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < values.size() && values[i] != std::numeric_limits<int>::max()) { // Use max int to represent null
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != std::numeric_limits<int>::max()) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
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

    // Example 1: Simple binary tree
    std::vector<int> values1 = {3, 9, 20, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 15, 7};
    TreeNode* root1 = createTree(values1);
    std::cout << "Example 1:" << std::endl;
    std::cout << "Iterative Queue: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_queue(root1));
    std::cout << "Recursive DFS: " << std::endl;
    printLevelOrder(solution.levelOrder_recursive_dfs(root1));
    std::cout << "Iterative Level Tracking: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_level_tracking(root1));
    std::cout << "DFS with Level Map: " << std::endl;
    printLevelOrder(solution.levelOrder_dfs_level_map(root1));

    // Example 2: Empty tree
    std::vector<int> values2 = {};
    TreeNode* root2 = createTree(values2);
    std::cout << "\nExample 2: Empty Tree" << std::endl;
    std::cout << "Iterative Queue: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_queue(root2));
    std::cout << "Recursive DFS: " << std::endl;
    printLevelOrder(solution.levelOrder_recursive_dfs(root2));
    std::cout << "Iterative Level Tracking: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_level_tracking(root2));
    std::cout << "DFS with Level Map: " << std::endl;
    printLevelOrder(solution.levelOrder_dfs_level_map(root2));

    // Example 3: Tree with only root
    std::vector<int> values3 = {1};
    TreeNode* root3 = createTree(values3);
    std::cout << "\nExample 3: Single Node Tree" << std::endl;
    std::cout << "Iterative Queue: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_queue(root3));
    std::cout << "Recursive DFS: " << std::endl;
    printLevelOrder(solution.levelOrder_recursive_dfs(root3));
    std::cout << "Iterative Level Tracking: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_level_tracking(root3));
    std::cout << "DFS with Level Map: " << std::endl;
    printLevelOrder(solution.levelOrder_dfs_level_map(root3));

    // Example 4: Skewed tree (left side)
    std::vector<int> values4 = {1, 2, std::numeric_limits<int>::max(), 3, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 4};
    TreeNode* root4 = createTree(values4);
    std::cout << "\nExample 4: Left Skewed Tree" << std::endl;
    std::cout << "Iterative Queue: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_queue(root4));
    std::cout << "Recursive DFS: " << std::endl;
    printLevelOrder(solution.levelOrder_recursive_dfs(root4));
    std::cout << "Iterative Level Tracking: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_level_tracking(root4));
    std::cout << "DFS with Level Map: " << std::endl;
    printLevelOrder(solution.levelOrder_dfs_level_map(root4));

    // Example 5: Complete Binary Tree
    std::vector<int> values5 = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root5 = createTree(values5);
    std::cout << "\nExample 5: Complete Binary Tree" << std::endl;
    std::cout << "Iterative Queue: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_queue(root5));
    std::cout << "Recursive DFS: " << std::endl;
    printLevelOrder(solution.levelOrder_recursive_dfs(root5));
    std::cout << "Iterative Level Tracking: " << std::endl;
    printLevelOrder(solution.levelOrder_iterative_level_tracking(root5));
    std::cout << "DFS with Level Map: " << std::endl;
    printLevelOrder(solution.levelOrder_dfs_level_map(root5));
    // Remember to free the allocated memory for the trees if needed
    // (not shown in this example for brevity, but important in real applications)
    delete root1;
    delete root2;
    delete root3;
    delete root4;
    delete root5;

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // Approach 1: Recursive Approach
    // - Recursively search for p and q in the tree.
    // - If both p and q are found in the left subtree, the LCA must be in the left subtree.
    // - If both p and q are found in the right subtree, the LCA must be in the right subtree.
    // - Otherwise, the current node is the LCA.
    TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }
        TreeNode* left = lowestCommonAncestorRecursive(root->left, p, q);
        TreeNode* right = lowestCommonAncestorRecursive(root->right, p, q);
        if (left == NULL) {
            return right;
        } else if (right == NULL) {
            return left;
        } else {
            return root;
        }
    }

    // Approach 2: Iterative using Parent Pointers
    // - Use a stack to traverse the tree and store each node's parent.
    // - Store the paths from the root to p and q in separate vectors.
    // - Compare the paths to find the last common node.
    TreeNode* lowestCommonAncestorIterativeParentPointers(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        std::map<TreeNode*, TreeNode*> parentMap; // Map to store child -> parent mapping
        std::stack<TreeNode*> stack;
        stack.push(root);
        parentMap[root] = nullptr; // Root has no parent

        // Iterate until we find both p and q
        while (parentMap.find(p) == parentMap.end() || parentMap.find(q) == parentMap.end()) {
            TreeNode* node = stack.top();
            stack.pop();

            if (node->left) {
                parentMap[node->left] = node;
                stack.push(node->left);
            }
            if (node->right) {
                parentMap[node->right] = node;
                stack.push(node->right);
            }
        }

        // Get the ancestors of p
        std::vector<TreeNode*> pathP;
        while (p) {
            pathP.push_back(p);
            p = parentMap[p];
        }

        // Get the ancestors of q
        std::vector<TreeNode*> pathQ;
        while (q) {
            pathQ.push_back(q);
            q = parentMap[q];
        }

        // Find the last common ancestor
        TreeNode* lca = nullptr;
        for (int i = pathP.size() - 1, j = pathQ.size() - 1; i >= 0 && j >= 0; --i, --j) {
            if (pathP[i] == pathQ[j]) {
                lca = pathP[i];
            } else {
                break;
            }
        }
        return lca;
    }

    // Approach 3: Using Node Levels (Iterative)
    // - Find the levels of nodes p and q.
    // - Bring the deeper node to the same level as the shallower node.
    // - Move both nodes up until they meet.
    TreeNode* lowestCommonAncestorWithLevels(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        std::map<TreeNode*, int> levelMap; // Stores node -> level
        std::queue<std::pair<TreeNode*, int>> queue; // Stores node and its level
        queue.push({root, 0});
        levelMap[root] = 0;

        // BFS to calculate levels of all nodes, including p and q
        while (!queue.empty()) {
            TreeNode* node = queue.front().first;
            int level = queue.front().second;
            queue.pop();

            if (node->left) {
                levelMap[node->left] = level + 1;
                queue.push({node->left, level + 1});
            }
            if (node->right) {
                levelMap[node->right] = level + 1;
                queue.push({node->right, level + 1});
            }
        }
        int levelP = levelMap[p];
        int levelQ = levelMap[q];

        // Bring the deeper node to the same level as the shallower node
        while (levelP > levelQ) {
            p = findParent(root, p); // Helper to find parent, see below
            levelP--;
        }
        while (levelQ > levelP) {
            q = findParent(root, q); // Helper to find parent
            levelQ--;
        }

        // Move both nodes up until they meet
        while (p != q) {
            p = findParent(root, p); // Helper to find parent
            q = findParent(root, q); // Helper to find parent
        }
        return p;
    }

    // Helper function to find the parent of a node in the tree.  Used by approach 3.
    TreeNode* findParent(TreeNode* root, TreeNode* child) {
        if (!root || root == child) return nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left == child || node->right == child) {
                return node;
            }
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return nullptr;
    }



    // Approach 4: Morris Traversal (No Extra Space)
    // - Morris traversal is a way to traverse a tree without using a stack or recursion.
    // - It works by temporarily modifying the tree structure.
    // - Find p and q using Morris Traversal.
    // - After finding p and q, find LCA.
    TreeNode* lowestCommonAncestorMorris(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        TreeNode* current = root;
        TreeNode* pre;

        // Find p and q using Morris Traversal
        while (current && (first == nullptr || second == nullptr)) {
            if (current->left == nullptr) {
                if (current == p) first = p;
                if (current == q) second = q;
                current = current->right;
            } else {
                pre = current->left;
                while (pre->right != nullptr && pre->right != current)
                    pre = pre->right;

                if (pre->right == nullptr) {
                    pre->right = current;
                    if (current == p) first = p;
                    if (current == q) second = q;
                    current = current->left;
                } else {
                    pre->right = nullptr;
                    current = current->right;
                }
            }
        }

        if (first == nullptr || second == nullptr) return nullptr; // Handle if p or q not in tree

        // Find LCA
        std::vector<TreeNode*> pathP, pathQ;
        getPath(root, p, pathP);
        getPath(root, q, pathQ);

        TreeNode* lca = nullptr;
        for (size_t i = 0, j = 0; i < pathP.size() && j < pathQ.size(); ++i, ++j) {
            if (pathP[i] == pathQ[j])
                lca = pathP[i];
            else
                break;
        }
        return lca;
    }

    // Helper function to get path from root to a node. Used by Morris.
    bool getPath(TreeNode* root, TreeNode* target, std::vector<TreeNode*>& path) {
        if (!root) return false;
        path.push_back(root);
        if (root == target) return true;
        if (getPath(root->left, target, path) || getPath(root->right, target, path))
            return true;
        path.pop_back();
        return false;
    }


    // Approach 5: Iterative using Stack
    // - Use a stack to keep track of the path from the root to the current node.
    // - When we find p or q, save the current path.
    // - Compare the two paths to find the LCA.
    TreeNode* lowestCommonAncestorIterativeStack(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        std::stack<TreeNode*> stack;
        std::vector<TreeNode*> pathP, pathQ;
        std::map<TreeNode*, bool> visited; // Keep track of visited

        stack.push(root);
        visited[root] = true;

        while (!stack.empty() && (pathP.empty() || pathQ.empty())) {
            TreeNode* current = stack.top();

            if (current == p && pathP.empty()) {
                // Convert stack to vector
                std::stack<TreeNode*> tempStack = stack;
                while (!tempStack.empty()) {
                    pathP.push_back(tempStack.top());
                    tempStack.pop();
                }
                std::reverse(pathP.begin(), pathP.end()); // Reverse to get correct order
            }
            if (current == q && pathQ.empty()) {
                 // Convert stack to vector
                std::stack<TreeNode*> tempStack = stack;
                while (!tempStack.empty()) {
                    pathQ.push_back(tempStack.top());
                    tempStack.pop();
                }
                std::reverse(pathQ.begin(), pathQ.end());  // Reverse to get correct order
            }

            // Explore left or right if possible
            if (current->left && !visited[current->left]) {
                stack.push(current->left);
                visited[current->left] = true;
            } else if (current->right && !visited[current->right]) {
                stack.push(current->right);
                visited[current->right] = true;
            } else {
                stack.pop(); // Backtrack
            }
        }
        // Find LCA
        TreeNode* lca = nullptr;
        for (size_t i = 0; i < pathP.size() && i < pathQ.size(); ++i) {
            if (pathP[i] == pathQ[i]) {
                lca = pathP[i];
            } else {
                break;
            }
        }
        return lca;
    }
};

// Helper function to create a sample binary tree for testing
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    return root;
}

int main() {
    Solution solution;
    TreeNode* root = createSampleTree();
    TreeNode* p = root->left; // Node 5
    TreeNode* q = root->right->right; // Node 8

    // Test all 5 approaches
    std::cout << "Lowest Common Ancestor (LCA) of " << p->val << " and " << q->val << " is:" << std::endl;

    // Approach 1: Recursive Approach
    TreeNode* lca1 = solution.lowestCommonAncestorRecursive(root, p, q);
    std::cout << "Recursive Approach: " << (lca1 ? lca1->val : -1) << std::endl;

    // Approach 2: Iterative using Parent Pointers
    TreeNode* lca2 = solution.lowestCommonAncestorIterativeParentPointers(root, p, q);
    std::cout << "Iterative with Parent Pointers: " << (lca2 ? lca2->val : -1) << std::endl;

    // Approach 3: Using Node Levels (Iterative)
    TreeNode* lca3 = solution.lowestCommonAncestorWithLevels(root, p, q);
    std::cout << "Iterative with Levels: " << (lca3 ? lca3->val : -1) << std::endl;

    // Approach 4: Morris Traversal (No Extra Space)
    TreeNode* lca4 = solution.lowestCommonAncestorMorris(root, p, q);
    std::cout << "Morris Traversal: " << (lca4 ? lca4->val : -1) << std::endl;

    // Approach 5: Iterative using Stack
    TreeNode* lca5 = solution.lowestCommonAncestorIterativeStack(root, p, q);
    std::cout << "Iterative with Stack: " << (lca5 ? lca5->val : -1) << std::endl;

    return 0;
}

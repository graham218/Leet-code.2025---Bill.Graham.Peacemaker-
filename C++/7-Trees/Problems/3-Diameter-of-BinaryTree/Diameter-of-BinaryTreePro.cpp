#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>   // For smart pointers
#include <functional> // For std::function
#include <stack>
#include <unordered_map>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 1. Recursive Approach (Basic)
//   - Computes height recursively.  Diameter is max of left height + right height at each node.
//   - Simple to understand but can be inefficient due to redundant height calculations.
int diameterOfBinaryTree_Recursive(TreeNode* root) {
    if (!root) return 0;
    int leftHeight = (root->left) ? 1 + std::max(diameterOfBinaryTree_Recursive(root->left->left), diameterOfBinaryTree_Recursive(root->left->right)) : 0;
    int rightHeight = (root->right) ? 1 + std::max(diameterOfBinaryTree_Recursive(root->right->left), diameterOfBinaryTree_Recursive(root->right->right)) : 0;
    int currentDiameter = leftHeight + rightHeight;
    int leftDiameter = diameterOfBinaryTree_Recursive(root->left);
    int rightDiameter = diameterOfBinaryTree_Recursive(root->right);
    return std::max(currentDiameter, std::max(leftDiameter, rightDiameter));
}

// 2. Recursive Approach (Optimized)
//   - Calculates height and diameter in a single pass.
//   - Avoids redundant height calculations, improving efficiency.
int diameterOfBinaryTree_Optimized(TreeNode* root, int* diameter) {
    if (!root) return 0;
    int leftHeight = diameterOfBinaryTree_Optimized(root->left, diameter);
    int rightHeight = diameterOfBinaryTree_Optimized(root->right, diameter);
    *diameter = std::max(*diameter, leftHeight + rightHeight);
    return 1 + std::max(leftHeight, rightHeight);
}

int diameterOfBinaryTree_Optimized(TreeNode* root) {
    int diameter = 0;
    diameterOfBinaryTree_Optimized(root, &diameter);
    return diameter;
}

// 3. Iterative Approach (Using Stack)
//   - Uses a stack to traverse the tree in a post-order manner.
//   - Stores the height of each node in a hash map to avoid redundant calculations.
//   - More complex but avoids recursion.
int diameterOfBinaryTree_Iterative(TreeNode* root) {
    if (!root) return 0;

    std::stack<TreeNode*> nodeStack;
    std::unordered_map<TreeNode*, int> heightMap;
    int diameter = 0;
    TreeNode* current = root;
    TreeNode* prev = nullptr;

    while (current || !nodeStack.empty()) {
        while (current) {
            nodeStack.push(current);
            current = current->left;
        }
        current = nodeStack.top();
        if (current->right && current->right != prev) {
            current = current->right;
        } else {
            nodeStack.pop();
            int leftHeight = (current->left) ? heightMap[current->left] : 0;
            int rightHeight = (current->right) ? heightMap[current->right] : 0;
            heightMap[current] = 1 + std::max(leftHeight, rightHeight);
            diameter = std::max(diameter, leftHeight + rightHeight);
            prev = current;
            current = nullptr;
        }
    }
    return diameter;
}

// 4. Level Order Traversal (BFS)
//   - Uses Breadth-First Search (BFS) with a queue.
//   - Calculates the height of each node during traversal.
//   - Diameter is updated by considering the heights of children for each node.
int diameterOfBinaryTree_BFS(TreeNode* root) {
    if (!root) return 0;

    std::queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    std::unordered_map<TreeNode*, int> heightMap;
    heightMap[root] = 0; // Height of root is 0
    int diameter = 0;

    while (!nodeQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        int leftHeight = 0;
        int rightHeight = 0;

        if (current->left) {
            nodeQueue.push(current->left);
            leftHeight = heightMap[current->left] + 1;
        }
        if (current->right) {
            nodeQueue.push(current->right);
            rightHeight = heightMap[current->right] + 1;
        }
        heightMap[current] = std::max(leftHeight, rightHeight);
        diameter = std::max(diameter, leftHeight + rightHeight);
    }
    return diameter;
}

// 5. Using Unique Pointer and Lambda (Modern C++)
//    - Demonstrates modern C++ features: unique_ptr for memory management and lambda for concise code.
//    -  Employs a recursive approach with a lambda function to calculate height and diameter.
int diameterOfBinaryTree_Modern(TreeNode* root) {
    if (!root) return 0;

    int diameter = 0;
    std::function<int(TreeNode*)> calculateHeight = [&](TreeNode* node) {
        if (!node) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        diameter = std::max(diameter, leftHeight + rightHeight);
        return 1 + std::max(leftHeight, rightHeight);
    };

    calculateHeight(root);
    return diameter;
}

// Helper function to construct a binary tree from a vector (for testing)
TreeNode* constructTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < values.size() && values[i] != -1) { // -1 represents null
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != -1) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
}

// Helper function to deallocate the binary tree (Good practice to prevent memory leaks)
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Example usage of the different approaches
    std::vector<int> treeNodes = {1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1}; // Example tree: [1,2,3,4,5]
    TreeNode* root = constructTree(treeNodes);

    std::cout << "Diameter of Binary Tree:\n";
    std::cout << "1. Recursive (Basic): " << diameterOfBinaryTree_Recursive(root) << std::endl;
    std::cout << "2. Recursive (Optimized): " << diameterOfBinaryTree_Optimized(root) << std::endl;
    std::cout << "3. Iterative (Stack): " << diameterOfBinaryTree_Iterative(root) << std::endl;
    std::cout << "4. BFS: " << diameterOfBinaryTree_BFS(root) << std::endl;
    std::cout << "5. Modern C++: " << diameterOfBinaryTree_Modern(root) << std::endl;

    deleteTree(root); // Clean up the allocated memory.  Important!

    // Example with a different tree
    std::vector<int> treeNodes2 = {1, 2, -1, 3, -1, 4, -1, 5};
    TreeNode* root2 = constructTree(treeNodes2);
    std::cout << "\nDiameter of Binary Tree 2:\n";
    std::cout << "1. Recursive (Basic): " << diameterOfBinaryTree_Recursive(root2) << std::endl;
    std::cout << "2. Recursive (Optimized): " << diameterOfBinaryTree_Optimized(root2) << std::endl;
    std::cout << "3. Iterative (Stack): " << diameterOfBinaryTree_Iterative(root2) << std::endl;
    std::cout << "4. BFS: " << diameterOfBinaryTree_BFS(root2) << std::endl;
    std::cout << "5. Modern C++: " << diameterOfBinaryTree_Modern(root2) << std::endl;
    deleteTree(root2);

    return 0;
}

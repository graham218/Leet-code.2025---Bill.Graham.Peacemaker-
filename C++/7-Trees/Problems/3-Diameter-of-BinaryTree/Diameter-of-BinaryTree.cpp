#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <functional> // Include for std::function
#include <unordered_map> // Include for std::unordered_map

using namespace std;

// Definition of a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Function to calculate the diameter of a binary tree.

// Approach 1: Recursive (Naive)
// Time Complexity: O(n^2) in the worst case (skewed tree), O(n log n) for balanced tree
// Space Complexity: O(height) -  due to recursive call stack,  O(n) in worst case (skewed tree)
int diameterOfBinaryTree_Recursive(TreeNode* root) {
    if (!root) {
        return 0;
    }

    // Calculate the height of the left and right subtrees.
    int leftHeight = (root->left) ? 1 + max(diameterOfBinaryTree_Recursive(root->left->left), diameterOfBinaryTree_Recursive(root->left->right)) : 0;
    int rightHeight = (root->right) ? 1 + max(diameterOfBinaryTree_Recursive(root->right->left), diameterOfBinaryTree_Recursive(root->right->right)) : 0;

    // Diameter through the root.
    int diameterThroughRoot = leftHeight + rightHeight;

    // Recursively calculate the diameter of the left and right subtrees.
    int leftDiameter = diameterOfBinaryTree_Recursive(root->left);
    int rightDiameter = diameterOfBinaryTree_Recursive(root->right);

    // Return the maximum of the three diameters.
    return max({diameterThroughRoot, leftDiameter, rightDiameter});
}

// Approach 2: Recursive (Optimized)
// Time Complexity: O(n) - Each node is visited exactly once.
// Space Complexity: O(height) - due to recursive call stack, O(n) in worst case.
int diameterOfBinaryTree_Optimized(TreeNode* root, int* diameter) {
    if (!root) {
        return 0;
    }

    // Recursively calculate the height of the left and right subtrees.
    int leftHeight = diameterOfBinaryTree_Optimized(root->left, diameter);
    int rightHeight = diameterOfBinaryTree_Optimized(root->right, diameter);

    // Calculate the diameter through the current root.
    *diameter = max(*diameter, leftHeight + rightHeight);

    // Return the height of the current node.
    return 1 + max(leftHeight, rightHeight);
}

int diameterOfBinaryTree_Optimized(TreeNode* root) {
    int diameter = 0;
    diameterOfBinaryTree_Optimized(root, &diameter);
    return diameter;
}


// Approach 3: Iterative using Level Order Traversal (BFS) - Not very efficient for diameter, more complex.
// Time Complexity: O(n^2) in worst case, where calculating height of subtrees can take O(n) for each node.
// Space Complexity: O(w) - where w is the maximum width of the tree.  O(n) in worst case.
int diameterOfBinaryTree_BFS(TreeNode* root) {
    if (!root) return 0;

    int diameter = 0;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // Helper function to calculate height (can be optimized, but kept here for clarity within BFS)
        function<int(TreeNode*)> calculateHeight = [&](TreeNode* node) {
            if (!node) return 0;
            return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
        };

        int leftHeight = (node->left) ? calculateHeight(node->left) : 0;
        int rightHeight = (node->right) ? calculateHeight(node->right) : 0;
        diameter = max(diameter, leftHeight + rightHeight);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return diameter;
}

// Approach 4: Iterative using Stack (Pre-order Traversal) -  More complex, not ideal for diameter
// Time Complexity: O(n) - Each node is visited.  Height calculations within the loop make it less efficient for diameter.
// Space Complexity: O(h) - max height of the tree. O(n) in worst case.

int diameterOfBinaryTree_Iterative(TreeNode* root) {
    if (!root) return 0;

    int diameter = 0;
    stack<TreeNode*> s;
    s.push(root);

    // Helper function to calculate height
    function<int(TreeNode*)> calculateHeight = [&](TreeNode* node) {
        if (!node) return 0;
        return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
    };
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();

        int leftHeight = (node->left) ? calculateHeight(node->left) : 0;
        int rightHeight = (node->right) ? calculateHeight(node->right) : 0;
        diameter = max(diameter, leftHeight + rightHeight);

        if (node->right) s.push(node->right); // Push right child first
        if (node->left) s.push(node->left);    // Push left child
    }
    return diameter;
}

// Approach 5:  Single Pass Post-Order Traversal (Most Efficient Iterative)
// This approach calculates the height and diameter in a single pass, iteratively.
// It mimics the optimized recursive approach, but uses a stack to avoid recursion.
// Time Complexity: O(n) - Each node is visited exactly once.
// Space Complexity: O(h) - Maximum height of the tree.  O(n) in the worst case (skewed tree).

int diameterOfBinaryTree_IterativePostOrder(TreeNode* root) {
    if (!root) return 0;

    int diameter = 0;
    stack<pair<TreeNode*, int>> stack; // Store node and its state (0: visit children, 1: process node)
    unordered_map<TreeNode*, int> heightMap; // Store calculated heights of nodes
    stack.push({root, 0});

    while (!stack.empty()) {
        pair<TreeNode*, int> current = stack.top();
        TreeNode* node = current.first;
        int state = current.second;
        stack.pop();

        if (state == 0) { // Visiting children
            stack.push({node, 1}); // Mark node to be processed after children
            if (node->right) stack.push({node->right, 0}); // Push right child first for post-order
            if (node->left) stack.push({node->left, 0});   // Then push left child
        } else { // Processing node
            int leftHeight = (node->left) ? heightMap[node->left] : 0;
            int rightHeight = (node->right) ? heightMap[node->right] : 0;

            // Calculate diameter through this node
            diameter = max(diameter, leftHeight + rightHeight);

            // Calculate height of this node and store it.
            int nodeHeight = 1 + max(leftHeight, rightHeight);
            heightMap[node] = nodeHeight;
        }
    }
    return diameter;
}


// Helper function to create a binary tree (for testing)
TreeNode* createBinaryTree(const vector<int>& values, int index) {
    if (index >= values.size() || values[index] == -1) { // -1 represents null
        return nullptr;
    }
    TreeNode* node = new TreeNode(values[index]);
    node->left = createBinaryTree(values, 2 * index + 1);
    node->right = createBinaryTree(values, 2 * index + 2);
    return node;
}

// Helper function to print the tree (for visualization) -  Using Level Order
void printBinaryTree(TreeNode* root) {
    if (!root) {
        cout << "Tree is empty" << endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "null ";
            }
        }
        cout << endl;
    }
}

int main() {
    // Example usage:
    // Create a binary tree: [1,2,3,4,5,null,null,null,null,null,null]  (see printout below)
    vector<int> treeNodes = {1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1}; // -1 represents null
    TreeNode* root = createBinaryTree(treeNodes, 0);

    cout << "Binary Tree (Level Order):" << endl;
    printBinaryTree(root);

    cout << "\nDiameter of Binary Tree:" << endl;
    cout << "Approach 1 (Recursive): " << diameterOfBinaryTree_Recursive(root) << endl;
    cout << "Approach 2 (Optimized Recursive): " << diameterOfBinaryTree_Optimized(root) << endl;
    cout << "Approach 3 (BFS): " << diameterOfBinaryTree_BFS(root) << endl;
    cout << "Approach 4 (Iterative): " << diameterOfBinaryTree_Iterative(root) << endl;
    cout << "Approach 5 (Iterative Post-Order): " << diameterOfBinaryTree_IterativePostOrder(root) << endl;


    // Example 2:
    vector<int> treeNodes2 = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root2 = createBinaryTree(treeNodes2, 0);
    cout << "\nBinary Tree 2 (Level Order):" << endl;
    printBinaryTree(root2);
    cout << "\nDiameter of Binary Tree 2:" << endl;
    cout << "Approach 1 (Recursive): " << diameterOfBinaryTree_Recursive(root2) << endl;
    cout << "Approach 2 (Optimized Recursive): " << diameterOfBinaryTree_Optimized(root2) << endl;
    cout << "Approach 3 (BFS): " << diameterOfBinaryTree_BFS(root2) << endl;
    cout << "Approach 4 (Iterative): " << diameterOfBinaryTree_Iterative(root2) << endl;
    cout << "Approach 5 (Iterative Post-Order): " << diameterOfBinaryTree_IterativePostOrder(root2) << endl;

    // Example 3: Skewed Tree (Worst Case for some approaches)
    vector<int> treeNodes3 = {1, 2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, 5}; // Skewed to the left
    TreeNode* root3 = createBinaryTree(treeNodes3, 0);
    cout << "\nBinary Tree 3 (Skewed - Level Order):" << endl;
    printBinaryTree(root3);
    cout << "\nDiameter of Binary Tree 3 (Skewed):" << endl;
    cout << "Approach 1 (Recursive): " << diameterOfBinaryTree_Recursive(root3) << endl;
    cout << "Approach 2 (Optimized Recursive): " << diameterOfBinaryTree_Optimized(root3) << endl;
    cout << "Approach 3 (BFS): " << diameterOfBinaryTree_BFS(root3) << endl;
    cout << "Approach 4 (Iterative): " << diameterOfBinaryTree_Iterative(root3) << endl;
    cout << "Approach 5 (Iterative Post-Order): " << diameterOfBinaryTree_IterativePostOrder(root3) << endl;


    return 0;
}

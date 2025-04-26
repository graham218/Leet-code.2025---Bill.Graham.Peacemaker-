#include <iostream>
#include <vector>
#include <stack>
#include <memory> // For smart pointers

// Basic structure for a tree node.  Using a unique_ptr for modern memory management in C++.
struct TreeNode {
    int data;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    // Constructor for the TreeNode.  Using initializer list.
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to create a sample tree for demonstration purposes.  Returns a unique_ptr to the root.
std::unique_ptr<TreeNode> createSampleTree() {
    std::unique_ptr<TreeNode> root = std::make_unique<TreeNode>(1); // Use make_unique
    root->left = std::make_unique<TreeNode>(2);
    root->right = std::make_unique<TreeNode>(3);
    root->left->left = std::make_unique<TreeNode>(4);
    root->left->right = std::make_unique<TreeNode>(5);
    root->right->left = std::make_unique<TreeNode>(6);
    root->right->right = std::make_unique<TreeNode>(7);
    return root;
}

// 1. Recursive DFS Traversal:  Core DFS algorithm.
//   - Project Application:  Traversing file system directories.  The tree structure represents directories and subdirectories.
void recursiveDFS(const TreeNode* node) {
    if (node == nullptr) {
        return; // Base case: If the node is null, return.
    }
    std::cout << node->data << " "; // Process the current node (e.g., print data, visit file).
    recursiveDFS(node->left.get());  // Recursively traverse the left subtree.
    recursiveDFS(node->right.get()); // Recursively traverse the right subtree.
}

// 2. Iterative DFS with Stack: Non-recursive DFS using a stack.
//   - Project Application:  Web crawler.  The tree represents the link structure of websites.
void iterativeDFS(const TreeNode* root) {
    if (root == nullptr) return;

    std::stack<const TreeNode*> nodeStack;
    nodeStack.push(root); // Push the root node onto the stack.

    while (!nodeStack.empty()) {
        const TreeNode* currentNode = nodeStack.top();
        nodeStack.pop();       // Pop the top node.
        std::cout << currentNode->data << " "; // Process the current node.

        // Push the right child first, so the left child is processed next.
        if (currentNode->right) {
            nodeStack.push(currentNode->right.get());
        }
        if (currentNode->left) {
            nodeStack.push(currentNode->left.get());
        }
    }
}

// 3. DFS with Path Tracking:  Store the path from the root to each node.
//   - Project Application:  Finding a route in a network.  The tree represents network topology.
void dfsWithPath(const TreeNode* node, std::vector<int>& path) {
    if (node == nullptr) {
        return;
    }

    path.push_back(node->data); // Add the current node's data to the path.
    if (!node->left && !node->right)
    {
        std::cout << "Path: ";
        for (int p : path)
        {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }

    dfsWithPath(node->left.get(), path);  // Explore left subtree.
    dfsWithPath(node->right.get(), path); // Explore right subtree.
    path.pop_back();                   // Remove the current node's data before returning.
}

// 4. DFS for Searching a Specific Value:  Stop DFS when a target value is found.
//   - Project Application:  Searching for a specific product in a product category tree (e-commerce).
bool dfsSearch(const TreeNode* node, int target, std::vector<int>& path) {
    if (node == nullptr) {
        return false; // Base case: target not found.
    }

    path.push_back(node->data);
    if (node->data == target) {
        std::cout << "Found " << target << " Path: ";
        for(int p : path)
        {
            std::cout << p << " ";
        }
        std::cout << std::endl;
        return true; // Target found!
    }

    // Recursively search in left and right subtrees.  If found in either, return true.
    if (dfsSearch(node->left.get(), target, path) || dfsSearch(node->right.get(), target, path)) {
        return true;
    }

    path.pop_back(); // Remove node from path if target not found in its subtree.
    return false; // Target not found in this subtree.
}

// 5. DFS for Counting Nodes with a Condition:
//    - Project Application:  Analyzing organizational hierarchies.  The tree represents employees and their managers.
int countNodes(const TreeNode* node, int threshold) {
    if (node == nullptr) {
        return 0;
    }

    int count = 0;
    if (node->data > threshold) { // Condition: node's data is greater than threshold.
        count = 1;
    }

    count += countNodes(node->left.get(), threshold);  // Count in left subtree.
    count += countNodes(node->right.get(), threshold); // Count in right subtree.
    return count;
}

int main() {
    // Create a sample tree.
    std::unique_ptr<TreeNode> root = createSampleTree();

    std::cout << "1. Recursive DFS Traversal: ";
    recursiveDFS(root.get());
    std::cout << std::endl;

    std::cout << "2. Iterative DFS with Stack: ";
    iterativeDFS(root.get());
    std::cout << std::endl;

    std::cout << "3. DFS with Path Tracking:" << std::endl;
    std::vector<int> path;
    dfsWithPath(root.get(), path);
    std::cout << std::endl;

    std::cout << "4. DFS for Searching Value 6: ";
    std::vector<int> searchPath;
    dfsSearch(root.get(), 6, searchPath);
    std::cout << std::endl;

    std::cout << "5. Count nodes greater than 3: " << countNodes(root.get(), 3) << std::endl;

    return 0; // Exit successfully.
}

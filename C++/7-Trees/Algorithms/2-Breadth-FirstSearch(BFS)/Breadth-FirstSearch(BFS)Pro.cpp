#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits> // Required for numeric_limits

// Basic structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to build a tree from a vector of values
// nullptr values in the vector represent missing nodes
TreeNode* buildTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        // Left child
        if (values[i] != std::numeric_limits<int>::max()) { // Use max int to represent null
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

// Function to print the tree in level order (BFS) - for verifying the tree structure
void printLevelOrder(TreeNode* root) {
    if (!root) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    std::cout << "Level Order Traversal: ";
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        std::cout << current->val << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << std::endl;
}

// 1. Basic Breadth-First Search (BFS)
//   - Concept: Simplest form of BFS, visiting nodes level by level.
//   - Real-world application: Finding the shortest path in an unweighted graph,
//     network routing (finding the closest servers), web crawler to explore pages.
void basicBFS(TreeNode* root) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);

    std::cout << "Basic BFS: ";
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        std::cout << current->val << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << std::endl;
}

// 2. BFS with Level Separation
//   - Concept:  Processes the tree level by level, keeping track of node counts for each level.
//   - Real-world application:  Calculating the height of a tree,
//      processing nodes in a specific order for UI rendering (e.g., layers),
//      analyzing tree structure (number of nodes per level).
void bfsWithLevelSeparation(TreeNode* root) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);
    int level = 0;

    std::cout << "BFS with Level Separation:\n";
    while (!q.empty()) {
        int levelSize = q.size();
        std::cout << "Level " << level++ << ": ";
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = q.front();
            q.pop();
            std::cout << current->val << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }
}

// 3. BFS for Finding a Specific Node
//    - Concept:  Modifies BFS to search for a target value within the tree.
//    - Real-world application:  Searching for a specific file or directory in a file system,
//       locating a particular user in a hierarchical organization structure,
//       finding a specific product in a category tree.
bool bfsFindNode(TreeNode* root, int target) {
    if (!root) return false;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->val == target) {
            std::cout << "Found node with value " << target << " using BFS.\n";
            return true;
        }
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << "Node with value " << target << " not found using BFS.\n";
    return false;
}

// 4. BFS to find the Shortest Path (in an unweighted tree, path length is # of edges)
//    - Concept: Uses BFS to find the shortest path from the root to a target node.
//    - Real-world application: Network routing (finding the route with the fewest hops),
//      game AI (finding the shortest path to an objective),
//      social network analysis (finding the shortest connection between two people).
int bfsShortestPath(TreeNode* root, int target) {
    if (!root) return -1;

    std::queue<std::pair<TreeNode*, int>> q; // Store node and its distance from root
    q.push({root, 0});
    std::vector<int> visited;

    while (!q.empty()) {
        TreeNode* current = q.front().first;
        int distance = q.front().second;
        q.pop();

        // Check if the node has been visited
        bool isVisited = false;
        for (int v : visited) {
            if (v == current->val) {
                isVisited = true;
                break;
            }
        }
        if (isVisited) continue;
        visited.push_back(current->val);

        if (current->val == target) {
            std::cout << "Shortest path to node " << target << " is " << distance << ".\n";
            return distance;
        }
        if (current->left) q.push({current->left, distance + 1});
        if (current->right) q.push({current->right, distance + 1});
    }
    std::cout << "Node " << target << " not found.\n";
    return -1;
}

// 5.  Iterative Level Order Traversal with Zigzag Pattern
//     - Concept: Performs a level-order traversal but alternates the direction
//       of visiting nodes between left-to-right and right-to-left.
//     - Real-world application:  Displaying search results in an alternating pattern for better UI readability,
//        processing data in a specific order for optimization,
//        text justification algorithms.
void zigzagLevelOrder(TreeNode* root) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true; // Direction flag

    std::cout << "Zigzag Level Order Traversal:\n";
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel(levelSize); // Store nodes at current level

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = q.front();
            q.pop();
            // Store the node's value in the correct order based on direction
            if (leftToRight) {
                currentLevel[i] = current->val;
            } else {
                currentLevel[levelSize - 1 - i] = current->val;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        // Print the current level
        for (int val : currentLevel) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        leftToRight = !leftToRight; // Flip the direction
    }
}

int main() {
    // Example tree construction:
    //       1
    //     /   \
    //    2     3
    //   / \   / \
    //  4   5 6   7
    //
    //  Represented as vector, using max int for null: [1, 2, 3, 4, 5, 6, 7]
    std::vector<int> treeValues = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root = buildTree(treeValues);
    printLevelOrder(root); // Verify tree structure.

    // Test the BFS functions
    basicBFS(root);
    bfsWithLevelSeparation(root);
    bfsFindNode(root, 5);
    bfsFindNode(root, 8); // Test case where node is not found.
    bfsShortestPath(root, 7);
    bfsShortestPath(root, 8); // Test case where node is not found.
    zigzagLevelOrder(root);

    // Example of a different tree, including nullptr/null nodes
    //       1
    //     /   \
    //    2     3
    //   / \     \
    //  4   5     7
    std::vector<int> treeValues2 = {1, 2, 3, 4, 5, std::numeric_limits<int>::max(), 7};
    TreeNode* root2 = buildTree(treeValues2);
    printLevelOrder(root2);

    basicBFS(root2);
    bfsWithLevelSeparation(root2);
    bfsFindNode(root2, 7);
    bfsFindNode(root2, 6);
    bfsShortestPath(root2, 7);
    bfsShortestPath(root2, 6);
    zigzagLevelOrder(root2);

    // Remember to free the allocated memory for the tree nodes if needed
    // (not shown in this example for brevity, but important in real applications).
    return 0;
}

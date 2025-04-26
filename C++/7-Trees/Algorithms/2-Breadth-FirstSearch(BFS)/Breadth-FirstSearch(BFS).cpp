#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <memory> // For smart pointers

// Basic structure for a tree node
struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Function to create a sample tree for demonstration
std::shared_ptr<TreeNode> createSampleTree() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);
    root->right->left = std::make_shared<TreeNode>(6);
    root->right->right = std::make_shared<TreeNode>(7);
    return root;
}

// 1. Iterative BFS using a queue (Standard Approach)
//   - Uses a queue to store nodes at each level.
//   - Processes nodes level by level.
void bfsIterativeQueue(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(root);

    std::cout << "BFS Iterative (Queue): ";
    while (!q.empty()) {
        std::shared_ptr<TreeNode> current = q.front();
        q.pop();
        std::cout << current->val << " ";

        if (current->left)  q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << std::endl;
}

// 2. Iterative BFS with Level Separation
//   - Uses two nested loops to process nodes level by level, clearly separating levels in the output.
void bfsIterativeLevelSeparation(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(root);

    std::cout << "BFS Iterative (Level Separation):" << std::endl;
    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            std::shared_ptr<TreeNode> current = q.front();
            q.pop();
            std::cout << current->val << " ";

            if (current->left)  q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl; // Move to the next line after processing each level
    }
}

// 3. Recursive BFS using a queue (Helper Function)
//   - Uses a queue and recursion.  The recursion manages the levels,
//     and the queue manages the nodes within each level.
void bfsRecursiveHelper(std::queue<std::shared_ptr<TreeNode>>& q) {
    if (q.empty()) return;

    std::shared_ptr<TreeNode> current = q.front();
    q.pop();
    std::cout << current->val << " ";

    if (current->left)  q.push(current->left);
    if (current->right) q.push(current->right);

    bfsRecursiveHelper(q); // Recursive call to process the next node in the queue
}

void bfsRecursiveQueue(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::queue<std::shared_ptr<TreeNode>> q;
    q.push(root);
    std::cout << "BFS Recursive (Queue): ";
    bfsRecursiveHelper(q);
    std::cout << std::endl;
}

// 4. BFS using a list as a queue
//    - Uses a doubly linked list as the queue.  Demonstrates using a different
//      container.  push_back and pop_front give queue behavior.
void bfsListQueue(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::list<std::shared_ptr<TreeNode>> q;
    q.push_back(root); // Use push_back for queue's push

    std::cout << "BFS with List (Queue): ";
    while (!q.empty()) {
        std::shared_ptr<TreeNode> current = q.front();
        q.pop_front(); // Use pop_front for queue's pop
        std::cout << current->val << " ";

        if (current->left)  q.push_back(current->left);
        if (current->right) q.push_back(current->right);
    }
    std::cout << std::endl;
}

// 5.  BFS with level tracking using a queue of pairs
void bfsLevelTracking(std::shared_ptr<TreeNode> root) {
    if (!root) return;

    std::queue<std::pair<std::shared_ptr<TreeNode>, int>> q; // Store node and its level
    q.push({root, 0}); // Start at level 0

    std::cout << "BFS with Level Tracking:\n";
    int previousLevel = -1; // Keep track of the previous level
    while (!q.empty()) {
        std::pair<std::shared_ptr<TreeNode>, int> currentPair = q.front();
        q.pop();
        std::shared_ptr<TreeNode> current = currentPair.first;
        int level = currentPair.second;

        if (level != previousLevel) {
            std::cout << "Level " << level << ": "; // Print level number
            previousLevel = level;
        }
        std::cout << current->val << " ";

        if (current->left)  q.push({current->left, level + 1});
        if (current->right) q.push({current->right, level + 1});
    }
    std::cout << std::endl;
}

int main() {
    std::shared_ptr<TreeNode> root = createSampleTree();

    bfsIterativeQueue(root);
    bfsIterativeLevelSeparation(root);
    bfsRecursiveQueue(root);
    bfsListQueue(root);
    bfsLevelTracking(root);

    return 0;
}


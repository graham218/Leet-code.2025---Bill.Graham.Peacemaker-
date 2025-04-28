#include <iostream>
#include <vector>
#include <stack>
#include <memory> // For smart pointers

// Definition of a binary tree node.  Using a smart pointer (unique_ptr)
// to automatically handle memory management.  This is crucial for larger
// projects to prevent memory leaks.
struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    TreeNode(int x) : val(x) {}
};

// Function to create a sample binary tree.  Returns a unique_ptr to the root.
std::unique_ptr<TreeNode> createSampleTree() {
    std::unique_ptr<TreeNode> root = std::make_unique<TreeNode>(1);
    root->left = std::make_unique<TreeNode>(2);
    root->right = std::make_unique<TreeNode>(3);
    root->left->left = std::make_unique<TreeNode>(4);
    root->left->right = std::make_unique<TreeNode>(5);
    root->right->left = std::make_unique<TreeNode>(6);
    root->right->right = std::make_unique<TreeNode>(7);
    return root;
}

// 1. Morris Inorder Traversal - Iterative, No Stack, No Recursion
//    - Project Application:  Efficient data serialization and deserialization
//      where minimizing memory footprint is critical (e.g., embedded systems,
//      network protocols).  Inorder traversal ensures data is processed
//      in a sorted order (for BSTs).
void morrisInorder(TreeNode* root, std::vector<int>& result) {
    TreeNode* current = root;
    while (current) {
        if (!current->left) {
            result.push_back(current->val);
            current = current->right.release(); // Manually release, current will be nullptr.
        } else {
            TreeNode* predecessor = current->left.get(); // Get raw pointer for manipulation.
            while (predecessor->right && predecessor->right.get() != current) {
                predecessor = predecessor->right.get();
            }
            if (!predecessor->right) {
                predecessor->right = std::unique_ptr<TreeNode>(current); // Store current
                TreeNode* temp = current;
                current = current->left.release();  // Manually release and move
                temp->left = nullptr; //prevent double free
            } else {
                predecessor->right = nullptr; // Restore the tree structure
                result.push_back(current->val);
                current = current->right.release(); // Manually release
            }
        }
    }
}

// 2. Morris Preorder Traversal
//   - Project Application:  Creating a copy of a tree or evaluating prefix
//     expressions.  Preorder traversal visits the node before its children,
//     useful for duplicating tree structures.
void morrisPreorder(TreeNode* root, std::vector<int>& result) {
    TreeNode* current = root;
    while (current) {
        if (!current->left) {
            result.push_back(current->val);
            current = current->right.release();
        } else {
            TreeNode* predecessor = current->left.get();
            while (predecessor->right && predecessor->right.get() != current) {
                predecessor = predecessor->right.get();
            }
            if (!predecessor->right) {
                predecessor->right = std::unique_ptr<TreeNode>(current);
                result.push_back(current->val); // Add before going left
                TreeNode* temp = current;
                current = current->left.release();
                temp->left = nullptr;
            } else {
                predecessor->right = nullptr;
                current = current->right.release();
            }
        }
    }
}

// 3. Morris Postorder Traversal (Tricky - requires reverse)
//    - Project Application:  Garbage collection algorithms (calculating object
//      lifetimes), compiler design (evaluating postfix expressions).
//      Postorder traversal is essential when a node's children must be
//      processed before the node itself.
void reverse(TreeNode* from, TreeNode* to) {
    if (from == to) return;
    TreeNode* prev = nullptr;
    TreeNode* curr = from;
    TreeNode* next = from->right.get(); // Use get()

    while (curr != to) {
        curr->right = std::unique_ptr<TreeNode>(prev); //transfer ownership
        prev = curr;
        curr = next;
        if(next)
            next = next->right.get();
    }
    curr->right = std::unique_ptr<TreeNode>(prev);
}

void morrisPostorder(TreeNode* root, std::vector<int>& result) {
    TreeNode* dummy = new TreeNode(0); // Use raw pointer for dummy, avoid smart pointer here.
    dummy->left = std::unique_ptr<TreeNode>(root); // Transfer ownership.  root is now managed by dummy
    TreeNode* current = dummy->left.get();
    TreeNode* prev = dummy;
    while (current) {
        if (!current->left) {
            prev = current;
            current = current->right.release();
        } else {
            TreeNode* predecessor = current->left.get();
            while (predecessor->right && predecessor->right.get() != current) {
                predecessor = predecessor->right.get();
            }
            if (!predecessor->right) {
                predecessor->right = std::unique_ptr<TreeNode>(current);
                prev = current;
                TreeNode* temp = current;
                current = current->left.release();
                temp->left = nullptr;
            } else {
                reverse(current->left.get(), current);
                TreeNode* temp = predecessor;
                while (temp != current->left.get()) {
                    result.push_back(temp->val);
                    temp = temp->right.get();
                }
                result.push_back(temp->val);
                reverse(current->left.get(), current);
                predecessor->right = nullptr;
                prev = current;
                current = current->right.release();
            }
        }
    }
    delete dummy; // Clean up dummy node.  This is VERY important.
}

// 4. Morris Inorder with Threading for Iterators
//   - Project Application: Implementing custom iterators for tree-like data
//     structures in a database or search engine.  Threading allows for
//     efficient traversal without the overhead of stack-based iteration.
class MorrisInorderIterator {
public:
    MorrisInorderIterator(TreeNode* root) : current_(root) {}

    int next() {
        while (current_) {
            if (!current_->left) {
                int val = current_->val;
                current_ = current_->right.release(); // Manually release
                return val;
            } else {
                TreeNode* predecessor = current_->left.get();
                while (predecessor->right && predecessor->right.get() != current_) {
                    predecessor = predecessor->right.get();
                }
                if (!predecessor->right) {
                    predecessor->right = std::unique_ptr<TreeNode>(current_);
                    TreeNode* temp = current_;
                    current_ = current_->left.release();
                    temp->left = nullptr;
                } else {
                    predecessor->right = nullptr;
                    int val = current_->val;
                    current_ = current_->right.release();
                    return val;
                }
            }
        }
        return -1; // End of traversal
    }

    bool hasNext() {
        return current_ != nullptr;
    }

private:
    TreeNode* current_;
};

// 5.  Morris Traversal for Finding a Target Value (Inorder Variation)
//    - Project Application:  Searching for a specific record in a sorted
//      data structure (represented as a BST) without using extra memory.
//      This is useful in memory-constrained environments like embedded
//      databases.
bool morrisSearch(TreeNode* root, int target) {
    TreeNode* current = root;
    while (current) {
        if (!current->left) {
            if (current->val == target) {
                return true;
            }
            current = current->right.release();
        } else {
            TreeNode* predecessor = current->left.get();
            while (predecessor->right && predecessor->right.get() != current) {
                predecessor = predecessor->right.get();
            }
            if (!predecessor->right) {
                predecessor->right = std::unique_ptr<TreeNode>(current);
                TreeNode* temp = current;
                current = current->left.release();
                temp->left = nullptr;
            } else {
                predecessor->right = nullptr;
                if (current->val == target) {
                    return true;
                }
                current = current->right.release();
            }
        }
    }
    return false;
}

int main() {
    // Create a sample binary tree using smart pointers
    std::unique_ptr<TreeNode> root = createSampleTree();

    std::cout << "Morris Inorder Traversal: ";
    std::vector<int> inorderResult;
    morrisInorder(root.get(), inorderResult); // Pass raw pointer
    for (int val : inorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Morris Preorder Traversal: ";
    std::vector<int> preorderResult;
    morrisPreorder(root.get(), preorderResult);
    for (int val : preorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Morris Postorder Traversal: ";
    std::vector<int> postorderResult;
    morrisPostorder(root.get(), postorderResult);
    for (int val : postorderResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Morris Inorder Iterator: ";
    MorrisInorderIterator iterator(root.get()); // Pass raw pointer
    while (iterator.hasNext()) {
        std::cout << iterator.next() << " ";
    }
    std::cout << std::endl;

    int target = 5;
    std::cout << "Morris Search for " << target << ": " << (morrisSearch(root.get(), target) ? "Found" : "Not Found") << std::endl;

    return 0; // No need to manually delete root, unique_ptr handles it.
}

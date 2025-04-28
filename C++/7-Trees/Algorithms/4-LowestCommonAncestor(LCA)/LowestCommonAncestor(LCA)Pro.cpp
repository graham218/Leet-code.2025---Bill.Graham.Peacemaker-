#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <set>
#include <functional> // Include for std::function

// Definition of a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /**
     * Approach 1: Recursive Approach
     *
     * This is the most intuitive approach.  We recursively traverse the tree.
     * If we find either p or q, we return that node.  The LCA is the first node
     * where the left and right subtrees return non-NULL values.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.  In the worst case, we might have to visit all nodes.
     * Space Complexity: O(H), where H is the height of the tree.  This is due to the recursive call stack.  In the worst case (skewed tree), H = N, so it becomes O(N).  In the best case (balanced tree), H = logN, so it's O(logN).
     */
    TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }

        TreeNode* left = lowestCommonAncestorRecursive(root->left, p, q);
        TreeNode* right = lowestCommonAncestorRecursive(root->right, p, q);

        if (left != NULL && right != NULL) {
            return root; // Found the LCA
        } else if (left != NULL) {
            return left;  // p and q are in the left subtree
        } else {
            return right; // p and q are in the right subtree
        }
    }



    /**
     * Approach 2: Iterative with Parent Pointers (Using a Map)
     *
     * 1.  Use a queue (BFS) or stack (DFS) to traverse the tree and store each node's parent in a map.
     * 2.  Trace the path from p to the root using the parent map and store the nodes in a set.
     * 3.  Trace the path from q to the root.  The first node encountered that is in the set
     * of p's ancestors is the LCA.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.  We visit each node at most twice.
     * Space Complexity: O(N), for the parent map and the set of ancestors.
     */
    TreeNode* lowestCommonAncestorIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return NULL;

        std::map<TreeNode*, TreeNode*> parentMap; // Map to store child -> parent
        std::queue<TreeNode*> q_bfs;  // Or use a stack for DFS
        q_bfs.push(root);
        parentMap[root] = NULL; // Root has no parent

        // 1. Build the parent map using BFS
        while (!q_bfs.empty()) {
            TreeNode* current = q_bfs.front();
            q_bfs.pop();
            if (current->left) {
                parentMap[current->left] = current;
                q_bfs.push(current->left);
            }
            if (current->right) {
                parentMap[current->right] = current;
                q_bfs.push(current->right);
            }
        }

        // 2. Find ancestors of p
        std::set<TreeNode*> pAncestors;
        while (p) {
            pAncestors.insert(p);
            p = parentMap[p];
        }

        // 3. Find LCA by traversing q's ancestors
        while (q) {
            if (pAncestors.find(q) != pAncestors.end()) {
                return q; // Found the LCA
            }
            q = parentMap[q];
        }

        return NULL; // Should not reach here if p and q are in the tree
    }

    /**
     * Approach 3: Iterative without Parent Pointers (Using Stacks)
     *
     * This approach avoids using extra space for parent pointers.  It uses stacks
     * to store the paths from the root to p and q.
     *
     * 1.  Use two stacks to perform non-recursive DFS to find the paths from the root to p and q.
     * 2.  Once the paths are found, compare the paths from the root.
     * 3.  The last common node in the two paths is the LCA.
     *
     * Time Complexity: O(N), where N is the number of nodes in the tree.
     * Space Complexity: O(H), where H is the height of the tree, due to the stacks.  In the worst case, H = N.
     */
    TreeNode* lowestCommonAncestorIterativeNoParent(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return NULL;

        std::stack<TreeNode*> pathP;
        std::stack<TreeNode*> pathQ;

        // Function to find path from root to a given node using DFS
        std::function<bool(TreeNode*, TreeNode*, std::stack<TreeNode*>&)> findPath =
            [&](TreeNode* node, TreeNode* target, std::stack<TreeNode*>& path) {
                if (!node) return false;

                path.push(node);
                if (node == target) return true;

                if (findPath(node->left, target, path) || findPath(node->right, target, path)) {
                    return true;
                }
                path.pop(); // Backtrack
                return false;
            };

        // Find paths to p and q
        if (!findPath(root, p, pathP) || !findPath(root, q, pathQ)) {
            return NULL; // p or q not found
        }

        // Find the LCA by comparing the paths
        TreeNode* lca = root;
        while (!pathP.empty() && !pathQ.empty() && pathP.top() == pathQ.top()) {
            lca = pathP.top();
            pathP.pop();
            pathQ.pop();
        }
        return lca;
    }


    /**
     * Approach 4:  Binary Lifting (for LCA in a Binary Tree - Preprocessing)
     *
     * This approach is more complex but can be very efficient for repeated LCA queries
     * on the same tree.  It involves preprocessing the tree to build a table that allows
     * us to find the ancestor of any node at any level in O(1) time.  For a binary tree,
     * this preprocessing is less beneficial than for general trees, but the concept is important.
     *
     * 1.  Calculate the depth of each node in the tree using DFS or BFS.
     * 2.  Find the LCA:
     * a.  Make sure p and q are at the same depth.  If not, move the deeper node up.
     * b.  Iteratively move both p and q up their ancestors until they meet.
     *
     * Time Complexity:
     * - Preprocessing: O(N) to calculate depths.
     * - Query: O(H) in the worst case, where H is the height of the tree.
     * Space Complexity: O(N) for the depth array
     *
     * Note: Binary lifting is usually used for general trees, where each node can have multiple children
     * and the height can be large.  For binary trees, the iterative methods above are often simpler
     * and more efficient due to the logarithmic height.  This implementation is included for completeness
     * and to show the general idea of binary lifting.
     */
    TreeNode* lowestCommonAncestorBinaryLifting(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return NULL;

        std::map<TreeNode*, int> depth;
        std::map<TreeNode*, TreeNode*> parent; // Store the parent of each node.

        // 1. Calculate depths using DFS
        std::function<void(TreeNode*, int, TreeNode*)> calculateDepth =
            [&](TreeNode* node, int d, TreeNode* par) {
                if (!node) return;
                depth[node] = d;
                parent[node] = par;
                calculateDepth(node->left, d + 1, node);
                calculateDepth(node->right, d + 1, node);
            };
        calculateDepth(root, 0, NULL); // Root has depth 0 and no parent

        // 2.  Find LCA
        int depthP = depth[p];
        int depthQ = depth[q];

        // a.  Make p and q at the same depth
        while (depthP > depthQ) {
            p = parent[p];
            depthP--;
        }
        while (depthQ > depthP) {
            q = parent[q];
            depthQ--;
        }

        // b.  Move p and q up until they meet
        while (p != q) {
            p = parent[p];
            q = parent[q];
        }
        return p; // or q, since they are the same at this point
    }

    /**
     * Approach 5: Tarjan's Offline Algorithm (for LCA in a Binary Tree)
     *
     * Tarjan's algorithm is an *offline* algorithm, meaning it requires all the queries (pairs of nodes for which we want to find the LCA) to be known beforehand.  It's very efficient.
     *
     * 1.  Perform a depth-first search (DFS) of the tree.
     * 2.  Maintain a Disjoint Set Union (DSU) data structure.  Each node starts in its own set.
     * 3.  When the DFS visits a node u:
     * a.  Make u the ancestor of itself in the DSU.
     * b.  For each child v of u, recursively visit v.  After visiting v, union the set of v with the set of u.
     * c.  For each query (x, y) where u is one of the nodes:
     * - If the other node (x or y) has already been visited, the LCA is the ancestor of the set that the other node belongs to.
     *
     * This approach is generally used for general trees and multiple queries, but can be adapted for binary trees.
     *
     * Time Complexity: O(N + Q * α(N)), where N is the number of nodes, Q is the number of queries, and α(N) is the inverse Ackermann function (very slow-growing, practically constant).
     * Space Complexity: O(N) for the DSU data structure and visited array.
     *
     * Note:  This implementation assumes the queries are provided in the `queries` vector.  Each query is a pair of TreeNode pointers.  This is more complex to set up, but very efficient for multiple LCA queries.
     */
    TreeNode* lowestCommonAncestorTarjan(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return NULL;

        std::map<TreeNode*, TreeNode*> ancestor; // DSU: ancestor[x] stores the ancestor of x
        std::map<TreeNode*, int> rank;        // DSU: rank[x] is the rank of x (for union by rank)
        std::map<TreeNode*, bool> visited;     // Keep track of visited nodes
        std::map<std::pair<TreeNode*, TreeNode*>, TreeNode*> lcaResults; //Store calculated LCAs
        std::vector<std::pair<TreeNode*, TreeNode*>> queries; // Store queries

        // Initialize DSU
        std::function<void(TreeNode*)> makeSet = [&](TreeNode* node) {
            if (!node) return;
            ancestor[node] = node;
            rank[node] = 0;
            visited[node] = false;
            makeSet(node->left);
            makeSet(node->right);
        };
        makeSet(root);

        // Function to find the representative of a set (path compression)
        std::function<TreeNode*(TreeNode*)> findSet =
            [&](TreeNode* node) -> TreeNode* {
                if (ancestor[node] != node) {
                    ancestor[node] = findSet(ancestor[node]); // Path compression
                }
                return ancestor[node];
            };

        // Function to union two sets (union by rank)
        std::function<void(TreeNode*, TreeNode*)> unionSets =
            [&](TreeNode* x, TreeNode* y) {
                TreeNode* xRoot = findSet(x);
                TreeNode* yRoot = findSet(y);

                if (xRoot != yRoot) {
                    if (rank[xRoot] < rank[yRoot]) {
                        ancestor[xRoot] = yRoot;
                    } else if (rank[xRoot] > rank[yRoot]) {
                        ancestor[yRoot] = xRoot;
                    } else {
                        ancestor[yRoot] = xRoot;
                        rank[xRoot]++;
                    }
                }
            };

        // Add the query.  In a real application, you'd have a list of queries.
        queries.push_back({p, q});

        TreeNode* result = NULL; // Default

        // Tarjan's DFS
        std::function<void(TreeNode*)> tarjanDFS = [&](TreeNode* node) {
            if (!node) return;

            visited[node] = true;
            ancestor[node] = node; // MakeSet

            tarjanDFS(node->left);
            if (node->left) {
                unionSets(node, node->left);
                ancestor[findSet(node)] = node;
            }

            tarjanDFS(node->right);
            if (node->right) {
                unionSets(node, node->right);
                ancestor[findSet(node)] = node;
            }

            // Process queries involving the current node
            for (const auto& query : queries) {
                TreeNode* other = (query.first == node) ? query.second : (query.second == node) ? query.first : NULL;
                if (other && visited[other]) {
                    result = findSet(other);
                    lcaResults[{query.first, query.second}] = result; //Store result
                    return; // Found for this query.
                }
            }
        };

        tarjanDFS(root);
        return result; // Return the LCA
    }
};

// Helper function to build a binary tree from a vector (for testing)
TreeNode* buildTree(const std::vector<int>& values, int index, int n) {
    if (index >= n || values[index] == -1) { // -1 represents NULL
        return NULL;
    }
    TreeNode* node = new TreeNode(values[index]);
    node->left = buildTree(values, 2 * index + 1, n);
    node->right = buildTree(values, 2 * index + 2, n);
    return node;
}

// Helper function to print the tree (for debugging)
void printTree(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    Solution sol;

    // Example tree:
    //       3
    //     /   \
    //    5     1
    //   / \   / \
    //  6   2  0  8
    //     / \
    //    7   4
    std::vector<int> treeValues = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}; // -1 for NULL
    TreeNode* root = buildTree(treeValues, 0, treeValues.size());
    TreeNode* p = root->left;  // Node 5
    TreeNode* q = root->right->left; // Node 0
    //printTree(root);

    // Test the different approaches
    std::cout << "Recursive Approach: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorRecursive(root, p, q)->val << std::endl;

    std::cout << "Iterative with Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterative(root, p, q)->val << std::endl;

    std::cout << "Iterative without Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterativeNoParent(root, p, q)->val << std::endl;

    std::cout << "Binary Lifting: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorBinaryLifting(root, p, q)->val << std::endl;

    std::cout << "Tarjan's Algorithm: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorTarjan(root, p, q)->val << std::endl;

    // Example with a different p and q
    p = root->left->right->left; // Node 7
    q = root->left->right->right; // Node 4
    std::cout << "Recursive Approach: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorRecursive(root, p, q)->val << std::endl;
    std::cout << "Iterative with Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterative(root, p, q)->val << std::endl;
    std::cout << "Iterative without Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterativeNoParent(root, p, q)->val << std::endl;
    std::cout << "Binary Lifting: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorBinaryLifting(root, p, q)->val << std::endl;
    std::cout << "Tarjan's Algorithm: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorTarjan(root, p, q)->val << std::endl;

    // Example where one node is the ancestor of the other
    p = root;
    q = root->left;
    std::cout << "Recursive Approach: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorRecursive(root, p, q)->val << std::endl;
    std::cout << "Iterative with Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterative(root, p, q)->val << std::endl;
    std::cout << "Iterative without Parent Pointers: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorIterativeNoParent(root, p, q)->val << std::endl;
    std::cout << "Binary Lifting: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorBinaryLifting(root, p, q)->val << std::endl;
    std::cout << "Tarjan's Algorithm: LCA(" << p->val << ", " << q->val << ") = "
              << sol.lowestCommonAncestorTarjan(root, p, q)->val << std::endl;

    return 0;
}

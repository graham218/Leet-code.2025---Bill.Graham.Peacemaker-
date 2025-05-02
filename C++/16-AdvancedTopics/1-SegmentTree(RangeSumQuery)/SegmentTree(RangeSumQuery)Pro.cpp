#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//-------------------------------------------
// 1. Basic Segment Tree Implementation (Static Array Input)
//-------------------------------------------
class SegmentTreeBasic {
    vector<int> tree;
    int n;

public:
    SegmentTreeBasic(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
        cout << "SegmentTreeBasic constructed." << endl;
    }

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int l, int r) {
        cout << "Basic Segment Tree Query: [" << l << ", " << r << "]" << endl;
        int result = queryUtil(0, 0, n - 1, l, r);
        cout << "Result: " << result << endl;
        return result;
    }

    int queryUtil(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return queryUtil(2 * node + 1, start, mid, l, r) +
               queryUtil(2 * node + 2, mid + 1, end, l, r);
    }
};

//-------------------------------------------
// 2. Lazy Propagation for Range Updates
//-------------------------------------------
class SegmentTreeLazy {
    vector<int> tree, lazy;
    int n;

public:
    SegmentTreeLazy(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(data, 0, 0, n - 1);
        cout << "SegmentTreeLazy constructed." << endl;
    }

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) tree[node] = data[start];
        else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void updateRange(int l, int r, int val) {
        cout << "Lazy Segment Tree Update Range: [" << l << ", " << r << "] with value " << val << endl;
        updateRangeUtil(0, 0, n - 1, l, r, val);
    }

    void updateRangeUtil(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (r < start || end < l) return;

        if (l <= start && end <= r) {
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRangeUtil(2 * node + 1, start, mid, l, r, val);
        updateRangeUtil(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int query(int l, int r) {
        cout << "Lazy Segment Tree Query: [" << l << ", " << r << "]" << endl;
        int result = queryUtil(0, 0, n - 1, l, r);
        cout << "Result: " << result << endl;
        return result;
    }

    int queryUtil(int node, int start, int end, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];

        int mid = (start + end) / 2;
        return queryUtil(2 * node + 1, start, mid, l, r) +
               queryUtil(2 * node + 2, mid + 1, end, l, r);
    }
};

//-------------------------------------------
// 3. Segment Tree with Point Updates (Real-time Analytics)
//-------------------------------------------
class SegmentTreePointUpdate {
    vector<int> tree;
    int n;

public:
    SegmentTreePointUpdate(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
        cout << "SegmentTreePointUpdate constructed." << endl;
    }

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) tree[node] = data[start];
        else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int idx, int val) {
        cout << "Point Update: Index " << idx << ", Value " << val << endl;
        updateUtil(0, 0, n - 1, idx, val);
    }

    void updateUtil(int node, int start, int end, int idx, int val) {
        if (start == end) tree[node] = val;
        else {
            int mid = (start + end) / 2;
            if (idx <= mid) updateUtil(2 * node + 1, start, mid, idx, val);
            else updateUtil(2 * node + 2, mid + 1, end, idx, val);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int l, int r) {
        cout << "Point Update Segment Tree Query: [" << l << ", " << r << "]" << endl;
        int result = queryUtil(0, 0, n - 1, l, r);
        cout << "Result: " << result << endl;
        return result;
    }

    int queryUtil(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return queryUtil(2 * node + 1, start, mid, l, r) +
               queryUtil(2 * node + 2, mid + 1, end, l, r);
    }
};

//-------------------------------------------
// 4. Dynamic Segment Tree (Large Sparse Arrays)
//-------------------------------------------
struct DynamicNode {
    int val = 0;
    DynamicNode *left = nullptr, *right = nullptr;
};

class SegmentTreeDynamic {
    DynamicNode* root;
    int start, end;

public:
    SegmentTreeDynamic(int start, int end) : start(start), end(end) {
        root = new DynamicNode();
        cout << "SegmentTreeDynamic constructed. Start: " << start << ", End: " << end << endl;
    }

    void update(DynamicNode* node, int l, int r, int idx, int val) {
        if (l == r) {
            node->val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            if (!node->left) node->left = new DynamicNode();
            update(node->left, l, mid, idx, val);
        } else {
            if (!node->right) node->right = new DynamicNode();
            update(node->right, mid + 1, r, idx, val);
        }
        node->val = (node->left ? node->left->val : 0) + (node->right ? node->right->val : 0);
    }

    void update(int idx, int val) {
        cout << "Dynamic Segment Tree Update: Index " << idx << ", Value " << val << endl;
        update(root, start, end, idx, val);
    }

    int query(DynamicNode* node, int l, int r, int ql, int qr) {
        if (!node || ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return node->val;
        int mid = (l + r) / 2;
        return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
    }

    int query(int l, int r) {
        cout << "Dynamic Segment Tree Query: [" << l << ", " << r << "]" << endl;
        int result = query(root, start, end, l, r);
        cout << "Result: " << result << endl;
        return result;
    }
};

//-------------------------------------------
// 5. Persistent Segment Tree (Versioned Queries)
//-------------------------------------------
struct PSTNode {
    int sum;
    PSTNode *left, *right;

    PSTNode(int val = 0) : sum(val), left(nullptr), right(nullptr) {}
};

class PersistentSegmentTree {
    vector<PSTNode*> versions;
    int n;

    PSTNode* build(const vector<int>& data, int l, int r) {
        if (l == r) return new PSTNode(data[l]);
        int mid = (l + r) / 2;
        PSTNode* left = build(data, l, mid);
        PSTNode* right = build(data, mid + 1, r);
        PSTNode* node = new PSTNode(left->sum + right->sum);
        node->left = left;
        node->right = right;
        return node;
    }

    PSTNode* update(PSTNode* node, int l, int r, int idx, int val) {
        if (l == r) return new PSTNode(val);
        int mid = (l + r) / 2;
        PSTNode* newNode = new PSTNode();
        if (idx <= mid) {
            newNode->left = update(node->left, l, mid, idx, val);
            newNode->right = node->right;
        } else {
            newNode->left = node->left;
            newNode->right = update(node->right, mid + 1, r, idx, val);
        }
        newNode->sum = newNode->left->sum + newNode->right->sum;
        return newNode;
    }

    int query(PSTNode* node, int l, int r, int ql, int qr) {
        if (!node || qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return node->sum;
        int mid = (l + r) / 2;
        return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
    }

public:
    PersistentSegmentTree(const vector<int>& data) {
        n = data.size();
        versions.push_back(build(data, 0, n - 1));
        cout << "PersistentSegmentTree constructed." << endl;
    }

    void update(int version, int idx, int val) {
        cout << "Persistent Segment Tree Update: Version " << version << ", Index " << idx << ", Value " << val << endl;
        versions.push_back(update(versions[version], 0, n - 1, idx, val));
    }

    int query(int version, int l, int r) {
        cout << "Persistent Segment Tree Query: Version " << version << ", Range [" << l << ", " << r << "]" << endl;
        int result = query(versions[version], 0, n - 1, l, r);
        cout << "Result: " << result << endl;
        return result;
    }
};

int main() {
    // Example Usage
    vector<int> data = {1, 3, 5, 7, 9, 11};

    // 1. Basic Segment Tree
    SegmentTreeBasic stBasic(data);
    stBasic.query(1, 3); // Output: 15

    // 2. Segment Tree with Lazy Propagation
    SegmentTreeLazy stLazy(data);
    stLazy.updateRange(1, 3, 2); // Add 2 to elements from index 1 to 3
    stLazy.query(1, 3); // Output: 21 (5 + 9 + 7)

    // 3. Segment Tree with Point Updates
    SegmentTreePointUpdate stPoint(data);
    stPoint.update(2, 10); // Update element at index 2 to 10
    stPoint.query(1, 3); // Output: 20 (3 + 10 + 7)

    // 4. Dynamic Segment Tree
    SegmentTreeDynamic stDynamic(0, 1000000); // Start and end range
    stDynamic.update(500000, 15);
    stDynamic.update(750000, 20);
    stDynamic.query(499990, 750010); // Output: 35

    // 5. Persistent Segment Tree
    PersistentSegmentTree pst(data);
    pst.update(0, 2, 15); // Create version 1 with update at index 2
    pst.update(1, 4, 25); // Create version 2 based on version 1
    pst.query(0, 1, 4); // Query version 0: Output: 25
    pst.query(1, 1, 4); // Query version 1: Output: 30
    pst.query(2, 1, 4); // Query version 2: Output: 40

    return 0;
}

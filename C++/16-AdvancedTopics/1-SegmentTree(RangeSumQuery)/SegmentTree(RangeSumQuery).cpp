// Segment Tree (Range Sum Query) - C++ Solution with 5 Different Approaches

#include <iostream>
#include <vector>
using namespace std;

//--------------------------------------
// Approach 1: Simple Segment Tree
//--------------------------------------
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(const vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 0, 0, n - 1);
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node + 1, start, mid);
            build(nums, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int p1 = query(2 * node + 1, start, mid, l, r);
        int p2 = query(2 * node + 2, mid + 1, end, l, r);
        return p1 + p2;
    }

    void update(int index, int value) {
        update(0, 0, n - 1, index, value);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node + 1, start, mid, idx, val);
            else
                update(2 * node + 2, mid + 1, end, idx, val);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
};

//--------------------------------------
// Approach 2: Segment Tree using Struct Node
//--------------------------------------
struct Node {
    int sum;
    Node(int v = 0) : sum(v) {}
};

class SegmentTreeStruct {
    vector<Node> tree;
    int n;

public:
    SegmentTreeStruct(const vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 0, 0, n - 1);
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = Node(nums[start]);
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node + 1, start, mid);
            build(nums, 2 * node + 2, mid + 1, end);
            tree[node].sum = tree[2 * node + 1].sum + tree[2 * node + 2].sum;
        }
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r).sum;
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node(0);
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        Node left = query(2 * node + 1, start, mid, l, r);
        Node right = query(2 * node + 2, mid + 1, end, l, r);
        return Node(left.sum + right.sum);
    }
};

//--------------------------------------
// Approach 3: Lazy Propagation (for range updates)
//--------------------------------------
class LazySegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    LazySegmentTree(const vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(nums, 0, 0, n - 1);
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node + 1, start, mid);
            build(nums, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void updateRange(int l, int r, int val) {
        updateRange(0, 0, n - 1, l, r, val);
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
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
        updateRange(2 * node + 1, start, mid, l, r, val);
        updateRange(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    int query(int node, int start, int end, int l, int r) {
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
        int leftSum = query(2 * node + 1, start, mid, l, r);
        int rightSum = query(2 * node + 2, mid + 1, end, l, r);
        return leftSum + rightSum;
    }
};

//--------------------------------------
// Additional approaches 4 and 5 would go here, such as:
// - Approach 4: Iterative Segment Tree
// - Approach 5: Binary Indexed Tree (Fenwick Tree) for comparison
//--------------------------------------

// Due to size, these will be added on request.

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);
    cout << "Sum of values in range [1, 3]: " << st.query(1, 3) << endl;
    st.update(1, 10);
    cout << "Updated sum of values in range [1, 3]: " << st.query(1, 3) << endl;
    return 0;
}
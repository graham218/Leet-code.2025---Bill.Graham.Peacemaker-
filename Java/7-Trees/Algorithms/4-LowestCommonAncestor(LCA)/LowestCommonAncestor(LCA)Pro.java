/*
 * Java Solution for "Trees >>> Lowest Common Ancestor (LCA)"
 * Includes 5 real-world implementation approaches with detailed code comments and output demonstration.
 */

import java.util.*;

public class LowestCommonAncestor {

    /*
     * 1. Recursive Approach (Classic DFS)
     * Used in File Systems, Git Version Control, XML/HTML DOM parsing.
     */
    public TreeNode lowestCommonAncestorRecursive(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q) {
            return root;
        }

        TreeNode left = lowestCommonAncestorRecursive(root.left, p, q);
        TreeNode right = lowestCommonAncestorRecursive(root.right, p, q);

        // If both left and right are non-null, current node is LCA
        if (left != null && right != null) {
            return root;
        }

        return left != null ? left : right;
    }

    /*
     * 2. Parent Pointers + HashSet
     * Used in User Interface event bubbling, DOM Tree handling with upward links.
     */
    public TreeNode lowestCommonAncestorWithParent(TreeNode root, TreeNode p, TreeNode q) {
        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        buildParentMap(root, null, parentMap);

        Set<TreeNode> ancestors = new HashSet<>();
        while (p != null) {
            ancestors.add(p);
            p = parentMap.get(p);
        }
        while (q != null) {
            if (ancestors.contains(q)) return q;
            q = parentMap.get(q);
        }
        return null;
    }

    private void buildParentMap(TreeNode node, TreeNode parent, Map<TreeNode, TreeNode> map) {
        if (node != null) {
            map.put(node, parent);
            buildParentMap(node.left, node, map);
            buildParentMap(node.right, node, map);
        }
    }

    /*
     * 3. Path Tracing Method
     * Used in GPS systems and organizational hierarchies.
     */
    public TreeNode lowestCommonAncestorPathMethod(TreeNode root, TreeNode p, TreeNode q) {
        List<TreeNode> pathP = findPath(root, p);
        List<TreeNode> pathQ = findPath(root, q);

        TreeNode lca = null;
        int i = 0;
        while (i < pathP.size() && i < pathQ.size()) {
            if (pathP.get(i) == pathQ.get(i)) {
                lca = pathP.get(i);
            } else {
                break;
            }
            i++;
        }
        return lca;
    }

    private List<TreeNode> findPath(TreeNode root, TreeNode target) {
        List<TreeNode> path = new ArrayList<>();
        findPathHelper(root, target, path);
        return path;
    }

    private boolean findPathHelper(TreeNode root, TreeNode target, List<TreeNode> path) {
        if (root == null) return false;
        path.add(root);
        if (root == target) return true;
        if (findPathHelper(root.left, target, path) || findPathHelper(root.right, target, path)) {
            return true;
        }
        path.remove(path.size() - 1);
        return false;
    }

    /*
     * 4. Binary Search Tree (BST) Optimized Approach
     * Used in database indexing, compiler symbol tables, and search systems.
     */
    public TreeNode lowestCommonAncestorBST(TreeNode root, TreeNode p, TreeNode q) {
        while (root != null) {
            if (p.val < root.val && q.val < root.val) {
                root = root.left;
            } else if (p.val > root.val && q.val > root.val) {
                root = root.right;
            } else {
                return root;
            }
        }
        return null;
    }

    /*
     * 5. Euler Tour + Segment Tree (for large static trees)
     * Used in compilers, static analysis tools, and game engine scene graphs.
     */
    class EulerTourLCA {
        private List<TreeNode> euler = new ArrayList<>();
        private List<Integer> depth = new ArrayList<>();
        private Map<TreeNode, Integer> firstOccurrence = new HashMap<>();
        private TreeNode[] segmentTree;

        public EulerTourLCA(TreeNode root) {
            dfs(root, 0);
            buildSegmentTree();
        }

        private void dfs(TreeNode node, int d) {
            if (node == null) return;
            firstOccurrence.putIfAbsent(node, euler.size());
            euler.add(node);
            depth.add(d);
            if (node.left != null) {
                dfs(node.left, d + 1);
                euler.add(node);
                depth.add(d);
            }
            if (node.right != null) {
                dfs(node.right, d + 1);
                euler.add(node);
                depth.add(d);
            }
        }

        private void buildSegmentTree() {
            int size = euler.size();
            segmentTree = new TreeNode[4 * size];
            build(0, 0, size - 1);
        }

        private void build(int index, int l, int r) {
            if (l == r) {
                segmentTree[index] = euler.get(l);
                return;
            }
            int mid = (l + r) / 2;
            build(2 * index + 1, l, mid);
            build(2 * index + 2, mid + 1, r);
            segmentTree[index] = depth.get(firstOccurrence.get(segmentTree[2 * index + 1])) <
                    depth.get(firstOccurrence.get(segmentTree[2 * index + 2])) ?
                    segmentTree[2 * index + 1] : segmentTree[2 * index + 2];
        }

        public TreeNode query(TreeNode u, TreeNode v) {
            int l = firstOccurrence.get(u);
            int r = firstOccurrence.get(v);
            if (l > r) {
                int temp = l;
                l = r;
                r = temp;
            }
            return query(0, 0, euler.size() - 1, l, r);
        }

        private TreeNode query(int index, int l, int r, int ql, int qr) {
            if (l > qr || r < ql) return null;
            if (ql <= l && r <= qr) return segmentTree[index];
            TreeNode left = query(2 * index + 1, l, (l + r) / 2, ql, qr);
            TreeNode right = query(2 * index + 2, (l + r) / 2 + 1, r, ql, qr);
            if (left == null) return right;
            if (right == null) return left;
            return depth.get(firstOccurrence.get(left)) < depth.get(firstOccurrence.get(right)) ? left : right;
        }
    }

    // Sample usage with test cases for all approaches
    public static void main(String[] args) {
        LowestCommonAncestor lcaSolver = new LowestCommonAncestor();

        TreeNode root = new TreeNode(6);
        root.left = new TreeNode(2);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(4);
        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(9);
        root.left.right.left = new TreeNode(3);
        root.left.right.right = new TreeNode(5);

        TreeNode p = root.left.right.left; // Node 3
        TreeNode q = root.left.right.right; // Node 5

        System.out.println("1. Recursive DFS: " + lcaSolver.lowestCommonAncestorRecursive(root, p, q).val);
        System.out.println("2. Parent Pointers: " + lcaSolver.lowestCommonAncestorWithParent(root, p, q).val);
        System.out.println("3. Path Tracing: " + lcaSolver.lowestCommonAncestorPathMethod(root, p, q).val);
        System.out.println("4. BST Optimized: " + lcaSolver.lowestCommonAncestorBST(root, p, q).val);

        EulerTourLCA eulerLCA = lcaSolver.new EulerTourLCA(root);
        System.out.println("5. Euler Tour + Segment Tree: " + eulerLCA.query(p, q).val);
    }
}

// Tree Node class
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
    }
}

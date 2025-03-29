from typing import Optional, List, Dict

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None, parent=None):
        """
        Initializes a TreeNode object.

        Args:
            val (int): The value of the node. Defaults to 0.
            left (Optional[TreeNode]): The left child of the node. Defaults to None.
            right (Optional[TreeNode]): The right child of the node. Defaults to None.
            parent (Optional[TreeNode]):  The parent of the node. Defaults to None.
        """
        self.val = val
        self.left = left
        self.right = right
        self.parent = parent  # Added parent reference

# Function to set parent references
def set_parents(node: Optional[TreeNode], parent: Optional[TreeNode] = None) -> None:
    """
    Sets the parent references for each node in a binary tree.  This is necessary for
    approaches that utilize parent pointers.  It performs a depth-first traversal.

    Args:
        node (Optional[TreeNode]): The current node being processed.
        parent (Optional[TreeNode]): The parent of the current node. Defaults to None for the root.
    """
    if node:
        node.parent = parent  # Set the parent of the current node
        set_parents(node.left, node)  # Recursively set parents for the left subtree
        set_parents(node.right, node)  # Recursively set parents for the right subtree

# Approach 1: Recursive LCA with Path Tracing
def lca_recursive_path(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    using a recursive approach.  This method traces the paths from the root to 'p' and
    'q' and then finds the last common node in those paths.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of 'p' and 'q', or None if either node is not in the tree.
    """
    path_p, path_q = [], []  # Lists to store paths from root to p and q

    def find_path(node: Optional[TreeNode], target: TreeNode, path: List[TreeNode]) -> bool:
        """
        Recursively searches for a path from the current node to the target node.

        Args:
            node (Optional[TreeNode]): The current node in the traversal.
            target (TreeNode): The target node to find the path to.
            path (List[TreeNode]): The list representing the path being built.

        Returns:
            bool: True if a path to the target is found, False otherwise.
        """
        if not node:
            return False  # Base case: if the node is None, no path found
        path.append(node)  # Add the current node to the path
        if node == target:
            return True  # Base case: if the current node is the target, path found
        # Recursively search in left and right subtrees
        if find_path(node.left, target, path) or find_path(node.right, target, path):
            return True  # If path found in either subtree, return True
        path.pop()  # If target not found in this subtree, remove the node from the path
        return False  # Path not found

    find_path(root, p, path_p)  # Find the path from root to p
    find_path(root, q, path_q)  # Find the path from root to q

    lca = None
    # Iterate through the paths to find the last common node
    for u, v in zip(path_p, path_q):
        if u == v:
            lca = u  # Update LCA if nodes are the same
        else:
            break  # Stop when the paths diverge
    return lca  # Return the last common node

# Approach 2: LCA Using Ancestor Hashing
def lca_ancestor_hashing(p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    using ancestor hashing.  This method assumes that each node has a pointer to its
    parent.  It works by collecting all ancestors of 'p' into a set and then traversing
    the ancestors of 'q' to find the first one present in the set.

    Args:
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of 'p' and 'q', or None if no common ancestor exists.
    """
    ancestor_set = set()  # Set to store ancestors of p
    while p:
        ancestor_set.add(p)  # Add p and its ancestors to the set
        p = p.parent
    while q:
        if q in ancestor_set:
            return q  # Return the first ancestor of q that is also an ancestor of p
        q = q.parent
    return None  # Return None if no common ancestor is found

# Approach 3: LCA Using Stack Iteration
def lca_stack(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    using stack iteration.  This method performs an iterative depth-first traversal
    using a stack to keep track of the path to each node.  It stores the path to each
    node and then finds the LCA by comparing the paths to 'p' and 'q'.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of 'p' and 'q', or None if either node is not in the tree.
    """
    stack = [(root, [])]  # Stack to store (node, path) pairs
    paths = {}  # Dictionary to store paths to each node
    while stack:
        node, path = stack.pop()
        if node:
            new_path = path + [node]  # Extend the path with the current node
            paths[node] = new_path  # Store the path to the current node
            stack.append((node.right, new_path))  # Push right child and its path
            stack.append((node.left, new_path))  # Push left child and its path

    path_p, path_q = paths[p], paths[q]  # Get the paths to p and q
    lca = None
    # Iterate through the paths to find the last common node
    for u, v in zip(path_p, path_q):
        if u == v:
            lca = u
        else:
            break
    return lca

# Approach 4: LCA with Depth Adjustment
def lca_adjust_depth(p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    by adjusting the depths of the two nodes.  This method assumes that each node has
    a pointer to its parent.  It brings the deeper node to the same depth as the
    shallower node and then iterates upwards until the two nodes meet.

    Args:
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of 'p' and 'q', or None if no common ancestor exists.
    """
    depth_map = {}  # Dictionary to store node depths

    def compute_depth(node: Optional[TreeNode]) -> int:
        """
        Computes the depth of a node recursively.

        Args:
            node (Optional[TreeNode]): The node to compute the depth of.

        Returns:
            int: The depth of the node.
        """
        if not node:
            return -1  # Base case: depth of None is -1
        if node not in depth_map:
            depth_map[node] = compute_depth(node.parent) + 1  # Depth is parent's depth + 1
        return depth_map[node]

    compute_depth(p)  # Compute depth of p
    compute_depth(q)  # Compute depth of q

    # Bring the deeper node to the same level as the shallower node
    while depth_map[p] > depth_map[q]:
        p = p.parent
    while depth_map[q] > depth_map[p]:
        q = q.parent

    # Iterate upwards until the two nodes meet
    while p != q:
        p, q = p.parent, q.parent
    return p  # Return the common ancestor

# Approach 5: LCA Using Binary Lifting
def preprocess_lca(root: Optional[TreeNode]) -> (Dict[TreeNode, Optional[TreeNode]], Dict[TreeNode, int], Dict[TreeNode, List[Optional[TreeNode]]]):
    """
    Preprocesses the binary tree for finding LCA using the binary lifting technique.
    This method computes the parent of each node, the depth of each node, and a table
    of ancestors for each node.  The ancestor table stores the 2^i-th ancestor of each node.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        tuple: A tuple containing:
            - Dict[TreeNode, Optional[TreeNode]]: A dictionary mapping nodes to their parents.
            - Dict[TreeNode, int]: A dictionary mapping nodes to their depths.
            - Dict[TreeNode, List[Optional[TreeNode]]]: A dictionary mapping nodes to their 2^i-th ancestors.
    """
    parent = {}  # Map node to its parent
    depth = {}  # Map node to its depth
    ancestors = {}  # Map node to its 2^i-th ancestors

    stack = [(root, None, 0)]  # Stack for iterative DFS: (node, parent, depth)
    while stack:
        node, par, d = stack.pop()
        if node:
            parent[node] = par
            depth[node] = d
            ancestors[node] = [None] * 20  # Initialize ancestor table (2^0, 2^1, ..., 2^19)
            ancestors[node][0] = par  # 2^0th ancestor is the parent
            # Compute 2^i-th ancestors using dynamic programming
            for i in range(1, 20):
                if ancestors[node][i - 1]:
                    ancestors[node][i] = ancestors[node][i - 1].parent if ancestors[node][i - 1] else None
            stack.append((node.right, node, d + 1))  # Push right child
            stack.append((node.left, node, d + 1))  # Push left child
    return parent, depth, ancestors

def lca_binary_lifting(p: TreeNode, q: TreeNode, parent: Dict[TreeNode, Optional[TreeNode]],
                       depth: Dict[TreeNode, int], ancestors: Dict[TreeNode, List[Optional[TreeNode]]]) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' using the precomputed
    ancestor information from `preprocess_lca`.  This method efficiently finds the LCA by
    iteratively moving the deeper node up to the same level as the shallower node and
    then moving both nodes up in parallel until they meet.

    Args:
        p (TreeNode): The first node.
        q (TreeNode): The second node.
        parent (Dict[TreeNode, Optional[TreeNode]]): Parent mapping from preprocessing.
        depth (Dict[TreeNode, int]): Depth mapping from preprocessing.
        ancestors (Dict[TreeNode, List[Optional[TreeNode]]]): Ancestor table from preprocessing.

    Returns:
        Optional[TreeNode]: The LCA of 'p' and 'q'.
    """
    if depth[p] < depth[q]:
        p, q = q, p  # Ensure p is deeper
    diff = depth[p] - depth[q]
    # Bring p to the same level as q
    for i in range(20):
        if diff & (1 << i):
            p = ancestors[p][i]
    if p == q:
        return p  # If they are the same, that's the LCA
    # Move p and q up in parallel until they meet
    for i in range(19, -1, -1):
        if ancestors[p][i] != ancestors[q][i]:
            p, q = ancestors[p][i], ancestors[q][i]
    return parent[p]  # The parent of p (or q) is the LCA

# Sample Tree Setup
tree = TreeNode(3, TreeNode(5, TreeNode(6), TreeNode(2, TreeNode(7), TreeNode(4))),
                TreeNode(1, TreeNode(0), TreeNode(8)))
set_parents(tree)  # Ensure parent pointers are set
p, q = tree.left, tree.left.right.right  # Nodes 5 and 4

# Execute LCA Methods
print("Recursive Path LCA:", lca_recursive_path(tree, p, q).val)
print("Ancestor Hashing LCA:", lca_ancestor_hashing(p, q).val)
print("Stack Iterative LCA:", lca_stack(tree, p, q).val)
print("LCA with Depth Adjustment:", lca_adjust_depth(p, q).val)

# Preprocessing for Binary Lifting
parent_map, depth_map, ancestors_map = preprocess_lca(tree)
print("Binary Lifting LCA:", lca_binary_lifting(p, q, parent_map, depth_map, ancestors_map).val)
